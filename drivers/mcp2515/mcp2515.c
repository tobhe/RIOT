/*
 * Copyright (C) 2017 Tobias Heider    <heidert@nm.ifi.lmu.de>
 * Copyright (C) 2017 Johannes Walcher <johannes.walcher@tum.de>
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup     drivers_mcp2515
 * @{
 *
 * @file
 * @brief       Implementation of public functions for mcp2515 drivers
 *
 * @author      Tobias Heider    <heidert@nm.ifi.lmu.de>
 * @author      Johannes Walcher <johannes.walcher@tum.de>
 *
 * @}
 */

#define ENABLE_DEBUG    (0)
#include "debug.h"

#include <mcp2515.h>

#include "mcp2515_internal.h"

extern mcp2515_t mcp2515;

static int _init(candev_t *candev);
static int _send(candev_t *candev, const struct can_frame *frame);
static void _isr(candev_t *candev);
static int _set(candev_t *candev, canopt_t opt, void *value, size_t value_len);
static int _get(candev_t *candev, canopt_t opt, void *value, size_t max_len);
static int _abort(candev_t *candev, const struct can_frame *frame);
static int _set_filter(candev_t *candev, const struct can_filter *filter);
static int _remove_filter(candev_t *candev, const struct can_filter *filter);
static int _power_up(candev_t *candev);
static int _power_down(candev_t *candev);

static void mcp2515_init(mcp2515_t *dev, void);
static void mcp2515_reset(mcp2515_t *dev, void);
static void mcp2515_read(mcp2515_t *dev, uint8_t addr, uint8_t *rx, uint16_t size);
static void mcp2515_write(mcp2515_t *dev, uint8_t addr, uint8_t *tx, uint16_t size);
static void mcp2515_read_rx(mcp2515_t *dev, uint8_t mode, uint8_t *rx, uint16_t size);
static void mcp2515_write_tx(mcp2515_t *dev, uint8_t mode, uint8_t *tx, uint16_t size);
static void mcp2515_bit_modify(mcp2515_t *dev, uint8_t addr, uint8_t mask, uint8_t data);
static uint8_t mcp2515_read_status(mcp2515_t *dev);
static uint8_t mcp2515_rx_status(mcp2515_t *dev);


static const candev_driver_t candev_mcp2515_driver = {
	.send = _send,
	.init = _init,
	.isr = _isr,
	.get = _get,
	.set = _set,
	.abort = _abort,
	.set_filter = _set_filter,
	.remove_filter = _remove_filter,
};

void mcp215_init(mpc2515_t *dev) {
	spi_acquire(dev->spi, dev->cs, SPI_MODE_3, SPI_CLK_1MHZ);
	DEBUG("Initializing MCP2515...\n");
}

void mcp2515_reset(mcp2515 *dev) {
	spi_acquire(dev->spi);
	spi_transfer_byte(dev->spi, dev->cs, false, MCP2515_SPI_RESET);
	spi_release(dev->spi);
}

void mcp2515_rts(mcp2515 *dev, uint8_t mode) {
	spi_acquire(dev->spi);
	uint8_t c = MCP2515_SPI_RTS | mode;
	spi_transfer_byte(dev->spi, dev->cs, false, c);
	spi_release(dev->spi);
}

void mcp2515_write(mcp2515 *dev,
                   uint8_t addr,
                   uint8_t *tx,
                   uint16_t size)
{
	spi_acquire(dev->spi);
	spi_transfer_byte(dev->spi, dev->cs, true, MCP2515_SPI_WRITE);
	spi_transfer_byte(dev->spi, dev->cs, true, addr);
	spi_transfer_bytes(dev->spi, dev->cs, false, tx, NULL, size);
	spi_release(dev->spi);
}

void mcp2515_read(mcp2515_t *dev,
                  uint8_t addr,
                  uint8_t *rx,
                  uint16_t size)
{
	spi_acquire(dev->spi);
	spi_transfer_byte(dev->spi, dev->cs, true, MCP2515_SPI_READ);
	spi_transfer_byte(dev->spi, dev->cs, true, addr);
	spi_transfer_bytes(dev->spi, dev->cs, false, NULL, rx, size);
	spi_release(dev->spi);
}

void mcp2515_read_rx(mcp2515_t *dev,
                     uint8_t mode,
                     uint8_t *rx,
                     uint16_t size)
{
	spi_acquire(dev->spi);
	uint8_t c = MCP2515_SPI_READ_RX | mode;
	spi_transfer_byte(dev->spi, dev->cs, true, c);
	spi_transfer_bytes(dev->spi, dev->cs, false, NULL, rx, size);
	spi_release(dev->spi);
}

void mcp2515_write_tx(mcp2515_t *dev,
                      uint8_t mode,
                      uint8_t *tx,
                      uint16_t size)
{
	spi_acquire(dev->spi);
	uint8_t c = SPI_WRITE_TX | mode;
	spi_transfer_byte(dev->spi, dev->cs, true, c);
	spi_transfer_bytes(dev->spi, dev->cs, false, tx, NULL, size);
	spi_release(dev->spi);
}


uint8_t mcp2515_read_status(mcp2515_t *dev) {
	spi_acquire(dev->spi);
	spi_transfer_byte(dev->spi, dev->cs, true, MCP2515_SPI_READ_STATUS);
	uint8_t ret = spi_transfer_byte(dev->spi, dev->cs, false, c);
	spi_release(dev->spi);
	return ret;
}

uint8_t mcp2515_read_rx_status(mcp2515_t *dev) {
	spi_acquire(dev->spi);
	spi_transfer_byte(dev->spi, dev->cs, true, MCP2515_SPI_RX_STATUS);
	uint8_t ret = spi_transfer_byte(dev->spi, dev->cs, false, c);
	spi_release(dev->spi);
	return ret;
}

void mcp2515_bit_modify(mcp2515_t *dev,
                        uint8_t addr,
                        uint8_t mask,
                        uint8_t data)
{
	spi_acquire(dev->spi);
	spi_transfer_byte(dev->spi, dev->cs, true, MCP2515_SPI_BIT_MODIFY);
	spi_transfer_byte(dev->spi, dev->cs, true, mask);
	spi_transfer_byte(dev->spi, dev->cs, false, data);
	spi_release(dev->spi);
}


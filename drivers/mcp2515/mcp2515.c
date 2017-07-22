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

static const candev_driver_t candev_linux_driver = {
  .send = _send,
  .init = _init,
  .isr = _isr,
  .get = _get,
  .set = _set,
  .abort = _abort,
  .set_filter = _set_filter,
  .remove_filter = _remove_filter,
};

void mcp215_spi_init(mpc2515_t *dev) {
  spi_acquire(dev->spi, dev->cs, SPI_MODE_3, SPI_CLK_1MHZ);
  DEBUG("Initializing MCP2515...\n");
}


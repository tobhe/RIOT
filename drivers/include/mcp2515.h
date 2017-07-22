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

#ifndef MCP2515_H
#define MCP2515_H

#ifdef __cplusplus
extern "C" {
#endif

#include "periph/spi.h"

typedef struct {
	candev_t candev;
	spi_t spi;
	spi_clk_t clk;
	spi_cs_t cs;
	gpio_t int_pin;
} mcp2515_t;

void mcp2515_init(mcp2515_t *);


#ifdef __cplusplus
}
#endif
#endif

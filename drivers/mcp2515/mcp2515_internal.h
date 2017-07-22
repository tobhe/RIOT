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
 * This file defines all register and command mappings and constants for the
 * mcp2515 chip.
 *
 * @author      Tobias Heider    <heidert@nm.ifi.lmu.de>
 * @author      Johannes Walcher <johannes.walcher@tum.de>
 *
 * @}
 */

#ifndef MCP2515_INTERNAL_H
#define MCP2515_INTERNAL_H

#ifdef __cplusplus
extern "C" {
#endif

#define MCP2515_SPI_RESET         (0xC0)
#define MCP2515_SPI_READ          (0x03)
#define MCP2515_SPI_READ_RX       (0x90)
#define MCP2515_SPI_WRITE         (0x02)
#define MCP2515_SPI_WRITE_TX      (0x40)
#define MCP2515_SPI_RTS           (0x80)
#define MCP2515_SPI_READ_STATUS   (0xA0)
#define MCP2515_SPI_RX_STATUS     (0xB0)
#define MCP2515_SPI_BIT_MODIFY    (0x05)

#define MCP2515_READ_MODE_B0_SID  (0x0)
#define MCP2515_READ_MODE_B0_DATA (0x2)
#define MCP2515_READ_MODE_B1_SID  (0x4)
#define MCP2515_READ_MODE_B1_DATA (0x6)

#define MCP2515_WRITE_MODE_B0_SID  (0x0)
#define MCP2515_WRITE_MODE_B0_DATA (0x1)
#define MCP2515_WRITE_MODE_B1_SID  (0x2)
#define MCP2515_WRITE_MODE_B1_DATA (0x3)
#define MCP2515_WRITE_MODE_B2_SID  (0x4)
#define MCP2515_WRITE_MODE_B2_DATA (0x5)

#define MCP2515_RTS_MODE_T0 (0x0)
#define MCP2515_RTS_MODE_T1 (0x2)
#define MCP2515_RTS_MODE_T2 (0x4)

enum MCP2515_REGISTERS {
	MCP2515_RXF0SIDH = 0x00,
	MCP2515_RXF0SIDL,
	MCP2515_RXF0EID8,
	MCP2515_RXF0EID0,
	MCP2515_RXF1SIDH,
	MCP2515_RXF1SIDL,
	MCP2515_RXF1EID8,
	MCP2515_RXF1EID0,
	MCP2515_RXF2SIDH,
	MCP2515_RXF2SIDL,
	MCP2515_RXF2EID8,
	MCP2515_RXF2EID0,
	MCP2515_BFPCTRL,
	MCP2515_TXRTSCTRL,
	MCP2515_CANSTAT,
	MCP2515_CANCTRL,
	MCP2515_RXF3SIDH = 0x10,
	MCP2515_RXF3SIDL,
	MCP2515_RXF3EID8,
	MCP2515_RXF3EID0,
	MCP2515_RXF4SIDH,
	MCP2515_RXF4SIDL,
	MCP2515_RXF4EID8,
	MCP2515_RXF4EID0,
	MCP2515_RXF5SIDH,
	MCP2515_RXF5SIDL,
	MCP2515_RXF5EID8,
	MCP2515_RXF5EID0,
	MCP2515_TEC,
	MCP2515_REC,
	//	MCP2515_CANSTAT,
	//	MCP2515_CANCTRL,
	MCP2515_RXM0SIDH = 0x20,
	MCP2515_RXM0SIDL,
	MCP2515_RXM0EID8,
	MCP2515_RXM0EID0,
	MCP2515_RXM1SIDH,
	MCP2515_RXM1SIDL,
	MCP2515_RXM1EID8,
	MCP2515_RXM1EID0,
	MCP2515_CNF3,
	MCP2515_CNF2,
	MCP2515_CNF1,
	MCP2515_CANINTE,
	MCP2515_CANINTF,
	MCP2515_EFLG,
	//	MCP2515_CANSTAT,
	//	MCP2515_CANCTRL,
	MCP2515_TXB0CTRL = 0x30,
	MCP2515_TXB0SIDH,
	MCP2515_TXB0SIDL,
	MCP2515_TXB0EID8,
	MCP2515_TXB0EID0,
	MCP2515_TXB0DLC,
	MCP2515_TXB0D0,
	MCP2515_TXB0D1,
	MCP2515_TXB0D2,
	MCP2515_TXB0D3,
	MCP2515_TXB0D4,
	MCP2515_TXB0D5,
	MCP2515_TXB0D6,
	MCP2515_TXB0D7,
	//	MCP2515_CANSTAT,
	//	MCP2515_CANCTRL,
	MCP2515_TXB1CTRL = 0x40,
	MCP2515_TXB1SIDH,
	MCP2515_TXB1SIDL,
	MCP2515_TXB1EID8,
	MCP2515_TXB1EID0,
	MCP2515_TXB1DLC,
	MCP2515_TXB1D0,
	MCP2515_TXB1D1,
	MCP2515_TXB1D2,
	MCP2515_TXB1D3,
	MCP2515_TXB1D4,
	MCP2515_TXB1D5,
	MCP2515_TXB1D6,
	MCP2515_TXB1D7,
	//	MCP2515_CANSTAT,
	//	MCP2515_CANCTRL,
	MCP2515_TXB2CTRL = 0x50,
	MCP2515_TXB2SIDH,
	MCP2515_TXB2SIDL,
	MCP2515_TXB2EID8,
	MCP2515_TXB2EID0,
	MCP2515_TXB2DLC,
	MCP2515_TXB2D0,
	MCP2515_TXB2D1,
	MCP2515_TXB2D2,
	MCP2515_TXB2D3,
	MCP2515_TXB2D4,
	MCP2515_TXB2D5,
	MCP2515_TXB2D6,
	MCP2515_TXB2D7,
	//	MCP2515_CANSTAT,
	//	MCP2515_CANCTRL,
	MCP2515_RXB0CTRL = 0x60,
	MCP2515_RXB0SIDH,
	MCP2515_RXB0SIDL,
	MCP2515_RXB0EID8,
	MCP2515_RXB0EID0,
	MCP2515_RXB0DLC,
	MCP2515_RXB0D0,
	MCP2515_RXB0D1,
	MCP2515_RXB0D2,
	MCP2515_RXB0D3,
	MCP2515_RXB0D4,
	MCP2515_RXB0D5,
	MCP2515_RXB0D6,
	MCP2515_RXB0D7,
//	MCP2515_CANSTAT,
//	MCP2515_CANCTRL,
	MCP2515_RXB1CTRL = 0x70,
	MCP2515_RXB1SIDH,
	MCP2515_RXB1SIDL,
	MCP2515_RXB1EID8,
	MCP2515_RXB1EID0,
	MCP2515_RXB1DLC,
	MCP2515_RXB1D0,
	MCP2515_RXB1D1,
	MCP2515_RXB1D2,
	MCP2515_RXB1D3,
	MCP2515_RXB1D4,
	MCP2515_RXB1D5,
	MCP2515_RXB1D6,
	MCP2515_RXB1D7,
//	MCP2515_CANSTAT,
//	MCP2515_CANCTRL,
};

#endif // MCP2515_INTERNAL_H

#ifdef __cplusplus
}
#endif
#endif

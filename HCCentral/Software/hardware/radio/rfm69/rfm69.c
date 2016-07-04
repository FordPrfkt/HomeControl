/*
*
* Copyright (c) 2016 by Daniel Walter <fordprfkt@googlemail.com>
*
* This program is free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* as published by the Free Software Foundation; either version 3
* of the License, or (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; if not, write to the Free Software
* Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*
* For more information on the GPL, please go to:
* http://www.gnu.org/copyleft/gpl.html
*/

#include <stdio.h>
#include <stdlib.h>
#include <util/delay.h>
#include "config.h"
#include "core/heartbeat.h"
#include "core/bit-macros.h"
#include "core/spi.h"
#include "rfm69cw_hw.h"
#include "rfm69.h"

#ifdef RFM69_SUPPORT

#define SPI_SEND(_d) (spi_trans(SPI_USART, _d))
#define SPI_RECV() (spi_trans(SPI_USART, 0))

const uint16_t rfm69Bitrate_Values[RFM69_NUM_BITRATES] = {
		0x682B, /* RFM69_BR_1k2 */
		0x3415, /* RFM69_BR_2k4 */
		0x0D05, /* RFM69_BR_9k6 */
		0x0A00, /* RFM69_BR_12k5 */
		0x0500, /* RFM69_BR_25 */
		0x0280, /* RFM69_BR_50 */
		0x00D5, /* RFM69_BR_150 */
		0x0080, /* RFM69_BR_250 */
		0x006B /* RFM69_BR_300 */
};

uint8_t rfm69_regRead(RFM69_ModuleID_t module, uint8_t reg);
void rfm69_regWrite(RFM69_ModuleID_t module, uint8_t reg, uint8_t data);

void RFM69_init(void)
{
	uint8_t ctr;

	for (ctr = 0; ctr < RFM69_NUM_MODULES; ctr++)
	{
		RFM69_reset(ctr);
		RFM69_setMode(ctr, RFM69_STANDBY_MODE);
		RFM69_calibrateOSC(ctr);
	}
}

void RFM69_reset(RFM69_ModuleID_t module)
{

}

void RFM69_setMode(RFM69_ModuleID_t module, RFM69_BasicMode_t mode);
{
	uint8_t regOpMode;

	regOpMode = rfm69_regRead(module, RFM69_REGOPMODE);

	regOpMode &= 0x80;
	regOpMode |= ((mode & 0x07) << 2);

	if (RFM69_LISTEN_MODE == mode)
	{
		regOpMode |= 0x20; /* RFM69_REGOPMODE_LISTENON */
	}
	else
	{
		regOpMode |= 0x10; /* RFM69_REGOPMODE_LISTENABORT */
	}

	rfm69_regWrite(mode, RFM69_REGOPMODE, regOpMode);
}

void RFM69_setBitrate(uint8_t module, RFM69_BitRate_e mode)
{
	/* RxBW anpassen! */
	/* Afc ein/ausschalten, ggf LO offset anpassen */
}

void RFM69_setSyncWord(uint8_t module, uint8_t syncWord[], uint8_t length)
{
	uint8_t regSyncCfg;
	uint8_t ctr;

	if (length > 8)
		length = 8;

	regSyncCfg = rfm69_regRead(module, RFM69_REGSYNCCONFIG);
	regSyncCfg &= ~(7 << 3);
	regSyncCfg |= (length << 3);

	/* TODO CS */
	SPI_SEND(RFM69_REGSYNCCONFIG);
	SPI_SEND(regSyncCfg);

	for (ctr = 0; ctr < length; ctr++)
	{
		SPI_SEND(syncWord[ctr]);
	}

	/* TODO CS */
}

void RFM69_setSyncMode(uint8_t module, bool syncOn)
{
	uint8_t regSyncCfg;

	regSyncCfg = rfm69_regRead(module, RFM69_REGSYNCCONFIG);

	if (true == syncOn)
	{
		regSyncCfg |= (_BV(7));
	}
	else
	{
		regSyncCfg &= ~(_BV(7));
	}

	rfm69_regWrite(module, RFM69_REGSYNCCONFIG, regSyncCfg);
}

void RFM69_setAddressFiltering(uint8_t module, RFM69_AddressFilterMode_t mode, uint8_t address)
{

}

void RFM69_setAESKey(uint8_t module, uint8_t aesKey[])
{

}

void RFM69_configureAES(uint8_t module, boolean aesEnable)
{

}

void RFM69_setPacketFormat(uint8_t module, uint8_t format, uint8_t payLoadLen)
{

}

void RFM69_transmit(uint8_t module, uint8_t data[])
{

}

void RFM69_calibrateOSC(RFM69_ModuleID_t module)
{
	uint8_t result;
	uint8_t ctr;

	rfm69_regWrite(module, RFM69_REGOSC1, _BV(7));

	do
	{
		result = rfm69_regRead(module, RFM69_REGOSC1);
	}while (((result & (1 << 6) != (1 << 6)) && (++ctr < 255));
}

uint8_t RFM69_getTemperature(RFM69_ModuleID_t module)
{
	uint8_t result;
	uint8_t ctr;

	RFM69_setMode(module, RFM69_STANDBY_MODE);

	rfm69_regWrite(module, RFM69_REGTEMP1, _BV(3));

	do
	{
		result = rfm69_regRead(module, RFM69_REGTEMP1);
	}while (((result & (1 << 2) != (1 << 2)) && (++ctr < 255));

	result = rfm69_regRead(module, RFM69_REGTEMP2);

	return result;
}

uint8_t rfm69_regRead(RFM69_ModuleID_t module, uint8_t reg)
{

}

void rfm69_regWrite(RFM69_ModuleID_t module, uint8_t reg, uint8_t data)
{

}

/*
 * -- Ethersex META --
 * header(hardware/radio/rfm69/rfm69.h)
 * init(rfm69_init)
 */

#endif /*RFM69_SUPPORT*/

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
#include <stdbool.h>
#include <util/delay.h>
#include "config.h"
#include "core/heartbeat.h"
#include "core/bit-macros.h"
#include "core/spi.h"
#include "rfm69cw_hw.h"
#include "rfm69.h"

#ifdef RFM69_SUPPORT

#define SPI_SEND(_d) (spi_send(SPI_USART, _d))
#define SPI_RECV() (spi_send(SPI_USART, 0))

#define RFM69_NUM_MODULES 1
#define _BV(x) (1 << x)

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
void rfm69_reset(RFM69_ModuleID_t module);
void rfm69_getInterruptFlags(RFM69_ModuleID_t module, uint16_t *irqFlags);
void rfm69_blinkLED(RFM69_ModuleID_t module);

void RFM69_init(void)
{
	uint8_t ctr;

	RFM69_DEBUG("Initialize.\n");

	PIN_SET(SPI_CS_RFM69_0);
	PIN_SET(SPI_CS_RFM69_1);

	for (ctr = 0; ctr < RFM69_NUM_MODULES; ctr++)
	{
		rfm69_reset(ctr);
		RFM69_setMode(ctr, RFM69_STANDBY_MODE);
		RFM69_calibrateOSC(ctr);

		/* Fest einstellen:
		 * PaLevel
		 * OuPower
		 * OcpTrim
		 * DioMapping
		 * PreambleSize
		 * DataWhitening
		 * ModulationShaping
		 * FrequencyDeviation
		 * CarrierFreqency
		 * AfcAutoOn
		 *  */
	}

	RFM69_DEBUG("Init Done\n");
}

void RFM69_setMode(RFM69_ModuleID_t module, RFM69_BasicMode_t mode)
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

	rfm69_regWrite(module, RFM69_REGOPMODE, regOpMode);

	RFM69_DEBUG("Mode set to %i\n", mode);
}

void RFM69_setAutoMode(RFM69_ModuleID_t module, RFM69_IntermediateMode_t mode,
		RFM69_ModeSwichCondition_t enterCondition, RFM69_ModeSwichCondition_t leaveCondition)
{

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

	PIN_CLEAR(SPI_CS_RFM69_0);

	SPI_SEND(RFM69_REGSYNCCONFIG);
	SPI_SEND(regSyncCfg);

	for (ctr = 0; ctr < length; ctr++)
	{
		SPI_SEND(syncWord[ctr]);
	}

	PIN_SET(SPI_CS_RFM69_0);
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

void RFM69_setAddressFiltering(uint8_t module, RFM69_AddressFilterMode_t mode, uint8_t address, uint8_t broadcastAddress)
{
	uint8_t regPacketConf;

	regPacketConf = rfm69_regRead(module, RFM69_REGPACKETCONFIG1);
	regPacketConf |= (uint8_t)((mode << 1) & 0x06);

	rfm69_regWrite(module, RFM69_REGPACKETCONFIG1, regPacketConf);
	rfm69_regWrite(module, RFM69_REGBROADCASTADRS, broadcastAddress);
}

void RFM69_setAESKey(uint8_t module, uint8_t aesKey[])
{
	uint8_t ctr;

	PIN_CLEAR(SPI_CS_RFM69_0);

	SPI_SEND(RFM69_REGAESKEY1);
	for (ctr = 0; ctr < RFM69_AESKEYLEN; ctr++)
	{
		SPI_SEND(aesKey[ctr]);
	}

	PIN_SET(SPI_CS_RFM69_0);
}

void RFM69_configureAES(uint8_t module, bool aesEnable)
{

}

void RFM69_setPacketFormat(uint8_t module, uint8_t format, uint8_t payLoadLen)
{
	uint8_t regPacketConf;
	regPacketConf = rfm69_regRead(module, RFM69_REGPACKETCONFIG1);
	regPacketConf |= (uint8_t)((format << 7) & 0x80);

	rfm69_regWrite(module, RFM69_REGPACKETCONFIG1, regPacketConf);
	rfm69_regWrite(module, RFM69_REGPAYLOADLENGTH, payLoadLen);
}

void RFM69_transmit(uint8_t module, uint8_t data[], uint8_t dataLen)
{

}

void RFM69_receive(uint8_t module, uint8_t data[], uint8_t dataLen)
{
}

void RFM69_calibrateOSC(RFM69_ModuleID_t module)
{
	uint8_t result;
	uint8_t ctr = 0;

	rfm69_regWrite(module, RFM69_REGOSC1, _BV(7));

	RFM69_DEBUG("Calibrating oscillator...\n");

	do
	{
		result = rfm69_regRead(module, RFM69_REGOSC1);
		RFM69_DEBUG("OSCCAL %i\n",result);
	}while (((result & (1 << 6)) != (1 << 6)) && (++ctr < 255));
	RFM69_DEBUG("OSCCAL Done. Counter: %i\n", ctr);
}

uint8_t RFM69_getTemperature(RFM69_ModuleID_t module)
{
	uint8_t result;
	uint8_t ctr = 0;

	RFM69_DEBUG("Read Temperature...\n");

	RFM69_setMode(module, RFM69_STANDBY_MODE);

	rfm69_regWrite(module, RFM69_REGTEMP1, _BV(3));

	do
	{
		result = rfm69_regRead(module, RFM69_REGTEMP1);
		RFM69_DEBUG("Result %i\n",result);
	}while (((result & (1 << 2)) == (1 << 2)) && (++ctr < 255));

	result = rfm69_regRead(module, RFM69_REGTEMP2);

	RFM69_DEBUG("Done. Counter: %i, Temperature: %i\n", ctr, result);

	return result;
}

uint8_t rfm69_regRead(RFM69_ModuleID_t module, uint8_t reg)
{
	uint8_t result;

	PIN_CLEAR(SPI_CS_RFM69_0);
	reg &= 0x7F;
	SPI_SEND(reg);
	result = SPI_RECV();
	PIN_SET(SPI_CS_RFM69_0);

	return result;
}

void rfm69_regWrite(RFM69_ModuleID_t module, uint8_t reg, uint8_t data)
{
	PIN_CLEAR(SPI_CS_RFM69_0);
	reg |= 0x80;
	SPI_SEND(reg);
	SPI_SEND(data);
	PIN_SET(SPI_CS_RFM69_0);
}

void rfm69_getInterruptFlags(RFM69_ModuleID_t module, uint16_t *irqFlags)
{
	PIN_CLEAR(SPI_CS_RFM69_0);
	SPI_SEND(RFM69_REGIRQFLAGS1);
	*irqFlags = SPI_RECV();
	*irqFlags |= SPI_RECV() << 8;
	PIN_SET(SPI_CS_RFM69_0);
}

void rfm69_reset(RFM69_ModuleID_t module)
{
	PIN_SET(SPI_CS_RFM69_0);
	PIN_SET(SPI_CS_RFM69_1);

	PIN_SET(RESET_RFM69);
	_delay_us(100);
	PIN_CLEAR(RESET_RFM69);
	_delay_ms(5);
}

void rfm69_blinkLED(RFM69_ModuleID_t module)
{

}

/*
 * -- Ethersex META --
 * header(hardware/radio/rfm69/rfm69.h)
 * init(RFM69_init)
 */

#endif /*RFM69_SUPPORT*/

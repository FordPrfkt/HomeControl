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

/* Enable the hook rfm69_dataReceived */
#define HOOK_NAME rfm69_dataReceived
#define HOOK_ARGS (uint8_t data[], uint8_t dataLen)
#define HOOK_COUNT 3
#define HOOK_ARGS_CALL (data, dataLen)
#define HOOK_IMPLEMENT 1

#define DEBUG_RFM69 1

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <avr/io.h>
#include <util/delay.h>
#include "config.h"
#include "core/heartbeat.h"
#include "core/bit-macros.h"
#include "core/spi.h"
#include "rfm69cw_hw.h"
#include "rfm69.h"

#ifdef RFM69_SUPPORT

#define RFM69_NUM_MODULES 2

#define RFM69_SPI_SEND(_d) (spi_send(SPI_USART, _d))
#define RFM69_SPI_RECV() (spi_send(SPI_USART, 0))

#define RFM69_RSSI_TRESHOLD (127u)

static RFM69_ModulationType_e rfm69_selectedModulation = RFM69_FSK_MODULATION;
static RFM69_BasicMode_t rfm69_currentMode = RFM69_SLEEP_MODE;

void rfm69_initModule(RFM69_ModuleID_t module);
static void rfm69_select(RFM69_ModuleID_t module);
static void rfm69_deselect(RFM69_ModuleID_t module);
static uint8_t rfm69_regRead(RFM69_ModuleID_t module, uint8_t reg);
static void rfm69_regWrite(RFM69_ModuleID_t module, uint8_t reg, uint8_t data);
bool rfm69_channelFree(uint8_t module);
static void rfm69_setMode(RFM69_ModuleID_t module, RFM69_BasicMode_t mode);
static void rfm69_getInterruptFlags(RFM69_ModuleID_t module, uint16_t *irqFlags);
static void rfm69_blinkLED(RFM69_ModuleID_t module);

/* TODO: Interrupts + Hook */
/* rfm69_dataReceived_call(data, dataLen); */

void RFM69_reset(RFM69_ModuleID_t module)
{
	rfm69_deselect(module);

	PIN_SET(RESET_RFM69);
	_delay_us(100);
	PIN_CLEAR(RESET_RFM69);
	_delay_ms(10);
	rfm69_blinkLED(module);

	rfm69_initModule(module);
}

inline void RFM69_sleepMode(RFM69_ModuleID_t module)
{
	rfm69_setMode(module, RFM69_SLEEP_MODE);
}

inline void RFM69_standbyMode(RFM69_ModuleID_t module)
{
	rfm69_setMode(module, RFM69_STANDBY_MODE);
}

inline void RFM69_rxMode(RFM69_ModuleID_t module)
{
	rfm69_setMode(module, RFM69_RECEIVE_MODE);
}

inline void RFM69_txMode(RFM69_ModuleID_t module)
{
	rfm69_setMode(module, RFM69_TRANSMIT_MODE);
}

void RFM69_listenMode(RFM69_ModuleID_t module,
		RFM69CW_ListModeConf_t *listenModeConf)
{
	uint8_t reg;

	reg = listenModeConf->listenResolIdle << RFM69CW_LISTEN1_LISTENRESOLIDLE;
	reg |= listenModeConf->listenResolRx << RFM69CW_LISTEN1_LISTENRESOLRX;
	reg |= listenModeConf->syncAddrMatch << RFM69CW_LISTEN1_LISTENCRITERIA;
	reg |= listenModeConf->listenEnd << RFM69CW_LISTEN1_LISTENEND;

	rfm69_select(module);
	RFM69_SPI_SEND(RFM69_REGLISTEN1 | RFM69CW_SPI_WRITE_FLAG);
	RFM69_SPI_SEND(reg);
	RFM69_SPI_SEND(listenModeConf->listenCoefIdle);
	RFM69_SPI_SEND(listenModeConf->listenCoefRx);
	rfm69_deselect(module);

	rfm69_setMode(module, RFM69_LISTEN_MODE);

	reg = rfm69_regRead(module, RFM69_REGOPMODE);
	reg &= ~(RFM69CW_OPMODE_MODE_MASK << RFM69CW_OPMODE_MODE);
	reg |= listenModeConf->listenEndMode << RFM69CW_OPMODE_MODE;
	rfm69_regWrite(module, RFM69_REGOPMODE, reg);
}

void RFM69_setAutoMode(RFM69_ModuleID_t module, RFM69_IntermediateMode_t mode,
		RFM69_ModeSwitchCondition_t enterCondition,
		RFM69_ModeSwitchCondition_t leaveCondition)
{
	uint8_t autoModeReg;

	autoModeReg = mode;
	autoModeReg |= (((uint8_t) leaveCondition) << 2);
	autoModeReg |= (((uint8_t) enterCondition) << 5);

	rfm69_regWrite(module, RFM69_REGAUTOMODES, autoModeReg);
}

void RFM69_setFrequency(RFM69_ModuleID_t module, uint32_t frequency)
{
	// switch to standby if TX/RX was active
	if (RFM69_RECEIVE_MODE == rfm69_currentMode
			|| RFM69_TRANSMIT_MODE == rfm69_currentMode)
	{
		rfm69_setMode(module, RFM69_STANDBY_MODE);
	}

	// calculate register value
	frequency /= RFM69CW_FSTEP;

	/* set new frequency */
	rfm69_select(module);
	RFM69_SPI_SEND(RFM69_REGFRFMSB | RFM69CW_SPI_WRITE_FLAG);
	RFM69_SPI_SEND(frequency >> 16);
	RFM69_SPI_SEND(frequency >> 8);
	RFM69_SPI_SEND(frequency);
	rfm69_deselect(module);
}

void RFM69_setFrequencyDeviation(RFM69_ModuleID_t module, uint16_t frequency)
{
	// switch to standby if TX/RX was active
	if (RFM69_RECEIVE_MODE == rfm69_currentMode
			|| RFM69_TRANSMIT_MODE == rfm69_currentMode)
	{
		rfm69_setMode(module, RFM69_STANDBY_MODE);
	}

	// calculate register value
	frequency /= RFM69CW_FSTEP;

	// set new frequency
	rfm69_select(module);
	RFM69_SPI_SEND(RFM69_REGFDEVMSB | RFM69CW_SPI_WRITE_FLAG);
	RFM69_SPI_SEND(frequency >> 8);
	RFM69_SPI_SEND(frequency);
	rfm69_deselect(module);
}

void RFM69_setOutputPower(uint8_t module, uint8_t power)
{

	power &= 0x1F; /* Limit to 5 bits */
	power |= 0x80; /* Set the PA0 enabled flag */

	/* output = -18dBm + power */

	rfm69_regWrite(module, RFM69_REGPALEVEL, power);
}

void RFM69_setBitrate(uint8_t module, RFM69_BitRate_t bitRate)
{
	if ((RFM69_FSK_MODULATION == rfm69_selectedModulation)
			|| ((RFM69_OOK_MODULATION == rfm69_selectedModulation)
					&& ((RFM69_BR_1k2 == bitRate) || (RFM69_BR_2k4 == bitRate)
							|| (RFM69_BR_9k6 == bitRate)
							|| (RFM69_BR_12k5 == bitRate)
							|| (RFM69_BR_25 == bitRate))))
	{
		rfm69_select(module);
		RFM69_SPI_SEND(RFM69_REGBITRATEMSB | RFM69CW_SPI_WRITE_FLAG);
		RFM69_SPI_SEND((uint8_t)(bitRate >> 8));
		RFM69_SPI_SEND((uint8_t )bitRate);
		rfm69_deselect(module);
		rfm69_blinkLED(module);
	}
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

	rfm69_select(module);

	RFM69_SPI_SEND(RFM69_REGSYNCCONFIG | RFM69CW_SPI_WRITE_FLAG);
	RFM69_SPI_SEND(regSyncCfg);

	for (ctr = 0; ctr < length; ctr++)
	{
		RFM69_SPI_SEND(syncWord[ctr]);
	}

	rfm69_deselect(module);
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

void RFM69_promiscousMode(bool enable)
{

}

void RFM69_setAddress(uint8_t module, RFM69_AddressFilterMode_t mode,
		uint8_t address, uint8_t broadcastAddress)
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

	rfm69_select(module);

	RFM69_SPI_SEND(RFM69_REGAESKEY1 | RFM69CW_SPI_WRITE_FLAG);
	for (ctr = 0; ctr < RFM69_AESKEYLEN; ctr++)
	{
		RFM69_SPI_SEND(aesKey[ctr]);
	}

	rfm69_deselect(module);
	rfm69_blinkLED(module);
}

void RFM69_configureAES(uint8_t module, bool aesEnable)
{
	uint8_t regPacketConf;

	regPacketConf = rfm69_regRead(module, RFM69_REGPACKETCONFIG2);
	regPacketConf &= ~_BV(RFM69CW_PACKETCONF2_AESON);
	regPacketConf |= (aesEnable << RFM69CW_PACKETCONF2_AESON);

	rfm69_regWrite(module, RFM69_REGPACKETCONFIG2, regPacketConf);
}

void RFM69_setPacketFormat(uint8_t module, uint8_t format, uint8_t payLoadLen)
{
	uint8_t regPacketConf;
	regPacketConf = rfm69_regRead(module, RFM69_REGPACKETCONFIG1);
	regPacketConf |= (uint8_t)((format << 7) & 0x80);

	rfm69_regWrite(module, RFM69_REGPACKETCONFIG1, regPacketConf);
	rfm69_regWrite(module, RFM69_REGPAYLOADLENGTH, payLoadLen);
}

void RFM69_setModulation(uint8_t module, RFM69_ModulationType_e modulation)
{
	uint8_t regDataModul;

	rfm69_selectedModulation = modulation;

	regDataModul = rfm69_regRead(module, RFM69_REGDATAMODUL);
	regDataModul = (regDataModul & 0xF3)
			| ((modulation << RFM69CW_DATAMODUL_MODULATIONTYPE) & 0x0C);
	rfm69_regWrite(module, RFM69_REGDATAMODUL, regDataModul);
}

uint8_t RFM69_getRSSI(uint8_t module, bool forceCalc)
{
	uint8_t rssiConf;

	if (true == forceCalc)
	{
		rssiConf = 1;

		rfm69_regWrite(module, RFM69_REGRSSICONFIG, rssiConf);

		do
		{
			rssiConf = rfm69_regRead(module, RFM69_REGRSSICONFIG);
		} while (rssiConf != 1);
	}

	rssiConf = rfm69_regRead(module, RFM69_REGRSSIVALUE);

	return rssiConf / 2;
}

void RFM69_transmit(uint8_t module, uint8_t data[], uint8_t dataLen)
{
	uint8_t ctr;

	/* TODO: Set PacketLength
	 * Check for 64 Bytes in AES Mode
	 */

	/* TODO: Write until datLen or Fifo Full interrupt.
	 * If Datalen then not reached, tx then continue
	 * Large Packet Handling from Manual*/

	/* TODO: Clear FIFO before send */

	/* TODO: IMplement CSMA/CD */

	rfm69_setMode(module, RFM69_STANDBY_MODE);

	rfm69_select(module);

	RFM69_SPI_SEND(RFM69_REGFIFO | RFM69CW_SPI_WRITE_FLAG);
	for (ctr = 0; ctr < dataLen; ctr++)
	{
		RFM69_SPI_SEND(data[ctr]);
	}

	rfm69_deselect(module);

	rfm69_blinkLED(module);

	rfm69_setMode(module, RFM69_TRANSMIT_MODE);

	/* TODO: Wait for Send */

	rfm69_setMode(module, RFM69_STANDBY_MODE);
}

void RFM69_receive(uint8_t module, uint8_t data[], uint8_t dataLen)
{
	uint8_t ctr;

	/* TODO: Check PacketLength */

	if (dataLen <= RFM69CW_MAX_PACKETSIZE)
	{
		rfm69_select(module);

		RFM69_SPI_SEND(RFM69_REGFIFO & (~RFM69CW_SPI_WRITE_FLAG));
		for (ctr = 0; ctr < dataLen; ctr++)
		{
			data[ctr] = RFM69_SPI_RECV();
		}

		rfm69_deselect(module);
		rfm69_blinkLED(module);
	}
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
		RFM69_DEBUG("OSCCAL %i\n", result);
	} while (((result & (1 << 6)) != (1 << 6)) && (++ctr < 255));
	RFM69_DEBUG("OSCCAL Done. Counter: %i\n", ctr);
}

uint8_t RFM69_getTemperature(RFM69_ModuleID_t module)
{
	uint8_t result;
	uint8_t ctr = 0;

	rfm69_setMode(module, RFM69_STANDBY_MODE);

	rfm69_regWrite(module, RFM69_REGTEMP1, _BV(3));

	do
	{
		result = rfm69_regRead(module, RFM69_REGTEMP1);
	} while (((result & (1 << 2)) == (1 << 2)) && (++ctr < 255));

	result = rfm69_regRead(module, RFM69_REGTEMP2);

	return result;
}

uint8_t RFM69_getVersion(uint8_t module)
{
	return rfm69_regRead(module, RFM69_REGVERSION);
}

void rfm69_initModule(RFM69_ModuleID_t module)
{
	uint8_t temp;

	temp = RFM69_getVersion(module);
	RFM69_DEBUG("Initializing module %i - Version %i\n", module, temp);

	/* Set DIO Pin Modes:
	 * DIO5: ModeReady
	 * DIO2: Fifo not empty
	 * DIO1: FiFo Full
	 * DIO0: CrcOK/PacketSent*/
	temp = (DIO_MAPPING_0 << RFM69CW_DIOMAPPING_DIO0)
			| (DIO_MAPPING_1 << RFM69CW_DIOMAPPING_DIO1)
			| (DIO_MAPPING_0 << RFM69CW_DIOMAPPING_DIO2);
	rfm69_regWrite(module, RFM69_REGDIOMAPPING1, temp);
	temp = (DIO_MAPPING_3 << RFM69CW_DIOMAPPING_DIO5)
			| (RFM69_CLKOUT_OFF << RFM69CW_DIOMAPPING_CLKOUT);
	rfm69_regWrite(module, RFM69_REGDIOMAPPING2, temp);

	/* Calibrate oscillator */
	rfm69_setMode(module, RFM69_STANDBY_MODE);
	RFM69_calibrateOSC(module);

	/* Fest einstellen:
	 * CarrierFreqency
	 *  */

	/* Preamble: 4 Byte */
	rfm69_regWrite(module, RFM69_REGPREAMBLEMSB, 0);
	rfm69_regWrite(module, RFM69_REGPREAMBLELSB, 4);

	/* Select Data Whitening as DC-Free Mechanism */
	temp = rfm69_regRead(module, RFM69_REGPACKETCONFIG1);
	temp &= (uint8_t) ~(RFM69CW_PACKETCONF_DCFREE_MASK
			<< RFM69CW_PACKETCONF_DCFREE);
	temp |= (RFM69_DCFREE_WHITENING << RFM69CW_PACKETCONF_DCFREE);
	rfm69_regWrite(module, RFM69_REGPREAMBLELSB, temp);

	/* Enable Modulation Shaping*/
	temp = rfm69_regRead(module, RFM69_REGDATAMODUL);
	temp &= (uint8_t) ~(RFM69CW_DATAMODUL_MODSHAPING_MASK
			<< RFM69CW_DATAMODUL_MODSHAPING);
	temp |= (1 << RFM69CW_DATAMODUL_MODSHAPING);
	rfm69_regWrite(module, RFM69_REGDATAMODUL, temp);

	/* AFC Auto on */
	temp = _BV(RFM69CW_AFCFEI_AFCAUTOON) | _BV(RFM69CW_AFCFEI_AFCAUTOCLEAR);
	rfm69_regWrite(module, RFM69_REGAFCFEI, temp);
}

void rfm69_setMode(RFM69_ModuleID_t module, RFM69_BasicMode_t mode)
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

	/* TODO: Wait for mode ready */

	rfm69_currentMode = mode;

	RFM69_DEBUG("Mode set to %i\n", mode);
}

void rfm69_select(RFM69_ModuleID_t module)
{
	if (RFM69_MOD_433 == module)
	{
		PIN_SET(STATUSLED_RFM69_0);
		PIN_CLEAR(SPI_CS_RFM69_0);
	}
	else if (RFM69_MOD_866 == module)
	{
		PIN_SET(STATUSLED_RFM69_1);
		PIN_CLEAR(SPI_CS_RFM69_1);
	}
	else
	{

	}
}

void rfm69_deselect(RFM69_ModuleID_t module)
{
	if (RFM69_MOD_433 == module)
	{
		PIN_CLEAR(STATUSLED_RFM69_0);
		PIN_SET(SPI_CS_RFM69_0);
	}
	else if (RFM69_MOD_866 == module)
	{
		PIN_CLEAR(STATUSLED_RFM69_1);
		PIN_SET(SPI_CS_RFM69_1);
	}
	else
	{

	}
}

uint8_t rfm69_regRead(RFM69_ModuleID_t module, uint8_t reg)
{
	uint8_t result;

	rfm69_select(module);
	reg &= ~RFM69CW_SPI_WRITE_FLAG;
	RFM69_SPI_SEND(reg);
	result = RFM69_SPI_RECV();
	rfm69_deselect(module);

	rfm69_blinkLED(module);

	return result;
}

void rfm69_regWrite(RFM69_ModuleID_t module, uint8_t reg, uint8_t data)
{

	rfm69_select(module);
	reg |= RFM69CW_SPI_WRITE_FLAG;
	RFM69_SPI_SEND(reg);
	RFM69_SPI_SEND(data);
	rfm69_deselect(module);

	rfm69_blinkLED(module);
}

void rfm69_getInterruptFlags(RFM69_ModuleID_t module, uint16_t *irqFlags)
{
	rfm69_select(module);
	RFM69_SPI_SEND(RFM69_REGIRQFLAGS1 & (~RFM69CW_SPI_WRITE_FLAG));
	*irqFlags = RFM69_SPI_RECV();
	*irqFlags |= RFM69_SPI_RECV() << 8;
	rfm69_deselect(module);
	rfm69_blinkLED(module);
}

bool rfm69_channelFree(uint8_t module)
{
	if (RFM69_getRSSI(module, true) <= RFM69_RSSI_TRESHOLD)
		return true;
	else
		return false;
}

void rfm69_blinkLED(RFM69_ModuleID_t module)
{
	/*	if (RFM69_MOD_433 == module)
	 {
	 PIN_SET(STATUSLED_RFM69_0);
	 }
	 else if (RFM69_MOD_866 == module)
	 {
	 PIN_SET(STATUSLED_RFM69_1);
	 }
	 else
	 {

	 }

	 rfm69_blinkCtr = 0;*/
}

void RFM69_init(void)
{
	uint8_t ctr;

	PIN_SET(SPI_CS_RFM69_0);
	PIN_SET(SPI_CS_RFM69_1);

	PIN_CLEAR(STATUSLED_RFM69_0);
	PIN_CLEAR(STATUSLED_RFM69_1);

	for (ctr = 0; ctr < RFM69_NUM_MODULES; ctr++)
	{
		rfm69_initModule(ctr);
	}
}

void RFM69_periodic(void)
{
	/*	rfm69_blinkCtr++;
	 if (rfm69_blinkCtr >= 10)
	 {
	 PIN_CLEAR(STATUSLED_RFM69_0);
	 PIN_CLEAR(STATUSLED_RFM69_1);
	 rfm69_blinkCtr = 0;
	 }*/
}

/*
 * -- Ethersex META --
 * header(hardware/radio/rfm69/rfm69.h)
 * timer(1, RFM69_periodic())
 * init(RFM69_init)
 */

#endif /*RFM69_SUPPORT*/

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

#ifndef HARDWARE_RADIO_RFM69_RFM69_H_
#define HARDWARE_RADIO_RFM69_RFM69_H_

#include <stdint.h>
#include <stdbool.h>
#include "config.h"
#include "rfm69cw_hw.h"

#ifdef RFM69_SUPPORT

typedef enum RFM69_ModuleID_e
{
	RFM69_MOD_433 = 0,
	RFM69_MOD_866 = 1
}RFM69_ModuleID_t;

void RFM69_init(void);
void RFM69_periodic(void);
void RFM69_reset(RFM69_ModuleID_t module);
void RFM69_sleepMode(RFM69_ModuleID_t module);
void RFM69_standbyMode(RFM69_ModuleID_t module);
void RFM69_rxMode(RFM69_ModuleID_t module);
void RFM69_txMode(RFM69_ModuleID_t module);
void RFM69_listenMode(RFM69_ModuleID_t module, RFM69CW_ListModeConf_t *listenModeConf);
void RFM69_setAutoMode(RFM69_ModuleID_t module, RFM69_IntermediateMode_t mode, RFM69_ModeSwitchCondition_t enterCondition, RFM69_ModeSwitchCondition_t leaveCondition);
void RFM69_setFrequency(RFM69_ModuleID_t module, uint32_t frequency);
void RFM69_setFrequencyDeviation(RFM69_ModuleID_t module, uint16_t frequency);
void RFM69_setOutputPower(uint8_t module, uint8_t power);
void RFM69_setBitrate(uint8_t module, RFM69_BitRate_t mode);
void RFM69_setSyncWord(uint8_t module, uint8_t syncWord[], uint8_t length);
void RFM69_setSyncMode(uint8_t module, bool syncOn);
void RFM69_setAddress(uint8_t module, RFM69_AddressFilterMode_t mode, uint8_t address, uint8_t broadcastAddress);
void RFM69_promiscousMode(bool enable);
void RFM69_setAESKey(uint8_t module, uint8_t aesKey[]);
void RFM69_configureAES(uint8_t module, bool aesEnable);
void RFM69_setPacketFormat(uint8_t module, uint8_t format, uint8_t payLoadLen);
void RFM69_setModulation(uint8_t module, RFM69_ModulationType_e modulation);
uint8_t RFM69_getRSSI(uint8_t module, bool forceCalc);
void RFM69_transmit(uint8_t module, uint8_t data[], uint8_t dataLen);
void RFM69_receive(uint8_t module, uint8_t data[], uint8_t dataLen);
void RFM69_calibrateOSC(RFM69_ModuleID_t module);
uint8_t RFM69_getTemperature(RFM69_ModuleID_t module);
uint8_t RFM69_getVersion(uint8_t module);

#ifdef DEBUG_RFM69
#include "core/debug.h"
#define RFM69_DEBUG(a...)  debug_printf("RFM69: " a)
#else
#define RFM69_DEBUG(a...)
#endif

#define HOOK_NAME rfm69_dataReceived
#define HOOK_ARGS (uint8_t data[], uint8_t dataLen)
#include "hook.def"
#undef HOOK_NAME
#undef HOOK_ARGS

#endif /* RFM69_SUPPORT */
#endif /* HARDWARE_RADIO_RFM69_RFM69_H_ */

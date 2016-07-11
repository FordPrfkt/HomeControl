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

#include "config.h"
#include "rfm69cw_hw.h"

#ifdef RFM69_SUPPORT

typedef enum RFM69_ModuleID_e
{
	RFM69_MOD_433 = 0,
	RFM69_MOD_866 = 1
}RFM69_ModuleID_t;

void RFM69_init(void);
void RFM69_setMode(RFM69_ModuleID_t module, RFM69_BasicMode_t mode);
uint8_t RFM69_getTemperature(RFM69_ModuleID_t module);
void RFM69_calibrateOSC(RFM69_ModuleID_t module);

void rfm69_setModulation(uint8_t module, uint8_t mode);
void rfm69_setPower(uint8_t module, uint8_t power);
void rfm69_setFreqency(uint8_t module, uint8_t freq);
void rfm69_setBitRate(uint8_t module, uint8_t freq);
void rfm69_setSyncWord(uint8_t module, uint8_t syncWord);
void rfm69_enableEncyption(uint8_t module, uint8_t aesKey);
void rfm69_standby(uint8_t module, uint8_t listenCriteria);
void rfm69_sleep(uint8_t module);
void rfm69_startOscCal(uint8_t module);
void rfm69_startRSSI(uint8_t module);
uint8_t rfm69_getRSSI(uint8_t module);

void rfm69_transmit(uint8_t module, uint8_t data);
void rfm69_receive(uint8_t module, uint8_t *data);

#ifdef DEBUG_RFM69
#include "core/debug.h"
#define RFM69_DEBUG(a...)  debug_printf("RFM69: " a)
#else
#define RFM69_DEBUG(a...)
#endif

#endif /* RFM69_SUPPORT */
#endif /* HARDWARE_RADIO_RFM69_RFM69_H_ */

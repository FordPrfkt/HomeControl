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

#ifndef HARDWARE_RADIO_RFM69_RFM69CW_HW_H_
#define HARDWARE_RADIO_RFM69_RFM69CW_HW_H_

#include "config.h"

#ifdef RFM69_SUPPORT

/* Register numbers */
#define	RFM69_REGFIFO			(0x00)	/* FIFO read/write access */
#define	RFM69_REGOPMODE 		(0x01)	/* Operating modes of the transceiver */
#define	RFM69_REGDATAMODUL		(0x02)	/* Data operation mode and Modulation settings */
#define	RFM69_REGBITRATEMSB		(0x03)	/* Bit Rate setting, Most Significant Bits */
#define	RFM69_REGBITRATELSB		(0x04)	/* Bit Rate setting, Least Significant Bits */
#define	RFM69_REGFDEVMSB		(0x05)	/* Frequency Deviation setting, Most Significant Bits */
#define	RFM69_REGFDEVLSB		(0x06)	/* Frequency Deviation setting, Least Significant Bits */
#define	RFM69_REGFRFMSB			(0x07)	/* RF Carrier Frequency, Most Significant Bits */
#define	RFM69_REGFRFMID 		(0x08)	/* RF Carrier Frequency, Intermediate Bits */
#define	RFM69_REGFRFLSB			(0x09)	/* RF Carrier Frequency, Least Significant Bits */
#define	RFM69_REGOSC1			(0x0A)	/* RC Oscillators Settings */
#define	RFM69_REGAFCCTRL		(0x0B)	/* AFC control in low modulation index situations */
#define	RFM69_REGLISTEN1		(0x0D)	/* Listen Mode settings */
#define	RFM69_REGLISTEN2		(0x0E)	/* Listen Mode Idle duration */
#define	RFM69_REGLISTEN3		(0x0F)	/* Listen Mode Rx duration */
#define	RFM69_REGVERSION		(0x10)	/* Chip Version */
#define	RFM69_REGPALEVEL		(0x11)	/* PA selection and Output Power control */
#define	RFM69_REGPARAMP			(0x12)	/* Control of the PA ramp time in FSK mode */
#define	RFM69_REGOCP			(0x13)	/* Over Current Protection control */
#define	RFM69_REGLNA			(0x18)	/* LNA settings */
#define	RFM69_REGRXBW			(0x19)	/* Channel Filter BW Control */
#define	RFM69_REGAFCBW			(0x1A)	/* Channel Filter BW control during the AFC routine */
#define	RFM69_REGOOKPEAK		(0x1B)	/* OOK demodulator selection and control in peak mode */
#define	RFM69_REGOOKAVG			(0x1C)	/* Average threshold control of the OOK demodulator */
#define	RFM69_REGOOKFIX			(0x1D)	/* Fixed threshold control of the OOK demodulator */
#define	RFM69_REGAFCFEI			(0x1E)	/* AFC and FEI control and status */
#define	RFM69_REGAFCMSB			(0x1F)	/* MSB of the frequency correction of the AFC */
#define	RFM69_REGAFCLSB			(0x20)	/* LSB of the frequency correction of the AFC */
#define	RFM69_REGFEIMSB			(0x21)	/* MSB of the calculated frequency error */
#define	RFM69_REGFEILSB			(0x22)	/* LSB of the calculated frequency error */
#define	RFM69_REGRSSICONFIG		(0x23)	/* RSSI-related settings */
#define	RFM69_REGRSSIVALUE		(0x24)	/* RSSI value in dBm */
#define	RFM69_REGDIOMAPPING1	(0x25)	/* Mapping of pins DIO0 to DIO3 */
#define	RFM69_REGDIOMAPPING2	(0x26)	/* Mapping DIO5, ClkOut frequency */
#define	RFM69_REGIRQFLAGS1		(0x27)	/* Status register: PLL Lock state, Timeout, RSSI > Threshold... */
#define	RFM69_REGIRQFLAGS2		(0x28)	/* Status register: FIFO handling flags... */
#define	RFM69_REGRSSITHRESH		(0x29)	/* RSSI Threshold control */
#define	RFM69_REGRXTIMEOUT1		(0x2A)	/* Timeout duration between Rx request and RSSI detection */
#define	RFM69_REGRXTIMEOUT2		(0x2B)	/* Timeout duration between RSSI detection and PayloadReady */
#define	RFM69_REGPREAMBLEMSB	(0x2C)	/* Preamble length, MSB */
#define	RFM69_REGPREAMBLELSB	(0x2D)	/* Preamble length, LSB */
#define	RFM69_REGSYNCCONFIG		(0x2E)	/* Sync Word Recognition control */
#define	RFM69_REGSYNCVALUE1		(0x2F)	/* Sync Word bytes, 1 through 8 */
#define	RFM69_REGSYNCVALUE2		(0x30)	/* Sync Word bytes, 1 through 8 */
#define	RFM69_REGSYNCVALUE3		(0x31)	/* Sync Word bytes, 1 through 8 */
#define	RFM69_REGSYNCVALUE4		(0x32)	/* Sync Word bytes, 1 through 8 */
#define	RFM69_REGSYNCVALUE5		(0x33)	/* Sync Word bytes, 1 through 8 */
#define	RFM69_REGSYNCVALUE6		(0x34)	/* Sync Word bytes, 1 through 8 */
#define	RFM69_REGSYNCVALUE7		(0x35)	/* Sync Word bytes, 1 through 8 */
#define	RFM69_REGSYNCVALUE8		(0x36)	/* Sync Word bytes, 1 through 8 */
#define	RFM69_REGPACKETCONFIG1	(0x37)	/* Packet mode settings */
#define	RFM69_REGPAYLOADLENGTH	(0x38)	/* Payload length setting */
#define	RFM69_REGNODEADRS		(0x39)	/* Node address */
#define	RFM69_REGBROADCASTADRS	(0x3A)	/* Broadcast address */
#define	RFM69_REGAUTOMODES		(0x3B)	/* Auto modes settings */
#define	RFM69_REGFIFOTHRESH		(0x3C)	/* Fifo threshold, Tx start condition */
#define	RFM69_REGPACKETCONFIG2	(0x3D)	/* Packet mode settings */
#define	RFM69_REGAESKEY1		(0x3E)	/* 16 bytes of the cypher key */
#define	RFM69_REGAESKEY2		(0x3F)	/* 16 bytes of the cypher key */
#define	RFM69_REGAESKEY3		(0x40)	/* 16 bytes of the cypher key */
#define	RFM69_REGAESKEY4		(0x41)	/* 16 bytes of the cypher key */
#define	RFM69_REGAESKEY5		(0x42)	/* 16 bytes of the cypher key */
#define	RFM69_REGAESKEY6		(0x43)	/* 16 bytes of the cypher key */
#define	RFM69_REGAESKEY7		(0x44)	/* 16 bytes of the cypher key */
#define	RFM69_REGAESKEY8		(0x45)	/* 16 bytes of the cypher key */
#define	RFM69_REGAESKEY9		(0x46)	/* 16 bytes of the cypher key */
#define	RFM69_REGAESKEY10		(0x47)	/* 16 bytes of the cypher key */
#define	RFM69_REGAESKEY11		(0x48)	/* 16 bytes of the cypher key */
#define	RFM69_REGAESKEY12		(0x49)	/* 16 bytes of the cypher key */
#define	RFM69_REGAESKEY13		(0x4A)	/* 16 bytes of the cypher key */
#define	RFM69_REGAESKEY14		(0x4B)	/* 16 bytes of the cypher key */
#define	RFM69_REGAESKEY15		(0x4C)	/* 16 bytes of the cypher key */
#define	RFM69_REGAESKEY16		(0x4D)	/* 16 bytes of the cypher key */
#define	RFM69_REGTEMP1			(0x4E)	/* Temperature Sensor control */
#define	RFM69_REGTEMP2			(0x4F)	/* Temperature readout */
#define	RFM69_REGTESTLNA		(0x58)	/* Sensitivity boost */
#define	RFM69_REGTESTPA1		(0x5A)
#define	RFM69_REGTESTPA2		(0x5C)
#define	RFM69_REGTESTDAGC		(0x6F)	/* Fading Margin Improvement */
#define	RFM69_REGTESTAFC		(0x71)	/* AFC offset for low modulation index AFC */

/* Diverse Settings */
#define RFM69_FXOSC (32u)
#define RFM69_FSTEP (61u)
#define RFM69_AESKEYLEN (16)
#define RFM69CW_MAX_PACKETSIZE (66)
#define RFM69CW_SPI_WRITE_FLAG (0x80)

#define RFM69CW_FSTEP (1u)

/* Bit positions */
#define RFM69CW_OPMODE_MODE (2)
#define RFM69CW_OPMODE_MODE_MASK (2)
#define RFM69CW_OPMODE_LISTENON (6)

#define RFM69CW_DATAMODUL_MODULATIONTYPE (3)
#define RFM69CW_DATAMODUL_MODSHAPING (0)
#define RFM69CW_DATAMODUL_MODSHAPING_MASK (3)

#define RFM69CW_OSC1_RCCALSTART (7)
#define RFM69CW_OSC1_RCCALDONE (6)

#define RFM69CW_TEMP1_TEMPMEASSTART (3)
#define RFM69CW_TEMP1_TEMPMEASRUN (2)

#define RFM69CW_DIOMAPPING_DIO0 (6)
#define RFM69CW_DIOMAPPING_DIO1 (4)
#define RFM69CW_DIOMAPPING_DIO2 (2)
#define RFM69CW_DIOMAPPING_DIO3 (0)
#define RFM69CW_DIOMAPPING_DIO5 (4)
#define RFM69CW_DIOMAPPING_CLKOUT (0)
#define RFM69CW_DIOMAPPING_MASK (3)

#define RFM69CW_PACKETCONF_DCFREE (5)
#define RFM69CW_PACKETCONF_DCFREE_MASK (3)
#define RFM69CW_PACKETCONF2_AESON (0)

#define RFM69CW_AFCFEI_FEIDONE (6)
#define RFM69CW_AFCFEI_FEISTART (5)
#define RFM69CW_AFCFEI_AFCDONE (4)
#define RFM69CW_AFCFEI_AFCAUTOCLEAR (3)
#define RFM69CW_AFCFEI_AFCAUTOON (2)
#define RFM69CW_AFCFEI_AFCCLEAR (1)
#define RFM69CW_AFCFEI_AFCSTART (0)

#define RFM69CW_LISTEN1_LISTENRESOLIDLE (6)
#define RFM69CW_LISTEN1_LISTENRESOLRX (4)
#define RFM69CW_LISTEN1_LISTENCRITERIA (3)
#define RFM69CW_LISTEN1_LISTENEND (1)

/* Setting structs */
typedef enum RFM69_BasicMode_e
{
	RFM69_SLEEP_MODE = 0,
	RFM69_STANDBY_MODE = 1,
	RFM69_FS_MODE = 2,
	RFM69_TRANSMIT_MODE = 3,
	RFM69_RECEIVE_MODE = 4,
	RFM69_LISTEN_MODE = 8,
}RFM69_BasicMode_t;

typedef enum RFM69_ListenEnd_e
{
	RFM69_LISTENEND_RX = 0,
	RFM69_LISTENEND_RX_WAIT = 1,
	RFM69_LISTENEND_RESUME = 2
}RFM69_ListenEnd_t;

typedef struct RFM69CW_ListModeConf_s
{
	uint8_t listenCoefIdle;
	uint8_t listenResolIdle;
	uint8_t listenCoefRx;
	uint8_t listenResolRx;
	bool syncAddrMatch;
	RFM69_ListenEnd_t listenEnd;
	RFM69_BasicMode_t listenEndMode;
}RFM69CW_ListModeConf_t;

/* Setting values */
typedef enum RFM69_ClkOut_e
{
	RFM69_CLKOUT_DIV0 = 0,
	RFM69_CLKOUT_DIV2,
	RFM69_CLKOUT_DIV4,
	RFM69_CLKOUT_DIV8,
	RFM69_CLKOUT_DIV16,
	RFM69_CLKOUT_DIV32,
	RFM69_CLKOUT_RC,
	RFM69_CLKOUT_OFF
}RFM69_ClkOut_t;

typedef enum RFM69_IntermediateMode_e
{
	mode,
}RFM69_IntermediateMode_t;

typedef enum RFM69_ModeSwichCondition_e
{
	mode12
}RFM69_ModeSwitchCondition_t;

typedef enum RFM69_ModulationType_t
{
	RFM69_FSK_MODULATION = 0,
	RFM69_OOK_MODULATION = 1
}RFM69_ModulationType_e;

typedef enum RFM69_AddressFilterMode_e
{
	RFM69_ADDRESS_FILTERING_OFF = 0,
	RFM69_ADDRESS_FILTERING_ON = 1,
	RFM69_ADDRESS_FILTERING_BC = 2
}RFM69_AddressFilterMode_t;

typedef enum RFM69_BitRate_e
{
	RFM69_BR_1k2 = 0x682B,
	RFM69_BR_2k4 = 0x3415,
	RFM69_BR_9k6 = 0x0D05,
	RFM69_BR_12k5 = 0x0A00,
	RFM69_BR_25 = 0x0500,
	RFM69_BR_50 = 0x0280,
	RFM69_BR_150 = 0x00D5,
	RFM69_BR_250 = 0x0080,
	RFM69_BR_300 = 0x006B
}RFM69_BitRate_t;

typedef enum RFM69_DIOMapping_e
{
	DIO_MAPPING_0 = 0,
	DIO_MAPPING_1 = 1,
	DIO_MAPPING_2 = 2,
	DIO_MAPPING_3 = 3
}RFM69_DIOMapping_t;

typedef enum RFM69_DCFreeMode_e
{
	RFM69_DCFREE_NONE = 0,
	RFM69_DCFREE_MANCHESTER = 1,
	RFM69_DCFREE_WHITENING = 2
}RFM69_DCFreeMode_t;

#endif /* RFM69_SUPPORT */
#endif /* HARDWARE_RADIO_RFM69_RFM69CW_HW_H_ */

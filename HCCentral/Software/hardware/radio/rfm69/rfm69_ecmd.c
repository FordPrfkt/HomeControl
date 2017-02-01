/*
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

#include <avr/pgmspace.h>
#include <stdio.h>
#include <stdlib.h>

#include "rfm69.h"

#include "protocols/ecmd/ecmd-base.h"

#define RFM69_MODULE_COUNT 2

int16_t parse_cmd_rfm69_status(char *cmd, char *output, uint16_t len)
{
  uint8_t module;
  uint16_t s = 0;

  if ((1 != sscanf_P(cmd, PSTR("%hhu"), &module)) ||
      (module >= RFM69_MODULE_COUNT))
    return ECMD_ERR_PARSE_ERROR;

  return ECMD_FINAL(snprintf_P(output, len, PSTR("rfm69 status: %04x"), s));
}

int16_t parse_cmd_rfm69_getrssi(char *cmd, char *output, uint16_t len)
{
  uint8_t module;
  uint16_t s = 0;

  if ((1 != sscanf_P(cmd, PSTR("%hhu"), &module)) ||
      (module >= RFM69_MODULE_COUNT))
    return ECMD_ERR_PARSE_ERROR;

  return ECMD_FINAL(snprintf_P(output, len, PSTR("rfm69 status: %04x"), s));
}

int16_t parse_cmd_rfm69_reset(char *cmd, char *output, uint16_t len)
{
  uint8_t module;
  uint16_t s = 0;

  if ((1 != sscanf_P(cmd, PSTR("%hhu"), &module)) ||
      (module >= RFM69_MODULE_COUNT))
    return ECMD_ERR_PARSE_ERROR;

  return ECMD_FINAL(snprintf_P(output, len, PSTR("rfm69 status: %04x"), s));
}

/*
  -- Ethersex META --
  block([[RFM69]])
  ecmd_feature(rfm69_status, "rfm69 status", MODULE, Display internal status of MODULE.)
  ecmd_feature(rfm69_getrssi, "rfm69 getdrssi", MODULE, Get the current RSSI of MODULE.)

  ecmd_ifdef(RFM69_433_USE_RESET)
    ecmd_feature(rfm69_reset, "rfm69 reset", , Re-initialize the RFM69 module.)
  ecmd_endif()
*/

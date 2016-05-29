/*
 * Copyright (c) Alexander Neumann <alexander@bumpern.de>
 * Copyright (c) 2012-2013 Erik Kunze <ethersex@erik-kunze.de>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License (either version 2 or
 * version 3) as published by the Free Software Foundation.
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

#include "config.h"

#include <avr/io.h>
#include "spi.h"
#include "core/spi.h"
#include "spi_usart.h"
#include "spi_soft.h"
#include "debug.h"
#include "hardware/radio/rfm12/rfm12.h"
void
spi_init(void)
{
  /* Input and Output configuration is done in the beginning of main(), so it
   * doesn't have to be done here
   */

  /* Set the chip-selects as high */

#ifdef ENC28J60_SUPPORT
  PIN_SET(SPI_CS_NET);
#endif

  PIN_SET(SPI_CS_SD_READER);

#ifdef RFM12_SUPPORT
  for (int8_t modul = 0; modul < RFM12_MODULE_COUNT; modul++)
  {
    *rfm12_moduls[modul].rfm12_port |= rfm12_moduls[modul].rfm12_mask;
  }
#endif

#ifdef USTREAM_SUPPORT
  PIN_SET(VS1053_CS);
#endif

#ifdef USART_SPI_SUPPORT
  spi_usart_init();
#endif /* USART_SPI_SUPPORT */

#ifdef HW_SPI_SUPPORT
  /* enable spi, set master and clock modes (f/2) */
  _SPCR0 = _BV(_SPE0) | _BV(_MSTR0);
  _SPSR0 = _BV(_SPI2X0);
#endif /*HW_SPI_SUPPORT*/
}

#ifdef HW_SPI_SUPPORT
static void
spi_wait_busy(void)
{
#ifdef SPI_TIMEOUT
  uint8_t timeout = 200;

  while (!(_SPSR0 & _BV(_SPIF0)) && timeout > 0)
    timeout--;

  if (timeout == 0)
    debug_printf("ERROR: spi timeout reached!\r\n");
#else
  while (!(_SPSR0 & _BV(_SPIF0)));
#endif
}
#endif /*HW_SPI_SUPPORT*/

uint8_t noinline
spi_send(SPI_Interface_t interface, uint8_t data)
{
	uint8_t result;

	switch(interface)
	{
#ifdef HW_SPI_SUPPORT
	case SPI_HW:
		  _SPDR0 = data;
		  spi_wait_busy();
		  result = _SPDR0;
		break;
#endif /* HW_SPI_SUPPORT */

#ifdef SOFT_SPI_SUPPORT
	case SPI_SW:
		result = spi_soft_send(data);
		break;
#endif /* SOFT_SPI_SUPPORT */

#ifdef USART_SPI_SUPPORT
	case SPI_USART:
		result = spi_usart_send(data);
		break;
#endif /* USART_SPI_SUPPORT */

	default:
		result = 0;
		break;
	}

  return result;
}

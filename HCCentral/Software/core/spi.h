/*
 *
 * (c) by Alexander Neumann <alexander@bumpern.de>
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

#ifndef _SPI_H
#define _SPI_H

#include <stdint.h>
#include "config.h"

#define noinline __attribute__((noinline))

#ifdef SPI_SUPPORT

typedef enum SPI_Interface_e
{
#ifdef HW_SPI_SUPPORT
SPI_HW = 0,
#endif

#ifdef SOFT_SPI_SUPPORT
SPI_SW = 1,
#endif

#ifdef USART_SPI_SUPPORT
SPI_USART = 2
#endif
}SPI_Interface_t;

/* prototypes */
void spi_init(void);
uint8_t noinline spi_send(SPI_Interface_t interface, uint8_t data);

#endif /* SPI_SUPPORT */

#endif /* _SPI_H */

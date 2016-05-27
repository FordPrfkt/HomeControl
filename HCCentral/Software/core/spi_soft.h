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

#ifndef _SPI_SOFT_H
#define _SPI_SOFT_H

#include <stdint.h>
#include "config.h"

#ifdef SOFT_SPI_SUPPORT
#define noinline __attribute__((noinline))

/* prototypes */
uint8_t noinline spi_soft_send(uint8_t data);
#endif /* SOFT_SPI_SUPPORT */

#endif /* _SPI_SOFT_H */

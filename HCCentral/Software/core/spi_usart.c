/*
 *
 * Christian Dietrich <stettberger@dokucode.de>
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
#include "debug.h"
#include "spi_usart.h"

#define USE_USART SPI_USE_USART
#define BAUD 9600 /* Dummy */
#include "core/usart.h"

static void spi_wait_busy(void);

void spi_usart_init(void)
{
    usart(UBRR, L) = 0;
    usart(UBRR, H) = 0;

    DDR_CONFIG_OUT(USART_XCK);

    /* Set MSPI mode of operation and SPI data mode 0. */
    usart(UCSR,C) = _BV(usart(UMSEL,1)) | _BV(usart(UMSEL,0)) /*| _BV(usart(UCSZ0)) | _BV(usart(UCPOL))*/;
    /* Enable receiver and transmitter. */
    usart(UCSR,B) = _BV(usart(RXEN)) | _BV(usart(TXEN));
    /* Set baud rate. */
    /* IMPORTANT: The Baud Rate must be set after the transmitter is enabled
     * */
    /* Set to the higest available Baudrate: fosc/2 */
    usart(UBRR, L) = 0x1F;
    usart(UBRR, H) = 0;
}

static void spi_wait_busy(void)
{

#   ifdef SPI_TIMEOUT
    uint8_t timeout = 200;

    while (!(usart(UCSR,A) & _BV(usart(RXC))) && timeout > 0)
        timeout--;

    if (timeout == 0)
        debug_printf("ERROR: spi timeout reached!\r\n");
#   else
    while (!(usart(UCSR,A) & _BV(usart(RXC))));
#   endif

}

uint8_t noinline spi_usart_send(uint8_t data)
{
    usart(UDR) = data;
    spi_wait_busy();

    return usart(UDR);

}

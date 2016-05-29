dnl
dnl user_HCCentral.m4
dnl
dnl Pin Configuration for 'user_HCCentral'.  Edit it to fit your needs.
dnl

ifdef(`conf_RFM12', `dnl
/* port the rfm12 module CS is attached to */
pin(SPI_CS_RFM12_0, PC1, OUTPUT)
pin(SPI_CS_RFM12_1, PC6, OUTPUT)
pin(FS20_RECV, PC2, INPUT)
pin(FS20_SEND, PC3, OUTPUT)
RFM12_USE_INT(0)
RFM12_ASK_SENSE_USE_INT(0)
')

ifdef(`conf_BUTTONS_INPUT', `
/* input buttons */
pin(BTN_MODE, PA3, INPUT)

#define BUTTONS_COUNT 1

#define BUTTONS_CONFIG(_x) \
_x(BTN_MODE)\
')

/*pin(SOFT_SPI_MOSI, PB4, OUTPUT)
pin(SOFT_SPI_MISO, PB5, OUTPUT)
pin(SOFT_SPI_SCK, PB6, OUTPUT)
*/

/* port the enc28j60 is attached to */
pin(SPI_CS_NET, PB0, OUTPUT)

pin(STATUSLED_HB_ACT, PA0, OUTPUT)
pin(STATUSLED_NETLINK, PA1, OUTPUT)
pin(STATUSLED_BOOTED, PA2, OUTPUT)

pin(USART_XCK, PD4, OUTPUT)

/* port the sd-reader CS is attached to */
pin(SPI_CS_SD_READER, PB1, OUTPUT)
/* uncomment and edit this if you have connected the CD (card detect) signal */
pin(SD_READER_AVAILABLE, PB2, INPUT)
/* uncomment and edit this if you have connected the WP (write protected) signal */
pin(SD_READER_WR_PROTECT, PB3, INPUT)

dnl
dnl user_HCCentral.m4
dnl
dnl Pin Configuration for 'user_HCCentral'.  Edit it to fit your needs.
dnl

ifdef(`conf_BUTTONS_INPUT', `
/* input buttons */
pin(BTN_MODE, PA3, INPUT)

#define BUTTONS_COUNT 1

#define BUTTONS_CONFIG(_x) \
_x(BTN_MODE)\
')

pin(SOFT_SPI_MOSI, PB4, OUTPUT)
pin(SOFT_SPI_MISO, PB5, OUTPUT)
pin(SOFT_SPI_SCK, PB6, OUTPUT)

/* port the enc28j60 is attached to */
pin(SPI_CS_NET, PB0, OUTPUT)

/* port the sd-reader CS is attached to */
pin(SPI_CS_SD_READER, PB1, OUTPUT)
/* uncomment and edit this if you have connected the CD (card detect) signal */
pin(SD_READER_AVAILABLE, PB2, INPUT)
/* uncomment and edit this if you have connected the WP (write protected) signal */
pin(SD_READER_WR_PROTECT, PB3, INPUT)

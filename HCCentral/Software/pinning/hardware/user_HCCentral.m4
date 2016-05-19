dnl
dnl user_HCCentral.m4
dnl
dnl Pin Configuration for 'user_HCCentral'.  Edit it to fit your needs.
dnl

ifdef(`conf_BUTTONS_INPUT', `
/* input buttons */
pin(BTN_MODE, PC2, INPUT)

#define BUTTONS_COUNT 1

#define BUTTONS_CONFIG(_x) \
_x(BTN_MODE)\
')

/* port the enc28j60 is attached to */
pin(SPI_CS_NET, SPI_CS_HARDWARE)

/* port the sd-reader CS is attached to */
pin(SPI_CS_SD_READER, PB2, OUTPUT)
/* uncomment and edit this if you have connected the CD (card detect) signal */
pin(SD_READER_AVAILABLE, PD4, INPUT)
/* uncomment and edit this if you have connected the WP (write protected) signal */
pin(SD_READER_WR_PROTECT, PD5, INPUT)
/* uncomment and edit this if power of the SD card can be switched on/off */
//pin(SD_READER_POWERON, PD6, OUTPUT)

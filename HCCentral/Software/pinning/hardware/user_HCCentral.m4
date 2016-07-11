dnl
dnl user_HCCentral.m4
dnl
dnl Pin Configuration for 'user_HCCentral'.  Edit it to fit your needs.
dnl

pin(SPI_CS_RFM69_0, PC1, OUTPUT)
pin(SPI_CS_RFM69_1, PC6, OUTPUT)
pin(RESET_RFM69, PC7, OUTPUT)
pin(STATUSLED_RFM69_0, PA0, OUTPUT)
pin(STATUSLED_RFM69_1, PA1, OUTPUT)
pin(DIO0_RFM69_0, PC0, INPUT)
pin(DIO0_RFM69_1, PC5, INPUT)
pin(DIO1_RFM69_0, PD6, INPUT)
pin(DIO1_RFM69_1, PC3, INPUT)
pin(DIO2_RFM69_0, PD7, INPUT)
pin(DIO2_RFM69_1, PC4, INPUT)
pin(DIO5_RFM69_0, PD5, INPUT)
pin(DIO5_RFM69_1, PC2, INPUT)

pin(USART_XCK, PD4, OUTPUT)

pin(STATUSLED_HB_ACT, PA2, OUTPUT)

ifdef(`conf_BUTTONS_INPUT', `
/* input buttons */
pin(BTN_MODE, PA3, INPUT)
#define BUTTONS_COUNT 1
#define BUTTONS_CONFIG(_x) \
_x(BTN_MODE)\
')

/* port the enc28j60 is attached to */
pin(SPI_CS_NET, PB0, OUTPUT)

/* port the sd-reader CS is attached to */
pin(SPI_CS_SD_READER, PB1, OUTPUT)
pin(SD_READER_AVAILABLE, PB2, INPUT)
pin(SD_READER_WR_PROTECT, PB3, INPUT)

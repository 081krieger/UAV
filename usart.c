#include "usart.h"

#define BAUD_RATE 9600
#define UBRR_RATE ((F_CPU/16)/BAUD_RATE - 1)
#define DATA_BITS_IN_FRAME 0x03
#define RX_BUFF 10

void initUSART(void) {
    UBRR0H = ((UBRR_RATE) & 0xF00);
    UBRR0L = (uint8_t) ((UBRR_RATE) & 0xFF);
    TX_START();
    RX_START();
    UCSR0C = (DATA_BITS_IN_FRAME << UCSZ00);
}

uint8_t getByte(void) {
    while (!(UCSR0A & _BV(RXC0)));
    return (uint8_t) UDR0;
}

void writeByte(unsigned char data) {
    while (!(UCSR0A & _BV(UDRE0)));
    UDR0 = (unsigned char) data;
}

void writeString(char *string) {
    while (*string != '\0') {
        writeByte(*string);
        ++string;
    }
}

const char * readString(void) {
    static char rxstr[RX_BUFF];
    static char* temp;
    temp = rxstr;

    while((*temp = getByte()) != '\n') {
        ++temp;
    }

    return rxstr;
}

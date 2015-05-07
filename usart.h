#ifndef USART_H_
#define USART_H_

#include <avr/io.h>
#include <stdint.h>
#include "util.h"

#define TX_START() UCSR0B |= _BV(TXEN0)  // Enable TX
#define TX_STOP() UCSR0B &= ~_BV(TXEN0) // Disable TX
#define RX_START() UCSR0B |= _BV(RXEN0) // Enable RX
#define RX_STOP() UCSR0B &= ~_BV(RXEN0) // Disable RX

void initUSART(void);
uint8_t getByte(void);
void writeByte(unsigned char data);
void writeString(char *string);
const char * readString(void);

#endif /* USART_H_ */

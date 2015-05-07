/*
 * D9 engine1
 * D10 engine2
 * D3 engine3
 * D11 engine4
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "engines.h"
#include "usart.h"
#include "util.h"

void initExternalInterrupts(void);


void initExternalInterrupts() {
    EIMSK |= 1 << INT0;
    EICRA |= (1 << ISC01) | (1 << ISC00);
}

int main() {
//    initEngineHardware();
    initUSART();
//    initExternalInterrupts();

//    setEnginePower(0, ENGINE1);
//    setEnginePower(0, ENGINE2);
//    setEnginePower(0, ENGINE3);
//    setEnginePower(0, ENGINE4);
//    _delay_ms(3000);

//    sei();
//    cli();
    int i = 0;
    while (i < 1000) {
        writeByte('b');
        writeByte('\r');
        writeByte('\n');
        i++;
    }

    return 1;
}



ISR(INT0_vect) {
// In case of interrupt (int/usart/etc)
}

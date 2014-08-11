/*
 * D9 engine1
 * D10 engine2
 * D3 engine3
 * D11 engine4
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define F_CPU 16000000UL // from external clock osc.

#define ENGINE_MIN_TICS 122 // 1.060 ms
#define ENGINE_MAX_TICS 22 // 1.860 ms

#define ENGINE1 1
#define ENGINE2 2
#define ENGINE3 3
#define ENGINE4 4

void initT1PhaseCorrectPWM(void);
void initT2PhaseCorrectPWM(void);
void initPorts(void);
void initExternalInterrupts(void);

void setEnginePower(int power, int engine); // power is [0...100]

// engine 1 & 2
// phase correct PWM mode
// 8 bit
// top at 0xFF
// prescaler = 64
// set to 1 after reaching board
void initT1PhaseCorrectPWM(void) {
    TCCR1A |= (1 << COM1A1) | (1 << COM1B1) | (1 << COM1A0) | (1 << COM1B0)
            | (1 << WGM10);
    TCCR1B |= (1 << CS11) | (1 << CS10);
} // PWM frequency is now 490 Hz

// engine 3 & 4
// phase correct PWM mode
// mode 1
// top at 0xFF
// prescaler = 64
// set to 1 after reaching board
void initT2PhaseCorrectPWM(void) {
    TCCR2A |= (1 << COM2A1) | (1 << COM2B1) | (1 << COM2A0) | (1 << COM2B0)
            | (1 << WGM20);
    TCCR2B |= (1 << CS22);
} // PWM frequency is now 490 Hz

// put OC1A and OC1B pins as output
void initPorts(void) {
    DDRB = 0xFF;
    DDRD = 0x00;
    DDRD |= (1 << PD3);
}

void initExternalInterrupts() {
    EIMSK |= 1 << INT0;
    EICRA |= (1 << ISC01) | (1 << ISC00);
}

int main() {
    initPorts();
    initT1PhaseCorrectPWM();
    initT2PhaseCorrectPWM();
    initExternalInterrupts();

    setEnginePower(0, ENGINE1);
    setEnginePower(0, ENGINE2);
    setEnginePower(0, ENGINE3);
    setEnginePower(0, ENGINE4);
    _delay_ms(3000);

    sei();

    while (1) {
//        OCR1A = ENGINE_MIN_TICS;
//        OCR1B = ENGINE_MAX_TIX;
    }
    cli();

    return 1;
}

void setEnginePower(int power, int engine) {
    if (power < 0 || power > 100)
        return;
    if (engine == 1) {
        OCR1A = ENGINE_MIN_TICS - power;
    } else if (engine == 2) {
        OCR1B = ENGINE_MIN_TICS - power;
    } else if (engine == 3) {
        OCR2A = ENGINE_MIN_TICS - power;
    } else if (engine == 4) {
        OCR2B = ENGINE_MIN_TICS - power;
    }
}

ISR(INT0_vect) {
    for (int i = 0; i <= 100; i++) {
        setEnginePower(i, ENGINE1);
        setEnginePower(i, ENGINE2);
        setEnginePower(i, ENGINE3);
        setEnginePower(i, ENGINE4);
        _delay_ms(100);
    }
    _delay_ms(1000);
    for (int i = 100; i >= 0; i--) {
        setEnginePower(i, ENGINE1);
        setEnginePower(i, ENGINE2);
        setEnginePower(i, ENGINE3);
        setEnginePower(i, ENGINE4);
        _delay_ms(100);
    }
    _delay_ms(1000);
    setEnginePower(0, ENGINE1);
    setEnginePower(0, ENGINE2);
    setEnginePower(0, ENGINE3);
    setEnginePower(0, ENGINE4);
    cli();
}

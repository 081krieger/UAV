#include <avr/io.h>
#include <avr/interrupt.h>

#define F_CPU 16000000UL // from external clock osc.

#define ENGINE_MIN_TICS 119 // 1.064 ms
#define ENGINE_MAX_TIX 25 // 1.8 ms

void initT1PhaseCorrectPWM(void);
void initPorts(void);

// phase correct PWM mode
// 8 bit
// top at 0xFF
// prescaler = 64
// clear to zero after reaching board
void initT1PhaseCorrectPWM(void) {
    TCCR1A |= (1 << COM1A1) | (1 << COM1B1) | (1 << WGM10);
    TCCR1B |= (1 << CS11) | (1 << CS10);
} // PWM frequency is now 490 Hz

// put OC1A and OC1B pins as output
void initPorts(void) {
    DDRB |= (1 << PB1) | (1 << PB2);
}

int main() {
    initPorts();
    initT1PhaseCorrectPWM();

    while(1) {
        OCR1A = ENGINE_MIN_TICS;
    }

    return 1;
}

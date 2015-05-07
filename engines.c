#include "engines.h"

void initT1PhaseCorrectPWM(void);
void initT2PhaseCorrectPWM(void);

// put OC1A and OC1B pins as output
void initEngineHardware(void) {
	DDRB = 0xFF;
    DDRD = 0x00;
    DDRD |= (1 << PD3);
    initT1PhaseCorrectPWM();
    initT2PhaseCorrectPWM();
}

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

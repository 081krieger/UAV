#ifndef ENGINES_H_
#define ENGINES_H_

#include <avr/io.h>

#define ENGINE_MIN_TICS 122 // 1.060 ms
#define ENGINE_MAX_TICS 22 // 1.860 ms

#define ENGINE1 1
#define ENGINE2 2
#define ENGINE3 3
#define ENGINE4 4

void initEngineHardware(void);
void setEnginePower(int power, int engine); // power is [0...100]

#endif /* ENGINES_H_ */

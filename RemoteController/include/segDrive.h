#ifndef SEGDRIVE_H
#define SEGDRIVE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <Arduino.h>

// Add your function declarations and macros here

extern int segmentChoosePins[];
extern int segmentDigitPins[];
extern int letters[3][4];

void initSegment();
void writeO();
void writeN();
void writeF(int digit);
void writeON();
void writeOFF();
void close();
void writeError(int loop_times);


#ifdef __cplusplus
}
#endif

#endif // SEGDRIVE_H
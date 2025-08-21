#include "segDrive.h"

int segmentChoosePins[] = {9, 5, 4};
int segmentDigitPins[] = {
  3, //b
  7, //c
  8, //d
  6  //g
};

int letters[3][4] = {
  {0,0,0,1},//O
  {0,0,1,1},//N
  {1,1,1,0} //F
};


void initSegment(){
  for (size_t i = 0; i < 3; i++)
  {
    pinMode(segmentChoosePins[i], OUTPUT);  // set segment selection pins as output
  }
  for (size_t i = 0; i < 4; i++)
  {
    pinMode(segmentDigitPins[i], OUTPUT);  // set segment digit pins as output
  }
  for (size_t i = 0; i < 4; i++)
  {
    digitalWrite(segmentDigitPins[i], HIGH);  // set segment digit pins to HIGH (off)
  }

  close();
}

void writeO(){
  digitalWrite(segmentChoosePins[0], HIGH);
  digitalWrite(segmentChoosePins[1], LOW);
  digitalWrite(segmentChoosePins[2], LOW);

  for (size_t i = 0; i < 4; i++)
  {
    digitalWrite(segmentDigitPins[i], letters[0][i]);
  }
}

void writeN(){
  digitalWrite(segmentChoosePins[0], LOW);
  digitalWrite(segmentChoosePins[1], HIGH);
  digitalWrite(segmentChoosePins[2], LOW);

  for (size_t i = 0; i < 4; i++)
  {
    digitalWrite(segmentDigitPins[i], letters[1][i]);
  }
}

void writeF(int digit){
  digitalWrite(segmentChoosePins[0], LOW);
  if (digit == 0)
  {
    digitalWrite(segmentChoosePins[1], HIGH);
    digitalWrite(segmentChoosePins[2], LOW);
  }
  else if (digit == 1)
  {
    digitalWrite(segmentChoosePins[1], LOW);
    digitalWrite(segmentChoosePins[2], HIGH);
  }

  for (size_t i = 0; i < 4; i++)
  {
    digitalWrite(segmentDigitPins[i], letters[2][i]);
  }
}

void writeON(){
  writeO();
  delay(12);
  writeN();
  delay(12);
}
void writeOFF(){
  writeO();
  delay(8);
  writeF(0);
  delay(8);
  writeF(1);
  delay(8);
}
void close() {
  for (size_t i = 0; i < 3; i++)
  {
    digitalWrite(segmentChoosePins[i], LOW);
  }
  for (size_t i = 0; i < 4; i++)
  {
    digitalWrite(segmentDigitPins[i], HIGH);
  }
}
void writeError(int loop_times){
  close();
  if (loop_times == 0)
  {
    digitalWrite(segmentChoosePins[0], HIGH);
    digitalWrite(segmentChoosePins[1], LOW);
    digitalWrite(segmentChoosePins[2], LOW);
  }
  else if (loop_times == 1)
  {
    digitalWrite(segmentChoosePins[0], LOW);
    digitalWrite(segmentChoosePins[1], HIGH);
    digitalWrite(segmentChoosePins[2], LOW);
  }
  else if (loop_times == 2)
  {
    digitalWrite(segmentChoosePins[0], LOW);
    digitalWrite(segmentChoosePins[1], LOW);
    digitalWrite(segmentChoosePins[2], HIGH);
  }
  digitalWrite(segmentDigitPins[0], LOW);
  digitalWrite(segmentDigitPins[1], LOW);
  digitalWrite(segmentDigitPins[2], LOW);
  digitalWrite(segmentDigitPins[3], LOW);
}
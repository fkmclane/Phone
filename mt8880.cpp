#include "Arduino.h"

#include "mt8880.h"

void mt8880_init() {
  //Prepare chip select and register select
  pinMode(CS, OUTPUT);
  digitalWrite(CS, HIGH);
  pinMode(RS, OUTPUT);
  digitalWrite(RS, HIGH);

  //Wait until 100ms after power on
  while(millis() < 100);

  //Creepy initialization magic from the datasheet
  mt8880_read(true);
  mt8880_write(0b0000, true);
  mt8880_write(0b0000, true);
  mt8880_write(0b1000, true);
  mt8880_write(0b0000, true);
  mt8880_read(true);
}

char mt8880_read(bool rs) {
  //Data pins should be inputs
  pinMode(D0, INPUT);
  pinMode(D1, INPUT);
  pinMode(D2, INPUT);
  pinMode(D3, INPUT);

  //Select chip
  digitalWrite(CS, LOW);

  //Select status/control registers (based on rs value)
  digitalWrite(RS, rs);

  //Read register
  digitalWrite(RW, HIGH);

  //Clock pulse (so the chip updates)
  digitalWrite(O2, HIGH);
  delay(5);

  //Storage
  char data = 0;

  //Fun bitwise stuff to read and combine the binary values
  data |= digitalRead(D3);
  data <<= 1;
  data |= digitalRead(D2);
  data <<= 1;
  data |= digitalRead(D1);
  data <<= 1;
  data |= digitalRead(D0);

  //Clock pulse
  digitalWrite(O2, LOW);
  delay(5);

  //Deselect chip
  digitalWrite(CS, HIGH);

  return data;
}

void mt8880_write(char data, bool rs) {
  //Data pins should be outputs
  pinMode(D0, OUTPUT);
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);

  //Select chip
  digitalWrite(CS, LOW);

  //Select status/control registers (based on rs value)
  digitalWrite(RS, rs);

  //Write register
  digitalWrite(RW, LOW);

  //Fun bitwise stuff to separate and write the binary values
  digitalWrite(D0, data & 1);
  data >>= 1;
  digitalWrite(D1, data & 1);
  data >>= 1;
  digitalWrite(D2, data & 1);
  data >>= 1;
  digitalWrite(D3, data & 1);
  data >>= 1;

  //Clock pulse (so the chip updates)
  digitalWrite(O2, HIGH);
  delay(5);

  //Clock pulse
  digitalWrite(O2, LOW);
  delay(5);

  //Deselect chip
  digitalWrite(CS, HIGH);
}

#include "Arduino.h"

#include "mt8880.h"

char dtmf_chars[] = { 'D', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '*', '#', 'A', 'B', 'C' };

void dtmf_init() {
  mt8880_init();

  //CTRL A: write both registers, IRQ enable, DTMF logic, tone output
  mt8880_write(0b1101, true);
  //CTRL B: x, dual tones, no test, no burst
  mt8880_write(0b0001, true);
}

void dtmf_write(char dtmf_char) {
  //Search for character in array and write its index number (corresponds to mt8880 datasheet values) if found
  for (char i = 0; i < 16; i++) {
    if (dtmf_chars[i] == dtmf_char) {
      //Technically this function is returning void since mt8880_write returns void
      //Here in case I decide to make it return a value later on
      return mt8880_write(i);
    }
  }
}

char dtmf_read() {
  //Return the character at the index number (corresponds to mt8880 datasheet values)
  return dtmf_chars[mt8880_read()];
}

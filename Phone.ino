#include "dtmf.h"

void setup() {
  dtmf_init();

  attachInterrupt(IRQ, dtmf_recv, FALLING);

  Serial.begin(9600);
}

void loop() {
  if(Serial.available())
    dtmf_write(Serial.read());

  delay(90);
}

void dtmf_recv() {
  Serial.print(dtmf_read());
}

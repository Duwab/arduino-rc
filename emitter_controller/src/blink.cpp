#include "Arduino.h"
#include "blink.h"

Blink::Blink()
{
    // constructor
    sD = 100;
    mD = 500;
    lD = 2000;
}

void Blink::init()
{
    // init
    pinMode(LED_BUILTIN, OUTPUT);
}

void Blink::once(int duration) {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(duration);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);
  delay(duration);                       // wait for a second
}

void Blink::ack() {
  once(sD);
  once(sD);
  once(sD);
}

#ifndef BLINK_H
#define BLINK_H

#include <Arduino.h>

class Blink
{
    public:
      Blink();
      void init();
      void once(int duration);
      void ack();
      int sD;
      int mD;
      int lD;
};

#endif

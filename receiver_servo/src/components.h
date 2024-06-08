#ifndef COMPONENTS_H
#define COMPONENTS_H

#include <Arduino.h>
#include <Servo.h>

class Components
{
    public:
      Components();
      void init();
      void setServo1(uint8_t angle, int rangeMin, int rangeMax);
      void setServo2(uint8_t angle, int rangeMin, int rangeMax);
};

#endif

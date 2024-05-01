#ifndef SENSORS_H
#define SENSORS_H

#include <Arduino.h>

class Sensors
{
    public:
      Sensors();
      void init();
      int getPinA();
      int getPinB();
      bool hasChangedPinA();
      bool hasChangedPinB();
      void recordPinA();
      void recordPinB();
    private:
      int _lastPinAValue;
      int _lastPinBValue;
};

#endif

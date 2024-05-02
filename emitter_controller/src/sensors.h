#ifndef SENSORS_H
#define SENSORS_H

#include <Arduino.h>

class Sensors
{
    public:
      Sensors();
      void init();
      uint8_t analogReadNormalized(int pinId, int maxMeasure);
      uint8_t getX();
      uint8_t getY();
      uint8_t getZ();
      bool getSW();
      void logValues();
    // private:
    //   int _lastPinAValue;
};

#endif

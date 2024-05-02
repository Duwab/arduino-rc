#ifndef SENSORS_H
#define SENSORS_H

#include <Arduino.h>

class Sensors
{
    public:
      Sensors();
      void init();
      int analogReadNormalized(int pinId, int maxMeasure);
      int getX();
      int getY();
      int getZ();
      int getSW();
      void logValues();
    // private:
    //   int _lastPinAValue;
};

#endif

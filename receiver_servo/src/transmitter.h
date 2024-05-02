#ifndef TRANSMITTER_H
#define TRANSMITTER_H

#include <Arduino.h>
#include <RF24.h>

class Transmitter
{
    public:
      Transmitter();
      void init();
      char* readMessage();
      RF24 _radio;
};

#endif

#ifndef TRANSMITTER_H
#define TRANSMITTER_H

#include <Arduino.h>
#include <RF24.h>

class Transmitter
{
    public:
      Transmitter();
      void init();
      void sendMessage(const char* messageOut);
      RF24 _radio;
};

#endif

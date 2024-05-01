#include "Arduino.h"
#include "sensors.h"

const int pinA = 3;
const int pinB = 4;

Sensors::Sensors()
{
    // constructor
    _lastPinAValue = 0;
    _lastPinBValue = 0;
}

void Sensors::init()
{
    pinMode(pinA, INPUT);
    pinMode(pinB, INPUT);
}

bool Sensors::hasChangedPinA()
{
    return _lastPinAValue != getPinA();
}

bool Sensors::hasChangedPinB()
{
    return _lastPinBValue != getPinB();
}

void Sensors::recordPinA()
{
    _lastPinAValue = getPinA();
}

void Sensors::recordPinB()
{
    _lastPinBValue = getPinB();
}

int Sensors::getPinA()
{
    return digitalRead(pinA);
}

int Sensors::getPinB()
{
    return digitalRead(pinB);
}

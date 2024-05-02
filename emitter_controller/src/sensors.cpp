#include "Arduino.h"
#include "sensors.h"

// joystick
#define VX_PIN 1
#define VY_PIN 2
#define BUTTON_SW_PIN 2
int valueX = 0;
int valueY = 0;
int valueZ = 0;
const int JOYSTICK_MAX = 1023; // manual read of this value

// potentiometer
#define VZ_PIN 5
const int POTENTIOMETER_MAX = 700; // manual read of this value

Sensors::Sensors()
{
    // constructor
}

void Sensors::init()
{
    // init joystick
    pinMode(BUTTON_SW_PIN, INPUT_PULLUP);
}

void Sensors::logValues()
{
    Serial.print("X:");
    Serial.print(getX(), DEC);
    Serial.print(" | Y:");
    Serial.print(getY(), DEC);
    Serial.print(" | Z:");
    Serial.print(getZ(), DEC);
    Serial.print(" | SW:");
    Serial.println(getSW(), DEC);
}

// X for the controller is in fact the VY pin of the joystick
int Sensors::getX()
{
    return analogReadNormalized(VY_PIN, JOYSTICK_MAX);
}

// Y : same explanation as X
int Sensors::getY()
{
    return analogReadNormalized(VX_PIN, JOYSTICK_MAX);
}

int Sensors::getZ()
{
    return 127 - analogReadNormalized(VZ_PIN, POTENTIOMETER_MAX);
}

int Sensors::getSW()
{
    return digitalRead(BUTTON_SW_PIN);
}

int Sensors::analogReadNormalized(int pinId, int maxMeasure)
{
    int measure = analogRead(pinId);

    if (measure < 0) {
        measure = 0;
    } else if (measure > maxMeasure) {
        measure = maxMeasure;
    }

    return map(measure, 0, maxMeasure, 0, 127);
}

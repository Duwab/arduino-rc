#include "Arduino.h"
#include "components.h"
#include <Servo.h>

#define pinSERVOESC 3
#define pinSERVO1   5
#define pinSERVO2   6
#define pinSERVO3   9

Servo servo1;
Servo servo2;
Servo servo3;
Servo servoESC;

#define dureeMinimaleImpulsionCommandeESC     1000        // La durée minimale pour une impulsion est de 1000 µs, soit 1 ms (comme pour un servomoteur, en fait)
#define dureeMaximaleImpulsionCommandeESC     2000        // La durée maximale pour une impulsion est de 2000 µs, soit 2 ms (comme pour un servomoteur, idem donc)

Components::Components()
{
    // constructor
}

int DELAY_BETWEEN_POS = 1000;
int DELAY_BETWEEN_SERVO = 0;

void Components::init()
{
    servo1.attach(pinSERVO1);
    servo2.attach(pinSERVO2);
    servo3.attach(pinSERVO3);
    servoESC.attach(pinSERVOESC, dureeMinimaleImpulsionCommandeESC, dureeMaximaleImpulsionCommandeESC);
    servo1.write(0);
    delay(DELAY_BETWEEN_SERVO);
    servo2.write(0);
    delay(DELAY_BETWEEN_POS);
    servo1.write(180);
    delay(DELAY_BETWEEN_SERVO);
    servo2.write(180);
    delay(DELAY_BETWEEN_POS);
    servo1.write(90);
    delay(DELAY_BETWEEN_SERVO);
    servo2.write(90);
}

void Components::setServo1(uint8_t angle, int rangeMin, int rangeMax) {
    int angleServo1 = map(angle, rangeMin, rangeMax, 0, 180);
    servo1.write(angleServo1);
}

void Components::setServo2(uint8_t angle, int rangeMin, int rangeMax) {
    int angleServo2 = map(angle, rangeMin, rangeMax, 0, 180);
    servo2.write(angleServo2);
}

void Components::setServo3(uint8_t angle, int rangeMin, int rangeMax) {
    int angleServo3 = map(angle, rangeMin, rangeMax, 0, 180);
    servo3.write(angleServo3);
}

void Components::setServoESC(uint8_t angle, int rangeMin, int rangeMax) {
    int escSpeed = map(angle, rangeMin, rangeMax, dureeMinimaleImpulsionCommandeESC, dureeMaximaleImpulsionCommandeESC);
    servoESC.writeMicroseconds(escSpeed);
}

/**
 * This emitter is for a multi-purpose remote controller
 * Will contain specific and evolutive sensors/transmission protocols
 * If core communication problems are encountered, prefer using the basic emitter to troubleshoot configuration
 */

#include "src/blink.h"
#include "src/sensors.h"
#include "src/transmitter.h"

Blink blinkUtil;
Sensors mySensors; // no brackets when no args
//Sensors mySensors(arg1, arg2);
Transmitter transmitter;

void setup() {
  Serial.begin(115200);
  blinkUtil.init();
  mySensors.init();
  blinkUtil.ack();
  transmitter.init();
  blinkUtil.ack();
}

void initRadio() {
}

// the loop function runs over and over again forever
void loop() {
  if (mySensors.hasChangedPinA()) {
    mySensors.recordPinA();
    transmitter.sendMessage("sendA");
  }
  if (mySensors.hasChangedPinB()) {
    mySensors.recordPinB();
    transmitter.sendMessage("sendB");
  }
  
  //if (radio.available()) {        // On vérifie si un message est en attente de lecture
  //  radio.read(&message, sizeof(message));             // Si oui, on le charge dans la variable "message"
  //}
}

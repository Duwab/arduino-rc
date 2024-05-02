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

struct ControllerData {
  uint8_t x; // 1o
  uint8_t y; // 1o
  uint8_t z; // 1o
  bool sw;   // 1o
  int other; // 2o
             //=6o (max 32o)
};

ControllerData controllerData = { 0, 0, 0, 0, 0 };

void setup() {
  Serial.begin(115200);
  blinkUtil.init();
  mySensors.init();
  blinkUtil.ack();
  transmitter.init();
  blinkUtil.ack();
}

// the loop function runs over and over again forever
void loop() {
  mySensors.logValues();
  transmitter.sendMessage("sendA");
  transmitter.sendMessage("sendB");

  readControllerData();
  transmitter._radio.write(&controllerData, sizeof(controllerData));
  delay(300);

  //if (radio.available()) {        // On vérifie si un message est en attente de lecture
  //  radio.read(&message, sizeof(message));             // Si oui, on le charge dans la variable "message"
  //}
}

void readControllerData() {
  controllerData.x = mySensors.getX();
  controllerData.y = mySensors.getY();
  controllerData.z = mySensors.getZ();
  controllerData.sw = mySensors.getSW();
  controllerData.other = 12;
}

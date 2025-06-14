/*
   ______               _                  _///  _           _                   _
  /   _  \             (_)                |  __\| |         | |                 (_)
  |  [_|  |__  ___  ___ _  ___  _ __      | |__ | | ___  ___| |_ _ __ ___  _ __  _  ___  _   _  ___
  |   ___/ _ \| __|| __| |/ _ \| '_ \_____|  __|| |/ _ \/  _|  _| '__/   \| '_ \| |/   \| | | |/ _ \
  |  |  | ( ) |__ ||__ | | ( ) | | | |____| |__ | |  __/| (_| |_| | | (_) | | | | | (_) | |_| |  __/
  \__|   \__,_|___||___|_|\___/|_| [_|    \____/|_|\___|\____\__\_|  \___/|_| |_|_|\__  |\__,_|\___|
                                                                                      | |
                                                                                      \_|
  Fichier:      HelloWorldNRF24L01-Recepteur
  Description:  Réception d'un message "Hello World" depuis un autre arduino nano, via un NRF24L01
  Auteur:       Passion-Électronique

  Librairie utilisée : https://github.com/nRF24/RF24

  Créé le 19.03.2021
*/
#include "Arduino.h"
#include "src/transmitter.h"
#include "src/components.h"

//Sensors mySensors(arg1, arg2);
Transmitter transmitter;
Components components;

struct ControllerData {
  uint8_t x; // 1o
  uint8_t y; // 1o
  uint8_t z; // 1o
  bool sw;   // 1o
  int other; // 2o
             //=6o (max 32o)
};

ControllerData controllerData = { 0, 0, 0, 0, 0 };

unsigned long lastMeasure = 0;

void setup() {
  // Initialisation du port série (pour afficher les infos reçues, sur le "Moniteur Série" de l'IDE Arduino)
  Serial.begin(115200);
  Serial.println("Récepteur NRF24L01");
  Serial.println("");

  components.init();
  transmitter.init();
  resetValues();
}

void loop() {
  char* lastMessage = transmitter.readMessage();

  if (strstr(lastMessage, "<empty>") != NULL) {
    return loopFallback();
  }
  if (strstr(lastMessage, "send") != NULL) {
    logMessage(lastMessage);
    return loopFallback();
  }

  lastMeasure = millis();

  memcpy(&controllerData, lastMessage, sizeof(controllerData));

  components.setServo1(controllerData.x, 0, 127);
  components.setServo2(controllerData.y, 0, 127);
  components.setServo3(controllerData.z, 0, 127);
  components.setServoESC(controllerData.z, 0, 127);
  logControllerData();

}

void loopFallback() {
  if ((millis() - lastMeasure) > 1000) {
    resetValues();
  }
}

void resetValues() {
  components.setServo1(63, 0, 127);
  components.setServo2(63, 0, 127);
  components.setServo3(63, 0, 127);
  components.setServoESC(0, 0, 127);
}

void logMessage(char* message)
{
  Serial.print("Message reçu (");
  Serial.print(sizeof(message));
  Serial.print(") : ");
  Serial.println(message);     // … et on l'affiche sur le port série !
}

void logControllerData()
{
  Serial.print("Controller: x=");
  Serial.print(controllerData.x, DEC);
  Serial.print(", y=");
  Serial.print(controllerData.y, DEC);
  Serial.print(", z=");
  Serial.print(controllerData.z, DEC);
  Serial.print(", sw=");
  Serial.print(controllerData.sw, DEC);
  Serial.print(", other=");
  Serial.println(controllerData.other, DEC);
}

void blinkLED(int pinId) {
  digitalWrite(pinId, 1);
  delay(100);
  digitalWrite(pinId, 0);
}

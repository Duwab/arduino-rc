#include <SPI.h>
#include <RF24.h>
#include "src/blink.h"
#include "src/sensors.h"
#include "src/transmitter.h"

#define pinCE   7             // On associe la broche "CE" du NRF24L01 à la sortie digitale D7 de l'arduino
#define pinCSN  8             // On associe la broche "CSN" du NRF24L01 à la sortie digitale D8 de l'arduino
RF24 radio(pinCE, pinCSN);    // Instanciation du NRF24L01

const int RADIO_CHANNEL = 44;
const rf24_pa_dbm_e RADIO_POWER = RF24_PA_MIN;
//const rf24_pa_dbm_e RADIO_POWER = RF24_PA_HIGH;
const rf24_datarate_e RADIO_RATE = RF24_250KBPS;

#define tunnel1  "PIPE1"       // On définit un "nom de tunnel" (5 caractères), pour pouvoir communiquer d'un NRF24 à l'autre
#define tunnel2  "PIPE2"
#define tunnel3  "PIPE3"
#define tunnel4  "PIPE4"
#define tunnel5  "PIPE5"
#define tunnel6  "PIPE6"

const byte adresse[6] = tunnel1;               // Mise au format "byte array" du nom du tunnel

Blink blinkUtil;
Sensors mySensors; // no brackets when no args
//Sensors mySensors(arg1, arg2);
Transmitter transmitter;

void setup() {
  Serial.begin(115200);
  blinkUtil.init();
  mySensors.init();
  transmitter.init();
  blinkUtil.ack();
  initRadio();
  blinkUtil.ack();
}

void initRadio() {
  radio.begin();
  radio.setChannel(RADIO_CHANNEL);
  radio.setDataRate(RADIO_RATE);
  radio.openWritingPipe(adresse);      // Ouverture du "tunnel1" en ÉCRITURE (émission radio)
  radio.setPALevel(RADIO_POWER);
  //radio.openReadingPipe(1, adresses[1]);   // Ouverture du "tunnel2" en LECTURE (réception radio)
  radio.stopListening();
}

// the loop function runs over and over again forever
void loop() {
  if (mySensors.hasChangedPinA()) {
    mySensors.recordPinA();
    sendMessage("sendA");
  }
  if (mySensors.hasChangedPinB()) {
    mySensors.recordPinB();
    sendMessage("sendB");
  }
  
  //if (radio.available()) {        // On vérifie si un message est en attente de lecture
  //  radio.read(&message, sizeof(message));             // Si oui, on le charge dans la variable "message"
  //}


}

void sendMessage(const char* messageOut) {
  //char messageOut[] = "Ma doudoune";    // Dans la limite de 32 octets (32 caractères, ici)
  Serial.println("send " + String(messageOut));
  radio.write(messageOut, strlen(messageOut));             // Envoi du contenu stocké dans la variable "message"
}

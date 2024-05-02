/**
 * Ensure both emitter & receiver has the same values for
 *   - RADIO_CHANNEL
 *   - RADIO_RATE
 *   - tunnel
 *   - data structs
 */

#include "Arduino.h"
#include "transmitter.h"
#include <SPI.h>
#include <RF24.h>

/*
  SPI communication (Serial Peripheral Interface)
  Arduino has 3 pins (11 - out, 12 - in, 13 - clock) ready to communicate with peripherals
    - communicates with 1 at a time
    - use CSN to tell the peripheral if it is involved in the communication
    - CE seems to tell the peripheral if controller is in transmission/reception mode
*/
#define pinCE   7
#define pinCSN  8
//pin MOSI = COPI = 11 = M0
//pin MISO = CIP0 = 12 = M1
//pin SCK = 13

const int RADIO_CHANNEL = 44;
const rf24_pa_dbm_e RADIO_POWER = RF24_PA_MIN;
const rf24_datarate_e RADIO_RATE = RF24_250KBPS;

#define tunnel1  "PIPE1"       // On définit un "nom de tunnel" (5 caractères), pour pouvoir communiquer d'un NRF24 à l'autre
#define tunnel2  "PIPE2"
#define tunnel3  "PIPE3"
#define tunnel4  "PIPE4"
#define tunnel5  "PIPE5"
#define tunnel6  "PIPE6"

const byte adresse[6] = tunnel1;               // Mise au format "byte array" du nom du tunnel
char message[32];                     // Avec cette librairie, on est "limité" à 32 caractères par message

Transmitter::Transmitter ()
    : _radio(pinCE, pinCSN) // Instanciation du NRF24L01
{
    // constructor
}

void Transmitter::init()
{
    // init
    _radio.begin();                      // Initialisation du module NRF24
    _radio.setChannel(RADIO_CHANNEL);
    _radio.setDataRate(RADIO_RATE);
    _radio.openReadingPipe(0, adresse);  // Ouverture du tunnel en LECTURE, avec le "nom" qu'on lui a donné
    _radio.setPALevel(RADIO_POWER);
    _radio.startListening();             // Démarrage de l'écoute du NRF24 (signifiant qu'on va recevoir, et non émettre quoi que ce soit, ici)
}

char* Transmitter::readMessage() {
  if (_radio.available()) {
    _radio.read(&message, sizeof(message));                        // Si un message vient d'arriver, on le charge dans la variable "message"
    //Serial.print(message);
  } else {
    memcpy(&message, "<empty>", sizeof(message));
  }

  return message;
}

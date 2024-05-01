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
//const rf24_pa_dbm_e RADIO_POWER = RF24_PA_HIGH;
const rf24_datarate_e RADIO_RATE = RF24_250KBPS;

#define tunnel1  "PIPE1"       // On définit un "nom de tunnel" (5 caractères), pour pouvoir communiquer d'un NRF24 à l'autre
#define tunnel2  "PIPE2"
#define tunnel3  "PIPE3"
#define tunnel4  "PIPE4"
#define tunnel5  "PIPE5"
#define tunnel6  "PIPE6"

const byte adresse[6] = tunnel1;               // Mise au format "byte array" du nom du tunnel

Transmitter::Transmitter ()
    : _radio(pinCE, pinCSN) // Instanciation du NRF24L01
{
    // constructor
}

void Transmitter::init()
{
    // init
    _radio.begin();
    _radio.setChannel(RADIO_CHANNEL);
    _radio.setDataRate(RADIO_RATE);
    _radio.openWritingPipe(adresse);      // Ouverture du "tunnel1" en ÉCRITURE (émission radio)
    _radio.setPALevel(RADIO_POWER);
    //radio.openReadingPipe(1, adresses[1]);   // Ouverture du "tunnel2" en LECTURE (réception radio)
    _radio.stopListening();
}

void Transmitter::sendMessage(const char* messageOut) {
  //char messageOut[] = "0123456789.0123456789.0123456789";    // Dans la limite de 32 octets (32 caractères, ici)
  Serial.println("send " + String(messageOut));
  _radio.write(messageOut, strlen(messageOut));             // Envoi du contenu stocké dans la variable "message"
}

#include <SPI.h>
#include <RF24.h>

#define pinStatus 2
#define pinCE   7             // On associe la broche "CE" du NRF24L01 à la sortie digitale D7 de l'arduino
#define pinCSN  8             // On associe la broche "CSN" du NRF24L01 à la sortie digitale D8 de l'arduino
RF24 radio(pinCE, pinCSN);    // Instanciation du NRF24L01

const int RADIO_CHANNEL = 12;
const rf24_pa_dbm_e RADIO_POWER = RF24_PA_HIGH;
const rf24_datarate_e RADIO_RATE = RF24_250KBPS;

#define tunnel1  "PIPE1"       // On définit un "nom de tunnel" (5 caractères), pour pouvoir communiquer d'un NRF24 à l'autre
#define tunnel2  "PIPE2"
#define tunnel3  "PIPE3"
#define tunnel4  "PIPE4"
#define tunnel5  "PIPE5"
#define tunnel6  "PIPE6"

const byte adresse[6] = tunnel1;               // Mise au format "byte array" du nom du tunnel


const int sD = 500;
const int mD = 2000;
const int LD = 3000;

void setup() {
  pinMode(pinStatus, OUTPUT);
  doBlink(sD);
  doBlink(sD);
  doBlink(sD);
  initRadio();
  doBlink(sD);
  doBlink(sD);
  doBlink(sD);
}

void initRadio() {
  radio.begin();
  radio.setChannel(RADIO_CHANNEL);
  radio.setPALevel(RF24_PA_HIGH);
  radio.setDataRate(RF24_250KBPS);
  radio.openWritingPipe(adresse);      // Ouverture du "tunnel1" en ÉCRITURE (émission radio)
  //radio.openReadingPipe(1, adresses[1]);   // Ouverture du "tunnel2" en LECTURE (réception radio)
  radio.stopListening();
}

// the loop function runs over and over again forever
void loop() {
  doBlink(mD);
  
  //if (radio.available()) {        // On vérifie si un message est en attente de lecture
  //  radio.read(&message, sizeof(message));             // Si oui, on le charge dans la variable "message"
  //}

  char messageOut[] = "Mon message à envoyer !";    // Dans la limite de 32 octets (32 caractères, ici)
  
  radio.write(&messageOut, sizeof(messageOut));             // Envoi du contenu stocké dans la variable "message"

}
  
void doBlink(int duration) {
  digitalWrite(pinStatus, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(duration);                       // wait for a second
  digitalWrite(pinStatus, LOW);    // turn the LED off by making the voltage LOW
  delay(duration);                       // wait for a second
}

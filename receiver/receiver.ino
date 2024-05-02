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
#include <SPI.h>
#include <RF24.h>

#define pinA    3             // pour les tests
#define pinB    4             // pour les tests
#define pinCE   7             // On associe la broche "CE" du NRF24L01 à la sortie digitale D7 de l'arduino
#define pinCSN  8             // On associe la broche "CSN" du NRF24L01 à la sortie digitale D8 de l'arduino
#define tunnel  "PIPE1"       // On définit le "nom de tunnel" (5 caractères) à travers lequel on va recevoir les données de l'émetteur

RF24 radio(pinCE, pinCSN);    // Instanciation du NRF24L01

const int RADIO_CHANNEL = 44;
const rf24_pa_dbm_e RADIO_POWER = RF24_PA_HIGH;
const rf24_datarate_e RADIO_RATE = RF24_250KBPS;

const byte adresse[6] = tunnel;       // Mise au format "byte array" du nom du tunnel
char message[32];                     // Avec cette librairie, on est "limité" à 32 caractères par message

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
  // Initialisation du port série (pour afficher les infos reçues, sur le "Moniteur Série" de l'IDE Arduino)
  Serial.begin(115200);
  Serial.println("Récepteur NRF24L01");
  Serial.println("");

  pinMode(pinA, OUTPUT);
  pinMode(pinB, OUTPUT);

  // Partie NRF24
  radio.begin();                      // Initialisation du module NRF24
  radio.setChannel(RADIO_CHANNEL);
  radio.setDataRate(RF24_250KBPS);
  radio.openReadingPipe(0, adresse);  // Ouverture du tunnel en LECTURE, avec le "nom" qu'on lui a donné
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();             // Démarrage de l'écoute du NRF24 (signifiant qu'on va recevoir, et non émettre quoi que ce soit, ici)
}

void loop() {
  //Serial.print("loop");
  //delay(100);
  // On vérifie à chaque boucle si un message est arrivé
  if (radio.available()) {
    radio.read(&message, sizeof(message));                        // Si un message vient d'arriver, on le charge dans la variable "message"
    logMessage();
    if (strstr(message, "send") == NULL) {
      memcpy(&controllerData, &message, sizeof(controllerData));
      logControllerData();
    } else {
      blinkLED();
    }
  }
}

void logMessage()
{
  Serial.print("Message reçu (");
  Serial.print(sizeof(message));
  Serial.print(") : ");
  Serial.println(message);     // … et on l'affiche sur le port série !
}

void logControllerData()
{
  Serial.print("This is a struct: x=");
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

void blinkLED() {
  int pinId = pinA;
  if (strstr(message, "sendB") != NULL) {
    pinId = pinB;
  }
  digitalWrite(pinId, 1);
  delay(100);
  digitalWrite(pinId, 0);
}

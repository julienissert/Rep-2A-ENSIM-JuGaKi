//imports libs//
#include <Servo.h>
//#include <PCM.h>
#include <IRremote.h> // >v3.0.0
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

//setup
Servo servo1; //Initialisation de la classe Servo pour le servo1
Servo servo2; //Initialisation de la classe Servo pour le servo2
#define PIN_SENSOR_IR 2 //Définition de la constante PIN_SENSOR_IR à 2
#define PIN_LED_IR 3 //Définition de la constante PIN_LED_IR à 3
#define PIN_SERVO_1 12 //Définition de la constante PIN_SERVO_1 à 12
#define PIN_SERVO_2 7 //Définition de la constante PIN_SERVO_2 à 7
#define PIN_BUTTON_TIR 11 //Définition de la constante PIN_BUTTON_TIR à 11
#define PIN_BUTTON_RST 4 //Définition de la constante PIN_BUTTON_RST à 4
#define VIBRATEUR_PIN 9 //Définition de la constante VIBRATEUR_PIN à 9
#define HP_PIN 10 //Définition de la constante HP_PIN à 10
#define joyX1 A0 //Définition de la constante joyX1 à A0
#define joyY1 A1 //Définition de la constante joyY1 à A1
#define joyX2 A2 //Définition de la constante joyX2 à A2
#define joyY2 A3 //Définition de la constante joyY2 à A3
#define HorizontalPotPin A4 //Définition de la constante HorizontalPotPin à A4
#define VerticalPotPin A5 //Définition de la constante VerticalPotPin à A5
int x =10; //Déclaration et initialisation de la variable x à 10
LiquidCrystal_I2C LCD(0x27,16,2); //Initialisation de la classe LiquidCrystal_I2C pour l'écran LCD
int i;

// gestion temps partie
bool game_bool = false; //Déclaration et initialisation de la variable booléenne game_bool à false
int game_time = 180; //Déclaration et initialisation de la variable entière game_time à 180 (en secondes)
int game_start_time; //Déclaration de la variable entière game_start_time
int game_elapsed_time; //Déclaration de la variable entière game_elapsed_time

// gestion resultats
bool results_bool = false; //Déclaration et initialisation de la variable booléenne results_bool à false
bool game_connexion_bool = false; //Déclaration et initialisation de la variable booléenne game_connexion_bool à false
bool win_bool = false; //Déclaration et initialisation de la variable booléenne win_bool à false

void setup () {
  // Initialisation des servomoteurs
  servo1.attach(PIN_SERVO_1); //Attachement du servo1 à la broche PIN_SERVO_1
  servo2.attach(PIN_SERVO_2); //Attachement du servo2 à la broche PIN_SERVO_2

  // Initialisation du recepteur IR
  Serial.begin(9600); //Initialisation de la communication série avec un débit de 9600 bauds
  IrReceiver.begin(PIN_SENSOR_IR); //Initialisation de l'objet IrReceiver avec la broche PIN_SENSOR_IR
  IrReceiver.resume(); //Reprise de la réception des signaux infrarouges
  
  // Initiallisation de l'emetteur IR
  IrSender.begin(PIN_LED_IR); //Initialisation de l'émetteur IR avec la broche PIN_LED_IR

  // Initialisation des pins bouton
  pinMode(PIN_BUTTON_RST, INPUT); //Définition de la broche PIN_BUTTON_RST en entrée
  pinMode(PIN_BUTTON_TIR, INPUT); //Définition de la broche PIN_BUTTON_TIR en entrée

  // Initialisation des pins sorties
  pinMode(VIBRATEUR_PIN, OUTPUT); //Définition de la broche VIBRATEUR_PIN en sortie

  // Initialisation de l'écran
  LCD.init(); //Initialisation de l'afficheur LCD
  LCD.backlight(); //Allumage du rétroéclairage de l'écran

  //Tutorial 
  Serial.print("Début pattern_lcd");

  LCD.clear(); //Effacement de l'écran
  LCD.setCursor(3, 0); //Positionnement du curseur à la colonne 3, ligne 0
  LCD.print("BIENVENUE A");

  LCD.setCursor(1, 1);
  LCD.print("BORD DU JUGAKI");

  LCD.display();
  delay(2000);

  LCD.clear();
  delay(20);

  LCD.setCursor(4, 0);
  LCD.print("VOUS AVEZ: ");

  LCD.setCursor(2, 1);
  LCD.print("tirs infinis");

  LCD.display();
  delay(2000);

  LCD.clear();
  delay(20);

  LCD.setCursor(0, 0);
  LCD.print("Rechargement: 3s ");

  LCD.display();
  delay(2000);

  LCD.clear();
  delay(20);

  LCD.setCursor(0, 0);
  LCD.print("Duree de partie:");

  LCD.setCursor(5, 1);
  LCD.print("3 min");

  LCD.display();
  delay(2000);

  LCD.clear();
  delay(20);
  LCD.setCursor(2, 0);
  LCD.print("BONNE CHANCE");

  LCD.setCursor(5, 1);
  LCD.print("^^");

  delay(2000);
  LCD.clear();
  LCD.setCursor(1, 0);
  LCD.print("VISE TON ENNEMI");

  LCD.display();
  digitalWrite(VIBRATEUR_PIN, HIGH);
  delay(250);
  digitalWrite(VIBRATEUR_PIN, LOW);
  delay(250);
  digitalWrite(VIBRATEUR_PIN, HIGH);
  delay(250);
  digitalWrite(VIBRATEUR_PIN, LOW);
  delay(250);
  digitalWrite(VIBRATEUR_PIN, HIGH);
  delay(250);
  digitalWrite(VIBRATEUR_PIN, LOW);

  delay(1000);
  LCD.clear();
  
  // gestion synchronisation timer
  while (game_connexion_bool != true) {
    if (IrReceiver.decode()) {
      Serial.println("Synchro trouvée");
      IrReceiver.printIRResultShort(&Serial);
      LCD.setCursor(2, 0);
      LCD.print("Connexion");
      LCD.setCursor(2, 1);
      LCD.print("etablie");
      LCD.display();
      game_start_time = millis() / 1000;
      game_connexion_bool = true;
    } else {
      Serial.println("Recherche connexion");
      LCD.setCursor(2, 0);
      LCD.print("Recherche");
      LCD.setCursor(2, 1);
      LCD.print("connexion");
      LCD.display();
    }
    delay(10);
    LCD.clear();
  }
}


void loop() {
  // Gestion servomoteurs
  int x = analogRead(A2); // Lecture de la valeur analogique de A2 et stockage dans la variable x
  Serial.println(x); // Affichage de la valeur de x sur le moniteur série

  int y = analogRead(A3); // Lecture de la valeur analogique de A3 et stockage dans la variable y
  Serial.println(y); // Affichage de la valeur de y sur le moniteur série

  int angle1 = map(x, 0, 1023, 40, 130); // Conversion de la valeur analogique x en angle dans la plage 40-130
  int angle2 = map(y, 0, 1023, 0, 50); // Conversion de la valeur analogique y en angle dans la plage 0-50

  angle1 = constrain(angle1, 40, 130); // Limitation de l'angle1 dans la plage autorisée (40-130)
  angle2 = constrain(angle2, 0, 50); // Limitation de l'angle2 dans la plage autorisée (0-50)

  servo1.write(angle1); // Déplacement du servo1 à l'angle1 spécifié
  servo2.write(angle2); // Déplacement du servo2 à l'angle2 spécifié

  // Gestion de l'écran
  LCD.clear(); // Effacement de l'écran LCD
  LCD.setCursor(1, 0); // Positionnement du curseur à la colonne 1, ligne 0
  LCD.print("Temps: ");
  LCD.setCursor(7, 0); // Positionnement du curseur à la colonne 7, ligne 0
  LCD.print(game_elapsed_time);
  LCD.display(); // Affichage du contenu de l'écran

  // Gestion receveur IR
  if (IrReceiver.decode()) {
    if (!game_bool) {
      Serial.println("Received something...");
      IrReceiver.printIRResultShort(&Serial); // Affichage d'un résumé des données reçues
      Serial.println("Début timer");
      game_bool = true;
      game_start_time = millis();
      IrReceiver.resume(); // Important, permet de recevoir le prochain signal IR
    }
  }


// Calcul du temps écoulé depuis le début de la partie
game_elapsed_time = (millis() / 1000) - game_start_time;

IrReceiver.resume();

while (game_elapsed_time > game_time) {
  game_connexion_bool = false;
  //game_bool = false;
  //results_bool = true;

  // Gestion des résultats
  //while (true) {
  //Serial.println("Debut results");

  LCD.clear();
  LCD.setCursor(3, 0);
  LCD.print("FIN DE PARTIE:");
  LCD.display();

  while (i < 2) {
    digitalWrite(VIBRATEUR_PIN, HIGH);
    delay(1000);
    digitalWrite(VIBRATEUR_PIN, LOW);
    i = i + 1;
  }
  i = 0;
  
  while (i < 300) {
    if (IrReceiver.decode()) {
      win_bool = true;
      delay(10);
      i = i + 1;
    }
  }

  if (win_bool) {
    while (true) {
      Serial.println("Received something...");
      IrReceiver.printIRResultShort(&Serial); // Affichage d'un résumé des données reçues
      LCD.setCursor(0, 1);
      LCD.print("TU ES VAINQUEUR");
      IrReceiver.resume(); // Important, permet de recevoir le prochain signal IR
      delay(100);
      LCD.clear();
    }
  } else if (!win_bool) {
    LCD.setCursor(0, 1);
    LCD.print("TU ES PERDANT");
    IrReceiver.resume(); // Important, permet de recevoir le prochain signal IR
    delay(100);
    LCD.clear();
  }
}

delay(10);
}void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}

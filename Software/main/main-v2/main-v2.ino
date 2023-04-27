//imports libs//
#include <Servo.h>
//#include <PCM.h>
#include <IRremote.h> // >v3.0.0
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

//setup
Servo servo1;
Servo servo2;
#define PIN_SENSOR_IR 2
#define PIN_SEND 3000000000000
#define PIN_LED_IR 3
#define PIN_SERVO_1 12
#define PIN_SERVO_2 13
#define PIN_BUTTON_TIR 11
#define PIN_BUTTON_RST 4
#define VIBRATEUR_PIN 9 
#define HP_PIN 10
#define IN1 7 //rouge sans scotch
#define IN2 8 //noir sans scotch
#define IN3 6 //jaune
#define IN4 5 //vert
#define joyX1 A0
#define joyY1 A1
#define joyX2 A2
#define joyX3 A3
#define HorizontalPotPin A4
#define VerticalPotPin A5
int x =10; // Temps d'attente
LiquidCrystal_I2C LCD(0x3E,16,2); // définit le type d'écran lcd 16 x 2

//gestion tir => ne sert à rien 
int munitions_nb = 10;
int tir_start_time;
int tir_elapsed_time;


//gestion rechargement munitions (quand munitions == 0)
bool munitionsoff_bool;
int munitionsoff_time = 10000;
int munitionsoff_start_time;
int munitionsoff_elapsed_time;
bool pattern_vibration1 ; //Vibration longue pour le rechargement

//gestion rearmement (entre chaque tir)
bool rearmement_bool;
int rearmement_time = 3000;
int rearmement_start_time;
int rearmement_elapsed_time;
bool pattern_vibration2 ; //Vibration courte pour le rearmement

// gestion vies
int vies_nb = 3;
bool recuperation_bool;
int recuperation_time = 5000;
int recuperation_start_time;
int recuperation_elapsed_time;
bool gameover_bool;
bool pattern_vibration3; //Vibration 3 coup récupération

//Tutorial

bool tutorial_bool = true;

//functions

void setup () {
  // Initialisation des servomoteurs
  servo1.attach(PIN_SERVO_1); // broche 9 pour servo1
  servo2.attach(PIN_SERVO_2); // broche 10 pour servo2

  // Initialisation du recepteur IR
  Serial.begin(9600); //initialize serial connection to print on the Serial Monitor of the Arduino IDE
  IrReceiver.begin(PIN_SENSOR_IR); // Initializes the IR receiver object

  // Initiallisation de l'emetteur IR
  IrSender.begin(PIN_LED_IR); // Initializes IR sender

  // Initialisation des pins moteur
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // Initialisation des pins bouton

  pinMode(PIN_BUTTON_RST, INPUT);
  pinMode(PIN_BUTTON_TIR, INPUT);

  // Initialisation des pins sorties

  pinMode(VIBRATEUR_PIN, OUTPUT);

  // Initialisation de l'écran

  LCD.init(); // initialisation de l'afficheur
  LCD.backlight();

}



void loop() {
  
  //calcul timer rearmement
  if (rearmement_bool) {
    pattern_vibration2 = true;
    rearmement_elapsed_time = millis() - rearmement_start_time;
    if (rearmement_elapsed_time>= rearmement_time){
      rearmement_bool = false;
      }
    }
  
  //calcul timer recuperation
  if (recuperation_bool) {
    pattern_vibration3 = true;
    recuperation_elapsed_time = millis() - recuperation_start_time;
    if (recuperation_elapsed_time>= recuperation_time){
      recuperation_bool = false;
      }
    }
    
  //calcul timer rechargement
  if (munitionsoff_bool) {
    pattern_vibration1 = true;
    munitionsoff_elapsed_time = millis() - munitionsoff_start_time;
    if (munitionsoff_elapsed_time>= recuperation_time){
      munitionsoff_bool = false;
      }
    }


pattern_servo();
pattern_lcd();
led_IR();
move_servos();
move_motors();
screen();
reset_button();
sensor_IR();
vibration();


}


//FUNCTIONS

void pattern_servo() {
  if (tutorial_bool) {
  int count = 0;
  // Mettre les servomoteurs à leur angle initial
  servo1.write(90);
  delay(100);
  servo1.write(180);
  servo2.write(20);

  // Attendre 2 secondes avant de commencer le pattern
  delay(20*x);

  while (true) {
    if (count < 10) { // continuer à faire bouger les servos
      // Définition des angles aléatoires pour chaque servomoteur
      int angle1 = servo1.read() + random(-10, 10); // angle aléatoire entre -5 et 5 degrés
      int angle2 = servo2.read() + random(-10, 10); // angle aléatoire entre -5 et 5 degrés

      // Limiter les angles dans les plages acceptées par les servomoteurs
      angle1 = constrain(angle1, 50, 130);
      angle2 = constrain(angle2, 0, 50);

      // Faire bouger les servomoteurs à leurs angles respectifs
      servo1.write(angle1);
      servo2.write(angle2);

      // Attendre 500ms avant le prochain mouvement
      delay(250);
      count++;
    } else { // stopper les servos et arrêter la boucle
      // Mettre les servomoteurs à leur angle initial
      servo1.write(90);
      servo2.write(20);

      while (true) {
      servo1.write(90);
      servo2.write(20);
      }
    }
  }
  
}
}

void pattern_lcd() {
  if (tutorial_bool) {
  Serial.println("début");

  LCD.setCursor(3, 0);
  LCD.print("BIENVENUE A");

  LCD.setCursor(1, 1);
  LCD.print("BORD DU JUGAKI");

  LCD.display();
  delay(1000);

  LCD.clear();
  delay(20);

  LCD.setCursor(4, 0);
  LCD.print("VOUS AVEZ: ");

  LCD.setCursor(0, 1);
  LCD.print("3 vies / 10 tirs");

  delay(20);
  LCD.display();
  delay(1000);

  LCD.clear();
  delay(20);

  LCD.setCursor(0, 0);
  LCD.print("Rechargement: 5s ");

  LCD.setCursor(0, 1);
  LCD.print("Penalite: 3s");

  LCD.display();
  delay(1000);

  LCD.clear();
  delay(20); 
  LCD.setCursor(2, 0);
  LCD.print("BONNE CHANCE");

  LCD.setCursor(5, 1);
  LCD.print("^^");

  LCD.display();
  delay(1000);

  LCD.clear();
  tutorial_bool = false;
  }
}



void led_IR() {
 if ((digitalRead(PIN_BUTTON_TIR) == HIGH) && (!munitionsoff_bool || !gameover_bool || rearmement_bool)){
  munitions_nb = munitions_nb - 1;
  IrSender.sendNEC(0x0102, 0x34, true, 0); // the address 0x0102 with the command 0x34 is sent 
  tir_start_time = millis();
  } 
}  





void move_servos () {
  if (!gameover_bool || !munitionsoff_bool){
  // Lire les valeurs du joystick
  int x = analogRead(A0);
  int y = analogRead(A1);

  // Convertir les valeurs analogiques en angles
  int angle1 = map(x, 0, 1023, 40, 130);
  int angle2 = map(y, 0, 1023, 0, 50);

  // Limiter les angles dans les plages acceptées par les servomoteurs
  angle1 = constrain(angle1, 40, 130);
  angle2 = constrain(angle2, 0, 50);

  // Bouger les servomoteurs à leurs angles respectifs
  servo1.write(angle1);
  servo2.write(angle2);
}}




void move_motors () {
  if (!gameover_bool || !recuperation_bool){
  // lecture de la position du joystick
  int x = analogRead(joyX1);
  int y = analogRead(joyY1);

  // calcul de la vitesse et du sens des moteurs
  int speed = map(x, 0, 1023, -255, 255);
  int dir = map(y, 0, 1023, -20, 20);

  //Serial.print("speed: ");
  //Serial.println(speed);
  Serial.print("dir: ");
  Serial.println(dir);

  // contrôle des moteurs en fonction de la vitesse et du sens
  if (dir < -5) { // droite
    analogWrite(IN1, 0);
    analogWrite(IN2, 0);
    analogWrite(IN3, speed);
    analogWrite(IN4, 0);
  } 
  else if (dir > 5) { // gauche
    analogWrite(IN1, speed);
    analogWrite(IN2, 0);
    analogWrite(IN3, 0);
    analogWrite(IN4, 0);
  } 
   else if (5 > dir > -5) { // dir neutre
    if (speed > 5) {
    analogWrite(IN1, speed);
    analogWrite(IN2, 0);
    analogWrite(IN3, speed);
    analogWrite(IN4, 0);
  } else if (speed < 5) {
    analogWrite(IN1, 0);
    analogWrite(IN2, -speed);
    analogWrite(IN3, 0);
    analogWrite(IN4, -speed);
    }
  } else { // arrêter
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
  }
}}



void screen () {
  LCD.setCursor(1, 0);
  LCD.print("Vies: ");
  LCD.setCursor(7, 0);
  LCD.print(vies_nb);
  LCD.setCursor(8, 0);
  LCD.print("Tirs :");
  LCD.setCursor(15, 0);
  LCD.print(munitions_nb);

if (gameover_bool) { 
  LCD.setCursor(1, 1);
  LCD.print("TU AS PERDU");
}
else if (rearmement_bool) {
  LCD.setCursor(1, 1);
  LCD.print("TIR > REARMEMENT");
}
else if (munitionsoff_bool) {
  LCD.setCursor(1, 0);
  LCD.print("TIR: O");
  LCD.setCursor(1, 1);
  LCD.print("> RECHARGE");
}
else if (recuperation_bool) {
  LCD.setCursor(1, 0);
  LCD.print("TU ES TOUCHé");
  LCD.setCursor(1, 1);
  LCD.print("> RECUPéRATION");
}
  LCD.display();
}



void reset_button () {
  if (digitalRead(PIN_BUTTON_RST) == HIGH) {
  asm volatile("jmp 0x00");
  }
}



void sensor_IR() {
  if (IrReceiver.decode()) {
    //Serial.println("Received something...");    
    IrReceiver.printIRResultShort(&Serial); // Prints a summary of the received data
    //Serial.println();
    if (!recuperation_bool) {
    vies_nb = vies_nb - 1;
    recuperation_start_time = millis();
    IrReceiver.resume(); // Important, enables to receive the next IR signal
  }  
  }
}


void vibration() {
  
  unsigned long temps_debut_vibration = 0; // Temps de début de la vibration en millisecondes
  bool vibration_en_cours = false; // Indique si une vibration est en cours
    // Vérification de la variable globale pattern_vibration1
  if (pattern_vibration1) {
    // Début de la vibration longue
    digitalWrite(VIBRATEUR_PIN, HIGH);
    temps_debut_vibration = millis();
    vibration_en_cours = true;
    pattern_vibration1 = false; // Remise à false de la variable globale
  }
  // Vérification de la variable globale pattern_vibration2
  else if (pattern_vibration2) {
    // Début de la vibration courte
    digitalWrite(VIBRATEUR_PIN, HIGH);
    temps_debut_vibration = millis();
    vibration_en_cours = true;
    pattern_vibration2 = false; // Remise à false de la variable globale
  }
  // Vérification de la variable globale pattern_vibration3
  else if (pattern_vibration3) {
    // Début des trois vibrations courtes de suite
    digitalWrite(VIBRATEUR_PIN, HIGH);
    temps_debut_vibration = millis();
    vibration_en_cours = true;
    pattern_vibration3 = false; // Remise à false de la variable globale
  }
  // Arrêt de la vibration si elle est en cours depuis plus de 500 millisecondes
  else if (vibration_en_cours && millis() - temps_debut_vibration > 500) {
    digitalWrite(VIBRATEUR_PIN, LOW);
    vibration_en_cours = false;
  }

  // Si une vibration est en cours, vérifier si elle doit être arrêtée
  if (vibration_en_cours) {
    if (pattern_vibration2) {
      // Arrêt de la vibration courte après 50 millisecondes
      if (millis() - temps_debut_vibration > 50) {
        digitalWrite(VIBRATEUR_PIN, LOW);
        delay(50); // Durée de la pause entre deux vibrations courtes en millisecondes
        digitalWrite(VIBRATEUR_PIN, HIGH);
        delay(50); // Durée de la vibration courte en millisecondes
        temps_debut_vibration = millis();
      }
    }
    else if (pattern_vibration3) {
      // Arrêt de la troisième vibration courte après 50 millisecondes
      if (millis() - temps_debut_vibration > 50) {
        digitalWrite(VIBRATEUR_PIN, LOW);
        delay(50); // Durée de la pause entre deux vibrations courtes en millisecondes
        digitalWrite(VIBRATEUR_PIN, HIGH);
        temps_debut_vibration = millis();
      }
    }
  }  
}

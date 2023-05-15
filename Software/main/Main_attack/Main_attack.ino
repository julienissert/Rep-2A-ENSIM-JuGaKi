
//imports libs//
#include <PWMServo.h>
#include <PCM.h>
#include <IRremote.h> // >v3.0.0
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

//setup
PWMServo servo1;
PWMServo servo2;
#define PIN_SENSOR_IR 2
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
LiquidCrystal_I2C LCD(0x27,16,2); // définit le type d'écran lcd 16 x 2

//gestion tir => ne sert à rien 
int munitions_nb = 10;
int tir_start_time;
int tir_elapsed_time;
int laser_time = 4000;


//gestion rechargement munitions (quand munitions == 0) => ne sert à rien
bool munitionsoff_bool = false;
int munitionsoff_time = 10000; //temps 10000
int munitionsoff_start_time;
int munitionsoff_elapsed_time;
bool pattern_vibration1 ; //Vibration longue pour le rechargement

//gestion rearmement (entre chaque tir) = ne sert à rien
bool rearmement_bool = false;
int rearmement_time = 3000; //temps 3000
int rearmement_start_time;
int rearmement_elapsed_time;
bool pattern_vibration2 ; //Vibration courte pour le rearmement

// gestion vies => ne sert à rien
int vies_nb = 3;
bool recuperation_bool = false;
int recuperation_time = 50000; //temps 5000
int recuperation_start_time;
int recuperation_elapsed_time;
bool gameover_bool;
bool pattern_vibration3; //Vibration 3 coup récupération

// gestion temps partie
bool game_bool = false;
int game_time = 180000; 
int game_start_time;
int game_elapsed_time;

// gestion resultats
bool results_bool = false;

//Tutorial

bool tutorial_bool = true;
bool tutorial2_bool = false;

//Son

int son=0;

const unsigned char defaite[] PROGMEM = {
129};

const unsigned char debut[] PROGMEM = {
126, 126, 128, 129, 129, 129, 127, 126, 125, 126, 128, 129, 129, 128, 127, 126, 126, 127, 128, 129, 129, 128, 127, 127, 127, 127, 127, 127, 128, 128, 128, 127, 126, 126, 128, 129, 129, 128, 127, 127, 127, 127, 128, 128, 127, 127, 127, 127, 127, 128, 128, 128, 127, 127, 128, 128, 128, 127, 127, 127, 128, 129, 128, 128, 127, 127, 127, 127, 128, 128, 128, 128, 128, 127, 127, 127, 128, 128, 128, 128, 127, 127, 127, 127, 128, 128, 128, 128, 128, 128, 127, 128, 128, 127, 127, 128, 127, 127, 127, 128, 128, 128, 128, 128, 128, 127, 127, 126, 127, 128, 129, 128, 127, 127, 127, 127, 127, 128, 128, 128, 128, 127, 127, 127, 127, 128, 129, 128, 127, 127, 127, 128, 128, 128, 127, 127, 127, 128, 128, 128, 128, 127, 127, 127, 128, 129, 128, 127, 126, 126, 127, 128, 130, 129, 127, 126, 126, 127, 128, 129, 128, 127, 128, 127, 126, 126, 127, 128, 129, 130, 129, 127, 125, 125, 126, 129, 131, 130, 128, 126, 124, 125, 127, 130, 131, 130, 128, 125, 125, 126, 128, 129, 129, 128, 127, 126, 126, 127, 129, 130, 129, 127, 126, 126, 127, 129, 129, 129, 128, 126, 125, 126, 127, 129, 129, 129, 128, 126, 126, 127, 127, 128, 128, 128, 128, 127, 127, 127, 128, 128, 127, 127, 127, 127, 128, 128, 128, 127, 127, 127, 128, 128, 128, 128, 128, 127, 126, 125, 127, 129, 130, 130, 127, 125, 125, 126, 128, 129, 129, 128, 128, 127, 125, 125, 127, 130, 131, 130, 127, 125, 124, 126, 128, 129, 129, 128, 127, 126, 127, 127, 128, 128, 128, 127, 127, 128, 128, 128, 127, 126, 127, 128, 130, 129, 127, 126, 126, 127, 128, 127, 127, 126, 127, 128, 129, 129, 129, 127, 127, 126, 126, 126, 128, 130, 130, 128, 126, 125, 125, 127, 128, 129, 130, 129, 127, 125, 124, 124, 127, 130, 130, 129, 129, 127, 126, 126, 126, 127, 129, 130, 129, 128, 127, 126, 127, 127, 128, 129, 128, 127, 127, 126, 126, 127, 128, 128, 127, 128, 128, 128, 128, 127, 126, 127, 128, 128, 127, 126, 127, 129, 129, 128, 127, 127, 127, 127, 128, 128, 129, 129, 127, 125, 124, 126, 128, 131, 131, 129, 127, 125, 125, 126, 128, 129, 131, 130, 127, 124, 123, 126, 131, 132, 130, 127, 124, 124, 126, 129, 130, 129, 128, 128, 127, 127, 127, 127, 128, 127, 127, 127, 128, 129, 130, 128, 126, 126, 128, 128, 128, 127, 127, 128, 129, 128, 126, 125, 125, 128, 131, 131, 129, 127, 127, 126, 126, 126, 127, 129, 131, 130, 127, 125, 125, 127, 129, 129, 129, 130, 129, 127, 125, 125, 127, 128, 128, 128, 128, 128, 129, 128, 128, 127, 126, 127, 129, 130, 128, 127, 126, 128, 127, 126, 127, 127, 128, 129, 129, 129, 128, 127, 125, 125, 127, 130, 131, 129, 126, 126, 127, 127, 128, 128, 128, 128, 128, 127, 128, 128, 128, 127, 128, 127, 126, 126, 128, 128, 128, 127, 126, 127, 128, 128, 128, 129, 128, 127, 126, 126, 128, 129, 128, 125, 124, 125, 128, 132, 133, 130, 125, 123, 125, 128, 128, 128, 127, 126, 128, 129, 128, 126, 126, 128, 128, 128, 129, 130, 129, 126, 124, 124, 126, 129, 130, 130, 128, 126, 126, 127, 128, 126, 125, 126, 130, 130, 127, 125, 126, 130, 129, 126, 123, 126, 129, 131, 130, 128, 124, 124, 126, 129, 130, 129, 129, 126, 126, 125, 125, 127, 128, 127, 130, 131, 129, 127, 126, 125, 125, 128, 131, 130, 126, 124, 126, 127, 130, 131, 128, 125, 124, 125, 130, 132, 132, 127, 123, 122, 125, 129, 130, 128, 126, 129, 131, 132, 128, 125, 123, 124, 125, 126, 126, 129, 131, 133, 130, 127, 126, 125, 126, 124, 126, 129, 131, 130, 127, 124, 127, 127, 130, 131, 130, 124, 125, 126, 127, 129, 127, 129, 128, 128, 159, 167, 103, 41, 22, 75, 180, 255, 253, 166, 55, 0, 11, 107, 215, 255, 225, 122, 25, 0, 42, 143, 236, 255, 202, 93, 7, 0, 69, 177, 252, 246, 168, 64, 2, 20, 105, 206, 255, 223, 127, 29, 0, 43, 145, 236, 255, 194, 90, 11, 5, 78, 181, 249, 241, 161, 61, 2, 22, 109, 207, 253, 221, 128, 34, 0, 46, 140, 227, 251, 195, 96, 19, 11, 76, 176, 245, 238, 163, 65, 7, 25, 108, 204, 250, 220, 131, 39, 5, 46, 137, 221, 247, 196, 102, 24, 12, 74, 171, 240, 237, 164, 69, 12, 28, 106, 197, 245, 218, 134, 46, 10, 47, 135, 217, 243, 196, 106, 30, 16, 74, 164, 231, 233, 168, 79, 21, 30, 101, 188, 235, 216, 139, 55, 18, 49, 129, 209, 238, 198, 113, 38, 20, 69, 157, 225, 231, 172, 85, 24, 29, 96, 184, 235, 218, 143, 58, 18, 47, 126, 206, 237, 198, 116, 41, 22, 70, 155, 222, 229, 172, 87, 28, 31, 96, 179, 230, 216, 146, 63, 23, 49, 125, 203, 233, 197, 117, 44, 26, 73, 153, 217, 225, 170, 89, 34, 36, 96, 176, 224, 211, 145, 67, 29, 53, 124, 197, 227, 194, 120, 51, 31, 72, 148, 211, 220, 171, 94, 39, 39, 96, 172, 219, 208, 146, 72, 34, 56, 122, 191, 221, 193, 124, 58, 37, 73, 144, 204, 215, 170, 98, 45, 43, 95, 168, 214, 205, 147, 76, 38, 57, 119, 188, 219, 193, 127, 61, 38, 72, 141, 201, 215, 172, 102, 47, 42, 90, 161, 211, 207, 153, 82, 41, 55, 115, 184, 217, 194, 128, 63, 38, 71, 140, 200, 214, 173, 103, 48, 42, 90, 161, 210, 206, 152, 83, 42, 57, 116, 183, 214, 191, 128, 65, 42, 74, 139, 197, 210, 171, 104, 52, 47, 92, 159, 205, 202, 152, 86, 47, 59, 115, 179, 211, 191, 131, 70, 45, 73, 136, 193, 209, 172, 107, 55, 47, 90, 156, 203, 202, 153, 88, 48, 59, 114, 178, 209, 189, 130, 70, 47, 75, 137, 192, 207, 170, 106, 56, 51, 93, 157, 201, 198, 150, 88, 51, 64, 117, 177, 206, 185, 128, 71, 49, 77, 138, 192, 205, 169, 106, 57, 52, 93, 156, 200, 198, 152, 91, 54, 64, 115, 175, 204, 185, 130, 74, 52, 79, 137, 189, 201, 166, 107, 60, 56, 96, 156, 197, 194, 149, 91, 57, 68, 117, 173, 200, 181, 129, 76, 57, 82, 137, 185, 197, 164, 108, 64, 61, 99, 154, 193, 190, 147, 93, 61, 72, 118, 170, 195, 177, 128, 79, 61, 86, 137, 181, 191, 160, 109, 70, 68, 104, 154, 187, 182, 143, 96, 68, 79, 120, 166, 187, 171, 129, 86, 70, 90, 133, 172, 182, 158, 114, 79, 74, 103, 147, 179, 179, 146, 101, 73, 80, 118, 161, 184, 170, 130, 89, 72, 91, 132, 170, 180, 156, 114, 80, 76, 106, 148, 177, 176, 144, 101, 75, 83, 119, 161, 181, 167, 128, 89, 75, 94, 134, 169, 178, 155, 114, 81, 78, 106, 147, 175, 173, 144, 104, 80, 86, 120, 158, 176, 163, 128, 93, 80, 97, 133, 165, 173, 152, 116, 86, 82, 108, 146, 172, 170, 141, 103, 80, 88, 122, 159, 175, 162, 127, 92, 80, 96, 130, 162, 173, 154, 116, 88, 86, 109, 142, 166, 168, 144, 106, 84, 94, 124, 149, 166, 161, 136, 122, 85, 58, 141, 217, 130, 60, 166, 199, 39, 23, 214, 230, 58, 63, 215, 165, 7, 86, 249, 165, 22, 118, 234, 108, 5, 151, 246, 99, 28, 179, 216, 53, 36, 205, 211, 49, 65, 221, 173, 17, 90, 242, 153, 16, 120, 237, 116, 15, 151, 236, 93, 29, 180, 219, 57, 40, 205, 205, 44, 66, 222, 174, 24, 94, 235, 147, 19, 122, 236, 118, 21, 151, 231, 89, 30, 182, 218, 58, 44, 207, 202, 42, 68, 221, 173, 28, 95, 232, 146, 20, 125, 237, 116, 19, 154, 232, 88, 29, 182, 219, 61, 44, 205, 202, 43, 67, 220, 174, 28, 96, 232, 146, 21, 123, 235, 120, 23, 150, 228, 90, 34, 179, 212, 64, 52, 200, 195, 50, 73, 212, 169, 36, 100, 222, 142, 32, 125, 222, 120, 38, 146, 214, 96, 44, 171, 205, 73, 58, 191, 188, 57, 79, 204, 163, 45, 105, 214, 136, 39, 131, 217, 116, 43, 149, 207, 95, 52, 170, 196, 74, 67, 191, 181, 60, 85, 200, 158, 51, 108, 206, 134, 48, 132, 207, 114, 52, 151, 198, 93, 61, 171, 187, 74, 75, 189, 172, 61, 93, 197, 150, 54, 116, 202, 127, 52, 139, 203, 108, 56, 156, 194, 89, 66, 175, 181, 72, 82, 189, 166, 62, 98, 197, 146, 55, 119, 200, 125, 55, 139, 197, 107, 60, 157, 191, 87, 68, 177, 180, 70, 84, 191, 163, 61, 100, 196, 144, 56, 121, 199, 123, 57, 143, 196, 104, 63, 159, 186, 86, 74, 177, 175, 71, 87, 189, 160, 62, 103, 194, 142, 59, 123, 196, 122, 60, 143, 193, 104, 65, 157, 184, 90, 77, 172, 171, 76, 91, 184, 157, 68, 104, 188, 141, 66, 123, 190, 123, 66, 141, 187, 105, 71, 157, 179, 90, 81, 172, 168, 77, 94, 183, 154, 68, 108, 187, 138, 68, 126, 188, 120, 68, 144, 185, 104, 74, 158, 176, 91, 85, 171, 164, 79, 98, 180, 150, 72, 111, 182, 136, 73, 129, 183, 119, 74, 144, 179, 104, 79, 157, 170, 92, 91, 169, 159, 82, 103, 177, 145, 75, 115, 179, 132, 77, 132, 178, 116, 79, 146, 174, 103, 84, 156, 165, 94, 96, 166, 154, 85, 107, 173, 141, 80, 120, 176, 128, 80, 135, 174, 114, 83, 148, 170, 101, 88, 158, 162, 93, 100, 166, 150, 86, 111, 172, 138, 82, 123, 173, 126, 83, 136, 171, 113, 87, 149, 166, 101, 92, 158, 158, 94, 104, 165, 145, 88, 116, 169, 133, 85, 128, 169, 122, 88, 140, 165, 110, 93, 150, 159, 101, 100, 158, 152, 96, 109, 162, 141, 91, 119, 165, 131, 89, 128, 166, 123, 91, 138, 162, 111, 95, 149, 157, 102, 101, 158, 150, 95, 110, 163, 139, 90, 121, 166, 129, 89, 131, 166, 120, 92, 141, 160, 109, 97, 150, 154, 101, 104, 158, 147, 96, 113, 161, 137, 92, 123, 163, 126, 91, 133, 164, 119, 95, 142, 158, 108, 100, 151, 152, 101, 107, 157, 144, 96, 116, 160, 134, 94, 125, 161, 125, 94, 135, 160, 117, 98, 142, 154, 108, 103, 150, 149, 101, 110, 156, 142, 98, 118, 158, 132, 96, 127, 159, 123, 96, 136, 157, 115, 100, 144, 152, 107, 106, 151, 145, 101, 113, 155, 139, 99, 120, 156, 130, 99, 129, 156, 122, 100, 137, 154, 115, 103, 143, 149, 108, 109, 150, 143, 103, 115, 153, 136, 100, 122, 154, 128, 100, 131, 154, 120, 102, 138, 152, 114, 105, 143, 146, 109, 112, 148, 140, 105, 118, 152, 134, 102, 124, 152, 127, 103, 132, 152, 120, 104, 138, 149, 114, 107, 143, 144, 109, 113, 148, 
};


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






//FUNCTIONS

void results() {
  if (results_bool) {
  Serial.println("Debut results");

  LCD.clear();
 LCD.setCursor(3, 0);
 LCD.print("FIN DE PARTIE:");

  if (IrReceiver.decode()) {
    Serial.println("Received something...");    
    IrReceiver.printIRResultShort(&Serial); // Prints a summary of the received data
    LCD.setCursor(0,1);
    LCD.print("TU ES VAINQUEUR");
    IrReceiver.resume(); // Important, enables to receive the next IR signal
    delay(5000);
    LCD.clear();
  } 
  else {
       LCD.setCursor(0,1);
    LCD.print("TU ES PERDANT");
    IrReceiver.resume(); // Important, enables to receive the next IR signal
    delay(5000);
    LCD.clear();
    }
   
  }

results_bool = false;
tutorial_bool =true;
}


void pattern_servo() {
  if (tutorial2_bool) {
  Serial.println("Début pattern_servo");
  int count = 0;
  // Mettre les servomoteurs à leur angle initial
  servo1.write(90);
  delay(100);
  servo1.write(180);
  servo2.write(20);

  // Attendre 2 secondes avant de commencer le pattern
  //delay(20*x);

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
    tutorial2_bool = false;
  }
  
}
}

void pattern_lcd() {
  if (tutorial_bool) {
  Serial.print("Début pattern_lcd");


  LCD.setCursor(3, 0);
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

  LCD.display();
  delay(1000);

  LCD.clear();

  startPlayback(debut,sizeof(debut));
  
  tutorial_bool = false;
  tutorial2_bool = true;
  }
}



void led_IR() {
 if ((digitalRead(PIN_BUTTON_TIR) == HIGH) ){
  Serial.println("led_IR");
  munitions_nb = munitions_nb - 1;
  IrSender.sendNEC(0x0102, 0x34, true, 0); // the address 0x0102 with the command 0x34 is sent 
  tir_start_time = millis();
  } 
}  



void move_servos () {
  if (!gameover_bool || !munitionsoff_bool){
  Serial.println("move_servos");
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
  Serial.println("move_motors");
  // lecture de la position du joystick
  int x = analogRead(joyX1);
  int y = analogRead(joyY1);

  // calcul de la vitesse et du sens des moteurs
  int speed = map(x, 0, 1023, -255, 255);
  int dir = map(y, 0, 1023, -20, 20);

  //Serial.print("speed: ");
  //Serial.println(speed);
  //Serial.print("dir: ");
  //Serial.println(dir);

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
  LCD.print("Temps: ");
  LCD.setCursor(7, 0);
  LCD.print(game_elapsed_time);


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
  Serial.println("reset_button");
  asm volatile("jmp 0x00");
  }
}



void sensor_IR() {
  if (!game_bool) {
  if (IrReceiver.decode()) {
    Serial.println("Received something...");    
    IrReceiver.printIRResultShort(&Serial); // Prints a summary of the received data
    Serial.println("Début timer");
    game_start_time = millis();
    IrReceiver.resume(); // Important, enables to receive the next IR signal
   
  }
}
}

void vibration() {
  
  unsigned long temps_debut_vibration = 0; // Temps de début de la vibration en millisecondes
  bool vibration_en_cours = false; // Indique si une vibration est en cours
    // Vérification de la variable globale pattern_vibration1
  if (pattern_vibration1) {
    Serial.println("vibration_1");
    // Début de la vibration longue
    digitalWrite(VIBRATEUR_PIN, HIGH);
    temps_debut_vibration = millis();
    vibration_en_cours = true;
    pattern_vibration1 = false; // Remise à false de la variable globale
  }
  // Vérification de la variable globale pattern_vibration2
  else if (pattern_vibration2) {
    Serial.println("vibration_2");
    // Début de la vibration courte
    digitalWrite(VIBRATEUR_PIN, HIGH);
    temps_debut_vibration = millis();
    vibration_en_cours = true;
    pattern_vibration2 = false; // Remise à false de la variable globale
  }
  // Vérification de la variable globale pattern_vibration3
  else if (pattern_vibration3) {
    Serial.println("vibration_3");
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

void loop() {
  
  //calcul timer rearmement
  if (rearmement_bool) {
    //pattern_vibration3 = true;
    recuperation_elapsed_time = millis() - recuperation_start_time;
    if (recuperation_elapsed_time>= recuperation_time){
      recuperation_bool = false;
      }
    }
    
  //calcul timer rechargement
  if (munitionsoff_bool) {
    //pattern_vibration1 = true;
    munitionsoff_elapsed_time = millis() - munitionsoff_start_time;
    if (munitionsoff_elapsed_time>= recuperation_time){
      munitionsoff_bool = false;
      }
    }

  //calcul timer partie
  if (game_bool) {
    game_elapsed_time = millis() - game_start_time;
    if (game_elapsed_time>= game_time){
      game_bool = false;
      results_bool = true;
      }
    }

Serial.println("in");
pattern_servo();
pattern_lcd();
//led_IR();
move_servos();
move_motors();
screen();
reset_button();
sensor_IR();
//vibration();
results();
Serial.println("out");

Serial.println(munitionsoff_bool);
Serial.println(rearmement_bool);
Serial.println(recuperation_bool);
Serial.println(gameover_bool);
Serial.println(pattern_vibration1);
Serial.println(pattern_vibration2);
Serial.println(pattern_vibration3);
delay(500);

}

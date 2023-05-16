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
/*/#define IN1 7 //rouge sans scotch
#define IN2 8 //noir sans scotch
#define IN3 6 //jaune
#define IN4 5 //vert/*/
#define joyX1 A0
#define joyY1 A1
#define joyX2 A2
#define joyX3 A3
#define HorizontalPotPin A4
#define VerticalPotPin A5
int x =10; // Temps d'attente
LiquidCrystal_I2C LCD(0x27,16,2); // définit le type d'écran lcd 16 x 2


// gestion temps partie
bool game_bool = false;
int game_time = 180000; 
int game_start_time;
int game_elapsed_time;

// gestion resultats
bool results_bool = false;



void setup () {
  // Initialisation des servomoteurs
  servo1.attach(PIN_SERVO_1); // broche 9 pour servo1
  servo2.attach(PIN_SERVO_2); // broche 10 pour servo2

  // Initialisation du recepteur IR
  Serial.begin(9600); //initialize serial connection to print on the Serial Monitor of the Arduino IDE
  IrReceiver.begin(PIN_SENSOR_IR); // Initializes the IR receiver object

  // Initiallisation de l'emetteur IR
  IrSender.begin(PIN_LED_IR); // Initializes IR sender


  // Initialisation des pins bouton

  pinMode(PIN_BUTTON_RST, INPUT);
  pinMode(PIN_BUTTON_TIR, INPUT);

  // Initialisation des pins sorties

  pinMode(VIBRATEUR_PIN, OUTPUT);

  // Initialisation de l'écran

  LCD.init(); // initialisation de l'afficheur
  LCD.backlight();

//Tutorial 

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
}
void loop() {

// Gestion servomoteurs

 Serial.println("move_servos");
  // Lire les valeurs du joystick
  int x = analogRead(A0);
  int y = analogRead(A1);

  // Convertir les valeurs analogiques en angles
  int angle1 = map(x, 0, 1023, 40, 130);
  int angle2 = map(y, 0, 1023, 0, 50);
  Serial.println(angle1);
  Serial.println(angle2);

  // Limiter les angles dans les plages acceptées par les servomoteurs
  angle1 = constrain(angle1, 40, 130);
  angle2 = constrain(angle2, 0, 50);

  // Bouger les servomoteurs à leurs angles respectifs
  servo1.write(angle1);
  servo2.write(angle2);

// Gestion de l'écran

  LCD.clear();
  LCD.setCursor(1, 0);
  LCD.print("Temps: ");
  LCD.setCursor(7, 0);
  LCD.print(game_elapsed_time);
  LCD.display();
}

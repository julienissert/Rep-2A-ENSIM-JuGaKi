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
#define PIN_SENSOR_LUM A3
#define PIN_LED_IR 3
#define PIN_SERVO_1 12
#define PIN_SERVO_2 7
#define PIN_BUTTON_TIR 11
#define PIN_BUTTON_RST 4
#define VIBRATEUR_PIN 9 
#define HP_PIN 10
#define joyX1 A0
#define joyY1 A1
#define joyX2 A2
#define joyY2 A3
#define HorizontalPotPin A4
#define VerticalPotPin A5
int x =10; // Temps d'attente
LiquidCrystal_I2C LCD(0x27,16,2); // définit le type d'écran lcd 16 x 2
int i;

// gestion temps partie
bool game_bool = false;
int game_time = 180; // en sec
int game_start_time;
int game_elapsed_time;

// gestion resultats
bool results_bool = false;
bool game_connexion_bool = true;
int lum_nb;
int lum_delta = 900;
int bcl_em = 0;

// gestion vies

int vies_nb = 3;



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

  LCD.clear();
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
  LCD.print(" 3 vies");

  LCD.display();
  delay(2000);

  LCD.clear();
  delay(20);

  LCD.setCursor(0, 0);
  LCD.print("Protection: 3s ");

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


 
  // gestion synchonisation timer
  //game_connexion_bool = true; // PHASE DE TEST
  while(!game_connexion_bool){
  lum_nb = analogRead(PIN_SENSOR_LUM);
  if(lum_nb >= lum_delta){
  Serial.println("Synchro trouvée"); 
 
  while (bcl_em < 10 ) {
  IrSender.sendNEC(0x0102, 0x34, true, 0);
  bcl_em = bcl_em+1;
  delay(10);
  } 
  
  LCD.setCursor(2, 0);
  LCD.print("Connexion");
  LCD.setCursor(2, 1);
  LCD.print("etablie");
  LCD.display();
  game_start_time = millis()/1000;
  game_connexion_bool = true;
  }
  
  else {
  Serial.println("Recherche connexion");
  LCD.setCursor(2, 0);
  LCD.print("Recherche");
  LCD.setCursor(2, 1);
  LCD.print("connexion");
  LCD.display();
  }
  
  delay(100);
  LCD.clear();
  }
 
}
void loop() {


// Gestion de l'écran

  LCD.clear();
  LCD.setCursor(1, 0);
  LCD.print("Temps: ");
  LCD.setCursor(7, 0);
  LCD.print(game_elapsed_time);
  LCD.display();
  Serial.println(game_elapsed_time);

    //calcul timer partie
    game_elapsed_time = (millis()/1000) - game_start_time;


  // gestion cible

  while (game_elapsed_time < game_time) {
  lum_nb = analogRead(PIN_SENSOR_LUM);
  if(lum_nb >= lum_delta){
  vies_nb = vies_nb-1;
  delay(3000);
  }
  }
  

  //gestion resultats 
   
  while (game_elapsed_time > game_time){




 LCD.clear();
 LCD.setCursor(3, 0);
 LCD.print("FIN DE PARTIE:");
 LCD.display();
 while (i < 2) {
  digitalWrite(VIBRATEUR_PIN, HIGH);
  delay(1000);
  digitalWrite(VIBRATEUR_PIN, LOW);
  i=i+1;
 }


  if (vies_nb >=1) {
    while(true) {
      
    LCD.setCursor(0,1);
    LCD.print("TU ES VAINQUEUR");
    IrSender.sendNEC(0x0102, 0x34, true, 0);
    delay(10);
    }
  } 
  else {
    while(true) {
      
    LCD.setCursor(0,1);
    LCD.print("TU ES VAINQUEUR");
    IrSender.sendNEC(0x0102, 0x34, true, 0);
    delay(10);
    }
 
}
  
 delay(10);
}}

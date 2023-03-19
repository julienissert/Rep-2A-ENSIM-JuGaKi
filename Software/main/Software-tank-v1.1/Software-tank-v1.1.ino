#include <Servo.h> 
#include <Wire.h>
#include <LiquidCrystal_I2C.h>


LiquidCrystal_I2C LCD(0x3E,16,2); // définit le type d'écran lcd 16 x 2

int ServoHorizontalPin = 3; 
int ServoVerticalPin = 4; 
int HorizontalPotPin = A0; 
int VerticalPotPin = A1; 
int ServoH_Min = 0; 
int ServoH_Max = 180; 
int ServoV_Min = 0; 
int ServoV_Max = 180;

Servo HorizontalServo; 
Servo VerticalServo;

int HorizontalPotValue; 
int HorizontalServoPosition; 
int VerticalPotValue; 
int VerticalServoPosition;

//angles maximum minimum des servos

int maxS1 = 130;
int minS1 = 50;
int maxS2 = 40;
int minS2 = 0;

//variables générales consommables combat

int vies;
int tirs;
bool recharge;
bool touche; //Donnée par la fonction capteur


//variables générales état

bool laser;
bool infra;
int son;
int VibPattern;


void setup() 
{
HorizontalServo.attach(ServoHorizontalPin); 
VerticalServo.attach(ServoVerticalPin); 
LCD.init(); // initialisation de l'afficheur
LCD.backlight();



}

void loop() 
{

HorizontalPotValue = analogRead(HorizontalPotPin); 
VerticalPotValue = analogRead(VerticalPotPin); 
HorizontalServoPosition = map(HorizontalPotValue, 0, 1023, ServoH_Min , ServoH_Max); 
VerticalServoPosition = map(VerticalPotValue, 0, 1023, ServoH_Min , ServoH_Max); 
HorizontalServo.write(HorizontalServoPosition); 
VerticalServo.write(VerticalServoPosition); 
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
delay(20);

}

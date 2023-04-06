// définition des pins du pont en H L298N
int IN1 = 7;
int IN2 = 8;
int IN3 = 6;
int IN4 = 5;

// définition des pins du joystick
int joyX = A0;
int joyY = A1;

void setup() {
  // définition des pins en sortie
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
}

void loop() {

  // lecture de la position du joystick
  int x = analogRead(joyX);
  int y = analogRead(joyY);
  
  // calcul de la vitesse et du sens des moteurs
  int speed = map(x, 0, 1023, -25, 25);
  int dir = map(y, 0, 1023, 255, 255);
   if (speed>=0) { // avancer
   
   if (dir<0){ 
   
  // faire tourner les moteurs en avant à vitesse moyenne
  digitalWrite(IN1, speed*(1/(dir+1)));
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, speed);
 }

   if (dir>=0){ 
   
  // faire tourner les moteurs en avant à vitesse moyenne
  digitalWrite(IN1, speed);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, speed*(dir+1));
 }
 
 }
if (speed<0) { // avancer
      
   
  // faire tourner les moteurs en avant à vitesse moyenne
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, speed);
  digitalWrite(IN3, speed);
  digitalWrite(IN4, LOW);
 }
//if (speed==0) { // avancer
      
   
  // faire tourner les moteurs en avant à vitesse moyenne
  //digitalWrite(IN1, LOW);
  //digitalWrite(IN2, LOW);
  //digitalWrite(IN3, LOW);
  //digitalWrite(IN4, LOW);
 //}
 
  delay(10); // attendre
}

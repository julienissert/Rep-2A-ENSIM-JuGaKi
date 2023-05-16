// définition des pins du pont en H L298N
int IN1 = 7; //rouge sans scotch R
int IN2 = 8; //noir sans scotch R
int IN3 = 6; //jaune L
int IN4 = 5; //vert L

// définition des pins du joystick
int joyX = A0;
int joyY = A1;

void setup() {
  // définition des pins en sortie
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // lecture de la position du joystick
  int x = analogRead(joyX);
  int y = analogRead(joyY);

//0=>1024

  // calcul de la vitesse et du sens des moteurs
  //int speed = map(x, 0, 1023, -255, 255);
  //int dir = map(y, 0, 1023, -20, 20);
  //int 200 = 100;
 
  //Serial.print("speed: ");
  //Serial.println(speed);
  //Serial.print("dir: ");
  //Serial.println(dir);

  // contrôle des moteurs en fonction de la vitesse et du sens
  if (y > 730) { // gauche
    analogWrite(IN1, 200);
    analogWrite(IN2, 0);
    analogWrite(IN3, 0);
    analogWrite(IN4, 0);
  }
  else if ( y < 320) { // droite
    analogWrite(IN1, 0);
    analogWrite(IN2, 0);
    analogWrite(IN3, 200);
    analogWrite(IN4, 0);
  }
   else if (x > 830) { // avant
    analogWrite(IN1, 200);
    analogWrite(IN2, 0);
    analogWrite(IN3, 200);
    analogWrite(IN4, 0);
   }
   else if (x < 320) { //arriere
    analogWrite(IN1, 0);
    analogWrite(IN2, 200);
    analogWrite(IN3, 0);
    analogWrite(IN4, 200);
    }
   else { // arrêter
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
  }

  // attendre un court moment avant la prochaine lecture du joystick
  Serial.println("x :");
  Serial.println(x);
  Serial.println("y :");
  Serial.println(y);
 
  delay(10);
}

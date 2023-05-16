// définition des broches du pont en H L298N
int IN1 = 7; //rouge sans scotch
int IN2 = 8; //noir sans scotch
int IN3 = 6; //jaune
int IN4 = 5; //vert

// définition des broches du joystick
int joyX = A0;
int joyY = A1;

void setup() {
  // définition des broches en sortie
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

  // calcul de la vitesse et de la direction des moteurs
  int speed = map(x, 0, 1023, -255, 255);
  int dir = map(y, 0, 1023, -20, 20);

  //Serial.print("speed: ");
  //Serial.println(speed);
  Serial.print("dir: ");
  Serial.println(dir);

  // contrôle des moteurs en fonction de la vitesse et de la direction
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
   else if (dir > -5 && dir < 5) { // direction neutre
    if (speed > 5) {
      analogWrite(IN1, speed);
      analogWrite(IN2, 0);
      analogWrite(IN3, speed);
      analogWrite(IN4, 0);
    } else if (speed < -5) {
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

  // attendre un court moment avant la prochaine lecture du joystick
  delay(10);
}

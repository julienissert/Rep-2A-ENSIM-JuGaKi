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
  Serial.begin(9600);
}

void loop() {
  // lecture de la position du joystick
  int x = analogRead(joyX);
  int y = analogRead(joyY);
  
  // calcul de la vitesse et du sens des moteurs
  int speed = map(x, 0, 1023, 0, 255);
  int dir = map(y, 0, 1023, 0, 255);

  Serial.print("speed: ");
  Serial.println(speed);

  // phase neutre
  if (4 > speed > -4) { // neutre
    analogWrite(IN1, LOW);
    analogWrite(IN2, LOW);
    analogWrite(IN3, LOW);
    analogWrite(IN4, LOW);
  } else if ( speed < -5) { // reculer
    analogWrite(IN1, 0);
    analogWrite(IN2, (-speed));
    analogWrite(IN3, 0);
    analogWrite(IN4, -speed);
  } else if (speed > 5) { // avancer
    digitalWrite(IN1, speed);
    digitalWrite(IN2, 0);
    digitalWrite(IN3, speed);
    digitalWrite(IN4, 0);
  }

  // attendre un court moment avant la prochaine lecture du joystick
  delay(10);
}

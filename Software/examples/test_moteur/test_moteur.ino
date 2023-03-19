// Pin de contrôle des moteurs
int motorPin1 = 5;
int motorPin2 = 6;

// Valeurs des angles de repos des moteurs
int angle1 = 0;
int angle2 = 0;

void setup() {
  // Initialisation des pins de contrôle des moteurs
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);

  // Initialisation de la communication série
  Serial.begin(9600);
}

void loop() {
  // Lecture des valeurs du joystick
  int x = analogRead(A0);
  int y = analogRead(A1);

  // Conversion des valeurs analogiques en valeurs de vitesse
  int speed = map(x, 0, 1023, 0, 255);
  int slowdown = map(y, 0, 1023, 0, 255);

  // Calcul de la vitesse de chaque moteur
  int motorSpeed1 = speed;
  int motorSpeed2 = speed;

  // Ralentissement du moteur en fonction de la valeur y du joystick
  if (slowdown > 0) {
    motorSpeed1 = map(slowdown, 0, 255, 0, speed);
    motorSpeed2 = map(slowdown, 0, 255, speed, 0);
  }

  // Contrôle des moteurs en fonction des vitesses calculées
  analogWrite(motorPin1, motorSpeed1);
  analogWrite(motorPin2, motorSpeed2);

  // Affichage des valeurs dans le moniteur série
  Serial.print("x: ");
  Serial.print(x);
  Serial.print(", y: ");
  Serial.print(y);
  Serial.print(", speed: ");
  Serial.print(speed);
  Serial.print(", slowdown: ");
  Serial.print(slowdown);
  Serial.print(", motorSpeed1: ");
  Serial.print(motorSpeed1);
  Serial.print(", motorSpeed2: ");
  Serial.println(motorSpeed2);

  // Attente de 10 ms avant la prochaine lecture des valeurs du joystick
  delay(10);
}

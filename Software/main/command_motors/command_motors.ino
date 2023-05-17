// Définition des pins du pont en H L298N
const int IN1 = 7; // Rouge sans scotch R
const int IN2 = 8; // Noir sans scotch R
const int IN3 = 6; // Jaune L
const int IN4 = 5; // Vert L

// Définition des pins du joystick
const int joyX = A0;
const int joyY = A1;

void setup() {
  // Définition des pins en sortie
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  
  Serial.begin(9600); // Initialisation de la communication série
}

void loop() {
  // Lecture de la position du joystick
  int x = analogRead(joyX);
  int y = analogRead(joyY);
  
  // Calcul de la vitesse et du sens des moteurs
  // int speed = map(x, 0, 1023, -255, 255);
  // int dir = map(y, 0, 1023, -20, 20);
  // int 200 = 100;

  // Affichage des valeurs sur le moniteur série
  // Serial.print("speed: ");
  // Serial.println(speed);
  // Serial.print("dir: ");
  // Serial.println(dir);

  // Contrôle des moteurs en fonction de la vitesse et du sens
  if (y > 730) { // Gauche
    analogWrite(IN1, 200);
    analogWrite(IN2, 0);
    analogWrite(IN3, 0);
    analogWrite(IN4, 0);
  }
  else if (y < 320) { // Droite
    analogWrite(IN1, 0);
    analogWrite(IN2, 0);
    analogWrite(IN3, 200);
    analogWrite(IN4, 0);
  }
  else if (x > 830) { // Avant
    analogWrite(IN1, 200);
    analogWrite(IN2, 0);
    analogWrite(IN3, 200);
    analogWrite(IN4, 0);
  }
  else if (x < 320) { // Arrière
    analogWrite(IN1, 0);
    analogWrite(IN2, 200);
    analogWrite(IN3, 0);
    analogWrite(IN4, 200);
  }
  else { // Arrêt
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
  }

  // Attente d'un court moment avant la prochaine lecture du joystick
  Serial.println("x :");
  Serial.println(x);
  Serial.println("y :");
  Serial.println(y);

  delay(10);
}

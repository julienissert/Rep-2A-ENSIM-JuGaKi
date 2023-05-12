#include <Servo.h>

Servo servo1;
Servo servo2;

void setup() {
  // Initialisation des servomoteurs
  servo1.attach(12); // broche 9 pour servo1
  servo2.attach(13); // broche 10 pour servo2

  // Mettre les servomoteurs à leur position initiale
  servo1.write(90);
  servo2.write(20);
}

void loop() {
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

  // Attendre 10ms avant la prochaine lecture des valeurs du joystick
  delay(10);
}

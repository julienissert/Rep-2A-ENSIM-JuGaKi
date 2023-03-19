#include <Servo.h>

Servo servo1;
Servo servo2;

void setup() {
  // Initialisation des servomoteurs
  servo1.attach(9); // broche 9 pour servo1
  servo2.attach(10); // broche 10 pour servo2

  // Mettre les servomoteurs à leur angle initial
  servo1.write(90);
  servo2.write(0);
  
  // Attendre 2 secondes avant de commencer le pattern
  delay(2000);

  // Boucle de démarrage avec mouvement des servos
  for (int i = 0; i < 100; i++) {
    // Définition des angles aléatoires pour chaque servomoteur
    int angle1 = servo1.read() + random(-10, 10); // angle aléatoire entre -5 et 5 degrés
    int angle2 = servo2.read() + random(-10, 10); // angle aléatoire entre -5 et 5 degrés
    
    // Limiter les angles dans les plages acceptées par les servomoteurs
    angle1 = constrain(angle1, 50, 130);
    angle2 = constrain(angle2, 0, 50);
    
    // Faire bouger les servomoteurs à leurs angles respectifs
    servo1.write(angle1);
    servo2.write(angle2);

    // Attendre 500ms avant le prochain mouvement
    delay(500);
  }

  // Mettre les servomoteurs à leur angle initial
  servo1.write(90);
  servo2.write(0);
  
  // Arrêter les servomoteurs
  //servo1.detach();
  //servo2.detach();
}

void loop() {
  // Le programme ne fera rien dans la boucle loop
  // car nous avons seulement besoin de faire bouger les servomoteurs
  // pendant la boucle setup.
}

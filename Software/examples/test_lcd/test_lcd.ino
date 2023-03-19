#include <Servo.h>

Servo servo1;
Servo servo2;
int count = 0;

void pattern_servo() {
  // Initialisation des servomoteurs
  servo1.attach(9); // broche 9 pour servo1
  servo2.attach(10); // broche 10 pour servo2

  // Mettre les servomoteurs à leur angle initial
  servo1.write(90);
  delay(100);
  servo1.write(180);
  servo2.write(20);

  // Attendre 2 secondes avant de commencer le pattern
  delay(2000);

  // La boucle loop ne fait rien de spécial, sauf qu'elle peut être utilisée pour
  // effectuer d'autres tâches pendant que les servomoteurs bougent.
  while (true) {
    if (count < 40) { // continuer à faire bouger les servos
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
      count++;
    } else { // stopper les servos et arrêter la boucle
      // Mettre les servomoteurs à leur angle initial
      servo1.write(90);
      servo2.write(20);

      // Arrêter les servomoteurs
      servo1.detach();
      servo2.detach();
      while (true) {
        // Boucle infinie pour éviter de sortir de la fonction loop()
      }
    }
  }
}

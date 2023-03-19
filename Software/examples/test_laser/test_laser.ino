bool laser_actif = true;


void activer_laser() {
  //bool laser_actif = true;
  //if (laser_actif) {
    digitalWrite(3, HIGH); // allumer la sortie 13
  //} else {
    //digitalWrite(3, LOW); // éteindre la sortie 13
  //}
}

// appeler comme ça
void setup() {}

void loop() {
  // Faire quelque chose d'autre dans la boucle principale
  // ...

  // Appeler la fonction activer_laser() de manière asynchrone
    digitalWrite(8, HIGH);

  // Continuer à faire quelque chose d'autre dans la boucle principale
  // ...
}

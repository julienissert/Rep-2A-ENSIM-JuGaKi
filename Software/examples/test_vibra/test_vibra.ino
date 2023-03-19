const int VIBRATEUR_PIN = 9; // Définition du pin sur lequel est branché le vibreur
unsigned long temps_debut_vibration = 0; // Temps de début de la vibration en millisecondes
bool vibration_en_cours = false; // Indique si une vibration est en cours

void vibration_asynchrone() {
  // Vérification de la variable globale pattern_vibration1
  if (pattern_vibration1) {
    // Début de la vibration longue
    digitalWrite(VIBRATEUR_PIN, HIGH);
    temps_debut_vibration = millis();
    vibration_en_cours = true;
    pattern_vibration1 = false; // Remise à false de la variable globale
  }
  // Vérification de la variable globale pattern_vibration2
  else if (pattern_vibration2) {
    // Début de la vibration courte
    digitalWrite(VIBRATEUR_PIN, HIGH);
    temps_debut_vibration = millis();
    vibration_en_cours = true;
    pattern_vibration2 = false; // Remise à false de la variable globale
  }
  // Vérification de la variable globale pattern_vibration3
  else if (pattern_vibration3) {
    // Début des trois vibrations courtes de suite
    digitalWrite(VIBRATEUR_PIN, HIGH);
    temps_debut_vibration = millis();
    vibration_en_cours = true;
    pattern_vibration3 = false; // Remise à false de la variable globale
  }
  // Arrêt de la vibration si elle est en cours depuis plus de 500 millisecondes
  else if (vibration_en_cours && millis() - temps_debut_vibration > 500) {
    digitalWrite(VIBRATEUR_PIN, LOW);
    vibration_en_cours = false;
  }

  // Si une vibration est en cours, vérifier si elle doit être arrêtée
  if (vibration_en_cours) {
    if (pattern_vibration2) {
      // Arrêt de la vibration courte après 50 millisecondes
      if (millis() - temps_debut_vibration > 50) {
        digitalWrite(VIBRATEUR_PIN, LOW);
        delay(50); // Durée de la pause entre deux vibrations courtes en millisecondes
        digitalWrite(VIBRATEUR_PIN, HIGH);
        delay(50); // Durée de la vibration courte en millisecondes
        temps_debut_vibration = millis();
      }
    }
    else if (pattern_vibration3) {
      // Arrêt de la troisième vibration courte après 50 millisecondes
      if (millis() - temps_debut_vibration > 50) {
        digitalWrite(VIBRATEUR_PIN, LOW);
        delay(50); // Durée de la pause entre deux vibrations courtes en millisecondes
        digitalWrite(VIBRATEUR_PIN, HIGH);
        temps_debut_vibration = millis();
      }
    }
  }
}

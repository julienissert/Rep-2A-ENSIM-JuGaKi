#include <IRremote.h> // Inclure la bibliothèque pour utiliser le capteur infrarouge

IRrecv irrecv(2); // Initialiser le capteur infrarouge sur la broche 2

void capteur_IR() {
  static unsigned long lastPrintTime = 0; // Temps de la dernière écriture dans le moniteur série
  static bool lastValue = false; // Dernière valeur du capteur infrarouge

  decode_results results;
  if (irrecv.decode(&results)) {
    bool value = results.value != 0;
    if (value != lastValue && millis() - lastPrintTime > 2000) {
      Serial.print("capteur infrarouge: ");
      Serial.println(value ? "touché" : "non touché");
      lastValue = value;
      lastPrintTime = millis();
    }
    irrecv.resume(); // Recevoir le prochain signal
  }
  else {
    // Si le capteur infrarouge ne détecte pas de signal, écrire "none"
    if (millis() - lastPrintTime > 500) {
      Serial.println("capteur infrarouge: none");
      lastPrintTime = millis();
    }
  }
}

void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn(); // Démarrer la réception des signaux infrarouges
}

unsigned long lastCheck = 0; // Temps de la dernière vérification du capteur infrarouge

void loop() {
  // Vérifier le capteur infrarouge toutes les 100 ms
  if (millis() - lastCheck > 100) {
    lastCheck = millis();
    capteur_IR();
  }
  
  // Autre code à exécuter dans la boucle principale
}

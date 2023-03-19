int IR_LED_PIN = 13; // Définir la broche pour la diode infrarouge

void setup() {
  pinMode(IR_LED_PIN, OUTPUT); // Configurer la broche en sortie
}

void loop() {
  digitalWrite(IR_LED_PIN, HIGH); // Allumer la diode infrarouge
  //delay(1000); // Attendre une seconde
  //digitalWrite(IR_LED_PIN, LOW); // Éteindre la diode infrarouge
  //delay(1000); // Attendre une seconde
}

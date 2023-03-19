const int BUTTON_PIN = 2; // numéro de la pin du bouton
const int IR_LED_PIN = 13; // numéro de la pin de la diode infrarouge

void allumer_diode_infrarouge() {
  digitalWrite(IR_LED_PIN, HIGH); // allume la diode infrarouge
  delay(1000); // attend 2 secondes
  digitalWrite(IR_LED_PIN, LOW); // éteint la diode infrarouge
}

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP); // configure la pin du bouton en entrée avec résistance de tirage vers le haut
  pinMode(IR_LED_PIN, OUTPUT); // configure la pin de la diode infrarouge en sortie
}

void loop() {
  if (digitalRead(BUTTON_PIN) == LOW) { // si le bouton est appuyé
    allumer_diode_infrarouge(); // allume la diode infrarouge pendant 2 secondes
  }
}

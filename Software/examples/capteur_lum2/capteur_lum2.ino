// Pin utilisé pour le capteur de luminosité
const int LDR_Pin = A0;

void setup() {
  // Configuration du port série à une vitesse de 9600 bauds
  Serial.begin(9600);
}

void loop() {
  // Lecture de la valeur de luminosité du capteur
  int luminosite = analogRead(LDR_Pin);
  
  // Affichage de la valeur de luminosité dans le moniteur série
  Serial.println(luminosite);
  
  // Attente de 100 millisecondes pour éviter une surcharge du port série
  delay(100);
}

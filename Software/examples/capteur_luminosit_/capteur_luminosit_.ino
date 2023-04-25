// Pin utilisé pour le capteur de luminosité
const int LDR_Pin = A0;

// Seuil de variation de luminosité
const int seuilLuminosite = 100;

void setup() {
  // Configuration du port série à une vitesse de 9600 bauds
  Serial.begin(9600);
}

void loop() {
  // Lecture de la valeur de luminosité du capteur
  int luminosite = analogRead(LDR_Pin);
  
  // Si la variation de luminosité est importante
  if (abs(luminosite - seuilLuminosite) > 50) {
    // Affichage de "touché" dans le moniteur série
    Serial.println("touché");
  }
  
  // Attente de 100 millisecondes pour éviter une surcharge du port série
  delay(100);
}

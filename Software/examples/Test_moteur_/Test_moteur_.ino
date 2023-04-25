#include <Arduino.h>

const int motor1Pin1 = 5;
const int motor1Pin2 = 6;
const int motor2Pin1 = 10;
const int motor2Pin2 = 11;
const int joystickPinX = A0;
const int joystickPinY = A1;

void setup() {
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);
  Serial.begin(9600);
}

void mouvement_tank() {
  int x = analogRead(joystickPinX);
  int y = analogRead(joystickPinY);

  int speedLeft = 0;
  int speedRight = 0;

  if (x > 530) {
    speedLeft = map(x, 530, 1023, 0, 255);
    speedRight = map(x, 530, 1023, 0, 255);
  } else if (x < 490) {
    speedLeft = map(x, 0, 490, -255, 0);
    speedRight = map(x, 0, 490, -255, 0);
  }

  if (y < 490) {
    int delta = map(y, 0, 490, 0, 255);
    speedLeft -= delta;
  } else if (y > 530) {
    int delta = map(y, 530, 1023, 0, 255);
    speedRight -= delta;
  }

  speedLeft = constrain(speedLeft, -255, 255);
  speedRight = constrain(speedRight, -255, 255);

  if (speedLeft < 0) {
    digitalWrite(motor1Pin1, LOW);
    analogWrite(motor1Pin2, abs(speedLeft));
  } else {
    digitalWrite(motor1Pin2, LOW);
    analogWrite(motor1Pin1, speedLeft);
  }

  if (speedRight < 0) {
    digitalWrite(motor2Pin1, LOW);
    analogWrite(motor2Pin2, abs(speedRight));
  } else {
    digitalWrite(motor2Pin2, LOW);
    analogWrite(motor2Pin1, speedRight);
  }

  Serial.print("Speed Left: ");
  Serial.print(speedLeft);
  Serial.print(", Speed Right: ");
  Serial.println(speedRight);
}

void loop() {
  mouvement_tank();
  delay(50);
}

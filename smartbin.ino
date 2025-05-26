#include <Servo.h>

// Ultrasonic hand
const int trig1 = 6;
const int echo1 = 7;

// Ultrasonic garbage
const int trig2 = 4;
const int echo2 = 5;

// Buzzer
const int buzzerPin = 8;

// Servo motor
const int servoPin = 9;

// LEDs
const int ledGreen = 10;
const int ledYellow = 11;
const int ledRed = 12;

Servo lid;
bool isLidOpen = false;
unsigned long lidOpenStart = 0;
const unsigned long lidOpenDuration = 5000; // 5 seconds

void setup() {
  pinMode(trig1, OUTPUT);
  pinMode(echo1, INPUT);

  pinMode(trig2, OUTPUT);
  pinMode(echo2, INPUT);

  pinMode(buzzerPin, OUTPUT);
  pinMode(ledGreen, OUTPUT);
  pinMode(ledYellow, OUTPUT);
  pinMode(ledRed, OUTPUT);

  lid.attach(servoPin);
  lid.write(0); // lid closed

  Serial.begin(9600);
}

void loop() {
  // Auto-close lid after 5 seconds
  if (isLidOpen && (millis() - lidOpenStart >= lidOpenDuration)) {
    lid.write(0);
    digitalWrite(buzzerPin, LOW);
    isLidOpen = false;
  }

  // Check for hand
  if (!isLidOpen) {
    float handDistance = readDistance(trig1, echo1);
    Serial.print("Hand distance: ");
    Serial.println(handDistance);

    if (handDistance < 10) {
      digitalWrite(buzzerPin, HIGH);
      lid.write(75); // open lid
      lidOpenStart = millis();
      isLidOpen = true;

      turnOffLEDs();
    }
  }

  // Check garbage level
  if (!isLidOpen) {
    float binDistance = readDistance(trig2, echo2);
    Serial.print("Bin distance: ");
    Serial.println(binDistance);

    if (binDistance > 16) {
      turnOnOnlyLED(ledGreen);
    } else if (binDistance > 8 && binDistance <= 16) {
      turnOnOnlyLED(ledYellow);
    } else {
      turnOnOnlyLED(ledRed);
    }
  }

  delay(200);
}

// Reads distance in cm using an ultrasonic sensor
float readDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  float distance = duration * 0.034 / 2;
  return distance;
}

void turnOnOnlyLED(int ledPin) {
  digitalWrite(ledGreen, LOW);
  digitalWrite(ledYellow, LOW);
  digitalWrite(ledRed, LOW);
  digitalWrite(ledPin, HIGH);
}

void turnOffLEDs() {
  digitalWrite(ledGreen, LOW);
  digitalWrite(ledYellow, LOW);
  digitalWrite(ledRed, LOW);
}

#include <Servo.h>

// Primul senzor (detecție mână)
const int trig1 = 6;
const int echo1 = 7;

// Al doilea senzor (nivel umplere)
const int trig2 = 4;
const int echo2 = 5;

// Buzzer și servo
const int buzzerPin = 8;
const int servoPin = 9;

// LED-uri
const int ledVerde = 10;
const int ledGalben = 11;
const int ledRosu = 12;

Servo capac;
bool capacDeschis = false;
unsigned long deschidereStart = 0;
const unsigned long durataDeschidere = 5000; // 5 secunde

void setup() {
  // Senzor 1
  pinMode(trig1, OUTPUT);
  pinMode(echo1, INPUT);

  // Senzor 2
  pinMode(trig2, OUTPUT);
  pinMode(echo2, INPUT);

  // Buzzer, LED-uri
  pinMode(buzzerPin, OUTPUT);
  pinMode(ledVerde, OUTPUT);
  pinMode(ledGalben, OUTPUT);
  pinMode(ledRosu, OUTPUT);

  // Servo
  capac.attach(servoPin);
  capac.write(0); // Închis

  Serial.begin(9600);
}

void loop() {
  // Verific dacă capacul trebuie închis
  if (capacDeschis && (millis() - deschidereStart >= durataDeschidere)) {
    capac.write(0);
    digitalWrite(buzzerPin, LOW);
    capacDeschis = false;
  }

  // Dacă capacul e închis → citim senzorul 1 (mână)
  if (!capacDeschis) {
    float distantaMana = masoaraDistanta(trig1, echo1);
    Serial.print("Distanta mana: ");
    Serial.println(distantaMana);

    if (distantaMana < 10) {
      digitalWrite(buzzerPin, HIGH);
      capac.write(90);
      deschidereStart = millis();
      capacDeschis = true;
    }
  }

  // Citim senzorul 2 (nivel umplere)
  float distantaGunoi = masoaraDistanta(trig2, echo2);
  Serial.print("Distanta gunoi: ");
  Serial.println(distantaGunoi);

  // Aprindem LED-ul potrivit
  if (distantaGunoi > 15) {
    aprindeDoarLED(ledVerde);
  } else if (distantaGunoi > 5 && distantaGunoi <= 15) {
    aprindeDoarLED(ledGalben);
  } else {
    aprindeDoarLED(ledRosu);
  }

  delay(200); // întârziere generală
}

// Funcție pentru citirea unei distanțe de la un senzor HC-SR04
float masoaraDistanta(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long durata = pulseIn(echoPin, HIGH);
  float distanta = durata * 0.034 / 2;
  return distanta;
}

// Funcție pentru a aprinde un singur LED și a le opri pe celelalte
void aprindeDoarLED(int ledPin) {
  digitalWrite(ledVerde, LOW);
  digitalWrite(ledGalben, LOW);
  digitalWrite(ledRosu, LOW);
  digitalWrite(ledPin, HIGH);
}

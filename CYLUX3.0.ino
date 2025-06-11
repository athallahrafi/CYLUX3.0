#include <Wire.h>
#include "Adafruit_TCS34725.h"

#define MDN 7
#define MDP 8
#define ENM 9
#define PSN 12
#define PSP 11
#define ENP 10
#define SW 2
#define LSR 4
#define LSY 5
#define LSG 6
#define LEDC A2
#define INTC A3

bool lastState = LOW;
bool triggerActive = false;
unsigned long startTime = 0;
const unsigned long runDuration = 120000;

Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_614MS, TCS34725_GAIN_1X);

void setup(void) {
  Serial.begin(9600);
  pinMode(SW, INPUT);
  pinMode(LSR, OUTPUT);
  pinMode(LSY, OUTPUT);
  pinMode(LSG, OUTPUT);
  pinMode(MDN, OUTPUT);
  pinMode(MDP, OUTPUT);
  pinMode(ENM, OUTPUT);
  pinMode(PSN, OUTPUT);
  pinMode(PSP, OUTPUT);
  pinMode(ENP, OUTPUT);
  pinMode(LEDC, OUTPUT);
  pinMode(INTC, OUTPUT);

  if (!tcs.begin()) {
    Serial.println("Sensor tidak ditemukan!");
    while (1);
  }

  digitalWrite(LSR, LOW);
  digitalWrite(LSY, LOW);
  digitalWrite(LSG, LOW);
  digitalWrite(LEDC, HIGH);
}

void loop(void) {
  bool currentState = digitalRead(SW);

  if (currentState == HIGH && lastState == LOW && !triggerActive) {
    triggerActive = true;
    delay(50);
    startTime = millis();

    digitalWrite(LSR, HIGH);
    digitalWrite(LSY, LOW);
    digitalWrite(LSG, LOW);
    delay(1000);

    digitalWrite(LSR, LOW);
    digitalWrite(LSY, HIGH);
    digitalWrite(LSG, LOW);
    delay(1000);

    digitalWrite(LSR, LOW);
    digitalWrite(LSY, LOW);
    digitalWrite(LSG, HIGH);

    readColor();
    PSR();
    MR();
  }
  if (triggerActive && millis() - startTime >= runDuration) {
    stopSystem();
    triggerActive = false;
  }

  lastState = currentState;
}

void readColor() {
  uint16_t r, g, b, c, colorTemp, lux;
  tcs.getRawData(&r, &g, &b, &c);
  colorTemp = tcs.calculateColorTemperature_dn40(r, g, b, c);
  lux = tcs.calculateLux(r, g, b);

  Serial.print("Color Temp: "); Serial.print(colorTemp); Serial.print(" K - ");
  Serial.print("Lux: "); Serial.print(lux); Serial.print(" - ");
  Serial.print("R: "); Serial.print(r); Serial.print(" ");
  Serial.print("G: "); Serial.print(g); Serial.print(" ");
  Serial.print("B: "); Serial.print(b); Serial.print(" ");
  Serial.print("C: "); Serial.println(c);
}

void MR() {
  digitalWrite(MDP, HIGH);
  digitalWrite(MDN, LOW);
  analogWrite(ENM, 150);
}

void MS() {
  analogWrite(ENM, 0);
}

void PSR() {
  digitalWrite(PSP, HIGH);
  digitalWrite(PSN, LOW);
  analogWrite(ENP, 150);
}

void PSS() {
  analogWrite(ENP, 0);
}

void stopSystem() {
  digitalWrite(LSR, HIGH);
  digitalWrite(LSY, LOW);
  digitalWrite(LSG, LOW);
  MS();
  PSS();
}
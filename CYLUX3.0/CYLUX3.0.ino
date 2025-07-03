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

int RED = -10;
int GREEN = -10;
int BLUE = -10;

// int rm = 0;
// int gm = 0;
// int bm = 0;
int rm = 6;
int gm = 14;
int bm = 11;
// int 30mR = 6;
// int 30mG = 14;
// int 30mB = 11;
int mR15 = 8;
int mG15 = 20;
int mB15 = 28;
int mR10 = 11;
int mG10 = 26;
int mB10 = 35;

bool lastState = LOW;
bool triggerActive = false;
unsigned long startTime = 0;
const unsigned long runDuration = 120000;
unsigned long lastRead = 0;
const int interval = 1000; // 1 detik

//Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_614MS, TCS34725_GAIN_1X);
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);


void setup(void) {
  Serial.begin(9600);
  delay(1000);
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

  // if (!tcs.begin()) {
  //   Serial.println("Sensor tidak ditemukan!");
  //   while (1);
  // }
  if (tcs.begin()) {
    Serial.println("Found sensor");
  } else {
    Serial.println("No TCS34725 found ... check your connections");
    // while (1);
  }

  digitalWrite(LSR, LOW);
  digitalWrite(LSY, LOW);
  digitalWrite(LSG, LOW);
  digitalWrite(LEDC, LOW);
}

void loop(void) {
  // bool currentState = digitalRead(SW);
  // // Serial.println(currentState);
  // // Serial.println("sistem standby");
  // if (currentState == HIGH && lastState == LOW && !triggerActive) {
  //   triggerActive = true;
  //   // Serial.println("sistem start");
  //   delay(50);
  //   startTime = millis();

  //   digitalWrite(LSR, HIGH);
  //   digitalWrite(LSY, LOW);
  //   digitalWrite(LSG, LOW);
  //   delay(1000);

  //   digitalWrite(LSR, LOW);
  //   digitalWrite(LSY, HIGH);
  //   digitalWrite(LSG, LOW);
  //   delay(1000);

  //   digitalWrite(LSR, LOW);
  //   digitalWrite(LSY, LOW);
  //   digitalWrite(LSG, HIGH);

  //   PSR();
  //   MR();
  // }

  // lastState = currentState;
  // stopSystem();
// <<<<<<< HEAD
  delay(1000);
  readColor();
  if(((rm!=RED))&&((gm!=GREEN))&&((bm!=BLUE))){
    PSR();
    MR();
    Serial.println("START SYSTEMS");
    Serial.print("R: ");
    Serial.print(RED);
    Serial.print("G: ");
    Serial.print(GREEN);
    Serial.print("B: ");
    Serial.print(BLUE);
    Serial.println(" ");
  }else if(((rm==RED)||(rm==RED+2)||(rm==RED-2))&&((gm==GREEN)||(gm==GREEN+2)||(gm==GREEN-2))&&((bm==BLUE)||(bm==BLUE+2)||(bm==BLUE-2))){
    stopSystem();
    Serial.println("STOP ALL SYSTEMS");
  }
  // }else if(RED!=rm&&GREEN!=gm&&BLUE!=bm){
  // }
  // if (millis() - startTime <= runDuration) {
    // PSR();
    // PSS();
  // }
  // delay(20000);
  //   triggerActive = false;
// =======
//   if (millis() - lastRead >= interval) {
//     lastRead = millis();
//     readColor();
//   }
  //   triggerActive = false;
  //delay(1000);
// >>>>>>> a84ef76ec554af3c3ce75407b9c27ca23c138a11
}

void readColor() {
  uint16_t r, g, b, c, colorTemp, lux;
  tcs.getRawData(&r, &g, &b, &c);
  colorTemp = tcs.calculateColorTemperature_dn40(r, g, b, c);
  lux = tcs.calculateLux(r, g, b);
  RED = r;
  GREEN = g;
  BLUE = b;
  // Serial.print("Color Temp: "); Serial.print(colorTemp); Serial.print(" K - ");
  // Serial.print("Lux: "); Serial.print(lux); Serial.print(" - ");
  // Serial.print("R: "); Serial.print(r); Serial.print(" ");
  // Serial.print("G: "); Serial.print(g); Serial.print(" ");
  // Serial.print("B: "); Serial.print(b); Serial.print(" ");
  // Serial.print("C: "); Serial.println(c);
}

void MR() {
  digitalWrite(MDP, HIGH);
  digitalWrite(MDN, LOW);
  analogWrite(ENM, 250);
}

void MS() {
  analogWrite(ENM, 0);
}

void PSR() {
  digitalWrite(PSP, HIGH);
  digitalWrite(PSN, LOW);
  analogWrite(ENP, 250);
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

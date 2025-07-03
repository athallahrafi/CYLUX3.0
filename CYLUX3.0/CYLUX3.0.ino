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

int RED = -1;
int GREEN = -1;
int BLUE = -1;

int RD5 = 23;  //9.5sec
int GD5 = 52;  //9.5sec
int BD5 = 61;  //9.5sec
int RD10 = 20; //19.0sec
int GD10 = 45; //19.0sec
int BD10 = 59; //19.0sec
int RD15 = 11;  //28.5sec
int GD15 = 26; //28.5sec
int BD15 = 36; //28.5sec
int RD20 = 7;  //38.0sec
int GD20 = 18;  //38.0sec
int BD20 = 27;  //38.0sec
int RD25 = 6;  //47.5sec
int GD25 = 14;  //47.5sec
int BD25 = 18;  //47.5sec
int RD30 = 5;  //57.0sec
int GD30 = 13; //57.0sec
int BD30 = 14; //57.0sec

int RDA = 0;
int GDA = 0;
int BDA = 0;

bool PASS = (RDA == RED) || (GDA == GREEN) || (BDA == BLUE);
bool OVR = (RDA == RED+2) || (GDA == GREEN+2) || (BDA == BLUE+2);
bool MIN = (RDA == RED-2) || (GDA == GREEN-2) || (BDA == BLUE-2);

bool isStopped = LOW;
bool lastState = LOW;
bool triggerActive = false;
unsigned long startTime = 0;
const unsigned long runDuration = 120000;
unsigned long lastRead = 0;
const int interval = 1000;

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
// <<<<<<< HEAD(millis() - startTime <= runDuration) {
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

//============================================================
  delay(1000);
  readColor();
  if(((RDA!=RED)&&(GDA!=GREEN)&&(BDA!=BLUE))&&isStopped==LOW){
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
  }else if(MIN||PASS||OVR){
    stopSystem();
    isStopped=HIGH;
    Serial.println("STOP ALL SYSTEMS");
  }
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
  analogWrite(ENM, 150);
}

void MS() {
  analogWrite(ENM, 0);
}

void PSR() {
  digitalWrite(PSP, HIGH);
  digitalWrite(PSN, LOW);
  analogWrite(ENP, 110);
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

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_TCS34725.h>

#define PSP 7
#define PSN 8
#define ENP 9
#define MDP 11
#define MDN 12
#define ENM 10
#define SW 2
#define LSR 4
#define LSY 5
#define LSG 6
#define LEDC A2
#define INTC A3
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

int RED = -10;
int GREEN = -10;
int BLUE = -10;
int CLEAR = -10;

int RDB = 2;
int GDB = 5;
int BDB = 8;
int CDB = 16;
int RDY = 1;
int GDY = 2;
int BDY = 1;
int CDY = 4;
bool lastState = 0;
unsigned long startTime = 0;
int time_run = 0;
const unsigned long runDuration = 120000;
unsigned long lastRead = 0;
unsigned long interval = 1000;
bool TCS_stats = 0;
typedef enum {
  RUNNING,
  STOPPED
} ProgramState;
ProgramState state = RUNNING;
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup(void) {
  Serial.begin(9600);
  startTime = millis();
  if (tcs.begin()) {
    TCS_stats = 1;
  } else {
    TCS_stats = 0;
  }
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(10, 0);
  display.println(F("CYLUX 3.0"));
  display.drawLine(0, 24, 127, 24, SSD1306_WHITE);
  display.setCursor(23, 16);
  display.setTextSize(1);
  display.println("SYSTEM");
  display.setCursor(70, 16);
  display.println(state);
  display.setCursor(0, 27);
  display.setTextSize(1);
  display.println("TCS:");
  display.setTextSize(1);
  display.setCursor(22, 27);
  display.setTextSize(1);
  display.print(TCS_stats);
  display.setCursor(0, 40);
  display.print("R:");
  display.setCursor(10, 40);
  display.print(RED);
  display.setCursor(30, 40);
  display.print("G:");
  display.setCursor(40, 40);
  display.print(GREEN);
  display.setCursor(65, 40);
  display.print("B:");
  display.setCursor(75, 40);
  display.print(BLUE);
  display.setCursor(98, 40);
  display.print("C:");
  display.setCursor(108, 40);
  display.print(CLEAR);
  display.setCursor(40, 55);
  display.print("TIME:");
  display.setCursor(75, 55);
  display.print(time_run);
  display.display();
  pinMode(SW, INPUT_PULLUP);
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

  digitalWrite(LSR, HIGH);
  digitalWrite(LSY, HIGH);
  digitalWrite(LSG, HIGH);
  digitalWrite(LEDC, LOW);
}

void loop(void) {
  readColor();
  update_lcd();
  bool BLE = (((RED < RDB) || (RED == RDB)) && ((GREEN < GDB) || (GREEN < GDB)) && ((BLUE < BDB) || (BLUE == BDB)) && ((CLEAR < CDB) || (CLEAR == CDB)));
  bool YLW = (((RED < RDY) || (RED == RDY)) && ((GREEN < GDY) || (GREEN < GDY)) && ((BLUE < BDY) || (BLUE == BDY)) && ((CLEAR < CDY) || (CLEAR == CDY)));
  if (state == RUNNING) {
    PSR();
    MR();
    time_run = (millis() - startTime) / 1000;
    if (BLE || YLW) {
      stopSystem();
      state = STOPPED;
    }
  } else {
    if (millis() - lastRead >= 1000) {
      lastRead = millis();
      Serial.print("R: ");
      Serial.print(RED);
      Serial.print("G: ");
      Serial.print(GREEN);
      Serial.print("B: ");
      Serial.print(BLUE);
      Serial.print("C: ");
      Serial.println(CLEAR);
      Serial.println("SYSTEM IS STOPPED");
    }
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
  CLEAR = c;
}
void MR() {
  digitalWrite(MDP, HIGH);
  digitalWrite(MDN, LOW);
  analogWrite(ENM, 255);
}
void MS() {
  digitalWrite(MDP, HIGH);
  digitalWrite(MDN, HIGH);
  analogWrite(ENM, 0);
}
void PSR() {
  digitalWrite(PSP, HIGH);
  digitalWrite(PSN, LOW);
  analogWrite(ENP,  200);
}
void update_lcd() {
  display.setTextSize(1);
  display.fillRect(70, 16, 40, 8, BLACK);
  display.fillRect(22, 27, 22, 8, BLACK);
  display.fillRect(10, 40, 20, 8, BLACK);
  display.fillRect(40, 40, 25, 8, BLACK);
  display.fillRect(75, 40, 22, 8, BLACK);
  display.fillRect(108, 40, 25, 8, BLACK);
  display.fillRect(0, 48, 25, 8, BLACK);
  display.fillRect(75, 55, 25, 8, BLACK);
  display.setCursor(10, 40);
  display.print(RED);
  display.setCursor(43, 40);
  display.print(GREEN);
  display.setCursor(75, 40);
  display.print(BLUE);
  display.setCursor(108, 40);
  display.print(CLEAR);
  display.setCursor(75, 55);
  display.print(time_run);
  display.setCursor(22, 27);
  if (TCS_stats==0){
    display.print("NOT DETECTED");
  }else{
    display.print("DETECTED");
  }
  display.setCursor(70, 16);
  if (state == RUNNING) {
    display.print("RUNNING");
  } else {
    display.print("STOPPED");
  }
  display.display();
}
void PSS() {
  digitalWrite(PSP, HIGH);
  digitalWrite(PSN, HIGH);
  analogWrite(ENP, 0);
}
void stopSystem() {
  MS();
  PSS();
  digitalWrite(LSR, HIGH);
  digitalWrite(LSY, LOW);
  digitalWrite(LSG, LOW);
}
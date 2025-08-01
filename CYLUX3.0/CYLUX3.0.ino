#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_TCS34725.h>

#define MDP 7
#define MDN 8
#define ENM 9
#define PSN 11
#define PSP 12
#define ENP 10
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

int RD15 = 25; //34.50sec
int GD15 = 51; //34.50sec
int BD15 = 58; //34.50sec
int RD18 = 24; //41.40sec
int GD18 = 48; //41.40sec
int BD18 = 52; //41.40sec
int RD20 = 24; //46.00sec
int GD20 = 47; //46.00sec
int BD20 = 48; //46.00sec
int RD22 = 22; //50.60sec
int GD22 = 43; //50.60sec
int BD22 = 42; //50.60sec
int RD24 = 20; //55.20sec
int GD24 = 20; //55.20sec
int BD24 = 40; //55.20sec
int RD25 = 36; //57.50sec
int GD25 = 20; //57.50sec
int BD25 = 39; //57.50sec
int RD26 = 20; //59.80sec
int GD26 = 39; //59.80sec
int BD26 = 33; //59.80sec
int RD28 = 19; //64.40sec
int GD28 = 37; //64.40sec
int BD28 = 31; //64.40sec
int RD30 = 19; //69.00sec
int GD30 = 37; //69.00sec
int BD30 = 29; //69.00sec
int RDA = RD30;
int GDA = GD30;
int BDA = BD30;

bool isStopped = 0;
bool lastState = 0;
bool triggerActive = false;
unsigned long startTime = 0;
const unsigned long runDuration = 120000;
unsigned long lastRead = 0;
const unsigned long countdown = 0;
unsigned long time_run = 0;
unsigned long interval = 1000;
bool TCS_stats = 0;
// enum SYS_MODE = {STANDBY,START,STOP};
// uint8_t SYSTEM_STATS = STANDBY;



//Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_614MS, TCS34725_GAIN_1X);
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

  // if (tcs.begin()) {
  //   Serial.println("Found sensor");
  // } else {
  //   Serial.println("No TCS34725 found ... check your connections");
  //   // while (1);
  // }
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup(void) {
  Serial.begin(9600);
  if (tcs.begin()) {
    TCS_stats=1;
  } else {
    TCS_stats=0;
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
  display.println("SYSTEM STANDBY");
  display.setCursor(62, 27);
  display.setTextSize(2);
  display.println(countdown);
  display.setCursor(0, 45);
  display.setTextSize(1);
  display.println("TCS:");
  display.setCursor(22, 45);
  display.print(TCS_stats);
  display.setCursor(35, 45);
  display.print("R:");
  display.setCursor(45, 45);
  display.print(RED);
  display.setCursor(68, 45);
  display.print("G:");
  display.setCursor(78, 45);
  display.print(GREEN);
  display.setCursor(100, 45);
  display.print("B:");
  display.setCursor(110, 45);
  display.print(WHITE);
  display.setCursor(40, 56);
  display.print("TIME:");
  display.setCursor(75, 56);
  display.print(time_run);
  display.display();
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

  digitalWrite(LSR, LOW);
  digitalWrite(LSY, LOW);
  digitalWrite(LSG, LOW);
  digitalWrite(LEDC, LOW);
}

void loop(void) {

  bool PASS = (RDA == RED) || (GDA == GREEN) || (BDA == BLUE);
  bool STOP = (RED==RDA) && (GREEN==GDA) && (BLUE == BDA);
  bool OVR = (RDA == RED+2) || (GDA == GREEN+2) || (BDA == BLUE+2);
  bool MIN = (RDA == RED-2) || (GDA == GREEN-2) || (BDA == BLUE-2);
  bool TOLERANCE = ((RDA-1 < RED < RDA+1) && (GDA-1 < GREEN < GDA+1) && (BDA-1 < BLUE < BDA+1));

  // if (millis() - lastUpdate >= 500) {
  //   lastUpdate = millis();
    
  // }
  // bool currentState = digitalRead(SW);
  // Serial.println(currentState);
  // Serial.println("sistem standby");
  // if (currentState == HIGH && lastState == LOW && !triggerActive) {
  //   triggerActive = true;
  //   Serial.println("sistem start");
  //   delay(50);
  //   startTime = millis();
  // delay(1000);
  // PSR();
  // MR();
  // delay(12000);
  // PSS();
  // MS();
  // delay(10000);
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
  //delay(1000  );
// >>>>>>> a84ef76ec554af3c3ce75407b9c27ca23c138a11

//============================================================
  // delay(1000);
  readColor();
  if(((RDA!=RED)&&(GDA!=GREEN)&&(BDA!=WHITE))&&isStopped==LOW){
    PSR();
    MR();
    if(millis() - lastRead >= 1000){
      lastRead = millis();
      Serial.println("START SYSTEMS");
      Serial.print("R: ");
      Serial.print(RED);
      Serial.print("G: ");
      Serial.print(GREEN);
      Serial.print("B: ");
      Serial.print(WHITE);
      Serial.println(" ");
    }
  }else if(TOLERANCE){
    if(millis() - lastRead >= 1000){
      lastRead = millis();
      Serial.print("R: ");
      Serial.print(RED);
      Serial.print("G: ");
      Serial.print(GREEN);
      Serial.print("B: ");
      Serial.print(WHITE);
      Serial.println(" ");
      Serial.println("SYSTEM IS STOPPED");
    }
    stopSystem();
    isStopped=HIGH;
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
  digitalWrite(MDP, LOW);
  digitalWrite(MDN, HIGH);
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
  analogWrite(ENP, 110);
}
void update_rgb_val(){
  display.setTextSize(1);
  display.fillRect(45, 45, 20, 8, BLACK);
  display.fillRect(78, 45, 20, 8, BLACK);
  display.fillRect(110, 45, 20, 8, BLACK);
  display.setCursor(45, 45); display.print(RED);
  display.setCursor(78, 45); display.print(GREEN);
  display.setCursor(110, 45); display.print(WHITE);
  display.display();
}
void update_countdown(){
  display.setTextSize(2);
  display.fillRect(62, 27, 20, 8, BLACK);
  display.setCursor(62, 27); display.print(countdown);
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

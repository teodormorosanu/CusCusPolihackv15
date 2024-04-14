#include "LiquidCrystal_I2C.h"
#include  "Wire.h"

#define BUZZ_IN 2 // Buzzer IN pin
#define BUZZ_VCC 3 // Buzzer VCC pin
#define RED_LED 4 // Red led pin
#define GREEN_LED 5 // Green led pin
#define L_BUTTON 6 // Left button pin
#define R_BUTTON 7 // Left button pin
#define LASER_DIODE A0 // Laser diode pin
#define I_SENSOR A1 // Inclination sensor pin 

LiquidCrystal_I2C lcd(0x27,  16, 2);

byte pointer[]={0x00, 0x00, 0x04, 0x02, 0x1D, 0X02, 0X04, 0X00};

bool leftButton, rightButton; // Buttons states (pressed / not pressed)
bool completed1 = false;
bool completed2 = false;
int cursor = 0;
int iteration = 0;

void BuzzerSetup() { // Method for buzzer setup
  pinMode(BUZZ_IN, OUTPUT); // Setting the buzzer pin as output
  pinMode(BUZZ_VCC, OUTPUT); // Powering the buzzer from another arduino pin
  digitalWrite(BUZZ_VCC, HIGH);
  tone(BUZZ_IN, 1200);
  delay(150);
  tone(BUZZ_IN, 1600);
  delay(150);
  tone(BUZZ_IN, 2000);
  delay(150);
  digitalWrite(BUZZ_VCC, LOW);
  noTone(BUZZ_IN);
}

void LEDsSetup() { // Method for LEDs setup
  pinMode(RED_LED, OUTPUT); // Setting the red LED pin as output
  pinMode(GREEN_LED, OUTPUT); // Setting the green LED pin as output
  digitalWrite(RED_LED, HIGH);
  digitalWrite(GREEN_LED, HIGH);
  delay(500);
  digitalWrite(RED_LED, LOW);
  digitalWrite(GREEN_LED, LOW);
  delay(500);
  digitalWrite(RED_LED, HIGH);
  digitalWrite(GREEN_LED, HIGH);
  delay(500);
  digitalWrite(RED_LED, LOW);
  digitalWrite(GREEN_LED, LOW);
}

void ButtonsSetup() { // Method for buttons setup
  pinMode(L_BUTTON, INPUT); // Setting the left button pin as input
  pinMode(R_BUTTON, INPUT); // Setting the right button pin as input
}

void LCDSetup() { // Method for LCD setup
  lcd.init(); // Intialising the LCD
  lcd.backlight(); // Lighting the LCD backlight
  lcd.createChar(1,  pointer);
  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("CUS KIT 1.0");
  delay(100);
  lcd.setCursor(3, 1);
  lcd.print("By Cus Cus");
  delay(3000);
  lcd.clear();
}

void AirplaneModuleSetup() {
  pinMode(LASER_DIODE, OUTPUT);
  pinMode(I_SENSOR, INPUT);
}

void setup() {
  Serial.begin(9600);
  BuzzerSetup(); // Method for buzzer setup
  LEDsSetup(); // Method for leds setup
  ButtonsSetup(); // Methos for buttons setup
  LCDSetup(); // Method for LCD setup
  AirplaneModuleSetup();
  digitalWrite(GREEN_LED, HIGH);
}

void MainPage() {
  lcd.clear(); 
  switch(cursor) {
    case 0: lcd.setCursor(0, 0);
    lcd.write(1);
    break;
    case 1: lcd.setCursor(0, 1); 
    lcd.write(1);
    break;
  }  
  lcd.setCursor(1, 0);
  lcd.print("1. SCHOOL"); 
  lcd.setCursor(1, 1);
  lcd.print("2. CREATIVITY");  
  lcd.setCursor(1, 2);
  if(digitalRead(L_BUTTON) == HIGH && digitalRead(R_BUTTON) == LOW) { 
    if(cursor > 0) {
      cursor--;
    }
    delay(35);
  }
  if(digitalRead(R_BUTTON) == HIGH && digitalRead(L_BUTTON) == LOW){
    if(cursor < 1) {
      cursor++;
    }
    delay(35);
  }
  if(digitalRead(L_BUTTON) == HIGH && digitalRead(R_BUTTON) == HIGH) {
    while(1) {
      Enter();
      if(digitalRead(L_BUTTON) == HIGH && digitalRead(R_BUTTON) == HIGH && cursor == 1) {
        cursor = 0;
        break;
      }
    }
  }
  Serial.println(cursor);
  delay(100);
}

void Enter() {
  switch(cursor) {
  case 0:
    lcd.clear();
    lcd.setCursor(1, 0);
    lcd.print("1. Cus Airplane");
    delay(50);
    if(digitalRead(L_BUTTON) == HIGH && digitalRead(R_BUTTON) == HIGH) {
      while(1) {
        CusAirplane();
      }
    }
    break;
  case 1:
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Available from");
    lcd.setCursor(0, 1);
    lcd.print("future versions");
    delay(75);
    break;
  }
  Serial.println(cursor);
}

void CusAirplane() {
    if(!completed1) {
      lcd.clear();
      lcd.setCursor(1, 0);
      lcd.print("1 : (+) -> VCC");
      lcd.setCursor(1, 1);
      lcd.print("2 : (-) -> GND");
      delay(3000);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("After connection");
      lcd.setCursor(0, 1);
      lcd.print("Hold R-Button");
      delay(3000);
    }
    if(digitalRead(R_BUTTON) == HIGH || completed1) {
      completed1 = true;
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("3 : (D) -> A0");
      delay(3000);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("After connection");
      lcd.setCursor(0, 1);
      lcd.print("Diode is ON");
      delay(3000);
      digitalWrite(LASER_DIODE, HIGH);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("");
    }
    if((digitalRead(R_BUTTON) == HIGH || completed1) && !completed2) {
      completed1 = true;
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("3 : (D) -> A0");
      delay(3000);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("After connection");
      lcd.setCursor(0, 1);
      lcd.print("Diode is ON");
      delay(3000);
      digitalWrite(LASER_DIODE, HIGH);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("");
      if(digitalRead(R_BUTTON) == HIGH) {
        completed2 = true;
      }
    }
    if(completed2) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("4 : (I) -> A1");
      delay(3000);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("After connection");
      lcd.setCursor(0, 1);
      lcd.print("Hold to START");
      delay(3000);
      lcd.clear();
      lcd.setCursor(0, 0);
      if(digitalRead(R_BUTTON) == HIGH) {
        while(1) {
          lcd.clear();
          lcd.print("Minigame");
          delay(50);
          //minigame
        }
      }
      lcd.print("");
    }
}

void loop() {
  MainPage();
}

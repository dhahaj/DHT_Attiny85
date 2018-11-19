#include <Wire.h>
#include <LiquidCrystal_PCF8574.h>
#include "DHT.h"

#define DHTPIN 3     // what digital pin we're connected to
#define DHTTYPE DHT11   // DHT 11

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_PCF8574 lcd(0x27);  // set the LCD address to 0x27 for a 16 chars and 2 line display

void setup() {
  dht.begin();
  Wire.begin();
  lcd.begin(16, 2); // initialize the lcd
  lcd.home(); lcd.clear(); lcd.setBacklight(200); lcd.noBlink(); lcd.noCursor();
  lcd.print("DHT11 Sensor");
}

void loop() {
  delay(2000);
  printTemps();
}

void printTemps() {
  float h = dht.readHumidity();
  float tC = dht.readTemperature();
  float f = dht.readTemperature(true);
  if (isnan(h) || isnan(tC) || isnan(f)) {
    lcd.clear();
    lcd.setCursor(2, 0);
    lcd.print("Error!");
    return;
  }
  lcd.setCursor(1, 0);
  lcd.print(tC);
  lcd.print("C/");
  lcd.print(f);
  lcd.print("F");
  lcd.setCursor(1, 1);
  lcd.print(h);
  lcd.print("%  ");

}


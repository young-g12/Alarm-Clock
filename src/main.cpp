#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <ThreeWire.h>
#include <RtcDS1302.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

ThreeWire myWire(7, 6, 8);
RtcDS1302<ThreeWire> Rtc(myWire);

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.clear();

  Rtc.Begin();

  // Uncomment this ONCE to set the RTC to your computer's
  // compile date and time:
  //
  RtcDateTime currentTime = RtcDateTime(__DATE__, __TIME__);
  Rtc.SetDateTime(currentTime);
}

void loop() {
  RtcDateTime now = Rtc.GetDateTime();

  // Date
  lcd.setCursor(0, 0);
  lcd.print("Date: ");

  if (now.Day() < 10) lcd.print("0");
  lcd.print(now.Day());
  lcd.print("/");

  if (now.Month() < 10) lcd.print("0");
  lcd.print(now.Month());
  lcd.print("/");

  lcd.print(now.Year());

  // Time
  lcd.setCursor(0, 1);
  lcd.print("Time: ");

  if (now.Hour() < 10) lcd.print("0");
  lcd.print(now.Hour());
  lcd.print(":");

  if (now.Minute() < 10) lcd.print("0");
  lcd.print(now.Minute());
  lcd.print(":");

  if (now.Second() < 10) lcd.print("0");
  lcd.print(now.Second());

  delay(500);
}
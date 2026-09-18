#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <ThreeWire.h>
#include <RtcDS1302.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

ThreeWire myWire(7, 6, 8);
RtcDS1302<ThreeWire> Rtc(myWire);

// Pins
int buttonPin = 4;
int buzzer = 3;

// =============================
// SET YOUR ALARM TIME HERE
// =============================
int alarmHour = 18;       // 18 = 6 PM
int alarmMinute = 33;     // 30 minutes

bool alarmOn = false;
bool alarmStopped = false;

void setup() {

  lcd.init();
  lcd.backlight();
  lcd.clear();

  Rtc.Begin();

  // Button uses internal pull-up resistor
  pinMode(buttonPin, INPUT_PULLUP);

  pinMode(buzzer, OUTPUT);

  // Make sure buzzer starts OFF
  digitalWrite(buzzer, LOW);

  // Uncomment this ONCE to set the RTC
  // to your computer's compile date/time.
  //
  // RtcDateTime currentTime = RtcDateTime(__DATE__, __TIME__);
  // Rtc.SetDateTime(currentTime);
}

void loop() {

  RtcDateTime now = Rtc.GetDateTime();

  // =============================
  // DISPLAY DATE
  // =============================

  lcd.setCursor(0, 0);
  lcd.print("Date: ");

  if (now.Day() < 10)
    lcd.print("0");

  lcd.print(now.Day());
  lcd.print("/");

  if (now.Month() < 10)
    lcd.print("0");

  lcd.print(now.Month());
  lcd.print("/");

  lcd.print(now.Year());

  // =============================
  // DISPLAY TIME
  // =============================

  lcd.setCursor(0, 1);
  lcd.print("Time: ");

  if (now.Hour() < 10)
    lcd.print("0");

  lcd.print(now.Hour());
  lcd.print(":");

  if (now.Minute() < 10)
    lcd.print("0");

  lcd.print(now.Minute());
  lcd.print(":");

  if (now.Second() < 10)
    lcd.print("0");

  lcd.print(now.Second());

  // =============================
  // RESET ALARM STOP
  // =============================

  if (now.Minute() != alarmMinute) {
    alarmStopped = false;
  }

  // =============================
  // CHECK ALARM TIME
  // =============================

  if (now.Hour() == alarmHour &&
      now.Minute() == alarmMinute &&
      !alarmStopped) {

    alarmOn = true;
  }

  // =============================
  // BUTTON
  // =============================

  int buttonState = digitalRead(buttonPin);

  // INPUT_PULLUP means:
  // LOW = button pressed
  // HIGH = button not pressed

  if (buttonState == LOW) {

    alarmOn = false;
    alarmStopped = true;
  }

  // =============================
  // BUZZER
  // =============================

  if (alarmOn) {
    digitalWrite(buzzer, HIGH);
  }
  else {
    digitalWrite(buzzer, LOW);
  }

  delay(100);
}

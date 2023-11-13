#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Wire.begin(10, 8);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(1, 0);
  lcd.print("Hello, world !");
  lcd.setCursor(2, 1);
  lcd.print("ESP32-C3 I2C");
}

void loop() {
  delay(100);
}

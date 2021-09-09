#include <GParser.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,20,4);

void setup()
{
  lcd.init();
  lcd.backlight();
  
  lcd.setCursor(0,0);
  lcd.print("please wait...");
  
  Serial.begin(9600);
  Serial.setTimeout(5);
  
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("listening for data!");
}

void loop()
{
  if (Serial.available()) {
    char str[12];
    int amount = Serial.readBytesUntil(';', str, 12);
    str[amount] = NULL;

    GParser data(str, ',');
    int am = data.split();

    lcd.clear();
  
    lcd.setCursor(5,0);
    lcd.print("monitoring");

    lcd.setCursor(0,1);
    lcd.print("ram load: ");
    lcd.print(data[0]);
    lcd.print("%");

    lcd.setCursor(0,2);
    lcd.print("cpu temp: ");
    lcd.print(data[1]);
    lcd.print((char)223);
    lcd.print("C");

    lcd.setCursor(0,3);
    lcd.print("gpu temp: ");
    lcd.print(data[2]);
    lcd.print((char)223);
    lcd.print("C");
  }
}

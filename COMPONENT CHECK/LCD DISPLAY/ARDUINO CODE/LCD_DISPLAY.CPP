// check the liquid crystal display 


#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include<Arduino.h>

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

void setup()
{
  lcd.init();                      // initialize the lcd 
  lcd.backlight();
  Serial.begin(9600);
  lcd.println("hello world");
}

void loop()
{

}
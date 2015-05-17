// Libraries
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <SD.h>
#include <Ethernet.h>

// LCD Screen
LiquidCrystal_I2C lcd(0x27,20,4);

void setup() 
{
  // Initialize LCD screen
  initDisplay();
  
}

void loop() 
{
  // Print message on the LCD screen
  lcd.setCursor(0,0);
  lcd.println("This is a test of the LCD screen!");
}

// Initialize LCD screen
void initDisplay()
{
  lcd.init();      
  lcd.backlight();
  lcd.clear();
}
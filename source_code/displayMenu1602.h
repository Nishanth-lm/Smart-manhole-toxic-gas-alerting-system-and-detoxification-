#ifndef _DISPLAY_MENU_1602_H
#define _DISPLAY_MENU_1602_H
#include "Arduino.h"
#include <Wire.h>
// The I2C LCD library
#include <LiquidCrystal_I2C.h>
// The menu wrapper library
#include <LiquidMenu.h>
// The I2C LCD object
#include "Button.h"

#include "sprayMotor.h"
#include "led.h"
#include "GSM_MODULE.h"
#include "GAS_SENSORS.h"

const char PHONE[] PROGMEM = "+919060344544";

SprayMotor sprayObj;

Led ledObj;
GAS_SENSORS gasObj;
GSM_MODULE gsm;

//OK  D5
//LEFT  D6
//RIGHT D7
//BACK  D8

float LPG = 0.0;
float methane = 0.0;
float co = 0.0;
float ammonia = 0.0;

// Button objects instantiation
const bool pullup = false;
Button left(7, pullup);
Button right(8, pullup);
//Button up(8, pullup);
//Button down(9, pullup);
Button enter(9, pullup);

LiquidCrystal_I2C lcd(0x27, 16, 2);

LiquidLine welcome_line1(1, 0,"MANHOLE GAS");
LiquidLine welcome_line2(1, 1, "DETECTION!!");
LiquidScreen welcome_screen(welcome_line1, welcome_line2);
LiquidLine gasLine1(1, 0, "LPG(PPM):", LPG);
LiquidLine gasLine2(1, 1,"CH4(PPM):" , methane);
LiquidScreen GASSCREEN1(gasLine1, gasLine2);
LiquidLine gasLine3(1, 0, "CO(PPM):", co);
LiquidLine gasLine4(1, 1, "NH4(PPM):", ammonia);
LiquidScreen GASSCREEN2(gasLine3, gasLine4);
LiquidLine clickLine(1, 0, " Click OK to");
LiquidLine spray_line(5, 1, " SPRAY");
LiquidLine demo_line(5, 1, " DEMO");
LiquidScreen screen3(clickLine, spray_line);
LiquidScreen screen4(clickLine, demo_line);

LiquidMenu menu(lcd);

void sprayliquid()
{
  ledObj.blueOn();
  Serial.println(F("Spray"));
  sprayObj.motor(1500);
  ledObj.blueOff();

}
void showDemo()
{
  //turn led red
  ledObj.redOn();
  //send message with values
  Serial.println(F("Demo"));
  String message PROGMEM = "LPG:" + String(LPG) + "\nCH4=" + String(methane) + "\nCO=" + String(co) + "\nNH4=" + String(ammonia);
  gsm.sendMessage(message, PHONE);
  sprayliquid();
  ledObj.redOff();


}
unsigned int count = 0;
class displayMenu1602
{

  public:
    void begin()
    {

      Serial.begin(9600);
      //uncomment in the final code after attaching gas sensors
      ledObj.greenOn();
      gasObj.begin();
      ledObj.greenOff();
      sprayObj.begin();
      ledObj.begin();
      ledObj.Red(500);
      ledObj.Blue(500);
      ledObj.Green(500);
      
      lcd.init();
      lcd.backlight();
      demo_line.attach_function(1, showDemo);
      spray_line.attach_function(1, sprayliquid);
      // Menu initialization.
      menu.init();
      // This is the method used to add a screen object to the menu.
      menu.add_screen(welcome_screen);
      menu.add_screen(GASSCREEN1);
      menu.add_screen(GASSCREEN2);
      menu.add_screen(screen3);
      menu.add_screen(screen4);
      menu.update();
      delay(3000);
      menu.next_screen();

    }

    void runMenu()
    {
      // Check all the buttons
      if (right.check() == LOW)
      {
        Serial.println(F("RIGHT button pressed"));
        menu.next_screen();
      }
      if (left.check() == LOW)
      {
        Serial.println(F("LEFT button pressed"));
        menu.previous_screen();
      }
      if (enter.check() == LOW)
      {
        Serial.println(F("ENTER button pressed"));
        // Switches focus to the next line.
        menu.switch_focus();
        //get the spray system running
        menu.call_function(1);
      }

      LPG = gasObj.getLpgPPM();
      methane = gasObj.getMethanePPM();
      co = gasObj.getCoPPM();
      ammonia = gasObj.getAmmoniaPPM();

      count = count + 1;
      if (count >= 10)
      {
        menu.update();
        count = 0;
      }

    }

};

#endif //_DISPLAY_MENU_1602_H

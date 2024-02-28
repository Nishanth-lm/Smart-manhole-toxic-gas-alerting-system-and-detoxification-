#include <Arduino.h>
#include "displayMenu1602.h"
#include <LiquidCrystal.h>
displayMenu1602 dispObj;
void setup() {
  // put your setup code here, to run once:
dispObj.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
 dispObj.runMenu();
}

#ifndef _LED_H
#define _LED_H
#include "Arduino.h"

const byte red = 10;
#define green 12
#define  blue 11

class Led
{
public:
    int _pin;

    void begin()
    {
        pinMode(red, OUTPUT);
        pinMode(green, OUTPUT);
        pinMode(blue, OUTPUT);
    }
    void redOn()
    {
        digitalWrite(red, HIGH);
    }
    void redOff()
    {
        digitalWrite(red, LOW);
    }
    void blueOn()
    {
        digitalWrite(blue,HIGH);
    }
    void blueOff()
    {
        digitalWrite(blue,LOW);
    }
    void greenOn()
    {
        digitalWrite(green,HIGH);
    }
    void greenOff()
    {
        digitalWrite(green,LOW);
    }
    void Green(int tym)
    {
         digitalWrite(green,HIGH);
         delay(tym);
         digitalWrite(green,LOW);
    }
    void Red(int tym)
    {
         digitalWrite(red,HIGH);
         delay(tym);
         digitalWrite(red,LOW);
    }
    void Blue(int tym)
    {
         digitalWrite(blue,HIGH);
         delay(tym);
         digitalWrite(blue,LOW);
    }
};
#endif

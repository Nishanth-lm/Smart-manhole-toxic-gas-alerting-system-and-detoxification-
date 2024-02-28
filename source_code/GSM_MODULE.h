#ifndef _GSM_MODULE_H
#define _GSM_MODULE_H
#include "Arduino.h"
#include <SoftwareSerial.h>

#define RX 4
#define TX 3

SoftwareSerial mySerial(RX, TX);
char incomingByte;
String inputString;
class GSM_MODULE
{
public:
    void sendMessage(String message, String number)
    {
        mySerial.begin(9600);
        delay(1000);
        mySerial.println(F("AT"));
        delay(500);
        mySerial.println(F("AT+CMGF=1"));
        delay(500);
        mySerial.println("AT+CMGS=\"" + number + "\"\r");
        delay(500);
        mySerial.print(message);
        delay(500);
        mySerial.write(26);
        delay(1000);
    }
};

#endif //_GSM_MODULE_H

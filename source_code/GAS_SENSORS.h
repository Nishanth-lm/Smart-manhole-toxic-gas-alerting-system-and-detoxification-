
#ifndef _GAS_SENSOR_H
#define _GAS_SENSOR_H
#include "Arduino.h"
#include <MQUnifiedsensor.h>

/************************Hardware Related Macros************************************/
#define         Board                   ("Arduino Mega")
const int       PMQ135                  =(A0);
const int       PMQ7                    =(A1);
const int       PMQ6                    =(A2);
const int       PMQ2                    =(A3);
/***********************Software Related Macros************************************/
#define         RatioMQ2CleanAir          (9.83) //RS / R0 = 9.83 ppm 
#define         RatioMQ6CleanAir          (10) //RS / R0 = 10 ppm 
#define         RatioMQ7CleanAir          (27.5) //RS / R0 = 27.5 ppm  
#define         RatioMQ135CleanAir        (3.6) //RS / R0 = 9.6 ppm 
#define         ADC_Bit_Resolution        (10) // 10 bit ADC 
#define         Voltage_Resolution        (5) // Volt resolution to calc the voltage
#define         Type                      ("Arduino Nano") //Board used
/*****************************Globals***********************************************/
//Declare Sensor
MQUnifiedsensor MQ135(Board, Voltage_Resolution, ADC_Bit_Resolution, PMQ135, Type);
MQUnifiedsensor MQ2(Board, Voltage_Resolution, ADC_Bit_Resolution, PMQ2, Type);
MQUnifiedsensor MQ6(Board, Voltage_Resolution, ADC_Bit_Resolution, PMQ6, Type);
MQUnifiedsensor MQ7(Board, Voltage_Resolution, ADC_Bit_Resolution, PMQ7, Type);
class GAS_SENSORS
{
  public:
    void begin() {
      //Init serial port
      Serial.begin(9600);
      //init the sensor
      MQ2.init();
      MQ2.setRegressionMethod(1); //_PPM =  a*ratio^b
      MQ2.setA(574.25); MQ2.setB(-2.222); // Configurate the ecuation values to get LPG concentration
      MQ2.setR0(9.659574468);

      MQ6.init();
      MQ6.setRegressionMethod(1); //_PPM =  a*ratio^b
      MQ6.setA(2127.2); MQ6.setB(-2.526); // Configurate the ecuation values to get CH4 concentration
      MQ6.setR0(13.4285714);

      MQ7.init();
      MQ7.setRegressionMethod(1); //_PPM =  a*ratio^b
      MQ7.setA(99.042); MQ7.setB(-1.518); // Configurate the ecuation values to get CO concentration
      MQ7.setR0(4);

      MQ135.init();
      MQ135.setRegressionMethod(1); //_PPM =  a*ratio^b
      MQ135.setA(102.2); MQ135.setB(-2.473);// Configurate the ecuation values to get NH4 concentration
      MQ135.setR0(10);

      /*****************************  MQ CAlibration ********************************************/
      // Explanation:
      // In this routine the sensor will measure the resistance of the sensor supposing before was pre-heated
      // and now is on clean air (Calibration conditions), and it will setup R0 value.
      // We recomend execute this routine only on setup or on the laboratory and save on the eeprom of your arduino
      // This routine not need to execute to every restart, you can load your R0 if you know the value
      // Acknowledgements: https://jayconsystems.com/blog/understanding-a-gas-sensor
      Serial.print(F("Calibrating please wait."));
      float MQ2calcR0 = 0,
            MQ6calcR0 = 0,
            MQ7calcR0 = 0,
            MQ135calcR0 = 0;
      for (int i = 1; i <= 10; i ++)
      {
        //Update the voltage lectures
        MQ2.update();
        MQ6.update();
        MQ7.update();
        MQ135.update();

        MQ2calcR0 += MQ2.calibrate(RatioMQ2CleanAir);
        MQ6calcR0 += MQ2.calibrate(RatioMQ6CleanAir);
        MQ7calcR0 += MQ2.calibrate(RatioMQ7CleanAir);
        MQ135calcR0 += MQ2.calibrate(RatioMQ135CleanAir);
        Serial.print(F("."));
      }
      MQ2.setR0(MQ2calcR0 / 20);
      MQ6.setR0(MQ6calcR0 / 20);
      MQ7.setR0(MQ7calcR0 / 20);
      MQ135.setR0(MQ135calcR0 / 20);
      

      if (isinf(MQ2calcR0) || isinf(MQ6calcR0) || isinf(MQ7calcR0) || isinf(MQ135calcR0)) {
        Serial.println(F("Warning: Conection issue founded, R0 is infite (Open circuit detected) please check your wiring and supply"));
        while (1);
      }
      if (MQ2calcR0 == 0 || MQ6calcR0 == 0 || MQ7calcR0 == 0 || MQ135calcR0 == 0) {
        Serial.println(F("Warning: Conection issue founded, R0 is zero (Analog pin with short circuit to ground) please check your wiring and supply"));
        while (1);
      }
      /*****************************  MQ CAlibration ********************************************/
    }

    float getLpgPPM()
    {
      MQ2.update();
      return (MQ2.readSensor());
    }
    float getMethanePPM()
    {
      MQ6.update();
      return (MQ6.readSensor());
    }
    float getCoPPM()
    {
      MQ7.update();
      return (MQ7.readSensor());
    }
    float getAmmoniaPPM()
    {
      MQ135.update();
      return (MQ135.readSensor());
    }

};
#endif

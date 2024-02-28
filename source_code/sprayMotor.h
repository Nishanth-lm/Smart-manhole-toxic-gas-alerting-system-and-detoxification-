#ifndef _SPRAY_MOTOR_H
#define _SPRAY_MOTOR_H
const byte in1 = 2;
const byte in2 = 5;
class SprayMotor
{
public:
    void begin()
    {
        pinMode(in1, OUTPUT);
        pinMode(in2, OUTPUT);

        // Turn off motors - Initial state
        digitalWrite(in1, LOW);
        digitalWrite(in2, LOW);
    }

    void motorOn()
    {
        digitalWrite(in1, HIGH);
        digitalWrite(in2, LOW);
    }
    void motorOff()
    {
        digitalWrite(in1, LOW);
        digitalWrite(in2, LOW);
    }
    void motor(int tym)
    {
        digitalWrite(in1, HIGH);
        digitalWrite(in2, LOW);
        delay(tym);
        digitalWrite(in1, LOW);
        digitalWrite(in2, LOW);
    }
};

#endif //_SPRAY_MOTOR_H
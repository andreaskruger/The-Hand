#include <Arduino.h>
#include <ADS1118.h>
#include <SPI.h>

// Change these constants according to your project's design
const float VCC = 3.3;			// voltage at Ardunio 5V line
const float R_DIV = 100000.0;	// resistor used to create a voltage divider

void initFlexSensor(int pin){
    pinMode(pin, INPUT);
}

float readResistance(int pin){
    int ADCflex = analogRead(pin);

    float Vflex = ADCflex * VCC / 4095.0; //1023.0
    float Rflex = R_DIV * (VCC / Vflex - 1.0);
    return Rflex;
}

float getAngle(int pin){
    float angle = readResistance(pin) * 2.6716/1000 - 30.2045 - 60; //From Matlab calibration
    return angle;
}

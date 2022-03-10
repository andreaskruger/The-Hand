#include <Arduino.h>
#include <ADS1118.h>
#include <SPI.h>

// Defining breakout board, multiplexter
#define CS 5
ADS1118 ads1118(CS);

// Change these constants according to your project's design
const float VCC = 3.3;			// voltage at Ardunio 5V line
const float R_DIV = 100000.0;	// resistor used to create a voltage divider

float readResistance(int pin, int type){    // 0<=type<6 -> on esp board, 6=<type<10 -> on multiplexer
    float Vflex = 0;
    if(type < 6){
        int ADCflex = analogRead(pin);
        Vflex = ADCflex * VCC / 4095.0; // 12 bit gives 4095 values
    }
    else if (type >= 6){
        Vflex = ads1118.getMilliVolts(pin) / 1000.0;
    }
    
    float Rflex = R_DIV * (VCC / Vflex - 1.0);
    return Rflex;
}

float getAngle(int pin, int type){
    float angle = readResistance(pin, type) * 2.6716/1000 - 30.2045 - 60; //From Matlab calibration
    return angle;
}


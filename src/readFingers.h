#include <Arduino.h>
#include <ADS1118.h>
#include <SPI.h>
#include <MedianFilter.h>

// Defining breakout board, multiplexter
#define CS 5
ADS1118 ads1118(CS);

// Defining filrer
#define SAMPLES 10
MedianFilter<float, SAMPLES> mf;

// Change these constants according to design
const float VCC = 3.3;			// voltage
const float R_DIV = 100000.0;	// resistor used to create a voltage divider

float readResistance(int pin, int type){    // 0<=type<4 -> on multiplexer, 4=<type<10 ->on esp board 
    float Vflex;
    if(type >= 4){
        int ADCflex = analogRead(pin);
        Vflex = ADCflex * VCC / 4095.0; // 12 bit gives 4095 values
    }
    else{
        Vflex = ads1118.getMilliVolts(pin) / 1000.0;
    }
    
    float Rflex = R_DIV * (VCC / Vflex - 1.0);
    //mf.addSample(Rflex);
    return Rflex; //mf.getMedian();
}

int getAngle(int pin, int type){
    int angle = readResistance(pin, type) * 2.6716/1000 - 76; //From Matlab calibration
    return angle;
}


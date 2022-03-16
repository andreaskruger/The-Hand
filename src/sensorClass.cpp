/**
 * This class file is used to create flex sensor objects that handle all reading
 * and filtering of each sensor signal.
*/
#include <Arduino.h>
#include <ADS1118.h>
#include <SPI.h>
#include "SensorClass.h"
#include "Config.h"


/*
    Constructor
*/
sensor::sensor(int pin, ADS1118 ads){
    m_pin = pin;
    ads1118 = ads;
}

/*
    Performs a measurement of the sensor and adds it to the median filter.
    Returns the median angle value.
*/
float sensor::getAngle(){
    float angle = getResistance(m_pin) * 2.6716/1000 - 30.2045 - 60; //From Matlab calibration

    m_f.addSample(angle);

    return m_f.getMedian();
}

/*
    Helper method for getAngle().
    Takes a reading at the voltage divider and returns a resistance.
*/
float sensor::getResistance(int pin){ 
    float Vflex;

    Vflex = ads1118.getMilliVolts(pin) / 1000.0;
    
    float Rflex = R_DIV * (VCC / Vflex - 1.0);
    return Rflex;
}


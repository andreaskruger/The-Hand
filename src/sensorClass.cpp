/**
 * This class file is used to create flex sensor objects that handle all reading
 * and filtering of each sensor signal.
*/

#include <Arduino.h>
#include <SPI.h>
#include "SensorClass.h"
#include "Config.h"


/**
 * Constructor
 * @param pin the pin to which the flex sensor is connected to.
 * @param ads the ADC breakout board object which the flexsensor is connected to.
*/

sensor::sensor(int pin){
    m_pin = pin;
}


/**
 * Performs a measurement of the sensor and adds it to the median filter.
 * @return a float with the median angle value.
*/

float sensor::getAngle(){
    float angle = getResistance(m_pin) * 2.6716/1000 - 30.2045 - 60; //From Matlab calibration

    m_f.addSample(angle);

    return m_f.getMedian();
}


/**
 * Helper method for getAngle().
 * Takes a reading at the voltage divider and returns a resistance.
 * @param pin the pin to take a reading from.
 * @return a float with the resistance of the flex sensor.
*/

float sensor::getResistance(int pin){ 
    float Vflex;

    //Vflex = ads1118.getMilliVolts(pin) / 1000.0;
    
    float Rflex = R_DIV * (VCC / Vflex - 1.0);
    return Rflex;
}



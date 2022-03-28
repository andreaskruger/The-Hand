/**
 * This class file is used to create flex sensor objects that handle all reading
 * and filtering of each sensor signal.
*/

#include <Arduino.h>
#include <SPI.h>
#include "flexSensor.h"
#include "Config.h"


/**
 * Constructor
 * @param pin the pin to which the flex sensor is connected to.
 * @param ads the ADC breakout board object which the flexsensor is connected to.
*/

flexSensor::flexSensor(int pin, int minimum_angle, int maximum_angle){
    m_pin = pin;
    min_angle = minimum_angle;
    max_angle = maximum_angle;
}


/**
 * Performs a measurement of the sensor and adds it to the median filter.
 * @return a float with the median angle value.
*/

float flexSensor::getAngle(){
    float angle = map(angle,calibrateOpen,calibrateClosed,min_angle,max_angle);
    m_f.addSample(angle);

    return m_f.getMedian();
}


/**
 * Helper method for getAngle().
 * Takes a reading at the voltage divider and returns a resistance.
 * @param pin the pin to take a reading from.
 * @return a float with the resistance of the flex sensor.
*/


void flexSensor::calibrate(int calibratedValue, int state){
    if(state == 1){
        calibrateOpen = calibratedValue;
    }
    if(state == 2){
        calibrateClosed = calibratedValue;
    }
}
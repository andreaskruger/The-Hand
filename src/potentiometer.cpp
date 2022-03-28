/**
 * This class file is used to create potentiometer objects that handle all reading
 * and filtering of each sensor signal.cha
*/

#include <Arduino.h>
#include <SPI.h>
#include "potentiometer.h"
#include "Config.h"


/**
 * Constructor
 * @param channel the channel to which the flex sensor is connected to.
 * @param minimum_angle the minimum angle of flex sensor.
 * @param maximum_angle the maximum angle of flex sensor.
*/

potentiometer::potentiometer(int pin, int minimum_angle, int maximum_angle){
    m_pin = pin;
    min_angle = minimum_angle;
    max_angle = maximum_angle;
}

int potentiometer::getValue(){
    return analogRead(m_pin);
}


/**
 * Performs a measurement of the sensor and adds it to the median filter.
 * @return a float with the median angle value.
*/
float potentiometer::getAngle(){
    float angle = map(analogRead(m_pin), calibrateMin, calibrateMax, min_angle, max_angle);
    m_f.addSample(angle);
    return m_f.getMedian();
}


// Calibrates the flex sensor, either the open or closed state depending on input
void potentiometer::calibrate(int state){
    if(state == 1){
        calibrateMin = analogRead(m_pin);
    }
    if(state == 2){
        calibrateMax = analogRead(m_pin);
    }
}
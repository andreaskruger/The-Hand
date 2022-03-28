/**
 * This class file is used to create flex sensor objects that handle all reading
 * and filtering of each sensor signal.
*/
#pragma once

#include <Arduino.h>
#include "Config.h"
#include "MedianFilter.h"

/**
 * Main class
*/
class flexSensor{
private:
    // Variables and objects
    int m_pin;
    int min_angle;
    int max_angle;
    int calibrateOpen;
    int calibrateClosed;
    // Number of samples are defined in config.h
    MedianFilter<float, SAMPLES> m_f;
    // Methods
    float getResistance(int);
public:
    flexSensor(int pin, int minimum_angle, int maximum_angle){};
    // Methods
    float getAngle();
    void calibrate(int calibratedValue, int state);
};
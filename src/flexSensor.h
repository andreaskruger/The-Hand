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
    int m_channel;
    int min_angle;
    int max_angle;
    int calibrateOpen;
    int calibrateClosed;
    // Number of samples are defined in config.h
    MedianFilter<float, SAMPLES> m_f;
    // Methods
    float getResistance(int);
    int readMux(int);
public:
    flexSensor(int channel, int minimum_angle, int maximum_angle);
    flexSensor(int channel);
    // Methods
    int getValue();
    float getAngle();
    void calibrate(bool state);
    int getCalibrateOpen();
    int getCalibrateClosed();
};
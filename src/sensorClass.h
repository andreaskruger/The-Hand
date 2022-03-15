/*
    This class file is used to create flex sensor objects that handle all reading
    and filtering of each sensor signal.
*/
#pragma once

#include <Arduino.h>
#include <ADS1118.h>
#include "config.h"
#include "MedianFilter.h"

/*
    Main class
*/
class sensor{
private:
    // Variables and objects
    int m_pin;
    ADS1118 ads1118(int);
    MedianFilter<float, SAMPLES> m_f;
    // Methods
    float getResistance(int);
public:
    sensor(int pin, ADS1118 ads){};
    // Methods
    float getAngle();
};
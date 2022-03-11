/*
    This class file is used to create flex sensor objects that handle all reading
    and filtering of each sensor signal.
*/
#pragma once

#include <Arduino.h>
#include "config.h"
#include "MedianFilter.h"

/*
    Main class
*/
class flexsensor{
    // Variables
private:
    int m_pin;
    String m_location;
    MedianFilter<float, SAMPLES> m_f;

public:
    flexsensor(int pin, String location){};
    // Methods
    // ... Gets
    float getMedian();
    String getlocation();
    // ... Sets
    void read();
};
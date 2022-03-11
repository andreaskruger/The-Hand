/*
    This class file is used to create flex sensor objects that handle all reading
    and filtering of each sensor signal.
*/
#include "flexsensorClass.h"
#include "readFingers.h"
/*
    Constructor
*/
flexsensor::flexsensor(int pin, String location){
    m_pin = pin;
    m_location = location;

    initFlexSensor(m_pin);
}

/*
    Performs a measurement of the sensor and adds it to the median filter.
*/
void flexsensor::read(){
    float m = analogRead(m_pin);
    int a = getAngle(m);
    m_f.addSample(a);
}
/*
    Returns the median sensor reading value.
*/
float flexsensor::getMedian(){
    return m_f.getMedian();
}

/*
    Returns the location of the sensor.
*/
String flexsensor::getlocation(){
    return m_location;
}
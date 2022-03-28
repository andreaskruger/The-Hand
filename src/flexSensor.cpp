/**
 * This class file is used to create flex sensor objects that handle all reading
 * and filtering of each sensor signal.cha
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


int flexSensor::readMux(int channel){
  int controlPin[] = {s0, s1, s2, s3};

  int muxChannel[16][4]={
    {0,0,0,0}, //channel 0
    {1,0,0,0}, //channel 1
    {0,1,0,0}, //channel 2
    {1,1,0,0}, //channel 3
    {0,0,1,0}, //channel 4
    {1,0,1,0}, //channel 5
    {0,1,1,0}, //channel 6
    {1,1,1,0}, //channel 7
    {0,0,0,1}, //channel 8
    {1,0,0,1}, //channel 9
    {0,1,0,1}, //channel 10
    {1,1,0,1}, //channel 11
    {0,0,1,1}, //channel 12
    {1,0,1,1}, //channel 13
    {0,1,1,1}, //channel 14
    {1,1,1,1}  //channel 15
  };

  //loop through the 4 sig
  for(int i = 0; i < 4; i ++){
    digitalWrite(controlPin[i], muxChannel[channel][i]);
  }

  //read the value at the SIG pin
  int val = analogRead(SIG_PIN);

  //return the value
  return val;
}


/**
 * Performs a measurement of the sensor and adds it to the median filter.
 * @return a float with the median angle value.
*/

int flexSensor::getValue(){
    return readMux(m_pin);
}

float flexSensor::getAngle(){
    float angle = map(readMux(m_pin),calibrateOpen,calibrateClosed,calibrateOpen,calibrateClosed);
    m_f.addSample(angle);
    return m_f.getMedian();
}


/**
 * Helper method for getAngle().
 * Takes a reading at the voltage divider and returns a resistance.
 * @param pin the pin to take a reading from.
 * @return a float with the resistance of the flex sensor.
*/

void flexSensor::calibrate(int state){
    if(state == 1){
        calibrateOpen = readMux(m_pin);
    }
    if(state == 2){
        calibrateClosed = readMux(m_pin);
    }
}
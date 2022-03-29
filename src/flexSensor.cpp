/**
 * This class file is used to create flex sensor objects that handle all reading
 * and filtering of each sensor signal.cha
*/

#include <Arduino.h>
#include <SPI.h>
#include "Config.h"
#include "flexSensor.h"

/**
 * Constructor
 * @param channel the channel to which the flex sensor is connected to.
 * @param minimum_angle the minimum angle of flex sensor.
 * @param maximum_angle the maximum angle of flex sensor.
*/

flexSensor::flexSensor(int channel, int minimum_angle, int maximum_angle){
    m_channel = channel;
    min_angle = minimum_angle;
    //max_angle = maximum_angle;
}

flexSensor::flexSensor(int channel){
    m_channel = channel;
    min_angle = 0;
    max_angle = 90;
}

// Changes multiplexer to read from int channel and then returns the read value
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

int flexSensor::getValue(){
    return readMux(m_channel);
}


/**
 * Performs a measurement of the sensor and adds it to the median filter.
 * @return a float with the median angle value.
*/
float flexSensor::getAngle(){
    float angle = map(readMux(m_channel),calibrateOpen,calibrateClosed,min_angle,max_angle);
    m_f.addSample(angle);
    return m_f.getMedian();
}


// Calibrates the flex sensor, either the open or closed state depending on input
void flexSensor::calibrate(bool state){
    if(state == false){
        calibrateOpen = readMux(m_channel);
    }
    if(state == true){
        calibrateClosed = readMux(m_channel);
    }
}
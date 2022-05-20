/**
 * This class file is used to create potentiometer objects that handle all reading
 * and filtering of each sensor signal.
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
 * @param multipl boolean that states whether the potentiometer is connected to the multiplexer or directly to the esp32.
*/
potentiometer::potentiometer(int channel, int minimum_angle, int maximum_angle){
  multipl = true;
  m_channel = channel;
  min_angle = minimum_angle;
  max_angle = maximum_angle;
  calibrateM = 0;
}
potentiometer::potentiometer(int channel){
  multipl =  true;
  m_channel = channel;
  min_angle = -20;
  max_angle = 20;
  calibrateM = 0;
}
potentiometer::potentiometer(bool multiplexer, int pin, int minimum_angle, int maximum_angle){
  multipl = multiplexer;
  m_channel = pin;
  min_angle = minimum_angle;
  max_angle = maximum_angle;
  calibrateM = 0;
}
potentiometer::potentiometer(bool multiplexer, int pin){
  multipl = multiplexer;
  m_channel = pin;
  min_angle = -15;
  max_angle = 15;
  calibrateM = 0;
}

/**
 * Changes multiplexer to read from int channel and then returns the read value.
 * @return analog reading from multiplexer in input channel.
 * this method is taken from http://adam-meyer.com/arduino/CD74HC4067 under MIT-License.
*/
int potentiometer::readMux(int channel){
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

// Returns value read from multiplexer at given channel (for debugging purposes mainly)
int potentiometer::getValue(){
  if(multipl){
    return readMux(m_channel);
  }
  else{
    return analogRead(m_channel);
  }
}


/**
 * Performs a measurement of the sensor and adds it to the median filter.
 * @return a float with the median angle value.
*/
float potentiometer::getAngle(){
  float angle;
  if(multipl){
    angle = map(readMux(m_channel), calibrateMin, calibrateMax, min_angle, max_angle);
  }
  else{
    angle = map(analogRead(m_channel), calibrateMin, calibrateMax, min_angle, max_angle);
  }
  m_f.addSample(angle);
  return m_f.getMedian();
}


/**
 * Calibrates the potentiometer, either the min or  max state depending on input.
 * @return void
*/
void potentiometer::calibrate(bool state){
  if(multipl){
    for(int i = 0; i < 2*SAMPLES; i++){
      m_f.addSample(readMux(m_channel));
    }
  }
  else{
    for(int i = 0; i < 2*SAMPLES; i++){
      m_f.addSample(analogRead(m_channel));
    }
  }

  if(!state){
    calibrateMin = m_f.getMedian();
  }

  else{
    calibrateMin = m_f.getMedian();
  }
    
}

/**
 * @returns value of calibrateMax
*/
int potentiometer::getCalibrateMax(){
  return calibrateMax;
}

/**
 * @returns value of calibrateMin
*/
int potentiometer::getCalibrateMin(){
  return calibrateMin;
}

/**
 * sets value of calibrateMax
*/
void potentiometer::setCalibrateMax(int val){
  calibrateMax = val;
}

/**
 * sets value of calibrateMin
*/
void potentiometer::setCalibrateMin(int val){
  calibrateMin = val;
}

void potentiometer::calibrateMean(int delta_min, int delta_max){
  for(int i = 0; i < 2*SAMPLES; i++){
    m_f.addSample(readMux(m_channel));
  }
  calibrateM = m_f.getMedian();
  calibrateMin = calibrateMax - delta_min;
  calibrateMax = calibrateMin - delta_max;
}
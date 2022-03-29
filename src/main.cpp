#include <Arduino.h>
#include "TalkyBoi.h"
#include "config.h"
#include "flexSensor.h"
#include "potentiometer.h"


/*
const uint8_t thumbIP_Pin = ads1118.AIN_0;
const uint8_t thumbMCP_Pin =  ads1118.AIN_1;
const uint8_t f1PIP_Pin =  ads1118.AIN_2;			
const uint8_t f1MCP_Pin = ads1118.AIN_3;			
const int f2PIP_Pin = 36;
const int f2MCP_Pin = 39;
const int f3PIP_Pin = 32;
const int f3MCP_Pin = 33;
const int f4PIP_Pin = 34;
const int f4MCP_Pin = 35;
const int pinList[] = {thumbIP_Pin, thumbMCP_Pin, f1PIP_Pin, f1MCP_Pin, f2PIP_Pin, f2MCP_Pin, f3PIP_Pin, f3MCP_Pin, f4PIP_Pin, f4MCP_Pin};
const int sizeList = sizeof(pinList)/sizeof(int);
float fingerAngles[10] = {0,0,0,0,0,0,0,0,0,0};
int sendID = 0;
*/


int buttonRun = 0;
int state = 0;

flexSensor thumbIP = flexSensor(0);
flexSensor thumbMCP = flexSensor(1);
flexSensor f1PIP = flexSensor(2);
flexSensor f1MCP = flexSensor(3);
flexSensor f2PIP = flexSensor(4);
flexSensor f2MCP = flexSensor(5);
flexSensor f3PIP = flexSensor(6);
flexSensor f3MCP = flexSensor(7);
flexSensor f4PIP = flexSensor(8);
flexSensor f4MCP = flexSensor(9);

flexSensor pinList[] = {thumbIP, thumbMCP, f1PIP, f1MCP, f2PIP, f2MCP, f3PIP, f3MCP, f4PIP, f4MCP};
const int sizeList = sizeof(pinList)/sizeof(int);
float fingerAngles[10] = {0,0,0,0,0,0,0,0,0,0};

 // Initiates the ADC breakout board.
/*
void initBoard2(){
    ads1118.begin();    // Initialize board
    ads1118.setSamplingRate(ads1118.RATE_860SPS);   // highest sampling rate possible
    ads1118.setFullScaleRange(ads1118.FSR_4096);    // 12 bit
}
*/

void initBoard(){
  pinMode(s0, OUTPUT);
  pinMode(s1, OUTPUT);
  pinMode(s2, OUTPUT);
  pinMode(s3, OUTPUT);

  digitalWrite(s0, LOW);
  digitalWrite(s1, LOW);
  digitalWrite(s2, LOW);
  digitalWrite(s3, LOW);
}

int readMux(int channel){
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
 * Toggles the state of the microcontroller.
*/
void interuptFunc(){
  static unsigned long last_interuptTime = 0;
  unsigned long interupt_time = millis();
  if(interupt_time - last_interuptTime){
    if (buttonRun){
      buttonRun = 0;
      state = 0;
    }else{
      buttonRun = 1;
      state = 1;
    }
  }
  last_interuptTime = interupt_time;
}


void setup() {
  Serial.begin(115200);
  delay(100);
  // getMACAdress();                          //MAC adress is run for the WIFI to work, the OTHER wearers MAC adress shall be written in this code and vice versa.
  // init_wifi();                             // Initiate ESP_NOW
  initBoard();                             // Initiate breakout board                  
  //attachInterrupt(17, interuptFunc, HIGH); // interupt for start/stop button
  Serial.println("calibration 1");
  hej123.calibrate(false);
  delay(2000);
  Serial.println("calibration 2");
  delay(2000);
  hej123.calibrate(true);
  delay(2000);
  Serial.println("done");
}

void loop() {
  /*
  sendID++;

  send(sendID, fingerAngles[0], fingerAngles[1], fingerAngles[2], fingerAngles[3], fingerAngles[4], fingerAngles[5], fingerAngles[6], fingerAngles[7], fingerAngles[8], fingerAngles[9]);
  */
  /*int val1 = readMux(0);
  int val2 = readMux(1);
  Serial.print("val 1: ");
  Serial.print(val1);
  Serial.print(" val 2: ");
  Serial.println(val2);*/

  Serial.print(hej123.getValue());
  Serial.print(" // ");
  Serial.print(hej123.getAngle());
  Serial.print(" // ");
  Serial.print(hej123.getCalibrateOpen());
  Serial.print(" // ");
  Serial.println(hej123.getCalibrateClosed());
  delay(100);

}




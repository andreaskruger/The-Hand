#include <Arduino.h>
#include "TalkyBoi.h"

// Pin connected to voltage divider output. used for analogRead to get resistance of the flexsensors
const uint8_t thumbIP_Pin = ads1118.AIN_0;
const uint8_t thumbMCP_Pin = ads1118.AIN_1;
const uint8_t f1PIP_Pin = ads1118.AIN_2;			
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

int buttonRun = 0;
int state = 0;

/**
 * Initiates the ADC breakout board.
*/
void initBoard(){
    ads1118.begin();    // Initialize board
    ads1118.setSamplingRate(ads1118.RATE_860SPS);   // highest sampling rate possible
    ads1118.setFullScaleRange(ads1118.FSR_4096);    // 12 bit
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
  getMACAdress();                          //MAC adress is run for the WIFI to work, the OTHER wearers MAC adress shall be written in this code and vice versa.
  init_wifi();                             // Initiate ESP_NOW
  initBoard();                             // Initiate breakout board                  
  //attachInterrupt(17, interuptFunc, HIGH); // interupt for start/stop button
}

void loop() {
  /*
  sendID++;

  send(sendID, fingerAngles[0], fingerAngles[1], fingerAngles[2], fingerAngles[3], fingerAngles[4], fingerAngles[5], fingerAngles[6], fingerAngles[7], fingerAngles[8], fingerAngles[9]);
  */
  delay(100);
}




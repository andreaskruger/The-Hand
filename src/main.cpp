#include <Arduino.h>
#include <readFingers.h>
#include <talkyBoi.h>

#define interuptPin 16

// Pin connected to voltage divider output. used for analogRead to get resistance of the flexsensors
const uint8_t thumbIP_Pin = ads1118.AIN_1;
const uint8_t thumbMCP_Pin = ads1118.AIN_0;
const uint8_t f1PIP_Pin = ads1118.AIN_3;			
const uint8_t f1MCP_Pin = ads1118.AIN_2;			
const int f2PIP_Pin = 39;
const int f2MCP_Pin = 36;
const int f3PIP_Pin = 33;
const int f3MCP_Pin = 32;
const int f4PIP_Pin = 35;
const int f4MCP_Pin = 34;
const int pinList[] = {thumbMCP_Pin, thumbIP_Pin, f1MCP_Pin, f1PIP_Pin, f2MCP_Pin, f2PIP_Pin, f3MCP_Pin, f3PIP_Pin, f4MCP_Pin, f4PIP_Pin};
const int sizeList = sizeof(pinList)/sizeof(int);
float fingerAngles[10] = {0,0,0,0,0,0,0,0,0,0};

int sendID = 0;

int setupState = 0;
int state = 0;

// Number of samples for the median filter.
// More samples => larger delay
const int SAMPLE_WINDOW = 10;

// filter objects for all joints
MedianFilter<int, SAMPLE_WINDOW> mf_thumbIP;
MedianFilter<int, SAMPLE_WINDOW> mf_thumbMCP;
MedianFilter<int, SAMPLE_WINDOW> mf_f1PIP;			
MedianFilter<int, SAMPLE_WINDOW> mf_f1MCP;			
MedianFilter<int, SAMPLE_WINDOW> mf_f2PIP;
MedianFilter<int, SAMPLE_WINDOW> mf_f2MCP;
MedianFilter<int, SAMPLE_WINDOW> mf_f3PIP;
MedianFilter<int, SAMPLE_WINDOW> mf_f3MCP;
MedianFilter<int, SAMPLE_WINDOW> mf_f4PIP;
MedianFilter<int, SAMPLE_WINDOW> mf_f4MCP;
MedianFilter<int, SAMPLE_WINDOW> calibrateFilter;

// Initiate the breakout board
void initBoard(){
    ads1118.begin();    // Initialize board
    ads1118.setSamplingRate(ads1118.RATE_860SPS);   // highest sampling rate possible
    ads1118.setFullScaleRange(ads1118.FSR_4096);    // 12 bit
}

// Initiate the pins that 
void initAnalogPin(){
  pinMode(f2PIP_Pin, INPUT);  // maybe change later!
    pinMode(f2MCP_Pin, INPUT); 
    pinMode(f3PIP_Pin, INPUT);  
    pinMode(f3MCP_Pin, INPUT);
    pinMode(f4PIP_Pin, INPUT);
    pinMode(f4MCP_Pin, INPUT);
}

/**
 * Interupt function for the initial calibration.
*/
void interuptCalibrate(){
    static unsigned long last_interuptTime = 0;
  unsigned long interupt_time = millis();
  if((interupt_time - last_interuptTime) > 200){
    setupState++;
  }
  last_interuptTime = interupt_time;
}

/**
 * Interupt function for pausing the sampling during runtime.
*/
void interuptFunc(){
  static unsigned long last_interuptTime = 0;
  unsigned long interupt_time = millis();
  if((interupt_time - last_interuptTime) > 200){
    if (state){
      state = 0;
    }else{
      state = 1;
    }
  }
  last_interuptTime = interupt_time;
}

/**
 * Helper function for printing all current joint values.
*/
void printAllValues(){
  Serial.print(mf_thumbIP.getMedian() + " ");
  Serial.print(mf_thumbMCP.getMedian() + " ");
  Serial.print(mf_f1PIP.getMedian() + " ");
  Serial.print(mf_f1MCP.getMedian() + " ");
  Serial.print(mf_f2PIP.getMedian() + " ");
  Serial.print(mf_f2MCP.getMedian() + " ");
  Serial.print(mf_f3PIP.getMedian() + " ");
  Serial.print(mf_f3MCP.getMedian() + " ");
  Serial.print(mf_f4PIP.getMedian() + " ");
  Serial.println(mf_f4MCP.getMedian());
}

void setup() {
  Serial.begin(115200);
  delay(100);
  pinMode(interuptPin,INPUT_PULLDOWN);
  getMACAdress();                          //MAC adress is run for the WIFI to work, the OTHER wearers MAC adress shall be written in this code and vice versa.
  init_wifi();                             // Initiate ESP_NOW
  initBoard();                             // Initiate breakout board 
  initAnalogPin();                         // Initiate analog pins on ESP 

  Serial.println("Wating for calibration...");
  attachInterrupt(16,interuptCalibrate,RISING); //Interupt for calibration, start with open hand
  while(setupState<1){delay(10);}               //Hold hand open to calibrate flexsensors for an open hand
  for (int i = 0; i < sizeList; i++){
      for (int j = 0; j <= 2*SAMPLE_WINDOW; j++){
        delay(10);
        int res = readResistance(pinList[i],i);
        calibrateFilter.addSample(res);
        //Serial.print(res);
        //Serial.print(" ");
        //Serial.println(calibrateFilter.getMedian());
      }
      calibrate(calibrateFilter.getMedian(), i, 1);           //Located in readFingers, takes a pin, type(breakoutboard or ESP), pos which is the position in 
  }                                                             //calibrate array and state(open 1 and closed 2)
  Serial.println("Calibrate 1: done");

  while(setupState<2){delay(10);}
  for (int i = 0; i < sizeList; i++){
      for (int j = 0; j <= 2*SAMPLE_WINDOW; j++){
        delay(10);
        int res = readResistance(pinList[i],i);
        calibrateFilter.addSample(res);
        //Serial.print(res);
        //Serial.print(" ");
        //Serial.println(calibrateFilter.getMedian());
      }
      calibrate(calibrateFilter.getMedian(), i, 2);           //Located in readFingers, takes a pin, type(breakoutboard or ESP), pos which is the position in                                                               
  }                                                             //calibrate array and state(open 1 and closed 2)

  Serial.println("Calibrate 2: done");
  //delay(5000);
  Serial.print("Calibrating");
  Serial.print(". ");
  delay(300);
  Serial.print(". ");
  delay(300);
  Serial.println(". ");
  delay(300);
  Serial.println("Calibration done!");
  detachInterrupt(16);
  delay(10);
  attachInterrupt(16, interuptFunc, RISING); // interupt for start/stop button
}

void loop() {
  while(state){delay(10);}                                             //interupt for pin 16 button

  mf_thumbIP.addSample(getAngle(pinList[0], 0, 0));
  mf_thumbMCP.addSample(getAngle(pinList[1], 1, 1));;
  mf_f1PIP.addSample(getAngle(pinList[2], 2, 2));;			
  mf_f1MCP.addSample(getAngle(pinList[3], 3, 3));;			
  mf_f2PIP.addSample(getAngle(pinList[4], 4, 4));;
  mf_f2MCP.addSample(getAngle(pinList[5], 5, 5));;
  mf_f3PIP.addSample(getAngle(pinList[6], 6, 6));;
  mf_f3MCP.addSample(getAngle(pinList[7], 7, 7));;
  mf_f4PIP.addSample(getAngle(pinList[8], 8, 8));;
  mf_f4MCP.addSample(getAngle(pinList[9], 9, 9));;
  
  
  sendID++;

  send(sendID, mf_thumbIP.getMedian(), mf_thumbMCP.getMedian(), mf_f1PIP.getMedian(), mf_f1MCP.getMedian(), mf_f2PIP.getMedian(), mf_f2PIP.getMedian(), mf_f3PIP.getMedian(), mf_f3MCP.getMedian(), mf_f4PIP.getMedian(), mf_f4MCP.getMedian());
 /*
  Serial.print(mf_thumbIP.getMedian());
  Serial.print(" ");
  Serial.print(mf_thumbMCP.getMedian());
  Serial.print(" ");
  Serial.print(mf_f1PIP.getMedian());
  Serial.print(" ");
  Serial.print(mf_f1MCP.getMedian());
  Serial.print(" ");
  Serial.print(mf_f2PIP.getMedian());
  Serial.print(" ");
  Serial.print(mf_f2MCP.getMedian());
  Serial.print(" ");
  Serial.print(mf_f3PIP.getMedian());
  Serial.print(" ");
  Serial.print(mf_f3MCP.getMedian());
  Serial.print(" ");
  Serial.print(mf_f4PIP.getMedian());
  Serial.print(" ");
  Serial.println(mf_f4MCP.getMedian());
  */

  delay(10);
}




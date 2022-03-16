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
const int pinList[] = {thumbIP_Pin, thumbMCP_Pin, f1PIP_Pin, f1MCP_Pin, f2PIP_Pin, f2MCP_Pin, f3PIP_Pin, f3MCP_Pin, f4PIP_Pin, f4MCP_Pin};
const int sizeList = sizeof(pinList)/sizeof(int);
float fingerAngles[10] = {0,0,0,0,0,0,0,0,0,0};

int sendID = 0;
int o = 0;

int buttonRun = 0;
int state = 0;

const int SAMPLE_WINDOW = 10;

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

void initBoard(){
    ads1118.begin();    // Initialize board
    ads1118.setSamplingRate(ads1118.RATE_860SPS);   // highest sampling rate possible
    ads1118.setFullScaleRange(ads1118.FSR_4096);    // 12 bit
}

void initAnalogPin(){
  pinMode(f2PIP_Pin, INPUT);  // maybe change later!
    pinMode(f2MCP_Pin, INPUT); 
    pinMode(f3PIP_Pin, INPUT);  
    pinMode(f3MCP_Pin, INPUT);
    pinMode(f4PIP_Pin, INPUT);
    pinMode(f4MCP_Pin, INPUT);
}

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



void setup() {
  Serial.begin(115200);
  delay(100);
  pinMode(interuptPin,INPUT_PULLDOWN);
  getMACAdress();                          //MAC adress is run for the WIFI to work, the OTHER wearers MAC adress shall be written in this code and vice versa.
  init_wifi();                             // Initiate ESP_NOW
  initBoard();                             // Initiate breakout board 
  initAnalogPin();                         // Initiate analog pins on ESP                      
  attachInterrupt(16, interuptFunc, RISING); // interupt for start/stop button
}

void loop() {
  //while(!state){}                                             //Remove this comment to have a butten that locks/unlocks the program when it is run. Needs a debounce for the button before it works.
  
  /*for(int i = 0; i<sizeList; i++){                              //Reads all sensors and puts it in a list.
    filters[i].addSample(getAngle(pinList[i], i));
    Serial.print(String(fingerAngles[i]) + " ");
  }*/
  mf_thumbIP.addSample(getAngle(pinList[0], 0));
  mf_thumbMCP.addSample(getAngle(pinList[1], 1));;
  mf_f1PIP.addSample(getAngle(pinList[2], 2));;			
  mf_f1MCP.addSample(getAngle(pinList[3], 3));;			
  mf_f2PIP.addSample(getAngle(pinList[4], 4));;
  mf_f2MCP.addSample(getAngle(pinList[5], 5));;
  mf_f3PIP.addSample(getAngle(pinList[6], 6));;
  mf_f3MCP.addSample(getAngle(pinList[7], 7));;
  mf_f4PIP.addSample(getAngle(pinList[8], 8));;
  mf_f4MCP.addSample(getAngle(pinList[9], 9));;
  
  Serial.println();
  
  sendID++;

  send(sendID, mf_thumbIP.getMedian(), mf_thumbMCP.getMedian(), mf_f1PIP.getMedian(), mf_f1MCP.getMedian(), mf_f2PIP.getMedian(), mf_f2PIP.getMedian(), mf_f3PIP.getMedian(), mf_f3MCP.getMedian(), mf_f4PIP.getMedian(), mf_f4MCP.getMedian());

  delay(10);
}




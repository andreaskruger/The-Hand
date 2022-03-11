#include <Arduino.h>
#include <readFingers.h>
#include <talkyBoi.h>

#define interuptPin 17


// Pin connected to voltage divider output. used for analogRead to get resistance of the flexsensors
const int f1PIP_Pin = 36;			
const int f1MCP_Pin = 39;			
const int f2PIP_Pin = 32;
const int f2MCP_Pin = 33;
const int f3PIP_Pin = 34;
const int f3MCP_Pin = 35;
const int f4PIP_Pin = 32;
const int f4MCP_Pin = 32;
const int thumbIP_Pin = 32;
const int thumbMCP_Pin = 32;
const int pinList[] = {thumbIP_Pin, thumbMCP_Pin, f1PIP_Pin, f1MCP_Pin, f2PIP_Pin, f2MCP_Pin, f3PIP_Pin, f3MCP_Pin, f4PIP_Pin,f4MCP_Pin};
const int sizeList = sizeof(pinList)/sizeof(int);
float fingerAngles[10] = {0,0,0,0,0,0,0,0,0,0};
int sendID = 0;
int o = 0;

int buttonRun = 0;
int state = 0;

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
  getMACAdress();                                               //MAC adress är vad som körs för att WIFI ska funkar, den ANDRA bärands MAC adress ska skrivas in i denna koden och tvärtom.
  init_wifi();                                                  //Initierar ESP_NOW
  for(int i = 0; i<sizeList; i++){                              //Initierar alla flexsensorer vi vill använda. 
    initFlexSensor(pinList[i]);
  }
  attachInterrupt(17, interuptFunc, HIGH);                      // interupt för start/stopp knapp
}

void loop() {
  //while(!state){}                                             //Ta bort kommentar för att ha en knapp som låser/öppnar programmet när det körs. Behöver en  debounce för knappen innan det funkar.

  for(int i = 0; i<sizeList; i++){                              //Läser alla sensorer och lägger i en lista
    fingerAngles[i] = getAngle(pinList[i]);
  }
  sendID++;

  send(sendID, fingerAngles[0], fingerAngles[1], fingerAngles[2], fingerAngles[3], fingerAngles[4], fingerAngles[5], fingerAngles[6], fingerAngles[7], fingerAngles[8], fingerAngles[9]);
  
  sendToModel(o,1.0,1.0);
  o++;
  delay(1000);

}


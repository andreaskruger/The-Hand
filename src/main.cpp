#include <Arduino.h>
#include <readFingers.h>
#include <talkyBoi.h>

#define interuptPin = 17;

const int f1PIP_Pin = 32;			// Pin connected to voltage divider output for the 1st fingers PIP joint
const int f1MCP_Pin = 33;			// Pin connected to voltage divider output for the 1st fingers MCP joint
const int pinList[] = {5,8,12,13,10,11};
const int sizeList = sizeof(pinList)/sizeof(int);
float fingerAngles[9];
int sendID = 0;

int buttonRun = 0;
int state = 0;


void interuptFunc(){
  if (buttonRun){
    buttonRun = 0;
    state = 0;
  }else{
    buttonRun = 1;
    state = 1;
  }
}

void setup() {
  Serial.begin(115200);
  
  delay(100);
  getMACAdress();//MAC adress är vad som körs för att WIFI ska funkar, den ANDRA bärands MAC adress ska skrivas in i denna koden och tvärtom.
  init_wifi();//Initierar ESP_NOW
  for(int i = 0; i<sizeList; i++){ //Initierar alla flexsensorer vi vill använda. 
    initFlexSensor(pinList[i]);
  }
  attachInterrupt(17, interuptFunc, HIGH); // interupt för start/stopp knapp
}

void loop() {
  //while(!state){}  //Ta bort kommentar för att ha en knapp som låser/öppnar programmet när det körs. Behöver en  debounce för knappen innan det funkar.

  for(int i = 0; i<sizeList; i++){//Läser alla sensorer och lägger i en lista
    fingerAngles[i] = getAngle(pinList[i]);
  }

  sendID++;
  send(sendID, fingerAngles[0], fingerAngles[1], fingerAngles[2], fingerAngles[3], fingerAngles[4], fingerAngles[5], fingerAngles[6], fingerAngles[7], fingerAngles[8], fingerAngles[9]);
  delay(10);
}


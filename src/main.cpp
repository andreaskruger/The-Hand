#include <Arduino.h>
#include <readFingers.h>
#include <talkyBoi.h>

const int f1PIP_Pin = 32;			// Pin connected to voltage divider output for the 1st fingers PIP joint
const int f1MCP_Pin = 33;			// Pin connected to voltage divider output for the 1st fingers MCP joint
const int pinList[] = {5,8,12,13,10,11};
const int sizeList = sizeof(pinList)/sizeof(int);
float fingerAngles[8];

void setup() {
  Serial.begin(115200);
  
  delay(100);
  getMACAdress();
  init_wifi();
  for(int i = 0; i<sizeList; i++){
    initFlexSensor(pinList[i]);
  }
}

void loop() {
  fingerAngles[0] = getAngle();
  float angle1PIP = getAngle(f1PIP_Pin);
  float angle1MCP = getAngle(f1MCP_Pin);

  //for reading all flexsensors and creating a list to be send
  //float *pointer = getAngleList();
  //float newAngleList[] = {};

  //for(int i = 0; i < 10; i++){
  //  newAngleList[i] = *pointer;
  //  pointer++;
  //}

  //if we only want to test and sending via serial port this is simpler
  //int pins[] = {32};
  //for(int i = 0; i < sizeof(pins); i++){
  //      Serial.println( String( getAngle(readResistance(pins[i])) ) );
  //  }

 // Serial.println(String(angle1PIP) + " " + String(angle1MCP));

  send(angle1PIP, angle1MCP);
  Serial.print("PIP: ");
  Serial.println(angle1PIP);
  Serial.print("MCP: ");
  Serial.println(angle1MCP);

  delay(10);
}


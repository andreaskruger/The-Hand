#include <Arduino.h>
#include "TalkyBoi.h"
#include "config.h"
#include "flexSensor.h"
#include "potentiometer.h"
#include "display.h"

int sendID = 0;

int buttonRun = 0;
int state = 0;
int calibrateState = 0;

// Declaring all flexSensor objects
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

// Declaring all potentiometer objects
potentiometer f1AD = potentiometer(10);
potentiometer f2AD = potentiometer(11);
potentiometer f3AD = potentiometer(12);
potentiometer f4AD = potentiometer(13);

// Creating list of flexSensor and list of potetiometer objects
flexSensor pinList[] = {thumbIP, thumbMCP, f1PIP, f1MCP, f2PIP, f2MCP, f3PIP, f3MCP, f4PIP, f4MCP};
potentiometer potList[4] = {f1AD,f2AD,f3AD,f4AD};
const int sizeList = sizeof(pinList)/sizeof(int);
// List of angles of all joints in fingers
float fingerAngles[14] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0};

 // Initiates the multiplexer.
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

/*
 *  Takes in a given channel number and outputs a multiplexer reading from that given channel.
 */
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
 * Interupt function for the initial calibration.
*/
void interuptCalibrate(){
  static unsigned long last_interuptTime = 0;
  unsigned long interupt_time = millis();
  if((interupt_time - last_interuptTime) > 200){
    calibrateState++;
  }
  last_interuptTime = interupt_time;
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

void display_angle(potentiometer sensor){
  disp_setTextColor(WHITE);
  disp_println(sensor.getAngle());
}
void display_angle(flexSensor sensor){
  disp_setTextColor(WHITE);
  disp_println(sensor.getAngle());
}

/*Calibrates all 10 flex sensors for flexion movement. First hold hand open until OK 
  is printed and then have hand closed until OK is printed again */
void calibrateFlexion(){
  attachInterrupt(16,interuptCalibrate,RISING);
  Serial.println("Flexion Calibr.");
  disp_clr();
  disp_setTextColor(WHITE);
  disp_println("Flexion Calibr.");
  disp_println("----------------");
  Serial.println("HAND OPEN");
  disp_print("HAND OPEN");
  while(calibrateState < 1){delay(50);}
  for(int i = 0; i<10 ; i++){
    pinList[i].calibrate(false);
  }
  Serial.println("OK");
  disp_setTextColor(GREEN);
  disp_println(" OK");
  delay(100);
  disp_setTextColor(WHITE);
  disp_println("-----");
  Serial.println("HAND CLOSED");
  disp_print("HAND CLOSED");
  while(calibrateState < 2){delay(50);}
  for(int i = 0; i<10 ; i++){
    pinList[i].calibrate(true);
  }
  Serial.println("OK");
  disp_setTextColor(GREEN);
  disp_println(" OK");
  delay(100);
  disp_setTextColor(WHITE);
  disp_println("-----");
  delay(100);
  disp_println("CALIBRATION");
  disp_println("COMPLETE");
  while(calibrateState < 3){delay(50);}
  calibrateState = 0;
  disp_clr();
  attachInterrupt(17,interuptFunc,HIGH);
}

/* Calibrates potentiometers for measuring abduction and adduction of fingers.
   Each finger is calibrated individually with instructions printed on the display */
void calibrateAbduction(){
  attachInterrupt(16,interuptCalibrate,RISING);
  for(int i = 0; i < sizeof(potList)/sizeof(potList[i]); i++){
    disp_clr();
    disp_setTextColor(WHITE);
    disp_println("Abduct. Calibr.");
    disp_println("----------------");
    disp_print("keep F");
    disp_print(i+1);
    disp_println(" left");
    Serial.println("Abduct. Calibr.");
    Serial.print("keep F");
    Serial.print(i+1);
    Serial.println(" left");
    Serial.print(sizeof(potList));
    while(calibrateState < i+1){delay(50);}

    potList[i].calibrate(false);
    disp_setTextColor(GREEN);
    Serial.println("OK");
    disp_println("OK");
    delay(100);
    disp_setTextColor(WHITE);
    disp_println("-----");
    disp_print("keep F");
    disp_print(i+1);
    disp_println(" right");
    Serial.print("keep F");
    Serial.print(i+1);
    Serial.print(" right");
    while(calibrateState < i+2){delay(50);}

    potList[i].calibrate(true);
    disp_setTextColor(GREEN);
    disp_println("OK");
    Serial.println("OK");
    delay(100);
    disp_setTextColor(WHITE);
    disp_println("-----");
    delay(500);
  }
  disp_println("CALIBRATION");
  disp_println("COMPLETE");
  Serial.println("CALIBRATION COMPLETE");
  while(calibrateState < 3){delay(50);}
  calibrateState = 0;
  disp_clr();
  attachInterrupt(17,interuptFunc,HIGH);
}

void setup() {
  Serial.begin(115200);
  delay(100);
  // getMACAdress();                          //MAC adress is run for the WIFI to work, the OTHER wearers MAC adress shall be written in this code and vice versa.
  // init_wifi();                             // Initiate ESP_NOW
  initBoard();                             // Initiate breakout board        
  disp_initialize();                       // Initialise display
  attachInterrupt(17, interuptFunc, HIGH); // interupt for start/stop button
  calibrateFlexion();                       // Calibrate flextion movement of fingers
  calibrateAbduction();                     // Calibrate abduction and adduction movement of fingers
}

void loop() {

  /*
  sendID++;

  send(sendID, fingerAngles[0], fingerAngles[1], fingerAngles[2], fingerAngles[3], fingerAngles[4], fingerAngles[5], fingerAngles[6], fingerAngles[7], fingerAngles[8], fingerAngles[9]);
  */

}


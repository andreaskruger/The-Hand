#include <Arduino.h>
#include <readFingers.h>
#include <talkyBoi.h>

const int flexpin = 32;

void setup() {
  initFlexRead();
  Serial.begin(115200);
  delay(100);
  getMACAdress();
  init_wifi();
}

void loop() {


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

  Serial.println(String( getAngle(readResistance(flexpin)))  );
  send(getAngle(readResistance(flexpin)));

  delay(200);
}


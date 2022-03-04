#include <Arduino.h>
#include <readFingers.h>

const int f1PIP_Pin = 32;			// Pin connected to voltage divider output for the 1st fingers PIP joint
const int f1MCP_Pin = 33;			// Pin connected to voltage divider output for the 1st fingers MIP joint

void setup() {
  initFlexSensor(f1PIP_Pin);
  Serial.begin(115200);
}

void loop() {

  float angle1PIP = getAngle(f1PIP_Pin);


  delay(200);
}

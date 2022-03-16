/**
 * This script is only for the receiving ESP32!
 * Do not change anything here.
*/
#include <Arduino.h>
#include <talkyBoi.h>

void setup() {
  Serial.begin(115200);
  delay(100);
  getMACAdress();                          //MAC adress is run for the WIFI to work, the OTHER wearers MAC adress shall be written in this code and vice versa.
  init_wifi();                             // Initiate ESP_NOW
}

void loop() {
}




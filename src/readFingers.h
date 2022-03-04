#include <Arduino.h>
#include <ADS1118.h>
#include <SPI.h>


const int f1PIP_Pin = 32;			// Pin connected to voltage divider output for the 1st fingers PIP joint
int fingerpins[] = {32};

// Change these constants according to your project's design
const float VCC = 3.3;			// voltage at Ardunio 5V line
const float R_DIV = 100000.0;	// resistor used to create a voltage divider

void initFlexRead(){
    for(int i = 0; i < sizeof(fingerpins); i++){
        pinMode(fingerpins[i], INPUT);
    }
}

float readResistance(int pin){
    int ADCflex = analogRead(pin);

    float Vflex = ADCflex * VCC / 4095.0; //1023.0
    float Rflex = R_DIV * (VCC / Vflex - 1.0);
    return Rflex;
}

float getAngle(float resistance){
    float angle = resistance * 3.8 / 1000 - 102.5; //From Matlab calibration
}

float *getAngleList(){
    float angles[] = {};

    for(int i = 0; i < sizeof(fingerpins); i++){
        angles[i] = getAngle(readResistance(fingerpins[i]));
    }

    return angles;
}

void printAngleList(){
    Serial.println('Angle list: ');
    Serial.println(sizeof(fingerpins));
    delay(2000);

    for(int i = 1; i <= 1; i++){     // OBS hårdkodad!!!!!
        //Serial.println('index: ' + String(i) + ' Value: ' + String( getAngle(readResistance(pins[i])) ) );
       
        delay(1000);
        Serial.println('index: ' + String(i) + ' Value: ' + String(readResistance(fingerpins[i])));
    }

}
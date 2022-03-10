#include <Arduino.h>
#include "Filter.h"


const int flexPin1 = 4;			// Pin connected to voltage divider output
const int flexPin2 = 0;			// Pin connected to voltage divider output
float fingerAngles[2] = {0,0};
float fingerAnglesFiltered[2] = {0,0};
const int sizeList = 2;

// Change these constants according to your project's design
const float VCC = 5;			// voltage at Ardunio 5V line
const float R_DIV = 10000.0;	// resistor used to create a voltage divider

void setup() {
  Serial.begin(115200);
	pinMode(flexPin1, INPUT);
	pinMode(flexPin2, INPUT);
}


void loop() {
  
	// Calculate angle of fingers
    int ADCflex0 = analogRead(flexPin1);
    int ADCflex1 = analogRead(flexPin2);

    float Vflex0 = ADCflex0 * VCC / 4095.0; //1023.0
	float Vflex1 = ADCflex1 * VCC / 4095.0; //1023.0

    float Rflex0 = R_DIV * (VCC / Vflex0 - 1.0);
	float Rflex1 = R_DIV * (VCC / Vflex1 - 1.0);
    
	float angle0 = Rflex0 * 2.6716/1000 - 30.2045 -20; 
	float angle1 = Rflex1 * 2.6716/1000 - 30.2045 -20; 

	fingerAngles[0] = angle0;
	fingerAngles[1] = angle1;


	//Läser alla sensorer och lägger i en lista som sedan filtreras
	for(int i = 0; i<sizeList; i++){                            
    	fingerAnglesFiltered[i] = getFilteredAngle(fingerAngles[i], i);
  	}

	Serial.printf("%.3f, %.3f, %.3f, %.3f\n",fingerAnglesFiltered[0],fingerAnglesFiltered[1],fingerAngles[0],fingerAngles[1]);
}
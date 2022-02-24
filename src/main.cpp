#include <Arduino.h>
#include <MegunoLink.h>
#include <Filter.h>

const int flexPin = A0;			// Pin connected to voltage divider output

// Change these constants according to your project's design
const float VCC = 5;			// voltage at Ardunio 5V line
const float R_DIV = 1000.0;	// resistor used to create a voltage divider

long FilterWeight = 10;
ExponentialFilter<long> ADCFilter(FilterWeight,0);

void setup() {
	Serial.begin(9600);
	pinMode(flexPin, INPUT);
}

void loop() {
	// Read the ADC, and calculate voltage and resistance from it
	int ADCflex = analogRead(flexPin);

	ADCFilter.Filter(ADCflex);

	float Vflex = ADCFilter.Current() * VCC / 1023.0;
	float Rflex = R_DIV * (VCC / Vflex - 1.0);
	Serial.print(Rflex);

    Serial.write(13);
    Serial.write(10);
}
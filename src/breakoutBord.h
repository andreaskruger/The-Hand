
#include <Arduino.h>
#include "ADS1118.h"
#include <SPI.h>

//Definition of the Arduino pin to be used as the chip select pin (SPI CS pin). Example: pin 5
#define CS 5

//Creating an ADS1118 object (object's name is ads1118)
ADS1118 ads1118(CS);

int adcValue=0;//This is the value in the ADC output register
byte dummyByte;//Byte that does nothing but allows the conversion cycle to complete.
byte upperByte;//Most significant BIT
byte lowerByte;//Least significant BIT


const float VCC = 3.3;			// voltage at Ardunio 5V line
const float R_DIV = 100000.0;	// resistor used to create a voltage divider


void setup(){
    Serial.begin(115200);
    ads1118.begin(); //Initialize the ADS1118. Default setting: PULLUP RESISTOR, ADC MODE, RATE 8SPS, SINGLE SHOT, ±0.256V, DIFFERENTIAL AIN0-AIN1

    /* Changing the sampling rate. RATE_8SPS, RATE_16SPS, RATE_32SPS, RATE_64SPS, RATE_128SPS, RATE_250SPS, RATE_475SPS, RATE_860SPS*/
    ads1118.setSamplingRate(ads1118.RATE_8SPS);

    /* Changing the input selected. Differential inputs: DIFF_0_1, DIFF_0_3, DIFF_1_3, DIFF_2_3. Single ended input: AIN_0, AIN_1, AIN_2, AIN_3*/
    ads1118.setInputSelected(ads1118.AIN_0);

    /* Changing the full scale range. 
     *  FSR_6144 (±6.144V)*, FSR_4096(±4.096V)*, FSR_2048(±2.048V), FSR_1024(±1.024V), FSR_0512(±0.512V), FSR_0256(±0.256V).
     *  (*) No more than VDD + 0.3 V must be applied to this device. 
     */
    ads1118.setFullScaleRange(ads1118.FSR_4096);

  
    
  
}


void loop(){
    //int ADCflex = analogRead(ads1118.AIN_0);
    int16_t ADCflex = ads1118.getADCValue(ads1118.AIN_0);

    float Vflex = ADCflex * VCC / 4095.0; //1023.0
    //float Rflex = R_DIV * (VCC / Vflex - 1.0);

    Serial.println(String(Vflex));

    delay(200); //You can use a delay to save power. The ADS1118 will be in power down state during all the delay time. (Optional)
}

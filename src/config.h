/**
 * Configuration file for the entire project.
 * Define and change all constant variables here!
*/
#pragma once

// Connection for CS pin on ADC breakout board
#define CS_PIN 17 

// Change these constants according to your project's design
const float VCC = 5;			// Voltage that the sensors are connected to
const float R_DIV = 100000.0;	// Resistor used to create a voltage divider

// Number of samples for the median filter
const int SAMPLES = 20;

// Pin to the push button that turns the controller on
#define INTERUPT_PIN 16
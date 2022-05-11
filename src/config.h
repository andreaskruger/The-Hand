/**
 * Configuration file for the entire project.
 * Define and change all constant variables here!
*/
#pragma once

// Connection for pins on multiplexer
#define SIG_PIN 36
#define s0  26
#define s1  27
#define s2  14
#define s3  12

// Connection for pins on display
#define DISP_RES 1 
#define DISP_DC 15
#define DISP_CS 5
#define DISP_SCK 18
#define DISP_MOSI 23

// Number of samples for the median filter
const int SAMPLES = 20;

// Pin to the push button that turns the controller on
#define INTERUPT_PIN 17
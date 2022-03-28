/**
 * Configuration file for the entire project.
 * Define and change all constant variables here!
*/
#pragma once

// Connection for pins on multiplexer
#define SIG_PIN 34
#define s0  25
#define s1  26
#define s2  27
#define s3  14

// Number of samples for the median filter
const int SAMPLES = 20;

// Pin to the push button that turns the controller on
#define INTERUPT_PIN 16
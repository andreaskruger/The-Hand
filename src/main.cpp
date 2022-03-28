/**
 * This branch is for testing the screen.
 * Link to github repo with wiki, examples, and more fonts:
 * https://github.com/moononournation/Arduino_GFX
*/
#include <Arduino.h>
#include <Arduino_GFX_Library.h>
#include "FreeMono12pt7b.h"
#include "config.h"
#include "display.h"

#define RESETPIN 32
#define MODEPIN 33

void setup() {
  Serial.begin(115200);
  disp_initialize();
  delay(100);
}

void loop() {
  disp_clr();
  disp_setTextColor(WHITE);
  disp_println("testing screen in white");
  delay(1000);
  disp_setTextColor(RED);
  disp_println("testing display in red");
  delay(1000);
}




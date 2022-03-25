/**
 * This branch is for testing the screen.
 * Link to github repo with wiki, examples, and more fonts:
 * https://github.com/moononournation/Arduino_GFX
*/
#include <Arduino.h>
#include <Arduino_GFX_Library.h>
#include "FreeMono12pt7b.h"

// Screen setup
Arduino_DataBus *bus = new Arduino_ESP32SPI(33 /* DC */, 5 /* CS */, 18 /* SCK */, 23 /* MOSI */, -1 /* MISO */, VSPI /* spi_num */);
//Arduino_DataBus *bus = new Arduino_ESP32SPI(33 /* DC */, 5 /* CS */, 18 /* SCK */, 23 /* MOSI */, 19 /* MISO */);
Arduino_GFX *gfx = new Arduino_ST7789(bus, 7 /* RST */, 0 /* rotation */, true /* IPS */,
    240 /* width */, 240 /* height */, 0 /* col offset 1 */, 0 /* row offset 1 */);

#define RESETPIN 32
#define MODEPIN 33

void setup() {
  Serial.begin(115200);
  delay(100);

  // Screen setup
  pinMode(32, OUTPUT);
  pinMode(33, OUTPUT);
  digitalWrite(32, HIGH);         // Keep reset pin high
  digitalWrite(33, HIGH);          // Set data mode to "Command"
  gfx->begin();                   // Start the screen object
  gfx->fillScreen(BLACK);         // "Clear" the screen
  gfx->setCursor(5, 15);          // Set print pointer to top left corner
  gfx->setFont(&FreeMono12pt7b);  // Set font
  gfx->setTextColor(RED);         // Set color
  gfx->println("Hello world!");
  delay(1000);
}

void loop() {
  gfx->setCursor(1, 15);
  delay(1000);
  gfx->setTextColor(WHITE);
  gfx->println("White text");
  delay(1000);
  gfx->setTextColor(GREEN);
  gfx->println("Green text");
  delay(1000);
  gfx->setTextColor(YELLOW);
  gfx->println("Yellow text");
  delay(1000);
  gfx->setTextColor(BLUE);
  gfx->print("Mixed ");
  gfx->setTextColor(RED);
  gfx->println("text");
  delay(1000);

  // "Clear screen" and reset cursor to top left corner
  gfx->fillScreen(BLACK);
}




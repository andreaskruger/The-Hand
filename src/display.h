/*
 * This header file is for seting up the LCD-display and creating methods to easily control the display from the main class.
 */
#include <Arduino.h>
#include <Arduino_GFX_Library.h>
#include "FreeMono12pt7b.h"
#include "config.h"

// Screen setup
Arduino_DataBus *bus = new Arduino_ESP32SPI(DISP_DC /* DC */, DISP_CS /* CS */, DISP_SCK /* SCK */, DISP_MOSI /* MOSI */, -1 /* MISO */, VSPI /* spi_num */);
//Arduino_DataBus *bus = new Arduino_ESP32SPI(33 /* DC */, 5 /* CS */, 18 /* SCK */, 23 /* MOSI */, 19 /* MISO */);
Arduino_GFX *gfx = new Arduino_ST7789(bus, 7 /* RST */, 0 /* rotation */, true /* IPS */,
    240 /* width */, 240 /* height */, 0 /* col offset 1 */, 0 /* row offset 1 */);

// Initialises the display, must be called before using other methods.
void disp_initialize(){
    // Display setup
    pinMode(DISP_RES, OUTPUT);
    pinMode(DISP_DC, OUTPUT);
    digitalWrite(DISP_RES, HIGH);         // Keep reset pin high
    digitalWrite(DISP_RES, HIGH);          // Set data mode to "Command"
    gfx->begin();                   // Start the screen object
    gfx->fillScreen(BLACK);         // "Clear" the screen
    gfx->setCursor(5, 15);          // Set print pointer to top left corner
    gfx->setFont(&FreeMono12pt7b);  // Set font
}

// Clear display and reset cursor
void disp_clr(){
    gfx->fillScreen(BLACK);         // "Clear" the display
    gfx->setCursor(5, 15);          // Set print pointer to top left corner
}

// Print line of text on display
void disp_println(String string){   
    gfx->println(string);
}
void disp_println(int num){
    gfx->println(num);
}

// Print text on display
void disp_print(String string){     
    gfx->print(string);
}
void disp_print(int num){
    gfx->print(num);
}

// Set cursor location on display
void disp_setCursor(int16_t x, int16_t y){
    gfx->setCursor(x,y);
}

// Set colour of text on display
void disp_setTextColor(int16_t COLOR){
    gfx->setTextColor(COLOR);
}
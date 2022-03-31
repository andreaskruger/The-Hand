#include <Arduino.h>
#include <Arduino_GFX_Library.h>
#include "FreeMono12pt7b.h"
#include "config.h"

// Screen setup
Arduino_DataBus *bus = new Arduino_ESP32SPI(DISP_DC /* DC */, DISP_CS /* CS */, DISP_SCK /* SCK */, DISP_MOSI /* MOSI */, -1 /* MISO */, VSPI /* spi_num */);
//Arduino_DataBus *bus = new Arduino_ESP32SPI(33 /* DC */, 5 /* CS */, 18 /* SCK */, 23 /* MOSI */, 19 /* MISO */);
Arduino_GFX *gfx = new Arduino_ST7789(bus, 7 /* RST */, 0 /* rotation */, true /* IPS */,
    240 /* width */, 240 /* height */, 0 /* col offset 1 */, 0 /* row offset 1 */);

void disp_initialize(){
    // Screen setup
    pinMode(DISP_RES, OUTPUT);
    pinMode(DISP_DC, OUTPUT);
    digitalWrite(DISP_RES, HIGH);         // Keep reset pin high
    digitalWrite(DISP_RES, HIGH);          // Set data mode to "Command"
    gfx->begin();                   // Start the screen object
    gfx->fillScreen(BLACK);         // "Clear" the screen
    gfx->setCursor(5, 15);          // Set print pointer to top left corner
    gfx->setFont(&FreeMono12pt7b);  // Set font
}

// Clear screen and reset cursor
void disp_clr(){
    gfx->fillScreen(BLACK);         // "Clear" the screen
    gfx->setCursor(5, 15);          // Set print pointer to top left corner
}

// print line of text on screen
void disp_println(String string){   
    gfx->println(string);
}

// print text on screen
void disp_print(String string){     
    gfx->print(string);
}

// Set cursor location on screen
void disp_setCursor(int16_t x, int16_t y){
    gfx->setCursor(x,y);
}

void disp_setTextColor(int16_t COLOR){
    gfx->setTextColor(COLOR);
}
#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"

//pins from tft display
#define TFT_DC 9
#define TFT_CS 10
#define TFT_RST 8
#define TFT_MISO 12
#define TFT_MOSI 11
#define TFT_CLK 13

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_MOSI, TFT_CLK, TFT_RST, TFT_MISO);

//variables
int minutes = 37;
int sec = 59;

void setup() {
  Serial.begin(9600);
  Serial.println("ILI9341 Test!");

  tft.begin();

  // read diagnostics (optional but can help debug problems)
  uint8_t x = tft.readcommand8(ILI9341_RDMODE);
  Serial.print("Display Power Mode: 0x"); Serial.println(x, HEX);
  x = tft.readcommand8(ILI9341_RDMADCTL);
  Serial.print("MADCTL Mode: 0x"); Serial.println(x, HEX);
  x = tft.readcommand8(ILI9341_RDPIXFMT);
  Serial.print("Pixel Format: 0x"); Serial.println(x, HEX);
  x = tft.readcommand8(ILI9341_RDIMGFMT);
  Serial.print("Image Format: 0x"); Serial.println(x, HEX);
  x = tft.readcommand8(ILI9341_RDSELFDIAG);
  Serial.print("Self Diagnostic: 0x"); Serial.println(x, HEX);

  Serial.println(F("Done!"));
  uint8_t rotation = 3;
  tft.setRotation(rotation);
}


void loop(void) {
  for (int i = 59; i > 0; i--) {
    sec--;
    testCountdown();
    delay(1000);
  }
}


unsigned long testCountdown() {
  tft.fillScreen(ILI9341_BLACK);
  //unsigned long start = micros();

  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(10);
  tft.println(String(minutes) + ":" + String(sec));
  tft.println();
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(2);
  tft.println("Time adjusted: ");

  //return micros() - start;
}

void printText(char *text, uint16_t color, int x, int y,int textSize)
{
  tft.setCursor(x, y);
  tft.setTextColor(color);
  tft.setTextSize(textSize);
  tft.setTextWrap(true);
  tft.print(text);
}

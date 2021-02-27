#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"

//Pins for display
#define TFT_DC 9
#define TFT_CS 10
//#define TFT_RST 8 //denne settes i stedet direktet til 3.3V

// Use hardware SPI (on Uno, #13 - SCK, #12 - MISO, #11 - MOSI) and the above for CS/DC
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);

//TIMER VARIABLES
//Start and end time (do not format ie 03)
int storedSeconds = 0;
int storedMinutes = 38;

const int stopPin = 2;
const int resetPin = 3;
const int triggerPin = 4;

//this stores last time millis was fired (second time keeping)
unsigned long time;

//running seconds (do not change)
int seconds = storedSeconds;
int minutes = storedMinutes;

//store the last time value to check if we should write to screen more efficiently
int lastSeconds = seconds;
int lastMinutes = minutes;

//number buffer for formatting
char minbuf[3];
char secbuf[3];


void setup() {
  pinMode(stopPin, INPUT);
  pinMode(resetPin, INPUT);
  pinMode(triggerPin, OUTPUT);

  Serial.begin(9600);
  while (!Serial) ; // wait for Arduino Serial Monitor
  Serial.println(F("ILI9341 Test!"));

  tft.begin();

  // read diagnostics (optional but can help debug problems)
  uint8_t x = tft.readcommand8(ILI9341_RDMODE);
  Serial.print(F("Display Power Mode: 0x")); Serial.println(x, HEX);
  x = tft.readcommand8(ILI9341_RDMADCTL);
  Serial.print(F("MADCTL Mode: 0x")); Serial.println(x, HEX);
  x = tft.readcommand8(ILI9341_RDPIXFMT);
  Serial.print(F("Pixel Format: 0x")); Serial.println(x, HEX);
  x = tft.readcommand8(ILI9341_RDIMGFMT);
  Serial.print(F("Image Format: 0x")); Serial.println(x, HEX);
  x = tft.readcommand8(ILI9341_RDSELFDIAG);
  Serial.print(F("Self Diagnostic: 0x")); Serial.println(x, HEX);

  time = millis(); //Start internal countdown
  int rotation = 3;
  tft.setRotation(rotation);
  defaultScreen();

}


void loop(void) {
  //Stop the timer when stop is pressed
  if (digitalRead(stopPin) == HIGH) {
    time = millis();
  }

  //reset timer
  if (digitalRead(resetPin) == HIGH) {
    resetTimer();
    digitalWrite(triggerPin, HIGH);
  }

  //Every second render the timer
  if ((millis() - time) >= 1000) {
    checkTime();
  }

}

unsigned long printText(String text, uint16_t xpos, uint16_t ypos, uint8_t textSize, uint16_t textColor) {
  unsigned long start = micros();
  tft.setCursor(xpos, ypos);
  tft.setTextColor(textColor);
  tft.setTextSize(textSize);
  tft.println(text);
  return micros() - start;
}

//Check if time has reached 0
void checkTime() {
  if (!(seconds == 0 && minutes == 0)) {
    renderTime();
  } else {
    fail(); //time is zero, do something
  }
}

void renderTime() {
  time = millis(); //reset internal second countdown

  //when seconds reach 0 subtract from minutes
  if (seconds == 0 && minutes != 0) {
    seconds = 60;
    minutes--;
  }
  seconds--;

  //only paint over seconds if there is a change in second
  if (lastSeconds != seconds) {
    tft.fillRect(164, 0, 143, 91, ILI9341_BLACK); //paint a black square over past seconds
  }
  //only paint over minutes if there is a change in minute
  if (lastMinutes != minutes) {
    tft.fillRect(0, 0, 143, 91, ILI9341_BLACK); //paint a black square over past minutes
  }
  sprintf(secbuf, "%02d", seconds); //using sprintf to format our time correctly (ie 01 instead of just 1)
  sprintf(minbuf, "%02d", minutes);
  printText(minbuf, 0, 0, 13, ILI9341_WHITE);
  printText(secbuf, 164, 0, 13, ILI9341_WHITE); //line 2 text
  lastSeconds = seconds;
  lastMinutes = minutes;
}

void fail() {
  digitalWrite(triggerPin, HIGH);
}

//reset the timer
void resetTimer() {
  seconds = storedSeconds;
  minutes = storedMinutes;
  checkTime();
}

//What's on the screen
unsigned long defaultScreen() {
  tft.fillScreen(ILI9341_BLACK);
  unsigned long start = micros();
  printText(":", 121, 0, 13, ILI9341_WHITE); //line 2 text
  printText("Time adjusted: ", 0, 180, 2, ILI9341_WHITE);
  timeadjustments();
  return micros() - start;
}
//for textsize 2, pixelwidth including 2 pixel spacing:
uint8_t digit = 12; 
uint8_t doubleDigit = 24;
uint8_t negDigit = 24;
uint8_t doubleNegDigit = 36;
uint8_t barWidth = 4;

unsigned long timeadjustments() {
  unsigned long start = micros();
  tft.fillRect(0, 200, 300, 20, ILI9341_BLACK); //paint a black square over past adjustments
  int adjustments[] = {5, 22, -5, -20,18,5,-5};
  int size = sizeof(adjustments) / 2; //size of array
  printText("|", 0, 200, 2, ILI9341_WHITE); //prints first bar
  int xpos = 6; //express the x position of timeadjustment

  for (int i = 0; i < size; i++) {//goes through adjustments array
    if (adjustments[i] >= 0 && adjustments[i] < 10) {//numbers from 0-9
      printText(String(adjustments[i]), xpos + 4, 200, 2, ILI9341_GREEN);
      printText("|", xpos + digit , 200, 2, ILI9341_WHITE);
      xpos += digit + barWidth;
    }
    else if (adjustments[i] >= 10) {//numbers over 9
      printText(String(adjustments[i]), xpos + 4, 200, 2, ILI9341_GREEN);
      printText("|", xpos + doubleDigit, 200, 2, ILI9341_WHITE);
      xpos += doubleDigit + barWidth;
    }
    else if (adjustments[i] < 0 && adjustments[i] > -10) { //negative numbers from 0-9
      printText(String(adjustments[i]), xpos + 4, 200, 2, ILI9341_RED);
      printText("|", xpos + negDigit, 200, 2, ILI9341_WHITE);
      xpos += negDigit + barWidth;
    }
    else if (adjustments <= -10) {
      printText(String(adjustments[i]), xpos + 4, 200, 2, ILI9341_RED);
      printText("|", xpos + doubleNegDigit, 200, 2, ILI9341_WHITE);
      xpos += doubleNegDigit + barWidth;
    }
  }
  return micros() - start;
}

//Nødvendige bibliotek for Arduino Due
#include <SPI.h>
#include <ILI9341_due_config.h>
#include <ILI9341_due.h>
#include <fonts\allFonts.h>

//Bibliotek for radiokommunikasjon
#include <nRF24L01.h>
#include <RF24.h>

//DISPLAY 1: 
#define TFT_RST 22 //RST is connected to pin 22 
#define TFT_DC 23 //DC is connected to pin 23
#define TFT_CS 4 //CS is connected to pin 4
//Use hardware SPI for MISO, MOSI and CLK, https://www.arduino.cc/en/Reference/SPI
ILI9341_due tftA = ILI9341_due(TFT_CS, TFT_DC, TFT_RST);

//DISPLAY 2
#define TFT_RST2 24 //RST is connected to pin 24
#define TFT_DC2 25 //DC is connected to pin 25
#define TFT_CS2 10 //CS is connected to pin 10
//Use hardware SPI for MISO, MOSI and CLK, https://www.arduino.cc/en/Reference/SPI
ILI9341_due tftB = ILI9341_due(TFT_CS2, TFT_DC2, TFT_RST2);

#include "logo.h" //Headerfile that contains the data for the logo that is displayen when the Hub is turned on.

//THINKING TIME VARIABLES FOR TEAM A
int storedSecondsA = 01; //We set seconds to 1 to begin with since the timer counts down 1 second the first time the thinking times is displayed.
int storedMinutesA = 38;

//THINKING TIME VARIABLES FOR TEAM A
int storedSecondsB = 01;//We set seconds to 1 to begin with since the timer counts down 1 second the first time the thinking times is displayed.
int storedMinutesB = 38;

//This stores last time millis was fired (second time keeping)
unsigned long TimeA;
unsigned long TimeB;

//Running seconds and minutes for team A
int secondsA = storedSecondsA;
int minutesA = storedMinutesA;

//Running seconds and minutes for team B
int secondsB = storedSecondsB;
int minutesB = storedMinutesB;

//Store the last time value to check if we should write to screen more efficiently
int lastSecondsA = secondsA;
int lastMinutesA = minutesA;
int lastSecondsB = secondsB;
int lastMinutesB = minutesB;

//Number buffer for formatting
char minbuf[3];
char secbuf[3];

//Arrays of adjustments for each team
const int arrayLength = 20; //Defines max length of array to be 20
int adjustmentsA[arrayLength] = {};
int adjustmentsB[arrayLength] = {};
int adjustmentsIndexA = 0; 
int adjustmentsIndexB = 0;

//Variables for buttons and leds for team A
const int startPinA = 29; //Start button for team A is connected to pin 29 on Due
const int stopPinA = 33; //Stop button for team A is connected to pin 33 on Due
const int ledA = 28; //Red LED is connected to pin 28
bool startPinAon = false; //Is true when time is running for team A
bool stopPinAon = true; //Is true when time is not running for team A

//Variables for buttons and leds for team B
const int startPinB = 26; //Start button for team B is connected to pin 26 on Due
const int stopPinB = 27; //Stop button for team B is connected to pin 27 on Due
const int ledB = 31; //Yellow LED is connected to pin 28
bool startPinBon = false; //Is true when time is running for team B
bool stopPinBon = true; //Is true when time is not running for team B

//Variables for rotary encoder
const int encoderDT = 2; //DT is connected to pin 2
const int encoderCLK = 3; //CLK is connected to pin 3
const int encoderSW = 32; //SW is connected to pin 32
int REpushCount = -1;     //How many times the button on the rotary encoder has been pushed
volatile int encoderValue = 0; //Stores the value of the encoder when rotated
int lastEncoderValue = encoderValue; //Stores the last value of the encoder 
bool encoderIsActive = false; //Is true when the button on the encoder is pushed and time is being adjusted

//Debounce button on rotary encoder
long debouncing_time = 200; //Debouncing time in milliseconds
volatile unsigned long last_micros = 0; //Holds the micros()-time for when the button was last pushed

ILI9341_due chosenDisplay = tftA; //Is either tftA or tftB depending on what display is chosen when adjusting time
bool Display = 0; //0 for display A, and 1 for display B


//Setup for radio comunications
#define CE_PIN 40 //CE is connected to pin 40
#define CSN_PIN 41 //CSN is connected to pin 41
const byte thisSlaveAddress[6] = "00001"; //Address that the two NRF-modules communicate on
RF24 radio(CE_PIN, CSN_PIN); 
int dataReceived; //This must match dataToSend in the TX
bool newData = false;

const int wifiLED = 12; //Blue LED is connected to pin 12


void setup()
{
  Serial.begin(9600); //Starts serial communication for debugging when Due is connected to a computer
  Serial3.begin(9600); //Serial port for ESP communication
  while (!Serial); // wait for Arduino Serial Monitor
  while (!Serial3); // wait for Serial 3

  //Display setup
  SPI.begin(); //Start SPI communication
  tftA.begin(); //Start communication with displayA
  tftB.begin(); //Start communication with displayA

  tftA.setRotation((iliRotation)3); //Rotates display, can be 1-4
  tftB.setRotation((iliRotation)1); //Rotates display, can be 1-4

  //Display logo on both screens for 3 seconds, uses data from the logo.h-file
  tftA.drawImage(logocurlwatch_2, 0, 0, logocurlwatch_2Width, logocurlwatch_2Height);
  tftB.drawImage(logocurlwatch_2, 0, 0, logocurlwatch_2Width, logocurlwatch_2Height);
  delay(3000);

  //Buttons and LED setup
  pinMode(startPinA, INPUT);
  pinMode(stopPinA, INPUT);
  pinMode(ledA, OUTPUT);
  pinMode(startPinB, INPUT);
  pinMode(stopPinB, INPUT);
  pinMode(ledB, OUTPUT);
  pinMode(wifiLED, OUTPUT);

  //Rotary encoder setup
  pinMode(encoderSW, INPUT_PULLUP);  // turn on pull-up resistor
  pinMode(encoderDT, INPUT_PULLUP);  // turn on pull-up resistor
  pinMode(encoderCLK, INPUT_PULLUP); // turn on pull-up resistor

  //Interrupts for buttons
  attachInterrupt(digitalPinToInterrupt(startPinA), startA, RISING);       //StartButtonA
  attachInterrupt(digitalPinToInterrupt(stopPinA), stopA, RISING);         //StopButtonA
  attachInterrupt(digitalPinToInterrupt(startPinB), startB, RISING);       //StartButtonB
  attachInterrupt(digitalPinToInterrupt(stopPinB), stopB, RISING);         //StopButtonB
  
  //Interrupts for rotary encoder
  attachInterrupt(digitalPinToInterrupt(encoderDT), encoderRotation, CHANGE); //Change in rotation
  attachInterrupt(digitalPinToInterrupt(encoderSW), encoderDebounce, RISING); //Button

  defaultScreen(); //Runs function that displays the deafualt screen

  TimeA = millis(); //Start internal countdown for team A
  TimeB = millis(); //Start internal countdown for team B

  //Setup radio communication
  radio.begin();
  radio.setDataRate( RF24_250KBPS );
  radio.openReadingPipe(0, thisSlaveAddress);
  radio.startListening(); //Starts listening for incoming data

  digitalWrite(wifiLED, LOW); //turns off blue wifi LED
}

//Setup for ESP communication
char Stime[] = "00:0000:00000"; //Char array with current time and status, to send to ESP
char A = '0';
char B = '0';
char upd = '0';


void loop(void)
{
  byte IncomingByte = 0; //IncomingByte is set to 1 when ESP and Due have a connection
  boolean ByteReady = false;

  while (Serial3.available()) {
    IncomingByte = Serial3.read();
    ByteReady = true;
  }
  upd = 0;
  if (startPinAon == true) {
    A = '1';
    upd = '1';
  }
  if (startPinBon == true) {
    B = '1';
    upd = '1';
  }
  if (stopPinAon == true) {
    A = '0';
    upd = '1';
  }
  if (stopPinBon == true) {
    B = '0';
    upd = '1';
  }
  sprintf(secbuf, "%02d", secondsA); //Stime is updated with the current time (er nok penere måter å gjøre dette på)
  sprintf(minbuf, "%02d", minutesA);
  Stime[0] = minbuf[0];
  Stime[1] = minbuf[1];
  Stime[3] = secbuf[0];
  Stime[4] = secbuf[1];
  sprintf(secbuf, "%02d", secondsB);
  sprintf(minbuf, "%02d", minutesB);
  Stime[5] = minbuf[0];
  Stime[6] = minbuf[1];
  Stime[8] = secbuf[0];
  Stime[9] = secbuf[1];

  Stime[10] = A;
  Stime[11] = B;
  Stime[12] = upd;

  //STATUS:
  //sender alltid update = 1, selv når ikke noe er nytt
  //Sendes ellers riktig, men ESP leser det feil, og leser alt som true.


  //Time is sent to the ESP if there is a connection
  if (ByteReady == 1 ) {
    Serial3.write(Stime, 14);
    digitalWrite(wifiLED, HIGH);
  }

  //Radio communication
  if (!encoderIsActive && radio.available()) { //If time is not being adjusted and data is received
    getData();
    showData();
  }

  //Every second check and render timerA
  if (encoderIsActive == false && startPinAon == true && stopPinAon == false) {
    if ((millis() - TimeA) >= 1000)    {
      checkTime(secondsA, minutesA, lastSecondsA, lastMinutesA, TimeA, tftA);
    }
  }


  //Every second check and render timerB
  if (encoderIsActive == false && startPinBon == true && stopPinBon == false) {
    if ((millis() - TimeB) >= 1000)
    {
      checkTime(secondsB, minutesB, lastSecondsB, lastMinutesB, TimeB, tftB);
    }
  }
}

//This is called when start button for team A is pressed
void startA() {
  if (encoderIsActive == false) { //Check that time is not being adjusted 
    stopB();
    digitalWrite(ledA, HIGH); //Turn on red LED
    startPinAon = true;
    stopPinAon = false;
  }
}

//What happens when start button for team B is pressed
void startB() {
  if (encoderIsActive == false) { //Check that time is not being adjusted 
    stopA();
    digitalWrite(ledB, HIGH); //Turn on yellow LED
    startPinBon = true;
    stopPinBon = false;
  }

}

//What happens when stop button for team A is pressed
void stopA() {
  digitalWrite(ledA, LOW); //Turn off red LED
  startPinAon = false;
  stopPinAon = true;
}

//What happens when stop button for team B is pressed
void stopB() {
  digitalWrite(ledB,  LOW); //Turn off yellow LED
  startPinBon = false;
  stopPinBon = true;
}

//Check if time has reached 0
void checkTime(int& seconds, int& minutes, int& lastSeconds, int& lastMinutes, unsigned long& Time, ILI9341_due& screen) {
  if (!(seconds == 0 && minutes == 0))  {
    renderTime(seconds, minutes, lastSeconds, lastMinutes, Time, screen);
  }
  else  {
    //Time is zero, nothing special happens
  }
}

//Upates the display with correct time when called
void renderTime(int& seconds, int& minutes, int& lastSeconds, int& lastMinutes, unsigned long& Time, ILI9341_due& screen) {
  Time = millis(); //reset internal second countdown

 //Updates seconds and minutes
  while (seconds > 60) { 
    seconds -= 60;
    minutes++;
  }
  while (seconds < 0) { 
    seconds += 60;
    minutes--;
  }

  //When seconds reach 0 subtract from minutes
  if (seconds == 0 && minutes != 0)  {
    seconds = 60;
    minutes--;
  }
  seconds--;


  //Only paint a black square over seconds if there is a change in second
  if (lastSeconds != seconds)  {
    screen.fillRect(164, 0, 155, 125, ILI9341_BLACK); //paint a black square over past seconds. The function fillRect() is defined in the ILI9341_due library
  }
  //only paint over minutes if there is a change in minute
  if (lastMinutes != minutes)  {
    screen.fillRect(0, 0, 155, 125, ILI9341_BLACK); //paint a black square over past minutes
  }
  sprintf(secbuf, "%02d", seconds); //using sprintf to format our time correctly (ie 01 instead of just 1)
  sprintf(minbuf, "%02d", minutes);
  printText(minbuf, 0, 0, 11, ILI9341_WHITE, screen); //Prints updated time to the correct display. The function printText is defined below
  printText(secbuf, 164, 0, 11, ILI9341_WHITE, screen); 
  lastSeconds = seconds; //Updated lastSeconds
  lastMinutes = minutes; //Updated lastMinutes
}

//Prints out default text on the displayes when called
unsigned long defaultScreen() {
  tftA.fillScreen(ILI9341_BLACK); //Paint whole screen black
  tftB.fillScreen(ILI9341_BLACK);

  unsigned long start = micros();

  //Display 1
  renderTime(secondsA, minutesA, lastSecondsA, lastMinutesA, TimeA, tftA);
  printText(":", 156, 25, 7, ILI9341_WHITE, tftA); //Prints colon between the minutes and the seconds
  printText("Time adjusted: ", 0, 180, 2, ILI9341_WHITE, tftA); //Print text at the lower part of the screen

  //Display 2
  renderTime(secondsB, minutesB, lastSecondsB, lastMinutesB, TimeB, tftB);
  printText(":", 156, 25, 7, ILI9341_WHITE, tftB); //Prints colon between the minutes and the seconds
  printText("Time adjusted: ", 0, 180, 2, ILI9341_WHITE, tftB); //Print text at the lower part of the screen

  return micros() - start;
}


//Variables for calculating positions for numbers in time adjustments for textsize 2. Pixelwidth including 2 pixel spacing on each side:
int digit = 14;
int doubleDigit = 32;
int trippleDigit = 50;
int negDigit = 26;
int doubleNegDigit = 44;
int trippleNegDigit = 60;
int barWidth = 4;
int textSize = 2;
//Function to add adjusted time to the screen
unsigned long timeadjustments(int adjustments[], ILI9341_due& screen) {
  unsigned long start = micros();
  int xpos = 6;     //express the x position of timeadjustment
  int ypos = 210;   //express the y position of timeadjustment

  screen.fillRect(0, ypos, 300, 20, ILI9341_BLACK); //paint a black square over past adjustments w=300, h=20
  printText("|", 0, ypos - 3, textSize, ILI9341_WHITE, tftA); //prints first bar

  for (int i = 0; i < arrayLength; i++) { //goes through the numbers in the adjustment array
    //Wont write 0's out
    if (adjustments[i] == 0)    {
      continue;
    }

    //numbers from 0-9
    else if (adjustments[i] >= 0 && adjustments[i] < 10) {
      printText(String(adjustments[i]), xpos, ypos, textSize, ILI9341_SPRINGGREEN, screen); //Print out time adjustment
      printText("|", xpos + digit, ypos - 3, textSize, ILI9341_WHITE, screen); //Print bar to the right of number
      xpos += digit + barWidth; //Update xpos
    }

    //numbers from 10-99
    else if (adjustments[i] >= 10 && adjustments[i] < 100)    {
      printText(String(adjustments[i]), xpos, ypos, textSize, ILI9341_SPRINGGREEN, screen); //Print out time adjustment
      printText("|", xpos + doubleDigit, ypos - 3, textSize, ILI9341_WHITE, screen); //Print bar to the right of number
      xpos += doubleDigit + barWidth; //Update xpos
    }

    //numbers from 100-999
    else if (adjustments[i] >= 100)    {
      printText(String(adjustments[i]), xpos, ypos, textSize, ILI9341_SPRINGGREEN, screen); //Print out time adjustment
      printText("|", xpos + trippleDigit, ypos - 3, textSize, ILI9341_WHITE, screen); //Print bar to the right of number
      xpos += trippleDigit + barWidth; //Update xpos
    }

    //negative numbers from 0-9
    else if (adjustments[i] < 0 && adjustments[i] > -10)    {
      printText(String(adjustments[i]), xpos, ypos, textSize, ILI9341_RED, screen); //Print out time adjustment
      printText("|", xpos + negDigit, ypos - 3, textSize, ILI9341_WHITE, screen); //Print bar to the right of number
      xpos += negDigit + barWidth; //Update xpos
    }

    //negativ numbers from 10-99
    else if (adjustments[i] <= -10 && adjustments[i] > -100)    {
      printText(String(adjustments[i]), xpos, ypos, textSize, ILI9341_RED, screen); //Print out time adjustment
      printText("|", xpos + doubleNegDigit, ypos - 3, textSize, ILI9341_WHITE, screen); //Print bar to the right of number
      xpos += doubleNegDigit + barWidth; //Update xpos
    }

    //negativ numbers from 100-999
    else if (adjustments[i] <= -100)    {
      printText(String(adjustments[i]), xpos, ypos, textSize, ILI9341_RED, screen); //Print out time adjustment
      printText("|", xpos + trippleNegDigit, ypos - 3, textSize, ILI9341_WHITE, screen); //Print bar to the right of number
      xpos += trippleNegDigit + barWidth; //Update xpos
    }
  }
  return micros() - start;
}

//Function to print text to the screen
unsigned long printText(String text, uint16_t xpos, uint16_t ypos, uint8_t textSize, uint16_t textColor, ILI9341_due screen) {
  unsigned long start = micros();
  screen.cursorToXY(xpos, ypos); //Point where text should start
  screen.setFont(Arial14); //Set font
  screen.setTextColor(textColor); //Set text color
  screen.setTextScale(textSize); //Set text size
  screen.println(text); //Print text to screen with
  return micros() - start;
}

//NRF radio communication to check if there is new data
void getData() {
  if ( radio.available() ) {
    radio.read( &dataReceived, sizeof(dataReceived) );
    newData = true;
  }
}

//If data is received the time for both teams stops by calling the function stopTimeForBothTeams which is decleared in RotaryEncoder.ino
void showData() {
  if (newData == true) {
    //Serial.print("Data received ");
    //Serial.println(dataReceived);
    if (dataReceived == 0) { //If hack sensor is pushed and then released the time stops for both teams
      stopTimeForBothTeams();
    }
    newData = false;
  }
}

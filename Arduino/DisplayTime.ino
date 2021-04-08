//Nødvendige bibliotek for Arduino Due
#include <SPI.h>
#include <ILI9341_due_config.h>
#include <ILI9341_due.h>
#include <fonts\allFonts.h>

//Bibliotek for radiokommunikasjon
#include <nRF24L01.h>
#include <RF24.h>

//DISPLAY 1
#define TFT_RST 22
#define TFT_DC 23
#define TFT_CS 4
// Use hardware SPI and the above for CS/DC, https://www.arduino.cc/en/Reference/SPI
ILI9341_due tft = ILI9341_due(TFT_CS, TFT_DC, TFT_RST);

//DISPLAY 2
#define TFT_RST2 24
#define TFT_DC2 25
#define TFT_CS2 10
// Use hardware SPI and the above for CS/DC
ILI9341_due tft2 = ILI9341_due(TFT_CS2, TFT_DC2, TFT_RST2);

//THINKING TIME VARIABLES
int storedSecondsA = 01;
int storedMinutesA = 38;

int storedSecondsB = 01;
int storedMinutesB = 38;

//This stores last time millis was fired (second time keeping)
unsigned long TimeA;
unsigned long TimeB;

//running seconds and minutes for team A
int secondsA = storedSecondsA;
int minutesA = storedMinutesA;

//running seconds and minutes for team B
int secondsB = storedSecondsB;
int minutesB = storedMinutesB;

//store the last time value to check if we should write to screen more efficiently
int lastSecondsA = secondsA;
int lastMinutesA = minutesA;
int lastSecondsB = secondsB;
int lastMinutesB = minutesB;

//number buffer for formatting
char minbuf[3];
char secbuf[3];

//Arrays of adjustments for each team
const int arrayLength = 20;
int adjustmentsA[arrayLength] = {};
int adjustmentsB[arrayLength] = {};
int adjustmentsIndexA = 0;
int adjustmentsIndexB = 0;

//Variables for buttons and leds for team A
const int startPinA = 26;
const int stopPinA = 27;
const int ledA = 28;
bool startPinAon = false;
bool stopPinAon = true;

//Variables for buttons and leds for team B
const int startPinB = 29;
const int stopPinB = 30;
const int ledB = 31;
bool startPinBon = false;
bool stopPinBon = true;

//Variables for rotary encoder
const int encoderDT = 2; //Må være koblet til pin 2 for å fungere optimalt
const int encoderCLK = 3; //Må være koblet til pin 3 for å fungere optimalt
const int encoderSW = 32; //Button
int REpushCount = -1;     //how many times the button on the rotary encoder has been pushed
volatile int encoderValue = 0;
int lastEncoderValue = encoderValue;
bool encoderIsActive = false;

//debounce button on rotary encoder
long debouncing_time = 25; //Debouncing Time in Milliseconds
volatile unsigned long last_micros;

ILI9341_due chosenDisplay = tft;
bool Display = 0; //0 for display A, and 1 for display B


//Setup for radio comunications
#define CE_PIN 40
#define CSN_PIN 41
const byte thisSlaveAddress[6] = "00001";
RF24 radio(CE_PIN, CSN_PIN);
int dataReceived; // this must match dataToSend in the TX
bool newData = false;


void setup()
{
  //Display setup
  Serial.begin(9600);
  Serial3.begin(9600); //Serial port for ESP communication
  while (!Serial); // wait for Arduino Serial Monitor
  while (!Serial3); // wait for Serial 3 (vet ikke om denne er nødvendig, men skader ikke)
  SPI.begin();
  tft.begin();
  tft2.begin();

  int rotation = 3; //rotates screen to horizontal orientation
  tft.setRotation((iliRotation)rotation);
  tft2.setRotation((iliRotation)rotation);

  //Buttons and LED setup
  pinMode(startPinA, INPUT);
  pinMode(stopPinA, INPUT);
  pinMode(ledA, OUTPUT);
  pinMode(startPinB, INPUT);
  pinMode(stopPinB, INPUT);
  pinMode(ledB, OUTPUT);

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

  defaultScreen(); //Starts deafualt screen

  TimeA = millis(); //Start internal countdown
  TimeB = millis(); //Start internal countdown

  //Setup radio communication
  Serial.println("SimpleRx Starting");
  radio.begin();
  radio.setDataRate( RF24_250KBPS );
  radio.openReadingPipe(0, thisSlaveAddress);
  radio.startListening();
}

//Setup for ESP communication
char Stime[] = "00:0000:00000"; //Char array with current time and status, to send to ESP 
char A = '0';
char B = '0';
char upd = '0';

void loop(void)
{
  byte IncomingByte=0; //IncomingByte is set to 1 when ESP and Due have a connection
  boolean ByteReady = false;

  while (Serial3.available()){
    IncomingByte=Serial3.read(); 
    ByteReady = true;
  }
  
  upd = 0;
  if(startPinAon == true){
    A = '1';
    upd = '1';
  }
  if(startPinBon == true){
    B = '1';
    upd = '1';
  }
  if(stopPinAon == true){
    A = '0';
    upd = '1';
  }
  if(stopPinBon == true){
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
  if(IncomingByte == 1 ){
    Serial3.write(Stime, 14);
    Serial.write(Stime, 14); //time is printed out, just for testing
  }
 
  
  //Radio communication
  if(!encoderIsActive && radio.available()) { //Dersom man ikkje justerer på tida
    getData();
    showData();
  }

  //Every second check and render timerA
  if (encoderIsActive == false && startPinAon == true && stopPinAon == false) {
    if ((millis() - TimeA) >= 1000)    {
      checkTime(secondsA, minutesA, lastSecondsA, lastMinutesA, TimeA, tft);
    }
  }


  //Every second check and render timerB
  if (encoderIsActive == false && startPinBon == true && stopPinBon == false) {
    if ((millis() - TimeB) >= 1000)
    {
      checkTime(secondsB, minutesB, lastSecondsB, lastMinutesB, TimeB, tft2);
    }
  }
}

//What happens when start button for team A is pressed
void startA() {
  stopB();
  digitalWrite(ledA, HIGH);
  startPinAon = true;
  stopPinAon = false;
}

//What happens when start button for team B is pressed
void startB() {
  stopA();
  digitalWrite(ledB, HIGH);
  startPinBon = true;
  stopPinBon = false;
}

//What happens when stop button for team A is pressed
void stopA() {
  digitalWrite(ledA, LOW);
  startPinAon = false;
  stopPinAon = true;
}

//What happens when stop button for team B is pressed
void stopB() {
  digitalWrite(ledB,  LOW);
  startPinBon = false;
  stopPinBon = true;
}

//Check if time has reached 0
void checkTime(int& seconds, int& minutes, int& lastSeconds, int& lastMinutes, unsigned long& Time, ILI9341_due& screen) {
  if (!(seconds == 0 && minutes == 0))  {
    renderTime(seconds, minutes, lastSeconds, lastMinutes, Time, screen);
  }
  else  {
    //time is zero, do something
  }
}

//Upates the screen with correct time when called
void renderTime(int& seconds, int& minutes, int& lastSeconds, int& lastMinutes, unsigned long& Time, ILI9341_due& screen) {
  Time = millis(); //reset internal second countdown

  while (seconds > 60) {
    seconds -= 60;
    minutes++;
  }
  while (seconds < 0) {
    seconds += 60;
    minutes--;
  }

  //when seconds reach 0 subtract from minutes
  if (seconds == 0 && minutes != 0)  {
    seconds = 60;
    minutes--;
  }
  seconds--;

  //only paint over seconds if there is a change in second
  if (lastSeconds != seconds)  {
    screen.fillRect(164, 0, 155, 125, ILI9341_BLACK); //paint a black square over past seconds
  }
  //only paint over minutes if there is a change in minute
  if (lastMinutes != minutes)  {
    screen.fillRect(0, 0, 155, 125, ILI9341_BLACK); //paint a black square over past minutes
  }
  sprintf(secbuf, "%02d", seconds); //using sprintf to format our time correctly (ie 01 instead of just 1)
  sprintf(minbuf, "%02d", minutes);
  printText(minbuf, 0, 0, 11, ILI9341_WHITE, screen);
  printText(secbuf, 164, 0, 11, ILI9341_WHITE, screen); //line 2 text
  lastSeconds = seconds;
  lastMinutes = minutes;
}

//Prints out default text on screen when powered on
unsigned long defaultScreen() {
  tft.fillScreen(ILI9341_BLACK);
  tft2.fillScreen(ILI9341_BLACK);

  unsigned long start = micros();
  //Display 1
  renderTime(secondsA, minutesA, lastSecondsA, lastMinutesA, TimeA, tft);
  printText(":", 156, 25, 7, ILI9341_WHITE, tft); //line 2 text
  printText("Time adjusted: ", 0, 180, 1, ILI9341_WHITE, tft);

  //Display 2
  renderTime(secondsB, minutesB, lastSecondsB, lastMinutesB, TimeB, tft2);
  printText(":", 156, 25, 7, ILI9341_WHITE, tft2); //line 2 text
  printText("Time adjusted: ", 0, 180, 1, ILI9341_WHITE, tft2);

  return micros() - start;
}


//Variables for calculating positions for nubers in time adjustments
//for textsize 2, pixelwidth including 2 pixel spacing:
uint8_t digit = 12;
uint8_t doubleDigit = 20;
uint8_t negDigit = 20;
uint8_t doubleNegDigit = 24;
uint8_t barWidth = 4;

//Function to add adjusted time to the screen
unsigned long timeadjustments(int adjustments[], ILI9341_due& screen) {
  unsigned long start = micros();
  screen.fillRect(0, 200, 300, 20, ILI9341_BLACK); //paint a black square over past adjustments

  printText("|", 0, 200, 1, ILI9341_WHITE, tft); //prints first bar
  int xpos = 6;                                  //express the x position of timeadjustment

  for (int i = 0; i < arrayLength; i++) { //goes through adjustments array
    //Wont write 0's out
    if (adjustments[i] == 0)    {
      continue;
    }

    //numbers from 0-9
    else if (adjustments[i] >= 0 && adjustments[i] < 10) {
      printText(String(adjustments[i]), xpos, 200, 1, ILI9341_GREEN, screen);
      printText("|", xpos + digit, 200, 1, ILI9341_WHITE, screen);
      xpos += digit + barWidth;
    }

    //numbers over 9
    else if (adjustments[i] >= 10)    {
      printText(String(adjustments[i]), xpos, 200, 1, ILI9341_GREEN, screen);
      printText("|", xpos + doubleDigit, 200, 1, ILI9341_WHITE, screen);
      xpos += doubleDigit + barWidth;
    }

    //negative numbers from 0-9
    else if (adjustments[i] < 0 && adjustments[i] > -10)    {
      printText(String(adjustments[i]), xpos, 200, 1, ILI9341_RED, screen);
      printText("|", xpos + negDigit, 200, 1, ILI9341_WHITE, screen);
      xpos += negDigit + barWidth;
    }

    //negativ numbers <= -10
    else if (adjustments[i] <= -10)    {
      printText(String(adjustments[i]), xpos, 200, 1, ILI9341_RED, screen);
      printText("|", xpos + doubleNegDigit, 200, 1, ILI9341_WHITE, screen);
      xpos += doubleNegDigit + barWidth;
    }
  }
  return micros() - start;
}

//Function to print text to the screen
unsigned long printText(String text, uint16_t xpos, uint16_t ypos, uint8_t textSize, uint16_t textColor, ILI9341_due screen) {
  unsigned long start = micros();
  screen.cursorToXY(xpos, ypos);
  screen.setFont(Arial14);
  screen.setTextColor(textColor);
  screen.setTextScale(textSize);
  screen.println(text);
  return micros() - start;
}

//NRF radio communication
void getData() {
  if ( radio.available() ) {
    radio.read( &dataReceived, sizeof(dataReceived) );
    newData = true;
  }
}

//NRF radio communication

void showData() {
  if (newData == true) {
    Serial.print("Data received ");
    Serial.println(dataReceived);
    newData = false;
  }
}

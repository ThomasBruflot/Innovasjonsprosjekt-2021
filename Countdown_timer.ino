//include libraries
#include <TFTv2.h>
#include <SPI.h>


//Start and end time (do not format ie 03)
int storedSeconds = 0;  
int storedMinutes = 5;

int stopPin = 2;  
int resetPin = 3;  
int triggerPin = 9;

int encoderPinA = 8;
int encoderPinB = 6;
int encoderPinALast = 7;
int encoderPos = 0;
int n = 0;

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

void setup(void) {  
  pinMode(stopPin,INPUT_PULLUP);
  pinMode(resetPin,INPUT_PULLUP);
  pinMode(triggerPin,OUTPUT);
  pinMode(encoderPinA, INPUT);
  pinMode(encoderPinB, INPUT);
  pinMode(encoderPinALast, INPUT);

  time = millis(); //Start internal countdown

  TFT_BL_ON;      // turn on the background light
  Tft.TFTinit();  // init TFT library
  defaultScreen(); //load default screen
}

void loop(void) {  

  //Stop the timer when stop is pressed
  if(digitalRead(stopPin)==HIGH){
    time = millis();
  }

  //reset timer
  if(digitalRead(resetPin)==LOW){
    resetTimer();
    digitalWrite(triggerPin, LOW);
  }

  //Every second render the timer
  if((millis()-time)>= 1000){
    checkTime();
  }

  if(1 == true){
    encoder();
  }
}





//Check if time has reached 0
void checkTime(){  
  if(!(seconds == 0 && minutes == 0)){
    renderTime();
  } else {
     fail(); //time is zero, do something
  }
}

void renderTime(){  
    time = millis(); //reset internal second countdown

    //when seconds reach 0 subtract from minutes
    if(seconds == 0 && minutes != 0){
      seconds = 60;
      minutes--; 
     }
     seconds--;

     //only paint over seconds if there is a change in second
     if(lastSeconds != seconds){
        Tft.fillRectangle(130, 130, 110, 65, BLACK); //paint a black square over past seconds
      }
      //only paint over minutes if there is a change in minute
     if(lastMinutes != minutes){
        Tft.fillRectangle(5, 130, 110, 65, BLACK); //paint a black square over past minutes
      }
     sprintf(secbuf,"%02d",seconds); //using sprintf to format our time correctly (ie 01 instead of just 1)
     sprintf(minbuf,"%02d",minutes);
     Tft.drawString(minbuf, 5, 130, 8.5, WHITE); //line 2 text
     Tft.drawString(secbuf, 130, 130, 8.5, WHITE); //line 2 text
     lastSeconds = seconds;
     lastMinutes = minutes; 
}

void fail(){  
    digitalWrite(triggerPin, HIGH); 
  }

//reset the timer
void resetTimer(){  
  seconds = storedSeconds;
  minutes = storedMinutes;
  checkTime();
}

//What's on the screen
void defaultScreen() {  
  Tft.fillScreen();
  Tft.drawString(":", 97, 130, 8, WHITE); //line 2 text
  Tft.drawString("TIME", 5, 10, 9, WHITE); //line 2 text
  Tft.drawString("REMAINING", 5, 90, 4, WHITE); //line 2 text
}

void encoder(){
  n = digitalRead(encoderPinA);
  if ((encoderPinALast == LOW) && (n == HIGH)) {
    if (digitalRead(encoderPinB) == LOW) {
      encoderPos--;
    } else {
      encoderPos++;
    }
  encoderPinALast = n;}
} 

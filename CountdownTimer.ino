//include libraries
#include <TFTv2.h>
#include <SPI.h>

int storedSeconds = 0;
int storedMinutes = 0;

int encoderPinA = 5;
int encoderPinB = 6;
int encoderPos = 0;
int encoderPinALast = LOW;
int n = LOW;
int stopPin = 2;
int resetPin = 3;
int setPin = 4;
int triggerPin = 9;

unsigned long time;

int seconds = storedSeconds;  
int minutes = storedMinutes;

int lastSeconds = seconds;  
int lastMinutes = minutes;

//For formattering
char minbuf[3];  
char secbuf[3];

void setup(void) {
  pinMode(setPin,INPUT_PULLUP);
  pinMode(stopPin,INPUT_PULLUP);
  pinMode(resetPin,INPUT_PULLUP);
  pinMode(triggerPin,OUTPUT);
  pinMode (encoderPinA, INPUT);
  pinMode (encoderPinB, INPUT);

  time = millis(); //Start internal countdown
  /*
  TFT_BL_ON;      // turn on the background light
  Tft.TFTinit();  // init TFT library
  defaultScreen(); //load default screen
  */
  
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
  
  /*if ((encoderPinALast == LOW) && (n == HIGH)) {
    if (digitalRead(encoderPinB) == LOW) {
      encoderPos--;
    } else {
      encoderPos++;
    }
  encoderPinALast = n;
  */
}

//Check if time has reached 0
void checkTime(){  
  if(!(seconds == 0 && minutes == 0)){
    /*renderTime();*/
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

     /*//only paint over seconds if there is a change in second
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
     */
     sprintf(secbuf,"%02d",seconds); //using sprintf to format our time correctly (ie 01 instead of just 1)
     sprintf(minbuf,"%02d",minutes);
     Serial.print(minbuf);
     Serial.print(secbuf);
     
     
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

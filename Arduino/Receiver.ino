/*
* Arduino Wireless Communication Tutorial
*       Example 1 - Receiver Code
*                
* by Dejan Nedelkovski, www.HowToMechatronics.com
* 
* Library: TMRh20/RF24, https://github.com/tmrh20/RF24/
*/
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(7, 8); // CE, CSN
const byte address[6] = "00001";

#define led 4

boolean buttonState = 0; 

void setup() {
  pinMode(4, OUTPUT); 
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
}
void loop() {
  //if (radio.available()) {
    //char text[32] = "";
    //radio.read(&text, sizeof(text));
    //Serial.println(text);
    //Serial.println(sizeof(buttonState)); 
 
    
    while (!radio.available());
    radio.read(&buttonState, sizeof(buttonState));
    Serial.println(buttonState); 
    if (buttonState == LOW) {
      digitalWrite(led, HIGH);
    }
    else {
      digitalWrite(led, LOW);
      //delay(200); 
  }
}
//}

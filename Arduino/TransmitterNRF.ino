/*
* Arduino Wireless Communication Tutorial
*     Example 1 - Transmitter Code
*                
* by Dejan Nedelkovski, www.HowToMechatronics.com
* 
* Library: TMRh20/RF24, https://github.com/tmrh20/RF24/
*/
/* Transmitter */
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#define button 2
RF24 radio(7, 8); // CE, CSN
const byte address[6] = "00001";
boolean buttonState = 0;
void setup() {
  pinMode(button, INPUT_PULLUP);
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  
}
void loop() {
  //const char text[] = "Hello World";
 // Serial.println(text);
  radio.stopListening();
  //radio.write(&text, sizeof(text));
  buttonState = digitalRead(button);
  radio.write(&buttonState, sizeof(buttonState));
}

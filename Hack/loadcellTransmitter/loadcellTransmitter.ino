
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

int sdaPin = A4; //Inputpin for O+
int sclPin = 2; //Inputpin for O-
int sclRead = 0; //Verdien til O+
int sdaRead = 0;  //Verdien til O-
int diff = 0; //Differansen mellom spenningen fra O+ og O-
bool active; //Sier om vi har kraft på sensoren
int ref = 0; //Referansespenning som man måler utifra, ideelt 0 men her 1

RF24 radio(7, 8); // CE, CSN
const byte address[6] = "00001"; //Address that the two NRF-modules communicate on

void setup() {

  Serial.begin(9600);
  pinMode(sclPin, INPUT_PULLUP); // turn on pull-up resistor
  attachInterrupt(digitalPinToInterrupt(sclPin), readInput, CHANGE);
  radio.begin(); //Start radio
  radio.openWritingPipe(address); 
  radio.setDataRate( RF24_250KBPS);
  radio.setPALevel(RF24_PA_MAX); //Set max power for sending data
  
}
void loop() {
  
}

void readInput(){
  sclRead = digitalRead(sclPin);  // read the input pin O-
  sdaRead = analogRead(sdaPin); //read the input pin O+
 
  Serial.println(sclRead);
  radio.write(&sclRead, sizeof(sclRead)); //Sends data to the NRF connected to Due
 }

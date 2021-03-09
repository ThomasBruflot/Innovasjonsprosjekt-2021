/*
Forklaring til pins:
GND - ground-pin
+ - 5V-pin
SW - button-pin (encoder0pinC i denne koden)
For rotasjon:
DT - Output A
CLK - OutputB
*/

const int encoderDT = 2;
const int encoderCLK = 8;
const int encoderSW = 7;//Button
unsigned long lastFire = 0;
volatile int encoder0Pos = 0;


void setup() {
  pinMode(encoderSW, INPUT_PULLUP);
  pinMode(encoderDT, INPUT_PULLUP);       // turn on pull-up resistor
  pinMode(encoderCLK, INPUT_PULLUP);       // turn on pull-up resistor
  //pinMode(interruptSW, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(encoderDT), doEncoder, CHANGE);  // encoder pin on interrupt 0 - pin 2
  
  Serial.begin (9600);
  Serial.println("start");                // a personal quirk
}

void loop() {
  // do some stuff here - the joy of interrupts is that they take care of themselves
  if(digitalRead(encoderSW) == LOW) {
    Serial.println("Knappen er trykket - loop");
  }
}


void doEncoder() {
  
  /* If pinA and pinB are both high or both low, it is spinning
     forward. If they're different, it's going backward.
  */
  if (digitalRead(encoderDT) == digitalRead(encoderCLK)) {
    encoder0Pos++;
  } else {
    encoder0Pos--;
  }

  Serial.println (encoder0Pos, DEC);
}

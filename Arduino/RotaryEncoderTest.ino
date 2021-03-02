/*
Forklaring til pins:

GND - ground-pin
+ - 5V-pin
SW - button-pin (encoder0pinC i denne koden)

For rotasjon:
DT - Output A
CLK - OutputB
*/

const int encoder0PinA = 2;
const int encoder0PinB = 4;
const int encoder0PinC = 7;//Button
unsigned long lastFire = 0;

volatile int encoder0Pos = 0;


void setup() {
  pinMode(encoder0PinC, INPUT_PULLUP);
  
  pinMode(encoder0PinA, INPUT_PULLUP);       // turn on pull-up resistor
  pinMode(encoder0PinB, INPUT_PULLUP);       // turn on pull-up resistor
  //pinMode(interruptPinC, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(encoder0PinA), doEncoder, CHANGE);  // encoder pin on interrupt 0 - pin 2
  
  Serial.begin (9600);
  Serial.println("start");                // a personal quirk
}

void loop() {
  // do some stuff here - the joy of interrupts is that they take care of themselves
  if(digitalRead(encoder0PinC) == LOW) {
    Serial.println("Knappen er trykket - loop");
  }
}


void doEncoder() {
  
  /* If pinA and pinB are both high or both low, it is spinning
     forward. If they're different, it's going backward.
  */
  if (digitalRead(encoder0PinA) == digitalRead(encoder0PinB)) {
    encoder0Pos++;
  } else {
    encoder0Pos--;
  }

  Serial.println (encoder0Pos, DEC);
}

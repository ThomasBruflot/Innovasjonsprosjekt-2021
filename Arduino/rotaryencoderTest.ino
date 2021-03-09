/*
  Forklaring til pins:
  GND - ground-pin
  + - 5V-pin
  SW - button-pin (encoder0pinC i denne koden)
  For rotasjon:
  DT - Output A
  CLK - OutputB
*/

//Variables for rotary encoder
const int encoderDT = 2; //Må være koblet til pin 2 for å fungere optimalt
const int encoderCLK = 3; //Må være koblet til pin 3 for å fungere optimalt
const int encoderSW = 32; //Button
volatile int encoder0Pos = 0;
int REpushCount = 0;     //how many times the button on the rotary encoder has been pushed


void setup() {
  pinMode(encoderSW, INPUT_PULLUP);
  pinMode(encoderDT, INPUT_PULLUP);       // turn on pull-up resistor
  pinMode(encoderCLK, INPUT_PULLUP);       // turn on pull-up resistor
  attachInterrupt(digitalPinToInterrupt(encoderDT), doEncoder, CHANGE);  // encoder pin on interrupt 0 - pin 2
  attachInterrupt(digitalPinToInterrupt(encoderSW), encoderState, FALLING); //Button

  Serial.begin (115200);
  Serial.println("start");                // a personal quirk
}

void loop() {
  
}
void encoderState() {
  if (REpushCount > 2) {
    REpushCount = 0;
  }

  switch (REpushCount)
  {
    case 0:
      //adjustTime();
      Serial.println("Case 0");
      //printText("RTpushCount: " + REpushCount, 0, 140, 3, ILI9341_WHITE, tft);
      break;
    case 1:
      Serial.println("Case 1");
      //printText("RTpushCount: " + REpushCount, 0, 140, 3, ILI9341_WHITE, tft);
      break;
    case 2:
      Serial.println("Case 2");
      //printText("RTpushCount: " + REpushCount, 0, 140, 3, ILI9341_WHITE, tft);
      break;
    default:
      break;
  }
  REpushCount++;
}


void doEncoder() {

  /* If pinA and pinB are both high or both low, it is spinning
     forward. If they're different, it's going backward.
  */
  if (digitalRead(encoderDT) == digitalRead(encoderCLK)) {
    encoder0Pos += 5;
  } else {
    encoder0Pos -= 5;
  }

  Serial.println (encoder0Pos, DEC);
}

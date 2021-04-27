//Every function that is controlled by the rotary encoder is implemented in this file.

void stopTimeForBothTeams() {
  digitalWrite(ledA, LOW);
  startPinAon = false;
  stopPinAon = true;
  digitalWrite(ledB,  LOW);
  startPinBon = false;
  stopPinBon = true;
}


//debounced the butten presses on the encoder
void encoderDebounce() {
  if ((long)(micros() - last_micros) >= debouncing_time * 1000) {
    encoderState(); //runs encoderState if it has gone a longer time than debouncing_time since last button press
    last_micros = micros();
  }
}

//Function to adjust the time with the rotary encoder.
void encoderState() {
  REpushCount++;

  if (REpushCount > 3) {
    REpushCount = 0;
  }

  //Serial.println("count: " + String(REpushCount));
  switch (REpushCount) { //switches to the case according to the number of button presses
    case 0: //Normal mode
      encoderIsActive = false;
      break;
    case 1: //Choose team to adjust time for
      stopTimeForBothTeams();
      encoderIsActive = true;
      printText("Adjust time here: ", 5, 150, 2, ILI9341_SILVER, tft);
      printText("Adjust time here: ", 5, 150, 2, ILI9341_SILVER, tft2);
      break;
    case 2: //Add or subtract seconds for chosen team
      encoderIsActive = true;
      encoderValue = 0;
      printText(String(encoderValue), 235, 150, 2, ILI9341_WHITE, chosenDisplay); //prints a 0 after "Adjust time here: " on the chosen display
      break;
    case 3: //confirm time adjustment
      confirmTimeAdjustment();
      REpushCount = 0;
      encoderIsActive = false;
      break;
    default:
      break;
  }
}


void chooseTeamAorB(int encoderVal) {
  if (lastEncoderValue >= encoderValue) {//lets you switch from one screen to another everytime you change the direction of the rotary encoder
    tft2.fillRect(0, 150, 230, 30, ILI9341_BLACK); //paint a black square over message in display 2
    printText("Adjust time here: ", 5, 150, 2, ILI9341_RED, tft); //red text on chosen screen
    printText("Adjust time here: ", 5, 150, 2, ILI9341_SILVER, tft2); //silver text on not chosen screen
    chosenDisplay = tft;
    Display = 0;
  } else {
    tft.fillRect(0, 150, 230, 30, ILI9341_BLACK); //paint a black square over message in display 1
    printText("Adjust time here: ", 5, 150, 2, ILI9341_RED, tft2); //red text on chosen screen
    printText("Adjust time here: ", 5, 150, 2, ILI9341_SILVER, tft); //silver text on not chosen screen
    chosenDisplay = tft2;
    Display = 1;
  }
}

//Returns a value corresponding to the rotation of the encoder
void encoderRotation() {
  if (digitalRead(encoderDT) == digitalRead(encoderCLK)) {
    encoderValue += 5; //increases the encoderValue with 5 for every tic on the rotary encoder going clock wise
  } else {
    encoderValue -= 5; //decreases the encoderValue with 5 for every tic on the rotary encoder going counter clock wise
  }
  switch (REpushCount) {//switches to the case according to the number of button presses
    case 0: //Normal mode
      encoderIsActive = false;
      break;
    case 1: //Choose team to adjust time for
      stopTimeForBothTeams();
      encoderIsActive = true;
      chooseTeamAorB(encoderValue);
      break;
    case 2: //Add or subtract seconds for chosen team
      encoderIsActive = true;
      adjustTimeOnDisplay(chosenDisplay);
      break;
    case 3: //confirm time adjustment
      encoderIsActive = false;
      break;
    default:
      break;
  }
  lastEncoderValue = encoderValue; //lastEncoderValue is used in the function chooseTeamAorB
}


//This function just prints out the encoder value on the chosen screen
void adjustTimeOnDisplay(ILI9341_due& screen) {
  screen.fillRect(230, 150, 270, 30, ILI9341_BLACK); //paint a black square over message in display
  printText(String(encoderValue), 235, 150, 2, ILI9341_WHITE, screen);
}

//This function runs when the time adjustment has been confirmed
void confirmTimeAdjustment() {
  if (Display == 0) {
    secondsA += encoderValue + 1; //renderTime subtracts 1 sec when it is being called, therefor we need to add one extra
    adjustmentsA[adjustmentsIndexA] = encoderValue; //updates the array of time adjustments for team A
    timeadjustments(adjustmentsA, tft); //runs the function that updates the time adjustments
    adjustmentsIndexA++;
    renderTime(secondsA, minutesA, lastSecondsA, lastMinutesA, TimeA, tft); //Updates to the new time on the display
    tft.fillRect(0, 150, 320, 30, ILI9341_BLACK); //paint a black square over message in display 1
    tft2.fillRect(0, 150, 320, 30, ILI9341_BLACK); //paint a black square over message in display 2
  }
  else {
    secondsB += encoderValue + 1; //renderTime subtracts 1 sec when it is being called, therefor we need to add one extra
    adjustmentsB[adjustmentsIndexB] = encoderValue; // updates the array of time adjustments for team A
    timeadjustments(adjustmentsB, tft2); //runs the function that updates the time adjustments
    adjustmentsIndexB++;
    renderTime(secondsB, minutesB, lastSecondsB, lastMinutesB, TimeB, tft2); //Updates to the new time on the display
    tft.fillRect(0, 150, 320, 30, ILI9341_BLACK); //paint a black square over message in display 1
    tft2.fillRect(0, 150, 320, 30, ILI9341_BLACK); //paint a black square over message in display 2
  }
}

//this functions is never called for now
void timeOut(ILI9341_due& screen) {
  screen.fillScreen(ILI9341_BLACK);
  printText("TIMEOUT", 5, 20, 5, ILI9341_RED, screen);
}

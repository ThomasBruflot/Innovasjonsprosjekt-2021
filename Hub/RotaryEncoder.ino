//Every function that is controlled by the rotary encoder is implemented in this file.

//Stops time for both teams and turns off the red and yellow LED
void stopTimeForBothTeams() {
  digitalWrite(ledA, LOW);
  startPinAon = false;
  stopPinAon = true;
  digitalWrite(ledB,  LOW);
  startPinBon = false;
  stopPinBon = true;
}


//When testing the button functionality on the encoder we discovered a lot of bouncing. This function will prevent the from happening.
//We check that there has gone a longer time than debouncing_time since last button press before encoderState() is being called.
void encoderDebounce() {
  if ((long)(micros() - last_micros) >= debouncing_time * 1000) { 
    encoderState(); //runs encoderState if it has been a longer time than debouncing_time since last button press
    last_micros = micros();
  }
}

//This function is called when the rotary encoder is being pressed
void encoderState() {
  REpushCount++; //Increase push count

  if (REpushCount > 3) {
    REpushCount = 0; //Since there are only 4 cases, 0-3
  }

  switch (REpushCount) { //switches to the case according to the number of button presses
    case 0: //Normal mode
      encoderIsActive = false;
      break;
    case 1: //Choose team to adjust time for
      stopTimeForBothTeams();
      encoderIsActive = true;
      printText("Adjust time here: ", 5, 150, 2, ILI9341_SILVER, tftA); //Displays a text in a silver color on display A
      printText("Adjust time here: ", 5, 150, 2, ILI9341_SILVER, tftB); //Displays a text in a silver color on display b
      break;
    case 2: //Add or subtract seconds for chosen team
      encoderIsActive = true;
      printText(String(0), 235, 150, 2, ILI9341_WHITE, chosenDisplay); //prints a 0 after "Adjust time here: " on the chosen display
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

//This function is called after first button press and the rotary encoder is being turned.
//Acording to which way the encoder is being turned, a display will display the text "Adjust time here: " in the color red
void chooseTeamAorB(int encoderVal) {
  if (lastEncoderValue >= encoderValue) {//lets you switch from one screen to another everytime you change the direction of the rotary encoder
    tftB.fillRect(0, 150, 230, 30, ILI9341_BLACK); //paint a black square over message in display 2
    printText("Adjust time here: ", 5, 150, 2, ILI9341_RED, tftA); //red text on chosen screen
    printText("Adjust time here: ", 5, 150, 2, ILI9341_SILVER, tftB); //silver text on not chosen screen
    chosenDisplay = tftA; //Update chosenDisplay
    Display = 0; //Update chosenDisplay
  } 
  else {
    tftA.fillRect(0, 150, 230, 30, ILI9341_BLACK); //paint a black square over message in display 1
    printText("Adjust time here: ", 5, 150, 2, ILI9341_RED, tftB); //red text on chosen screen
    printText("Adjust time here: ", 5, 150, 2, ILI9341_SILVER, tftA); //silver text on not chosen screen
    chosenDisplay = tftB;//Update chosenDisplay
    Display = 1; //Update chosenDisplay
  }
}

//This function is called every time there is a change in rotation on the rotary encoder.
//Returns a value corresponding to the rotation of the encoder.
void encoderRotation() {
  if (digitalRead(encoderDT) == digitalRead(encoderCLK)) { //If encoder is turned clock wise
    encoderValue += 5; //increases the encoderValue with 5 for every tic on the rotary encoder going clock wise
  } else { //If encoder is turned counter clock wise
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
  printText(String(encoderValue), 235, 150, 2, ILI9341_WHITE, screen); //Print value of the encoder to the display
}

//This function runs when the time adjustment has been confirmed, after 3 button presses
void confirmTimeAdjustment() {
  if (Display == 0) {
    secondsA += encoderValue + 1; //renderTime subtracts 1 sec when it is being called, therefor we need to add one extra
    adjustmentsA[adjustmentsIndexA] = encoderValue; //updates the array of time adjustments for team A
    timeadjustments(adjustmentsA, tftA); //runs the function that updates the time adjustments
    adjustmentsIndexA++; //Increment the index to the next available spot in the array
    renderTime(secondsA, minutesA, lastSecondsA, lastMinutesA, TimeA, tftA); //Updates to the new time on the display
    tftA.fillRect(0, 150, 320, 30, ILI9341_BLACK); //paint a black square over message in display 1
    tftB.fillRect(0, 150, 320, 30, ILI9341_BLACK); //paint a black square over message in display 2
  }
  else {
    secondsB += encoderValue + 1; //renderTime subtracts 1 sec when it is being called, therefor we need to add one extra
    adjustmentsB[adjustmentsIndexB] = encoderValue; // updates the array of time adjustments for team A
    timeadjustments(adjustmentsB, tftB); //runs the function that updates the time adjustments
    adjustmentsIndexB++; //Increment the index to the next available spot in the array
    renderTime(secondsB, minutesB, lastSecondsB, lastMinutesB, TimeB, tftB); //Updates to the new time on the display
    tftA.fillRect(0, 150, 320, 30, ILI9341_BLACK); //paint a black square over message in display 1
    tftB.fillRect(0, 150, 320, 30, ILI9341_BLACK); //paint a black square over message in display 2
  }
}

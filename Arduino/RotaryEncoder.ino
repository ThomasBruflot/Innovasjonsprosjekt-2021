void encoderDebounce() {
  if ((long)(micros() - last_micros) >= debouncing_time * 1000) {
    encoderState();
    last_micros = micros();
  }
}

//Funksjon for å justere tiden med rotary encoder.
void encoderState() {
  REpushCount++;

  if (REpushCount > 3) {
    REpushCount = 0;
  }

  Serial.println("count: " + String(REpushCount));
  switch (REpushCount) {
    case 0: //Normal mode
      encoderIsActive = false;
      break;
    case 1: //Choose team to adjust time for
      stopTimeForBothTeams();
      encoderIsActive = true;
      break;
    case 2: //Add or subtract seconds for chosen team
      encoderIsActive = true;
      encoderValue = 0;
      break;
    case 3: //confirm time adjustment
      confirmTimeAdjustment();
      REpushCount = 0;
      Serial.println("count: " + String(REpushCount));
      encoderIsActive = false;
      break;
    default:
      break;
  }

}

void chooseTeamAorB(int encoderVal) {
  if (lastEncoderValue <= encoderValue) {
    Serial.println("Top display");
    tft2.fillRect(0, 150, 230, 30, ILI9341_BLACK); //paint a black square over message in display 2
    printText("Adjust time here: ", 5, 150, 2, ILI9341_RED, tft);
    chosenDisplay = tft;
    Display = 0;
  } else {
    Serial.println("Bottom display");
    tft.fillRect(0, 150, 230, 30, ILI9341_BLACK); //paint a black square over message in display 1
    printText("Adjust time here: ", 5, 150, 2, ILI9341_RED, tft2);
    chosenDisplay = tft2;
    Display = 1;
  }
}

//Returns a value corresponding to the rotation of the encoder
void encoderRotation() {
  if (digitalRead(encoderDT) == digitalRead(encoderCLK)) {
    encoderValue += 5;
  } else {
    encoderValue -= 5;
  }
  //Serial.println("RE value: " + String(encoderValue));

  switch (REpushCount) {
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
  lastEncoderValue = encoderValue;
}

void adjustTimeOnDisplay(ILI9341_due& screen) {
  screen.fillRect(230, 150, 270, 30, ILI9341_BLACK); //paint a black square over message in display
  printText(String(encoderValue), 235, 150, 2, ILI9341_WHITE, screen);
}


void confirmTimeAdjustment() {
  if (Display == 0) {
    secondsA += encoderValue + 1; //renderTime trekker fra 1 sec når den blir kalt, legger derfor til 1 ekstra
    adjustmentsA[adjustmentsIndexA] = encoderValue;
    timeadjustments(adjustmentsA, tft);
    adjustmentsIndexA++;
    renderTime(secondsA, minutesA, lastSecondsA, lastMinutesA, TimeA, tft);
    tft.fillRect(0, 150, 320, 30, ILI9341_BLACK); //paint a black square over message in display 2
  }
  else {
    secondsB += encoderValue + 1; //renderTime trekker fra 1 sec når den blir kalt, legger derfor til 1 ekstra
    adjustmentsB[adjustmentsIndexB] = encoderValue;
    timeadjustments(adjustmentsB, tft2);
    adjustmentsIndexB++;
    renderTime(secondsB, minutesB, lastSecondsB, lastMinutesB, TimeB, tft2);
    tft2.fillRect(0, 150, 320, 30, ILI9341_BLACK); //paint a black square over message in display 2

  }
}

void stopTimeForBothTeams() {
  //stop time for both teams
  digitalWrite(ledA, LOW);
  startPinAon = false;
  stopPinAon = true;
  digitalWrite(ledB,  LOW);
  startPinBon = false;
  stopPinBon = true;
}

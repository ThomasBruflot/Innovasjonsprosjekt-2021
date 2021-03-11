//Funksjon for å justere tiden med rotary encoder.
void encoderState() {
  if (REpushCount > 3) {
    REpushCount = 0;
  }
  Serial.println("count: " + String(REpushCount));
  switch (REpushCount) {
    case 0:
      stopTimeForBothTeams();
      //printText("Count: " + String(REpushCount), 20, 140, 1, ILI9341_WHITE, tft);
      break;
    case 1:
      stopTimeForBothTeams();
      //printText("Count: " + String(REpushCount), 20, 140, 1, ILI9341_WHITE, tft);
      break;
    case 2:
      stopTimeForBothTeams();
      //printText("Count: " + String(REpushCount), 20, 140, 1, ILI9341_WHITE, tft);
      break;
    default:
      break;
  }
  REpushCount++;

}

void chooseTeamAorB(int encoderVal) {
  if (encoderVal >= 0) {
    Serial.println("Top display");
    tft2.fillRect(0, 145, 250, 15, ILI9341_BLACK); //paint a black square over message in display 2
    printText("Adjust time here: ", 5, 150, 2, ILI9341_RED, tft);
  } else {
    Serial.println("Bottom display");
    tft.fillRect(0, 145, 250, 15, ILI9341_BLACK); //paint a black square over message in display 1
    printText("Adjust time here: ", 5, 150, 2, ILI9341_RED, tft);
  }
}

//Returns a value corresponding to the rotation of the encoder
void encoderRotation() {
  switch (REpushCount) {
    case 0:
      //printText("Count: " + String(REpushCount), 20, 140, 1, ILI9341_WHITE, tft);
      break;
    case 1:
      chooseTeamAorB(encoderValue);
      //printText("Count: " + String(REpushCount), 20, 140, 1, ILI9341_WHITE, tft);
      break;
    case 2:
      //printText("Count: " + String(REpushCount), 20, 140, 1, ILI9341_WHITE, tft);
      break;
    default:
      break;
  }

  if (digitalRead(encoderDT) == digitalRead(encoderCLK)) {
    encoderValue += 5;
  } else {
    encoderValue -= 5;
  }
  Serial.println("RE value: " + String(encoderValue));
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

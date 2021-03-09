//Funksjon for å justere tiden med rotary encoder.
void encoderState(){
  REpushCount++;
  if(REpushCount > 2){
    REpushCount = 0;
  }

  switch (REpushCount)
  {
  case 0:
    //adjustTime();
    printText("RTpushCount: " + REpushCount, 0, 140, 3, ILI9341_WHITE, tft);
    break;
  case 1:
    printText("RTpushCount: " + REpushCount, 0, 140, 3, ILI9341_WHITE, tft);
    break;
  case 2:
    printText("RTpushCount: " + REpushCount, 0, 140, 3, ILI9341_WHITE, tft);
    break;
  default:
    break;
  }      
} 

/*void chooseTeamAorB(){
    if(encoderPosChoose < 0) {
      timeA += encoderPos;
      timeAdjustedA = encoderPos;
     } 
     else if (encoderPosChoose > 0) {
        timeB += encoderPos;
        timeAdjustedB = encoderPos;
      }
}*/

//Konfigurasjon ved oppstart for å sette tiden.
/*void configuration() {
  REpushCount = digitalRead(encoderDT);
  
  
    timeA = encoderPos;
    timeB = encoderPos;
     
  }*/

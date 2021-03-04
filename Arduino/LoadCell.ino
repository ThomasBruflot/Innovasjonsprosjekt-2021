int sdaPin = A4; //Inputpin for O+
int sclPin = A5; //Inputpin for O-
int sclRead = 0; //Verdien til O+
int sdaRead = 0;  //Verdien til O-
int diff = 0; //Differansen mellom spenningen fra O+ og O-
bool active; //Sier om vi har kraft på sensoren
int ref = 1; //Referansespenning som man måler utifra, ideelt 0 men her 1

void setup() {
  Serial.begin(9600);           //  setup serial
  
}

void loop() {
  sclRead = analogRead(sclPin);  // read the input pin O-
  sdaRead = analogRead(sdaPin); //read the input pin O+
  diff = sdaRead - sclRead;  //Regner differansen (virtuell ground)
  Serial.println(diff);          // debug value

  if((diff+1) > ref) {
    active = HIGH; //Hvis vi har over 1 mer differanse på spenningene 
                   //sier vi at det er merkbar kraft på sensoren 
  }
  else {
    active = LOW; //Hvis vi ikke har en stor nok differanse på spenningen
  }
  
}

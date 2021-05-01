#include <ESP8266WiFi.h> //bibliotek brukt for WIFI funksjonalitet
#include <FirebaseArduino.h> //bibliotek brukt for Firebase funksjonalitet 


#define FIREBASE_HOST "elsys-prosj-default-rtdb.firebaseio.com" //firebase host 
#define FIREBASE_AUTH "yBXLp4gx1EVfhEuLPTXmQpvmEP36iZkts1uc7PvL" //firebase auth
#define WIFI_SSID "ElsysGruppe1" //WIFI navn
#define WIFI_PASSWORD "Oktober08" //WIFI passord

void setup() {
  Serial.begin(9600); 
 
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);   // Kobler ESP'en til WIFI
  
  while (WiFi.status() != WL_CONNECTED) { // Løkke som passer på at WIFI blir koblet til før resten av koden kjøres
    delay(500);
  }
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH); // Kobler ESP til Firebase 
}

int n = 0; // int for å telle antall gjennomganger i løkken 

char LagA[] = "00:00"; // variabelen som holder tidsdata til lag A
char LagB[] = "00:00"; // variabelen som holder tidsdata til lag  B
char A[] = "0"; // variabel som er 1 om tiden til lag A teller ned, og 0 ellers
char B[] = "0"; // variabel som er 1 om tiden til lag B teller ned, og 0 ellers
char upd[] = "0"; // variabel som er 1 om dersom det har skjedd endring i statusen til spillet, og 0 ellers

byte b = 1; // byte som sendes til Due som brukes til å bekrefte tilkobling mellom ESP og Due
String IncomingString=""; // String med som holder stringen som kommer inn på Serial
boolean StringReady = false; // Bool som er true om det har kommet en ny string i Serial

String name = "";

void loop() {
  Serial.write(b); // Due leser 1 om den er en kobling

  IncomingString=""; // Stringen tømmes igjen ved hver gjennomgang av løkken
  StringReady = false; // Bool settes tilbake til false ved hver gjennomgang av løkken
  
  while (Serial.available()){
    IncomingString=Serial.readString(); // Leser Stringen i Serial
    StringReady = true; 
  }

  if (StringReady){ // Om det har kommet inn data fra Serial settes variabelene definert over til å være denne nye dataen
    for (int i = 0; i < sizeof(LagA)-1; i++){
      LagA[i] = IncomingString.charAt(i);  //LagA får de første 5 tallene 
      LagB[i] = IncomingString.charAt(i+5); //LagB får de 5 neste tallene 
    }
    A[0] = IncomingString.charAt(10);
    B[0] = IncomingString.charAt(11);
    upd[0] = IncomingString.charAt(12);
    Firebase.setString("/LagA/Tid", LagA); // De to tidene pushes til firebase
    Firebase.setString("/LagB/Tid", LagB);
    Firebase.setString("/LagA/TellerNed", A); // De tre statusvariabelene pushes til firebase
    Firebase.setString("/LagB/TellerNed", B);
    Firebase.setString("/LagA/Oppdater", upd);
    Firebase.setString("/LagB/Oppdater", upd);
  }
  
  // Laster opp nye verdier til firebase sin /logs variabel
  name = Firebase.pushInt("logs", n++);
}

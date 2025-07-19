#include "DHT.h"
#define DHTPIN 2        // Pin a cui è collegato il sensore
#define DHTTYPE DHT22    // Indicazione del modello del sensore
DHT dht(DHTPIN, DHTTYPE);
char buffer[50];
uint8_t aperturaVal = 0;
uint8_t chiusuraVal = 0;
int TempMax=0;
int TempMin=10000;
int HumMax=0;
int HumMin=10000;
bool aperto=0;
bool enable = 0;
String status;
#include <SPI.h>
 
void setup()   {
  Serial.begin(9600);
  dht.begin();
  pinMode(4, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  digitalWrite(4, LOW);
  chiudi();

}
 
void loop()
{
    float t = dht.readTemperature();
  float h = dht.readHumidity();


    String input = Serial.readStringUntil('\n');  // legge fino a newline
    input.trim(); // rimuove spazi extra

    input.toCharArray(buffer, sizeof(buffer));

    int a, c;
    if (sscanf(buffer, "apertura=%dchiusura=%d", &a, &c) == 2) {
      aperturaVal = a;
      chiusuraVal = c;
    }
// Rimuovi tutti i caratteri 0xFF
String cleanedInput = "";
for (int i = 0; i < input.length(); i++) {
  if (input[i] != 0xFF) {
    cleanedInput += input[i];
  }
}

if (strstr(buffer, "enable") != NULL) {
  enable = true;
}
if (strstr(buffer, "noenable") != NULL) {
  enable = false;
}

if (strstr(buffer, "apri") != NULL) {
  apri();
}
if (strstr(buffer, "chiudi") != NULL) {
  chiudi();
}


if(int(h*100)<HumMin){
  HumMin=h*100;
}
if(int(h*100)>HumMax){
  HumMax=h*100;
}
if(int(t*100)>TempMax){
  TempMax=t*100;
}
if(int(t*100)<TempMin){
  TempMin=t*100;
}
if((int(t*100)<chiusuraVal*100)&&aperto==1 && enable==0){
  chiudi();
}
if((int(t*100)>aperturaVal*100)&&aperto==0&&enable==0){
  apri();
}
InvDisp("Temp.val",int(t * 100));
InvDisp("Hum.val",int(h * 100));
InvDisp("TempMax.val",TempMax);
InvDisp("HumMax.val",HumMax);
InvDisp("TempMin.val",TempMin);
InvDisp("HumMin.val",HumMin);
InvDisptxt("status.txt", "\"" + status + "\"");
if (aperturaVal >= 0 && aperturaVal <= 100) {
  InvDisp("aper.val", aperturaVal);
}

if (chiusuraVal >= 0 && chiusuraVal <= 100) {
  InvDisp("chiu.val", chiusuraVal);
}

}

void InvDisp(String varName, int value) {
  Serial.print(varName);
  Serial.print("=");
  Serial.print(value);
  Serial.write(0xff);
  Serial.write(0xff);
  Serial.write(0xff);
  delay(30);
}
void InvDisptxt(String varName, String value) {
  Serial.print(varName);
  Serial.print("=");
  Serial.print(value);
  Serial.write(0xff);
  Serial.write(0xff);
  Serial.write(0xff);
  delay(30);
}
void apri(){
  digitalWrite(7,1);
digitalWrite(8,0);
delay(200);
digitalWrite(4,1);
delay(2000);
digitalWrite(4,0);
digitalWrite(7,0);
digitalWrite(8,0);
aperto=1;
status="aperte";
}
void chiudi(){
digitalWrite(7,0);
digitalWrite(8,1);
delay(200);
digitalWrite(4,1);
delay(2000);
digitalWrite(4,0);
digitalWrite(7,0);
digitalWrite(8,0);
aperto=0;
status="chiuse";
}



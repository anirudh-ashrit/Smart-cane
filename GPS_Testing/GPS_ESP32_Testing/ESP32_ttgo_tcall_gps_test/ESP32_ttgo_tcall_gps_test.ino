#include <TinyGPS++.h>

TinyGPSPlus gps;

void displayInfo(){
  Serial.print(F("Location: "));
  if(gps.location.isValid()){
    Serial.print(gps.location.lat(), 8); //Print Latitude
    Serial.print(F(","));
    Serial.print(gps.location.lng(), 8); //Print Longitude 
  }
  else{
    Serial.print(F("Invalid"));
  }
  Serial.println();
}

void setup() {
  Serial.begin(9600);
}

void loop() {
  
  while(Serial.available() > 0){
    if(gps.encode(Serial.read())){
      displayInfo();
    }
  }
}

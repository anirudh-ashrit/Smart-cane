#define RXD2 14
#define TXD2 12

#define hardcode

#ifdef hardcode

HardwareSerial gps_serial(2);

void setup() {
  Serial.begin(9600);
  Serial.printf("LETS START");
  gps_serial.begin(9600, SERIAL_8N1, RXD2, TXD2);
}
 
void loop() {
  while(gps_serial.available()) {
    Serial.print(char(gps_serial.read()));  // read from gps, write to serial debug port
    //Serial.print("I am here");
    //delay(1);
  }
}
#endif

#ifdef TINYGPS

#include <TinyGPS++.h>

TinyGPSPlus gps;
HardwareSerial gps_serial(2);

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
  gps_serial.begin(9600, SERIAL_8N1, RXD2, TXD2);
}

void loop() {
  
  while(gps_serial.available()){
    if(gps.encode(Serial.read())){
      displayInfo();
    }
  }
}

#endif

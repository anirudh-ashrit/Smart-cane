#define RXD2 14
#define TXD2 12

#include <TinyGPS++.h>


TinyGPSPlus gps; //The TinyGPS++ object
HardwareSerial gps_serial(2);

float latitude, longitude;
String lat_str, lng_str;

void setup() {
  Serial.begin(9600);
  Serial.printf("LETS START");
  gps_serial.begin(9600, SERIAL_8N1, RXD2, TXD2);
}
 
void loop() {
  while(gps_serial.available()) {               //While data is available
    //Serial.print(char(gps_serial.read()));    //read from gps, write to serial debug port
    if(gps.encode(gps_serial.read())){           //read GPS data
      if(gps.location.isValid()){               //Check whether gps location is valid
          latitude = gps.location.lat();
          lat_str = String(latitude, 6);        //Latitude location is stored in a string 
          longitude = gps.location.lng();
          lng_str = String(longitude, 6);       //Latitude location is stored in a string
          Serial.print("LAT:  ");
          Serial.println(lat_str);  
          Serial.print("LONG: ");
          Serial.println(lng_str);
          
      }
    }
    
  }
}

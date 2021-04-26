//#include<HardwareSerial.h>//No extra libray installed
#define RXD2 14
#define TXD2 12

HardwareSerial gps_serial(2);

void setup() {
  Serial.begin(9600);
  Serial.printf("LETS START");
  gps_serial.begin(9600, SERIAL_8N1, RXD2, TXD2);
}
 
void loop() {
  while(gps_serial.available()) {
   Serial.print(char(gps_serial.read()));  // read from gps, write to serial debug port
  Serial.print("I am here");
  }
}

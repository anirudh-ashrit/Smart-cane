//// IoT based Fall Detection using NodeMCU and MPU6050 Sensor
////https://theiotprojects.com
//#include <Wire.h>
//#include <WiFi.h>
//#include <HTTPClient.h>
//#include <ArduinoJson.h>
//
//
//const int MPU_addr=0x68;  // I2C address of the MPU-6050
//int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;
//float ax=0, ay=0, az=0, gx=0, gy=0, gz=0;
//boolean fall = false; //stores if a fall has occurred
//boolean trigger1=false; //stores if first trigger (lower threshold) has occurred
//boolean trigger2=false; //stores if second trigger (upper threshold) has occurred
//boolean trigger3=false; //stores if third trigger (orientation change) has occurred
//byte trigger1count=0; //stores the counts past since trigger 1 was set true
//byte trigger2count=0; //stores the counts past since trigger 2 was set true
//byte trigger3count=0; //stores the counts past since trigger 3 was set true
//int angleChange=0;
//// WiFi network info.
//const char *ssid = 
//"Avalon Access 1300"; // Enter your Wi-Fi Name
//const char *pass = "Indore4Nagpur4"; // Enter your Wi-Fi Password
//void send_event(const char *event);
//const char *host = "maker.ifttt.com";
//const char *privateKey = "f4XL9LAXqVWmrAeqWoQGGCpYz_mt1Y7caS3tj_XFAd_";
//
//const char* Host = "www.googleapis.com";
//String thisPage = "/geolocation/v1/geolocate?key=";
//String key = "AIzaSyByxOTGDz9pG1fcBNEgRcGD8TZ6WlPHM5s";
//int status = WL_IDLE_STATUS;
//String jsonString = "{\n";
//
//double latitude    = 0.0;
//double longitude   = 0.0;
//double accuracy    = 0.0;
//int more_text = 1; // set to 1 for more debug output
//
//void setup(){
// Serial.begin(115200);
// Wire.begin();
// Wire.beginTransmission(MPU_addr);
// Wire.write(0x6B);  // PWR_MGMT_1 register
// Wire.write(0);     // set to zero (wakes up the MPU-6050)
// Wire.endTransmission(true);
// Serial.println("Wrote to IMU");
//  Serial.println("Connecting to ");
//  Serial.println(ssid);
//  WiFi.begin(ssid, pass);
//  while (WiFi.status() != WL_CONNECTED)
//  {
//    delay(500);
//    Serial.print(".");              // print ... till not connected
//  }
//  Serial.println("");
//  Serial.println("WiFi connected");
// }
//void loop(){
// mpu_read();
// ax = (AcX-2050)/16384.00;
// ay = (AcY-77)/16384.00;
// az = (AcZ-1947)/16384.00;
// gx = (GyX+270)/131.07;
// gy = (GyY-351)/131.07;
// gz = (GyZ+136)/131.07;
// // calculating Amplitute vactor for 3 axis
// float Raw_Amp = pow(pow(ax,2)+pow(ay,2)+pow(az,2),0.5);
// int Amp = Raw_Amp * 10;  // Mulitiplied by 10 bcz values are between 0 to 1
// delay(500);
// Serial.println(Amp);
// if (Amp<=2 && trigger2==false){ //if AM breaks lower threshold (0.4g)
//   trigger1=true;
//   Serial.println("TRIGGER 1 ACTIVATED");
//   }
// if (trigger1==true){
//   trigger1count++;
//   if (Amp>=12){ //if AM breaks upper threshold (3g)
//     trigger2=true;
//     Serial.println("TRIGGER 2 ACTIVATED");
//     trigger1=false; trigger1count=0;
//     }
// }
// if (trigger2==true){
//   trigger2count++;
//   angleChange = pow(pow(gx,2)+pow(gy,2)+pow(gz,2),0.5); Serial.println(angleChange);
//   if (angleChange>=30 && angleChange<=400){ //if orientation changes by between 80-100 degrees
//     trigger3=true; trigger2=false; trigger2count=0;
//     Serial.println(angleChange);
//     Serial.println("TRIGGER 3 ACTIVATED");
//       }
//   }
// if (trigger3==true){
//    trigger3count++;
//    if (trigger3count>=10){ 
//       angleChange = pow(pow(gx,2)+pow(gy,2)+pow(gz,2),0.5);
//       //delay(10);
//       Serial.println(angleChange); 
//       if ((angleChange>=0) && (angleChange<=10)){ //if orientation changes remains between 0-10 degrees
//           fall=true; trigger3=false; trigger3count=0;
//           Serial.println(angleChange);
//             }
//       else{ //user regained normal orientation
//          trigger3=false; trigger3count=0;
//          Serial.println("TRIGGER 3 DEACTIVATED");
//       }
//     }
//  }
// if (fall==true){ //in event of a fall detection
//   Serial.println("FALL DETECTED");
//   send_event("fall_detected"); 
//   fall=false;
//   }
// if (trigger2count>=6){ //allow 0.5s for orientation change
//   trigger2=false; trigger2count=0;
//   Serial.println("TRIGGER 2 DECACTIVATED");
//   }
// if (trigger1count>=6){ //allow 0.5s for AM to break upper threshold
//   trigger1=false; trigger1count=0;
//   Serial.println("TRIGGER 1 DECACTIVATED");
//   }
//  delay(100);
//
//  DynamicJsonBuffer jsonBuffer;
//  
//  WiFiClientSecure client;
//
//  //Connect to the client and make the api call
//  Serial.print("Requesting URL: ");
//  Serial.println("https://" + (String)Host + thisPage + key);
//  Serial.println(" ");
//  if (client.connect(Host, 443)) {
//    Serial.println("Connected");
//    client.println("POST " + thisPage + key + " HTTP/1.1");
//    client.println("Host: " + (String)Host);
//    client.println("Connection: close");
//    client.println("Content-Type: application/json");
//    client.println("User-Agent: Arduino/1.0");
//    client.print("Content-Length: ");
//    client.println(jsonString.length());
//    client.println();
//    client.print(jsonString);
//    delay(500);
//  }
//
//  //Read and parse all the lines of the reply from server
//  while (client.available()) {
//    String line = client.readStringUntil('\r');
//    if (more_text) {
//      Serial.print(line);
//    }
//    JsonObject& root = jsonBuffer.parseObject(line);
//    if (root.success()) {
//      latitude    = root["location"]["lat"];
//      longitude   = root["location"]["lng"];
//      accuracy   = root["accuracy"];
//    }
//  }
//
//  Serial.println("closing connection");
//  Serial.println();
//  client.stop();
//
//  Serial.print("Latitude = ");
//  Serial.println(latitude, 6);
//  Serial.print("Longitude = ");
//  Serial.println(longitude, 6);
//  Serial.print("Accuracy = ");
//  Serial.println(accuracy);
//
//
//}
//
//
////////////////////////////////////////////////////////////
//
//
//void mpu_read(){
// Wire.beginTransmission(MPU_addr);
// Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
// Wire.endTransmission(false);
// Wire.requestFrom(MPU_addr,14,true);  // request a total of 14 registers
// AcX=Wire.read()<<8|Wire.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)    
// AcY=Wire.read()<<8|Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
// AcZ=Wire.read()<<8|Wire.read();  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
// Tmp=Wire.read()<<8|Wire.read();  // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
// GyX=Wire.read()<<8|Wire.read();  // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
// GyY=Wire.read()<<8|Wire.read();  // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
// GyZ=Wire.read()<<8|Wire.read();  // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
// }
//void send_event(const char *event)
//{
//  Serial.print("Connecting to "); 
//  Serial.println(host);
//    // Use WiFiClient class to create TCP connections
//  WiFiClient client;
//  const int httpPort = 80;
//  if (!client.connect(host, httpPort)) {
//    Serial.println("Connection failed");
//    return;
//  }
//    // We now create a URI for the request
//  String url = "/trigger/";
//  url += event;
//  url += "/with/key/";
//  url += privateKey;
//  Serial.print("Requesting URL: ");
//  Serial.println(url);
//  // This will send the request to the server
//  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
//               "Host: " + host + "\r\n" + 
//               "Connection: close\r\n\r\n");
//  while(client.connected())
//  {
//    if(client.available())
//    {
//      String line = client.readStringUntil('\r');
//      Serial.print(line);
//    } else {
//      // No data yet, wait a bit
//      delay(50);
//    };
//  }
//  Serial.println();
//  Serial.println("closing connection");
//  client.stop();
//}





/*********************************************************************
  This is the code for Fetching your location from Google Geolocation API
  
  This code is provided by 
  techiesms
*********************************************************************/

#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <WiFi.h>

char myssid[] = "Avalon Access 1300";         // your network SSID (name)
char mypass[] = "Indore4Nagpur4";          // your network password


//Credentials for Google GeoLocation API...
const char* Host = "www.googleapis.com";
String thisPage = "/geolocation/v1/geolocate?key=";
String key = "AIzaSyByxOTGDz9pG1fcBNEgRcGD8TZ6WlPHM5s";

int status = WL_IDLE_STATUS;
String jsonString = "{\n";

double latitude    = 0.0;
double longitude   = 0.0;
double accuracy    = 0.0;
int more_text = 1; // set to 1 for more debug output




void setup()   {
  Serial.begin(115200);


  Serial.println("Start");
  // Set WiFi to station mode and disconnect from an AP if it was previously connected
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
  Serial.println("Setup done");
  // We start by connecting to a WiFi network
  Serial.print("Connecting to ");
  Serial.println(myssid);
  WiFi.begin(myssid, mypass);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(".");


}


void loop() {

  char bssid[6];
  DynamicJsonBuffer jsonBuffer;
  Serial.println("scan start");
  // WiFi.scanNetworks will return the number of networks found
  int n = WiFi.scanNetworks();
  Serial.println("scan done");
  if (n == 0)
    Serial.println("no networks found");
  else
  {
    Serial.print(n);
    Serial.println(" networks found...");

    if (more_text) {
      // Print out the formatted json...
      Serial.println("{");
      Serial.println("\"homeMobileCountryCode\": 234,");  // this is a real UK MCC
      Serial.println("\"homeMobileNetworkCode\": 27,");   // and a real UK MNC
      Serial.println("\"radioType\": \"gsm\",");          // for gsm
      Serial.println("\"carrier\": \"Vodafone\",");       // associated with Vodafone
      //Serial.println("\"cellTowers\": [");                // I'm not reporting any cell towers
      //Serial.println("],");
      Serial.println("\"wifiAccessPoints\": [");
      for (int i = 0; i < n; ++i)
      {
        Serial.println("{");
        Serial.print("\"macAddress\" : \"");
        Serial.print(WiFi.BSSIDstr(i));
        Serial.println("\",");
        Serial.print("\"signalStrength\": ");
        Serial.println(WiFi.RSSI(i));
        if (i < n - 1)
        {
          Serial.println("},");
        }
        else
        {
          Serial.println("}");
        }
      }
      Serial.println("]");
      Serial.println("}");
    }
    Serial.println(" ");
  }
  // now build the jsonString...
  jsonString = "{\n";
  jsonString += "\"homeMobileCountryCode\": 234,\n"; // this is a real UK MCC
  jsonString += "\"homeMobileNetworkCode\": 27,\n";  // and a real UK MNC
  jsonString += "\"radioType\": \"gsm\",\n";         // for gsm
  jsonString += "\"carrier\": \"Vodafone\",\n";      // associated with Vodafone
  jsonString += "\"wifiAccessPoints\": [\n";
  for (int j = 0; j < n; ++j)
  {
    jsonString += "{\n";
    jsonString += "\"macAddress\" : \"";
    jsonString += (WiFi.BSSIDstr(j));
    jsonString += "\",\n";
    jsonString += "\"signalStrength\": ";
    jsonString += WiFi.RSSI(j);
    jsonString += "\n";
    if (j < n - 1)
    {
      jsonString += "},\n";
    }
    else
    {
      jsonString += "}\n";
    }
  }
  jsonString += ("]\n");
  jsonString += ("}\n");
  //--------------------------------------------------------------------

  Serial.println("");

  WiFiClientSecure client;

  //Connect to the client and make the api call
  Serial.print("Requesting URL: ");
  Serial.println("https://" + (String)Host + thisPage + key);
  Serial.println(" ");
  if (client.connect(Host, 443)) {
    Serial.println("Connected");
    client.println("POST " + thisPage + key + " HTTP/1.1");
    client.println("Host: " + (String)Host);
    client.println("Connection: close");
    client.println("Content-Type: application/json");
    client.println("User-Agent: Arduino/1.0");
    client.print("Content-Length: ");
    client.println(jsonString.length());
    client.println();
    client.print(jsonString);
    delay(500);
  }

  //Read and parse all the lines of the reply from server
  while (client.available()) {
    String line = client.readStringUntil('\r');
    if (more_text) {
      Serial.print(line);
    }
    JsonObject& root = jsonBuffer.parseObject(line);
    if (root.success()) {
      latitude    = root["location"]["lat"];
      longitude   = root["location"]["lng"];
      accuracy   = root["accuracy"];
    }
  }

  Serial.println("closing connection");
  Serial.println();
  client.stop();

  Serial.print("Latitude = ");
  Serial.println(latitude, 6);
  Serial.print("Longitude = ");
  Serial.println(longitude, 6);
  Serial.print("Accuracy = ");
  Serial.println(accuracy);




}

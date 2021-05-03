#include "NewPing.h"

const int trigPin = 23;
const int echoPin = 22;
const int buzzPin = 21;

//float duration, distance;
//
//void setup() {
//  pinMode(trigPin, OUTPUT);
//  pinMode(echoPin, INPUT);
//  Serial.begin(115200);
//}
//
//void loop() {
//  digitalWrite(trigPin, LOW);
//  delayMicroseconds(2);
//  digitalWrite(trigPin, HIGH);
//  delayMicroseconds(10);
//  digitalWrite(trigPin, LOW);
//
//  duration = pulseIn(echoPin, HIGH);
//  distance = (duration*.0343)/2;
//  Serial.print("Distance: ");
//  Serial.println(distance);
//  delay(100);
//}

NewPing sonar(trigPin, echoPin);

float distance;

void setup(){
  pinMode(buzzPin, OUTPUT);
  ledcSetup(0,1E5,12);
  ledcAttachPin(buzzPin,0);
  Serial.begin(115200);
}

void loop(){
  float distance = sonar.ping_median(5);

  if(distance < 1000) ledcWriteTone(0, 800);
  else
  {
    ledcWrite(0,0);
    Serial.print("Distance: ");
    Serial.print(distance, 1); Serial.println(" cm");
  }
 
  delay(50);
}

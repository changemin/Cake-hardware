#include<Servo.h>

#define lockerPin 3

Servo locker;

void setup(){
  Serial.begin(9600);
  locker.attach(lockerPin);
}

void loop(){
  doorOpen();
  delay(1000);
  doorClose();
  delay(1000);
}

void doorOpen(){
  locker.write(0);
  Serial.println("[Servo]Door Opened");
}

void doorClose(){
  locker.write(90);
  Serial.println("[Servo]Door Closed");
}

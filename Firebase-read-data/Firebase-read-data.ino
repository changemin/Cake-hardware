#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

#define FIREBASE_HOST "test.firebaseio.com"
#define FIREBASE_AUTH "YOUR KEY HERE"

#define WIFI_SSID "YOUR SSID"
#define WIFI_PASSWORD "YOUR PASS"

const char* roomID = "0101";

void setup() {
  Serial.begin(9600);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.stream("");
}

int isDoor(){
  return Firebase.getBool("/rooms/0101");
}

void loop() {
  Serial.println(isDoor());
}
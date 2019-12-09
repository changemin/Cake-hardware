#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

#define FIREBASE_HOST "YOUR FIREBASE HOST"
#define FIREBASE_AUTH "YOUR FIREBASE KEY"
#define WIFI_SSID "YOUR WIFI SSID"
#define WIFI_PASSWORD "YOUR WIFI PASS"

void setup() {
  Serial.begin(115200);
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
}

void loop() {
  boolean Status = Firebase.getBool("isDoor");
  Serial.print("READ : ");
  Serial.println(Status);
  delay(1000);

  if(Status ==true){
    // Door Open
  }
  else if(Status ==false){
    // Door Close
  }
  // Firebase.remove("number"); //remove data
  delay(1000);
}
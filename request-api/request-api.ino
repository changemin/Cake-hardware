#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

#include <WiFiClient.h>

const char* ssid = "YOUR SSID"; //Enter SSID
const char* password = "YOUR PASS"; //Enter Password

char server[] = "www.test.com";

WiFiClient client

void httpRequest(){
  Serial.println();
  client.stop();
  if(client.connet(server,80)){
    Serial.println("[HTTP Request]Connecting to server...");

    client.print(F("POST somthing"));
  }
  else {
    Serial.println("[HTTP Request]Connection failed");
  }
}

void setup(void)
{ 
  Serial.begin(115200);
  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) 
  {
     delay(500);
     Serial.print("*");
  }
  
  Serial.println("");
  Serial.println("WiFi connection Successful");
  Serial.print("The IP Address of ESP8266 Module is: ");
  Serial.print(WiFi.localIP());// Print the IP address
}

void loop() 
{
  httpRequest();
}



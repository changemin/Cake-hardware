/*
 * Initial Author: ryand1011 (https://github.com/ryand1011)
 *
 * Reads data written by a program such as "rfid_write_personal_data.ino"
 *
 * See: https://github.com/miguelbalboa/rfid/tree/master/examples/rfid_write_personal_data
 *
 * Uses MIFARE RFID card using RFID-RC522 reader
 * Uses MFRC522 - Library
 * -----------------------------------------------------------------------------------------
 *             MFRC522      Arduino       Arduino   Arduino    Arduino          Arduino
 *             Reader/PCD   Uno/101       Mega      Nano v3    Leonardo/Micro   Pro Micro
 * Signal      Pin          Pin           Pin       Pin        Pin              Pin
 * -----------------------------------------------------------------------------------------
 * RST/Reset   RST          9             5         D9         RESET/ICSP-5     RST
 * SPI SS      SDA(SS)      10            53        D10        10               10
 * SPI MOSI    MOSI         11 / ICSP-4   51        D11        ICSP-4           16
 * SPI MISO    MISO         12 / ICSP-1   50        D12        ICSP-1           14
 * SPI SCK     SCK          13 / ICSP-3   52        D13        ICSP-3           15
*/

#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>
#include <Adafruit_NeoPixel.h>
#include <FirebaseArduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

#define ssid "USER_SSID"
#define password "PASSWORD"

#define FIREBASE_HOST "-=-=-=-=-=-=-=-=-=-="
#define FIREBASE_AUTH "-=-=-=-=-=-=-=-=-="

#define roomId "0101"

#define ledStripN 10
#define ledStripPin 10
#define lockerPin 11

#define RST_PIN         3          // Configurable, see typical pin layout above
#define SS_PIN          4          // Configurable, see typical pin layout above

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance

Adafruit_NeoPixel ledStrip = Adafruit_NeoPixel(ledStripN, ledStripPin, NEO_GRB+NEO_KHZ800); // Init Neopixel LED ledStrip

Servo locker;

char server[] "www.test.com";

WiFiClient client

//*****************************************************************************************//
void setup() {
  Serial.begin(115200);                                           // Initialize serial communications with the PC
  SPI.begin();                // Init SPI bus
  locker.attach(lockerPin);
  mfrc522.PCD_Init();                                              // Init MFRC522 card
  Serial.println(F("Read personal data on a MIFARE PICC:"));    //shows in serial that it is ready to read
  locker.attach(lockerPin);
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.stream("");
  connectWiFi();
}

//*****************************************************************************************//
void loop() {
  if(mfrc522.PICC_IsNewCardPresent()){
    String UID = getUID();
    Serial.println(UID);
    httpRequest(UID);
  }
  if(isDoor() == 1){
    doorOpen();
  }
  else if(isDoor() == 0){
    doorClose();
  }
}
//*****************************************************************************************//

void ledColorAll(int R, int G, int B, int interval){
    for(int i = 0 ; i < ledStripN; i ++){
        ledStrip.setPixelColor(i, R, G, B);
        ledStrip.show();
        delay(interval);
    }
}

void doorOpen(){
    locker.write(0);
}

void doorClose(){
    locker.write(90);
}

void connectWiFi(){
  int tmp = 0;
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
    ledColorAll(0,0,255,50);
  }
}

boolean isDoor(){
  return Firebase.getBool("/rooms/0101");
}

String getUID(){
  if ( ! mfrc522.PICC_ReadCardSerial()) { //Since a PICC placed get Serial and continue
    return "";
  }
  String UID = "";
  for(int i = 0 ; i < 5; i ++){
    String tmp = String(mfrc522.uid.uidByte[i], HEX);
    UID += tmp;
  }
  //Serial.println(UID);
  mfrc522.PICC_HaltA(); // Stop reading
  mfrc522.PCD_StopCrypto1();

  return UID;
}

void httpRequest(String UID){
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
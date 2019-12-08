#include <Adafruit_NeoPixel.h>
#define ledStripN 10
#define ledStripPin 3

Adafruit_NeoPixel ledStrip = Adafruit_NeoPixel(ledStripN, ledStripPin, NEO_GRB+NEO_KHZ800);

void setup(){
  Serial.begin(9600);
  ledStrip.begin();
}
void loop(){
  Serial.println("hello");
  for(int i = 0 ; i < ledStripN; i ++){
    ledStrip.setPixelColor(i,255,0,0);
    ledStrip.show();  
  }
  
}


#include "Adafruit_APDS9960.h"
Adafruit_APDS9960 apds;

void setup() {
  Serial.begin(115200);

  if(!apds.begin()){
    Serial.println("failed to initialize device! Please check your wiring.");
  }
  else Serial.println("Device initialized!");

  apds.enableColor(true);

  apds.setADCGain(APDS9960_AGAIN_16X);
}

void loop() {

  uint16_t r, g, b, c;
  

  while(!apds.colorDataReady()){
    delay(5);
  }


  apds.getColorData(&r, &g, &b, &c);
  Serial.print("Red Light: ");
  Serial.print(r);
  
  Serial.print(" || Green Light: ");
  Serial.print(g);
  
  Serial.print(" || Blue Light: ");
  Serial.print(b);
  
  Serial.print(" || Ambient Light: ");
  Serial.println(c);
  Serial.println();
  
  delay(500);
}
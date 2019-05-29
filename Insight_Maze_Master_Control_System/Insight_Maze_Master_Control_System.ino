#include "InsightMazeMaster.h"
#include "globals.h"

Master ma(PINS_ID_OUT, PIN_BTN, PIN_SD_CS);

void setup() {
  // put your setup code here, to run once:
  ma.masterSetup();
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
  Serial.println("Waiting for button press...");
}

void loop() {
  // put your main code here, to run repeatedly:
  
  ma.sctProtocol(1);



}

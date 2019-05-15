#include "InsightMazeMaster.h"
#include "globals.h"

Master ma(PINS_ID_OUT, PINS_LED, PIN_BTN, PIN_CS);

int dummyCommands0[] = {0, 9, 10, 100, 130, 19};
int dummyCommands1[] = {45, 32, 105, 140, 10, 59};
int dummyCommands2[] = {63, 237, 17, 106, 3, 204};

String paths[60];
int pathNum = 0;

void setup() {
  // put your setup code here, to run once:
  ma.masterSetup();

  ma.setCommands(dummyCommands0);
  Serial.println("Waiting for button press..."); 
}

void loop() {
  // put your main code here, to run repeatedly:
  ma.updateBtnVals();
  
  if (ma.isBtnPressed()) {
    Serial.print(ma.state()); Serial.print('-');
    switch (ma.state()) {
      case 0:
        Serial.println("Reading SD Card");
        ma.getPathsFromSD();
        break;
      case 1:
        ma.printPaths();
        Serial.println("Press button to configure first layout.");
        break;
      case 2:
        Serial.println("Configuring next layout..." + ma.getPath(pathNum));
        // Configure
        Serial.println("Check that configuration is correct.");
        Serial.println("Waiting for button press...");
        break;
      case 3:
        Serial.println("Go.");
        Serial.println("Press button upon completion...");
        pathNum++;
        break;
    }
  }
  else ma.setCommands(DO_NOTHING);

  ma.transmitCommands();
}

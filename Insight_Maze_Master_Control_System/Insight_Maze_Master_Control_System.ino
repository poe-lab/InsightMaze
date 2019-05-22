#include "InsightMazeMaster.h"
#include "globals.h"

LiquidCrystal_I2C lcd(0x27, 16, 2);
Master ma(PINS_ID_OUT, PINS_LED, PIN_BTN, PIN_CS, lcd);

//int dummyCommands0[] = {3+128, 2+128, 2+128, 4+128, 130+128, 19+128};
//int dummyCommands1[] = {45+128, 32+128, 105+128, 140, 10+128, 59+128};
//int dummyCommands2[] = {63+128, 237, 17+128, 106+128, 3+128, 204};

String paths[60];
int pathNum = 0;

void setup() {
  // put your setup code here, to run once:
  ma.masterSetup();

  Serial.println("Waiting for button press...");
}

void loop() {
  // put your main code here, to run repeatedly:
  ma.updateBtnVals();

  if (ma.isBtnPressed()) {
    Serial.print(ma.state()); Serial.print('-');
    Serial.print(ma.btnCounter()); Serial.println('-');

    switch (ma.state()) {
      case 0:
        Serial.println("Reading SD Card");
        ma.getPathsFromSD();
        Serial.println("Done...waiting for button press.");
        break;
      case 1:
        ma.printPaths();
        Serial.println("Press button to configure first layout.");
        break;
      case 2:
        Serial.println("Configuring " + ma.getPath(pathNum) + " layout..." );

        Serial.println(*(ma.splitPathCommands(ma.getPath(pathNum))));


        //        ma.setCommands(ma.splitPathCommands(ma.getPath(pathNum)));

        //        delay(2000); // Configure
        Serial.print("Check that configuration is correct. ");
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

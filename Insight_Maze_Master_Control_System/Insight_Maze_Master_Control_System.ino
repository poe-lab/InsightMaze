#include "InsightMazeMaster.h"
#include "globals.h"

//Master ma(PINS_ID_OUT[0], PINS_ID_OUT[1], PINS_ID_OUT[2], PINS_ID_OUT[3], PINS_ID_OUT[4], PINS_ID_OUT[5]);
Master ma(PINS_ID_OUT, PINS_LED, PIN_BTN);
void setup() {
  // put your setup code here, to run once:
  ma.masterSetup();
}

void loop() {
  // put your main code here, to run repeatedly:

}

#include "InsightMaze.h"
#include "globals.h"

SyringePump r0(SYRINGE_0_STEP_PIN, SYRINGE_0_DIR_PIN, SYRINGE_SPML, SYRINGE_MAX_VOL);
SyringePump r1(SYRINGE_1_STEP_PIN, SYRINGE_1_DIR_PIN, SYRINGE_SPML, SYRINGE_MAX_VOL);
SyringePump r2(SYRINGE_2_STEP_PIN, SYRINGE_2_DIR_PIN, SYRINGE_SPML, SYRINGE_MAX_VOL);

Sensor s0(PIN_SENSOR_0);
Sensor s1(PIN_SENSOR_1);
Sensor s2(PIN_SENSOR_2);
Sensor s3(PIN_SENSOR_3);

Door d0(PIN_DOOR_0, POS_D0[0], POS_D0[1]);
Door d1(PIN_DOOR_1, POS_D1[0], POS_D1[1]);
Door d2(PIN_DOOR_2, POS_D2[0], POS_D2[1]);
Door d3(PIN_DOOR_3, POS_D3[0], POS_D3[1]);
Door d4(PIN_DOOR_4, POS_D4[0], POS_D4[1]);
Door d5(PIN_DOOR_5, POS_D5[0], POS_D5[1]);

Module m0(PIN_ID, s0, s1, s2, s3, d0, d1, d2, d3, d4, d5);
EndModule e0(PIN_ID, s0, s1, s2, d0, d1, d2, d3, d4, d5, r0, r1, r2);

void setup() {
//  r0.syringeSetup();
//  r1.syringeSetup();
//  r1.syringeSetup();

  m0.moduleSetup();
  m0.testDoors(1500, 1500);
  
}

void loop() {

  ///////// SENSOR TESTING /////////////
  m0.checkSensors();
  m0.testSensors(63);
  
  if(m0.isSensorRise(0)){
    Serial.println("Rising Edge Detected.");
    delay(1000);
  }
  if(m0.isSensorFall(0)){
    Serial.println("Falling Edge Detected.");
    delay(1000);
  }

//  ///////// DOOR TESTING ////////////////
//  m0.setPath('r');
//  m0.printDoorsStates(); Serial.println(' ');
//  delay(1000);
//  
//  m0.setPath('c');
//  m0.printDoorsStates(); Serial.println(' ');
//  delay(1000);
//
//  m0.setPath('l');
//  m0.printDoorsStates(); Serial.println(' ');
//  delay(1000);
  
}

/////////////////////// TESTING COMPONENTS CODE //////////////////////////

void testSyringePump(SyringePump syringePump, float mL, int timeDelay) {
  syringePump.dispenseMilliliters(mL);
  delay(timeDelay);
}

//////////////////////////////////////////////////////////////////////////

void slavePracticeSetup() {
  m0.moduleSetup();
  Serial.begin(115200);
}

void slavePracticeProtocol() {
  unsigned int commands = m0.receiveCommands();
  Serial.print(millis()); Serial.print(" ");
  Serial.print(m0.id()); Serial.print(" ");
  Serial.print(commands); Serial.print(" ");
  Serial.println(commands, BIN);
  m0.interpretCommands(commands);
}


void moveSyringePump(SyringePump syringePump, bool isDirUp) {
  if (isDirUp)
    syringePump.dirUp();
  else
    syringePump.dirDown();

  syringePump.stepMotor();
}

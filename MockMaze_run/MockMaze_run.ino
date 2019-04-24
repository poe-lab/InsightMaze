#include "globals.h"
#include "MockMaze.h"

Sensor s0(PIN_SENSOR_0);
Sensor s1(PIN_SENSOR_1);
Sensor s2(PIN_SENSOR_2);
Sensor s3(PIN_SENSOR_3);

Door d0(PIN_DOOR_0, POS_D0[0], POS_D0[1]); //identify what a door is and position of door?
Door d1(PIN_DOOR_1, POS_D1[0], POS_D1[1]);
Door d2(PIN_DOOR_2, POS_D2[0], POS_D2[1]);
Door d3(PIN_DOOR_3, POS_D3[0], POS_D3[1]);
Door d4(PIN_DOOR_4, POS_D4[0], POS_D4[1]);
Door d5(PIN_DOOR_5, POS_D5[0], POS_D5[1]);

int timedelay = 3000; // lets me change time interval here instead of time in every part of code
void setup() { // this will only run once

  s0.sensorSetup();
  s1.sensorSetup();
  s2.sensorSetup();
  s3.sensorSetup();

  d0.doorSetup();
  d1.doorSetup();
  d2.doorSetup();
  d3.doorSetup();
  d4.doorSetup();
  d5.doorSetup();

  d0.doorClose();
  d1.doorClose();
  d2.doorClose();
  d3.doorClose();
  d4.doorClose();
  d5.doorClose();
  delay(timedelay);

  Serial.begin(9600);
}

void testSensors() {
  printSensorsVals();
  printSensorsValIsPastThresh();
  printSensorsValWasPastThresh();
  printSensorsIsTrig(); //this adds IsTrig to the serial monitor
  Serial.println(' ');
}

void loop() { //repeat the following sequence in a loop
  
    testSensors();

    if (s2.isTrig()) {
      d4.doorOpen();
      printDoorsStates();
      delay(timedelay);
    }

  d4.doorClose();
  printDoorsStates();
  delay(timedelay);

  if (s0.isTrig()) {
    d5.doorOpen();
    printDoorsStates();
    delay(timedelay);
  }

  d0.doorClose(); //close all doors
  d1.doorClose();
  d2.doorClose();
  d3.doorClose();
  d4.doorClose();
  d5.doorClose();
  printDoorsStates();
  delay(timedelay);

  d2.doorOpen();
  printDoorsStates();
  delay(timedelay);

  d2.doorClose();
  printDoorsStates();
  delay(timedelay);

  d3.doorOpen();
  printDoorsStates();
  delay(timedelay);

  d0.doorClose(); //close all doors
  d1.doorClose();
  d2.doorClose();
  d3.doorClose();
  d4.doorClose();
  d5.doorClose();
  printDoorsStates();
  delay(timedelay);

  d0.doorOpen();
  printDoorsStates();
  delay(timedelay);

  d0.doorClose();
  printDoorsStates();
  delay(timedelay);

  d1.doorOpen();
  printDoorsStates();
  delay(timedelay);

  d1.doorClose();
  printDoorsStates();
  delay(timedelay);
}

void printSensorsVals() {
  Serial.print("sVal:");
  Serial.print(s0.getSensorVal()); Serial.print(',');
  Serial.print(s1.getSensorVal()); Serial.print(',');
  Serial.print(s2.getSensorVal()); Serial.print(',');
  Serial.print(s3.getSensorVal()); Serial.print(" - ");
}

void printSensorsValIsPastThresh() {
  Serial.print("isPast:");
  Serial.print(s0.isPastThresh()); Serial.print(',');
  Serial.print(s1.isPastThresh()); Serial.print(',');
  Serial.print(s2.isPastThresh()); Serial.print(',');
  Serial.print(s3.isPastThresh()); Serial.print(" - ");
}

void printSensorsValWasPastThresh() {
  Serial.print("wasPast:");
  Serial.print(s0.wasPastThresh()); Serial.print(',');
  Serial.print(s1.wasPastThresh()); Serial.print(',');
  Serial.print(s2.wasPastThresh()); Serial.print(',');
  Serial.print(s3.wasPastThresh()); Serial.print(" - ");
}

void printSensorsIsTrig() {
  Serial.print("isTrig:");
  Serial.print(s0.isTrig()); Serial.print(',');
  Serial.print(s1.isTrig()); Serial.print(',');
  Serial.print(s2.isTrig()); Serial.print(',');
  Serial.print(s3.isTrig()); Serial.print(" - ");
}

void printDoorsStates() {
  Serial.print(d0.isOpen()); Serial.print(' ');
  Serial.print(d1.isOpen()); Serial.print(' ');
  Serial.print(d2.isOpen()); Serial.print(' ');
  Serial.print(d3.isOpen()); Serial.print(' ');
  Serial.print(d4.isOpen()); Serial.print(' ');
  Serial.println(d5.isOpen());
}

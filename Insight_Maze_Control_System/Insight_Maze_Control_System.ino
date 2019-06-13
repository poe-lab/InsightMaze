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

Module m(PIN_ID, s0, s1, s2, s3, d0, d1, d2, d3, d4, d5);
EndModule e(PIN_ID, PIN_ALERT, s0, s1, s2, d0, d1, d2, d3, d4, d5, r0, r1, r2);

unsigned int commands;
bool needsToSetPath = true;
int dir = 0;

int pinsLEDs[] = {13, 12, 8, 7, 4, 2};

void setup() {

  e.moduleSetup();

  // Sets up leds to represent doors
  for (int i = 0; i < sizeof(pinsLEDs) / sizeof(pinsLEDs[0]); i++) {
    pinMode(pinsLEDs[i], OUTPUT);
    digitalWrite(pinsLEDs[i], LOW);
  }

}

void loop() {
  e.updateSensors();
  e.testSensors(0b111111);

    digitalWrite(pinsLEDs[0], HIGH);
    delay(1000);
  }
    digitalWrite(pinsLEDs[0], LOW);
  }




}

/////////////////// COMMUNICATION CODE ///////////////////////////////////////////////////////

void doorsAsLEDs(int leds[]) {
  for (int i = 0; i < NUM_MAIN_DOORS; i++) {
    if (m.isDoorOpen(i)) digitalWrite(leds[i], HIGH);
    else digitalWrite(leds[i], LOW);
  }
}

/////////////////// SEQUENTIAL CHOICE TASK CODE ////////////////////////////////////////////////

void slaveMainProtocol() {
  m.updateSensors();

  // Skips over if commands are DO_NOTHING
  if (commands != 0) {
    // Prints id of module and commands received in decimal and binary
    Serial.print(m.id()); Serial.print(" ");
    Serial.print(commands); Serial.print(" ");
    Serial.print(commands, BIN);

    if ((commands & 0b11000000) == 0b10000000) {
      dir = (commands & 0b00000011); // first two bits contain direction information
      m.setPath(dir);
      needsToSetPath = false;
    }
    Serial.println(' ');
  }

  // Code to check sensors
  if (!needsToSetPath) {
    switch (dir) {
      case LEFT:
        if (m.isSensorFall(0)) m.closeDoor(0);
        if (m.isSensorFall(3)) m.closeDoor(3);
        break;
      case CENTER:
        if (m.isSensorFall(1)) m.closeDoor(1);
        if (m.isSensorFall(3)) m.closeDoor(4);
        break;
      case RIGHT:
        if (m.isSensorFall(2)) m.closeDoor(2);
        if (m.isSensorFall(3)) m.closeDoor(5);
        break;
    }
  }

  doorsAsLEDs(pinsLEDs); // treats leds as door -> if door is open corresponding led will be on
}

  m.updateSensors();

  // Skips over if commands are DO_NOTHING
  if (commands != 0) {
    // Prints id of module and commands received in decimal and binary
    Serial.print(m.id()); Serial.print(" ");
    Serial.print(commands); Serial.print(" ");
    Serial.print(commands, BIN);

    if ((commands & 0b11000000) == 0b10000000) {
      dir = (commands & 0b00000011); // first two bits contain direction information
      m.openAllDoors();
      needsToSetPath = false;
    }
    Serial.println(' ');
  }

  // Code to check sensors

  doorsAsLEDs(pinsLEDs); // treats leds as door -> if door is open corresponding led will be on
}

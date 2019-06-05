#ifndef GLOBAL_H
#define GLOBAL_H

#define PIN_ID A7
#define PIN_ALERT A6

#define PIN_SENSOR_0 A0
#define PIN_SENSOR_1 A1
#define PIN_SENSOR_2 A2
#define PIN_SENSOR_3 A3

#define PIN_DOOR_0 3
#define PIN_DOOR_1 5
#define PIN_DOOR_2 6
#define PIN_DOOR_3 9
#define PIN_DOOR_4 10
#define PIN_DOOR_5 11

const int POS_D0[] = {150, 50};
const int POS_D1[] = {50, 160};
const int POS_D2[] = {45, 160};
const int POS_D3[] = {150, 50};
const int POS_D4[] = {90, 0};
const int POS_D5[] = {150, 50};

const bool DOOR_CONFIG_1[] = {true, true, true, true, true, true};

const float SYRINGE_SPML = 7300; // steps per mL was 7100
const float SYRINGE_MAX_VOL = 5;  // mL
#define SYRINGE_0_STEP_PIN 13
#define SYRINGE_0_DIR_PIN 12
#define SYRINGE_1_STEP_PIN 8
#define SYRINGE_1_DIR_PIN 7
#define SYRINGE_2_STEP_PIN 4
#define SYRINGE_2_DIR_PIN 2

#endif // GLOBAL_H

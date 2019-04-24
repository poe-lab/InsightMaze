#include "Sensor.h"
#include "SyringePump.h"
#include "Door.h"
#include <Arduino.h>

const int NUM_MAIN_SENSORS = 4;
const int NUM_MAIN_DOORS = 6;
const int NUM_START_SENSORS = 4;
const int NUM_START_DOORS = 6;
const int NUM_END_SENSORS = 3;
const int NUM_END_DOORS = 6;
const int NUM_END_SYRINGE_PUMPS = 3;

const int ID_VALS_OUT[] = {0, 51, 102, 153, 204, 255};
const int ID_RES = 10;
const int NUM_IDS = 6;
const char IDS[] = {'s', 'a', 'b', 'c', 'd', 'r'};

class Module {
  public:
    Module(int pintID, Sensor s0, Sensor s1, Sensor s2, Sensor s3, Door d0, Door d1, Door d2, Door d3, Door d4, Door d5);
    void moduleSetup();
    void openDoor(int doorID);
    void closeDoor(int doorID);
    bool isDoorOpen(int doorID);
    
    int getSensorVal(int sensorID);
    void checkSensors();
    bool isSensorFall(int sensorID);
    bool isSensorRise(int sensorID);
    int getSensorThresh(int sensorID);
    bool isSensorPastThresh(int sensorID);
    bool wasSensorPastThresh(int sensorID);

    char id();
    unsigned int receiveCommands();
    void interpretCommands(unsigned int commands);

  private:
    char m_id;
    int m_pinID;
    Door* m_doors[NUM_MAIN_DOORS];
    Sensor* m_sensors[NUM_MAIN_SENSORS];

    Sensor m_s0;
    Sensor m_s1;
    Sensor m_s2;
    Sensor m_s3;
    Door m_d0;
    Door m_d1;
    Door m_d2;
    Door m_d3;
    Door m_d4;
    Door m_d5;

    bool m_needsToConfig;
};

class EndModule {
  public:
    EndModule(int pintID, Sensor s0, Sensor s1, Sensor s2, Door d0, Door d1, Door d2, Door d3, Door d4, Door d5, SyringePump r0, SyringePump r1, SyringePump r2);
    void moduleSetup();
    void openDoor(int doorID);
    void closeDoor(int doorID);
    int getSensorVal(int sensorID);
    void checkSensors();
    bool isSensorTrig(int sensorID);
    void dispenseReward(int syringePumpID, float vol);
    char id();
    unsigned int receiveCommands();
    void interpretCommands(unsigned int commands);

  private:
    char m_id;
    int m_pinID;
    Door* m_doors[NUM_END_DOORS];
    Sensor* m_sensors[NUM_END_SENSORS];
    SyringePump* m_syringePumps[NUM_END_SYRINGE_PUMPS];

    Sensor m_s0;
    Sensor m_s1;
    Sensor m_s2;

    Door m_d0;
    Door m_d1;
    Door m_d2;
    Door m_d3;
    Door m_d4;
    Door m_d5;

    SyringePump m_r0;
    SyringePump m_r1;
    SyringePump m_r2;

    bool m_needsToConfig;
};

#include "Sensor.h"
#include "SyringePump.h"
#include "Door.h"
#include <Arduino.h>

#define NUM_MAIN_SENSORS 4
#define NUM_MAIN_DOORS 6
#define NUM_START_SENSORS 4
#define NUM_START_DOORS 6
#define NUM_END_SENSORS 3
#define NUM_END_DOORS 6
#define NUM_END_SYRINGE_PUMPS 3

#define RIGHT 1
#define LEFT 2
#define CENTER 3

const int ID_VALS_OUT[] = {0, 51, 102, 153, 204, 255};
const int ID_VALS_IN[] = {0, 205, 409, 614, 818, 1023};
const int NUM_IDS = sizeof(ID_VALS_OUT) / sizeof(ID_VALS_OUT[0]);
const char IDS[] = {'a', 'b', 'c', 'd', 'e', 'f'};
#define ID_RES 50

class Module {
  public:
    Module(int pintID, Sensor s0, Sensor s1, Sensor s2, Sensor s3, Door d0, Door d1, Door d2, Door d3, Door d4, Door d5);
    void moduleSetup();                           // Sets up module class must be called in void setup() before any actions are done with the module
    
    void openDoor(int doorID);                    // Opens the door with specific door ID 
    void closeDoor(int doorID);                   // Closes the door with specific door ID
    bool isDoorOpen(int doorID);                  // Returns whether or not the door with specific door ID is open (true->open)
    void openAllDoors();                          // Opens all the doors of the module
    void closeAllDoors();                         // Closes all the doors of the module
    void testDoors(int closeTime, int openTime);  // Closes all the doors of the module, waits closeTime in milliseconds, then opens all the doors, waits openTime milliseconds
    void printDoorsStates();                      // Prints out the states of all the doors in the module (true->open)
    void setPath(int path);                       // Configures the doors to a specific path of the maze; takes arguments of the following: 'l'->left, 'r'->right, 'c'->center
    
    int getSensorVal(int sensorID);               // Returns the sensor value of the sensor with specific sensor ID
    void updateSensors();                         // Must be called at the beginning of void loop() to update the sensors values and states
    bool isSensorFall(int sensorID);              // Returns whether or not an object left the view of the sensor 
    bool isSensorRise(int sensorID);              // Returns whether or not an object entered the view of the sensor 
    int getSensorThresh(int sensorID);            // Returns the threshold value of the sensor with the specific sensor ID
    bool isObjInSensorView(int sensorID);         // Returns whether or not an object is in the view of the sensor
    bool wasObjInSensorView(int sensorID);        // Returns whether or not an object was just in the view of the sensor
    void printSensorsVals();                      // Prints all the values of the sensors of the module
    void printIsObjSensorView();                  // Prints whether an object is in view of the all sensors of the module 
    void printWasObjSensorView();                 // Prints whether an object was just in view of the all sensors of the module 
    void printSensorsIsFall();                    // Prints whether an object just left the view of the all sensors of the module 
    void printSensorsIsRise();                    // Prints whether an object just entered the view of the all sensors of the module 
    void printSensorsThresh();                    // Prints the thresholds of all the sensors of the module
    void testSensors(int values);                 // Prints specified values of the sensors in the module

    char id();                                    // Returns the id of the module
    unsigned int receiveCommands();               // Returns the commands of the module
    void interpretCommands(unsigned int commands);// Interprets the commands of the module and follows specified protocol

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
    void openDoor(int doorID);                    // Opens the door with specific door ID 
    void closeDoor(int doorID);                   // Closes the door with specific door ID
    bool isDoorOpen(int doorID);                  // Returns whether or not the door with specific door ID is open (true->open)
    void openAllDoors();                          // Opens all the doors of the module
    void closeAllDoors();                         // Closes all the doors of the module
    void testDoors(int closeTime, int openTime);  // Closes all the doors of the module, waits closeTime in milliseconds, then opens all the doors, waits openTime milliseconds
    void printDoorsStates();                      // Prints out the states of all the doors in the module (true->open)
    void setPath(int path);                       // Configures the doors to a specific path of the maze; takes arguments of the following: 'l'->left, 'r'->right, 'c'->center
    
    int getSensorVal(int sensorID);               // Returns the sensor value of the sensor with specific sensor ID
    void updateSensors();                         // Must be called at the beginning of void loop() to update the sensors values and states
    bool isSensorFall(int sensorID);              // Returns whether or not an object left the view of the sensor 
    bool isSensorRise(int sensorID);              // Returns whether or not an object entered the view of the sensor 
    int getSensorThresh(int sensorID);            // Returns the threshold value of the sensor with the specific sensor ID
    bool isObjInSensorView(int sensorID);         // Returns whether or not an object is in the view of the sensor
    bool wasObjInSensorView(int sensorID);        // Returns whether or not an object was just in the view of the sensor
    void printSensorsVals();                      // Prints all the values of the sensors of the module
    void printIsObjSensorView();                  // Prints whether an object is in view of the all sensors of the module 
    void printWasObjSensorView();                 // Prints whether an object was just in view of the all sensors of the module 
    void printSensorsIsFall();                    // Prints whether an object just left the view of the all sensors of the module 
    void printSensorsIsRise();                    // Prints whether an object just entered the view of the all sensors of the module 
    void printSensorsThresh();                    // Prints the thresholds of all the sensors of the module
    void testSensors(int values);                 // Prints specified values of the sensors in the module

    void dispenseReward(int syringePumpID, float vol); // Tells syringe pump of specific ID to dispense specified volume
    
    char id();                                    // Returns the id of the module
    unsigned int receiveCommands();               // Returns the commands of the module
    void interpretCommands(unsigned int commands);// Interprets the commands of the module and follows specified protocol


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

    int m_commands;

    bool m_needsToConfig;
};

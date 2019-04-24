#include <Arduino.h>
#include "InsightMaze.h"

//////////////////////////// MAIN MODULE CLASS ///////////////////////////////////////////

Module::Module(int pinID, Sensor s0, Sensor s1, Sensor s2, Sensor s3, Door d0, Door d1, Door d2, Door d3, Door d4, Door d5)
  : m_s0(s0), m_s1(s1), m_s2(s2), m_s3(s3), m_d0(d0), m_d1(d1), m_d2(d2), m_d3(d3), m_d4(d4), m_d5(d5) 
{
  m_pinID = pinID;
  
  m_s0 = s0;
  m_s1 = s1;
  m_s2 = s2;
  m_s3 = s3;
  m_sensors[0] = &m_s0;
  m_sensors[1] = &m_s1;
  m_sensors[2] = &m_s2;
  m_sensors[3] = &m_s3;

  m_d0 = d0;
  m_d1 = d1;
  m_d2 = d2;
  m_d3 = d3;
  m_d4 = d4;
  m_d5 = d5;
  m_doors[0] = &m_d0;
  m_doors[1] = &m_d1;
  m_doors[2] = &m_d2;
  m_doors[3] = &m_d3;
  m_doors[4] = &m_d4;
  m_doors[5] = &m_d5;
}

void Module::moduleSetup(){
  // Calls setup fuinction for all sensors
  for(int i = 0; i < NUM_MAIN_SENSORS; i++)
    m_sensors[i]->sensorSetup();
  
  // Calls setup function for all doors
  for(int i = 0; i < NUM_MAIN_DOORS; i++)
    m_doors[i]->doorSetup();
  
  m_needsToConfig = true;

  // Determines ID char of Module
  int idValIn = analogRead(m_pinID);
  idValIn = map(idValIn, 0, 1023, 0, 255);
  // Serial.print(idValIn); Serial.print(' ');

  char id = 'e';

  for(int i = 0; i < NUM_IDS; i++) {
    if(idValIn >= ID_VALS_OUT[i] - 4 * ID_RES && idValIn <= ID_VALS_OUT[i] + ID_RES)
      m_id = IDS[i];
  }
}

void Module::openDoor(int doorID){
  m_doors[doorID]->doorOpen();
}

void Module::closeDoor(int doorID){
  m_doors[doorID]->doorClose();
}

bool Module::isDoorOpen(int doorID){
  return (m_doors[doorID]->isOpen());
}

int Module::getSensorVal(int sensorID){
  return (m_sensors[sensorID]->getSensorVal());
}

void Module::checkSensors(){
  for(int i = 0; i < NUM_MAIN_SENSORS; i++){
    m_sensors[i]->sensorUpdate();
  }
}

bool Module::isSensorFall(int sensorID){
  return (m_sensors[sensorID]->isFallEdge());
}

bool Module::isSensorRise(int sensorID){
  return (m_sensors[sensorID]->isRiseEdge());
}

int Module::getSensorThresh(int sensorID){
  return (m_sensors[sensorID]->getThreshold());
}

bool Module::isSensorPastThresh(int sensorID){
  return (m_sensors[sensorID]->isPastThresh());
}

bool Module::wasSensorPastThresh(int sensorID){
  return (m_sensors[sensorID]->wasPastThresh());
}

char Module::id(){
  return m_id;
}

unsigned int Module::receiveCommands() {
  String receiving = Serial.readStringUntil('\n');
  unsigned int recCommands = 0;
  char charCommands[25];
  String strCommands = "";
  
  if(receiving.length() == 25) {
    receiving.toCharArray(charCommands, 25);

    for(int i = 0; i < receiving.length(); i++)
      if(charCommands[i] == m_id){ 
        strCommands += charCommands[i+1];
        strCommands += charCommands[i+2];
        strCommands += charCommands[i+3];
        recCommands = strCommands.toInt();
      }
  }
  
  return recCommands;
}

void Module::interpretCommands(unsigned int commands){
  unsigned int protocol = (commands & 0b11000000) >> 6;
}

//////////////////////////////////////////////////////////////////////////


/////////////////// End Module Class ////////////////////////////////////
EndModule::EndModule(int pinID, Sensor s0, Sensor s1, Sensor s2, Door d0, Door d1, Door d2, Door d3, Door d4, Door d5, SyringePump r0, SyringePump r1, SyringePump r2)
  : m_s0(s0), m_s1(s1), m_s2(s2), m_d0(d0), m_d1(d1), m_d2(d2), m_d3(d3), m_d4(d4), m_d5(d5), m_r0(r0), m_r1(r1), m_r2(r2)
{
  m_pinID = pinID;
  
  m_s0 = s0;
  m_s1 = s1;
  m_s2 = s2;
  m_sensors[0] = &m_s0;
  m_sensors[1] = &m_s1;
  m_sensors[2] = &m_s2;

  m_d0 = d0;
  m_d1 = d1;
  m_d2 = d2;
  m_d3 = d3;
  m_d4 = d4;
  m_d5 = d5;
  m_doors[0] = &m_d0;
  m_doors[1] = &m_d1;
  m_doors[2] = &m_d2;
  m_doors[3] = &m_d3;
  m_doors[4] = &m_d4;
  m_doors[5] = &m_d5;

  m_r0 = r0;
  m_r1 = r1;
  m_r2 = r2;
  m_syringePumps[0] = &m_r0;
  m_syringePumps[1] = &m_r1;
  m_syringePumps[2] = &m_r2;
}

void EndModule::moduleSetup(){
  // Calls setup fuinction for all sensors
  for(int i = 0; i < NUM_END_SENSORS; i++)
    m_sensors[i]->sensorSetup();
  
  // Calls setup function for all doors
  for(int i = 0; i < NUM_END_DOORS; i++)
    m_doors[i]->doorSetup();

  for(int i = 0; i < NUM_END_SYRINGE_PUMPS; i++){
    m_syringePumps[i]->syringeSetup();
  }
  m_needsToConfig = true;

  // Determines ID char of Module
  int idValIn = analogRead(m_pinID);
  idValIn = map(idValIn, 0, 1023, 0, 255);
  // Serial.print(idValIn); Serial.print(' ');

  char id = 'e';

  for(int i = 0; i < NUM_IDS; i++) {
    if(idValIn >= ID_VALS_OUT[i] - 4 * ID_RES && idValIn <= ID_VALS_OUT[i] + ID_RES)
      m_id = IDS[i];
  }
}

void EndModule::openDoor(int doorID){
  m_doors[doorID]->doorOpen();
}

void EndModule::closeDoor(int doorID){
  m_doors[doorID]->doorClose();
}

int EndModule::getSensorVal(int sensorID){
  return (m_sensors[sensorID]->getSensorVal());
}

void EndModule::checkSensors(){
  for(int i = 0; i < NUM_END_SENSORS; i++){
    m_sensors[i]->isPastThresh();
  }
}

bool EndModule::isSensorTrig(int sensorID){
  return (m_sensors[sensorID]->isFallEdge());
}

void EndModule::dispenseReward(int syringePumpID, float vol){
  m_syringePumps[syringePumpID]->dispenseMilliliters(vol);
}

char EndModule::id(){
  return m_id;
}

unsigned int EndModule::receiveCommands() {
  String receiving = Serial.readStringUntil('\n');
  unsigned int recCommands = 0;
  char charCommands[25];
  String strCommands = "";
  
  if(receiving.length() == 25) {
    receiving.toCharArray(charCommands, 25);

    for(int i = 0; i < receiving.length(); i++)
      if(charCommands[i] == m_id){ 
        strCommands += charCommands[i+1];
        strCommands += charCommands[i+2];
        strCommands += charCommands[i+3];
        recCommands = strCommands.toInt();
      }
  }
  
  return recCommands;
}

void EndModule::interpretCommands(unsigned int commands){
  unsigned int protocol = (commands & 0b11000000) >> 6;
}

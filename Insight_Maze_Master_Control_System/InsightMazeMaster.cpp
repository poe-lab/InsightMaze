#include <Arduino.h>
#include "InsightMazeMaster.h"

Master::Master(int pinsID[], int pinsLEDs[], int pinBtn, int pinCS){
  m_pinsModules = pinsID;
  m_pinsLEDs = pinsLEDs;
  m_pinBtn = pinBtn;
  m_pinCS = pinCS;

  m_btnVal = HIGH;
  m_btnPastVal = HIGH;
  m_btnCounter = 0;
}

void Master::masterSetup(){
  for(int i = 0; i < NUM_IDS; i++){
    pinMode(*(m_pinsModules + i), OUTPUT);
    analogWrite(*(m_pinsModules + i), ID_VALS_OUT[i]);
  }

  for(int i = 0; i < 3; i++){
    pinMode(*(m_pinsLEDs + i), OUTPUT);
    digitalWrite(*(m_pinsLEDs + i), LOW);
  }

  pinMode(m_pinBtn, INPUT_PULLUP);

  Serial.begin(9600);
  Serial1.begin(9600);

  Serial.print("Initializing SD card...");

  // see if the card is present and can be initialized:
  if (!SD.begin(m_pinCS)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    while (1);
  }
  Serial.println("card initialized.");

}

void Master::turnLED(char color){
  switch(color){
    case 'r':
      digitalWrite(*m_pinsLEDs, HIGH);
      digitalWrite(*(m_pinsLEDs + 1), LOW);
      digitalWrite(*(m_pinsLEDs + 2), LOW);
      break;

    case 'g':
      digitalWrite(*m_pinsLEDs, LOW);
      digitalWrite(*(m_pinsLEDs + 1), HIGH);
      digitalWrite(*(m_pinsLEDs + 2), LOW);
      break;

    case 'b':
      digitalWrite(*m_pinsLEDs, LOW);
      digitalWrite(*(m_pinsLEDs + 1), LOW);
      digitalWrite(*(m_pinsLEDs + 2), HIGH);
      break;

    case 'y':
      digitalWrite(*m_pinsLEDs, HIGH);
      digitalWrite(*(m_pinsLEDs + 1), HIGH);
      digitalWrite(*(m_pinsLEDs + 2), LOW);
      break;

    case 'c':
      digitalWrite(*m_pinsLEDs, LOW);
      digitalWrite(*(m_pinsLEDs + 1), HIGH);
      digitalWrite(*(m_pinsLEDs + 2), HIGH);
      break;

    case 'm':
      digitalWrite(*m_pinsLEDs, HIGH);
      digitalWrite(*(m_pinsLEDs + 1), LOW);
      digitalWrite(*(m_pinsLEDs + 2), HIGH);
      break;
  }
}

void Master::setCommands(int commands[]){
  m_commands = commands;
}

void Master::transmitCommands(){
  String transmission = "";

  for (int i = 0; i < NUM_IDS; i++) {
    transmission += IDS[i];
    
    if(*(m_commands + i) < 10) transmission += "00";
    else if(*(m_commands + i) < 100) transmission += "0";
    transmission += *(m_commands + i);
  }

  Serial1.println(transmission);
}

void Master::updateBtnVals(){
  m_btnPastVal = m_btnVal;
  m_btnVal = digitalRead(m_pinBtn);

  if(isBtnPressed()) m_btnCounter++;
}

bool Master::isBtnPressed(){
  return (m_btnPastVal && !m_btnVal);
}

unsigned int Master::btnCounter(){
  return m_btnCounter;
}

unsigned int Master::state(){
  int masterState;
  switch(m_btnCounter){
    case 1:
      masterState = 0;
      break;
    case 2:
      masterState = 1;
      break;
    default:
      if(m_btnCounter % 2 == 1) masterState = 2;
      else masterState = 3;
      break;
  }
  
  return masterState;
}

void Master::getPathsFromSD(){
  int pathNum = 0;
  String path = "";

  File pathFile = SD.open("paths.txt");

  if(pathFile){
    while(pathFile.available()){
      char dir = char(pathFile.read());
      if(dir != '\n')
        path +=  dir;
      else{
        m_paths[pathNum] = path;
        path = "";
        pathNum++;
      }
    }
  }
}

void Master::printPaths(){
  for(int i = 0; i < MAX_NUM_PATHS; i++){
    Serial.print("Path "); Serial.print(i); Serial.print(": "); Serial.println(m_paths[i]);
  }
}

String Master::getPath(int pathNum){
  return m_paths[pathNum];
}

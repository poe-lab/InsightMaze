#include <Arduino.h>
#include "InsightMazeMaster.h"

Master::Master(int pinsID[], int pinsLEDs[], int pinBtn, int pinCS, LiquidCrystal_I2C lcd){
  m_pinsModules = pinsID;
  m_pinsLEDs = pinsLEDs;
  m_pinBtn = pinBtn;
  m_pinCS = pinCS;
  m_lcd = &lcd;

  m_btnVal = HIGH;
  m_btnPastVal = HIGH;
  m_btnCounter = 0;
}

void Master::masterSetup(){
  m_lcd->init();                      // initialize the lcd 

  // Print a message to the LCD.
  m_lcd->backlight();
  printToLCD(3, "Welcome to", 2, "Insight Maze");
  pinMode(44, OUTPUT);
  digitalWrite(44, HIGH);

  delay(2000);
  
  for(int i = 0; i < NUM_IDS; i++){
    pinMode(*(m_pinsModules + i), OUTPUT);
    analogWrite(*(m_pinsModules + i), ID_VALS_OUT[i]);
  }

  for(int i = 0; i < 3; i++){
    pinMode(*(m_pinsLEDs + i), OUTPUT);
    digitalWrite(*(m_pinsLEDs + i), LOW);
  }

  pinMode(m_pinBtn, INPUT_PULLUP);

  Serial.begin(2400);
  Serial1.begin(9600);

  Serial.print("Initializing SD card...");
  printToLCD(3, "Initializing", 2, "SD card...");

  

  // see if the card is present and can be initialized:
  if (!SD.begin(m_pinCS)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    while (1);
  }
  
  
  Serial.println("card initialized.");
  printToLCD(1, "SD Initialized", 0, " ");

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

  Serial.println(transmission);
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

  pathFile.close();
}

void Master::printPaths(){
  for(int i = 0; i < MAX_NUM_PATHS; i++){
    Serial.print("Path "); Serial.print(i); Serial.print(": "); Serial.println(m_paths[i]);
  }
}

String Master::getPath(int pathNum){
  return m_paths[pathNum];
}

void Master::printToLCD(int startPos0, String line0, int startPos1, String line1){
  m_lcd->clear();
  m_lcd->setCursor(startPos0, 0);
  m_lcd->print(line0);
  m_lcd->setCursor(startPos1, 1);
  m_lcd->print(line1);
}

int* Master::splitPathCommands(String paths){
  char* dir;
  dir = paths.c_str();
  int* pathCommands;

  for(int i = 0; i < NUM_IDS; i++){
    switch(*(dir + i)){
      case 'l':
        *(pathCommands + i) = 0b00000010;
        break;
      case 'c':
        *(pathCommands + i) = 0b00000001;
        break;
      case 'r':
        *(pathCommands + i) = 0b00000011;
        break;
    }
  }

  return pathCommands;
  
}

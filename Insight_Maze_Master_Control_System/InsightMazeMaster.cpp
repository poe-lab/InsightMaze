#include <Arduino.h>
#include "InsightMazeMaster.h"

Master::Master(int pinsID[], int pinBtn, int pinCS) {
  m_pinsModules = pinsID;
  m_pinBtn = pinBtn;
  m_pinCS = pinCS;

  m_btnVal = HIGH;
  m_btnPastVal = HIGH;
  m_btnCounter = 0;
  m_pathNum = 0;
}

void Master::masterSetup() {

  for (int i = 0; i < NUM_IDS; i++) {
    pinMode(*(m_pinsModules + i), OUTPUT);
    analogWrite(*(m_pinsModules + i), ID_VALS_OUT[i]);
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

void Master::setCommands(int commands[]) {
  m_commands = commands;
}

void Master::transmitCommands() {
  String transmission = "";

  for (int i = 0; i < NUM_IDS; i++) {
    transmission += IDS[i];

    if (*(m_commands + i) < 10) transmission += "00";
    else if (*(m_commands + i) < 100) transmission += "0";
    transmission += *(m_commands + i);
  }

  Serial1.println(transmission);
  if (transmission != "s000a000b000c000d000r000") Serial.println(transmission);
}

void Master::updateBtnVals() {
  m_btnPastVal = m_btnVal;
  m_btnVal = digitalRead(m_pinBtn);

  if (isBtnPressed()) m_btnCounter++;
}

bool Master::isBtnPressed() {
  return (m_btnPastVal && !m_btnVal);
}

unsigned int Master::btnCounter() {
  return m_btnCounter;
}

unsigned int Master::state() {
  int masterState;
  switch (m_btnCounter) {
    case 1:
      masterState = 0;
      break;
    case 2:
      masterState = 1;
      break;
    default:
      if (m_btnCounter % 2 == 1) masterState = 2;
      else masterState = 3;
      break;
  }

  return masterState;
}

void Master::getPathsFromSD() {
  int pathNum = 0;
  String path = "";

  File pathFile = SD.open("paths.txt");

  if (pathFile) {
    while (pathFile.available()) {
      char dir = char(pathFile.read());
      if (dir != '\n')
        path +=  dir;
      else {
        m_paths[pathNum] = path;
        path = "";
        pathNum++;
      }
    }
  }

  pathFile.close();
}

void Master::printPaths() {
  for (int i = 0; i < MAX_NUM_PATHS; i++) {
    Serial.print("Path "); Serial.print(i); Serial.print(": "); Serial.println(m_paths[i]);
  }
}

String Master::getPath(int pathNum) {
  return m_paths[pathNum];
}

int* Master::sctSplitPathCommands(String paths, int hiddenRule) {
  int* pathCommands = new int[NUM_IDS];

  for (int i = 0; i < paths.length(); i++) {
    switch (paths[i]) {
      case 'l':
        *(pathCommands + i) = 0b10000000 | LEFT;
        break;
      case 'c':
        *(pathCommands + i) = 0b10000000 | CENTER;
        break;
      case 'r':
        *(pathCommands + i) = 0b10000000 | RIGHT;
        break;
    }
  }

  for (int i = NUM_IDS - paths.length(); i < NUM_IDS; i++) {
    if (i == NUM_IDS - 1) *(pathCommands + NUM_IDS - 1) = *(pathCommands + hiddenRule);
    else *(pathCommands + i) = 0;

  }

  return pathCommands;
}

void Master::sctProtocol(int hiddenRule) {
  updateBtnVals();

  if (isBtnPressed()) {
    Serial.print("state: "); Serial.println(state());

    switch (state()) {
      case 0:
        Serial.println("Reading SD Card");
        getPathsFromSD();
        Serial.println("Done...waiting for button press.");
        digitalWrite(13, LOW);
        break;
      case 1:
        printPaths();
        Serial.println("Press button to configure first layout.");
        break;
      case 2:
        if (getPath(m_pathNum) == "" || m_pathNum >= MAX_NUM_PATHS) {
          Serial.println("No more paths to run.");
        }
        else {
          Serial.println("Configuring " + getPath(m_pathNum) + " layout..." );

          setCommands(sctSplitPathCommands(getPath(m_pathNum), hiddenRule));

          Serial.print("Check that configuration is correct. ");
          Serial.println("Waiting for button press...");
          digitalWrite(13, HIGH);
        }
        break;
      case 3:
        if (getPath(m_pathNum) == "" || m_pathNum >= MAX_NUM_PATHS) {
          Serial.println("No more paths to run.");
        }
        else {
          Serial.println("Go.");
          Serial.println("Press button upon completion...");
          digitalWrite(13, LOW);
          m_pathNum++;
        }
        break;
    }

  }
  else setCommands(DO_NOTHING);

  transmitCommands();
}

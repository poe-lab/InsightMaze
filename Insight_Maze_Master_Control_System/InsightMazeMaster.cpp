#include <Arduino.h>
#include "InsightMazeMaster.h"

Master::Master(int pinsID[], int pinsLEDs[], int pinBtn){
  m_pinsModules = pinsID;
  m_pinsLEDs = pinsLEDs;
  m_pinBtn = pinBtn;
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

}

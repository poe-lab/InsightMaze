#include "SyringePump.h"
#include <Arduino.h>

SyringePump::SyringePump(int stepPin, int dirPin, float spmL, float maxV) {
  m_spmL = spmL;
  m_mLps = 1/spmL;
  m_stepPin = stepPin;
  m_dirPin = dirPin;
  m_maxVol = maxV; 
}

void SyringePump::syringeSetup() {
  pinMode(m_stepPin, OUTPUT);
  pinMode(m_dirPin, OUTPUT);
}

void SyringePump::dispenseMilliliters(float vol) {
  
  if(vol > 0)
    dirUp();
  else
    dirDown();

  int numSteps = abs(vol) * m_spmL;

  for(int i = 0; i < numSteps; i++)
    stepMotor();
}


// PRIVATE ==============================================

void SyringePump::dirDown() {
  digitalWrite(m_dirPin, HIGH);
  m_isDirUp = false;
}

void SyringePump::dirUp() {
  digitalWrite(m_dirPin, LOW);
  m_isDirUp = true;
}

void SyringePump::stepMotor() {
  digitalWrite(m_stepPin, HIGH);
  delayMicroseconds(SYRINGE_STEP_DELAY);
  digitalWrite(m_stepPin, LOW);

  if (m_isDirUp)
    m_volume += m_mLps;
  else
    m_volume -= m_mLps;
}





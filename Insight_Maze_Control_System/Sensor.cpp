#include "Sensor.h"
#include <Arduino.h>

Sensor::Sensor(int pin) {
  m_pin = pin;  
  m_isPastThresh = false;
  m_wasPastThresh = false;
}

void Sensor::sensorSetup() {
  pinMode(m_pin, INPUT);
  m_ambientLight = analogRead(m_pin);
  m_thresh = m_ambientLight - SENSOR_THRESHOLD_DIFF;
}

void Sensor::sensorUpdate() {
  int sensorVal = analogRead(m_pin);

  m_wasPastThresh = m_isPastThresh;

  if(sensorVal < m_ambientLight - SENSOR_THRESHOLD_DIFF){
    m_isPastThresh = true;
  }
  else
    m_isPastThresh = false;
}

bool Sensor::wasPastThresh(){
  return m_wasPastThresh;
}

bool Sensor::isPastThresh(){
  return m_isPastThresh;
}

bool Sensor::isFallEdge(){
  bool isFallEdge = false;
  if(!m_isPastThresh && m_wasPastThresh)
    isFallEdge = true;
  return isFallEdge;
}

bool Sensor::isRiseEdge(){
  bool isRiseEdge = false;
  if(m_isPastThresh && !m_wasPastThresh)
    isRiseEdge = true;
  return isRiseEdge;
}

int Sensor::getSensorVal() {
  return analogRead(m_pin);
}

int Sensor::getThreshold() {
  return m_thresh;
}

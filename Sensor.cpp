#include "Sensor.h"
#include <Arduino.h>

Sensor::Sensor(int pin) {
  m_pin = pin;  
  m_isPastThresh = false;
  m_wasPastThresh = false;
  m_isTrig = false;
}

void Sensor::sensorSetup() {
  pinMode(m_pin, INPUT);
  m_ambientLight = analogRead(m_pin);
  m_thresh = m_ambientLight - SENSOR_THRESHOLD_DIFF;
}

bool Sensor::isPastThresh() {
  int sensorVal = analogRead(m_pin);

  if(sensorVal < m_ambientLight - SENSOR_THRESHOLD_DIFF || sensorVal > m_ambientLight + SENSOR_THRESHOLD_DIFF){
    m_isPastThresh = true;
    m_wasPastThresh = true;
  }
  else
    m_isPastThresh = false;

  return m_isPastThresh;
}

bool Sensor::wasPastThresh(){
  return m_wasPastThresh;
}

bool Sensor::isTrig(){
  if(!m_isPastThresh && m_wasPastThresh)
    m_isTrig = true;
  return m_isTrig;
}

int Sensor::getSensorVal() {
  return analogRead(m_pin);
}

int Sensor::getThreshold() {
  return m_thresh;
}

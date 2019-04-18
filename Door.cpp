#include "Door.h"
#include <Arduino.h>
#include <Servo.h>

Door::Door(int pin, int posOpen, int posClose) { //
  m_pin = pin;
  m_isOpen = true; //
  m_posOpen = posOpen;
  m_posClose = posClose;
}

void Door::doorSetup() { //
  m_servo.attach(m_pin);
}

void Door::doorOpen() { //
  if (!m_isOpen) {
    m_servo.write(m_posOpen);
    m_isOpen = true;
  }
}

void Door::doorClose() {
  if (m_isOpen) {
    //Fast close
    //    m_servo.write(m_posClose);
    // Slow Close
    int pos = m_posOpen;
    while (pos != m_posClose) {
      m_servo.write(pos);
      if (m_posOpen < m_posClose) pos++; //incremental position movement by 1
      else pos--;
    }

    m_isOpen = false;
  }

}

bool Door::isOpen() {
  return m_isOpen;
  
}

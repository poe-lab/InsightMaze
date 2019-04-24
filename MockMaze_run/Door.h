#include <Servo.h>

class Door {
  public:
    Door(int pin, int posOpen, int posClose);
    void doorSetup();
    void doorOpen();
    void doorClose();
    bool isOpen(); // tells you what state the door is in

  private: // these variables are not supposed to be directly used
    int m_pin;
    bool m_isOpen;
    int m_posOpen;
    int m_posClose;
    Servo m_servo;
};

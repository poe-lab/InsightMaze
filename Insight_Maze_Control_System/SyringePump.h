const int SYRINGE_STEP_DELAY = 500;
const int WAIT_AFTER_PIPETTE = 10;

class SyringePump {
  public:
    SyringePump(int stepPin, int dirPin, float spmL, float maxV);

    void syringeSetup();    // sets up pins for syringe pump
    void stepMotor();   // steps and updates position accordingly
    void dispenseMilliliters(float vol); // dispenses vol of mL
    
    void dirDown();     // changes pindir for stepper to down
    void dirUp();       // changes pindir for stepper to up
    
  private:    
    int m_stepPin;      // 
    int m_dirPin;       // 
    int m_isDirUp;      // dirPin current value
    float m_spmL;        // step -> volume conversion factor
    float m_mLps;        // volume -> step conversion factor
    float m_volume;     // current volume in pipette
    float m_maxVol;     // maximum volume able to be stored
};



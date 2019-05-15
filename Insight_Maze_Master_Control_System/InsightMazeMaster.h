
const int NUM_MAIN_SENSORS = 4;
const int NUM_MAIN_DOORS = 6;
const int NUM_START_SENSORS = 4;
const int NUM_START_DOORS = 6;
const int NUM_END_SENSORS = 3;
const int NUM_END_DOORS = 6;
const int NUM_END_SYRINGE_PUMPS = 3;

const int ID_VALS_OUT[] = {0, 51, 102, 153, 204, 255};

const int ID_RES = 10;
const int NUM_IDS = sizeof(ID_VALS_OUT) / sizeof(ID_VALS_OUT[0]);
const char IDS[] = {'s', 'a', 'b', 'c', 'd', 'r'};

class Master{
  public:
    Master(int pinsID[], int pinsLED[], int pinBtn);
    void masterSetup();

  private:
    int *m_pinsModules;
    int *m_pinsLEDs;

    int m_pinRedLED;
    int m_pinGreenLED;
    int m_pinBlueLED;
    int m_pinBtn;
    
  
    
};

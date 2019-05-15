#include <SPI.h>
#include <SD.h>

const int ID_VALS_OUT[] = {0, 51, 102, 153, 204, 255};
const int ID_RES = 10;
const int NUM_IDS = sizeof(ID_VALS_OUT) / sizeof(ID_VALS_OUT[0]);
const char IDS[] = {'s', 'a', 'b', 'c', 'd', 'r'};

const int NUM_STATES = 3;
const int MAX_NUM_PATHS = 60;

const int DO_NOTHING[] = {0, 0, 0, 0, 0, 0};

class Master{
  public:
    Master(int pinsID[], int pinsLEDs[], int pinBtn, int pinCS);
    void masterSetup();
    void setCommands(int commands[]);
    void transmitCommands();
    void updateBtnVals();
    bool isBtnPressed();
    unsigned int btnCounter();
    unsigned int state();
    void getPathsFromSD();
    void printPaths();
    String getPath(int pathNum);

  private:
    int *m_pinsModules;
    int *m_pinsLEDs;
    int m_pinBtn;
    int m_pinCS;

    bool m_btnVal;
    bool m_btnPastVal;
    unsigned int m_btnCounter;
    
    String m_paths[MAX_NUM_PATHS];

    int *m_commands;

    void turnLED(char color);
    
};

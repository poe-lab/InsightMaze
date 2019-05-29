#include <SPI.h>
#include <SD.h>
#include <Wire.h>

#define NUM_STATES 3
#define MAX_NUM_PATHS 60

#define RIGHT 1
#define LEFT 2
#define CENTER 3

const int ID_VALS_OUT[] = {0, 51, 102, 153, 204, 255};
const int NUM_IDS = sizeof(ID_VALS_OUT) / sizeof(ID_VALS_OUT[0]);
const char IDS[] = {'s', 'a', 'b', 'c', 'd', 'r'};

const int DO_NOTHING[] = {0, 0, 0, 0, 0, 0};

class Master {
  public:
    Master(int pinsID[], int pinBtn, int pinSDCS);            // Constructor for master class states the pins used for identifying modules, pin for button, and pin used for CS of SD card reader
    void masterSetup();                                       // Sets up master: declares pins as outputs and send out proper signals to each one; sets button pin as input 
    void setCommands(int commands[]);                         // Takes array of length 6 to send to each module and stores as master's commands
    void transmitCommands();                                  // Transmits the master's stored commands
    void updateBtnVals();                                     // MUST have at the beginning of each loop to update button state
    bool isBtnPressed();                                      // Returns true if the button was pressed during the loop and updates m_btnCounter
    unsigned int btnCounter();                                // Returns the number of button presses (m_btnCounter)
    unsigned int state();                                     // Returns state based on the number of button presses
    void getPathsFromSD();                                    // Reads SD card and stores the paths in the master class
    void printPaths();                                        // Prints all the stored paths within the master class
    String getPath(int pathNum);                              // Returns the string of specified path number
    int* sctSplitPathCommands(String paths, int hiddenRule);  // Creates array for specific path and hidden rule location                                      
    void sctProtocol(int hiddenRule);                         // Executes the protocol for SCT experiments

  private:
    int *m_pinsModules;
    int m_pinBtn;
    int m_pinCS;

    bool m_btnVal;
    bool m_btnPastVal;
    unsigned int m_btnCounter;

    String m_paths[MAX_NUM_PATHS];
    int m_pathNum;  
    int *m_commands;

};

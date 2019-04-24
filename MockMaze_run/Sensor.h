
const int SENSOR_THRESHOLD = 850;
const int SENSOR_THRESHOLD_DIFF = 60; //if reading of sensor goes 60 beyond ambient light reading, indicates object in front of sensor

class Sensor{
  public:
  Sensor(int pin);
  void sensorSetup(); //takes ambient light reading and declares all pins and 
  bool isPastThresh(); 
  bool wasPastThresh();
  bool isTrig();
  int getSensorVal();
  int getThreshold();
  
  
  private:
  int m_pin;
  int m_thresh;
  bool m_isPastThresh;
  bool m_wasPastThresh;
  bool m_isTrig;
  int m_ambientLight;
};

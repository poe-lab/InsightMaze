
#define SENSOR_THRESHOLD_DIFF 50

class Sensor{
  public:
  Sensor(int pin);
  void sensorSetup();
  void sensorUpdate();
  bool isPastThresh();
  bool wasPastThresh();
  bool isFallEdge();
  bool isRiseEdge();
  int getSensorVal();
  int getThreshold();
  
  
  private:
  int m_pin;
  int m_thresh;
  bool m_isPastThresh;
  bool m_wasPastThresh;
  int m_ambientLight;
};

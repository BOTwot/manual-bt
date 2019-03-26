
#include <Arduino.h>
#include <Wire.h>
#include <I2C_Anything.h>
class GyroRead
{
  private:
    float angle;
    int  _addr;
    float rtvalue;
  public:
    void beginn(int addr)
    
    {
      _addr=addr;
      Wire.begin();
      Wire.beginTransmission(addr);

    }
    float getAngle()
    {
      if (Wire.requestFrom(_addr, 4)) {
        rtvalue = I2C_readAnything (angle);
      }
      return angle;
    }
};

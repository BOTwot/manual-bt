#include "GyroRead.h"
GyroRead a;
float angle;
void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  a.beginn(8);
}

void loop() {
  // put your main code here, to run repeatedly:
  angle = a.getAngle();
  Serial.println(angle);
}

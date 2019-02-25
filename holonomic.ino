#include<XBOXUSB.h>
#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif
#include <SPI.h>
#define m1c 2
#define m1a 3
#define m2c 4
#define m2a 5
#define m3c 44
#define m3a 45
int pwm1,pwm2,pwm3; // pwm to each motor
USB Usb;
XBOXUSB Xbox(&Usb);
void setup() {
  pinMode(m1c,OUTPUT);
  pinMode(m1a,OUTPUT);
  pinMode(m2c,OUTPUT);
  pinMode(m2a,OUTPUT);
  pinMode(m3c,OUTPUT);
  pinMode(m3a,OUTPUT);
  Serial.begin(115200);
  #if !defined(__MIPSEL__)
  while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
  #endif
  if (Usb.Init() == -1) {
  Serial.print(F("\r\nOSC did not start"));
  while (1); //halt
  }
  Serial.print(F("\r\nXBOX USB Library Started"));
}   

void loop() 
{
  Usb.Task();
  if (Xbox.Xbox360Connected) 
 {    
  if (Xbox.getButtonPress(L2))  
  {
      rl(Xbox.getButtonPress(L2));
      Serial.print("L2: ");
      Serial.print(Xbox.getButtonPress(L2));    
  }  
  else if(Xbox.getButtonPress(R2))
  {
     rr(Xbox.getButtonPress(R2));
     Serial.print("\tR2: ");
     Serial.println(Xbox.getButtonPress(R2));
  }
  if (Xbox.getAnalogHat(LeftHatY) > 7500 || Xbox.getAnalogHat(LeftHatY) < -7500 || Xbox.getAnalogHat(RightHatX) > 7500 || Xbox.getAnalogHat(RightHatX) < -7500 ) 
  {
      if (Xbox.getAnalogHat(RightHatX) > 7500)  //right turn
       {
        right(Xbox.getAnalogHat(RightHatX));
//        Serial.print(F("RIGHT: "));
//        Serial.print(Xbox.getAnalogHat(RightHatX));
//        Serial.print("\t");
       }
      else if(Xbox.getAnalogHat(RightHatX) < -7500) //left turn
       {
        left(Xbox.getAnalogHat(RightHatX));
//        Serial.print(F("LEFT: "));
//        Serial.print(Xbox.getAnalogHat(RightHatX));
//        Serial.print("\t");
       }
      if (Xbox.getAnalogHat(LeftHatY) > 7500)
       {
        forward(Xbox.getAnalogHat(LeftHatY));
//        Serial.print(F("FORWARD: "));
//        Serial.print(Xbox.getAnalogHat(LeftHatY)); //forward
//        Serial.print("\t");
       }
      else if( Xbox.getAnalogHat(LeftHatY) < -7500)
       {
        backward(Xbox.getAnalogHat(LeftHatY));
//        Serial.print(F("BACKWARD: "));
//        Serial.print(Xbox.getAnalogHat(LeftHatY)); //backward
//        Serial.print("\t");
       }
       Serial.println();  
   } 
 }
 delay(55);
 forward(7500); //initial if no joystick command
 backward(-7500);
 right(7500);
 left(-7500);
 rl(0);
 rr(0);
}
void forward(int f )
{
 pwm2 = pwm3 = map(f,7500,32767,0,255);
 analogWrite(m2a,pwm2);
 analogWrite(m3a,pwm3);
Serial.println(pwm2);
}
void backward(int b )
{
 pwm2 = pwm3 = map(b,-7500,-32768,0,255);
 analogWrite(m2c,pwm2);
 analogWrite(m3c,pwm3);
Serial.println(pwm2);
}
void right(int r )
{
 pwm1 = pwm3 = map(r,7500,32767,0,255);
 analogWrite(m1a,pwm1);
 analogWrite(m3a,pwm3);
Serial.println(pwm1);
}
void left(int l )
{
 pwm1 = pwm2 = map(l,-7500,-32768,0,255);
 analogWrite(m1c,pwm1);
 analogWrite(m2a,pwm2);
Serial.println(pwm1);
}
void rl(int a)
{
  pwm1 = pwm2 = pwm3 = map(a,0,255,0,255);
  analogWrite(m1a,pwm1);
  analogWrite(m2c,pwm1);
  analogWrite(m3c,pwm1);
}
void rr(int b)
{
  pwm1 = pwm2 = pwm3 = map(b,0,255,0,255);
  analogWrite(m1c,pwm1);
  analogWrite(m2a,pwm2);
  analogWrite(m3a,pwm3);
}

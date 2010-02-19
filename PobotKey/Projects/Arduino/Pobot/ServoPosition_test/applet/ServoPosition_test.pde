#include "Servo.h"
#include "PositionServo.h"

PositionServo serv;

void setup()
{
  pinMode(13,OUTPUT);
  serv.attach(10);
  //
  Serial.begin(38400);


}

void loop()
{    
  while (Serial.available() > 0)
  {
    if (Serial.read() == '+') {
      serv.write(0);
    } 
    else {
      serv.write(180);
    }
  }


  //
  Serial.println(serv.position());
  // 
  delay(333);

}

int val = 0;
#include <Servo.h>
#define sensor 2
Servo myservo;


void setup() 
{
  Serial.begin(9600);
  myservo.attach(3);
  pinMode(sensor, INPUT);

}

void loop() 
{
  val = digitalRead(sensor);
  Serial.println(val);
  delay(100);

  if(val == HIGH){

  myservo.write(180);
  delay(2000);

  } else{

  myservo.write(0);

  }


}

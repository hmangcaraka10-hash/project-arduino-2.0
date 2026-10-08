#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <Servo.h>
#define infrared 7
#define LED 8   
LiquidCrystal_I2C lcd(0x27, 16, 2);

Servo myservo;


void setup() 
{


 pinMode(LED, OUTPUT);
 lcd.init();
 lcd.backlight();
 pinMode(infrared, INPUT);
 Serial.begin(9600);
 myservo.attach(9);


}

void loop() 
{

 lcd.clear();
 lcd.setCursor(0,0);
 lcd.println("status: ");
 
 
  lcd.setCursor(0, 1);

 if(digitalRead(infrared) == LOW) {
  lcd.print("objek Terdeteksi");
  digitalWrite(LED, HIGH);
  Serial.println("OBJECT_DETECTED");
  myservo.write(0);

 } else {
  lcd.print("objek tidak ada");
  Serial.println("OBJECT_NOT DETECTED");
  digitalWrite(LED, LOW);
  myservo.write(360);


 }

delay(300);

}

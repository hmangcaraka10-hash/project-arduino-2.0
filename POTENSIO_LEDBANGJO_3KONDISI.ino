int val = 0;
#define MERAH 12
#define KUNING 11
#define HIJAU 10

void setup() 
{
 Serial.begin(9600);
 pinMode(MERAH, OUTPUT);
 pinMode(KUNING, OUTPUT);
 pinMode(HIJAU, OUTPUT);
}

void loop() 
{
  val = analogRead(A0);
  Serial.println(val);


  if(val < 300){
   digitalWrite(MERAH, LOW);
   digitalWrite(KUNING, LOW);
   digitalWrite(HIJAU, HIGH);
  }
  else if(val > 300 && val < 700){
   digitalWrite(MERAH, LOW);
   digitalWrite(KUNING, HIGH);
   digitalWrite(HIJAU, LOW);
  }
 else if(val > 700){
   digitalWrite(MERAH, HIGH);
   digitalWrite(KUNING, LOW);
   digitalWrite(HIJAU, LOW);
  }
}

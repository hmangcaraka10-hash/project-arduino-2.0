#include <SPI.h>
#include <MFRC522.h>

// ================= PIN =================
#define RST_PIN 9
#define SS_PIN  10

int in   = 7;   // Tombol
int sole = 4;   // Solenoid

#define in1 3
#define in2 6
int izin;
String strUID = "";
unsigned long TIMEOUT = 5000;
unsigned long starttime = 0;
unsigned long startingalarm = 0;

// ================= RFID =================
MFRC522 rfid(SS_PIN, RST_PIN);

// UID kartu yang diizinkan
String targetUID = "D1 2D D4 06";

// ================= STATE =================
bool state = LOW;

int now = HIGH;
int last = HIGH;

unsigned long debounce = 100;
unsigned long lastDebounceTime = 0;

unsigned long lastRFIDTime = 0;
const unsigned long RFID_DELAY = 1500;

// =========================================
// TOGGLE OUTPUT
// =========================================

// Menggunakan pin 8 untuk buzzer/speaker (sesuaikan dengan rangkainmu)
int melody = 3; 

void ALARM() {
  pinMode(melody, OUTPUT);
  
for (int i = 0; i < 10; i++) {
    tone(melody, 880); 
    delay(300);
    tone(melody, 660); 
    delay(300);
  }
    
  
 startingalarm = millis();
 if(millis() - startingalarm <= TIMEOUT){
  noTone(melody);

 }

}


void toggleOutput()
{
  state = !state;
  digitalWrite(sole, state);
  Serial.print("Solenoid : ");
  Serial.println(state ? "ON" : "OFF");
}

// =========================================
// TOMBOL
// =========================================
void Tombol()
{
  now = digitalRead(in);

  // INPUT_PULLUP:
  // HIGH = tidak ditekan
  // LOW  = ditekan

  if (now == LOW &&
      last == HIGH &&
      (millis() - lastDebounceTime > debounce))
  {
    toggleOutput();

    lastDebounceTime = millis();
  }

  last = now;
}

// =========================================
// RFID
// =========================================
void readNUID()
{

  if (!rfid.PICC_IsNewCardPresent())
    return;

  if (!rfid.PICC_ReadCardSerial())
    return;

 

  for (byte i = 0; i < rfid.uid.size; i++)
  {
    if (rfid.uid.uidByte[i] < 0x10)
      strUID += "0";

    strUID += String(rfid.uid.uidByte[i], HEX);

    if (i < rfid.uid.size - 1)
      strUID += " ";
  }

  strUID.toUpperCase();

  Serial.print("UID Terbaca : ");
  Serial.println(strUID);

  if (strUID == targetUID)
  {
    if (millis() - lastRFIDTime > RFID_DELAY)
    {
      Serial.println("Akses Diterima");
      izin = true;
      starttime = millis();

      lastRFIDTime = millis();
    }
  }
  else if(strUID == "53 50 8C 35 74 00 01"){
  izin = false;

  ALARM();
  
  
  }
  else
  {
    Serial.println("Akses Ditolak");
   
  }

  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();
  return(strUID);

}

// =========================================
// SETUP
// =========================================
void setup()
{
  Serial.begin(9600);

  pinMode(in, INPUT_PULLUP);

  pinMode(sole, OUTPUT);
  digitalWrite(sole, state);

  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);

  SPI.begin();
  rfid.PCD_Init();

  delay(4);

  Serial.println("RFID Ready");
  Serial.println("Tempelkan kartu...");
}

// =========================================
// LOOP
// =========================================
void loop()
{
  strUID = "";
  readNUID();
  

  if(izin == true && millis() - starttime <= TIMEOUT){
  Tombol();

  }


}
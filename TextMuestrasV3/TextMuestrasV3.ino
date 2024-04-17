/*
a diferencia de la V2 en esta se muestran las habitacion y el estado del dispostivo en la misma True=esta en la sala
False= no esta en la sala

*/

#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>


#define RST_PIN 9
#define SS_1_PIN 10
#define SS_2_PIN 8

MFRC522 mfrc522[2];
LiquidCrystal_I2C lcd(0x27, 16, 2);
String LcdText[2] = {"", ""};
bool StateRoom[2]= {false,false};


void setup() {
  Serial.begin(9600);
  SPI.begin();
  lcd.init();

  mfrc522[0].PCD_Init(SS_1_PIN, RST_PIN);
  mfrc522[1].PCD_Init(SS_2_PIN, RST_PIN);


  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Iniciando");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Wait for card...");
}

void loop() {
  for (int i = 0; i < 2; i++) {
    if (mfrc522[i].PICC_IsNewCardPresent() && mfrc522[i].PICC_ReadCardSerial()) {
      lcd.clear();

      StateRoom[i]= !StateRoom[i];
      //LcdText[i]=dump_byte_array(mfrc522[i].uid.uidByte, mfrc522[i].uid.size);
      //PrintLcd(LcdText[0],LcdText[1]);
      PrintLcd(StateRoom[0] ? "True":"False",StateRoom[1] ? "True":"False");
      mfrc522[i].PICC_HaltA();
      mfrc522[i].PCD_StopCrypto1();
    }
  }
}

void PrintLcd(String p1, String p2){
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Room 1:");
      lcd.print(p1);
      lcd.setCursor(0,1);
      lcd.print("Room 2:");
      lcd.print(p2);
}

String dump_byte_array(byte *buffer, byte bufferSize) {
  String uidStr = "";

  for (byte i = 0; i < bufferSize; i++) {
    uidStr += (buffer[i] < 0x10 ? "0" : "");
    uidStr += String(buffer[i], HEX);
  }
  return uidStr;
}

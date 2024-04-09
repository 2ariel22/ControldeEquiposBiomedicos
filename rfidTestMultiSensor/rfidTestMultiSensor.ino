#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN 9
#define SS_1_PIN 10
#define SS_2_PIN 8

MFRC522 mfrc522[2]; // Solo necesitamos 2 lectores RFID

void setup() {
  Serial.begin(9600);
  SPI.begin();

  mfrc522[0].PCD_Init(SS_1_PIN, RST_PIN);
  mfrc522[1].PCD_Init(SS_2_PIN, RST_PIN);
}

void loop() {
  for (int i = 0; i < 2; i++) {
    if (mfrc522[i].PICC_IsNewCardPresent() && mfrc522[i].PICC_ReadCardSerial()) {
      Serial.print("UID ");
      Serial.print(i + 1);
      Serial.print(": ");
      dump_byte_array(mfrc522[i].uid.uidByte, mfrc522[i].uid.size);
      Serial.println();
      mfrc522[i].PICC_HaltA();
      mfrc522[i].PCD_StopCrypto1();
    }
  }
}

void dump_byte_array(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], HEX);
  }
}

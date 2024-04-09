#include <SPI.h>
#include <MFRC522.h>
#include <LinkedList.h>
#include <LiquidCrystal_I2C.h>

#define RST_PIN 9  // Pin 9 para el reset del RC522
#define SS_PIN 10  // Pin 10 para el SS (SDA) del RC522

MFRC522 mfrc522(SS_PIN, RST_PIN);

LiquidCrystal_I2C lcd(0x27, 16, 2);

LinkedList<String> Tarjetas;
LinkedList<bool> TarjetasEstados;

int buscarIndice(LinkedList<String>& lista, String elemento) {
  for (int i = 0; i < lista.size(); i++) {
    if (lista.get(i) == elemento) {
      return i;
    }
  }
  return -1;
}

void setup() {
  Serial.begin(9600);  // Iniciamos la comunicación serial
  SPI.begin();         // Iniciamos el Bus SPI
  mfrc522.PCD_Init();  // Iniciamos el MFRC522
  Serial.println("Lectura del UID");
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.print("wait for tarjeta");
}

void loop() {

  if (mfrc522.PICC_IsNewCardPresent()) {

    if (mfrc522.PICC_ReadCardSerial()) {
      String uidStr = "";

      for (byte i = 0; i < mfrc522.uid.size; i++) {
        // Concatenamos los bytes del UID en un string
        uidStr += (mfrc522.uid.uidByte[i] < 0x10 ? "0" : "");
        uidStr += String(mfrc522.uid.uidByte[i], HEX);
      }
      int indice = buscarIndice(Tarjetas, uidStr);
      if (indice != -1) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print(Tarjetas[0]);

        delay(100);

      } else {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("add new card");
        Tarjetas.add(uidStr);
      }



      mfrc522.PICC_HaltA();
    }
  }
}

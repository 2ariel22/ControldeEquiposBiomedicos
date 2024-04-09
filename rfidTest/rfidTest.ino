#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN_1   9   // Pin 9 para el reset del primer RC522
#define SS_PIN_1    10   // Pin 10 para el SS (SDA) del primer RC522

#define SS_PIN_2    8   // Pin 7 para el SS (SDA) del segundo RC522

MFRC522 mfrc522_1(SS_PIN_1, RST_PIN_1); // Creamos el objeto para el primer RC522
MFRC522 mfrc522_2(SS_PIN_2, RST_PIN_1); // Creamos el objeto para el segundo RC522

void setup() {
    Serial.begin(9600); // Iniciamos la comunicación serial
    SPI.begin();        // Iniciamos el Bus SPI
    mfrc522_1.PCD_Init(); // Iniciamos el primer MFRC522
    mfrc522_2.PCD_Init(); // Iniciamos el segundo MFRC522

    Serial.println("Lectura del UID");
}

void loop() {
    // Revisamos si hay nuevas tarjetas presentes en el primer lector
    if (mfrc522_1.PICC_IsNewCardPresent()) {  
        // Seleccionamos una tarjeta
        if (mfrc522_1.PICC_ReadCardSerial()) {
            // Enviamos serialmente su UID
            Serial.print("Card UID (Reader 1):");
            for (byte i = 0; i < mfrc522_1.uid.size; i++) {
                Serial.print(mfrc522_1.uid.uidByte[i] < 0x10 ? " 0" : " ");
                Serial.print(mfrc522_1.uid.uidByte[i], HEX);   
            } 
            Serial.println();
            // Terminamos la lectura de la tarjeta actual
            mfrc522_1.PICC_HaltA();         
        }      
    }   

    // Revisamos si hay nuevas tarjetas presentes en el segundo lector
    if (mfrc522_2.PICC_IsNewCardPresent()) {  
        // Seleccionamos una tarjeta
        if (mfrc522_2.PICC_ReadCardSerial()) {
            // Enviamos serialmente su UID
            Serial.print("Card UID (Reader 2):");
            for (byte i = 0; i < mfrc522_2.uid.size; i++) {
                Serial.print(mfrc522_2.uid.uidByte[i] < 0x10 ? " 0" : " ");
                Serial.print(mfrc522_2.uid.uidByte[i], HEX);   
            } 
            Serial.println();
            // Terminamos la lectura de la tarjeta actual
            mfrc522_2.PICC_HaltA();         
        }      
    }   
}

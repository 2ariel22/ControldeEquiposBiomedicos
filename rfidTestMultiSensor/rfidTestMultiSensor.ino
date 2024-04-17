#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN 0
#define SS_1_PIN 5
#define SS_2_PIN 4
#define SS_3_PIN 2
#define SS_4_PIN 25
#define SS_5_PIN 26


MFRC522 mfrc522[5];  //hacemos una lista de objetos tipo: mfrc522 porque tenemos 5 sensoseres del mismo tipo

byte ActualUID[4]; //almacenará el código del Tag leído
byte Tensometro[4]= {0x43, 0x17, 0xD9, 0x0D} ; //Esto son los codigos de cada tarjeta
byte CarroDePoDo[4]= {0x23, 0x93, 0x76, 0xA5} ; 
byte Monitor[4]= {0x33, 0x96, 0x38, 0x16} ; 
byte BombaDeInfusion[4]= {0x93, 0xFd, 0x19, 0x16} ; 
byte Desfribilador[4]= {0x03, 0xE1, 0x89, 0x1F} ; 

String Place[5] = {"E/S Taller","Bodega Taller","Salida Taller","false","false"}; //Lugares disponibles en el hospital

void setup() {
  Serial.begin(115200);
  // tiempo de espera para que energicemos los sensores con la fuente externa
  SPI.begin();  // se inicia la comunicacion spi para "hablar" con los sensores Rfid
  delay(200);
  mfrc522[0].PCD_Init(SS_1_PIN, RST_PIN);  //iniciamos manualmente cada sensor
  delay(200);
  mfrc522[1].PCD_Init(SS_2_PIN, RST_PIN);
  delay(200);
  mfrc522[2].PCD_Init(SS_3_PIN, RST_PIN);
  delay(200);
  mfrc522[3].PCD_Init(SS_4_PIN, RST_PIN);
  delay(200);
  mfrc522[4].PCD_Init(SS_5_PIN, RST_PIN);
  delay(200);

  Serial.print("Tarjetas Iniciadas");  //damos aviso que ya se iniciaron
}

void loop() {
  for (int i = 0; i < 5; i++) {  //usamos este for para recorrer la lista de Rfid y luego verificar si han detectado algun equipo medico
    if (mfrc522[i].PICC_IsNewCardPresent() && mfrc522[i].PICC_ReadCardSerial()) {
      //Serial.print("UID ");
      //Serial.print(i + 1);
      //Serial.print(": ");
      dump_byte_array(mfrc522[i].uid.uidByte, mfrc522[i].uid.size);
      Serial.println();
      mfrc522[i].PICC_HaltA();
      mfrc522[i].PCD_StopCrypto1();
      if (i==2)// si i ==2 quiere decir que estamos en la salida de la bodega
        Serial.println("Ningun equipo medico puede Salir sin Autorizacion");
      if(compareArray(ActualUID, Tensometro))
        Serial.println("Tensometro en "+ Place[i]); // la ubicacion en el arreglo place coincide con el orden de los lectores. 
        // por lo tanto "i" es igual al lugar en el que se encuentra 
      else if(compareArray(ActualUID, CarroDePoDo))
        Serial.println("CarroDePoDo en "+ Place[i]);
    
    else if(compareArray(ActualUID, Monitor))
        Serial.println("Monitor en "+ Place[i]);
    
    else if(compareArray(ActualUID, BombaDeInfusion))
        Serial.println("BombaDeInfusion en "+ Place[i]);
    
    else if(compareArray(ActualUID, Desfribilador))
        Serial.println("Desfribilador en "+ Place[i]);
    }
    
  }
}

void dump_byte_array(byte *buffer, byte bufferSize) {//almacena la lectura en ActualUID
  for (byte i = 0; i < bufferSize; i++) {
    //Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    //Serial.print(buffer[i], HEX);
    ActualUID[i]=buffer[i]; 
  }
}

boolean compareArray(byte array1[], byte array2[]) {// esta funcion compara los codigos y lanza True si coinciden
  if (array1[0] != array2[0]) return (false);
  if (array1[1] != array2[1]) return (false);
  if (array1[2] != array2[2]) return (false);
  if (array1[3] != array2[3]) return (false);
  return (true);
}

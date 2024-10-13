#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 21   // Change to an appropriate GPIO pin
#define RST_PIN 27 // Change to an appropriate GPIO pin

MFRC522 rfid(SS_PIN, RST_PIN); // Instance of the class

void setup() { 
  Serial.begin(9600);
  SPI.begin(); // Init SPI bus
  Serial.println("Initializing MFRC522...");
  rfid.PCD_Init(); // Init RC522 
  Serial.println("MFRC522 Initialized");
}

void loop() {
  if ( ! rfid.PICC_IsNewCardPresent()) {
    return;
  }
  if ( ! rfid.PICC_ReadCardSerial()) {
    return;
  }
  
  Serial.print("RFID Tag UID: ");
  for (byte i = 0; i < rfid.uid.size; i++) {
    Serial.print(rfid.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(rfid.uid.uidByte[i], HEX);
  }
  Serial.println();
  
  rfid.PICC_HaltA(); // Halt PICC
}

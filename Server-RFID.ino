#include <WiFi.h>
#include <HTTPClient.h>
#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 21   // Change to an appropriate GPIO pin
#define RST_PIN 27 // Change to an appropriate GPIO pin
const char* ssid = "";           // Replace with your Wi-Fi SSID
const char* password = "";   // Replace with your Wi-Fi password
const char* serverUrl = "http://"IP":8080/open"; // Replace with your server URL


MFRC522 rfid(SS_PIN, RST_PIN);
void setup() {
  Serial.begin(115200);
  SPI.begin(); // Init SPI bus
  // Connect to Wi-Fi
  rfid.PCD_Init(); // Init RC522 
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected to WiFi");
}

void loop() {
  if ( ! rfid.PICC_IsNewCardPresent()) {
    return;
  }
  if ( ! rfid.PICC_ReadCardSerial()) {
    return;
  }

  String content= "";
  byte letter;
  for (byte i = 0; i < rfid.uid.size; i++) 
  {
     Serial.print(rfid.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(rfid.uid.uidByte[i], HEX);
     content.concat(String(rfid.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(rfid.uid.uidByte[i], HEX));
  }

  content.toUpperCase();
  if (content.substring(1) == "TAG") { // Replace with Desired RFID tag ID
    Serial.println("ID read:");
    HTTPClient http;
    http.begin(serverUrl);
    int httpCode = http.GET();
    
    if (httpCode > 0) {
      Serial.printf("Request sent, response code: %d\n", httpCode);
    } else {
      Serial.printf("Request failed, error: %s\n", http.errorToString(httpCode).c_str());
    }
    
    http.end();
    
    delay(1000); // Debounce delay
  }
}

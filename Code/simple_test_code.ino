#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10   // SDA
#define RST_PIN 7   // RST

MFRC522 rfid(SS_PIN, RST_PIN);

void setup() {
  Serial.begin(9600);
  SPI.begin();          // Init SPI bus
  rfid.PCD_Init();      // Init RC522
  Serial.println("Scan your RFID card...");
}

void loop() {
  // Wait for a new card
  if (!rfid.PICC_IsNewCardPresent()) return;
  if (!rfid.PICC_ReadCardSerial()) return;

  // Print UID
  Serial.print("Card UID: ");
  for (byte i = 0; i < rfid.uid.size; i++) {
    if (rfid.uid.uidByte[i] < 0x10) Serial.print("0");
    Serial.print(rfid.uid.uidByte[i], HEX);
    Serial.print(" ");
  }
  Serial.println();

  // Stop communication
  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();
  delay(1000);  // small delay to avoid flooding
}

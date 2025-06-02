#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 7

#define GREEN_LED 6
#define RED_LED 5

MFRC522 rfid(SS_PIN, RST_PIN);

unsigned long sessionStartTime = 0;
const unsigned long sessionTimeout = 5000; // 5 sec

bool sessionActive = false;
String currentStudentUID = "";

struct Book {
  String uid;
  String title;
  bool isBorrowed;
  String borrowedBy;
};

Book books[] = {
  {"B50F6BAE", "Book: Intro to AI", false, ""}
};

String studentList[] = {
  "53202021" // Example Student UID
 
};

void setup() {
  Serial.begin(9600);
  SPI.begin();
  rfid.PCD_Init();

  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);

  Serial.println("LibraTag ready.");
}

void loop() {
  if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial()) {
    checkTimeout();
    return;
  }

  String uidStr = getUIDString();

  // New student scanning
  if (isStudent(uidStr)) {
    if (sessionActive && uidStr != currentStudentUID) {
      Serial.println("⚠️ New student scanned. Closing previous session.");
    }
    currentStudentUID = uidStr;
    sessionStartTime = millis();
    sessionActive = true;
    Serial.print("🎓 Student ID: "); Serial.println(currentStudentUID);
    blinkLED(GREEN_LED);
    return;
  }

  // Must scan student first
  if (!sessionActive) {
    Serial.println("⛔ Error: Scan student ID first.");
    blinkLED(RED_LED);
    return;
  }

  // Handle book scan
  handleBookScan(uidStr);
}

void checkTimeout() {
  if (sessionActive && millis() - sessionStartTime > sessionTimeout) {
    Serial.println("⌛ Session expired.");
    sessionActive = false;
    currentStudentUID = "";
  }
}

void handleBookScan(String bookUID) {
  for (int i = 0; i < sizeof(books) / sizeof(books[0]); i++) {
    if (books[i].uid == bookUID) {
      if (books[i].isBorrowed && books[i].borrowedBy == currentStudentUID) {
        books[i].isBorrowed = false;
        books[i].borrowedBy = "";
        Serial.println("✅ Returned: " + books[i].title);
        blinkLED(GREEN_LED);
      } else if (!books[i].isBorrowed) {
        books[i].isBorrowed = true;
        books[i].borrowedBy = currentStudentUID;
        Serial.println("✅ Borrowed: " + books[i].title);
        blinkLED(GREEN_LED);
      } else {
        Serial.println("⛔ Error: Book borrowed by someone else.");
        blinkLED(RED_LED);
      }
      return;
    }
  }
  Serial.println("❌ Unknown book UID.");
  blinkLED(RED_LED);
}

bool isStudent(String uid) {
  for (String id : studentList) {
    if (id == uid) return true;
  }
  return false;
}

String getUIDString() {
  String uid = "";
  for (byte i = 0; i < rfid.uid.size; i++) {
    if (rfid.uid.uidByte[i] < 0x10) uid += "0";
    uid += String(rfid.uid.uidByte[i], HEX);
  }
  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();
  uid.toUpperCase();
  return uid;
}

void blinkLED(int pin) {
  digitalWrite(pin, HIGH);
  delay(300);
  digitalWrite(pin, LOW);
}

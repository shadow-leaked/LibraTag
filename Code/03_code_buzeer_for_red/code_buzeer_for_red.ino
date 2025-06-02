#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 7

#define GREEN_LED 6
#define RED_LED 5
#define BUZZER 4

MFRC522 rfid(SS_PIN, RST_PIN);

unsigned long sessionStartTime = 0;
const unsigned long sessionTimeout = 5000; // 5 sec session

bool sessionActive = false;
String currentStudentUID = "";

// Structure for books
struct Book {
  String uid;
  String title;
  bool isBorrowed;
  String borrowedBy;
};

// Book inventory
Book books[] = {
  {"B50F6BAE", "Book: Intro to AI", false, ""},
  {"A3B1C2D4", "Book: Data Structures", false, ""},
  {"9F34AC12", "Book: Electronics Basics", false, ""}
};

// List of valid students
String studentList[] = {
  "53202021", // Example Student UID
  "A1B2C3D4"
};

void setup() {
  Serial.begin(9600);
  SPI.begin();
  rfid.PCD_Init();

  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  digitalWrite(GREEN_LED, LOW);
  digitalWrite(RED_LED, LOW);
  digitalWrite(BUZZER, LOW);

  Serial.println("🔐 LibraTag RFID System Initialized.");
}

void loop() {
  if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial()) {
    checkTimeout();
    return;
  }

  String uidStr = getUIDString();

  // Student Scan
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

  // If no active session, deny book scan
  if (!sessionActive) {
    Serial.println("⛔ Error: Please scan your student ID first.");
    errorSignal();
    return;
  }

  // Process book
  handleBookScan(uidStr);
}

void checkTimeout() {
  if (sessionActive && millis() - sessionStartTime > sessionTimeout) {
    Serial.println("⌛ Session expired. Please scan ID again.");
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
        Serial.println("⛔ Error: Book already borrowed by someone else.");
        errorSignal();
      }
      return;
    }
  }

  Serial.println("❌ Unknown book tag scanned.");
  errorSignal();
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

void errorSignal() {
  digitalWrite(RED_LED, HIGH);
  tone(BUZZER, 1000, 300);
  delay(300);
  digitalWrite(RED_LED, LOW);
  noTone(BUZZER);
}

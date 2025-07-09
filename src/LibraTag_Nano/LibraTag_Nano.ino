// NOTE: This code is licensed for academic use only.
// Commercial use requires a paid license.
// See LICENSE file or contact author.

#include <SPI.h>
#include <MFRC522.h>
#include <SoftwareSerial.h>

#define RST_PIN 9
#define SS_PIN 10
MFRC522 rfid(SS_PIN, RST_PIN);

// Pins
#define GREEN_LED 3
#define RED_LED 4
#define BUZZER 5
#define BUTTON 7

// Session
bool sessionActive = false;
String currentStudentUID = "";
String scannedBooks[3];
int scannedBookCount = 0;
unsigned long sessionStartTime = 0;
const unsigned long SESSION_TIMEOUT = 20000; // 20 sec

// Whitelists
const String validStudents[] = {"B50F6BAE", "6506BEAE", "25F3FFAF","25DEBCAF"};
const String validBooks[] = {"53202021", "F36B0D21", "E3448D21","43954521"};

SoftwareSerial linkToUNO(2, 6); // TX to UNO RX, RX to UNO TX

void setup() {
  Serial.begin(9600);
  linkToUNO.begin(9600);
  SPI.begin();
  rfid.PCD_Init();

  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(BUTTON, INPUT_PULLUP);

  startupBlink();
  showCode(0);
}

void loop() {
  checkButton();
  manageSessionTimeout();

  if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial()) return;
  String uid = getUID(rfid.uid);
  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();

  if (!sessionActive) {
    if (isStudent(uid)) {
      startSession(uid);
    } else if (isBook(uid)) {
      showCode(9);
    } else {
      showCode(5);
    }
  } else {
    if (uid == currentStudentUID) {
      showCode(10);
    } else if (isBook(uid)) {
      if (isDuplicateBook(uid)) {
        showCode(7);
      } else if (scannedBookCount >= 3) {
        showCode(8);
      } else {
        scannedBooks[scannedBookCount++] = uid;
        sendToUNO("BORROW," + currentStudentUID + "," + uid);
        showCode(2);
      }
    } else {
      showCode(5);
    }
  }
}

// Functions
void startSession(String uid) {
  sessionActive = true;
  currentStudentUID = uid;
  sessionStartTime = millis();
  scannedBookCount = 0;
  showCode(1);
}

void endSession(int code) {
  sessionActive = false;
  currentStudentUID = "";
  scannedBookCount = 0;
  showCode(code);
}

void manageSessionTimeout() {
  if (sessionActive && (millis() - sessionStartTime > SESSION_TIMEOUT)) {
    endSession(3);
  }
}

void checkButton() {
  if (digitalRead(BUTTON) == LOW && sessionActive) {
    delay(50);
    if (digitalRead(BUTTON) == LOW) {
      endSession(4);
    }
  }
}

bool isStudent(String uid) {
  for (String s : validStudents) if (s == uid) return true;
  return false;
}

bool isBook(String uid) {
  for (String b : validBooks) if (b == uid) return true;
  return false;
}

bool isDuplicateBook(String uid) {
  for (int i = 0; i < scannedBookCount; i++) if (scannedBooks[i] == uid) return true;
  return false;
}

String getUID(MFRC522::Uid uid) {
  String uidStr = "";
  for (byte i = 0; i < uid.size; i++) {
    if (uid.uidByte[i] < 0x10) uidStr += "0";
    uidStr += String(uid.uidByte[i], HEX);
  }
  uidStr.toUpperCase();
  return uidStr;
}

void sendToUNO(String logLine) {
  linkToUNO.println(logLine);
}

void showCode(int code) {
  Serial.print("Code ");
  if (code < 10) Serial.print("0");
  Serial.print(code);
  Serial.print(": ");
  switch (code) {
    case 0: Serial.println("System Ready"); signal(GREEN_LED, 1, 300, 1000); break;
    case 1: Serial.println("Session started"); signal(GREEN_LED, 2, 200, 1100); break;
    case 2: Serial.println("Book accepted"); signal(GREEN_LED, 1, 150, 1200); break;
    case 3: Serial.println("Session timeout"); signal(RED_LED, 2, 200, 400); break;
    case 4: Serial.println("Session ended"); signal(RED_LED, 1, 200, 450); break;
    case 5: Serial.println("Unknown UID"); signal(RED_LED, 3, 150, 500); break;
    case 7: Serial.println("Duplicate book"); signal(RED_LED, 3, 100, 600); break;
    case 8: Serial.println("Book limit reached"); signal(RED_LED, 2, 250, 650); break;
    case 9: Serial.println("Book as student"); signal(RED_LED, 3, 150, 700); break;
    case 10: Serial.println("Re-scanned student"); signal(RED_LED, 2, 200, 750); break;
  }
}

void signal(int ledPin, int flashes, int duration, int toneFreq) {
  for (int i = 0; i < flashes; i++) {
    digitalWrite(ledPin, HIGH);
    tone(BUZZER, toneFreq, duration);
    delay(duration);
    digitalWrite(ledPin, LOW);
    delay(80);
  }
}

void startupBlink() {
  for (int i = 0; i < 3; i++) {
    digitalWrite(GREEN_LED, HIGH); tone(BUZZER, 1000, 100); delay(150); digitalWrite(GREEN_LED, LOW);
    digitalWrite(RED_LED, HIGH); tone(BUZZER, 500, 100); delay(150); digitalWrite(RED_LED, LOW);
  }
}

// NOTE: This code is licensed for academic use only.
// Commercial use requires a paid license.
// See LICENSE file or contact author.

// --- INCLUDES ---
#include <SPI.h>
#include <SD.h>
#include <Wire.h>
#include <SoftwareSerial.h>

// --- PINS ---
#define SD_CS     7      // SD Card Chip Select
#define NANO_RX   2      // Connected to Nano TX (SoftwareSerial RX)
#define NANO_TX   6      // Connected to Nano RX (SoftwareSerial TX)

SoftwareSerial nanoSerial(NANO_RX, NANO_TX);

// --- GLOBALS ---
File logFile;
const char* logFilename = "records.csv";

// === STRUCTURE ===
struct Entry {
  String student;
  String book;
  String action;
  String timestamp;
};

// === SETUP ===
void setup() {
  Serial.begin(9600);
  nanoSerial.begin(9600);
  initSD();
  Serial.println("UNO Logger Ready.");
}

// === LOOP ===
void loop() {
  if (!nanoSerial.available()) return;
  String data = nanoSerial.readStringUntil('\n');
  data.trim();

  Entry entry = parseData(data);
  if (entry.student.length() == 0 || entry.book.length() == 0) {
    Serial.println("[WARN] Malformed input, skipping.");
    return;
  }

  String lastStudent = "", lastAction = "";
  getBookState(entry.book, lastStudent, lastAction);

  // Determine new action
  if (lastAction == "") {
    entry.action = "BORROW";
  } else if (lastAction == "BORROW") {
    if (lastStudent == entry.student) {
      entry.action = "RETURN";
    } else {
      Serial.println("[ERROR] Unauthorized return attempt by " + entry.student);
      return;
    }
  } else { // lastAction == "RETURN"
    entry.action = "BORROW";
  }

  entry.timestamp = getTimestamp();
  if (logEntry(entry)) {
    Serial.println("Logged: " + entry.student + "," + entry.book + "," + entry.action);
  } else {
    Serial.println("[ERROR] Failed to write to SD.");
  }
}

// === FUNCTIONS ===

void initSD() {
  if (!SD.begin(SD_CS)) {
    Serial.println("[ERROR] SD Init failed.");
    while (true);
  }
  // Ensure the log file exists, create header if missing
  if (!SD.exists(logFilename)) {
    File f = SD.open(logFilename, FILE_WRITE);
    if (f) {
      f.println("Student,Book,Action,Timestamp");
      f.close();
    }
  }
  delay(100); // Give SD card time to settle
}

Entry parseData(const String& line) {
  Entry e;
  // Expecting format: MODE,StudentUID,BookUID
  int first = line.indexOf(',');
  int second = (first >= 0) ? line.indexOf(',', first + 1) : -1;
  if (first >= 0 && second >= 0) {
    e.student = line.substring(first + 1, second);
    e.book = line.substring(second + 1);
    e.student.trim();
    e.book.trim();
  }
  return e;
}

bool getBookState(const String& bookUID, String& student, String& action) {
  File f = SD.open(logFilename, FILE_READ);
  if (!f) return false;
  student = "";
  action = "";
  while (f.available()) {
    String line = f.readStringUntil('\n');
    if (line.length() == 0) continue;
    int c1 = line.indexOf(',');
    int c2 = line.indexOf(',', c1 + 1);
    int c3 = line.indexOf(',', c2 + 1);
    if (c1 < 0 || c2 < 0 || c3 < 0) continue;
    String s = line.substring(0, c1);
    String b = line.substring(c1 + 1, c2);
    String a = line.substring(c2 + 1, c3);
    if (b == bookUID) {
      student = s;
      action = a;
    }
  }
  f.close();
  return true;
}

bool logEntry(const Entry& e) {
  logFile = SD.open(logFilename, FILE_WRITE);
  if (!logFile) return false;
  logFile.print(e.student); logFile.print(',');
  logFile.print(e.book);    logFile.print(',');
  logFile.print(e.action);  logFile.print(',');
  logFile.println(e.timestamp);
  logFile.close();
  return true;
}

String getTimestamp() {
  unsigned long t = millis() / 1000;
  return String(t) + "s";
}

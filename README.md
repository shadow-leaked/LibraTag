# LibraTag  
*A Secure, Scalable RFID-Based Library Management System*

[![Build Status](https://img.shields.io/badge/build-passing-brightgreen.svg)](https://github.com/LibraTag/LibraTag/actions)  
[![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0.en.html)  
[![Platform](https://img.shields.io/badge/platform-Arduino-orange.svg)](https://www.arduino.cc/)  
[![PRs Welcome](https://img.shields.io/badge/PRs-welcome-brightgreen.svg)](https://makeapullrequest.com)  
[![Open Source Love](https://img.shields.io/badge/open%20source-%E2%9D%A4-red.svg)](https://opensource.org)

---

> “Making library automation truly accessible with low-cost hardware and intelligent design.”

---

## 📚 Overview

**LibraTag** is a robust, low-cost RFID-based system designed for managing book borrowing and returns in academic or public libraries. Powered by Arduino, it eliminates manual logbooks and leverages RFID, session security, and storage modules to automate workflows — while staying affordable and flexible.

This project is ideal for institutions in need of efficient resource management without enterprise-level infrastructure.

---

## 🔑 Features

- ✅ **RFID-based Identity Management**  
  Assign unique UIDs to students and books using RFID cards/stickers.

- ✅ **Secure Session Handling**  
  Prevent unauthorized scans using auto-expiring session windows.

- ✅ **Visual & Audio Feedback**  
  LED indicators and a 5V buzzer show real-time operation status.

- ✅ **Borrow / Return Logic**  
  Automatic check-in/check-out by UID recognition and book status.

- ✅ **Admin Override Support**  
  Special card/tag can override rules to manage conflicts.

- ✅ **SD Card Data Logging**  
  Logs all borrowing/return activity with timestamps.

- ✅ **RTC Clock Integration (DS3231)**  
  Ensures accurate time-logging for each transaction.

- ✅ **EEPROM/SD Storage Option**  
  Choice between persistent memory for metadata and logs.

---

## 🔧 Hardware Requirements

| Component               | Quantity | Description                                |
|------------------------|----------|--------------------------------------------|
| Arduino UNO R3 (clone) | 1        | Main controller                            |
| RC522 RFID Reader      | 1        | Reads student and book tags                |
| RFID Tags/Stickers     | Many     | Placed on each book                        |
| RFID Cards/Keychains   | ≥ 1      | Assigned to students and admin             |
| 5V Active Buzzer       | 1        | Emits tone for errors or confirmations     |
| Green LED              | 1        | Indicates success (e.g., book borrowed)    |
| Red LED                | 1        | Indicates error or invalid action          |
| 220Ω Resistors         | 2        | Used with LEDs to limit current            |
| SD Card Module         | 1        | Optional: log transactions to SD           |
| Micro SD Card (≥2 GB)  | 1        | Storage medium                             |
| RTC Module (DS3231)    | 1        | Adds time-keeping for logs                 |
| Breadboard + Jumper Wires| N      | For prototyping                            |
| 3D Printed/Custom Enclosure | 1   | Optional: project case for deployment      |

---

## 🚦 System Flow

1. **Student scans RFID card**  
   → Session starts (5s window to scan books)

2. **Book tag scanned**  
   → If not borrowed → marked as borrowed  
   → If already borrowed by same student → returned  
   → If borrowed by someone else → error

3. **Session expires in 5s or on new student scan**  
   → Resets system

4. **LED/Buzzer feedback**  
   → Green = Success  
   → Red + Buzz = Error

5. **All actions logged (if SD & RTC present)**

---

## 💾 Data Logging (Optional)

If SD card and RTC are present, each scan operation is recorded with:

```csv
[DATE], [TIME], [ACTION], [STUDENT_UID], [BOOK_UID], [BOOK_TITLE]
```

Helps build history, detect misuse, and audit lending activity.

## 🛠 Setup

- Flash Arduino UNO with `libra_tag.ino`
- Connect RC522, LEDs, buzzer, and optionally SD & RTC modules
- Configure UID list of students and books in the code
- Power up and monitor via Serial or logs
- Scan student → scan book(s) → done

## 🛡 License

This project is licensed under the **GNU General Public License v3.0**  
See [LICENSE](./LICENSE) for details.

© 2025 **LibraTag Team**  
All rights reserved. License headers embedded in code are non-removable per GPLv3.

## 🙌 Contributing

Want to improve it? Add support for LCDs? Web syncing?  
[Pull Requests Welcome](https://github.com/shadow-leaked/LibraTag/pulls)

## 📌 Future Enhancements

- 🔗 **WiFi sync** to a remote database (ESP32)
- 📟 **LCD display** for user messages
- 🧪 **Web-based book admin dashboard**
- 📤 **Remote admin override**

---
> “A well-managed library reflects a well-managed mind.” – LibraTag Team
---

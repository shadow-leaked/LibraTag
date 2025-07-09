# 📘 LibraTag  
*A Secure, Scalable RFID-Based Library Management System for Academic Use*


![License: Commercial Use Requires Payment](https://img.shields.io/badge/license-Commercial%20Use%20Paid-red)
[![Build Status](https://img.shields.io/badge/build-passing-brightgreen.svg)](https://github.com/shadow-leaked/LibraTag/actions)
[![Platform](https://img.shields.io/badge/platform-Arduino-orange.svg)](https://www.arduino.cc/)
[![PRs Welcome](https://img.shields.io/badge/PRs-welcome-brightgreen.svg)](https://github.com/shadow-leaked/LibraTag/pulls)

---

> “Making library automation truly accessible with low-cost hardware and intelligent design.”

---

## 📚 Overview

**LibraTag** is a modular RFID-based system designed to streamline library management in **schools, colleges, and research labs**. It enables secure, session-based borrowing and returning of books using low-cost Arduino hardware and RFID tags — **without enterprise infrastructure**.

Unlike traditional systems, LibraTag supports real-time feedback, data logging, and strict UID-based verification, making it ideal for academic use while also adaptable for commercial deployments with licensing.

---

## 🔑 Core Features

- ✅ **RFID Identity & Asset Tagging**  
  Distinct UIDs for students and books using RC522 and RFID tags.

- ✅ **Time-Limited Sessions**  
  Prevents spoofed scans via auto-expiring borrowing windows.

- ✅ **Secure Book Borrow/Return Logic**  
  Detects duplicate entries, student mismatch, and over-borrowing.

- ✅ **Dual Microcontroller Architecture**  
  Arduino Nano (RFID logic) + UNO (logging, decision control).

- ✅ **Visual & Audio Feedback**  
  Red/Green LEDs and buzzer feedback for fast user cues.

- ✅ **Offline Logging (SD Card + RTC)**  
  Timestamped logging for auditing and analytics.

- ✅ **Admin Card Support**  
  Override actions in emergency/maintenance situations.

---

## 🧰 Hardware Requirements

| Component                  | Qty | Notes                                               |
|---------------------------|-----|-----------------------------------------------------|
| Arduino UNO R3            | 1   | Logging & decision controller                       |
| Arduino Nano              | 1   | RFID reader logic                                   |
| RC522 RFID Module         | 1   | Reads RFID cards & book tags                        |
| RFID Cards/Stickers       | ✱   | UID tags for students/books                         |
| 5V Active Buzzer          | 1   | Error/success tones                                 |
| Green LED + Red LED       | 1+1 | Indicates system state                              |
| 220Ω Resistors            | 2   | Current limiting for LEDs                           |
| Push Button               | 1   | Ends sessions manually                              |
| Micro SD Card Module      | 1   | Optional: persistent logging                        |
| DS3231 RTC Module         | 1   | Adds real-time clock                                |
| Micro SD Card (≥2 GB)     | 1   | Stores log entries                                  |
| Breadboard & Jumper Wires | ✱   | For prototyping                                     |
| Enclosure (3D-Printed)    | 1   | Optional but recommended for durability             |

---

## 🔁 System Workflow

```plaintext
Student Scan → Session Opens (20s Window)
      ↓
Book(s) Scanned → Validated, Logged, Feedback Given
      ↓
Session Auto-Closes or Ends via Button
```
✅ Green LED + Tone → Success   
❌ Red LED + Buzz → Error / Invalid Action  
🕒 20s timeout after last student scan

## 💾 Logging Format
If SD + RTC modules are attached, every transaction is saved in the following format:
```
[DATE], [TIME], [ACTION], [STUDENT_UID], [BOOK_UID], [ROLL_NO/BOOK_ID]
```
Examples:
```
2025-07-08, 14:12:35, BORROW, 23AC4411, F36B0D21, BC-1745
2025-07-08, 14:13:05, RETURN, 23AC4411, F36B0D21, BC-1745
```
This allows for complete audit trails, misusage detection, and lending statistics.

## ⚙️ Project Setup

### 🔌 Wire Modules
Connect RFID, LEDs, buzzer, button, RTC & SD to Nano/UNO as per circuit.

### 💾 Flash Controllers
- Upload `LibraTag_Nano.ino` to **Arduino Nano**  
- Upload `LibraTag_UNO.ino` to **Arduino UNO**

### 🧾 Configure UIDs
Add valid book UIDs and student UIDs in the Nano code.

### ▶️ Power On System
System enters idle mode; ready to scan.

---

## 🛡 Licensing

LibraTag uses a **Custom Dual License** model:

| Use Case          | Terms                                           |
|-------------------|--------------------------------------------------|
| 🎓 Students       | Free for academic projects & personal use        |
| 🏫 Researchers    | Free for non-commercial research purposes         |
| 🏢 Commercial Use | Paid License Required                            |

> **You may not** use this project for commercial, for-profit, or SaaS integration without an explicit paid license.  
See [`LICENSE`](./LICENSE) for full legal terms.

---

## 📌 Future Enhancements

- 🌐 **ESP32-based Web Sync**
- 📟 **LCD Message Display for Scans**
- 🛜 **Remote Admin Override via Wi-Fi**
- 🧾 **QR Code Printout of Logs**
- 📊 **Web Dashboard for Admins**

---

## 🙌 Contributing

We welcome PRs that:
- Add new modules (LCD, NFC, wireless)
- Improve session security
- Add multilingual feedback
- Optimize memory usage on Nano

**Fork → Branch → PR → Merge 🔁**  
→ [Contribute here](https://github.com/shadow-leaked/LibraTag/pulls)

---

## 📣 Attribution

© 2025 **LibraTag Team**  
All rights reserved.  
License headers embedded in source code are **non-removable** under this license.

> “A well-managed library reflects a well-managed mind.” — *LibraTag Team*

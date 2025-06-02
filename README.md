# 📚 LibraTag – RFID-Based Library Book Borrowing System with Offline History Logging

**LibraTag** is a smart, secure, and low-cost RFID-based library automation system designed for educational institutes. Built using Arduino, it allows students to borrow and return RFID-tagged books using their student ID card. It now features **offline transaction logging** to preserve all borrowing/return history—even without internet or a database.

---

## 🚀 Features

- ✅ RFID student card & book tag detection using RC522
- ✅ Session-based control (5 seconds)
- ✅ Borrow/Return identification logic
- ✅ Unlimited book borrow capability
- ✅ Secure session closure on timeout or new user scan
- ✅ LED & Buzzer for visual/audio feedback
- ✅ Offline transaction history storage
  - ➕ SD card logging *(preferred)*
  - ➕ EEPROM backup *(fallback or budget solution)*
- ✅ Error handling: wrong scan order, duplicate borrow, unauthorized UID
- ✅ Modular, maintainable codebase

---

## 🛠️ Hardware Requirements

| Component              | Quantity |
|-----------------------|----------|
| Arduino Uno R3 / R4   | 1        |
| MFRC522 RFID Module   | 1        |
| RFID Cards            | As needed (students) |
| RFID Stickers (Tags)  | As needed (books) |
| SD Card Module        | 1        |
| Micro SD Card (≥ 1 GB preferred) | 1 |
| Green LED                        | 1        |
| Red LED                          | 1        |
| Passive 5V Buzzer                | 1        |
| Breadboard + Jumper Wires        | ~20      |
| Optional: EEPROM chip     | 1        |

---

## 🔌 Wiring

### RC522 to Arduino

| RC522 Pin | Arduino Uno Pin |
|-----------|------------------|
| SDA       | 10               |
| SCK       | 13               |
| MOSI      | 11               |
| MISO      | 12               |
| GND       | GND              |
| RST       | 7                |
| 3.3V      | 3.3V             |

### LEDs

| LED       | Pin   | Resistor | To   |
|-----------|-------|----------|------|
| Green     | D6    | 220Ω     | GND  |
| Red       | D5    | 220Ω     | GND  |

---

## 🧪 Behavior

1. Student scans card → session starts
2. Books must be scanned within 3 seconds
3. Each book scan checks:
   - If not borrowed → it is marked *borrowed*
   - If already borrowed → it is *returned*
4. New student scan interrupts session
5. LED Feedback:
   - 🟢 Green = Success (borrow/return)
   - 🔴 Red = Error (invalid action, timeout, etc.)

---
## 🧠 How It Works

### Workflow

1. **Student Scans ID**: Session opens for 5 seconds.
2. **Books Scanned**: Borrow or return logic is triggered.
3. **Logs Written**: Each transaction (borrow/return) is saved to `log.txt` on SD card.
4. **Visual/Auditory Feedback**: Green LED for success, red + buzzer for error.
5. **New Scan?**: New student UID auto-closes old session.
6. **Timeout?**: Session closes after 5 seconds of inactivity.

---

## ⚙️ Setup Instructions

1. Connect RFID module, LEDs, and buzzer as per the wiring guide.
2. Format SD card to FAT32 and insert into SD module.
3. Upload code via Arduino IDE.
4. Open Serial Monitor for real-time debug logs.
5. Start scanning student ID cards followed by books.

---
## 👤 Author

Developed by **Shadow leaked**  &  **Silvia Khumukcham**  
BCA Minor Project | India 🇮🇳  
Contact: shadowleaked@gmail.com & khsilvia8@gmail.com

---
## 🔐 License

This project is licensed under the **MIT License**.  
You are free to use, modify, and distribute this for educational or personal use.

---
## 🧱 Future Upgrades

- 📡 Firebase integration for remote database
- 🧑‍🏫 Admin master card for manual overrides
- 📱 Mobile/Web interface for students
- 📖 LCD/OLED display for book status

---

> “A well-managed library reflects a well-managed mind.” – LibraTag Team
---

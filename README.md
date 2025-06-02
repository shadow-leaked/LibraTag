# 📚 LibraTag

**LibraTag** is a smart, RFID-based library book borrowing system designed to automate and secure the book lending process in educational institutions. The system uses RFID cards for students and RFID stickers on books to streamline transactions and eliminate human errors or misuse.

---

## 🎯 Features

- 🧠 Dual RFID logic: Student card activates session; book tags get linked within 3–5 seconds.
- 🕐 Timed sessions: Automatically closes student session to prevent misuse.
- 🚫 Tamper-resistant: If another student scans their ID mid-session, the previous session is force-closed.
- ♻️ Unlimited books per session.
- 💰 Low-cost hardware using Arduino Uno + RC522.
- 🪛 Designed with budget-friendly jugaad in mind.

---

## 🛠️ Hardware Requirements

| Component            | Quantity | Notes                            |
|----------------------|----------|----------------------------------|
| Arduino Uno (R3/R4)  | 1        | Any standard compatible board    |
| RC522 RFID Reader    | 1        | 3.3V module                      |
| RFID Card (13.56MHz) | 1+       | Student identity                 |
| RFID Sticker (NFC)   | 5+       | Attach to books                  |
| Jumper Wires         | -        | Male-to-female (for breadboard) |
| Breadboard (optional)| 1        | For modular prototyping          |
| USB Cable            | 1        | Arduino to PC connection         |

> ⚠️ Power RC522 with **3.3V only**, not 5V.

---

## 🔌 Wiring Diagram

| RC522 Pin | Arduino UNO Pin |
|-----------|-----------------|
| SDA       | D10             |
| SCK       | D13             |
| MOSI      | D11             |
| MISO      | D12             |
| RST       | D7              |
| GND       | GND             |
| VCC       | 3.3V            |

---

## 💻 Software Setup

1. **Libraries Needed**
   - [MFRC522](https://github.com/miguelbalboa/rfid)
   - SPI (comes with Arduino IDE)

2. **Upload Code**
   - Use the `LibraTag.ino` file.
   - Open Serial Monitor at `9600` baud.
   - Place a student card, then scan book tags.

3. **Behavior**
   - Scanning a student card opens a timed window (e.g., 5 sec).
   - Any scanned book RFID within this window is linked to the student.
   - Timeout auto-closes the session to avoid accidental borrowing.

---

## 🔐 License

This project is licensed under the [MIT License](./LICENSE). You are free to use, modify, and distribute it with proper attribution.

---

## 👤 Author

Developed by **Shadow leaked**  &  **Silvia Khumukcham**  
BCA Minor Project | India 🇮🇳  
Contact: shadowleaked@gmail.com & khsilvia8@gmail.com

---

## 🙌 Contributions

Pull requests are welcome! If you'd like to improve the project or add features (like database logging, LCD display, or Wi-Fi integration), feel free to fork and contribute.

---

## ✅ Future Scope

- Integration with Google Sheets via ESP32
- Web dashboard for librarians
- SMS/email notification on borrowing

---


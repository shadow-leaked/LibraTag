# LibraTag 📚🔖

**RFID-Based Smart Library Book Borrow/Return System**

LibraTag is a low-cost, scalable system designed for institutes to automate library operations using RFID technology. Built with Arduino Uno, RC522 RFID reader, and simple LEDs, it enables secure and efficient book borrowing and returning.

---

## 🎯 Features

- 🔐 **Student authentication** via RFID card
- 📖 **Book tracking** using RFID tags
- ⏱️ **Timed session** (3s) to avoid misuse
- 🔄 **Force reset** on new student card scan
- 🟢🟥 **LED feedback** for success/error
- ✅ No book limit
- ⚙️ Easily extensible to a Python/SQL backend or Firebase

---

## 🧰 Hardware Used

| Component               | Quantity |
|-------------------------|----------|
| Arduino Uno R3          | 1        |
| RC522 RFID Module       | 1        |
| RFID Card (Student ID)  | 1+       |
| RFID Sticker/Tag (Book) | 1+       |
| Red LED (Error)         | 1        |
| Green LED (Success)     | 1        |
| 220Ω Resistors          | 2        |
| Jumper Wires + Breadboard| As needed |

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

## 📜 License

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


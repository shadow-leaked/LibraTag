# System Architecture – LibraTag

LibraTag operates on a **dual-controller model**:

- **Nano**: Handles RFID scanning, session logic, and validation.
- **UNO**: Responsible for data logging, RTC time-stamping, and optional EEPROM storage.

## 🧩 High-Level Block Diagram
```
[RFID Reader] → Nano → Serial → UNO → [SD Card / EEPROM / RTC]  
                 ↓  
        [LEDs, Buzzer, Button]
```

## 📌 Nano Role (RFID & Session Node)

- Detects UID from RFID reader  
- Starts a session upon valid student scan  
- Accepts books during session  
- Validates UIDs, prevents duplicates, enforces limit  
- Sends formatted log strings to UNO  

## 📌 UNO Role (Logging Node)

- Receives session logs from Nano  
- Stamps logs with RTC time  
- Saves to SD Card or EEPROM  
- Handles data persistence  

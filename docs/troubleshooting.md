# Troubleshooting – LibraTag

## 🔧 Common Issues

| Problem              | Solution                                   |
| -------------------- | ------------------------------------------ |
| SD Card not logging  | Format as FAT32, check CS pin              |
| No buzzer sound      | Check D5, use active buzzer                |
| UID not detected     | Print UID using `Serial.println(getUID())` |
| Serial shows garbage | Check baud rate (9600)                     |
| RTC not syncing      | Use DS3231; check battery and wiring       |

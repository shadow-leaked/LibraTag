# Hardware Wiring – LibraTag

## ⚙️ Arduino Nano (RFID Controller)

| Component  | Pin on Nano | Notes              |
| ---------- | ----------- | ------------------ |
| RFID RC522 | D10–D13     | SPI interface      |
| Green LED  | D3          | Success indicator  |
| Red LED    | D4          | Error indicator    |
| Buzzer     | D5          | Active buzzer      |
| Button     | D7          | End session button |
| UNO RX     | D2 (TX)     | SoftwareSerial     |
| UNO TX     | D6 (RX)     | SoftwareSerial     |

## ⚙️ Arduino UNO (Data Logger)

| Component      | Pin on UNO | Notes         |
| -------------- | ---------- | ------------- |
| SD Card Module | D10–D13    | SPI interface |
| RTC DS3231     | A4/A5      | I2C SDA/SCL   |
| Nano RX        | D2 (TX)    | From Nano     |
| Nano TX        | D3 (RX)    | From Nano     |

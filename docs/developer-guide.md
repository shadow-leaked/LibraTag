# Developer Guide – LibraTag

## 💬 Serial Communication (Nano → UNO)
```
Format: BORROW,<studentUID>,<bookUID>
```

UNO expects this input and adds time stamps.

## 🔁 Session Lifecycle (on Nano)

1. Student tag scanned → starts session  
2. Book scanned → validated and logged  
3. Timeout or button ends session  

## 💡 EEPROM Use (Optional)

Can store borrowed book metadata if SD is absent.           
Format:
```
<slot>: <studentUID>,<bookUID>,<timestamp
```

## 🔐 Adding More Feedback Codes

- Add new case under `showCode(int)` in Nano  
- Map it to LED/Buzzer pattern + Serial print  

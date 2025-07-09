# Log Data Format – LibraTag

All session actions are recorded by the UNO in `.csv` format if an SD Card is present.

## 📄 Sample CSV Line
```
2025-07-09, 12:42:10, BORROW, 53202021, F36B0D21, "Thermodynamics"
```

## 📑 Columns Explained

| Field        | Description                       |
| ------------ | --------------------------------- |
| DATE         | RTC Date (YYYY-MM-DD)             |
| TIME         | RTC Time (HH:MM:SS)               |
| ACTION       | BORROW / RETURN                   |
| STUDENT_UID  | UID of the student tag            |
| BOOK_UID     | UID of the scanned book           |
| BOOK_TITLE   | Optional: From predefined UID map |

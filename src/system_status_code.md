# 📘 System Status Codes

This document outlines the success and error codes used by the system during operation.

---

## ✅ Success Codes

| Code | Description |
|------|-------------|
| `00` | **System Ready** — The system has powered on and initialized successfully. |
| `01` | **Session Started** — A valid student UID has been scanned to initiate a borrowing session. |
| `02` | **Book Accepted** — A valid and new book UID has been scanned during an active session. |
| `04` | **Session Ended by Button Press** — The session was manually ended using the physical button. |

---

## ❌ Failure/Error Codes

| Code | Description |
|------|-------------|
| `03` | **Session Timeout** — No books were scanned within the timeout window (20 seconds); session auto-terminated. |
| `05` | **Unknown UID Scanned** — The UID scanned is not listed in either the student or book whitelist. |
| `07` | **Duplicate Book UID Scanned** — The book has already been scanned in the current session. |
| `08` | **Book Limit Reached** — The student has scanned the maximum number of allowed books (3 in this system). |
| `09` | **Book Scanned as Student (Invalid Session Start)** — A book UID was scanned when the system was expecting a student UID to begin the session. |
| `10` | **Student Re-Scanned During Session** — The same student UID was scanned again during an active session. |

## Waveshare‑13892 RFID Driver v2 — STM32 + MFRC522 + LCD UI
This repository contains a complete driver and demonstration application for the Waveshare 13892 RFID module (MFRC522) running on an STM32 microcontroller.
The project integrates:

* MFRC522 RFID communication (ISO14443A)

* UID detection and card database lookup

* LCD UI (SPI 160×128)

* Button input with software debounce

* Configurable beep modes (single / double)

* UART logging

* Modular and clean driver structure

* It serves as a ready‑to‑use reference for RFID‑based access systems, embedded UI demos, or educational STM32 projects.

## Project Structure

```text
Core/
├── Inc/
│   ├── RC522.h
│   ├── lcd_init.h
│   ├── lcd_run.h
│   ├── lcd_control.h
│   ├── lcd_beep_ui.h
│   ├── button_debounce.h
│   ├── cards_and_tags.h
│   └── main.h
└── Src/
    ├── main.c
    ├── RC522.c
    ├── lcd_init.c
    ├── lcd_run.c
    ├── lcd_control.c
    ├── lcd_beep_ui.c
    ├── button_debounce.c
    └── cards_and_tags.c
```




<img width="626" height="587" alt="Zrzut ekranu 2026-06-12 222538" src="https://github.com/user-attachments/assets/1d6fe43c-6d8f-4504-9748-805d89677f99" />

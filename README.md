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

# 🔧 Hardware Requirements
* STM32 microcontroller (F1/F3/WB series or similar)

* MFRC522 RFID module (Waveshare 13892)

* 160×128 SPI LCD display

* 4× buttons (UP / DOWN / LEFT / RIGHT)

* Buzzer (GPIO‑controlled)

* SPI connections:

* SPI1 → LCD

* SPI2 → MFRC522

# 🚀 Features
1. RFID Card Reading
The MFRC522 driver implements:

* MFRC522_Request() — card presence detection

* MFRC522_Anticoll() — UID reading

* MFRC522_SelectTag() — card selection

* MFRC522_Read() / MFRC522_Write() — block operations

The driver uses SPI transfers such as:

* “Writing data to the FIFO”
* “Reading the received data in FIFO”

(from your RC522.c implementation)

* 2. New UID Detection
The function Read_data_from_rfid():

polls the reader every 1 second,

compares UID with the last detected one,

looks up the card in the internal database,

displays card info on the LCD,

triggers a beep,

sends a UART message.

* 3. Card Database
Defined in cards_and_tags.c:

```c
Card cards[] = {
    {{119,141,249,216,219}, "Karta pier"},
    {{172,198,79,35,6},     "Pestka pier"}
};
```

find_card() returns the card name based on UID.

* 4. LCD User Interface
The UI includes:

card detection screen,

beep‑mode selection screen,

card list display.

LCD functions:

lcd_init()

lcd_print_line()

lcd_fill_box()

lcd_draw_beep_mode_ui()

* 5. Button Handling (Debounce)
button_debounce.c implements a finite‑state machine:

BTN_IDLE

BTN_DEBOUNCE

BTN_PRESSED

Each press generates a single event, ideal for menu navigation.

* 6. Beep Modes
Implemented in lcd_beep_ui.c:

Single beep (1 × 1000 ms)

Double beep (2 × 500 ms)

Mode toggled with the UP button

Visual feedback on LCD (green/red circles)


<img width="626" height="587" alt="Zrzut ekranu 2026-06-12 222538" src="https://github.com/user-attachments/assets/1d6fe43c-6d8f-4504-9748-805d89677f99" />

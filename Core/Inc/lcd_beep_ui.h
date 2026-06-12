#ifndef LCD_BEEP_UI_H
#define LCD_BEEP_UI_H

#include <stdint.h>

void lcd_draw_beep_mode_ui(void);
void lcd_toggle_beep_mode(void);
uint8_t get_beep_mode(void);
void beep(void);
#endif

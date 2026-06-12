#include "lcd_control.h"
#include "cards_and_tags.h"
#include <string.h>

extern const Card cards[];
extern const int cards_count;

void lcd_cmd(uint8_t cmd)		//funkcja statyczna bo tylko w tym pliku (nie widoczna dla innych plików)To bardzo ważne, bo dzięki temu nie pojawia się ryzyko konfliktu nazw, a nasze moduły są lepiej od siebie odizolowane.
{
	// Set DC low to indicate command transmission									//W przypadku funkcji statycznych nie umieszczamy ich deklaracji w pliku nagłówkowym. Ograniczamy się jedynie do umieszczenia funkcji w pliku źródłowym!
	HAL_GPIO_WritePin(LCD_DC_GPIO_Port, LCD_DC_Pin, GPIO_PIN_RESET);	//ustawienie stanu niskiego na pinie DC aby wyslac komende
	 // Select the LCD controller (active low)
	HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_RESET);	//ustawienie stanu niskiego na pinie CS aby wybrac sterownik wyswietlacza
	 // Transmit one command byte over SPI
	HAL_SPI_Transmit(&hspi2, &cmd, 1, HAL_MAX_DELAY);					//wyslanie danych
	// Deselect the LCD controller
	HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_SET);		//stan wysoki na linii CS
}
/**
 * Sends a data byte to the LCD controller.
 */
void lcd_data(uint8_t data)		//funkcja do wysylania danych
{
	// Set DC high to indicate data transmission
	HAL_GPIO_WritePin(LCD_DC_GPIO_Port, LCD_DC_Pin, GPIO_PIN_SET);
	// Select the LCD controller
	HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_RESET);
	 // Transmit one data byte over SPI
	HAL_SPI_Transmit(&hspi2, &data, 1, HAL_MAX_DELAY);
	// Deselect the LCD controller
	HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_SET);
}
/**
 * Marks a value as an LCD command by setting bit 8.
 *
 * Values without this flag are treated as display data.
 */

/**
 * Sends either a command or data depending on bit 8.
 *
 * Bit 8 acts as a flag:
 *   - set   -> command
 *   - clear -> data
 */
void lcd_send(uint16_t value)
{
	if (value & 0x100) {
		lcd_cmd(value);
	} else {
		lcd_data(value);
	}
}
/**
 * LCD initialization sequence.
 *
 * Commands are marked using CMD(), while the remaining values
 * are interpreted as data bytes associated with the preceding command.
 */



void lcd_data16(uint16_t value)		//funkcja do wysylania slow 16 bitowych
{
	lcd_data(value >> 8);   // High byte
	lcd_data(value);        // Low byte
}

void lcd_set_window(int x, int y, int width, int height)
{
  lcd_cmd(ST7735S_CASET);
  lcd_data16(LCD_OFFSET_X + x);
  lcd_data16(LCD_OFFSET_X + x + width - 1);

  lcd_cmd(ST7735S_RASET);
  lcd_data16(LCD_OFFSET_Y + y);
  lcd_data16(LCD_OFFSET_Y + y + height- 1);
}


void lcd_fill_box(int x, int y, int width, int height, uint16_t color)
{
	lcd_set_window(x, y, width, height);

	lcd_cmd(ST7735S_RAMWR);
	for (int i = 0; i < width * height; i++)
		lcd_data16(color);
}


void lcd_draw_char(int x, int y, char c, uint16_t color, uint16_t bg)
{
    if (c >= 'a' && c <= 'z') c -= 32;
    if (c < 'A' || c > 'Z') return;

    int idx = c - 'A';

    lcd_set_window(x, y, 12, 16);
    lcd_cmd(ST7735S_RAMWR);

    for (int row = 0; row < 16; row++)
    {
        uint16_t line = font12x16[idx][row];

        for (int col = 0; col < 12; col++)
        {
            if (line & (1 << (11 - col)))
                lcd_data16(color);
            else
                lcd_data16(bg);
        }
    }
}

// ---------------- STRING ----------------
void lcd_print(int x, int y, const char *str, uint16_t color, uint16_t bg)
{
    while (*str)
    {
        lcd_draw_char(x, y, *str, color, bg);
        x += 12;
        str++;
    }
}



void lcd_print_line(int line, const char *str, uint16_t color, uint16_t bg)
{
    int x = 10;
    int y = (line - 1) * LINE_H;

    lcd_clear_line(y, bg);   // 👈 KLUCZOWE

    lcd_print(x, y, str, color, bg);
}

void lcd_clear_line(int y, uint16_t bg)
{
    lcd_set_window(0, y, 160, LINE_H); // albo szerokość Twojego LCD
    lcd_cmd(ST7735S_RAMWR);

    for (int i = 0; i < 160 * LINE_H; i++)
    {
        lcd_data16(bg);
    }
}

char* find_card(uint8_t *UID)
{
    for (int i = 0; i < cards_count; i++)
    {
        if (memcmp(UID, cards[i].UID, 5) == 0)
        {
            return cards[i].name;
        }
    }
    return NULL;
}

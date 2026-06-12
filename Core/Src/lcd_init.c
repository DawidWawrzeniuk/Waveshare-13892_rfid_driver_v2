#include "lcd_init.h"
#include "lcd_control.h"
void lcd_init(void)
{
  int i;
  // Perform hardware reset
  HAL_GPIO_WritePin(LCD_RST_GPIO_Port, LCD_RST_Pin, GPIO_PIN_RESET);
  HAL_Delay(100);
  HAL_GPIO_WritePin(LCD_RST_GPIO_Port, LCD_RST_Pin, GPIO_PIN_SET);
  HAL_Delay(100);
  // Send all commands and data from initialization table
  for (i = 0; i < sizeof(init_table) / sizeof(uint16_t); i++) //To popularny sposób w C na policzenie ile elementów ma tablica.

	  	  	  	  	  	  	  	  	  	  	  	  	  	  	  	 // sizeof(init_table) → rozmiar całej tablicy w bajtach

																 // sizeof(uint16_t) → rozmiar jednego elementu (2 bajty)
  {
    lcd_send(init_table[i]);
  }

  HAL_Delay(200);
  // Exit sleep mode
  lcd_cmd(ST7735S_SLPOUT);		//budzenie z trybu uspienia
  HAL_Delay(120);
  // Turn display on
  lcd_cmd(ST7735S_DISPON);		//wlaczenie wyswietlacza
}

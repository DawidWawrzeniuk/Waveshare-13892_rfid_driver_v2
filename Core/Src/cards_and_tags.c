#include "cards_and_tags.h"
#include "lcd_control.h"
Card cards[] = {
    {{119,141,249,216,219}, "Karta pier"},
    {{172,198,79,35,6},     "Pestka pier"}
};


const uint8_t cards_count = sizeof(cards) / sizeof(cards[0]);



void show_cards(void)
{
    if (HAL_GPIO_ReadPin(menu_right_GPIO_Port, menu_right_Pin) == GPIO_PIN_SET)
    {
        lcd_print_line(1, "MEMORY OF", WHITE, BLACK);
        lcd_print_line(2, "CARDS:", WHITE, BLACK);
        for(int i=0; i<= cards_count;i++)
        {
        lcd_print_line(3+i, cards[i].name, WHITE, BLACK);
        }

    }
}

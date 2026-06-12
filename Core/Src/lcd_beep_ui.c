#include "lcd_beep_ui.h"
#include "lcd_control.h"
#include <stdint.h>

// kolory RGB565
#define COLOR_BG      0x0000
#define COLOR_ON      0x07E0
#define COLOR_OFF     0xF800
#define time_of_beeping 1000
#define RADIUS 10

static uint8_t mode_single_beep = 1;


// ---------------- PROTOTYP WEWNĘTRZNY ----------------
static void draw_circle(int cx, int cy, int r, uint16_t color)
{
    for (int y = -r; y <= r; y++)
    {
        for (int x = -r; x <= r; x++)
        {
            if (x*x + y*y <= r*r)
            {
                lcd_fill_box(cx + x, cy + y, 1, 1, color);
            }
        }
    }
}

// ---------------- UI ----------------
void lcd_draw_beep_mode_ui(void)
{
    // clear screen
    lcd_fill_box(0, 0, 160, 128, COLOR_BG);

    // LEFT = single beep
    if (mode_single_beep)
        draw_circle(50, 64, RADIUS, COLOR_ON);
    else
        draw_circle(50, 64, RADIUS, COLOR_OFF);

    // RIGHT = double beep
    if (!mode_single_beep)
        draw_circle(110, 64, RADIUS, COLOR_ON);
    else
        draw_circle(110, 64, RADIUS, COLOR_OFF);
}

// ---------------- TOGGLE ----------------
void lcd_toggle_beep_mode(void)
{
    mode_single_beep = !mode_single_beep;
    lcd_draw_beep_mode_ui();
}

// ---------------- GET ----------------
uint8_t get_beep_mode(void)
{
    return mode_single_beep;
}


void beep(void)
{
    if(mode_single_beep)
    {
        HAL_GPIO_WritePin(beeper_GPIO_Port, beeper_Pin, GPIO_PIN_SET);

        uint32_t start = HAL_GetTick();
        while((HAL_GetTick() - start) < time_of_beeping)
        {
            // wait
        }

        HAL_GPIO_WritePin(beeper_GPIO_Port, beeper_Pin, GPIO_PIN_RESET);
    }
    if(!mode_single_beep)
    {
        uint32_t start;
        // first beep
        HAL_GPIO_WritePin(beeper_GPIO_Port, beeper_Pin, GPIO_PIN_SET);
        start = HAL_GetTick();
        while((HAL_GetTick() - start) < (time_of_beeping / 2));

        HAL_GPIO_WritePin(beeper_GPIO_Port, beeper_Pin, GPIO_PIN_RESET);

        // wait
        start = HAL_GetTick();
        while((HAL_GetTick() - start) < (time_of_beeping / 2));

        // second beep
        HAL_GPIO_WritePin(beeper_GPIO_Port, beeper_Pin, GPIO_PIN_SET);
        start = HAL_GetTick();
        while((HAL_GetTick() - start) < (time_of_beeping / 2));

        HAL_GPIO_WritePin(beeper_GPIO_Port, beeper_Pin, GPIO_PIN_RESET);
    }
}

#include "button_debounce.h"

#define DEBOUNCE_TIME 30

void button_update(Button *b)
{
    switch (b->state)
    {
        case BTN_IDLE:
            if (HAL_GPIO_ReadPin(b->port, b->pin) == GPIO_PIN_SET)
            {
                b->state = BTN_DEBOUNCE;
                b->time = HAL_GetTick();
            }
            break;

        case BTN_DEBOUNCE:
            if (HAL_GetTick() - b->time >= DEBOUNCE_TIME)
            {
                if (HAL_GPIO_ReadPin(b->port, b->pin) == GPIO_PIN_SET)
                {
                    b->state = BTN_PRESSED;
                    b->pressed_event = 1;
                }
                else
                {
                    b->state = BTN_IDLE;
                }
            }
            break;

        case BTN_PRESSED:
            if (HAL_GPIO_ReadPin(b->port, b->pin) == GPIO_PIN_RESET)
            {
                b->state = BTN_IDLE;
            }
            break;
    }
}

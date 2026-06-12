#include <stdint.h>
#include <main.h>
typedef enum {
    BTN_IDLE,
    BTN_DEBOUNCE,
    BTN_PRESSED
} ButtonState;

typedef struct {
    GPIO_TypeDef *port;
    uint16_t pin;

    ButtonState state;
    uint32_t time;

    uint8_t pressed_event;   // 1 = klik wykryty
} Button;

// funkcje
void button_update(Button *b);


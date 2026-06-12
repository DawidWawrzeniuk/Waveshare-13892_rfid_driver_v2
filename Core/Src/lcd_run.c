#include "lcd_run.h"


uint32_t last_read_time = 0;
uint8_t last_UID[5] = {0};
uint8_t str[16];
uint8_t status;
uint8_t sNum[5];

char *msg1 = "Reading from card\r\n";
char *msg2 = "Reading from TAG\r\n";

void Read_data_from_rfid(void)
{
    // Check if 1 second passed since last read
    if ((HAL_GetTick() - last_read_time) > 1000)
    {
        // Detect new UID (compare with previous)
        if (memcpy(last_UID, str, 5) != 0)
        {
            // Save new UID
            memcpy(last_UID, str, 5);

            // Clear LCD lines 1–4
//            lcd_clear_line(0 * LINE_H, BLACK);
//            lcd_clear_line(1 * LINE_H, BLACK);
//            lcd_clear_line(2 * LINE_H, BLACK);
//            lcd_clear_line(3 * LINE_H, BLACK);

            // Request card presence
            status = MFRC522_Request(PICC_REQIDL, str);
            if (status == MI_OK)
            {
                // Anti-collision: read UID
                status = MFRC522_Anticoll(str);
                if (status == MI_OK)
                {
                    memcpy(sNum, str, 5);

                    // Check if card exists in database
                    char *name = find_card(str);

                    if (name != NULL)
                    {
                        // Send UART message
                        HAL_UART_Transmit(&huart2, (uint8_t*)msg1, strlen(msg1), HAL_MAX_DELAY);

                        // Display detection info
                        beep();
                        lcd_print_line(2, "DETECTED", WHITE, BLACK);
                        lcd_print_line(3, name, WHITE, BLACK);
                        lcd_print_line(1, "", WHITE, BLACK);
                        lcd_print_line(4, "", WHITE, BLACK);
                        lcd_print_line(5, "", WHITE, BLACK);
                    }
                }
            }

            // Update last read time
            last_read_time = HAL_GetTick();
        }
    }
}

#ifndef HAL_BUTTONS_H
#define HAL_BUTTONS_H

#include <stdbool.h>

void HAL_Buttons_Init(void);
bool HAL_Button1_IsPressed(void); // Nút chuyển Mode
bool HAL_Button2_IsPressed(void); // Nút tưới thủ công

#endif
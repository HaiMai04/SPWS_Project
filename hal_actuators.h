#ifndef HAL_ACTUATORS_H
#define HAL_ACTUATORS_H

#include "config.h"

typedef enum {
    LED_COLOR_OFF,
    LED_COLOR_GREEN,  
    LED_COLOR_YELLOW, 
    LED_COLOR_RED 
} LedColor_t;

void HAL_Actuators_Init(void);
void HAL_Pump_Control(PumpState_t state);
void HAL_LED_SetColor(LedColor_t color);

#endif
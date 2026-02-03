#include "hal_actuators.h"
#include <stdio.h>

void HAL_Actuators_Init(void) {
    printf("[HW] Actuators Initialized.\n");
}

void HAL_Pump_Control(PumpState_t state) {
    if (state == PUMP_ON) {
        printf(">>> [PUMP] ON (Dang tuoi nuoc...)\n");
    } else {
        printf(">>> [PUMP] OFF\n");
    }
}

void HAL_LED_SetColor(LedColor_t color) {
    printf("[LED] Mau hien tai: ");
    switch (color) {
        case LED_COLOR_GREEN: printf("XANH (He thong on dinh)\n"); break;
        case LED_COLOR_YELLOW: printf("VANG (Dang hoat dong)\n"); break;
        case LED_COLOR_RED: printf("DO (Canh bao)\n"); break;
        default: printf("TAT\n"); break;
    }
}
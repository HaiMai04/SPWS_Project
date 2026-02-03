#include "hal_sensors.h"
#include <stdlib.h> // cho rand()

void HAL_Sensors_Init(void) {
}

float HAL_Sensors_ReadSoilMoisture(void) {
    return 40.0f + (float)(rand() % 40);
}

float HAL_Sensors_ReadTemperature(void) {
    return 20.0f + (float)(rand() % 15);
}
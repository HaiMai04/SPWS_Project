#ifndef HAL_SENSORS_H
#define HAL_SENSORS_H

#include "config.h"

void HAL_Sensors_Init(void);
float HAL_Sensors_ReadSoilMoisture(void);
float HAL_Sensors_ReadTemperature(void);

#endif
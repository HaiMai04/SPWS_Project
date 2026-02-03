#ifndef CONFIG_H
#define CONFIG_H

#include <stdint.h>
#include <stdbool.h>
typedef enum {
    MODE_AUTO,
    MODE_MANUAL
} SystemMode_t;

typedef enum {
    PUMP_OFF,
    PUMP_ON
} PumpState_t;

typedef struct {
    uint8_t minMoistureThreshold; 
    uint8_t maxMoistureThreshold;
    uint32_t maxWateringDuration_s; 
    uint32_t manualWateringDuration_s; 
    uint32_t sensorReadInterval_s; 
} SystemSettings_t;

typedef struct {
    float soilMoisture;
    float temperature; 
} SensorData_t;

typedef struct {
    SystemMode_t currentMode;
    PumpState_t pumpState;
    uint32_t wateringTimer; 
} SystemState_t;

#endif
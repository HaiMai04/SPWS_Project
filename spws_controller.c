#include "spws_controller.h"
#include "hal_sensors.h"
#include "hal_actuators.h"
#include "hal_buttons.h"
#include <stdio.h>

// Các biến toàn cục nội bộ module
static SystemSettings_t settings;
static SystemState_t state;
static SensorData_t sensors;

void SPWS_Init(void) {
    // 1. Cài đặt giá trị mặc định
    settings.minMoistureThreshold = 50;  // Dưới 50% là tưới
    settings.maxMoistureThreshold = 80;  // Trên 80% là dừng
    settings.maxWateringDuration_s = 10; // Tưới tối đa 10s tự ngắt
    settings.manualWateringDuration_s = 5; // Tưới tay 5s
    settings.sensorReadInterval_s = 2;   // 2s đọc 1 lần

    // 2. Trạng thái ban đầu
    state.currentMode = MODE_AUTO;
    state.pumpState = PUMP_OFF;
    state.wateringTimer = 0;

    // 3. Khởi tạo phần cứng
    HAL_Sensors_Init();
    HAL_Actuators_Init();
    HAL_Buttons_Init();

    printf("[SYSTEM] SPWS Initialized. Mode: AUTO.\n");
}

static void RunAutoMode(void) {
    // Logic tưới tự động
    if (sensors.soilMoisture < settings.minMoistureThreshold) {
        if (state.pumpState == PUMP_OFF) {
            printf("[AUTO] Do am thap (%.1f%%) -> BAT BOM.\n", sensors.soilMoisture);
            state.pumpState = PUMP_ON;
            state.wateringTimer = 0;
            HAL_Pump_Control(PUMP_ON);
            HAL_LED_SetColor(LED_COLOR_YELLOW);
        }
    }

    if (state.pumpState == PUMP_ON) {
        state.wateringTimer++;
        // Điều kiện dừng bơm: Đủ ẩm HOẶC quá thời gian
        if (sensors.soilMoisture > settings.maxMoistureThreshold || 
            state.wateringTimer > settings.maxWateringDuration_s) {
            
            printf("[AUTO] Dung bom (Do am: %.1f%%, Timer: %ds).\n", 
                   sensors.soilMoisture, state.wateringTimer);
            state.pumpState = PUMP_OFF;
            HAL_Pump_Control(PUMP_OFF);
            HAL_LED_SetColor(LED_COLOR_GREEN);
        }
    } else {
        HAL_LED_SetColor(LED_COLOR_GREEN);
    }
}

static void RunManualMode(void) {
    // Nút 2: Kích hoạt tưới tay (Logic xử lý nút nhấn ở hàm Run chung)
    if (state.pumpState == PUMP_ON) {
        state.wateringTimer++;
        HAL_LED_SetColor(LED_COLOR_YELLOW);
        
        if (state.wateringTimer >= settings.manualWateringDuration_s) {
            printf("[MANUAL] Het thoi gian tuoi tay -> TAT BOM.\n");
            state.pumpState = PUMP_OFF;
            HAL_Pump_Control(PUMP_OFF);
        }
    } else {
        HAL_LED_SetColor(LED_COLOR_RED); // LED đỏ báo hiệu đang ở chế độ Manual/Standby
    }
}

void SPWS_Run(void) {
    // 1. Đọc cảm biến
    sensors.soilMoisture = HAL_Sensors_ReadSoilMoisture();
    sensors.temperature = HAL_Sensors_ReadTemperature();
    
    // In thông tin giám sát
    printf("\n--- Status: %s | Temp: %.1f C | Moisture: %.1f%% ---\n", 
           (state.currentMode == MODE_AUTO) ? "AUTO" : "MANUAL", 
           sensors.temperature, sensors.soilMoisture);

    // 2. Xử lý nút nhấn
    if (HAL_Button1_IsPressed()) {
        // Chuyển chế độ
        if (state.currentMode == MODE_AUTO) {
            state.currentMode = MODE_MANUAL;
            printf("[INPUT] Button 1 Pressed -> Switched to MANUAL.\n");
            // Tắt bơm ngay nếu đang chạy
            if (state.pumpState == PUMP_ON) {
                state.pumpState = PUMP_OFF;
                HAL_Pump_Control(PUMP_OFF);
            }
        } else {
            state.currentMode = MODE_AUTO;
            printf("[INPUT] Button 1 Pressed -> Switched to AUTO.\n");
        }
    }

    if (state.currentMode == MODE_MANUAL && HAL_Button2_IsPressed()) {
        // Kích hoạt tưới tay
        if (state.pumpState == PUMP_OFF) {
            printf("[INPUT] Button 2 Pressed -> Manual Watering Start.\n");
            state.pumpState = PUMP_ON;
            state.wateringTimer = 0;
            HAL_Pump_Control(PUMP_ON);
        }
    }

    // 3. Chạy logic theo chế độ
    if (state.currentMode == MODE_AUTO) {
        RunAutoMode();
    } else {
        RunManualMode();
    }
}
#include <Arduino.h>
#include <ESP_Panel_Library.h>
#include <esp_display_panel.hpp>
#include "esp_lv_adapter_arduino.h" 
#include "src/ui.h"

using namespace esp_panel::drivers;
using namespace esp_panel::board;
Board *board = nullptr;

void setup() {
    Serial.begin(115200);
    board = new Board();
    if (board == nullptr) {
        while (1) delay(100);
    }
    board->init();
    LCD *lcd = board->getLCD();
    Touch *touch = board->getTouch();
    board->begin();
    esp_lv_adapter_config_t adapter_config = ESP_LV_ADAPTER_DEFAULT_CONFIG();
    ESP_ERROR_CHECK(esp_lv_adapter_init(&adapter_config));
    esp_lv_adapter_display_config_t disp_config = ESP_LV_ADAPTER_DISPLAY_RGB_DEFAULT_CONFIG(
        lcd, 
        800, 
        480, 
        ESP_LV_ADAPTER_ROTATE_0
    );
    lv_display_t *disp = esp_lv_adapter_register_display(&disp_config);
    if (disp == nullptr) {

        while (1) delay(100);
    }
    if (touch != nullptr) {
        esp_lv_adapter_touch_config_t touch_config = ESP_LV_ADAPTER_TOUCH_DEFAULT_CONFIG(disp, touch);
        lv_indev_t *indev = esp_lv_adapter_register_touch(&touch_config);
        if (indev == nullptr) {

        }
    }
    ESP_ERROR_CHECK(esp_lv_adapter_start());
    if (esp_lv_adapter_lock(-1) == ESP_OK) {
        ui_init(); // Запуск вашей графики
        esp_lv_adapter_unlock();
    }
}

void loop() {
    
    vTaskDelay(pdMS_TO_TICKS(1000));
}

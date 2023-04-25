#pragma once

#include <Arduino.h>
#include <Arduino_LPS22HB.h>
#include <Arduino_HTS221.h>

void hi_init_rgb_led();
void hi_display_prediction(float result);
float hi_read_pressure();
float hi_read_temperature();
float hi_read_humidity();
void hi_init_hardware();
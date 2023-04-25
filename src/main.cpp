/* Edge Impulse ingestion SDK
 * Copyright (c) 2022 EdgeImpulse Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

/* Includes ---------------------------------------------------------------- */
#include "User_files/Hardware_interface/hardware_interface.h"
#include "User_files/BLE/BLE_api.h"
#include <stdint.h>
#include <stdlib.h>
#include "User_files/Machine_learning/machine_learning.h"

/**
* @brief      Arduino setup function
*/
void setup()
{
    // put your setup code here, to run once:
    Serial.begin(115200);
    // comment out the below line to cancel the wait for USB connection (needed for native USB)
    while (!Serial);
    Serial.println("Edge Impulse Inferencing Demo");
    hi_init_hardware();
    ble_api_init_ble();
    // summary of inferencing settings (from model_metadata.h)
    // ei_printf("Inferencing settings:\n");
    // ei_printf("\tImage resolution: %dx%d\n", EI_CLASSIFIER_INPUT_WIDTH, EI_CLASSIFIER_INPUT_HEIGHT);
    // ei_printf("\tFrame size: %d\n", EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE);
    // ei_printf("\tNo. of classes: %d\n", sizeof(ei_classifier_inferencing_categories) / sizeof(ei_classifier_inferencing_categories[0]));
}

/**
* @brief      Get data and run inferencing
*
* @param[in]  debug  Get debug info if true
*/
void loop()
{
    // Serial.println(hi_read_pressure());
    // Serial.println(hi_read_temperature());
    
    // float res[2];
    // predict(res);
    
    // Serial.print("Prediction[0]=");
    // Serial.print(res[0]);
    // Serial.print(" Prediction[1]=");
    // Serial.println(res[1]);
    // hi_display_prediction(res[1]);
    
    ble_api_ble_loop();
    
   
}
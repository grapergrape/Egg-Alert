#include "User_files/BLE/BLE_api.h"
#include "User_files/Hardware_interface/hardware_interface.h"
#include "User_files/Machine_learning/machine_learning.h"
#include "Arduino.h"

// Define the ESS (Enviromental Sensing Servuce) service and characteristics
BLEService essService("181A"); // ESS service UUID
BLECharacteristic temperatureCharacteristic("2A6E", BLERead | BLENotify,2); // Temperature characteristic UUID
BLECharacteristic pressureCharacteristic("2A6D", BLERead | BLENotify,4); // Pressure characteristic UUID

BLEDescriptor pressureDescriptor = BLEDescriptor("2901", "Pressure");
BLEDescriptor temperatureDescriptor = BLEDescriptor("2901", "Temperature");

//Current time service for sending time data
BLEService currentTimeService("1805");
BLECharacteristic currentTimeCharacteristic("2A2B", BLEWrite | BLERead | BLENotify, 9);

//Custom service for sending machine learning predictions
BLEService machineLearningService("19B10000-E8F2-537E-4F6C-D104768A1214"); // create a BLE service
BLEIntCharacteristic predictionCharacteristic("19B10003-E8F2-537E-4F6C-D104768A1214", BLERead | BLENotify);
BLEDescriptor predictionDescriptor = BLEDescriptor("2901", "Egg prediction");

void ble_api_ble_loop()
{
    long previousMillis = 0;
    // wait for a Bluetooth® Low Energy central
    BLEDevice central = BLE.central();
    if (central) 
    {
        Serial.print("Connected to central: ");
        // print the central's BT address:
        Serial.println(central.address());
        // turn on the LED to indicate the connection:
        digitalWrite(LED_BUILTIN, HIGH);

    
        // while the central is connected:
        while (central.connected()) 
        {
            long currentMillis = millis();
            // if 200ms have passed, check the battery level:
            if (currentMillis - previousMillis >= 5000) 
            {
                previousMillis = currentMillis;

                uint32_t pressureValue = (uint32_t)(hi_read_pressure() * 10); // read pressure from sensor
                uint16_t  temperatureValue = (uint16_t) (hi_read_temperature()*100); // read temperature from sensor
                float predictionValue[2]; // make a machine learning prediction
                predict(predictionValue);
                int prediction;
                if(predictionValue[1] > 0.5)
                {
                    prediction = 1;
                }else{
                    prediction = 0;
                }
                pressureCharacteristic.writeValue((uint8_t*)&pressureValue, sizeof(pressureValue));
                temperatureCharacteristic.writeValue((uint8_t*)&temperatureValue, sizeof(temperatureValue));
                predictionCharacteristic.writeValue(prediction);
                hi_display_prediction(predictionValue[1]);

                char time[9];
                //currentTimeCharacteristic.readValue((unsigned char *)time, 9);
                //Serial.print(time);
            
            }
        }
      // when the central disconnects, turn off the LED:
      digitalWrite(LED_BUILTIN, LOW);
      Serial.print("Disconnected from central: ");
      Serial.println(central.address());
      

   }
}
static void handle_current_time_ble(BLEDevice central, BLECharacteristic characteristic)
{
    char time[9];
    currentTimeCharacteristic.readValue((unsigned char *)time, 9);
    Serial.print(time);
    Serial.println();
}
void ble_api_init_ble()
{
    if (!BLE.begin()) {
        Serial.println("failed to initialize BLE!");
        while (1);
    }

    /*Setup device name*/
    BLE.setLocalName("EggAlert");
    BLE.setDeviceName("EggAlert");

    /*Setup service for sending ML predictions*/
    BLE.setAdvertisedServiceUuid(machineLearningService.uuid());
    BLE.setAppearance(0x0540);
    machineLearningService.addCharacteristic(predictionCharacteristic);
    predictionCharacteristic.addDescriptor(predictionDescriptor);
    BLE.addService(machineLearningService);

    /*Setup service for sending enviorment data*/
    BLE.setAdvertisedService(essService.uuid());
    essService.addCharacteristic(temperatureCharacteristic);
    essService.addCharacteristic(pressureCharacteristic);
    BLE.addService(essService);

    /*Setup current time service*/
    BLE.setAdvertisedService(currentTimeService);
    currentTimeService.addCharacteristic(currentTimeCharacteristic);
    //add event handler
    currentTimeCharacteristic.setEventHandler(BLEWritten, handle_current_time_ble);
    BLE.addService(currentTimeService);
    BLE.advertise();

}
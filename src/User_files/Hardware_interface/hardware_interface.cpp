#include "User_files/Hardware_interface/hardware_interface.h"

void hi_init_rgb_led()
{
    pinMode(LEDR,OUTPUT);
    pinMode(LEDG,OUTPUT);
    pinMode(LEDB,OUTPUT);
    pinMode(LED_PWR, OUTPUT);
}

void hi_display_prediction(float result)
{
    if(result <= 0.5)
    {
        pinMode(LED_PWR, HIGH);
        digitalWrite(LEDR,0);
        digitalWrite(LEDG,1);
        digitalWrite(LEDB,1);

    }else{
        pinMode(LED_PWR, HIGH);
        digitalWrite(LEDR,1);
        digitalWrite(LEDG,0);
        digitalWrite(LEDB,1);
    }
}

float hi_read_pressure()
{
    return BARO.readPressure(MILLIBAR);
}
float hi_read_temperature()
{
    return BARO.readTemperature();
}
float hi_read_humidity()
{
    return HTS.readHumidity();
}
void hi_init_hardware()
{
    hi_init_rgb_led();

    if (!BARO.begin()) 
    {
        Serial.println("Failed to initialize pressure sensor!");
        while (1);
    }

}
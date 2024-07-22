#ifndef TEMPGAS_HPP
#define TEMPGAS_HPP

#include <Adafruit_SGP40.h>
#include <Adafruit_BME680.h>
#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>

namespace TEMPGAS {

#define BME_SCK 13
#define BME_MISO 12
#define BME_MOSI 11
#define BME_CS 10
#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_SGP40 sgp;
Adafruit_BME680 bme;

void initialise();
void measurement();

void initialise() {
    Serial.begin(115200);
        while (!Serial) { delay(10); } // Wait for serial console to open!

    Serial.println("SGP40 test");

    sgp.begin();
    if (! sgp.begin()){
        Serial.println("Sensor not found :(");
        while (1);
    }

    Serial.print("Found SGP40 serial #");
    Serial.print(sgp.serialnumber[0], HEX);
    Serial.print(sgp.serialnumber[1], HEX);
    Serial.println(sgp.serialnumber[2], HEX);

    // Set up oversampling and filter initialization
    bme.setTemperatureOversampling(BME680_OS_8X);
    bme.setHumidityOversampling(BME680_OS_2X);
    bme.setPressureOversampling(BME680_OS_4X);
    bme.setIIRFilterSize(BME680_FILTER_SIZE_3);
    bme.setGasHeater(320, 150); // 320*C for 150 ms
    // Tell BME680 to begin measurement.
    bme.begin();
    unsigned long endTime = bme.beginReading();
    if (endTime == 0) {
        Serial.println(F("Failed to begin reading :("));
        return;
    }
}

float temperature_measurement() {
    float t = bme.readTemperature();
    Serial.print("Temp *C = "); Serial.print(t); Serial.print("\t\t");
    float h = bme.readHumidity();
    Serial.print("Hum. % = "); Serial.println(h);

    return t;
}

int32_t voc_measurement(){
    int32_t voc_index;
    float t = bme.readTemperature();
    float h = bme.readHumidity();
    voc_index = sgp.measureVocIndex(t, h);
    Serial.print("Voc Index: ");
    Serial.println(voc_index);

    return voc_index;
}

}//namespace TEMPGAS

#endif
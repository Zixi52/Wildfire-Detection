#ifndef GAS_HPP
#define GAS_HPP

#include <Adafruit_SGP40.h>
#include <Adafruit_BME680.h>
#include <Arduino.h>

namespace GAS {

Adafruit_SGP40 sgp(*theWire);
Adafruit_BME680 bme;

void initialize();
void measurement();

void initialize() {
    Serial.begin(115200);
        while (!Serial) { delay(10); } // Wait for serial console to open!

    Serial.println("SGP40 test");

    if (! sgp.begin()){
        Serial.println("Sensor not found :(");
        while (1);
    }

    Serial.print("Found SGP40 serial #");
    Serial.print(sgp.serialnumber[0], HEX);
    Serial.print(sgp.serialnumber[1], HEX);
    Serial.println(sgp.serialnumber[2], HEX);
}

void measurement() {
    uint16_t sraw;
    int32_t voc_index;
  
    float t = bme.readTemperature();
    Serial.print("Temp *C = "); Serial.print(t); Serial.print("\t\t");
    float h = bme.readHumidity();
    Serial.print("Hum. % = "); Serial.println(h);

    sraw = sgp.measureRaw(t, h);
    Serial.print("Raw measurement: ");
    Serial.println(sraw);

    voc_index = sgp.measureVocIndex(t, h);
    Serial.print("Voc Index: ");
    Serial.println(voc_index);
}
}

#endif
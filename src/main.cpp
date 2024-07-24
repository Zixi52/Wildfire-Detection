#include <Arduino.h>
#include <coord.hpp>
#include <gps.hpp>
#include <io.hpp>
#include <temp-gas.hpp>
#include <Adafruit_GFX.h>

float received_temp;
float received_VOC;

void handleTemp(AdafruitIO_Data *data);
void handleVOC(AdafruitIO_Data *data);
void alert();

void setup() {
  // start the serial connection
  Serial.begin(115200);
  while (!Serial);

  // initialise peripherals
  GPS::initialise();
  TEMPGAS::initialise();
  // connect to io.adafruit.com
  IO::try_connect();

  IO::sharedTemp->onMessage(handleTemp);
  IO::sharedVOC->onMessage(handleVOC);
}

void loop() {
  IO::run();
  delay(7000);

  auto my_coords{GPS::query_GPS()};

  if (IO::IO_connected) {
    IO::location->save(1, my_coords.latitude, my_coords.longitude,
                      my_coords.altitude);
    IO::temp->save(TEMPGAS::temperature_measurement()); 
    IO::voc_lev->save(TEMPGAS::voc_measurement());
    IO::avgTemp->save((received_temp + TEMPGAS::temperature_measurement())/2.0);
    IO::avgVOC->save((received_VOC + TEMPGAS::voc_measurement())/2.0);
    alert();
  } else {
    //Serial prints all the stuff
    Serial.println(my_coords.latitude);
    Serial.println(my_coords.lat);
    Serial.println(my_coords.longitude);
    Serial.println(my_coords.lon);
    Serial.println(my_coords.altitude);
    Serial.println(TEMPGAS::temperature_measurement());
    Serial.println(TEMPGAS::voc_measurement());
  }
}

void handleTemp(AdafruitIO_Data *data) {
  received_temp = data->toFloat();

  // Fetch info from IO
  double received_lat = data->lat();
  double received_lon = data->lon();
  double received_ele = data->ele();

}

void handleVOC(AdafruitIO_Data *data) {
  received_VOC = data->toFloat();

  // Fetch info from IO
  double received_lat = data->lat();
  double received_lon = data->lon();
  double received_ele = data->ele();

}

void alert() {
    if (TEMPGAS::temperature_measurement() >= 500 && TEMPGAS::voc_measurement() >= 1250 && received_temp >= 100) {
        IO::alert->save("Fire");
    } else if (TEMPGAS::temperature_measurement() >= 100 || TEMPGAS::voc_measurement() >= 250 || received_temp >= 100) {
        IO::alert->save("Smoke");
    } else {
        IO::alert->save("No Hay Problema");
    }
}
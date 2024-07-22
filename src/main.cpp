#include <Arduino.h>
#include <coord.hpp>
#include <gps.hpp>
#include <io.hpp>
#include <temp-gas.hpp>

void setup() {
  // start the serial connection
  Serial.begin(115200);
  while (!Serial);

  // initialise peripherals
  GPS::initialise();
  TEMPGAS::initialise();
  // connect to io.adafruit.com
  IO::try_connect();
}

void loop() {
  IO::run();
  delay(5000);

  auto my_coords{GPS::query_GPS()};

  if (IO::IO_connected) {
    IO::location->save(1, my_coords.latitude, my_coords.longitude,
                      my_coords.altitude);
    IO::temp->save(2, TEMPGAS::temperature_measurement()); 
    IO::voc_lev->save(3, TEMPGAS::voc_measurement()); 
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
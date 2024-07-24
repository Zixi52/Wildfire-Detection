#ifndef IO_HPP
#define IO_HPP

// Fetch your key from Adafruit
#define IO_USERNAME ""
#define IO_KEY ""

/******************************* WIFI **************************************/

#define WIFI_SSID ""
#define WIFI_PASS ""

#include <AdafruitIO_WiFi.h>

namespace IO {

bool IO_connected{false};

// IO handler
AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);

// Feeds
AdafruitIO_Feed *location = io.feed("GPS");
AdafruitIO_Feed *temp = io.feed("Heat");
AdafruitIO_Feed *voc_lev = io.feed("VOC");
AdafruitIO_Feed *alert = io.feed("alert");
AdafruitIO_Feed *sharedTemp = io.feed("Temperature", "thuang8823");
AdafruitIO_Feed *sharedVOC = io.feed("VOC", "thuang8823");
AdafruitIO_Feed *avgTemp = io.feed("Average Temp");
AdafruitIO_Feed *avgVOC = io.feed("Average VOC Level");

// attempt connection
void try_connect() {
  Serial.print("Connecting to Adafruit IO");

  io.connect();

  // waits for a connection for 10 seconds
  for (std::size_t i{0}; (i < 20) || (io.status() < AIO_CONNECTED); i++) {
    Serial.print(".");
    delay(500);
  }

  if (io.status() < AIO_CONNECTED) {
    Serial.println("Connection failed");
  } else {
    Serial.println("Connected to Adafruit IO\n");
    Serial.println(io.statusText());
    IO_connected = true;
  }
}

// run if connected
void run() { io.run(); }

}  // namespace IO

#endif  // IO_HPP
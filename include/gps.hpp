#ifndef GPS_HPP
#define GPS_HPP

#include <Adafruit_GPS.h>
#include <Arduino.h>
#include <coord.hpp>

namespace GPS {

Adafruit_GPS GPS(&Wire);

/**
 * @brief initialises the GPS
 *
 */
void initialise() {
  GPS.begin(0x10);

  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);

  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);

  GPS.sendCommand(PGCMD_ANTENNA);
}

/**
 * @brief queries GPS for info
 *
 * @return coord
 */
coord query_GPS() {
  return {GPS.latitude, GPS.lat, GPS.longitude, GPS.lon, GPS.altitude};
}

}  // namespace GPS

#endif  // GPS_HPP
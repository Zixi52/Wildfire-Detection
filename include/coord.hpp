#ifndef COORD_HPP
#define COORD_HPP

namespace GPS {

/**
 * @brief struct to handle coords
 *
 */
struct coord {
  double latitude;
  char lat;
  double longitude;
  char lon;
  double altitude;

  coord() = default;

  coord(double latitude, char lat, double longitude, char lon, double altitude)
      : latitude(latitude),
        lat(lat),
        longitude(longitude),
        lon(lon),
        altitude(altitude) {}
};

}  // namespace GPS

#endif  // COORD_HPP
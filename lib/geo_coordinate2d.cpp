#include "quad_keys/geo_coordinate2d.h"

namespace quad_keys {
const double Longitude::min_longitude = -180.0;
const double Longitude::max_longitude = 180.0;
const double Latitude::min_latitude = -90.0;
const double Latitude::max_latitude = 90.0;

Longitude::Longitude(double val)
    : m_val(std::max(std::min(max_longitude, val), min_longitude)) {}

Longitude::Longitude(const Longitude &other) : m_val(other.m_val) {}

Longitude &Longitude::operator=(const Longitude &rhs) {
  m_val = rhs.m_val;
  return (*this);
}

bool Longitude::near(const Longitude &other, const double eps) const {
  const double diff = std::fabs(m_val - other.m_val);
  return (diff <= eps);
}

Latitude::Latitude(double val)
    : m_val(std::max(std::min(max_latitude, val), min_latitude)) {}

Latitude::Latitude(const Latitude &other) : m_val(other.m_val) {}

Latitude &Latitude::operator=(const Latitude &rhs) {
  m_val = rhs.m_val;
  return (*this);
}

bool Latitude::near(const Latitude &other, const double eps) const {
  const double diff = std::fabs(m_val - other.m_val);
  return (diff <= eps);
}

GeoCoordinate2d::GeoCoordinate2d() : m_longitude(0.0), m_latitude(0.0) {}

GeoCoordinate2d::GeoCoordinate2d(const GeoCoordinate2d &other)
    : m_longitude(other.m_longitude), m_latitude(other.m_latitude) {}

GeoCoordinate2d &GeoCoordinate2d::operator=(const GeoCoordinate2d &rhs) {
  m_longitude = rhs.m_longitude;
  m_latitude = rhs.m_latitude;
  return (*this);
}

GeoCoordinate2d::GeoCoordinate2d(const struct Longitude &longit,
                                 const struct Latitude &latit)
    : m_longitude(longit), m_latitude(latit) {}

void GeoCoordinate2d::set_longitude(double longit) {
  struct Longitude l(longit);
  m_longitude = l;
}

void GeoCoordinate2d::set_latitude(double latit) {
  struct Latitude l(latit);
  m_latitude = l;
}

bool GeoCoordinate2d::near(const GeoCoordinate2d &other,
                           const double eps) const {
  return m_latitude.near(other.m_latitude, eps) &&
         m_longitude.near(other.m_longitude, eps);
}
};  // namespace quad_keys

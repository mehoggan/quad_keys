#include "quad_key/geo_coordinate2d.h"

namespace quad_keys
{
  const double longitude::min_longitude = -180.0;
  const double longitude::max_longitude = 180.0;
  const double latitude::min_latitude = -90.0;
  const double latitude::max_latitude = 90.0;

  longitude::longitude(double val) :
    m_val(std::max(std::min(max_longitude, val), min_longitude))
  {}

  longitude::longitude(const longitude &other) :
    m_val(other.m_val)
  {}

  longitude &longitude::operator=(const longitude &rhs)
  {
    m_val = rhs.m_val;
    return (*this);
  }

  bool longitude::near(const longitude &other,
    const double eps) const
  {
    const double diff = std::fabs(m_val - other.m_val);
    return (diff <= eps);
  }

  latitude::latitude(double val) :
    m_val(std::max(std::min(max_latitude, val), min_latitude))
  {}

  latitude::latitude(const latitude &other) :
      m_val(other.m_val)
  {}

  latitude &latitude::operator=(const latitude &rhs)
  {
    m_val = rhs.m_val;
    return (*this);
  }

  bool latitude::near(const latitude &other, const double eps) const
  {
    const double diff = std::fabs(m_val - other.m_val);
    return (diff <= eps);
  }

  geo_coordinate2d::geo_coordinate2d() :
    m_longitude(0.0),
    m_latitude(0.0)
  {}

  geo_coordinate2d::geo_coordinate2d(const geo_coordinate2d &other) :
    m_longitude(other.m_longitude),
    m_latitude(other.m_latitude)
  {}

  geo_coordinate2d &geo_coordinate2d::operator=(const geo_coordinate2d &rhs)
  {
    m_longitude = rhs.m_longitude;
    m_latitude = rhs.m_latitude;
    return (*this);
  }

  geo_coordinate2d::geo_coordinate2d(const struct longitude &longit,
    const struct latitude &latit) :
    m_longitude(longit),
    m_latitude(latit)
  {}

  void geo_coordinate2d::longitude(double longit)
  {
    struct longitude l(longit);
    m_longitude = l;
  }

  void geo_coordinate2d::latitude(double latit)
  {
    struct latitude l(latit);
    m_latitude = l;
  }

  bool geo_coordinate2d::near(const geo_coordinate2d &other,
    const double eps) const
  {
    return m_latitude.near(other.m_latitude, eps) &&
      m_longitude.near(other.m_longitude, eps);
  }
};

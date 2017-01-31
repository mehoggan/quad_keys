#ifndef GEOCOORDINATE2D_H_INCLUDED
#define GEOCOORDINATE2D_H_INCLUDED

#include "declspec.h"

#include "quad_key/geo_coordinate2d.h"

#include <algorithm>
#include <cfloat>
#include <cmath>
#include <cstdint>
#include <limits>
#include <ostream>
#include <type_traits>

namespace quad_keys
{
  struct DLLSPEC_QUADKEY longitude
  {
  public:
    static const double min_longitude;
    static const double max_longitude;

  private:
    double m_val;
    friend class geo_coordinate2d;

  public:
    explicit longitude(double val);

    longitude(const longitude &other);
    longitude &operator=(const longitude &rhs);

    double val() const { return m_val; }

    bool near(const longitude &other,
      const double eps = std::numeric_limits<double>::epsilon()) const;

    bool operator<(const longitude &rhs) const
    {
      return m_val < rhs.m_val;
    }
    bool operator<=(const longitude &rhs) const
    {
      return m_val <= rhs.m_val;
    }
    bool operator>(const longitude &rhs) const
    {
      return !((*this) <= rhs);
    }
    bool operator>=(const longitude &rhs) const
    {
      return !((*this) < rhs);
    }
    bool operator==(const longitude &rhs) const
    {
      return m_val == rhs.m_val;
    }
    bool operator!=(const longitude &rhs) const
    {
      return !((*this) == rhs);
    }
    double operator-(const longitude &subtrahend) const
    {
      return (m_val - subtrahend.m_val);
    }
    friend std::ostream &operator<<(std::ostream &out, const longitude &obj)
    {
      return out << obj.m_val;
    }
  };

  struct DLLSPEC_QUADKEY latitude
  {
  public:
    static const double min_latitude;
    static const double max_latitude;

  private:
    double m_val;
    friend class geo_coordinate2d;

  public:
    explicit latitude(double val);

    latitude(const latitude &other);
    latitude &operator=(const latitude &rhs);

    double val() const { return m_val; }

    bool near(const latitude &other,
      const double eps = std::numeric_limits<double>::epsilon()) const;

    bool operator<(const latitude &rhs) const
    {
      return m_val < rhs.m_val;
    }
    bool operator<=(const latitude &rhs) const
    {
      return m_val <= rhs.m_val;
    }
    bool operator>(const latitude &rhs) const
    {
      return !((*this) <= rhs);
    }
    bool operator>=(const latitude &rhs) const
    {
      return !((*this) < rhs);
    }
    bool operator==(const latitude &rhs) const
    {
      return m_val == rhs.m_val;
    }
    bool operator!=(const latitude &rhs) const
    {
      return !((*this) == rhs);
    }
    double operator-(const latitude &subtrahend) const
    {
      return (m_val - subtrahend.m_val);
    }
    friend std::ostream &operator<<(std::ostream &out, const latitude &obj)
    {
      return out << obj.m_val;
    }
  };

  class DLLSPEC_QUADKEY geo_coordinate2d
  {
  private:
    longitude m_longitude;
    latitude m_latitude;
    friend class geo_coordinate_bounding_box2d;

  public:
    geo_coordinate2d();

    geo_coordinate2d(const longitude &longitude, const latitude &latitude);

    geo_coordinate2d(const geo_coordinate2d &other);
    geo_coordinate2d &operator=(const geo_coordinate2d &rhs);

    void set_longitude(double longit);
    void set_latitude(double latit);
    void set_longitude(const struct longitude &longit)
    {m_longitude = longit;}
    void set_latitude(const struct latitude &latit)
    {m_latitude = latit;}

    const struct longitude &get_longitude() const {return m_longitude;}
    const struct latitude &get_latitude() const {return m_latitude;}

    bool near(const geo_coordinate2d &other,
      const double eps = std::numeric_limits<double>::epsilon()) const;

    inline bool operator==(const geo_coordinate2d &rhs) const
    {
      return (m_longitude == rhs.m_longitude) &&
        (m_latitude == rhs.m_latitude);
    }

    inline bool operator!=(const geo_coordinate2d &rhs) const
    {
        return !((*this) == rhs);
    }
    friend std::ostream &operator<<(std::ostream &out,
      const geo_coordinate2d &obj)
    {
      return out << "(" << obj.m_longitude << "," << obj.m_latitude << ")";
    }
  };
}
#endif

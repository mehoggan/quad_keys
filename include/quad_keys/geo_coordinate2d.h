#ifndef GEOCOORDINATE2D_H_INCLUDED
#define GEOCOORDINATE2D_H_INCLUDED

#include <algorithm>
#include <cfloat>
#include <cmath>
#include <cstdint>
#include <limits>
#include <ostream>
#include <type_traits>

namespace quad_keys
{
  struct Longitude
  {
  public:
    static const double min_longitude;
    static const double max_longitude;

  private:
    double m_val;
    friend class GeoCoordinate2d;

  public:
    explicit Longitude(double val);

    Longitude(const Longitude &other);
    Longitude &operator=(const Longitude &rhs);

    double val() const { return m_val; }

    bool near(const Longitude &other,
      const double eps = std::numeric_limits<double>::epsilon()) const;

    bool operator<(const Longitude &rhs) const
    {
      return m_val < rhs.m_val;
    }
    bool operator<=(const Longitude &rhs) const
    {
      return m_val <= rhs.m_val;
    }
    bool operator>(const Longitude &rhs) const
    {
      return !((*this) <= rhs);
    }
    bool operator>=(const Longitude &rhs) const
    {
      return !((*this) < rhs);
    }
    bool operator==(const Longitude &rhs) const
    {
      return m_val == rhs.m_val;
    }
    bool operator!=(const Longitude &rhs) const
    {
      return !((*this) == rhs);
    }
    double operator-(const Longitude &subtrahend) const
    {
      return (m_val - subtrahend.m_val);
    }
    friend std::ostream &operator<<(std::ostream &out, const Longitude &obj)
    {
      return out << obj.m_val;
    }
  };

  struct Latitude
  {
  public:
    static const double min_latitude;
    static const double max_latitude;

  private:
    double m_val;
    friend class GeoCoordinate2d;

  public:
    explicit Latitude(double val);

    Latitude(const Latitude &other);
    Latitude &operator=(const Latitude &rhs);

    double val() const { return m_val; }

    bool near(const Latitude &other,
      const double eps = std::numeric_limits<double>::epsilon()) const;

    bool operator<(const Latitude &rhs) const
    {
      return m_val < rhs.m_val;
    }
    bool operator<=(const Latitude &rhs) const
    {
      return m_val <= rhs.m_val;
    }
    bool operator>(const Latitude &rhs) const
    {
      return !((*this) <= rhs);
    }
    bool operator>=(const Latitude &rhs) const
    {
      return !((*this) < rhs);
    }
    bool operator==(const Latitude &rhs) const
    {
      return m_val == rhs.m_val;
    }
    bool operator!=(const Latitude &rhs) const
    {
      return !((*this) == rhs);
    }
    double operator-(const Latitude &subtrahend) const
    {
      return (m_val - subtrahend.m_val);
    }
    friend std::ostream &operator<<(std::ostream &out, const Latitude &obj)
    {
      return out << obj.m_val;
    }
  };

  class GeoCoordinate2d
  {
  private:
    Longitude m_longitude;
    Latitude m_latitude;
    friend class GeoCoordinateBoundingBox2d;

  public:
    GeoCoordinate2d();

    GeoCoordinate2d(const Longitude &longitude, const Latitude &latitude);

    GeoCoordinate2d(const GeoCoordinate2d &other);
    GeoCoordinate2d &operator=(const GeoCoordinate2d &rhs);

    void set_longitude(double longit);
    void set_latitude(double latit);
    void set_longitude(const struct Longitude &longit)
    {m_longitude = longit;}
    void set_latitude(const struct Latitude &latit)
    {m_latitude = latit;}

    const struct Longitude &get_longitude() const {return m_longitude;}
    const struct Latitude &get_latitude() const {return m_latitude;}

    bool near(const GeoCoordinate2d &other,
      const double eps = std::numeric_limits<double>::epsilon()) const;

    inline bool operator==(const GeoCoordinate2d &rhs) const
    {
      return (m_longitude == rhs.m_longitude) &&
        (m_latitude == rhs.m_latitude);
    }

    inline bool operator!=(const GeoCoordinate2d &rhs) const
    {
      return !((*this) == rhs);
    }

    friend std::ostream &operator<<(std::ostream &out,
      const GeoCoordinate2d &obj)
    {
      return out << "(" << obj.m_longitude << "," << obj.m_latitude << ")";
    }
  };
}
#endif

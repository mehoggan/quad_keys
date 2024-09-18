#ifndef GEOCOORDINATEBOUNDINGBOX2D_H_INCLUDED
#define GEOCOORDINATEBOUNDINGBOX2D_H_INCLUDED

#include "quad_keys/geo_coordinate2d.h"

namespace quad_keys {
class GeoCoordinateBoundingBox2d {
 private:
  GeoCoordinate2d m_lower_left;
  GeoCoordinate2d m_upper_right;

 public:
  GeoCoordinateBoundingBox2d();

  GeoCoordinateBoundingBox2d(const GeoCoordinate2d &coordinate0,
                             const GeoCoordinate2d &coordinate1);

  bool contains(const GeoCoordinate2d &coordinate) const;
  void grow_to_contain(const GeoCoordinate2d &coordinate);

  const GeoCoordinate2d &lower_left() const { return m_lower_left; }
  const GeoCoordinate2d &upper_right() const { return m_upper_right; }
  const GeoCoordinate2d upper_left() const {
    return GeoCoordinate2d(m_lower_left.get_longitude(),
                           m_upper_right.get_latitude());
  }
  const GeoCoordinate2d lower_right() const {
    return GeoCoordinate2d(m_upper_right.get_longitude(),
                           m_lower_left.get_latitude());
  }
  bool operator==(const GeoCoordinateBoundingBox2d &rhs) const {
    return (m_lower_left == rhs.m_lower_left &&
            m_upper_right == rhs.m_upper_right);
  }
  friend std::ostream &operator<<(std::ostream &out,
                                  const GeoCoordinateBoundingBox2d &obj) {
    return out << "[" << obj.m_lower_left << "," << obj.m_upper_right << "]";
  }

  bool is_valid() const;
};
}  // namespace quad_keys
#endif

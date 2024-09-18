#include "quad_keys/geo_coordinate_bounding_box2d.h"

namespace quad_keys {
GeoCoordinateBoundingBox2d::GeoCoordinateBoundingBox2d()
    : m_lower_left(Longitude(180.0), Latitude(90.0)),
      m_upper_right(Longitude(-180.0), Latitude(-90.0)) {}

GeoCoordinateBoundingBox2d::GeoCoordinateBoundingBox2d(
    const GeoCoordinate2d &coordinate0, const GeoCoordinate2d &coordinate1)
    : m_lower_left(Longitude(180.0), Latitude(90.0)),
      m_upper_right(Longitude(-180.0), Latitude(-90.0)) {
  grow_to_contain(coordinate0);
  grow_to_contain(coordinate1);
}

bool GeoCoordinateBoundingBox2d::contains(
    const GeoCoordinate2d &coordinate) const {
  bool is_in = true;

  is_in &= is_valid();
  is_in &= (coordinate.get_longitude() >= lower_left().get_longitude());
  is_in &= (coordinate.get_latitude() >= lower_left().get_latitude());
  is_in &= (coordinate.get_longitude() <= upper_right().get_longitude());
  is_in &= (coordinate.get_latitude() <= upper_right().get_latitude());

  return is_in;
}

void GeoCoordinateBoundingBox2d::grow_to_contain(
    const GeoCoordinate2d &coordinate) {
  GeoCoordinate2d lower_left(
      std::min(m_lower_left.get_longitude(), coordinate.get_longitude()),
      std::min(m_lower_left.get_latitude(), coordinate.get_latitude()));
  GeoCoordinate2d upper_right(
      std::max(m_upper_right.get_longitude(), coordinate.get_longitude()),
      std::max(m_upper_right.get_latitude(), coordinate.get_latitude()));

  m_lower_left = lower_left;
  m_upper_right = upper_right;
}

bool GeoCoordinateBoundingBox2d::is_valid() const {
  bool valid = true;

  valid &= (m_lower_left.get_longitude() <= m_upper_right.get_longitude());
  valid &= (m_lower_left.get_latitude() <= m_upper_right.get_latitude());

  return valid;
}
}  // namespace quad_keys

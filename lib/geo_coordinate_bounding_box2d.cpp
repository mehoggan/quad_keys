#include "quad_key/geo_coordinate_bounding_box2d.h"

namespace quad_keys
{
  geo_coordinate_bounding_box2d::geo_coordinate_bounding_box2d() :
    m_lower_left(longitude(180.0), latitude(90.0)),
    m_upper_right(longitude(-180.0), latitude(-90.0))
  {}

  geo_coordinate_bounding_box2d::geo_coordinate_bounding_box2d(
    const geo_coordinate2d &coordinate0,
    const geo_coordinate2d &coordinate1) :
    m_lower_left(longitude(180.0), latitude(90.0)),
    m_upper_right(longitude(-180.0), latitude(-90.0))
  {
    grow_to_contain(coordinate0);
    grow_to_contain(coordinate1);
  }

  bool geo_coordinate_bounding_box2d::contains(
    const geo_coordinate2d &coordinate) const
  {
    bool is_in = true;

    is_in &= is_valid();
    is_in &= (coordinate.get_longitude() >= lower_left().get_longitude());
    is_in &= (coordinate.get_latitude() >= lower_left().get_latitude());
    is_in &= (coordinate.get_longitude() <= upper_right().get_longitude());
    is_in &= (coordinate.get_latitude() <= upper_right().get_latitude());

    return is_in;
  }

  void geo_coordinate_bounding_box2d::grow_to_contain(
    const geo_coordinate2d &coordinate)
  {
    geo_coordinate2d lower_left(
      std::min(m_lower_left.get_longitude(), coordinate.get_longitude()),
      std::min(m_lower_left.get_latitude(), coordinate.get_latitude()));
    geo_coordinate2d upper_right(
      std::max(m_upper_right.get_longitude(), coordinate.get_longitude()),
      std::max(m_upper_right.get_latitude(), coordinate.get_latitude()));

    m_lower_left = lower_left;
    m_upper_right = upper_right;
  }

  bool geo_coordinate_bounding_box2d::is_valid() const
  {
    bool valid = true;

    valid &= (m_lower_left.get_longitude() <= m_upper_right.get_longitude());
    valid &= (m_lower_left.get_latitude() <= m_upper_right.get_latitude());

    return valid;
  }
}

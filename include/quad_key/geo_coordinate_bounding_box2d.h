#ifndef GEOCOORDINATEBOUNDINGBOX2D_H_INCLUDED
#define GEOCOORDINATEBOUNDINGBOX2D_H_INCLUDED

#include "quad_keys_declspec.h"

#include "quad_key/geo_coordinate2d.h"

namespace quad_keys
{
  class DLLSPEC_QUADKEY geo_coordinate_bounding_box2d
  {
  private:
    geo_coordinate2d m_lower_left;
    geo_coordinate2d m_upper_right;

  public:
    geo_coordinate_bounding_box2d();

    geo_coordinate_bounding_box2d(
      const geo_coordinate2d &coordinate0,
      const geo_coordinate2d &coordinate1);

    bool contains(const geo_coordinate2d &coordinate) const;
    void grow_to_contain(const geo_coordinate2d &coordinate);

    const geo_coordinate2d &lower_left() const {return m_lower_left;}
    const geo_coordinate2d &upper_right() const {return m_upper_right;}
    const geo_coordinate2d upper_left() const
    {
      return geo_coordinate2d(m_lower_left.get_longitude(),
        m_upper_right.get_latitude());
    }
    const geo_coordinate2d lower_right() const
    {
      return geo_coordinate2d(m_upper_right.get_longitude(),
        m_lower_left.get_latitude());
    }
    bool operator==(const geo_coordinate_bounding_box2d &rhs) const
    {
      return (m_lower_left == rhs.m_lower_left &&
        m_upper_right == rhs.m_upper_right);
    }
    friend std::ostream &operator<<(std::ostream &out,
      const geo_coordinate_bounding_box2d &obj)
    {
      return out << "[" << obj.m_lower_left << "," << obj.m_upper_right
        << "]";
    }

    bool is_valid() const;
  };
}
#endif

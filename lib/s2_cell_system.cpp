#include "quad_key/s2_cell_system.h"

#include <cassert>

namespace quad_keys
{
  namespace detail
  {
    const std::uint32_t face_bits = 3u;
    const std::uint32_t num_faces = 6u;
    const std::uint32_t pos_bits = (quad_key::max_depth(type::s2_cell) << 1)
      + 1;
    const std::uint32_t max_size = 1 << quad_key::max_depth(type::s2_cell);

    u_position point_from_lat_long(const geo_coordinate2d &coords)
    {
      return {0u, 0u};
    }
  }

  void s2_cell_system::get_geo_coordinate_bounds2d(
      geo_coordinate_bounding_box2d &out_bounds,
      const quad_key &self) const
  {
    (void)detail::face_bits;
    (void)detail::num_faces;
  }

  std::string s2_cell_system::to_internal_string(const quad_key &self) const
  {
    return "";
  }

  quad_key s2_cell_system::from_internal_string(
    const std::string &in_string) const
  {
    return quad_key(type::s2_cell);
  }

  quad_key s2_cell_system::get_key_from_longitude_latitude_at_depth(
    const geo_coordinate2d &coords, std::uint8_t depth) const
  {
    // Inclusion here consists of ???
    //    x------x------x
    //    |      |      |
    //    |      |      |
    //    x------x------x
    //    |      |      |
    //    |      |      |
    //    x------x------x
    return quad_key(type::s2_cell);
  }

  std::vector<quad_key>
  s2_cell_system::get_keys_from_longitude_latitude_bounding_box(
    const geo_coordinate_bounding_box2d &bounds, std::uint8_t depth) const
  {
    std::vector<quad_key> out_keys;

    return out_keys;
  }

  std::uint8_t s2_cell_system::max_depth() const
  {
    return 30u;
  }

  std::uint32_t s2_cell_system::max_rows(std::uint8_t depth) const
  {
    if (depth > max_depth()) {
      return 0;
    }
    return 0;
  }

  std::uint32_t s2_cell_system::max_cols(std::uint8_t depth) const
  {
    if (depth > max_depth()) {
      return 0;
    }
    return 0;
  }
}

#include "quad_key/none_system.h"

namespace quad_keys
{
  bool none_system::is_valid(const quad_key &/*key*/) const
  {
    return false;
  }

  bool none_system::is_root_key(const quad_key &/*self*/) const
  {
    return true;
  }

  quad_key none_system::get_parent(const quad_key &/*self*/) const
  {
    return quad_key();
  }

  bool none_system::is_my_ancestor(const quad_key &/*quadKey*/,
    const quad_key &/*self*/) const
  {
    return false;
  }

  quad_key none_system::get_ancestor(std::uint8_t /*depthDelta*/,
    const quad_key &/*self*/) const
  {
    return quad_key();
  }

  quad_key none_system::get_child(quad_key::quadrant /*quadrant*/,
    const quad_key &/*self*/) const
  {
    return quad_key();
  }

  std::vector<quad_key> none_system::get_children(
    const quad_key &/*self*/) const
  {
    return std::vector<quad_key>();
  }

  std::vector<quad_key> none_system::get_descendants(
    std::uint8_t /*depth_delta*/, const quad_key &/*self*/) const
  {
    return std::vector<quad_key>();
  }

  std::vector<quad_key> none_system::get_siblings(
    const quad_key &/*self*/) const
  {
    return std::vector<quad_key>();
  }

  std::vector<quad_key> none_system::get_neighbors(
    const quad_key &/*self*/) const
  {
    return std::vector<quad_key>();
  }

  void none_system::get_geo_coordinate_bounds2d(
    geo_coordinate_bounding_box2d &out_bounds,
    const quad_key &/*self*/) const
  {
    out_bounds = geo_coordinate_bounding_box2d();
  }

  std::string none_system::to_internal_string(const quad_key &/*self*/) const
  {
    return "";
  }

  quad_key none_system::from_internal_string(
    const std::string &/*inString*/) const
  {
    return quad_key();
  }

  quad_key none_system::get_key_from_longitude_latitude_at_depth(
    const geo_coordinate2d &/*coords*/, std::uint8_t /*depth*/) const
  {
    return quad_key();
  }

  std::vector<quad_key>
  none_system::get_keys_from_longitude_latitude_bounding_box(
    const geo_coordinate_bounding_box2d &/*bounds*/,
    std::uint8_t /*depth*/) const
  {
    return std::vector<quad_key>();
  }

  std::uint8_t none_system::max_depth() const
  {
    return 0;
  }

  std::uint32_t none_system::max_rows(std::uint8_t /*depth*/) const
  {
    return 0;
  }

  std::uint32_t none_system::max_cols(std::uint8_t /*depth*/) const
  {
    return 0;
  }
}

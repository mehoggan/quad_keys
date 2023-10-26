#include "quad_keys/none_system.h"

namespace quad_keys
{
  bool NoneSystem::is_valid(const QuadKey &/*key*/) const
  {
    return false;
  }

  bool NoneSystem::is_root_key(const QuadKey &/*self*/) const
  {
    return true;
  }

  QuadKey NoneSystem::get_parent(const QuadKey &/*self*/) const
  {
    return QuadKey();
  }

  bool NoneSystem::is_my_ancestor(const QuadKey &/*quadKey*/,
    const QuadKey &/*self*/) const
  {
    return false;
  }

  QuadKey NoneSystem::get_ancestor(std::uint8_t /*depthDelta*/,
    const QuadKey &/*self*/) const
  {
    return QuadKey();
  }

  QuadKey NoneSystem::get_child(QuadKey::quadrant /*quadrant*/,
    const QuadKey &/*self*/) const
  {
    return QuadKey();
  }

  std::vector<QuadKey> NoneSystem::get_children(
    const QuadKey &/*self*/) const
  {
    return std::vector<QuadKey>();
  }

  std::vector<QuadKey> NoneSystem::get_descendants(
    std::uint8_t /*depth_delta*/, const QuadKey &/*self*/) const
  {
    return std::vector<QuadKey>();
  }

  std::vector<QuadKey> NoneSystem::get_siblings(
    const QuadKey &/*self*/) const
  {
    return std::vector<QuadKey>();
  }

  std::vector<QuadKey> NoneSystem::get_neighbors(
    const QuadKey &/*self*/) const
  {
    return std::vector<QuadKey>();
  }

  void NoneSystem::get_geo_coordinate_bounds2d(
    GeoCoordinateBoundingBox2d &out_bounds,
    const QuadKey &/*self*/) const
  {
    out_bounds = GeoCoordinateBoundingBox2d();
  }

  std::string NoneSystem::to_internal_string(const QuadKey &/*self*/) const
  {
    return "";
  }

  QuadKey NoneSystem::from_internal_string(
    const std::string &/*inString*/) const
  {
    return QuadKey();
  }

  QuadKey NoneSystem::get_key_from_longitude_latitude_at_depth(
    const GeoCoordinate2d &/*coords*/, std::uint8_t /*depth*/) const
  {
    return QuadKey();
  }

  std::vector<QuadKey>
  NoneSystem::get_keys_from_longitude_latitude_bounding_box(
    const GeoCoordinateBoundingBox2d &/*bounds*/,
    std::uint8_t /*depth*/) const
  {
    return std::vector<QuadKey>();
  }

  std::uint8_t NoneSystem::max_depth() const
  {
    return 0;
  }

  std::uint32_t NoneSystem::max_rows(std::uint8_t /*depth*/) const
  {
    return 0;
  }

  std::uint32_t NoneSystem::max_cols(std::uint8_t /*depth*/) const
  {
    return 0;
  }
}

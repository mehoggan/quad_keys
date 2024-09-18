#include "quad_keys/quad_key.h"

#include <exception>

#include "quad_keys/system.h"

namespace quad_keys {
QuadKey::QuadKey()
    : m_type(Type::None),
      m_row(0),
      m_col(0),
      m_depth(0),
      m_impl(&System::get_system_from_enum(Type::None)) {}

QuadKey::QuadKey(Type t)
    : m_type(t),
      m_row(0),
      m_col(0),
      m_depth(0),
      m_impl(&System::get_system_from_enum(t)) {}

QuadKey::QuadKey(Type t, std::uint32_t row, std::uint32_t col,
                 std::uint8_t depth)
    : m_type(t),
      m_row(row),
      m_col(col),
      m_depth(depth),
      m_impl(&System::get_system_from_enum(t)) {
  if (!m_impl->is_valid((*this))) {
    (*this) = QuadKey();
  }
}

QuadKey::QuadKey(const QuadKey &other)
    : m_type(other.m_type),
      m_row(other.m_row),
      m_col(other.m_col),
      m_depth(other.m_depth),
      m_impl(other.m_impl) {}

QuadKey &QuadKey::operator=(const QuadKey &other) {
  m_type = other.m_type;
  m_row = other.m_row;
  m_col = other.m_col;
  m_depth = other.m_depth;
  m_impl = other.m_impl;

  return (*this);
}

std::string QuadKey::type_as_string() const { return type_to_string(m_type); }

bool QuadKey::is_root_key() const { return m_impl->is_root_key((*this)); }

QuadKey QuadKey::get_parent() const { return m_impl->get_parent((*this)); }

bool QuadKey::is_my_ancestor(const QuadKey &quad_key) const {
  return m_impl->is_my_ancestor(quad_key, (*this));
}

QuadKey QuadKey::get_ancestor(std::uint8_t depth_delta) const {
  return m_impl->get_ancestor(depth_delta, (*this));
}

QuadKey QuadKey::get_child(quadrant quad_id) const {
  return m_impl->get_child(quad_id, (*this));
}

std::vector<QuadKey> QuadKey::get_children() const {
  std::vector<QuadKey> out_keys;
  out_keys = m_impl->get_children((*this));
  return out_keys;
}

std::vector<QuadKey> QuadKey::get_descendants(std::uint8_t depth_delta) const {
  std::vector<QuadKey> out_keys;
  out_keys = m_impl->get_descendants(depth_delta, (*this));
  return out_keys;
}

std::vector<QuadKey> QuadKey::get_siblings() const {
  std::vector<QuadKey> out_keys;
  out_keys = m_impl->get_siblings((*this));
  return out_keys;
}

std::vector<QuadKey> QuadKey::get_neighbors() const {
  std::vector<QuadKey> out_keys;
  out_keys = m_impl->get_neighbors((*this));
  return out_keys;
}

void QuadKey::get_geo_coordinate_bounds2d(
    GeoCoordinateBoundingBox2d &out_bounds) const {
  m_impl->get_geo_coordinate_bounds2d(out_bounds, (*this));
}

std::string QuadKey::to_internal_string() const {
  return m_impl->to_internal_string((*this));
}

QuadKey QuadKey::from_internal_string(Type t, const std::string &in_string) {
  return QuadKey(t).m_impl->from_internal_string(in_string);
}

QuadKey QuadKey::get_key_from_longitude_latitude_at_depth(
    Type t, const GeoCoordinate2d &coords, std::uint8_t depth) {
  if (depth > QuadKey::max_depth(t)) {
    return QuadKey();
  }

  QuadKey key = QuadKey(t).m_impl->get_key_from_longitude_latitude_at_depth(
      coords, depth);
  return key;
}

std::vector<QuadKey> QuadKey::get_keys_from_longitude_latitude_bounding_box(
    Type t, const GeoCoordinateBoundingBox2d &bounds, std::uint8_t depth) {
  std::vector<QuadKey> out_keys;

  if (depth > QuadKey::max_depth(t) || !bounds.is_valid()) {
    return out_keys;
  }

  out_keys = QuadKey(t).m_impl->get_keys_from_longitude_latitude_bounding_box(
      bounds, depth);

  return out_keys;
}

std::uint8_t QuadKey::max_depth(Type t) {
  return QuadKey(t).m_impl->max_depth();
}

std::uint32_t QuadKey::max_rows(Type t, std::uint8_t depth) {
  return QuadKey(t).m_impl->max_rows(depth);
}

std::uint32_t QuadKey::max_cols(Type t, std::uint8_t depth) {
  return QuadKey(t).m_impl->max_cols(depth);
}

std::uint64_t QuadKey::max_tiles(Type t, std::uint8_t depth) {
  return max_cols(t, depth) * max_rows(t, depth);
}
}  // namespace quad_keys

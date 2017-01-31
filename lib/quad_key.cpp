#include "quad_key/quad_key.h"
#include "quad_key/system.h"

#include <exception>

namespace quad_keys
{
  quad_key::quad_key() :
    m_type(type::none),
    m_row(0),
    m_col(0),
    m_depth(0),
    m_impl(&system::get_system_from_enum(type::none))
  {}

  quad_key::quad_key(type t) :
    m_type(t),
    m_row(0),
    m_col(0),
    m_depth(0),
    m_impl(&system::get_system_from_enum(t))
  {}

  quad_key::quad_key(type t, std::uint32_t row, std::uint32_t col,
    std::uint8_t depth) :
    m_type(t),
    m_row(row),
    m_col(col),
    m_depth(depth),
    m_impl(&system::get_system_from_enum(t))
  {
    if (!m_impl->is_valid((*this))) {
      (*this) = quad_key();
    }
  }

  quad_key::quad_key(const quad_key &other) :
    m_type(other.m_type),
    m_row(other.m_row),
    m_col(other.m_col),
    m_depth(other.m_depth),
    m_impl(other.m_impl)
  {}

  quad_key &quad_key::operator=(const quad_key &other)
  {
    m_type = other.m_type;
    m_row = other.m_row;
    m_col = other.m_col;
    m_depth = other.m_depth;
    m_impl = other.m_impl;

    return (*this);
  }

  std::string quad_key::type_as_string() const
  {
    return type_to_string(m_type);
  }

  bool quad_key::is_root_key() const
  {
    return m_impl->is_root_key((*this));
  }

  quad_key quad_key::get_parent() const
  {
    return m_impl->get_parent((*this));
  }

  bool quad_key::is_my_ancestor(const quad_key &quad_key) const
  {
    return m_impl->is_my_ancestor(quad_key, (*this));
  }

  quad_key quad_key::get_ancestor(std::uint8_t depth_delta) const
  {
    return m_impl->get_ancestor(depth_delta, (*this));
  }

  quad_key quad_key::get_child(quadrant quad_id) const
  {
    return m_impl->get_child(quad_id, (*this));
  }

  std::vector<quad_key> quad_key::get_children() const
  {
    std::vector<quad_key> out_keys;
    out_keys = m_impl->get_children((*this));
    return out_keys;
  }

  std::vector<quad_key>
  quad_key::get_descendants(std::uint8_t depth_delta) const
  {
    std::vector<quad_key> out_keys;
    out_keys = m_impl->get_descendants(depth_delta, (*this));
    return out_keys;
  }

  std::vector<quad_key> quad_key::get_siblings() const
  {
    std::vector<quad_key> out_keys;
    out_keys = m_impl->get_siblings((*this));
    return out_keys;
  }

  std::vector<quad_key> quad_key::get_neighbors() const
  {
    std::vector<quad_key> out_keys;
    out_keys = m_impl->get_neighbors((*this));
    return out_keys;
  }

  void quad_key::get_geo_coordinate_bounds2d(
      geo_coordinate_bounding_box2d &out_bounds) const
  {
    m_impl->get_geo_coordinate_bounds2d(out_bounds, (*this));
  }

  std::string quad_key::to_internal_string() const
  {
    return m_impl->to_internal_string((*this));
  }

  quad_key quad_key::from_internal_string(type t,
    const std::string &in_string)
  {
    return quad_key(t).m_impl->from_internal_string(in_string);
  }

  quad_key quad_key::get_key_from_longitude_latitude_at_depth(type t,
    const geo_coordinate2d &coords, std::uint8_t depth)
  {
    if (depth > quad_key::max_depth(t)) {
      return quad_key();
    }

    quad_key key =
      quad_key(t).m_impl->get_key_from_longitude_latitude_at_depth(coords,
        depth);
    return key;
  }

  std::vector<quad_key>
  quad_key::get_keys_from_longitude_latitude_bounding_box(
    type t, const geo_coordinate_bounding_box2d &bounds,
    std::uint8_t depth)
  {
    std::vector<quad_key> out_keys;

    if (depth > quad_key::max_depth(t) || !bounds.is_valid()) {
      return out_keys;
    }

    out_keys =
      quad_key(t).m_impl->get_keys_from_longitude_latitude_bounding_box(
        bounds, depth);

    return out_keys;
  }

  std::uint8_t quad_key::max_depth(type t)
  {
    return quad_key(t).m_impl->max_depth();
  }

  std::uint32_t quad_key::max_rows(type t, std::uint8_t depth)
  {
    return quad_key(t).m_impl->max_rows(depth);
  }

  std::uint32_t quad_key::max_cols(type t, std::uint8_t depth)
  {
    return quad_key(t).m_impl->max_cols(depth);
  }

  std::uint64_t quad_key::max_tiles(type t, std::uint8_t depth)
  {
    return max_cols(t, depth) * max_rows(t, depth);
  }
}

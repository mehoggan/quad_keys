#include "quad_key/system.h"

#include "quad_key/bing_system.h"
#include "quad_key/lat_long_system.h"
#include "quad_key/ulp_qnr_system.h"
#include "quad_key/morton_system.h"
#include "quad_key/none_system.h"
#include "quad_key/osgeo_system.h"

namespace quad_keys
{
  static bing_system bing_system;
  static lat_long_system lat_long_system;
  static ulp_qnr_system mos_qnr_system;
  static morton_system nds_system;
  static none_system none_system;
  static osgeo_system osgeo_system;

  system::system()
  {}

  system &system::get_system_from_enum(type t)
  {
    switch (t) {
    case type::bing: return bing_system;
    case type::lat_long: return lat_long_system;
    case type::ulp_qnr: return mos_qnr_system;
    case type::osgeo: return osgeo_system;
    case type::morton: return nds_system;
    case type::none: // Fall through
    default: return none_system;
    }
  }

  bool system::is_valid(const quad_key &key) const
  {
    bool valid = true;

    valid &= (key.get_depth() <= max_depth());
    valid &= (key.get_row() < max_rows(key.get_depth()));
    valid &= (key.get_col() < max_cols(key.get_depth()));

    return valid;
  }

  bool system::is_root_key(const quad_key &self) const
  {
    return (((self.get_row() == 0) && (self.get_col() == 0)) &&
      (self.get_depth() == 0));
  }

  quad_key system::get_parent(const quad_key &self) const
  {
    if (self.is_root_key() || self.get_type() == type::none) {
        return quad_key();
    }

    std::uint32_t row = self.get_row() >> 1u;
    std::uint32_t col = self.get_col() >> 1u;
    std::uint8_t depth = self.get_depth() - 1;

    return quad_key(self.get_type(), row, col, depth);
  }

  bool system::is_my_ancestor(const quad_key &quad_key,
    const class quad_key &self) const
  {
    bool check = false;

    if (quad_key.get_depth() >= self.get_depth() ||
      quad_key.get_type() != self.get_type() ||
      quad_key.get_type() == type::none) {
      check = false;
    } else {
      std::uint8_t delta_depth = self.get_depth() - quad_key.get_depth();
      class quad_key tmp = get_ancestor(delta_depth, self);
      check = (tmp == quad_key);
    }

    return check;
  }

  quad_key system::get_ancestor(std::uint8_t depth_delta,
    const quad_key &self) const
  {
    if (static_cast<std::int8_t>(self.get_depth()) -
      static_cast<std::int8_t>(depth_delta) < 0) {
      return quad_key();
    }

    if (self.get_type() == type::none || depth_delta == 0) {
      return quad_key();
    }

    std::uint32_t shift = depth_delta;
    std::uint32_t row = self.get_row() >> shift;
    std::uint32_t col = self.get_col() >> shift;
    std::uint8_t depth = self.get_depth() - depth_delta;

    return quad_key(self.get_type(), row, col, depth);
  }

  quad_key system::get_child(quad_key::quadrant quad_id,
      const quad_key &self) const
  {
    std::uint8_t depth = self.get_depth() + 1;
    if (depth > quad_key::max_depth(self.get_type())) {
      return quad_key();
    }

    if (self.get_type() == type::none) {
      return quad_key();
    } else {
      std::uint32_t row = (self.get_row() << 1);
      std::uint32_t col = (self.get_col() << 1);

      switch (quad_id) {
      case quad_key::quadrant::north_west: row += 1u; break;
      case quad_key::quadrant::north_east: row += 1u; col += 1u; break;
      case quad_key::quadrant::south_east: col += 1u; break;
      case quad_key::quadrant::south_west: break;
      }

      return quad_key(self.get_type(), row, col, depth);
    }
  }

  std::vector<quad_key> system::get_children(const quad_key &self) const
  {
    std::vector<quad_key> out_keys;

    for (std::uint8_t quad_id = 0; quad_id < 4; ++quad_id) {
      quad_key child = get_child(
        static_cast<quad_key::quadrant>(quad_id), self);
      detail::insert_vector_if_valid_and_unique(out_keys, child);
    }

    return out_keys;
  }

  std::vector<quad_key> system::get_descendants(
    std::uint8_t depth_delta, const quad_key &self) const
  {
    std::vector<quad_key> out_keys;

    if (self.get_type() == type::none || depth_delta == 0) {
      return out_keys;
    }

    const std::uint8_t max = quad_key::max_depth(self.get_type());
    if (static_cast<std::int8_t>(self.get_depth()) +
      static_cast<std::int8_t>(depth_delta) > max) {
      return out_keys;
    }

    std::uint32_t shift = depth_delta;
    std::uint32_t row = self.get_row() << shift;
    std::uint32_t col = self.get_col() << shift;
    std::uint8_t depth = self.get_depth() + depth_delta;

    std::uint32_t rows = quad_key::max_rows(self.get_type(), depth_delta);
    std::uint32_t cols = quad_key::max_cols(self.get_type(), depth_delta);

    for (std::uint32_t r = row; r < rows; ++r) {
      for (std::uint32_t c = col; c < cols; ++c) {
        quad_key descendant(self.get_type(), r, c, depth);
        detail::insert_vector_if_valid_and_unique(out_keys, descendant);
      }
    }

    return out_keys;
  }

  std::vector<quad_key> system::get_siblings(const quad_key &self) const
  {
    std::vector<quad_key> out_keys;

    if (self.is_root_key()) {
      return out_keys;
    } else {
      quad_key parent = self.get_parent();
      std::vector<quad_key> children;
      children = parent.get_children();
      children.erase(std::remove(children.begin(), children.end(), self),
        children.end());
      for (auto key : children) {
        detail::insert_vector_if_valid_and_unique(out_keys, key);
      }
    }

    return out_keys;
  }

  std::vector<quad_key> system::get_neighbors(const quad_key &self) const
  {
    std::vector<quad_key> out_keys;

    if (self.is_root_key()) {
      return out_keys;
    } else {
      quad_key n(self.get_type(), self.get_row() + 1, self.get_col() + 0,
        self.get_depth());
      quad_key ne(self.get_type(), self.get_row() + 1, self.get_col() + 1,
        self.get_depth());
      quad_key e(self.get_type(), self.get_row() + 0, self.get_col() + 1,
        self.get_depth());
      quad_key se(self.get_type(), self.get_row() - 1, self.get_col() + 1,
        self.get_depth());
      quad_key s(self.get_type(), self.get_row() - 1, self.get_col() + 0,
        self.get_depth());
      quad_key sw(self.get_type(), self.get_row() - 1, self.get_col() - 1,
        self.get_depth());
      quad_key w(self.get_type(), self.get_row() + 0, self.get_col() - 1,
          self.get_depth());
      quad_key nw(self.get_type(), self.get_row() + 1, self.get_col() - 1,
          self.get_depth());

      uint32_t max_col_index = quad_key::max_cols(self.get_type(),
        self.get_depth()) - 1;

      // These two conditionals deal with wrap around in the Longitudinal
      // direction.
      if (e.get_type() == type::none) {
        e = quad_key(self.get_type(),self.get_row(), 0, self.get_depth());

        if (n.get_type() == type::none) {
          se = quad_key(self.get_type(),self.get_row() - 1, 0,
            self.get_depth());
        } else {
          ne = quad_key(self.get_type(),self.get_row() + 1, 0,
            self.get_depth());
        }

         if (s.get_type() == type::none) {
           ne = quad_key(self.get_type(),self.get_row() + 1, 0,
             self.get_depth());
         } else {
           se = quad_key(self.get_type(),self.get_row() - 1, 0,
             self.get_depth());
         }
      }

      if (w.get_type() == type::none) {
        w = quad_key(self.get_type(),self.get_row(), max_col_index,
          self.get_depth());

        if (n.get_type() == type::none) {
          sw = quad_key(self.get_type(),self.get_row() - 1, max_col_index,
            self.get_depth());
        } else {
          nw = quad_key(self.get_type(),self.get_row() + 1, max_col_index,
            self.get_depth());
        }

        if (s.get_type() == type::none) {
          nw = quad_key(self.get_type(),self.get_row() + 1, max_col_index,
            self.get_depth());
        } else {
          sw = quad_key(self.get_type(),self.get_row() - 1, max_col_index,
            self.get_depth());
        }
      }

      detail::insert_vector_if_valid_and_unique(out_keys, n);
      detail::insert_vector_if_valid_and_unique(out_keys, ne);
      detail::insert_vector_if_valid_and_unique(out_keys, e);
      detail::insert_vector_if_valid_and_unique(out_keys, se);
      detail::insert_vector_if_valid_and_unique(out_keys, s);
      detail::insert_vector_if_valid_and_unique(out_keys, sw);
      detail::insert_vector_if_valid_and_unique(out_keys, w);
      detail::insert_vector_if_valid_and_unique(out_keys, nw);
    }

    return out_keys;
  }

  void system::get_geo_coordinate_bounds2d(
      geo_coordinate_bounding_box2d &out_bounds,
      const quad_key &/*self*/) const
  {
    out_bounds = geo_coordinate_bounding_box2d();
  }

  std::string system::to_internal_string(const quad_key &/*self*/) const
  {
    return "";
  }

  quad_key system::from_internal_string(
    const std::string &/*in_string*/) const
  {
    return quad_key();
  }

  quad_key system::get_key_from_longitude_latitude_at_depth(
    const geo_coordinate2d &/*coords*/, std::uint8_t /*depth*/) const
  {
    return quad_key();
  }

  std::vector<quad_key>
  system::get_keys_from_longitude_latitude_bounding_box(
    const geo_coordinate_bounding_box2d &/*bounds*/,
    std::uint8_t /*depth*/) const
  {
    return std::vector<quad_key>();
  }

  std::uint8_t system::max_depth() const
  {
    return 0;
  }

  uint32_t system::max_rows(std::uint8_t /*depth*/) const
  {
    return 0;
  }

  uint32_t system::max_cols(std::uint8_t /*depth*/) const
  {
    return 0;
  }
}

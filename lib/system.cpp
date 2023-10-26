#include "quad_keys/system.h"

#include "quad_keys/bing_system.h"
#include "quad_keys/lat_lon_system.h"
#include "quad_keys/ulp_qnr_system.h"
#include "quad_keys/morton_system.h"
#include "quad_keys/none_system.h"
#include "quad_keys/osgeo_system.h"

namespace quad_keys
{
  static BingSystem bing_system;
  static LatLonSystem lat_lon_system;
  static UlpQnrSystem mos_qnr_system;
  static MortonSystem nds_system;
  static NoneSystem none_system;
  static OsGeoSystem osgeo_system;

  System::System()
  {}

  System &System::get_system_from_enum(Type t)
  {
    switch (t) {
    case Type::Bing: return bing_system;
    case Type::LatLon: return lat_lon_system;
    case Type::UlpQnr: return mos_qnr_system;
    case Type::OsGeo: return osgeo_system;
    case Type::Morton: return nds_system;
    case Type::None: // Fall through
    default: return none_system;
    }
  }

  bool System::is_valid(const QuadKey &key) const
  {
    bool valid = true;

    valid &= (key.get_depth() <= max_depth());
    valid &= (key.get_row() < max_rows(key.get_depth()));
    valid &= (key.get_col() < max_cols(key.get_depth()));

    return valid;
  }

  bool System::is_root_key(const QuadKey &self) const
  {
    return (((self.get_row() == 0) && (self.get_col() == 0)) &&
      (self.get_depth() == 0));
  }

  QuadKey System::get_parent(const QuadKey &self) const
  {
    if (self.is_root_key() || self.get_type() == Type::None) {
        return QuadKey();
    }

    std::uint32_t row = self.get_row() >> 1u;
    std::uint32_t col = self.get_col() >> 1u;
    std::uint8_t depth = self.get_depth() - 1;

    return QuadKey(self.get_type(), row, col, depth);
  }

  bool System::is_my_ancestor(const QuadKey &quad_key,
    const class QuadKey &self) const
  {
    bool check = false;

    if (quad_key.get_depth() >= self.get_depth() ||
      quad_key.get_type() != self.get_type() ||
      quad_key.get_type() == Type::None) {
      check = false;
    } else {
      std::uint8_t delta_depth = self.get_depth() - quad_key.get_depth();
      class QuadKey tmp = get_ancestor(delta_depth, self);
      check = (tmp == quad_key);
    }

    return check;
  }

  QuadKey System::get_ancestor(std::uint8_t depth_delta,
    const QuadKey &self) const
  {
    if (static_cast<std::int8_t>(self.get_depth()) -
      static_cast<std::int8_t>(depth_delta) < 0) {
      return QuadKey();
    }

    if (self.get_type() == Type::None || depth_delta == 0) {
      return QuadKey();
    }

    std::uint32_t shift = depth_delta;
    std::uint32_t row = self.get_row() >> shift;
    std::uint32_t col = self.get_col() >> shift;
    std::uint8_t depth = self.get_depth() - depth_delta;

    return QuadKey(self.get_type(), row, col, depth);
  }

  QuadKey System::get_child(QuadKey::quadrant quad_id,
    const QuadKey &self) const
  {
    std::uint8_t depth = self.get_depth() + 1;
    if (depth > QuadKey::max_depth(self.get_type())) {
      return QuadKey();
    }

    if (self.get_type() == Type::None) {
      return QuadKey();
    } else {
      std::uint32_t row = (self.get_row() << 1);
      std::uint32_t col = (self.get_col() << 1);

      switch (quad_id) {
      case QuadKey::quadrant::north_west: row += 1u; break;
      case QuadKey::quadrant::north_east: row += 1u; col += 1u; break;
      case QuadKey::quadrant::south_east: col += 1u; break;
      case QuadKey::quadrant::south_west: break;
      }

      return QuadKey(self.get_type(), row, col, depth);
    }
  }

  std::vector<QuadKey> System::get_children(const QuadKey &self) const
  {
    std::vector<QuadKey> out_keys;

    for (std::uint8_t quad_id = 0; quad_id < 4; ++quad_id) {
      QuadKey child = get_child(
        static_cast<QuadKey::quadrant>(quad_id), self);
      detail::insert_vector_if_valid_and_unique(out_keys, child);
    }

    return out_keys;
  }

  std::vector<QuadKey> System::get_descendants(
    std::uint8_t depth_delta, const QuadKey &self) const
  {
    std::vector<QuadKey> out_keys;

    if (self.get_type() == Type::None || depth_delta == 0) {
      return out_keys;
    }

    const std::uint8_t max = QuadKey::max_depth(self.get_type());
    if (static_cast<std::int8_t>(self.get_depth()) +
      static_cast<std::int8_t>(depth_delta) > max) {
      return out_keys;
    }

    std::uint32_t shift = depth_delta;
    std::uint32_t row = self.get_row() << shift;
    std::uint32_t col = self.get_col() << shift;
    std::uint8_t depth = self.get_depth() + depth_delta;

    std::uint32_t rows = QuadKey::max_rows(self.get_type(), depth_delta);
    std::uint32_t cols = QuadKey::max_cols(self.get_type(), depth_delta);

    for (std::uint32_t r = row; r < rows; ++r) {
      for (std::uint32_t c = col; c < cols; ++c) {
        QuadKey descendant(self.get_type(), r, c, depth);
        detail::insert_vector_if_valid_and_unique(out_keys, descendant);
      }
    }

    return out_keys;
  }

  std::vector<QuadKey> System::get_siblings(const QuadKey &self) const
  {
    std::vector<QuadKey> out_keys;

    if (self.is_root_key()) {
      return out_keys;
    } else {
      QuadKey parent = self.get_parent();
      std::vector<QuadKey> children;
      children = parent.get_children();
      children.erase(std::remove(children.begin(), children.end(), self),
        children.end());
      for (auto key : children) {
        detail::insert_vector_if_valid_and_unique(out_keys, key);
      }
    }

    return out_keys;
  }

  std::vector<QuadKey> System::get_neighbors(const QuadKey &self) const
  {
    std::vector<QuadKey> out_keys;

    if (self.is_root_key()) {
      return out_keys;
    } else {
      QuadKey n(self.get_type(), self.get_row() + 1, self.get_col() + 0,
        self.get_depth());
      QuadKey ne(self.get_type(), self.get_row() + 1, self.get_col() + 1,
        self.get_depth());
      QuadKey e(self.get_type(), self.get_row() + 0, self.get_col() + 1,
        self.get_depth());
      QuadKey se(self.get_type(), self.get_row() - 1, self.get_col() + 1,
        self.get_depth());
      QuadKey s(self.get_type(), self.get_row() - 1, self.get_col() + 0,
        self.get_depth());
      QuadKey sw(self.get_type(), self.get_row() - 1, self.get_col() - 1,
        self.get_depth());
      QuadKey w(self.get_type(), self.get_row() + 0, self.get_col() - 1,
          self.get_depth());
      QuadKey nw(self.get_type(), self.get_row() + 1, self.get_col() - 1,
          self.get_depth());

      uint32_t max_col_index = QuadKey::max_cols(self.get_type(),
        self.get_depth()) - 1;

      // These two conditionals deal with wrap around in the Longitudinal
      // direction.
      if (e.get_type() == Type::None) {
        e = QuadKey(self.get_type(),self.get_row(), 0, self.get_depth());

        if (n.get_type() == Type::None) {
          se = QuadKey(self.get_type(),self.get_row() - 1, 0,
            self.get_depth());
        } else {
          ne = QuadKey(self.get_type(),self.get_row() + 1, 0,
            self.get_depth());
        }

         if (s.get_type() == Type::None) {
           ne = QuadKey(self.get_type(),self.get_row() + 1, 0,
             self.get_depth());
         } else {
           se = QuadKey(self.get_type(),self.get_row() - 1, 0,
             self.get_depth());
         }
      }

      if (w.get_type() == Type::None) {
        w = QuadKey(self.get_type(),self.get_row(), max_col_index,
          self.get_depth());

        if (n.get_type() == Type::None) {
          sw = QuadKey(self.get_type(),self.get_row() - 1, max_col_index,
            self.get_depth());
        } else {
          nw = QuadKey(self.get_type(),self.get_row() + 1, max_col_index,
            self.get_depth());
        }

        if (s.get_type() == Type::None) {
          nw = QuadKey(self.get_type(),self.get_row() + 1, max_col_index,
            self.get_depth());
        } else {
          sw = QuadKey(self.get_type(),self.get_row() - 1, max_col_index,
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

  void System::get_geo_coordinate_bounds2d(
    GeoCoordinateBoundingBox2d &out_bounds,
    const QuadKey &/*self*/) const
  {
    out_bounds = GeoCoordinateBoundingBox2d();
  }

  std::string System::to_internal_string(const QuadKey &/*self*/) const
  {
    return "";
  }

  QuadKey System::from_internal_string(
    const std::string &/*in_string*/) const
  {
    return QuadKey();
  }

  QuadKey System::get_key_from_longitude_latitude_at_depth(
    const GeoCoordinate2d &/*coords*/, std::uint8_t /*depth*/) const
  {
    return QuadKey();
  }

  std::vector<QuadKey>
  System::get_keys_from_longitude_latitude_bounding_box(
    const GeoCoordinateBoundingBox2d &/*bounds*/,
    std::uint8_t /*depth*/) const
  {
    return std::vector<QuadKey>();
  }

  std::uint8_t System::max_depth() const
  {
    return 0;
  }

  uint32_t System::max_rows(std::uint8_t /*depth*/) const
  {
    return 0;
  }

  uint32_t System::max_cols(std::uint8_t /*depth*/) const
  {
    return 0;
  }
}

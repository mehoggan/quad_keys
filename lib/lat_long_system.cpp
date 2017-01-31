#include "quad_key/lat_long_system.h"

namespace quad_keys
{
  static const double total_lon = 360.0;
  static const double total_lat = 180.0;
  static const std::uint32_t ulp_lon = 0xffffffff;
  static const std::uint32_t ulp_lat = 0x7fffffff;

  namespace detail
  { 
    u_tile lat_long_to_ulp(const geo_coordinate2d &coords)
    {
      double longitude = coords.longitude().val();
      std::uint32_t x = (std::uint32_t)(((longitude + 180.0) / total_lon)
        * ulp_lon);
      double latitude = coords.latitude().val();
      std::uint32_t y = (std::uint32_t)(((latitude + 90.0) / total_lat)
        * ulp_lat);
      return u_tile(x, y);
    }

    geo_coordinate2d ulp_to_lat_long(const u_tile &tile)
    {
      longitude longit(((total_lon * tile.x) / (double)(ulp_lon)) - 180.0);
      latitude latit(((total_lat * tile.y) / (double)(ulp_lat)) - 90.0);
      return geo_coordinate2d(longit, latit);
    }

    u_tile quad_key_to_ulp(const quad_key &self)
    {
      std::uint32_t step_x = ulp_lon >> self.get_depth();
      std::uint32_t step_y = ulp_lat >> self.get_depth();

      std::uint32_t ulp_x = self.get_col() * step_x;
      std::uint32_t ulp_y = self.get_row() * step_y;

      return u_tile(ulp_x, ulp_y);
    }

    quad_key ulp_to_quad_key(const u_tile &tile, std::uint8_t depth)
    {
      std::uint32_t step_x = ulp_lon >> depth;
      std::uint32_t step_y = ulp_lat >> depth;

      std::uint32_t col = tile.x / step_x;
      std::uint32_t row = tile.y / step_y;

      // Deal with 180.0 lon and 90.0 lat respectively.
      col = std::max(0u, std::min(col, quad_key::max_cols(type::lat_long,
        depth) - 1));
      row = std::max(0u, std::min(row, quad_key::max_rows(type::lat_long,
        depth) - 1));

      return quad_key(type::lat_long, row, col, depth);
    }
  }

  void lat_long_system::get_geo_coordinate_bounds2d(
    geo_coordinate_bounding_box2d &out_bounds,
    const quad_key &self) const
  {
    std::uint8_t depth = self.get_depth();
    std::uint32_t step_x = ulp_lon >> depth;
    std::uint32_t step_y = ulp_lat >> depth;

    u_tile ulp_ll = detail::quad_key_to_ulp(self);
    geo_coordinate2d ll = detail::ulp_to_lat_long(ulp_ll);
    u_tile ulp_ur(ulp_ll.x + step_x, ulp_ll.y + step_y);
    geo_coordinate2d ur = detail::ulp_to_lat_long(ulp_ur);

    out_bounds = geo_coordinate_bounding_box2d(ll, ur);
  }

  std::string lat_long_system::to_internal_string(const quad_key &self) const
  {
    std::string str;
    if (self.is_root_key()) {
      return str;
    }
    str.resize(self.get_depth());

    quad_key tmp = self;
    std::size_t index = str.length() - 1u;

    const char table[4] = { '2', '3', '0', '1' };

    do {
      quad_key parent = tmp.get_parent();
      for (auto quadrant : {
        quad_key::quadrant::south_west,
        quad_key::quadrant::south_east,
        quad_key::quadrant::north_west,
        quad_key::quadrant::north_east }) {

        if (parent.get_child(quadrant) == tmp) {
          str[index--] = table[static_cast<std::uint8_t>(quadrant)];
          break;
        }
      }
      tmp = parent;
    } while (!tmp.is_root_key());

    return str;
  }

  quad_key lat_long_system::from_internal_string(
    const std::string &in_string) const
  {
    std::uint8_t depth = static_cast<std::uint8_t>(in_string.length());

    if (depth > max_depth()) {
      return quad_key();
    }

    auto valid_chars = {'0', '1', '2', '3'};
    for (auto c : in_string) {
      if (std::find(valid_chars.begin(), valid_chars.end(), c)
        == valid_chars.end()) {
        return quad_key();
      }
    }

    quad_key ret(type::bing);
    for (auto c : in_string) {
      switch (c) {
      case '2': ret = ret.get_child(quad_key::quadrant::south_west); break;
      case '3': ret = ret.get_child(quad_key::quadrant::south_east); break;
      case '0': ret = ret.get_child(quad_key::quadrant::north_west); break;
      case '1': ret = ret.get_child(quad_key::quadrant::north_east); break;
      }
    }
    return ret;
  }

  quad_key lat_long_system::get_key_from_longitude_latitude_at_depth(
    const geo_coordinate2d &coords, std::uint8_t depth) const
  {
    u_tile ulp = detail::lat_long_to_ulp(coords);
    quad_key ret = detail::ulp_to_quad_key(ulp, depth);
    return ret;
  }

  std::vector<quad_key>
  lat_long_system::get_keys_from_longitude_latitude_bounding_box(
    const geo_coordinate_bounding_box2d &bounds,
    std::uint8_t depth) const
  {
    std::vector<quad_key> out_keys;

    u_tile ulp_ll = detail::lat_long_to_ulp(bounds.lower_left());
    quad_key ll = detail::ulp_to_quad_key(ulp_ll, depth);

    // This only works because inclusion is lower left
    u_tile ulp_ur = detail::lat_long_to_ulp(bounds.upper_right());
    quad_key ur = detail::ulp_to_quad_key(ulp_ur, depth);


    for (std::uint32_t r = ll.get_row(); r <= ur.get_row(); ++r) {
      for (std::uint32_t c = ll.get_col(); c <= ur.get_col(); ++c) {
        quad_key key(type::lat_long, r, c, depth);
        detail::insert_vector_if_valid_and_unique(out_keys, key);
      }
    }

    return out_keys;
  }

  std::uint8_t lat_long_system::max_depth() const
  {
    return 23u;
  }

  std::uint32_t lat_long_system::max_rows(std::uint8_t depth) const
  {
    if (depth > max_depth()) {
      return 0;
    }
    return 1 << depth;
  }

  std::uint32_t lat_long_system::max_cols(std::uint8_t depth) const
  {
    if (depth > max_depth()) {
        return 0;
    }
    return 1 << depth;
  }
}

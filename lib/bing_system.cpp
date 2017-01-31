#include "quad_key/bing_system.h"

namespace quad_keys
{
  namespace detail
  {
    const std::uint32_t pixels_per_tile = 256u;

    double mercator_formula_sinusoidal(const latitude &latitude)
    {
      double radians = latitude.val() * pi / 180.0;
      double meters = std::sin(radians);
      return std::log((1.0 + meters) / (1.0 - meters)) / (4.0 * pi);
    }

    latitude inverse_mercator_formula_sinusoidal(double radians)
    {
      double latit =
        90.0 - 360.0 * std::atan(std::exp(-radians * 2.0 * pi)) / pi;
      return latitude(latit);
    }

    u_pixel lat_long_to_pixel(const geo_coordinate2d &coords,
      std::uint8_t depth)
    {
      const double map_size = static_cast<double>(pixels_per_tile << depth);

      double longit = coords.get_longitude().val();
      double latit = mercator_latitude_clamp(coords.get_latitude()).val();
      double x = (longit + 180.0) / 360.0;
      double y = 0.5 - mercator_formula_sinusoidal(latitude(latit));

      const double max = map_size - 1.0;
      const double h = 0.5;
      return u_pixel(
        (std::uint32_t)(std::min(std::max(x * map_size + h, 0.0), max)),
        (std::uint32_t)(std::min(std::max(y * map_size + h, 0.0), max)));
    }

    geo_coordinate2d pixel_to_lat_long(const u_pixel &pixel,
      std::uint8_t depth)
    {
      const double map_size = static_cast<double>(pixels_per_tile << depth);

      double max = map_size - 1.0;
      double px = static_cast<double>(pixel.x);
      double py = static_cast<double>(pixel.y);
      double x = std::min(std::max(px, 0.0), max) / map_size - 0.5;
      double y = 0.5 - std::min(std::max(py, 0.0), max) / map_size;

      longitude lon(360.0 * x);
      latitude lat(inverse_mercator_formula_sinusoidal(y));

      return geo_coordinate2d(lon, lat);
    }

    u_tile pixel_to_tile(const u_pixel &pixel)
    {
      return u_tile(pixel.x / pixels_per_tile, pixel.y / pixels_per_tile);
    }

    u_pixel tile_to_pixel(const u_tile &tile)
    {
      return u_pixel(tile.x * pixels_per_tile, tile.y * pixels_per_tile);
    }

    std::string tile_to_base_4(const u_tile &tile, std::uint8_t depth)
    {
      std::string curr = "";

      for (std::uint8_t d = depth; d > 0; --d) {
        std::uint8_t quad = 0;
        std::uint32_t mask = 1 << (d - 1);

        if ((tile.x & mask) != 0u) {
            ++quad;
        }

        if ((tile.y & mask) != 0u) {
            quad += 2;
        }

        switch (quad) {
        case 0: curr += '0'; break;
        case 1: curr += '1'; break;
        case 2: curr += '2'; break;
        case 3: curr += '3'; break;
        }
      }

      return curr;
    }

    u_tile base_4_to_tile(const std::string &base4)
    {
      u_tile tile;

      std::uint8_t depth = static_cast<std::uint8_t>(base4.length());
      for (std::uint8_t d = depth; d > 0; --d) {
        std::uint32_t mask = 1 << (d - 1);
        std::uint8_t next_depth = depth - d + 1;
        std::string parent = base4.substr(0, next_depth);

        switch (parent[parent.length() - 1]) {
        case '0': break;
        case '1': tile.x |= mask; break;
        case '2': tile.y |= mask; break;
        case '3': tile.x |= mask; tile.y |= mask; break;
        }
      }

      return tile;
    }

    quad_key bing_tile_to_quad_key(const u_tile &tile, std::uint8_t depth)
    {
      std::uint32_t max_index = quad_key::max_rows(type::bing, depth) - 1u;
      std::uint32_t row = max_index - tile.y;
      std::uint32_t col = tile.x;

      return quad_key(type::bing, row, col, depth);
    }

    u_tile quad_key_to_bing_tile(const quad_key &key)
    {
      std::uint32_t max_index = quad_key::max_rows(type::bing,
        key.get_depth()) - 1u;
      std::uint32_t y = max_index - key.get_row();
      std::uint32_t x = key.get_col();

      return u_tile(x, y);
    }
  }

  void bing_system::get_geo_coordinate_bounds2d(
      geo_coordinate_bounding_box2d &out_bounds,
      const quad_key &self) const
  {
    std::uint8_t depth = self.get_depth();

    u_tile tm = detail::quad_key_to_bing_tile(self);
    u_pixel top_left_pixel = detail::tile_to_pixel(tm);
    geo_coordinate2d tl_coords = detail::pixel_to_lat_long(top_left_pixel,
      depth);

    u_tile tmbr(tm.x + 1, tm.y + 1);
    u_pixel bottom_right_pixel = detail::tile_to_pixel(tmbr);
    geo_coordinate2d br_coords = detail::pixel_to_lat_long(
      bottom_right_pixel, depth);

    out_bounds = geo_coordinate_bounding_box2d(
      geo_coordinate2d(tl_coords.get_longitude(), br_coords.get_latitude()),
      geo_coordinate2d(br_coords.get_longitude(), tl_coords.get_latitude()));
  }

  std::string bing_system::to_internal_string(const quad_key &self) const
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

  quad_key bing_system::from_internal_string(
    const std::string &in_string) const
  {
    std::uint8_t depth = static_cast<std::uint8_t>(in_string.length());

    if (depth > max_depth()) {
      return quad_key();
    }

    auto valid_chars = {'0', '1', '2', '3'};
    for (auto c : in_string) {
      if (std::find(valid_chars.begin(), valid_chars.end(), c) ==
        valid_chars.end()) {
        return quad_key();
      }
    }

    quad_key ret(type::bing);
    for (auto c : in_string) {
      switch (c) {
      case '2': {
        ret = ret.get_child(quad_key::quadrant::south_west);
      }
        break;
      case '3': {
        ret = ret.get_child(quad_key::quadrant::south_east);
      }
        break;
      case '0': {
        ret = ret.get_child(quad_key::quadrant::north_west);
      }
        break;
      case '1': {
        ret = ret.get_child(quad_key::quadrant::north_east);
      }
        break;
      }
    }
    return ret;
  }

  quad_key bing_system::get_key_from_longitude_latitude_at_depth(
    const geo_coordinate2d &coords, std::uint8_t depth) const
  {
    // Inclusion here consists of upper left
    // ul x------x------x
    //    |      |      |
    //    |      |      |
    //    x------x------x
    //    |      |      |
    //    |      |      |
    //    x------x------x
    u_pixel ll_pixel = detail::lat_long_to_pixel(coords, depth);
    u_tile tile = detail::pixel_to_tile(ll_pixel);

    return detail::bing_tile_to_quad_key(tile, depth);
  }

  std::vector<quad_key>
  bing_system::get_keys_from_longitude_latitude_bounding_box(
    const geo_coordinate_bounding_box2d &bounds, std::uint8_t depth) const
  {
    std::vector<quad_key> out_keys;

    geo_coordinate2d top_left(bounds.lower_left().get_longitude(),
      bounds.upper_right().get_latitude());
    geo_coordinate2d bottom_right(bounds.upper_right().get_longitude(),
      bounds.lower_left().get_latitude());

    u_pixel ul_pixel = detail::lat_long_to_pixel(top_left, depth);
    u_tile ul_tile = detail::pixel_to_tile(ul_pixel);

    u_pixel lr_pixel = detail::lat_long_to_pixel(bottom_right, depth);
    u_tile lr_tile = detail::pixel_to_tile(lr_pixel);

    for (std::uint32_t x = ul_tile.x; x <= lr_tile.x; ++x) {
      for (std::uint32_t y = ul_tile.y; y <= lr_tile.y; ++y) {
        quad_key key = detail::bing_tile_to_quad_key(u_tile(x, y), depth);
        detail::insert_vector_if_valid_and_unique(out_keys, key);
      }
    }

    return out_keys;
  }

  std::uint8_t bing_system::max_depth() const
  {
    return 23u;
  }

  std::uint32_t bing_system::max_rows(std::uint8_t depth) const
  {
    if (depth > max_depth()) {
      return 0;
    }
    return 1 << depth;
  }

  std::uint32_t bing_system::max_cols(std::uint8_t depth) const
  {
    if (depth > max_depth()) {
      return 0;
    }
    return 1 << depth;
  }
}

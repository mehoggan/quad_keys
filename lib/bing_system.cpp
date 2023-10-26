#include "quad_keys/bing_system.h"

namespace quad_keys
{
  namespace detail
  {
    const std::uint32_t pixels_per_tile = 256u;

    double mercator_formula_sinusoidal(const Latitude &latitude)
    {
      double radians = latitude.val() * pi / 180.0;
      double meters = std::sin(radians);
      return std::log((1.0 + meters) / (1.0 - meters)) / (4.0 * pi);
    }

    Latitude inverse_mercator_formula_sinusoidal(double radians)
    {
      double latit =
        90.0 - 360.0 * std::atan(std::exp(-radians * 2.0 * pi)) / pi;
      return Latitude(latit);
    }

    UPixel lat_long_to_pixel(const GeoCoordinate2d &coords, std::uint8_t depth)
    {
      const double map_size = static_cast<double>(pixels_per_tile << depth);

      double longit = coords.get_longitude().val();
      double latit = mercator_latitude_clamp(coords.get_latitude()).val();
      double x = (longit + 180.0) / 360.0;
      double y = 0.5 - mercator_formula_sinusoidal(Latitude(latit));

      const double max = map_size - 1.0;
      const double h = 0.5;
      return UPixel(
        (std::uint32_t)(std::min(std::max(x * map_size + h, 0.0), max)),
        (std::uint32_t)(std::min(std::max(y * map_size + h, 0.0), max)));
    }

    GeoCoordinate2d pixel_to_lat_long(const UPixel &pixel, std::uint8_t depth)
    {
      const double map_size = static_cast<double>(pixels_per_tile << depth);

      double max = map_size - 1.0;
      double px = static_cast<double>(pixel.x);
      double py = static_cast<double>(pixel.y);
      double x = std::min(std::max(px, 0.0), max) / map_size - 0.5;
      double y = 0.5 - std::min(std::max(py, 0.0), max) / map_size;

      Longitude lon(360.0 * x);
      Latitude lat(inverse_mercator_formula_sinusoidal(y));

      return GeoCoordinate2d(lon, lat);
    }

    UTile pixel_to_tile(const UPixel &pixel)
    {
      return UTile(pixel.x / pixels_per_tile, pixel.y / pixels_per_tile);
    }

    UPixel tile_to_pixel(const UTile &tile)
    {
      return UPixel(tile.x * pixels_per_tile, tile.y * pixels_per_tile);
    }

    std::string tile_to_base_4(const UTile &tile, std::uint8_t depth)
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

    UTile base_4_to_tile(const std::string &base4)
    {
      UTile tile;

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

    QuadKey bing_tile_to_QuadKey(const UTile &tile, std::uint8_t depth)
    {
      std::uint32_t max_index = QuadKey::max_rows(Type::Bing, depth) - 1u;
      std::uint32_t row = max_index - tile.y;
      std::uint32_t col = tile.x;

      return QuadKey(Type::Bing, row, col, depth);
    }

    UTile QuadKey_to_bing_tile(const QuadKey &key)
    {
      std::uint32_t max_index = QuadKey::max_rows(Type::Bing,
        key.get_depth()) - 1u;
      std::uint32_t y = max_index - key.get_row();
      std::uint32_t x = key.get_col();

      return UTile(x, y);
    }
  }

  void BingSystem::get_geo_coordinate_bounds2d(
      GeoCoordinateBoundingBox2d &out_bounds,
      const QuadKey &self) const
  {
    std::uint8_t depth = self.get_depth();

    UTile tm = detail::QuadKey_to_bing_tile(self);
    UPixel top_left_pixel = detail::tile_to_pixel(tm);
    GeoCoordinate2d tl_coords = detail::pixel_to_lat_long(top_left_pixel,
      depth);

    UTile tmbr(tm.x + 1, tm.y + 1);
    UPixel bottom_right_pixel = detail::tile_to_pixel(tmbr);
    GeoCoordinate2d br_coords = detail::pixel_to_lat_long(
      bottom_right_pixel, depth);

    out_bounds = GeoCoordinateBoundingBox2d(
      GeoCoordinate2d(tl_coords.get_longitude(), br_coords.get_latitude()),
      GeoCoordinate2d(br_coords.get_longitude(), tl_coords.get_latitude()));
  }

  std::string BingSystem::to_internal_string(const QuadKey &self) const
  {
    std::string str;
    if (self.is_root_key()) {
      return str;
    }
    str.resize(self.get_depth());

    QuadKey tmp = self;
    std::size_t index = str.length() - 1u;

    const char table[4] = { '2', '3', '0', '1' };

    do {
      QuadKey parent = tmp.get_parent();
      for (auto quadrant : {
        QuadKey::quadrant::south_west,
        QuadKey::quadrant::south_east,
        QuadKey::quadrant::north_west,
        QuadKey::quadrant::north_east }) {

        if (parent.get_child(quadrant) == tmp) {
          str[index--] = table[static_cast<std::uint8_t>(quadrant)];
          break;
        }
      }
      tmp = parent;
    } while (!tmp.is_root_key());

    return str;
  }

  QuadKey BingSystem::from_internal_string(
    const std::string &in_string) const
  {
    std::uint8_t depth = static_cast<std::uint8_t>(in_string.length());

    if (depth > max_depth()) {
      return QuadKey();
    }

    auto valid_chars = {'0', '1', '2', '3'};
    for (auto c : in_string) {
      if (std::find(valid_chars.begin(), valid_chars.end(), c) ==
        valid_chars.end()) {
        return QuadKey();
      }
    }

    QuadKey ret(Type::Bing);
    for (auto c : in_string) {
      switch (c) {
      case '2': {
        ret = ret.get_child(QuadKey::quadrant::south_west);
      }
        break;
      case '3': {
        ret = ret.get_child(QuadKey::quadrant::south_east);
      }
        break;
      case '0': {
        ret = ret.get_child(QuadKey::quadrant::north_west);
      }
        break;
      case '1': {
        ret = ret.get_child(QuadKey::quadrant::north_east);
      }
        break;
      }
    }
    return ret;
  }

  QuadKey BingSystem::get_key_from_longitude_latitude_at_depth(
    const GeoCoordinate2d &coords, std::uint8_t depth) const
  {
    // Inclusion here consists of upper left
    // ul x------x------x
    //    |      |      |
    //    |      |      |
    //    x------x------x
    //    |      |      |
    //    |      |      |
    //    x------x------x
    UPixel ll_pixel = detail::lat_long_to_pixel(coords, depth);
    UTile tile = detail::pixel_to_tile(ll_pixel);

    return detail::bing_tile_to_QuadKey(tile, depth);
  }

  std::vector<QuadKey>
  BingSystem::get_keys_from_longitude_latitude_bounding_box(
    const GeoCoordinateBoundingBox2d &bounds, std::uint8_t depth) const
  {
    std::vector<QuadKey> out_keys;

    GeoCoordinate2d top_left(bounds.lower_left().get_longitude(),
      bounds.upper_right().get_latitude());
    GeoCoordinate2d bottom_right(bounds.upper_right().get_longitude(),
      bounds.lower_left().get_latitude());

    UPixel ul_pixel = detail::lat_long_to_pixel(top_left, depth);
    UTile ul_tile = detail::pixel_to_tile(ul_pixel);

    UPixel lr_pixel = detail::lat_long_to_pixel(bottom_right, depth);
    UTile lr_tile = detail::pixel_to_tile(lr_pixel);

    for (std::uint32_t x = ul_tile.x; x <= lr_tile.x; ++x) {
      for (std::uint32_t y = ul_tile.y; y <= lr_tile.y; ++y) {
        QuadKey key = detail::bing_tile_to_QuadKey(UTile(x, y), depth);
        detail::insert_vector_if_valid_and_unique(out_keys, key);
      }
    }

    return out_keys;
  }

  std::uint8_t BingSystem::max_depth() const
  {
    return 23u;
  }

  std::uint32_t BingSystem::max_rows(std::uint8_t depth) const
  {
    if (depth > max_depth()) {
      return 0;
    }
    return 1 << depth;
  }

  std::uint32_t BingSystem::max_cols(std::uint8_t depth) const
  {
    if (depth > max_depth()) {
      return 0;
    }
    return 1 << depth;
  }
}

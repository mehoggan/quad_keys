#include "quad_key/morton_system.h"

#include "quad_key/macros.h"

#include <cassert>

namespace quad_keys
{
  namespace detail
  {
    const double longitude_range =
      longitude::max_longitude - longitude::min_longitude;
    const double latitude_range =
      latitude::max_latitude - latitude::min_latitude;
    const std::uint32_t x_domain = 0xffffffff;
    const std::uint32_t y_domain = 0x7fffffff;

    std::int64_t position_to_morton_code(const position &pos)
    {
      std::int64_t morton_code = 0;

      std::uint64_t x = spread_by_1_bit(pos.x);
      std::uint64_t y = spread_by_1_bit(pos.y);

      morton_code |= x;
      morton_code |= (y << 1);

      return morton_code & (~0x8000000000000000ull);
    }

    position morton_code_to_position(std::int64_t morton_code)
    {
      int64_t x = compact_by_1_bit(morton_code);
      int64_t y = compact_by_1_bit(morton_code >> 1);

      return position((std::int32_t)x, (std::int32_t)y);
    }

    geo_coordinate2d position_to_lat_long(const position &pos)
    {
      std::int64_t morton_code = position_to_morton_code(pos);

      std::int32_t y = pos.y;
      // 0x(NotUsed)(East/West)(North/South)0 0000 0000 0000
      bool below_equator =
        ((morton_code & 0x2000000000000000) != 0x0000000000000000);
      if (below_equator) {
        y |= 0x80000000;
      }

      static double long_span = std::abs(longitude_range);
      double lon = (pos.x / static_cast<double>(x_domain)) * (long_span);

      static double lat_span = std::abs(latitude_range);
      double lat = (y / static_cast<double>(y_domain)) * (lat_span);

      return geo_coordinate2d(longitude(lon), latitude(lat));
    }

    position lat_long_to_morton_position(const geo_coordinate2d &coords)
    {
      std::int32_t x = 0;
      std::int32_t y = 0;

      double percent_x = coords.get_longitude().val() / (longitude_range);
      double percent_y = coords.get_latitude().val() / (latitude_range);

      double lon = std::floor(percent_x * (double)x_domain);
      double lat = std::floor(percent_y * (double)y_domain);

      x = static_cast<std::int32_t>(lon);
      y = static_cast<std::int32_t>(lat);
      y &= (~0x80000000);

      return position(x, y);
    }

    std::uint32_t morton_code_to_tile_id(std::int64_t morton,
      std::uint8_t depth)
    {
      morton &= (~0x8000000000000000ull);
      std::uint32_t morton_msb = (std::uint32_t)(
          morton >> (62ull - 2 * depth));
      std::uint32_t tile_depth = 1 << (depth + 16u);
      std::uint32_t tile_id = tile_depth | morton_msb;
      return tile_id;
    }

    std::uint8_t depth_from_morton_tile_id(std::uint32_t tile_id)
    {
      std::uint32_t local_tile_id = tile_id;
      std::uint8_t depth = msb32(local_tile_id);
      depth -= 16u;
      return depth;
    }

    std::int64_t tile_id_to_morton_code(std::uint32_t tile_id)
    {
      std::uint32_t local_tile_id = tile_id;
      std::uint8_t depth = depth_from_morton_tile_id(tile_id);
      local_tile_id ^= 1 << (depth + 16u);
      std::int64_t morton_at_depth = ((std::int64_t)local_tile_id) <<
        (62ull - 2 * depth);

      return morton_at_depth;
    }

    // As a note for the two functions below. If c' and r' are in  space,
    // and both tc and tr (total columns and rows) are functions of the
    // current depth.
    //
    // Then:
    // c' = (c + (tc / 2) % tc
    // r' = (r + (tr / 2) % tr
    //
    // We can perform the inverse using the following assumption. Knowing
    // the definition of "%" to be x % y  = z iff E some "n":
    //
    // x = n * y + z. In our case we assume n == 1.
    // Solving for both c and r respectively we get:
    //
    // (c + (tc / 2)) = n * tc + c' ==> c = (tc / 2) + c'
    // (r + (tr / 2)) = n * tr + r' ==> r = (tr / 2) + r'
    //
    // In the conversion back to c' and r' we % again to keep numbers
    // within range of tc and tr.
    position quad_key_to_morton_position(const quad_key &key)
    {
      std::uint8_t depth = key.get_depth();

      std::uint32_t col = key.get_col();
      std::uint32_t total_cols = quad_key::max_cols(type::morton, depth);
      std::uint32_t half_cols = total_cols >> 1;
      std::uint32_t col_prime = (col + half_cols) % total_cols;

      std::uint32_t row = key.get_row();
      std::uint32_t total_rows = quad_key::max_rows(type::morton, depth);
      std::uint32_t half_rows = total_rows >> 1;
      std::uint32_t row_prime = (row + half_rows) % total_rows;

      std::uint64_t x = spread_by_1_bit(col_prime);
      std::uint64_t y = spread_by_1_bit(row_prime);

      std::int64_t interleave = 0;
      interleave |= x;
      interleave |= (y << 1);

      std::uint32_t tile = (1 << (depth + 16u)) |
          static_cast<std::uint32_t>(interleave);
      std::int64_t morton = tile_id_to_morton_code(tile);
      position pos = morton_code_to_position(morton);
      return pos;
    }

    quad_key tile_id_to_quad_key(std::uint32_t tile, std::uint8_t depth)
    {
      tile = tile ^ (1 << (depth + 16u));

      int64_t col_prime = compact_by_1_bit(static_cast<int64_t>(tile));
      std::uint32_t total_cols = quad_key::max_cols(type::morton, depth);
      std::uint32_t half_cols = total_cols >> 1;

      int64_t row_prime = compact_by_1_bit(static_cast<int64_t>(tile >> 1));
      std::uint32_t total_rows = quad_key::max_rows(type::morton, depth);
      std::uint32_t half_rows = total_rows >> 1;

      std::uint32_t col = (half_cols + col_prime) % total_cols;
      std::uint32_t row = (half_rows + row_prime) % total_rows;

      return quad_key(type::morton, row, col, depth);
    }

    quad_key position_to_quad_key(const position &pos, std::uint8_t depth)
    {
      std::int64_t morton = position_to_morton_code(pos);
      std::uint32_t tile = morton_code_to_tile_id(morton, depth);
      return tile_id_to_quad_key(tile, depth);
    }

    std::string tile_to_string(std::uint32_t tile)
    {
      //2,147,483,647'\0'
      const std::uint8_t buff_size = 11u;
      char buff[buff_size];
      snprintf(buff, buff_size, "%d", tile);
      return std::string(buff);
    }

    std::uint32_t string_to_morton_tile(const std::string &morton_str,
      bool *success)
    {
      char* endptr;
      std::uint32_t tile = std::strtol(morton_str.c_str(), &endptr, 0);
      if (*endptr == '\0' && tile != 0) {
        if (success) {
          *success = true;
        }
        return tile;
      }

      if (success) {
        *success = false;
      }

      return 0;
    }
  }

  void morton_system::get_geo_coordinate_bounds2d(
    geo_coordinate_bounding_box2d &out_bounds,
    const quad_key &self) const
  {
    std::uint8_t depth = self.get_depth();
    if (depth == 0) {
      if (self.get_col() == 0) {
        out_bounds = geo_coordinate_bounding_box2d(
          geo_coordinate2d(longitude(-180.0), latitude(- 90.0)),
          geo_coordinate2d(longitude(-  0.1), latitude(+ 90.0)));
      } else {
        out_bounds = geo_coordinate_bounding_box2d(
          geo_coordinate2d(longitude(+  0.0), latitude(- 90.0)),
          geo_coordinate2d(longitude(+180.0), latitude(+ 90.0)));
      }
    } else {
      position pos_ll = detail::quad_key_to_morton_position(self);
      geo_coordinate2d ll = detail::position_to_lat_long(pos_ll);

      std::int32_t delta_x = detail::x_domain >> (depth + 1);
      std::int32_t delta_y = detail::y_domain >> depth;

      position pos_ur(pos_ll.x + delta_x, pos_ll.y + delta_y);
      geo_coordinate2d ur = detail::position_to_lat_long(pos_ur);

      out_bounds = geo_coordinate_bounding_box2d(ll, ur);
    }
  }

  std::string morton_system::to_internal_string(const quad_key &self) const
  {
    // Z-Order for depths 0 and 1 are reflected over Y-Axis
    std::uint8_t depth = self.get_depth();
    if (depth == 0) {
      std::size_t index = self.get_col();
      std::uint32_t tile = static_cast<std::uint32_t>(-1);
      switch (index) {
      case 0: tile = 65537u; break;
      case 1: tile = 65536u; break;
      default: assert(false && "This is impossible!!!");
      }
      std::string ret = detail::tile_to_string(tile);
      return ret;
    } else if (depth == 1) {
      std::size_t index = (self.get_row() * 4) + (self.get_col() % 4);
      std::uint32_t tile = static_cast<std::uint32_t>(-1);
      switch (index) {
      case 0: tile = 131078u; break;
      case 1: tile = 131079u; break;
      case 2: tile = 131074u; break;
      case 3: tile = 131075u; break;
      case 4: tile = 131076u; break;
      case 5: tile = 131077u; break;
      case 6: tile = 131072u; break;
      case 7: tile = 131073u; break;
      default: assert(false && "This is impossible!!!");
      }
      std::string ret = detail::tile_to_string(tile);
      return ret;
    } else {
      position pos = detail::quad_key_to_morton_position(self);
      std::int64_t morton = detail::position_to_morton_code(pos);
      std::uint32_t tile = detail::morton_code_to_tile_id(morton, depth);
      std::string ret = detail::tile_to_string(tile);
      return ret;
    }
  }

  quad_key morton_system::from_internal_string(
    const std::string &in_string) const
  {
    bool success = false;
    std::uint32_t tile = detail::string_to_morton_tile(in_string, &success);
    if (!success) {
      return quad_key();
    }

    // Z-Order for depths 0 and 1 are reflected over Y-Axis
    std::uint8_t depth = detail::depth_from_morton_tile_id(tile);
    if (depth == 0) {
      return (tile == 65537) ? quad_key(type::morton, 0, 0, depth) :
        quad_key(type::morton, 0, 1, depth);
    } else if (depth == 1) {
        int32_t index = 131079 - tile;
        switch (index) {
        case 0: return quad_key(type::morton, 0, 1, 1);
        case 1: return quad_key(type::morton, 0, 0, 1);
        case 2: return quad_key(type::morton, 1, 1, 1);
        case 3: return quad_key(type::morton, 1, 0, 1);
        case 4: return quad_key(type::morton, 0, 3, 1);
        case 5: return quad_key(type::morton, 0, 2, 1);
        case 6: return quad_key(type::morton, 1, 3, 1);
        case 7: return quad_key(type::morton, 1, 2, 1);
        default: assert(index > 0 && "This is immpossible!!!");
        }
    } else {
      quad_key ret = detail::tile_id_to_quad_key(tile, depth);
      return ret;
    }

    return quad_key();
  }

  quad_key morton_system::get_key_from_longitude_latitude_at_depth(
    const geo_coordinate2d &coords, std::uint8_t depth) const
  {
    position pos = detail::lat_long_to_morton_position(coords);
    quad_key ret = detail::position_to_quad_key(pos, depth);
    return ret;
  }

  std::vector<quad_key>
  morton_system::get_keys_from_longitude_latitude_bounding_box(
    const geo_coordinate_bounding_box2d &bou,
    std::uint8_t depth) const
  {
    std::vector<quad_key> quad_keys;
    position ll = detail::lat_long_to_morton_position(bou.lower_left());
    position ur = detail::lat_long_to_morton_position(bou.upper_right());

    quad_key ll_qk = detail::position_to_quad_key(ll, depth);
    quad_key ur_qk = detail::position_to_quad_key(ur, depth);

    for (auto col = ll_qk.get_col(); col <= ur_qk.get_col(); ++col) {
      for (auto row = ll_qk.get_row(); row <= ur_qk.get_row(); ++row) {
        quad_key qk(type::morton, row, col, depth);
        detail::insert_vector_if_valid_and_unique(quad_keys, qk);
      }
    }

    return quad_keys;
  }

  std::uint8_t morton_system::max_depth() const
  {
    return 15u;
  }

  std::uint32_t morton_system::max_rows(std::uint8_t depth) const
  {
    if (depth > max_depth()) {
      return 0;
    }
    if (depth == 0) {
      return 1;
    }
    return 1 << depth;
  }

  std::uint32_t morton_system::max_cols(std::uint8_t depth) const
  {
    if (depth > max_depth()) {
      return 0;
    }
    return 1 << (depth + 1);
  }
}

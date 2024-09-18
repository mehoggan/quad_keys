#include "quad_keys/lat_lon_system.h"

namespace quad_keys {
static const double total_lon = 360.0;
static const double total_lat = 180.0;
static const std::uint32_t ulp_lon = 0xffffffff;
static const std::uint32_t ulp_lat = 0x7fffffff;

namespace detail {
UTile lat_long_to_ulp(const GeoCoordinate2d &coords) {
  double longitude = coords.get_longitude().val();
  std::uint32_t x =
      (std::uint32_t)(((longitude + 180.0) / total_lon) * ulp_lon);
  double latitude = coords.get_latitude().val();
  std::uint32_t y = (std::uint32_t)(((latitude + 90.0) / total_lat) * ulp_lat);
  return UTile(x, y);
}

GeoCoordinate2d ulp_to_lat_long(const UTile &tile) {
  Longitude longit(((total_lon * tile.x) / (double)(ulp_lon)) - 180.0);
  Latitude latit(((total_lat * tile.y) / (double)(ulp_lat)) - 90.0);
  return GeoCoordinate2d(longit, latit);
}

UTile QuadKey_to_ulp(const QuadKey &self) {
  std::uint32_t step_x = ulp_lon >> self.get_depth();
  std::uint32_t step_y = ulp_lat >> self.get_depth();

  std::uint32_t ulp_x = self.get_col() * step_x;
  std::uint32_t ulp_y = self.get_row() * step_y;

  return UTile(ulp_x, ulp_y);
}

QuadKey ulp_to_QuadKey(const UTile &tile, std::uint8_t depth) {
  std::uint32_t step_x = ulp_lon >> depth;
  std::uint32_t step_y = ulp_lat >> depth;

  std::uint32_t col = tile.x / step_x;
  std::uint32_t row = tile.y / step_y;

  // Deal with 180.0 lon and 90.0 lat respectively.
  col = std::min(col, QuadKey::max_cols(Type::LatLon, depth) - 1);
  row = std::min(row, QuadKey::max_rows(Type::LatLon, depth) - 1);

  return QuadKey(Type::LatLon, row, col, depth);
}
}  // namespace detail

void LatLonSystem::get_geo_coordinate_bounds2d(
    GeoCoordinateBoundingBox2d &out_bounds, const QuadKey &self) const {
  std::uint8_t depth = self.get_depth();
  std::uint32_t step_x = ulp_lon >> depth;
  std::uint32_t step_y = ulp_lat >> depth;

  UTile ulp_ll = detail::QuadKey_to_ulp(self);
  GeoCoordinate2d ll = detail::ulp_to_lat_long(ulp_ll);
  UTile ulp_ur(ulp_ll.x + step_x, ulp_ll.y + step_y);
  GeoCoordinate2d ur = detail::ulp_to_lat_long(ulp_ur);

  out_bounds = GeoCoordinateBoundingBox2d(ll, ur);
}

std::string LatLonSystem::to_internal_string(const QuadKey &self) const {
  std::string str;
  if (self.is_root_key()) {
    return str;
  }
  str.resize(self.get_depth());

  QuadKey tmp = self;
  std::size_t index = str.length() - 1u;

  const char table[4] = {'2', '3', '0', '1'};

  do {
    QuadKey parent = tmp.get_parent();
    for (auto quadrant :
         {QuadKey::quadrant::south_west, QuadKey::quadrant::south_east,
          QuadKey::quadrant::north_west, QuadKey::quadrant::north_east}) {
      if (parent.get_child(quadrant) == tmp) {
        str[index--] = table[static_cast<std::uint8_t>(quadrant)];
        break;
      }
    }
    tmp = parent;
  } while (!tmp.is_root_key());

  return str;
}

QuadKey LatLonSystem::from_internal_string(const std::string &in_string) const {
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

  QuadKey ret(Type::LatLon);
  for (auto c : in_string) {
    switch (c) {
      case '2':
        ret = ret.get_child(QuadKey::quadrant::south_west);
        break;
      case '3':
        ret = ret.get_child(QuadKey::quadrant::south_east);
        break;
      case '0':
        ret = ret.get_child(QuadKey::quadrant::north_west);
        break;
      case '1':
        ret = ret.get_child(QuadKey::quadrant::north_east);
        break;
    }
  }
  return ret;
}

QuadKey LatLonSystem::get_key_from_longitude_latitude_at_depth(
    const GeoCoordinate2d &coords, std::uint8_t depth) const {
  UTile ulp = detail::lat_long_to_ulp(coords);
  QuadKey ret = detail::ulp_to_QuadKey(ulp, depth);
  return ret;
}

std::vector<QuadKey>
LatLonSystem::get_keys_from_longitude_latitude_bounding_box(
    const GeoCoordinateBoundingBox2d &bounds, std::uint8_t depth) const {
  std::vector<QuadKey> out_keys;

  UTile ulp_ll = detail::lat_long_to_ulp(bounds.lower_left());
  QuadKey ll = detail::ulp_to_QuadKey(ulp_ll, depth);

  // This only works because inclusion is lower left
  UTile ulp_ur = detail::lat_long_to_ulp(bounds.upper_right());
  QuadKey ur = detail::ulp_to_QuadKey(ulp_ur, depth);

  for (std::uint32_t r = ll.get_row(); r <= ur.get_row(); ++r) {
    for (std::uint32_t c = ll.get_col(); c <= ur.get_col(); ++c) {
      QuadKey key(Type::LatLon, r, c, depth);
      detail::insert_vector_if_valid_and_unique(out_keys, key);
    }
  }

  return out_keys;
}

std::uint8_t LatLonSystem::max_depth() const { return 23u; }

std::uint32_t LatLonSystem::max_rows(std::uint8_t depth) const {
  if (depth > max_depth()) {
    return 0;
  }
  return 1 << depth;
}

std::uint32_t LatLonSystem::max_cols(std::uint8_t depth) const {
  if (depth > max_depth()) {
    return 0;
  }
  return 1 << depth;
}
}  // namespace quad_keys

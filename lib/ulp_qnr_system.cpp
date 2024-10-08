#include "quad_keys/ulp_qnr_system.h"

namespace quad_keys {
namespace detail {
UPosition geopt32_from_lat_lon(const GeoCoordinate2d &coords) {
  double lon = coords.get_longitude().val();
  lon += 180.0;
  while (lon < 0.0) {
    lon += 360.0;
  }
  while (lon > 360.0) {
    lon -= 360.0;
  }
  lon /= 360.0;

  double lat = coords.get_latitude().val();
  lat += 90.0;
  while (lat < 0.0) {
    lat += 360.0;
  }
  while (lat > 360.0) {
    lat -= 360.0;
  }
  lat /= 360.0;

  return UPosition(static_cast<std::uint32_t>(lon * 0xffffffff),
                   static_cast<std::uint32_t>(lat * 0xffffffff));
}

GeoCoordinate2d lat_lon_from_geopt32(const UPosition &geopt) {
  double lon = static_cast<double>(geopt.x) / 0xffffffff * 360.0;
  double lat = static_cast<double>(geopt.y) / 0xffffffff * 360.0;

  lon -= 180.0;
  lat -= 90.0;

  return GeoCoordinate2d(Longitude(lon), Latitude(lat));
}

std::uint64_t qnr_from_geopt32(const UPosition &geopt, std::uint8_t depth) {
  const std::uint64_t mask = (1 << depth) - 1;
  const std::uint8_t shift = 32u - depth;

  const std::uint64_t qnr =
      static_cast<std::uint64_t>((geopt.x >> shift) & mask) |
      (static_cast<std::uint64_t>((geopt.y >> shift) & mask) << depth) |
      (static_cast<std::uint64_t>(1) << (depth << 1));

  return qnr;
}

std::uint8_t compute_depth_ulp_qnr(std::uint64_t qnr) {
  std::uint64_t mask = 0x0000ffff00000000;

  std::uint8_t depth = 0;

  if (qnr & mask) {
    mask <<= 16, depth = 16;
  } else {
    mask >>= 16;
  }

  if (qnr & mask) {
    mask <<= 8, depth = 8;
  } else {
    mask >>= 8;
  }

  if (qnr & mask) {
    mask <<= 4, depth |= 4;
  } else {
    mask >>= 4;
  }

  if (qnr & mask) {
    mask <<= 2, depth |= 2;
  } else {
    mask >>= 2;
  }

  if (qnr & mask) {
    depth |= 1;
  }

  return depth;
}

UPosition geopt32_from_qnr(std::uint64_t qnr) {
  const std::uint8_t depth = compute_depth_ulp_qnr(qnr);
  const std::uint64_t mask = (1 << depth) - 1;
  const std::uint32_t shift = 32u - depth;

  UPosition result;

  result.x = static_cast<std::uint32_t>((qnr & mask) << shift);
  result.y = static_cast<std::uint32_t>(((qnr >> depth) & mask) << shift);

  return result;
}

QuadKey mos_qnr_to_quad_key(std::uint64_t qnr, std::uint8_t depth) {
  UPosition pos = geopt32_from_qnr(qnr);
  std::uint32_t col_step = 0xffffffff >> depth;
  std::uint32_t row_step =
      (depth > 1) ? (0x7fffffff >> (depth - 1)) : (0x7fffffff);
  std::uint32_t col = pos.x / (col_step);
  std::uint32_t row = pos.y / (row_step);
  return QuadKey(Type::UlpQnr, row, col, depth);
}

std::uint64_t quad_key_to_ulp_qnr(const QuadKey &key) {
  std::uint8_t depth = key.get_depth();
  std::uint32_t col_step = 0xffffffff >> depth;
  std::uint32_t row_step =
      (depth > 1) ? (0x7fffffff >> (depth - 1)) : (0x7fffffff);
  UPosition pos(key.get_col() * (col_step + 1), key.get_row() * (row_step + 1));
  std::uint64_t qnr = qnr_from_geopt32(pos, depth);
  return qnr;
}

std::string qnr_to_string(std::uint64_t qnr) {
  // 18,446,744,073,709,551,615'\0'
  const std::uint8_t buff_size = 21u;
  char buff[buff_size];
  snprintf(buff, buff_size, "%llu", static_cast<long long unsigned>(qnr));
  return std::string(buff);
}

std::uint64_t string_to_qnr(const std::string &qnr_str, bool *success) {
  char *endptr;
  std::uint64_t qnr = std::strtoull(qnr_str.c_str(), &endptr, 0);
  if (*endptr == '\0' && qnr != 0) {
    if (success) {
      *success = true;
    }
    return qnr;
  }

  if (success) {
    *success = false;
  }
  return 0;
}
}  // namespace detail

void UlpQnrSystem::get_geo_coordinate_bounds2d(
    GeoCoordinateBoundingBox2d &out_bounds, const QuadKey &self) const {
  GeoCoordinateBoundingBox2d ret;
  std::uint8_t depth = self.get_depth();
  double lon_step = 360.0 / static_cast<double>(1 << depth);
  double lat_step = 360.0 / static_cast<double>(1 << depth);
  std::uint64_t qnr = detail::quad_key_to_ulp_qnr(self);
  UPosition sw = detail::geopt32_from_qnr(qnr);
  GeoCoordinate2d sw_coord = detail::lat_lon_from_geopt32(sw);
  GeoCoordinate2d ne_coord(Longitude(sw_coord.get_longitude().val() + lon_step),
                           Latitude(sw_coord.get_latitude().val() + lat_step));

  ret = GeoCoordinateBoundingBox2d(sw_coord, ne_coord);

  out_bounds = ret;
}

std::string UlpQnrSystem::to_internal_string(const QuadKey &self) const {
  std::uint64_t qnr = detail::quad_key_to_ulp_qnr(self);
  std::string ret = detail::qnr_to_string(qnr);
  return ret;
}

QuadKey UlpQnrSystem::from_internal_string(const std::string &in_string) const {
  bool success = false;
  std::uint64_t qnr = detail::string_to_qnr(in_string, &success);
  if (!success) {
    return QuadKey();
  }
  std::uint8_t depth = detail::compute_depth_ulp_qnr(qnr);
  QuadKey ret = detail::mos_qnr_to_quad_key(qnr, depth);
  return ret;
}

QuadKey UlpQnrSystem::get_key_from_longitude_latitude_at_depth(
    const GeoCoordinate2d &coords, std::uint8_t depth) const {
  UPosition pos = detail::geopt32_from_lat_lon(coords);
  std::uint64_t qnr = detail::qnr_from_geopt32(pos, depth);
  QuadKey ret = detail::mos_qnr_to_quad_key(qnr, depth);
  return ret;
}

std::vector<QuadKey>
UlpQnrSystem::get_keys_from_longitude_latitude_bounding_box(
    const GeoCoordinateBoundingBox2d &bounds, std::uint8_t depth) const {
  std::vector<QuadKey> ret;

  UPosition sw = detail::geopt32_from_lat_lon(bounds.lower_left());
  UPosition ne = detail::geopt32_from_lat_lon(bounds.upper_right());

  std::uint32_t col_step = (0xffffffff >> depth);
  std::uint32_t row_step =
      (depth > 0) ? (0x7fffffff >> (depth - 1)) : (0x7fffffff);

  sw.x &= ~(col_step);
  sw.y &= ~(row_step);

  std::uint32_t ne_col = (ne.x & ~(col_step));
  if (ne_col != ne.x) {
    ne.x = ne_col + col_step;
  }
  std::uint32_t ne_row = (ne.y & ~(row_step));
  if (ne_row != ne.y) {
    ne.y = ne_row + row_step;
  }

  std::uint32_t cols = (ne.x - sw.x) / col_step;
  std::uint32_t rows = (ne.y - sw.y) / row_step;

  for (std::uint32_t xStep = 0; xStep < cols; ++xStep) {
    std::uint32_t currentX = sw.x + (xStep * (col_step + 1));
    for (std::uint32_t yStep = 0; yStep < rows; ++yStep) {
      std::uint32_t currentY = sw.y + (yStep * (row_step + 1));
      UPosition pos(currentX, currentY);
      std::uint64_t qnr = detail::qnr_from_geopt32(pos, depth);
      QuadKey key = detail::mos_qnr_to_quad_key(qnr, depth);
      detail::insert_vector_if_valid_and_unique(ret, key);
    }
  }

  return ret;
}

std::uint8_t UlpQnrSystem::max_depth() const { return 23u; }

std::uint32_t UlpQnrSystem::max_rows(std::uint8_t depth) const {
  if (depth > max_depth()) {
    return 0;
  }
  if (depth == 0) {
    return 1;
  }
  return 1 << (depth - 1);
}

std::uint32_t UlpQnrSystem::max_cols(std::uint8_t depth) const {
  if (depth > max_depth()) {
    return 0;
  }
  return 1 << depth;
}
}  // namespace quad_keys

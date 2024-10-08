#include "quad_keys/utils.h"

#include <math.h>

namespace quad_keys {
UInt32XYPair_t::UInt32XYPair_t() : x(0), y(0) {}

UInt32XYPair_t::UInt32XYPair_t(std::uint32_t xparam, std::uint32_t yparam)
    : x(xparam), y(yparam) {}

Int32XYPair_t::Int32XYPair_t() : x(0), y(0) {}

Int32XYPair_t::Int32XYPair_t(std::int32_t xparam, std::int32_t yparam)
    : x(xparam), y(yparam) {}

DoubleXYPair_t::DoubleXYPair_t() : x(0.0), y(0.0) {}

DoubleXYPair_t::DoubleXYPair_t(double xparam, double yparam)
    : x(xparam), y(yparam) {}

namespace detail {
const double earth_radius = 6378137.0;
const double earth_cirucmference = 2.0 * earth_radius * pi;
const double mercator_min_latitude = -85.05112878;
const double mercator_max_latitude = 85.05112878;
const double pi = 4.0 * std::atan(1.0);

void insert_vector_if_valid_and_unique(std::vector<QuadKey> &outkeys,
                                       const QuadKey &key) {
  if (std::find(outkeys.begin(), outkeys.end(), key) == outkeys.end() &&
      key.get_type() != Type::None) {
    outkeys.push_back(key);
  }
}

Latitude mercator_latitude_clamp(const Latitude &lat) {
  double latit = lat.val();
  latit = std::max(mercator_min_latitude, latit);
  latit = std::min(mercator_max_latitude, latit);
  return Latitude(latit);
}

double mercator_tangent_half_angle_formula(const Latitude &latitude) {
  double radians = degrees_to_radians(latitude.val());
  return std::log(std::tan((pi / 4.0) + (radians / 2.0)));
}

Latitude inverse_mercator_tangent_half_angle_formula(double radians) {
  return Latitude(radians_to_degrees(std::atan(std::sinh(radians))));
}

double degrees_to_radians(double degrees) { return degrees * (pi / 180.0); }

double radians_to_degrees(double radians) { return radians * (180.0 / pi); }

std::uint8_t msb32(std::uint32_t x) {
  std::uint32_t depth = (~0u);
  std::uint32_t shift = 0u;

  depth = (x > 0xffff) << 4;
  x >>= depth;
  shift = (x > 0xff) << 3;
  x >>= shift;
  depth |= shift;
  shift = (x > 0xf) << 2;
  x >>= shift;
  depth |= shift;
  shift = (x > 0x3) << 1;
  x >>= shift;
  depth |= shift;
  shift = (x > 0x1);
  depth |= shift;

  return static_cast<std::uint8_t>(depth);
}

std::uint64_t spread_by_1_bit(std::int64_t x) {
  x &= 0x00000000ffffffffull;
  x = (x | (x << 16)) & 0x0000ffff0000ffffull;
  x = (x | (x << 8)) & 0x00ff00ff00ff00ffull;
  x = (x | (x << 4)) & 0x0f0f0f0f0f0f0f0full;
  x = (x | (x << 2)) & 0x3333333333333333ull;
  x = (x | (x << 1)) & 0x5555555555555555ull;

  return x;
}

std::int64_t compact_by_1_bit(std::int64_t x) {
  x &= 0x5555555555555555ull;
  x = (x | (x >> 1)) & 0x3333333333333333ull;
  x = (x | (x >> 2)) & 0x0f0f0f0f0f0f0f0full;
  x = (x | (x >> 4)) & 0x00ff00ff00ff00ffull;
  x = (x | (x >> 8)) & 0x0000ffff0000ffffull;
  x = (x | (x >> 16)) & 0x00000000ffffffffull;

  return x;
}
}  // namespace detail
}  // namespace quad_keys

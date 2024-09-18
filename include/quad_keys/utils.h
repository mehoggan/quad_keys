#ifndef QUADKEY_UTILS_H_INCLUDED
#define QUADKEY_UTILS_H_INCLUDED

#include <cfloat>
#include <cmath>
#include <cstdint>
#include <vector>

#include "quad_keys/quad_key.h"

namespace quad_keys {
struct UInt32XYPair_t {
  std::uint32_t x;
  std::uint32_t y;

  UInt32XYPair_t();

  UInt32XYPair_t(std::uint32_t xparam, std::uint32_t yparam);
  friend bool operator==(const UInt32XYPair_t &lhs, const UInt32XYPair_t &rhs) {
    return lhs.x == rhs.x && lhs.y == rhs.y;
  }
  friend bool operator!=(const UInt32XYPair_t &lhs, const UInt32XYPair_t &rhs) {
    return lhs.x != rhs.x && lhs.y != rhs.y;
  }
};
using UPixel = UInt32XYPair_t;
using UTile = UInt32XYPair_t;
using UPosition = UInt32XYPair_t;

struct Int32XYPair_t {
  std::int32_t x;
  std::int32_t y;

  Int32XYPair_t();

  Int32XYPair_t(std::int32_t xparam, std::int32_t yparam);
  friend bool operator==(const Int32XYPair_t &lhs, const Int32XYPair_t &rhs) {
    return lhs.x == rhs.x && lhs.y == rhs.y;
  }
  friend bool operator!=(const Int32XYPair_t &lhs, const Int32XYPair_t &rhs) {
    return lhs.x != rhs.x && lhs.y != rhs.y;
  }
};
using Pixel = Int32XYPair_t;
using Tile = Int32XYPair_t;
using Position = Int32XYPair_t;

struct DoubleXYPair_t {
  double x;
  double y;

  DoubleXYPair_t();

  DoubleXYPair_t(double xparam, double yparam);
  friend bool operator==(const DoubleXYPair_t &lhs, const DoubleXYPair_t &rhs) {
    return lhs.x == rhs.x && lhs.y == rhs.y;
  }
  friend bool operator!=(const DoubleXYPair_t &lhs, const DoubleXYPair_t &rhs) {
    return lhs.x != rhs.x && lhs.y != rhs.y;
  }
};
using FPixel = DoubleXYPair_t;
using MetersXY = DoubleXYPair_t;

namespace detail {
extern const double earth_radius;
extern const double earth_cirucmference;
extern const double mercator_min_latitude;
extern const double mercator_max_latitude;
extern const double pi;

void insert_vector_if_valid_and_unique(std::vector<QuadKey> &out_keys,
                                       const QuadKey &key);

Latitude mercator_latitude_clamp(const Latitude &coords);

double mercator_tangent_half_angle_formula(const Latitude &latitude);

Latitude inverse_mercator_tangent_half_angle_formula(double radians);

double degrees_to_radians(double degrees);

double radians_to_degrees(double radians);

std::uint8_t msb32(std::uint32_t x);

std::uint64_t spread_by_1_bit(std::int64_t x);

std::int64_t compact_by_1_bit(std::int64_t x);
}  // namespace detail
}  // namespace quad_keys

#endif

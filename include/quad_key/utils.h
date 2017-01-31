#ifndef QUADKEY_UTILS_H_INCLUDED
#define QUADKEY_UTILS_H_INCLUDED

#include "quad_key/quad_key.h"

#include <cfloat>
#include <cmath>
#include <cstdint>
#include <vector>

namespace quad_keys
{
  struct uint32_xy_pair_t
  {
    std::uint32_t x;
    std::uint32_t y;

    uint32_xy_pair_t();

    uint32_xy_pair_t(std::uint32_t xparam, std::uint32_t yparam);
    friend bool operator==(const uint32_xy_pair_t &lhs,
        const uint32_xy_pair_t &rhs)
    {
      return lhs.x == rhs.x && lhs.y == rhs.y;
    }
    friend bool operator!=(const uint32_xy_pair_t &lhs,
      const uint32_xy_pair_t &rhs)
    {
      return lhs.x != rhs.x && lhs.y != rhs.y;
    }
  };
  using u_pixel = uint32_xy_pair_t;
  using u_tile = uint32_xy_pair_t;
  using u_position = uint32_xy_pair_t;

  struct int32_xy_pair_t
  {
    std::int32_t x;
    std::int32_t y;

    int32_xy_pair_t();

    int32_xy_pair_t(std::int32_t xparam, std::int32_t yparam);
    friend bool operator==(const int32_xy_pair_t &lhs,
      const int32_xy_pair_t &rhs)
    {
      return lhs.x == rhs.x && lhs.y == rhs.y;
    }
    friend bool operator!=(const int32_xy_pair_t &lhs,
        const int32_xy_pair_t &rhs)
    {
      return lhs.x != rhs.x && lhs.y != rhs.y;
    }
  };
  using pixel = int32_xy_pair_t;
  using tile = int32_xy_pair_t;
  using position = int32_xy_pair_t;

  struct double_xy_pair_t
  {
    double x;
    double y;

    double_xy_pair_t();

    double_xy_pair_t(double xparam, double yparam);
    friend bool operator==(const double_xy_pair_t &lhs,
        const double_xy_pair_t &rhs)
    {
        return lhs.x == rhs.x && lhs.y == rhs.y;
    }
    friend bool operator!=(const double_xy_pair_t &lhs,
        const double_xy_pair_t &rhs)
    {
        return lhs.x != rhs.x && lhs.y != rhs.y;
    }
  };
  using f_pixel = double_xy_pair_t;
  using meters_xy = double_xy_pair_t;

  namespace detail
  {
    extern const double earth_radius;
    extern const double earth_cirucmference;
    extern const double mercator_min_latitude;
    extern const double mercator_max_latitude;
    extern const double pi;

    void insert_vector_if_valid_and_unique(std::vector<quad_key> &out_keys,
        const quad_key &key);

    latitude mercator_latitude_clamp(const latitude &coords);

    double mercator_tangent_half_angle_formula(const latitude &latitude);

    latitude inverse_mercator_tangent_half_angle_formula(double radians);

    double degrees_to_radians(double degrees);

    double radians_to_degrees(double radians);

    std::uint8_t msb32(std::uint32_t x);

    std::uint64_t spread_by_1_bit(std::int64_t x);

    std::int64_t compact_by_1_bit(std::int64_t x);
  }
}

#endif

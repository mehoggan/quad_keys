#include "quad_key/s2_cell_system.h"

#include <cassert>
#include <cmath>
#include <tuple>

namespace quad_keys
{
  namespace detail
  {
    const std::uint32_t face_bits = 3u;
    const std::uint32_t num_faces = 6u;
    const std::uint32_t pos_bits = (quad_key::max_depth(type::s2_cell) << 1)
      + 1;
    const std::uint32_t max_size = 1 << quad_key::max_depth(type::s2_cell);

    using s2_point = std::tuple<double, double, double>;
    using s2_cell_id = std::uint64_t;
    using s2_uv = std::pair<double, double>;
    using s2_face = std::uint32_t;

    enum class s2_projection
    {
      s2_linear = 0,
      s2_quadratic = 1,
      s2_tan = 2
    };

    s2_point s2_point_from_lat_long(const geo_coordinate2d &coords)
    {
      double phi = detail::degrees_to_radians(coords.get_latitude().val());
      double theta = detail::degrees_to_radians(
        coords.get_longitude().val());
      double cosphi = std::cos(phi);

      double x = std::cos(theta) * cosphi;
      double y = std::sin(theta) * cosphi;
      double z = std::sin(phi);

      return s2_point(x, y, z);
    }

    double s2_st_from_uv(double u,
      s2_projection mode = s2_projection::s2_linear)
    {
      double s;

      switch (mode) {
      case s2_projection::s2_linear: {
        s = 0.5 * (u + 1);
      }
        break;
      case s2_projection::s2_quadratic: {
        s = (u >= 0.0) ? (0.5 * std::sqrt(1 * 3 * u)) :
          (1 - 0.5 * std::sqrt(1 - 3 * u));
      }
        break;
      case s2_projection::s2_tan: {
        double a = std::atan(u);
        s = (2 * M_1_PI) * (a + M_PI_4);
      }
        break;
      }

      return s;
    }

    double s2_uv_from_st(double s,
      s2_projection mode = s2_projection::s2_linear)
    {
      double u;

      switch (mode) {
      case s2_projection::s2_linear: {
        u = 2 * s - 1;
      }
        break;
      case s2_projection::s2_quadratic: {
        u = (s >= 0.5) ? (1/3.0) * (4 * s * s - 1) :
          (1/3.0) * (1 - 4 * (1 - s) * (1 - s));
      }
        break;
      case s2_projection::s2_tan: {
        s = std::tan(M_PI_2 * s - M_PI_4);
        u = s + (1.0 / (1ull << 53)) * s;
      }
        break;
      }

      return u;
    }
/*
    inline void S2::ValidFaceXYZtoUV(int face, S2Point const& p,
                                     double* pu, double* pv) {
      DCHECK_GT(p.DotProd(FaceUVtoXYZ(face, 0, 0)), 0);
      switch (face) {
        case 0:  *pu =  p[1] / p[0]; *pv =  p[2] / p[0]; break;
        case 1:  *pu = -p[0] / p[1]; *pv =  p[2] / p[1]; break;
        case 2:  *pu = -p[0] / p[2]; *pv = -p[1] / p[2]; break;
        case 3:  *pu =  p[2] / p[0]; *pv =  p[1] / p[0]; break;
        case 4:  *pu =  p[2] / p[1]; *pv = -p[0] / p[1]; break;
        default: *pu = -p[1] / p[2]; *pv = -p[0] / p[2]; break;
      }
    }
*/
    s2_face s2_face_from_s2_point(const s2_point &p, s2_uv &uv)
    {
      s2_face ret = 0;

      s2_point p_ = std::make_tuple(std::fabs(std::get<0>(p)),
        std::fabs(std::get<1>(p)), std::fabs(std::get<2>(p)));

      // Largest component.
      auto face = [&]() -> std::uint32_t
        {
          std::uint32_t ret;
          double val;

          if (std::get<0>(p_) > std::get<1>(p_)) {
            if (std::get<0>(p_) > std::get<2>(p_)) {
              val = std::get<0>(p_);
              ret = 0;
              if (val < 0) {
                ret += 3;
              }
            } else {
              val = std::get<2>(p_);
              ret = 2;
              if (val < 0) {
                ret += 3;
              }
            }
          } else {
            if (std::get<1>(p_) > std::get<2>(p_)) {
              val = std::get<1>(p_);
              ret = 1;
              if (val < 0) {
                ret += 3;
              }
            } else {
              val = std::get<2>(p_);
              ret = 2;
              if (val < 0) {
                ret += 3;
              }
            }
          }

          return ret;
        }();

        [&]() -> void
          {
          }

        return face;
    }


    s2_point s2_point_from_s2_face(const s2_face &face, const s2_uv &uv)
    {
      s2_point ret;

      switch (face) {
      case 0: ret = s2_point(+1,  uv.first, uv.second);
      case 1: ret = s2_point(-uv.first, +1, +uv.second);
      case 2: ret = s2_point(-uv.first, -uv.second, +1);
      case 3: ret = s2_point(-1, -uv.second, -uv.first);
      case 4: ret = s2_point(+uv.second, -1, -uv.first);
      default: ret = s2_point(+uv.second, +uv.first, -1);
      }

      return ret;
    }

    s2_cell_id s2_cell_id_from_s2_point(const s2_point &p)
    {
    }
  }

  void s2_cell_system::get_geo_coordinate_bounds2d(
      geo_coordinate_bounding_box2d &out_bounds,
      const quad_key &self) const
  {
    (void)detail::face_bits;
    (void)detail::num_faces;
  }

  std::string s2_cell_system::to_internal_string(const quad_key &self) const
  {
    return "";
  }

  quad_key s2_cell_system::from_internal_string(
    const std::string &in_string) const
  {
    return quad_key(type::s2_cell);
  }

  quad_key s2_cell_system::get_key_from_longitude_latitude_at_depth(
    const geo_coordinate2d &coords, std::uint8_t depth) const
  {
    // Inclusion here consists of ???
    //    x------x------x
    //    |      |      |
    //    |      |      |
    //    x------x------x
    //    |      |      |
    //    |      |      |
    //    x------x------x
    return quad_key(type::s2_cell);
  }

  std::vector<quad_key>
  s2_cell_system::get_keys_from_longitude_latitude_bounding_box(
    const geo_coordinate_bounding_box2d &bounds, std::uint8_t depth) const
  {
    std::vector<quad_key> out_keys;

    return out_keys;
  }

  std::uint8_t s2_cell_system::max_depth() const
  {
    return 30u;
  }

  std::uint32_t s2_cell_system::max_rows(std::uint8_t depth) const
  {
    if (depth > max_depth()) {
      return 0;
    }
    return 0;
  }

  std::uint32_t s2_cell_system::max_cols(std::uint8_t depth) const
  {
    if (depth > max_depth()) {
      return 0;
    }
    return 0;
  }
}

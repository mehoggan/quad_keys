#include "quad_keys/osgeo_system.h"

#include <cstring>

#define to_double(d) static_cast<double>((d))
#define to_uint32(u) static_cast<std::uint32_t>((u))
#define to_int32(i) static_cast<std::int32_t>((i))

namespace quad_keys
{
  namespace detail
  {
    // Converts WGS84 Datum to XY in Spherical Mercator. Note are length is
    // defined as S = (theta) * r. Where theta is exrpessed in radians.
    MetersXY lat_lon_to_meters(const GeoCoordinate2d & coords)
    {
      const double r = earth_radius;

      GeoCoordinate2d loc = coords;
      loc.set_latitude(mercator_latitude_clamp(coords.get_latitude()));
      double mx = degrees_to_radians(loc.get_longitude().val()) * r;
      double my = mercator_tangent_half_angle_formula(loc.get_latitude()) * r;
      return MetersXY(mx, my);
    }

    GeoCoordinate2d meters_to_lat_lon(const MetersXY &mxy)
    {
        const double r = earth_radius;

        auto lon = radians_to_degrees(mxy.x / r);
        auto lat =
          inverse_mercator_tangent_half_angle_formula(mxy.y / r).val();
        return GeoCoordinate2d(Longitude(lon), Latitude(lat));
    }

    FPixel meters_to_pixels(const MetersXY &mxy, std::uint8_t depth)
    {
      // 2 * pi * r / pixels. Initial resoultion 256, but because we start
      // with 2^0 we only need to shift by an initial 7 not 8.
      double res = (pi * earth_radius) / to_double(1 << (7 + depth));
      double px = to_double((mxy.x + pi * earth_radius) / res);
      double py = to_double((mxy.y + pi * earth_radius) / res);
      return FPixel(px, py);
    }

    MetersXY pixels_to_meters(const FPixel &pixel, std::uint8_t depth)
    {
      // 2 * pi * r / pixels. Initial resoultion 256, but because we start
      // with 2^0 we only need to shift by an initial 7 not 8.
      double res = (pi * earth_radius) / to_double(1 << (7 + depth));
      double mx = (pixel.x * res) - pi * earth_radius;
      double my = (pixel.y * res) - pi * earth_radius;

      return MetersXY(mx, my);
    }

    Tile pixels_to_tile(const FPixel &pixel)
    {
      std::int32_t tx = to_uint32(ceil(pixel.x / 256.0) - 1);
      std::int32_t ty = to_uint32(ceil(pixel.y / 256.0) - 1);

      // This does not conform to the doc, but is used
      tx = std::max(tx, 0);
      ty = std::max(ty, 0);

      return Tile(tx, ty);
    }

    MetersXY tile_to_meters(const Tile &tile, std::uint8_t depth)
    {
      FPixel pixel(tile.x * 256.0, tile.y * 256.0);
      MetersXY mxy = pixels_to_meters(pixel, depth);
      return mxy;
    }
  }

  void OsGeoSystem::get_geo_coordinate_bounds2d(
    GeoCoordinateBoundingBox2d &out_bounds, const QuadKey &self) const
  {
    std::uint8_t depth = self.get_depth();

    Tile tilell(to_int32(self.get_col()), to_int32(self.get_row()));
    MetersXY llm = detail::tile_to_meters(tilell, depth);
    GeoCoordinate2d ll = detail::meters_to_lat_lon(llm);

    Tile tileur(to_int32(self.get_col() + 1), to_int32(self.get_row() + 1));
    MetersXY urm = detail::tile_to_meters(tileur, depth);
    GeoCoordinate2d ur = detail::meters_to_lat_lon(urm);

    out_bounds = GeoCoordinateBoundingBox2d(ll, ur);
  }

  std::string OsGeoSystem::to_internal_string(const QuadKey &self) const
  {
    std::uint8_t depth = self.get_depth();
    std::uint32_t row = self.get_row();
    std::uint32_t col = self.get_col();
    // 4294967295 UINT_MAX/UINT_MAX/BYTE_MAX'\0'
    const std::uint8_t size = 10 + 1 + 10 + 1 + 3 + 1;
    char buf[size];
    snprintf(buf, size, "%u/%u/%u", depth, col, row);
    return std::string(buf);
  }

  QuadKey OsGeoSystem::from_internal_string(
    const std::string &in_string) const
  {
    std::int32_t row = std::numeric_limits<std::int32_t>::min();
    std::int32_t col = std::numeric_limits<std::int32_t>::min();
    std::uint8_t depth = std::numeric_limits<std::uint8_t>::max();
    char *dup = strdup(in_string.c_str());
    char *token = strtok(dup, "/");
    std::size_t token_count = 0;
    while (token) {
      //2,147,483,647'\0'
      switch (token_count) {
      case 2: {
        char* endptr;
        row = std::strtol(token, &endptr, 0);
        if (*endptr != '\0') {
          return QuadKey();
        }
      }
        break;
      case 1: {
        char* endptr;
        col = std::strtol(token, &endptr, 0);
        if (*endptr != '\0') {
          return QuadKey();
        }
      }
        break;
      case 0: {
        char* endptr;
        depth = static_cast<std::uint8_t>(std::strtol(token, &endptr, 0));
        if (*endptr != '\0') {
          return QuadKey();
        }
      }
        break;
      default: {
        return QuadKey();
      }
      }
      token = strtok(nullptr, "/");
      ++token_count;
    }
    free(dup);

    std::int32_t max_rows = to_int32(QuadKey::max_rows(Type::OsGeo,
      QuadKey::max_depth(Type::OsGeo)));
    std::int32_t max_cols = to_int32(QuadKey::max_cols(Type::OsGeo,
      QuadKey::max_depth(Type::OsGeo)));

    if (row >= max_rows || row < -1) {
      return QuadKey();
    }
    if (col >= max_cols || col < -1) {
      return QuadKey();
    }
    if (depth > QuadKey::max_depth(Type::OsGeo)) {
      return QuadKey();
    }

    if (row == -1) {
      row = 0;
    }
    if (col == -1) {
      col = 0;
    }

    return QuadKey(Type::OsGeo, to_uint32(row), to_uint32(col), depth);
  }

  QuadKey OsGeoSystem::get_key_from_longitude_latitude_at_depth(
    const GeoCoordinate2d &coords, std::uint8_t depth) const
  {
    Type t = Type::OsGeo;
    MetersXY xy = detail::lat_lon_to_meters(coords);
    FPixel pxy = detail::meters_to_pixels(xy, depth);
    Tile txy = detail::pixels_to_tile(pxy);
    std::int32_t max_rows_index = to_int32(QuadKey::max_rows(t, depth) - 1);
    txy.y = std::min(txy.y, max_rows_index);
    std::int32_t max_cols_index = to_int32(QuadKey::max_cols(t, depth) - 1);
    txy.x = std::min(txy.x, max_cols_index);
    return QuadKey(Type::OsGeo, to_uint32(txy.y), to_uint32(txy.x), depth);
  }

  std::vector<QuadKey>
  OsGeoSystem::get_keys_from_longitude_latitude_bounding_box(
    const GeoCoordinateBoundingBox2d &bounds, std::uint8_t depth) const
  {
    std::vector<QuadKey> quad_keys;
    MetersXY xyll = detail::lat_lon_to_meters(bounds.lower_left());
    FPixel pxyll = detail::meters_to_pixels(xyll, depth);
    Tile txyll = detail::pixels_to_tile(pxyll);

    MetersXY xyur = detail::lat_lon_to_meters(bounds.upper_right());
    FPixel pxyur = detail::meters_to_pixels(xyur, depth);
    Tile txyur = detail::pixels_to_tile(pxyur);

    for (std::int32_t row = txyll.y; row <= txyur.y; ++row) {
      for (std::int32_t col = txyll.x; col <= txyur.x; ++col) {
        detail::insert_vector_if_valid_and_unique(quad_keys, QuadKey(
          Type::OsGeo, to_uint32(row), to_uint32(col), depth));
      }
    }

    return quad_keys;
  }

  std::uint8_t OsGeoSystem::max_depth() const
  {
    return 22u;
  }

  uint32_t OsGeoSystem::max_rows(std::uint8_t depth) const
  {
    if (depth > max_depth()) {
      return 0;
    }
    return 1 << depth;
  }

  std::uint32_t OsGeoSystem::max_cols(std::uint8_t depth) const
  {
    if (depth > max_depth()) {
      return 0;
    }
    return 1 << depth;
  }
}

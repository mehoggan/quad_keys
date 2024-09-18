#ifndef MORTONQUADKEYSYSTEM_H_INCLUDED
#define MORTONQUADKEYSYSTEM_H_INCLUDED

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "quad_keys/geo_coordinate2d.h"
#include "quad_keys/geo_coordinate_bounding_box2d.h"
#include "quad_keys/quad_key.h"
#include "quad_keys/quad_key_types.h"
#include "quad_keys/system.h"

namespace quad_keys {
class MortonSystem : public System {
 private:
  friend class QuadKey;

 private:
  virtual void get_geo_coordinate_bounds2d(
      GeoCoordinateBoundingBox2d &outbounds, const QuadKey &self) const;

  virtual std::string to_internal_string(const QuadKey &self) const;

  virtual QuadKey from_internal_string(const std::string &in_string) const;

  virtual QuadKey get_key_from_longitude_latitude_at_depth(
      const GeoCoordinate2d &coords, std::uint8_t depth) const;

  virtual std::vector<QuadKey> get_keys_from_longitude_latitude_bounding_box(
      const GeoCoordinateBoundingBox2d &bounds, std::uint8_t depth) const;

  virtual std::uint8_t max_depth() const;

  virtual std::uint32_t max_rows(std::uint8_t depth) const;

  virtual std::uint32_t max_cols(std::uint8_t depth) const;
};
}  // namespace quad_keys
#endif

#ifndef LATLONGQUADKEYSYSTEM_H_INCLUDED
#define LATLONGQUADKEYSYSTEM_H_INCLUDED

#include "quad_key/quad_key.h"
#include "quad_key/quad_key_types.h"
#include "quad_key/geo_coordinate2d.h"
#include "quad_key/geo_coordinate_bounding_box2d.h"
#include "quad_key/system.h"

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

namespace quad_keys
{
  class lat_long_system : public system
  {
  private:
    friend class quad_key;

  private:
    virtual void get_geo_coordinate_bounds2d(
      geo_coordinate_bounding_box2d &out_bounds, const quad_key &self) const;

    virtual std::string to_internal_string(const quad_key &self) const;

    virtual quad_key from_internal_string(
      const std::string &in_string) const;

    virtual quad_key get_key_from_longitude_latitude_at_depth(
      const geo_coordinate2d &coords, std::uint8_t depth) const;

    virtual std::vector<quad_key>
    get_keys_from_longitude_latitude_bounding_box(
      const geo_coordinate_bounding_box2d &bounds, std::uint8_t depth) const;

    virtual std::uint8_t max_depth() const;

    virtual std::uint32_t max_rows(std::uint8_t depth) const;

    virtual std::uint32_t max_cols(std::uint8_t depth) const;
  };
}
#endif

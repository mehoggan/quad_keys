#ifndef QUADKEYNONESYSTEM_H_INCLUDED
#define QUADKEYNONESYSTEM_H_INCLUDED

#include "quad_keys/quad_key.h"
#include "quad_keys/quad_key_types.h"
#include "quad_keys/geo_coordinate2d.h"
#include "quad_keys/geo_coordinate_bounding_box2d.h"
#include "quad_keys/system.h"

#include <cstdint>
#include <memory>
#include <vector>

namespace quad_keys
{
  class NoneSystem : public System
  {
  private:
    friend class QuadKey;

  private:
    virtual bool is_valid(const QuadKey &key) const;

    virtual bool is_root_key(const QuadKey &self) const;

    virtual QuadKey get_parent(const QuadKey &self) const;

    virtual bool is_my_ancestor(const QuadKey &QuadKey,
      const class QuadKey &self) const;

    virtual QuadKey get_ancestor(std::uint8_t depth_delta,
      const QuadKey &self) const;

    virtual QuadKey get_child(QuadKey::quadrant quad_id,
      const QuadKey &self) const;

    virtual std::vector<QuadKey> get_children(const QuadKey &self) const;

    virtual std::vector<QuadKey> get_descendants(
      std::uint8_t depth_delta, const QuadKey &self) const;

    virtual std::vector<QuadKey> get_siblings(const QuadKey &self) const;

    virtual std::vector<QuadKey> get_neighbors(const QuadKey &self) const;

    virtual void get_geo_coordinate_bounds2d(
      GeoCoordinateBoundingBox2d &out_bounds, const QuadKey &self) const;

    virtual std::string to_internal_string(const QuadKey &self) const;

    virtual QuadKey from_internal_string(
      const std::string &in_string) const;

    virtual QuadKey get_key_from_longitude_latitude_at_depth(
      const GeoCoordinate2d &coords, std::uint8_t depth) const;

    virtual std::vector<QuadKey> get_keys_from_longitude_latitude_bounding_box(
      const GeoCoordinateBoundingBox2d &bounds, std::uint8_t depth) const;

    virtual std::uint8_t max_depth() const;

    virtual std::uint32_t max_rows(std::uint8_t depth) const;

    virtual std::uint32_t max_cols(std::uint8_t depth) const;
  };
}
#endif

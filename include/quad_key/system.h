#ifndef QUADKEYSYSTEM_H_INCLUDED
#define QUADKEYSYSTEM_H_INCLUDED

#include "quad_key/quad_key.h"
#include "quad_key/quad_key_types.h"
#include "quad_key/geo_coordinate2d.h"
#include "quad_key/geo_coordinate_bounding_box2d.h"
#include "quad_key/utils.h"

#include <algorithm>
#include <cstdint>
#include <memory>
#include <sstream>
#include <vector>

namespace quad_keys
{
 class system
 {
 private:
   friend class quad_key;

 public:
   system();

 protected:
   static system &get_system_from_enum(type system_type);

   virtual bool is_valid(const quad_key &key) const;

   virtual bool is_root_key(const quad_key &self) const;

   virtual quad_key get_parent(const quad_key &self) const;

   virtual bool is_my_ancestor(const quad_key &qk,
      const quad_key &self) const;

   virtual quad_key get_ancestor(std::uint8_t depth_delta,
     const quad_key &self) const;

   virtual quad_key get_child(quad_key::quadrant quad_id,
     const quad_key &self) const;

   virtual std::vector<quad_key> get_children(const quad_key &self) const;

   virtual std::vector<quad_key> get_descendants(std::uint8_t depth_delta,
     const quad_key &self) const;

   virtual std::vector<quad_key> get_siblings(const quad_key &self) const;

   virtual std::vector<quad_key> get_neighbors(const quad_key &self) const;

   virtual void get_geo_coordinate_bounds2d(
     geo_coordinate_bounding_box2d &out_bounds, const quad_key &self) const;

   virtual std::string to_internal_string(const quad_key &self) const;

   virtual quad_key from_internal_string(const std::string &in_string) const;

   virtual quad_key get_key_from_longitude_latitude_at_depth(
     const geo_coordinate2d &coords, std::uint8_t depth) const;

   virtual std::vector<quad_key>
   get_keys_from_longitude_latitude_bounding_box(
     const geo_coordinate_bounding_box2d &bounds,
     std::uint8_t depth) const;

   virtual std::uint8_t max_depth() const;

   virtual std::uint32_t max_rows(std::uint8_t depth) const;

   virtual std::uint32_t max_cols(std::uint8_t depth) const;
 };
}
#endif

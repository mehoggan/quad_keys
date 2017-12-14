#ifndef QUADKEY_H_INCLUDED
#define QUADKEY_H_INCLUDED

#include "quad_keys_declspec.h"

#include "quad_key/quad_key_types.h"
#include "quad_key/geo_coordinate2d.h"
#include "quad_key/geo_coordinate_bounding_box2d.h"

#include <algorithm>
#include <cstdint>
#include <ostream>
#include <string>
#include <vector>

//                        0
//      0                                        1
//  0       1                                2       3
// 0 1     2 3                              4 5     6 7
// Row or column math equates to
// descendant = 2^depth * ancestor + offset
// ancestor = (descendant - offset) / 2^depth
namespace quad_keys
{
  class system;

  class DLLSPEC_QUADKEY quad_key
  {
  private:
    type m_type;
    std::uint32_t m_row;
    std::uint32_t m_col;
    std::uint8_t m_depth;
    system *m_impl;

  public:
    enum class quadrant
    {
      south_west = 0,
      south_east = 1,
      north_west = 2,
      north_east = 3,
    };

    quad_key();

    explicit quad_key(type t);

    quad_key(type t, std::uint32_t row, std::uint32_t col,
      std::uint8_t depth);

    quad_key(const quad_key &other);

    quad_key &operator=(const quad_key &other);

    // Function that can be implemented in row column space
    type get_type() const {return m_type;}

    std::string type_as_string() const;

    std::uint32_t get_row() const {return m_row;}

    std::uint32_t get_col() const {return m_col;}

    std::uint8_t get_depth() const {return m_depth;}

    // Functions that cannot be implemented in row column space generically
    bool is_root_key() const;

    quad_key get_parent() const;

    bool is_my_ancestor(const quad_key &quad_key) const;

    quad_key get_ancestor(std::uint8_t depth_delta) const;

    quad_key get_child(quadrant quad_id) const;

    std::vector<quad_key> get_children() const;

    std::vector<quad_key> get_descendants(std::uint8_t depth_delta) const;

    std::vector<quad_key> get_siblings() const;

    std::vector<quad_key> get_neighbors() const;

    // Functions that are unique to a given System's implementation.
    void get_geo_coordinate_bounds2d(
        geo_coordinate_bounding_box2d &out_bounds) const;

    std::string to_internal_string() const;

    // Static functions that cannot be implemented in row column space at
    // all
    static quad_key from_internal_string(type t,
      const std::string &in_string);

    static quad_key get_key_from_longitude_latitude_at_depth(type t,
        const geo_coordinate2d &coords, std::uint8_t depth);

    static std::vector<quad_key>
    get_keys_from_longitude_latitude_bounding_box(
      type t, const geo_coordinate_bounding_box2d &bounds,
      std::uint8_t depth);

    static std::uint8_t max_depth(type t);

    static std::uint32_t max_rows(type t, std::uint8_t depth);

    static std::uint32_t max_cols(type t, std::uint8_t depth);

    static std::uint64_t max_tiles(type t, std::uint8_t depth);

    bool operator<(const quad_key &rhs) const
    {
      return m_row < rhs.m_row ||
        (!(m_row < rhs.m_row) && m_col < rhs.m_col) ||
        ((!(m_row < rhs.m_row) && !(m_col < rhs.m_col)) &&
        m_depth < rhs.m_depth);
    }

    bool operator==(const quad_key &rhs) const
    {
      return m_row == rhs.m_row && m_col == rhs.m_col &&
        m_type == rhs.m_type && m_depth == rhs.m_depth;
    }

    bool operator!=(const quad_key &rhs) const
    {
      return !((*this) == rhs);
    }

    friend std::ostream &operator<<(std::ostream &out, const quad_key &obj)
    {
      return out << obj.type_as_string() << ", " << obj.get_row() << ", " <<
        obj.get_col() << ", " << static_cast<std::uint32_t>(
        obj.get_depth());
    }
  };
}

#endif

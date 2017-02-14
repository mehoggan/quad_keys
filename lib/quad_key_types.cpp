#include "quad_key/quad_key_types.h"

namespace quad_keys
{
  std::string type_to_string(type t)
  {
    switch (t) {
    case type::bing: return "bing";
    case type::lat_long: return "lat_long";
    case type::morton: return "morton";
    case type::none: return "none";
    case type::osgeo: return "os_geo";
    case type::ulp_qnr: return "ulp_qnr";
    case type::s2_cell: return "s2_cell";
    default: return "";
    }
  }
}

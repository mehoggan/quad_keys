#include "quad_key/quad_key_types.h"

namespace quad_keys
{
  std::string type_to_string(type t)
  {
    switch (t) {
    case type::bing: return "Bing";
    case type::lat_long: return "LatLong";
    case type::ulp_qnr: return "UlpQnr";
    case type::morton: return "Morton";
    case type::none: return "None";
    case type::osgeo: return "OsGeo";
    default: return "";
    }
  }
}

#include "quad_keys/quad_key_types.h"

namespace quad_keys {
std::string type_to_string(Type t) {
  switch (t) {
    case Type::Bing:
      return "bing";
    case Type::LatLon:
      return "lat_long";
    case Type::Morton:
      return "morton";
    case Type::None:
      return "none";
    case Type::OsGeo:
      return "os_geo";
    case Type::UlpQnr:
      return "ulp_qnr";
    default:
      return "";
  }
}
}  // namespace quad_keys

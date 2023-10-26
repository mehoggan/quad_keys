#ifndef QUADKEYSYSTEMENUM_H_INCLUDED
#define QUADKEYSYSTEMENUM_H_INCLUDED

#include <string>

namespace quad_keys
{
  enum class Type
  {
    Bing,
    LatLon,
    Morton,
    None,
    OsGeo,
    UlpQnr
  };

  std::string type_to_string(Type t);
}
#endif

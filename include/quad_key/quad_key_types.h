#ifndef QUADKEYSYSTEMENUM_H_INCLUDED
#define QUADKEYSYSTEMENUM_H_INCLUDED

#include "declspec.h"

#include <string>

namespace quad_keys
{
  enum class type
  {
    none,
    bing,
    lat_long,
    ulp_qnr,
    osgeo,
    morton,
  };

  DLLSPEC_QUADKEY std::string type_to_string(type t);
}
#endif

#ifndef QUADKEYSYSTEMENUM_H_INCLUDED
#define QUADKEYSYSTEMENUM_H_INCLUDED

#include "quad_keys_declspec.h"

#include <string>

namespace quad_keys
{
  enum class type
  {
    bing,
    lat_long,
    morton,
    none,
    osgeo,
    ulp_qnr,
    s2_cell
  };

  DLLSPEC_QUADKEY std::string type_to_string(type t);
}
#endif

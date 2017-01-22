#ifndef QUADKEYSYSTEMENUM_H_INCLUDED
#define QUADKEYSYSTEMENUM_H_INCLUDED

#include "declspec.h"

#include <string>

namespace QuadKeys
{
    enum class Type
    {
        None,
        Bing,
        LatLong,
        UlpQnr,
        OsGeo,
        Morton,
    };

    DLLSPEC_QUADKEY std::string typeToString(Type type);
}
#endif

#include "QuadKey/QuadKeyTypes.h"

namespace QuadKeys
{
    std::string typeToString(Type type)
    {
        switch (type) {
        case Type::Bing: return "Bing";
        case Type::LatLong: return "LatLong";
        case Type::UlpQnr: return "UlpQnr";
        case Type::Morton: return "Morton";
        case Type::None: return "None";
        case Type::OsGeo: return "OsGeo";
        default: return "";
        }
    }
}

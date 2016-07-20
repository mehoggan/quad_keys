#include "QuadKey/Utils.h"

#include <math.h>

namespace QuadKeys
{
    UInt32_XYPair_t::UInt32_XYPair_t() :
        x(0),
        y(0)
    {}

    UInt32_XYPair_t::UInt32_XYPair_t(std::uint32_t xparam,
        std::uint32_t yparam) :
        x(xparam),
        y(yparam)
    {}

    Int32_XYPair_t::Int32_XYPair_t() :
        x(0),
        y(0)
    {}

    Int32_XYPair_t::Int32_XYPair_t(std::int32_t xparam, std::int32_t yparam) :
        x(xparam),
        y(yparam)
    {}

    Double_XYPair_t::Double_XYPair_t() :
        x(0.0),
        y(0.0)
    {}

    Double_XYPair_t::Double_XYPair_t(double xparam, double yparam) :
        x(xparam),
        y(yparam)
    {}

    namespace Detail
    {
        const double earthRadius = 6378137.0;
        const double earthCirucmference = 2.0 * earthRadius * pi;
        const double mercatorMinLatitude = -85.05112878;
        const double mercatorMaxLatitude = 85.05112878;
        const double pi = 4.0 * std::atan(1.0);

        void insertVectorIfValidAndUnique(
            std::vector<QuadKey> &outKeys, const QuadKey &key)
        {
            if (std::find(outKeys.begin(), outKeys.end(), key) ==
                outKeys.end() && key.getType() != Type::None) {
                outKeys.push_back(key);
            }
        }

        Latitude mercatorLatitudeClamp(const Latitude &lat)
        {
            double latitude = lat.val();
            latitude = std::max(mercatorMinLatitude, latitude);
            latitude = std::min(mercatorMaxLatitude, latitude);
            return Latitude(latitude);
        }

        double mercatorTangentHalfAngleFormula(const Latitude &latitude)
        {
            double radians = degreesToRadians(latitude.val());
            return std::log(std::tan((pi / 4.0) + (radians / 2.0)));
        }

        Latitude inverseMercatorTangentHalfAngleFormula(double radians)
        {
            return Latitude(radiansToDegrees(std::atan(std::sinh(radians))));
        }

        double degreesToRadians(double degrees)
        {
            return degrees * (pi / 180.0);
        }

        double radiansToDegrees(double radians)
        {
            return radians * (180.0 / pi);
        }

        std::uint8_t msb32(std::uint32_t x)
        {
            std::uint32_t depth = (~0u);
            std::uint32_t shift = 0u;

            depth = (x > 0xFFFF) << 4;
            x >>= depth;
            shift = (x > 0xFF) << 3;
            x >>= shift;
            depth |= shift;
            shift = (x > 0xF) << 2;
            x >>= shift;
            depth |= shift;
            shift = (x > 0x3) << 1;
            x >>= shift;
            depth |= shift;
            shift = (x > 0x1);
            depth |= shift;

            return static_cast<std::uint8_t>(depth);
        }

        std::uint64_t spreadBy1Bit(std::int64_t x)
        {
            x &= 0x00000000ffffffffull;
            x = (x | (x << 16)) & 0x0000ffff0000ffffull;
            x = (x | (x << 8)) & 0x00ff00ff00ff00ffull;
            x = (x | (x << 4)) & 0x0f0f0f0f0f0f0f0full;
            x = (x | (x << 2)) & 0x3333333333333333ull;
            x = (x | (x << 1)) & 0x5555555555555555ull;

            return x;
        }

        std::int64_t compactBy1Bit(std::int64_t x)
        {
            x &= 0x5555555555555555ull;
            x = (x | (x >> 1)) & 0x3333333333333333ull;
            x = (x | (x >> 2)) & 0x0f0f0f0f0f0f0f0full;
            x = (x | (x >> 4)) & 0x00ff00ff00ff00ffull;
            x = (x | (x >> 8)) & 0x0000ffff0000ffffull;
            x = (x | (x >> 16)) & 0x00000000ffffffffull;

            return x;
        }
    }
}

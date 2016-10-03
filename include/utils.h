#ifndef QUADKEY_UTILS_H_INCLUDED
#define QUADKEY_UTILS_H_INCLUDED

#include "QuadKey/QuadKey.h"

#include <cfloat>
#include <cmath>
#include <cstdint>
#include <vector>

namespace QuadKeys
{
    struct UInt32_XYPair_t
    {
        std::uint32_t x;
        std::uint32_t y;

        UInt32_XYPair_t();

        UInt32_XYPair_t(std::uint32_t xparam, std::uint32_t yparam);
        friend bool operator==(const UInt32_XYPair_t &lhs,
            const UInt32_XYPair_t &rhs)
        {
            return lhs.x == rhs.x && lhs.y == rhs.y;
        }
        friend bool operator!=(const UInt32_XYPair_t &lhs,
            const UInt32_XYPair_t &rhs)
        {
            return lhs.x != rhs.x && lhs.y != rhs.y;
        }
    };
    using UPixel = UInt32_XYPair_t;
    using UTile = UInt32_XYPair_t;
    using UPosition = UInt32_XYPair_t;

    struct Int32_XYPair_t
    {
        std::int32_t x;
        std::int32_t y;

        Int32_XYPair_t();

        Int32_XYPair_t(std::int32_t xparam, std::int32_t yparam);
        friend bool operator==(const Int32_XYPair_t &lhs,
            const Int32_XYPair_t &rhs)
        {
            return lhs.x == rhs.x && lhs.y == rhs.y;
        }
        friend bool operator!=(const Int32_XYPair_t &lhs,
            const Int32_XYPair_t &rhs)
        {
            return lhs.x != rhs.x && lhs.y != rhs.y;
        }
    };
    using Pixel = Int32_XYPair_t;
    using Tile = Int32_XYPair_t;
    using Position = Int32_XYPair_t;

    struct Double_XYPair_t
    {
        double x;
        double y;

        Double_XYPair_t();

        Double_XYPair_t(double xparam, double yparam);
        friend bool operator==(const Double_XYPair_t &lhs,
            const Double_XYPair_t &rhs)
        {
            return lhs.x == rhs.x && lhs.y == rhs.y;
        }
        friend bool operator!=(const Double_XYPair_t &lhs,
            const Double_XYPair_t &rhs)
        {
            return lhs.x != rhs.x && lhs.y != rhs.y;
        }
    };
    using FPixel = Double_XYPair_t;
    using MetersXY = Double_XYPair_t;

    namespace Detail
    {
        extern const double earthRadius;
        extern const double earthCirucmference;
        extern const double mercatorMinLatitude;
        extern const double mercatorMaxLatitude;
        extern const double pi;

        void insertVectorIfValidAndUnique(std::vector<QuadKey> &outKeys,
            const QuadKey &key);

        Latitude mercatorLatitudeClamp(const Latitude &coords);

        double mercatorTangentHalfAngleFormula(const Latitude &latitude);

        Latitude inverseMercatorTangentHalfAngleFormula(double radians);

        double degreesToRadians(double degrees);

        double radiansToDegrees(double radians);

        std::uint8_t msb32(std::uint32_t x);

        std::uint64_t spreadBy1Bit(std::int64_t x);

        std::int64_t compactBy1Bit(std::int64_t x);
    }
}

#endif

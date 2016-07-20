#ifndef NDSQUADKEYSYSTEM_H_INCLUDED
#define NDSQUADKEYSYSTEM_H_INCLUDED

#include "QuadKey/QuadKey.h"
#include "QuadKey/QuadKeyTypes.h"
#include "QuadKey/GeoCoordinate2d.h"
#include "QuadKey/GeoCoordinateBoundingBox2d.h"
#include "QuadKey/System.h"

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

namespace QuadKeys
{
    // Consult,
    // https://confluence.in.here.com/display/PDOD/Quadtrees,+Quadkeys,+and+Morton+Codes
    // for more information.
    class MortonSystem : public System
    {
    private:
        friend class QuadKey;

    private:
        virtual void getGeoCoordinateBounds2d(
            GeoCoordinateBoundingBox2d &outBounds, const QuadKey &self) const;

        virtual std::string toInternalString(const QuadKey &self) const;

        virtual QuadKey fromInternalString(const std::string &inString) const;

        virtual QuadKey getKeyFromLongitudeLatitudeAtDepth(
            const GeoCoordinate2d &coords, std::uint8_t depth) const;

        virtual std::vector<QuadKey> getKeysFromLongitudeLatitudeBoundingBox(
            const GeoCoordinateBoundingBox2d &bounds,
            std::uint8_t depth) const;

        virtual std::uint8_t maxDepth() const;

        virtual std::uint32_t maxRows(std::uint8_t depth) const;

        virtual std::uint32_t maxCols(std::uint8_t depth) const;
    };
}
#endif

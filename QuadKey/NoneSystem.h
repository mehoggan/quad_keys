#ifndef QUADKEYNONESYSTEM_H_INCLUDED
#define QUADKEYNONESYSTEM_H_INCLUDED

#include "QuadKey/QuadKey.h"
#include "QuadKey/QuadKeyTypes.h"
#include "QuadKey/GeoCoordinate2d.h"
#include "QuadKey/GeoCoordinateBoundingBox2d.h"
#include "QuadKey/System.h"

#include <cstdint>
#include <memory>
#include <vector>

namespace QuadKeys
{
    class NoneSystem : public System
    {
    private:
        friend class QuadKey;

    private:
        virtual bool isValid(const QuadKey &key) const;

        virtual bool isRootKey(const QuadKey &self) const;

        virtual QuadKey getParent(const QuadKey &self) const;

        virtual bool isMyAncestor(const QuadKey &quadKey,
            const QuadKey &self) const;

        virtual QuadKey getAncestor(std::uint8_t depthDelta,
            const QuadKey &self) const;

        virtual QuadKey getChild(QuadKey::Quadrant quadrant,
            const QuadKey &self) const;

        virtual std::vector<QuadKey> getChildren(const QuadKey &self) const;

        virtual std::vector<QuadKey> getDescendants(
            std::uint8_t depthDelta, const QuadKey &self) const;

        virtual std::vector<QuadKey> getSiblings(const QuadKey &self) const;

        virtual std::vector<QuadKey> getNeighbors(const QuadKey &self) const;

        virtual void getGeoCoordinateBounds2d(
            GeoCoordinateBoundingBox2d &outBounds,
            const QuadKey &self) const;

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

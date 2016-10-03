#include "QuadKey/NoneSystem.h"

namespace QuadKeys
{
    bool NoneSystem::isValid(const QuadKey &/*key*/) const
    {
        return false;
    }

    bool NoneSystem::isRootKey(const QuadKey &/*self*/) const
    {
        return true;
    }

    QuadKey NoneSystem::getParent(const QuadKey &/*self*/) const
    {
        return QuadKey();
    }

    bool NoneSystem::isMyAncestor(const QuadKey &/*quadKey*/,
        const QuadKey &/*self*/) const
    {
        return false;
    }

    QuadKey NoneSystem::getAncestor(std::uint8_t /*depthDelta*/,
        const QuadKey &/*self*/) const
    {
        return QuadKey();
    }

    QuadKey NoneSystem::getChild(QuadKey::Quadrant /*quadrant*/,
        const QuadKey &/*self*/) const
    {
        return QuadKey();
    }

    std::vector<QuadKey> NoneSystem::getChildren(const QuadKey &/*self*/) const
    {
        return std::vector<QuadKey>();
    }

    std::vector<QuadKey> NoneSystem::getDescendants(
        std::uint8_t /*depthDelta*/, const QuadKey &/*self*/) const
    {
        return std::vector<QuadKey>();
    }

    std::vector<QuadKey> NoneSystem::getSiblings(const QuadKey &/*self*/) const
    {
        return std::vector<QuadKey>();
    }

    std::vector<QuadKey> NoneSystem::getNeighbors(const QuadKey &/*self*/) const
    {
        return std::vector<QuadKey>();
    }

    void NoneSystem::getGeoCoordinateBounds2d(
        GeoCoordinateBoundingBox2d &outBounds,
        const QuadKey &/*self*/) const
    {
        outBounds = GeoCoordinateBoundingBox2d();
    }

    std::string NoneSystem::toInternalString(const QuadKey &/*self*/) const
    {
        return "";
    }

    QuadKey NoneSystem::fromInternalString(
        const std::string &/*inString*/) const
    {
        return QuadKey();
    }

    QuadKey NoneSystem::getKeyFromLongitudeLatitudeAtDepth(
        const GeoCoordinate2d &/*coords*/,
        std::uint8_t /*depth*/) const
    {
        return QuadKey();
    }

    std::vector<QuadKey> NoneSystem::getKeysFromLongitudeLatitudeBoundingBox(
        const GeoCoordinateBoundingBox2d &/*bounds*/,
        std::uint8_t /*depth*/) const
    {
        return std::vector<QuadKey>();
    }

    std::uint8_t NoneSystem::maxDepth() const
    {
        return 0;
    }

    std::uint32_t NoneSystem::maxRows(std::uint8_t /*depth*/) const
    {
        return 0;
    }

    std::uint32_t NoneSystem::maxCols(std::uint8_t /*depth*/) const
    {
        return 0;
    }
}

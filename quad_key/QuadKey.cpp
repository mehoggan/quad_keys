#include "QuadKey/QuadKey.h"
#include "QuadKey/System.h"

#include <exception>

namespace QuadKeys
{
    QuadKey::QuadKey() :
        m_Type(Type::None),
        m_Row(0),
        m_Col(0),
        m_Depth(0),
        m_Impl(&System::getSystemFromEnum(Type::None))
    {}

    QuadKey::QuadKey(Type type) :
        m_Type(type),
        m_Row(0),
        m_Col(0),
        m_Depth(0),
        m_Impl(&System::getSystemFromEnum(type))
    {}

    QuadKey::QuadKey(Type type, std::uint32_t row, std::uint32_t col,
        std::uint8_t depth) :
        m_Type(type),
        m_Row(row),
        m_Col(col),
        m_Depth(depth),
        m_Impl(&System::getSystemFromEnum(type))
    {
        if (!m_Impl->isValid((*this))) {
            (*this) = QuadKey();
        }
    }

    QuadKey::QuadKey(const QuadKey &other) :
        m_Type(other.m_Type),
        m_Row(other.m_Row),
        m_Col(other.m_Col),
        m_Depth(other.m_Depth),
        m_Impl(other.m_Impl)
    {}

    QuadKey &QuadKey::operator=(const QuadKey &other)
    {
        m_Type = other.m_Type;
        m_Row = other.m_Row;
        m_Col = other.m_Col;
        m_Depth = other.m_Depth;
        m_Impl = other.m_Impl;

        return (*this);
    }

    std::string QuadKey::typeAsString() const
    {
        return typeToString(m_Type);
    }

    bool QuadKey::isRootKey() const
    {
        return m_Impl->isRootKey((*this));
    }

    QuadKey QuadKey::getParent() const
    {
        return m_Impl->getParent((*this));
    }

    bool QuadKey::isMyAncestor(const QuadKey &quadKey) const
    {
        return m_Impl->isMyAncestor(quadKey, (*this));
    }

    QuadKey QuadKey::getAncestor(std::uint8_t depthDelta) const
    {
        return m_Impl->getAncestor(depthDelta, (*this));
    }

    QuadKey QuadKey::getChild(Quadrant quadrant) const
    {
        return m_Impl->getChild(quadrant, (*this));
    }

    std::vector<QuadKey> QuadKey::getChildren() const
    {
        std::vector<QuadKey> outKeys;
        outKeys = m_Impl->getChildren((*this));
        return outKeys;
    }

    std::vector<QuadKey> QuadKey::getDescendants(std::uint8_t depthDelta) const
    {
        std::vector<QuadKey> outKeys;
        outKeys = m_Impl->getDescendants(depthDelta, (*this));
        return outKeys;
    }

    std::vector<QuadKey> QuadKey::getSiblings() const
    {
        std::vector<QuadKey> outKeys;
        outKeys = m_Impl->getSiblings((*this));
        return outKeys;
    }

    std::vector<QuadKey> QuadKey::getNeighbors() const
    {
        std::vector<QuadKey> outKeys;
        outKeys = m_Impl->getNeighbors((*this));
        return outKeys;
    }

    void QuadKey::getGeoCoordinateBounds2d(
        GeoCoordinateBoundingBox2d &outBounds) const
    {
        m_Impl->getGeoCoordinateBounds2d(outBounds, (*this));
    }

    std::string QuadKey::toInternalString() const
    {
        return m_Impl->toInternalString((*this));
    }

    QuadKey QuadKey::fromInternalString(Type type, const std::string &inString)
    {
        return QuadKey(type).m_Impl->fromInternalString(inString);
    }

    QuadKey QuadKey::getKeyFromLongitudeLatitudeAtDepth(Type type,
        const GeoCoordinate2d &coords, std::uint8_t depth)
    {
        if (depth > QuadKey::maxDepth(type)) {
            return QuadKey();
        }

        QuadKey key = QuadKey(type).m_Impl->getKeyFromLongitudeLatitudeAtDepth(
            coords, depth);
        return key;
    }

    std::vector<QuadKey> QuadKey::getKeysFromLongitudeLatitudeBoundingBox(
        Type type, const GeoCoordinateBoundingBox2d &bounds,
        std::uint8_t depth)
    {
        std::vector<QuadKey> outKeys;

        if (depth > QuadKey::maxDepth(type) || !bounds.isValid()) {
            return outKeys;
        }

        outKeys = QuadKey(type).m_Impl->getKeysFromLongitudeLatitudeBoundingBox(
            bounds, depth);

        return outKeys;
    }

    std::uint8_t QuadKey::maxDepth(Type type)
    {
        return QuadKey(type).m_Impl->maxDepth();
    }

    std::uint32_t QuadKey::maxRows(Type type, std::uint8_t depth)
    {
        return QuadKey(type).m_Impl->maxRows(depth);
    }

    std::uint32_t QuadKey::maxCols(Type type, std::uint8_t depth)
    {
        return QuadKey(type).m_Impl->maxCols(depth);
    }

    std::uint64_t QuadKey::maxTiles(Type type, std::uint8_t depth)
    {
        return maxCols(type, depth) * maxRows(type, depth);
    }
}

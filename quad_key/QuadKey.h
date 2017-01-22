#ifndef QUADKEY_H_INCLUDED
#define QUADKEY_H_INCLUDED

#include "declspec.h"

#include "QuadKey/QuadKeyTypes.h"
#include "QuadKey/GeoCoordinate2d.h"
#include "QuadKey/GeoCoordinateBoundingBox2d.h"

#include <algorithm>
#include <cstdint>
#include <ostream>
#include <string>
#include <vector>

//                        0
//      0                                        1
//  0       1                                2       3
// 0 1     2 3                              4 5     6 7
// Row or column math equates to
// descendant = 2^depth * ancestor + offset
// ancestor = (descendant - offset) / 2^depth

namespace QuadKeys
{
    class System;

    class DLLSPEC_QUADKEY QuadKey
    {
    private:
        Type m_Type;
        std::uint32_t m_Row;
        std::uint32_t m_Col;
        std::uint8_t m_Depth;
        System *m_Impl;

    public:
        enum class Quadrant
        {
            SouthWest = 0,
            SouthEast = 1,
            NorthWest = 2,
            NorthEast = 3,
        };

        QuadKey();

        explicit QuadKey(Type type);

        QuadKey(Type type, std::uint32_t row, std::uint32_t col,
            std::uint8_t depth);

        QuadKey(const QuadKey &other);

        QuadKey &operator=(const QuadKey &other);

        // Function that can be implemented in row column space
        Type getType() const {return m_Type;}

        std::string typeAsString() const;

        std::uint32_t getRow() const {return m_Row;}

        std::uint32_t getCol() const {return m_Col;}

        std::uint8_t getDepth() const {return m_Depth;}

        // Functions that cannot be implemented in row column space generically
        bool isRootKey() const;

        QuadKey getParent() const;

        bool isMyAncestor(const QuadKey &quadKey) const;

        QuadKey getAncestor(std::uint8_t depthDelta) const;

        QuadKey getChild(Quadrant quadrant) const;

        std::vector<QuadKey> getChildren() const;

        std::vector<QuadKey> getDescendants(std::uint8_t depthDelta) const;

        std::vector<QuadKey> getSiblings() const;

        std::vector<QuadKey> getNeighbors() const;

        // Functions that are unique to a given System's implementation.
        void getGeoCoordinateBounds2d(
            GeoCoordinateBoundingBox2d &outBounds) const;

        std::string toInternalString() const;

        // Static functions that cannot be implemented in row column space at
        // all
        static QuadKey fromInternalString(Type type,
            const std::string &inString);

        static QuadKey getKeyFromLongitudeLatitudeAtDepth(Type type,
            const GeoCoordinate2d &coords, std::uint8_t depth);

        static std::vector<QuadKey> getKeysFromLongitudeLatitudeBoundingBox(
            Type type, const GeoCoordinateBoundingBox2d &bounds,
            std::uint8_t depth);

        static std::uint8_t maxDepth(Type type);

        static std::uint32_t maxRows(Type type, std::uint8_t depth);

        static std::uint32_t maxCols(Type type, std::uint8_t depth);

        static std::uint64_t maxTiles(Type type, std::uint8_t depth);

        bool operator<(const QuadKey &rhs) const
        {
            return m_Row < rhs.m_Row ||
                (!(m_Row < rhs.m_Row) && m_Col < rhs.m_Col) ||
                ((!(m_Row < rhs.m_Row) && !(m_Col < rhs.m_Col)) &&
                m_Depth < rhs.m_Depth);
        }

        bool operator==(const QuadKey &rhs) const
        {
            return m_Row == rhs.m_Row && m_Col == rhs.m_Col &&
                m_Type == rhs.m_Type && m_Depth == rhs.m_Depth;
        }

        bool operator!=(const QuadKey &rhs) const
        {
            return !((*this) == rhs);
        }

        friend std::ostream &operator<<(std::ostream &out, const QuadKey &obj)
        {
            return out << obj.typeAsString() << ", " << obj.getRow() << ", " <<
                obj.getCol() << ", " << static_cast<std::uint32_t>(
                obj.getDepth());
        }
    };
}

#endif

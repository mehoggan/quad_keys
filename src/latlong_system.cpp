#include "QuadKey/LatLongSystem.h"

namespace QuadKeys
{
    static const double totalLon = 360.0;
    static const double totalLat = 180.0;
    static const std::uint32_t ulpLon = 0xFFFFFFFF;
    static const std::uint32_t ulpLat = 0x7FFFFFFF;

    namespace Detail
    {
        UTile latLongToUlp(const GeoCoordinate2d &coords)
        {
            double longitude = coords.longitude().val();
            std::uint32_t x = (std::uint32_t)(((longitude + 180.0) / totalLon)
                * ulpLon);
            double latitude = coords.latitude().val();
            std::uint32_t y = (std::uint32_t)(((latitude + 90.0) / totalLat)
                * ulpLat);
            return UTile(x, y);
        }

        GeoCoordinate2d ulpToLatLong(const UTile &tile)
        {
            Longitude longitude(((totalLon * tile.x) /
              (double)(ulpLon)) - 180.0);
            Latitude latitude(((totalLat * tile.y) / (double)(ulpLat)) - 90.0);
            return GeoCoordinate2d(longitude, latitude);
        }

        UTile quadKeyToUlp(const QuadKey &self)
        {
            std::uint32_t stepX = ulpLon >> self.getDepth();
            std::uint32_t stepY = ulpLat >> self.getDepth();

            std::uint32_t ulpX = self.getCol() * stepX;
            std::uint32_t ulpY = self.getRow() * stepY;

            return UTile(ulpX, ulpY);
        }

        QuadKey ulpToQuadKey(const UTile &tile, std::uint8_t depth)
        {
            std::uint32_t stepX = ulpLon >> depth;
            std::uint32_t stepY = ulpLat >> depth;

            std::uint32_t col = tile.x / stepX;
            std::uint32_t row = tile.y / stepY;

            // Deal with 180.0 lon and 90.0 lat respectively.
            col = std::max(0u, std::min(col, QuadKey::maxCols(Type::LatLong,
              depth) - 1));
            row = std::max(0u, std::min(row, QuadKey::maxRows(Type::LatLong,
              depth) - 1));

            return QuadKey(Type::LatLong, row, col, depth);
        }
    }

    void LatLongSystem::getGeoCoordinateBounds2d(
        GeoCoordinateBoundingBox2d &outBounds,
        const QuadKey &self) const
    {
        std::uint8_t depth = self.getDepth();
        std::uint32_t stepX = ulpLon >> depth;
        std::uint32_t stepY = ulpLat >> depth;

        UTile ulpLL = Detail::quadKeyToUlp(self);
        GeoCoordinate2d ll = Detail::ulpToLatLong(ulpLL);
        UTile ulpUR(ulpLL.x + stepX, ulpLL.y + stepY);
        GeoCoordinate2d ur = Detail::ulpToLatLong(ulpUR);

        outBounds = GeoCoordinateBoundingBox2d(ll, ur);
    }

    std::string LatLongSystem::toInternalString(const QuadKey &self) const
    {
        std::string str;
        if (self.isRootKey()) {
            return str;
        }
        str.resize(self.getDepth());

        QuadKey tmp = self;
        std::size_t index = str.length() - 1u;

        const char table[4] = { '2', '3', '0', '1' };

        do {
            QuadKey parent = tmp.getParent();
            for (auto quadrant : {
                QuadKey::Quadrant::SouthWest,
                QuadKey::Quadrant::SouthEast,
                QuadKey::Quadrant::NorthWest,
                QuadKey::Quadrant::NorthEast }) {

                if (parent.getChild(quadrant) == tmp) {
                    str[index--] = table[static_cast<std::uint8_t>(quadrant)];
                    break;
                }
            }
            tmp = parent;
        } while (!tmp.isRootKey());

        return str;
    }

    QuadKey LatLongSystem::fromInternalString(const std::string &inString) const
    {
        std::uint8_t depth = static_cast<std::uint8_t>(inString.length());

        if (depth > maxDepth()) {
            return QuadKey();
        }

        auto validChars = {'0', '1', '2', '3'};
        for (auto c : inString) {
            if (std::find(validChars.begin(), validChars.end(), c)
                == validChars.end()) {
                return QuadKey();
            }
        }

        QuadKey ret(Type::Bing);
        for (auto c : inString) {
            switch (c) {
            case '2': ret = ret.getChild(QuadKey::Quadrant::SouthWest); break;
            case '3': ret = ret.getChild(QuadKey::Quadrant::SouthEast); break;
            case '0': ret = ret.getChild(QuadKey::Quadrant::NorthWest); break;
            case '1': ret = ret.getChild(QuadKey::Quadrant::NorthEast); break;
            }
        }
        return ret;
    }

    QuadKey LatLongSystem::getKeyFromLongitudeLatitudeAtDepth(
        const GeoCoordinate2d &coords, std::uint8_t depth) const
    {
        UTile ulp = Detail::latLongToUlp(coords);
        QuadKey ret = Detail::ulpToQuadKey(ulp, depth);
        return ret;
    }

    std::vector<QuadKey> LatLongSystem::getKeysFromLongitudeLatitudeBoundingBox(
        const GeoCoordinateBoundingBox2d &bounds,
        std::uint8_t depth) const
    {
        std::vector<QuadKey> outKeys;

        UTile ulpLL = Detail::latLongToUlp(bounds.lowerLeft());
        QuadKey ll = Detail::ulpToQuadKey(ulpLL, depth);

        // This only works because inclusion is lower left
        UTile ulpUR = Detail::latLongToUlp(bounds.upperRight());
        QuadKey ur = Detail::ulpToQuadKey(ulpUR, depth);


        for (std::uint32_t r = ll.getRow(); r <= ur.getRow(); ++r) {
            for (std::uint32_t c = ll.getCol(); c <= ur.getCol(); ++c) {
                QuadKey key(Type::LatLong, r, c, depth);
                Detail::insertVectorIfValidAndUnique(outKeys, key);
            }
        }

        return outKeys;
    }

    std::uint8_t LatLongSystem::maxDepth() const
    {
        return 23u;
    }

    std::uint32_t LatLongSystem::maxRows(std::uint8_t depth) const
    {
        if (depth > maxDepth()) {
            return 0;
        }
        return 1 << depth;
    }

    std::uint32_t LatLongSystem::maxCols(std::uint8_t depth) const
    {
        if (depth > maxDepth()) {
            return 0;
        }
        return 1 << depth;
    }
}

#include "QuadKey/MortonSystem.h"

#include "QuadKey/Macros.h"

#include <cassert>

namespace QuadKeys
{
    namespace Detail
    {
        const double longitudeRange =
            Longitude::maxLongitude - Longitude::minLongitude;
        const double latitudeRange =
            Latitude::maxLatitude - Latitude::minLatitude;
        const std::uint32_t xDomain = 0xffffffff;
        const std::uint32_t yDomain = 0x7fffffff;

        std::int64_t ndsPositionToMortonMortonCode(const Position &pos)
        {
            std::int64_t mortonCode = 0;

            std::uint64_t x = spreadBy1Bit(pos.x);
            std::uint64_t y = spreadBy1Bit(pos.y);

            mortonCode |= x;
            mortonCode |= (y << 1);

            return mortonCode & (~0x8000000000000000ull);
        }

        Position ndsMortonCodeToMortonPosition(std::int64_t mortonCode)
        {
            int64_t x = compactBy1Bit(mortonCode);
            int64_t y = compactBy1Bit(mortonCode >> 1);

            return Position((std::int32_t)x, (std::int32_t)y);
        }

        GeoCoordinate2d ndsPositionToLatLong(const Position &pos)
        {
            std::int64_t mortonCode = ndsPositionToMortonMortonCode(pos);

            std::int32_t y = pos.y;
            // 0x(NotUsed)(East/West)(North/South)0 0000 0000 0000
            bool belowEquator =
                ((mortonCode & 0x2000000000000000) != 0x0000000000000000);
            if (belowEquator) {
                y |= 0x80000000;
            }

            static double longSpan = std::abs(longitudeRange);
            double lon = (pos.x / static_cast<double>(xDomain)) *
              (longSpan);

            static double latSpan = std::abs(latitudeRange);
            double lat = (y / static_cast<double>(yDomain)) * (latSpan);

            return GeoCoordinate2d(Longitude(lon), Latitude(lat));
        }

        Position latLongToMortonPosition(const GeoCoordinate2d &coords)
        {
            std::int32_t x = 0;
            std::int32_t y = 0;

            double percentX = coords.longitude().val() / (longitudeRange);
            double percentY = coords.latitude().val() / (latitudeRange);

            double lon = std::floor(percentX * (double)xDomain);
            double lat = std::floor(percentY * (double)yDomain);

            x = static_cast<std::int32_t>(lon);
            y = static_cast<std::int32_t>(lat);
            y &= (~0x80000000);

            return Position(x, y);
        }

        std::uint32_t ndsMortonCodeToMortonTileId(std::int64_t morton,
            std::uint8_t depth)
        {
            morton &= (~0x8000000000000000ull);
            std::uint32_t mortonMSB = (std::uint32_t)(
                morton >> (62ull - 2 * depth));
            std::uint32_t tileDepth = 1 << (depth + 16u);
            std::uint32_t tileId = tileDepth | mortonMSB;
            return tileId;
        }

        std::uint8_t depthFromMortonTileId(std::uint32_t tileId)
        {
            std::uint32_t localTileId = tileId;
            std::uint8_t depth = msb32(localTileId);
            depth -= 16u;
            return depth;
        }

        std::int64_t ndsTileIdToMortonMortonCode(std::uint32_t tileId)
        {
            std::uint32_t localTileId = tileId;
            std::uint8_t depth = depthFromMortonTileId(tileId);
            localTileId ^= 1 << (depth + 16u);
            std::int64_t mortonAtDepth = ((std::int64_t)localTileId) <<
                (62ull - 2 * depth);

            return mortonAtDepth;
        }

        // As a note for the two functions below. If c' and r' are in nds space,
        // and both Tc and Tr (total columns and rows) are functions of the
        // current depth.
        //
        // Then:
        // c' = (c + (Tc / 2) % Tc
        // r' = (r + (Tr / 2) % Tr
        //
        // We can perform the inverse using the following assumption. Knowing
        // the definition of "%" to be x % y  = z iff E some "n":
        //
        // x = n * y + z. In our case we assume n == 1.
        // Solving for both c and r respectively we get:
        //
        // (c + (Tc / 2)) = n * Tc + c' ==> c = (Tc / 2) + c'
        // (r + (Tr / 2)) = n * Tr + r' ==> r = (Tr / 2) + r'
        //
        // In the conversion back to c' and r' we % again to keep numbers
        // within range of Tc and Tr.
        Position quadKeyToMortonPosition(const QuadKey &key)
        {
            std::uint8_t depth = key.getDepth();

            std::uint32_t col = key.getCol();
            std::uint32_t totalCols = QuadKey::maxCols(Type::Morton, depth);
            std::uint32_t halfCols = totalCols >> 1;
            std::uint32_t colPrime = (col + halfCols) % totalCols;

            std::uint32_t row = key.getRow();
            std::uint32_t totalRows = QuadKey::maxRows(Type::Morton, depth);
            std::uint32_t halfRows = totalRows >> 1;
            std::uint32_t rowPrime = (row + halfRows) % totalRows;

            std::uint64_t x = spreadBy1Bit(colPrime);
            std::uint64_t y = spreadBy1Bit(rowPrime);

            std::int64_t interleave = 0;
            interleave |= x;
            interleave |= (y << 1);

            std::uint32_t tile = (1 << (depth + 16u)) |
                static_cast<std::uint32_t>(interleave);
            std::int64_t morton = ndsTileIdToMortonMortonCode(tile);
            Position pos = ndsMortonCodeToMortonPosition(morton);
            return pos;
        }

        QuadKey ndsTileIdToQuadKey(std::uint32_t tile, std::uint8_t depth)
        {
            tile = tile ^ (1 << (depth + 16u));

            int64_t colPrime = compactBy1Bit(static_cast<int64_t>(tile));
            std::uint32_t totalCols = QuadKey::maxCols(Type::Morton, depth);
            std::uint32_t halfCols = totalCols >> 1;

            int64_t rowPrime = compactBy1Bit(static_cast<int64_t>(tile >> 1));
            std::uint32_t totalRows = QuadKey::maxRows(Type::Morton, depth);
            std::uint32_t halfRows = totalRows >> 1;

            std::uint32_t col = (halfCols + colPrime) % totalCols;
            std::uint32_t row = (halfRows + rowPrime) % totalRows;

            return QuadKey(Type::Morton, row, col, depth);
        }

        QuadKey ndsPositionToQuadKey(const Position &pos, std::uint8_t depth)
        {
            std::int64_t morton = ndsPositionToMortonMortonCode(pos);
            std::uint32_t tile = ndsMortonCodeToMortonTileId(morton, depth);
            return ndsTileIdToQuadKey(tile, depth);
        }

        std::string ndsTileToString(std::uint32_t tile)
        {
            //2,147,483,647'\0'
            const std::uint8_t buffSize = 11u;
            char buff[buffSize];
            snprintf(buff, buffSize, "%d", tile);
            return std::string(buff);
        }

        std::uint32_t stringToMortonTile(const std::string &qnrStr, bool *success)
        {
            char* endptr;
            std::uint32_t tile = std::strtol(qnrStr.c_str(), &endptr, 0);
            if (*endptr == '\0' && tile != 0) {
                if (success) {
                    *success = true;
                }
                return tile;
            }

            if (success) {
                *success = false;
            }
            return 0;
        }
    }

    void MortonSystem::getGeoCoordinateBounds2d(
        GeoCoordinateBoundingBox2d &outBounds, const QuadKey &self) const
    {
        std::uint8_t depth = self.getDepth();
        if (depth == 0) {
            if (self.getCol() == 0) {
                outBounds = GeoCoordinateBoundingBox2d(
                    GeoCoordinate2d(Longitude(-180.0), Latitude(- 90.0)),
                    GeoCoordinate2d(Longitude(-  0.1), Latitude(+ 90.0)));
            } else {
                outBounds = GeoCoordinateBoundingBox2d(
                    GeoCoordinate2d(Longitude(+  0.0), Latitude(- 90.0)),
                    GeoCoordinate2d(Longitude(+180.0), Latitude(+ 90.0)));
            }
        } else {
            Position posLL = Detail::quadKeyToMortonPosition(self);
            GeoCoordinate2d ll = Detail::ndsPositionToLatLong(posLL);

            std::int32_t deltaX = Detail::xDomain >> (depth + 1);
            std::int32_t deltaY = Detail::yDomain >> depth;

            Position posUR(posLL.x + deltaX, posLL.y + deltaY);
            GeoCoordinate2d ur = Detail::ndsPositionToLatLong(posUR);

            outBounds = GeoCoordinateBoundingBox2d(ll, ur);
        }
    }

    std::string MortonSystem::toInternalString(const QuadKey &self) const
    {
        // Z-Order for depths 0 and 1 are reflected over Y-Axis
        std::uint8_t depth = self.getDepth();
        if (depth == 0) {
            std::size_t index = self.getCol();
            std::uint32_t tile = static_cast<std::uint32_t>(-1);
            switch (index) {
            case 0: tile = 65537u; break;
            case 1: tile = 65536u; break;
            default: assert(false && "This is impossible!!!");
            }
            std::string ret = Detail::ndsTileToString(tile);
            return ret;
        } else if (depth == 1) {
            std::size_t index = (self.getRow() * 4) + (self.getCol() % 4);
            std::uint32_t tile = static_cast<std::uint32_t>(-1);
            switch (index) {
            case 0: tile = 131078u; break;
            case 1: tile = 131079u; break;
            case 2: tile = 131074u; break;
            case 3: tile = 131075u; break;
            case 4: tile = 131076u; break;
            case 5: tile = 131077u; break;
            case 6: tile = 131072u; break;
            case 7: tile = 131073u; break;
            default: assert(false && "This is impossible!!!");
            }
            std::string ret = Detail::ndsTileToString(tile);
            return ret;
        } else {
            Position pos = Detail::quadKeyToMortonPosition(self);
            std::int64_t morton = Detail::ndsPositionToMortonMortonCode(pos);
            std::uint32_t tile = Detail::ndsMortonCodeToMortonTileId(morton,
                depth);
            std::string ret = Detail::ndsTileToString(tile);
            return ret;
        }
    }

    QuadKey MortonSystem::fromInternalString(const std::string &inString) const
    {
        bool success = false;
        std::uint32_t tile = Detail::stringToMortonTile(inString, &success);
        if (!success) {
            return QuadKey();
        }

        // Z-Order for depths 0 and 1 are reflected over Y-Axis
        std::uint8_t depth = Detail::depthFromMortonTileId(tile);
        if (depth == 0) {
            return (tile == 65537) ? QuadKey(Type::Morton, 0, 0, depth) :
                QuadKey(Type::Morton, 0, 1, depth);
        } else if (depth == 1) {
            int32_t index = 131079 - tile;
            switch (index) {
            case 0: return QuadKey(Type::Morton, 0, 1, 1);
            case 1: return QuadKey(Type::Morton, 0, 0, 1);
            case 2: return QuadKey(Type::Morton, 1, 1, 1);
            case 3: return QuadKey(Type::Morton, 1, 0, 1);
            case 4: return QuadKey(Type::Morton, 0, 3, 1);
            case 5: return QuadKey(Type::Morton, 0, 2, 1);
            case 6: return QuadKey(Type::Morton, 1, 3, 1);
            case 7: return QuadKey(Type::Morton, 1, 2, 1);
            default: assert(index > 0 && "This is immpossible!!!");
            }
        } else {
            QuadKey ret = Detail::ndsTileIdToQuadKey(tile, depth);
            return ret;
        }

        return QuadKey();
    }

    QuadKey MortonSystem::getKeyFromLongitudeLatitudeAtDepth(
        const GeoCoordinate2d &coords, std::uint8_t depth) const
    {
        Position pos = Detail::latLongToMortonPosition(coords);
        QuadKey ret = Detail::ndsPositionToQuadKey(pos, depth);
        return ret;
    }

    std::vector<QuadKey> MortonSystem::getKeysFromLongitudeLatitudeBoundingBox(
        const GeoCoordinateBoundingBox2d &bounds,
        std::uint8_t depth) const
    {
        std::vector<QuadKey> quadKeys;
        Position ll = Detail::latLongToMortonPosition(bounds.lowerLeft());
        Position ur = Detail::latLongToMortonPosition(bounds.upperRight());

        QuadKey llQK = Detail::ndsPositionToQuadKey(ll, depth);
        QuadKey urQK = Detail::ndsPositionToQuadKey(ur, depth);

        for (auto col = llQK.getCol(); col <= urQK.getCol(); ++col) {
            for (auto row = llQK.getRow(); row <= urQK.getRow(); ++row) {
                QuadKey quadKey(Type::Morton, row, col, depth);
                Detail::insertVectorIfValidAndUnique(quadKeys, quadKey);
            }
        }

        return quadKeys;
    }

    std::uint8_t MortonSystem::maxDepth() const
    {
        return 15u;
    }

    std::uint32_t MortonSystem::maxRows(std::uint8_t depth) const
    {
        if (depth > maxDepth()) {
            return 0;
        }
        if (depth == 0) {
            return 1;
        }
        return 1 << depth;
    }

    std::uint32_t MortonSystem::maxCols(std::uint8_t depth) const
    {
        if (depth > maxDepth()) {
            return 0;
        }
        return 1 << (depth + 1);
    }
}

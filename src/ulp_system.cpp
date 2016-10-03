#include "QuadKey/UlpQnrSystem.h"

#include "QuadKey/Macros.h"

namespace QuadKeys
{
    namespace Detail
    {
        UPosition geoPt32FromLatLon(const GeoCoordinate2d &coords)
        {
            double lon = coords.longitude().val();
            lon += 180.0;
            while (lon < 0.0) {
                lon += 360.0;
            }
            while (lon > 360.0) {
                lon -= 360.0;
            }
            lon /= 360.0;

            double lat = coords.latitude().val();
            lat += 90.0;
            while (lat < 0.0) {
                lat += 360.0;
            }
            while (lat > 360.0) {
                lat -= 360.0;
            }
            lat /= 360.0;

            return UPosition(
                static_cast<std::uint32_t>(lon * 0xffffffff),
                static_cast<std::uint32_t>(lat * 0xffffffff));
        }

        GeoCoordinate2d latLonFromGeoPt32(const UPosition &geoPt)
        {
            double lon = static_cast<double>(geoPt.x) / 0xffffffff * 360.0;
            double lat = static_cast<double>(geoPt.y) / 0xffffffff * 360.0;

            lon -= 180.0;
            lat -= 90.0;

            return GeoCoordinate2d(Longitude(lon), Latitude(lat));
        }

        std::uint64_t qnrFromGeoPt32(const UPosition &geoPt,
            std::uint8_t depth)
        {
            const std::uint64_t mask = (1 << depth) - 1;
            const std::uint8_t shift = 32u - depth;

            const std::uint64_t qnr =
                static_cast<std::uint64_t>((geoPt.x >> shift) & mask) |
                (static_cast<std::uint64_t>((geoPt.y >> shift) & mask)
                 << depth) | (static_cast<std::uint64_t>(1) << (depth << 1));

            return qnr;
        }

        std::uint8_t computeDepthUlpQnr(std::uint64_t qnr)
        {
            std::uint64_t mask = 0x0000ffff00000000;

            std::uint8_t depth = 0;

            if (qnr & mask) {
                mask <<= 16, depth = 16;
            } else {
                mask >>= 16;
            }

            if (qnr & mask) {
                mask <<= 8, depth = 8;
            } else {
                mask >>= 8;
            }

            if (qnr & mask) {
                mask <<= 4, depth |= 4;
            } else {
                mask >>= 4;
            }

            if (qnr & mask) {
                mask <<= 2, depth |= 2;
            } else {
                mask >>= 2;
            }

            if (qnr & mask) {
                depth |= 1;
            }

            return depth;
        }

        UPosition geoPt32FromQnr(std::uint64_t qnr)
        {
            const std::uint8_t depth = computeDepthUlpQnr(qnr);
            const std::uint64_t mask = (1 << depth) - 1;
            const std::uint32_t shift = 32u - depth;

            UPosition result;

            result.x = static_cast<std::uint32_t>((qnr & mask) << shift);
            result.y = static_cast<std::uint32_t>(((qnr >> depth) & mask)
                << shift);

            return result;
        }

        QuadKey mosQnrToQuadKey(std::uint64_t qnr, std::uint8_t depth)
        {
            UPosition pos = geoPt32FromQnr(qnr);
            std::uint32_t colStep = 0xffffffff >> depth;
            std::uint32_t rowStep = (depth > 1) ? (0x7fffffff >> (depth - 1)) :
                (0x7fffffff);
            std::uint32_t col = pos.x / (colStep);
            std::uint32_t row = pos.y / (rowStep);
            return QuadKey(Type::UlpQnr, row, col, depth);
        }

        std::uint64_t quadKeyToUlpQnr(const QuadKey &key)
        {
            std::uint8_t depth = key.getDepth();
            std::uint32_t colStep = 0xffffffff >> depth;
            std::uint32_t rowStep = (depth > 1) ? (0x7fffffff >> (depth - 1)) :
                (0x7fffffff);
            UPosition pos(key.getCol() * (colStep + 1),
                key.getRow() * (rowStep + 1));
            std::uint64_t qnr = qnrFromGeoPt32(pos, depth);
            return qnr;
        }

        std::string qnrToString(std::uint64_t qnr)
        {
            //18,446,744,073,709,551,615'\0'
            const std::uint8_t buffSize = 21u;
            char buff[buffSize];
            snprintf(buff, buffSize, "%llu",
                static_cast<long long unsigned>(qnr));
            return std::string(buff);
        }

        std::uint64_t stringToQnr(const std::string &qnrStr, bool *success)
        {
            char* endptr;
            std::uint64_t qnr = std::strtoull(qnrStr.c_str(), &endptr, 0);
            if (*endptr == '\0' && qnr != 0) {
                if (success) {
                    *success = true;
                }
                return qnr;
            }

            if (success) {
                *success = false;
            }
            return 0;
        }
    }

    void UlpQnrSystem::getGeoCoordinateBounds2d(
        GeoCoordinateBoundingBox2d &outBounds, const QuadKey &self) const
    {
        GeoCoordinateBoundingBox2d ret;
        std::uint8_t depth = self.getDepth();
        double lonStep = 360.0 / static_cast<double>(1 << depth);
        double latStep = 360.0 / static_cast<double>(1 << depth);
        std::uint64_t qnr = Detail::quadKeyToUlpQnr(self);
        UPosition sw = Detail::geoPt32FromQnr(qnr);
        GeoCoordinate2d swCoord = Detail::latLonFromGeoPt32(sw);
        GeoCoordinate2d neCoord(
           Longitude(swCoord.longitude().val() + lonStep),
           Latitude(swCoord.latitude().val() + latStep));

        ret = GeoCoordinateBoundingBox2d(swCoord, neCoord);

        outBounds = ret;
    }

    std::string UlpQnrSystem::toInternalString(const QuadKey &self) const
    {
        std::uint64_t qnr = Detail::quadKeyToUlpQnr(self);
        std::string ret = Detail::qnrToString(qnr);
        return ret;
    }

    QuadKey UlpQnrSystem::fromInternalString(const std::string &inString) const
    {
        bool success = false;
        std::uint64_t qnr = Detail::stringToQnr(inString, &success);
        if (!success) {
            return QuadKey();
        }
        std::uint8_t  depth = Detail::computeDepthUlpQnr(qnr);
        QuadKey ret = Detail::mosQnrToQuadKey(qnr, depth);
        return ret;
    }

    QuadKey UlpQnrSystem::getKeyFromLongitudeLatitudeAtDepth(
        const GeoCoordinate2d &coords, std::uint8_t depth) const
    {
        UPosition pos = Detail::geoPt32FromLatLon(coords);
        std::uint64_t qnr = Detail::qnrFromGeoPt32(pos, depth);
        QuadKey ret = Detail::mosQnrToQuadKey(qnr, depth);
        return ret;
    }

    std::vector<QuadKey> UlpQnrSystem::getKeysFromLongitudeLatitudeBoundingBox(
        const GeoCoordinateBoundingBox2d &bounds,
        std::uint8_t depth) const
    {
        std::vector<QuadKey> ret;

        UPosition sw = Detail::geoPt32FromLatLon(bounds.lowerLeft());
        UPosition ne = Detail::geoPt32FromLatLon(bounds.upperRight());

        std::uint32_t colStep = (0xffffffff >> depth);
        std::uint32_t rowStep = (depth > 0) ? (0x7fffffff >> (depth - 1)) :
            (0x7fffffff);

        sw.x &= ~(colStep);
        sw.y &= ~(rowStep);

        std::uint32_t neCol = (ne.x & ~(colStep));
        if (neCol != ne.x) {
            ne.x = neCol + colStep;
        }
        std::uint32_t neRow = (ne.y & ~(rowStep));
        if (neRow != ne.y) {
            ne.y = neRow + rowStep;
        }

        std::uint32_t cols = (ne.x - sw.x) / colStep;
        std::uint32_t rows = (ne.y - sw.y) / rowStep;

        for (std::uint32_t xStep = 0; xStep < cols; ++xStep) {
            std::uint32_t currentX = sw.x + (xStep * (colStep + 1));
            for (std::uint32_t yStep = 0; yStep < rows; ++yStep) {
                std::uint32_t currentY = sw.y + (yStep * (rowStep + 1));
                UPosition pos(currentX, currentY);
                std::uint64_t qnr = Detail::qnrFromGeoPt32(pos, depth);
                QuadKey key = Detail::mosQnrToQuadKey(qnr, depth);
                Detail::insertVectorIfValidAndUnique(ret, key);
            }
        }

        return ret;
    }

    std::uint8_t UlpQnrSystem::maxDepth() const
    {
        return 23u;
    }

    std::uint32_t UlpQnrSystem::maxRows(std::uint8_t depth) const
    {
        if (depth > maxDepth()) {
            return 0;
        }
        if (depth == 0) {
            return 1;
        }
        return 1 << (depth - 1);
    }

    std::uint32_t UlpQnrSystem::maxCols(std::uint8_t depth) const
    {
        if (depth > maxDepth()) {
            return 0;
        }
        return 1 << depth;
    }
}

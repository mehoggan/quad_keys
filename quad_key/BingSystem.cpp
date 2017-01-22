#include "QuadKey/BingSystem.h"

namespace QuadKeys
{
    namespace Detail
    {
        const std::uint32_t pixelsPerTile = 256u;

        double mercatorFormulaSinusoidal(const Latitude &latitude)
        {
            double radians = latitude.val() * pi / 180.0;
            double meters = std::sin(radians);
            return std::log((1.0 + meters) / (1.0 - meters)) / (4.0 * pi);
        }

        Latitude inverseMercatorFormulaSinusoidal(double radians)
        {
            double latitude =
                90.0 - 360.0 * std::atan(std::exp(-radians * 2.0 * pi)) / pi;
            return Latitude(latitude);
        }

        UPixel latLongToPixel(const GeoCoordinate2d &coords,
            std::uint8_t depth)
        {
            const double mapSize = static_cast<double>(pixelsPerTile << depth);

            double longitude = coords.longitude().val();
            double latitude = mercatorLatitudeClamp(coords.latitude()).val();
            double x = (longitude + 180.0) / 360.0;
            double y = 0.5 - mercatorFormulaSinusoidal(Latitude(latitude));

            const double max = mapSize - 1.0;
            const double h = 0.5;
            return UPixel(
                (std::uint32_t)(std::min(std::max(x * mapSize + h, 0.0), max)),
                (std::uint32_t)(std::min(std::max(y * mapSize + h, 0.0), max)));
        }

        GeoCoordinate2d pixelToLatLong(const UPixel &pixel, std::uint8_t depth)
        {
            const double mapSize = static_cast<double>(pixelsPerTile << depth);

            double max = mapSize - 1.0;
            double px = static_cast<double>(pixel.x);
            double py = static_cast<double>(pixel.y);
            double x = std::min(std::max(px, 0.0), max) / mapSize - 0.5;
            double y = 0.5 - std::min(std::max(py, 0.0), max) / mapSize;

            Longitude lon(360.0 * x);
            Latitude lat(inverseMercatorFormulaSinusoidal(y));

            return GeoCoordinate2d(lon, lat);
        }

        UTile pixelToTile(const UPixel &pixel)
        {
            return UTile(pixel.x / pixelsPerTile, pixel.y / pixelsPerTile);
        }

        UPixel tileToPixel(const UTile &tile)
        {
            return UPixel(tile.x * pixelsPerTile, tile.y * pixelsPerTile);
        }

        std::string tileToBase4(const UTile &tile, std::uint8_t depth)
        {
            std::string curr = "";

            for (std::uint8_t d = depth; d > 0; --d) {
                std::uint8_t quad = 0;
                std::uint32_t mask = 1 << (d - 1);

                if ((tile.x & mask) != 0u) {
                    ++quad;
                }

                if ((tile.y & mask) != 0u) {
                    quad += 2;
                }

                switch (quad) {
                case 0: curr += '0'; break;
                case 1: curr += '1'; break;
                case 2: curr += '2'; break;
                case 3: curr += '3'; break;
                }
            }

            return curr;
        }

        UTile base4ToTile(const std::string &base4)
        {
            UTile tile;

            std::uint8_t depth = static_cast<std::uint8_t>(base4.length());
            for (std::uint8_t d = depth; d > 0; --d) {
                std::uint32_t mask = 1 << (d - 1);
                std::uint8_t nextDepth = depth - d + 1;
                std::string parent = base4.substr(0, nextDepth);

                switch (parent[parent.length() - 1]) {
                case '0': break;
                case '1': tile.x |= mask; break;
                case '2': tile.y |= mask; break;
                case '3': tile.x |= mask; tile.y |= mask; break;
                }
            }

            return tile;
        }

        QuadKey bingTileToQuadKey(const UTile &tile, std::uint8_t depth)
        {
            std::uint32_t maxIndex = QuadKey::maxRows(Type::Bing, depth) - 1u;
            std::uint32_t row = maxIndex - tile.y;
            std::uint32_t col = tile.x;

            return QuadKey(Type::Bing, row, col, depth);
        }

        UTile quadKeyToBingTile(const QuadKey &key)
        {
            std::uint32_t maxIndex = QuadKey::maxRows(Type::Bing,
                key.getDepth()) - 1u;
            std::uint32_t y = maxIndex - key.getRow();
            std::uint32_t x = key.getCol();

            return UTile(x, y);
        }
    }

    void BingSystem::getGeoCoordinateBounds2d(
        GeoCoordinateBoundingBox2d &outBounds,
        const QuadKey &self) const
    {
        std::uint8_t depth = self.getDepth();

        UTile tm = Detail::quadKeyToBingTile(self);
        UPixel topLeftPixel = Detail::tileToPixel(tm);
        GeoCoordinate2d tlCoords = Detail::pixelToLatLong(topLeftPixel, depth);

        UTile tmbr(tm.x + 1, tm.y + 1);
        UPixel bottomRightPixel = Detail::tileToPixel(tmbr);
        GeoCoordinate2d brCoords = Detail::pixelToLatLong(bottomRightPixel,
            depth);

        outBounds = GeoCoordinateBoundingBox2d(
            GeoCoordinate2d(tlCoords.longitude(), brCoords.latitude()),
            GeoCoordinate2d(brCoords.longitude(), tlCoords.latitude()));
    }

    std::string BingSystem::toInternalString(const QuadKey &self) const
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

    QuadKey BingSystem::fromInternalString(const std::string &inString) const
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

    QuadKey BingSystem::getKeyFromLongitudeLatitudeAtDepth(
        const GeoCoordinate2d &coords, std::uint8_t depth) const
    {
        // Inclusion here consists of upper left
        // ul X------X------X
        //    |      |      |
        //    |      |      |
        //    X------X------X
        //    |      |      |
        //    |      |      |
        //    X------X------X
        UPixel llPixel = Detail::latLongToPixel(coords, depth);
        UTile tile = Detail::pixelToTile(llPixel);

        return Detail::bingTileToQuadKey(tile, depth);
    }

    std::vector<QuadKey> BingSystem::getKeysFromLongitudeLatitudeBoundingBox(
        const GeoCoordinateBoundingBox2d &bounds,
        std::uint8_t depth) const
    {
        std::vector<QuadKey> outKeys;

        GeoCoordinate2d topLeft(bounds.lowerLeft().longitude(),
            bounds.upperRight().latitude());
        GeoCoordinate2d bottomRight(bounds.upperRight().longitude(),
            bounds.lowerLeft().latitude());

        UPixel ulPixel = Detail::latLongToPixel(topLeft, depth);
        UTile ulTile = Detail::pixelToTile(ulPixel);

        UPixel lrPixel = Detail::latLongToPixel(bottomRight, depth);
        UTile lrTile = Detail::pixelToTile(lrPixel);

        for (std::uint32_t x = ulTile.x; x <= lrTile.x; ++x) {
            for (std::uint32_t y = ulTile.y; y <= lrTile.y; ++y) {
                QuadKey key = Detail::bingTileToQuadKey(UTile(x, y), depth);
                Detail::insertVectorIfValidAndUnique(outKeys, key);
            }
        }

        return outKeys;
    }

    std::uint8_t BingSystem::maxDepth() const
    {
        return 23u;
    }

    std::uint32_t BingSystem::maxRows(std::uint8_t depth) const
    {
        if (depth > maxDepth()) {
            return 0;
        }
        return 1 << depth;
    }

    std::uint32_t BingSystem::maxCols(std::uint8_t depth) const
    {
        if (depth > maxDepth()) {
            return 0;
        }
        return 1 << depth;
    }
}

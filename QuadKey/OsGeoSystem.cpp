#include "QuadKey/OsGeoSystem.h"

#include "QuadKey/Macros.h"

#define to_double(d) static_cast<double>((d))
#define to_uint32(u) static_cast<std::uint32_t>((u))
#define to_int32(i) static_cast<std::int32_t>((i))

namespace QuadKeys
{
    namespace Detail
    {
        // Converts WGS84 Datum to XY in Spherical Mercator. Note are length is
        // defined as S = (theta) * r. Where theta is exrpessed in radians.
        MetersXY latLonToMeters(const GeoCoordinate2d & coords)
        {
            const double r = earthRadius;

            GeoCoordinate2d loc = coords;
            loc.latitude(mercatorLatitudeClamp(coords.latitude()));
            double mx = degreesToRadians(loc.longitude().val()) * r;
            double my = mercatorTangentHalfAngleFormula(loc.latitude()) * r;
            return MetersXY(mx, my);
        }

        GeoCoordinate2d metersToLatLon(const MetersXY &mxy)
        {
            const double r = earthRadius;

            auto lon = radiansToDegrees(mxy.x / r);
            auto lat = inverseMercatorTangentHalfAngleFormula(mxy.y / r).val();
            return GeoCoordinate2d(Longitude(lon), Latitude(lat));
        }

        FPixel metersToPixels(const MetersXY &mxy, std::uint8_t depth)
        {
            // 2 * pi * r / pixels. Initial resoultion 256, but because we start
            // with 2^0 we only need to shift by an initial 7 not 8.
            double res = (pi * earthRadius) / to_double(1 << (7 + depth));
            double px = to_double((mxy.x + pi * earthRadius) / res);
            double py = to_double((mxy.y + pi * earthRadius) / res);
            return FPixel(px, py);
        }

        MetersXY pixelsToMeters(const FPixel &pixel, std::uint8_t depth)
        {
            // 2 * pi * r / pixels. Initial resoultion 256, but because we start
            // with 2^0 we only need to shift by an initial 7 not 8.
            double res = (pi * earthRadius) / to_double(1 << (7 + depth));
            double mx = (pixel.x * res) - pi * earthRadius;
            double my = (pixel.y * res) - pi * earthRadius;

            return MetersXY(mx, my);
        }

        Tile pixelsToTile(const FPixel &pixel)
        {
            std::int32_t tx = to_uint32(ceil(pixel.x / 256.0) - 1);
            std::int32_t ty = to_uint32(ceil(pixel.y / 256.0) - 1);

            // This does not conform to the doc, but is used
            tx = std::max(tx, 0);
            ty = std::max(ty, 0);

            return Tile(tx, ty);
        }

        MetersXY tileToMeters(const Tile &tile, std::uint8_t depth)
        {
            FPixel pixel(tile.x * 256.0, tile.y * 256.0);
            MetersXY mxy = pixelsToMeters(pixel, depth);
            return mxy;
        }
    }

    void OsGeoSystem::getGeoCoordinateBounds2d(
        GeoCoordinateBoundingBox2d &outBounds, const QuadKey &self) const
    {
        std::uint8_t depth = self.getDepth();

        Tile tilell(to_int32(self.getCol()), to_int32(self.getRow()));
        MetersXY llm = Detail::tileToMeters(tilell, depth);
        GeoCoordinate2d ll = Detail::metersToLatLon(llm);

        Tile tileur(to_int32(self.getCol() + 1), to_int32(self.getRow() + 1));
        MetersXY urm = Detail::tileToMeters(tileur, depth);
        GeoCoordinate2d ur = Detail::metersToLatLon(urm);

        outBounds = GeoCoordinateBoundingBox2d(ll, ur);
    }

    std::string OsGeoSystem::toInternalString(const QuadKey &self) const
    {
        std::uint8_t depth = self.getDepth();
        std::uint32_t row = self.getRow();
        std::uint32_t col = self.getCol();
        // 4294967295 UINT_MAX/UINT_MAX/BYTE_MAX'\0'
        const std::uint8_t size = 10 + 1 + 10 + 1 + 3 + 1;
        char buf[size];
        snprintf(buf, size, "%u/%u/%u", depth, col, row);
        return std::string(buf);
    }

    QuadKey OsGeoSystem::fromInternalString(const std::string &inString) const
    {
        std::int32_t row = std::numeric_limits<std::int32_t>::min();
        std::int32_t col = std::numeric_limits<std::int32_t>::min();
        std::uint8_t depth = std::numeric_limits<std::uint8_t>::max();
        char *dup = strdup(inString.c_str());
        char *token = strtok(dup, "/");
        std::size_t tokenCount = 0;
        while (token) {
            //2,147,483,647'\0'
            switch (tokenCount) {
            case 2: {
                char* endptr;
                row = std::strtol(token, &endptr, 0);
                if (*endptr != '\0') {
                    return QuadKey();
                }
            }
                    break;
            case 1: {
                char* endptr;
                col = std::strtol(token, &endptr, 0);
                if (*endptr != '\0') {
                    return QuadKey();
                }
            }
                    break;
            case 0: {
                char* endptr;
                depth = static_cast<std::uint8_t>(std::strtol(token, &endptr,
                    0));
                if (*endptr != '\0') {
                    return QuadKey();
                }
            }
                    break;
            default: {
                return QuadKey();
            }
            }
            token = strtok(NULL, "/");
            ++tokenCount;
        }
        free(dup);

        std::int32_t maxRows = to_int32(QuadKey::maxRows(Type::OsGeo,
            QuadKey::maxDepth(Type::OsGeo)));
        std::int32_t maxCols = to_int32(QuadKey::maxCols(Type::OsGeo,
            QuadKey::maxDepth(Type::OsGeo)));

        if (row >= maxRows || row < -1) {
            return QuadKey();
        }
        if (col >= maxCols || col < -1) {
            return QuadKey();
        }
        if (depth > QuadKey::maxDepth(Type::OsGeo)) {
            return QuadKey();
        }

        if (row == -1) {
            row = 0;
        }

        if (col == -1) {
            col = 0;
        }

        return QuadKey(Type::OsGeo, to_uint32(row), to_uint32(col), depth);
    }

    QuadKey OsGeoSystem::getKeyFromLongitudeLatitudeAtDepth(
        const GeoCoordinate2d &coords, std::uint8_t depth) const
    {
        Type type = Type::OsGeo;
        MetersXY xy = Detail::latLonToMeters(coords);
        FPixel pxy = Detail::metersToPixels(xy, depth);
        Tile txy = Detail::pixelsToTile(pxy);
        std::int32_t maxRowsIndex = to_int32(QuadKey::maxRows(type, depth) - 1);
        txy.y = std::min(txy.y, maxRowsIndex);
        std::int32_t maxColsIndex = to_int32(QuadKey::maxCols(type, depth) - 1);
        txy.x = std::min(txy.x, maxColsIndex);
        return QuadKey(Type::OsGeo, to_uint32(txy.y), to_uint32(txy.x), depth);
    }

    std::vector<QuadKey> OsGeoSystem::getKeysFromLongitudeLatitudeBoundingBox(
        const GeoCoordinateBoundingBox2d &bounds, std::uint8_t depth) const
    {
        std::vector<QuadKey> quadKeys;
        MetersXY xyll = Detail::latLonToMeters(bounds.lowerLeft());
        FPixel pxyll = Detail::metersToPixels(xyll, depth);
        Tile txyll = Detail::pixelsToTile(pxyll);

        MetersXY xyur = Detail::latLonToMeters(bounds.upperRight());
        FPixel pxyur = Detail::metersToPixels(xyur, depth);
        Tile txyur = Detail::pixelsToTile(pxyur);

        for (std::int32_t row = txyll.y; row <= txyur.y; ++row) {
            for (std::int32_t col = txyll.x; col <= txyur.x; ++col) {
                Detail::insertVectorIfValidAndUnique(quadKeys, QuadKey(
                    Type::OsGeo, to_uint32(row), to_uint32(col), depth));
            }
        }

        return quadKeys;
    }

    std::uint8_t OsGeoSystem::maxDepth() const
    {
        return 22u;
    }

    uint32_t OsGeoSystem::maxRows(std::uint8_t depth) const
    {
        if (depth > maxDepth()) {
            return 0;
        }
        return 1 << depth;
    }

    std::uint32_t OsGeoSystem::maxCols(std::uint8_t depth) const
    {
        if (depth > maxDepth()) {
            return 0;
        }
        return 1 << depth;
    }
}

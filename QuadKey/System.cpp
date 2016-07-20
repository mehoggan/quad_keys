#include "QuadKey/System.h"

#include "QuadKey/BingSystem.h"
#include "QuadKey/LatLongSystem.h"
#include "QuadKey/UlpQnrSystem.h"
#include "QuadKey/MortonSystem.h"
#include "QuadKey/NoneSystem.h"
#include "QuadKey/OsGeoSystem.h"

namespace QuadKeys
{
    static BingSystem bingSystem;
    static LatLongSystem latlongSystem;
    static UlpQnrSystem mosQnrSystem;
    static MortonSystem ndsSystem;
    static NoneSystem noneSystem;
    static OsGeoSystem osGeoSystem;

    System::System()
    {}

    System &System::getSystemFromEnum(Type systemType)
    {
        switch (systemType)
        {
        case Type::Bing: return bingSystem;
        case Type::LatLong: return latlongSystem;
        case Type::UlpQnr: return mosQnrSystem;
        case Type::OsGeo: return osGeoSystem;
        case Type::Morton: return ndsSystem;
        case Type::None: // Fall through
        default: return noneSystem;
        }
    }

    bool System::isValid(const QuadKey &key) const
    {
        bool valid = true;

        valid &= (key.getDepth() <= maxDepth());
        valid &= (key.getRow() < maxRows(key.getDepth()));
        valid &= (key.getCol() < maxCols(key.getDepth()));

        return valid;
    }

    bool System::isRootKey(const QuadKey &self) const
    {
        return (((self.getRow() == 0) && (self.getCol() == 0)) &&
            (self.getDepth() == 0));
    }

    QuadKey System::getParent(const QuadKey &self) const
    {
        if (self.isRootKey() || self.getType() == Type::None) {
            return QuadKey();
        }

        std::uint32_t row = self.getRow() >> 1u;
        std::uint32_t col = self.getCol() >> 1u;
        std::uint8_t depth = self.getDepth() - 1;

        return QuadKey(self.getType(), row, col, depth);
    }

    bool System::isMyAncestor(const QuadKey &quadKey,
        const QuadKey &self) const
    {
        bool check = false;

        if (quadKey.getDepth() >= self.getDepth() ||
            quadKey.getType() != self.getType() ||
            quadKey.getType() == Type::None) {
            check = false;
        } else {
            std::uint8_t deltaDepth = self.getDepth() - quadKey.getDepth();
            QuadKey tmp = getAncestor(deltaDepth, self);
            check = (tmp == quadKey);
        }

        return check;
    }

    QuadKey System::getAncestor(std::uint8_t depthDelta,
        const QuadKey &self) const
    {
        if (static_cast<std::int8_t>(self.getDepth()) -
            static_cast<std::int8_t>(depthDelta) < 0) {
            return QuadKey();
        }

        if (self.getType() == Type::None || depthDelta == 0) {
            return QuadKey();
        }

        std::uint32_t shift = depthDelta;
        std::uint32_t row = self.getRow() >> shift;
        std::uint32_t col = self.getCol() >> shift;
        std::uint8_t depth = self.getDepth() - depthDelta;

        return QuadKey(self.getType(), row, col, depth);
    }

    QuadKey System::getChild(QuadKey::Quadrant quadrant,
        const QuadKey &self) const
    {
        std::uint8_t depth = self.getDepth() + 1;
        if (depth > QuadKey::maxDepth(self.getType())) {
            return QuadKey();
        }

        if (self.getType() == Type::None) {
            return QuadKey();
        } else {
            std::uint32_t row = (self.getRow() << 1);
            std::uint32_t col = (self.getCol() << 1);

            switch (quadrant) {
            case QuadKey::Quadrant::NorthWest: row += 1u; break;
            case QuadKey::Quadrant::NorthEast: row += 1u; col += 1u; break;
            case QuadKey::Quadrant::SouthEast: col += 1u; break;
            case QuadKey::Quadrant::SouthWest: break;
            }

            return QuadKey(self.getType(), row, col, depth);
        }
    }

    std::vector<QuadKey> System::getChildren(const QuadKey &self) const
    {
        std::vector<QuadKey> outKeys;

        for (std::uint8_t quadrant = 0; quadrant < 4; ++quadrant) {
            QuadKey child =
              getChild(static_cast<QuadKey::Quadrant>(quadrant), self);
            Detail::insertVectorIfValidAndUnique(outKeys, child);
        }

        return outKeys;
    }

    std::vector<QuadKey> System::getDescendants(
        std::uint8_t depthDelta, const QuadKey &self) const
    {
        std::vector<QuadKey> outKeys;

        if (self.getType() == Type::None || depthDelta == 0) {
            return outKeys;
        }

        const std::uint8_t max = QuadKey::maxDepth(self.getType());
        if (static_cast<std::int8_t>(self.getDepth()) +
            static_cast<std::int8_t>(depthDelta) > max) {
            return outKeys;
        }

        std::uint32_t shift = depthDelta;
        std::uint32_t row = self.getRow() << shift;
        std::uint32_t col = self.getCol() << shift;
        std::uint8_t depth = self.getDepth() + depthDelta;

        std::uint32_t rows = QuadKey::maxRows(self.getType(), depthDelta);
        std::uint32_t cols = QuadKey::maxCols(self.getType(), depthDelta);

        for (std::uint32_t r = row; r < rows; ++r) {
            for (std::uint32_t c = col; c < cols; ++c) {
                QuadKey descendant(self.getType(), r, c, depth);
                Detail::insertVectorIfValidAndUnique(outKeys, descendant);
            }
        }

        return outKeys;
    }

    std::vector<QuadKey> System::getSiblings(const QuadKey &self) const
    {
        std::vector<QuadKey> outKeys;

        if (self.isRootKey()) {
            return outKeys;
        } else {
            QuadKey parent = self.getParent();
            std::vector<QuadKey> children;
            children = parent.getChildren();
            children.erase(std::remove(children.begin(), children.end(), self),
                children.end());
            for (auto key : children) {
                Detail::insertVectorIfValidAndUnique(outKeys, key);
            }
        }

        return outKeys;
    }

    std::vector<QuadKey> System::getNeighbors(const QuadKey &self) const
    {
        std::vector<QuadKey> outKeys;

        if (self.isRootKey()) {
            return outKeys;
        } else {
            QuadKey n(self.getType(), self.getRow() + 1, self.getCol() + 0,
                self.getDepth());
            QuadKey ne(self.getType(), self.getRow() + 1, self.getCol() + 1,
                self.getDepth());
            QuadKey e(self.getType(), self.getRow() + 0, self.getCol() + 1,
                self.getDepth());
            QuadKey se(self.getType(), self.getRow() - 1, self.getCol() + 1,
                self.getDepth());
            QuadKey s(self.getType(), self.getRow() - 1, self.getCol() + 0,
                self.getDepth());
            QuadKey sw(self.getType(), self.getRow() - 1, self.getCol() - 1,
                self.getDepth());
            QuadKey w(self.getType(), self.getRow() + 0, self.getCol() - 1,
                self.getDepth());
            QuadKey nw(self.getType(), self.getRow() + 1, self.getCol() - 1,
                self.getDepth());

            uint32_t maxColIndex = QuadKey::maxCols(
                self.getType(), self.getDepth()) - 1;

            // These two conditionals deal with wrap around in the Longitudinal
            // direction.
            if (e.getType() == Type::None) {
                e = QuadKey(self.getType(),self.getRow(), 0, self.getDepth());

                if (n.getType() == Type::None) {
                    se = QuadKey(self.getType(),self.getRow() - 1, 0,
                        self.getDepth());
                } else {
                    ne = QuadKey(self.getType(),self.getRow() + 1, 0,
                        self.getDepth());
                }

                 if (s.getType() == Type::None) {
                     ne = QuadKey(self.getType(),self.getRow() + 1, 0,
                         self.getDepth());
                 } else {
                     se = QuadKey(self.getType(),self.getRow() - 1, 0,
                         self.getDepth());
                 }
            }

            if (w.getType() == Type::None) {
                w = QuadKey(self.getType(),self.getRow(), maxColIndex,
                    self.getDepth());

                if (n.getType() == Type::None) {
                    sw = QuadKey(self.getType(),self.getRow() - 1, maxColIndex,
                        self.getDepth());
                } else {
                    nw = QuadKey(self.getType(),self.getRow() + 1, maxColIndex,
                        self.getDepth());
                }

                if (s.getType() == Type::None) {
                    nw = QuadKey(self.getType(),self.getRow() + 1, maxColIndex,
                        self.getDepth());
                } else {
                    sw = QuadKey(self.getType(),self.getRow() - 1, maxColIndex,
                        self.getDepth());
                }
            }

            Detail::insertVectorIfValidAndUnique(outKeys, n);
            Detail::insertVectorIfValidAndUnique(outKeys, ne);
            Detail::insertVectorIfValidAndUnique(outKeys, e);
            Detail::insertVectorIfValidAndUnique(outKeys, se);
            Detail::insertVectorIfValidAndUnique(outKeys, s);
            Detail::insertVectorIfValidAndUnique(outKeys, sw);
            Detail::insertVectorIfValidAndUnique(outKeys, w);
            Detail::insertVectorIfValidAndUnique(outKeys, nw);
        }

        return outKeys;
    }

    void System::getGeoCoordinateBounds2d(
        GeoCoordinateBoundingBox2d &outBounds, const QuadKey &/*self*/) const
    {
        outBounds = GeoCoordinateBoundingBox2d();
    }

    std::string System::toInternalString(const QuadKey &/*self*/) const
    {
        return "";
    }

    QuadKey System::fromInternalString(const std::string &/*inString*/) const
    {
        return QuadKey();
    }

    QuadKey System::getKeyFromLongitudeLatitudeAtDepth(
        const GeoCoordinate2d &/*coords*/, std::uint8_t /*depth*/) const
    {
        return QuadKey();
    }

    std::vector<QuadKey> System::getKeysFromLongitudeLatitudeBoundingBox(
        const GeoCoordinateBoundingBox2d &/*bounds*/,
        std::uint8_t /*depth*/) const
    {
        return std::vector<QuadKey>();
    }

    std::uint8_t System::maxDepth() const
    {
        return 0;
    }

    uint32_t System::maxRows(std::uint8_t /*depth*/) const
    {
        return 0;
    }

    uint32_t System::maxCols(std::uint8_t /*depth*/) const
    {
        return 0;
    }
}

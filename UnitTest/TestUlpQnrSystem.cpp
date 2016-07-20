#include <gtest/gtest.h>

#include "QuadKey/GeoCoordinate2d.h"
#include "QuadKey/Macros.h"
#include "QuadKey/QuadKey.h"

#include <algorithm>
#include <numeric>
#include <iostream>

namespace QuadKeys
{
    class UlpQnrSystemTest : public ::testing::Test
    {
    protected:
        virtual void SetUp() {}
        virtual void TearDown() {}
    };

    TEST(MOSQNRSYSTEM, IsValid)
    {
        // Same as BingSystem
    }

    TEST(MOSQNRSYSTEM, IsRootKey)
    {
        // Same as BingSystem
    }

    TEST(MOSQNRSYSTEM, GetParent)
    {
        // Same as BingSystem
    }

    TEST(MOSQNRSYSTEM, IsMyAncestor)
    {
        // Same as BingSystem
    }

    TEST(MOSQNRSYSTEM, GetAncestor)
    {
        // Same as BingSystem
    }

    TEST(MOSQNRSYSTEM, GetChild)
    {
        // Same as BingSystem
    }

    TEST(MOSQNRSYSTEM, GetChildren)
    {
        // Same as BingSystem
    }

    TEST(MOSQNRSYSTEM, GetDescendants)
    {
        // Same as BingSystem
    }

    TEST(MOSQNRSYSTEM, GetSiblings)
    {
        // Same as BingSystem
    }

    TEST(MOSQNRSYSTEM, GetNeighbors)
    {
        // Same as BingSystem
    }

    TEST(MOSQNRSYSTEM, FromStringToString)
    {
        QuadKey quadKey(Type::UlpQnr, 0, 0, 0);
        std::string fmt = quadKey.toInternalString();
        EXPECT_EQ("1", fmt);
        QuadKey quadKeyBack = QuadKey::fromInternalString(Type::UlpQnr, fmt);
        EXPECT_EQ(quadKey, quadKeyBack);

        quadKey = QuadKey(Type::UlpQnr, 0, 0, 1);
        fmt = quadKey.toInternalString();
        EXPECT_EQ("4", fmt);
        quadKeyBack = QuadKey::fromInternalString(Type::UlpQnr, fmt);
        EXPECT_EQ(quadKey, quadKeyBack);

        quadKey = QuadKey(Type::UlpQnr, 0, 1, 1);
        fmt = quadKey.toInternalString();
        EXPECT_EQ("5", fmt);
        quadKeyBack = QuadKey::fromInternalString(Type::UlpQnr, fmt);
        EXPECT_EQ(quadKey, quadKeyBack);

        quadKey = QuadKey(Type::UlpQnr, 0, 0, 2);
        fmt = quadKey.toInternalString();
        EXPECT_EQ("16", fmt);
        quadKeyBack = QuadKey::fromInternalString(Type::UlpQnr, fmt);
        EXPECT_EQ(quadKey, quadKeyBack);

        quadKey = QuadKey(Type::UlpQnr, 0, 1, 2);
        fmt = quadKey.toInternalString();
        EXPECT_EQ("17", fmt);
        quadKeyBack = QuadKey::fromInternalString(Type::UlpQnr, fmt);
        EXPECT_EQ(quadKey, quadKeyBack);

        quadKey = QuadKey(Type::UlpQnr, 1, 0, 2);
        fmt = quadKey.toInternalString();
        EXPECT_EQ("20", fmt);
        quadKeyBack = QuadKey::fromInternalString(Type::UlpQnr, fmt);
        EXPECT_EQ(quadKey, quadKeyBack);

        quadKey = QuadKey(Type::UlpQnr, 1, 1, 2);
        fmt = quadKey.toInternalString();
        EXPECT_EQ("21", fmt);
        quadKeyBack = QuadKey::fromInternalString(Type::UlpQnr, fmt);
        EXPECT_EQ(quadKey, quadKeyBack);

        quadKey = QuadKey(Type::UlpQnr, 0, 2, 2);
        fmt = quadKey.toInternalString();
        EXPECT_EQ("18", fmt);
        quadKeyBack = QuadKey::fromInternalString(Type::UlpQnr, fmt);
        EXPECT_EQ(quadKey, quadKeyBack);

        quadKey = QuadKey(Type::UlpQnr, 0, 3, 2);
        fmt = quadKey.toInternalString();
        EXPECT_EQ("19", fmt);
        quadKeyBack = QuadKey::fromInternalString(Type::UlpQnr, fmt);
        EXPECT_EQ(quadKey, quadKeyBack);

        quadKey = QuadKey(Type::UlpQnr, 1, 2, 2);
        fmt = quadKey.toInternalString();
        EXPECT_EQ("22", fmt);
        quadKeyBack = QuadKey::fromInternalString(Type::UlpQnr, fmt);
        EXPECT_EQ(quadKey, quadKeyBack);

        quadKey = QuadKey(Type::UlpQnr, 1, 3, 2);
        fmt = quadKey.toInternalString();
        EXPECT_EQ("23", fmt);
        quadKeyBack = QuadKey::fromInternalString(Type::UlpQnr, fmt);
        EXPECT_EQ(quadKey, quadKeyBack);

        // For Sanity Purposes and to Verify NO Fence Post Erros. Use a bit of
        // brute force.
        std::vector<int> expected(32);
        std::iota(expected.begin(), expected.end(), 64);
        for (std::uint32_t i = 0; i < (8 * 4); ++i) {
            std::uint32_t row = i / 8;
            std::uint32_t col = i % 8;
            quadKey = QuadKey(Type::UlpQnr, row, col, 3);
            fmt = quadKey.toInternalString();

            char buff[3]; // '\0' 64-95
            snprintf(buff, 3, "%d", expected[i]);
            std::string expectedStr(buff);

            EXPECT_EQ(expectedStr, fmt) << "Failed on 64 + " << i << "th key";
            quadKeyBack = QuadKey::fromInternalString(Type::UlpQnr, fmt);
            EXPECT_EQ(quadKey, quadKeyBack) << "Failed on 64 + " << i <<
                "th key";
        }

        quadKey = QuadKey(Type::UlpQnr, 0, 0, 3);
        fmt = quadKey.toInternalString();
        EXPECT_EQ("64", fmt);
        quadKeyBack = QuadKey::fromInternalString(Type::UlpQnr, fmt);
        EXPECT_EQ(quadKey, quadKeyBack);
    }

    TEST(MOSQNRSYSTEM, GetKeyFromLongitudeLatitudeAtDepthToBounds)
    {
        QuadKey computedKey;
        computedKey = QuadKey::getKeyFromLongitudeLatitudeAtDepth(Type::UlpQnr,
            GeoCoordinate2d(Longitude(-180.0), Latitude(-90.0)), 0);
        EXPECT_EQ("1", computedKey.toInternalString());
        computedKey = QuadKey::getKeyFromLongitudeLatitudeAtDepth(Type::UlpQnr,
            GeoCoordinate2d(Longitude(0.0 ), Latitude(0.0)), 0);
        EXPECT_EQ("1", computedKey.toInternalString());

        computedKey = QuadKey::getKeyFromLongitudeLatitudeAtDepth(Type::UlpQnr,
            GeoCoordinate2d(Longitude(-180.0 ), Latitude(-90.0)), 1);
        EXPECT_EQ("4", computedKey.toInternalString());
        computedKey = QuadKey::getKeyFromLongitudeLatitudeAtDepth(Type::UlpQnr,
            GeoCoordinate2d(Longitude(-180.0 ), Latitude(90.0)), 1);
        EXPECT_EQ("4", computedKey.toInternalString());
        computedKey = QuadKey::getKeyFromLongitudeLatitudeAtDepth(Type::UlpQnr,
            GeoCoordinate2d(Longitude(0.1 ), Latitude(-90.0)), 1);
        EXPECT_EQ("5", computedKey.toInternalString());
        computedKey = QuadKey::getKeyFromLongitudeLatitudeAtDepth(Type::UlpQnr,
            GeoCoordinate2d(Longitude(180.0 ), Latitude(90.0)), 1);
        EXPECT_EQ("5", computedKey.toInternalString());

        computedKey = QuadKey::getKeyFromLongitudeLatitudeAtDepth(Type::UlpQnr,
            GeoCoordinate2d(Longitude(-180.0 ), Latitude(-90.0)), 2);
        EXPECT_EQ("16", computedKey.toInternalString());
        computedKey = QuadKey::getKeyFromLongitudeLatitudeAtDepth(Type::UlpQnr,
            GeoCoordinate2d(Longitude(-89.9 ), Latitude(-90.0)), 2);
        EXPECT_EQ("17", computedKey.toInternalString());
        computedKey = QuadKey::getKeyFromLongitudeLatitudeAtDepth(Type::UlpQnr,
            GeoCoordinate2d(Longitude(0.1 ), Latitude(-90.0)), 2);
        EXPECT_EQ("18", computedKey.toInternalString());
        computedKey = QuadKey::getKeyFromLongitudeLatitudeAtDepth(Type::UlpQnr,
            GeoCoordinate2d(Longitude(90.1 ), Latitude(-90.0)), 2);
        EXPECT_EQ("19", computedKey.toInternalString());
        computedKey = QuadKey::getKeyFromLongitudeLatitudeAtDepth(Type::UlpQnr,
            GeoCoordinate2d(Longitude(-180.0 ), Latitude(0.1)), 2);
        EXPECT_EQ("20", computedKey.toInternalString());
        computedKey = QuadKey::getKeyFromLongitudeLatitudeAtDepth(Type::UlpQnr,
            GeoCoordinate2d(Longitude(-89.9 ), Latitude(0.1)), 2);
        EXPECT_EQ("21", computedKey.toInternalString());
        computedKey = QuadKey::getKeyFromLongitudeLatitudeAtDepth(Type::UlpQnr,
            GeoCoordinate2d(Longitude(0.1 ), Latitude(0.1)), 2);
        EXPECT_EQ("22", computedKey.toInternalString());
        computedKey = QuadKey::getKeyFromLongitudeLatitudeAtDepth(Type::UlpQnr,
            GeoCoordinate2d(Longitude(90.1 ), Latitude(0.1)), 2);
        EXPECT_EQ("23", computedKey.toInternalString());
    }

    TEST(MOSQNRSYSTEM, GetKeysFromLongitudeLatitudeBoundingBox)
    {
        std::vector<QuadKey> outKeys;
        QuadKey quadKey;

        // Select Entire Earth
        outKeys = QuadKey::getKeysFromLongitudeLatitudeBoundingBox(Type::UlpQnr,
            GeoCoordinateBoundingBox2d(
                GeoCoordinate2d(Longitude(-180.0), Latitude(-90.0)),
                GeoCoordinate2d(Longitude(180.0), Latitude(90.0))), 0);
        quadKey = QuadKey::fromInternalString(Type::UlpQnr, "1");
        EXPECT_EQ(1, outKeys.size());
        EXPECT_NE(std::find(outKeys.begin(), outKeys.end(), quadKey),
            outKeys.end());

        // Select Very Center of the Earth
        outKeys = QuadKey::getKeysFromLongitudeLatitudeBoundingBox(Type::UlpQnr,
            GeoCoordinateBoundingBox2d(
                GeoCoordinate2d(Longitude(-0.1), Latitude(-0.1)),
                GeoCoordinate2d(Longitude(0.1), Latitude(0.1))), 0);
        quadKey = QuadKey::fromInternalString(Type::UlpQnr, "1");
        EXPECT_EQ(1, outKeys.size());
        EXPECT_NE(std::find(outKeys.begin(), outKeys.end(), quadKey),
            outKeys.end());

        // Select Western Hemisphere
        outKeys = QuadKey::getKeysFromLongitudeLatitudeBoundingBox(Type::UlpQnr,
            GeoCoordinateBoundingBox2d(
                GeoCoordinate2d(Longitude(-180.0), Latitude(-90.0)),
                GeoCoordinate2d(Longitude(0.0), Latitude(90.0))), 1);
        quadKey = QuadKey::fromInternalString(Type::UlpQnr, "4");
        EXPECT_EQ(1, outKeys.size());
        EXPECT_NE(std::find(outKeys.begin(), outKeys.end(), quadKey),
            outKeys.end());

        // Select Eastern Hemisphere
        outKeys = QuadKey::getKeysFromLongitudeLatitudeBoundingBox(Type::UlpQnr,
            GeoCoordinateBoundingBox2d(
                GeoCoordinate2d(Longitude(0.1), Latitude(-90.0)),
                GeoCoordinate2d(Longitude(180), Latitude(90.0))), 1);
        quadKey = QuadKey::fromInternalString(Type::UlpQnr, "5");
        EXPECT_EQ(1, outKeys.size());
        EXPECT_NE(std::find(outKeys.begin(), outKeys.end(), quadKey),
            outKeys.end());

        // Select Entire Planet
        outKeys = QuadKey::getKeysFromLongitudeLatitudeBoundingBox(Type::UlpQnr,
            GeoCoordinateBoundingBox2d(
                GeoCoordinate2d(Longitude(-180.0), Latitude(-90.0)),
                GeoCoordinate2d(Longitude(180), Latitude(90.0))), 1);
        QuadKey quadKeya = QuadKey::fromInternalString(Type::UlpQnr, "4");
        QuadKey quadKeyb = QuadKey::fromInternalString(Type::UlpQnr, "5");
        EXPECT_EQ(2, outKeys.size());
        EXPECT_NE(std::find(outKeys.begin(), outKeys.end(), quadKeya),
            outKeys.end());
        EXPECT_NE(std::find(outKeys.begin(), outKeys.end(), quadKeyb),
            outKeys.end());

        // Select South West Corner
        outKeys = QuadKey::getKeysFromLongitudeLatitudeBoundingBox(Type::UlpQnr,
            GeoCoordinateBoundingBox2d(
                GeoCoordinate2d(Longitude(-180.0), Latitude(-90.0)),
                GeoCoordinate2d(Longitude(-90.0), Latitude(0.0))), 2);
        quadKey = QuadKey::fromInternalString(Type::UlpQnr, "16");
        EXPECT_EQ(1, outKeys.size());
        EXPECT_NE(std::find(outKeys.begin(), outKeys.end(), quadKey),
            outKeys.end());

        // Select South America
        outKeys = QuadKey::getKeysFromLongitudeLatitudeBoundingBox(Type::UlpQnr,
            GeoCoordinateBoundingBox2d(
                GeoCoordinate2d(Longitude(-89.9), Latitude(-90.0)),
                GeoCoordinate2d(Longitude(0.0), Latitude(0.0))), 2);
        quadKey = QuadKey::fromInternalString(Type::UlpQnr, "17");
        EXPECT_EQ(1, outKeys.size());
        EXPECT_NE(std::find(outKeys.begin(), outKeys.end(), quadKey),
            outKeys.end());

        // Select North West Corner
        outKeys = QuadKey::getKeysFromLongitudeLatitudeBoundingBox(Type::UlpQnr,
            GeoCoordinateBoundingBox2d(
                GeoCoordinate2d(Longitude(-180.0), Latitude(0.1)),
                GeoCoordinate2d(Longitude(-90.0), Latitude(90.0))), 2);
        quadKey = QuadKey::fromInternalString(Type::UlpQnr, "20");
        EXPECT_EQ(1, outKeys.size());
        EXPECT_NE(std::find(outKeys.begin(), outKeys.end(), quadKey),
            outKeys.end());

        // Select Greenland
        outKeys = QuadKey::getKeysFromLongitudeLatitudeBoundingBox(Type::UlpQnr,
            GeoCoordinateBoundingBox2d(
                GeoCoordinate2d(Longitude(-89.9), Latitude(0.1)),
                GeoCoordinate2d(Longitude(0.0), Latitude(90.0))), 2);
        quadKey = QuadKey::fromInternalString(Type::UlpQnr, "21");
        EXPECT_EQ(1, outKeys.size());
        EXPECT_NE(std::find(outKeys.begin(), outKeys.end(), quadKey),
            outKeys.end());

        // Select South Pole
        outKeys = QuadKey::getKeysFromLongitudeLatitudeBoundingBox(Type::UlpQnr,
            GeoCoordinateBoundingBox2d(
                GeoCoordinate2d(Longitude(0.1), Latitude(-90.0)),
                GeoCoordinate2d(Longitude(90.0), Latitude(0.0))), 2);
        quadKey = QuadKey::fromInternalString(Type::UlpQnr, "18");
        EXPECT_EQ(1, outKeys.size());
        EXPECT_NE(std::find(outKeys.begin(), outKeys.end(), quadKey),
            outKeys.end());

        // Select South East Corner
        outKeys = QuadKey::getKeysFromLongitudeLatitudeBoundingBox(Type::UlpQnr,
            GeoCoordinateBoundingBox2d(
                GeoCoordinate2d(Longitude(90.1), Latitude(-90.0)),
                GeoCoordinate2d(Longitude(180.0), Latitude(0.0))), 2);
        quadKey = QuadKey::fromInternalString(Type::UlpQnr, "19");
        EXPECT_EQ(1, outKeys.size());
        EXPECT_NE(std::find(outKeys.begin(), outKeys.end(), quadKey),
            outKeys.end());

        // Select Over Europe
        outKeys = QuadKey::getKeysFromLongitudeLatitudeBoundingBox(Type::UlpQnr,
            GeoCoordinateBoundingBox2d(
                GeoCoordinate2d(Longitude(0.1), Latitude(0.1)),
                GeoCoordinate2d(Longitude(90.0), Latitude(90.0))), 2);
        quadKey = QuadKey::fromInternalString(Type::UlpQnr, "22");
        EXPECT_EQ(1, outKeys.size());
        EXPECT_NE(std::find(outKeys.begin(), outKeys.end(), quadKey),
            outKeys.end());

        // Select North East Corner
        outKeys = QuadKey::getKeysFromLongitudeLatitudeBoundingBox(Type::UlpQnr,
            GeoCoordinateBoundingBox2d(
                GeoCoordinate2d(Longitude(90.1), Latitude(0.1)),
                GeoCoordinate2d(Longitude(180.0), Latitude(90.0))), 2);
        quadKey = QuadKey::fromInternalString(Type::UlpQnr, "23");
        EXPECT_EQ(1, outKeys.size());
        EXPECT_NE(std::find(outKeys.begin(), outKeys.end(), quadKey),
            outKeys.end());

        // Select Entire Map
        outKeys = QuadKey::getKeysFromLongitudeLatitudeBoundingBox(Type::UlpQnr,
            GeoCoordinateBoundingBox2d(
                GeoCoordinate2d(Longitude(-179.9), Latitude(-89.9)),
                GeoCoordinate2d(Longitude(90.1), Latitude(0.1))), 2);
        QuadKey quadKey0 = QuadKey::fromInternalString(Type::UlpQnr, "16");
        QuadKey quadKey1 = QuadKey::fromInternalString(Type::UlpQnr, "17");
        QuadKey quadKey2 = QuadKey::fromInternalString(Type::UlpQnr, "18");
        QuadKey quadKey3 = QuadKey::fromInternalString(Type::UlpQnr, "19");
        QuadKey quadKey4 = QuadKey::fromInternalString(Type::UlpQnr, "20");
        QuadKey quadKey5 = QuadKey::fromInternalString(Type::UlpQnr, "21");
        QuadKey quadKey6 = QuadKey::fromInternalString(Type::UlpQnr, "22");
        QuadKey quadKey7 = QuadKey::fromInternalString(Type::UlpQnr, "23");
        EXPECT_EQ(8, outKeys.size());
        EXPECT_NE(std::find(outKeys.begin(), outKeys.end(), quadKey0),
            outKeys.end());
        EXPECT_NE(std::find(outKeys.begin(), outKeys.end(), quadKey1),
            outKeys.end());
        EXPECT_NE(std::find(outKeys.begin(), outKeys.end(), quadKey2),
            outKeys.end());
        EXPECT_NE(std::find(outKeys.begin(), outKeys.end(), quadKey3),
            outKeys.end());
        EXPECT_NE(std::find(outKeys.begin(), outKeys.end(), quadKey4),
            outKeys.end());
        EXPECT_NE(std::find(outKeys.begin(), outKeys.end(), quadKey5),
            outKeys.end());
        EXPECT_NE(std::find(outKeys.begin(), outKeys.end(), quadKey6),
            outKeys.end());
        EXPECT_NE(std::find(outKeys.begin(), outKeys.end(), quadKey7),
            outKeys.end());
    }

    TEST(MOSQNRSYSTEM, SelectedCities)
    {
        // TODO: Implement Tests. Taken from Earthscape. No tests there.
    }
}

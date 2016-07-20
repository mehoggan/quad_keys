#include <gtest/gtest.h>

#include "QuadKey/GeoCoordinate2d.h"
#include "QuadKey/QuadKey.h"

#include <iostream>

namespace QuadKeys
{
    class OsGeoSystemTest : public ::testing::Test
    {
    protected:
        virtual void SetUp() {}
        virtual void TearDown() {}
    };

    TEST(OSGEOSYSTEM, IsValid)
    {
        // Same as BingSystem
    }

    TEST(OSGEOSYSTEM, IsRootKey)
    {
        // Same as BingSystem
    }

    TEST(OSGEOSYSTEM, GetParent)
    {
        // Same as BingSystem
    }

    TEST(OSGEOSYSTEM, IsMyAncestor)
    {
        // Same as BingSystem
    }

    TEST(OSGEOSYSTEM, GetAncestor)
    {
        // Same as BingSystem
    }

    TEST(OSGEOSYSTEM, GetChild)
    {
        // Same as BingSystem
    }

    TEST(OSGEOSYSTEM, GetChildren)
    {
        // Same as BingSystem
    }

    TEST(OSGEOSYSTEM, GetDescendants)
    {
        // Same as BingSystem
    }

    TEST(OSGEOSYSTEM, GetSiblings)
    {
        // Same as BingSystem
    }

    TEST(OSGEOSYSTEM, GetNeighbors)
    {
        // Same as BingSystem
    }

    TEST(OSGEOSYSTEM, FromStringToString)
    {
        // Same thing as OsGeo Except for it allows for negative 1 in both the
        // rows and the columns. depth/col/row.
        QuadKey quadKey(Type::OsGeo, 3, 3, 2);
        std::string fmt = quadKey.toInternalString();
        EXPECT_EQ("2/3/3", fmt);
        QuadKey quadKeyBack = QuadKey::fromInternalString(Type::OsGeo, fmt);
        EXPECT_EQ(quadKey, quadKeyBack);

        fmt = "0/-1/-1";
        quadKeyBack = QuadKey::fromInternalString(Type::OsGeo, fmt);
        EXPECT_EQ(QuadKey(Type::OsGeo, 0, 0, 0), quadKeyBack);

        fmt = "1/1/-1";
        quadKeyBack = QuadKey::fromInternalString(Type::OsGeo, fmt);
        EXPECT_EQ(QuadKey(Type::OsGeo, 0, 1, 1), quadKeyBack);

        fmt = "1/-1/1";
        quadKeyBack = QuadKey::fromInternalString(Type::OsGeo, fmt);
        EXPECT_EQ(QuadKey(Type::OsGeo, 1, 0, 1), quadKeyBack);
    }

    TEST(OSGEOSYSTEM, GetKeyFromLongitudeLatitudeAtDepthToBounds)
    {
        QuadKey quadKey;
        GeoCoordinateBoundingBox2d bbox;

        // Inclusion here consists of upper right. In the case along bottom or
        // left Inclusion points the opposite direction.
        //    X------X------X ur
        //    |      |      |
        //    |      |      |
        //    X------X------X
        //    |      |      |
        //    |      |      |
        //    X------X------X
        // Note that in this system bounds consist of all 4 sides, so two quads
        // will share the same boundary.
        quadKey = QuadKey::getKeyFromLongitudeLatitudeAtDepth(Type::OsGeo,
            GeoCoordinate2d(Longitude(-180.0), Latitude(+85.05113877)), 0);
        EXPECT_EQ(QuadKey(Type::OsGeo, 0, 0, 0), quadKey);
        quadKey = QuadKey::getKeyFromLongitudeLatitudeAtDepth(Type::OsGeo,
            GeoCoordinate2d(Longitude(+180.0), Latitude(+85.05113877)), 0);
        EXPECT_EQ(QuadKey(Type::OsGeo, 0, 0, 0), quadKey);
        quadKey = QuadKey::getKeyFromLongitudeLatitudeAtDepth(Type::OsGeo,
            GeoCoordinate2d(Longitude(+180.0), Latitude(-85.05113877)), 0);
        EXPECT_EQ(QuadKey(Type::OsGeo, 0, 0, 0), quadKey);
        quadKey = QuadKey::getKeyFromLongitudeLatitudeAtDepth(Type::OsGeo,
            GeoCoordinate2d(Longitude(-180.0), Latitude(-85.05113877)), 0);
        EXPECT_EQ(QuadKey(Type::OsGeo, 0, 0, 0), quadKey);
        quadKey.getGeoCoordinateBounds2d(bbox);
        EXPECT_TRUE(bbox.lowerLeft().near(GeoCoordinate2d(
            Longitude(-180.0), Latitude(-85.05113877)), 1e-4)) << "Actual = "
            << bbox.lowerLeft() << " for " << quadKey;
        EXPECT_TRUE(bbox.upperRight().near(GeoCoordinate2d(
            Longitude(+180.0), Latitude(+85.05113877)), 1e-4)) << "Actual = "
            << bbox.upperRight() << " for " << quadKey;

        quadKey = QuadKey::getKeyFromLongitudeLatitudeAtDepth(Type::OsGeo,
            GeoCoordinate2d(Longitude(+0.0), Latitude(+0.00000000)), 0);
        EXPECT_EQ(QuadKey(Type::OsGeo, 0, 0, 0), quadKey);

        quadKey = QuadKey::getKeyFromLongitudeLatitudeAtDepth(Type::OsGeo,
            GeoCoordinate2d(Longitude(-180.0), Latitude(+85.05113877)), 1);
        EXPECT_EQ(QuadKey(Type::OsGeo, 1, 0, 1), quadKey);
        quadKey.getGeoCoordinateBounds2d(bbox);
        EXPECT_TRUE(bbox.lowerLeft().near(GeoCoordinate2d(
            Longitude(-180.0), Latitude(+0.00000000)), 1e-4)) << "Actual = "
            << bbox.lowerLeft() << " for " << quadKey;
        EXPECT_TRUE(bbox.upperRight().near(GeoCoordinate2d(
            Longitude(+0.0), Latitude(+85.05113877)), 1e-4)) << "Actual = "
            << bbox.upperRight() << " for " << quadKey;

        quadKey = QuadKey::getKeyFromLongitudeLatitudeAtDepth(Type::OsGeo,
            GeoCoordinate2d(Longitude(+180.0), Latitude(+85.05113877)), 1);
        EXPECT_EQ(QuadKey(Type::OsGeo, 1, 1, 1), quadKey);
        quadKey.getGeoCoordinateBounds2d(bbox);
        EXPECT_TRUE(bbox.lowerLeft().near(GeoCoordinate2d(
            Longitude(+0.0), Latitude(+0.00000000)), 1e-4)) << "Actual = "
            << bbox.lowerLeft() << " for " << quadKey;
        EXPECT_TRUE(bbox.upperRight().near(GeoCoordinate2d(
            Longitude(+180.0), Latitude(+85.05113877)), 1e-4)) << "Actual = "
            << bbox.upperRight() << " for " << quadKey;

        quadKey = QuadKey::getKeyFromLongitudeLatitudeAtDepth(Type::OsGeo,
            GeoCoordinate2d(Longitude(+180.0), Latitude(-85.05113877)), 1);
        EXPECT_EQ(QuadKey(Type::OsGeo, 0, 1, 1), quadKey);
        quadKey.getGeoCoordinateBounds2d(bbox);
        EXPECT_TRUE(bbox.lowerLeft().near(GeoCoordinate2d(
            Longitude(+0.0), Latitude(-85.05113877)), 1e-4)) << "Actual = "
            << bbox.lowerLeft() << " for " << quadKey;
        EXPECT_TRUE(bbox.upperRight().near(GeoCoordinate2d(
            Longitude(+180.0), Latitude(+0.00000000)), 1e-4)) << "Actual = "
            << bbox.upperRight() << " for " << quadKey;

        quadKey = QuadKey::getKeyFromLongitudeLatitudeAtDepth(Type::OsGeo,
            GeoCoordinate2d(Longitude(-180.0), Latitude(-85.05113877)), 1);
        EXPECT_EQ(QuadKey(Type::OsGeo, 0, 0, 1), quadKey);
        quadKey.getGeoCoordinateBounds2d(bbox);
        EXPECT_TRUE(bbox.lowerLeft().near(GeoCoordinate2d(
            Longitude(-180.0), Latitude(-85.05113877)), 1e-4)) << "Actual = "
            << bbox.lowerLeft() << " for " << quadKey;
        EXPECT_TRUE(bbox.upperRight().near(GeoCoordinate2d(
            Longitude(+0.0), Latitude(+0.00000000)), 1e-4)) << "Actual = "
            << bbox.upperRight() << " for " << quadKey;

        quadKey = QuadKey::getKeyFromLongitudeLatitudeAtDepth(Type::OsGeo,
            GeoCoordinate2d(Longitude(-180.0), Latitude(+0.00000000)), 1);
        EXPECT_EQ(QuadKey(Type::OsGeo, 0, 0, 1), quadKey);
        quadKey = QuadKey::getKeyFromLongitudeLatitudeAtDepth(Type::OsGeo,
            GeoCoordinate2d(Longitude(+0.0), Latitude(+85.05113877)), 1);
        EXPECT_EQ(QuadKey(Type::OsGeo, 1, 0, 1), quadKey);
        quadKey = QuadKey::getKeyFromLongitudeLatitudeAtDepth(Type::OsGeo,
            GeoCoordinate2d(Longitude(+180.0), Latitude(+0.00000000)), 1);
        EXPECT_EQ(QuadKey(Type::OsGeo, 0, 1, 1), quadKey);
        quadKey = QuadKey::getKeyFromLongitudeLatitudeAtDepth(Type::OsGeo,
            GeoCoordinate2d(Longitude(+0.0), Latitude(-85.05113877)), 1);
        EXPECT_EQ(QuadKey(Type::OsGeo, 0, 0, 1), quadKey);
        quadKey = QuadKey::getKeyFromLongitudeLatitudeAtDepth(Type::OsGeo,
            GeoCoordinate2d(Longitude(+0.0), Latitude(+0.00000000)), 1);
        EXPECT_EQ(QuadKey(Type::OsGeo, 0, 0, 1), quadKey);

        // Note at depth 2 because of the Mercator projection the lines
        // of latitude are note perfect divisions by 2.
        quadKey = QuadKey::getKeyFromLongitudeLatitudeAtDepth(Type::OsGeo,
            GeoCoordinate2d(Longitude(-180.0), Latitude(-85.05113877)), 2);
        EXPECT_EQ(QuadKey(Type::OsGeo, 0, 0, 2), quadKey);
        quadKey = QuadKey::getKeyFromLongitudeLatitudeAtDepth(Type::OsGeo,
            GeoCoordinate2d(Longitude(-180.0), Latitude(-66.5133)), 2);
        EXPECT_EQ(QuadKey(Type::OsGeo, 0, 0, 2), quadKey);
        quadKey = QuadKey::getKeyFromLongitudeLatitudeAtDepth(Type::OsGeo,
            GeoCoordinate2d(Longitude(-180.0), Latitude(-66.5132)), 2);
        EXPECT_EQ(QuadKey(Type::OsGeo, 1, 0, 2), quadKey);
        quadKey = QuadKey::getKeyFromLongitudeLatitudeAtDepth(Type::OsGeo,
            GeoCoordinate2d(Longitude(-180.0), Latitude(+0.1)), 2);
        EXPECT_EQ(QuadKey(Type::OsGeo, 2, 0, 2), quadKey);
        quadKey = QuadKey::getKeyFromLongitudeLatitudeAtDepth(Type::OsGeo,
            GeoCoordinate2d(Longitude(-180.0), Latitude(+66.5132)), 2);
        EXPECT_EQ(QuadKey(Type::OsGeo, 2, 0, 2), quadKey);
        quadKey = QuadKey::getKeyFromLongitudeLatitudeAtDepth(Type::OsGeo,
            GeoCoordinate2d(Longitude(-180.0), Latitude(+66.5133)), 2);
        EXPECT_EQ(QuadKey(Type::OsGeo, 3, 0, 2), quadKey);
        quadKey = QuadKey::getKeyFromLongitudeLatitudeAtDepth(Type::OsGeo,
            GeoCoordinate2d(Longitude(-180.0), Latitude(+85.05113877)), 2);
        EXPECT_EQ(QuadKey(Type::OsGeo, 3, 0, 2), quadKey);
        quadKey = QuadKey::getKeyFromLongitudeLatitudeAtDepth(Type::OsGeo,
            GeoCoordinate2d(Longitude(-90.0), Latitude(-85.05113877)), 2);
        EXPECT_EQ(QuadKey(Type::OsGeo, 0, 0, 2), quadKey);
        quadKey = QuadKey::getKeyFromLongitudeLatitudeAtDepth(Type::OsGeo,
            GeoCoordinate2d(Longitude(-90.0), Latitude(-66.5133)), 2);
        EXPECT_EQ(QuadKey(Type::OsGeo, 0, 0, 2), quadKey);
        quadKey = QuadKey::getKeyFromLongitudeLatitudeAtDepth(Type::OsGeo,
            GeoCoordinate2d(Longitude(-90.0), Latitude(-66.5132)), 2);
        EXPECT_EQ(QuadKey(Type::OsGeo, 1, 0, 2), quadKey);
        quadKey = QuadKey::getKeyFromLongitudeLatitudeAtDepth(Type::OsGeo,
            GeoCoordinate2d(Longitude(-90.0), Latitude(+0.1)), 2);
        EXPECT_EQ(QuadKey(Type::OsGeo, 2, 0, 2), quadKey);
        quadKey = QuadKey::getKeyFromLongitudeLatitudeAtDepth(Type::OsGeo,
            GeoCoordinate2d(Longitude(-90.0), Latitude(+66.5132)), 2);
        EXPECT_EQ(QuadKey(Type::OsGeo, 2, 0, 2), quadKey);
        quadKey = QuadKey::getKeyFromLongitudeLatitudeAtDepth(Type::OsGeo,
            GeoCoordinate2d(Longitude(-90.0), Latitude(+66.5133)), 2);
        EXPECT_EQ(QuadKey(Type::OsGeo, 3, 0, 2), quadKey);
        quadKey = QuadKey::getKeyFromLongitudeLatitudeAtDepth(Type::OsGeo,
            GeoCoordinate2d(Longitude(-90.0), Latitude(+85.05113877)), 2);
        EXPECT_EQ(QuadKey(Type::OsGeo, 3, 0, 2), quadKey);
        quadKey = QuadKey::getKeyFromLongitudeLatitudeAtDepth(Type::OsGeo,
            GeoCoordinate2d(Longitude(-89.9), Latitude(-85.05113877)), 2);
        EXPECT_EQ(QuadKey(Type::OsGeo, 0, 1, 2), quadKey);
        quadKey = QuadKey::getKeyFromLongitudeLatitudeAtDepth(Type::OsGeo,
            GeoCoordinate2d(Longitude(-89.9), Latitude(-66.5133)), 2);
        EXPECT_EQ(QuadKey(Type::OsGeo, 0, 1, 2), quadKey);
        quadKey = QuadKey::getKeyFromLongitudeLatitudeAtDepth(Type::OsGeo,
            GeoCoordinate2d(Longitude(-89.9), Latitude(-66.5132)), 2);
        EXPECT_EQ(QuadKey(Type::OsGeo, 1, 1, 2), quadKey);
        quadKey = QuadKey::getKeyFromLongitudeLatitudeAtDepth(Type::OsGeo,
            GeoCoordinate2d(Longitude(-89.9), Latitude(+0.1)), 2);
        EXPECT_EQ(QuadKey(Type::OsGeo, 2, 1, 2), quadKey);
        quadKey = QuadKey::getKeyFromLongitudeLatitudeAtDepth(Type::OsGeo,
            GeoCoordinate2d(Longitude(-89.9), Latitude(+66.5132)), 2);
        EXPECT_EQ(QuadKey(Type::OsGeo, 2, 1, 2), quadKey);
        quadKey = QuadKey::getKeyFromLongitudeLatitudeAtDepth(Type::OsGeo,
            GeoCoordinate2d(Longitude(-89.9), Latitude(+66.5133)), 2);
        EXPECT_EQ(QuadKey(Type::OsGeo, 3, 1, 2), quadKey);
        quadKey = QuadKey::getKeyFromLongitudeLatitudeAtDepth(Type::OsGeo,
            GeoCoordinate2d(Longitude(-89.9), Latitude(+85.05113877)), 2);
        EXPECT_EQ(QuadKey(Type::OsGeo, 3, 1, 2), quadKey);
        quadKey = QuadKey::getKeyFromLongitudeLatitudeAtDepth(Type::OsGeo,
            GeoCoordinate2d(Longitude(+0.0), Latitude(-85.05113877)), 2);
        EXPECT_EQ(QuadKey(Type::OsGeo, 0, 1, 2), quadKey);
        quadKey = QuadKey::getKeyFromLongitudeLatitudeAtDepth(Type::OsGeo,
            GeoCoordinate2d(Longitude(+0.0), Latitude(-66.5133)), 2);
        EXPECT_EQ(QuadKey(Type::OsGeo, 0, 1, 2), quadKey);
        quadKey = QuadKey::getKeyFromLongitudeLatitudeAtDepth(Type::OsGeo,
            GeoCoordinate2d(Longitude(+0.0), Latitude(-66.5132)), 2);
        EXPECT_EQ(QuadKey(Type::OsGeo, 1, 1, 2), quadKey);
        quadKey = QuadKey::getKeyFromLongitudeLatitudeAtDepth(Type::OsGeo,
            GeoCoordinate2d(Longitude(+0.0), Latitude(+0.1)), 2);
        EXPECT_EQ(QuadKey(Type::OsGeo, 2, 1, 2), quadKey);
        quadKey = QuadKey::getKeyFromLongitudeLatitudeAtDepth(Type::OsGeo,
            GeoCoordinate2d(Longitude(+0.0), Latitude(+66.5132)), 2);
        EXPECT_EQ(QuadKey(Type::OsGeo, 2, 1, 2), quadKey);
        quadKey = QuadKey::getKeyFromLongitudeLatitudeAtDepth(Type::OsGeo,
            GeoCoordinate2d(Longitude(+0.0), Latitude(+66.5133)), 2);
        EXPECT_EQ(QuadKey(Type::OsGeo, 3, 1, 2), quadKey);
        quadKey = QuadKey::getKeyFromLongitudeLatitudeAtDepth(Type::OsGeo,
            GeoCoordinate2d(Longitude(+0.0), Latitude(+85.05113877)), 2);
        EXPECT_EQ(QuadKey(Type::OsGeo, 3, 1, 2), quadKey);
        quadKey = QuadKey::getKeyFromLongitudeLatitudeAtDepth(Type::OsGeo,
            GeoCoordinate2d(Longitude(+0.1), Latitude(-85.05113877)), 2);
        EXPECT_EQ(QuadKey(Type::OsGeo, 0, 2, 2), quadKey);
        quadKey = QuadKey::getKeyFromLongitudeLatitudeAtDepth(Type::OsGeo,
            GeoCoordinate2d(Longitude(+0.1), Latitude(-66.5133)), 2);
        EXPECT_EQ(QuadKey(Type::OsGeo, 0, 2, 2), quadKey);
        quadKey = QuadKey::getKeyFromLongitudeLatitudeAtDepth(Type::OsGeo,
            GeoCoordinate2d(Longitude(+0.1), Latitude(-66.5132)), 2);
        EXPECT_EQ(QuadKey(Type::OsGeo, 1, 2, 2), quadKey);
        quadKey = QuadKey::getKeyFromLongitudeLatitudeAtDepth(Type::OsGeo,
            GeoCoordinate2d(Longitude(+0.1), Latitude(+0.1)), 2);
        EXPECT_EQ(QuadKey(Type::OsGeo, 2, 2, 2), quadKey);
        quadKey = QuadKey::getKeyFromLongitudeLatitudeAtDepth(Type::OsGeo,
            GeoCoordinate2d(Longitude(+0.1), Latitude(+66.5132)), 2);
        EXPECT_EQ(QuadKey(Type::OsGeo, 2, 2, 2), quadKey);
        quadKey = QuadKey::getKeyFromLongitudeLatitudeAtDepth(Type::OsGeo,
            GeoCoordinate2d(Longitude(+0.1), Latitude(+66.5133)), 2);
        EXPECT_EQ(QuadKey(Type::OsGeo, 3, 2, 2), quadKey);
        quadKey = QuadKey::getKeyFromLongitudeLatitudeAtDepth(Type::OsGeo,
            GeoCoordinate2d(Longitude(+0.1), Latitude(+85.05113877)), 2);
        EXPECT_EQ(QuadKey(Type::OsGeo, 3, 2, 2), quadKey);
        quadKey = QuadKey::getKeyFromLongitudeLatitudeAtDepth(Type::OsGeo,
            GeoCoordinate2d(Longitude(+90.0), Latitude(-85.05113877)), 2);
        EXPECT_EQ(QuadKey(Type::OsGeo, 0, 2, 2), quadKey);
        quadKey = QuadKey::getKeyFromLongitudeLatitudeAtDepth(Type::OsGeo,
            GeoCoordinate2d(Longitude(+90.0), Latitude(-66.5133)), 2);
        EXPECT_EQ(QuadKey(Type::OsGeo, 0, 2, 2), quadKey);
        quadKey = QuadKey::getKeyFromLongitudeLatitudeAtDepth(Type::OsGeo,
            GeoCoordinate2d(Longitude(+90.0), Latitude(-66.5132)), 2);
        EXPECT_EQ(QuadKey(Type::OsGeo, 1, 2, 2), quadKey);
        quadKey = QuadKey::getKeyFromLongitudeLatitudeAtDepth(Type::OsGeo,
            GeoCoordinate2d(Longitude(+90.0), Latitude(+0.1)), 2);
        EXPECT_EQ(QuadKey(Type::OsGeo, 2, 2, 2), quadKey);
        quadKey = QuadKey::getKeyFromLongitudeLatitudeAtDepth(Type::OsGeo,
            GeoCoordinate2d(Longitude(+90.0), Latitude(+66.5132)), 2);
        EXPECT_EQ(QuadKey(Type::OsGeo, 2, 2, 2), quadKey);
        quadKey = QuadKey::getKeyFromLongitudeLatitudeAtDepth(Type::OsGeo,
            GeoCoordinate2d(Longitude(+90.0), Latitude(+66.5133)), 2);
        EXPECT_EQ(QuadKey(Type::OsGeo, 3, 2, 2), quadKey);
        quadKey = QuadKey::getKeyFromLongitudeLatitudeAtDepth(Type::OsGeo,
            GeoCoordinate2d(Longitude(+90.0), Latitude(+85.05113877)), 2);
        EXPECT_EQ(QuadKey(Type::OsGeo, 3, 2, 2), quadKey);
        quadKey = QuadKey::getKeyFromLongitudeLatitudeAtDepth(Type::OsGeo,
            GeoCoordinate2d(Longitude(+90.1), Latitude(-85.05113877)), 2);
        EXPECT_EQ(QuadKey(Type::OsGeo, 0, 3, 2), quadKey);
        quadKey = QuadKey::getKeyFromLongitudeLatitudeAtDepth(Type::OsGeo,
            GeoCoordinate2d(Longitude(+90.1), Latitude(-66.5133)), 2);
        EXPECT_EQ(QuadKey(Type::OsGeo, 0, 3, 2), quadKey);
        quadKey = QuadKey::getKeyFromLongitudeLatitudeAtDepth(Type::OsGeo,
            GeoCoordinate2d(Longitude(+90.1), Latitude(-66.5132)), 2);
        EXPECT_EQ(QuadKey(Type::OsGeo, 1, 3, 2), quadKey);
        quadKey = QuadKey::getKeyFromLongitudeLatitudeAtDepth(Type::OsGeo,
            GeoCoordinate2d(Longitude(+90.1), Latitude(+0.1)), 2);
        EXPECT_EQ(QuadKey(Type::OsGeo, 2, 3, 2), quadKey);
        quadKey = QuadKey::getKeyFromLongitudeLatitudeAtDepth(Type::OsGeo,
            GeoCoordinate2d(Longitude(+90.1), Latitude(+66.5132)), 2);
        EXPECT_EQ(QuadKey(Type::OsGeo, 2, 3, 2), quadKey);
        quadKey = QuadKey::getKeyFromLongitudeLatitudeAtDepth(Type::OsGeo,
            GeoCoordinate2d(Longitude(+90.1), Latitude(+66.5133)), 2);
        EXPECT_EQ(QuadKey(Type::OsGeo, 3, 3, 2), quadKey);
        quadKey = QuadKey::getKeyFromLongitudeLatitudeAtDepth(Type::OsGeo,
            GeoCoordinate2d(Longitude(+90.1), Latitude(+85.05113877)), 2);
        EXPECT_EQ(QuadKey(Type::OsGeo, 3, 3, 2), quadKey);
        quadKey = QuadKey::getKeyFromLongitudeLatitudeAtDepth(Type::OsGeo,
            GeoCoordinate2d(Longitude(+180.0), Latitude(-85.05113877)), 2);
        EXPECT_EQ(QuadKey(Type::OsGeo, 0, 3, 2), quadKey);
        quadKey = QuadKey::getKeyFromLongitudeLatitudeAtDepth(Type::OsGeo,
            GeoCoordinate2d(Longitude(+180.0), Latitude(-66.5133)), 2);
        EXPECT_EQ(QuadKey(Type::OsGeo, 0, 3, 2), quadKey);
        quadKey = QuadKey::getKeyFromLongitudeLatitudeAtDepth(Type::OsGeo,
            GeoCoordinate2d(Longitude(+180.0), Latitude(-66.5132)), 2);
        EXPECT_EQ(QuadKey(Type::OsGeo, 1, 3, 2), quadKey);
        quadKey = QuadKey::getKeyFromLongitudeLatitudeAtDepth(Type::OsGeo,
            GeoCoordinate2d(Longitude(+180.0), Latitude(+0.1)), 2);
        EXPECT_EQ(QuadKey(Type::OsGeo, 2, 3, 2), quadKey);
        quadKey = QuadKey::getKeyFromLongitudeLatitudeAtDepth(Type::OsGeo,
            GeoCoordinate2d(Longitude(+180.0), Latitude(+66.5132)), 2);
        EXPECT_EQ(QuadKey(Type::OsGeo, 2, 3, 2), quadKey);
        quadKey = QuadKey::getKeyFromLongitudeLatitudeAtDepth(Type::OsGeo,
            GeoCoordinate2d(Longitude(+180.0), Latitude(+66.5133)), 2);
        EXPECT_EQ(QuadKey(Type::OsGeo, 3, 3, 2), quadKey);
        quadKey = QuadKey::getKeyFromLongitudeLatitudeAtDepth(Type::OsGeo,
            GeoCoordinate2d(Longitude(+180.0), Latitude(+85.05113877)), 2);
        EXPECT_EQ(QuadKey(Type::OsGeo, 3, 3, 2), quadKey);
    }

    TEST(OSGEOSYSTEM, GetKeysFromLongitudeLatitudeBoundingBox)
    {
        std::vector<QuadKey> quadKeys;

        quadKeys = QuadKey::getKeysFromLongitudeLatitudeBoundingBox(
            Type::OsGeo, GeoCoordinateBoundingBox2d(
            GeoCoordinate2d(Longitude(+0.0), Latitude(-0.10000000)),
            GeoCoordinate2d(Longitude(+0.1), Latitude(+0.10000000))),
            0);
        EXPECT_EQ(1u, quadKeys.size());
        EXPECT_NE(std::find(quadKeys.begin(), quadKeys.end(), QuadKey(
            Type::OsGeo, 0, 0, 0)), quadKeys.end());

        quadKeys = QuadKey::getKeysFromLongitudeLatitudeBoundingBox(
            Type::OsGeo, GeoCoordinateBoundingBox2d(
            GeoCoordinate2d(Longitude(-180.0), Latitude(-85.05113877)),
            GeoCoordinate2d(Longitude(+180.0), Latitude(+85.05113877))),
            1);
        EXPECT_EQ(4u, quadKeys.size());
        EXPECT_NE(std::find(quadKeys.begin(), quadKeys.end(), QuadKey(
            Type::OsGeo, 0, 0, 1)), quadKeys.end());
        EXPECT_NE(std::find(quadKeys.begin(), quadKeys.end(), QuadKey(
            Type::OsGeo, 0, 1, 1)), quadKeys.end());
        EXPECT_NE(std::find(quadKeys.begin(), quadKeys.end(), QuadKey(
            Type::OsGeo, 1, 0, 1)), quadKeys.end());
        EXPECT_NE(std::find(quadKeys.begin(), quadKeys.end(), QuadKey(
            Type::OsGeo, 1, 1, 1)), quadKeys.end());

        quadKeys = QuadKey::getKeysFromLongitudeLatitudeBoundingBox(
            Type::OsGeo, GeoCoordinateBoundingBox2d(
            GeoCoordinate2d(Longitude(-180.0), Latitude(-85.05113877)),
            GeoCoordinate2d(Longitude(+0.0), Latitude(+85.05113877))),
            1);
        EXPECT_EQ(2u, quadKeys.size());
        EXPECT_NE(std::find(quadKeys.begin(), quadKeys.end(), QuadKey(
            Type::OsGeo, 1, 0, 1)), quadKeys.end());
        EXPECT_NE(std::find(quadKeys.begin(), quadKeys.end(), QuadKey(
            Type::OsGeo, 0, 0, 1)), quadKeys.end());

        quadKeys = QuadKey::getKeysFromLongitudeLatitudeBoundingBox(
            Type::OsGeo, GeoCoordinateBoundingBox2d(
            GeoCoordinate2d(Longitude(+0.1), Latitude(-85.05113877)),
            GeoCoordinate2d(Longitude(+180.0), Latitude(+85.05113877))),
            1);
        EXPECT_EQ(2u, quadKeys.size());
        EXPECT_NE(std::find(quadKeys.begin(), quadKeys.end(), QuadKey(
            Type::OsGeo, 1, 1, 1)), quadKeys.end());
        EXPECT_NE(std::find(quadKeys.begin(), quadKeys.end(), QuadKey(
            Type::OsGeo, 0, 1, 1)), quadKeys.end());

        quadKeys = QuadKey::getKeysFromLongitudeLatitudeBoundingBox(
            Type::OsGeo, GeoCoordinateBoundingBox2d(
            GeoCoordinate2d(Longitude(-180.0), Latitude(-85.05113877)),
            GeoCoordinate2d(Longitude(+0.0), Latitude(+0.00000000))),
            1);
        EXPECT_EQ(1u, quadKeys.size());
        EXPECT_NE(std::find(quadKeys.begin(), quadKeys.end(), QuadKey(
            Type::OsGeo, 0, 0, 1)), quadKeys.end());

        quadKeys = QuadKey::getKeysFromLongitudeLatitudeBoundingBox(
            Type::OsGeo, GeoCoordinateBoundingBox2d(
            GeoCoordinate2d(Longitude(-180.0), Latitude(+0.10000000)),
            GeoCoordinate2d(Longitude(+0.0), Latitude(+85.05113877))),
            1);
        EXPECT_EQ(1u, quadKeys.size());
        EXPECT_NE(std::find(quadKeys.begin(), quadKeys.end(), QuadKey(
            Type::OsGeo, 1, 0, 1)), quadKeys.end());

        quadKeys = QuadKey::getKeysFromLongitudeLatitudeBoundingBox(
            Type::OsGeo, GeoCoordinateBoundingBox2d(
            GeoCoordinate2d(Longitude(+0.1), Latitude(-85.05113877)),
            GeoCoordinate2d(Longitude(+180.0), Latitude(+0.00000000))),
            1);
        EXPECT_EQ(1u, quadKeys.size());
        EXPECT_NE(std::find(quadKeys.begin(), quadKeys.end(), QuadKey(
            Type::OsGeo, 0, 1, 1)), quadKeys.end());

        quadKeys = QuadKey::getKeysFromLongitudeLatitudeBoundingBox(
            Type::OsGeo, GeoCoordinateBoundingBox2d(
            GeoCoordinate2d(Longitude(+0.1), Latitude(+0.10000000)),
            GeoCoordinate2d(Longitude(+180.0), Latitude(+85.05113877))),
            1);
        EXPECT_EQ(1u, quadKeys.size());
        EXPECT_NE(std::find(quadKeys.begin(), quadKeys.end(), QuadKey(
            Type::OsGeo, 1, 1, 1)), quadKeys.end());
    }

    TEST(OSGEOSYSTEM, SelectedCities)
    {
        // TODO: Implement Tests. Taken from Earthscape. No tests there.
    }
}

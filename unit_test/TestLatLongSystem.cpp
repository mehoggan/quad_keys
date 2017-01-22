#include <gtest/gtest.h>

#include "QuadKey/GeoCoordinate2d.h"
#include "QuadKey/QuadKey.h"

#include <iostream>

namespace QuadKeys
{
    class LatLongSystemTest : public ::testing::Test
    {
    protected:
        virtual void SetUp() {}
        virtual void TearDown() {}
    };

    TEST(LATLONGSYSTEM, IsValid)
    {
        // Same as BingSystem
    }

    TEST(LATLONGSYSTEM, IsRootKey)
    {
        // Same as BingSystem
    }

    TEST(LATLONGSYSTEM, GetParent)
    {
        // Same as BingSystem
    }

    TEST(LATLONGSYSTEM, IsMyAncestor)
    {
        // Same as BingSystem
    }

    TEST(LATLONGSYSTEM, GetAncestor)
    {
        // Same as BingSystem
    }

    TEST(LATLONGSYSTEM, GetChild)
    {
        // Same as BingSystem
    }

    TEST(LATLONGSYSTEM, GetChildren)
    {
        // Same as BingSystem
    }

    TEST(LATLONGSYSTEM, GetDescendants)
    {
        // Same as BingSystem
    }

    TEST(LATLONGSYSTEM, GetSiblings)
    {
        // Same as BingSystem
    }

    TEST(LATLONGSYSTEM, GetNeighbors)
    {
        // Same as BingSystem
    }

    TEST(LATLONGSYSTEM, FromStringToString)
    {
        // Same as BingSystem
    }

    TEST(LATLONGSYSTEM, GetGeoCoordinateBounds2d)
    {
        QuadKey key;
        GeoCoordinateBoundingBox2d bbox;

        { // Depth 0
            key = QuadKey(Type::LatLong, 0, 0, 0);
            key.getGeoCoordinateBounds2d(bbox);
            EXPECT_EQ(GeoCoordinate2d(Longitude(-180.0), Latitude(-90.0)),
                bbox.lowerLeft());
            EXPECT_EQ(GeoCoordinate2d(Longitude(+180.0), Latitude(+90.0)),
                bbox.upperRight());
        }

        { // Depth 1
            key = QuadKey(Type::LatLong, 0, 0, 1);
            key.getGeoCoordinateBounds2d(bbox);
            EXPECT_TRUE(bbox.lowerLeft().longitude().near(
              Longitude(-180.0), std::numeric_limits<float>::epsilon()));
            EXPECT_TRUE(bbox.lowerLeft().latitude().near(
              Latitude(-90.0), std::numeric_limits<float>::epsilon()));
            EXPECT_TRUE(bbox.upperRight().longitude().near(
              Longitude(+0.0), std::numeric_limits<float>::epsilon()));
            EXPECT_TRUE(bbox.upperRight().latitude().near(
              Latitude(+0.0), std::numeric_limits<float>::epsilon()));

            key = QuadKey(Type::LatLong, 0, 1, 1);
            key.getGeoCoordinateBounds2d(bbox);
            EXPECT_TRUE(bbox.lowerLeft().longitude().near(
              Longitude(+0.0), std::numeric_limits<float>::epsilon()));
            EXPECT_TRUE(bbox.lowerLeft().latitude().near(
              Latitude(-90.0), std::numeric_limits<float>::epsilon()));
            EXPECT_TRUE(bbox.upperRight().longitude().near(
              Longitude(+180.0), std::numeric_limits<float>::epsilon()));
            EXPECT_TRUE(bbox.upperRight().latitude().near(
              Latitude(+0.0), std::numeric_limits<float>::epsilon()));

            key = QuadKey(Type::LatLong, 1, 0, 1);
            key.getGeoCoordinateBounds2d(bbox);
            EXPECT_TRUE(bbox.lowerLeft().longitude().near(
              Longitude(-180.0), std::numeric_limits<float>::epsilon()));
            EXPECT_TRUE(bbox.lowerLeft().latitude().near(
              Latitude(+0.0), std::numeric_limits<float>::epsilon()));
            EXPECT_TRUE(bbox.upperRight().longitude().near(
              Longitude(+0.0), std::numeric_limits<float>::epsilon()));
            EXPECT_TRUE(bbox.upperRight().latitude().near(
              Latitude(+90.0), std::numeric_limits<float>::epsilon()));

            key = QuadKey(Type::LatLong, 1, 1, 1);
            key.getGeoCoordinateBounds2d(bbox);
            EXPECT_TRUE(bbox.lowerLeft().longitude().near(
              Longitude(+0.0), std::numeric_limits<float>::epsilon()));
            EXPECT_TRUE(bbox.lowerLeft().latitude().near(
              Latitude(+0.0), std::numeric_limits<float>::epsilon()));
            EXPECT_TRUE(bbox.upperRight().longitude().near(
              Longitude(+180.0), std::numeric_limits<float>::epsilon()));
            EXPECT_TRUE(bbox.upperRight().latitude().near(
              Latitude(+90.0), std::numeric_limits<float>::epsilon()));
        }
    }

    TEST(LATLONGSYSTEM, GetKeyFromLongitudeLatitudeAtDepthToBounds)
    {
       QuadKey key;

        { // Depth 0
            key = QuadKey::getKeyFromLongitudeLatitudeAtDepth(
                Type::LatLong, GeoCoordinate2d(Longitude(-180.0),
                Latitude(-90)), 0u);
            EXPECT_EQ(QuadKey(Type::LatLong, 0, 0, 0), key);
            EXPECT_EQ("", key.toInternalString());
        }

        // Inclusion here consists of lower left
        //    X------X------X
        //    |   2  |   3  |
        //    |      |      |
        //    X------X------X
        //    |   0  |   1  |
        //    |      |      |
        // ll X------X------X
        { // Depth 1
            key = QuadKey::getKeyFromLongitudeLatitudeAtDepth( // Q0 ll
                Type::LatLong, GeoCoordinate2d(Longitude(-180.0),
                Latitude(-90.0)), 1u);
            EXPECT_EQ(QuadKey(Type::LatLong, 0, 0, 1), key);
            EXPECT_EQ("2", key.toInternalString());
            key = QuadKey::getKeyFromLongitudeLatitudeAtDepth( // Q0 lr
                Type::LatLong, GeoCoordinate2d(Longitude(-0.1),
                Latitude(-90.0)), 1u);
            EXPECT_EQ(QuadKey(Type::LatLong, 0, 0, 1), key);
            EXPECT_EQ("2", key.toInternalString());
            key = QuadKey::getKeyFromLongitudeLatitudeAtDepth( // Q0 ur
                Type::LatLong, GeoCoordinate2d(Longitude(-0.1),
                Latitude(-0.1)), 1u);
            EXPECT_EQ(QuadKey(Type::LatLong, 0, 0, 1), key);
            EXPECT_EQ("2", key.toInternalString());
            key = QuadKey::getKeyFromLongitudeLatitudeAtDepth( // Q0 ul
                Type::LatLong, GeoCoordinate2d(Longitude(-180.0),
                Latitude(-0.1)), 1u);
            EXPECT_EQ(QuadKey(Type::LatLong, 0, 0, 1), key);
            EXPECT_EQ("2", key.toInternalString());

            key = QuadKey::getKeyFromLongitudeLatitudeAtDepth( // Q1 ll
                Type::LatLong, GeoCoordinate2d(Longitude(+0.0),
                Latitude(-90.0)), 1u);
            EXPECT_EQ(QuadKey(Type::LatLong, 0, 1, 1), key);
            EXPECT_EQ("3", key.toInternalString());
            key = QuadKey::getKeyFromLongitudeLatitudeAtDepth( // Q1 lr
                Type::LatLong, GeoCoordinate2d(Longitude(+180.0),
                Latitude(-90.0)), 1u);
            EXPECT_EQ(QuadKey(Type::LatLong, 0, 1, 1), key);
            EXPECT_EQ("3", key.toInternalString());
            key = QuadKey::getKeyFromLongitudeLatitudeAtDepth( // Q1 ur
                Type::LatLong, GeoCoordinate2d(Longitude(+180.0),
                Latitude(-0.1)), 1u);
            EXPECT_EQ(QuadKey(Type::LatLong, 0, 1, 1), key);
            EXPECT_EQ("3", key.toInternalString());
            key = QuadKey::getKeyFromLongitudeLatitudeAtDepth( // Q1 ul
                Type::LatLong, GeoCoordinate2d(Longitude(+0.0),
                Latitude(-0.1)), 1u);
            EXPECT_EQ(QuadKey(Type::LatLong, 0, 1, 1), key);
            EXPECT_EQ("3", key.toInternalString());

            key = QuadKey::getKeyFromLongitudeLatitudeAtDepth( // Q2 ll
                Type::LatLong, GeoCoordinate2d(Longitude(-180.0),
                Latitude(+0.0)), 1u);
            EXPECT_EQ(QuadKey(Type::LatLong, 1, 0, 1), key);
            EXPECT_EQ("0", key.toInternalString());
            key = QuadKey::getKeyFromLongitudeLatitudeAtDepth( // Q2 lr
                Type::LatLong, GeoCoordinate2d(Longitude(-0.1),
                Latitude(+0.0)), 1u);
            EXPECT_EQ(QuadKey(Type::LatLong, 1, 0, 1), key);
            EXPECT_EQ("0", key.toInternalString());
            key = QuadKey::getKeyFromLongitudeLatitudeAtDepth( // Q2 ur
                Type::LatLong, GeoCoordinate2d(Longitude(-180.0),
                Latitude(+90.0)), 1u);
            EXPECT_EQ(QuadKey(Type::LatLong, 1, 0, 1), key);
            EXPECT_EQ("0", key.toInternalString());
            key = QuadKey::getKeyFromLongitudeLatitudeAtDepth( // Q2 ul
                Type::LatLong, GeoCoordinate2d(Longitude(-0.1),
                Latitude(+90.0)), 1u);
            EXPECT_EQ(QuadKey(Type::LatLong, 1, 0, 1), key);
            EXPECT_EQ("0", key.toInternalString());

            key = QuadKey::getKeyFromLongitudeLatitudeAtDepth( // Q3 ll
                Type::LatLong, GeoCoordinate2d(Longitude(+0.0),
                Latitude(+0.0)), 1u);
            EXPECT_EQ(QuadKey(Type::LatLong, 1, 1, 1), key);
            EXPECT_EQ("1", key.toInternalString());
            key = QuadKey::getKeyFromLongitudeLatitudeAtDepth( // Q3 lr
                Type::LatLong, GeoCoordinate2d(Longitude(+180.0),
                Latitude(+0.0)), 1u);
            EXPECT_EQ(QuadKey(Type::LatLong, 1, 1, 1), key);
            EXPECT_EQ("1", key.toInternalString());
            key = QuadKey::getKeyFromLongitudeLatitudeAtDepth( // Q3 ur
                Type::LatLong, GeoCoordinate2d(Longitude(+0.0),
                Latitude(+90.0)), 1u);
            EXPECT_EQ(QuadKey(Type::LatLong, 1, 1, 1), key);
            EXPECT_EQ("1", key.toInternalString());
            key = QuadKey::getKeyFromLongitudeLatitudeAtDepth( // Q3 ul
                Type::LatLong, GeoCoordinate2d(Longitude(+180.0),
                Latitude(+90.0)), 1u);
            EXPECT_EQ(QuadKey(Type::LatLong, 1, 1, 1), key);
            EXPECT_EQ("1", key.toInternalString());
        }
    }

    TEST(LATLONGSYSTEM, GetKeysFromLongitudeLatitudeBoundingBox)
    {
        {
            std::vector<QuadKey> outKeys;
            outKeys = QuadKey::getKeysFromLongitudeLatitudeBoundingBox(
                Type::LatLong,
                GeoCoordinateBoundingBox2d(
                    GeoCoordinate2d(Longitude(-180.0), Latitude(+90.0)),
                    GeoCoordinate2d(Longitude(+180.0), Latitude(-90.0))), 0);
            EXPECT_EQ(1u, outKeys.size());
            EXPECT_NE(outKeys.end(), std::find(outKeys.begin(), outKeys.end(),
                QuadKey(Type::LatLong, 0, 0, 0)));
        }

        {
            std::vector<QuadKey> outKeys;
            outKeys = QuadKey::getKeysFromLongitudeLatitudeBoundingBox(
                Type::LatLong,
                GeoCoordinateBoundingBox2d(
                    GeoCoordinate2d(Longitude(-180.0), Latitude(+90.0)),
                    GeoCoordinate2d(Longitude(+180.0), Latitude(-90.0))), 1);
            EXPECT_EQ(4u, outKeys.size());
            EXPECT_NE(outKeys.end(), std::find(outKeys.begin(), outKeys.end(),
                QuadKey(Type::LatLong, 0, 0, 1)));
            EXPECT_NE(outKeys.end(), std::find(outKeys.begin(), outKeys.end(),
                QuadKey(Type::LatLong, 0, 1, 1)));
            EXPECT_NE(outKeys.end(), std::find(outKeys.begin(), outKeys.end(),
                QuadKey(Type::LatLong, 1, 0, 1)));
            EXPECT_NE(outKeys.end(), std::find(outKeys.begin(), outKeys.end(),
                QuadKey(Type::LatLong, 1, 1, 1)));
        }

        {
            std::vector<QuadKey> outKeys;
            outKeys = QuadKey::getKeysFromLongitudeLatitudeBoundingBox(
                Type::LatLong,
                GeoCoordinateBoundingBox2d(
                    GeoCoordinate2d(Longitude(-180.0), Latitude(-0.1)),
                    GeoCoordinate2d(Longitude(-0.1), Latitude(+90.0))), 1);
            EXPECT_EQ(2u, outKeys.size());
            EXPECT_NE(outKeys.end(), std::find(outKeys.begin(), outKeys.end(),
                QuadKey(Type::LatLong, 0, 0, 1)));
            EXPECT_NE(outKeys.end(), std::find(outKeys.begin(), outKeys.end(),
                QuadKey(Type::LatLong, 1, 0, 1)));
        }

        {
            std::vector<QuadKey> outKeys;
            outKeys = QuadKey::getKeysFromLongitudeLatitudeBoundingBox(
                Type::LatLong,
                GeoCoordinateBoundingBox2d(
                    GeoCoordinate2d(Longitude(+0.0), Latitude(-0.1)),
                    GeoCoordinate2d(Longitude(+180.0), Latitude(+90.0))), 1);
            EXPECT_EQ(2u, outKeys.size());
            EXPECT_NE(outKeys.end(), std::find(outKeys.begin(), outKeys.end(),
                QuadKey(Type::LatLong, 0, 1, 1)));
            EXPECT_NE(outKeys.end(), std::find(outKeys.begin(), outKeys.end(),
                QuadKey(Type::LatLong, 1, 1, 1)));
        }

        {
            std::vector<QuadKey> outKeys;
            outKeys = QuadKey::getKeysFromLongitudeLatitudeBoundingBox(
                Type::LatLong,
                GeoCoordinateBoundingBox2d(
                    GeoCoordinate2d(Longitude(-0.1), Latitude(-0.1)),
                    GeoCoordinate2d(Longitude(+0.1), Latitude(+0.1))), 1);
            EXPECT_EQ(4u, outKeys.size());
            EXPECT_NE(outKeys.end(), std::find(outKeys.begin(), outKeys.end(),
                QuadKey(Type::LatLong, 0, 0, 1)));
            EXPECT_NE(outKeys.end(), std::find(outKeys.begin(), outKeys.end(),
                QuadKey(Type::LatLong, 0, 1, 1)));
            EXPECT_NE(outKeys.end(), std::find(outKeys.begin(), outKeys.end(),
                QuadKey(Type::LatLong, 1, 0, 1)));
            EXPECT_NE(outKeys.end(), std::find(outKeys.begin(), outKeys.end(),
                QuadKey(Type::LatLong, 1, 1, 1)));
        }
    }

    TEST(LATLONGSYSTEM, TestKnownSampleOfLocations)
    {
        QuadKey key;

        {
            key = QuadKey::getKeyFromLongitudeLatitudeAtDepth(
                Type::LatLong, GeoCoordinate2d(Longitude(-122.4183),
                Latitude(37.7750)), 1u);
            EXPECT_EQ("0", key.toInternalString());
            key = QuadKey::getKeyFromLongitudeLatitudeAtDepth(
                Type::LatLong, GeoCoordinate2d(Longitude(-122.4183),
                Latitude(37.7750)), 2u);
            EXPECT_EQ("02", key.toInternalString());
            key = QuadKey::getKeyFromLongitudeLatitudeAtDepth(
                Type::LatLong, GeoCoordinate2d(Longitude(-122.4183),
                Latitude(37.7750)), 3u);
            EXPECT_EQ("021", key.toInternalString());
            key = QuadKey::getKeyFromLongitudeLatitudeAtDepth(
                Type::LatLong, GeoCoordinate2d(Longitude(-122.4183),
                Latitude(37.7750)), 4u);
            EXPECT_EQ("0210", key.toInternalString());
        }

        {
            key = QuadKey::getKeyFromLongitudeLatitudeAtDepth(
                Type::LatLong, GeoCoordinate2d(Longitude(+134.9),
                Latitude(-67.6)), 3u);
            EXPECT_EQ(QuadKey(Type::LatLong, 0, 6, 3), key);
            EXPECT_EQ("332", key.toInternalString());

            key = QuadKey::getKeyFromLongitudeLatitudeAtDepth(
                Type::LatLong, GeoCoordinate2d(Longitude(+135.0),
                Latitude(-67.5)), 3u);
            EXPECT_EQ(QuadKey(Type::LatLong, 1, 7, 3), key);
            EXPECT_EQ("331", key.toInternalString());
        }
    }
}

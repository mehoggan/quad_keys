#include <gtest/gtest.h>

#include "QuadKey/GeoCoordinateBoundingBox2d.h"
#include "QuadKey/GeoCoordinate2d.h"

#include <iostream>

namespace QuadKeys
{
    class GeoCoordinateBoundingBox2dTest : public ::testing::Test
    {
    protected:
        virtual void SetUp() {}
        virtual void TearDown() {}
    };

    TEST(GEOCOORDINATEBOUNDINGBOX2D, DefaultCtor)
    {
        GeoCoordinateBoundingBox2d empty;
        ASSERT_FALSE(empty.isValid());
        ASSERT_FALSE(empty.contains(
            GeoCoordinate2d(Longitude(0.0), Latitude(0.0))));
    }

    TEST(GEOCOORDINATEBOUNDINGBOX2D, CtorStandardConstruction)
    {
        { // Lower Left / Upper Right Construction
            GeoCoordinateBoundingBox2d geoBox(
                GeoCoordinate2d(Longitude(0.0), Latitude(0.0)),
                GeoCoordinate2d(Longitude(180.0), Latitude(90.0)));

            EXPECT_EQ(GeoCoordinate2d(Longitude(0.0), Latitude(0.0)),
                geoBox.lowerLeft());
            EXPECT_EQ(GeoCoordinate2d(Longitude(180.0), Latitude(90.0)),
                geoBox.upperRight());
            EXPECT_TRUE(geoBox.isValid());
        }

        { // Upper Left / Lower Right Construction
            GeoCoordinateBoundingBox2d geoBox(
                GeoCoordinate2d(Longitude(0.0), Latitude(90.0)),
                GeoCoordinate2d(Longitude(180.0), Latitude(0.0)));

            EXPECT_EQ(GeoCoordinate2d(Longitude(0.0), Latitude(0.0)),
                geoBox.lowerLeft());
            EXPECT_EQ(GeoCoordinate2d(Longitude(180.0), Latitude(90.0)),
                geoBox.upperRight());
            EXPECT_TRUE(geoBox.isValid());
        }

        { // Upper Right / Lower Left Construction
            GeoCoordinateBoundingBox2d geoBox(
                GeoCoordinate2d(Longitude(180.0), Latitude(0.0)),
                GeoCoordinate2d(Longitude(0.0), Latitude(90.0)));

            EXPECT_EQ(GeoCoordinate2d(Longitude(0.0), Latitude(0.0)),
                geoBox.lowerLeft());
            EXPECT_EQ(GeoCoordinate2d(Longitude(180.0), Latitude(90.0)),
                geoBox.upperRight());
            EXPECT_TRUE(geoBox.isValid());
        }

        { // Lower Right / Upper Left Construction
            GeoCoordinateBoundingBox2d geoBox(
                GeoCoordinate2d(Longitude(180.0), Latitude(0.0)),
                GeoCoordinate2d(Longitude(0.0), Latitude(90.0)));

            EXPECT_EQ(GeoCoordinate2d(Longitude(0.0), Latitude(0.0)),
                geoBox.lowerLeft());
            EXPECT_EQ(GeoCoordinate2d(Longitude(180.0), Latitude(90.0)),
                geoBox.upperRight());
            EXPECT_TRUE(geoBox.isValid());
        }
    }

    TEST(GEOCOORDINATEBOUNDINGBOX2D, CtorLinearBoxAndPoint)
    {
        { // Horizontal
            GeoCoordinateBoundingBox2d geoBox(
                GeoCoordinate2d(Longitude(0.0), Latitude(0.0)),
                GeoCoordinate2d(Longitude(0.0), Latitude(90.0)));

            EXPECT_EQ(GeoCoordinate2d(Longitude(0.0), Latitude(0.0)),
                geoBox.lowerLeft());
            EXPECT_EQ(GeoCoordinate2d(Longitude(0.0), Latitude(90.0)),
                geoBox.upperRight());
            EXPECT_TRUE(geoBox.isValid());
        }

        { // Vertical
            GeoCoordinateBoundingBox2d geoBox(
                GeoCoordinate2d(Longitude(0.0), Latitude(0.0)),
                GeoCoordinate2d(Longitude(180.0), Latitude(0.0)));

            EXPECT_EQ(GeoCoordinate2d(Longitude(0.0), Latitude(0.0)),
                geoBox.lowerLeft());
            EXPECT_EQ(GeoCoordinate2d(Longitude(180.0), Latitude(0.0)),
                geoBox.upperRight());
            EXPECT_TRUE(geoBox.isValid());
        }

        { // Point
            GeoCoordinateBoundingBox2d geoBox(
                GeoCoordinate2d(Longitude(0.0), Latitude(0.0)),
                GeoCoordinate2d(Longitude(0.0), Latitude(0.0)));

            EXPECT_TRUE(geoBox.isValid());
        }
    }

    TEST(GEOCOORDINATEBOUNDINGBOX2D, ContainsOrNot)
    {
        {
            GeoCoordinateBoundingBox2d geoBox(
                GeoCoordinate2d(Longitude(90.0), Latitude(45.0)),
                GeoCoordinate2d(Longitude(-90.0), Latitude(-45.0)));

            EXPECT_TRUE(geoBox.isValid());

            EXPECT_TRUE(geoBox.contains(GeoCoordinate2d(Longitude(0.0),
                Latitude(0.0))));

            EXPECT_TRUE(geoBox.contains(GeoCoordinate2d(Longitude(90.0),
                Latitude(45.0))));
            EXPECT_TRUE(geoBox.contains(GeoCoordinate2d(Longitude(90.0),
                Latitude(-45.0))));
            EXPECT_TRUE(geoBox.contains(GeoCoordinate2d(Longitude(-90.0),
                Latitude(-45.0))));
            EXPECT_TRUE(geoBox.contains(GeoCoordinate2d(Longitude(-90.0),
                Latitude(45.0))));

            EXPECT_FALSE(geoBox.contains(GeoCoordinate2d(Longitude(90.01),
                Latitude(45.01))));
            EXPECT_FALSE(geoBox.contains(GeoCoordinate2d(Longitude(90.01),
                Latitude(-45.01))));
            EXPECT_FALSE(geoBox.contains(GeoCoordinate2d(Longitude(-90.01),
                Latitude(-45.01))));
            EXPECT_FALSE(geoBox.contains(GeoCoordinate2d(Longitude(-90.01),
                Latitude(45.01))));
        }

        {
            GeoCoordinateBoundingBox2d geoBox(
                GeoCoordinate2d(Longitude(90.0), Latitude(45.0)),
                GeoCoordinate2d(Longitude(0.1), Latitude(0.1)));

            EXPECT_EQ(GeoCoordinate2d(Longitude(0.1), Latitude(0.1)),
                geoBox.lowerLeft());
            EXPECT_EQ(GeoCoordinate2d(Longitude(90.0), Latitude(45.0)),
                geoBox.upperRight());

            EXPECT_TRUE(geoBox.isValid());

            EXPECT_TRUE(geoBox.contains(GeoCoordinate2d(Longitude(90.0),
                Latitude(45.0))));
            EXPECT_TRUE(geoBox.contains(GeoCoordinate2d(Longitude(90.0),
                Latitude(0.1))));
            EXPECT_TRUE(geoBox.contains(GeoCoordinate2d(Longitude(0.1),
                Latitude(0.1))));
            EXPECT_TRUE(geoBox.contains(GeoCoordinate2d(Longitude(0.1),
                Latitude(45.0))));

            EXPECT_FALSE(geoBox.contains(GeoCoordinate2d(Longitude(90.01),
                Latitude(45.01))));
            EXPECT_FALSE(geoBox.contains(GeoCoordinate2d(Longitude(90.01),
                Latitude(0.0))));
            EXPECT_FALSE(geoBox.contains(GeoCoordinate2d(Longitude(0.0),
                Latitude(0.0))));
            EXPECT_FALSE(geoBox.contains(GeoCoordinate2d(Longitude(0.0),
                Latitude(45.01))));
        }
    }

    TEST(GEOCOORDINATEBOUNDINGBOX2D, GrowToContain)
    {
        {
            GeoCoordinateBoundingBox2d geoBox(
                GeoCoordinate2d(Longitude(-90.0), Latitude(-45.0)),
                GeoCoordinate2d(Longitude(90.0), Latitude(45.0)));

            EXPECT_EQ(GeoCoordinate2d(Longitude(-90.0), Latitude(-45.0)),
                geoBox.lowerLeft());
            EXPECT_EQ(GeoCoordinate2d(Longitude(90.0), Latitude(45.0)),
                geoBox.upperRight());

            geoBox.growToContain(GeoCoordinate2d(Longitude(180.0),
                Latitude(90.0)));

            EXPECT_EQ(GeoCoordinate2d(Longitude(-90.0), Latitude(-45.0)),
                geoBox.lowerLeft());
            EXPECT_EQ(GeoCoordinate2d(Longitude(180.0), Latitude(90.0)),
                geoBox.upperRight());
        }

        {
            GeoCoordinateBoundingBox2d geoBox(
                GeoCoordinate2d(Longitude(-90.0), Latitude(-45.0)),
                GeoCoordinate2d(Longitude(90.0), Latitude(45.0)));

            EXPECT_EQ(GeoCoordinate2d(Longitude(-90.0), Latitude(-45.0)),
                geoBox.lowerLeft());
            EXPECT_EQ(GeoCoordinate2d(Longitude(90.0), Latitude(45.0)),
                geoBox.upperRight());

            geoBox.growToContain(GeoCoordinate2d(Longitude(-180.0),
                Latitude(-90.0)));

            EXPECT_EQ(GeoCoordinate2d(Longitude(-180.0), Latitude(-90.0)),
                geoBox.lowerLeft());
            EXPECT_EQ(GeoCoordinate2d(Longitude(90.0), Latitude(45.0)),
                geoBox.upperRight());
        }

        {
            GeoCoordinateBoundingBox2d geoBox(
                GeoCoordinate2d(Longitude(-90.0), Latitude(-45.0)),
                GeoCoordinate2d(Longitude(90.0), Latitude(45.0)));

            EXPECT_EQ(GeoCoordinate2d(Longitude(-90.0), Latitude(-45.0)),
                geoBox.lowerLeft());
            EXPECT_EQ(GeoCoordinate2d(Longitude(90.0), Latitude(45.0)),
                geoBox.upperRight());

            geoBox.growToContain(GeoCoordinate2d(Longitude(-180.0),
                Latitude(90.0)));

            EXPECT_EQ(GeoCoordinate2d(Longitude(-180.0), Latitude(-45.0)),
                geoBox.lowerLeft());
            EXPECT_EQ(GeoCoordinate2d(Longitude(90.0), Latitude(90.0)),
                geoBox.upperRight());
        }

        {
            GeoCoordinateBoundingBox2d geoBox(
                GeoCoordinate2d(Longitude(-90.0), Latitude(-45.0)),
                GeoCoordinate2d(Longitude(90.0), Latitude(45.0)));

            EXPECT_EQ(GeoCoordinate2d(Longitude(-90.0), Latitude(-45.0)),
                geoBox.lowerLeft());
            EXPECT_EQ(GeoCoordinate2d(Longitude(90.0), Latitude(45.0)),
                geoBox.upperRight());

            geoBox.growToContain(GeoCoordinate2d(Longitude(180.0),
                Latitude(-90.0)));

            EXPECT_EQ(GeoCoordinate2d(Longitude(-90.0), Latitude(-90.0)),
                geoBox.lowerLeft());
            EXPECT_EQ(GeoCoordinate2d(Longitude(180.0), Latitude(45.0)),
                geoBox.upperRight());
        }

        {
            GeoCoordinateBoundingBox2d geoBox(
                GeoCoordinate2d(Longitude(-90.0), Latitude(-45.0)),
                GeoCoordinate2d(Longitude(90.0), Latitude(45.0)));

            EXPECT_EQ(GeoCoordinate2d(Longitude(-90.0), Latitude(-45.0)),
                geoBox.lowerLeft());
            EXPECT_EQ(GeoCoordinate2d(Longitude(90.0), Latitude(45.0)),
                geoBox.upperRight());

            geoBox.growToContain(GeoCoordinate2d(Longitude(0.0),
                Latitude(0.0)));

            EXPECT_EQ(GeoCoordinate2d(Longitude(-90.0), Latitude(-45.0)),
                geoBox.lowerLeft());
            EXPECT_EQ(GeoCoordinate2d(Longitude(90.0), Latitude(45.0)),
                geoBox.upperRight());
        }
    }
}

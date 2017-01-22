#include <gtest/gtest.h>
#include "QuadKey/GeoCoordinate2d.h"
#include <iostream>

namespace QuadKeys
{
    class GeoCoordinate2dTest : public ::testing::Test
    {
    protected:
        virtual void SetUp() {}
        virtual void TearDown() {}
    };

    TEST(GEOCOORDINATE2D, DefaultCtor)
    {
        GeoCoordinate2d empty;
        EXPECT_EQ(Longitude(0.0), empty.longitude());
        EXPECT_EQ(Latitude(0.0), empty.latitude());
    }

    TEST(GEOCOORDINATE2D, Ctor)
    {
        {
            GeoCoordinate2d coord(Longitude(0.0), Latitude(0.0));
            EXPECT_EQ(Longitude(0.0), coord.longitude());
            EXPECT_EQ(Latitude(0.0), coord.latitude());
        }

        {
            GeoCoordinate2d coord(Longitude(-180.001), Latitude(-95.0));
            EXPECT_EQ(Longitude(-180.0), coord.longitude());
            EXPECT_EQ(Latitude(-90.0), coord.latitude());
        }

        {
            GeoCoordinate2d coord(Longitude(-180.001), Latitude(95.0));
            EXPECT_EQ(Longitude(-180.0), coord.longitude());
            EXPECT_EQ(Latitude(90.0), coord.latitude());
        }

        {
            GeoCoordinate2d coord(Longitude(180.001), Latitude(95.0));
            EXPECT_EQ(Longitude(180.0), coord.longitude());
            EXPECT_EQ(Latitude(90.0), coord.latitude());
        }

        {
            GeoCoordinate2d coord(Longitude(180.001), Latitude(-95.0));
            EXPECT_EQ(Longitude(180.0), coord.longitude());
            EXPECT_EQ(Latitude(-90.0), coord.latitude());
        }
    }

    TEST(GEOCOORDINATE2D, Near)
    {
        {
            Longitude lon(0.001);
            EXPECT_TRUE(lon.near(Longitude(0.0009), 1e-3));
        }

        {
            Longitude lon(0.001);
            EXPECT_FALSE(lon.near(Longitude(0.0009), 1e-4));
        }

        {
            Latitude lat(0.001);
            EXPECT_TRUE(lat.near(Latitude(0.0009), 1e-3));
        }

        {
            Latitude lat(0.001);
            EXPECT_FALSE(lat.near(Latitude(0.0009), 1e-4));
        }

        {
            GeoCoordinate2d coord(Longitude(0.001), Latitude(0.001));
            EXPECT_TRUE(coord.near(GeoCoordinate2d(Longitude(0.0009),
                Latitude(0.0009)), 1e-3));
        }

        {
            GeoCoordinate2d coord(Longitude(0.001), Latitude(0.001));
            EXPECT_FALSE(coord.near(GeoCoordinate2d(Longitude(0.001),
                Latitude(0.0009)), 1e-4));
        }

        {
            GeoCoordinate2d coord(Longitude(0.001), Latitude(0.001));
            EXPECT_FALSE(coord.near(GeoCoordinate2d(Longitude(0.0009),
                Latitude(0.001)), 1e-4));
        }
    }

    TEST(GEOCOORDINATE2D, Operator_LT)
    {
        GeoCoordinate2d sw(Longitude(-0.1), Latitude(-0.1));
        GeoCoordinate2d ne(Longitude(+0.1), Latitude(+0.1));

        EXPECT_TRUE(sw.longitude() < ne.longitude());
        EXPECT_TRUE(sw.latitude() < ne.latitude());
    }

    TEST(GEOCOORDINATE2D, Operator_LTEQ)
    {
        {
            GeoCoordinate2d sw(Longitude(-0.1), Latitude(-0.1));
            GeoCoordinate2d ne(Longitude(+0.1), Latitude(+0.1));

            EXPECT_TRUE(sw.longitude() <= ne.longitude());
            EXPECT_TRUE(sw.latitude() <= ne.latitude());
        }

        {
            GeoCoordinate2d sw(Longitude(-0.1), Latitude(-0.1));
            GeoCoordinate2d ne(Longitude(-0.1), Latitude(-0.1));

            EXPECT_TRUE(sw.longitude() <= ne.longitude());
            EXPECT_TRUE(sw.latitude() <= ne.latitude());
        }
    }

    TEST(GEOCOORDINATE2D, Operator_EQ)
    {
        GeoCoordinate2d sw(Longitude(-0.1), Latitude(-0.1));
        GeoCoordinate2d ne(Longitude(-0.1), Latitude(-0.1));

        EXPECT_TRUE(sw.longitude() == ne.longitude());
        EXPECT_TRUE(sw.latitude() == ne.latitude());
    }
}

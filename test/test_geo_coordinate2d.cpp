#include <gtest/gtest.h>

#include "quad_keys/geo_coordinate2d.h"

#include <iostream>

namespace quad_keys
{
  class TestGeoCoordinate2d : public ::testing::Test
  {
  protected:
    virtual void SetUp() {}
    virtual void TearDown() {}
  };

  TEST(GEOCOORDINATE2D, default_ctor)
  {
    GeoCoordinate2d empty;
    EXPECT_EQ(Longitude(0.0), empty.get_longitude());
    EXPECT_EQ(Latitude(0.0), empty.get_latitude());
  }

  TEST(GEOCOORDINATE2D, ctor)
  {
    {
      GeoCoordinate2d coord(Longitude(0.0), Latitude(0.0));
      EXPECT_EQ(Longitude(0.0), coord.get_longitude());
      EXPECT_EQ(Latitude(0.0), coord.get_latitude());
    }

    {
      GeoCoordinate2d coord(Longitude(-180.001), Latitude(-95.0));
      EXPECT_EQ(Longitude(-180.0), coord.get_longitude());
      EXPECT_EQ(Latitude(-90.0), coord.get_latitude());
    }

    {
      GeoCoordinate2d coord(Longitude(-180.001), Latitude(95.0));
      EXPECT_EQ(Longitude(-180.0), coord.get_longitude());
      EXPECT_EQ(Latitude(90.0), coord.get_latitude());
    }

    {
      GeoCoordinate2d coord(Longitude(180.001), Latitude(95.0));
      EXPECT_EQ(Longitude(180.0), coord.get_longitude());
      EXPECT_EQ(Latitude(90.0), coord.get_latitude());
    }

    {
      GeoCoordinate2d coord(Longitude(180.001), Latitude(-95.0));
      EXPECT_EQ(Longitude(180.0), coord.get_longitude());
      EXPECT_EQ(Latitude(-90.0), coord.get_latitude());
    }
  }

  TEST(GEOCOORDINATE2D, near)
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

  TEST(GEOCOORDINATE2D, operator_lt)
  {
    GeoCoordinate2d sw(Longitude(-0.1), Latitude(-0.1));
    GeoCoordinate2d ne(Longitude(+0.1), Latitude(+0.1));

    EXPECT_TRUE(sw.get_longitude() < ne.get_longitude());
    EXPECT_TRUE(sw.get_latitude() < ne.get_latitude());
  }

  TEST(GEOCOORDINATE2D, operator_lteq)
  {
    {
      GeoCoordinate2d sw(Longitude(-0.1), Latitude(-0.1));
      GeoCoordinate2d ne(Longitude(+0.1), Latitude(+0.1));

      EXPECT_TRUE(sw.get_longitude() <= ne.get_longitude());
      EXPECT_TRUE(sw.get_latitude() <= ne.get_latitude());
    }

    {
      GeoCoordinate2d sw(Longitude(-0.1), Latitude(-0.1));
      GeoCoordinate2d ne(Longitude(-0.1), Latitude(-0.1));

      EXPECT_TRUE(sw.get_longitude() <= ne.get_longitude());
      EXPECT_TRUE(sw.get_latitude() <= ne.get_latitude());
    }
  }

  TEST(GEOCOORDINATE2D, operator_eq)
  {
    GeoCoordinate2d sw(Longitude(-0.1), Latitude(-0.1));
    GeoCoordinate2d ne(Longitude(-0.1), Latitude(-0.1));

    EXPECT_TRUE(sw.get_longitude() == ne.get_longitude());
    EXPECT_TRUE(sw.get_latitude() == ne.get_latitude());
  }
}

#include <gtest/gtest.h>

#include "quad_key/geo_coordinate2d.h"

#include <iostream>

namespace quad_keys
{
  class test_geo_coordinate2d : public ::testing::Test
  {
  protected:
    virtual void SetUp() {}
    virtual void TearDown() {}
  };

  TEST(GEOCOORDINATE2D, default_ctor)
  {
    geo_coordinate2d empty;
    EXPECT_EQ(longitude(0.0), empty.get_longitude());
    EXPECT_EQ(latitude(0.0), empty.get_latitude());
  }

  TEST(GEOCOORDINATE2D, ctor)
  {
    {
      geo_coordinate2d coord(longitude(0.0), latitude(0.0));
      EXPECT_EQ(longitude(0.0), coord.get_longitude());
      EXPECT_EQ(latitude(0.0), coord.get_latitude());
    }

    {
      geo_coordinate2d coord(longitude(-180.001), latitude(-95.0));
      EXPECT_EQ(longitude(-180.0), coord.get_longitude());
      EXPECT_EQ(latitude(-90.0), coord.get_latitude());
    }

    {
      geo_coordinate2d coord(longitude(-180.001), latitude(95.0));
      EXPECT_EQ(longitude(-180.0), coord.get_longitude());
      EXPECT_EQ(latitude(90.0), coord.get_latitude());
    }

    {
      geo_coordinate2d coord(longitude(180.001), latitude(95.0));
      EXPECT_EQ(longitude(180.0), coord.get_longitude());
      EXPECT_EQ(latitude(90.0), coord.get_latitude());
    }

    {
      geo_coordinate2d coord(longitude(180.001), latitude(-95.0));
      EXPECT_EQ(longitude(180.0), coord.get_longitude());
      EXPECT_EQ(latitude(-90.0), coord.get_latitude());
    }
  }

  TEST(GEOCOORDINATE2D, near)
  {
    {
      longitude lon(0.001);
      EXPECT_TRUE(lon.near(longitude(0.0009), 1e-3));
    }

    {
      longitude lon(0.001);
      EXPECT_FALSE(lon.near(longitude(0.0009), 1e-4));
    }

    {
      latitude lat(0.001);
      EXPECT_TRUE(lat.near(latitude(0.0009), 1e-3));
    }

    {
      latitude lat(0.001);
      EXPECT_FALSE(lat.near(latitude(0.0009), 1e-4));
    }

    {
      geo_coordinate2d coord(longitude(0.001), latitude(0.001));
      EXPECT_TRUE(coord.near(geo_coordinate2d(longitude(0.0009),
        latitude(0.0009)), 1e-3));
    }

    {
      geo_coordinate2d coord(longitude(0.001), latitude(0.001));
      EXPECT_FALSE(coord.near(geo_coordinate2d(longitude(0.001),
        latitude(0.0009)), 1e-4));
    }

    {
      geo_coordinate2d coord(longitude(0.001), latitude(0.001));
      EXPECT_FALSE(coord.near(geo_coordinate2d(longitude(0.0009),
        latitude(0.001)), 1e-4));
    }
  }

  TEST(GEOCOORDINATE2D, operator_lt)
  {
    geo_coordinate2d sw(longitude(-0.1), latitude(-0.1));
    geo_coordinate2d ne(longitude(+0.1), latitude(+0.1));

    EXPECT_TRUE(sw.get_longitude() < ne.get_longitude());
    EXPECT_TRUE(sw.get_latitude() < ne.get_latitude());
  }

  TEST(GEOCOORDINATE2D, operator_lteq)
  {
    {
      geo_coordinate2d sw(longitude(-0.1), latitude(-0.1));
      geo_coordinate2d ne(longitude(+0.1), latitude(+0.1));

      EXPECT_TRUE(sw.get_longitude() <= ne.get_longitude());
      EXPECT_TRUE(sw.get_latitude() <= ne.get_latitude());
    }

    {
      geo_coordinate2d sw(longitude(-0.1), latitude(-0.1));
      geo_coordinate2d ne(longitude(-0.1), latitude(-0.1));

      EXPECT_TRUE(sw.get_longitude() <= ne.get_longitude());
      EXPECT_TRUE(sw.get_latitude() <= ne.get_latitude());
    }
  }

  TEST(GEOCOORDINATE2D, operator_eq)
  {
    geo_coordinate2d sw(longitude(-0.1), latitude(-0.1));
    geo_coordinate2d ne(longitude(-0.1), latitude(-0.1));

    EXPECT_TRUE(sw.get_longitude() == ne.get_longitude());
    EXPECT_TRUE(sw.get_latitude() == ne.get_latitude());
  }
}

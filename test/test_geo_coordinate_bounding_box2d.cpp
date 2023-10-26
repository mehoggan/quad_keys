#include <gtest/gtest.h>

#include "quad_keys/geo_coordinate_bounding_box2d.h"
#include "quad_keys/geo_coordinate2d.h"

#include <iostream>

namespace quad_keys
{
  class TestGeoCoordinateBoundingBox2d : public ::testing::Test
  {
  protected:
    virtual void SetUp() {}
    virtual void TearDown() {}
  };

  TEST(GEOCOORDINATEBOUNDINGBOX2D, default_ctor)
  {
    GeoCoordinateBoundingBox2d empty;
    ASSERT_FALSE(empty.is_valid());
    ASSERT_FALSE(empty.contains(
      GeoCoordinate2d(Longitude(0.0), Latitude(0.0))));
  }

  TEST(GEOCOORDINATEBOUNDINGBOX2D, ctor_standard_construction)
  {
    { // Lower Left / Upper Right Construction
      GeoCoordinateBoundingBox2d geo_box(
        GeoCoordinate2d(Longitude(0.0), Latitude(0.0)),
        GeoCoordinate2d(Longitude(180.0), Latitude(90.0)));

      EXPECT_EQ(GeoCoordinate2d(Longitude(0.0), Latitude(0.0)),
        geo_box.lower_left());
      EXPECT_EQ(GeoCoordinate2d(Longitude(180.0), Latitude(90.0)),
        geo_box.upper_right());
      EXPECT_TRUE(geo_box.is_valid());
    }

    { // Upper Left / Lower Right Construction
      GeoCoordinateBoundingBox2d geo_box(
        GeoCoordinate2d(Longitude(0.0), Latitude(90.0)),
        GeoCoordinate2d(Longitude(180.0), Latitude(0.0)));

      EXPECT_EQ(GeoCoordinate2d(Longitude(0.0), Latitude(0.0)),
        geo_box.lower_left());
      EXPECT_EQ(GeoCoordinate2d(Longitude(180.0), Latitude(90.0)),
        geo_box.upper_right());
      EXPECT_TRUE(geo_box.is_valid());
    }

    { // Upper Right / Lower Left Construction
      GeoCoordinateBoundingBox2d geo_box(
        GeoCoordinate2d(Longitude(180.0), Latitude(0.0)),
        GeoCoordinate2d(Longitude(0.0), Latitude(90.0)));

      EXPECT_EQ(GeoCoordinate2d(Longitude(0.0), Latitude(0.0)),
        geo_box.lower_left());
      EXPECT_EQ(GeoCoordinate2d(Longitude(180.0), Latitude(90.0)),
        geo_box.upper_right());
      EXPECT_TRUE(geo_box.is_valid());
    }

    { // Lower Right / Upper Left Construction
      GeoCoordinateBoundingBox2d geo_box(
        GeoCoordinate2d(Longitude(180.0), Latitude(0.0)),
        GeoCoordinate2d(Longitude(0.0), Latitude(90.0)));

      EXPECT_EQ(GeoCoordinate2d(Longitude(0.0), Latitude(0.0)),
        geo_box.lower_left());
      EXPECT_EQ(GeoCoordinate2d(Longitude(180.0), Latitude(90.0)),
        geo_box.upper_right());
      EXPECT_TRUE(geo_box.is_valid());
    }
  }

  TEST(GEOCOORDINATEBOUNDINGBOX2D, ctor_linear_box_and_point)
  {
    { // Horizontal
      GeoCoordinateBoundingBox2d geo_box(
        GeoCoordinate2d(Longitude(0.0), Latitude(0.0)),
        GeoCoordinate2d(Longitude(0.0), Latitude(90.0)));

      EXPECT_EQ(GeoCoordinate2d(Longitude(0.0), Latitude(0.0)),
        geo_box.lower_left());
      EXPECT_EQ(GeoCoordinate2d(Longitude(0.0), Latitude(90.0)),
        geo_box.upper_right());
      EXPECT_TRUE(geo_box.is_valid());
    }

    { // Vertical
      GeoCoordinateBoundingBox2d geo_box(
        GeoCoordinate2d(Longitude(0.0), Latitude(0.0)),
        GeoCoordinate2d(Longitude(180.0), Latitude(0.0)));

      EXPECT_EQ(GeoCoordinate2d(Longitude(0.0), Latitude(0.0)),
        geo_box.lower_left());
      EXPECT_EQ(GeoCoordinate2d(Longitude(180.0), Latitude(0.0)),
        geo_box.upper_right());
      EXPECT_TRUE(geo_box.is_valid());
    }

    { // Point
      GeoCoordinateBoundingBox2d geo_box(
        GeoCoordinate2d(Longitude(0.0), Latitude(0.0)),
        GeoCoordinate2d(Longitude(0.0), Latitude(0.0)));

      EXPECT_TRUE(geo_box.is_valid());
    }
  }

  TEST(GEOCOORDINATEBOUNDINGBOX2D, contains_or_not)
  {
    {
      GeoCoordinateBoundingBox2d geo_box(
        GeoCoordinate2d(Longitude(90.0), Latitude(45.0)),
        GeoCoordinate2d(Longitude(-90.0), Latitude(-45.0)));

      EXPECT_TRUE(geo_box.is_valid());

      EXPECT_TRUE(geo_box.contains(GeoCoordinate2d(Longitude(0.0),
        Latitude(0.0))));

      EXPECT_TRUE(geo_box.contains(GeoCoordinate2d(Longitude(90.0),
        Latitude(45.0))));
      EXPECT_TRUE(geo_box.contains(GeoCoordinate2d(Longitude(90.0),
        Latitude(-45.0))));
      EXPECT_TRUE(geo_box.contains(GeoCoordinate2d(Longitude(-90.0),
        Latitude(-45.0))));
      EXPECT_TRUE(geo_box.contains(GeoCoordinate2d(Longitude(-90.0),
        Latitude(45.0))));

      EXPECT_FALSE(geo_box.contains(GeoCoordinate2d(Longitude(90.01),
        Latitude(45.01))));
      EXPECT_FALSE(geo_box.contains(GeoCoordinate2d(Longitude(90.01),
        Latitude(-45.01))));
      EXPECT_FALSE(geo_box.contains(GeoCoordinate2d(Longitude(-90.01),
        Latitude(-45.01))));
      EXPECT_FALSE(geo_box.contains(GeoCoordinate2d(Longitude(-90.01),
        Latitude(45.01))));
    }

    {
      GeoCoordinateBoundingBox2d geo_box(
        GeoCoordinate2d(Longitude(90.0), Latitude(45.0)),
        GeoCoordinate2d(Longitude(0.1), Latitude(0.1)));

      EXPECT_EQ(GeoCoordinate2d(Longitude(0.1), Latitude(0.1)),
        geo_box.lower_left());
      EXPECT_EQ(GeoCoordinate2d(Longitude(90.0), Latitude(45.0)),
        geo_box.upper_right());

      EXPECT_TRUE(geo_box.is_valid());

      EXPECT_TRUE(geo_box.contains(GeoCoordinate2d(Longitude(90.0),
        Latitude(45.0))));
      EXPECT_TRUE(geo_box.contains(GeoCoordinate2d(Longitude(90.0),
        Latitude(0.1))));
      EXPECT_TRUE(geo_box.contains(GeoCoordinate2d(Longitude(0.1),
        Latitude(0.1))));
      EXPECT_TRUE(geo_box.contains(GeoCoordinate2d(Longitude(0.1),
        Latitude(45.0))));

      EXPECT_FALSE(geo_box.contains(GeoCoordinate2d(Longitude(90.01),
        Latitude(45.01))));
      EXPECT_FALSE(geo_box.contains(GeoCoordinate2d(Longitude(90.01),
        Latitude(0.0))));
      EXPECT_FALSE(geo_box.contains(GeoCoordinate2d(Longitude(0.0),
        Latitude(0.0))));
      EXPECT_FALSE(geo_box.contains(GeoCoordinate2d(Longitude(0.0),
        Latitude(45.01))));
    }
  }

  TEST(GEOCOORDINATEBOUNDINGBOX2D, grow_to_contain)
  {
    {
      GeoCoordinateBoundingBox2d geo_box(
        GeoCoordinate2d(Longitude(-90.0), Latitude(-45.0)),
        GeoCoordinate2d(Longitude(90.0), Latitude(45.0)));

      EXPECT_EQ(GeoCoordinate2d(Longitude(-90.0), Latitude(-45.0)),
        geo_box.lower_left());
      EXPECT_EQ(GeoCoordinate2d(Longitude(90.0), Latitude(45.0)),
        geo_box.upper_right());

      geo_box.grow_to_contain(GeoCoordinate2d(Longitude(180.0),
        Latitude(90.0)));

      EXPECT_EQ(GeoCoordinate2d(Longitude(-90.0), Latitude(-45.0)),
        geo_box.lower_left());
      EXPECT_EQ(GeoCoordinate2d(Longitude(180.0), Latitude(90.0)),
        geo_box.upper_right());
    }

    {
      GeoCoordinateBoundingBox2d geo_box(
        GeoCoordinate2d(Longitude(-90.0), Latitude(-45.0)),
        GeoCoordinate2d(Longitude(90.0), Latitude(45.0)));

      EXPECT_EQ(GeoCoordinate2d(Longitude(-90.0), Latitude(-45.0)),
        geo_box.lower_left());
      EXPECT_EQ(GeoCoordinate2d(Longitude(90.0), Latitude(45.0)),
        geo_box.upper_right());

      geo_box.grow_to_contain(GeoCoordinate2d(Longitude(-180.0),
        Latitude(-90.0)));

      EXPECT_EQ(GeoCoordinate2d(Longitude(-180.0), Latitude(-90.0)),
        geo_box.lower_left());
      EXPECT_EQ(GeoCoordinate2d(Longitude(90.0), Latitude(45.0)),
        geo_box.upper_right());
    }

    {
      GeoCoordinateBoundingBox2d geo_box(
        GeoCoordinate2d(Longitude(-90.0), Latitude(-45.0)),
        GeoCoordinate2d(Longitude(90.0), Latitude(45.0)));

      EXPECT_EQ(GeoCoordinate2d(Longitude(-90.0), Latitude(-45.0)),
        geo_box.lower_left());
      EXPECT_EQ(GeoCoordinate2d(Longitude(90.0), Latitude(45.0)),
        geo_box.upper_right());

      geo_box.grow_to_contain(GeoCoordinate2d(Longitude(-180.0),
        Latitude(90.0)));

      EXPECT_EQ(GeoCoordinate2d(Longitude(-180.0), Latitude(-45.0)),
        geo_box.lower_left());
      EXPECT_EQ(GeoCoordinate2d(Longitude(90.0), Latitude(90.0)),
        geo_box.upper_right());
    }

    {
      GeoCoordinateBoundingBox2d geo_box(
        GeoCoordinate2d(Longitude(-90.0), Latitude(-45.0)),
        GeoCoordinate2d(Longitude(90.0), Latitude(45.0)));

      EXPECT_EQ(GeoCoordinate2d(Longitude(-90.0), Latitude(-45.0)),
        geo_box.lower_left());
      EXPECT_EQ(GeoCoordinate2d(Longitude(90.0), Latitude(45.0)),
        geo_box.upper_right());

      geo_box.grow_to_contain(GeoCoordinate2d(Longitude(180.0),
        Latitude(-90.0)));

      EXPECT_EQ(GeoCoordinate2d(Longitude(-90.0), Latitude(-90.0)),
        geo_box.lower_left());
      EXPECT_EQ(GeoCoordinate2d(Longitude(180.0), Latitude(45.0)),
        geo_box.upper_right());
    }

    {
      GeoCoordinateBoundingBox2d geo_box(
        GeoCoordinate2d(Longitude(-90.0), Latitude(-45.0)),
        GeoCoordinate2d(Longitude(90.0), Latitude(45.0)));

      EXPECT_EQ(GeoCoordinate2d(Longitude(-90.0), Latitude(-45.0)),
        geo_box.lower_left());
      EXPECT_EQ(GeoCoordinate2d(Longitude(90.0), Latitude(45.0)),
        geo_box.upper_right());

      geo_box.grow_to_contain(GeoCoordinate2d(Longitude(0.0),
        Latitude(0.0)));

      EXPECT_EQ(GeoCoordinate2d(Longitude(-90.0), Latitude(-45.0)),
        geo_box.lower_left());
      EXPECT_EQ(GeoCoordinate2d(Longitude(90.0), Latitude(45.0)),
        geo_box.upper_right());
    }
  }
}

#include <gtest/gtest.h>

#include "quad_key/geo_coordinate_bounding_box2d.h"
#include "quad_key/geo_coordinate2d.h"

#include <iostream>

namespace quad_keys
{
    class test_geo_coordinate_bounding_box2d : public ::testing::Test
    {
    protected:
      virtual void SetUp() {}
      virtual void TearDown() {}
    };

    TEST(GEOCOORDINATEBOUNDINGBOX2D, default_ctor)
    {
      geo_coordinate_bounding_box2d empty;
      ASSERT_FALSE(empty.is_valid());
      ASSERT_FALSE(empty.contains(
        geo_coordinate2d(longitude(0.0), latitude(0.0))));
    }

    TEST(GEOCOORDINATEBOUNDINGBOX2D, ctor_standard_construction)
    {
      { // Lower Left / Upper Right Construction
        geo_coordinate_bounding_box2d geo_box(
          geo_coordinate2d(longitude(0.0), latitude(0.0)),
          geo_coordinate2d(longitude(180.0), latitude(90.0)));

        EXPECT_EQ(geo_coordinate2d(longitude(0.0), latitude(0.0)),
          geo_box.lower_left());
        EXPECT_EQ(geo_coordinate2d(longitude(180.0), latitude(90.0)),
          geo_box.upper_right());
        EXPECT_TRUE(geo_box.is_valid());
      }

      { // Upper Left / Lower Right Construction
        geo_coordinate_bounding_box2d geo_box(
          geo_coordinate2d(longitude(0.0), latitude(90.0)),
          geo_coordinate2d(longitude(180.0), latitude(0.0)));

        EXPECT_EQ(geo_coordinate2d(longitude(0.0), latitude(0.0)),
          geo_box.lower_left());
        EXPECT_EQ(geo_coordinate2d(longitude(180.0), latitude(90.0)),
          geo_box.upper_right());
        EXPECT_TRUE(geo_box.is_valid());
      }

      { // Upper Right / Lower Left Construction
        geo_coordinate_bounding_box2d geo_box(
          geo_coordinate2d(longitude(180.0), latitude(0.0)),
          geo_coordinate2d(longitude(0.0), latitude(90.0)));

        EXPECT_EQ(geo_coordinate2d(longitude(0.0), latitude(0.0)),
          geo_box.lower_left());
        EXPECT_EQ(geo_coordinate2d(longitude(180.0), latitude(90.0)),
          geo_box.upper_right());
        EXPECT_TRUE(geo_box.is_valid());
      }

      { // Lower Right / Upper Left Construction
        geo_coordinate_bounding_box2d geo_box(
          geo_coordinate2d(longitude(180.0), latitude(0.0)),
          geo_coordinate2d(longitude(0.0), latitude(90.0)));

        EXPECT_EQ(geo_coordinate2d(longitude(0.0), latitude(0.0)),
          geo_box.lower_left());
        EXPECT_EQ(geo_coordinate2d(longitude(180.0), latitude(90.0)),
          geo_box.upper_right());
        EXPECT_TRUE(geo_box.is_valid());
      }
    }

    TEST(GEOCOORDINATEBOUNDINGBOX2D, ctor_linear_box_and_point)
    {
      { // Horizontal
        geo_coordinate_bounding_box2d geo_box(
          geo_coordinate2d(longitude(0.0), latitude(0.0)),
          geo_coordinate2d(longitude(0.0), latitude(90.0)));

        EXPECT_EQ(geo_coordinate2d(longitude(0.0), latitude(0.0)),
          geo_box.lower_left());
        EXPECT_EQ(geo_coordinate2d(longitude(0.0), latitude(90.0)),
          geo_box.upper_right());
        EXPECT_TRUE(geo_box.is_valid());
      }

      { // Vertical
        geo_coordinate_bounding_box2d geo_box(
          geo_coordinate2d(longitude(0.0), latitude(0.0)),
          geo_coordinate2d(longitude(180.0), latitude(0.0)));

        EXPECT_EQ(geo_coordinate2d(longitude(0.0), latitude(0.0)),
          geo_box.lower_left());
        EXPECT_EQ(geo_coordinate2d(longitude(180.0), latitude(0.0)),
          geo_box.upper_right());
        EXPECT_TRUE(geo_box.is_valid());
      }

      { // Point
        geo_coordinate_bounding_box2d geo_box(
          geo_coordinate2d(longitude(0.0), latitude(0.0)),
          geo_coordinate2d(longitude(0.0), latitude(0.0)));

        EXPECT_TRUE(geo_box.is_valid());
      }
    }

    TEST(GEOCOORDINATEBOUNDINGBOX2D, contains_or_not)
    {
      {
        geo_coordinate_bounding_box2d geo_box(
          geo_coordinate2d(longitude(90.0), latitude(45.0)),
          geo_coordinate2d(longitude(-90.0), latitude(-45.0)));

        EXPECT_TRUE(geo_box.is_valid());

        EXPECT_TRUE(geo_box.contains(geo_coordinate2d(longitude(0.0),
          latitude(0.0))));

        EXPECT_TRUE(geo_box.contains(geo_coordinate2d(longitude(90.0),
          latitude(45.0))));
        EXPECT_TRUE(geo_box.contains(geo_coordinate2d(longitude(90.0),
          latitude(-45.0))));
        EXPECT_TRUE(geo_box.contains(geo_coordinate2d(longitude(-90.0),
          latitude(-45.0))));
        EXPECT_TRUE(geo_box.contains(geo_coordinate2d(longitude(-90.0),
          latitude(45.0))));

        EXPECT_FALSE(geo_box.contains(geo_coordinate2d(longitude(90.01),
          latitude(45.01))));
        EXPECT_FALSE(geo_box.contains(geo_coordinate2d(longitude(90.01),
          latitude(-45.01))));
        EXPECT_FALSE(geo_box.contains(geo_coordinate2d(longitude(-90.01),
          latitude(-45.01))));
        EXPECT_FALSE(geo_box.contains(geo_coordinate2d(longitude(-90.01),
          latitude(45.01))));
      }

      {
        geo_coordinate_bounding_box2d geo_box(
          geo_coordinate2d(longitude(90.0), latitude(45.0)),
          geo_coordinate2d(longitude(0.1), latitude(0.1)));

        EXPECT_EQ(geo_coordinate2d(longitude(0.1), latitude(0.1)),
          geo_box.lower_left());
        EXPECT_EQ(geo_coordinate2d(longitude(90.0), latitude(45.0)),
          geo_box.upper_right());

        EXPECT_TRUE(geo_box.is_valid());

        EXPECT_TRUE(geo_box.contains(geo_coordinate2d(longitude(90.0),
          latitude(45.0))));
        EXPECT_TRUE(geo_box.contains(geo_coordinate2d(longitude(90.0),
          latitude(0.1))));
        EXPECT_TRUE(geo_box.contains(geo_coordinate2d(longitude(0.1),
          latitude(0.1))));
        EXPECT_TRUE(geo_box.contains(geo_coordinate2d(longitude(0.1),
          latitude(45.0))));

        EXPECT_FALSE(geo_box.contains(geo_coordinate2d(longitude(90.01),
          latitude(45.01))));
        EXPECT_FALSE(geo_box.contains(geo_coordinate2d(longitude(90.01),
          latitude(0.0))));
        EXPECT_FALSE(geo_box.contains(geo_coordinate2d(longitude(0.0),
          latitude(0.0))));
        EXPECT_FALSE(geo_box.contains(geo_coordinate2d(longitude(0.0),
          latitude(45.01))));
      }
    }

    TEST(GEOCOORDINATEBOUNDINGBOX2D, grow_to_contain)
    {
      {
        geo_coordinate_bounding_box2d geo_box(
          geo_coordinate2d(longitude(-90.0), latitude(-45.0)),
          geo_coordinate2d(longitude(90.0), latitude(45.0)));

        EXPECT_EQ(geo_coordinate2d(longitude(-90.0), latitude(-45.0)),
          geo_box.lower_left());
        EXPECT_EQ(geo_coordinate2d(longitude(90.0), latitude(45.0)),
          geo_box.upper_right());

        geo_box.grow_to_contain(geo_coordinate2d(longitude(180.0),
          latitude(90.0)));

        EXPECT_EQ(geo_coordinate2d(longitude(-90.0), latitude(-45.0)),
          geo_box.lower_left());
        EXPECT_EQ(geo_coordinate2d(longitude(180.0), latitude(90.0)),
          geo_box.upper_right());
      }

      {
        geo_coordinate_bounding_box2d geo_box(
          geo_coordinate2d(longitude(-90.0), latitude(-45.0)),
          geo_coordinate2d(longitude(90.0), latitude(45.0)));

        EXPECT_EQ(geo_coordinate2d(longitude(-90.0), latitude(-45.0)),
          geo_box.lower_left());
        EXPECT_EQ(geo_coordinate2d(longitude(90.0), latitude(45.0)),
          geo_box.upper_right());

        geo_box.grow_to_contain(geo_coordinate2d(longitude(-180.0),
          latitude(-90.0)));

        EXPECT_EQ(geo_coordinate2d(longitude(-180.0), latitude(-90.0)),
          geo_box.lower_left());
        EXPECT_EQ(geo_coordinate2d(longitude(90.0), latitude(45.0)),
          geo_box.upper_right());
      }

      {
        geo_coordinate_bounding_box2d geo_box(
          geo_coordinate2d(longitude(-90.0), latitude(-45.0)),
          geo_coordinate2d(longitude(90.0), latitude(45.0)));

        EXPECT_EQ(geo_coordinate2d(longitude(-90.0), latitude(-45.0)),
          geo_box.lower_left());
        EXPECT_EQ(geo_coordinate2d(longitude(90.0), latitude(45.0)),
          geo_box.upper_right());

        geo_box.grow_to_contain(geo_coordinate2d(longitude(-180.0),
          latitude(90.0)));

        EXPECT_EQ(geo_coordinate2d(longitude(-180.0), latitude(-45.0)),
          geo_box.lower_left());
        EXPECT_EQ(geo_coordinate2d(longitude(90.0), latitude(90.0)),
          geo_box.upper_right());
      }

      {
        geo_coordinate_bounding_box2d geo_box(
          geo_coordinate2d(longitude(-90.0), latitude(-45.0)),
          geo_coordinate2d(longitude(90.0), latitude(45.0)));

        EXPECT_EQ(geo_coordinate2d(longitude(-90.0), latitude(-45.0)),
          geo_box.lower_left());
        EXPECT_EQ(geo_coordinate2d(longitude(90.0), latitude(45.0)),
          geo_box.upper_right());

        geo_box.grow_to_contain(geo_coordinate2d(longitude(180.0),
          latitude(-90.0)));

        EXPECT_EQ(geo_coordinate2d(longitude(-90.0), latitude(-90.0)),
          geo_box.lower_left());
        EXPECT_EQ(geo_coordinate2d(longitude(180.0), latitude(45.0)),
          geo_box.upper_right());
      }

      {
        geo_coordinate_bounding_box2d geo_box(
          geo_coordinate2d(longitude(-90.0), latitude(-45.0)),
          geo_coordinate2d(longitude(90.0), latitude(45.0)));

        EXPECT_EQ(geo_coordinate2d(longitude(-90.0), latitude(-45.0)),
          geo_box.lower_left());
        EXPECT_EQ(geo_coordinate2d(longitude(90.0), latitude(45.0)),
          geo_box.upper_right());

        geo_box.grow_to_contain(geo_coordinate2d(longitude(0.0),
          latitude(0.0)));

        EXPECT_EQ(geo_coordinate2d(longitude(-90.0), latitude(-45.0)),
          geo_box.lower_left());
        EXPECT_EQ(geo_coordinate2d(longitude(90.0), latitude(45.0)),
          geo_box.upper_right());
      }
    }
}

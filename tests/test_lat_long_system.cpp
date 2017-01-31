#include <gtest/gtest.h>

#include "quad_key/geo_coordinate2d.h"
#include "quad_key/quad_key.h"

#include <iostream>

namespace quad_keys
{
  class test_lat_long_system : public ::testing::Test
  {
  protected:
    virtual void SetUp() {}
    virtual void TearDown() {}
  };

  TEST(LATLONGSYSTEM, is_valid)
  {
    // Same as bing_system
  }

  TEST(LATLONGSYSTEM, is_root_key)
  {
    // Same as bing_system
  }

  TEST(LATLONGSYSTEM, get_parent)
  {
    // Same as bing_system
  }

  TEST(LATLONGSYSTEM, is_my_ancestor)
  {
    // Same as bing_system
  }

  TEST(LATLONGSYSTEM, get_ancestor)
  {
    // Same as bing_system
  }

  TEST(LATLONGSYSTEM, get_child)
  {
    // Same as bing_system
  }

  TEST(LATLONGSYSTEM, get_children)
  {
    // Same as bing_system
  }

  TEST(LATLONGSYSTEM, get_descendants)
  {
    // Same as bing_system
  }

  TEST(LATLONGSYSTEM, get_siblings)
  {
    // Same as bing_system
  }

  TEST(LATLONGSYSTEM, get_neighbors)
  {
    // Same as bing_system
  }

  TEST(LATLONGSYSTEM, from_string_to_string)
  {
    // Same as bing_system
  }

  TEST(LATLONGSYSTEM, get_geocoordinate_bounds2d)
  {
    quad_key key;
    geo_coordinate_bounding_box2d bbox;

    { // Depth 0
      key = quad_key(type::lat_long, 0, 0, 0);
      key.get_geo_coordinate_bounds2d(bbox);
      EXPECT_EQ(geo_coordinate2d(longitude(-180.0), latitude(-90.0)),
        bbox.lower_left());
      EXPECT_EQ(geo_coordinate2d(longitude(+180.0), latitude(+90.0)),
        bbox.upper_right());
    }

    { // Depth 1
      key = quad_key(type::lat_long, 0, 0, 1);
      key.get_geo_coordinate_bounds2d(bbox);
      EXPECT_TRUE(bbox.lower_left().get_longitude().near(
        longitude(-180.0), std::numeric_limits<float>::epsilon()));
      EXPECT_TRUE(bbox.lower_left().get_latitude().near(
        latitude(-90.0), std::numeric_limits<float>::epsilon()));
      EXPECT_TRUE(bbox.upper_right().get_longitude().near(
        longitude(+0.0), std::numeric_limits<float>::epsilon()));
      EXPECT_TRUE(bbox.upper_right().get_latitude().near(
        latitude(+0.0), std::numeric_limits<float>::epsilon()));

      key = quad_key(type::lat_long, 0, 1, 1);
      key.get_geo_coordinate_bounds2d(bbox);
      EXPECT_TRUE(bbox.lower_left().get_longitude().near(
        longitude(+0.0), std::numeric_limits<float>::epsilon()));
      EXPECT_TRUE(bbox.lower_left().get_latitude().near(
        latitude(-90.0), std::numeric_limits<float>::epsilon()));
      EXPECT_TRUE(bbox.upper_right().get_longitude().near(
        longitude(+180.0), std::numeric_limits<float>::epsilon()));
      EXPECT_TRUE(bbox.upper_right().get_latitude().near(
        latitude(+0.0), std::numeric_limits<float>::epsilon()));

      key = quad_key(type::lat_long, 1, 0, 1);
      key.get_geo_coordinate_bounds2d(bbox);
      EXPECT_TRUE(bbox.lower_left().get_longitude().near(
        longitude(-180.0), std::numeric_limits<float>::epsilon()));
      EXPECT_TRUE(bbox.lower_left().get_latitude().near(
        latitude(+0.0), std::numeric_limits<float>::epsilon()));
      EXPECT_TRUE(bbox.upper_right().get_longitude().near(
        longitude(+0.0), std::numeric_limits<float>::epsilon()));
      EXPECT_TRUE(bbox.upper_right().get_latitude().near(
        latitude(+90.0), std::numeric_limits<float>::epsilon()));

      key = quad_key(type::lat_long, 1, 1, 1);
      key.get_geo_coordinate_bounds2d(bbox);
      EXPECT_TRUE(bbox.lower_left().get_longitude().near(
        longitude(+0.0), std::numeric_limits<float>::epsilon()));
      EXPECT_TRUE(bbox.lower_left().get_latitude().near(
        latitude(+0.0), std::numeric_limits<float>::epsilon()));
      EXPECT_TRUE(bbox.upper_right().get_longitude().near(
        longitude(+180.0), std::numeric_limits<float>::epsilon()));
      EXPECT_TRUE(bbox.upper_right().get_latitude().near(
        latitude(+90.0), std::numeric_limits<float>::epsilon()));
    }
  }

  TEST(LATLONGSYSTEM, get_key_from_longitude_latitude_at_depth_to_bounds)
  {
     quad_key key;

      { // Depth 0
        key = quad_key::get_key_from_longitude_latitude_at_depth(
            type::lat_long, geo_coordinate2d(longitude(-180.0),
            latitude(-90)), 0u);
        EXPECT_EQ(quad_key(type::lat_long, 0, 0, 0), key);
        EXPECT_EQ("", key.to_internal_string());
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
        key = quad_key::get_key_from_longitude_latitude_at_depth( // Q0 ll
          type::lat_long, geo_coordinate2d(longitude(-180.0),
          latitude(-90.0)), 1u);
        EXPECT_EQ(quad_key(type::lat_long, 0, 0, 1), key);
        EXPECT_EQ("2", key.to_internal_string());
        key = quad_key::get_key_from_longitude_latitude_at_depth( // Q0 lr
          type::lat_long, geo_coordinate2d(longitude(-0.1),
          latitude(-90.0)), 1u);
        EXPECT_EQ(quad_key(type::lat_long, 0, 0, 1), key);
        EXPECT_EQ("2", key.to_internal_string());
        key = quad_key::get_key_from_longitude_latitude_at_depth( // Q0 ur
          type::lat_long, geo_coordinate2d(longitude(-0.1),
          latitude(-0.1)), 1u);
        EXPECT_EQ(quad_key(type::lat_long, 0, 0, 1), key);
        EXPECT_EQ("2", key.to_internal_string());
        key = quad_key::get_key_from_longitude_latitude_at_depth( // Q0 ul
          type::lat_long, geo_coordinate2d(longitude(-180.0),
          latitude(-0.1)), 1u);
        EXPECT_EQ(quad_key(type::lat_long, 0, 0, 1), key);
        EXPECT_EQ("2", key.to_internal_string());

        key = quad_key::get_key_from_longitude_latitude_at_depth( // Q1 ll
          type::lat_long, geo_coordinate2d(longitude(+0.0),
          latitude(-90.0)), 1u);
        EXPECT_EQ(quad_key(type::lat_long, 0, 1, 1), key);
        EXPECT_EQ("3", key.to_internal_string());
        key = quad_key::get_key_from_longitude_latitude_at_depth( // Q1 lr
          type::lat_long, geo_coordinate2d(longitude(+180.0),
          latitude(-90.0)), 1u);
        EXPECT_EQ(quad_key(type::lat_long, 0, 1, 1), key);
        EXPECT_EQ("3", key.to_internal_string());
        key = quad_key::get_key_from_longitude_latitude_at_depth( // Q1 ur
          type::lat_long, geo_coordinate2d(longitude(+180.0),
          latitude(-0.1)), 1u);
        EXPECT_EQ(quad_key(type::lat_long, 0, 1, 1), key);
        EXPECT_EQ("3", key.to_internal_string());
        key = quad_key::get_key_from_longitude_latitude_at_depth( // Q1 ul
          type::lat_long, geo_coordinate2d(longitude(+0.0),
          latitude(-0.1)), 1u);
        EXPECT_EQ(quad_key(type::lat_long, 0, 1, 1), key);
        EXPECT_EQ("3", key.to_internal_string());

        key = quad_key::get_key_from_longitude_latitude_at_depth( // Q2 ll
          type::lat_long, geo_coordinate2d(longitude(-180.0),
          latitude(+0.0)), 1u);
        EXPECT_EQ(quad_key(type::lat_long, 1, 0, 1), key);
        EXPECT_EQ("0", key.to_internal_string());
        key = quad_key::get_key_from_longitude_latitude_at_depth( // Q2 lr
          type::lat_long, geo_coordinate2d(longitude(-0.1),
          latitude(+0.0)), 1u);
        EXPECT_EQ(quad_key(type::lat_long, 1, 0, 1), key);
        EXPECT_EQ("0", key.to_internal_string());
        key = quad_key::get_key_from_longitude_latitude_at_depth( // Q2 ur
          type::lat_long, geo_coordinate2d(longitude(-180.0),
          latitude(+90.0)), 1u);
        EXPECT_EQ(quad_key(type::lat_long, 1, 0, 1), key);
        EXPECT_EQ("0", key.to_internal_string());
        key = quad_key::get_key_from_longitude_latitude_at_depth( // Q2 ul
          type::lat_long, geo_coordinate2d(longitude(-0.1),
          latitude(+90.0)), 1u);
        EXPECT_EQ(quad_key(type::lat_long, 1, 0, 1), key);
        EXPECT_EQ("0", key.to_internal_string());

        key = quad_key::get_key_from_longitude_latitude_at_depth( // Q3 ll
          type::lat_long, geo_coordinate2d(longitude(+0.0),
          latitude(+0.0)), 1u);
        EXPECT_EQ(quad_key(type::lat_long, 1, 1, 1), key);
        EXPECT_EQ("1", key.to_internal_string());
        key = quad_key::get_key_from_longitude_latitude_at_depth( // Q3 lr
          type::lat_long, geo_coordinate2d(longitude(+180.0),
          latitude(+0.0)), 1u);
        EXPECT_EQ(quad_key(type::lat_long, 1, 1, 1), key);
        EXPECT_EQ("1", key.to_internal_string());
        key = quad_key::get_key_from_longitude_latitude_at_depth( // Q3 ur
          type::lat_long, geo_coordinate2d(longitude(+0.0),
          latitude(+90.0)), 1u);
        EXPECT_EQ(quad_key(type::lat_long, 1, 1, 1), key);
        EXPECT_EQ("1", key.to_internal_string());
        key = quad_key::get_key_from_longitude_latitude_at_depth( // Q3 ul
          type::lat_long, geo_coordinate2d(longitude(+180.0),
          latitude(+90.0)), 1u);
        EXPECT_EQ(quad_key(type::lat_long, 1, 1, 1), key);
        EXPECT_EQ("1", key.to_internal_string());
      }
  }

  TEST(LATLONGSYSTEM, get_keys_from_longitude_latitude_bounding_box)
  {
    {
      std::vector<quad_key> out_keys;
      out_keys = quad_key::get_keys_from_longitude_latitude_bounding_box(
        type::lat_long,
        geo_coordinate_bounding_box2d(
          geo_coordinate2d(longitude(-180.0), latitude(+90.0)),
          geo_coordinate2d(longitude(+180.0), latitude(-90.0))), 0);
      EXPECT_EQ(1u, out_keys.size());
      EXPECT_NE(out_keys.end(), std::find(out_keys.begin(), out_keys.end(),
        quad_key(type::lat_long, 0, 0, 0)));
    }

    {
      std::vector<quad_key> out_keys;
      out_keys = quad_key::get_keys_from_longitude_latitude_bounding_box(
        type::lat_long,
        geo_coordinate_bounding_box2d(
          geo_coordinate2d(longitude(-180.0), latitude(+90.0)),
          geo_coordinate2d(longitude(+180.0), latitude(-90.0))), 1);
      EXPECT_EQ(4u, out_keys.size());
      EXPECT_NE(out_keys.end(), std::find(out_keys.begin(), out_keys.end(),
        quad_key(type::lat_long, 0, 0, 1)));
      EXPECT_NE(out_keys.end(), std::find(out_keys.begin(), out_keys.end(),
        quad_key(type::lat_long, 0, 1, 1)));
      EXPECT_NE(out_keys.end(), std::find(out_keys.begin(), out_keys.end(),
        quad_key(type::lat_long, 1, 0, 1)));
      EXPECT_NE(out_keys.end(), std::find(out_keys.begin(), out_keys.end(),
        quad_key(type::lat_long, 1, 1, 1)));
    }

    {
      std::vector<quad_key> out_keys;
      out_keys = quad_key::get_keys_from_longitude_latitude_bounding_box(
        type::lat_long,
        geo_coordinate_bounding_box2d(
          geo_coordinate2d(longitude(-180.0), latitude(-0.1)),
          geo_coordinate2d(longitude(-0.1), latitude(+90.0))), 1);
      EXPECT_EQ(2u, out_keys.size());
      EXPECT_NE(out_keys.end(), std::find(out_keys.begin(), out_keys.end(),
        quad_key(type::lat_long, 0, 0, 1)));
      EXPECT_NE(out_keys.end(), std::find(out_keys.begin(), out_keys.end(),
        quad_key(type::lat_long, 1, 0, 1)));
    }

    {
      std::vector<quad_key> out_keys;
      out_keys = quad_key::get_keys_from_longitude_latitude_bounding_box(
        type::lat_long,
        geo_coordinate_bounding_box2d(
          geo_coordinate2d(longitude(+0.0), latitude(-0.1)),
          geo_coordinate2d(longitude(+180.0), latitude(+90.0))), 1);
      EXPECT_EQ(2u, out_keys.size());
      EXPECT_NE(out_keys.end(), std::find(out_keys.begin(), out_keys.end(),
        quad_key(type::lat_long, 0, 1, 1)));
      EXPECT_NE(out_keys.end(), std::find(out_keys.begin(), out_keys.end(),
        quad_key(type::lat_long, 1, 1, 1)));
    }

    {
      std::vector<quad_key> out_keys;
      out_keys = quad_key::get_keys_from_longitude_latitude_bounding_box(
        type::lat_long,
        geo_coordinate_bounding_box2d(
          geo_coordinate2d(longitude(-0.1), latitude(-0.1)),
          geo_coordinate2d(longitude(+0.1), latitude(+0.1))), 1);
      EXPECT_EQ(4u, out_keys.size());
      EXPECT_NE(out_keys.end(), std::find(out_keys.begin(), out_keys.end(),
          quad_key(type::lat_long, 0, 0, 1)));
      EXPECT_NE(out_keys.end(), std::find(out_keys.begin(), out_keys.end(),
          quad_key(type::lat_long, 0, 1, 1)));
      EXPECT_NE(out_keys.end(), std::find(out_keys.begin(), out_keys.end(),
          quad_key(type::lat_long, 1, 0, 1)));
      EXPECT_NE(out_keys.end(), std::find(out_keys.begin(), out_keys.end(),
          quad_key(type::lat_long, 1, 1, 1)));
    }
  }

  TEST(LATLONGSYSTEM, test_known_sample_of_locations)
  {
    quad_key key;

    {
      key = quad_key::get_key_from_longitude_latitude_at_depth(
        type::lat_long, geo_coordinate2d(longitude(-122.4183),
        latitude(37.7750)), 1u);
      EXPECT_EQ("0", key.to_internal_string());
      key = quad_key::get_key_from_longitude_latitude_at_depth(
        type::lat_long, geo_coordinate2d(longitude(-122.4183),
        latitude(37.7750)), 2u);
      EXPECT_EQ("02", key.to_internal_string());
      key = quad_key::get_key_from_longitude_latitude_at_depth(
        type::lat_long, geo_coordinate2d(longitude(-122.4183),
        latitude(37.7750)), 3u);
      EXPECT_EQ("021", key.to_internal_string());
      key = quad_key::get_key_from_longitude_latitude_at_depth(
        type::lat_long, geo_coordinate2d(longitude(-122.4183),
        latitude(37.7750)), 4u);
      EXPECT_EQ("0210", key.to_internal_string());
    }

    {
      key = quad_key::get_key_from_longitude_latitude_at_depth(
        type::lat_long, geo_coordinate2d(longitude(+134.9),
        latitude(-67.6)), 3u);
      EXPECT_EQ(quad_key(type::lat_long, 0, 6, 3), key);
      EXPECT_EQ("332", key.to_internal_string());

      key = quad_key::get_key_from_longitude_latitude_at_depth(
        type::lat_long, geo_coordinate2d(longitude(+135.0),
        latitude(-67.5)), 3u);
      EXPECT_EQ(quad_key(type::lat_long, 1, 7, 3), key);
      EXPECT_EQ("331", key.to_internal_string());
    }
  }
}

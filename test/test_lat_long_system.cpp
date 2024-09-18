#include <gtest/gtest.h>

#include <iostream>

#include "quad_keys/geo_coordinate2d.h"
#include "quad_keys/quad_key.h"

namespace quad_keys {
class TestLatLongSystem : public ::testing::Test {
 protected:
  virtual void SetUp() {}
  virtual void TearDown() {}
};

TEST(LATLONGSYSTEM, is_valid) {
  // Same as bing_system
}

TEST(LATLONGSYSTEM, is_root_key) {
  // Same as bing_system
}

TEST(LATLONGSYSTEM, get_parent) {
  // Same as bing_system
}

TEST(LATLONGSYSTEM, is_my_ancestor) {
  // Same as bing_system
}

TEST(LATLONGSYSTEM, get_ancestor) {
  // Same as bing_system
}

TEST(LATLONGSYSTEM, get_child) {
  // Same as bing_system
}

TEST(LATLONGSYSTEM, get_children) {
  // Same as bing_system
}

TEST(LATLONGSYSTEM, get_descendants) {
  // Same as bing_system
}

TEST(LATLONGSYSTEM, get_siblings) {
  // Same as bing_system
}

TEST(LATLONGSYSTEM, get_neighbors) {
  // Same as bing_system
}

TEST(LATLONGSYSTEM, from_string_to_string) {
  // Same as bing_system
}

TEST(LATLONGSYSTEM, get_geocoordinate_bounds2d) {
  QuadKey key;
  GeoCoordinateBoundingBox2d bbox;

  {  // Depth 0
    key = QuadKey(Type::LatLon, 0, 0, 0);
    key.get_geo_coordinate_bounds2d(bbox);
    EXPECT_EQ(GeoCoordinate2d(Longitude(-180.0), Latitude(-90.0)),
              bbox.lower_left());
    EXPECT_EQ(GeoCoordinate2d(Longitude(+180.0), Latitude(+90.0)),
              bbox.upper_right());
  }

  {  // Depth 1
    key = QuadKey(Type::LatLon, 0, 0, 1);
    key.get_geo_coordinate_bounds2d(bbox);
    EXPECT_TRUE(bbox.lower_left().get_longitude().near(
        Longitude(-180.0), std::numeric_limits<float>::epsilon()));
    EXPECT_TRUE(bbox.lower_left().get_latitude().near(
        Latitude(-90.0), std::numeric_limits<float>::epsilon()));
    EXPECT_TRUE(bbox.upper_right().get_longitude().near(
        Longitude(+0.0), std::numeric_limits<float>::epsilon()));
    EXPECT_TRUE(bbox.upper_right().get_latitude().near(
        Latitude(+0.0), std::numeric_limits<float>::epsilon()));

    key = QuadKey(Type::LatLon, 0, 1, 1);
    key.get_geo_coordinate_bounds2d(bbox);
    EXPECT_TRUE(bbox.lower_left().get_longitude().near(
        Longitude(+0.0), std::numeric_limits<float>::epsilon()));
    EXPECT_TRUE(bbox.lower_left().get_latitude().near(
        Latitude(-90.0), std::numeric_limits<float>::epsilon()));
    EXPECT_TRUE(bbox.upper_right().get_longitude().near(
        Longitude(+180.0), std::numeric_limits<float>::epsilon()));
    EXPECT_TRUE(bbox.upper_right().get_latitude().near(
        Latitude(+0.0), std::numeric_limits<float>::epsilon()));

    key = QuadKey(Type::LatLon, 1, 0, 1);
    key.get_geo_coordinate_bounds2d(bbox);
    EXPECT_TRUE(bbox.lower_left().get_longitude().near(
        Longitude(-180.0), std::numeric_limits<float>::epsilon()));
    EXPECT_TRUE(bbox.lower_left().get_latitude().near(
        Latitude(+0.0), std::numeric_limits<float>::epsilon()));
    EXPECT_TRUE(bbox.upper_right().get_longitude().near(
        Longitude(+0.0), std::numeric_limits<float>::epsilon()));
    EXPECT_TRUE(bbox.upper_right().get_latitude().near(
        Latitude(+90.0), std::numeric_limits<float>::epsilon()));

    key = QuadKey(Type::LatLon, 1, 1, 1);
    key.get_geo_coordinate_bounds2d(bbox);
    EXPECT_TRUE(bbox.lower_left().get_longitude().near(
        Longitude(+0.0), std::numeric_limits<float>::epsilon()));
    EXPECT_TRUE(bbox.lower_left().get_latitude().near(
        Latitude(+0.0), std::numeric_limits<float>::epsilon()));
    EXPECT_TRUE(bbox.upper_right().get_longitude().near(
        Longitude(+180.0), std::numeric_limits<float>::epsilon()));
    EXPECT_TRUE(bbox.upper_right().get_latitude().near(
        Latitude(+90.0), std::numeric_limits<float>::epsilon()));
  }
}

TEST(LATLONGSYSTEM, get_key_from_longitude_latitude_at_depth_to_bounds) {
  QuadKey key;

  {  // Depth 0
    key = QuadKey::get_key_from_longitude_latitude_at_depth(
        Type::LatLon, GeoCoordinate2d(Longitude(-180.0), Latitude(-90)), 0u);
    EXPECT_EQ(QuadKey(Type::LatLon, 0, 0, 0), key);
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
  {                                                           // Depth 1
    key = QuadKey::get_key_from_longitude_latitude_at_depth(  // Q0 ll
        Type::LatLon, GeoCoordinate2d(Longitude(-180.0), Latitude(-90.0)), 1u);
    EXPECT_EQ(QuadKey(Type::LatLon, 0, 0, 1), key);
    EXPECT_EQ("2", key.to_internal_string());
    key = QuadKey::get_key_from_longitude_latitude_at_depth(  // Q0 lr
        Type::LatLon, GeoCoordinate2d(Longitude(-0.1), Latitude(-90.0)), 1u);
    EXPECT_EQ(QuadKey(Type::LatLon, 0, 0, 1), key);
    EXPECT_EQ("2", key.to_internal_string());
    key = QuadKey::get_key_from_longitude_latitude_at_depth(  // Q0 ur
        Type::LatLon, GeoCoordinate2d(Longitude(-0.1), Latitude(-0.1)), 1u);
    EXPECT_EQ(QuadKey(Type::LatLon, 0, 0, 1), key);
    EXPECT_EQ("2", key.to_internal_string());
    key = QuadKey::get_key_from_longitude_latitude_at_depth(  // Q0 ul
        Type::LatLon, GeoCoordinate2d(Longitude(-180.0), Latitude(-0.1)), 1u);
    EXPECT_EQ(QuadKey(Type::LatLon, 0, 0, 1), key);
    EXPECT_EQ("2", key.to_internal_string());

    key = QuadKey::get_key_from_longitude_latitude_at_depth(  // Q1 ll
        Type::LatLon, GeoCoordinate2d(Longitude(+0.0), Latitude(-90.0)), 1u);
    EXPECT_EQ(QuadKey(Type::LatLon, 0, 1, 1), key);
    EXPECT_EQ("3", key.to_internal_string());
    key = QuadKey::get_key_from_longitude_latitude_at_depth(  // Q1 lr
        Type::LatLon, GeoCoordinate2d(Longitude(+180.0), Latitude(-90.0)), 1u);
    EXPECT_EQ(QuadKey(Type::LatLon, 0, 1, 1), key);
    EXPECT_EQ("3", key.to_internal_string());
    key = QuadKey::get_key_from_longitude_latitude_at_depth(  // Q1 ur
        Type::LatLon, GeoCoordinate2d(Longitude(+180.0), Latitude(-0.1)), 1u);
    EXPECT_EQ(QuadKey(Type::LatLon, 0, 1, 1), key);
    EXPECT_EQ("3", key.to_internal_string());
    key = QuadKey::get_key_from_longitude_latitude_at_depth(  // Q1 ul
        Type::LatLon, GeoCoordinate2d(Longitude(+0.0), Latitude(-0.1)), 1u);
    EXPECT_EQ(QuadKey(Type::LatLon, 0, 1, 1), key);
    EXPECT_EQ("3", key.to_internal_string());

    key = QuadKey::get_key_from_longitude_latitude_at_depth(  // Q2 ll
        Type::LatLon, GeoCoordinate2d(Longitude(-180.0), Latitude(+0.0)), 1u);
    EXPECT_EQ(QuadKey(Type::LatLon, 1, 0, 1), key);
    EXPECT_EQ("0", key.to_internal_string());
    key = QuadKey::get_key_from_longitude_latitude_at_depth(  // Q2 lr
        Type::LatLon, GeoCoordinate2d(Longitude(-0.1), Latitude(+0.0)), 1u);
    EXPECT_EQ(QuadKey(Type::LatLon, 1, 0, 1), key);
    EXPECT_EQ("0", key.to_internal_string());
    key = QuadKey::get_key_from_longitude_latitude_at_depth(  // Q2 ur
        Type::LatLon, GeoCoordinate2d(Longitude(-180.0), Latitude(+90.0)), 1u);
    EXPECT_EQ(QuadKey(Type::LatLon, 1, 0, 1), key);
    EXPECT_EQ("0", key.to_internal_string());
    key = QuadKey::get_key_from_longitude_latitude_at_depth(  // Q2 ul
        Type::LatLon, GeoCoordinate2d(Longitude(-0.1), Latitude(+90.0)), 1u);
    EXPECT_EQ(QuadKey(Type::LatLon, 1, 0, 1), key);
    EXPECT_EQ("0", key.to_internal_string());

    key = QuadKey::get_key_from_longitude_latitude_at_depth(  // Q3 ll
        Type::LatLon, GeoCoordinate2d(Longitude(+0.0), Latitude(+0.0)), 1u);
    EXPECT_EQ(QuadKey(Type::LatLon, 1, 1, 1), key);
    EXPECT_EQ("1", key.to_internal_string());
    key = QuadKey::get_key_from_longitude_latitude_at_depth(  // Q3 lr
        Type::LatLon, GeoCoordinate2d(Longitude(+180.0), Latitude(+0.0)), 1u);
    EXPECT_EQ(QuadKey(Type::LatLon, 1, 1, 1), key);
    EXPECT_EQ("1", key.to_internal_string());
    key = QuadKey::get_key_from_longitude_latitude_at_depth(  // Q3 ur
        Type::LatLon, GeoCoordinate2d(Longitude(+0.0), Latitude(+90.0)), 1u);
    EXPECT_EQ(QuadKey(Type::LatLon, 1, 1, 1), key);
    EXPECT_EQ("1", key.to_internal_string());
    key = QuadKey::get_key_from_longitude_latitude_at_depth(  // Q3 ul
        Type::LatLon, GeoCoordinate2d(Longitude(+180.0), Latitude(+90.0)), 1u);
    EXPECT_EQ(QuadKey(Type::LatLon, 1, 1, 1), key);
    EXPECT_EQ("1", key.to_internal_string());
  }
}

TEST(LATLONGSYSTEM, get_keys_from_longitude_latitude_bounding_box) {
  {
    std::vector<QuadKey> out_keys;
    out_keys = QuadKey::get_keys_from_longitude_latitude_bounding_box(
        Type::LatLon,
        GeoCoordinateBoundingBox2d(
            GeoCoordinate2d(Longitude(-180.0), Latitude(+90.0)),
            GeoCoordinate2d(Longitude(+180.0), Latitude(-90.0))),
        0);
    EXPECT_EQ(1u, out_keys.size());
    EXPECT_NE(out_keys.end(), std::find(out_keys.begin(), out_keys.end(),
                                        QuadKey(Type::LatLon, 0, 0, 0)));
  }

  {
    std::vector<QuadKey> out_keys;
    out_keys = QuadKey::get_keys_from_longitude_latitude_bounding_box(
        Type::LatLon,
        GeoCoordinateBoundingBox2d(
            GeoCoordinate2d(Longitude(-180.0), Latitude(+90.0)),
            GeoCoordinate2d(Longitude(+180.0), Latitude(-90.0))),
        1);
    EXPECT_EQ(4u, out_keys.size());
    EXPECT_NE(out_keys.end(), std::find(out_keys.begin(), out_keys.end(),
                                        QuadKey(Type::LatLon, 0, 0, 1)));
    EXPECT_NE(out_keys.end(), std::find(out_keys.begin(), out_keys.end(),
                                        QuadKey(Type::LatLon, 0, 1, 1)));
    EXPECT_NE(out_keys.end(), std::find(out_keys.begin(), out_keys.end(),
                                        QuadKey(Type::LatLon, 1, 0, 1)));
    EXPECT_NE(out_keys.end(), std::find(out_keys.begin(), out_keys.end(),
                                        QuadKey(Type::LatLon, 1, 1, 1)));
  }

  {
    std::vector<QuadKey> out_keys;
    out_keys = QuadKey::get_keys_from_longitude_latitude_bounding_box(
        Type::LatLon,
        GeoCoordinateBoundingBox2d(
            GeoCoordinate2d(Longitude(-180.0), Latitude(-0.1)),
            GeoCoordinate2d(Longitude(-0.1), Latitude(+90.0))),
        1);
    EXPECT_EQ(2u, out_keys.size());
    EXPECT_NE(out_keys.end(), std::find(out_keys.begin(), out_keys.end(),
                                        QuadKey(Type::LatLon, 0, 0, 1)));
    EXPECT_NE(out_keys.end(), std::find(out_keys.begin(), out_keys.end(),
                                        QuadKey(Type::LatLon, 1, 0, 1)));
  }

  {
    std::vector<QuadKey> out_keys;
    out_keys = QuadKey::get_keys_from_longitude_latitude_bounding_box(
        Type::LatLon,
        GeoCoordinateBoundingBox2d(
            GeoCoordinate2d(Longitude(+0.0), Latitude(-0.1)),
            GeoCoordinate2d(Longitude(+180.0), Latitude(+90.0))),
        1);
    EXPECT_EQ(2u, out_keys.size());
    EXPECT_NE(out_keys.end(), std::find(out_keys.begin(), out_keys.end(),
                                        QuadKey(Type::LatLon, 0, 1, 1)));
    EXPECT_NE(out_keys.end(), std::find(out_keys.begin(), out_keys.end(),
                                        QuadKey(Type::LatLon, 1, 1, 1)));
  }

  {
    std::vector<QuadKey> out_keys;
    out_keys = QuadKey::get_keys_from_longitude_latitude_bounding_box(
        Type::LatLon,
        GeoCoordinateBoundingBox2d(
            GeoCoordinate2d(Longitude(-0.1), Latitude(-0.1)),
            GeoCoordinate2d(Longitude(+0.1), Latitude(+0.1))),
        1);
    EXPECT_EQ(4u, out_keys.size());
    EXPECT_NE(out_keys.end(), std::find(out_keys.begin(), out_keys.end(),
                                        QuadKey(Type::LatLon, 0, 0, 1)));
    EXPECT_NE(out_keys.end(), std::find(out_keys.begin(), out_keys.end(),
                                        QuadKey(Type::LatLon, 0, 1, 1)));
    EXPECT_NE(out_keys.end(), std::find(out_keys.begin(), out_keys.end(),
                                        QuadKey(Type::LatLon, 1, 0, 1)));
    EXPECT_NE(out_keys.end(), std::find(out_keys.begin(), out_keys.end(),
                                        QuadKey(Type::LatLon, 1, 1, 1)));
  }
}

TEST(LATLONGSYSTEM, test_known_sample_of_locations) {
  QuadKey key;

  {
    key = QuadKey::get_key_from_longitude_latitude_at_depth(
        Type::LatLon, GeoCoordinate2d(Longitude(-122.4183), Latitude(37.7750)),
        1u);
    EXPECT_EQ("0", key.to_internal_string());
    key = QuadKey::get_key_from_longitude_latitude_at_depth(
        Type::LatLon, GeoCoordinate2d(Longitude(-122.4183), Latitude(37.7750)),
        2u);
    EXPECT_EQ("02", key.to_internal_string());
    key = QuadKey::get_key_from_longitude_latitude_at_depth(
        Type::LatLon, GeoCoordinate2d(Longitude(-122.4183), Latitude(37.7750)),
        3u);
    EXPECT_EQ("021", key.to_internal_string());
    key = QuadKey::get_key_from_longitude_latitude_at_depth(
        Type::LatLon, GeoCoordinate2d(Longitude(-122.4183), Latitude(37.7750)),
        4u);
    EXPECT_EQ("0210", key.to_internal_string());
  }

  {
    key = QuadKey::get_key_from_longitude_latitude_at_depth(
        Type::LatLon, GeoCoordinate2d(Longitude(+134.9), Latitude(-67.6)), 3u);
    EXPECT_EQ(QuadKey(Type::LatLon, 0, 6, 3), key);
    EXPECT_EQ("332", key.to_internal_string());

    key = QuadKey::get_key_from_longitude_latitude_at_depth(
        Type::LatLon, GeoCoordinate2d(Longitude(+135.0), Latitude(-67.5)), 3u);
    EXPECT_EQ(QuadKey(Type::LatLon, 1, 7, 3), key);
    EXPECT_EQ("331", key.to_internal_string());
  }
}
}  // namespace quad_keys

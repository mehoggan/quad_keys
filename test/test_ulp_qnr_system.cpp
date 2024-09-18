#include <gtest/gtest.h>

#include <algorithm>
#include <iostream>
#include <numeric>

#include "quad_keys/geo_coordinate2d.h"
#include "quad_keys/quad_key.h"

namespace quad_keys {
class TestUlpQnrSystem : public ::testing::Test {
 protected:
  virtual void SetUp() {}
  virtual void TearDown() {}
};

TEST(MOSQNRSYSTEM, is_valid) {
  // Same as bing_system
}

TEST(MOSQNRSYSTEM, is_root_key) {
  // Same as bing_system
}

TEST(MOSQNRSYSTEM, get_parent) {
  // Same as bing_system
}

TEST(MOSQNRSYSTEM, is_my_ancestor) {
  // Same as bing_system
}

TEST(MOSQNRSYSTEM, get_ancestor) {
  // Same as bing_system
}

TEST(MOSQNRSYSTEM, get_child) {
  // Same as bing_system
}

TEST(MOSQNRSYSTEM, get_children) {
  // Same as bing_system
}

TEST(MOSQNRSYSTEM, get_descendants) {
  // Same as bing_system
}

TEST(MOSQNRSYSTEM, get_siblings) {
  // Same as bing_system
}

TEST(MOSQNRSYSTEM, get_neighbors) {
  // Same as bing_system
}

TEST(MOSQNRSYSTEM, from_string_to_string) {
  QuadKey qk(Type::UlpQnr, 0, 0, 0);
  std::string fmt = qk.to_internal_string();
  EXPECT_EQ("1", fmt);
  QuadKey qk_back = QuadKey::from_internal_string(Type::UlpQnr, fmt);
  EXPECT_EQ(qk, qk_back);

  qk = QuadKey(Type::UlpQnr, 0, 0, 1);
  fmt = qk.to_internal_string();
  EXPECT_EQ("4", fmt);
  qk_back = QuadKey::from_internal_string(Type::UlpQnr, fmt);
  EXPECT_EQ(qk, qk_back);

  qk = QuadKey(Type::UlpQnr, 0, 1, 1);
  fmt = qk.to_internal_string();
  EXPECT_EQ("5", fmt);
  qk_back = QuadKey::from_internal_string(Type::UlpQnr, fmt);
  EXPECT_EQ(qk, qk_back);

  qk = QuadKey(Type::UlpQnr, 0, 0, 2);
  fmt = qk.to_internal_string();
  EXPECT_EQ("16", fmt);
  qk_back = QuadKey::from_internal_string(Type::UlpQnr, fmt);
  EXPECT_EQ(qk, qk_back);

  qk = QuadKey(Type::UlpQnr, 0, 1, 2);
  fmt = qk.to_internal_string();
  EXPECT_EQ("17", fmt);
  qk_back = QuadKey::from_internal_string(Type::UlpQnr, fmt);
  EXPECT_EQ(qk, qk_back);

  qk = QuadKey(Type::UlpQnr, 1, 0, 2);
  fmt = qk.to_internal_string();
  EXPECT_EQ("20", fmt);
  qk_back = QuadKey::from_internal_string(Type::UlpQnr, fmt);
  EXPECT_EQ(qk, qk_back);

  qk = QuadKey(Type::UlpQnr, 1, 1, 2);
  fmt = qk.to_internal_string();
  EXPECT_EQ("21", fmt);
  qk_back = QuadKey::from_internal_string(Type::UlpQnr, fmt);
  EXPECT_EQ(qk, qk_back);

  qk = QuadKey(Type::UlpQnr, 0, 2, 2);
  fmt = qk.to_internal_string();
  EXPECT_EQ("18", fmt);
  qk_back = QuadKey::from_internal_string(Type::UlpQnr, fmt);
  EXPECT_EQ(qk, qk_back);

  qk = QuadKey(Type::UlpQnr, 0, 3, 2);
  fmt = qk.to_internal_string();
  EXPECT_EQ("19", fmt);
  qk_back = QuadKey::from_internal_string(Type::UlpQnr, fmt);
  EXPECT_EQ(qk, qk_back);

  qk = QuadKey(Type::UlpQnr, 1, 2, 2);
  fmt = qk.to_internal_string();
  EXPECT_EQ("22", fmt);
  qk_back = QuadKey::from_internal_string(Type::UlpQnr, fmt);
  EXPECT_EQ(qk, qk_back);

  qk = QuadKey(Type::UlpQnr, 1, 3, 2);
  fmt = qk.to_internal_string();
  EXPECT_EQ("23", fmt);
  qk_back = QuadKey::from_internal_string(Type::UlpQnr, fmt);
  EXPECT_EQ(qk, qk_back);

  // For Sanity Purposes and to Verify NO Fence Post Erros. Use a bit of
  // brute force.
  std::vector<int> expected(32);
  std::iota(expected.begin(), expected.end(), 64);
  for (std::uint32_t i = 0; i < (8 * 4); ++i) {
    std::uint32_t row = i / 8;
    std::uint32_t col = i % 8;
    qk = QuadKey(Type::UlpQnr, row, col, 3);
    fmt = qk.to_internal_string();

    char buff[3];  // '\0' 64-95
    snprintf(buff, 3, "%d", expected[i]);
    std::string expected_str(buff);

    EXPECT_EQ(expected_str, fmt) << "Failed on 64 + " << i << "th key";
    qk_back = QuadKey::from_internal_string(Type::UlpQnr, fmt);
    EXPECT_EQ(qk, qk_back) << "Failed on 64 + " << i << "th key";
  }

  qk = QuadKey(Type::UlpQnr, 0, 0, 3);
  fmt = qk.to_internal_string();
  EXPECT_EQ("64", fmt);
  qk_back = QuadKey::from_internal_string(Type::UlpQnr, fmt);
  EXPECT_EQ(qk, qk_back);
}

TEST(MOSQNRSYSTEM, get_key_from_longitude_latitude_at_depth_to_bounds) {
  QuadKey computed_key;
  computed_key = QuadKey::get_key_from_longitude_latitude_at_depth(
      Type::UlpQnr, GeoCoordinate2d(Longitude(-180.0), Latitude(-90.0)), 0);
  EXPECT_EQ("1", computed_key.to_internal_string());
  computed_key = QuadKey::get_key_from_longitude_latitude_at_depth(
      Type::UlpQnr, GeoCoordinate2d(Longitude(0.0), Latitude(0.0)), 0);
  EXPECT_EQ("1", computed_key.to_internal_string());

  computed_key = QuadKey::get_key_from_longitude_latitude_at_depth(
      Type::UlpQnr, GeoCoordinate2d(Longitude(-180.0), Latitude(-90.0)), 1);
  EXPECT_EQ("4", computed_key.to_internal_string());
  computed_key = QuadKey::get_key_from_longitude_latitude_at_depth(
      Type::UlpQnr, GeoCoordinate2d(Longitude(-180.0), Latitude(90.0)), 1);
  EXPECT_EQ("4", computed_key.to_internal_string());
  computed_key = QuadKey::get_key_from_longitude_latitude_at_depth(
      Type::UlpQnr, GeoCoordinate2d(Longitude(0.1), Latitude(-90.0)), 1);
  EXPECT_EQ("5", computed_key.to_internal_string());
  computed_key = QuadKey::get_key_from_longitude_latitude_at_depth(
      Type::UlpQnr, GeoCoordinate2d(Longitude(180.0), Latitude(90.0)), 1);
  EXPECT_EQ("5", computed_key.to_internal_string());

  computed_key = QuadKey::get_key_from_longitude_latitude_at_depth(
      Type::UlpQnr, GeoCoordinate2d(Longitude(-180.0), Latitude(-90.0)), 2);
  EXPECT_EQ("16", computed_key.to_internal_string());
  computed_key = QuadKey::get_key_from_longitude_latitude_at_depth(
      Type::UlpQnr, GeoCoordinate2d(Longitude(-89.9), Latitude(-90.0)), 2);
  EXPECT_EQ("17", computed_key.to_internal_string());
  computed_key = QuadKey::get_key_from_longitude_latitude_at_depth(
      Type::UlpQnr, GeoCoordinate2d(Longitude(0.1), Latitude(-90.0)), 2);
  EXPECT_EQ("18", computed_key.to_internal_string());
  computed_key = QuadKey::get_key_from_longitude_latitude_at_depth(
      Type::UlpQnr, GeoCoordinate2d(Longitude(90.1), Latitude(-90.0)), 2);
  EXPECT_EQ("19", computed_key.to_internal_string());
  computed_key = QuadKey::get_key_from_longitude_latitude_at_depth(
      Type::UlpQnr, GeoCoordinate2d(Longitude(-180.0), Latitude(0.1)), 2);
  EXPECT_EQ("20", computed_key.to_internal_string());
  computed_key = QuadKey::get_key_from_longitude_latitude_at_depth(
      Type::UlpQnr, GeoCoordinate2d(Longitude(-89.9), Latitude(0.1)), 2);
  EXPECT_EQ("21", computed_key.to_internal_string());
  computed_key = QuadKey::get_key_from_longitude_latitude_at_depth(
      Type::UlpQnr, GeoCoordinate2d(Longitude(0.1), Latitude(0.1)), 2);
  EXPECT_EQ("22", computed_key.to_internal_string());
  computed_key = QuadKey::get_key_from_longitude_latitude_at_depth(
      Type::UlpQnr, GeoCoordinate2d(Longitude(90.1), Latitude(0.1)), 2);
  EXPECT_EQ("23", computed_key.to_internal_string());
}

TEST(MOSQNRSYSTEM, get_keys_from_longitude_latitude_bounding_box) {
  std::vector<QuadKey> out_keys;
  QuadKey qk;

  // Select Entire Earth
  out_keys = QuadKey::get_keys_from_longitude_latitude_bounding_box(
      Type::UlpQnr,
      GeoCoordinateBoundingBox2d(
          GeoCoordinate2d(Longitude(-180.0), Latitude(-90.0)),
          GeoCoordinate2d(Longitude(180.0), Latitude(90.0))),
      0);
  qk = QuadKey::from_internal_string(Type::UlpQnr, "1");
  EXPECT_EQ(1u, out_keys.size());
  EXPECT_NE(std::find(out_keys.begin(), out_keys.end(), qk), out_keys.end());

  // Select Very Center of the Earth
  out_keys = QuadKey::get_keys_from_longitude_latitude_bounding_box(
      Type::UlpQnr,
      GeoCoordinateBoundingBox2d(
          GeoCoordinate2d(Longitude(-0.1), Latitude(-0.1)),
          GeoCoordinate2d(Longitude(0.1), Latitude(0.1))),
      0);
  qk = QuadKey::from_internal_string(Type::UlpQnr, "1");
  EXPECT_EQ(1u, out_keys.size());
  EXPECT_NE(std::find(out_keys.begin(), out_keys.end(), qk), out_keys.end());

  // Select Western Hemisphere
  out_keys = QuadKey::get_keys_from_longitude_latitude_bounding_box(
      Type::UlpQnr,
      GeoCoordinateBoundingBox2d(
          GeoCoordinate2d(Longitude(-180.0), Latitude(-90.0)),
          GeoCoordinate2d(Longitude(0.0), Latitude(90.0))),
      1);
  qk = QuadKey::from_internal_string(Type::UlpQnr, "4");
  EXPECT_EQ(1u, out_keys.size());
  EXPECT_NE(std::find(out_keys.begin(), out_keys.end(), qk), out_keys.end());

  // Select Eastern Hemisphere
  out_keys = QuadKey::get_keys_from_longitude_latitude_bounding_box(
      Type::UlpQnr,
      GeoCoordinateBoundingBox2d(
          GeoCoordinate2d(Longitude(0.1), Latitude(-90.0)),
          GeoCoordinate2d(Longitude(180), Latitude(90.0))),
      1);
  qk = QuadKey::from_internal_string(Type::UlpQnr, "5");
  EXPECT_EQ(1u, out_keys.size());
  EXPECT_NE(std::find(out_keys.begin(), out_keys.end(), qk), out_keys.end());

  // Select Entire Planet
  out_keys = QuadKey::get_keys_from_longitude_latitude_bounding_box(
      Type::UlpQnr,
      GeoCoordinateBoundingBox2d(
          GeoCoordinate2d(Longitude(-180.0), Latitude(-90.0)),
          GeoCoordinate2d(Longitude(180), Latitude(90.0))),
      1);
  QuadKey qka = QuadKey::from_internal_string(Type::UlpQnr, "4");
  QuadKey qkb = QuadKey::from_internal_string(Type::UlpQnr, "5");
  EXPECT_EQ(2u, out_keys.size());
  EXPECT_NE(std::find(out_keys.begin(), out_keys.end(), qka), out_keys.end());
  EXPECT_NE(std::find(out_keys.begin(), out_keys.end(), qkb), out_keys.end());

  // Select South West Corner
  out_keys = QuadKey::get_keys_from_longitude_latitude_bounding_box(
      Type::UlpQnr,
      GeoCoordinateBoundingBox2d(
          GeoCoordinate2d(Longitude(-180.0), Latitude(-90.0)),
          GeoCoordinate2d(Longitude(-90.0), Latitude(0.0))),
      2);
  qk = QuadKey::from_internal_string(Type::UlpQnr, "16");
  EXPECT_EQ(1u, out_keys.size());
  EXPECT_NE(std::find(out_keys.begin(), out_keys.end(), qk), out_keys.end());

  // Select South America
  out_keys = QuadKey::get_keys_from_longitude_latitude_bounding_box(
      Type::UlpQnr,
      GeoCoordinateBoundingBox2d(
          GeoCoordinate2d(Longitude(-89.9), Latitude(-90.0)),
          GeoCoordinate2d(Longitude(0.0), Latitude(0.0))),
      2);
  qk = QuadKey::from_internal_string(Type::UlpQnr, "17");
  EXPECT_EQ(1u, out_keys.size());
  EXPECT_NE(std::find(out_keys.begin(), out_keys.end(), qk), out_keys.end());

  // Select North West Corner
  out_keys = QuadKey::get_keys_from_longitude_latitude_bounding_box(
      Type::UlpQnr,
      GeoCoordinateBoundingBox2d(
          GeoCoordinate2d(Longitude(-180.0), Latitude(0.1)),
          GeoCoordinate2d(Longitude(-90.0), Latitude(90.0))),
      2);
  qk = QuadKey::from_internal_string(Type::UlpQnr, "20");
  EXPECT_EQ(1u, out_keys.size());
  EXPECT_NE(std::find(out_keys.begin(), out_keys.end(), qk), out_keys.end());

  // Select Greenland
  out_keys = QuadKey::get_keys_from_longitude_latitude_bounding_box(
      Type::UlpQnr,
      GeoCoordinateBoundingBox2d(
          GeoCoordinate2d(Longitude(-89.9), Latitude(0.1)),
          GeoCoordinate2d(Longitude(0.0), Latitude(90.0))),
      2);
  qk = QuadKey::from_internal_string(Type::UlpQnr, "21");
  EXPECT_EQ(1u, out_keys.size());
  EXPECT_NE(std::find(out_keys.begin(), out_keys.end(), qk), out_keys.end());

  // Select South Pole
  out_keys = QuadKey::get_keys_from_longitude_latitude_bounding_box(
      Type::UlpQnr,
      GeoCoordinateBoundingBox2d(
          GeoCoordinate2d(Longitude(0.1), Latitude(-90.0)),
          GeoCoordinate2d(Longitude(90.0), Latitude(0.0))),
      2);
  qk = QuadKey::from_internal_string(Type::UlpQnr, "18");
  EXPECT_EQ(1u, out_keys.size());
  EXPECT_NE(std::find(out_keys.begin(), out_keys.end(), qk), out_keys.end());

  // Select South East Corner
  out_keys = QuadKey::get_keys_from_longitude_latitude_bounding_box(
      Type::UlpQnr,
      GeoCoordinateBoundingBox2d(
          GeoCoordinate2d(Longitude(90.1), Latitude(-90.0)),
          GeoCoordinate2d(Longitude(180.0), Latitude(0.0))),
      2);
  qk = QuadKey::from_internal_string(Type::UlpQnr, "19");
  EXPECT_EQ(1u, out_keys.size());
  EXPECT_NE(std::find(out_keys.begin(), out_keys.end(), qk), out_keys.end());

  // Select Over Europe
  out_keys = QuadKey::get_keys_from_longitude_latitude_bounding_box(
      Type::UlpQnr,
      GeoCoordinateBoundingBox2d(
          GeoCoordinate2d(Longitude(0.1), Latitude(0.1)),
          GeoCoordinate2d(Longitude(90.0), Latitude(90.0))),
      2);
  qk = QuadKey::from_internal_string(Type::UlpQnr, "22");
  EXPECT_EQ(1u, out_keys.size());
  EXPECT_NE(std::find(out_keys.begin(), out_keys.end(), qk), out_keys.end());

  // Select North East Corner
  out_keys = QuadKey::get_keys_from_longitude_latitude_bounding_box(
      Type::UlpQnr,
      GeoCoordinateBoundingBox2d(
          GeoCoordinate2d(Longitude(90.1), Latitude(0.1)),
          GeoCoordinate2d(Longitude(180.0), Latitude(90.0))),
      2);
  qk = QuadKey::from_internal_string(Type::UlpQnr, "23");
  EXPECT_EQ(1u, out_keys.size());
  EXPECT_NE(std::find(out_keys.begin(), out_keys.end(), qk), out_keys.end());

  // Select Entire Map
  out_keys = QuadKey::get_keys_from_longitude_latitude_bounding_box(
      Type::UlpQnr,
      GeoCoordinateBoundingBox2d(
          GeoCoordinate2d(Longitude(-179.9), Latitude(-89.9)),
          GeoCoordinate2d(Longitude(90.1), Latitude(0.1))),
      2);
  QuadKey qk0 = QuadKey::from_internal_string(Type::UlpQnr, "16");
  QuadKey qk1 = QuadKey::from_internal_string(Type::UlpQnr, "17");
  QuadKey qk2 = QuadKey::from_internal_string(Type::UlpQnr, "18");
  QuadKey qk3 = QuadKey::from_internal_string(Type::UlpQnr, "19");
  QuadKey qk4 = QuadKey::from_internal_string(Type::UlpQnr, "20");
  QuadKey qk5 = QuadKey::from_internal_string(Type::UlpQnr, "21");
  QuadKey qk6 = QuadKey::from_internal_string(Type::UlpQnr, "22");
  QuadKey qk7 = QuadKey::from_internal_string(Type::UlpQnr, "23");
  EXPECT_EQ(8u, out_keys.size());
  EXPECT_NE(std::find(out_keys.begin(), out_keys.end(), qk0), out_keys.end());
  EXPECT_NE(std::find(out_keys.begin(), out_keys.end(), qk1), out_keys.end());
  EXPECT_NE(std::find(out_keys.begin(), out_keys.end(), qk2), out_keys.end());
  EXPECT_NE(std::find(out_keys.begin(), out_keys.end(), qk3), out_keys.end());
  EXPECT_NE(std::find(out_keys.begin(), out_keys.end(), qk4), out_keys.end());
  EXPECT_NE(std::find(out_keys.begin(), out_keys.end(), qk5), out_keys.end());
  EXPECT_NE(std::find(out_keys.begin(), out_keys.end(), qk6), out_keys.end());
  EXPECT_NE(std::find(out_keys.begin(), out_keys.end(), qk7), out_keys.end());
}

TEST(MOSQNRSYSTEM, selected_cities) {
  // TODO: Implement Tests. Taken from Earthscape. No tests there.
}
}  // namespace quad_keys

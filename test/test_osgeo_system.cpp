#include <gtest/gtest.h>

#include "quad_keys/geo_coordinate2d.h"
#include "quad_keys/quad_key.h"

#include <iostream>

namespace quad_keys
{
  class TestOsGeoSystem : public ::testing::Test
  {
  protected:
    virtual void SetUp() {}
    virtual void TearDown() {}
  };

  TEST(OSGEOSYSTEM, IsValid)
  {
    // Same as bing_system
  }

  TEST(OSGEOSYSTEM, IsRootKey)
  {
    // Same as bing_system
  }

  TEST(OSGEOSYSTEM, GetParent)
  {
    // Same as bing_system
  }

  TEST(OSGEOSYSTEM, IsMyAncestor)
  {
    // Same as bing_system
  }

  TEST(OSGEOSYSTEM, GetAncestor)
  {
    // Same as bing_system
  }

  TEST(OSGEOSYSTEM, GetChild)
  {
    // Same as bing_system
  }

  TEST(OSGEOSYSTEM, GetChildren)
  {
    // Same as bing_system
  }

  TEST(OSGEOSYSTEM, GetDescendants)
  {
    // Same as bing_system
  }

  TEST(OSGEOSYSTEM, GetSiblings)
  {
    // Same as bing_system
  }

  TEST(OSGEOSYSTEM, GetNeighbors)
  {
    // Same as bing_system
  }

  TEST(OSGEOSYSTEM, from_string_to_string)
  {
    // Same thing as OsGeo Except for it allows for negative 1 in both the
    // rows and the columns. depth/col/row.
    QuadKey qk(Type::OsGeo, 3, 3, 2);
    std::string fmt = qk.to_internal_string();
    EXPECT_EQ("2/3/3", fmt);
    QuadKey qk_back = QuadKey::from_internal_string(Type::OsGeo, fmt);
    EXPECT_EQ(qk, qk_back);

    fmt = "0/-1/-1";
    qk_back = QuadKey::from_internal_string(Type::OsGeo, fmt);
    EXPECT_EQ(QuadKey(Type::OsGeo, 0, 0, 0), qk_back);

    fmt = "1/1/-1";
    qk_back = QuadKey::from_internal_string(Type::OsGeo, fmt);
    EXPECT_EQ(QuadKey(Type::OsGeo, 0, 1, 1), qk_back);

    fmt = "1/-1/1";
    qk_back = QuadKey::from_internal_string(Type::OsGeo, fmt);
    EXPECT_EQ(QuadKey(Type::OsGeo, 1, 0, 1), qk_back);
  }

  TEST(OSGEOSYSTEM, GetKeyFromlongitudelatitudeAtDepthToBounds)
  {
    QuadKey qk;
    GeoCoordinateBoundingBox2d bbox;

    // Inclusion here consists of upper right. In the case along bottom or
    // left Inclusion points the opposite direction.
    //    X------X------X ur
    //    |      |      |
    //    |      |      |
    //    X------X------X
    //    |      |      |
    //    |      |      |
    //    X------X------X
    // Note that in this system bounds consist of all 4 sides, so two quads
    // will share the same boundary.
    qk = QuadKey::get_key_from_longitude_latitude_at_depth(Type::OsGeo,
      GeoCoordinate2d(Longitude(-180.0), Latitude(+85.05113877)), 0);
    EXPECT_EQ(QuadKey(Type::OsGeo, 0, 0, 0), qk);
    qk = QuadKey::get_key_from_longitude_latitude_at_depth(Type::OsGeo,
      GeoCoordinate2d(Longitude(+180.0), Latitude(+85.05113877)), 0);
    EXPECT_EQ(QuadKey(Type::OsGeo, 0, 0, 0), qk);
    qk = QuadKey::get_key_from_longitude_latitude_at_depth(Type::OsGeo,
      GeoCoordinate2d(Longitude(+180.0), Latitude(-85.05113877)), 0);
    EXPECT_EQ(QuadKey(Type::OsGeo, 0, 0, 0), qk);
    qk = QuadKey::get_key_from_longitude_latitude_at_depth(Type::OsGeo,
      GeoCoordinate2d(Longitude(-180.0), Latitude(-85.05113877)), 0);
    EXPECT_EQ(QuadKey(Type::OsGeo, 0, 0, 0), qk);
    qk.get_geo_coordinate_bounds2d(bbox);
    EXPECT_TRUE(bbox.lower_left().near(GeoCoordinate2d(
      Longitude(-180.0), Latitude(-85.05113877)), 1e-4)) << "Actual = "
      << bbox.lower_left() << " for " << qk;
    EXPECT_TRUE(bbox.upper_right().near(GeoCoordinate2d(
      Longitude(+180.0), Latitude(+85.05113877)), 1e-4)) << "Actual = "
      << bbox.upper_right() << " for " << qk;

    qk = QuadKey::get_key_from_longitude_latitude_at_depth(Type::OsGeo,
      GeoCoordinate2d(Longitude(+0.0), Latitude(+0.00000000)), 0);
    EXPECT_EQ(QuadKey(Type::OsGeo, 0, 0, 0), qk);

    qk = QuadKey::get_key_from_longitude_latitude_at_depth(Type::OsGeo,
      GeoCoordinate2d(Longitude(-180.0), Latitude(+85.05113877)), 1);
    EXPECT_EQ(QuadKey(Type::OsGeo, 1, 0, 1), qk);
    qk.get_geo_coordinate_bounds2d(bbox);
    EXPECT_TRUE(bbox.lower_left().near(GeoCoordinate2d(
      Longitude(-180.0), Latitude(+0.00000000)), 1e-4)) << "Actual = "
      << bbox.lower_left() << " for " << qk;
    EXPECT_TRUE(bbox.upper_right().near(GeoCoordinate2d(
      Longitude(+0.0), Latitude(+85.05113877)), 1e-4)) << "Actual = "
      << bbox.upper_right() << " for " << qk;

    qk = QuadKey::get_key_from_longitude_latitude_at_depth(Type::OsGeo,
      GeoCoordinate2d(Longitude(+180.0), Latitude(+85.05113877)), 1);
    EXPECT_EQ(QuadKey(Type::OsGeo, 1, 1, 1), qk);
    qk.get_geo_coordinate_bounds2d(bbox);
    EXPECT_TRUE(bbox.lower_left().near(GeoCoordinate2d(
      Longitude(+0.0), Latitude(+0.00000000)), 1e-4)) << "Actual = "
      << bbox.lower_left() << " for " << qk;
    EXPECT_TRUE(bbox.upper_right().near(GeoCoordinate2d(
      Longitude(+180.0), Latitude(+85.05113877)), 1e-4)) << "Actual = "
      << bbox.upper_right() << " for " << qk;

    qk = QuadKey::get_key_from_longitude_latitude_at_depth(Type::OsGeo,
      GeoCoordinate2d(Longitude(+180.0), Latitude(-85.05113877)), 1);
    EXPECT_EQ(QuadKey(Type::OsGeo, 0, 1, 1), qk);
    qk.get_geo_coordinate_bounds2d(bbox);
    EXPECT_TRUE(bbox.lower_left().near(GeoCoordinate2d(
      Longitude(+0.0), Latitude(-85.05113877)), 1e-4)) << "Actual = "
      << bbox.lower_left() << " for " << qk;
    EXPECT_TRUE(bbox.upper_right().near(GeoCoordinate2d(
      Longitude(+180.0), Latitude(+0.00000000)), 1e-4)) << "Actual = "
      << bbox.upper_right() << " for " << qk;

    qk = QuadKey::get_key_from_longitude_latitude_at_depth(Type::OsGeo,
      GeoCoordinate2d(Longitude(-180.0), Latitude(-85.05113877)), 1);
    EXPECT_EQ(QuadKey(Type::OsGeo, 0, 0, 1), qk);
    qk.get_geo_coordinate_bounds2d(bbox);
    EXPECT_TRUE(bbox.lower_left().near(GeoCoordinate2d(
      Longitude(-180.0), Latitude(-85.05113877)), 1e-4)) << "Actual = "
      << bbox.lower_left() << " for " << qk;
    EXPECT_TRUE(bbox.upper_right().near(GeoCoordinate2d(
      Longitude(+0.0), Latitude(+0.00000000)), 1e-4)) << "Actual = "
      << bbox.upper_right() << " for " << qk;

    qk = QuadKey::get_key_from_longitude_latitude_at_depth(Type::OsGeo,
      GeoCoordinate2d(Longitude(-180.0), Latitude(+0.00000000)), 1);
    EXPECT_EQ(QuadKey(Type::OsGeo, 0, 0, 1), qk);
    qk = QuadKey::get_key_from_longitude_latitude_at_depth(Type::OsGeo,
      GeoCoordinate2d(Longitude(+0.0), Latitude(+85.05113877)), 1);
    EXPECT_EQ(QuadKey(Type::OsGeo, 1, 0, 1), qk);
    qk = QuadKey::get_key_from_longitude_latitude_at_depth(Type::OsGeo,
      GeoCoordinate2d(Longitude(+180.0), Latitude(+0.00000000)), 1);
    EXPECT_EQ(QuadKey(Type::OsGeo, 0, 1, 1), qk);
    qk = QuadKey::get_key_from_longitude_latitude_at_depth(Type::OsGeo,
      GeoCoordinate2d(Longitude(+0.0), Latitude(-85.05113877)), 1);
    EXPECT_EQ(QuadKey(Type::OsGeo, 0, 0, 1), qk);
    qk = QuadKey::get_key_from_longitude_latitude_at_depth(Type::OsGeo,
      GeoCoordinate2d(Longitude(+0.0), Latitude(+0.00000000)), 1);
    EXPECT_EQ(QuadKey(Type::OsGeo, 0, 0, 1), qk);

    // Note at depth 2 because of the Mercator projection the lines
    // of latitude are note perfect divisions by 2.
    qk = QuadKey::get_key_from_longitude_latitude_at_depth(Type::OsGeo,
      GeoCoordinate2d(Longitude(-180.0), Latitude(-85.05113877)), 2);
    EXPECT_EQ(QuadKey(Type::OsGeo, 0, 0, 2), qk);
    qk = QuadKey::get_key_from_longitude_latitude_at_depth(Type::OsGeo,
      GeoCoordinate2d(Longitude(-180.0), Latitude(-66.5133)), 2);
    EXPECT_EQ(QuadKey(Type::OsGeo, 0, 0, 2), qk);
    qk = QuadKey::get_key_from_longitude_latitude_at_depth(Type::OsGeo,
      GeoCoordinate2d(Longitude(-180.0), Latitude(-66.5132)), 2);
    EXPECT_EQ(QuadKey(Type::OsGeo, 1, 0, 2), qk);
    qk = QuadKey::get_key_from_longitude_latitude_at_depth(Type::OsGeo,
      GeoCoordinate2d(Longitude(-180.0), Latitude(+0.1)), 2);
    EXPECT_EQ(QuadKey(Type::OsGeo, 2, 0, 2), qk);
    qk = QuadKey::get_key_from_longitude_latitude_at_depth(Type::OsGeo,
      GeoCoordinate2d(Longitude(-180.0), Latitude(+66.5132)), 2);
    EXPECT_EQ(QuadKey(Type::OsGeo, 2, 0, 2), qk);
    qk = QuadKey::get_key_from_longitude_latitude_at_depth(Type::OsGeo,
      GeoCoordinate2d(Longitude(-180.0), Latitude(+66.5133)), 2);
    EXPECT_EQ(QuadKey(Type::OsGeo, 3, 0, 2), qk);
    qk = QuadKey::get_key_from_longitude_latitude_at_depth(Type::OsGeo,
      GeoCoordinate2d(Longitude(-180.0), Latitude(+85.05113877)), 2);
    EXPECT_EQ(QuadKey(Type::OsGeo, 3, 0, 2), qk);
    qk = QuadKey::get_key_from_longitude_latitude_at_depth(Type::OsGeo,
      GeoCoordinate2d(Longitude(-90.0), Latitude(-85.05113877)), 2);
    EXPECT_EQ(QuadKey(Type::OsGeo, 0, 0, 2), qk);
    qk = QuadKey::get_key_from_longitude_latitude_at_depth(Type::OsGeo,
      GeoCoordinate2d(Longitude(-90.0), Latitude(-66.5133)), 2);
    EXPECT_EQ(QuadKey(Type::OsGeo, 0, 0, 2), qk);
    qk = QuadKey::get_key_from_longitude_latitude_at_depth(Type::OsGeo,
      GeoCoordinate2d(Longitude(-90.0), Latitude(-66.5132)), 2);
    EXPECT_EQ(QuadKey(Type::OsGeo, 1, 0, 2), qk);
    qk = QuadKey::get_key_from_longitude_latitude_at_depth(Type::OsGeo,
      GeoCoordinate2d(Longitude(-90.0), Latitude(+0.1)), 2);
    EXPECT_EQ(QuadKey(Type::OsGeo, 2, 0, 2), qk);
    qk = QuadKey::get_key_from_longitude_latitude_at_depth(Type::OsGeo,
      GeoCoordinate2d(Longitude(-90.0), Latitude(+66.5132)), 2);
    EXPECT_EQ(QuadKey(Type::OsGeo, 2, 0, 2), qk);
    qk = QuadKey::get_key_from_longitude_latitude_at_depth(Type::OsGeo,
      GeoCoordinate2d(Longitude(-90.0), Latitude(+66.5133)), 2);
    EXPECT_EQ(QuadKey(Type::OsGeo, 3, 0, 2), qk);
    qk = QuadKey::get_key_from_longitude_latitude_at_depth(Type::OsGeo,
      GeoCoordinate2d(Longitude(-90.0), Latitude(+85.05113877)), 2);
    EXPECT_EQ(QuadKey(Type::OsGeo, 3, 0, 2), qk);
    qk = QuadKey::get_key_from_longitude_latitude_at_depth(Type::OsGeo,
      GeoCoordinate2d(Longitude(-89.9), Latitude(-85.05113877)), 2);
    EXPECT_EQ(QuadKey(Type::OsGeo, 0, 1, 2), qk);
    qk = QuadKey::get_key_from_longitude_latitude_at_depth(Type::OsGeo,
      GeoCoordinate2d(Longitude(-89.9), Latitude(-66.5133)), 2);
    EXPECT_EQ(QuadKey(Type::OsGeo, 0, 1, 2), qk);
    qk = QuadKey::get_key_from_longitude_latitude_at_depth(Type::OsGeo,
      GeoCoordinate2d(Longitude(-89.9), Latitude(-66.5132)), 2);
    EXPECT_EQ(QuadKey(Type::OsGeo, 1, 1, 2), qk);
    qk = QuadKey::get_key_from_longitude_latitude_at_depth(Type::OsGeo,
      GeoCoordinate2d(Longitude(-89.9), Latitude(+0.1)), 2);
    EXPECT_EQ(QuadKey(Type::OsGeo, 2, 1, 2), qk);
    qk = QuadKey::get_key_from_longitude_latitude_at_depth(Type::OsGeo,
      GeoCoordinate2d(Longitude(-89.9), Latitude(+66.5132)), 2);
    EXPECT_EQ(QuadKey(Type::OsGeo, 2, 1, 2), qk);
    qk = QuadKey::get_key_from_longitude_latitude_at_depth(Type::OsGeo,
      GeoCoordinate2d(Longitude(-89.9), Latitude(+66.5133)), 2);
    EXPECT_EQ(QuadKey(Type::OsGeo, 3, 1, 2), qk);
    qk = QuadKey::get_key_from_longitude_latitude_at_depth(Type::OsGeo,
      GeoCoordinate2d(Longitude(-89.9), Latitude(+85.05113877)), 2);
    EXPECT_EQ(QuadKey(Type::OsGeo, 3, 1, 2), qk);
    qk = QuadKey::get_key_from_longitude_latitude_at_depth(Type::OsGeo,
      GeoCoordinate2d(Longitude(+0.0), Latitude(-85.05113877)), 2);
    EXPECT_EQ(QuadKey(Type::OsGeo, 0, 1, 2), qk);
    qk = QuadKey::get_key_from_longitude_latitude_at_depth(Type::OsGeo,
      GeoCoordinate2d(Longitude(+0.0), Latitude(-66.5133)), 2);
    EXPECT_EQ(QuadKey(Type::OsGeo, 0, 1, 2), qk);
    qk = QuadKey::get_key_from_longitude_latitude_at_depth(Type::OsGeo,
      GeoCoordinate2d(Longitude(+0.0), Latitude(-66.5132)), 2);
    EXPECT_EQ(QuadKey(Type::OsGeo, 1, 1, 2), qk);
    qk = QuadKey::get_key_from_longitude_latitude_at_depth(Type::OsGeo,
      GeoCoordinate2d(Longitude(+0.0), Latitude(+0.1)), 2);
    EXPECT_EQ(QuadKey(Type::OsGeo, 2, 1, 2), qk);
    qk = QuadKey::get_key_from_longitude_latitude_at_depth(Type::OsGeo,
      GeoCoordinate2d(Longitude(+0.0), Latitude(+66.5132)), 2);
    EXPECT_EQ(QuadKey(Type::OsGeo, 2, 1, 2), qk);
    qk = QuadKey::get_key_from_longitude_latitude_at_depth(Type::OsGeo,
      GeoCoordinate2d(Longitude(+0.0), Latitude(+66.5133)), 2);
    EXPECT_EQ(QuadKey(Type::OsGeo, 3, 1, 2), qk);
    qk = QuadKey::get_key_from_longitude_latitude_at_depth(Type::OsGeo,
      GeoCoordinate2d(Longitude(+0.0), Latitude(+85.05113877)), 2);
    EXPECT_EQ(QuadKey(Type::OsGeo, 3, 1, 2), qk);
    qk = QuadKey::get_key_from_longitude_latitude_at_depth(Type::OsGeo,
      GeoCoordinate2d(Longitude(+0.1), Latitude(-85.05113877)), 2);
    EXPECT_EQ(QuadKey(Type::OsGeo, 0, 2, 2), qk);
    qk = QuadKey::get_key_from_longitude_latitude_at_depth(Type::OsGeo,
      GeoCoordinate2d(Longitude(+0.1), Latitude(-66.5133)), 2);
    EXPECT_EQ(QuadKey(Type::OsGeo, 0, 2, 2), qk);
    qk = QuadKey::get_key_from_longitude_latitude_at_depth(Type::OsGeo,
      GeoCoordinate2d(Longitude(+0.1), Latitude(-66.5132)), 2);
    EXPECT_EQ(QuadKey(Type::OsGeo, 1, 2, 2), qk);
    qk = QuadKey::get_key_from_longitude_latitude_at_depth(Type::OsGeo,
      GeoCoordinate2d(Longitude(+0.1), Latitude(+0.1)), 2);
    EXPECT_EQ(QuadKey(Type::OsGeo, 2, 2, 2), qk);
    qk = QuadKey::get_key_from_longitude_latitude_at_depth(Type::OsGeo,
      GeoCoordinate2d(Longitude(+0.1), Latitude(+66.5132)), 2);
    EXPECT_EQ(QuadKey(Type::OsGeo, 2, 2, 2), qk);
    qk = QuadKey::get_key_from_longitude_latitude_at_depth(Type::OsGeo,
      GeoCoordinate2d(Longitude(+0.1), Latitude(+66.5133)), 2);
    EXPECT_EQ(QuadKey(Type::OsGeo, 3, 2, 2), qk);
    qk = QuadKey::get_key_from_longitude_latitude_at_depth(Type::OsGeo,
      GeoCoordinate2d(Longitude(+0.1), Latitude(+85.05113877)), 2);
    EXPECT_EQ(QuadKey(Type::OsGeo, 3, 2, 2), qk);
    qk = QuadKey::get_key_from_longitude_latitude_at_depth(Type::OsGeo,
      GeoCoordinate2d(Longitude(+90.0), Latitude(-85.05113877)), 2);
    EXPECT_EQ(QuadKey(Type::OsGeo, 0, 2, 2), qk);
    qk = QuadKey::get_key_from_longitude_latitude_at_depth(Type::OsGeo,
      GeoCoordinate2d(Longitude(+90.0), Latitude(-66.5133)), 2);
    EXPECT_EQ(QuadKey(Type::OsGeo, 0, 2, 2), qk);
    qk = QuadKey::get_key_from_longitude_latitude_at_depth(Type::OsGeo,
      GeoCoordinate2d(Longitude(+90.0), Latitude(-66.5132)), 2);
    EXPECT_EQ(QuadKey(Type::OsGeo, 1, 2, 2), qk);
    qk = QuadKey::get_key_from_longitude_latitude_at_depth(Type::OsGeo,
      GeoCoordinate2d(Longitude(+90.0), Latitude(+0.1)), 2);
    EXPECT_EQ(QuadKey(Type::OsGeo, 2, 2, 2), qk);
    qk = QuadKey::get_key_from_longitude_latitude_at_depth(Type::OsGeo,
      GeoCoordinate2d(Longitude(+90.0), Latitude(+66.5132)), 2);
    EXPECT_EQ(QuadKey(Type::OsGeo, 2, 2, 2), qk);
    qk = QuadKey::get_key_from_longitude_latitude_at_depth(Type::OsGeo,
      GeoCoordinate2d(Longitude(+90.0), Latitude(+66.5133)), 2);
    EXPECT_EQ(QuadKey(Type::OsGeo, 3, 2, 2), qk);
    qk = QuadKey::get_key_from_longitude_latitude_at_depth(Type::OsGeo,
      GeoCoordinate2d(Longitude(+90.0), Latitude(+85.05113877)), 2);
    EXPECT_EQ(QuadKey(Type::OsGeo, 3, 2, 2), qk);
    qk = QuadKey::get_key_from_longitude_latitude_at_depth(Type::OsGeo,
      GeoCoordinate2d(Longitude(+90.1), Latitude(-85.05113877)), 2);
    EXPECT_EQ(QuadKey(Type::OsGeo, 0, 3, 2), qk);
    qk = QuadKey::get_key_from_longitude_latitude_at_depth(Type::OsGeo,
      GeoCoordinate2d(Longitude(+90.1), Latitude(-66.5133)), 2);
    EXPECT_EQ(QuadKey(Type::OsGeo, 0, 3, 2), qk);
    qk = QuadKey::get_key_from_longitude_latitude_at_depth(Type::OsGeo,
      GeoCoordinate2d(Longitude(+90.1), Latitude(-66.5132)), 2);
    EXPECT_EQ(QuadKey(Type::OsGeo, 1, 3, 2), qk);
    qk = QuadKey::get_key_from_longitude_latitude_at_depth(Type::OsGeo,
      GeoCoordinate2d(Longitude(+90.1), Latitude(+0.1)), 2);
    EXPECT_EQ(QuadKey(Type::OsGeo, 2, 3, 2), qk);
    qk = QuadKey::get_key_from_longitude_latitude_at_depth(Type::OsGeo,
      GeoCoordinate2d(Longitude(+90.1), Latitude(+66.5132)), 2);
    EXPECT_EQ(QuadKey(Type::OsGeo, 2, 3, 2), qk);
    qk = QuadKey::get_key_from_longitude_latitude_at_depth(Type::OsGeo,
      GeoCoordinate2d(Longitude(+90.1), Latitude(+66.5133)), 2);
    EXPECT_EQ(QuadKey(Type::OsGeo, 3, 3, 2), qk);
    qk = QuadKey::get_key_from_longitude_latitude_at_depth(Type::OsGeo,
      GeoCoordinate2d(Longitude(+180.0), Latitude(-85.05113877)), 2);
    EXPECT_EQ(QuadKey(Type::OsGeo, 0, 3, 2), qk);
    qk = QuadKey::get_key_from_longitude_latitude_at_depth(Type::OsGeo,
      GeoCoordinate2d(Longitude(+180.0), Latitude(-66.5133)), 2);
    EXPECT_EQ(QuadKey(Type::OsGeo, 0, 3, 2), qk);
    qk = QuadKey::get_key_from_longitude_latitude_at_depth(Type::OsGeo,
      GeoCoordinate2d(Longitude(+180.0), Latitude(-66.5132)), 2);
    EXPECT_EQ(QuadKey(Type::OsGeo, 1, 3, 2), qk);
    qk = QuadKey::get_key_from_longitude_latitude_at_depth(Type::OsGeo,
      GeoCoordinate2d(Longitude(+180.0), Latitude(+0.1)), 2);
    EXPECT_EQ(QuadKey(Type::OsGeo, 2, 3, 2), qk);
    qk = QuadKey::get_key_from_longitude_latitude_at_depth(Type::OsGeo,
      GeoCoordinate2d(Longitude(+180.0), Latitude(+66.5133)), 2);
    EXPECT_EQ(QuadKey(Type::OsGeo, 3, 3, 2), qk);
    qk = QuadKey::get_key_from_longitude_latitude_at_depth(Type::OsGeo,
      GeoCoordinate2d(Longitude(+180.0), Latitude(+85.05113877)), 2);
    EXPECT_EQ(QuadKey(Type::OsGeo, 3, 3, 2), qk);
  }

  TEST(OSGEOSYSTEM, get_keys_from_longitude_latitude_bounding_box)
  {
    std::vector<QuadKey> qks;

    qks = QuadKey::get_keys_from_longitude_latitude_bounding_box(
      Type::OsGeo, GeoCoordinateBoundingBox2d(
      GeoCoordinate2d(Longitude(+0.0), Latitude(-0.10000000)),
      GeoCoordinate2d(Longitude(+0.1), Latitude(+0.10000000))),
      0);
    EXPECT_EQ(1u, qks.size());
    EXPECT_NE(std::find(qks.begin(), qks.end(), QuadKey(
      Type::OsGeo, 0, 0, 0)), qks.end());

    qks = QuadKey::get_keys_from_longitude_latitude_bounding_box(
      Type::OsGeo, GeoCoordinateBoundingBox2d(
      GeoCoordinate2d(Longitude(-180.0), Latitude(-85.05113877)),
      GeoCoordinate2d(Longitude(+180.0), Latitude(+85.05113877))),
      1);
    EXPECT_EQ(4u, qks.size());
    EXPECT_NE(std::find(qks.begin(), qks.end(), QuadKey(
      Type::OsGeo, 0, 0, 1)), qks.end());
    EXPECT_NE(std::find(qks.begin(), qks.end(), QuadKey(
      Type::OsGeo, 0, 1, 1)), qks.end());
    EXPECT_NE(std::find(qks.begin(), qks.end(), QuadKey(
      Type::OsGeo, 1, 0, 1)), qks.end());
    EXPECT_NE(std::find(qks.begin(), qks.end(), QuadKey(
      Type::OsGeo, 1, 1, 1)), qks.end());

    qks = QuadKey::get_keys_from_longitude_latitude_bounding_box(
      Type::OsGeo, GeoCoordinateBoundingBox2d(
      GeoCoordinate2d(Longitude(-180.0), Latitude(-85.05113877)),
      GeoCoordinate2d(Longitude(+0.0), Latitude(+85.05113877))),
      1);
    EXPECT_EQ(2u, qks.size());
    EXPECT_NE(std::find(qks.begin(), qks.end(), QuadKey(
      Type::OsGeo, 1, 0, 1)), qks.end());
    EXPECT_NE(std::find(qks.begin(), qks.end(), QuadKey(
      Type::OsGeo, 0, 0, 1)), qks.end());

    qks = QuadKey::get_keys_from_longitude_latitude_bounding_box(
      Type::OsGeo, GeoCoordinateBoundingBox2d(
      GeoCoordinate2d(Longitude(+0.1), Latitude(-85.05113877)),
      GeoCoordinate2d(Longitude(+180.0), Latitude(+85.05113877))),
      1);
    EXPECT_EQ(2u, qks.size());
    EXPECT_NE(std::find(qks.begin(), qks.end(), QuadKey(
      Type::OsGeo, 1, 1, 1)), qks.end());
    EXPECT_NE(std::find(qks.begin(), qks.end(), QuadKey(
      Type::OsGeo, 0, 1, 1)), qks.end());

    qks = QuadKey::get_keys_from_longitude_latitude_bounding_box(
      Type::OsGeo, GeoCoordinateBoundingBox2d(
      GeoCoordinate2d(Longitude(-180.0), Latitude(-85.05113877)),
      GeoCoordinate2d(Longitude(+0.0), Latitude(+0.00000000))),
      1);
    EXPECT_EQ(1u, qks.size());
    EXPECT_NE(std::find(qks.begin(), qks.end(), QuadKey(
      Type::OsGeo, 0, 0, 1)), qks.end());

    qks = QuadKey::get_keys_from_longitude_latitude_bounding_box(
      Type::OsGeo, GeoCoordinateBoundingBox2d(
      GeoCoordinate2d(Longitude(-180.0), Latitude(+0.10000000)),
      GeoCoordinate2d(Longitude(+0.0), Latitude(+85.05113877))),
      1);
    EXPECT_EQ(1u, qks.size());
    EXPECT_NE(std::find(qks.begin(), qks.end(), QuadKey(
      Type::OsGeo, 1, 0, 1)), qks.end());

    qks = QuadKey::get_keys_from_longitude_latitude_bounding_box(
      Type::OsGeo, GeoCoordinateBoundingBox2d(
      GeoCoordinate2d(Longitude(+0.1), Latitude(-85.05113877)),
      GeoCoordinate2d(Longitude(+180.0), Latitude(+0.00000000))),
      1);
    EXPECT_EQ(1u, qks.size());
    EXPECT_NE(std::find(qks.begin(), qks.end(), QuadKey(
      Type::OsGeo, 0, 1, 1)), qks.end());

    qks = QuadKey::get_keys_from_longitude_latitude_bounding_box(
      Type::OsGeo, GeoCoordinateBoundingBox2d(
      GeoCoordinate2d(Longitude(+0.1), Latitude(+0.10000000)),
      GeoCoordinate2d(Longitude(+180.0), Latitude(+85.05113877))),
      1);
    EXPECT_EQ(1u, qks.size());
    EXPECT_NE(std::find(qks.begin(), qks.end(), QuadKey(
      Type::OsGeo, 1, 1, 1)), qks.end());
  }

  TEST(OSGEOSYSTEM, selected_cities)
  {
    // TODO: Implement Tests. Taken from Earthscape. No tests there.
  }
}

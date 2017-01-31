#include <gtest/gtest.h>

#include "quad_key/geo_coordinate2d.h"
#include "quad_key/quad_key.h"

#include <iostream>

namespace quad_keys
{
  class test_osgeo_system : public ::testing::Test
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
    quad_key qk(type::osgeo, 3, 3, 2);
    std::string fmt = qk.to_internal_string();
    EXPECT_EQ("2/3/3", fmt);
    quad_key qk_back = quad_key::from_internal_string(type::osgeo, fmt);
    EXPECT_EQ(qk, qk_back);

    fmt = "0/-1/-1";
    qk_back = quad_key::from_internal_string(type::osgeo, fmt);
    EXPECT_EQ(quad_key(type::osgeo, 0, 0, 0), qk_back);

    fmt = "1/1/-1";
    qk_back = quad_key::from_internal_string(type::osgeo, fmt);
    EXPECT_EQ(quad_key(type::osgeo, 0, 1, 1), qk_back);

    fmt = "1/-1/1";
    qk_back = quad_key::from_internal_string(type::osgeo, fmt);
    EXPECT_EQ(quad_key(type::osgeo, 1, 0, 1), qk_back);
  }

  TEST(OSGEOSYSTEM, GetKeyFromlongitudelatitudeAtDepthToBounds)
  {
    quad_key qk;
    geo_coordinate_bounding_box2d bbox;

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
    qk = quad_key::get_key_from_longitude_latitude_at_depth(type::osgeo,
      geo_coordinate2d(longitude(-180.0), latitude(+85.05113877)), 0);
    EXPECT_EQ(quad_key(type::osgeo, 0, 0, 0), qk);
    qk = quad_key::get_key_from_longitude_latitude_at_depth(type::osgeo,
      geo_coordinate2d(longitude(+180.0), latitude(+85.05113877)), 0);
    EXPECT_EQ(quad_key(type::osgeo, 0, 0, 0), qk);
    qk = quad_key::get_key_from_longitude_latitude_at_depth(type::osgeo,
      geo_coordinate2d(longitude(+180.0), latitude(-85.05113877)), 0);
    EXPECT_EQ(quad_key(type::osgeo, 0, 0, 0), qk);
    qk = quad_key::get_key_from_longitude_latitude_at_depth(type::osgeo,
      geo_coordinate2d(longitude(-180.0), latitude(-85.05113877)), 0);
    EXPECT_EQ(quad_key(type::osgeo, 0, 0, 0), qk);
    qk.get_geo_coordinate_bounds2d(bbox);
    EXPECT_TRUE(bbox.lower_left().near(geo_coordinate2d(
      longitude(-180.0), latitude(-85.05113877)), 1e-4)) << "Actual = "
      << bbox.lower_left() << " for " << qk;
    EXPECT_TRUE(bbox.upper_right().near(geo_coordinate2d(
      longitude(+180.0), latitude(+85.05113877)), 1e-4)) << "Actual = "
      << bbox.upper_right() << " for " << qk;

    qk = quad_key::get_key_from_longitude_latitude_at_depth(type::osgeo,
      geo_coordinate2d(longitude(+0.0), latitude(+0.00000000)), 0);
    EXPECT_EQ(quad_key(type::osgeo, 0, 0, 0), qk);

    qk = quad_key::get_key_from_longitude_latitude_at_depth(type::osgeo,
      geo_coordinate2d(longitude(-180.0), latitude(+85.05113877)), 1);
    EXPECT_EQ(quad_key(type::osgeo, 1, 0, 1), qk);
    qk.get_geo_coordinate_bounds2d(bbox);
    EXPECT_TRUE(bbox.lower_left().near(geo_coordinate2d(
      longitude(-180.0), latitude(+0.00000000)), 1e-4)) << "Actual = "
      << bbox.lower_left() << " for " << qk;
    EXPECT_TRUE(bbox.upper_right().near(geo_coordinate2d(
      longitude(+0.0), latitude(+85.05113877)), 1e-4)) << "Actual = "
      << bbox.upper_right() << " for " << qk;

    qk = quad_key::get_key_from_longitude_latitude_at_depth(type::osgeo,
      geo_coordinate2d(longitude(+180.0), latitude(+85.05113877)), 1);
    EXPECT_EQ(quad_key(type::osgeo, 1, 1, 1), qk);
    qk.get_geo_coordinate_bounds2d(bbox);
    EXPECT_TRUE(bbox.lower_left().near(geo_coordinate2d(
      longitude(+0.0), latitude(+0.00000000)), 1e-4)) << "Actual = "
      << bbox.lower_left() << " for " << qk;
    EXPECT_TRUE(bbox.upper_right().near(geo_coordinate2d(
      longitude(+180.0), latitude(+85.05113877)), 1e-4)) << "Actual = "
      << bbox.upper_right() << " for " << qk;

    qk = quad_key::get_key_from_longitude_latitude_at_depth(type::osgeo,
      geo_coordinate2d(longitude(+180.0), latitude(-85.05113877)), 1);
    EXPECT_EQ(quad_key(type::osgeo, 0, 1, 1), qk);
    qk.get_geo_coordinate_bounds2d(bbox);
    EXPECT_TRUE(bbox.lower_left().near(geo_coordinate2d(
      longitude(+0.0), latitude(-85.05113877)), 1e-4)) << "Actual = "
      << bbox.lower_left() << " for " << qk;
    EXPECT_TRUE(bbox.upper_right().near(geo_coordinate2d(
      longitude(+180.0), latitude(+0.00000000)), 1e-4)) << "Actual = "
      << bbox.upper_right() << " for " << qk;

    qk = quad_key::get_key_from_longitude_latitude_at_depth(type::osgeo,
      geo_coordinate2d(longitude(-180.0), latitude(-85.05113877)), 1);
    EXPECT_EQ(quad_key(type::osgeo, 0, 0, 1), qk);
    qk.get_geo_coordinate_bounds2d(bbox);
    EXPECT_TRUE(bbox.lower_left().near(geo_coordinate2d(
      longitude(-180.0), latitude(-85.05113877)), 1e-4)) << "Actual = "
      << bbox.lower_left() << " for " << qk;
    EXPECT_TRUE(bbox.upper_right().near(geo_coordinate2d(
      longitude(+0.0), latitude(+0.00000000)), 1e-4)) << "Actual = "
      << bbox.upper_right() << " for " << qk;

    qk = quad_key::get_key_from_longitude_latitude_at_depth(type::osgeo,
      geo_coordinate2d(longitude(-180.0), latitude(+0.00000000)), 1);
    EXPECT_EQ(quad_key(type::osgeo, 0, 0, 1), qk);
    qk = quad_key::get_key_from_longitude_latitude_at_depth(type::osgeo,
      geo_coordinate2d(longitude(+0.0), latitude(+85.05113877)), 1);
    EXPECT_EQ(quad_key(type::osgeo, 1, 0, 1), qk);
    qk = quad_key::get_key_from_longitude_latitude_at_depth(type::osgeo,
      geo_coordinate2d(longitude(+180.0), latitude(+0.00000000)), 1);
    EXPECT_EQ(quad_key(type::osgeo, 0, 1, 1), qk);
    qk = quad_key::get_key_from_longitude_latitude_at_depth(type::osgeo,
      geo_coordinate2d(longitude(+0.0), latitude(-85.05113877)), 1);
    EXPECT_EQ(quad_key(type::osgeo, 0, 0, 1), qk);
    qk = quad_key::get_key_from_longitude_latitude_at_depth(type::osgeo,
      geo_coordinate2d(longitude(+0.0), latitude(+0.00000000)), 1);
    EXPECT_EQ(quad_key(type::osgeo, 0, 0, 1), qk);

    // Note at depth 2 because of the Mercator projection the lines
    // of latitude are note perfect divisions by 2.
    qk = quad_key::get_key_from_longitude_latitude_at_depth(type::osgeo,
      geo_coordinate2d(longitude(-180.0), latitude(-85.05113877)), 2);
    EXPECT_EQ(quad_key(type::osgeo, 0, 0, 2), qk);
    qk = quad_key::get_key_from_longitude_latitude_at_depth(type::osgeo,
      geo_coordinate2d(longitude(-180.0), latitude(-66.5133)), 2);
    EXPECT_EQ(quad_key(type::osgeo, 0, 0, 2), qk);
    qk = quad_key::get_key_from_longitude_latitude_at_depth(type::osgeo,
      geo_coordinate2d(longitude(-180.0), latitude(-66.5132)), 2);
    EXPECT_EQ(quad_key(type::osgeo, 1, 0, 2), qk);
    qk = quad_key::get_key_from_longitude_latitude_at_depth(type::osgeo,
      geo_coordinate2d(longitude(-180.0), latitude(+0.1)), 2);
    EXPECT_EQ(quad_key(type::osgeo, 2, 0, 2), qk);
    qk = quad_key::get_key_from_longitude_latitude_at_depth(type::osgeo,
      geo_coordinate2d(longitude(-180.0), latitude(+66.5132)), 2);
    EXPECT_EQ(quad_key(type::osgeo, 2, 0, 2), qk);
    qk = quad_key::get_key_from_longitude_latitude_at_depth(type::osgeo,
      geo_coordinate2d(longitude(-180.0), latitude(+66.5133)), 2);
    EXPECT_EQ(quad_key(type::osgeo, 3, 0, 2), qk);
    qk = quad_key::get_key_from_longitude_latitude_at_depth(type::osgeo,
      geo_coordinate2d(longitude(-180.0), latitude(+85.05113877)), 2);
    EXPECT_EQ(quad_key(type::osgeo, 3, 0, 2), qk);
    qk = quad_key::get_key_from_longitude_latitude_at_depth(type::osgeo,
      geo_coordinate2d(longitude(-90.0), latitude(-85.05113877)), 2);
    EXPECT_EQ(quad_key(type::osgeo, 0, 0, 2), qk);
    qk = quad_key::get_key_from_longitude_latitude_at_depth(type::osgeo,
      geo_coordinate2d(longitude(-90.0), latitude(-66.5133)), 2);
    EXPECT_EQ(quad_key(type::osgeo, 0, 0, 2), qk);
    qk = quad_key::get_key_from_longitude_latitude_at_depth(type::osgeo,
      geo_coordinate2d(longitude(-90.0), latitude(-66.5132)), 2);
    EXPECT_EQ(quad_key(type::osgeo, 1, 0, 2), qk);
    qk = quad_key::get_key_from_longitude_latitude_at_depth(type::osgeo,
      geo_coordinate2d(longitude(-90.0), latitude(+0.1)), 2);
    EXPECT_EQ(quad_key(type::osgeo, 2, 0, 2), qk);
    qk = quad_key::get_key_from_longitude_latitude_at_depth(type::osgeo,
      geo_coordinate2d(longitude(-90.0), latitude(+66.5132)), 2);
    EXPECT_EQ(quad_key(type::osgeo, 2, 0, 2), qk);
    qk = quad_key::get_key_from_longitude_latitude_at_depth(type::osgeo,
      geo_coordinate2d(longitude(-90.0), latitude(+66.5133)), 2);
    EXPECT_EQ(quad_key(type::osgeo, 3, 0, 2), qk);
    qk = quad_key::get_key_from_longitude_latitude_at_depth(type::osgeo,
      geo_coordinate2d(longitude(-90.0), latitude(+85.05113877)), 2);
    EXPECT_EQ(quad_key(type::osgeo, 3, 0, 2), qk);
    qk = quad_key::get_key_from_longitude_latitude_at_depth(type::osgeo,
      geo_coordinate2d(longitude(-89.9), latitude(-85.05113877)), 2);
    EXPECT_EQ(quad_key(type::osgeo, 0, 1, 2), qk);
    qk = quad_key::get_key_from_longitude_latitude_at_depth(type::osgeo,
      geo_coordinate2d(longitude(-89.9), latitude(-66.5133)), 2);
    EXPECT_EQ(quad_key(type::osgeo, 0, 1, 2), qk);
    qk = quad_key::get_key_from_longitude_latitude_at_depth(type::osgeo,
      geo_coordinate2d(longitude(-89.9), latitude(-66.5132)), 2);
    EXPECT_EQ(quad_key(type::osgeo, 1, 1, 2), qk);
    qk = quad_key::get_key_from_longitude_latitude_at_depth(type::osgeo,
      geo_coordinate2d(longitude(-89.9), latitude(+0.1)), 2);
    EXPECT_EQ(quad_key(type::osgeo, 2, 1, 2), qk);
    qk = quad_key::get_key_from_longitude_latitude_at_depth(type::osgeo,
      geo_coordinate2d(longitude(-89.9), latitude(+66.5132)), 2);
    EXPECT_EQ(quad_key(type::osgeo, 2, 1, 2), qk);
    qk = quad_key::get_key_from_longitude_latitude_at_depth(type::osgeo,
      geo_coordinate2d(longitude(-89.9), latitude(+66.5133)), 2);
    EXPECT_EQ(quad_key(type::osgeo, 3, 1, 2), qk);
    qk = quad_key::get_key_from_longitude_latitude_at_depth(type::osgeo,
      geo_coordinate2d(longitude(-89.9), latitude(+85.05113877)), 2);
    EXPECT_EQ(quad_key(type::osgeo, 3, 1, 2), qk);
    qk = quad_key::get_key_from_longitude_latitude_at_depth(type::osgeo,
      geo_coordinate2d(longitude(+0.0), latitude(-85.05113877)), 2);
    EXPECT_EQ(quad_key(type::osgeo, 0, 1, 2), qk);
    qk = quad_key::get_key_from_longitude_latitude_at_depth(type::osgeo,
      geo_coordinate2d(longitude(+0.0), latitude(-66.5133)), 2);
    EXPECT_EQ(quad_key(type::osgeo, 0, 1, 2), qk);
    qk = quad_key::get_key_from_longitude_latitude_at_depth(type::osgeo,
      geo_coordinate2d(longitude(+0.0), latitude(-66.5132)), 2);
    EXPECT_EQ(quad_key(type::osgeo, 1, 1, 2), qk);
    qk = quad_key::get_key_from_longitude_latitude_at_depth(type::osgeo,
      geo_coordinate2d(longitude(+0.0), latitude(+0.1)), 2);
    EXPECT_EQ(quad_key(type::osgeo, 2, 1, 2), qk);
    qk = quad_key::get_key_from_longitude_latitude_at_depth(type::osgeo,
      geo_coordinate2d(longitude(+0.0), latitude(+66.5132)), 2);
    EXPECT_EQ(quad_key(type::osgeo, 2, 1, 2), qk);
    qk = quad_key::get_key_from_longitude_latitude_at_depth(type::osgeo,
      geo_coordinate2d(longitude(+0.0), latitude(+66.5133)), 2);
    EXPECT_EQ(quad_key(type::osgeo, 3, 1, 2), qk);
    qk = quad_key::get_key_from_longitude_latitude_at_depth(type::osgeo,
      geo_coordinate2d(longitude(+0.0), latitude(+85.05113877)), 2);
    EXPECT_EQ(quad_key(type::osgeo, 3, 1, 2), qk);
    qk = quad_key::get_key_from_longitude_latitude_at_depth(type::osgeo,
      geo_coordinate2d(longitude(+0.1), latitude(-85.05113877)), 2);
    EXPECT_EQ(quad_key(type::osgeo, 0, 2, 2), qk);
    qk = quad_key::get_key_from_longitude_latitude_at_depth(type::osgeo,
      geo_coordinate2d(longitude(+0.1), latitude(-66.5133)), 2);
    EXPECT_EQ(quad_key(type::osgeo, 0, 2, 2), qk);
    qk = quad_key::get_key_from_longitude_latitude_at_depth(type::osgeo,
      geo_coordinate2d(longitude(+0.1), latitude(-66.5132)), 2);
    EXPECT_EQ(quad_key(type::osgeo, 1, 2, 2), qk);
    qk = quad_key::get_key_from_longitude_latitude_at_depth(type::osgeo,
      geo_coordinate2d(longitude(+0.1), latitude(+0.1)), 2);
    EXPECT_EQ(quad_key(type::osgeo, 2, 2, 2), qk);
    qk = quad_key::get_key_from_longitude_latitude_at_depth(type::osgeo,
      geo_coordinate2d(longitude(+0.1), latitude(+66.5132)), 2);
    EXPECT_EQ(quad_key(type::osgeo, 2, 2, 2), qk);
    qk = quad_key::get_key_from_longitude_latitude_at_depth(type::osgeo,
      geo_coordinate2d(longitude(+0.1), latitude(+66.5133)), 2);
    EXPECT_EQ(quad_key(type::osgeo, 3, 2, 2), qk);
    qk = quad_key::get_key_from_longitude_latitude_at_depth(type::osgeo,
      geo_coordinate2d(longitude(+0.1), latitude(+85.05113877)), 2);
    EXPECT_EQ(quad_key(type::osgeo, 3, 2, 2), qk);
    qk = quad_key::get_key_from_longitude_latitude_at_depth(type::osgeo,
      geo_coordinate2d(longitude(+90.0), latitude(-85.05113877)), 2);
    EXPECT_EQ(quad_key(type::osgeo, 0, 2, 2), qk);
    qk = quad_key::get_key_from_longitude_latitude_at_depth(type::osgeo,
      geo_coordinate2d(longitude(+90.0), latitude(-66.5133)), 2);
    EXPECT_EQ(quad_key(type::osgeo, 0, 2, 2), qk);
    qk = quad_key::get_key_from_longitude_latitude_at_depth(type::osgeo,
      geo_coordinate2d(longitude(+90.0), latitude(-66.5132)), 2);
    EXPECT_EQ(quad_key(type::osgeo, 1, 2, 2), qk);
    qk = quad_key::get_key_from_longitude_latitude_at_depth(type::osgeo,
      geo_coordinate2d(longitude(+90.0), latitude(+0.1)), 2);
    EXPECT_EQ(quad_key(type::osgeo, 2, 2, 2), qk);
    qk = quad_key::get_key_from_longitude_latitude_at_depth(type::osgeo,
      geo_coordinate2d(longitude(+90.0), latitude(+66.5132)), 2);
    EXPECT_EQ(quad_key(type::osgeo, 2, 2, 2), qk);
    qk = quad_key::get_key_from_longitude_latitude_at_depth(type::osgeo,
      geo_coordinate2d(longitude(+90.0), latitude(+66.5133)), 2);
    EXPECT_EQ(quad_key(type::osgeo, 3, 2, 2), qk);
    qk = quad_key::get_key_from_longitude_latitude_at_depth(type::osgeo,
      geo_coordinate2d(longitude(+90.0), latitude(+85.05113877)), 2);
    EXPECT_EQ(quad_key(type::osgeo, 3, 2, 2), qk);
    qk = quad_key::get_key_from_longitude_latitude_at_depth(type::osgeo,
      geo_coordinate2d(longitude(+90.1), latitude(-85.05113877)), 2);
    EXPECT_EQ(quad_key(type::osgeo, 0, 3, 2), qk);
    qk = quad_key::get_key_from_longitude_latitude_at_depth(type::osgeo,
      geo_coordinate2d(longitude(+90.1), latitude(-66.5133)), 2);
    EXPECT_EQ(quad_key(type::osgeo, 0, 3, 2), qk);
    qk = quad_key::get_key_from_longitude_latitude_at_depth(type::osgeo,
      geo_coordinate2d(longitude(+90.1), latitude(-66.5132)), 2);
    EXPECT_EQ(quad_key(type::osgeo, 1, 3, 2), qk);
    qk = quad_key::get_key_from_longitude_latitude_at_depth(type::osgeo,
      geo_coordinate2d(longitude(+90.1), latitude(+0.1)), 2);
    EXPECT_EQ(quad_key(type::osgeo, 2, 3, 2), qk);
    qk = quad_key::get_key_from_longitude_latitude_at_depth(type::osgeo,
      geo_coordinate2d(longitude(+90.1), latitude(+66.5132)), 2);
    EXPECT_EQ(quad_key(type::osgeo, 2, 3, 2), qk);
    qk = quad_key::get_key_from_longitude_latitude_at_depth(type::osgeo,
      geo_coordinate2d(longitude(+90.1), latitude(+66.5133)), 2);
    EXPECT_EQ(quad_key(type::osgeo, 3, 3, 2), qk);
    qk = quad_key::get_key_from_longitude_latitude_at_depth(type::osgeo,
      geo_coordinate2d(longitude(+180.0), latitude(-85.05113877)), 2);
    EXPECT_EQ(quad_key(type::osgeo, 0, 3, 2), qk);
    qk = quad_key::get_key_from_longitude_latitude_at_depth(type::osgeo,
      geo_coordinate2d(longitude(+180.0), latitude(-66.5133)), 2);
    EXPECT_EQ(quad_key(type::osgeo, 0, 3, 2), qk);
    qk = quad_key::get_key_from_longitude_latitude_at_depth(type::osgeo,
      geo_coordinate2d(longitude(+180.0), latitude(-66.5132)), 2);
    EXPECT_EQ(quad_key(type::osgeo, 1, 3, 2), qk);
    qk = quad_key::get_key_from_longitude_latitude_at_depth(type::osgeo,
      geo_coordinate2d(longitude(+180.0), latitude(+0.1)), 2);
    EXPECT_EQ(quad_key(type::osgeo, 2, 3, 2), qk);
    qk = quad_key::get_key_from_longitude_latitude_at_depth(type::osgeo,
      geo_coordinate2d(longitude(+180.0), latitude(+66.5133)), 2);
    EXPECT_EQ(quad_key(type::osgeo, 3, 3, 2), qk);
    qk = quad_key::get_key_from_longitude_latitude_at_depth(type::osgeo,
      geo_coordinate2d(longitude(+180.0), latitude(+85.05113877)), 2);
    EXPECT_EQ(quad_key(type::osgeo, 3, 3, 2), qk);
  }

  TEST(OSGEOSYSTEM, get_keys_from_longitude_latitude_bounding_box)
  {
    std::vector<quad_key> qks;

    qks = quad_key::get_keys_from_longitude_latitude_bounding_box(
      type::osgeo, geo_coordinate_bounding_box2d(
      geo_coordinate2d(longitude(+0.0), latitude(-0.10000000)),
      geo_coordinate2d(longitude(+0.1), latitude(+0.10000000))),
      0);
    EXPECT_EQ(1u, qks.size());
    EXPECT_NE(std::find(qks.begin(), qks.end(), quad_key(
      type::osgeo, 0, 0, 0)), qks.end());

    qks = quad_key::get_keys_from_longitude_latitude_bounding_box(
      type::osgeo, geo_coordinate_bounding_box2d(
      geo_coordinate2d(longitude(-180.0), latitude(-85.05113877)),
      geo_coordinate2d(longitude(+180.0), latitude(+85.05113877))),
      1);
    EXPECT_EQ(4u, qks.size());
    EXPECT_NE(std::find(qks.begin(), qks.end(), quad_key(
      type::osgeo, 0, 0, 1)), qks.end());
    EXPECT_NE(std::find(qks.begin(), qks.end(), quad_key(
      type::osgeo, 0, 1, 1)), qks.end());
    EXPECT_NE(std::find(qks.begin(), qks.end(), quad_key(
      type::osgeo, 1, 0, 1)), qks.end());
    EXPECT_NE(std::find(qks.begin(), qks.end(), quad_key(
      type::osgeo, 1, 1, 1)), qks.end());

    qks = quad_key::get_keys_from_longitude_latitude_bounding_box(
      type::osgeo, geo_coordinate_bounding_box2d(
      geo_coordinate2d(longitude(-180.0), latitude(-85.05113877)),
      geo_coordinate2d(longitude(+0.0), latitude(+85.05113877))),
      1);
    EXPECT_EQ(2u, qks.size());
    EXPECT_NE(std::find(qks.begin(), qks.end(), quad_key(
      type::osgeo, 1, 0, 1)), qks.end());
    EXPECT_NE(std::find(qks.begin(), qks.end(), quad_key(
      type::osgeo, 0, 0, 1)), qks.end());

    qks = quad_key::get_keys_from_longitude_latitude_bounding_box(
      type::osgeo, geo_coordinate_bounding_box2d(
      geo_coordinate2d(longitude(+0.1), latitude(-85.05113877)),
      geo_coordinate2d(longitude(+180.0), latitude(+85.05113877))),
      1);
    EXPECT_EQ(2u, qks.size());
    EXPECT_NE(std::find(qks.begin(), qks.end(), quad_key(
      type::osgeo, 1, 1, 1)), qks.end());
    EXPECT_NE(std::find(qks.begin(), qks.end(), quad_key(
      type::osgeo, 0, 1, 1)), qks.end());

    qks = quad_key::get_keys_from_longitude_latitude_bounding_box(
      type::osgeo, geo_coordinate_bounding_box2d(
      geo_coordinate2d(longitude(-180.0), latitude(-85.05113877)),
      geo_coordinate2d(longitude(+0.0), latitude(+0.00000000))),
      1);
    EXPECT_EQ(1u, qks.size());
    EXPECT_NE(std::find(qks.begin(), qks.end(), quad_key(
      type::osgeo, 0, 0, 1)), qks.end());

    qks = quad_key::get_keys_from_longitude_latitude_bounding_box(
      type::osgeo, geo_coordinate_bounding_box2d(
      geo_coordinate2d(longitude(-180.0), latitude(+0.10000000)),
      geo_coordinate2d(longitude(+0.0), latitude(+85.05113877))),
      1);
    EXPECT_EQ(1u, qks.size());
    EXPECT_NE(std::find(qks.begin(), qks.end(), quad_key(
      type::osgeo, 1, 0, 1)), qks.end());

    qks = quad_key::get_keys_from_longitude_latitude_bounding_box(
      type::osgeo, geo_coordinate_bounding_box2d(
      geo_coordinate2d(longitude(+0.1), latitude(-85.05113877)),
      geo_coordinate2d(longitude(+180.0), latitude(+0.00000000))),
      1);
    EXPECT_EQ(1u, qks.size());
    EXPECT_NE(std::find(qks.begin(), qks.end(), quad_key(
      type::osgeo, 0, 1, 1)), qks.end());

    qks = quad_key::get_keys_from_longitude_latitude_bounding_box(
      type::osgeo, geo_coordinate_bounding_box2d(
      geo_coordinate2d(longitude(+0.1), latitude(+0.10000000)),
      geo_coordinate2d(longitude(+180.0), latitude(+85.05113877))),
      1);
    EXPECT_EQ(1u, qks.size());
    EXPECT_NE(std::find(qks.begin(), qks.end(), quad_key(
      type::osgeo, 1, 1, 1)), qks.end());
  }

  TEST(OSGEOSYSTEM, selected_cities)
  {
    // TODO: Implement Tests. Taken from Earthscape. No tests there.
  }
}

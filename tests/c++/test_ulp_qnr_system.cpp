#include <gtest/gtest.h>

#include "quad_key/geo_coordinate2d.h"
#include "quad_key/macros.h"
#include "quad_key/quad_key.h"

#include <algorithm>
#include <numeric>
#include <iostream>

namespace quad_keys
{
  class test_ulp_qnr_system : public ::testing::Test
  {
  protected:
    virtual void SetUp() {}
    virtual void TearDown() {}
  };

  TEST(MOSQNRSYSTEM, is_valid)
  {
    // Same as bing_system
  }

  TEST(MOSQNRSYSTEM, is_root_key)
  {
    // Same as bing_system
  }

  TEST(MOSQNRSYSTEM, get_parent)
  {
    // Same as bing_system
  }

  TEST(MOSQNRSYSTEM, is_my_ancestor)
  {
    // Same as bing_system
  }

  TEST(MOSQNRSYSTEM, get_ancestor)
  {
    // Same as bing_system
  }

  TEST(MOSQNRSYSTEM, get_child)
  {
    // Same as bing_system
  }

  TEST(MOSQNRSYSTEM, get_children)
  {
    // Same as bing_system
  }

  TEST(MOSQNRSYSTEM, get_descendants)
  {
    // Same as bing_system
  }

  TEST(MOSQNRSYSTEM, get_siblings)
  {
    // Same as bing_system
  }

  TEST(MOSQNRSYSTEM, get_neighbors)
  {
    // Same as bing_system
  }

  TEST(MOSQNRSYSTEM, from_string_to_string)
  {
    quad_key qk(type::ulp_qnr, 0, 0, 0);
    std::string fmt = qk.to_internal_string();
    EXPECT_EQ("1", fmt);
    quad_key qk_back = quad_key::from_internal_string(type::ulp_qnr, fmt);
    EXPECT_EQ(qk, qk_back);

    qk = quad_key(type::ulp_qnr, 0, 0, 1);
    fmt = qk.to_internal_string();
    EXPECT_EQ("4", fmt);
    qk_back = quad_key::from_internal_string(type::ulp_qnr, fmt);
    EXPECT_EQ(qk, qk_back);

    qk = quad_key(type::ulp_qnr, 0, 1, 1);
    fmt = qk.to_internal_string();
    EXPECT_EQ("5", fmt);
    qk_back = quad_key::from_internal_string(type::ulp_qnr, fmt);
    EXPECT_EQ(qk, qk_back);

    qk = quad_key(type::ulp_qnr, 0, 0, 2);
    fmt = qk.to_internal_string();
    EXPECT_EQ("16", fmt);
    qk_back = quad_key::from_internal_string(type::ulp_qnr, fmt);
    EXPECT_EQ(qk, qk_back);

    qk = quad_key(type::ulp_qnr, 0, 1, 2);
    fmt = qk.to_internal_string();
    EXPECT_EQ("17", fmt);
    qk_back = quad_key::from_internal_string(type::ulp_qnr, fmt);
    EXPECT_EQ(qk, qk_back);

    qk = quad_key(type::ulp_qnr, 1, 0, 2);
    fmt = qk.to_internal_string();
    EXPECT_EQ("20", fmt);
    qk_back = quad_key::from_internal_string(type::ulp_qnr, fmt);
    EXPECT_EQ(qk, qk_back);

    qk = quad_key(type::ulp_qnr, 1, 1, 2);
    fmt = qk.to_internal_string();
    EXPECT_EQ("21", fmt);
    qk_back = quad_key::from_internal_string(type::ulp_qnr, fmt);
    EXPECT_EQ(qk, qk_back);

    qk = quad_key(type::ulp_qnr, 0, 2, 2);
    fmt = qk.to_internal_string();
    EXPECT_EQ("18", fmt);
    qk_back = quad_key::from_internal_string(type::ulp_qnr, fmt);
    EXPECT_EQ(qk, qk_back);

    qk = quad_key(type::ulp_qnr, 0, 3, 2);
    fmt = qk.to_internal_string();
    EXPECT_EQ("19", fmt);
    qk_back = quad_key::from_internal_string(type::ulp_qnr, fmt);
    EXPECT_EQ(qk, qk_back);

    qk = quad_key(type::ulp_qnr, 1, 2, 2);
    fmt = qk.to_internal_string();
    EXPECT_EQ("22", fmt);
    qk_back = quad_key::from_internal_string(type::ulp_qnr, fmt);
    EXPECT_EQ(qk, qk_back);

    qk = quad_key(type::ulp_qnr, 1, 3, 2);
    fmt = qk.to_internal_string();
    EXPECT_EQ("23", fmt);
    qk_back = quad_key::from_internal_string(type::ulp_qnr, fmt);
    EXPECT_EQ(qk, qk_back);

    // For Sanity Purposes and to Verify NO Fence Post Erros. Use a bit of
    // brute force.
    std::vector<int> expected(32);
    std::iota(expected.begin(), expected.end(), 64);
    for (std::uint32_t i = 0; i < (8 * 4); ++i) {
      std::uint32_t row = i / 8;
      std::uint32_t col = i % 8;
      qk = quad_key(type::ulp_qnr, row, col, 3);
      fmt = qk.to_internal_string();

      char buff[3]; // '\0' 64-95
      snprintf(buff, 3, "%d", expected[i]);
      std::string expected_str(buff);

      EXPECT_EQ(expected_str, fmt) << "Failed on 64 + " << i << "th key";
      qk_back = quad_key::from_internal_string(type::ulp_qnr, fmt);
      EXPECT_EQ(qk, qk_back) << "Failed on 64 + " << i <<
        "th key";
    }

    qk = quad_key(type::ulp_qnr, 0, 0, 3);
    fmt = qk.to_internal_string();
    EXPECT_EQ("64", fmt);
    qk_back = quad_key::from_internal_string(type::ulp_qnr, fmt);
    EXPECT_EQ(qk, qk_back);
  }

  TEST(MOSQNRSYSTEM, get_key_from_longitude_latitude_at_depth_to_bounds)
  {
    quad_key computed_key;
    computed_key = quad_key::get_key_from_longitude_latitude_at_depth(
      type::ulp_qnr,geo_coordinate2d(longitude(-180.0), latitude(-90.0)), 0);
    EXPECT_EQ("1", computed_key.to_internal_string());
    computed_key = quad_key::get_key_from_longitude_latitude_at_depth(
      type::ulp_qnr, geo_coordinate2d(longitude(0.0 ), latitude(0.0)), 0);
    EXPECT_EQ("1", computed_key.to_internal_string());

    computed_key = quad_key::get_key_from_longitude_latitude_at_depth(
      type::ulp_qnr, geo_coordinate2d(longitude(-180.0 ), latitude(-90.0)),
      1);
    EXPECT_EQ("4", computed_key.to_internal_string());
    computed_key = quad_key::get_key_from_longitude_latitude_at_depth(
      type::ulp_qnr, geo_coordinate2d(longitude(-180.0 ), latitude(90.0)),
      1);
    EXPECT_EQ("4", computed_key.to_internal_string());
    computed_key = quad_key::get_key_from_longitude_latitude_at_depth(
      type::ulp_qnr, geo_coordinate2d(longitude(0.1 ), latitude(-90.0)), 1);
    EXPECT_EQ("5", computed_key.to_internal_string());
    computed_key = quad_key::get_key_from_longitude_latitude_at_depth(
      type::ulp_qnr, geo_coordinate2d(longitude(180.0 ), latitude(90.0)),
      1);
    EXPECT_EQ("5", computed_key.to_internal_string());

    computed_key = quad_key::get_key_from_longitude_latitude_at_depth(
      type::ulp_qnr, geo_coordinate2d(longitude(-180.0 ), latitude(-90.0)),
      2);
    EXPECT_EQ("16", computed_key.to_internal_string());
    computed_key = quad_key::get_key_from_longitude_latitude_at_depth(
      type::ulp_qnr, geo_coordinate2d(longitude(-89.9 ), latitude(-90.0)),
      2);
    EXPECT_EQ("17", computed_key.to_internal_string());
    computed_key = quad_key::get_key_from_longitude_latitude_at_depth(
      type::ulp_qnr, geo_coordinate2d(longitude(0.1 ), latitude(-90.0)), 2);
    EXPECT_EQ("18", computed_key.to_internal_string());
    computed_key = quad_key::get_key_from_longitude_latitude_at_depth(
      type::ulp_qnr, geo_coordinate2d(longitude(90.1 ), latitude(-90.0)), 2);
    EXPECT_EQ("19", computed_key.to_internal_string());
    computed_key = quad_key::get_key_from_longitude_latitude_at_depth(
      type::ulp_qnr, geo_coordinate2d(longitude(-180.0 ), latitude(0.1)), 2);
    EXPECT_EQ("20", computed_key.to_internal_string());
    computed_key = quad_key::get_key_from_longitude_latitude_at_depth(
      type::ulp_qnr, geo_coordinate2d(longitude(-89.9 ), latitude(0.1)), 2);
    EXPECT_EQ("21", computed_key.to_internal_string());
    computed_key = quad_key::get_key_from_longitude_latitude_at_depth(
      type::ulp_qnr, geo_coordinate2d(longitude(0.1 ), latitude(0.1)), 2);
    EXPECT_EQ("22", computed_key.to_internal_string());
    computed_key = quad_key::get_key_from_longitude_latitude_at_depth(
      type::ulp_qnr, geo_coordinate2d(longitude(90.1 ), latitude(0.1)), 2);
    EXPECT_EQ("23", computed_key.to_internal_string());
  }

  TEST(MOSQNRSYSTEM, get_keys_from_longitude_latitude_bounding_box)
  {
    std::vector<quad_key> out_keys;
    quad_key qk;

    // Select Entire Earth
    out_keys = quad_key::get_keys_from_longitude_latitude_bounding_box(
      type::ulp_qnr,
      geo_coordinate_bounding_box2d(
        geo_coordinate2d(longitude(-180.0), latitude(-90.0)),
        geo_coordinate2d(longitude(180.0), latitude(90.0))), 0);
    qk = quad_key::from_internal_string(type::ulp_qnr, "1");
    EXPECT_EQ(1, out_keys.size());
    EXPECT_NE(std::find(out_keys.begin(), out_keys.end(), qk),
      out_keys.end());

    // Select Very Center of the Earth
    out_keys = quad_key::get_keys_from_longitude_latitude_bounding_box(
      type::ulp_qnr,
      geo_coordinate_bounding_box2d(
        geo_coordinate2d(longitude(-0.1), latitude(-0.1)),
        geo_coordinate2d(longitude(0.1), latitude(0.1))), 0);
    qk = quad_key::from_internal_string(type::ulp_qnr, "1");
    EXPECT_EQ(1, out_keys.size());
    EXPECT_NE(std::find(out_keys.begin(), out_keys.end(), qk),
      out_keys.end());

    // Select Western Hemisphere
    out_keys = quad_key::get_keys_from_longitude_latitude_bounding_box(
      type::ulp_qnr,
      geo_coordinate_bounding_box2d(
        geo_coordinate2d(longitude(-180.0), latitude(-90.0)),
        geo_coordinate2d(longitude(0.0), latitude(90.0))), 1);
    qk = quad_key::from_internal_string(type::ulp_qnr, "4");
    EXPECT_EQ(1, out_keys.size());
    EXPECT_NE(std::find(out_keys.begin(), out_keys.end(), qk),
      out_keys.end());

    // Select Eastern Hemisphere
    out_keys = quad_key::get_keys_from_longitude_latitude_bounding_box(
      type::ulp_qnr,
      geo_coordinate_bounding_box2d(
        geo_coordinate2d(longitude(0.1), latitude(-90.0)),
        geo_coordinate2d(longitude(180), latitude(90.0))), 1);
    qk = quad_key::from_internal_string(type::ulp_qnr, "5");
    EXPECT_EQ(1, out_keys.size());
    EXPECT_NE(std::find(out_keys.begin(), out_keys.end(), qk),
      out_keys.end());

    // Select Entire Planet
    out_keys = quad_key::get_keys_from_longitude_latitude_bounding_box(
      type::ulp_qnr,
      geo_coordinate_bounding_box2d(
        geo_coordinate2d(longitude(-180.0), latitude(-90.0)),
        geo_coordinate2d(longitude(180), latitude(90.0))), 1);
    quad_key qka = quad_key::from_internal_string(type::ulp_qnr, "4");
    quad_key qkb = quad_key::from_internal_string(type::ulp_qnr, "5");
    EXPECT_EQ(2, out_keys.size());
    EXPECT_NE(std::find(out_keys.begin(), out_keys.end(), qka),
        out_keys.end());
    EXPECT_NE(std::find(out_keys.begin(), out_keys.end(), qkb),
      out_keys.end());

    // Select South West Corner
    out_keys = quad_key::get_keys_from_longitude_latitude_bounding_box(
      type::ulp_qnr,
      geo_coordinate_bounding_box2d(
        geo_coordinate2d(longitude(-180.0), latitude(-90.0)),
        geo_coordinate2d(longitude(-90.0), latitude(0.0))), 2);
    qk = quad_key::from_internal_string(type::ulp_qnr, "16");
    EXPECT_EQ(1, out_keys.size());
    EXPECT_NE(std::find(out_keys.begin(), out_keys.end(), qk),
      out_keys.end());

    // Select South America
    out_keys = quad_key::get_keys_from_longitude_latitude_bounding_box(
      type::ulp_qnr,
      geo_coordinate_bounding_box2d(
        geo_coordinate2d(longitude(-89.9), latitude(-90.0)),
        geo_coordinate2d(longitude(0.0), latitude(0.0))), 2);
    qk = quad_key::from_internal_string(type::ulp_qnr, "17");
    EXPECT_EQ(1, out_keys.size());
    EXPECT_NE(std::find(out_keys.begin(), out_keys.end(), qk),
      out_keys.end());

    // Select North West Corner
    out_keys = quad_key::get_keys_from_longitude_latitude_bounding_box(
      type::ulp_qnr,
      geo_coordinate_bounding_box2d(
        geo_coordinate2d(longitude(-180.0), latitude(0.1)),
        geo_coordinate2d(longitude(-90.0), latitude(90.0))), 2);
    qk = quad_key::from_internal_string(type::ulp_qnr, "20");
    EXPECT_EQ(1, out_keys.size());
    EXPECT_NE(std::find(out_keys.begin(), out_keys.end(), qk),
      out_keys.end());

    // Select Greenland
    out_keys = quad_key::get_keys_from_longitude_latitude_bounding_box(
      type::ulp_qnr,
      geo_coordinate_bounding_box2d(
        geo_coordinate2d(longitude(-89.9), latitude(0.1)),
        geo_coordinate2d(longitude(0.0), latitude(90.0))), 2);
    qk = quad_key::from_internal_string(type::ulp_qnr, "21");
    EXPECT_EQ(1, out_keys.size());
    EXPECT_NE(std::find(out_keys.begin(), out_keys.end(), qk),
      out_keys.end());

    // Select South Pole
    out_keys = quad_key::get_keys_from_longitude_latitude_bounding_box(
      type::ulp_qnr,
      geo_coordinate_bounding_box2d(
        geo_coordinate2d(longitude(0.1), latitude(-90.0)),
        geo_coordinate2d(longitude(90.0), latitude(0.0))), 2);
    qk = quad_key::from_internal_string(type::ulp_qnr, "18");
    EXPECT_EQ(1, out_keys.size());
    EXPECT_NE(std::find(out_keys.begin(), out_keys.end(), qk),
      out_keys.end());

    // Select South East Corner
    out_keys = quad_key::get_keys_from_longitude_latitude_bounding_box(
      type::ulp_qnr,
      geo_coordinate_bounding_box2d(
        geo_coordinate2d(longitude(90.1), latitude(-90.0)),
        geo_coordinate2d(longitude(180.0), latitude(0.0))), 2);
    qk = quad_key::from_internal_string(type::ulp_qnr, "19");
    EXPECT_EQ(1, out_keys.size());
    EXPECT_NE(std::find(out_keys.begin(), out_keys.end(), qk),
      out_keys.end());

    // Select Over Europe
    out_keys = quad_key::get_keys_from_longitude_latitude_bounding_box(
      type::ulp_qnr,
      geo_coordinate_bounding_box2d(
        geo_coordinate2d(longitude(0.1), latitude(0.1)),
        geo_coordinate2d(longitude(90.0), latitude(90.0))), 2);
    qk = quad_key::from_internal_string(type::ulp_qnr, "22");
    EXPECT_EQ(1, out_keys.size());
    EXPECT_NE(std::find(out_keys.begin(), out_keys.end(), qk),
        out_keys.end());

    // Select North East Corner
    out_keys = quad_key::get_keys_from_longitude_latitude_bounding_box(
      type::ulp_qnr,
      geo_coordinate_bounding_box2d(
        geo_coordinate2d(longitude(90.1), latitude(0.1)),
        geo_coordinate2d(longitude(180.0), latitude(90.0))), 2);
    qk = quad_key::from_internal_string(type::ulp_qnr, "23");
    EXPECT_EQ(1, out_keys.size());
    EXPECT_NE(std::find(out_keys.begin(), out_keys.end(), qk),
        out_keys.end());

    // Select Entire Map
    out_keys = quad_key::get_keys_from_longitude_latitude_bounding_box(
      type::ulp_qnr,
      geo_coordinate_bounding_box2d(
        geo_coordinate2d(longitude(-179.9), latitude(-89.9)),
        geo_coordinate2d(longitude(90.1), latitude(0.1))), 2);
    quad_key qk0 = quad_key::from_internal_string(type::ulp_qnr, "16");
    quad_key qk1 = quad_key::from_internal_string(type::ulp_qnr, "17");
    quad_key qk2 = quad_key::from_internal_string(type::ulp_qnr, "18");
    quad_key qk3 = quad_key::from_internal_string(type::ulp_qnr, "19");
    quad_key qk4 = quad_key::from_internal_string(type::ulp_qnr, "20");
    quad_key qk5 = quad_key::from_internal_string(type::ulp_qnr, "21");
    quad_key qk6 = quad_key::from_internal_string(type::ulp_qnr, "22");
    quad_key qk7 = quad_key::from_internal_string(type::ulp_qnr, "23");
    EXPECT_EQ(8, out_keys.size());
    EXPECT_NE(std::find(out_keys.begin(), out_keys.end(), qk0),
      out_keys.end());
    EXPECT_NE(std::find(out_keys.begin(), out_keys.end(), qk1),
      out_keys.end());
    EXPECT_NE(std::find(out_keys.begin(), out_keys.end(), qk2),
      out_keys.end());
    EXPECT_NE(std::find(out_keys.begin(), out_keys.end(), qk3),
      out_keys.end());
    EXPECT_NE(std::find(out_keys.begin(), out_keys.end(), qk4),
      out_keys.end());
    EXPECT_NE(std::find(out_keys.begin(), out_keys.end(), qk5),
      out_keys.end());
    EXPECT_NE(std::find(out_keys.begin(), out_keys.end(), qk6),
      out_keys.end());
    EXPECT_NE(std::find(out_keys.begin(), out_keys.end(), qk7),
      out_keys.end());
  }

  TEST(MOSQNRSYSTEM, selected_cities)
  {
    // TODO: Implement Tests. Taken from Earthscape. No tests there.
  }
}

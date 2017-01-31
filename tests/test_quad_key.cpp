#include <gtest/gtest.h>

#include "quad_key/geo_coordinate2d.h"
#include "quad_key/quad_key.h"

#include <iostream>

namespace quad_keys
{
  class geo_coordinate2dTest : public ::testing::Test
  {
  protected:
    virtual void SetUp() {}
    virtual void TearDown() {}
  };

  // Tests that are agnostic of a specific system.
  TEST(QUADKEY, default_ctor)
  {
    quad_key key;
    EXPECT_EQ(0u, key.get_row());
    EXPECT_EQ(0u, key.get_col());
    EXPECT_EQ(0u, key.get_depth());
    EXPECT_EQ(type::none, key.get_type());
  }

  TEST(QUADKEY, ctor_only_type)
  {
    {
      quad_key key(type::bing);
      EXPECT_EQ(0u, key.get_row());
      EXPECT_EQ(0u, key.get_col());
      EXPECT_EQ(0u, key.get_depth());
      EXPECT_EQ(type::bing, key.get_type());
    }
    {
      quad_key key(type::lat_long);
      EXPECT_EQ(0u, key.get_row());
      EXPECT_EQ(0u, key.get_col());
      EXPECT_EQ(0u, key.get_depth());
      EXPECT_EQ(type::lat_long, key.get_type());
    }
    {
      quad_key key(type::ulp_qnr);
      EXPECT_EQ(0u, key.get_row());
      EXPECT_EQ(0u, key.get_col());
      EXPECT_EQ(0u, key.get_depth());
      EXPECT_EQ(type::ulp_qnr, key.get_type());
    }
    {
      quad_key key(type::morton);
      EXPECT_EQ(0u, key.get_row());
      EXPECT_EQ(0u, key.get_col());
      EXPECT_EQ(0u, key.get_depth());
      EXPECT_EQ(type::morton, key.get_type());
    }
    {
      quad_key key(type::none);
      EXPECT_EQ(0u, key.get_row());
      EXPECT_EQ(0u, key.get_col());
      EXPECT_EQ(0u, key.get_depth());
      EXPECT_EQ(type::none, key.get_type());
    }
    {
      quad_key key(type::osgeo);
      EXPECT_EQ(0u, key.get_row());
      EXPECT_EQ(0u, key.get_col());
      EXPECT_EQ(0u, key.get_depth());
      EXPECT_EQ(type::osgeo, key.get_type());
    }
  }

  TEST(QUADKEY, copy_ctor)
  {
    quad_key key(type::osgeo);
    EXPECT_EQ(0u, key.get_row());
    EXPECT_EQ(0u, key.get_col());
    EXPECT_EQ(0u, key.get_depth());
    EXPECT_EQ(type::osgeo, key.get_type());

    quad_key copy(key);
    EXPECT_EQ(0u, copy.get_row());
    EXPECT_EQ(0u, copy.get_col());
    EXPECT_EQ(0u, copy.get_depth());
    EXPECT_EQ(type::osgeo, copy.get_type());
  }

  TEST(QUADKEY, assignment_operator)
  {
    quad_key key(type::osgeo);
    EXPECT_EQ(0u, key.get_row());
    EXPECT_EQ(0u, key.get_col());
    EXPECT_EQ(0u, key.get_depth());
    EXPECT_EQ(type::osgeo, key.get_type());

    quad_key copy;
    copy = key;
    EXPECT_EQ(0u, copy.get_row());
    EXPECT_EQ(0u, copy.get_col());
    EXPECT_EQ(0u, copy.get_depth());
    EXPECT_EQ(type::osgeo, copy.get_type());
  }

  TEST(QUADKEY, is_root_key)
  {
    quad_key key(type::osgeo);
    EXPECT_TRUE(key.is_root_key());
  }

  // Tests that outside of construction are agnostic of a system.
  TEST(QUADKEY, system_specific_ctor)
  {
    auto types = { type::bing, type::lat_long, type::ulp_qnr, type::morton,
      type::none, type::osgeo };
    for (auto type : types) {
      for (uint8_t depth = 0; depth < 10; ++depth) {
        uint32_t max_rows = quad_key::max_rows(type, depth);
        uint32_t max_cols = quad_key::max_cols(type, depth);

        std::string typeStr = quad_key(type).type_as_string();

        quad_key invalid(type, max_rows, max_cols, depth);
        EXPECT_EQ(quad_key(), invalid) <<
            (std::string("Failed invalid check on type ") + typeStr);
        quad_key valid(type, max_rows - 1, max_cols - 1, depth);
        EXPECT_EQ(quad_key(type, max_rows - 1, max_cols - 1, depth),
            valid) << (std::string("Failed valid check on type ") +
            typeStr);
      }
    }
  }
}

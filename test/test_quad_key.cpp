#include <gtest/gtest.h>

#include "quad_keys/geo_coordinate2d.h"
#include "quad_keys/quad_key.h"

#include <iostream>

namespace quad_keys
{
  class QuadKeyTest : public ::testing::Test
  {
  protected:
    virtual void SetUp() {}
    virtual void TearDown() {}
  };

  // Tests that are agnostic of a specific system.
  TEST(QUADKEY, default_ctor)
  {
    QuadKey key;
    EXPECT_EQ(0u, key.get_row());
    EXPECT_EQ(0u, key.get_col());
    EXPECT_EQ(0u, key.get_depth());
    EXPECT_EQ(Type::None, key.get_type());
  }

  TEST(QUADKEY, ctor_only_type)
  {
    {
      QuadKey key(Type::Bing);
      EXPECT_EQ(0u, key.get_row());
      EXPECT_EQ(0u, key.get_col());
      EXPECT_EQ(0u, key.get_depth());
      EXPECT_EQ(Type::Bing, key.get_type());
    }
    {
      QuadKey key(Type::LatLon);
      EXPECT_EQ(0u, key.get_row());
      EXPECT_EQ(0u, key.get_col());
      EXPECT_EQ(0u, key.get_depth());
      EXPECT_EQ(Type::LatLon, key.get_type());
    }
    {
      QuadKey key(Type::UlpQnr);
      EXPECT_EQ(0u, key.get_row());
      EXPECT_EQ(0u, key.get_col());
      EXPECT_EQ(0u, key.get_depth());
      EXPECT_EQ(Type::UlpQnr, key.get_type());
    }
    {
      QuadKey key(Type::Morton);
      EXPECT_EQ(0u, key.get_row());
      EXPECT_EQ(0u, key.get_col());
      EXPECT_EQ(0u, key.get_depth());
      EXPECT_EQ(Type::Morton, key.get_type());
    }
    {
      QuadKey key(Type::None);
      EXPECT_EQ(0u, key.get_row());
      EXPECT_EQ(0u, key.get_col());
      EXPECT_EQ(0u, key.get_depth());
      EXPECT_EQ(Type::None, key.get_type());
    }
    {
      QuadKey key(Type::OsGeo);
      EXPECT_EQ(0u, key.get_row());
      EXPECT_EQ(0u, key.get_col());
      EXPECT_EQ(0u, key.get_depth());
      EXPECT_EQ(Type::OsGeo, key.get_type());
    }
  }

  TEST(QUADKEY, copy_ctor)
  {
    QuadKey key(Type::OsGeo);
    EXPECT_EQ(0u, key.get_row());
    EXPECT_EQ(0u, key.get_col());
    EXPECT_EQ(0u, key.get_depth());
    EXPECT_EQ(Type::OsGeo, key.get_type());

    QuadKey copy(key);
    EXPECT_EQ(0u, copy.get_row());
    EXPECT_EQ(0u, copy.get_col());
    EXPECT_EQ(0u, copy.get_depth());
    EXPECT_EQ(Type::OsGeo, copy.get_type());
  }

  TEST(QUADKEY, assignment_operator)
  {
    QuadKey key(Type::OsGeo);
    EXPECT_EQ(0u, key.get_row());
    EXPECT_EQ(0u, key.get_col());
    EXPECT_EQ(0u, key.get_depth());
    EXPECT_EQ(Type::OsGeo, key.get_type());

    QuadKey copy;
    copy = key;
    EXPECT_EQ(0u, copy.get_row());
    EXPECT_EQ(0u, copy.get_col());
    EXPECT_EQ(0u, copy.get_depth());
    EXPECT_EQ(Type::OsGeo, copy.get_type());
  }

  TEST(QUADKEY, is_root_key)
  {
    QuadKey key(Type::OsGeo);
    EXPECT_TRUE(key.is_root_key());
  }

  // Tests that outside of construction are agnostic of a system.
  TEST(QUADKEY, system_specific_ctor)
  {
    auto types = { Type::Bing, Type::LatLon, Type::UlpQnr, Type::Morton,
      Type::None, Type::OsGeo};
    for (auto type : types) {
      for (uint8_t depth = 0; depth < 10; ++depth) {
        uint32_t max_rows = QuadKey::max_rows(type, depth);
        uint32_t max_cols = QuadKey::max_cols(type, depth);

        std::string type_str = QuadKey(type).type_as_string();

        QuadKey invalid(type, max_rows, max_cols, depth);
        EXPECT_EQ(QuadKey(), invalid) <<
          (std::string("Failed invalid check on type ") + type_str);
        QuadKey valid(type, max_rows - 1, max_cols - 1, depth);
        EXPECT_EQ(QuadKey(type, max_rows - 1, max_cols - 1, depth),
          valid) << (std::string("Failed valid check on type ") +
          type_str);
      }
    }
  }
}

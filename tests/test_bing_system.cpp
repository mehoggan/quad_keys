#include <gtest/gtest.h>

#include "quad_key/geo_coordinate2d.h"
#include "quad_key/quad_key.h"

#include <cmath>

namespace quad_keys
{
  class test_bing_system : public ::testing::Test
  {
  protected:
    virtual void SetUp() {}
    virtual void TearDown() {}
  };

  TEST(BINGSYSTEM, is_valid)
  {
  }

  TEST(BINGSYSTEM, is_root_key)
  {
  }

  TEST(BINGSYSTEM, get_parent)
  {
    {
      quad_key bing_key0(type::bing, 0, 0, 1);
      quad_key bing_key1(type::bing, 1, 0, 1);
      quad_key bing_key2(type::bing, 1, 1, 1);
      quad_key bing_key3(type::bing, 0, 1, 1);

      quad_key bing_key_p(type::bing, 0, 0, 0);

      ASSERT_TRUE(bing_key_p.get_type() == type::bing);
      ASSERT_TRUE(bing_key0.get_type() == type::bing);
      ASSERT_TRUE(bing_key1.get_type() == type::bing);
      ASSERT_TRUE(bing_key2.get_type() == type::bing);
      ASSERT_TRUE(bing_key3.get_type() == type::bing);

      EXPECT_EQ(bing_key_p, bing_key0.get_parent());
      EXPECT_EQ(bing_key_p, bing_key1.get_parent());
      EXPECT_EQ(bing_key_p, bing_key2.get_parent());
      EXPECT_EQ(bing_key_p, bing_key3.get_parent());
    }

    {
      quad_key bing_key0(type::bing, 5, 6, 3);
      quad_key bing_key1(type::bing, 4, 6, 3);
      quad_key bing_key2(type::bing, 4, 7, 3);
      quad_key bing_key3(type::bing, 5, 7, 3);

      quad_key bing_key_p(type::bing, 2, 3, 2);

      ASSERT_TRUE(bing_key_p.get_type() == type::bing);
      ASSERT_TRUE(bing_key0.get_type() == type::bing);
      ASSERT_TRUE(bing_key1.get_type() == type::bing);
      ASSERT_TRUE(bing_key2.get_type() == type::bing);
      ASSERT_TRUE(bing_key3.get_type() == type::bing);

      EXPECT_EQ(bing_key_p, bing_key0.get_parent());
      EXPECT_EQ(bing_key_p, bing_key1.get_parent());
      EXPECT_EQ(bing_key_p, bing_key2.get_parent());
      EXPECT_EQ(bing_key_p, bing_key3.get_parent());
    }
  }

  TEST(BINGSYSTEM, is_my_ancestor)
  {
    {
      quad_key key(type::bing, 5, 7, 3);
      EXPECT_FALSE(key.is_my_ancestor(quad_key()));
      EXPECT_FALSE(key.is_my_ancestor(quad_key(type::osgeo, 2, 3, 2)));
      EXPECT_FALSE(key.is_my_ancestor(quad_key(type::osgeo, 0, 0, 0)));
      EXPECT_TRUE(key.is_my_ancestor(quad_key(type::bing, 2, 3, 2)));
      EXPECT_TRUE(key.is_my_ancestor(quad_key(type::bing, 0, 0, 0)));
      EXPECT_FALSE(key.is_my_ancestor(quad_key(type::bing, 5, 7, 3)));

      quad_key none;
      EXPECT_FALSE(none.is_my_ancestor(quad_key()));
    }

    {
      quad_key key(type::bing, 5, 7, 3);
      EXPECT_FALSE(key.is_my_ancestor(quad_key()));
      EXPECT_FALSE(key.is_my_ancestor(quad_key(type::osgeo, 2, 3, 2)));
      EXPECT_FALSE(key.is_my_ancestor(quad_key(type::osgeo, 0, 0, 0)));
      EXPECT_TRUE(key.is_my_ancestor(quad_key(type::bing, 2, 3, 2)));
      EXPECT_TRUE(key.is_my_ancestor(quad_key(type::bing, 0, 0, 0)));
      EXPECT_FALSE(key.is_my_ancestor(quad_key(type::bing, 5, 7, 3)));

      quad_key none;
      EXPECT_FALSE(none.is_my_ancestor(quad_key()));
    }
  }

  TEST(BINGSYSTEM, get_ancestor)
  {
    {
      quad_key key(type::bing, 0, 7, 3);
      quad_key ancestor(type::bing, 0, 1, 1);
      EXPECT_EQ(ancestor, key.get_ancestor(2));
    }

    {
      quad_key key(type::bing, 4, 31, 5);
      quad_key ancestor(type::bing, 0, 1, 1);
      EXPECT_EQ(ancestor, key.get_ancestor(4));
    }

    {
      quad_key key(type::bing, 4, 31, 5);
      quad_key ancestor(type::bing, 0, 3, 2);
      EXPECT_EQ(ancestor, key.get_ancestor(3));
    }

    {
      quad_key key(type::bing, 4, 31, 5);
      quad_key ancestor(type::bing, 1, 7, 3);
      EXPECT_EQ(ancestor, key.get_ancestor(2));
    }
  }

  TEST(BINGSYSTEM, get_child)
  {
    EXPECT_EQ(quad_key(),
      quad_key().get_child(quad_key::quadrant::north_west));
    uint8_t max_depth_bing = quad_key::max_depth(type::bing);
    EXPECT_EQ(quad_key(), quad_key(type::bing, 0, 0,
      max_depth_bing).get_child(quad_key::quadrant::north_east));


    {
      quad_key key(type::bing, 0, 0, 3);
      EXPECT_EQ(quad_key(type::bing, 1, 0, 4),
        key.get_child(quad_key::quadrant::north_west));
      EXPECT_EQ(quad_key(type::bing, 1, 1, 4),
        key.get_child(quad_key::quadrant::north_east));
      EXPECT_EQ(quad_key(type::bing, 0, 1, 4),
        key.get_child(quad_key::quadrant::south_east));
      EXPECT_EQ(quad_key(type::bing, 0, 0, 4),
        key.get_child(quad_key::quadrant::south_west));
    }

    {
      quad_key key(type::bing, 2, 3, 3);
      EXPECT_EQ(quad_key(type::bing, 5, 6, 4),
        key.get_child(quad_key::quadrant::north_west));
      EXPECT_EQ(quad_key(type::bing, 5, 7, 4),
        key.get_child(quad_key::quadrant::north_east));
      EXPECT_EQ(quad_key(type::bing, 4, 7, 4),
        key.get_child(quad_key::quadrant::south_east));
      EXPECT_EQ(quad_key(type::bing, 4, 6, 4),
        key.get_child(quad_key::quadrant::south_west));
    }
  }

  TEST(BINGSYSTEM, get_children)
  {
    std::vector<quad_key> test_keys;
    uint8_t max_depthBing = quad_key::max_depth(type::bing);
    test_keys = quad_key(type::bing, 0, 0, max_depthBing).get_children();
    EXPECT_TRUE(test_keys.empty());

    test_keys.clear();

    test_keys = quad_key(type::bing, 0, 0, 1).get_children();
    EXPECT_EQ(4u, test_keys.size());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      quad_key(type::bing, 0, 0, 2)), test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      quad_key(type::bing, 0, 1, 2)), test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      quad_key(type::bing, 1, 0, 2)), test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      quad_key(type::bing, 1, 1, 2)), test_keys.end());

    test_keys = quad_key(type::bing, 0, 1, 1).get_children();
    EXPECT_EQ(4u, test_keys.size());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      quad_key(type::bing, 0, 2, 2)), test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      quad_key(type::bing, 0, 3, 2)), test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      quad_key(type::bing, 1, 2, 2)), test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      quad_key(type::bing, 1, 3, 2)), test_keys.end());

    test_keys = quad_key(type::bing, 1, 0, 1).get_children();
    EXPECT_EQ(4u, test_keys.size());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      quad_key(type::bing, 2, 0, 2)), test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      quad_key(type::bing, 2, 1, 2)), test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      quad_key(type::bing, 3, 0, 2)), test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      quad_key(type::bing, 3, 1, 2)), test_keys.end());

    test_keys = quad_key(type::bing, 1, 1, 1).get_children();
    EXPECT_EQ(4u, test_keys.size());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      quad_key(type::bing, 2, 2, 2)), test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      quad_key(type::bing, 2, 3, 2)), test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      quad_key(type::bing, 3, 2, 2)), test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      quad_key(type::bing, 3, 3, 2)), test_keys.end());

    test_keys.clear();
  }

  TEST(BINGSYSTEM, get_descendants)
  {
    uint8_t bingMaxDepth = quad_key::max_depth(type::bing);
    quad_key testKey(type::bing, 0, 0, bingMaxDepth - 3);
    std::vector<quad_key> test_keys;
    test_keys = testKey.get_descendants(4);
    EXPECT_EQ(0u, test_keys.size());

    quad_key none;
    test_keys = none.get_descendants(1);
    EXPECT_EQ(0u, test_keys.size());

    {
      quad_key key(type::bing, 0, 0, 0);
      test_keys = key.get_descendants(0);
      EXPECT_EQ(0u, test_keys.size());
    }

    {
      quad_key key(type::bing, 0, 0, 0);

      test_keys = key.get_descendants(1);
      EXPECT_EQ(4u, test_keys.size());
      EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
        quad_key(type::bing, 0, 0, 1)), test_keys.end());
      EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
        quad_key(type::bing, 0, 1, 1)), test_keys.end());
      EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
        quad_key(type::bing, 1, 0, 1)), test_keys.end());
      EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
        quad_key(type::bing, 1, 1, 1)), test_keys.end());

      test_keys = key.get_descendants(2);
      EXPECT_EQ(16u, test_keys.size());
      EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
        quad_key(type::bing, 0, 0, 2)), test_keys.end());
      EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
        quad_key(type::bing, 0, 1, 2)), test_keys.end());
      EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
        quad_key(type::bing, 0, 2, 2)), test_keys.end());
      EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
        quad_key(type::bing, 0, 3, 2)), test_keys.end());
      EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
        quad_key(type::bing, 1, 0, 2)), test_keys.end());
      EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
        quad_key(type::bing, 1, 1, 2)), test_keys.end());
      EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
        quad_key(type::bing, 1, 2, 2)), test_keys.end());
      EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
        quad_key(type::bing, 1, 3, 2)), test_keys.end());
      EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
        quad_key(type::bing, 2, 0, 2)), test_keys.end());
      EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
        quad_key(type::bing, 2, 1, 2)), test_keys.end());
      EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
        quad_key(type::bing, 2, 2, 2)), test_keys.end());
      EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
        quad_key(type::bing, 2, 3, 2)), test_keys.end());
      EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
        quad_key(type::bing, 3, 0, 2)), test_keys.end());
      EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
        quad_key(type::bing, 3, 1, 2)), test_keys.end());
      EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
        quad_key(type::bing, 3, 2, 2)), test_keys.end());
      EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
        quad_key(type::bing, 3, 3, 2)), test_keys.end());

      test_keys = key.get_descendants(3);
      EXPECT_EQ(64u, test_keys.size());
      EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
        quad_key(type::bing, 0, 0, 3)), test_keys.end());
      EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
        quad_key(type::bing, 0, 1, 3)), test_keys.end());
      EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
        quad_key(type::bing, 0, 2, 3)), test_keys.end());
      EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
        quad_key(type::bing, 0, 3, 3)), test_keys.end());
      EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
        quad_key(type::bing, 0, 4, 3)), test_keys.end());
      EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
        quad_key(type::bing, 0, 5, 3)), test_keys.end());
      EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
        quad_key(type::bing, 0, 6, 3)), test_keys.end());
      EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
        quad_key(type::bing, 0, 7, 3)), test_keys.end());
      EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
        quad_key(type::bing, 1, 0, 3)), test_keys.end());
      EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
        quad_key(type::bing, 1, 1, 3)), test_keys.end());
      EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
        quad_key(type::bing, 1, 2, 3)), test_keys.end());
      EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
        quad_key(type::bing, 1, 3, 3)), test_keys.end());
      EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
        quad_key(type::bing, 1, 4, 3)), test_keys.end());
      EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
        quad_key(type::bing, 1, 5, 3)), test_keys.end());
      EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
        quad_key(type::bing, 1, 6, 3)), test_keys.end());
      EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
        quad_key(type::bing, 1, 7, 3)), test_keys.end());
      EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
        quad_key(type::bing, 2, 0, 3)), test_keys.end());
      EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
        quad_key(type::bing, 2, 1, 3)), test_keys.end());
      EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
        quad_key(type::bing, 2, 2, 3)), test_keys.end());
      EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
        quad_key(type::bing, 2, 3, 3)), test_keys.end());
      EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
        quad_key(type::bing, 2, 4, 3)), test_keys.end());
      EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
        quad_key(type::bing, 2, 5, 3)), test_keys.end());
      EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
        quad_key(type::bing, 2, 6, 3)), test_keys.end());
      EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
        quad_key(type::bing, 2, 7, 3)), test_keys.end());
      EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
        quad_key(type::bing, 3, 0, 3)), test_keys.end());
      EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
        quad_key(type::bing, 3, 1, 3)), test_keys.end());
      EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
        quad_key(type::bing, 3, 2, 3)), test_keys.end());
      EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
        quad_key(type::bing, 3, 3, 3)), test_keys.end());
      EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
        quad_key(type::bing, 3, 4, 3)), test_keys.end());
      EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
        quad_key(type::bing, 3, 5, 3)), test_keys.end());
      EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
        quad_key(type::bing, 3, 6, 3)), test_keys.end());
      EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
        quad_key(type::bing, 3, 7, 3)), test_keys.end());
      EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
        quad_key(type::bing, 4, 0, 3)), test_keys.end());
      EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
        quad_key(type::bing, 4, 1, 3)), test_keys.end());
      EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
        quad_key(type::bing, 4, 2, 3)), test_keys.end());
      EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
        quad_key(type::bing, 4, 3, 3)), test_keys.end());
      EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
        quad_key(type::bing, 4, 4, 3)), test_keys.end());
      EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
        quad_key(type::bing, 4, 5, 3)), test_keys.end());
      EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
        quad_key(type::bing, 4, 6, 3)), test_keys.end());
      EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
        quad_key(type::bing, 4, 7, 3)), test_keys.end());
      EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
        quad_key(type::bing, 5, 0, 3)), test_keys.end());
      EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
        quad_key(type::bing, 5, 1, 3)), test_keys.end());
      EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
        quad_key(type::bing, 5, 2, 3)), test_keys.end());
      EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
        quad_key(type::bing, 5, 3, 3)), test_keys.end());
      EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
        quad_key(type::bing, 5, 4, 3)), test_keys.end());
      EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
        quad_key(type::bing, 5, 5, 3)), test_keys.end());
      EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
        quad_key(type::bing, 5, 6, 3)), test_keys.end());
      EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
        quad_key(type::bing, 5, 7, 3)), test_keys.end());
      EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
        quad_key(type::bing, 6, 0, 3)), test_keys.end());
      EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
        quad_key(type::bing, 6, 1, 3)), test_keys.end());
      EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
        quad_key(type::bing, 6, 2, 3)), test_keys.end());
      EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
        quad_key(type::bing, 6, 3, 3)), test_keys.end());
      EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
        quad_key(type::bing, 6, 4, 3)), test_keys.end());
      EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
        quad_key(type::bing, 6, 5, 3)), test_keys.end());
      EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
        quad_key(type::bing, 6, 6, 3)), test_keys.end());
      EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
        quad_key(type::bing, 6, 7, 3)), test_keys.end());
      EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
        quad_key(type::bing, 7, 0, 3)), test_keys.end());
      EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
        quad_key(type::bing, 7, 1, 3)), test_keys.end());
      EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
        quad_key(type::bing, 7, 2, 3)), test_keys.end());
      EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
        quad_key(type::bing, 7, 3, 3)), test_keys.end());
      EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
        quad_key(type::bing, 7, 4, 3)), test_keys.end());
      EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
        quad_key(type::bing, 7, 5, 3)), test_keys.end());
      EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
        quad_key(type::bing, 7, 6, 3)), test_keys.end());
      EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
        quad_key(type::bing, 7, 7, 3)), test_keys.end());
    }
  }

  TEST(BINGSYSTEM, get_siblings)
  {
    std::vector<quad_key> test_keys;

    test_keys = quad_key().get_siblings();
    EXPECT_TRUE(test_keys.empty());

    test_keys = quad_key(type::bing, 0, 0, 0).get_siblings();
    EXPECT_TRUE(test_keys.empty());

    test_keys = quad_key(type::bing, 0, 0, 1).get_siblings();
    EXPECT_EQ(3u, test_keys.size());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      quad_key(type::bing, 0, 1, 1)), test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      quad_key(type::bing, 1, 1, 1)), test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      quad_key(type::bing, 1, 0, 1)), test_keys.end());
  }

  TEST(BINGSYSTEM, get_neighbors)
  {
    std::vector<quad_key> test_keys;

    test_keys = quad_key().get_neighbors();
    EXPECT_TRUE(test_keys.empty());

    test_keys = quad_key(type::bing, 0, 0, 0).get_neighbors();
    EXPECT_TRUE(test_keys.empty());

    test_keys.clear();

    test_keys = quad_key(type::bing, 0, 0, 2).get_neighbors();
    EXPECT_EQ(5u, test_keys.size());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      quad_key(type::bing, 0, 1, 2)), test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      quad_key(type::bing, 1, 1, 2)), test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      quad_key(type::bing, 1, 0, 2)), test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      quad_key(type::bing, 0, 3, 2)), test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      quad_key(type::bing, 1, 3, 2)), test_keys.end());

    test_keys.clear();

    test_keys = quad_key(type::bing, 0, 1, 2).get_neighbors();
    EXPECT_EQ(5u, test_keys.size());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      quad_key(type::bing, 0, 0, 2)), test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      quad_key(type::bing, 1, 0, 2)), test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      quad_key(type::bing, 1, 1, 2)), test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      quad_key(type::bing, 1, 2, 2)), test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      quad_key(type::bing, 0, 2, 2)), test_keys.end());

    test_keys.clear();

    test_keys = quad_key(type::bing, 0, 2, 2).get_neighbors();
    EXPECT_EQ(5u, test_keys.size());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      quad_key(type::bing, 0, 1, 2)), test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      quad_key(type::bing, 1, 1, 2)), test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      quad_key(type::bing, 1, 2, 2)), test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      quad_key(type::bing, 1, 3, 2)), test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      quad_key(type::bing, 0, 3, 2)), test_keys.end());

    test_keys.clear();

    test_keys = quad_key(type::bing, 0, 3, 2).get_neighbors();
    EXPECT_EQ(5u, test_keys.size());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      quad_key(type::bing, 0, 2, 2)), test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      quad_key(type::bing, 1, 2, 2)), test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      quad_key(type::bing, 1, 3, 2)), test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      quad_key(type::bing, 1, 0, 2)), test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      quad_key(type::bing, 0, 0, 2)), test_keys.end());

    test_keys.clear();

    test_keys = quad_key(type::bing, 1, 0, 2).get_neighbors();
    EXPECT_EQ(8u, test_keys.size());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      quad_key(type::bing, 0, 0, 2)), test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      quad_key(type::bing, 0, 1, 2)), test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      quad_key(type::bing, 1, 1, 2)), test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      quad_key(type::bing, 2, 1, 2)), test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      quad_key(type::bing, 2, 0, 2)), test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      quad_key(type::bing, 2, 3, 2)), test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      quad_key(type::bing, 1, 3, 2)), test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      quad_key(type::bing, 0, 3, 2)), test_keys.end());

    test_keys.clear();

    test_keys = quad_key(type::bing, 1, 1, 2).get_neighbors();
    EXPECT_EQ(8u, test_keys.size());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      quad_key(type::bing, 1, 0, 2)), test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      quad_key(type::bing, 0, 0, 2)), test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      quad_key(type::bing, 0, 1, 2)), test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      quad_key(type::bing, 2, 2, 2)), test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      quad_key(type::bing, 2, 1, 2)), test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      quad_key(type::bing, 2, 0, 2)), test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      quad_key(type::bing, 0, 2, 2)), test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      quad_key(type::bing, 1, 2, 2)), test_keys.end());

    test_keys.clear();

    test_keys = quad_key(type::bing, 1, 2, 2).get_neighbors();
    EXPECT_EQ(8u, test_keys.size());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      quad_key(type::bing, 1, 1, 2)), test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      quad_key(type::bing, 0, 1, 2)), test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      quad_key(type::bing, 0, 2, 2)), test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      quad_key(type::bing, 2, 3, 2)), test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      quad_key(type::bing, 2, 2, 2)), test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      quad_key(type::bing, 2, 1, 2)), test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      quad_key(type::bing, 0, 3, 2)), test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      quad_key(type::bing, 1, 3, 2)), test_keys.end());

    test_keys.clear();

    test_keys = quad_key(type::bing, 1, 3, 2).get_neighbors();
    EXPECT_EQ(8u, test_keys.size());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      quad_key(type::bing, 1, 2, 2)), test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      quad_key(type::bing, 0, 2, 2)), test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      quad_key(type::bing, 0, 3, 2)), test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      quad_key(type::bing, 2, 0, 2)), test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      quad_key(type::bing, 2, 3, 2)), test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      quad_key(type::bing, 2, 2, 2)), test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      quad_key(type::bing, 0, 0, 2)), test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      quad_key(type::bing, 1, 0, 2)), test_keys.end());

    test_keys.clear();

    test_keys = quad_key(type::bing, 4, 7, 3).get_neighbors();
    EXPECT_EQ(8u, test_keys.size());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      quad_key(type::bing, 3, 7, 3)), test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      quad_key(type::bing, 3, 6, 3)), test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      quad_key(type::bing, 4, 6, 3)), test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      quad_key(type::bing, 5, 6, 3)), test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      quad_key(type::bing, 5, 7, 3)), test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      quad_key(type::bing, 5, 0, 3)), test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      quad_key(type::bing, 4, 0, 3)), test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      quad_key(type::bing, 3, 0, 3)), test_keys.end());

    test_keys.clear();

    test_keys = quad_key(type::bing, 4, 0, 3).get_neighbors();
    EXPECT_EQ(8u, test_keys.size());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      quad_key(type::bing, 3, 0, 3)), test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      quad_key(type::bing, 3, 1, 3)), test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      quad_key(type::bing, 4, 1, 3)), test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      quad_key(type::bing, 5, 1, 3)), test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      quad_key(type::bing, 5, 0, 3)), test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      quad_key(type::bing, 5, 7, 3)), test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      quad_key(type::bing, 4, 7, 3)), test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      quad_key(type::bing, 3, 7, 3)), test_keys.end());

    test_keys.clear();
  }

  TEST(BINGSYSTEM, from_string_to_string)
  {
    {
      quad_key root = quad_key::from_internal_string(type::bing, "");
      EXPECT_EQ(0u, root.get_row());
      EXPECT_EQ(0u, root.get_col());
      EXPECT_EQ(0u, root.get_depth());
    }

    {
      quad_key key;
      key = quad_key::from_internal_string(type::bing, "0");
      EXPECT_EQ(1u, key.get_row());
      EXPECT_EQ(0u, key.get_col());
      EXPECT_EQ(1u, key.get_depth());
      EXPECT_EQ("0", key.to_internal_string());
      key = quad_key::from_internal_string(type::bing, "1");
      EXPECT_EQ(1u, key.get_row());
      EXPECT_EQ(1u, key.get_col());
      EXPECT_EQ(1u, key.get_depth());
      EXPECT_EQ("1", key.to_internal_string());
      key = quad_key::from_internal_string(type::bing, "2");
      EXPECT_EQ(0u, key.get_row());
      EXPECT_EQ(0u, key.get_col());
      EXPECT_EQ(1u, key.get_depth());
      EXPECT_EQ("2", key.to_internal_string());
      key = quad_key::from_internal_string(type::bing, "3");
      EXPECT_EQ(0u, key.get_row());
      EXPECT_EQ(1u, key.get_col());
      EXPECT_EQ(1u, key.get_depth());
      EXPECT_EQ("3", key.to_internal_string());
    }

    {
      quad_key key;
      key = quad_key::from_internal_string(type::bing, "00");
      EXPECT_EQ(3u, key.get_row());
      EXPECT_EQ(0u, key.get_col());
      EXPECT_EQ(2u, key.get_depth());
      EXPECT_EQ("00", key.to_internal_string());
      key = quad_key::from_internal_string(type::bing, "01");
      EXPECT_EQ(3u, key.get_row());
      EXPECT_EQ(1u, key.get_col());
      EXPECT_EQ(2u, key.get_depth());
      EXPECT_EQ("01", key.to_internal_string());
      key = quad_key::from_internal_string(type::bing, "02");
      EXPECT_EQ(2u, key.get_row());
      EXPECT_EQ(0u, key.get_col());
      EXPECT_EQ(2u, key.get_depth());
      EXPECT_EQ("02", key.to_internal_string());
      key = quad_key::from_internal_string(type::bing, "03");
      EXPECT_EQ(2u, key.get_row());
      EXPECT_EQ(1u, key.get_col());
      EXPECT_EQ(2u, key.get_depth());
      EXPECT_EQ("03", key.to_internal_string());
      key = quad_key::from_internal_string(type::bing, "10");
      EXPECT_EQ(3u, key.get_row());
      EXPECT_EQ(2u, key.get_col());
      EXPECT_EQ(2u, key.get_depth());
      EXPECT_EQ("10", key.to_internal_string());
      key = quad_key::from_internal_string(type::bing, "11");
      EXPECT_EQ(3u, key.get_row());
      EXPECT_EQ(3u, key.get_col());
      EXPECT_EQ(2u, key.get_depth());
      EXPECT_EQ("11", key.to_internal_string());
      key = quad_key::from_internal_string(type::bing, "12");
      EXPECT_EQ(2u, key.get_row());
      EXPECT_EQ(2u, key.get_col());
      EXPECT_EQ(2u, key.get_depth());
      EXPECT_EQ("12", key.to_internal_string());
      key = quad_key::from_internal_string(type::bing, "13");
      EXPECT_EQ(2u, key.get_row());
      EXPECT_EQ(3u, key.get_col());
      EXPECT_EQ(2u, key.get_depth());
      EXPECT_EQ("13", key.to_internal_string());
      key = quad_key::from_internal_string(type::bing, "20");
      EXPECT_EQ(1u, key.get_row());
      EXPECT_EQ(0u, key.get_col());
      EXPECT_EQ(2u, key.get_depth());
      EXPECT_EQ("20", key.to_internal_string());
      key = quad_key::from_internal_string(type::bing, "21");
      EXPECT_EQ(1u, key.get_row());
      EXPECT_EQ(1u, key.get_col());
      EXPECT_EQ(2u, key.get_depth());
      EXPECT_EQ("21", key.to_internal_string());
      key = quad_key::from_internal_string(type::bing, "22");
      EXPECT_EQ(0u, key.get_row());
      EXPECT_EQ(0u, key.get_col());
      EXPECT_EQ(2u, key.get_depth());
      EXPECT_EQ("22", key.to_internal_string());
      key = quad_key::from_internal_string(type::bing, "23");
      EXPECT_EQ(0u, key.get_row());
      EXPECT_EQ(1u, key.get_col());
      EXPECT_EQ(2u, key.get_depth());
      EXPECT_EQ("23", key.to_internal_string());
      key = quad_key::from_internal_string(type::bing, "30");
      EXPECT_EQ(1u, key.get_row());
      EXPECT_EQ(2u, key.get_col());
      EXPECT_EQ(2u, key.get_depth());
      EXPECT_EQ("30", key.to_internal_string());
      key = quad_key::from_internal_string(type::bing, "31");
      EXPECT_EQ(1u, key.get_row());
      EXPECT_EQ(3u, key.get_col());
      EXPECT_EQ(2u, key.get_depth());
      EXPECT_EQ("31", key.to_internal_string());
      key = quad_key::from_internal_string(type::bing, "32");
      EXPECT_EQ(0u, key.get_row());
      EXPECT_EQ(2u, key.get_col());
      EXPECT_EQ(2u, key.get_depth());
      EXPECT_EQ("32", key.to_internal_string());
      key = quad_key::from_internal_string(type::bing, "33");
      EXPECT_EQ(0u, key.get_row());
      EXPECT_EQ(3u, key.get_col());
      EXPECT_EQ(2u, key.get_depth());
      EXPECT_EQ("33", key.to_internal_string());
    }
  }

  TEST(BINGSYSTEM, get_get_coordinate_bounds2d)
  {
    quad_key key;
    geo_coordinate_bounding_box2d bbox;

    { // Depth 0
      key = quad_key::from_internal_string(type::bing, "");
      key.get_geo_coordinate_bounds2d(bbox);
      EXPECT_FLOAT_EQ(-180.0f,
        static_cast<float>(bbox.lower_left().get_longitude().val()));
      EXPECT_FLOAT_EQ(-84.928322f,
        static_cast<float>(bbox.lower_left().get_latitude().val()));
      EXPECT_FLOAT_EQ(178.593750f,
        static_cast<float>(bbox.upper_right().get_longitude().val()));
      EXPECT_FLOAT_EQ(85.051132f,
        static_cast<float>(bbox.upper_right().get_latitude().val()));
    }
  }

  TEST(BINGSYSTEM, get_key_from_longitude_latitude_at_depth_to_bounds)
  {
    quad_key key;
    geo_coordinate_bounding_box2d bbox;
    double diff = 0.0;

    { // Depth 0
      key = quad_key::get_key_from_longitude_latitude_at_depth(
        type::bing, geo_coordinate2d(longitude(-180.0),
        latitude(-84.0)), 0u);
      EXPECT_EQ(quad_key(type::bing, 0, 0, 0), key);
      key.get_geo_coordinate_bounds2d(bbox);
      diff = std::fabs(bbox.lower_left().get_longitude() - longitude(-180.0));
      EXPECT_GT(2.0, diff);
      diff = std::fabs(bbox.lower_left().get_latitude() - latitude(-85.0));
      EXPECT_GT(2.0, diff);
      diff = std::fabs(bbox.upper_right().get_longitude() - longitude(+180.0));
      EXPECT_GT(2.0, diff);
      diff = std::fabs(bbox.upper_right().get_latitude() - latitude(+85.0));
      EXPECT_GT(2.0, diff);
    }

    // Inclusion here consists of upper left
    // ul X------X------X
    //    |      |      |
    //    |      |      |
    //    X------X------X
    //    |      |      |
    //    |      |      |
    //    X------X------X
    longitude left(-180.0);
    longitude midLeft(-0.36); // This is related to math used by Bing
    longitude midRight(0.0);
    longitude right(+180.0);
    latitude bottom(-90.0); // Outside of Mercator space. Puts them in.
    latitude midBottom(0.0);
    latitude midTop(0.36); // This is related to math used by Bing
    latitude top(+90.0); // Outside of Mercator space. Puts them in.

    { // Depth 1
      key = quad_key::get_key_from_longitude_latitude_at_depth( // Q0 ul
        type::bing, geo_coordinate2d(left, top), 1u);
      EXPECT_EQ(quad_key(type::bing, 1, 0, 1), key);
      key = quad_key::get_key_from_longitude_latitude_at_depth( // Q0 ll
        type::bing, geo_coordinate2d(left, midTop), 1u);
      EXPECT_EQ(quad_key(type::bing, 1, 0, 1), key);
      key = quad_key::get_key_from_longitude_latitude_at_depth( // Q0 lr
        type::bing, geo_coordinate2d(midLeft, midTop), 1u);
      EXPECT_EQ(quad_key(type::bing, 1, 0, 1), key);
      key = quad_key::get_key_from_longitude_latitude_at_depth( // Q0 ur
        type::bing, geo_coordinate2d(midLeft, top), 1u);
      EXPECT_EQ(quad_key(type::bing, 1, 0, 1), key);
      key.get_geo_coordinate_bounds2d(bbox);
      diff = std::fabs(bbox.lower_left().get_longitude() - left);
      EXPECT_GT(2.0, diff);
      diff = std::fabs(bbox.lower_left().get_latitude() - midTop);
      EXPECT_GT(2.0, diff);
      diff = std::fabs(bbox.upper_right().get_longitude() - midLeft);
      EXPECT_GT(2.0, diff);
      diff = std::fabs(bbox.upper_right().get_latitude() - latitude(+85.0));
      EXPECT_GT(2.0, diff);

      key = quad_key::get_key_from_longitude_latitude_at_depth( // Q1 ul
        type::bing, geo_coordinate2d(midRight, top), 1u);
      EXPECT_EQ(quad_key(type::bing, 1, 1, 1), key);
      key = quad_key::get_key_from_longitude_latitude_at_depth( // Q1 ll
        type::bing, geo_coordinate2d(midRight, midTop), 1u);
      EXPECT_EQ(quad_key(type::bing, 1, 1, 1), key);
      key = quad_key::get_key_from_longitude_latitude_at_depth( // Q1 lr
        type::bing, geo_coordinate2d(right, midTop), 1u);
      EXPECT_EQ(quad_key(type::bing, 1, 1, 1), key);
      key = quad_key::get_key_from_longitude_latitude_at_depth( // Q1 ur
        type::bing, geo_coordinate2d(right, top), 1u);
      EXPECT_EQ(quad_key(type::bing, 1, 1, 1), key);
      key.get_geo_coordinate_bounds2d(bbox);
      diff = std::fabs(bbox.lower_left().get_longitude() - midRight);
      EXPECT_GT(2.0, diff);
      diff = std::fabs(bbox.lower_left().get_latitude() - midTop);
      EXPECT_GT(2.0, diff);
      diff = std::fabs(bbox.upper_right().get_longitude() - right);
      EXPECT_GT(2.0, diff);
      diff = std::fabs(bbox.upper_right().get_latitude() - latitude(+85.0));
      EXPECT_GT(2.0, diff);

      key = quad_key::get_key_from_longitude_latitude_at_depth( // Q2 ul
        type::bing, geo_coordinate2d(left, midBottom), 1u);
      EXPECT_EQ(quad_key(type::bing, 0, 0, 1), key);
      key = quad_key::get_key_from_longitude_latitude_at_depth( // Q2 ll
        type::bing, geo_coordinate2d(left, bottom), 1u);
      EXPECT_EQ(quad_key(type::bing, 0, 0, 1), key);
      key = quad_key::get_key_from_longitude_latitude_at_depth( // Q2 lr
        type::bing, geo_coordinate2d(midLeft, bottom), 1u);
      EXPECT_EQ(quad_key(type::bing, 0, 0, 1), key);
      key = quad_key::get_key_from_longitude_latitude_at_depth( // Q2 ur
        type::bing, geo_coordinate2d(midLeft, midBottom), 1u);
      EXPECT_EQ(quad_key(type::bing, 0, 0, 1), key);
      key.get_geo_coordinate_bounds2d(bbox);
      diff = std::fabs(bbox.lower_left().get_longitude() - left);
      EXPECT_GT(2.0, diff);
      diff = std::fabs(bbox.lower_left().get_latitude() - latitude(-85.0));
      EXPECT_GT(2.0, diff);
      diff = std::fabs(bbox.upper_right().get_longitude() - midLeft);
      EXPECT_GT(2.0, diff);
      diff = std::fabs(bbox.upper_right().get_latitude() - midBottom);
      EXPECT_GT(2.0, diff);

      key = quad_key::get_key_from_longitude_latitude_at_depth( // Q3 ul
        type::bing, geo_coordinate2d(midRight, midBottom), 1u);
      EXPECT_EQ(quad_key(type::bing, 0, 1, 1), key);
      key = quad_key::get_key_from_longitude_latitude_at_depth( // Q3 ll
        type::bing, geo_coordinate2d(midRight, bottom), 1u);
      EXPECT_EQ(quad_key(type::bing, 0, 1, 1), key);
      key = quad_key::get_key_from_longitude_latitude_at_depth( // Q3 lr
        type::bing, geo_coordinate2d(right, bottom), 1u);
      EXPECT_EQ(quad_key(type::bing, 0, 1, 1), key);
      key = quad_key::get_key_from_longitude_latitude_at_depth( // Q3 ur
        type::bing, geo_coordinate2d(right, midBottom), 1u);
      EXPECT_EQ(quad_key(type::bing, 0, 1, 1), key);
      key.get_geo_coordinate_bounds2d(bbox);
      diff = std::fabs(bbox.lower_left().get_longitude() - midRight);
      EXPECT_GT(2.0, diff);
      diff = std::fabs(bbox.lower_left().get_latitude() - latitude(-85.0));
      EXPECT_GT(2.0, diff);
      diff = std::fabs(bbox.upper_right().get_longitude() - right);
      EXPECT_GT(2.0, diff);
      diff = std::fabs(bbox.upper_right().get_latitude() - midBottom);
      EXPECT_GT(2.0, diff);
    }
  }

  TEST(BINGSYSTEM, get_keys_from_longitude_latitude_bounding_box)
  {
    {
      std::vector<quad_key> out_keys;
      out_keys = quad_key::get_keys_from_longitude_latitude_bounding_box(
        type::bing,
        geo_coordinate_bounding_box2d(
        geo_coordinate2d(longitude(-180.0), latitude(+90.0)),
        geo_coordinate2d(longitude(+180.0), latitude(-90.0))), 0);
      EXPECT_EQ(1u, out_keys.size());
      EXPECT_NE(out_keys.end(), std::find(out_keys.begin(), out_keys.end(),
        quad_key(type::bing, 0, 0, 0)));
    }

    {
      std::vector<quad_key> out_keys;
      out_keys = quad_key::get_keys_from_longitude_latitude_bounding_box(
        type::bing,
        geo_coordinate_bounding_box2d(
        geo_coordinate2d(longitude(-180.0), latitude(+90.0)),
        geo_coordinate2d(longitude(+180.0), latitude(-90.0))), 1);
      EXPECT_EQ(4u, out_keys.size());
      EXPECT_NE(out_keys.end(), std::find(out_keys.begin(), out_keys.end(),
        quad_key(type::bing, 0, 0, 1)));
      EXPECT_NE(out_keys.end(), std::find(out_keys.begin(), out_keys.end(),
        quad_key(type::bing, 0, 1, 1)));
      EXPECT_NE(out_keys.end(), std::find(out_keys.begin(), out_keys.end(),
        quad_key(type::bing, 1, 0, 1)));
      EXPECT_NE(out_keys.end(), std::find(out_keys.begin(), out_keys.end(),
        quad_key(type::bing, 1, 1, 1)));
    }

    {
      std::vector<quad_key> out_keys;
      out_keys = quad_key::get_keys_from_longitude_latitude_bounding_box(
        type::bing,
        geo_coordinate_bounding_box2d(
        geo_coordinate2d(longitude(-180.0), latitude(+0.35)),
        geo_coordinate2d(longitude(-0.36), latitude(+90.0))), 1);
      EXPECT_EQ(2u, out_keys.size());
      EXPECT_NE(out_keys.end(), std::find(out_keys.begin(), out_keys.end(),
        quad_key(type::bing, 0, 0, 1)));
      EXPECT_NE(out_keys.end(), std::find(out_keys.begin(), out_keys.end(),
        quad_key(type::bing, 1, 0, 1)));
    }

    {
      std::vector<quad_key> out_keys;
      out_keys = quad_key::get_keys_from_longitude_latitude_bounding_box(
        type::bing,
        geo_coordinate_bounding_box2d(
          geo_coordinate2d(longitude(-0.36), latitude(+0.36)),
          geo_coordinate2d(longitude(+0.36), latitude(+90.0))), 1);
      EXPECT_EQ(2u, out_keys.size());
      EXPECT_NE(out_keys.end(), std::find(out_keys.begin(), out_keys.end(),
        quad_key(type::bing, 1, 0, 1)));
      EXPECT_NE(out_keys.end(), std::find(out_keys.begin(), out_keys.end(),
        quad_key(type::bing, 1, 1, 1)));
    }

    {
      std::vector<quad_key> out_keys;
      out_keys = quad_key::get_keys_from_longitude_latitude_bounding_box(
        type::bing,
        geo_coordinate_bounding_box2d(
          geo_coordinate2d(longitude(-0.36), latitude(+0.35)),
          geo_coordinate2d(longitude(+0.36), latitude(+90.0))), 1);
      EXPECT_EQ(4u, out_keys.size());
      EXPECT_NE(out_keys.end(), std::find(out_keys.begin(), out_keys.end(),
        quad_key(type::bing, 0, 0, 1)));
      EXPECT_NE(out_keys.end(), std::find(out_keys.begin(), out_keys.end(),
        quad_key(type::bing, 0, 1, 1)));
      EXPECT_NE(out_keys.end(), std::find(out_keys.begin(), out_keys.end(),
        quad_key(type::bing, 1, 0, 1)));
      EXPECT_NE(out_keys.end(), std::find(out_keys.begin(), out_keys.end(),
        quad_key(type::bing, 1, 1, 1)));
    }
  }

  TEST(BINGSYSTEM, SelectedCities)
  {
    quad_key key;
    const type t = type::bing;

    { // Chicago 41.822, -87.635
      const std::uint8_t depth = 16;
      geo_coordinate2d coords(longitude(-87.635), latitude(41.822));

      key = quad_key::get_key_from_longitude_latitude_at_depth(t,
        coords, depth);
      std::string key_str = key.to_internal_string();
      EXPECT_EQ("0302222310321132", key_str);

      geo_coordinate_bounding_box2d bbox;
      key.get_geo_coordinate_bounds2d(bbox);

      // Note that Bing will return a bounding box of all sides inclusive
      std::vector<quad_key> keys;
      keys = quad_key::get_keys_from_longitude_latitude_bounding_box(t,
        bbox, depth);
      EXPECT_EQ(4u, keys.size());
      EXPECT_NE(keys.end(), std::find(keys.begin(), keys.end(), key));
    }

    { // Rio -43.1964,-22.9083
      const std::uint8_t depth = 17;
      geo_coordinate2d coords(longitude(-43.1964), latitude(-22.9083));

      key = quad_key::get_key_from_longitude_latitude_at_depth(t,
        coords, depth);
      std::string key_str = key.to_internal_string();
      EXPECT_EQ("21120001212232200", key_str);

      geo_coordinate_bounding_box2d bbox;
      key.get_geo_coordinate_bounds2d(bbox);

      // Note that Bing will return a bounding box of all sides inclusive
      std::vector<quad_key> keys;
      keys = quad_key::get_keys_from_longitude_latitude_bounding_box(t,
        bbox, depth);
      EXPECT_EQ(4u, keys.size());
      EXPECT_NE(keys.end(), std::find(keys.begin(), keys.end(), key));
    }

    { // Helsinki 60.1708 N, 24.9375 E
      const std::uint8_t depth = 17;
      geo_coordinate2d coords(longitude(24.9375), latitude(60.1708));

      key = quad_key::get_key_from_longitude_latitude_at_depth(t, coords,
        depth);
      std::string key_str = key.to_internal_string();
      EXPECT_EQ("12012021101330131", key_str);

      geo_coordinate_bounding_box2d bbox;
      key.get_geo_coordinate_bounds2d(bbox);

      // Note that Bing will return a bounding box of all sides inclusive
      std::vector<quad_key> keys;
      keys = quad_key::get_keys_from_longitude_latitude_bounding_box(t,
        bbox, depth);
      EXPECT_EQ(4u, keys.size());
      EXPECT_NE(keys.end(), std::find(keys.begin(), keys.end(), key));
    }

    { // Cape Town South Africa 33.9253 S, 18.4239 E
      const std::uint8_t depth = 17;
      geo_coordinate2d coords(longitude(18.4239), latitude(-33.9253));

      key = quad_key::get_key_from_longitude_latitude_at_depth(t, coords,
        depth);
      std::string key_str = key.to_internal_string();
      EXPECT_EQ("30023103202132011", key_str);

      geo_coordinate_bounding_box2d bbox;
      key.get_geo_coordinate_bounds2d(bbox);

      // Note that Bing will return a bounding box of all sides inclusive
      std::vector<quad_key> keys;
      keys = quad_key::get_keys_from_longitude_latitude_bounding_box(t,
        bbox, depth);
      EXPECT_EQ(4u, keys.size());
      EXPECT_NE(keys.end(), std::find(keys.begin(), keys.end(), key));
    }

    { // Quito 0.2500 S, 78.5833 W
      const std::uint8_t depth = 17;
      geo_coordinate2d coords(longitude(-78.5836), latitude(-0.25));

      key = quad_key::get_key_from_longitude_latitude_at_depth(t, coords,
        depth);
      std::string key_str = key.to_internal_string();
      EXPECT_EQ("21001000002133122", key_str);

      geo_coordinate_bounding_box2d bbox;
      key.get_geo_coordinate_bounds2d(bbox);

      // Note that Bing will return a bounding box of all sides inclusive
      std::vector<quad_key> keys;
      keys = quad_key::get_keys_from_longitude_latitude_bounding_box(t,
        bbox, depth);
      EXPECT_EQ(4u, keys.size());
      EXPECT_NE(keys.end(), std::find(keys.begin(), keys.end(), key));
    }
  }
}

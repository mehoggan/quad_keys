#include <gtest/gtest.h>

#include <cmath>

#include "quad_keys/geo_coordinate2d.h"
#include "quad_keys/quad_key.h"

namespace quad_keys {
class TestBingSystem : public ::testing::Test {
 protected:
  virtual void SetUp() {}
  virtual void TearDown() {}
};

TEST(BINGSYSTEM, is_valid) {}

TEST(BINGSYSTEM, is_root_key) {}

TEST(BINGSYSTEM, get_parent) {
  {
    QuadKey bing_key0(Type::Bing, 0, 0, 1);
    QuadKey bing_key1(Type::Bing, 1, 0, 1);
    QuadKey bing_key2(Type::Bing, 1, 1, 1);
    QuadKey bing_key3(Type::Bing, 0, 1, 1);

    QuadKey bing_key_p(Type::Bing, 0, 0, 0);

    ASSERT_TRUE(bing_key_p.get_type() == Type::Bing);
    ASSERT_TRUE(bing_key0.get_type() == Type::Bing);
    ASSERT_TRUE(bing_key1.get_type() == Type::Bing);
    ASSERT_TRUE(bing_key2.get_type() == Type::Bing);
    ASSERT_TRUE(bing_key3.get_type() == Type::Bing);

    EXPECT_EQ(bing_key_p, bing_key0.get_parent());
    EXPECT_EQ(bing_key_p, bing_key1.get_parent());
    EXPECT_EQ(bing_key_p, bing_key2.get_parent());
    EXPECT_EQ(bing_key_p, bing_key3.get_parent());
  }

  {
    QuadKey bing_key0(Type::Bing, 5, 6, 3);
    QuadKey bing_key1(Type::Bing, 4, 6, 3);
    QuadKey bing_key2(Type::Bing, 4, 7, 3);
    QuadKey bing_key3(Type::Bing, 5, 7, 3);

    QuadKey bing_key_p(Type::Bing, 2, 3, 2);

    ASSERT_TRUE(bing_key_p.get_type() == Type::Bing);
    ASSERT_TRUE(bing_key0.get_type() == Type::Bing);
    ASSERT_TRUE(bing_key1.get_type() == Type::Bing);
    ASSERT_TRUE(bing_key2.get_type() == Type::Bing);
    ASSERT_TRUE(bing_key3.get_type() == Type::Bing);

    EXPECT_EQ(bing_key_p, bing_key0.get_parent());
    EXPECT_EQ(bing_key_p, bing_key1.get_parent());
    EXPECT_EQ(bing_key_p, bing_key2.get_parent());
    EXPECT_EQ(bing_key_p, bing_key3.get_parent());
  }
}

TEST(BINGSYSTEM, is_my_ancestor) {
  {
    QuadKey key(Type::Bing, 5, 7, 3);
    EXPECT_FALSE(key.is_my_ancestor(QuadKey()));
    EXPECT_FALSE(key.is_my_ancestor(QuadKey(Type::OsGeo, 2, 3, 2)));
    EXPECT_FALSE(key.is_my_ancestor(QuadKey(Type::OsGeo, 0, 0, 0)));
    EXPECT_TRUE(key.is_my_ancestor(QuadKey(Type::Bing, 2, 3, 2)));
    EXPECT_TRUE(key.is_my_ancestor(QuadKey(Type::Bing, 0, 0, 0)));
    EXPECT_FALSE(key.is_my_ancestor(QuadKey(Type::Bing, 5, 7, 3)));

    QuadKey none;
    EXPECT_FALSE(none.is_my_ancestor(QuadKey()));
  }

  {
    QuadKey key(Type::Bing, 5, 7, 3);
    EXPECT_FALSE(key.is_my_ancestor(QuadKey()));
    EXPECT_FALSE(key.is_my_ancestor(QuadKey(Type::OsGeo, 2, 3, 2)));
    EXPECT_FALSE(key.is_my_ancestor(QuadKey(Type::OsGeo, 0, 0, 0)));
    EXPECT_TRUE(key.is_my_ancestor(QuadKey(Type::Bing, 2, 3, 2)));
    EXPECT_TRUE(key.is_my_ancestor(QuadKey(Type::Bing, 0, 0, 0)));
    EXPECT_FALSE(key.is_my_ancestor(QuadKey(Type::Bing, 5, 7, 3)));

    QuadKey none;
    EXPECT_FALSE(none.is_my_ancestor(QuadKey()));
  }
}

TEST(BINGSYSTEM, get_ancestor) {
  {
    QuadKey key(Type::Bing, 0, 7, 3);
    QuadKey ancestor(Type::Bing, 0, 1, 1);
    EXPECT_EQ(ancestor, key.get_ancestor(2));
  }

  {
    QuadKey key(Type::Bing, 4, 31, 5);
    QuadKey ancestor(Type::Bing, 0, 1, 1);
    EXPECT_EQ(ancestor, key.get_ancestor(4));
  }

  {
    QuadKey key(Type::Bing, 4, 31, 5);
    QuadKey ancestor(Type::Bing, 0, 3, 2);
    EXPECT_EQ(ancestor, key.get_ancestor(3));
  }

  {
    QuadKey key(Type::Bing, 4, 31, 5);
    QuadKey ancestor(Type::Bing, 1, 7, 3);
    EXPECT_EQ(ancestor, key.get_ancestor(2));
  }
}

TEST(BINGSYSTEM, get_child) {
  EXPECT_EQ(QuadKey(), QuadKey().get_child(QuadKey::quadrant::north_west));
  uint8_t max_depth_bing = QuadKey::max_depth(Type::Bing);
  EXPECT_EQ(QuadKey(), QuadKey(Type::Bing, 0, 0, max_depth_bing)
                           .get_child(QuadKey::quadrant::north_east));

  {
    QuadKey key(Type::Bing, 0, 0, 3);
    EXPECT_EQ(QuadKey(Type::Bing, 1, 0, 4),
              key.get_child(QuadKey::quadrant::north_west));
    EXPECT_EQ(QuadKey(Type::Bing, 1, 1, 4),
              key.get_child(QuadKey::quadrant::north_east));
    EXPECT_EQ(QuadKey(Type::Bing, 0, 1, 4),
              key.get_child(QuadKey::quadrant::south_east));
    EXPECT_EQ(QuadKey(Type::Bing, 0, 0, 4),
              key.get_child(QuadKey::quadrant::south_west));
  }

  {
    QuadKey key(Type::Bing, 2, 3, 3);
    EXPECT_EQ(QuadKey(Type::Bing, 5, 6, 4),
              key.get_child(QuadKey::quadrant::north_west));
    EXPECT_EQ(QuadKey(Type::Bing, 5, 7, 4),
              key.get_child(QuadKey::quadrant::north_east));
    EXPECT_EQ(QuadKey(Type::Bing, 4, 7, 4),
              key.get_child(QuadKey::quadrant::south_east));
    EXPECT_EQ(QuadKey(Type::Bing, 4, 6, 4),
              key.get_child(QuadKey::quadrant::south_west));
  }
}

TEST(BINGSYSTEM, get_children) {
  std::vector<QuadKey> test_keys;
  uint8_t max_depthBing = QuadKey::max_depth(Type::Bing);
  test_keys = QuadKey(Type::Bing, 0, 0, max_depthBing).get_children();
  EXPECT_TRUE(test_keys.empty());

  test_keys.clear();

  test_keys = QuadKey(Type::Bing, 0, 0, 1).get_children();
  EXPECT_EQ(4u, test_keys.size());
  EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                      QuadKey(Type::Bing, 0, 0, 2)),
            test_keys.end());
  EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                      QuadKey(Type::Bing, 0, 1, 2)),
            test_keys.end());
  EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                      QuadKey(Type::Bing, 1, 0, 2)),
            test_keys.end());
  EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                      QuadKey(Type::Bing, 1, 1, 2)),
            test_keys.end());

  test_keys = QuadKey(Type::Bing, 0, 1, 1).get_children();
  EXPECT_EQ(4u, test_keys.size());
  EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                      QuadKey(Type::Bing, 0, 2, 2)),
            test_keys.end());
  EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                      QuadKey(Type::Bing, 0, 3, 2)),
            test_keys.end());
  EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                      QuadKey(Type::Bing, 1, 2, 2)),
            test_keys.end());
  EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                      QuadKey(Type::Bing, 1, 3, 2)),
            test_keys.end());

  test_keys = QuadKey(Type::Bing, 1, 0, 1).get_children();
  EXPECT_EQ(4u, test_keys.size());
  EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                      QuadKey(Type::Bing, 2, 0, 2)),
            test_keys.end());
  EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                      QuadKey(Type::Bing, 2, 1, 2)),
            test_keys.end());
  EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                      QuadKey(Type::Bing, 3, 0, 2)),
            test_keys.end());
  EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                      QuadKey(Type::Bing, 3, 1, 2)),
            test_keys.end());

  test_keys = QuadKey(Type::Bing, 1, 1, 1).get_children();
  EXPECT_EQ(4u, test_keys.size());
  EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                      QuadKey(Type::Bing, 2, 2, 2)),
            test_keys.end());
  EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                      QuadKey(Type::Bing, 2, 3, 2)),
            test_keys.end());
  EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                      QuadKey(Type::Bing, 3, 2, 2)),
            test_keys.end());
  EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                      QuadKey(Type::Bing, 3, 3, 2)),
            test_keys.end());

  test_keys.clear();
}

TEST(BINGSYSTEM, get_descendants) {
  uint8_t bingMaxDepth = QuadKey::max_depth(Type::Bing);
  QuadKey test_key(Type::Bing, 0, 0, bingMaxDepth - 3);
  std::vector<QuadKey> test_keys;
  test_keys = test_key.get_descendants(4);
  EXPECT_EQ(0u, test_keys.size());

  QuadKey none;
  test_keys = none.get_descendants(1);
  EXPECT_EQ(0u, test_keys.size());

  {
    QuadKey key(Type::Bing, 0, 0, 0);
    test_keys = key.get_descendants(0);
    EXPECT_EQ(0u, test_keys.size());
  }

  {
    QuadKey key(Type::Bing, 0, 0, 0);

    test_keys = key.get_descendants(1);
    EXPECT_EQ(4u, test_keys.size());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                        QuadKey(Type::Bing, 0, 0, 1)),
              test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                        QuadKey(Type::Bing, 0, 1, 1)),
              test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                        QuadKey(Type::Bing, 1, 0, 1)),
              test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                        QuadKey(Type::Bing, 1, 1, 1)),
              test_keys.end());

    test_keys = key.get_descendants(2);
    EXPECT_EQ(16u, test_keys.size());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                        QuadKey(Type::Bing, 0, 0, 2)),
              test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                        QuadKey(Type::Bing, 0, 1, 2)),
              test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                        QuadKey(Type::Bing, 0, 2, 2)),
              test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                        QuadKey(Type::Bing, 0, 3, 2)),
              test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                        QuadKey(Type::Bing, 1, 0, 2)),
              test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                        QuadKey(Type::Bing, 1, 1, 2)),
              test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                        QuadKey(Type::Bing, 1, 2, 2)),
              test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                        QuadKey(Type::Bing, 1, 3, 2)),
              test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                        QuadKey(Type::Bing, 2, 0, 2)),
              test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                        QuadKey(Type::Bing, 2, 1, 2)),
              test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                        QuadKey(Type::Bing, 2, 2, 2)),
              test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                        QuadKey(Type::Bing, 2, 3, 2)),
              test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                        QuadKey(Type::Bing, 3, 0, 2)),
              test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                        QuadKey(Type::Bing, 3, 1, 2)),
              test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                        QuadKey(Type::Bing, 3, 2, 2)),
              test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                        QuadKey(Type::Bing, 3, 3, 2)),
              test_keys.end());

    test_keys = key.get_descendants(3);
    EXPECT_EQ(64u, test_keys.size());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                        QuadKey(Type::Bing, 0, 0, 3)),
              test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                        QuadKey(Type::Bing, 0, 1, 3)),
              test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                        QuadKey(Type::Bing, 0, 2, 3)),
              test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                        QuadKey(Type::Bing, 0, 3, 3)),
              test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                        QuadKey(Type::Bing, 0, 4, 3)),
              test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                        QuadKey(Type::Bing, 0, 5, 3)),
              test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                        QuadKey(Type::Bing, 0, 6, 3)),
              test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                        QuadKey(Type::Bing, 0, 7, 3)),
              test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                        QuadKey(Type::Bing, 1, 0, 3)),
              test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                        QuadKey(Type::Bing, 1, 1, 3)),
              test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                        QuadKey(Type::Bing, 1, 2, 3)),
              test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                        QuadKey(Type::Bing, 1, 3, 3)),
              test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                        QuadKey(Type::Bing, 1, 4, 3)),
              test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                        QuadKey(Type::Bing, 1, 5, 3)),
              test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                        QuadKey(Type::Bing, 1, 6, 3)),
              test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                        QuadKey(Type::Bing, 1, 7, 3)),
              test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                        QuadKey(Type::Bing, 2, 0, 3)),
              test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                        QuadKey(Type::Bing, 2, 1, 3)),
              test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                        QuadKey(Type::Bing, 2, 2, 3)),
              test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                        QuadKey(Type::Bing, 2, 3, 3)),
              test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                        QuadKey(Type::Bing, 2, 4, 3)),
              test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                        QuadKey(Type::Bing, 2, 5, 3)),
              test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                        QuadKey(Type::Bing, 2, 6, 3)),
              test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                        QuadKey(Type::Bing, 2, 7, 3)),
              test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                        QuadKey(Type::Bing, 3, 0, 3)),
              test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                        QuadKey(Type::Bing, 3, 1, 3)),
              test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                        QuadKey(Type::Bing, 3, 2, 3)),
              test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                        QuadKey(Type::Bing, 3, 3, 3)),
              test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                        QuadKey(Type::Bing, 3, 4, 3)),
              test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                        QuadKey(Type::Bing, 3, 5, 3)),
              test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                        QuadKey(Type::Bing, 3, 6, 3)),
              test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                        QuadKey(Type::Bing, 3, 7, 3)),
              test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                        QuadKey(Type::Bing, 4, 0, 3)),
              test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                        QuadKey(Type::Bing, 4, 1, 3)),
              test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                        QuadKey(Type::Bing, 4, 2, 3)),
              test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                        QuadKey(Type::Bing, 4, 3, 3)),
              test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                        QuadKey(Type::Bing, 4, 4, 3)),
              test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                        QuadKey(Type::Bing, 4, 5, 3)),
              test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                        QuadKey(Type::Bing, 4, 6, 3)),
              test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                        QuadKey(Type::Bing, 4, 7, 3)),
              test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                        QuadKey(Type::Bing, 5, 0, 3)),
              test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                        QuadKey(Type::Bing, 5, 1, 3)),
              test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                        QuadKey(Type::Bing, 5, 2, 3)),
              test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                        QuadKey(Type::Bing, 5, 3, 3)),
              test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                        QuadKey(Type::Bing, 5, 4, 3)),
              test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                        QuadKey(Type::Bing, 5, 5, 3)),
              test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                        QuadKey(Type::Bing, 5, 6, 3)),
              test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                        QuadKey(Type::Bing, 5, 7, 3)),
              test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                        QuadKey(Type::Bing, 6, 0, 3)),
              test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                        QuadKey(Type::Bing, 6, 1, 3)),
              test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                        QuadKey(Type::Bing, 6, 2, 3)),
              test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                        QuadKey(Type::Bing, 6, 3, 3)),
              test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                        QuadKey(Type::Bing, 6, 4, 3)),
              test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                        QuadKey(Type::Bing, 6, 5, 3)),
              test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                        QuadKey(Type::Bing, 6, 6, 3)),
              test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                        QuadKey(Type::Bing, 6, 7, 3)),
              test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                        QuadKey(Type::Bing, 7, 0, 3)),
              test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                        QuadKey(Type::Bing, 7, 1, 3)),
              test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                        QuadKey(Type::Bing, 7, 2, 3)),
              test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                        QuadKey(Type::Bing, 7, 3, 3)),
              test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                        QuadKey(Type::Bing, 7, 4, 3)),
              test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                        QuadKey(Type::Bing, 7, 5, 3)),
              test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                        QuadKey(Type::Bing, 7, 6, 3)),
              test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                        QuadKey(Type::Bing, 7, 7, 3)),
              test_keys.end());
  }
}

TEST(BINGSYSTEM, get_siblings) {
  std::vector<QuadKey> test_keys;

  test_keys = QuadKey().get_siblings();
  EXPECT_TRUE(test_keys.empty());

  test_keys = QuadKey(Type::Bing, 0, 0, 0).get_siblings();
  EXPECT_TRUE(test_keys.empty());

  test_keys = QuadKey(Type::Bing, 0, 0, 1).get_siblings();
  EXPECT_EQ(3u, test_keys.size());
  EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                      QuadKey(Type::Bing, 0, 1, 1)),
            test_keys.end());
  EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                      QuadKey(Type::Bing, 1, 1, 1)),
            test_keys.end());
  EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                      QuadKey(Type::Bing, 1, 0, 1)),
            test_keys.end());
}

TEST(BINGSYSTEM, get_neighbors) {
  std::vector<QuadKey> test_keys;

  test_keys = QuadKey().get_neighbors();
  EXPECT_TRUE(test_keys.empty());

  test_keys = QuadKey(Type::Bing, 0, 0, 0).get_neighbors();
  EXPECT_TRUE(test_keys.empty());

  test_keys.clear();

  test_keys = QuadKey(Type::Bing, 0, 0, 2).get_neighbors();
  EXPECT_EQ(5u, test_keys.size());
  EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                      QuadKey(Type::Bing, 0, 1, 2)),
            test_keys.end());
  EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                      QuadKey(Type::Bing, 1, 1, 2)),
            test_keys.end());
  EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                      QuadKey(Type::Bing, 1, 0, 2)),
            test_keys.end());
  EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                      QuadKey(Type::Bing, 0, 3, 2)),
            test_keys.end());
  EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                      QuadKey(Type::Bing, 1, 3, 2)),
            test_keys.end());

  test_keys.clear();

  test_keys = QuadKey(Type::Bing, 0, 1, 2).get_neighbors();
  EXPECT_EQ(5u, test_keys.size());
  EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                      QuadKey(Type::Bing, 0, 0, 2)),
            test_keys.end());
  EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                      QuadKey(Type::Bing, 1, 0, 2)),
            test_keys.end());
  EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                      QuadKey(Type::Bing, 1, 1, 2)),
            test_keys.end());
  EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                      QuadKey(Type::Bing, 1, 2, 2)),
            test_keys.end());
  EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                      QuadKey(Type::Bing, 0, 2, 2)),
            test_keys.end());

  test_keys.clear();

  test_keys = QuadKey(Type::Bing, 0, 2, 2).get_neighbors();
  EXPECT_EQ(5u, test_keys.size());
  EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                      QuadKey(Type::Bing, 0, 1, 2)),
            test_keys.end());
  EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                      QuadKey(Type::Bing, 1, 1, 2)),
            test_keys.end());
  EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                      QuadKey(Type::Bing, 1, 2, 2)),
            test_keys.end());
  EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                      QuadKey(Type::Bing, 1, 3, 2)),
            test_keys.end());
  EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                      QuadKey(Type::Bing, 0, 3, 2)),
            test_keys.end());

  test_keys.clear();

  test_keys = QuadKey(Type::Bing, 0, 3, 2).get_neighbors();
  EXPECT_EQ(5u, test_keys.size());
  EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                      QuadKey(Type::Bing, 0, 2, 2)),
            test_keys.end());
  EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                      QuadKey(Type::Bing, 1, 2, 2)),
            test_keys.end());
  EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                      QuadKey(Type::Bing, 1, 3, 2)),
            test_keys.end());
  EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                      QuadKey(Type::Bing, 1, 0, 2)),
            test_keys.end());
  EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                      QuadKey(Type::Bing, 0, 0, 2)),
            test_keys.end());

  test_keys.clear();

  test_keys = QuadKey(Type::Bing, 1, 0, 2).get_neighbors();
  EXPECT_EQ(8u, test_keys.size());
  EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                      QuadKey(Type::Bing, 0, 0, 2)),
            test_keys.end());
  EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                      QuadKey(Type::Bing, 0, 1, 2)),
            test_keys.end());
  EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                      QuadKey(Type::Bing, 1, 1, 2)),
            test_keys.end());
  EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                      QuadKey(Type::Bing, 2, 1, 2)),
            test_keys.end());
  EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                      QuadKey(Type::Bing, 2, 0, 2)),
            test_keys.end());
  EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                      QuadKey(Type::Bing, 2, 3, 2)),
            test_keys.end());
  EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                      QuadKey(Type::Bing, 1, 3, 2)),
            test_keys.end());
  EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                      QuadKey(Type::Bing, 0, 3, 2)),
            test_keys.end());

  test_keys.clear();

  test_keys = QuadKey(Type::Bing, 1, 1, 2).get_neighbors();
  EXPECT_EQ(8u, test_keys.size());
  EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                      QuadKey(Type::Bing, 1, 0, 2)),
            test_keys.end());
  EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                      QuadKey(Type::Bing, 0, 0, 2)),
            test_keys.end());
  EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                      QuadKey(Type::Bing, 0, 1, 2)),
            test_keys.end());
  EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                      QuadKey(Type::Bing, 2, 2, 2)),
            test_keys.end());
  EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                      QuadKey(Type::Bing, 2, 1, 2)),
            test_keys.end());
  EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                      QuadKey(Type::Bing, 2, 0, 2)),
            test_keys.end());
  EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                      QuadKey(Type::Bing, 0, 2, 2)),
            test_keys.end());
  EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                      QuadKey(Type::Bing, 1, 2, 2)),
            test_keys.end());

  test_keys.clear();

  test_keys = QuadKey(Type::Bing, 1, 2, 2).get_neighbors();
  EXPECT_EQ(8u, test_keys.size());
  EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                      QuadKey(Type::Bing, 1, 1, 2)),
            test_keys.end());
  EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                      QuadKey(Type::Bing, 0, 1, 2)),
            test_keys.end());
  EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                      QuadKey(Type::Bing, 0, 2, 2)),
            test_keys.end());
  EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                      QuadKey(Type::Bing, 2, 3, 2)),
            test_keys.end());
  EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                      QuadKey(Type::Bing, 2, 2, 2)),
            test_keys.end());
  EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                      QuadKey(Type::Bing, 2, 1, 2)),
            test_keys.end());
  EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                      QuadKey(Type::Bing, 0, 3, 2)),
            test_keys.end());
  EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                      QuadKey(Type::Bing, 1, 3, 2)),
            test_keys.end());

  test_keys.clear();

  test_keys = QuadKey(Type::Bing, 1, 3, 2).get_neighbors();
  EXPECT_EQ(8u, test_keys.size());
  EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                      QuadKey(Type::Bing, 1, 2, 2)),
            test_keys.end());
  EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                      QuadKey(Type::Bing, 0, 2, 2)),
            test_keys.end());
  EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                      QuadKey(Type::Bing, 0, 3, 2)),
            test_keys.end());
  EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                      QuadKey(Type::Bing, 2, 0, 2)),
            test_keys.end());
  EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                      QuadKey(Type::Bing, 2, 3, 2)),
            test_keys.end());
  EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                      QuadKey(Type::Bing, 2, 2, 2)),
            test_keys.end());
  EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                      QuadKey(Type::Bing, 0, 0, 2)),
            test_keys.end());
  EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                      QuadKey(Type::Bing, 1, 0, 2)),
            test_keys.end());

  test_keys.clear();

  test_keys = QuadKey(Type::Bing, 4, 7, 3).get_neighbors();
  EXPECT_EQ(8u, test_keys.size());
  EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                      QuadKey(Type::Bing, 3, 7, 3)),
            test_keys.end());
  EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                      QuadKey(Type::Bing, 3, 6, 3)),
            test_keys.end());
  EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                      QuadKey(Type::Bing, 4, 6, 3)),
            test_keys.end());
  EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                      QuadKey(Type::Bing, 5, 6, 3)),
            test_keys.end());
  EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                      QuadKey(Type::Bing, 5, 7, 3)),
            test_keys.end());
  EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                      QuadKey(Type::Bing, 5, 0, 3)),
            test_keys.end());
  EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                      QuadKey(Type::Bing, 4, 0, 3)),
            test_keys.end());
  EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                      QuadKey(Type::Bing, 3, 0, 3)),
            test_keys.end());

  test_keys.clear();

  test_keys = QuadKey(Type::Bing, 4, 0, 3).get_neighbors();
  EXPECT_EQ(8u, test_keys.size());
  EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                      QuadKey(Type::Bing, 3, 0, 3)),
            test_keys.end());
  EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                      QuadKey(Type::Bing, 3, 1, 3)),
            test_keys.end());
  EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                      QuadKey(Type::Bing, 4, 1, 3)),
            test_keys.end());
  EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                      QuadKey(Type::Bing, 5, 1, 3)),
            test_keys.end());
  EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                      QuadKey(Type::Bing, 5, 0, 3)),
            test_keys.end());
  EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                      QuadKey(Type::Bing, 5, 7, 3)),
            test_keys.end());
  EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                      QuadKey(Type::Bing, 4, 7, 3)),
            test_keys.end());
  EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
                      QuadKey(Type::Bing, 3, 7, 3)),
            test_keys.end());

  test_keys.clear();
}

TEST(BINGSYSTEM, from_string_to_string) {
  {
    QuadKey root = QuadKey::from_internal_string(Type::Bing, "");
    EXPECT_EQ(0u, root.get_row());
    EXPECT_EQ(0u, root.get_col());
    EXPECT_EQ(0u, root.get_depth());
  }

  {
    QuadKey key;
    key = QuadKey::from_internal_string(Type::Bing, "0");
    EXPECT_EQ(1u, key.get_row());
    EXPECT_EQ(0u, key.get_col());
    EXPECT_EQ(1u, key.get_depth());
    EXPECT_EQ("0", key.to_internal_string());
    key = QuadKey::from_internal_string(Type::Bing, "1");
    EXPECT_EQ(1u, key.get_row());
    EXPECT_EQ(1u, key.get_col());
    EXPECT_EQ(1u, key.get_depth());
    EXPECT_EQ("1", key.to_internal_string());
    key = QuadKey::from_internal_string(Type::Bing, "2");
    EXPECT_EQ(0u, key.get_row());
    EXPECT_EQ(0u, key.get_col());
    EXPECT_EQ(1u, key.get_depth());
    EXPECT_EQ("2", key.to_internal_string());
    key = QuadKey::from_internal_string(Type::Bing, "3");
    EXPECT_EQ(0u, key.get_row());
    EXPECT_EQ(1u, key.get_col());
    EXPECT_EQ(1u, key.get_depth());
    EXPECT_EQ("3", key.to_internal_string());
  }

  {
    QuadKey key;
    key = QuadKey::from_internal_string(Type::Bing, "00");
    EXPECT_EQ(3u, key.get_row());
    EXPECT_EQ(0u, key.get_col());
    EXPECT_EQ(2u, key.get_depth());
    EXPECT_EQ("00", key.to_internal_string());
    key = QuadKey::from_internal_string(Type::Bing, "01");
    EXPECT_EQ(3u, key.get_row());
    EXPECT_EQ(1u, key.get_col());
    EXPECT_EQ(2u, key.get_depth());
    EXPECT_EQ("01", key.to_internal_string());
    key = QuadKey::from_internal_string(Type::Bing, "02");
    EXPECT_EQ(2u, key.get_row());
    EXPECT_EQ(0u, key.get_col());
    EXPECT_EQ(2u, key.get_depth());
    EXPECT_EQ("02", key.to_internal_string());
    key = QuadKey::from_internal_string(Type::Bing, "03");
    EXPECT_EQ(2u, key.get_row());
    EXPECT_EQ(1u, key.get_col());
    EXPECT_EQ(2u, key.get_depth());
    EXPECT_EQ("03", key.to_internal_string());
    key = QuadKey::from_internal_string(Type::Bing, "10");
    EXPECT_EQ(3u, key.get_row());
    EXPECT_EQ(2u, key.get_col());
    EXPECT_EQ(2u, key.get_depth());
    EXPECT_EQ("10", key.to_internal_string());
    key = QuadKey::from_internal_string(Type::Bing, "11");
    EXPECT_EQ(3u, key.get_row());
    EXPECT_EQ(3u, key.get_col());
    EXPECT_EQ(2u, key.get_depth());
    EXPECT_EQ("11", key.to_internal_string());
    key = QuadKey::from_internal_string(Type::Bing, "12");
    EXPECT_EQ(2u, key.get_row());
    EXPECT_EQ(2u, key.get_col());
    EXPECT_EQ(2u, key.get_depth());
    EXPECT_EQ("12", key.to_internal_string());
    key = QuadKey::from_internal_string(Type::Bing, "13");
    EXPECT_EQ(2u, key.get_row());
    EXPECT_EQ(3u, key.get_col());
    EXPECT_EQ(2u, key.get_depth());
    EXPECT_EQ("13", key.to_internal_string());
    key = QuadKey::from_internal_string(Type::Bing, "20");
    EXPECT_EQ(1u, key.get_row());
    EXPECT_EQ(0u, key.get_col());
    EXPECT_EQ(2u, key.get_depth());
    EXPECT_EQ("20", key.to_internal_string());
    key = QuadKey::from_internal_string(Type::Bing, "21");
    EXPECT_EQ(1u, key.get_row());
    EXPECT_EQ(1u, key.get_col());
    EXPECT_EQ(2u, key.get_depth());
    EXPECT_EQ("21", key.to_internal_string());
    key = QuadKey::from_internal_string(Type::Bing, "22");
    EXPECT_EQ(0u, key.get_row());
    EXPECT_EQ(0u, key.get_col());
    EXPECT_EQ(2u, key.get_depth());
    EXPECT_EQ("22", key.to_internal_string());
    key = QuadKey::from_internal_string(Type::Bing, "23");
    EXPECT_EQ(0u, key.get_row());
    EXPECT_EQ(1u, key.get_col());
    EXPECT_EQ(2u, key.get_depth());
    EXPECT_EQ("23", key.to_internal_string());
    key = QuadKey::from_internal_string(Type::Bing, "30");
    EXPECT_EQ(1u, key.get_row());
    EXPECT_EQ(2u, key.get_col());
    EXPECT_EQ(2u, key.get_depth());
    EXPECT_EQ("30", key.to_internal_string());
    key = QuadKey::from_internal_string(Type::Bing, "31");
    EXPECT_EQ(1u, key.get_row());
    EXPECT_EQ(3u, key.get_col());
    EXPECT_EQ(2u, key.get_depth());
    EXPECT_EQ("31", key.to_internal_string());
    key = QuadKey::from_internal_string(Type::Bing, "32");
    EXPECT_EQ(0u, key.get_row());
    EXPECT_EQ(2u, key.get_col());
    EXPECT_EQ(2u, key.get_depth());
    EXPECT_EQ("32", key.to_internal_string());
    key = QuadKey::from_internal_string(Type::Bing, "33");
    EXPECT_EQ(0u, key.get_row());
    EXPECT_EQ(3u, key.get_col());
    EXPECT_EQ(2u, key.get_depth());
    EXPECT_EQ("33", key.to_internal_string());
  }
}

TEST(BINGSYSTEM, get_get_coordinate_bounds2d) {
  QuadKey key;
  GeoCoordinateBoundingBox2d bbox;

  {  // Depth 0
    key = QuadKey::from_internal_string(Type::Bing, "");
    key.get_geo_coordinate_bounds2d(bbox);
    EXPECT_FLOAT_EQ(
        -180.0f, static_cast<float>(bbox.lower_left().get_longitude().val()));
    EXPECT_FLOAT_EQ(-84.928322f,
                    static_cast<float>(bbox.lower_left().get_latitude().val()));
    EXPECT_FLOAT_EQ(178.593750f, static_cast<float>(
                                     bbox.upper_right().get_longitude().val()));
    EXPECT_FLOAT_EQ(85.051132f, static_cast<float>(
                                    bbox.upper_right().get_latitude().val()));
  }
}

TEST(BINGSYSTEM, get_key_from_longitude_latitude_at_depth_to_bounds) {
  QuadKey key;
  GeoCoordinateBoundingBox2d bbox;
  double diff = 0.0;

  {  // Depth 0
    key = QuadKey::get_key_from_longitude_latitude_at_depth(
        Type::Bing, GeoCoordinate2d(Longitude(-180.0), Latitude(-84.0)), 0u);
    EXPECT_EQ(QuadKey(Type::Bing, 0, 0, 0), key);
    key.get_geo_coordinate_bounds2d(bbox);
    diff = std::fabs(bbox.lower_left().get_longitude() - Longitude(-180.0));
    EXPECT_GT(2.0, diff);
    diff = std::fabs(bbox.lower_left().get_latitude() - Latitude(-85.0));
    EXPECT_GT(2.0, diff);
    diff = std::fabs(bbox.upper_right().get_longitude() - Longitude(+180.0));
    EXPECT_GT(2.0, diff);
    diff = std::fabs(bbox.upper_right().get_latitude() - Latitude(+85.0));
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
  Longitude left(-180.0);
  Longitude midLeft(-0.36);  // This is related to math used by Bing
  Longitude midRight(0.0);
  Longitude right(+180.0);
  Latitude bottom(-90.0);  // Outside of Mercator space. Puts them in.
  Latitude midBottom(0.0);
  Latitude midTop(0.36);  // This is related to math used by Bing
  Latitude top(+90.0);    // Outside of Mercator space. Puts them in.

  {                                                           // Depth 1
    key = QuadKey::get_key_from_longitude_latitude_at_depth(  // Q0 ul
        Type::Bing, GeoCoordinate2d(left, top), 1u);
    EXPECT_EQ(QuadKey(Type::Bing, 1, 0, 1), key);
    key = QuadKey::get_key_from_longitude_latitude_at_depth(  // Q0 ll
        Type::Bing, GeoCoordinate2d(left, midTop), 1u);
    EXPECT_EQ(QuadKey(Type::Bing, 1, 0, 1), key);
    key = QuadKey::get_key_from_longitude_latitude_at_depth(  // Q0 lr
        Type::Bing, GeoCoordinate2d(midLeft, midTop), 1u);
    EXPECT_EQ(QuadKey(Type::Bing, 1, 0, 1), key);
    key = QuadKey::get_key_from_longitude_latitude_at_depth(  // Q0 ur
        Type::Bing, GeoCoordinate2d(midLeft, top), 1u);
    EXPECT_EQ(QuadKey(Type::Bing, 1, 0, 1), key);
    key.get_geo_coordinate_bounds2d(bbox);
    diff = std::fabs(bbox.lower_left().get_longitude() - left);
    EXPECT_GT(2.0, diff);
    diff = std::fabs(bbox.lower_left().get_latitude() - midTop);
    EXPECT_GT(2.0, diff);
    diff = std::fabs(bbox.upper_right().get_longitude() - midLeft);
    EXPECT_GT(2.0, diff);
    diff = std::fabs(bbox.upper_right().get_latitude() - Latitude(+85.0));
    EXPECT_GT(2.0, diff);

    key = QuadKey::get_key_from_longitude_latitude_at_depth(  // Q1 ul
        Type::Bing, GeoCoordinate2d(midRight, top), 1u);
    EXPECT_EQ(QuadKey(Type::Bing, 1, 1, 1), key);
    key = QuadKey::get_key_from_longitude_latitude_at_depth(  // Q1 ll
        Type::Bing, GeoCoordinate2d(midRight, midTop), 1u);
    EXPECT_EQ(QuadKey(Type::Bing, 1, 1, 1), key);
    key = QuadKey::get_key_from_longitude_latitude_at_depth(  // Q1 lr
        Type::Bing, GeoCoordinate2d(right, midTop), 1u);
    EXPECT_EQ(QuadKey(Type::Bing, 1, 1, 1), key);
    key = QuadKey::get_key_from_longitude_latitude_at_depth(  // Q1 ur
        Type::Bing, GeoCoordinate2d(right, top), 1u);
    EXPECT_EQ(QuadKey(Type::Bing, 1, 1, 1), key);
    key.get_geo_coordinate_bounds2d(bbox);
    diff = std::fabs(bbox.lower_left().get_longitude() - midRight);
    EXPECT_GT(2.0, diff);
    diff = std::fabs(bbox.lower_left().get_latitude() - midTop);
    EXPECT_GT(2.0, diff);
    diff = std::fabs(bbox.upper_right().get_longitude() - right);
    EXPECT_GT(2.0, diff);
    diff = std::fabs(bbox.upper_right().get_latitude() - Latitude(+85.0));
    EXPECT_GT(2.0, diff);

    key = QuadKey::get_key_from_longitude_latitude_at_depth(  // Q2 ul
        Type::Bing, GeoCoordinate2d(left, midBottom), 1u);
    EXPECT_EQ(QuadKey(Type::Bing, 0, 0, 1), key);
    key = QuadKey::get_key_from_longitude_latitude_at_depth(  // Q2 ll
        Type::Bing, GeoCoordinate2d(left, bottom), 1u);
    EXPECT_EQ(QuadKey(Type::Bing, 0, 0, 1), key);
    key = QuadKey::get_key_from_longitude_latitude_at_depth(  // Q2 lr
        Type::Bing, GeoCoordinate2d(midLeft, bottom), 1u);
    EXPECT_EQ(QuadKey(Type::Bing, 0, 0, 1), key);
    key = QuadKey::get_key_from_longitude_latitude_at_depth(  // Q2 ur
        Type::Bing, GeoCoordinate2d(midLeft, midBottom), 1u);
    EXPECT_EQ(QuadKey(Type::Bing, 0, 0, 1), key);
    key.get_geo_coordinate_bounds2d(bbox);
    diff = std::fabs(bbox.lower_left().get_longitude() - left);
    EXPECT_GT(2.0, diff);
    diff = std::fabs(bbox.lower_left().get_latitude() - Latitude(-85.0));
    EXPECT_GT(2.0, diff);
    diff = std::fabs(bbox.upper_right().get_longitude() - midLeft);
    EXPECT_GT(2.0, diff);
    diff = std::fabs(bbox.upper_right().get_latitude() - midBottom);
    EXPECT_GT(2.0, diff);

    key = QuadKey::get_key_from_longitude_latitude_at_depth(  // Q3 ul
        Type::Bing, GeoCoordinate2d(midRight, midBottom), 1u);
    EXPECT_EQ(QuadKey(Type::Bing, 0, 1, 1), key);
    key = QuadKey::get_key_from_longitude_latitude_at_depth(  // Q3 ll
        Type::Bing, GeoCoordinate2d(midRight, bottom), 1u);
    EXPECT_EQ(QuadKey(Type::Bing, 0, 1, 1), key);
    key = QuadKey::get_key_from_longitude_latitude_at_depth(  // Q3 lr
        Type::Bing, GeoCoordinate2d(right, bottom), 1u);
    EXPECT_EQ(QuadKey(Type::Bing, 0, 1, 1), key);
    key = QuadKey::get_key_from_longitude_latitude_at_depth(  // Q3 ur
        Type::Bing, GeoCoordinate2d(right, midBottom), 1u);
    EXPECT_EQ(QuadKey(Type::Bing, 0, 1, 1), key);
    key.get_geo_coordinate_bounds2d(bbox);
    diff = std::fabs(bbox.lower_left().get_longitude() - midRight);
    EXPECT_GT(2.0, diff);
    diff = std::fabs(bbox.lower_left().get_latitude() - Latitude(-85.0));
    EXPECT_GT(2.0, diff);
    diff = std::fabs(bbox.upper_right().get_longitude() - right);
    EXPECT_GT(2.0, diff);
    diff = std::fabs(bbox.upper_right().get_latitude() - midBottom);
    EXPECT_GT(2.0, diff);
  }
}

TEST(BINGSYSTEM, get_keys_from_longitude_latitude_bounding_box) {
  {
    std::vector<QuadKey> out_keys;
    out_keys = QuadKey::get_keys_from_longitude_latitude_bounding_box(
        Type::Bing,
        GeoCoordinateBoundingBox2d(
            GeoCoordinate2d(Longitude(-180.0), Latitude(+90.0)),
            GeoCoordinate2d(Longitude(+180.0), Latitude(-90.0))),
        0);
    EXPECT_EQ(1u, out_keys.size());
    EXPECT_NE(out_keys.end(), std::find(out_keys.begin(), out_keys.end(),
                                        QuadKey(Type::Bing, 0, 0, 0)));
  }

  {
    std::vector<QuadKey> out_keys;
    out_keys = QuadKey::get_keys_from_longitude_latitude_bounding_box(
        Type::Bing,
        GeoCoordinateBoundingBox2d(
            GeoCoordinate2d(Longitude(-180.0), Latitude(+90.0)),
            GeoCoordinate2d(Longitude(+180.0), Latitude(-90.0))),
        1);
    EXPECT_EQ(4u, out_keys.size());
    EXPECT_NE(out_keys.end(), std::find(out_keys.begin(), out_keys.end(),
                                        QuadKey(Type::Bing, 0, 0, 1)));
    EXPECT_NE(out_keys.end(), std::find(out_keys.begin(), out_keys.end(),
                                        QuadKey(Type::Bing, 0, 1, 1)));
    EXPECT_NE(out_keys.end(), std::find(out_keys.begin(), out_keys.end(),
                                        QuadKey(Type::Bing, 1, 0, 1)));
    EXPECT_NE(out_keys.end(), std::find(out_keys.begin(), out_keys.end(),
                                        QuadKey(Type::Bing, 1, 1, 1)));
  }

  {
    std::vector<QuadKey> out_keys;
    out_keys = QuadKey::get_keys_from_longitude_latitude_bounding_box(
        Type::Bing,
        GeoCoordinateBoundingBox2d(
            GeoCoordinate2d(Longitude(-180.0), Latitude(+0.35)),
            GeoCoordinate2d(Longitude(-0.36), Latitude(+90.0))),
        1);
    EXPECT_EQ(2u, out_keys.size());
    EXPECT_NE(out_keys.end(), std::find(out_keys.begin(), out_keys.end(),
                                        QuadKey(Type::Bing, 0, 0, 1)));
    EXPECT_NE(out_keys.end(), std::find(out_keys.begin(), out_keys.end(),
                                        QuadKey(Type::Bing, 1, 0, 1)));
  }

  {
    std::vector<QuadKey> out_keys;
    out_keys = QuadKey::get_keys_from_longitude_latitude_bounding_box(
        Type::Bing,
        GeoCoordinateBoundingBox2d(
            GeoCoordinate2d(Longitude(-0.36), Latitude(+0.36)),
            GeoCoordinate2d(Longitude(+0.36), Latitude(+90.0))),
        1);
    EXPECT_EQ(2u, out_keys.size());
    EXPECT_NE(out_keys.end(), std::find(out_keys.begin(), out_keys.end(),
                                        QuadKey(Type::Bing, 1, 0, 1)));
    EXPECT_NE(out_keys.end(), std::find(out_keys.begin(), out_keys.end(),
                                        QuadKey(Type::Bing, 1, 1, 1)));
  }

  {
    std::vector<QuadKey> out_keys;
    out_keys = QuadKey::get_keys_from_longitude_latitude_bounding_box(
        Type::Bing,
        GeoCoordinateBoundingBox2d(
            GeoCoordinate2d(Longitude(-0.36), Latitude(+0.35)),
            GeoCoordinate2d(Longitude(+0.36), Latitude(+90.0))),
        1);
    EXPECT_EQ(4u, out_keys.size());
    EXPECT_NE(out_keys.end(), std::find(out_keys.begin(), out_keys.end(),
                                        QuadKey(Type::Bing, 0, 0, 1)));
    EXPECT_NE(out_keys.end(), std::find(out_keys.begin(), out_keys.end(),
                                        QuadKey(Type::Bing, 0, 1, 1)));
    EXPECT_NE(out_keys.end(), std::find(out_keys.begin(), out_keys.end(),
                                        QuadKey(Type::Bing, 1, 0, 1)));
    EXPECT_NE(out_keys.end(), std::find(out_keys.begin(), out_keys.end(),
                                        QuadKey(Type::Bing, 1, 1, 1)));
  }
}

TEST(BINGSYSTEM, SelectedCities) {
  QuadKey key;
  const Type t = Type::Bing;

  {  // Chicago 41.822, -87.635
    const std::uint8_t depth = 16;
    GeoCoordinate2d coords(Longitude(-87.635), Latitude(41.822));

    key = QuadKey::get_key_from_longitude_latitude_at_depth(t, coords, depth);
    std::string key_str = key.to_internal_string();
    EXPECT_EQ("0302222310321132", key_str);

    GeoCoordinateBoundingBox2d bbox;
    key.get_geo_coordinate_bounds2d(bbox);

    // Note that Bing will return a bounding box of all sides inclusive
    std::vector<QuadKey> keys;
    keys =
        QuadKey::get_keys_from_longitude_latitude_bounding_box(t, bbox, depth);
    EXPECT_EQ(4u, keys.size());
    EXPECT_NE(keys.end(), std::find(keys.begin(), keys.end(), key));
  }

  {  // Rio -43.1964,-22.9083
    const std::uint8_t depth = 17;
    GeoCoordinate2d coords(Longitude(-43.1964), Latitude(-22.9083));

    key = QuadKey::get_key_from_longitude_latitude_at_depth(t, coords, depth);
    std::string key_str = key.to_internal_string();
    EXPECT_EQ("21120001212232200", key_str);

    GeoCoordinateBoundingBox2d bbox;
    key.get_geo_coordinate_bounds2d(bbox);

    // Note that Bing will return a bounding box of all sides inclusive
    std::vector<QuadKey> keys;
    keys =
        QuadKey::get_keys_from_longitude_latitude_bounding_box(t, bbox, depth);
    EXPECT_EQ(4u, keys.size());
    EXPECT_NE(keys.end(), std::find(keys.begin(), keys.end(), key));
  }

  {  // Helsinki 60.1708 N, 24.9375 E
    const std::uint8_t depth = 17;
    GeoCoordinate2d coords(Longitude(24.9375), Latitude(60.1708));

    key = QuadKey::get_key_from_longitude_latitude_at_depth(t, coords, depth);
    std::string key_str = key.to_internal_string();
    EXPECT_EQ("12012021101330131", key_str);

    GeoCoordinateBoundingBox2d bbox;
    key.get_geo_coordinate_bounds2d(bbox);

    // Note that Bing will return a bounding box of all sides inclusive
    std::vector<QuadKey> keys;
    keys =
        QuadKey::get_keys_from_longitude_latitude_bounding_box(t, bbox, depth);
    EXPECT_EQ(4u, keys.size());
    EXPECT_NE(keys.end(), std::find(keys.begin(), keys.end(), key));
  }

  {  // Cape Town South Africa 33.9253 S, 18.4239 E
    const std::uint8_t depth = 17;
    GeoCoordinate2d coords(Longitude(18.4239), Latitude(-33.9253));

    key = QuadKey::get_key_from_longitude_latitude_at_depth(t, coords, depth);
    std::string key_str = key.to_internal_string();
    EXPECT_EQ("30023103202132011", key_str);

    GeoCoordinateBoundingBox2d bbox;
    key.get_geo_coordinate_bounds2d(bbox);

    // Note that Bing will return a bounding box of all sides inclusive
    std::vector<QuadKey> keys;
    keys =
        QuadKey::get_keys_from_longitude_latitude_bounding_box(t, bbox, depth);
    EXPECT_EQ(4u, keys.size());
    EXPECT_NE(keys.end(), std::find(keys.begin(), keys.end(), key));
  }

  {  // Quito 0.2500 S, 78.5833 W
    const std::uint8_t depth = 17;
    GeoCoordinate2d coords(Longitude(-78.5836), Latitude(-0.25));

    key = QuadKey::get_key_from_longitude_latitude_at_depth(t, coords, depth);
    std::string key_str = key.to_internal_string();
    EXPECT_EQ("21001000002133122", key_str);

    GeoCoordinateBoundingBox2d bbox;
    key.get_geo_coordinate_bounds2d(bbox);

    // Note that Bing will return a bounding box of all sides inclusive
    std::vector<QuadKey> keys;
    keys =
        QuadKey::get_keys_from_longitude_latitude_bounding_box(t, bbox, depth);
    EXPECT_EQ(4u, keys.size());
    EXPECT_NE(keys.end(), std::find(keys.begin(), keys.end(), key));
  }
}
}  // namespace quad_keys

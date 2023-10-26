#include <gtest/gtest.h>

#include "quad_keys/geo_coordinate2d.h"
#include "quad_keys/quad_key.h"

#include <iostream>
#include <sstream>
#include <utility>

namespace quad_keys
{
  class TestMortonSystem : public ::testing::Test
  {
  protected:
    virtual void SetUp() {}
    virtual void TearDown() {}
  };

  TEST(MORTONSYSTEM, is_valid)
  {
    // Same as bing_system
  }

  TEST(MORTONSYSTEM, is_root_key)
  {
    // Same as bing_system
  }

  TEST(MORTONSYSTEM, get_parent)
  {
    // Same as bing_system
  }

  TEST(MORTONSYSTEM, is_my_ancestor)
  {
    // Same as bing_system
  }

  TEST(MORTONSYSTEM, get_ancestor)
  {
    {
      QuadKey key(Type::Morton, 0, 1, 1);
      QuadKey ancestor(Type::Morton, 0, 0, 0);
      EXPECT_EQ(ancestor, key.get_ancestor(1));
      EXPECT_EQ(key.get_parent(), key.get_ancestor(1));
    }
    {
      QuadKey key(Type::Morton, 0, 0, 1);
      QuadKey ancestor(Type::Morton, 0, 0, 0);
      EXPECT_EQ(ancestor, key.get_ancestor(1));
      EXPECT_EQ(key.get_parent(), key.get_ancestor(1));
    }
    {
      QuadKey key(Type::Morton, 1, 1, 1);
      QuadKey ancestor(Type::Morton, 0, 0, 0);
      EXPECT_EQ(ancestor, key.get_ancestor(1));
    }
    {
      QuadKey key(Type::Morton, 1, 2, 1);
      QuadKey ancestor(Type::Morton, 0, 1, 0);
      EXPECT_EQ(ancestor, key.get_ancestor(1));
    }
    {
      QuadKey key(Type::Morton, 0, 3, 1);
      QuadKey ancestor(Type::Morton, 0, 1, 0);
      EXPECT_EQ(ancestor, key.get_ancestor(1));
    }
  }

  TEST(MORTONSYSTEM, get_child)
  {
    // Same as bing_system
  }

  TEST(MORTONSYSTEM, get_children)
  {
    // Same as bing_system
  }

  TEST(MORTONSYSTEM, get_descendants)
  {
    // Same as bing_system
  }

  TEST(MORTONSYSTEM, get_siblings)
  {
    std::vector<QuadKey> test_keys;
    test_keys = QuadKey(Type::Morton, 0, 0, 1).get_siblings();
    EXPECT_EQ(3u, test_keys.size());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      QuadKey(Type::Morton, 1, 0, 1)), test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      QuadKey(Type::Morton, 1, 1, 1)), test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      QuadKey(Type::Morton, 0, 1, 1)), test_keys.end());
    test_keys = QuadKey(Type::Morton, 1, 3, 1).get_siblings();
    EXPECT_EQ(3u, test_keys.size());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      QuadKey(Type::Morton, 1, 2, 1)), test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      QuadKey(Type::Morton, 0, 2, 1)), test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      QuadKey(Type::Morton, 0, 3, 1)), test_keys.end());
  }

  TEST(MORTONSYSTEM, get_neighbors)
  {
    // Same as bing_system but just to be safe
    std::vector<QuadKey> test_keys;
    test_keys = QuadKey().get_neighbors();
    EXPECT_TRUE(test_keys.empty());
    test_keys.clear();

    test_keys = QuadKey(Type::Morton, 0, 0, 2).get_neighbors();
    EXPECT_EQ(5u, test_keys.size());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      QuadKey(Type::Morton, 0, 1, 2)), test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      QuadKey(Type::Morton, 1, 1, 2)), test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      QuadKey(Type::Morton, 1, 0, 2)), test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      QuadKey(Type::Morton, 0, 7, 2)), test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      QuadKey(Type::Morton, 1, 7, 2)), test_keys.end());
    test_keys.clear();

    test_keys = QuadKey(Type::Morton, 0, 1, 2).get_neighbors();
    EXPECT_EQ(5u, test_keys.size());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      QuadKey(Type::Morton, 0, 0, 2)), test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      QuadKey(Type::Morton, 1, 0, 2)), test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      QuadKey(Type::Morton, 1, 1, 2)), test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      QuadKey(Type::Morton, 1, 2, 2)), test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      QuadKey(Type::Morton, 0, 2, 2)), test_keys.end());
    test_keys.clear();

    test_keys = QuadKey(Type::Morton, 0, 2, 2).get_neighbors();
    EXPECT_EQ(5u, test_keys.size());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      QuadKey(Type::Morton, 0, 1, 2)), test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      QuadKey(Type::Morton, 1, 1, 2)), test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      QuadKey(Type::Morton, 1, 2, 2)), test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      QuadKey(Type::Morton, 1, 3, 2)), test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      QuadKey(Type::Morton, 0, 3, 2)), test_keys.end());
    test_keys.clear();

    test_keys = QuadKey(Type::Morton, 0, 3, 2).get_neighbors();
    EXPECT_EQ(5u, test_keys.size());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      QuadKey(Type::Morton, 0, 2, 2)), test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      QuadKey(Type::Morton, 1, 2, 2)), test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      QuadKey(Type::Morton, 1, 3, 2)), test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      QuadKey(Type::Morton, 1, 4, 2)), test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      QuadKey(Type::Morton, 0, 4, 2)), test_keys.end());
    test_keys.clear();

    test_keys = QuadKey(Type::Morton, 0, 0, 2).get_neighbors();
    EXPECT_EQ(5u, test_keys.size());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      QuadKey(Type::Morton, 0, 1, 2)), test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      QuadKey(Type::Morton, 1, 1, 2)), test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      QuadKey(Type::Morton, 1, 0, 2)), test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      QuadKey(Type::Morton, 1, 7, 2)), test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      QuadKey(Type::Morton, 0, 7, 2)), test_keys.end());
    test_keys.clear();

    test_keys = QuadKey(Type::Morton, 3, 1, 2).get_neighbors();
    EXPECT_EQ(5u, test_keys.size());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      QuadKey(Type::Morton, 3, 0, 2)), test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      QuadKey(Type::Morton, 2, 0, 2)), test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      QuadKey(Type::Morton, 2, 1, 2)), test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      QuadKey(Type::Morton, 2, 2, 2)), test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      QuadKey(Type::Morton, 3, 2, 2)), test_keys.end());
    test_keys.clear();

    test_keys = QuadKey(Type::Morton, 3, 2, 2).get_neighbors();
    EXPECT_EQ(5u, test_keys.size());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      QuadKey(Type::Morton, 3, 1, 2)), test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      QuadKey(Type::Morton, 2, 1, 2)), test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      QuadKey(Type::Morton, 2, 2, 2)), test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      QuadKey(Type::Morton, 2, 3, 2)), test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      QuadKey(Type::Morton, 3, 3, 2)), test_keys.end());
    test_keys.clear();

    test_keys = QuadKey(Type::Morton, 3, 3, 2).get_neighbors();
    EXPECT_EQ(5u, test_keys.size());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      QuadKey(Type::Morton, 3, 2, 2)), test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      QuadKey(Type::Morton, 2, 2, 2)), test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      QuadKey(Type::Morton, 2, 3, 2)), test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      QuadKey(Type::Morton, 2, 4, 2)), test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      QuadKey(Type::Morton, 3, 4, 2)), test_keys.end());
    test_keys.clear();

    test_keys = QuadKey(Type::Bing, 4, 7, 3).get_neighbors();
    EXPECT_EQ(8u, test_keys.size());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      QuadKey(Type::Bing, 3, 7, 3)), test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      QuadKey(Type::Bing, 3, 6, 3)), test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      QuadKey(Type::Bing, 4, 6, 3)), test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      QuadKey(Type::Bing, 5, 6, 3)), test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      QuadKey(Type::Bing, 5, 7, 3)), test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      QuadKey(Type::Bing, 5, 0, 3)), test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      QuadKey(Type::Bing, 4, 0, 3)), test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      QuadKey(Type::Bing, 3, 0, 3)), test_keys.end());
    test_keys.clear();

    test_keys = QuadKey(Type::Bing, 4, 0, 3).get_neighbors();
    EXPECT_EQ(8u, test_keys.size());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      QuadKey(Type::Bing, 3, 0, 3)), test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      QuadKey(Type::Bing, 3, 1, 3)), test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      QuadKey(Type::Bing, 4, 1, 3)), test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      QuadKey(Type::Bing, 5, 1, 3)), test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      QuadKey(Type::Bing, 5, 0, 3)), test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      QuadKey(Type::Bing, 5, 7, 3)), test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      QuadKey(Type::Bing, 4, 7, 3)), test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
     QuadKey(Type::Bing, 3, 7, 3)), test_keys.end());
    test_keys.clear();

    test_keys = QuadKey(Type::Morton, 0, 0, 0).get_neighbors();
    EXPECT_EQ(0u, test_keys.size());
  }

  TEST(MORTONSYSTEM, from_string_to_string)
  {
    // X ==> Unused
    // O ==> Used but never set
    // (0,1) ==> Binary digits
    QuadKey qk(Type::Morton, 0, 0, 0);
    std::string fmt = qk.to_internal_string();
    EXPECT_EQ("65537", fmt); // XXXX XXXX XXXX XXX1 XXXX XXXX XXXX XXO1
    class QuadKey quad_key_back = QuadKey::from_internal_string(
      Type::Morton, fmt);
    EXPECT_EQ(qk, quad_key_back);

    qk = QuadKey(Type::Morton, 0, 1, 0);
    fmt = qk.to_internal_string();
    EXPECT_EQ("65536", fmt); // XXXX XXXX XXXX XXX1 XXXX XXXX XXXX XXO0
    quad_key_back = QuadKey::from_internal_string(Type::Morton, fmt);
    EXPECT_EQ(qk, quad_key_back);

    qk = QuadKey(Type::Morton, 0, 0, 1);
    fmt = qk.to_internal_string();
    EXPECT_EQ("131078", fmt); // XXXX XXXX XXXX XX1X XXXX XXXX XXXX O110
    quad_key_back = QuadKey::from_internal_string(Type::Morton, fmt);
    EXPECT_EQ(qk, quad_key_back);

    qk = QuadKey(Type::Morton, 0, 1, 1);
    fmt = qk.to_internal_string();
    EXPECT_EQ("131079", fmt); // XXXX XXXX XXXX XX1O OOOO OOOO OOOO O111
    quad_key_back = QuadKey::from_internal_string(Type::Morton, fmt);
    EXPECT_EQ(qk, quad_key_back);

    qk = QuadKey(Type::Morton, 0, 2, 1);
    fmt = qk.to_internal_string();
    EXPECT_EQ("131074", fmt); // XXXX XXXX XXXX XX1X XXXX XXXX XXXX O010
    quad_key_back = QuadKey::from_internal_string(Type::Morton, fmt);
    EXPECT_EQ(qk, quad_key_back);

    qk = QuadKey(Type::Morton, 0, 3, 1);
    fmt = qk.to_internal_string();
    EXPECT_EQ("131075", fmt); // XXXX XXXX XXXX XX1X XXXX XXXX XXXX O011
    quad_key_back = QuadKey::from_internal_string(Type::Morton, fmt);
    EXPECT_EQ(qk, quad_key_back);

    qk = QuadKey(Type::Morton, 1, 0, 1);
    fmt = qk.to_internal_string();
    EXPECT_EQ("131076", fmt); // XXXX XXXX XXXX XX1X XXXX XXXX XXXX O100
    quad_key_back = QuadKey::from_internal_string(Type::Morton, fmt);
    EXPECT_EQ(qk, quad_key_back);

    qk = QuadKey(Type::Morton, 1, 1, 1);
    fmt = qk.to_internal_string();
    EXPECT_EQ("131077", fmt); // XXXX XXXX XXXX XX1X XXXX XXXX XXXX O101
    quad_key_back = QuadKey::from_internal_string(Type::Morton, fmt);
    EXPECT_EQ(qk, quad_key_back);

    qk = QuadKey(Type::Morton, 1, 2, 1);
    fmt = qk.to_internal_string();
    EXPECT_EQ("131072", fmt); // XXXX XXXX XXXX XX1X XXXX XXXX XXXX O000
    quad_key_back = QuadKey::from_internal_string(Type::Morton, fmt);
    EXPECT_EQ(qk, quad_key_back);

    qk = QuadKey(Type::Morton, 1, 3, 1);
    fmt = qk.to_internal_string();
    EXPECT_EQ("131073", fmt); // XXXX XXXX XXXX XX1X XXXX XXXX XXXX O001
    quad_key_back = QuadKey::from_internal_string(Type::Morton, fmt);
    EXPECT_EQ(qk, quad_key_back);

    qk = QuadKey(Type::Morton, 0, 0, 2);
    fmt = qk.to_internal_string();
    EXPECT_EQ("262168", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO1 1000
    quad_key_back = QuadKey::from_internal_string(Type::Morton, fmt);
    EXPECT_EQ(qk, quad_key_back);

    qk = QuadKey(Type::Morton, 0, 1, 2);
    fmt = qk.to_internal_string();
    EXPECT_EQ("262169", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO1 1001
    quad_key_back = QuadKey::from_internal_string(Type::Morton, fmt);
    EXPECT_EQ(qk, quad_key_back);

    qk = QuadKey(Type::Morton, 0, 2, 2);
    fmt = qk.to_internal_string();
    EXPECT_EQ("262172", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO1 1100
    quad_key_back = QuadKey::from_internal_string(Type::Morton, fmt);
    EXPECT_EQ(qk, quad_key_back);

    qk = QuadKey(Type::Morton, 0, 3, 2);
    fmt = qk.to_internal_string();
    EXPECT_EQ("262173", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO1 1101
    quad_key_back = QuadKey::from_internal_string(Type::Morton, fmt);
    EXPECT_EQ(qk, quad_key_back);

    qk = QuadKey(Type::Morton, 0, 4, 2);
    fmt = qk.to_internal_string();
    EXPECT_EQ("262152", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO0 1000
    quad_key_back = QuadKey::from_internal_string(Type::Morton, fmt);
    EXPECT_EQ(qk, quad_key_back);

    qk = QuadKey(Type::Morton, 0, 5, 2);
    fmt = qk.to_internal_string();
    EXPECT_EQ("262153", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO0 1001
    quad_key_back = QuadKey::from_internal_string(Type::Morton, fmt);
    EXPECT_EQ(qk, quad_key_back);

    qk = QuadKey(Type::Morton, 0, 6, 2);
    fmt = qk.to_internal_string();
    EXPECT_EQ("262156", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO0 1100
    quad_key_back = QuadKey::from_internal_string(Type::Morton, fmt);
    EXPECT_EQ(qk, quad_key_back);

    qk = QuadKey(Type::Morton, 0, 7, 2);
    fmt = qk.to_internal_string();
    EXPECT_EQ("262157", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO0 1101
    quad_key_back = QuadKey::from_internal_string(Type::Morton, fmt);
    EXPECT_EQ(qk, quad_key_back);

    qk = QuadKey(Type::Morton, 1, 0, 2);
    fmt = qk.to_internal_string();
    EXPECT_EQ("262170", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO1 1010
    quad_key_back = QuadKey::from_internal_string(Type::Morton, fmt);
    EXPECT_EQ(qk, quad_key_back);

    qk = QuadKey(Type::Morton, 1, 1, 2);
    fmt = qk.to_internal_string();
    EXPECT_EQ("262171", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO1 1011
    quad_key_back = QuadKey::from_internal_string(Type::Morton, fmt);
    EXPECT_EQ(qk, quad_key_back);

    qk = QuadKey(Type::Morton, 1, 2, 2);
    fmt = qk.to_internal_string();
    EXPECT_EQ("262174", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO1 1110
    quad_key_back = QuadKey::from_internal_string(Type::Morton, fmt);
    EXPECT_EQ(qk, quad_key_back);

    qk = QuadKey(Type::Morton, 1, 3, 2);
    fmt = qk.to_internal_string();
    EXPECT_EQ("262175", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO1 1111
    quad_key_back = QuadKey::from_internal_string(Type::Morton, fmt);
    EXPECT_EQ(qk, quad_key_back);

    qk = QuadKey(Type::Morton, 1, 4, 2);
    fmt = qk.to_internal_string();
    EXPECT_EQ("262154", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO0 1010
    quad_key_back = QuadKey::from_internal_string(Type::Morton, fmt);
    EXPECT_EQ(qk, quad_key_back);

    qk = QuadKey(Type::Morton, 1, 5, 2);
    fmt = qk.to_internal_string();
    EXPECT_EQ("262155", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO0 1011
    quad_key_back = QuadKey::from_internal_string(Type::Morton, fmt);
    EXPECT_EQ(qk, quad_key_back);

    qk = QuadKey(Type::Morton, 1, 6, 2);
    fmt = qk.to_internal_string();
    EXPECT_EQ("262158", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO0 1110
    quad_key_back = QuadKey::from_internal_string(Type::Morton, fmt);
    EXPECT_EQ(qk, quad_key_back);

    qk = QuadKey(Type::Morton, 1, 7, 2);
    fmt = qk.to_internal_string();
    EXPECT_EQ("262159", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO0 1111
    quad_key_back = QuadKey::from_internal_string(Type::Morton, fmt);
    EXPECT_EQ(qk, quad_key_back);

    qk = QuadKey(Type::Morton, 2, 0, 2);
    fmt = qk.to_internal_string();
    EXPECT_EQ("262160", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO1 0000
    quad_key_back = QuadKey::from_internal_string(Type::Morton, fmt);
    EXPECT_EQ(qk, quad_key_back);

    qk = QuadKey(Type::Morton, 2, 1, 2);
    fmt = qk.to_internal_string();
    EXPECT_EQ("262161", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO1 0001
    quad_key_back = QuadKey::from_internal_string(Type::Morton, fmt);
    EXPECT_EQ(qk, quad_key_back);

    qk = QuadKey(Type::Morton, 2, 2, 2);
    fmt = qk.to_internal_string();
    EXPECT_EQ("262164", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO1 0100
    quad_key_back = QuadKey::from_internal_string(Type::Morton, fmt);
    EXPECT_EQ(qk, quad_key_back);

    qk = QuadKey(Type::Morton, 2, 3, 2);
    fmt = qk.to_internal_string();
    EXPECT_EQ("262165", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO1 0101
    quad_key_back = QuadKey::from_internal_string(Type::Morton, fmt);
    EXPECT_EQ(qk, quad_key_back);

    qk = QuadKey(Type::Morton, 2, 4, 2);
    fmt = qk.to_internal_string();
    EXPECT_EQ("262144", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO0 0000
    quad_key_back = QuadKey::from_internal_string(Type::Morton, fmt);
    EXPECT_EQ(qk, quad_key_back);

    qk = QuadKey(Type::Morton, 2, 5, 2);
    fmt = qk.to_internal_string();
    EXPECT_EQ("262145", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO0 0001
    quad_key_back = QuadKey::from_internal_string(Type::Morton, fmt);
    EXPECT_EQ(qk, quad_key_back);

    qk = QuadKey(Type::Morton, 2, 6, 2);
    fmt = qk.to_internal_string();
    EXPECT_EQ("262148", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO0 0100
    quad_key_back = QuadKey::from_internal_string(Type::Morton, fmt);
    EXPECT_EQ(qk, quad_key_back);

    qk = QuadKey(Type::Morton, 2, 7, 2);
    fmt = qk.to_internal_string();
    EXPECT_EQ("262149", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO0 0101
    quad_key_back = QuadKey::from_internal_string(Type::Morton, fmt);
    EXPECT_EQ(qk, quad_key_back);

    qk = QuadKey(Type::Morton, 3, 0, 2);
    fmt = qk.to_internal_string();
    EXPECT_EQ("262162", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO1 0010
    quad_key_back = QuadKey::from_internal_string(Type::Morton, fmt);
    EXPECT_EQ(qk, quad_key_back);

    qk = QuadKey(Type::Morton, 3, 1, 2);
    fmt = qk.to_internal_string();
    EXPECT_EQ("262163", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO1 0011
    quad_key_back = QuadKey::from_internal_string(Type::Morton, fmt);
    EXPECT_EQ(qk, quad_key_back);

    qk = QuadKey(Type::Morton, 3, 2, 2);
    fmt = qk.to_internal_string();
    EXPECT_EQ("262166", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO1 0110
    quad_key_back = QuadKey::from_internal_string(Type::Morton, fmt);
    EXPECT_EQ(qk, quad_key_back);

    qk = QuadKey(Type::Morton, 3, 3, 2);
    fmt = qk.to_internal_string();
    EXPECT_EQ("262167", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO1 0111
    quad_key_back = QuadKey::from_internal_string(Type::Morton, fmt);
    EXPECT_EQ(qk, quad_key_back);

    qk = QuadKey(Type::Morton, 3, 4, 2);
    fmt = qk.to_internal_string();
    EXPECT_EQ("262146", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO0 0010
    quad_key_back = QuadKey::from_internal_string(Type::Morton, fmt);
    EXPECT_EQ(qk, quad_key_back);

    qk = QuadKey(Type::Morton, 3, 5, 2);
    fmt = qk.to_internal_string();
    EXPECT_EQ("262147", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO0 0011
    quad_key_back = QuadKey::from_internal_string(Type::Morton, fmt);
    EXPECT_EQ(qk, quad_key_back);

    qk = QuadKey(Type::Morton, 3, 6, 2);
    fmt = qk.to_internal_string();
    EXPECT_EQ("262150", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO0 0110
    quad_key_back = QuadKey::from_internal_string(Type::Morton, fmt);
    EXPECT_EQ(qk, quad_key_back);

    qk = QuadKey(Type::Morton, 3, 7, 2);
    fmt = qk.to_internal_string();
    EXPECT_EQ("262151", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO0 0111
    quad_key_back = QuadKey::from_internal_string(Type::Morton, fmt);
    EXPECT_EQ(qk, quad_key_back);
  }

  TEST(MORTONSYSTEM, get_key_from_longitude_latitude_at_depth_to_bounds)
  {
    GeoCoordinate2d coords;
    std::uint8_t depth = 0;
    { // West
      QuadKey morton_key;
      coords = GeoCoordinate2d(Longitude(-0.1), Latitude(0.0));
      morton_key = QuadKey::get_key_from_longitude_latitude_at_depth(
        Type::Morton, coords, depth);
      EXPECT_EQ("65537", morton_key.to_internal_string());
      coords = GeoCoordinate2d(Longitude(-180.0), Latitude(90.0));
      morton_key = QuadKey::get_key_from_longitude_latitude_at_depth(
        Type::Morton, coords, depth);
      EXPECT_EQ("65537", morton_key.to_internal_string());
      coords = GeoCoordinate2d(Longitude(-180.0), Latitude(-90.0));
      morton_key = QuadKey::get_key_from_longitude_latitude_at_depth(
        Type::Morton, coords, depth);
      EXPECT_EQ("65537", morton_key.to_internal_string());
      GeoCoordinateBoundingBox2d actual;
      morton_key.get_geo_coordinate_bounds2d(actual);
      EXPECT_TRUE(GeoCoordinate2d(Longitude(-180.0),
        Latitude(- 90.0)).near(actual.lower_left(), 1)) <<
        "actual = " << actual.lower_left();
      EXPECT_TRUE(GeoCoordinate2d(Longitude(-  0.1),
        Latitude(+ 90.0)).near(actual.upper_right(), 1)) <<
        "actual = " << actual.upper_right();
    }
    { // East
      QuadKey morton_key;
      coords = GeoCoordinate2d(Longitude(0.0), Latitude(0.0));
      morton_key = QuadKey::get_key_from_longitude_latitude_at_depth(
        Type::Morton, coords, depth);
      EXPECT_EQ("65536", morton_key.to_internal_string());
      coords = GeoCoordinate2d(Longitude(180.0), Latitude(-90.0));
      morton_key = QuadKey::get_key_from_longitude_latitude_at_depth(
        Type::Morton, coords, depth);
      EXPECT_EQ("65536", morton_key.to_internal_string());
      coords = GeoCoordinate2d(Longitude(180.0), Latitude(90.0));
      morton_key = QuadKey::get_key_from_longitude_latitude_at_depth(
        Type::Morton, coords, depth);
      EXPECT_EQ("65536", morton_key.to_internal_string());
      GeoCoordinateBoundingBox2d actual;
      morton_key.get_geo_coordinate_bounds2d(actual);
      EXPECT_TRUE(GeoCoordinate2d(Longitude(+  0.0),
        Latitude(- 90.0)).near(actual.lower_left(), 1)) <<
        "actual = " << actual.lower_left();
      EXPECT_TRUE(GeoCoordinate2d(Longitude(+180.0),
        Latitude(+ 90.0)).near(actual.upper_right(), 1)) <<
        "actual = " << actual.upper_right();
    }
    depth = 1;
    { // 0x6
      QuadKey morton_key;
      coords = GeoCoordinate2d(Longitude(-180.0), Latitude(-0.1));
      morton_key = QuadKey::get_key_from_longitude_latitude_at_depth(
        Type::Morton, coords, depth);
      EXPECT_EQ("131078", morton_key.to_internal_string());
      coords = GeoCoordinate2d(Longitude(-180.0), Latitude(-90.0));
      morton_key = QuadKey::get_key_from_longitude_latitude_at_depth(
        Type::Morton, coords, depth);
      EXPECT_EQ("131078", morton_key.to_internal_string());
      coords = GeoCoordinate2d(Longitude(-90.1), Latitude(-90.0));
      morton_key = QuadKey::get_key_from_longitude_latitude_at_depth(
        Type::Morton, coords, depth);
      EXPECT_EQ("131078", morton_key.to_internal_string());
      coords = GeoCoordinate2d(Longitude(-90.1), Latitude(-0.1));
      morton_key = QuadKey::get_key_from_longitude_latitude_at_depth(
        Type::Morton, coords, depth);
      EXPECT_EQ("131078", morton_key.to_internal_string());
    }
    { // 0x7
      QuadKey morton_key;
      coords = GeoCoordinate2d(Longitude(-90.0), Latitude(-0.1));
      morton_key = QuadKey::get_key_from_longitude_latitude_at_depth(
        Type::Morton, coords, depth);
      EXPECT_EQ("131079", morton_key.to_internal_string());
      coords = GeoCoordinate2d(Longitude(-90.0), Latitude(-90.0));
      morton_key = QuadKey::get_key_from_longitude_latitude_at_depth(
        Type::Morton, coords, depth);
      EXPECT_EQ("131079", morton_key.to_internal_string());
      coords = GeoCoordinate2d(Longitude(-0.1), Latitude(-90.0));
      morton_key = QuadKey::get_key_from_longitude_latitude_at_depth(
        Type::Morton, coords, depth);
      EXPECT_EQ("131079", morton_key.to_internal_string());
      coords = GeoCoordinate2d(Longitude(-0.1), Latitude(-0.1));
      morton_key = QuadKey::get_key_from_longitude_latitude_at_depth(
        Type::Morton, coords, depth);
      EXPECT_EQ("131079", morton_key.to_internal_string());
    }
    { // 0x2
      QuadKey morton_key;
      coords = GeoCoordinate2d(Longitude(0.0), Latitude(-0.1));
      morton_key = QuadKey::get_key_from_longitude_latitude_at_depth(
        Type::Morton, coords, depth);
      EXPECT_EQ("131074", morton_key.to_internal_string());
      coords = GeoCoordinate2d(Longitude(0.0), Latitude(-90.0));
      morton_key = QuadKey::get_key_from_longitude_latitude_at_depth(
        Type::Morton, coords, depth);
      EXPECT_EQ("131074", morton_key.to_internal_string());
      coords = GeoCoordinate2d(Longitude(90.0), Latitude(-90.0));
      morton_key = QuadKey::get_key_from_longitude_latitude_at_depth(
        Type::Morton, coords, depth);
      EXPECT_EQ("131074", morton_key.to_internal_string());
      coords = GeoCoordinate2d(Longitude(90.0), Latitude(-0.1));
      morton_key = QuadKey::get_key_from_longitude_latitude_at_depth(
        Type::Morton, coords, depth);
      EXPECT_EQ("131074", morton_key.to_internal_string());
    }
    { // 0x3
      QuadKey morton_key;
      coords = GeoCoordinate2d(Longitude(90.1), Latitude(-0.1));
      morton_key = QuadKey::get_key_from_longitude_latitude_at_depth(
        Type::Morton, coords, depth);
      EXPECT_EQ("131075", morton_key.to_internal_string());
      coords = GeoCoordinate2d(Longitude(90.1), Latitude(-90.0));
      morton_key = QuadKey::get_key_from_longitude_latitude_at_depth(
        Type::Morton, coords, depth);
      EXPECT_EQ("131075", morton_key.to_internal_string());
      coords = GeoCoordinate2d(Longitude(180.0), Latitude(-90.0));
      morton_key = QuadKey::get_key_from_longitude_latitude_at_depth(
        Type::Morton, coords, depth);
      EXPECT_EQ("131075", morton_key.to_internal_string());
      coords = GeoCoordinate2d(Longitude(180.0), Latitude(-0.1));
      morton_key = QuadKey::get_key_from_longitude_latitude_at_depth(
        Type::Morton, coords, depth);
      EXPECT_EQ("131075", morton_key.to_internal_string());
    }
    { // 0x4
      QuadKey morton_key;
      coords = GeoCoordinate2d(Longitude(-180.0), Latitude(90.0));
      morton_key = QuadKey::get_key_from_longitude_latitude_at_depth(
          Type::Morton, coords, depth);
      EXPECT_EQ("131076", morton_key.to_internal_string());
      coords = GeoCoordinate2d(Longitude(-180.0), Latitude(0.0));
      morton_key = QuadKey::get_key_from_longitude_latitude_at_depth(
          Type::Morton, coords, depth);
      EXPECT_EQ("131076", morton_key.to_internal_string());
      coords = GeoCoordinate2d(Longitude(-90.1), Latitude(0.0));
      morton_key = QuadKey::get_key_from_longitude_latitude_at_depth(
          Type::Morton, coords, depth);
      EXPECT_EQ("131076", morton_key.to_internal_string());
      coords = GeoCoordinate2d(Longitude(-90.1), Latitude(90.0));
      morton_key = QuadKey::get_key_from_longitude_latitude_at_depth(
          Type::Morton, coords, depth);
      EXPECT_EQ("131076", morton_key.to_internal_string());
    }
    { // 0x5
      QuadKey morton_key;
      coords = GeoCoordinate2d(Longitude(-90.0), Latitude(90.0));
      morton_key = QuadKey::get_key_from_longitude_latitude_at_depth(
        Type::Morton, coords, depth);
      EXPECT_EQ("131077", morton_key.to_internal_string());
      coords = GeoCoordinate2d(Longitude(-90.0), Latitude(0.0));
      morton_key = QuadKey::get_key_from_longitude_latitude_at_depth(
        Type::Morton, coords, depth);
      EXPECT_EQ("131077", morton_key.to_internal_string());
      coords = GeoCoordinate2d(Longitude(-0.1), Latitude(0.0));
      morton_key = QuadKey::get_key_from_longitude_latitude_at_depth(
        Type::Morton, coords, depth);
      EXPECT_EQ("131077", morton_key.to_internal_string());
      coords = GeoCoordinate2d(Longitude(-0.1), Latitude(90.0));
      morton_key = QuadKey::get_key_from_longitude_latitude_at_depth(
        Type::Morton, coords, depth);
      EXPECT_EQ("131077", morton_key.to_internal_string());
    }
    { // 0x0
      QuadKey morton_key;
      coords = GeoCoordinate2d(Longitude(0.0), Latitude(90.0));
      morton_key = QuadKey::get_key_from_longitude_latitude_at_depth(
        Type::Morton, coords, depth);
      EXPECT_EQ("131072", morton_key.to_internal_string());
      coords = GeoCoordinate2d(Longitude(0.0), Latitude(0.0));
      morton_key = QuadKey::get_key_from_longitude_latitude_at_depth(
        Type::Morton, coords, depth);
      EXPECT_EQ("131072", morton_key.to_internal_string());
      coords = GeoCoordinate2d(Longitude(90.0), Latitude(0.0));
      morton_key = QuadKey::get_key_from_longitude_latitude_at_depth(
        Type::Morton, coords, depth);
      EXPECT_EQ("131072", morton_key.to_internal_string());
      coords = GeoCoordinate2d(Longitude(90.0), Latitude(90.0));
      morton_key = QuadKey::get_key_from_longitude_latitude_at_depth(
        Type::Morton, coords, depth);
      EXPECT_EQ("131072", morton_key.to_internal_string());
    }
    { // 0x1
      QuadKey morton_key;
      coords = GeoCoordinate2d(Longitude(90.1), Latitude(90.0));
      morton_key = QuadKey::get_key_from_longitude_latitude_at_depth(
        Type::Morton, coords, depth);
      EXPECT_EQ("131073", morton_key.to_internal_string());
      coords = GeoCoordinate2d(Longitude(90.1), Latitude(0.0));
      morton_key = QuadKey::get_key_from_longitude_latitude_at_depth(
        Type::Morton, coords, depth);
      EXPECT_EQ("131073", morton_key.to_internal_string());
      coords = GeoCoordinate2d(Longitude(180.0), Latitude(0.0));
      morton_key = QuadKey::get_key_from_longitude_latitude_at_depth(
        Type::Morton, coords, depth);
      EXPECT_EQ("131073", morton_key.to_internal_string());
      coords = GeoCoordinate2d(Longitude(180.0), Latitude(90.0));
      morton_key = QuadKey::get_key_from_longitude_latitude_at_depth(
        Type::Morton, coords, depth);
      EXPECT_EQ("131073", morton_key.to_internal_string());
    }
    depth = 2;
    for (const auto &pair : {
      std::make_pair(GeoCoordinateBoundingBox2d(
          GeoCoordinate2d(Longitude(-180.0), Latitude(- 90.0)),
          GeoCoordinate2d(Longitude(-135.1), Latitude(- 45.1))),
          "262168"),
      std::make_pair(GeoCoordinateBoundingBox2d(
          GeoCoordinate2d(Longitude(-135.0), Latitude(- 90.0)),
          GeoCoordinate2d(Longitude(- 90.1), Latitude(- 45.1))),
          "262169"),
      std::make_pair(GeoCoordinateBoundingBox2d(
          GeoCoordinate2d(Longitude(- 90.0), Latitude(- 90.0)),
          GeoCoordinate2d(Longitude(- 45.1), Latitude(- 45.1))),
          "262172"),
      std::make_pair(GeoCoordinateBoundingBox2d(
          GeoCoordinate2d(Longitude(- 45.0), Latitude(- 90.0)),
          GeoCoordinate2d(Longitude(-  0.1), Latitude(- 45.1))),
          "262173"),
      std::make_pair(GeoCoordinateBoundingBox2d(
          GeoCoordinate2d(Longitude(+  0.0), Latitude(- 90.0)),
          GeoCoordinate2d(Longitude(+ 45.0), Latitude(- 45.1))),
          "262152"),
      std::make_pair(GeoCoordinateBoundingBox2d(
          GeoCoordinate2d(Longitude(+ 45.1), Latitude(- 90.0)),
          GeoCoordinate2d(Longitude(+ 90.0), Latitude(- 45.1))),
          "262153"),
      std::make_pair(GeoCoordinateBoundingBox2d(
          GeoCoordinate2d(Longitude(+ 90.1), Latitude(- 90.0)),
          GeoCoordinate2d(Longitude(+135.0), Latitude(- 45.1))),
          "262156"),
      std::make_pair(GeoCoordinateBoundingBox2d(
          GeoCoordinate2d(Longitude(+135.1), Latitude(- 90.0)),
          GeoCoordinate2d(Longitude(+180.0), Latitude(- 45.1))),
          "262157"),
      std::make_pair(GeoCoordinateBoundingBox2d(
          GeoCoordinate2d(Longitude(-180.0), Latitude(- 45.0)),
          GeoCoordinate2d(Longitude(-135.1), Latitude(-  0.1))),
          "262170"),
      std::make_pair(GeoCoordinateBoundingBox2d(
          GeoCoordinate2d(Longitude(-135.0), Latitude(- 45.0)),
          GeoCoordinate2d(Longitude(- 90.1), Latitude(-  0.1))),
          "262171"),
      std::make_pair(GeoCoordinateBoundingBox2d(
          GeoCoordinate2d(Longitude(- 90.0), Latitude(- 45.0)),
          GeoCoordinate2d(Longitude(- 45.1), Latitude(-  0.1))),
          "262174"),
      std::make_pair(GeoCoordinateBoundingBox2d(
          GeoCoordinate2d(Longitude(- 45.0), Latitude(- 45.0)),
          GeoCoordinate2d(Longitude(-  0.1), Latitude(-  0.1))),
          "262175"),
      std::make_pair(GeoCoordinateBoundingBox2d(
          GeoCoordinate2d(Longitude(+  0.0), Latitude(- 45.0)),
          GeoCoordinate2d(Longitude(+ 45.0), Latitude(-  0.1))),
          "262154"),
      std::make_pair(GeoCoordinateBoundingBox2d(
          GeoCoordinate2d(Longitude(+ 45.1), Latitude(- 45.0)),
          GeoCoordinate2d(Longitude(+ 90.0), Latitude(-  0.1))),
          "262155"),
      std::make_pair(GeoCoordinateBoundingBox2d(
          GeoCoordinate2d(Longitude(+ 90.1), Latitude(- 45.0)),
          GeoCoordinate2d(Longitude(+135.0), Latitude(-  0.1))),
          "262158"),
      std::make_pair(GeoCoordinateBoundingBox2d(
          GeoCoordinate2d(Longitude(+135.1), Latitude(- 45.0)),
          GeoCoordinate2d(Longitude(+180.0), Latitude(-  0.1))),
          "262159"),
      std::make_pair(GeoCoordinateBoundingBox2d(
          GeoCoordinate2d(Longitude(-180.0), Latitude(+  0.0)),
          GeoCoordinate2d(Longitude(-135.1), Latitude(+ 45.0))),
          "262160"),
      std::make_pair(GeoCoordinateBoundingBox2d(
          GeoCoordinate2d(Longitude(-135.0), Latitude(+  0.0)),
          GeoCoordinate2d(Longitude(- 90.1), Latitude(+ 45.0))),
          "262161"),
      std::make_pair(GeoCoordinateBoundingBox2d(
          GeoCoordinate2d(Longitude(- 90.0), Latitude(+  0.0)),
          GeoCoordinate2d(Longitude(- 45.1), Latitude(+ 45.0))),
          "262164"),
      std::make_pair(GeoCoordinateBoundingBox2d(
          GeoCoordinate2d(Longitude(- 45.0), Latitude(+  0.0)),
          GeoCoordinate2d(Longitude(-  0.1), Latitude(+ 45.0))),
          "262165"),
      std::make_pair(GeoCoordinateBoundingBox2d(
          GeoCoordinate2d(Longitude(+  0.0), Latitude(+  0.0)),
          GeoCoordinate2d(Longitude(+ 45.0), Latitude(+ 45.0))),
          "262144"),
      std::make_pair(GeoCoordinateBoundingBox2d(
          GeoCoordinate2d(Longitude(+ 45.1), Latitude(+  0.0)),
          GeoCoordinate2d(Longitude(+ 90.0), Latitude(+ 45.0))),
          "262145"),
      std::make_pair(GeoCoordinateBoundingBox2d(
          GeoCoordinate2d(Longitude(+ 90.1), Latitude(+  0.0)),
          GeoCoordinate2d(Longitude(+135.0), Latitude(+ 45.0))),
          "262148"),
      std::make_pair(GeoCoordinateBoundingBox2d(
          GeoCoordinate2d(Longitude(+135.1), Latitude(+  0.0)),
          GeoCoordinate2d(Longitude(+180.0), Latitude(+ 45.0))),
          "262149"),
      std::make_pair(GeoCoordinateBoundingBox2d(
          GeoCoordinate2d(Longitude(-180.0), Latitude(+ 45.1)),
          GeoCoordinate2d(Longitude(-135.1), Latitude(+ 90.0))),
          "262162"),
      std::make_pair(GeoCoordinateBoundingBox2d(
          GeoCoordinate2d(Longitude(-135.0), Latitude(+ 45.1)),
          GeoCoordinate2d(Longitude(- 90.1), Latitude(+ 90.0))),
          "262163"),
      std::make_pair(GeoCoordinateBoundingBox2d(
          GeoCoordinate2d(Longitude(- 90.0), Latitude(+ 45.1)),
          GeoCoordinate2d(Longitude(- 45.1), Latitude(+ 90.0))),
          "262166"),
      std::make_pair(GeoCoordinateBoundingBox2d(
          GeoCoordinate2d(Longitude(- 45.0), Latitude(+ 45.1)),
          GeoCoordinate2d(Longitude(-  0.1), Latitude(+ 90.0))),
          "262167"),
      std::make_pair(GeoCoordinateBoundingBox2d(
          GeoCoordinate2d(Longitude(+  0.0), Latitude(+ 45.1)),
          GeoCoordinate2d(Longitude(+ 45.0), Latitude(+ 90.0))),
          "262146"),
      std::make_pair(GeoCoordinateBoundingBox2d(
          GeoCoordinate2d(Longitude(+ 45.1), Latitude(+ 45.1)),
          GeoCoordinate2d(Longitude(+ 90.0), Latitude(+ 90.0))),
          "262147"),
      std::make_pair(GeoCoordinateBoundingBox2d(
          GeoCoordinate2d(Longitude(+ 90.1), Latitude(+ 45.1)),
          GeoCoordinate2d(Longitude(+135.0), Latitude(+ 90.0))),
          "262150"),
      std::make_pair(GeoCoordinateBoundingBox2d(
          GeoCoordinate2d(Longitude(+135.1), Latitude(+ 45.1)),
          GeoCoordinate2d(Longitude(+180.0), Latitude(+ 90.0))),
          "262151")}) {
      const auto &bbox = pair.first;
      GeoCoordinate2d ll(bbox.lower_left());
      GeoCoordinate2d lr(bbox.upper_right().get_longitude(),
        bbox.lower_left().get_latitude());
      GeoCoordinate2d ur(bbox.upper_right());
      GeoCoordinate2d ul(bbox.lower_left().get_longitude(),
        bbox.upper_right().get_latitude());
      QuadKey morton_key;
      morton_key = QuadKey::get_key_from_longitude_latitude_at_depth(
        Type::Morton, ll, depth);
      EXPECT_EQ(pair.second, morton_key.to_internal_string()) << "ll: " <<
        pair.second << " " << pair.first;
      morton_key = QuadKey::get_key_from_longitude_latitude_at_depth(
        Type::Morton, lr, depth);
      EXPECT_EQ(pair.second, morton_key.to_internal_string()) << "lr: " <<
        pair.second << " " << pair.first;
      morton_key = QuadKey::get_key_from_longitude_latitude_at_depth(
        Type::Morton, ur, depth);
      EXPECT_EQ(pair.second, morton_key.to_internal_string()) << "ur: " <<
        pair.second << " " << pair.first;
      morton_key = QuadKey::get_key_from_longitude_latitude_at_depth(
        Type::Morton, ul, depth);
      EXPECT_EQ(pair.second, morton_key.to_internal_string()) << "ul: " <<
        pair.second << " " << pair.first;
      GeoCoordinateBoundingBox2d actual;
      morton_key.get_geo_coordinate_bounds2d(actual);
      EXPECT_TRUE(ll.near(actual.lower_left(), 1)) <<
        "actual = " << actual.lower_left() << std::endl <<
        "ll     = " << ll;
      EXPECT_TRUE(ur.near(actual.upper_right(), 1)) <<
        "actual = " << actual.upper_right() << std::endl <<
        "ur     = " << ur;
    }
  }

  TEST(MORTONSYSTEM, get_keys_from_longitude_latitude_bounding_box)
  {
    for (const auto &data : {
      std::make_pair<GeoCoordinateBoundingBox2d, std::vector<QuadKey>>(
        GeoCoordinateBoundingBox2d(
          GeoCoordinate2d(Longitude(-180.0), Latitude(- 90.0)),
          GeoCoordinate2d(Longitude(-  0.1), Latitude(+ 90.0))),
        {
          QuadKey(Type::Morton, 0, 0, 0)
        }),
      std::make_pair<GeoCoordinateBoundingBox2d, std::vector<QuadKey>>(
        GeoCoordinateBoundingBox2d(
          GeoCoordinate2d(Longitude(+  0.0), Latitude(- 90.0)),
          GeoCoordinate2d(Longitude(+180.0), Latitude(+ 90.0))),
        {
          QuadKey(Type::Morton, 0, 1, 0)
        }),
      }) {
      std::vector<QuadKey> expected;
      expected = QuadKey::get_keys_from_longitude_latitude_bounding_box(
        Type::Morton, data.first, 0);
      EXPECT_EQ(data.second.size(), expected.size());
      for (const QuadKey &quad_key : data.second) {
        EXPECT_NE(std::find(data.second.begin(), data.second.end(),
          quad_key), data.second.end());
      }
    }
    for (const auto &data : {
      std::make_pair<GeoCoordinateBoundingBox2d, std::vector<QuadKey>>(
        GeoCoordinateBoundingBox2d(
          GeoCoordinate2d(Longitude(-180.0), Latitude(- 90.0)),
          GeoCoordinate2d(Longitude(-  0.1), Latitude(+ 90.0))),
        {
          QuadKey(Type::Morton, 0, 0, 1), QuadKey(Type::Morton, 0, 1, 1),
          QuadKey(Type::Morton, 1, 0, 1), QuadKey(Type::Morton, 1, 1, 1)
        }),
      std::make_pair<GeoCoordinateBoundingBox2d, std::vector<QuadKey>>(
        GeoCoordinateBoundingBox2d(
          GeoCoordinate2d(Longitude(+  0.0), Latitude(- 90.0)),
          GeoCoordinate2d(Longitude(+180.0), Latitude(+ 90.0))),
        {
          QuadKey(Type::Morton, 0, 2, 1), QuadKey(Type::Morton, 0, 3, 1),
          QuadKey(Type::Morton, 1, 2, 1), QuadKey(Type::Morton, 1, 3, 1),
        }),
      std::make_pair<GeoCoordinateBoundingBox2d, std::vector<QuadKey>>(
        GeoCoordinateBoundingBox2d(
          GeoCoordinate2d(Longitude(-180.0), Latitude(- 90.0)),
          GeoCoordinate2d(Longitude(-  0.1), Latitude(-  0.1))),
        {
          QuadKey(Type::Morton, 0, 0, 1), QuadKey(Type::Morton, 0, 1, 1),
        }),
      std::make_pair<GeoCoordinateBoundingBox2d, std::vector<QuadKey>>(
        GeoCoordinateBoundingBox2d(
          GeoCoordinate2d(Longitude(-180.0), Latitude(+  0.0)),
          GeoCoordinate2d(Longitude(-  0.1), Latitude(+ 90.0))),
        {
          QuadKey(Type::Morton, 1, 0, 1), QuadKey(Type::Morton, 1, 1, 1),
        }),
      std::make_pair<GeoCoordinateBoundingBox2d, std::vector<QuadKey>>(
        GeoCoordinateBoundingBox2d(
          GeoCoordinate2d(Longitude(+  0.0), Latitude(- 90.0)),
          GeoCoordinate2d(Longitude(+180.0), Latitude(-  0.1))),
        {
          QuadKey(Type::Morton, 0, 2, 1), QuadKey(Type::Morton, 0, 3, 1),
        }),
      std::make_pair<GeoCoordinateBoundingBox2d, std::vector<QuadKey>>(
        GeoCoordinateBoundingBox2d(
          GeoCoordinate2d(Longitude(+  0.0), Latitude(+  0.0)),
          GeoCoordinate2d(Longitude(+180.0), Latitude(+ 90.0))),
        {
          QuadKey(Type::Morton, 1, 2, 1), QuadKey(Type::Morton, 1, 3, 1),
        }),
      std::make_pair<GeoCoordinateBoundingBox2d, std::vector<QuadKey>>(
        GeoCoordinateBoundingBox2d(
          GeoCoordinate2d(Longitude(-180.0), Latitude(- 90.0)),
          GeoCoordinate2d(Longitude(- 90.1), Latitude(-  0.1))),
        {
          QuadKey(Type::Morton, 0, 0, 1),
        }),
      std::make_pair<GeoCoordinateBoundingBox2d, std::vector<QuadKey>>(
        GeoCoordinateBoundingBox2d(
          GeoCoordinate2d(Longitude(- 90.0), Latitude(- 90.0)),
          GeoCoordinate2d(Longitude(-  0.1), Latitude(-  0.1))),
        {
          QuadKey(Type::Morton, 0, 0, 1),
        }),
      std::make_pair<GeoCoordinateBoundingBox2d, std::vector<QuadKey>>(
        GeoCoordinateBoundingBox2d(
          GeoCoordinate2d(Longitude(+  0.0), Latitude(- 90.0)),
          GeoCoordinate2d(Longitude(+ 90.0), Latitude(-  0.1))),
        {
          QuadKey(Type::Morton, 0, 2, 1),
        }),
      std::make_pair<GeoCoordinateBoundingBox2d, std::vector<QuadKey>>(
        GeoCoordinateBoundingBox2d(
          GeoCoordinate2d(Longitude(+ 90.1), Latitude(- 90.0)),
          GeoCoordinate2d(Longitude(+180.0), Latitude(-  0.1))),
        {
          QuadKey(Type::Morton, 0, 3, 1),
        }),
      std::make_pair<GeoCoordinateBoundingBox2d, std::vector<QuadKey>>(
        GeoCoordinateBoundingBox2d(
          GeoCoordinate2d(Longitude(-180.0), Latitude(+  0.0)),
          GeoCoordinate2d(Longitude(- 90.1), Latitude(+ 90.0))),
        {
          QuadKey(Type::Morton, 1, 0, 1),
        }),
      std::make_pair<GeoCoordinateBoundingBox2d, std::vector<QuadKey>>(
        GeoCoordinateBoundingBox2d(
          GeoCoordinate2d(Longitude(- 90.0), Latitude(+  0.0)),
          GeoCoordinate2d(Longitude(-  0.1), Latitude(+ 90.0))),
        {
          QuadKey(Type::Morton, 1, 1, 1),
        }),
      std::make_pair<GeoCoordinateBoundingBox2d, std::vector<QuadKey>>(
        GeoCoordinateBoundingBox2d(
          GeoCoordinate2d(Longitude(+  0.0), Latitude(+  0.0)),
          GeoCoordinate2d(Longitude(+ 90.0), Latitude(+ 90.0))),
        {
          QuadKey(Type::Morton, 1, 2, 1),
        }),
      std::make_pair<GeoCoordinateBoundingBox2d, std::vector<QuadKey>>(
        GeoCoordinateBoundingBox2d(
          GeoCoordinate2d(Longitude(+ 90.1), Latitude(+  0.0)),
          GeoCoordinate2d(Longitude(+180.0), Latitude(+ 90.0))),
        {
          QuadKey(Type::Morton, 1, 3, 1),
        }),
      }) {
      std::vector<QuadKey> expected;
      expected = QuadKey::get_keys_from_longitude_latitude_bounding_box(
        Type::Morton, data.first, 1);
      EXPECT_EQ(data.second.size(), expected.size());
      for (const QuadKey &quad_key : data.second) {
        EXPECT_NE(std::find(data.second.begin(), data.second.end(),
          quad_key), data.second.end()) << quad_key;
      }
    }

    {
      auto data =
        std::make_pair<GeoCoordinateBoundingBox2d, std::vector<QuadKey>>
          (GeoCoordinateBoundingBox2d(
            GeoCoordinate2d(Longitude(-140.0), Latitude(- 48.0)),
            GeoCoordinate2d(Longitude(+ 10.0), Latitude(+ 39.0))),
        {
          QuadKey(Type::Morton, 0, 0, 2), QuadKey(Type::Morton, 0, 1, 2),
          QuadKey(Type::Morton, 0, 2, 2), QuadKey(Type::Morton, 0, 3, 2),
          QuadKey(Type::Morton, 0, 4, 2), QuadKey(Type::Morton, 1, 0, 2),
          QuadKey(Type::Morton, 1, 1, 2), QuadKey(Type::Morton, 1, 2, 2),
          QuadKey(Type::Morton, 1, 3, 2), QuadKey(Type::Morton, 1, 4, 2),
          QuadKey(Type::Morton, 2, 0, 2), QuadKey(Type::Morton, 2, 1, 2),
          QuadKey(Type::Morton, 2, 2, 2), QuadKey(Type::Morton, 2, 3, 2),
          QuadKey(Type::Morton, 2, 4, 2),
        });
      std::vector<QuadKey> expected;
      expected = QuadKey::get_keys_from_longitude_latitude_bounding_box(
        Type::Morton, data.first, 2);
      EXPECT_EQ(data.second.size(), expected.size());
      for (const QuadKey &quad_key : data.second) {
        EXPECT_NE(std::find(data.second.begin(), data.second.end(),
          quad_key), data.second.end()) << quad_key;
      }
    }
  }

  TEST(MORTONSYSTEM, selected_cities)
  {
    {
      auto data = std::make_pair(13, GeoCoordinate2d(
        Longitude(+  2.29450000000000),
        Latitude( + 48.85822200000000)));
      std::uint32_t tile = 8428778 | (1 << (
        static_cast<std::uint8_t>(data.first) + 16));
      std::stringstream ss;
      ss << tile;
      QuadKey morton_quad_key =
        QuadKey::get_key_from_longitude_latitude_at_depth(
          Type::Morton, data.second, static_cast<std::uint8_t>(data.first));
      EXPECT_EQ(ss.str(), morton_quad_key.to_internal_string());
    }
    {
      auto data = std::make_pair(13, GeoCoordinate2d(
        Longitude(- 74.04444400000000),
        Latitude( + 40.68916700000000)));
      std::uint32_t tile = 86924190 | (1 << (
        static_cast<std::uint8_t>(data.first) + 16));
      std::stringstream ss;
      ss << tile;
      QuadKey morton_quad_key =
        QuadKey::get_key_from_longitude_latitude_at_depth(
          Type::Morton, data.second, static_cast<std::uint8_t>(data.first));
      EXPECT_EQ(ss.str(), morton_quad_key.to_internal_string());
    }
    {
      auto data = std::make_pair(13, GeoCoordinate2d(
        Longitude(- 43.15744400000000),
        Latitude( - 22.94865800000000)));
      std::uint32_t tile = 130726287 | (1 << (
        static_cast<std::uint8_t>(data.first) + 16));
      std::stringstream ss;
      ss << tile;
      QuadKey morton_quad_key =
        QuadKey::get_key_from_longitude_latitude_at_depth(
          Type::Morton, data.second, static_cast<std::uint8_t>(data.first));
      EXPECT_EQ(ss.str(), morton_quad_key.to_internal_string());
    }
    {
      auto data = std::make_pair(13, GeoCoordinate2d(
        Longitude(+151.21527800000000),
        Latitude( - 33.85611100000000)));
      std::uint32_t tile = 63372939 | (1 << (
        static_cast<std::uint8_t>(data.first) + 16));
      std::stringstream ss;
      ss << tile;
      QuadKey morton_quad_key =
        QuadKey::get_key_from_longitude_latitude_at_depth(
          Type::Morton, data.second, static_cast<std::uint8_t>(data.first));
      EXPECT_EQ(ss.str(), morton_quad_key.to_internal_string());
    }
    {
      auto data = std::make_pair(13, GeoCoordinate2d(
        Longitude(+  0.00000000000000),
        Latitude( + 51.50300000000000)));
      std::uint32_t tile = 8521770 | (1 << (
        static_cast<std::uint8_t>(data.first) + 16));
      std::stringstream ss;
      ss << tile;
      QuadKey morton_quad_key =
        QuadKey::get_key_from_longitude_latitude_at_depth(
         Type::Morton, data.second, static_cast<std::uint8_t>(data.first));
      EXPECT_EQ(ss.str(), morton_quad_key.to_internal_string());
    }
    {
      auto data = std::make_pair(13, GeoCoordinate2d(
        Longitude(- 78.45000000000000),
        Latitude( +  0.00000000000000)));
      std::uint32_t tile = 84148305 | (1 << (
        static_cast<std::uint8_t>(data.first) + 16));
      std::stringstream ss;
      ss << tile;
      QuadKey morton_quad_key =
        QuadKey::get_key_from_longitude_latitude_at_depth(
          Type::Morton, data.second, static_cast<std::uint8_t>(data.first));
      EXPECT_EQ(ss.str(), morton_quad_key.to_internal_string());
    }
    {
      auto data = std::make_pair(10, GeoCoordinate2d(
        Longitude(+  2.29450000000000),
        Latitude( + 48.85822200000000)));
      std::uint32_t tile = 131699u | (1 << (16 +
        static_cast<std::uint8_t>(data.first)));
      std::stringstream ss;
      ss << tile;
      QuadKey morton_quad_key =
        QuadKey::get_key_from_longitude_latitude_at_depth(
          Type::Morton, data.second, static_cast<std::uint8_t>(data.first));
      EXPECT_EQ(ss.str(), morton_quad_key.to_internal_string());
    }
    {
      auto data = std::make_pair(10, GeoCoordinate2d(
        Longitude(- 74.04444400000000),
        Latitude( + 40.68916700000000)));
      std::uint32_t tile = 1358190u | (1 << (16 +
        static_cast<std::uint8_t>(data.first)));
      std::stringstream ss;
      ss << tile;
      QuadKey morton_quad_key =
        QuadKey::get_key_from_longitude_latitude_at_depth(
          Type::Morton, data.second, static_cast<std::uint8_t>(data.first));
      EXPECT_EQ(ss.str(), morton_quad_key.to_internal_string());
    }
    {
      auto data = std::make_pair(10, GeoCoordinate2d(
        Longitude(- 43.15744400000000),
        Latitude( - 22.94865800000000)));
      std::uint32_t tile = 2042598u | (1 << (16 +
        static_cast<std::uint8_t>(data.first)));
      std::stringstream ss;
      ss << tile;
      QuadKey morton_quad_key =
        QuadKey::get_key_from_longitude_latitude_at_depth(
          Type::Morton, data.second, static_cast<std::uint8_t>(data.first));
      EXPECT_EQ(ss.str(), morton_quad_key.to_internal_string());
    }
    {
      auto data = std::make_pair(10, GeoCoordinate2d(
        Longitude(+151.21527800000000),
        Latitude( - 33.85611100000000)));
      std::uint32_t tile = 990202u | (1 << (16 +
        static_cast<std::uint8_t>(data.first)));
      std::stringstream ss;
      ss << tile;
      QuadKey morton_quad_key =
        QuadKey::get_key_from_longitude_latitude_at_depth(
          Type::Morton, data.second, static_cast<std::uint8_t>(data.first));
      EXPECT_EQ(ss.str(), morton_quad_key.to_internal_string());
    }
    {
      auto data = std::make_pair(10, GeoCoordinate2d(
        Longitude(+  0.00000000000000),
        Latitude( + 51.50300000000000)));
      std::uint32_t tile = 133152u | (1 << (16 +
        static_cast<std::uint8_t>(data.first)));
      std::stringstream ss;
      ss << tile;
      QuadKey morton_quad_key =
        QuadKey::get_key_from_longitude_latitude_at_depth(
          Type::Morton, data.second, static_cast<std::uint8_t>(data.first));
      EXPECT_EQ(ss.str(), morton_quad_key.to_internal_string());
    }
    {
      auto data = std::make_pair(10, GeoCoordinate2d(
        Longitude(- 78.45000000000000),
        Latitude( +  0.00000000000000)));
      std::uint32_t tile = 1314817u | (1 << (16 +
        static_cast<std::uint8_t>(data.first)));
      std::stringstream ss;
      ss << tile;
      QuadKey morton_quad_key =
        QuadKey::get_key_from_longitude_latitude_at_depth(
          Type::Morton, data.second, static_cast<std::uint8_t>(data.first));
      EXPECT_EQ(ss.str(), morton_quad_key.to_internal_string());
    }
  }
}

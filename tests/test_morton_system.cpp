#include <gtest/gtest.h>

#include "quad_key/geo_coordinate2d.h"
#include "quad_key/quad_key.h"

#include <iostream>
#include <sstream>
#include <utility>

namespace quad_keys
{
  class test_morton_system : public ::testing::Test
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
      quad_key key(type::morton, 0, 1, 1);
      quad_key ancestor(type::morton, 0, 0, 0);
      EXPECT_EQ(ancestor, key.get_ancestor(1));
      EXPECT_EQ(key.get_parent(), key.get_ancestor(1));
    }
    {
      quad_key key(type::morton, 0, 0, 1);
      quad_key ancestor(type::morton, 0, 0, 0);
      EXPECT_EQ(ancestor, key.get_ancestor(1));
      EXPECT_EQ(key.get_parent(), key.get_ancestor(1));
    }
    {
      quad_key key(type::morton, 1, 1, 1);
      quad_key ancestor(type::morton, 0, 0, 0);
      EXPECT_EQ(ancestor, key.get_ancestor(1));
    }
    {
      quad_key key(type::morton, 1, 2, 1);
      quad_key ancestor(type::morton, 0, 1, 0);
      EXPECT_EQ(ancestor, key.get_ancestor(1));
    }
    {
      quad_key key(type::morton, 0, 3, 1);
      quad_key ancestor(type::morton, 0, 1, 0);
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
    std::vector<quad_key> test_keys;
    test_keys = quad_key(type::morton, 0, 0, 1).get_siblings();
    EXPECT_EQ(3u, test_keys.size());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      quad_key(type::morton, 1, 0, 1)), test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      quad_key(type::morton, 1, 1, 1)), test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      quad_key(type::morton, 0, 1, 1)), test_keys.end());
    test_keys = quad_key(type::morton, 1, 3, 1).get_siblings();
    EXPECT_EQ(3u, test_keys.size());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      quad_key(type::morton, 1, 2, 1)), test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      quad_key(type::morton, 0, 2, 1)), test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      quad_key(type::morton, 0, 3, 1)), test_keys.end());
  }

  TEST(MORTONSYSTEM, get_neighbors)
  {
    // Same as bing_system but just to be safe
    std::vector<quad_key> test_keys;
    test_keys = quad_key().get_neighbors();
    EXPECT_TRUE(test_keys.empty());
    test_keys.clear();

    test_keys = quad_key(type::morton, 0, 0, 2).get_neighbors();
    EXPECT_EQ(5u, test_keys.size());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      quad_key(type::morton, 0, 1, 2)), test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      quad_key(type::morton, 1, 1, 2)), test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      quad_key(type::morton, 1, 0, 2)), test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      quad_key(type::morton, 0, 7, 2)), test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      quad_key(type::morton, 1, 7, 2)), test_keys.end());
    test_keys.clear();

    test_keys = quad_key(type::morton, 0, 1, 2).get_neighbors();
    EXPECT_EQ(5u, test_keys.size());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      quad_key(type::morton, 0, 0, 2)), test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      quad_key(type::morton, 1, 0, 2)), test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      quad_key(type::morton, 1, 1, 2)), test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      quad_key(type::morton, 1, 2, 2)), test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      quad_key(type::morton, 0, 2, 2)), test_keys.end());
    test_keys.clear();

    test_keys = quad_key(type::morton, 0, 2, 2).get_neighbors();
    EXPECT_EQ(5u, test_keys.size());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      quad_key(type::morton, 0, 1, 2)), test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      quad_key(type::morton, 1, 1, 2)), test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      quad_key(type::morton, 1, 2, 2)), test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      quad_key(type::morton, 1, 3, 2)), test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      quad_key(type::morton, 0, 3, 2)), test_keys.end());
    test_keys.clear();

    test_keys = quad_key(type::morton, 0, 3, 2).get_neighbors();
    EXPECT_EQ(5u, test_keys.size());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      quad_key(type::morton, 0, 2, 2)), test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      quad_key(type::morton, 1, 2, 2)), test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      quad_key(type::morton, 1, 3, 2)), test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      quad_key(type::morton, 1, 4, 2)), test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      quad_key(type::morton, 0, 4, 2)), test_keys.end());
    test_keys.clear();

    test_keys = quad_key(type::morton, 0, 0, 2).get_neighbors();
    EXPECT_EQ(5u, test_keys.size());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      quad_key(type::morton, 0, 1, 2)), test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      quad_key(type::morton, 1, 1, 2)), test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      quad_key(type::morton, 1, 0, 2)), test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      quad_key(type::morton, 1, 7, 2)), test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      quad_key(type::morton, 0, 7, 2)), test_keys.end());
    test_keys.clear();

    test_keys = quad_key(type::morton, 3, 1, 2).get_neighbors();
    EXPECT_EQ(5u, test_keys.size());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      quad_key(type::morton, 3, 0, 2)), test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      quad_key(type::morton, 2, 0, 2)), test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      quad_key(type::morton, 2, 1, 2)), test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      quad_key(type::morton, 2, 2, 2)), test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      quad_key(type::morton, 3, 2, 2)), test_keys.end());
    test_keys.clear();

    test_keys = quad_key(type::morton, 3, 2, 2).get_neighbors();
    EXPECT_EQ(5u, test_keys.size());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      quad_key(type::morton, 3, 1, 2)), test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      quad_key(type::morton, 2, 1, 2)), test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      quad_key(type::morton, 2, 2, 2)), test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      quad_key(type::morton, 2, 3, 2)), test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      quad_key(type::morton, 3, 3, 2)), test_keys.end());
    test_keys.clear();

    test_keys = quad_key(type::morton, 3, 3, 2).get_neighbors();
    EXPECT_EQ(5u, test_keys.size());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      quad_key(type::morton, 3, 2, 2)), test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      quad_key(type::morton, 2, 2, 2)), test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      quad_key(type::morton, 2, 3, 2)), test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      quad_key(type::morton, 2, 4, 2)), test_keys.end());
    EXPECT_NE(std::find(test_keys.begin(), test_keys.end(),
      quad_key(type::morton, 3, 4, 2)), test_keys.end());
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

    test_keys = quad_key(type::morton, 0, 0, 0).get_neighbors();
    EXPECT_EQ(0u, test_keys.size());
  }

  TEST(MORTONSYSTEM, from_string_to_string)
  {
    // X ==> Unused
    // O ==> Used but never set
    // (0,1) ==> Binary digits
    quad_key qk(type::morton, 0, 0, 0);
    std::string fmt = qk.to_internal_string();
    EXPECT_EQ("65537", fmt); // XXXX XXXX XXXX XXX1 XXXX XXXX XXXX XXO1
    class quad_key quad_key_back = quad_key::from_internal_string(type::morton, fmt);
    EXPECT_EQ(qk, quad_key_back);

    qk = quad_key(type::morton, 0, 1, 0);
    fmt = qk.to_internal_string();
    EXPECT_EQ("65536", fmt); // XXXX XXXX XXXX XXX1 XXXX XXXX XXXX XXO0
    quad_key_back = quad_key::from_internal_string(type::morton, fmt);
    EXPECT_EQ(qk, quad_key_back);

    qk = quad_key(type::morton, 0, 0, 1);
    fmt = qk.to_internal_string();
    EXPECT_EQ("131078", fmt); // XXXX XXXX XXXX XX1X XXXX XXXX XXXX O110
    quad_key_back = quad_key::from_internal_string(type::morton, fmt);
    EXPECT_EQ(qk, quad_key_back);

    qk = quad_key(type::morton, 0, 1, 1);
    fmt = qk.to_internal_string();
    EXPECT_EQ("131079", fmt); // XXXX XXXX XXXX XX1O OOOO OOOO OOOO O111
    quad_key_back = quad_key::from_internal_string(type::morton, fmt);
    EXPECT_EQ(qk, quad_key_back);

    qk = quad_key(type::morton, 0, 2, 1);
    fmt = qk.to_internal_string();
    EXPECT_EQ("131074", fmt); // XXXX XXXX XXXX XX1X XXXX XXXX XXXX O010
    quad_key_back = quad_key::from_internal_string(type::morton, fmt);
    EXPECT_EQ(qk, quad_key_back);

    qk = quad_key(type::morton, 0, 3, 1);
    fmt = qk.to_internal_string();
    EXPECT_EQ("131075", fmt); // XXXX XXXX XXXX XX1X XXXX XXXX XXXX O011
    quad_key_back = quad_key::from_internal_string(type::morton, fmt);
    EXPECT_EQ(qk, quad_key_back);

    qk = quad_key(type::morton, 1, 0, 1);
    fmt = qk.to_internal_string();
    EXPECT_EQ("131076", fmt); // XXXX XXXX XXXX XX1X XXXX XXXX XXXX O100
    quad_key_back = quad_key::from_internal_string(type::morton, fmt);
    EXPECT_EQ(qk, quad_key_back);

    qk = quad_key(type::morton, 1, 1, 1);
    fmt = qk.to_internal_string();
    EXPECT_EQ("131077", fmt); // XXXX XXXX XXXX XX1X XXXX XXXX XXXX O101
    quad_key_back = quad_key::from_internal_string(type::morton, fmt);
    EXPECT_EQ(qk, quad_key_back);

    qk = quad_key(type::morton, 1, 2, 1);
    fmt = qk.to_internal_string();
    EXPECT_EQ("131072", fmt); // XXXX XXXX XXXX XX1X XXXX XXXX XXXX O000
    quad_key_back = quad_key::from_internal_string(type::morton, fmt);
    EXPECT_EQ(qk, quad_key_back);

    qk = quad_key(type::morton, 1, 3, 1);
    fmt = qk.to_internal_string();
    EXPECT_EQ("131073", fmt); // XXXX XXXX XXXX XX1X XXXX XXXX XXXX O001
    quad_key_back = quad_key::from_internal_string(type::morton, fmt);
    EXPECT_EQ(qk, quad_key_back);

    qk = quad_key(type::morton, 0, 0, 2);
    fmt = qk.to_internal_string();
    EXPECT_EQ("262168", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO1 1000
    quad_key_back = quad_key::from_internal_string(type::morton, fmt);
    EXPECT_EQ(qk, quad_key_back);

    qk = quad_key(type::morton, 0, 1, 2);
    fmt = qk.to_internal_string();
    EXPECT_EQ("262169", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO1 1001
    quad_key_back = quad_key::from_internal_string(type::morton, fmt);
    EXPECT_EQ(qk, quad_key_back);

    qk = quad_key(type::morton, 0, 2, 2);
    fmt = qk.to_internal_string();
    EXPECT_EQ("262172", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO1 1100
    quad_key_back = quad_key::from_internal_string(type::morton, fmt);
    EXPECT_EQ(qk, quad_key_back);

    qk = quad_key(type::morton, 0, 3, 2);
    fmt = qk.to_internal_string();
    EXPECT_EQ("262173", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO1 1101
    quad_key_back = quad_key::from_internal_string(type::morton, fmt);
    EXPECT_EQ(qk, quad_key_back);

    qk = quad_key(type::morton, 0, 4, 2);
    fmt = qk.to_internal_string();
    EXPECT_EQ("262152", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO0 1000
    quad_key_back = quad_key::from_internal_string(type::morton, fmt);
    EXPECT_EQ(qk, quad_key_back);

    qk = quad_key(type::morton, 0, 5, 2);
    fmt = qk.to_internal_string();
    EXPECT_EQ("262153", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO0 1001
    quad_key_back = quad_key::from_internal_string(type::morton, fmt);
    EXPECT_EQ(qk, quad_key_back);

    qk = quad_key(type::morton, 0, 6, 2);
    fmt = qk.to_internal_string();
    EXPECT_EQ("262156", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO0 1100
    quad_key_back = quad_key::from_internal_string(type::morton, fmt);
    EXPECT_EQ(qk, quad_key_back);

    qk = quad_key(type::morton, 0, 7, 2);
    fmt = qk.to_internal_string();
    EXPECT_EQ("262157", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO0 1101
    quad_key_back = quad_key::from_internal_string(type::morton, fmt);
    EXPECT_EQ(qk, quad_key_back);

    qk = quad_key(type::morton, 1, 0, 2);
    fmt = qk.to_internal_string();
    EXPECT_EQ("262170", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO1 1010
    quad_key_back = quad_key::from_internal_string(type::morton, fmt);
    EXPECT_EQ(qk, quad_key_back);

    qk = quad_key(type::morton, 1, 1, 2);
    fmt = qk.to_internal_string();
    EXPECT_EQ("262171", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO1 1011
    quad_key_back = quad_key::from_internal_string(type::morton, fmt);
    EXPECT_EQ(qk, quad_key_back);

    qk = quad_key(type::morton, 1, 2, 2);
    fmt = qk.to_internal_string();
    EXPECT_EQ("262174", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO1 1110
    quad_key_back = quad_key::from_internal_string(type::morton, fmt);
    EXPECT_EQ(qk, quad_key_back);

    qk = quad_key(type::morton, 1, 3, 2);
    fmt = qk.to_internal_string();
    EXPECT_EQ("262175", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO1 1111
    quad_key_back = quad_key::from_internal_string(type::morton, fmt);
    EXPECT_EQ(qk, quad_key_back);

    qk = quad_key(type::morton, 1, 4, 2);
    fmt = qk.to_internal_string();
    EXPECT_EQ("262154", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO0 1010
    quad_key_back = quad_key::from_internal_string(type::morton, fmt);
    EXPECT_EQ(qk, quad_key_back);

    qk = quad_key(type::morton, 1, 5, 2);
    fmt = qk.to_internal_string();
    EXPECT_EQ("262155", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO0 1011
    quad_key_back = quad_key::from_internal_string(type::morton, fmt);
    EXPECT_EQ(qk, quad_key_back);

    qk = quad_key(type::morton, 1, 6, 2);
    fmt = qk.to_internal_string();
    EXPECT_EQ("262158", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO0 1110
    quad_key_back = quad_key::from_internal_string(type::morton, fmt);
    EXPECT_EQ(qk, quad_key_back);

    qk = quad_key(type::morton, 1, 7, 2);
    fmt = qk.to_internal_string();
    EXPECT_EQ("262159", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO0 1111
    quad_key_back = quad_key::from_internal_string(type::morton, fmt);
    EXPECT_EQ(qk, quad_key_back);

    qk = quad_key(type::morton, 2, 0, 2);
    fmt = qk.to_internal_string();
    EXPECT_EQ("262160", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO1 0000
    quad_key_back = quad_key::from_internal_string(type::morton, fmt);
    EXPECT_EQ(qk, quad_key_back);

    qk = quad_key(type::morton, 2, 1, 2);
    fmt = qk.to_internal_string();
    EXPECT_EQ("262161", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO1 0001
    quad_key_back = quad_key::from_internal_string(type::morton, fmt);
    EXPECT_EQ(qk, quad_key_back);

    qk = quad_key(type::morton, 2, 2, 2);
    fmt = qk.to_internal_string();
    EXPECT_EQ("262164", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO1 0100
    quad_key_back = quad_key::from_internal_string(type::morton, fmt);
    EXPECT_EQ(qk, quad_key_back);

    qk = quad_key(type::morton, 2, 3, 2);
    fmt = qk.to_internal_string();
    EXPECT_EQ("262165", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO1 0101
    quad_key_back = quad_key::from_internal_string(type::morton, fmt);
    EXPECT_EQ(qk, quad_key_back);

    qk = quad_key(type::morton, 2, 4, 2);
    fmt = qk.to_internal_string();
    EXPECT_EQ("262144", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO0 0000
    quad_key_back = quad_key::from_internal_string(type::morton, fmt);
    EXPECT_EQ(qk, quad_key_back);

    qk = quad_key(type::morton, 2, 5, 2);
    fmt = qk.to_internal_string();
    EXPECT_EQ("262145", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO0 0001
    quad_key_back = quad_key::from_internal_string(type::morton, fmt);
    EXPECT_EQ(qk, quad_key_back);

    qk = quad_key(type::morton, 2, 6, 2);
    fmt = qk.to_internal_string();
    EXPECT_EQ("262148", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO0 0100
    quad_key_back = quad_key::from_internal_string(type::morton, fmt);
    EXPECT_EQ(qk, quad_key_back);

    qk = quad_key(type::morton, 2, 7, 2);
    fmt = qk.to_internal_string();
    EXPECT_EQ("262149", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO0 0101
    quad_key_back = quad_key::from_internal_string(type::morton, fmt);
    EXPECT_EQ(qk, quad_key_back);

    qk = quad_key(type::morton, 3, 0, 2);
    fmt = qk.to_internal_string();
    EXPECT_EQ("262162", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO1 0010
    quad_key_back = quad_key::from_internal_string(type::morton, fmt);
    EXPECT_EQ(qk, quad_key_back);

    qk = quad_key(type::morton, 3, 1, 2);
    fmt = qk.to_internal_string();
    EXPECT_EQ("262163", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO1 0011
    quad_key_back = quad_key::from_internal_string(type::morton, fmt);
    EXPECT_EQ(qk, quad_key_back);

    qk = quad_key(type::morton, 3, 2, 2);
    fmt = qk.to_internal_string();
    EXPECT_EQ("262166", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO1 0110
    quad_key_back = quad_key::from_internal_string(type::morton, fmt);
    EXPECT_EQ(qk, quad_key_back);

    qk = quad_key(type::morton, 3, 3, 2);
    fmt = qk.to_internal_string();
    EXPECT_EQ("262167", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO1 0111
    quad_key_back = quad_key::from_internal_string(type::morton, fmt);
    EXPECT_EQ(qk, quad_key_back);

    qk = quad_key(type::morton, 3, 4, 2);
    fmt = qk.to_internal_string();
    EXPECT_EQ("262146", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO0 0010
    quad_key_back = quad_key::from_internal_string(type::morton, fmt);
    EXPECT_EQ(qk, quad_key_back);

    qk = quad_key(type::morton, 3, 5, 2);
    fmt = qk.to_internal_string();
    EXPECT_EQ("262147", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO0 0011
    quad_key_back = quad_key::from_internal_string(type::morton, fmt);
    EXPECT_EQ(qk, quad_key_back);

    qk = quad_key(type::morton, 3, 6, 2);
    fmt = qk.to_internal_string();
    EXPECT_EQ("262150", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO0 0110
    quad_key_back = quad_key::from_internal_string(type::morton, fmt);
    EXPECT_EQ(qk, quad_key_back);

    qk = quad_key(type::morton, 3, 7, 2);
    fmt = qk.to_internal_string();
    EXPECT_EQ("262151", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO0 0111
    quad_key_back = quad_key::from_internal_string(type::morton, fmt);
    EXPECT_EQ(qk, quad_key_back);
  }

  TEST(MORTONSYSTEM, get_key_from_longitude_latitude_at_depth_to_bounds)
  {
    geo_coordinate2d coords;
    std::uint8_t depth = 0;
    { // West
      quad_key morton_key;
      coords = geo_coordinate2d(longitude(-0.1), latitude(0.0));
      morton_key = quad_key::get_key_from_longitude_latitude_at_depth(
        type::morton, coords, depth);
      EXPECT_EQ("65537", morton_key.to_internal_string());
      coords = geo_coordinate2d(longitude(-180.0), latitude(90.0));
      morton_key = quad_key::get_key_from_longitude_latitude_at_depth(
        type::morton, coords, depth);
      EXPECT_EQ("65537", morton_key.to_internal_string());
      coords = geo_coordinate2d(longitude(-180.0), latitude(-90.0));
      morton_key = quad_key::get_key_from_longitude_latitude_at_depth(
        type::morton, coords, depth);
      EXPECT_EQ("65537", morton_key.to_internal_string());
      geo_coordinate_bounding_box2d actual;
      morton_key.get_geo_coordinate_bounds2d(actual);
      EXPECT_TRUE(geo_coordinate2d(longitude(-180.0),
        latitude(- 90.0)).near(actual.lower_left(), 1)) <<
        "actual = " << actual.lower_left();
      EXPECT_TRUE(geo_coordinate2d(longitude(-  0.1),
        latitude(+ 90.0)).near(actual.upper_right(), 1)) <<
        "actual = " << actual.upper_right();
    }
    { // East
      quad_key morton_key;
      coords = geo_coordinate2d(longitude(0.0), latitude(0.0));
      morton_key = quad_key::get_key_from_longitude_latitude_at_depth(
        type::morton, coords, depth);
      EXPECT_EQ("65536", morton_key.to_internal_string());
      coords = geo_coordinate2d(longitude(180.0), latitude(-90.0));
      morton_key = quad_key::get_key_from_longitude_latitude_at_depth(
        type::morton, coords, depth);
      EXPECT_EQ("65536", morton_key.to_internal_string());
      coords = geo_coordinate2d(longitude(180.0), latitude(90.0));
      morton_key = quad_key::get_key_from_longitude_latitude_at_depth(
        type::morton, coords, depth);
      EXPECT_EQ("65536", morton_key.to_internal_string());
      geo_coordinate_bounding_box2d actual;
      morton_key.get_geo_coordinate_bounds2d(actual);
      EXPECT_TRUE(geo_coordinate2d(longitude(+  0.0),
        latitude(- 90.0)).near(actual.lower_left(), 1)) <<
        "actual = " << actual.lower_left();
      EXPECT_TRUE(geo_coordinate2d(longitude(+180.0),
        latitude(+ 90.0)).near(actual.upper_right(), 1)) <<
        "actual = " << actual.upper_right();
    }
    depth = 1;
    { // 0x6
      quad_key morton_key;
      coords = geo_coordinate2d(longitude(-180.0), latitude(-0.1));
      morton_key = quad_key::get_key_from_longitude_latitude_at_depth(
        type::morton, coords, depth);
      EXPECT_EQ("131078", morton_key.to_internal_string());
      coords = geo_coordinate2d(longitude(-180.0), latitude(-90.0));
      morton_key = quad_key::get_key_from_longitude_latitude_at_depth(
        type::morton, coords, depth);
      EXPECT_EQ("131078", morton_key.to_internal_string());
      coords = geo_coordinate2d(longitude(-90.1), latitude(-90.0));
      morton_key = quad_key::get_key_from_longitude_latitude_at_depth(
        type::morton, coords, depth);
      EXPECT_EQ("131078", morton_key.to_internal_string());
      coords = geo_coordinate2d(longitude(-90.1), latitude(-0.1));
      morton_key = quad_key::get_key_from_longitude_latitude_at_depth(
        type::morton, coords, depth);
      EXPECT_EQ("131078", morton_key.to_internal_string());
    }
    { // 0x7
      quad_key morton_key;
      coords = geo_coordinate2d(longitude(-90.0), latitude(-0.1));
      morton_key = quad_key::get_key_from_longitude_latitude_at_depth(
        type::morton, coords, depth);
      EXPECT_EQ("131079", morton_key.to_internal_string());
      coords = geo_coordinate2d(longitude(-90.0), latitude(-90.0));
      morton_key = quad_key::get_key_from_longitude_latitude_at_depth(
        type::morton, coords, depth);
      EXPECT_EQ("131079", morton_key.to_internal_string());
      coords = geo_coordinate2d(longitude(-0.1), latitude(-90.0));
      morton_key = quad_key::get_key_from_longitude_latitude_at_depth(
        type::morton, coords, depth);
      EXPECT_EQ("131079", morton_key.to_internal_string());
      coords = geo_coordinate2d(longitude(-0.1), latitude(-0.1));
      morton_key = quad_key::get_key_from_longitude_latitude_at_depth(
        type::morton, coords, depth);
      EXPECT_EQ("131079", morton_key.to_internal_string());
    }
    { // 0x2
      quad_key morton_key;
      coords = geo_coordinate2d(longitude(0.0), latitude(-0.1));
      morton_key = quad_key::get_key_from_longitude_latitude_at_depth(
        type::morton, coords, depth);
      EXPECT_EQ("131074", morton_key.to_internal_string());
      coords = geo_coordinate2d(longitude(0.0), latitude(-90.0));
      morton_key = quad_key::get_key_from_longitude_latitude_at_depth(
        type::morton, coords, depth);
      EXPECT_EQ("131074", morton_key.to_internal_string());
      coords = geo_coordinate2d(longitude(90.0), latitude(-90.0));
      morton_key = quad_key::get_key_from_longitude_latitude_at_depth(
        type::morton, coords, depth);
      EXPECT_EQ("131074", morton_key.to_internal_string());
      coords = geo_coordinate2d(longitude(90.0), latitude(-0.1));
      morton_key = quad_key::get_key_from_longitude_latitude_at_depth(
        type::morton, coords, depth);
      EXPECT_EQ("131074", morton_key.to_internal_string());
    }
    { // 0x3
      quad_key morton_key;
      coords = geo_coordinate2d(longitude(90.1), latitude(-0.1));
      morton_key = quad_key::get_key_from_longitude_latitude_at_depth(
        type::morton, coords, depth);
      EXPECT_EQ("131075", morton_key.to_internal_string());
      coords = geo_coordinate2d(longitude(90.1), latitude(-90.0));
      morton_key = quad_key::get_key_from_longitude_latitude_at_depth(
        type::morton, coords, depth);
      EXPECT_EQ("131075", morton_key.to_internal_string());
      coords = geo_coordinate2d(longitude(180.0), latitude(-90.0));
      morton_key = quad_key::get_key_from_longitude_latitude_at_depth(
        type::morton, coords, depth);
      EXPECT_EQ("131075", morton_key.to_internal_string());
      coords = geo_coordinate2d(longitude(180.0), latitude(-0.1));
      morton_key = quad_key::get_key_from_longitude_latitude_at_depth(
        type::morton, coords, depth);
      EXPECT_EQ("131075", morton_key.to_internal_string());
    }
    { // 0x4
      quad_key morton_key;
      coords = geo_coordinate2d(longitude(-180.0), latitude(90.0));
      morton_key = quad_key::get_key_from_longitude_latitude_at_depth(
          type::morton, coords, depth);
      EXPECT_EQ("131076", morton_key.to_internal_string());
      coords = geo_coordinate2d(longitude(-180.0), latitude(0.0));
      morton_key = quad_key::get_key_from_longitude_latitude_at_depth(
          type::morton, coords, depth);
      EXPECT_EQ("131076", morton_key.to_internal_string());
      coords = geo_coordinate2d(longitude(-90.1), latitude(0.0));
      morton_key = quad_key::get_key_from_longitude_latitude_at_depth(
          type::morton, coords, depth);
      EXPECT_EQ("131076", morton_key.to_internal_string());
      coords = geo_coordinate2d(longitude(-90.1), latitude(90.0));
      morton_key = quad_key::get_key_from_longitude_latitude_at_depth(
          type::morton, coords, depth);
      EXPECT_EQ("131076", morton_key.to_internal_string());
    }
    { // 0x5
      quad_key morton_key;
      coords = geo_coordinate2d(longitude(-90.0), latitude(90.0));
      morton_key = quad_key::get_key_from_longitude_latitude_at_depth(
        type::morton, coords, depth);
      EXPECT_EQ("131077", morton_key.to_internal_string());
      coords = geo_coordinate2d(longitude(-90.0), latitude(0.0));
      morton_key = quad_key::get_key_from_longitude_latitude_at_depth(
        type::morton, coords, depth);
      EXPECT_EQ("131077", morton_key.to_internal_string());
      coords = geo_coordinate2d(longitude(-0.1), latitude(0.0));
      morton_key = quad_key::get_key_from_longitude_latitude_at_depth(
        type::morton, coords, depth);
      EXPECT_EQ("131077", morton_key.to_internal_string());
      coords = geo_coordinate2d(longitude(-0.1), latitude(90.0));
      morton_key = quad_key::get_key_from_longitude_latitude_at_depth(
        type::morton, coords, depth);
      EXPECT_EQ("131077", morton_key.to_internal_string());
    }
    { // 0x0
      quad_key morton_key;
      coords = geo_coordinate2d(longitude(0.0), latitude(90.0));
      morton_key = quad_key::get_key_from_longitude_latitude_at_depth(
        type::morton, coords, depth);
      EXPECT_EQ("131072", morton_key.to_internal_string());
      coords = geo_coordinate2d(longitude(0.0), latitude(0.0));
      morton_key = quad_key::get_key_from_longitude_latitude_at_depth(
        type::morton, coords, depth);
      EXPECT_EQ("131072", morton_key.to_internal_string());
      coords = geo_coordinate2d(longitude(90.0), latitude(0.0));
      morton_key = quad_key::get_key_from_longitude_latitude_at_depth(
        type::morton, coords, depth);
      EXPECT_EQ("131072", morton_key.to_internal_string());
      coords = geo_coordinate2d(longitude(90.0), latitude(90.0));
      morton_key = quad_key::get_key_from_longitude_latitude_at_depth(
        type::morton, coords, depth);
      EXPECT_EQ("131072", morton_key.to_internal_string());
    }
    { // 0x1
      quad_key morton_key;
      coords = geo_coordinate2d(longitude(90.1), latitude(90.0));
      morton_key = quad_key::get_key_from_longitude_latitude_at_depth(
        type::morton, coords, depth);
      EXPECT_EQ("131073", morton_key.to_internal_string());
      coords = geo_coordinate2d(longitude(90.1), latitude(0.0));
      morton_key = quad_key::get_key_from_longitude_latitude_at_depth(
        type::morton, coords, depth);
      EXPECT_EQ("131073", morton_key.to_internal_string());
      coords = geo_coordinate2d(longitude(180.0), latitude(0.0));
      morton_key = quad_key::get_key_from_longitude_latitude_at_depth(
        type::morton, coords, depth);
      EXPECT_EQ("131073", morton_key.to_internal_string());
      coords = geo_coordinate2d(longitude(180.0), latitude(90.0));
      morton_key = quad_key::get_key_from_longitude_latitude_at_depth(
        type::morton, coords, depth);
      EXPECT_EQ("131073", morton_key.to_internal_string());
    }
    depth = 2;
    for (const auto &pair : {
      std::make_pair(geo_coordinate_bounding_box2d(
          geo_coordinate2d(longitude(-180.0), latitude(- 90.0)),
          geo_coordinate2d(longitude(-135.1), latitude(- 45.1))),
          "262168"),
      std::make_pair(geo_coordinate_bounding_box2d(
          geo_coordinate2d(longitude(-135.0), latitude(- 90.0)),
          geo_coordinate2d(longitude(- 90.1), latitude(- 45.1))),
          "262169"),
      std::make_pair(geo_coordinate_bounding_box2d(
          geo_coordinate2d(longitude(- 90.0), latitude(- 90.0)),
          geo_coordinate2d(longitude(- 45.1), latitude(- 45.1))),
          "262172"),
      std::make_pair(geo_coordinate_bounding_box2d(
          geo_coordinate2d(longitude(- 45.0), latitude(- 90.0)),
          geo_coordinate2d(longitude(-  0.1), latitude(- 45.1))),
          "262173"),
      std::make_pair(geo_coordinate_bounding_box2d(
          geo_coordinate2d(longitude(+  0.0), latitude(- 90.0)),
          geo_coordinate2d(longitude(+ 45.0), latitude(- 45.1))),
          "262152"),
      std::make_pair(geo_coordinate_bounding_box2d(
          geo_coordinate2d(longitude(+ 45.1), latitude(- 90.0)),
          geo_coordinate2d(longitude(+ 90.0), latitude(- 45.1))),
          "262153"),
      std::make_pair(geo_coordinate_bounding_box2d(
          geo_coordinate2d(longitude(+ 90.1), latitude(- 90.0)),
          geo_coordinate2d(longitude(+135.0), latitude(- 45.1))),
          "262156"),
      std::make_pair(geo_coordinate_bounding_box2d(
          geo_coordinate2d(longitude(+135.1), latitude(- 90.0)),
          geo_coordinate2d(longitude(+180.0), latitude(- 45.1))),
          "262157"),
      std::make_pair(geo_coordinate_bounding_box2d(
          geo_coordinate2d(longitude(-180.0), latitude(- 45.0)),
          geo_coordinate2d(longitude(-135.1), latitude(-  0.1))),
          "262170"),
      std::make_pair(geo_coordinate_bounding_box2d(
          geo_coordinate2d(longitude(-135.0), latitude(- 45.0)),
          geo_coordinate2d(longitude(- 90.1), latitude(-  0.1))),
          "262171"),
      std::make_pair(geo_coordinate_bounding_box2d(
          geo_coordinate2d(longitude(- 90.0), latitude(- 45.0)),
          geo_coordinate2d(longitude(- 45.1), latitude(-  0.1))),
          "262174"),
      std::make_pair(geo_coordinate_bounding_box2d(
          geo_coordinate2d(longitude(- 45.0), latitude(- 45.0)),
          geo_coordinate2d(longitude(-  0.1), latitude(-  0.1))),
          "262175"),
      std::make_pair(geo_coordinate_bounding_box2d(
          geo_coordinate2d(longitude(+  0.0), latitude(- 45.0)),
          geo_coordinate2d(longitude(+ 45.0), latitude(-  0.1))),
          "262154"),
      std::make_pair(geo_coordinate_bounding_box2d(
          geo_coordinate2d(longitude(+ 45.1), latitude(- 45.0)),
          geo_coordinate2d(longitude(+ 90.0), latitude(-  0.1))),
          "262155"),
      std::make_pair(geo_coordinate_bounding_box2d(
          geo_coordinate2d(longitude(+ 90.1), latitude(- 45.0)),
          geo_coordinate2d(longitude(+135.0), latitude(-  0.1))),
          "262158"),
      std::make_pair(geo_coordinate_bounding_box2d(
          geo_coordinate2d(longitude(+135.1), latitude(- 45.0)),
          geo_coordinate2d(longitude(+180.0), latitude(-  0.1))),
          "262159"),
      std::make_pair(geo_coordinate_bounding_box2d(
          geo_coordinate2d(longitude(-180.0), latitude(+  0.0)),
          geo_coordinate2d(longitude(-135.1), latitude(+ 45.0))),
          "262160"),
      std::make_pair(geo_coordinate_bounding_box2d(
          geo_coordinate2d(longitude(-135.0), latitude(+  0.0)),
          geo_coordinate2d(longitude(- 90.1), latitude(+ 45.0))),
          "262161"),
      std::make_pair(geo_coordinate_bounding_box2d(
          geo_coordinate2d(longitude(- 90.0), latitude(+  0.0)),
          geo_coordinate2d(longitude(- 45.1), latitude(+ 45.0))),
          "262164"),
      std::make_pair(geo_coordinate_bounding_box2d(
          geo_coordinate2d(longitude(- 45.0), latitude(+  0.0)),
          geo_coordinate2d(longitude(-  0.1), latitude(+ 45.0))),
          "262165"),
      std::make_pair(geo_coordinate_bounding_box2d(
          geo_coordinate2d(longitude(+  0.0), latitude(+  0.0)),
          geo_coordinate2d(longitude(+ 45.0), latitude(+ 45.0))),
          "262144"),
      std::make_pair(geo_coordinate_bounding_box2d(
          geo_coordinate2d(longitude(+ 45.1), latitude(+  0.0)),
          geo_coordinate2d(longitude(+ 90.0), latitude(+ 45.0))),
          "262145"),
      std::make_pair(geo_coordinate_bounding_box2d(
          geo_coordinate2d(longitude(+ 90.1), latitude(+  0.0)),
          geo_coordinate2d(longitude(+135.0), latitude(+ 45.0))),
          "262148"),
      std::make_pair(geo_coordinate_bounding_box2d(
          geo_coordinate2d(longitude(+135.1), latitude(+  0.0)),
          geo_coordinate2d(longitude(+180.0), latitude(+ 45.0))),
          "262149"),
      std::make_pair(geo_coordinate_bounding_box2d(
          geo_coordinate2d(longitude(-180.0), latitude(+ 45.1)),
          geo_coordinate2d(longitude(-135.1), latitude(+ 90.0))),
          "262162"),
      std::make_pair(geo_coordinate_bounding_box2d(
          geo_coordinate2d(longitude(-135.0), latitude(+ 45.1)),
          geo_coordinate2d(longitude(- 90.1), latitude(+ 90.0))),
          "262163"),
      std::make_pair(geo_coordinate_bounding_box2d(
          geo_coordinate2d(longitude(- 90.0), latitude(+ 45.1)),
          geo_coordinate2d(longitude(- 45.1), latitude(+ 90.0))),
          "262166"),
      std::make_pair(geo_coordinate_bounding_box2d(
          geo_coordinate2d(longitude(- 45.0), latitude(+ 45.1)),
          geo_coordinate2d(longitude(-  0.1), latitude(+ 90.0))),
          "262167"),
      std::make_pair(geo_coordinate_bounding_box2d(
          geo_coordinate2d(longitude(+  0.0), latitude(+ 45.1)),
          geo_coordinate2d(longitude(+ 45.0), latitude(+ 90.0))),
          "262146"),
      std::make_pair(geo_coordinate_bounding_box2d(
          geo_coordinate2d(longitude(+ 45.1), latitude(+ 45.1)),
          geo_coordinate2d(longitude(+ 90.0), latitude(+ 90.0))),
          "262147"),
      std::make_pair(geo_coordinate_bounding_box2d(
          geo_coordinate2d(longitude(+ 90.1), latitude(+ 45.1)),
          geo_coordinate2d(longitude(+135.0), latitude(+ 90.0))),
          "262150"),
      std::make_pair(geo_coordinate_bounding_box2d(
          geo_coordinate2d(longitude(+135.1), latitude(+ 45.1)),
          geo_coordinate2d(longitude(+180.0), latitude(+ 90.0))),
          "262151")}) {
      const auto &bbox = pair.first;
      geo_coordinate2d ll(bbox.lower_left());
      geo_coordinate2d lr(bbox.upper_right().get_longitude(),
        bbox.lower_left().get_latitude());
      geo_coordinate2d ur(bbox.upper_right());
      geo_coordinate2d ul(bbox.lower_left().get_longitude(),
        bbox.upper_right().get_latitude());
      quad_key morton_key;
      morton_key = quad_key::get_key_from_longitude_latitude_at_depth(
        type::morton, ll, depth);
      EXPECT_EQ(pair.second, morton_key.to_internal_string()) << "ll: " <<
        pair.second << " " << pair.first;
      morton_key = quad_key::get_key_from_longitude_latitude_at_depth(
        type::morton, lr, depth);
      EXPECT_EQ(pair.second, morton_key.to_internal_string()) << "lr: " <<
        pair.second << " " << pair.first;
      morton_key = quad_key::get_key_from_longitude_latitude_at_depth(
        type::morton, ur, depth);
      EXPECT_EQ(pair.second, morton_key.to_internal_string()) << "ur: " <<
        pair.second << " " << pair.first;
      morton_key = quad_key::get_key_from_longitude_latitude_at_depth(
        type::morton, ul, depth);
      EXPECT_EQ(pair.second, morton_key.to_internal_string()) << "ul: " <<
        pair.second << " " << pair.first;
      geo_coordinate_bounding_box2d actual;
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
      std::make_pair<geo_coordinate_bounding_box2d, std::vector<quad_key>>(
        geo_coordinate_bounding_box2d(
          geo_coordinate2d(longitude(-180.0), latitude(- 90.0)),
          geo_coordinate2d(longitude(-  0.1), latitude(+ 90.0))),
        {
          quad_key(type::morton, 0, 0, 0)
        }),
      std::make_pair<geo_coordinate_bounding_box2d, std::vector<quad_key>>(
        geo_coordinate_bounding_box2d(
          geo_coordinate2d(longitude(+  0.0), latitude(- 90.0)),
          geo_coordinate2d(longitude(+180.0), latitude(+ 90.0))),
        {
          quad_key(type::morton, 0, 1, 0)
        }),
      }) {
      std::vector<quad_key> expected;
      expected = quad_key::get_keys_from_longitude_latitude_bounding_box(
        type::morton, data.first, 0);
      EXPECT_EQ(data.second.size(), expected.size());
      for (const quad_key &quad_key : data.second) {
        EXPECT_NE(std::find(data.second.begin(), data.second.end(),
          quad_key), data.second.end());
      }
    }
    for (const auto &data : {
      std::make_pair<geo_coordinate_bounding_box2d, std::vector<quad_key>>(
        geo_coordinate_bounding_box2d(
          geo_coordinate2d(longitude(-180.0), latitude(- 90.0)),
          geo_coordinate2d(longitude(-  0.1), latitude(+ 90.0))),
        {
          quad_key(type::morton, 0, 0, 1), quad_key(type::morton, 0, 1, 1),
          quad_key(type::morton, 1, 0, 1), quad_key(type::morton, 1, 1, 1)
        }),
      std::make_pair<geo_coordinate_bounding_box2d, std::vector<quad_key>>(
        geo_coordinate_bounding_box2d(
          geo_coordinate2d(longitude(+  0.0), latitude(- 90.0)),
          geo_coordinate2d(longitude(+180.0), latitude(+ 90.0))),
        {
          quad_key(type::morton, 0, 2, 1), quad_key(type::morton, 0, 3, 1),
          quad_key(type::morton, 1, 2, 1), quad_key(type::morton, 1, 3, 1),
        }),
      std::make_pair<geo_coordinate_bounding_box2d, std::vector<quad_key>>(
        geo_coordinate_bounding_box2d(
          geo_coordinate2d(longitude(-180.0), latitude(- 90.0)),
          geo_coordinate2d(longitude(-  0.1), latitude(-  0.1))),
        {
          quad_key(type::morton, 0, 0, 1), quad_key(type::morton, 0, 1, 1),
        }),
      std::make_pair<geo_coordinate_bounding_box2d, std::vector<quad_key>>(
        geo_coordinate_bounding_box2d(
          geo_coordinate2d(longitude(-180.0), latitude(+  0.0)),
          geo_coordinate2d(longitude(-  0.1), latitude(+ 90.0))),
        {
          quad_key(type::morton, 1, 0, 1), quad_key(type::morton, 1, 1, 1),
        }),
      std::make_pair<geo_coordinate_bounding_box2d, std::vector<quad_key>>(
        geo_coordinate_bounding_box2d(
          geo_coordinate2d(longitude(+  0.0), latitude(- 90.0)),
          geo_coordinate2d(longitude(+180.0), latitude(-  0.1))),
        {
          quad_key(type::morton, 0, 2, 1), quad_key(type::morton, 0, 3, 1),
        }),
      std::make_pair<geo_coordinate_bounding_box2d, std::vector<quad_key>>(
        geo_coordinate_bounding_box2d(
          geo_coordinate2d(longitude(+  0.0), latitude(+  0.0)),
          geo_coordinate2d(longitude(+180.0), latitude(+ 90.0))),
        {
          quad_key(type::morton, 1, 2, 1), quad_key(type::morton, 1, 3, 1),
        }),
      std::make_pair<geo_coordinate_bounding_box2d, std::vector<quad_key>>(
        geo_coordinate_bounding_box2d(
          geo_coordinate2d(longitude(-180.0), latitude(- 90.0)),
          geo_coordinate2d(longitude(- 90.1), latitude(-  0.1))),
        {
          quad_key(type::morton, 0, 0, 1),
        }),
      std::make_pair<geo_coordinate_bounding_box2d, std::vector<quad_key>>(
        geo_coordinate_bounding_box2d(
          geo_coordinate2d(longitude(- 90.0), latitude(- 90.0)),
          geo_coordinate2d(longitude(-  0.1), latitude(-  0.1))),
        {
          quad_key(type::morton, 0, 0, 1),
        }),
      std::make_pair<geo_coordinate_bounding_box2d, std::vector<quad_key>>(
        geo_coordinate_bounding_box2d(
          geo_coordinate2d(longitude(+  0.0), latitude(- 90.0)),
          geo_coordinate2d(longitude(+ 90.0), latitude(-  0.1))),
        {
          quad_key(type::morton, 0, 2, 1),
        }),
      std::make_pair<geo_coordinate_bounding_box2d, std::vector<quad_key>>(
        geo_coordinate_bounding_box2d(
          geo_coordinate2d(longitude(+ 90.1), latitude(- 90.0)),
          geo_coordinate2d(longitude(+180.0), latitude(-  0.1))),
        {
          quad_key(type::morton, 0, 3, 1),
        }),
      std::make_pair<geo_coordinate_bounding_box2d, std::vector<quad_key>>(
        geo_coordinate_bounding_box2d(
          geo_coordinate2d(longitude(-180.0), latitude(+  0.0)),
          geo_coordinate2d(longitude(- 90.1), latitude(+ 90.0))),
        {
          quad_key(type::morton, 1, 0, 1),
        }),
      std::make_pair<geo_coordinate_bounding_box2d, std::vector<quad_key>>(
        geo_coordinate_bounding_box2d(
          geo_coordinate2d(longitude(- 90.0), latitude(+  0.0)),
          geo_coordinate2d(longitude(-  0.1), latitude(+ 90.0))),
        {
          quad_key(type::morton, 1, 1, 1),
        }),
      std::make_pair<geo_coordinate_bounding_box2d, std::vector<quad_key>>(
        geo_coordinate_bounding_box2d(
          geo_coordinate2d(longitude(+  0.0), latitude(+  0.0)),
          geo_coordinate2d(longitude(+ 90.0), latitude(+ 90.0))),
        {
          quad_key(type::morton, 1, 2, 1),
        }),
      std::make_pair<geo_coordinate_bounding_box2d, std::vector<quad_key>>(
        geo_coordinate_bounding_box2d(
          geo_coordinate2d(longitude(+ 90.1), latitude(+  0.0)),
          geo_coordinate2d(longitude(+180.0), latitude(+ 90.0))),
        {
          quad_key(type::morton, 1, 3, 1),
        }),
      }) {
      std::vector<quad_key> expected;
      expected = quad_key::get_keys_from_longitude_latitude_bounding_box(
        type::morton, data.first, 1);
      EXPECT_EQ(data.second.size(), expected.size());
      for (const quad_key &quad_key : data.second) {
        EXPECT_NE(std::find(data.second.begin(), data.second.end(),
          quad_key), data.second.end()) << quad_key;
      }
    }

    {
      auto data =
        std::make_pair<geo_coordinate_bounding_box2d, std::vector<quad_key>>
          (geo_coordinate_bounding_box2d(
            geo_coordinate2d(longitude(-140.0), latitude(- 48.0)),
            geo_coordinate2d(longitude(+ 10.0), latitude(+ 39.0))),
        {
          quad_key(type::morton, 0, 0, 2), quad_key(type::morton, 0, 1, 2),
          quad_key(type::morton, 0, 2, 2), quad_key(type::morton, 0, 3, 2),
          quad_key(type::morton, 0, 4, 2), quad_key(type::morton, 1, 0, 2),
          quad_key(type::morton, 1, 1, 2), quad_key(type::morton, 1, 2, 2),
          quad_key(type::morton, 1, 3, 2), quad_key(type::morton, 1, 4, 2),
          quad_key(type::morton, 2, 0, 2), quad_key(type::morton, 2, 1, 2),
          quad_key(type::morton, 2, 2, 2), quad_key(type::morton, 2, 3, 2),
          quad_key(type::morton, 2, 4, 2),
        });
      std::vector<quad_key> expected;
      expected = quad_key::get_keys_from_longitude_latitude_bounding_box(
        type::morton, data.first, 2);
      EXPECT_EQ(data.second.size(), expected.size());
      for (const quad_key &quad_key : data.second) {
        EXPECT_NE(std::find(data.second.begin(), data.second.end(),
          quad_key), data.second.end()) << quad_key;
      }
    }
  }

  TEST(MORTONSYSTEM, selected_cities)
  {
    {
      auto data = std::make_pair(13, geo_coordinate2d(
        longitude(+  2.29450000000000),
        latitude( + 48.85822200000000)));
      std::uint32_t tile = 8428778 | (1 << (
        static_cast<std::uint8_t>(data.first) + 16));
      std::stringstream ss;
      ss << tile;
      quad_key morton_quad_key =
        quad_key::get_key_from_longitude_latitude_at_depth(
          type::morton, data.second, static_cast<std::uint8_t>(data.first));
      EXPECT_EQ(ss.str(), morton_quad_key.to_internal_string());
    }
    {
      auto data = std::make_pair(13, geo_coordinate2d(
        longitude(- 74.04444400000000),
        latitude( + 40.68916700000000)));
      std::uint32_t tile = 86924190 | (1 << (
        static_cast<std::uint8_t>(data.first) + 16));
      std::stringstream ss;
      ss << tile;
      quad_key morton_quad_key =
        quad_key::get_key_from_longitude_latitude_at_depth(
          type::morton, data.second, static_cast<std::uint8_t>(data.first));
      EXPECT_EQ(ss.str(), morton_quad_key.to_internal_string());
    }
    {
      auto data = std::make_pair(13, geo_coordinate2d(
        longitude(- 43.15744400000000),
        latitude( - 22.94865800000000)));
      std::uint32_t tile = 130726287 | (1 << (
        static_cast<std::uint8_t>(data.first) + 16));
      std::stringstream ss;
      ss << tile;
      quad_key morton_quad_key =
        quad_key::get_key_from_longitude_latitude_at_depth(
          type::morton, data.second, static_cast<std::uint8_t>(data.first));
      EXPECT_EQ(ss.str(), morton_quad_key.to_internal_string());
    }
    {
      auto data = std::make_pair(13, geo_coordinate2d(
        longitude(+151.21527800000000),
        latitude( - 33.85611100000000)));
      std::uint32_t tile = 63372939 | (1 << (
        static_cast<std::uint8_t>(data.first) + 16));
      std::stringstream ss;
      ss << tile;
      quad_key morton_quad_key =
        quad_key::get_key_from_longitude_latitude_at_depth(
          type::morton, data.second, static_cast<std::uint8_t>(data.first));
      EXPECT_EQ(ss.str(), morton_quad_key.to_internal_string());
    }
    {
      auto data = std::make_pair(13, geo_coordinate2d(
        longitude(+  0.00000000000000),
        latitude( + 51.50300000000000)));
      std::uint32_t tile = 8521770 | (1 << (
        static_cast<std::uint8_t>(data.first) + 16));
      std::stringstream ss;
      ss << tile;
      quad_key morton_quad_key =
        quad_key::get_key_from_longitude_latitude_at_depth(
         type::morton, data.second, static_cast<std::uint8_t>(data.first));
      EXPECT_EQ(ss.str(), morton_quad_key.to_internal_string());
    }
    {
      auto data = std::make_pair(13, geo_coordinate2d(
        longitude(- 78.45000000000000),
        latitude( +  0.00000000000000)));
      std::uint32_t tile = 84148305 | (1 << (
        static_cast<std::uint8_t>(data.first) + 16));
      std::stringstream ss;
      ss << tile;
      quad_key morton_quad_key =
        quad_key::get_key_from_longitude_latitude_at_depth(
          type::morton, data.second, static_cast<std::uint8_t>(data.first));
      EXPECT_EQ(ss.str(), morton_quad_key.to_internal_string());
    }
    {
      auto data = std::make_pair(10, geo_coordinate2d(
        longitude(+  2.29450000000000),
        latitude( + 48.85822200000000)));
      std::uint32_t tile = 131699u | (1 << (16 +
        static_cast<std::uint8_t>(data.first)));
      std::stringstream ss;
      ss << tile;
      quad_key morton_quad_key =
        quad_key::get_key_from_longitude_latitude_at_depth(
          type::morton, data.second, static_cast<std::uint8_t>(data.first));
      EXPECT_EQ(ss.str(), morton_quad_key.to_internal_string());
    }
    {
      auto data = std::make_pair(10, geo_coordinate2d(
        longitude(- 74.04444400000000),
        latitude( + 40.68916700000000)));
      std::uint32_t tile = 1358190u | (1 << (16 +
        static_cast<std::uint8_t>(data.first)));
      std::stringstream ss;
      ss << tile;
      quad_key morton_quad_key =
        quad_key::get_key_from_longitude_latitude_at_depth(
          type::morton, data.second, static_cast<std::uint8_t>(data.first));
      EXPECT_EQ(ss.str(), morton_quad_key.to_internal_string());
    }
    {
      auto data = std::make_pair(10, geo_coordinate2d(
        longitude(- 43.15744400000000),
        latitude( - 22.94865800000000)));
      std::uint32_t tile = 2042598u | (1 << (16 +
        static_cast<std::uint8_t>(data.first)));
      std::stringstream ss;
      ss << tile;
      quad_key morton_quad_key =
        quad_key::get_key_from_longitude_latitude_at_depth(
          type::morton, data.second, static_cast<std::uint8_t>(data.first));
      EXPECT_EQ(ss.str(), morton_quad_key.to_internal_string());
    }
    {
      auto data = std::make_pair(10, geo_coordinate2d(
        longitude(+151.21527800000000),
        latitude( - 33.85611100000000)));
      std::uint32_t tile = 990202u | (1 << (16 +
        static_cast<std::uint8_t>(data.first)));
      std::stringstream ss;
      ss << tile;
      quad_key morton_quad_key =
        quad_key::get_key_from_longitude_latitude_at_depth(
          type::morton, data.second, static_cast<std::uint8_t>(data.first));
      EXPECT_EQ(ss.str(), morton_quad_key.to_internal_string());
    }
    {
      auto data = std::make_pair(10, geo_coordinate2d(
        longitude(+  0.00000000000000),
        latitude( + 51.50300000000000)));
      std::uint32_t tile = 133152u | (1 << (16 +
        static_cast<std::uint8_t>(data.first)));
      std::stringstream ss;
      ss << tile;
      quad_key morton_quad_key =
        quad_key::get_key_from_longitude_latitude_at_depth(
          type::morton, data.second, static_cast<std::uint8_t>(data.first));
      EXPECT_EQ(ss.str(), morton_quad_key.to_internal_string());
    }
    {
      auto data = std::make_pair(10, geo_coordinate2d(
        longitude(- 78.45000000000000),
        latitude( +  0.00000000000000)));
      std::uint32_t tile = 1314817u | (1 << (16 +
        static_cast<std::uint8_t>(data.first)));
      std::stringstream ss;
      ss << tile;
      quad_key morton_quad_key =
        quad_key::get_key_from_longitude_latitude_at_depth(
          type::morton, data.second, static_cast<std::uint8_t>(data.first));
      EXPECT_EQ(ss.str(), morton_quad_key.to_internal_string());
    }
  }
}

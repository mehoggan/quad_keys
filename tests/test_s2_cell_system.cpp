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

  TEST(S2CELLSYSTEM, is_valid)
  {
  }

  TEST(S2CELLSYSTEM, is_root_key)
  {
  }

  TEST(S2CELLSYSTEM, get_parent)
  {
  }

  TEST(S2CELLSYSTEM, is_my_ancestor)
  {
  }

  TEST(S2CELLSYSTEM, get_ancestor)
  {
  }

  TEST(S2CELLSYSTEM, get_child)
  {
  }

  TEST(S2CELLSYSTEM, get_children)
  {
  }

  TEST(S2CELLSYSTEM, get_descendants)
  {
  }

  TEST(S2CELLSYSTEM, get_siblings)
  {
  }

  TEST(S2CELLSYSTEM, get_neighbors)
  {
  }

  TEST(S2CELLSYSTEM, from_string_to_string)
  {
  }

  TEST(S2CELLSYSTEM, get_get_coordinate_bounds2d)
  {
  }

  TEST(S2CELLSYSTEM, get_key_from_longitude_latitude_at_depth_to_bounds)
  {
    // Inclusion here consists of ???
    //    X------X------X
    //    |      |      |
    //    |      |      |
    //    X------X------X
    //    |      |      |
    //    |      |      |
    //    X------X------X
  }

  TEST(S2CELLSYSTEM, get_keys_from_longitude_latitude_bounding_box)
  {
  }

  TEST(S2CELLSYSTEM, SelectedCities)
  {
  }
}

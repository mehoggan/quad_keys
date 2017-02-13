"""
Unit Tests for System
"""

from __future__ import print_function

import unittest


class TestSystem(unittest.TestCase):
    """Class for running unit tests."""

    def test_is_valid(self):
        """See TestQuadKey.test_is_valid."""
        # Same as bing_system

    def test_is_root_key(self):
        """See TestQuadKey.test_is_root_key."""
        # Same as bing_system

    def test_get_parent(self):
        """Test to get parent of a generically formatted quad_key."""
        # Same as bing_system

    def test_is_my_ancestor(self):
        """Checks to see if specified quad_key.quad_key up in the hierarchy
        is an "ancestor" of the given quad_key.
        """
        # Same as bing_system

    def test_get_ancestor(self):
        """Gets the ancestor up the tree according to a delta provided."""
        # Same as bing_system

    def test_get_child(self):
        """Get a single child NE, SE, NW, SW"""
        # Same as bing_system

    def test_get_children(self):
        """Get all the childern of a quad_key."""
        # Same as bing_system

    def test_get_descendants(self):
        """Get all the defendants at some delta in the tree."""
        # Same as bing_system

    def test_get_siblings(self):
        """Test to get siblings of a given quad_key.quad_key."""
        # Same as bing_system

    def test_get_neighbors(self):
        """Test to get the neighbors of a given quad_key."""
        # Same as bing_system

    def test_to_string_from_string(self):
        """
        Test to convert an internally formatted string and back.
        """

    def test_get_geo_coordinate_bounds_2d(self):
        """
        Test to get geographic bounds of quad_key.
        """

    def test_get_key_from_longitude_latitude_at_depth_to_bounds(self):
        """Test to get a quad_key.quad_key from longitude and latitude and
        then get bounds.
        """

    def test_get_keys_from_longitude_latitude_bounding_box(self):
        """Test to get the bounding box of a quad_key."""

    def test_selected_cities(self):
        """Test a given set of known places make sure they work."""

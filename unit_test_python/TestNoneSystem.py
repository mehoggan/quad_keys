"""
Unit Tests for None System
"""

from __future__ import print_function
import unittest
from quadkey import QuadKey
from quadkey import Type__None
from quadkey import GeoCoordinate2d
from quadkey import GeoCoordinateBoundingBox2d
from quadkey import Longitude
from quadkey import Latitude


class TestNoneSystem(unittest.TestCase):
    """
    Class for running unit tests.
    """

    def test_is_valid(self):
        """
        See TestQuadKey.test_is_valid
        """
        # Same as BingSystem

    def test_is_root_key(self):
        """
        See TestQuadKey.test_is_root_key
        """
        # Same as BingSystem

    def test_get_parent(self):
        """
        Test to get parent of a generically formatted quad_key.
        """
        # Same as BingSystem

    def test_is_my_ancestor(self):
        """
        Checks to see if specified quadkey up in the hierarchy is an "ancestor"
        of the given quad_key.
        """
        # Same as BingSystem

    def test_get_ancestor(self):
        """
        Gets the ancestor up the tree according to a delta provided.
        """
        # Same as BingSystem

    def test_get_child(self):
        """
        Get a single child NE, SE, NW, SW
        """
        # Same as BingSystem

    def test_get_children(self):
        """
        Get all the childern of a quad_key.
        """
        # Same as BingSystem

    def test_get_descendants(self):
        """
        Get all the defendants at some delta in the tree.
        """
        # Same as BingSystem

    def test_get_siblings(self):
        """
        Test to get siblings of a given quadkey
        """
        # Same as BingSystem

    def test_get_neighbors(self):
        """
        Test to get the neighbors of a given quadquad_key.
        """
        # Same as BingSystem

    def test_to_string_from_string(self):
        """
        Test to convert an internally formatted string and back.
        """

    def test_get_geo_coordinate_bounds_2d(self):
        """
        Test to get geographic bounds of quadquad_key.
        """

    def test_get_key_from_longitude_latitude_at_depth_to_bounds(self):
        """
        Test to get a quadkey from longitude and latitude and then get bounds.
        """

    def test_get_keys_from_longitude_latitude_bounding_box(self):
        """
        Test to get the bounding box of a quadquad_key.
        """

    def test_selected_cities(self):
        """
        Test a given set of known places make sure they work.
        """


def main():
    """
    Bootstrap function for this module
    """
    suite = unittest.TestLoader().loadTestsFromTestCase(TestNoneSystem)
    unittest.TextTestRunner(verbosity=2).run(suite)

"""
Unit Tests for osgeo System
"""

from __future__ import print_function

import unittest

from quad_keys.quad_keys import QuadKey
from quad_keys.quad_keys import Type_OsGeo
from quad_keys.quad_keys import GeoCoordinate2d
from quad_keys.quad_keys import GeoCoordinateBoundingBox2d
from quad_keys.quad_keys import Longitude
from quad_keys.quad_keys import Latitude


class TestosgeoSystem(unittest.TestCase):
    """Class for running unit tests."""

    def test_is_valid(self):
        """See TestQuadKey.test_is_valid."""
        # Same as bing_system

    def test_is_root_key(self):
        """See TestQuadKey.test_is_root_key."""
        # Same as bing_system

    def test_get_parent(self):
        """Test to get parent of a generically formatted QuadKey."""
        # Same as bing_system

    def test_is_my_ancestor(self):
        """Checks to see if specified QuadKey.quad_key up in the hierarchy
        is an "ancestor" of the given QuadKey.
        """
        # Same as bing_system

    def test_get_ancestor(self):
        """Gets the ancestor up the tree according to a delta provided."""
        # Same as bing_system

    def test_get_child(self):
        """Get a single child NE, SE, NW, SW."""
        # Same as bing_system

    def test_get_children(self):
        """Get all the childern of a QuadKey."""
        # Same as bing_system

    def test_get_descendants(self):
        """Get all the defendants at some delta in the tree."""
        # Same as bing_system

    def test_get_siblings(self):
        """Test to get siblings of a given QuadKey.QuadKey."""
        # Same as bing_system

    def test_get_neighbors(self):
        """Test to get the neighbors of a given QuadKey."""
        # Same as bing_system

    def test_to_string_from_string(self):
        """Test to convert an internally formatted string and back."""
        # Same thing as osgeo Except for it allows for negative 1 in both
        # the rows and the columns. depth/col/row.
        qk = QuadKey(Type_OsGeo, 3, 3, 2)
        fmt = qk.to_internal_string()
        self.assertEqual("2/3/3", fmt)
        quad_key_back = QuadKey.from_internal_string(Type_OsGeo, fmt)
        self.assertEqual(qk, quad_key_back)

        fmt = "0/-1/-1"
        quad_key_back = QuadKey.from_internal_string(Type_OsGeo, fmt)
        self.assertEqual(QuadKey(Type_OsGeo, 0, 0, 0), quad_key_back)

        fmt = "1/1/-1"
        quad_key_back = QuadKey.from_internal_string(Type_OsGeo, fmt)
        self.assertEqual(QuadKey(Type_OsGeo, 0, 1, 1), quad_key_back)

        fmt = "1/-1/1"
        quad_key_back = QuadKey.from_internal_string(Type_OsGeo, fmt)
        self.assertEqual(QuadKey(Type_OsGeo, 1, 0, 1), quad_key_back)

    def test_get_geo_coordinate_bounds_2d(self):
        """Test to get geographic bounds of QuadKey."""
        bbox = GeoCoordinateBoundingBox2d()

        qk = QuadKey.from_internal_string(Type_OsGeo, "0/0/0")
        qk.get_geo_coordinate_bounds2d(bbox)
        self.assertTrue(Longitude(-180.0).near(
            bbox.lower_left().get_longitude(), 1e-4))
        self.assertTrue(Latitude(-85.051132).near(
            bbox.lower_left().get_latitude(), 1e-4))
        self.assertTrue(Longitude(+180.0).near(
            bbox.upper_right().get_longitude(), 1e-4))
        self.assertTrue(Latitude(+85.051132).near(
            bbox.upper_right().get_latitude(), 1e-4))

    def test_get_key_from_longitude_latitude_at_depth_to_bounds(self):  # noqa E501  # pylint: disable = too-many-statements
        """Test to get a QuadKey.quad_key from longitude and latitude and
        then get bounds.
        """
        bbox = GeoCoordinateBoundingBox2d()

        # Inclusion here consists of upper right. In the case along bottom or
        # left Inclusion points the opposite direction.
        #    X------X------X ur
        #    |      |      |
        #    |      |      |
        #    X------X------X
        #    |      |      |
        #    |      |      |
        #    X------X------X
        # Note that in this system bounds consist of all 4 sides, so two
        # quads will share the same boundary.
        qk = QuadKey.get_key_from_longitude_latitude_at_depth(
            Type_OsGeo,
            GeoCoordinate2d(Longitude(-180.0), Latitude(+85.05113877)), 0)
        self.assertEqual(QuadKey(Type_OsGeo, 0, 0, 0), qk)
        qk = QuadKey.get_key_from_longitude_latitude_at_depth(
            Type_OsGeo,
            GeoCoordinate2d(Longitude(+180.0), Latitude(+85.05113877)), 0)
        self.assertEqual(QuadKey(Type_OsGeo, 0, 0, 0), qk)
        qk = QuadKey.get_key_from_longitude_latitude_at_depth(
            Type_OsGeo,
            GeoCoordinate2d(Longitude(+180.0), Latitude(-85.05113877)), 0)
        self.assertEqual(QuadKey(Type_OsGeo, 0, 0, 0), qk)
        qk = QuadKey.get_key_from_longitude_latitude_at_depth(
            Type_OsGeo,
            GeoCoordinate2d(Longitude(-180.0), Latitude(-85.05113877)), 0)
        self.assertEqual(QuadKey(Type_OsGeo, 0, 0, 0), qk)
        qk.get_geo_coordinate_bounds2d(bbox)
        self.assertTrue(bbox.lower_left().near(GeoCoordinate2d(
            Longitude(-180.0), Latitude(-85.05113877)), 1e-4))
        self.assertTrue(bbox.upper_right().near(GeoCoordinate2d(
            Longitude(+180.0), Latitude(+85.05113877)), 1e-4))

        qk = QuadKey.get_key_from_longitude_latitude_at_depth(
            Type_OsGeo,
            GeoCoordinate2d(Longitude(+0.0), Latitude(+0.00000000)), 0)
        self.assertEqual(QuadKey(Type_OsGeo, 0, 0, 0), qk)

        qk = QuadKey.get_key_from_longitude_latitude_at_depth(
            Type_OsGeo,
            GeoCoordinate2d(Longitude(-180.0), Latitude(+85.05113877)), 1)
        self.assertEqual(QuadKey(Type_OsGeo, 1, 0, 1), qk)
        qk.get_geo_coordinate_bounds2d(bbox)
        self.assertTrue(bbox.lower_left().near(GeoCoordinate2d(
            Longitude(-180.0), Latitude(+0.00000000)), 1e-4))
        self.assertTrue(bbox.upper_right().near(GeoCoordinate2d(
            Longitude(+0.0), Latitude(+85.05113877)), 1e-4))

        qk = QuadKey.get_key_from_longitude_latitude_at_depth(
            Type_OsGeo,
            GeoCoordinate2d(Longitude(+180.0), Latitude(+85.05113877)), 1)
        self.assertEqual(QuadKey(Type_OsGeo, 1, 1, 1), qk)
        qk.get_geo_coordinate_bounds2d(bbox)
        self.assertTrue(bbox.lower_left().near(GeoCoordinate2d(
            Longitude(+0.0), Latitude(+0.00000000)), 1e-4))
        self.assertTrue(bbox.upper_right().near(GeoCoordinate2d(
            Longitude(+180.0), Latitude(+85.05113877)), 1e-4))

        qk = QuadKey.get_key_from_longitude_latitude_at_depth(
            Type_OsGeo,
            GeoCoordinate2d(Longitude(+180.0), Latitude(-85.05113877)), 1)
        self.assertEqual(QuadKey(Type_OsGeo, 0, 1, 1), qk)
        qk.get_geo_coordinate_bounds2d(bbox)
        self.assertTrue(bbox.lower_left().near(GeoCoordinate2d(
            Longitude(+0.0), Latitude(-85.05113877)), 1e-4))
        self.assertTrue(bbox.upper_right().near(GeoCoordinate2d(
            Longitude(+180.0), Latitude(+0.00000000)), 1e-4))

        qk = QuadKey.get_key_from_longitude_latitude_at_depth(
            Type_OsGeo,
            GeoCoordinate2d(Longitude(-180.0), Latitude(-85.05113877)), 1)
        self.assertEqual(QuadKey(Type_OsGeo, 0, 0, 1), qk)
        qk.get_geo_coordinate_bounds2d(bbox)
        self.assertTrue(bbox.lower_left().near(GeoCoordinate2d(
            Longitude(-180.0), Latitude(-85.05113877)), 1e-4))
        self.assertTrue(bbox.upper_right().near(GeoCoordinate2d(
            Longitude(+0.0), Latitude(+0.00000000)), 1e-4))

        qk = QuadKey.get_key_from_longitude_latitude_at_depth(
            Type_OsGeo,
            GeoCoordinate2d(Longitude(-180.0), Latitude(+0.00000000)), 1)
        self.assertEqual(QuadKey(Type_OsGeo, 0, 0, 1), qk)
        qk = QuadKey.get_key_from_longitude_latitude_at_depth(
            Type_OsGeo,
            GeoCoordinate2d(Longitude(+0.0), Latitude(+85.05113877)), 1)
        self.assertEqual(QuadKey(Type_OsGeo, 1, 0, 1), qk)
        qk = QuadKey.get_key_from_longitude_latitude_at_depth(
            Type_OsGeo,
            GeoCoordinate2d(Longitude(+180.0), Latitude(+0.00000000)), 1)
        self.assertEqual(QuadKey(Type_OsGeo, 0, 1, 1), qk)
        qk = QuadKey.get_key_from_longitude_latitude_at_depth(
            Type_OsGeo,
            GeoCoordinate2d(Longitude(+0.0), Latitude(-85.05113877)), 1)
        self.assertEqual(QuadKey(Type_OsGeo, 0, 0, 1), qk)
        qk = QuadKey.get_key_from_longitude_latitude_at_depth(
            Type_OsGeo,
            GeoCoordinate2d(Longitude(+0.0), Latitude(+0.00000000)), 1)
        self.assertEqual(QuadKey(Type_OsGeo, 0, 0, 1), qk)

        # Note at depth 2 because of the Mercator projection the lines
        # of latitude are note perfect divisions by 2.
        qk = QuadKey.get_key_from_longitude_latitude_at_depth(
            Type_OsGeo,
            GeoCoordinate2d(Longitude(-180.0), Latitude(-85.05113877)), 2)
        self.assertEqual(QuadKey(Type_OsGeo, 0, 0, 2), qk)
        qk = QuadKey.get_key_from_longitude_latitude_at_depth(
            Type_OsGeo,
            GeoCoordinate2d(Longitude(-180.0), Latitude(-66.5133)), 2)
        self.assertEqual(QuadKey(Type_OsGeo, 0, 0, 2), qk)
        qk = QuadKey.get_key_from_longitude_latitude_at_depth(
            Type_OsGeo,
            GeoCoordinate2d(Longitude(-180.0), Latitude(-66.5132)), 2)
        self.assertEqual(QuadKey(Type_OsGeo, 1, 0, 2), qk)
        qk = QuadKey.get_key_from_longitude_latitude_at_depth(
            Type_OsGeo,
            GeoCoordinate2d(Longitude(-180.0), Latitude(+0.1)), 2)
        self.assertEqual(QuadKey(Type_OsGeo, 2, 0, 2), qk)
        qk = QuadKey.get_key_from_longitude_latitude_at_depth(
            Type_OsGeo,
            GeoCoordinate2d(Longitude(-180.0), Latitude(+66.5132)), 2)
        self.assertEqual(QuadKey(Type_OsGeo, 2, 0, 2), qk)
        qk = QuadKey.get_key_from_longitude_latitude_at_depth(
            Type_OsGeo,
            GeoCoordinate2d(Longitude(-180.0), Latitude(+66.5133)), 2)
        self.assertEqual(QuadKey(Type_OsGeo, 3, 0, 2), qk)
        qk = QuadKey.get_key_from_longitude_latitude_at_depth(
            Type_OsGeo,
            GeoCoordinate2d(Longitude(-180.0), Latitude(+85.05113877)), 2)
        self.assertEqual(QuadKey(Type_OsGeo, 3, 0, 2), qk)
        qk = QuadKey.get_key_from_longitude_latitude_at_depth(
            Type_OsGeo,
            GeoCoordinate2d(Longitude(-90.0), Latitude(-85.05113877)), 2)
        self.assertEqual(QuadKey(Type_OsGeo, 0, 0, 2), qk)
        qk = QuadKey.get_key_from_longitude_latitude_at_depth(
            Type_OsGeo,
            GeoCoordinate2d(Longitude(-90.0), Latitude(-66.5133)), 2)
        self.assertEqual(QuadKey(Type_OsGeo, 0, 0, 2), qk)
        qk = QuadKey.get_key_from_longitude_latitude_at_depth(
            Type_OsGeo,
            GeoCoordinate2d(Longitude(-90.0), Latitude(-66.5132)), 2)
        self.assertEqual(QuadKey(Type_OsGeo, 1, 0, 2), qk)
        qk = QuadKey.get_key_from_longitude_latitude_at_depth(
            Type_OsGeo,
            GeoCoordinate2d(Longitude(-90.0), Latitude(+0.1)), 2)
        self.assertEqual(QuadKey(Type_OsGeo, 2, 0, 2), qk)
        qk = QuadKey.get_key_from_longitude_latitude_at_depth(
            Type_OsGeo,
            GeoCoordinate2d(Longitude(-90.0), Latitude(+66.5132)), 2)
        self.assertEqual(QuadKey(Type_OsGeo, 2, 0, 2), qk)
        qk = QuadKey.get_key_from_longitude_latitude_at_depth(
            Type_OsGeo,
            GeoCoordinate2d(Longitude(-90.0), Latitude(+66.5133)), 2)
        self.assertEqual(QuadKey(Type_OsGeo, 3, 0, 2), qk)
        qk = QuadKey.get_key_from_longitude_latitude_at_depth(
            Type_OsGeo,
            GeoCoordinate2d(Longitude(-90.0), Latitude(+85.05113877)), 2)
        self.assertEqual(QuadKey(Type_OsGeo, 3, 0, 2), qk)
        qk = QuadKey.get_key_from_longitude_latitude_at_depth(
            Type_OsGeo,
            GeoCoordinate2d(Longitude(-89.9), Latitude(-85.05113877)), 2)
        self.assertEqual(QuadKey(Type_OsGeo, 0, 1, 2), qk)
        qk = QuadKey.get_key_from_longitude_latitude_at_depth(
            Type_OsGeo,
            GeoCoordinate2d(Longitude(-89.9), Latitude(-66.5133)), 2)
        self.assertEqual(QuadKey(Type_OsGeo, 0, 1, 2), qk)
        qk = QuadKey.get_key_from_longitude_latitude_at_depth(
            Type_OsGeo,
            GeoCoordinate2d(Longitude(-89.9), Latitude(-66.5132)), 2)
        self.assertEqual(QuadKey(Type_OsGeo, 1, 1, 2), qk)
        qk = QuadKey.get_key_from_longitude_latitude_at_depth(
            Type_OsGeo,
            GeoCoordinate2d(Longitude(-89.9), Latitude(+0.1)), 2)
        self.assertEqual(QuadKey(Type_OsGeo, 2, 1, 2), qk)
        qk = QuadKey.get_key_from_longitude_latitude_at_depth(
            Type_OsGeo,
            GeoCoordinate2d(Longitude(-89.9), Latitude(+66.5132)), 2)
        self.assertEqual(QuadKey(Type_OsGeo, 2, 1, 2), qk)
        qk = QuadKey.get_key_from_longitude_latitude_at_depth(
            Type_OsGeo,
            GeoCoordinate2d(Longitude(-89.9), Latitude(+66.5133)), 2)
        self.assertEqual(QuadKey(Type_OsGeo, 3, 1, 2), qk)
        qk = QuadKey.get_key_from_longitude_latitude_at_depth(
            Type_OsGeo,
            GeoCoordinate2d(Longitude(-89.9), Latitude(+85.05113877)), 2)
        self.assertEqual(QuadKey(Type_OsGeo, 3, 1, 2), qk)
        qk = QuadKey.get_key_from_longitude_latitude_at_depth(
            Type_OsGeo,
            GeoCoordinate2d(Longitude(+0.0), Latitude(-85.05113877)), 2)
        self.assertEqual(QuadKey(Type_OsGeo, 0, 1, 2), qk)
        qk = QuadKey.get_key_from_longitude_latitude_at_depth(
            Type_OsGeo,
            GeoCoordinate2d(Longitude(+0.0), Latitude(-66.5133)), 2)
        self.assertEqual(QuadKey(Type_OsGeo, 0, 1, 2), qk)
        qk = QuadKey.get_key_from_longitude_latitude_at_depth(
            Type_OsGeo,
            GeoCoordinate2d(Longitude(+0.0), Latitude(-66.5132)), 2)
        self.assertEqual(QuadKey(Type_OsGeo, 1, 1, 2), qk)
        qk = QuadKey.get_key_from_longitude_latitude_at_depth(
            Type_OsGeo,
            GeoCoordinate2d(Longitude(+0.0), Latitude(+0.1)), 2)
        self.assertEqual(QuadKey(Type_OsGeo, 2, 1, 2), qk)
        qk = QuadKey.get_key_from_longitude_latitude_at_depth(
            Type_OsGeo,
            GeoCoordinate2d(Longitude(+0.0), Latitude(+66.5132)), 2)
        self.assertEqual(QuadKey(Type_OsGeo, 2, 1, 2), qk)
        qk = QuadKey.get_key_from_longitude_latitude_at_depth(
            Type_OsGeo,
            GeoCoordinate2d(Longitude(+0.0), Latitude(+66.5133)), 2)
        self.assertEqual(QuadKey(Type_OsGeo, 3, 1, 2), qk)
        qk = QuadKey.get_key_from_longitude_latitude_at_depth(
            Type_OsGeo,
            GeoCoordinate2d(Longitude(+0.0), Latitude(+85.05113877)), 2)
        self.assertEqual(QuadKey(Type_OsGeo, 3, 1, 2), qk)
        qk = QuadKey.get_key_from_longitude_latitude_at_depth(
            Type_OsGeo,
            GeoCoordinate2d(Longitude(+0.1), Latitude(-85.05113877)), 2)
        self.assertEqual(QuadKey(Type_OsGeo, 0, 2, 2), qk)
        qk = QuadKey.get_key_from_longitude_latitude_at_depth(
            Type_OsGeo,
            GeoCoordinate2d(Longitude(+0.1), Latitude(-66.5133)), 2)
        self.assertEqual(QuadKey(Type_OsGeo, 0, 2, 2), qk)
        qk = QuadKey.get_key_from_longitude_latitude_at_depth(
            Type_OsGeo,
            GeoCoordinate2d(Longitude(+0.1), Latitude(-66.5132)), 2)
        self.assertEqual(QuadKey(Type_OsGeo, 1, 2, 2), qk)
        qk = QuadKey.get_key_from_longitude_latitude_at_depth(
            Type_OsGeo,
            GeoCoordinate2d(Longitude(+0.1), Latitude(+0.1)), 2)
        self.assertEqual(QuadKey(Type_OsGeo, 2, 2, 2), qk)
        qk = QuadKey.get_key_from_longitude_latitude_at_depth(
            Type_OsGeo,
            GeoCoordinate2d(Longitude(+0.1), Latitude(+66.5132)), 2)
        self.assertEqual(QuadKey(Type_OsGeo, 2, 2, 2), qk)
        qk = QuadKey.get_key_from_longitude_latitude_at_depth(
            Type_OsGeo,
            GeoCoordinate2d(Longitude(+0.1), Latitude(+66.5133)), 2)
        self.assertEqual(QuadKey(Type_OsGeo, 3, 2, 2), qk)
        qk = QuadKey.get_key_from_longitude_latitude_at_depth(
            Type_OsGeo,
            GeoCoordinate2d(Longitude(+0.1), Latitude(+85.05113877)), 2)
        self.assertEqual(QuadKey(Type_OsGeo, 3, 2, 2), qk)
        qk = QuadKey.get_key_from_longitude_latitude_at_depth(
            Type_OsGeo,
            GeoCoordinate2d(Longitude(+90.0), Latitude(-85.05113877)), 2)
        self.assertEqual(QuadKey(Type_OsGeo, 0, 2, 2), qk)
        qk = QuadKey.get_key_from_longitude_latitude_at_depth(
            Type_OsGeo,
            GeoCoordinate2d(Longitude(+90.0), Latitude(-66.5133)), 2)
        self.assertEqual(QuadKey(Type_OsGeo, 0, 2, 2), qk)
        qk = QuadKey.get_key_from_longitude_latitude_at_depth(
            Type_OsGeo,
            GeoCoordinate2d(Longitude(+90.0), Latitude(-66.5132)), 2)
        self.assertEqual(QuadKey(Type_OsGeo, 1, 2, 2), qk)
        qk = QuadKey.get_key_from_longitude_latitude_at_depth(
            Type_OsGeo,
            GeoCoordinate2d(Longitude(+90.0), Latitude(+0.1)), 2)
        self.assertEqual(QuadKey(Type_OsGeo, 2, 2, 2), qk)
        qk = QuadKey.get_key_from_longitude_latitude_at_depth(
            Type_OsGeo,
            GeoCoordinate2d(Longitude(+90.0), Latitude(+66.5132)), 2)
        self.assertEqual(QuadKey(Type_OsGeo, 2, 2, 2), qk)
        qk = QuadKey.get_key_from_longitude_latitude_at_depth(
            Type_OsGeo,
            GeoCoordinate2d(Longitude(+90.0), Latitude(+66.5133)), 2)
        self.assertEqual(QuadKey(Type_OsGeo, 3, 2, 2), qk)
        qk = QuadKey.get_key_from_longitude_latitude_at_depth(
            Type_OsGeo,
            GeoCoordinate2d(Longitude(+90.0), Latitude(+85.05113877)), 2)
        self.assertEqual(QuadKey(Type_OsGeo, 3, 2, 2), qk)
        qk = QuadKey.get_key_from_longitude_latitude_at_depth(
            Type_OsGeo,
            GeoCoordinate2d(Longitude(+90.1), Latitude(-85.05113877)), 2)
        self.assertEqual(QuadKey(Type_OsGeo, 0, 3, 2), qk)
        qk = QuadKey.get_key_from_longitude_latitude_at_depth(
            Type_OsGeo,
            GeoCoordinate2d(Longitude(+90.1), Latitude(-66.5133)), 2)
        self.assertEqual(QuadKey(Type_OsGeo, 0, 3, 2), qk)
        qk = QuadKey.get_key_from_longitude_latitude_at_depth(
            Type_OsGeo,
            GeoCoordinate2d(Longitude(+90.1), Latitude(-66.5132)), 2)
        self.assertEqual(QuadKey(Type_OsGeo, 1, 3, 2), qk)
        qk = QuadKey.get_key_from_longitude_latitude_at_depth(
            Type_OsGeo,
            GeoCoordinate2d(Longitude(+90.1), Latitude(+0.1)), 2)
        self.assertEqual(QuadKey(Type_OsGeo, 2, 3, 2), qk)
        qk = QuadKey.get_key_from_longitude_latitude_at_depth(
            Type_OsGeo,
            GeoCoordinate2d(Longitude(+90.1), Latitude(+66.5132)), 2)
        self.assertEqual(QuadKey(Type_OsGeo, 2, 3, 2), qk)
        qk = QuadKey.get_key_from_longitude_latitude_at_depth(
            Type_OsGeo,
            GeoCoordinate2d(Longitude(+90.1), Latitude(+66.5133)), 2)
        self.assertEqual(QuadKey(Type_OsGeo, 3, 3, 2), qk)
        qk = QuadKey.get_key_from_longitude_latitude_at_depth(
            Type_OsGeo,
            GeoCoordinate2d(Longitude(+90.1), Latitude(+85.05113877)), 2)
        self.assertEqual(QuadKey(Type_OsGeo, 3, 3, 2), qk)
        qk = QuadKey.get_key_from_longitude_latitude_at_depth(
            Type_OsGeo,
            GeoCoordinate2d(Longitude(+180.0), Latitude(-85.05113877)), 2)
        self.assertEqual(QuadKey(Type_OsGeo, 0, 3, 2), qk)
        qk = QuadKey.get_key_from_longitude_latitude_at_depth(
            Type_OsGeo,
            GeoCoordinate2d(Longitude(+180.0), Latitude(-66.5133)), 2)
        self.assertEqual(QuadKey(Type_OsGeo, 0, 3, 2), qk)
        qk = QuadKey.get_key_from_longitude_latitude_at_depth(
            Type_OsGeo,
            GeoCoordinate2d(Longitude(+180.0), Latitude(-66.5132)), 2)
        self.assertEqual(QuadKey(Type_OsGeo, 1, 3, 2), qk)
        qk = QuadKey.get_key_from_longitude_latitude_at_depth(
            Type_OsGeo,
            GeoCoordinate2d(Longitude(+180.0), Latitude(+0.1)), 2)
        self.assertEqual(QuadKey(Type_OsGeo, 2, 3, 2), qk)
        qk = QuadKey.get_key_from_longitude_latitude_at_depth(
            Type_OsGeo,
            GeoCoordinate2d(Longitude(+180.0), Latitude(+66.5132)), 2)
        self.assertEqual(QuadKey(Type_OsGeo, 2, 3, 2), qk)
        qk = QuadKey.get_key_from_longitude_latitude_at_depth(
            Type_OsGeo,
            GeoCoordinate2d(Longitude(+180.0), Latitude(+66.5133)), 2)
        self.assertEqual(QuadKey(Type_OsGeo, 3, 3, 2), qk)
        qk = QuadKey.get_key_from_longitude_latitude_at_depth(
            Type_OsGeo,
            GeoCoordinate2d(Longitude(+180.0), Latitude(+85.05113877)), 2)
        self.assertEqual(QuadKey(Type_OsGeo, 3, 3, 2), qk)

    def test_get_keys_from_longitude_latitude_bounding_box(self):
        """Test to get the bounding box of a QuadKey."""
        quad_keys = QuadKey.get_keys_from_longitude_latitude_bounding_box(
            Type_OsGeo, GeoCoordinateBoundingBox2d(
                GeoCoordinate2d(Longitude(+0.0), Latitude(-0.10000000)),
                GeoCoordinate2d(Longitude(+0.1), Latitude(+0.10000000))),
            0)
        self.assertEqual(1, quad_keys.size())
        self.assertTrue(QuadKey(Type_OsGeo, 0, 0, 0) in quad_keys)

        quad_keys = QuadKey.get_keys_from_longitude_latitude_bounding_box(
            Type_OsGeo, GeoCoordinateBoundingBox2d(
                GeoCoordinate2d(Longitude(-180.0), Latitude(-85.05113877)),
                GeoCoordinate2d(Longitude(+180.0), Latitude(+85.05113877))),
            1)
        self.assertEqual(4, quad_keys.size())
        self.assertTrue(QuadKey(Type_OsGeo, 0, 0, 1) in quad_keys)
        self.assertTrue(QuadKey(Type_OsGeo, 0, 1, 1) in quad_keys)
        self.assertTrue(QuadKey(Type_OsGeo, 1, 0, 1) in quad_keys)
        self.assertTrue(QuadKey(Type_OsGeo, 1, 1, 1) in quad_keys)

        quad_keys = QuadKey.get_keys_from_longitude_latitude_bounding_box(
            Type_OsGeo, GeoCoordinateBoundingBox2d(
                GeoCoordinate2d(Longitude(-180.0), Latitude(-85.05113877)),
                GeoCoordinate2d(Longitude(+0.0), Latitude(+85.05113877))),
            1)
        self.assertEqual(2, quad_keys.size())
        self.assertTrue(QuadKey(Type_OsGeo, 1, 0, 1) in quad_keys)
        self.assertTrue(QuadKey(Type_OsGeo, 0, 0, 1) in quad_keys)

        quad_keys = QuadKey.get_keys_from_longitude_latitude_bounding_box(
            Type_OsGeo, GeoCoordinateBoundingBox2d(
                GeoCoordinate2d(Longitude(+0.1), Latitude(-85.05113877)),
                GeoCoordinate2d(Longitude(+180.0), Latitude(+85.05113877))),
            1)
        self.assertEqual(2, quad_keys.size())
        self.assertTrue(QuadKey(Type_OsGeo, 1, 1, 1) in quad_keys)
        self.assertTrue(QuadKey(Type_OsGeo, 0, 1, 1) in quad_keys)

        quad_keys = QuadKey.get_keys_from_longitude_latitude_bounding_box(
            Type_OsGeo, GeoCoordinateBoundingBox2d(
                GeoCoordinate2d(Longitude(-180.0), Latitude(-85.05113877)),
                GeoCoordinate2d(Longitude(+0.0), Latitude(+0.00000000))),
            1)
        self.assertEqual(1, quad_keys.size())
        self.assertTrue(QuadKey(Type_OsGeo, 0, 0, 1) in quad_keys)

        quad_keys = QuadKey.get_keys_from_longitude_latitude_bounding_box(
            Type_OsGeo, GeoCoordinateBoundingBox2d(
                GeoCoordinate2d(Longitude(-180.0), Latitude(+0.10000000)),
                GeoCoordinate2d(Longitude(+0.0), Latitude(+85.05113877))),
            1)
        self.assertEqual(1, quad_keys.size())
        self.assertTrue(QuadKey(Type_OsGeo, 1, 0, 1) in quad_keys)

        quad_keys = QuadKey.get_keys_from_longitude_latitude_bounding_box(
            Type_OsGeo, GeoCoordinateBoundingBox2d(
                GeoCoordinate2d(Longitude(+0.1), Latitude(-85.05113877)),
                GeoCoordinate2d(Longitude(+180.0), Latitude(+0.00000000))),
            1)
        self.assertEqual(1, quad_keys.size())
        self.assertTrue(QuadKey(Type_OsGeo, 0, 1, 1) in quad_keys)

        quad_keys = QuadKey.get_keys_from_longitude_latitude_bounding_box(
            Type_OsGeo, GeoCoordinateBoundingBox2d(
                GeoCoordinate2d(Longitude(+0.1), Latitude(+0.10000000)),
                GeoCoordinate2d(Longitude(+180.0), Latitude(+85.05113877))),
            1)
        self.assertEqual(1, quad_keys.size())
        self.assertTrue(QuadKey(Type_OsGeo, 1, 1, 1) in quad_keys)

    def test_selected_cities(self):
        """Test a given set of known places make sure they work."""

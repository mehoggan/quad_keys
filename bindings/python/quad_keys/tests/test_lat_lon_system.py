"""
Unit Tests for lat_long System
"""

from __future__ import print_function

import unittest

from quad_keys.quad_keys import QuadKey
from quad_keys.quad_keys import Type_LatLon
from quad_keys.quad_keys import GeoCoordinate2d
from quad_keys.quad_keys import GeoCoordinateBoundingBox2d
from quad_keys.quad_keys import Longitude
from quad_keys.quad_keys import Latitude


class TestLatLonSystem(unittest.TestCase):
    """Class for running unit tests."""

    def test_is_valid(self):
        """See TestQuadKey.test_is_valid."""

    def test_is_root_key(self):
        """See TestQuadKey.test_is_root_key."""

    def test_get_parent(self):
        """Test to get parent of a generically formatted QuadKey."""
        # Same as BingSystem

    def test_is_my_ancestor(self):
        """Checks to see if specified QuadKey.quad_key up in the hierarchy
        is an "ancestor" of the given QuadKey.
        """
        # Same as BingSystem

    def test_get_ancestor(self):
        """Gets the ancestor up the tree according to a delta provided."""
        # Same as BingSystem

    def test_get_child(self):
        """Get a single child NE, SE, NW, SW."""
        # Same as BingSystem

    def test_get_children(self):
        """Get all the childern of a QuadKey."""
        # Same as BingSystem

    def test_get_descendants(self):
        """Get all the defendants at some delta in the tree."""
        # Same as BingSystem

    def test_get_siblings(self):
        """Test to get siblings of a given QuadKey.QuadKey."""
        # Same as BingSystem

    def test_get_neighbors(self):
        """Test to get the neighbors of a given quadQuadKey."""
        # Same as BingSystem

    def test_to_string_from_string(self):
        """Test to convert an internally formatted string and back."""
        # Same as BingSystem

    def test_get_geo_coordinate_bounds_2d(self):
        """Test to get geographic bounds of quadQuadKey."""
        bbox = GeoCoordinateBoundingBox2d()

        qk = QuadKey(Type_LatLon, 0, 0, 0)
        qk.get_geo_coordinate_bounds2d(bbox)
        self.assertTrue(GeoCoordinate2d(
            Longitude(-180.0), Latitude(-90.0)) == bbox.lower_left())
        self.assertTrue(GeoCoordinate2d(
            Longitude(+180.0), Latitude(+90.0)) == bbox.upper_right())

        qk = QuadKey(Type_LatLon, 0, 0, 1)
        qk.get_geo_coordinate_bounds2d(bbox)
        self.assertTrue(
            bbox.lower_left().get_longitude().near(Longitude(-180.0), 1e-6))
        self.assertTrue(
            bbox.lower_left().get_latitude().near(Latitude(-90.0), 1e-6))
        self.assertTrue(
            bbox.upper_right().get_longitude().near(Longitude(+0.0), 1e-6))
        self.assertTrue(
            bbox.upper_right().get_latitude().near(Latitude(+0.0), 1e-6))

        qk = QuadKey(Type_LatLon, 0, 1, 1)
        qk.get_geo_coordinate_bounds2d(bbox)
        self.assertTrue(
            bbox.lower_left().get_longitude().near(Longitude(+0.0), 1e-6))
        self.assertTrue(
            bbox.lower_left().get_latitude().near(Latitude(-90.0), 1e-6))
        self.assertTrue(
            bbox.upper_right().get_longitude().near(Longitude(+180.0), 1e-6))
        self.assertTrue(
            bbox.upper_right().get_latitude().near(Latitude(+0.0), 1e-6))

        qk = QuadKey(Type_LatLon, 1, 0, 1)
        qk.get_geo_coordinate_bounds2d(bbox)
        self.assertTrue(
            bbox.lower_left().get_longitude().near(Longitude(-180.0), 1e-6))
        self.assertTrue(
            bbox.lower_left().get_latitude().near(Latitude(+0.0), 1e-6))
        self.assertTrue(
            bbox.upper_right().get_longitude().near(Longitude(+0.0), 1e-6))
        self.assertTrue(
            bbox.upper_right().get_latitude().near(Latitude(+90.0), 1e-6))

        qk = QuadKey(Type_LatLon, 1, 1, 1)
        qk.get_geo_coordinate_bounds2d(bbox)
        self.assertTrue(
            bbox.lower_left().get_longitude().near(Longitude(+0.0), 1e-6))
        self.assertTrue(
            bbox.lower_left().get_latitude().near(Latitude(+0.0), 1e-6))
        self.assertTrue(
            bbox.upper_right().get_longitude().near(Longitude(+180.0), 1e-6))
        self.assertTrue(
            bbox.upper_right().get_latitude().near(Latitude(+90.0), 1e-6))

    def test_get_key_from_longitude_latitude_at_depth_to_bounds(self):  # noqa E501  # pylint: disable=too-many-statements
        """Test to get a QuadKey.quad_key from longitude and latitude and
        then get bounds.
        """

        qk = QuadKey.get_key_from_longitude_latitude_at_depth(
            Type_LatLon, GeoCoordinate2d(Longitude(-180.0),
                                         Latitude(-90)), 0)
        self.assertTrue(QuadKey(Type_LatLon, 0, 0, 0) == qk)
        self.assertEqual("", qk.to_internal_string())

        # Inclusion here consists of lower left
        #    X------X------X
        #    |   2  |   3  |
        #    |      |      |
        #    X------X------X
        #    |   0  |   1  |
        #    |      |      |
        # ll X------X------X
        qk = QuadKey.get_key_from_longitude_latitude_at_depth(
            Type_LatLon, GeoCoordinate2d(Longitude(-180.0),
                                         Latitude(-90.0)), 1)
        self.assertTrue(QuadKey(Type_LatLon, 0, 0, 1) == qk)
        self.assertEqual("2", qk.to_internal_string())
        qk = QuadKey.get_key_from_longitude_latitude_at_depth(
            Type_LatLon, GeoCoordinate2d(Longitude(-0.1),
                                         Latitude(-90.0)), 1)
        self.assertTrue(QuadKey(Type_LatLon, 0, 0, 1) == qk)
        self.assertEqual("2", qk.to_internal_string())
        qk = QuadKey.get_key_from_longitude_latitude_at_depth(
            Type_LatLon, GeoCoordinate2d(Longitude(-0.1),
                                         Latitude(-0.1)), 1)
        self.assertTrue(QuadKey(Type_LatLon, 0, 0, 1) == qk)
        self.assertEqual("2", qk.to_internal_string())
        qk = QuadKey.get_key_from_longitude_latitude_at_depth(
            Type_LatLon, GeoCoordinate2d(Longitude(-180.0),
                                         Latitude(-0.1)), 1)
        self.assertTrue(QuadKey(Type_LatLon, 0, 0, 1) == qk)
        self.assertEqual("2", qk.to_internal_string())

        qk = QuadKey.get_key_from_longitude_latitude_at_depth(
            Type_LatLon, GeoCoordinate2d(Longitude(+0.0),
                                         Latitude(-90.0)), 1)
        self.assertTrue(QuadKey(Type_LatLon, 0, 1, 1) == qk)
        self.assertEqual("3", qk.to_internal_string())
        qk = QuadKey.get_key_from_longitude_latitude_at_depth(
            Type_LatLon, GeoCoordinate2d(Longitude(+180.0),
                                         Latitude(-90.0)), 1)
        self.assertTrue(QuadKey(Type_LatLon, 0, 1, 1) == qk)
        self.assertEqual("3", qk.to_internal_string())
        qk = QuadKey.get_key_from_longitude_latitude_at_depth(
            Type_LatLon, GeoCoordinate2d(Longitude(+180.0),
                                         Latitude(-0.1)), 1)
        self.assertTrue(QuadKey(Type_LatLon, 0, 1, 1) == qk)
        self.assertEqual("3", qk.to_internal_string())
        qk = QuadKey.get_key_from_longitude_latitude_at_depth(
            Type_LatLon, GeoCoordinate2d(Longitude(+0.0),
                                         Latitude(-0.1)), 1)
        self.assertTrue(QuadKey(Type_LatLon, 0, 1, 1) == qk)
        self.assertEqual("3", qk.to_internal_string())

        qk = QuadKey.get_key_from_longitude_latitude_at_depth(
            Type_LatLon, GeoCoordinate2d(Longitude(-180.0),
                                         Latitude(+0.0)), 1)
        self.assertTrue(QuadKey(Type_LatLon, 1, 0, 1) == qk)
        self.assertEqual("0", qk.to_internal_string())
        qk = QuadKey.get_key_from_longitude_latitude_at_depth(
            Type_LatLon, GeoCoordinate2d(Longitude(-0.1),
                                         Latitude(+0.0)), 1)
        self.assertTrue(QuadKey(Type_LatLon, 1, 0, 1) == qk)
        self.assertEqual("0", qk.to_internal_string())
        qk = QuadKey.get_key_from_longitude_latitude_at_depth(
            Type_LatLon, GeoCoordinate2d(Longitude(-180.0),
                                         Latitude(+90.0)), 1)
        self.assertTrue(QuadKey(Type_LatLon, 1, 0, 1) == qk)
        self.assertEqual("0", qk.to_internal_string())
        qk = QuadKey.get_key_from_longitude_latitude_at_depth(
            Type_LatLon, GeoCoordinate2d(Longitude(-0.1),
                                         Latitude(+90.0)), 1)
        self.assertTrue(QuadKey(Type_LatLon, 1, 0, 1) == qk)
        self.assertEqual("0", qk.to_internal_string())

        qk = QuadKey.get_key_from_longitude_latitude_at_depth(
            Type_LatLon, GeoCoordinate2d(Longitude(+0.0),
                                         Latitude(+0.0)), 1)
        self.assertTrue(QuadKey(Type_LatLon, 1, 1, 1) == qk)
        self.assertEqual("1", qk.to_internal_string())
        qk = QuadKey.get_key_from_longitude_latitude_at_depth(
            Type_LatLon, GeoCoordinate2d(Longitude(+180.0),
                                         Latitude(+0.0)), 1)
        self.assertTrue(QuadKey(Type_LatLon, 1, 1, 1) == qk)
        self.assertEqual("1", qk.to_internal_string())
        qk = QuadKey.get_key_from_longitude_latitude_at_depth(
            Type_LatLon, GeoCoordinate2d(Longitude(+0.0),
                                         Latitude(+90.0)), 1)
        self.assertTrue(QuadKey(Type_LatLon, 1, 1, 1) == qk)
        self.assertEqual("1", qk.to_internal_string())
        qk = QuadKey.get_key_from_longitude_latitude_at_depth(
            Type_LatLon, GeoCoordinate2d(Longitude(+180.0),
                                         Latitude(+90.0)), 1)
        self.assertTrue(QuadKey(Type_LatLon, 1, 1, 1) == qk)
        self.assertEqual("1", qk.to_internal_string())

    def test_get_keys_from_longitude_latitude_bounding_box(self):
        """Test to get the bounding box of a quadQuadKey."""
        outkeys = QuadKey.get_keys_from_longitude_latitude_bounding_box(
            Type_LatLon,
            GeoCoordinateBoundingBox2d(
                GeoCoordinate2d(Longitude(-180.0), Latitude(+90.0)),
                GeoCoordinate2d(Longitude(+180.0), Latitude(-90.0))),
            0)
        self.assertEqual(1, outkeys.size())
        self.assertTrue(QuadKey(Type_LatLon, 0, 0, 0) in outkeys)

        outkeys = QuadKey.get_keys_from_longitude_latitude_bounding_box(
            Type_LatLon,
            GeoCoordinateBoundingBox2d(
                GeoCoordinate2d(Longitude(-180.0), Latitude(+90.0)),
                GeoCoordinate2d(Longitude(+180.0), Latitude(-90.0))),
            1)
        self.assertEqual(4, outkeys.size())
        self.assertTrue(QuadKey(Type_LatLon, 0, 0, 1) in outkeys)
        self.assertTrue(QuadKey(Type_LatLon, 0, 1, 1) in outkeys)
        self.assertTrue(QuadKey(Type_LatLon, 1, 0, 1) in outkeys)
        self.assertTrue(QuadKey(Type_LatLon, 1, 1, 1) in outkeys)

        outkeys = QuadKey.get_keys_from_longitude_latitude_bounding_box(
            Type_LatLon,
            GeoCoordinateBoundingBox2d(
                GeoCoordinate2d(Longitude(-180.0), Latitude(-0.1)),
                GeoCoordinate2d(Longitude(-0.1), Latitude(+90.0))),
            1)
        self.assertEqual(2, outkeys.size())
        self.assertTrue(QuadKey(Type_LatLon, 0, 0, 1) in outkeys)
        self.assertTrue(QuadKey(Type_LatLon, 1, 0, 1) in outkeys)

        outkeys = QuadKey.get_keys_from_longitude_latitude_bounding_box(
            Type_LatLon,
            GeoCoordinateBoundingBox2d(
                GeoCoordinate2d(Longitude(+0.0), Latitude(-0.1)),
                GeoCoordinate2d(Longitude(+180.0), Latitude(+90.0))),
            1)
        self.assertEqual(2, outkeys.size())
        self.assertTrue(QuadKey(Type_LatLon, 0, 1, 1) in outkeys)
        self.assertTrue(QuadKey(Type_LatLon, 1, 1, 1) in outkeys)

        outkeys = QuadKey.get_keys_from_longitude_latitude_bounding_box(
            Type_LatLon,
            GeoCoordinateBoundingBox2d(
                GeoCoordinate2d(Longitude(-0.1), Latitude(-0.1)),
                GeoCoordinate2d(Longitude(+0.1), Latitude(+0.1))),
            1)
        self.assertEqual(4, outkeys.size())
        self.assertTrue(QuadKey(Type_LatLon, 0, 0, 1) in outkeys)
        self.assertTrue(QuadKey(Type_LatLon, 0, 1, 1) in outkeys)
        self.assertTrue(QuadKey(Type_LatLon, 1, 0, 1) in outkeys)
        self.assertTrue(QuadKey(Type_LatLon, 1, 1, 1) in outkeys)

    def test_selected_cities(self):
        """Test a given set of known places make sure they work."""
        qk = QuadKey.get_key_from_longitude_latitude_at_depth(
            Type_LatLon, GeoCoordinate2d(Longitude(-122.4183),
                                         Latitude(37.7750)), 1)
        self.assertEqual("0", qk.to_internal_string())
        qk = QuadKey.get_key_from_longitude_latitude_at_depth(
            Type_LatLon, GeoCoordinate2d(Longitude(-122.4183),
                                         Latitude(37.7750)), 2)
        self.assertEqual("02", qk.to_internal_string())
        qk = QuadKey.get_key_from_longitude_latitude_at_depth(
            Type_LatLon, GeoCoordinate2d(Longitude(-122.4183),
                                         Latitude(37.7750)), 3)
        self.assertEqual("021", qk.to_internal_string())
        qk = QuadKey.get_key_from_longitude_latitude_at_depth(
            Type_LatLon, GeoCoordinate2d(Longitude(-122.4183),
                                         Latitude(37.7750)), 4)
        self.assertEqual("0210", qk.to_internal_string())

        qk = QuadKey.get_key_from_longitude_latitude_at_depth(
            Type_LatLon, GeoCoordinate2d(Longitude(+134.9),
                                         Latitude(-67.6)), 3)
        self.assertTrue(QuadKey(Type_LatLon, 0, 6, 3) == qk)
        self.assertEqual("332", qk.to_internal_string())

        qk = QuadKey.get_key_from_longitude_latitude_at_depth(
            Type_LatLon, GeoCoordinate2d(Longitude(+135.0),
                                         Latitude(-67.5)), 3)
        self.assertTrue(QuadKey(Type_LatLon, 1, 7, 3) == qk)
        self.assertEqual("331", qk.to_internal_string())

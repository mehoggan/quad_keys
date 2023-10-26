"""
Unit Tests for lat_long System
"""

from __future__ import print_function

import unittest

from quad_key.quad_key import quad_key
from quad_key.quad_key import type_lat_long
from quad_key.quad_key import geo_coordinate2d
from quad_key.quad_key import geo_coordinate_bounding_box2d
from quad_key.quad_key import longitude
from quad_key.quad_key import latitude


class Testlat_longSystem(unittest.TestCase):
    """Class for running unit tests."""

    def test_is_valid(self):
        """See Testquad_key.test_is_valid."""

    def test_is_root_key(self):
        """See Testquad_key.test_is_root_key."""

    def test_get_parent(self):
        """Test to get parent of a generically formatted quad_key."""
        # Same as BingSystem

    def test_is_my_ancestor(self):
        """Checks to see if specified quad_key.quad_key up in the hierarchy
        is an "ancestor" of the given quad_key.
        """
        # Same as BingSystem

    def test_get_ancestor(self):
        """Gets the ancestor up the tree according to a delta provided."""
        # Same as BingSystem

    def test_get_child(self):
        """Get a single child NE, SE, NW, SW."""
        # Same as BingSystem

    def test_get_children(self):
        """Get all the childern of a quad_key."""
        # Same as BingSystem

    def test_get_descendants(self):
        """Get all the defendants at some delta in the tree."""
        # Same as BingSystem

    def test_get_siblings(self):
        """Test to get siblings of a given quad_key.quad_key."""
        # Same as BingSystem

    def test_get_neighbors(self):
        """Test to get the neighbors of a given quadquad_key."""
        # Same as BingSystem

    def test_to_string_from_string(self):
        """Test to convert an internally formatted string and back."""
        # Same as BingSystem

    def test_get_geo_coordinate_bounds_2d(self):
        """Test to get geographic bounds of quadquad_key."""
        bbox = geo_coordinate_bounding_box2d()

        qk = quad_key(type_lat_long, 0, 0, 0)
        qk.get_geo_coordinate_bounds2d(bbox)
        self.assertTrue(geo_coordinate2d(
            longitude(-180.0), latitude(-90.0)) == bbox.lower_left())
        self.assertTrue(geo_coordinate2d(
            longitude(+180.0), latitude(+90.0)) == bbox.upper_right())

        qk = quad_key(type_lat_long, 0, 0, 1)
        qk.get_geo_coordinate_bounds2d(bbox)
        self.assertTrue(
            bbox.lower_left().get_longitude().near(longitude(-180.0), 1e-6))
        self.assertTrue(
            bbox.lower_left().get_latitude().near(latitude(-90.0), 1e-6))
        self.assertTrue(
            bbox.upper_right().get_longitude().near(longitude(+0.0), 1e-6))
        self.assertTrue(
            bbox.upper_right().get_latitude().near(latitude(+0.0), 1e-6))

        qk = quad_key(type_lat_long, 0, 1, 1)
        qk.get_geo_coordinate_bounds2d(bbox)
        self.assertTrue(
            bbox.lower_left().get_longitude().near(longitude(+0.0), 1e-6))
        self.assertTrue(
            bbox.lower_left().get_latitude().near(latitude(-90.0), 1e-6))
        self.assertTrue(
            bbox.upper_right().get_longitude().near(longitude(+180.0), 1e-6))
        self.assertTrue(
            bbox.upper_right().get_latitude().near(latitude(+0.0), 1e-6))

        qk = quad_key(type_lat_long, 1, 0, 1)
        qk.get_geo_coordinate_bounds2d(bbox)
        self.assertTrue(
            bbox.lower_left().get_longitude().near(longitude(-180.0), 1e-6))
        self.assertTrue(
            bbox.lower_left().get_latitude().near(latitude(+0.0), 1e-6))
        self.assertTrue(
            bbox.upper_right().get_longitude().near(longitude(+0.0), 1e-6))
        self.assertTrue(
            bbox.upper_right().get_latitude().near(latitude(+90.0), 1e-6))

        qk = quad_key(type_lat_long, 1, 1, 1)
        qk.get_geo_coordinate_bounds2d(bbox)
        self.assertTrue(
            bbox.lower_left().get_longitude().near(longitude(+0.0), 1e-6))
        self.assertTrue(
            bbox.lower_left().get_latitude().near(latitude(+0.0), 1e-6))
        self.assertTrue(
            bbox.upper_right().get_longitude().near(longitude(+180.0), 1e-6))
        self.assertTrue(
            bbox.upper_right().get_latitude().near(latitude(+90.0), 1e-6))

    def test_get_key_from_longitude_latitude_at_depth_to_bounds(self):
        """Test to get a quad_key.quad_key from longitude and latitude and
        then get bounds.
        """

        qk = quad_key.get_key_from_longitude_latitude_at_depth(
            type_lat_long, geo_coordinate2d(longitude(-180.0),
                                            latitude(-90)), 0)
        self.assertTrue(quad_key(type_lat_long, 0, 0, 0) == qk)
        self.assertEquals("", qk.to_internal_string())

        # Inclusion here consists of lower left
        #    X------X------X
        #    |   2  |   3  |
        #    |      |      |
        #    X------X------X
        #    |   0  |   1  |
        #    |      |      |
        # ll X------X------X
        qk = quad_key.get_key_from_longitude_latitude_at_depth(
            type_lat_long, geo_coordinate2d(longitude(-180.0),
                                            latitude(-90.0)), 1)
        self.assertTrue(quad_key(type_lat_long, 0, 0, 1) == qk)
        self.assertEquals("2", qk.to_internal_string())
        qk = quad_key.get_key_from_longitude_latitude_at_depth(
            type_lat_long, geo_coordinate2d(longitude(-0.1),
                                            latitude(-90.0)), 1)
        self.assertTrue(quad_key(type_lat_long, 0, 0, 1) == qk)
        self.assertEquals("2", qk.to_internal_string())
        qk = quad_key.get_key_from_longitude_latitude_at_depth(
            type_lat_long, geo_coordinate2d(longitude(-0.1),
                                            latitude(-0.1)), 1)
        self.assertTrue(quad_key(type_lat_long, 0, 0, 1) == qk)
        self.assertEquals("2", qk.to_internal_string())
        qk = quad_key.get_key_from_longitude_latitude_at_depth(
            type_lat_long, geo_coordinate2d(longitude(-180.0),
                                            latitude(-0.1)), 1)
        self.assertTrue(quad_key(type_lat_long, 0, 0, 1) == qk)
        self.assertEquals("2", qk.to_internal_string())

        qk = quad_key.get_key_from_longitude_latitude_at_depth(
            type_lat_long, geo_coordinate2d(longitude(+0.0),
                                            latitude(-90.0)), 1)
        self.assertTrue(quad_key(type_lat_long, 0, 1, 1) == qk)
        self.assertEquals("3", qk.to_internal_string())
        qk = quad_key.get_key_from_longitude_latitude_at_depth(
            type_lat_long, geo_coordinate2d(longitude(+180.0),
                                            latitude(-90.0)), 1)
        self.assertTrue(quad_key(type_lat_long, 0, 1, 1) == qk)
        self.assertEquals("3", qk.to_internal_string())
        qk = quad_key.get_key_from_longitude_latitude_at_depth(
            type_lat_long, geo_coordinate2d(longitude(+180.0),
                                            latitude(-0.1)), 1)
        self.assertTrue(quad_key(type_lat_long, 0, 1, 1) == qk)
        self.assertEquals("3", qk.to_internal_string())
        qk = quad_key.get_key_from_longitude_latitude_at_depth(
            type_lat_long, geo_coordinate2d(longitude(+0.0),
                                            latitude(-0.1)), 1)
        self.assertTrue(quad_key(type_lat_long, 0, 1, 1) == qk)
        self.assertEquals("3", qk.to_internal_string())

        qk = quad_key.get_key_from_longitude_latitude_at_depth(
            type_lat_long, geo_coordinate2d(longitude(-180.0),
                                            latitude(+0.0)), 1)
        self.assertTrue(quad_key(type_lat_long, 1, 0, 1) == qk)
        self.assertEquals("0", qk.to_internal_string())
        qk = quad_key.get_key_from_longitude_latitude_at_depth(
            type_lat_long, geo_coordinate2d(longitude(-0.1),
                                            latitude(+0.0)), 1)
        self.assertTrue(quad_key(type_lat_long, 1, 0, 1) == qk)
        self.assertEquals("0", qk.to_internal_string())
        qk = quad_key.get_key_from_longitude_latitude_at_depth(
            type_lat_long, geo_coordinate2d(longitude(-180.0),
                                            latitude(+90.0)), 1)
        self.assertTrue(quad_key(type_lat_long, 1, 0, 1) == qk)
        self.assertEquals("0", qk.to_internal_string())
        qk = quad_key.get_key_from_longitude_latitude_at_depth(
            type_lat_long, geo_coordinate2d(longitude(-0.1),
                                            latitude(+90.0)), 1)
        self.assertTrue(quad_key(type_lat_long, 1, 0, 1) == qk)
        self.assertEquals("0", qk.to_internal_string())

        qk = quad_key.get_key_from_longitude_latitude_at_depth(
            type_lat_long, geo_coordinate2d(longitude(+0.0),
                                            latitude(+0.0)), 1)
        self.assertTrue(quad_key(type_lat_long, 1, 1, 1) == qk)
        self.assertEquals("1", qk.to_internal_string())
        qk = quad_key.get_key_from_longitude_latitude_at_depth(
            type_lat_long, geo_coordinate2d(longitude(+180.0),
                                            latitude(+0.0)), 1)
        self.assertTrue(quad_key(type_lat_long, 1, 1, 1) == qk)
        self.assertEquals("1", qk.to_internal_string())
        qk = quad_key.get_key_from_longitude_latitude_at_depth(
            type_lat_long, geo_coordinate2d(longitude(+0.0),
                                            latitude(+90.0)), 1)
        self.assertTrue(quad_key(type_lat_long, 1, 1, 1) == qk)
        self.assertEquals("1", qk.to_internal_string())
        qk = quad_key.get_key_from_longitude_latitude_at_depth(
            type_lat_long, geo_coordinate2d(longitude(+180.0),
                                            latitude(+90.0)), 1)
        self.assertTrue(quad_key(type_lat_long, 1, 1, 1) == qk)
        self.assertEquals("1", qk.to_internal_string())

    def test_get_keys_from_longitude_latitude_bounding_box(self):
        """Test to get the bounding box of a quadquad_key."""
        outkeys = quad_key.get_keys_from_longitude_latitude_bounding_box(
            type_lat_long,
            geo_coordinate_bounding_box2d(
                geo_coordinate2d(longitude(-180.0), latitude(+90.0)),
                geo_coordinate2d(longitude(+180.0), latitude(-90.0))),
            0)
        self.assertEquals(1, outkeys.size())
        self.assertTrue(quad_key(type_lat_long, 0, 0, 0) in outkeys)

        outkeys = quad_key.get_keys_from_longitude_latitude_bounding_box(
            type_lat_long,
            geo_coordinate_bounding_box2d(
                geo_coordinate2d(longitude(-180.0), latitude(+90.0)),
                geo_coordinate2d(longitude(+180.0), latitude(-90.0))),
            1)
        self.assertEquals(4, outkeys.size())
        self.assertTrue(quad_key(type_lat_long, 0, 0, 1) in outkeys)
        self.assertTrue(quad_key(type_lat_long, 0, 1, 1) in outkeys)
        self.assertTrue(quad_key(type_lat_long, 1, 0, 1) in outkeys)
        self.assertTrue(quad_key(type_lat_long, 1, 1, 1) in outkeys)

        outkeys = quad_key.get_keys_from_longitude_latitude_bounding_box(
            type_lat_long,
            geo_coordinate_bounding_box2d(
                geo_coordinate2d(longitude(-180.0), latitude(-0.1)),
                geo_coordinate2d(longitude(-0.1), latitude(+90.0))),
            1)
        self.assertEquals(2, outkeys.size())
        self.assertTrue(quad_key(type_lat_long, 0, 0, 1) in outkeys)
        self.assertTrue(quad_key(type_lat_long, 1, 0, 1) in outkeys)

        outkeys = quad_key.get_keys_from_longitude_latitude_bounding_box(
            type_lat_long,
            geo_coordinate_bounding_box2d(
                geo_coordinate2d(longitude(+0.0), latitude(-0.1)),
                geo_coordinate2d(longitude(+180.0), latitude(+90.0))),
            1)
        self.assertEquals(2, outkeys.size())
        self.assertTrue(quad_key(type_lat_long, 0, 1, 1) in outkeys)
        self.assertTrue(quad_key(type_lat_long, 1, 1, 1) in outkeys)

        outkeys = quad_key.get_keys_from_longitude_latitude_bounding_box(
            type_lat_long,
            geo_coordinate_bounding_box2d(
                geo_coordinate2d(longitude(-0.1), latitude(-0.1)),
                geo_coordinate2d(longitude(+0.1), latitude(+0.1))),
            1)
        self.assertEquals(4, outkeys.size())
        self.assertTrue(quad_key(type_lat_long, 0, 0, 1) in outkeys)
        self.assertTrue(quad_key(type_lat_long, 0, 1, 1) in outkeys)
        self.assertTrue(quad_key(type_lat_long, 1, 0, 1) in outkeys)
        self.assertTrue(quad_key(type_lat_long, 1, 1, 1) in outkeys)

    def test_selected_cities(self):
        """Test a given set of known places make sure they work."""
        qk = quad_key.get_key_from_longitude_latitude_at_depth(
            type_lat_long, geo_coordinate2d(longitude(-122.4183),
                                            latitude(37.7750)), 1)
        self.assertEquals("0", qk.to_internal_string())
        qk = quad_key.get_key_from_longitude_latitude_at_depth(
            type_lat_long, geo_coordinate2d(longitude(-122.4183),
                                            latitude(37.7750)), 2)
        self.assertEquals("02", qk.to_internal_string())
        qk = quad_key.get_key_from_longitude_latitude_at_depth(
            type_lat_long, geo_coordinate2d(longitude(-122.4183),
                                            latitude(37.7750)), 3)
        self.assertEquals("021", qk.to_internal_string())
        qk = quad_key.get_key_from_longitude_latitude_at_depth(
            type_lat_long, geo_coordinate2d(longitude(-122.4183),
                                            latitude(37.7750)), 4)
        self.assertEquals("0210", qk.to_internal_string())

        qk = quad_key.get_key_from_longitude_latitude_at_depth(
            type_lat_long, geo_coordinate2d(longitude(+134.9),
                                            latitude(-67.6)), 3)
        self.assertTrue(quad_key(type_lat_long, 0, 6, 3) == qk)
        self.assertEquals("332", qk.to_internal_string())

        qk = quad_key.get_key_from_longitude_latitude_at_depth(
            type_lat_long, geo_coordinate2d(longitude(+135.0),
                                            latitude(-67.5)), 3)
        self.assertTrue(quad_key(type_lat_long, 1, 7, 3) == qk)
        self.assertEquals("331", qk.to_internal_string())

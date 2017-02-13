"""
Unit Tests for geo_coordinate2d
"""

from __future__ import print_function

import unittest

from quad_key.quad_key import geo_coordinate2d
from quad_key.quad_key import longitude
from quad_key.quad_key import latitude


class TestGeoCoordinate2d(unittest.TestCase):
    """Class for running unit tests."""

    def test_default_ctor(self):
        """Test default ctor."""
        empty = geo_coordinate2d()
        self.assertEquals(longitude(0.0), empty.get_longitude())
        self.assertEquals(latitude(0.0), empty.get_latitude())

    def test_ctor(self):
        """Test ctor."""
        coord = geo_coordinate2d(longitude(0.0), latitude(0.0))
        self.assertEquals(longitude(0.0), coord.get_longitude())
        self.assertEquals(latitude(0.0), coord.get_latitude())

        coord = geo_coordinate2d(longitude(-180.001), latitude(-95.0))
        self.assertEquals(longitude(-180.0), coord.get_longitude())
        self.assertEquals(latitude(-90.0), coord.get_latitude())

        coord = geo_coordinate2d(longitude(-180.001), latitude(95.0))
        self.assertEquals(longitude(-180.0), coord.get_longitude())
        self.assertEquals(latitude(90.0), coord.get_latitude())

        coord = geo_coordinate2d(longitude(180.001), latitude(95.0))
        self.assertEquals(longitude(180.0), coord.get_longitude())
        self.assertEquals(latitude(90.0), coord.get_latitude())

        coord = geo_coordinate2d(longitude(180.001), latitude(-95.0))
        self.assertEquals(longitude(180.0), coord.get_longitude())
        self.assertEquals(latitude(-90.0), coord.get_latitude())

    def test_near(self):
        """Test to see if one coord is near another."""
        lon = longitude(0.001)
        self.assertTrue(lon.near(longitude(0.0009), 1e-3))

        lon = longitude(0.001)
        self.assertFalse(lon.near(longitude(0.0009), 1e-4))

        lat = latitude(0.001)
        self.assertTrue(lat.near(latitude(0.0009), 1e-3))

        lat = latitude(0.001)
        self.assertFalse(lat.near(latitude(0.0009), 1e-4))

        coord = geo_coordinate2d(longitude(0.001), latitude(0.001))
        self.assertTrue(coord.near(
            geo_coordinate2d(longitude(0.0009), latitude(0.0009)), 1e-3))

        coord = geo_coordinate2d(longitude(0.001), latitude(0.001))
        self.assertFalse(coord.near(
            geo_coordinate2d(longitude(0.001), latitude(0.0009)), 1e-4))

        coord = geo_coordinate2d(longitude(0.001), latitude(0.001))
        self.assertFalse(coord.near(
            geo_coordinate2d(longitude(0.0009), latitude(0.001)), 1e-4))

    def test_operator_less_than(self):
        """Tests less than operator."""
        sw = geo_coordinate2d(longitude(-0.1), latitude(-0.1))
        ne = geo_coordinate2d(longitude(+0.1), latitude(+0.1))

        self.assertTrue(sw.get_longitude() < ne.get_longitude())
        self.assertTrue(sw.get_latitude() < ne.get_latitude())

    def test_operator_less_than_or_equal(self):
        """Tests less than or equal operator."""
        sw = geo_coordinate2d(longitude(-0.1), latitude(-0.1))
        ne = geo_coordinate2d(longitude(+0.1), latitude(+0.1))
        self.assertTrue(sw.get_longitude() <= ne.get_longitude())
        self.assertTrue(sw.get_latitude() <= ne.get_latitude())

        sw = geo_coordinate2d(longitude(-0.1), latitude(-0.1))
        ne = geo_coordinate2d(longitude(-0.1), latitude(-0.1))
        self.assertTrue(sw.get_longitude() <= ne.get_longitude())
        self.assertTrue(sw.get_latitude() <= ne.get_latitude())

    def test_operator_equal(self):
        """Tests for equality of geo_coordinate2d."""
        sw = geo_coordinate2d(longitude(-0.1), latitude(-0.1))
        ne = geo_coordinate2d(longitude(-0.1), latitude(-0.1))
        self.assertEquals(sw.get_longitude(), ne.get_longitude())
        self.assertEquals(sw.get_latitude(), ne.get_latitude())

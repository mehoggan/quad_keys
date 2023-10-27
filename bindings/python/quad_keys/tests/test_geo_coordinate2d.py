"""
Unit Tests for GeoCoordinate2d
"""

from __future__ import print_function

import unittest

from quad_keys.quad_keys import GeoCoordinate2d
from quad_keys.quad_keys import Longitude
from quad_keys.quad_keys import Latitude


class TestGeoCoordinate2d(unittest.TestCase):
    """Class for running unit tests."""

    def test_default_ctor(self):
        """Test default ctor."""
        empty = GeoCoordinate2d()
        self.assertEqual(Longitude(0.0), empty.get_longitude())
        self.assertEqual(Latitude(0.0), empty.get_latitude())

    def test_ctor(self):
        """Test ctor."""
        coord = GeoCoordinate2d(Longitude(0.0), Latitude(0.0))
        self.assertEqual(Longitude(0.0), coord.get_longitude())
        self.assertEqual(Latitude(0.0), coord.get_latitude())

        coord = GeoCoordinate2d(Longitude(-180.001), Latitude(-95.0))
        self.assertEqual(Longitude(-180.0), coord.get_longitude())
        self.assertEqual(Latitude(-90.0), coord.get_latitude())

        coord = GeoCoordinate2d(Longitude(-180.001), Latitude(95.0))
        self.assertEqual(Longitude(-180.0), coord.get_longitude())
        self.assertEqual(Latitude(90.0), coord.get_latitude())

        coord = GeoCoordinate2d(Longitude(180.001), Latitude(95.0))
        self.assertEqual(Longitude(180.0), coord.get_longitude())
        self.assertEqual(Latitude(90.0), coord.get_latitude())

        coord = GeoCoordinate2d(Longitude(180.001), Latitude(-95.0))
        self.assertEqual(Longitude(180.0), coord.get_longitude())
        self.assertEqual(Latitude(-90.0), coord.get_latitude())

    def test_near(self):
        """Test to see if one coord is near another."""
        lon = Longitude(0.001)
        self.assertTrue(lon.near(Longitude(0.0009), 1e-3))

        lon = Longitude(0.001)
        self.assertFalse(lon.near(Longitude(0.0009), 1e-4))

        lat = Latitude(0.001)
        self.assertTrue(lat.near(Latitude(0.0009), 1e-3))

        lat = Latitude(0.001)
        self.assertFalse(lat.near(Latitude(0.0009), 1e-4))

        coord = GeoCoordinate2d(Longitude(0.001), Latitude(0.001))
        self.assertTrue(coord.near(
            GeoCoordinate2d(Longitude(0.0009), Latitude(0.0009)), 1e-3))

        coord = GeoCoordinate2d(Longitude(0.001), Latitude(0.001))
        self.assertFalse(coord.near(
            GeoCoordinate2d(Longitude(0.001), Latitude(0.0009)), 1e-4))

        coord = GeoCoordinate2d(Longitude(0.001), Latitude(0.001))
        self.assertFalse(coord.near(
            GeoCoordinate2d(Longitude(0.0009), Latitude(0.001)), 1e-4))

    def test_operator_less_than(self):
        """Tests less than operator."""
        sw = GeoCoordinate2d(Longitude(-0.1), Latitude(-0.1))
        ne = GeoCoordinate2d(Longitude(+0.1), Latitude(+0.1))

        self.assertTrue(sw.get_longitude() < ne.get_longitude())
        self.assertTrue(sw.get_latitude() < ne.get_latitude())

    def test_operator_less_than_or_equal(self):
        """Tests less than or equal operator."""
        sw = GeoCoordinate2d(Longitude(-0.1), Latitude(-0.1))
        ne = GeoCoordinate2d(Longitude(+0.1), Latitude(+0.1))
        self.assertTrue(sw.get_longitude() <= ne.get_longitude())
        self.assertTrue(sw.get_latitude() <= ne.get_latitude())

        sw = GeoCoordinate2d(Longitude(-0.1), Latitude(-0.1))
        ne = GeoCoordinate2d(Longitude(-0.1), Latitude(-0.1))
        self.assertTrue(sw.get_longitude() <= ne.get_longitude())
        self.assertTrue(sw.get_latitude() <= ne.get_latitude())

    def test_operator_equal(self):
        """Tests for equality of GeoCoordinate2d."""
        sw = GeoCoordinate2d(Longitude(-0.1), Latitude(-0.1))
        ne = GeoCoordinate2d(Longitude(-0.1), Latitude(-0.1))
        self.assertEqual(sw.get_longitude(), ne.get_longitude())
        self.assertEqual(sw.get_latitude(), ne.get_latitude())

"""
Unit Tests for GeoCoordinate2d
"""

from __future__ import print_function
import unittest
from quadkey import GeoCoordinate2d
from quadkey import Longitude
from quadkey import Latitude


class TestGeoCoordinate2d(unittest.TestCase):
    """
    Class for running unit tests.
    """

    def test_default_ctor(self):
        """
        Test default ctor
        """
        empty = GeoCoordinate2d()
        self.assertEquals(Longitude(0.0), empty.longitude())
        self.assertEquals(Latitude(0.0), empty.latitude())

    def test_ctor(self):
        """
        Test ctor
        """
        coord = GeoCoordinate2d(Longitude(0.0), Latitude(0.0))
        self.assertEquals(Longitude(0.0), coord.longitude())
        self.assertEquals(Latitude(0.0), coord.latitude())

        coord = GeoCoordinate2d(Longitude(-180.001), Latitude(-95.0))
        self.assertEquals(Longitude(-180.0), coord.longitude())
        self.assertEquals(Latitude(-90.0), coord.latitude())

        coord = GeoCoordinate2d(Longitude(-180.001), Latitude(95.0))
        self.assertEquals(Longitude(-180.0), coord.longitude())
        self.assertEquals(Latitude(90.0), coord.latitude())

        coord = GeoCoordinate2d(Longitude(180.001), Latitude(95.0))
        self.assertEquals(Longitude(180.0), coord.longitude())
        self.assertEquals(Latitude(90.0), coord.latitude())

        coord = GeoCoordinate2d(Longitude(180.001), Latitude(-95.0))
        self.assertEquals(Longitude(180.0), coord.longitude())
        self.assertEquals(Latitude(-90.0), coord.latitude())

    def test_near(self):
        """
        Test to see if one coord is near another
        """
        lon = Longitude(0.001)
        self.assertTrue(lon.near(Longitude(0.0009), 1e-3))

        lon = Longitude(0.001)
        self.assertFalse(lon.near(Longitude(0.0009), 1e-4))

        lat = Latitude(0.001)
        self.assertTrue(lat.near(Latitude(0.0009), 1e-3))

        lat = Latitude(0.001)
        self.assertFalse(lat.near(Latitude(0.0009), 1e-4))

        coord = GeoCoordinate2d(Longitude(0.001), Latitude(0.001))
        self.assertTrue(coord.near(GeoCoordinate2d(Longitude(0.0009),
                                                   Latitude(0.0009)), 1e-3))

        coord = GeoCoordinate2d(Longitude(0.001), Latitude(0.001))
        self.assertFalse(coord.near(GeoCoordinate2d(Longitude(0.001),
                                                    Latitude(0.0009)), 1e-4))

        coord = GeoCoordinate2d(Longitude(0.001), Latitude(0.001))
        self.assertFalse(coord.near(GeoCoordinate2d(Longitude(0.0009),
                                                    Latitude(0.001)), 1e-4))

    def test_operator_less_than(self):
        """
        Tests less than operator.
        """
        sw = GeoCoordinate2d(Longitude(-0.1), Latitude(-0.1))
        ne = GeoCoordinate2d(Longitude(+0.1), Latitude(+0.1))

        self.assertTrue(sw.longitude() < ne.longitude())
        self.assertTrue(sw.latitude() < ne.latitude())

    def test_operator_less_than_or_equal(self):
        """
        Tests less than or equal operator
        """
        sw = GeoCoordinate2d(Longitude(-0.1), Latitude(-0.1))
        ne = GeoCoordinate2d(Longitude(+0.1), Latitude(+0.1))
        self.assertTrue(sw.longitude() <= ne.longitude())
        self.assertTrue(sw.latitude() <= ne.latitude())

        sw = GeoCoordinate2d(Longitude(-0.1), Latitude(-0.1))
        ne = GeoCoordinate2d(Longitude(-0.1), Latitude(-0.1))
        self.assertTrue(sw.longitude() <= ne.longitude())
        self.assertTrue(sw.latitude() <= ne.latitude())

    def test_operator_equal(self):
        """
        Tests for equality of GeoCoordinate2d
        """
        sw = GeoCoordinate2d(Longitude(-0.1), Latitude(-0.1))
        ne = GeoCoordinate2d(Longitude(-0.1), Latitude(-0.1))
        self.assertEquals(sw.longitude(), ne.longitude())
        self.assertEquals(sw.latitude(), ne.latitude())


def main():
    """
    Bootstrap function for this module
    """
    suite = unittest.TestLoader().loadTestsFromTestCase(TestGeoCoordinate2d)
    unittest.TextTestRunner(verbosity=2).run(suite)

"""
Unit Tests for GeoCoordinateBoundingBox2d
"""

from __future__ import print_function
import unittest
from quadkey import GeoCoordinateBoundingBox2d
from quadkey import GeoCoordinate2d
from quadkey import Longitude
from quadkey import Latitude


class TestGeoCoordinateBoundingBox2d(unittest.TestCase):
    """
    Class for running unit tests.
    """

    def test_default_ctor(self):
        empty = GeoCoordinateBoundingBox2d()
        self.assertFalse(empty.isValid())
        self.assertFalse(empty.contains(GeoCoordinate2d(Longitude(0.0),
                                                        Latitude(0.0))))

    def test_ctor_standard_construction(self):
        geobox = GeoCoordinateBoundingBox2d(GeoCoordinate2d(Longitude(0.0),
                                                            Latitude(0.0)),
                                            GeoCoordinate2d(Longitude(180.0),
                                                            Latitude(90.0)))
        self.assertEquals(GeoCoordinate2d(Longitude(0.0), Latitude(0.0)),
                          geobox.lowerLeft())
        self.assertEquals(GeoCoordinate2d(Longitude(180.0), Latitude(90.0)),
                          geobox.upperRight())
        self.assertTrue(geobox.isValid())

        geobox = GeoCoordinateBoundingBox2d(GeoCoordinate2d(Longitude(0.0),
                                                            Latitude(90.0)),
                                            GeoCoordinate2d(Longitude(180.0),
                                                            Latitude(0.0)))
        self.assertEquals(GeoCoordinate2d(Longitude(0.0), Latitude(0.0)),
                          geobox.lowerLeft())
        self.assertEquals(GeoCoordinate2d(Longitude(180.0), Latitude(90.0)),
                          geobox.upperRight())
        self.assertTrue(geobox.isValid())

        geobox = GeoCoordinateBoundingBox2d(GeoCoordinate2d(Longitude(180.0),
                                                            Latitude(0.0)),
                                            GeoCoordinate2d(Longitude(0.0),
                                                            Latitude(90.0)))
        self.assertEquals(GeoCoordinate2d(Longitude(0.0), Latitude(0.0)),
                          geobox.lowerLeft())
        self.assertEquals(GeoCoordinate2d(Longitude(180.0), Latitude(90.0)),
                          geobox.upperRight())
        self.assertTrue(geobox.isValid())

        geobox = GeoCoordinateBoundingBox2d(GeoCoordinate2d(Longitude(180.0),
                                                            Latitude(0.0)),
                                            GeoCoordinate2d(Longitude(0.0),
                                                            Latitude(90.0)))
        self.assertEquals(GeoCoordinate2d(Longitude(0.0), Latitude(0.0)),
                          geobox.lowerLeft())
        self.assertEquals(GeoCoordinate2d(Longitude(180.0), Latitude(90.0)),
                          geobox.upperRight())
        self.assertTrue(geobox.isValid())

    def test_ctor_linear_box_and_point(self):
        geobox = GeoCoordinateBoundingBox2d(GeoCoordinate2d(Longitude(0.0),
                                                            Latitude(0.0)),
                                            GeoCoordinate2d(Longitude(0.0),
                                                            Latitude(90.0)))
        self.assertEquals(GeoCoordinate2d(Longitude(0.0), Latitude(0.0)),
                          geobox.lowerLeft())
        self.assertEquals(GeoCoordinate2d(Longitude(0.0), Latitude(90.0)),
                          geobox.upperRight())
        self.assertTrue(geobox.isValid())

        geobox = GeoCoordinateBoundingBox2d(GeoCoordinate2d(Longitude(0.0),
                                                            Latitude(0.0)),
                                            GeoCoordinate2d(Longitude(180.0),
                                                            Latitude(0.0)))
        self.assertEquals(GeoCoordinate2d(Longitude(0.0), Latitude(0.0)),
                          geobox.lowerLeft())
        self.assertEquals(GeoCoordinate2d(Longitude(180.0), Latitude(0.0)),
                          geobox.upperRight())
        self.assertTrue(geobox.isValid())

        geobox = GeoCoordinateBoundingBox2d(GeoCoordinate2d(Longitude(0.0),
                                                            Latitude(0.0)),
                                            GeoCoordinate2d(Longitude(0.0),
                                                            Latitude(0.0)))
        self.assertTrue(geobox.isValid())

    def test_contains_or_not(self):
        geobox = GeoCoordinateBoundingBox2d(GeoCoordinate2d(Longitude(90.0),
                                                            Latitude(45.0)),
                                            GeoCoordinate2d(Longitude(-90.0),
                                                            Latitude(-45.0)))
        self.assertTrue(geobox.isValid())
        self.assertTrue(geobox.contains(GeoCoordinate2d(Longitude(0.0),
                                                        Latitude(0.0))))
        self.assertTrue(geobox.contains(GeoCoordinate2d(Longitude(90.0),
                                                        Latitude(45.0))))
        self.assertTrue(geobox.contains(GeoCoordinate2d(Longitude(90.0),
                                                        Latitude(-45.0))))
        self.assertTrue(geobox.contains(GeoCoordinate2d(Longitude(-90.0),
                                                        Latitude(-45.0))))
        self.assertTrue(geobox.contains(GeoCoordinate2d(Longitude(-90.0),
                                                        Latitude(45.0))))
        self.assertFalse(geobox.contains(GeoCoordinate2d(Longitude(90.01),
                                                         Latitude(45.01))))
        self.assertFalse(geobox.contains(GeoCoordinate2d(Longitude(90.01),
                                                         Latitude(-45.01))))
        self.assertFalse(geobox.contains(GeoCoordinate2d(Longitude(-90.01),
                                                         Latitude(-45.01))))
        self.assertFalse(geobox.contains(GeoCoordinate2d(Longitude(-90.01),
                                                         Latitude(45.01))))

        geobox = GeoCoordinateBoundingBox2d(GeoCoordinate2d(Longitude(90.0),
                                                            Latitude(45.0)),
                                            GeoCoordinate2d(Longitude(0.1),
                                                            Latitude(0.1)))
        self.assertEquals(GeoCoordinate2d(Longitude(0.1), Latitude(0.1)),
                          geobox.lowerLeft())
        self.assertTrue(GeoCoordinate2d(Longitude(90.0), Latitude(45.0)),
                        geobox.upperRight())
        self.assertTrue(geobox.isValid())
        self.assertTrue(geobox.contains(GeoCoordinate2d(Longitude(90.0),
                                                        Latitude(45.0))))
        self.assertTrue(geobox.contains(GeoCoordinate2d(Longitude(90.0),
                                                        Latitude(0.1))))
        self.assertTrue(geobox.contains(GeoCoordinate2d(Longitude(0.1),
                                                        Latitude(0.1))))
        self.assertTrue(geobox.contains(GeoCoordinate2d(Longitude(0.1),
                                                        Latitude(45.0))))
        self.assertFalse(geobox.contains(GeoCoordinate2d(Longitude(90.01),
                                                         Latitude(45.01))))
        self.assertFalse(geobox.contains(GeoCoordinate2d(Longitude(90.01),
                                                         Latitude(0.0))))
        self.assertFalse(geobox.contains(GeoCoordinate2d(Longitude(0.0),
                                                         Latitude(0.0))))
        self.assertFalse(geobox.contains(GeoCoordinate2d(Longitude(0.0),
                                                         Latitude(45.01))))

    def test_grow_to_contain(self):
        geobox = GeoCoordinateBoundingBox2d(GeoCoordinate2d(Longitude(-90.0),
                                                            Latitude(-45.0)),
                                            GeoCoordinate2d(Longitude(90.0),
                                                            Latitude(45.0)))
        self.assertEquals(GeoCoordinate2d(Longitude(-90.0), Latitude(-45.0)),
                          geobox.lowerLeft())
        self.assertEquals(GeoCoordinate2d(Longitude(90.0), Latitude(45.0)),
                          geobox.upperRight())
        geobox.growToContain(GeoCoordinate2d(Longitude(180.0), Latitude(90.0)))
        self.assertEquals(GeoCoordinate2d(Longitude(-90.0), Latitude(-45.0)),
                          geobox.lowerLeft())
        self.assertEquals(GeoCoordinate2d(Longitude(180.0), Latitude(90.0)),
                          geobox.upperRight())

        geobox = GeoCoordinateBoundingBox2d(GeoCoordinate2d(Longitude(-90.0),
                                                            Latitude(-45.0)),
                                            GeoCoordinate2d(Longitude(90.0),
                                                            Latitude(45.0)))
        self.assertEquals(GeoCoordinate2d(Longitude(-90.0), Latitude(-45.0)),
                          geobox.lowerLeft())
        self.assertEquals(GeoCoordinate2d(Longitude(90.0), Latitude(45.0)),
                          geobox.upperRight())
        geobox.growToContain(
            GeoCoordinate2d(Longitude(-180.0), Latitude(-90.0)))
        self.assertEquals(GeoCoordinate2d(Longitude(-180.0), Latitude(-90.0)),
                          geobox.lowerLeft())
        self.assertEquals(GeoCoordinate2d(Longitude(90.0), Latitude(45.0)),
                          geobox.upperRight())

        geobox = GeoCoordinateBoundingBox2d(GeoCoordinate2d(Longitude(-90.0),
                                                            Latitude(-45.0)),
                                            GeoCoordinate2d(Longitude(90.0),
                                                            Latitude(45.0)))
        self.assertTrue(GeoCoordinate2d(Longitude(-90.0), Latitude(-45.0)),
                        geobox.lowerLeft())
        self.assertEquals(GeoCoordinate2d(Longitude(90.0), Latitude(45.0)),
                          geobox.upperRight())
        geobox.growToContain(GeoCoordinate2d(Longitude(-180.0), Latitude(90.0)))
        self.assertEquals(GeoCoordinate2d(Longitude(-180.0), Latitude(-45.0)),
                          geobox.lowerLeft())
        self.assertEquals(GeoCoordinate2d(Longitude(90.0), Latitude(90.0)),
                          geobox.upperRight())

        geobox = GeoCoordinateBoundingBox2d(GeoCoordinate2d(Longitude(-90.0),
                                                            Latitude(-45.0)),
                                            GeoCoordinate2d(Longitude(90.0),
                                                            Latitude(45.0)))
        self.assertEquals(GeoCoordinate2d(Longitude(-90.0), Latitude(-45.0)),
                          geobox.lowerLeft())
        self.assertEquals(GeoCoordinate2d(Longitude(90.0), Latitude(45.0)),
                          geobox.upperRight())
        geobox.growToContain(GeoCoordinate2d(Longitude(180.0), Latitude(-90.0)))
        self.assertEquals(GeoCoordinate2d(Longitude(-90.0), Latitude(-90.0)),
                          geobox.lowerLeft())
        self.assertEquals(GeoCoordinate2d(Longitude(180.0), Latitude(45.0)),
                          geobox.upperRight())

        geobox = GeoCoordinateBoundingBox2d(GeoCoordinate2d(Longitude(-90.0),
                                                            Latitude(-45.0)),
                                            GeoCoordinate2d(Longitude(90.0),
                                                            Latitude(45.0)))
        self.assertEquals(GeoCoordinate2d(Longitude(-90.0), Latitude(-45.0)),
                          geobox.lowerLeft())
        self.assertEquals(GeoCoordinate2d(Longitude(90.0), Latitude(45.0)),
                          geobox.upperRight())
        geobox.growToContain(GeoCoordinate2d(Longitude(0.0), Latitude(0.0)))
        self.assertEquals(GeoCoordinate2d(Longitude(-90.0), Latitude(-45.0)),
                          geobox.lowerLeft())
        self.assertEquals(GeoCoordinate2d(Longitude(90.0), Latitude(45.0)),
                          geobox.upperRight())


def main():
    """
    Bootstrap function for this module
    """
    suite = unittest.TestLoader().loadTestsFromTestCase(
        TestGeoCoordinateBoundingBox2d)
    unittest.TextTestRunner(verbosity=2).run(suite)

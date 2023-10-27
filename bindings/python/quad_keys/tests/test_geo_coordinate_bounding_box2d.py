"""
Unit Tests for GeoCoordinateBoundingBox2d
"""

from __future__ import print_function

import unittest

from quad_keys.quad_keys import GeoCoordinateBoundingBox2d
from quad_keys.quad_keys import GeoCoordinate2d
from quad_keys.quad_keys import Longitude
from quad_keys.quad_keys import Latitude


class TestGeoCoordinateBoundingBox2d(unittest.TestCase):
    """Class for running unit tests."""

    def test_default_ctor(self):
        """default ctor construction."""
        empty = GeoCoordinateBoundingBox2d()
        self.assertFalse(empty.is_valid())
        self.assertFalse(empty.contains(GeoCoordinate2d(Longitude(0.0),
                                                        Latitude(0.0))))

    def test_ctor_standard_construction(self):
        """default ctor construction."""
        geobox = GeoCoordinateBoundingBox2d(
            GeoCoordinate2d(Longitude(0.0), Latitude(0.0)),
            GeoCoordinate2d(Longitude(180.0), Latitude(90.0)))
        self.assertEqual(GeoCoordinate2d(Longitude(0.0), Latitude(0.0)),
                         geobox.lower_left())
        self.assertEqual(GeoCoordinate2d(Longitude(180.0), Latitude(90.0)),
                         geobox.upper_right())
        self.assertTrue(geobox.is_valid())

        geobox = GeoCoordinateBoundingBox2d(
            GeoCoordinate2d(Longitude(0.0), Latitude(90.0)),
            GeoCoordinate2d(Longitude(180.0), Latitude(0.0)))
        self.assertEqual(GeoCoordinate2d(Longitude(0.0), Latitude(0.0)),
                         geobox.lower_left())
        self.assertEqual(GeoCoordinate2d(Longitude(180.0), Latitude(90.0)),
                         geobox.upper_right())
        self.assertTrue(geobox.is_valid())

        geobox = GeoCoordinateBoundingBox2d(
            GeoCoordinate2d(Longitude(180.0), Latitude(0.0)),
            GeoCoordinate2d(Longitude(0.0), Latitude(90.0)))
        self.assertEqual(GeoCoordinate2d(Longitude(0.0), Latitude(0.0)),
                         geobox.lower_left())
        self.assertEqual(GeoCoordinate2d(Longitude(180.0), Latitude(90.0)),
                         geobox.upper_right())
        self.assertTrue(geobox.is_valid())

        geobox = GeoCoordinateBoundingBox2d(
            GeoCoordinate2d(Longitude(180.0), Latitude(0.0)),
            GeoCoordinate2d(Longitude(0.0), Latitude(90.0)))
        self.assertEqual(GeoCoordinate2d(Longitude(0.0), Latitude(0.0)),
                         geobox.lower_left())
        self.assertEqual(GeoCoordinate2d(Longitude(180.0), Latitude(90.0)),
                         geobox.upper_right())
        self.assertTrue(geobox.is_valid())

    def test_ctor_linear_box_and_point(self):
        """default ctor construction."""
        geobox = GeoCoordinateBoundingBox2d(
            GeoCoordinate2d(Longitude(0.0), Latitude(0.0)),
            GeoCoordinate2d(Longitude(0.0), Latitude(90.0)))
        self.assertEqual(GeoCoordinate2d(Longitude(0.0), Latitude(0.0)),
                         geobox.lower_left())
        self.assertEqual(GeoCoordinate2d(Longitude(0.0), Latitude(90.0)),
                         geobox.upper_right())
        self.assertTrue(geobox.is_valid())

        geobox = GeoCoordinateBoundingBox2d(
            GeoCoordinate2d(Longitude(0.0), Latitude(0.0)),
            GeoCoordinate2d(Longitude(180.0), Latitude(0.0)))
        self.assertEqual(GeoCoordinate2d(Longitude(0.0), Latitude(0.0)),
                         geobox.lower_left())
        self.assertEqual(GeoCoordinate2d(Longitude(180.0), Latitude(0.0)),
                         geobox.upper_right())
        self.assertTrue(geobox.is_valid())

        geobox = GeoCoordinateBoundingBox2d(
            GeoCoordinate2d(Longitude(0.0), Latitude(0.0)),
            GeoCoordinate2d(Longitude(0.0), Latitude(0.0)))
        self.assertTrue(geobox.is_valid())

    def test_contains_or_not(self):
        """containment test."""
        geobox = GeoCoordinateBoundingBox2d(
            GeoCoordinate2d(Longitude(90.0), Latitude(45.0)),
            GeoCoordinate2d(Longitude(-90.0), Latitude(-45.0)))
        self.assertTrue(geobox.is_valid())
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

        geobox = GeoCoordinateBoundingBox2d(
            GeoCoordinate2d(Longitude(90.0), Latitude(45.0)),
            GeoCoordinate2d(Longitude(0.1), Latitude(0.1)))
        self.assertEqual(GeoCoordinate2d(Longitude(0.1), Latitude(0.1)),
                         geobox.lower_left())
        self.assertTrue(GeoCoordinate2d(Longitude(90.0), Latitude(45.0)),
                        geobox.upper_right())
        self.assertTrue(geobox.is_valid())
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
        """grow to contain test"""
        geobox = GeoCoordinateBoundingBox2d(
            GeoCoordinate2d(Longitude(-90.0), Latitude(-45.0)),
            GeoCoordinate2d(Longitude(90.0), Latitude(45.0)))
        self.assertEqual(GeoCoordinate2d(Longitude(-90.0),
                                         Latitude(-45.0)),
                         geobox.lower_left())
        self.assertEqual(GeoCoordinate2d(Longitude(90.0), Latitude(45.0)),
                         geobox.upper_right())
        geobox.grow_to_contain(GeoCoordinate2d(Longitude(180.0),
                                               Latitude(90.0)))
        self.assertEqual(GeoCoordinate2d(Longitude(-90.0),
                                         Latitude(-45.0)),
                         geobox.lower_left())
        self.assertEqual(GeoCoordinate2d(Longitude(180.0), Latitude(90.0)),
                         geobox.upper_right())

        geobox = GeoCoordinateBoundingBox2d(
            GeoCoordinate2d(Longitude(-90.0), Latitude(-45.0)),
            GeoCoordinate2d(Longitude(90.0), Latitude(45.0)))
        self.assertEqual(GeoCoordinate2d(Longitude(-90.0),
                                         Latitude(-45.0)),
                         geobox.lower_left())
        self.assertEqual(GeoCoordinate2d(Longitude(90.0), Latitude(45.0)),
                         geobox.upper_right())
        geobox.grow_to_contain(
            GeoCoordinate2d(Longitude(-180.0), Latitude(-90.0)))
        self.assertEqual(GeoCoordinate2d(Longitude(-180.0),
                                         Latitude(-90.0)),
                         geobox.lower_left())
        self.assertEqual(GeoCoordinate2d(Longitude(90.0), Latitude(45.0)),
                         geobox.upper_right())

        geobox = GeoCoordinateBoundingBox2d(
            GeoCoordinate2d(Longitude(-90.0), Latitude(-45.0)),
            GeoCoordinate2d(Longitude(90.0), Latitude(45.0)))
        self.assertTrue(GeoCoordinate2d(Longitude(-90.0), Latitude(-45.0)),
                        geobox.lower_left())
        self.assertEqual(GeoCoordinate2d(Longitude(90.0), Latitude(45.0)),
                         geobox.upper_right())
        geobox.grow_to_contain(GeoCoordinate2d(Longitude(-180.0),
                                               Latitude(90.0)))
        self.assertEqual(GeoCoordinate2d(Longitude(-180.0),
                                         Latitude(-45.0)),
                         geobox.lower_left())
        self.assertEqual(GeoCoordinate2d(Longitude(90.0), Latitude(90.0)),
                         geobox.upper_right())

        geobox = GeoCoordinateBoundingBox2d(
            GeoCoordinate2d(Longitude(-90.0), Latitude(-45.0)),
            GeoCoordinate2d(Longitude(90.0), Latitude(45.0)))
        self.assertEqual(GeoCoordinate2d(Longitude(-90.0),
                                         Latitude(-45.0)),
                         geobox.lower_left())
        self.assertEqual(GeoCoordinate2d(Longitude(90.0), Latitude(45.0)),
                         geobox.upper_right())
        geobox.grow_to_contain(GeoCoordinate2d(Longitude(180.0),
                                               Latitude(-90.0)))
        self.assertEqual(GeoCoordinate2d(Longitude(-90.0),
                                         Latitude(-90.0)),
                         geobox.lower_left())
        self.assertEqual(GeoCoordinate2d(Longitude(180.0),
                                         Latitude(45.0)),
                         geobox.upper_right())

        geobox = GeoCoordinateBoundingBox2d(
            GeoCoordinate2d(Longitude(-90.0), Latitude(-45.0)),
            GeoCoordinate2d(Longitude(90.0), Latitude(45.0)))
        self.assertEqual(GeoCoordinate2d(Longitude(-90.0),
                                         Latitude(-45.0)),
                         geobox.lower_left())
        self.assertEqual(GeoCoordinate2d(Longitude(90.0), Latitude(45.0)),
                         geobox.upper_right())
        geobox.grow_to_contain(GeoCoordinate2d(Longitude(0.0),
                                               Latitude(0.0)))
        self.assertEqual(GeoCoordinate2d(Longitude(-90.0),
                                         Latitude(-45.0)),
                         geobox.lower_left())
        self.assertEqual(GeoCoordinate2d(Longitude(90.0), Latitude(45.0)),
                         geobox.upper_right())

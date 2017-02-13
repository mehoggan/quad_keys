"""
Unit Tests for geo_coordinate_bounding_box2d
"""

from __future__ import print_function

import unittest

from quad_key.quad_key import geo_coordinate_bounding_box2d
from quad_key.quad_key import geo_coordinate2d
from quad_key.quad_key import longitude
from quad_key.quad_key import latitude


class TestGeoCoordinateBoundingBox2d(unittest.TestCase):
    """Class for running unit tests."""

    def test_default_ctor(self):
        empty = geo_coordinate_bounding_box2d()
        self.assertFalse(empty.is_valid())
        self.assertFalse(empty.contains(geo_coordinate2d(longitude(0.0),
                                                         latitude(0.0))))

    def test_ctor_standard_construction(self):
        geobox = geo_coordinate_bounding_box2d(
            geo_coordinate2d(longitude(0.0), latitude(0.0)),
            geo_coordinate2d(longitude(180.0), latitude(90.0)))
        self.assertEquals(geo_coordinate2d(longitude(0.0), latitude(0.0)),
                          geobox.lower_left())
        self.assertEquals(geo_coordinate2d(longitude(180.0), latitude(90.0)),
                          geobox.upper_right())
        self.assertTrue(geobox.is_valid())

        geobox = geo_coordinate_bounding_box2d(
            geo_coordinate2d(longitude(0.0), latitude(90.0)),
            geo_coordinate2d(longitude(180.0), latitude(0.0)))
        self.assertEquals(geo_coordinate2d(longitude(0.0), latitude(0.0)),
                          geobox.lower_left())
        self.assertEquals(geo_coordinate2d(longitude(180.0), latitude(90.0)),
                          geobox.upper_right())
        self.assertTrue(geobox.is_valid())

        geobox = geo_coordinate_bounding_box2d(
            geo_coordinate2d(longitude(180.0), latitude(0.0)),
            geo_coordinate2d(longitude(0.0), latitude(90.0)))
        self.assertEquals(geo_coordinate2d(longitude(0.0), latitude(0.0)),
                          geobox.lower_left())
        self.assertEquals(geo_coordinate2d(longitude(180.0), latitude(90.0)),
                          geobox.upper_right())
        self.assertTrue(geobox.is_valid())

        geobox = geo_coordinate_bounding_box2d(
            geo_coordinate2d(longitude(180.0), latitude(0.0)),
            geo_coordinate2d(longitude(0.0), latitude(90.0)))
        self.assertEquals(geo_coordinate2d(longitude(0.0), latitude(0.0)),
                          geobox.lower_left())
        self.assertEquals(geo_coordinate2d(longitude(180.0), latitude(90.0)),
                          geobox.upper_right())
        self.assertTrue(geobox.is_valid())

    def test_ctor_linear_box_and_point(self):
        geobox = geo_coordinate_bounding_box2d(
            geo_coordinate2d(longitude(0.0), latitude(0.0)),
            geo_coordinate2d(longitude(0.0), latitude(90.0)))
        self.assertEquals(geo_coordinate2d(longitude(0.0), latitude(0.0)),
                          geobox.lower_left())
        self.assertEquals(geo_coordinate2d(longitude(0.0), latitude(90.0)),
                          geobox.upper_right())
        self.assertTrue(geobox.is_valid())

        geobox = geo_coordinate_bounding_box2d(
            geo_coordinate2d(longitude(0.0), latitude(0.0)),
            geo_coordinate2d(longitude(180.0), latitude(0.0)))
        self.assertEquals(geo_coordinate2d(longitude(0.0), latitude(0.0)),
                          geobox.lower_left())
        self.assertEquals(geo_coordinate2d(longitude(180.0), latitude(0.0)),
                          geobox.upper_right())
        self.assertTrue(geobox.is_valid())

        geobox = geo_coordinate_bounding_box2d(
            geo_coordinate2d(longitude(0.0), latitude(0.0)),
            geo_coordinate2d(longitude(0.0), latitude(0.0)))
        self.assertTrue(geobox.is_valid())

    def test_contains_or_not(self):
        geobox = geo_coordinate_bounding_box2d(
            geo_coordinate2d(longitude(90.0), latitude(45.0)),
            geo_coordinate2d(longitude(-90.0), latitude(-45.0)))
        self.assertTrue(geobox.is_valid())
        self.assertTrue(geobox.contains(geo_coordinate2d(longitude(0.0),
                                                         latitude(0.0))))
        self.assertTrue(geobox.contains(geo_coordinate2d(longitude(90.0),
                                                         latitude(45.0))))
        self.assertTrue(geobox.contains(geo_coordinate2d(longitude(90.0),
                                                         latitude(-45.0))))
        self.assertTrue(geobox.contains(geo_coordinate2d(longitude(-90.0),
                                                         latitude(-45.0))))
        self.assertTrue(geobox.contains(geo_coordinate2d(longitude(-90.0),
                                                         latitude(45.0))))
        self.assertFalse(geobox.contains(geo_coordinate2d(longitude(90.01),
                                                          latitude(45.01))))
        self.assertFalse(geobox.contains(geo_coordinate2d(longitude(90.01),
                                                          latitude(-45.01))))
        self.assertFalse(geobox.contains(geo_coordinate2d(longitude(-90.01),
                                                          latitude(-45.01))))
        self.assertFalse(geobox.contains(geo_coordinate2d(longitude(-90.01),
                                                          latitude(45.01))))

        geobox = geo_coordinate_bounding_box2d(
            geo_coordinate2d(longitude(90.0), latitude(45.0)),
            geo_coordinate2d(longitude(0.1), latitude(0.1)))
        self.assertEquals(geo_coordinate2d(longitude(0.1), latitude(0.1)),
                          geobox.lower_left())
        self.assertTrue(geo_coordinate2d(longitude(90.0), latitude(45.0)),
                        geobox.upper_right())
        self.assertTrue(geobox.is_valid())
        self.assertTrue(geobox.contains(geo_coordinate2d(longitude(90.0),
                                                         latitude(45.0))))
        self.assertTrue(geobox.contains(geo_coordinate2d(longitude(90.0),
                                                         latitude(0.1))))
        self.assertTrue(geobox.contains(geo_coordinate2d(longitude(0.1),
                                                         latitude(0.1))))
        self.assertTrue(geobox.contains(geo_coordinate2d(longitude(0.1),
                                                         latitude(45.0))))
        self.assertFalse(geobox.contains(geo_coordinate2d(longitude(90.01),
                                                          latitude(45.01))))
        self.assertFalse(geobox.contains(geo_coordinate2d(longitude(90.01),
                                                          latitude(0.0))))
        self.assertFalse(geobox.contains(geo_coordinate2d(longitude(0.0),
                                                          latitude(0.0))))
        self.assertFalse(geobox.contains(geo_coordinate2d(longitude(0.0),
                                                          latitude(45.01))))

    def test_grow_to_contain(self):
        geobox = geo_coordinate_bounding_box2d(
            geo_coordinate2d(longitude(-90.0), latitude(-45.0)),
            geo_coordinate2d(longitude(90.0), latitude(45.0)))
        self.assertEquals(geo_coordinate2d(longitude(-90.0),
                                           latitude(-45.0)),
                          geobox.lower_left())
        self.assertEquals(geo_coordinate2d(longitude(90.0), latitude(45.0)),
                          geobox.upper_right())
        geobox.grow_to_contain(geo_coordinate2d(longitude(180.0),
                                                latitude(90.0)))
        self.assertEquals(geo_coordinate2d(longitude(-90.0),
                                           latitude(-45.0)),
                          geobox.lower_left())
        self.assertEquals(geo_coordinate2d(longitude(180.0), latitude(90.0)),
                          geobox.upper_right())

        geobox = geo_coordinate_bounding_box2d(
            geo_coordinate2d(longitude(-90.0), latitude(-45.0)),
            geo_coordinate2d(longitude(90.0), latitude(45.0)))
        self.assertEquals(geo_coordinate2d(longitude(-90.0),
                                           latitude(-45.0)),
                          geobox.lower_left())
        self.assertEquals(geo_coordinate2d(longitude(90.0), latitude(45.0)),
                          geobox.upper_right())
        geobox.grow_to_contain(
            geo_coordinate2d(longitude(-180.0), latitude(-90.0)))
        self.assertEquals(geo_coordinate2d(longitude(-180.0),
                                           latitude(-90.0)),
                          geobox.lower_left())
        self.assertEquals(geo_coordinate2d(longitude(90.0), latitude(45.0)),
                          geobox.upper_right())

        geobox = geo_coordinate_bounding_box2d(
            geo_coordinate2d(longitude(-90.0), latitude(-45.0)),
            geo_coordinate2d(longitude(90.0), latitude(45.0)))
        self.assertTrue(geo_coordinate2d(longitude(-90.0), latitude(-45.0)),
                        geobox.lower_left())
        self.assertEquals(geo_coordinate2d(longitude(90.0), latitude(45.0)),
                          geobox.upper_right())
        geobox.grow_to_contain(geo_coordinate2d(longitude(-180.0),
                                                latitude(90.0)))
        self.assertEquals(geo_coordinate2d(longitude(-180.0),
                                           latitude(-45.0)),
                          geobox.lower_left())
        self.assertEquals(geo_coordinate2d(longitude(90.0), latitude(90.0)),
                          geobox.upper_right())

        geobox = geo_coordinate_bounding_box2d(
            geo_coordinate2d(longitude(-90.0), latitude(-45.0)),
            geo_coordinate2d(longitude(90.0), latitude(45.0)))
        self.assertEquals(geo_coordinate2d(longitude(-90.0),
                                           latitude(-45.0)),
                          geobox.lower_left())
        self.assertEquals(geo_coordinate2d(longitude(90.0), latitude(45.0)),
                          geobox.upper_right())
        geobox.grow_to_contain(geo_coordinate2d(longitude(180.0),
                                                latitude(-90.0)))
        self.assertEquals(geo_coordinate2d(longitude(-90.0),
                                           latitude(-90.0)),
                          geobox.lower_left())
        self.assertEquals(geo_coordinate2d(longitude(180.0),
                                           latitude(45.0)),
                          geobox.upper_right())

        geobox = geo_coordinate_bounding_box2d(
            geo_coordinate2d(longitude(-90.0), latitude(-45.0)),
            geo_coordinate2d(longitude(90.0), latitude(45.0)))
        self.assertEquals(geo_coordinate2d(longitude(-90.0),
                                           latitude(-45.0)),
                          geobox.lower_left())
        self.assertEquals(geo_coordinate2d(longitude(90.0), latitude(45.0)),
                          geobox.upper_right())
        geobox.grow_to_contain(geo_coordinate2d(longitude(0.0),
                                                latitude(0.0)))
        self.assertEquals(geo_coordinate2d(longitude(-90.0),
                                           latitude(-45.0)),
                          geobox.lower_left())
        self.assertEquals(geo_coordinate2d(longitude(90.0), latitude(45.0)),
                          geobox.upper_right())

"""
Unit Tests for OsGeo System
"""

from __future__ import print_function
import unittest
from quadkey import QuadKey
from quadkey import Type__None
from quadkey import Type_OsGeo
from quadkey import GeoCoordinate2d
from quadkey import GeoCoordinateBoundingBox2d
from quadkey import Longitude
from quadkey import Latitude


class TestOsGeoSystem(unittest.TestCase):
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
        # Same thing as OsGeo Except for it allows for negative 1 in both the
        # rows and the columns. depth/col/row.
        quad_key = QuadKey(Type_OsGeo, 3, 3, 2)
        fmt = quad_key.toInternalString()
        self.assertEqual("2/3/3", fmt)
        quad_key_back = QuadKey.fromInternalString(Type_OsGeo, fmt)
        self.assertEqual(quad_key, quad_key_back)

        fmt = "0/-1/-1"
        quad_key_back = QuadKey.fromInternalString(Type_OsGeo, fmt)
        self.assertEqual(QuadKey(Type_OsGeo, 0, 0, 0), quad_key_back)

        fmt = "1/1/-1"
        quad_key_back = QuadKey.fromInternalString(Type_OsGeo, fmt)
        self.assertEqual(QuadKey(Type_OsGeo, 0, 1, 1), quad_key_back)

        fmt = "1/-1/1"
        quad_key_back = QuadKey.fromInternalString(Type_OsGeo, fmt)
        self.assertEqual(QuadKey(Type_OsGeo, 1, 0, 1), quad_key_back)

    def test_get_geo_coordinate_bounds_2d(self):
        """
        Test to get geographic bounds of quadquad_key.
        """
        bbox = GeoCoordinateBoundingBox2d()

        quad_key = QuadKey.fromInternalString(Type_OsGeo, "0/0/0")
        quad_key.getGeoCoordinateBounds2d(bbox)
        self.assertTrue(Longitude(-180.0).near(
            bbox.lowerLeft().longitude(), 1e-4))
        self.assertTrue(Latitude(-85.051132).near(
            bbox.lowerLeft().latitude(), 1e-4))
        self.assertTrue(Longitude(+180.0).near(
            bbox.upperRight().longitude(), 1e-4))
        self.assertTrue(Latitude(+85.051132).near(
            bbox.upperRight().latitude(), 1e-4))

    def test_get_key_from_longitude_latitude_at_depth_to_bounds(self):
        """
        Test to get a quadkey from longitude and latitude and then get bounds.
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
        # Note that in this system bounds consist of all 4 sides, so two quads
        # will share the same boundary.
        quad_key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
            Type_OsGeo,
            GeoCoordinate2d(Longitude(-180.0), Latitude(+85.05113877)), 0)
        self.assertEqual(QuadKey(Type_OsGeo, 0, 0, 0), quad_key)
        quad_key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
            Type_OsGeo,
            GeoCoordinate2d(Longitude(+180.0), Latitude(+85.05113877)), 0)
        self.assertEqual(QuadKey(Type_OsGeo, 0, 0, 0), quad_key)
        quad_key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
            Type_OsGeo,
            GeoCoordinate2d(Longitude(+180.0), Latitude(-85.05113877)), 0)
        self.assertEqual(QuadKey(Type_OsGeo, 0, 0, 0), quad_key)
        quad_key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
            Type_OsGeo,
            GeoCoordinate2d(Longitude(-180.0), Latitude(-85.05113877)), 0)
        self.assertEqual(QuadKey(Type_OsGeo, 0, 0, 0), quad_key)
        quad_key.getGeoCoordinateBounds2d(bbox)
        self.assertTrue(bbox.lowerLeft().near(GeoCoordinate2d(
            Longitude(-180.0), Latitude(-85.05113877)), 1e-4))
        self.assertTrue(bbox.upperRight().near(GeoCoordinate2d(
            Longitude(+180.0), Latitude(+85.05113877)), 1e-4))

        quad_key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
            Type_OsGeo,
            GeoCoordinate2d(Longitude(+0.0), Latitude(+0.00000000)), 0)
        self.assertEqual(QuadKey(Type_OsGeo, 0, 0, 0), quad_key)

        quad_key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
            Type_OsGeo,
            GeoCoordinate2d(Longitude(-180.0), Latitude(+85.05113877)), 1)
        self.assertEqual(QuadKey(Type_OsGeo, 1, 0, 1), quad_key)
        quad_key.getGeoCoordinateBounds2d(bbox)
        self.assertTrue(bbox.lowerLeft().near(GeoCoordinate2d(
            Longitude(-180.0), Latitude(+0.00000000)), 1e-4))
        self.assertTrue(bbox.upperRight().near(GeoCoordinate2d(
            Longitude(+0.0), Latitude(+85.05113877)), 1e-4))

        quad_key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
            Type_OsGeo,
            GeoCoordinate2d(Longitude(+180.0), Latitude(+85.05113877)), 1)
        self.assertEqual(QuadKey(Type_OsGeo, 1, 1, 1), quad_key)
        quad_key.getGeoCoordinateBounds2d(bbox)
        self.assertTrue(bbox.lowerLeft().near(GeoCoordinate2d(
            Longitude(+0.0), Latitude(+0.00000000)), 1e-4))
        self.assertTrue(bbox.upperRight().near(GeoCoordinate2d(
            Longitude(+180.0), Latitude(+85.05113877)), 1e-4))

        quad_key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
            Type_OsGeo,
            GeoCoordinate2d(Longitude(+180.0), Latitude(-85.05113877)), 1)
        self.assertEqual(QuadKey(Type_OsGeo, 0, 1, 1), quad_key)
        quad_key.getGeoCoordinateBounds2d(bbox)
        self.assertTrue(bbox.lowerLeft().near(GeoCoordinate2d(
            Longitude(+0.0), Latitude(-85.05113877)), 1e-4))
        self.assertTrue(bbox.upperRight().near(GeoCoordinate2d(
            Longitude(+180.0), Latitude(+0.00000000)), 1e-4))

        quad_key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
            Type_OsGeo,
            GeoCoordinate2d(Longitude(-180.0), Latitude(-85.05113877)), 1)
        self.assertEqual(QuadKey(Type_OsGeo, 0, 0, 1), quad_key)
        quad_key.getGeoCoordinateBounds2d(bbox)
        self.assertTrue(bbox.lowerLeft().near(GeoCoordinate2d(
            Longitude(-180.0), Latitude(-85.05113877)), 1e-4))
        self.assertTrue(bbox.upperRight().near(GeoCoordinate2d(
            Longitude(+0.0), Latitude(+0.00000000)), 1e-4))

        quad_key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
            Type_OsGeo,
            GeoCoordinate2d(Longitude(-180.0), Latitude(+0.00000000)), 1)
        self.assertEqual(QuadKey(Type_OsGeo, 0, 0, 1), quad_key)
        quad_key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
            Type_OsGeo,
            GeoCoordinate2d(Longitude(+0.0), Latitude(+85.05113877)), 1)
        self.assertEqual(QuadKey(Type_OsGeo, 1, 0, 1), quad_key)
        quad_key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
            Type_OsGeo,
            GeoCoordinate2d(Longitude(+180.0), Latitude(+0.00000000)), 1)
        self.assertEqual(QuadKey(Type_OsGeo, 0, 1, 1), quad_key)
        quad_key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
            Type_OsGeo,
            GeoCoordinate2d(Longitude(+0.0), Latitude(-85.05113877)), 1)
        self.assertEqual(QuadKey(Type_OsGeo, 0, 0, 1), quad_key)
        quad_key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
            Type_OsGeo,
            GeoCoordinate2d(Longitude(+0.0), Latitude(+0.00000000)), 1)
        self.assertEqual(QuadKey(Type_OsGeo, 0, 0, 1), quad_key)

        # Note at depth 2 because of the Mercator projection the lines
        # of latitude are note perfect divisions by 2.
        quad_key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
            Type_OsGeo,
            GeoCoordinate2d(Longitude(-180.0), Latitude(-85.05113877)), 2)
        self.assertEqual(QuadKey(Type_OsGeo, 0, 0, 2), quad_key)
        quad_key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
            Type_OsGeo,
            GeoCoordinate2d(Longitude(-180.0), Latitude(-66.5133)), 2)
        self.assertEqual(QuadKey(Type_OsGeo, 0, 0, 2), quad_key)
        quad_key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
            Type_OsGeo,
            GeoCoordinate2d(Longitude(-180.0), Latitude(-66.5132)), 2)
        self.assertEqual(QuadKey(Type_OsGeo, 1, 0, 2), quad_key)
        quad_key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
            Type_OsGeo,
            GeoCoordinate2d(Longitude(-180.0), Latitude(+0.1)), 2)
        self.assertEqual(QuadKey(Type_OsGeo, 2, 0, 2), quad_key)
        quad_key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
            Type_OsGeo,
            GeoCoordinate2d(Longitude(-180.0), Latitude(+66.5132)), 2)
        self.assertEqual(QuadKey(Type_OsGeo, 2, 0, 2), quad_key)
        quad_key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
            Type_OsGeo,
            GeoCoordinate2d(Longitude(-180.0), Latitude(+66.5133)), 2)
        self.assertEqual(QuadKey(Type_OsGeo, 3, 0, 2), quad_key)
        quad_key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
            Type_OsGeo,
            GeoCoordinate2d(Longitude(-180.0), Latitude(+85.05113877)), 2)
        self.assertEqual(QuadKey(Type_OsGeo, 3, 0, 2), quad_key)
        quad_key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
            Type_OsGeo,
            GeoCoordinate2d(Longitude(-90.0), Latitude(-85.05113877)), 2)
        self.assertEqual(QuadKey(Type_OsGeo, 0, 0, 2), quad_key)
        quad_key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
            Type_OsGeo,
            GeoCoordinate2d(Longitude(-90.0), Latitude(-66.5133)), 2)
        self.assertEqual(QuadKey(Type_OsGeo, 0, 0, 2), quad_key)
        quad_key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
            Type_OsGeo,
            GeoCoordinate2d(Longitude(-90.0), Latitude(-66.5132)), 2)
        self.assertEqual(QuadKey(Type_OsGeo, 1, 0, 2), quad_key)
        quad_key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
            Type_OsGeo,
            GeoCoordinate2d(Longitude(-90.0), Latitude(+0.1)), 2)
        self.assertEqual(QuadKey(Type_OsGeo, 2, 0, 2), quad_key)
        quad_key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
            Type_OsGeo,
            GeoCoordinate2d(Longitude(-90.0), Latitude(+66.5132)), 2)
        self.assertEqual(QuadKey(Type_OsGeo, 2, 0, 2), quad_key)
        quad_key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
            Type_OsGeo,
            GeoCoordinate2d(Longitude(-90.0), Latitude(+66.5133)), 2)
        self.assertEqual(QuadKey(Type_OsGeo, 3, 0, 2), quad_key)
        quad_key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
            Type_OsGeo,
            GeoCoordinate2d(Longitude(-90.0), Latitude(+85.05113877)), 2)
        self.assertEqual(QuadKey(Type_OsGeo, 3, 0, 2), quad_key)
        quad_key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
            Type_OsGeo,
            GeoCoordinate2d(Longitude(-89.9), Latitude(-85.05113877)), 2)
        self.assertEqual(QuadKey(Type_OsGeo, 0, 1, 2), quad_key)
        quad_key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
            Type_OsGeo,
            GeoCoordinate2d(Longitude(-89.9), Latitude(-66.5133)), 2)
        self.assertEqual(QuadKey(Type_OsGeo, 0, 1, 2), quad_key)
        quad_key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
            Type_OsGeo,
            GeoCoordinate2d(Longitude(-89.9), Latitude(-66.5132)), 2)
        self.assertEqual(QuadKey(Type_OsGeo, 1, 1, 2), quad_key)
        quad_key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
            Type_OsGeo,
            GeoCoordinate2d(Longitude(-89.9), Latitude(+0.1)), 2)
        self.assertEqual(QuadKey(Type_OsGeo, 2, 1, 2), quad_key)
        quad_key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
            Type_OsGeo,
            GeoCoordinate2d(Longitude(-89.9), Latitude(+66.5132)), 2)
        self.assertEqual(QuadKey(Type_OsGeo, 2, 1, 2), quad_key)
        quad_key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
            Type_OsGeo,
            GeoCoordinate2d(Longitude(-89.9), Latitude(+66.5133)), 2)
        self.assertEqual(QuadKey(Type_OsGeo, 3, 1, 2), quad_key)
        quad_key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
            Type_OsGeo,
            GeoCoordinate2d(Longitude(-89.9), Latitude(+85.05113877)), 2)
        self.assertEqual(QuadKey(Type_OsGeo, 3, 1, 2), quad_key)
        quad_key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
            Type_OsGeo,
            GeoCoordinate2d(Longitude(+0.0), Latitude(-85.05113877)), 2)
        self.assertEqual(QuadKey(Type_OsGeo, 0, 1, 2), quad_key)
        quad_key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
            Type_OsGeo,
            GeoCoordinate2d(Longitude(+0.0), Latitude(-66.5133)), 2)
        self.assertEqual(QuadKey(Type_OsGeo, 0, 1, 2), quad_key)
        quad_key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
            Type_OsGeo,
            GeoCoordinate2d(Longitude(+0.0), Latitude(-66.5132)), 2)
        self.assertEqual(QuadKey(Type_OsGeo, 1, 1, 2), quad_key)
        quad_key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
            Type_OsGeo,
            GeoCoordinate2d(Longitude(+0.0), Latitude(+0.1)), 2)
        self.assertEqual(QuadKey(Type_OsGeo, 2, 1, 2), quad_key)
        quad_key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
            Type_OsGeo,
            GeoCoordinate2d(Longitude(+0.0), Latitude(+66.5132)), 2)
        self.assertEqual(QuadKey(Type_OsGeo, 2, 1, 2), quad_key)
        quad_key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
            Type_OsGeo,
            GeoCoordinate2d(Longitude(+0.0), Latitude(+66.5133)), 2)
        self.assertEqual(QuadKey(Type_OsGeo, 3, 1, 2), quad_key)
        quad_key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
            Type_OsGeo,
            GeoCoordinate2d(Longitude(+0.0), Latitude(+85.05113877)), 2)
        self.assertEqual(QuadKey(Type_OsGeo, 3, 1, 2), quad_key)
        quad_key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
            Type_OsGeo,
            GeoCoordinate2d(Longitude(+0.1), Latitude(-85.05113877)), 2)
        self.assertEqual(QuadKey(Type_OsGeo, 0, 2, 2), quad_key)
        quad_key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
            Type_OsGeo,
            GeoCoordinate2d(Longitude(+0.1), Latitude(-66.5133)), 2)
        self.assertEqual(QuadKey(Type_OsGeo, 0, 2, 2), quad_key)
        quad_key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
            Type_OsGeo,
            GeoCoordinate2d(Longitude(+0.1), Latitude(-66.5132)), 2)
        self.assertEqual(QuadKey(Type_OsGeo, 1, 2, 2), quad_key)
        quad_key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
            Type_OsGeo,
            GeoCoordinate2d(Longitude(+0.1), Latitude(+0.1)), 2)
        self.assertEqual(QuadKey(Type_OsGeo, 2, 2, 2), quad_key)
        quad_key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
            Type_OsGeo,
            GeoCoordinate2d(Longitude(+0.1), Latitude(+66.5132)), 2)
        self.assertEqual(QuadKey(Type_OsGeo, 2, 2, 2), quad_key)
        quad_key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
            Type_OsGeo,
            GeoCoordinate2d(Longitude(+0.1), Latitude(+66.5133)), 2)
        self.assertEqual(QuadKey(Type_OsGeo, 3, 2, 2), quad_key)
        quad_key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
            Type_OsGeo,
            GeoCoordinate2d(Longitude(+0.1), Latitude(+85.05113877)), 2)
        self.assertEqual(QuadKey(Type_OsGeo, 3, 2, 2), quad_key)
        quad_key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
            Type_OsGeo,
            GeoCoordinate2d(Longitude(+90.0), Latitude(-85.05113877)), 2)
        self.assertEqual(QuadKey(Type_OsGeo, 0, 2, 2), quad_key)
        quad_key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
            Type_OsGeo,
            GeoCoordinate2d(Longitude(+90.0), Latitude(-66.5133)), 2)
        self.assertEqual(QuadKey(Type_OsGeo, 0, 2, 2), quad_key)
        quad_key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
            Type_OsGeo,
            GeoCoordinate2d(Longitude(+90.0), Latitude(-66.5132)), 2)
        self.assertEqual(QuadKey(Type_OsGeo, 1, 2, 2), quad_key)
        quad_key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
            Type_OsGeo,
            GeoCoordinate2d(Longitude(+90.0), Latitude(+0.1)), 2)
        self.assertEqual(QuadKey(Type_OsGeo, 2, 2, 2), quad_key)
        quad_key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
            Type_OsGeo,
            GeoCoordinate2d(Longitude(+90.0), Latitude(+66.5132)), 2)
        self.assertEqual(QuadKey(Type_OsGeo, 2, 2, 2), quad_key)
        quad_key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
            Type_OsGeo,
            GeoCoordinate2d(Longitude(+90.0), Latitude(+66.5133)), 2)
        self.assertEqual(QuadKey(Type_OsGeo, 3, 2, 2), quad_key)
        quad_key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
            Type_OsGeo,
            GeoCoordinate2d(Longitude(+90.0), Latitude(+85.05113877)), 2)
        self.assertEqual(QuadKey(Type_OsGeo, 3, 2, 2), quad_key)
        quad_key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
            Type_OsGeo,
            GeoCoordinate2d(Longitude(+90.1), Latitude(-85.05113877)), 2)
        self.assertEqual(QuadKey(Type_OsGeo, 0, 3, 2), quad_key)
        quad_key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
            Type_OsGeo,
            GeoCoordinate2d(Longitude(+90.1), Latitude(-66.5133)), 2)
        self.assertEqual(QuadKey(Type_OsGeo, 0, 3, 2), quad_key)
        quad_key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
            Type_OsGeo,
            GeoCoordinate2d(Longitude(+90.1), Latitude(-66.5132)), 2)
        self.assertEqual(QuadKey(Type_OsGeo, 1, 3, 2), quad_key)
        quad_key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
            Type_OsGeo,
            GeoCoordinate2d(Longitude(+90.1), Latitude(+0.1)), 2)
        self.assertEqual(QuadKey(Type_OsGeo, 2, 3, 2), quad_key)
        quad_key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
            Type_OsGeo,
            GeoCoordinate2d(Longitude(+90.1), Latitude(+66.5132)), 2)
        self.assertEqual(QuadKey(Type_OsGeo, 2, 3, 2), quad_key)
        quad_key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
            Type_OsGeo,
            GeoCoordinate2d(Longitude(+90.1), Latitude(+66.5133)), 2)
        self.assertEqual(QuadKey(Type_OsGeo, 3, 3, 2), quad_key)
        quad_key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
            Type_OsGeo,
            GeoCoordinate2d(Longitude(+90.1), Latitude(+85.05113877)), 2)
        self.assertEqual(QuadKey(Type_OsGeo, 3, 3, 2), quad_key)
        quad_key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
            Type_OsGeo,
            GeoCoordinate2d(Longitude(+180.0), Latitude(-85.05113877)), 2)
        self.assertEqual(QuadKey(Type_OsGeo, 0, 3, 2), quad_key)
        quad_key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
            Type_OsGeo,
            GeoCoordinate2d(Longitude(+180.0), Latitude(-66.5133)), 2)
        self.assertEqual(QuadKey(Type_OsGeo, 0, 3, 2), quad_key)
        quad_key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
            Type_OsGeo,
            GeoCoordinate2d(Longitude(+180.0), Latitude(-66.5132)), 2)
        self.assertEqual(QuadKey(Type_OsGeo, 1, 3, 2), quad_key)
        quad_key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
            Type_OsGeo,
            GeoCoordinate2d(Longitude(+180.0), Latitude(+0.1)), 2)
        self.assertEqual(QuadKey(Type_OsGeo, 2, 3, 2), quad_key)
        quad_key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
            Type_OsGeo,
            GeoCoordinate2d(Longitude(+180.0), Latitude(+66.5132)), 2)
        self.assertEqual(QuadKey(Type_OsGeo, 2, 3, 2), quad_key)
        quad_key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
            Type_OsGeo,
            GeoCoordinate2d(Longitude(+180.0), Latitude(+66.5133)), 2)
        self.assertEqual(QuadKey(Type_OsGeo, 3, 3, 2), quad_key)
        quad_key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
            Type_OsGeo,
            GeoCoordinate2d(Longitude(+180.0), Latitude(+85.05113877)), 2)
        self.assertEqual(QuadKey(Type_OsGeo, 3, 3, 2), quad_key)

    def test_get_keys_from_longitude_latitude_bounding_box(self):
        """
        Test to get the bounding box of a quadquad_key.
        """
        quad_keys = QuadKey.getKeysFromLongitudeLatitudeBoundingBox(
            Type_OsGeo, GeoCoordinateBoundingBox2d(
                GeoCoordinate2d(Longitude(+0.0), Latitude(-0.10000000)),
                GeoCoordinate2d(Longitude(+0.1), Latitude(+0.10000000))),
            0)
        self.assertEqual(1, quad_keys.size())
        self.assertTrue(QuadKey(Type_OsGeo, 0, 0, 0) in quad_keys)

        quad_keys = QuadKey.getKeysFromLongitudeLatitudeBoundingBox(
            Type_OsGeo, GeoCoordinateBoundingBox2d(
                GeoCoordinate2d(Longitude(-180.0), Latitude(-85.05113877)),
                GeoCoordinate2d(Longitude(+180.0), Latitude(+85.05113877))),
            1)
        self.assertEqual(4, quad_keys.size())
        self.assertTrue(QuadKey(Type_OsGeo, 0, 0, 1) in quad_keys)
        self.assertTrue(QuadKey(Type_OsGeo, 0, 1, 1) in quad_keys)
        self.assertTrue(QuadKey(Type_OsGeo, 1, 0, 1) in quad_keys)
        self.assertTrue(QuadKey(Type_OsGeo, 1, 1, 1) in quad_keys)

        quad_keys = QuadKey.getKeysFromLongitudeLatitudeBoundingBox(
            Type_OsGeo, GeoCoordinateBoundingBox2d(
                GeoCoordinate2d(Longitude(-180.0), Latitude(-85.05113877)),
                GeoCoordinate2d(Longitude(+0.0), Latitude(+85.05113877))),
            1)
        self.assertEqual(2, quad_keys.size())
        self.assertTrue(QuadKey(Type_OsGeo, 1, 0, 1) in quad_keys)
        self.assertTrue(QuadKey(Type_OsGeo, 0, 0, 1) in quad_keys)

        quad_keys = QuadKey.getKeysFromLongitudeLatitudeBoundingBox(
            Type_OsGeo, GeoCoordinateBoundingBox2d(
                GeoCoordinate2d(Longitude(+0.1), Latitude(-85.05113877)),
                GeoCoordinate2d(Longitude(+180.0), Latitude(+85.05113877))),
            1)
        self.assertEqual(2, quad_keys.size())
        self.assertTrue(QuadKey(Type_OsGeo, 1, 1, 1) in quad_keys)
        self.assertTrue(QuadKey(Type_OsGeo, 0, 1, 1) in quad_keys)

        quad_keys = QuadKey.getKeysFromLongitudeLatitudeBoundingBox(
            Type_OsGeo, GeoCoordinateBoundingBox2d(
                GeoCoordinate2d(Longitude(-180.0), Latitude(-85.05113877)),
                GeoCoordinate2d(Longitude(+0.0), Latitude(+0.00000000))),
            1)
        self.assertEqual(1, quad_keys.size())
        self.assertTrue(QuadKey(Type_OsGeo, 0, 0, 1) in quad_keys)

        quad_keys = QuadKey.getKeysFromLongitudeLatitudeBoundingBox(
            Type_OsGeo, GeoCoordinateBoundingBox2d(
                GeoCoordinate2d(Longitude(-180.0), Latitude(+0.10000000)),
                GeoCoordinate2d(Longitude(+0.0), Latitude(+85.05113877))),
            1)
        self.assertEqual(1, quad_keys.size())
        self.assertTrue(QuadKey(Type_OsGeo, 1, 0, 1) in quad_keys)

        quad_keys = QuadKey.getKeysFromLongitudeLatitudeBoundingBox(
            Type_OsGeo, GeoCoordinateBoundingBox2d(
                GeoCoordinate2d(Longitude(+0.1), Latitude(-85.05113877)),
                GeoCoordinate2d(Longitude(+180.0), Latitude(+0.00000000))),
            1)
        self.assertEqual(1, quad_keys.size())
        self.assertTrue(QuadKey(Type_OsGeo, 0, 1, 1) in quad_keys)

        quad_keys = QuadKey.getKeysFromLongitudeLatitudeBoundingBox(
            Type_OsGeo, GeoCoordinateBoundingBox2d(
                GeoCoordinate2d(Longitude(+0.1), Latitude(+0.10000000)),
                GeoCoordinate2d(Longitude(+180.0), Latitude(+85.05113877))),
            1)
        self.assertEqual(1, quad_keys.size())
        self.assertTrue(QuadKey(Type_OsGeo, 1, 1, 1) in quad_keys)

    def test_selected_cities(self):
        """
        Test a given set of known places make sure they work.
        """


def main():
    """
    Bootstrap function for this module
    """
    suite = unittest.TestLoader().loadTestsFromTestCase(TestOsGeoSystem)
    unittest.TextTestRunner(verbosity=2).run(suite)

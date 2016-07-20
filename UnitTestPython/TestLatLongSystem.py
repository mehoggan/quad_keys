"""
Unit Tests for LatLong System
"""

from __future__ import print_function
import unittest
from quadkey import QuadKey
from quadkey import Type_LatLong
from quadkey import GeoCoordinate2d
from quadkey import GeoCoordinateBoundingBox2d
from quadkey import Longitude
from quadkey import Latitude


class TestLatLongSystem(unittest.TestCase):
    """
    Class for running unit tests.
    """

    def test_is_valid(self):
        """
        See TestQuadKey.test_is_valid
        """

    def test_is_root_key(self):
        """
        See TestQuadKey.test_is_root_key
        """

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
        # Same as BingSystem

    def test_get_geo_coordinate_bounds_2d(self):
        """
        Test to get geographic bounds of quadquad_key.
        """
        bbox = GeoCoordinateBoundingBox2d()

        quad_key = QuadKey(Type_LatLong, 0, 0, 0)
        quad_key.getGeoCoordinateBounds2d(bbox)
        self.assertTrue(GeoCoordinate2d(Longitude(-180.0), Latitude(-90.0)) ==
                        bbox.lowerLeft())
        self.assertTrue(GeoCoordinate2d(Longitude(+180.0), Latitude(+90.0)) ==
                        bbox.upperRight())

        quad_key = QuadKey(Type_LatLong, 0, 0, 1)
        quad_key.getGeoCoordinateBounds2d(bbox)
        self.assertTrue(bbox.lowerLeft().longitude().near(Longitude(-180.0),
                                                          1e-6))
        self.assertTrue(bbox.lowerLeft().latitude().near(Latitude(-90.0),
                                                         1e-6))
        self.assertTrue(bbox.upperRight().longitude().near(Longitude(+0.0),
                                                           1e-6))
        self.assertTrue(bbox.upperRight().latitude().near(Latitude(+0.0),
                                                          1e-6))

        quad_key = QuadKey(Type_LatLong, 0, 1, 1)
        quad_key.getGeoCoordinateBounds2d(bbox)
        self.assertTrue(bbox.lowerLeft().longitude().near(Longitude(+0.0),
                                                          1e-6))
        self.assertTrue(bbox.lowerLeft().latitude().near(Latitude(-90.0),
                                                         1e-6))
        self.assertTrue(bbox.upperRight().longitude().near(Longitude(+180.0),
                                                           1e-6))
        self.assertTrue(bbox.upperRight().latitude().near(Latitude(+0.0),
                                                          1e-6))

        quad_key = QuadKey(Type_LatLong, 1, 0, 1)
        quad_key.getGeoCoordinateBounds2d(bbox)
        self.assertTrue(bbox.lowerLeft().longitude().near(Longitude(-180.0),
                                                          1e-6))
        self.assertTrue(bbox.lowerLeft().latitude().near(Latitude(+0.0),
                                                         1e-6))
        self.assertTrue(bbox.upperRight().longitude().near(Longitude(+0.0),
                                                           1e-6))
        self.assertTrue(bbox.upperRight().latitude().near(Latitude(+90.0),
                                                          1e-6))

        quad_key = QuadKey(Type_LatLong, 1, 1, 1)
        quad_key.getGeoCoordinateBounds2d(bbox)
        self.assertTrue(bbox.lowerLeft().longitude().near(Longitude(+0.0),
                                                          1e-6))
        self.assertTrue(bbox.lowerLeft().latitude().near(Latitude(+0.0),
                                                         1e-6))
        self.assertTrue(bbox.upperRight().longitude().near(Longitude(+180.0),
                                                           1e-6))
        self.assertTrue(bbox.upperRight().latitude().near(Latitude(+90.0),
                                                          1e-6))

    def test_get_key_from_longitude_latitude_at_depth_to_bounds(self):
        """
        Test to get a quadkey from longitude and latitude and then get bounds.
        """

        quad_key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
            Type_LatLong, GeoCoordinate2d(Longitude(-180.0),
                                          Latitude(-90)), 0)
        self.assertTrue(QuadKey(Type_LatLong, 0, 0, 0) == quad_key)
        self.assertEquals("", quad_key.toInternalString())

        # Inclusion here consists of lower left
        #    X------X------X
        #    |   2  |   3  |
        #    |      |      |
        #    X------X------X
        #    |   0  |   1  |
        #    |      |      |
        # ll X------X------X
        quad_key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
            Type_LatLong, GeoCoordinate2d(Longitude(-180.0),
                                          Latitude(-90.0)), 1)
        self.assertTrue(QuadKey(Type_LatLong, 0, 0, 1) == quad_key)
        self.assertEquals("2", quad_key.toInternalString())
        quad_key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
            Type_LatLong, GeoCoordinate2d(Longitude(-0.1),
                                          Latitude(-90.0)), 1)
        self.assertTrue(QuadKey(Type_LatLong, 0, 0, 1) == quad_key)
        self.assertEquals("2", quad_key.toInternalString())
        quad_key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
            Type_LatLong, GeoCoordinate2d(Longitude(-0.1),
                                          Latitude(-0.1)), 1)
        self.assertTrue(QuadKey(Type_LatLong, 0, 0, 1) == quad_key)
        self.assertEquals("2", quad_key.toInternalString())
        quad_key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
            Type_LatLong, GeoCoordinate2d(Longitude(-180.0),
                                          Latitude(-0.1)), 1)
        self.assertTrue(QuadKey(Type_LatLong, 0, 0, 1) == quad_key)
        self.assertEquals("2", quad_key.toInternalString())

        quad_key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
            Type_LatLong, GeoCoordinate2d(Longitude(+0.0),
                                          Latitude(-90.0)), 1)
        self.assertTrue(QuadKey(Type_LatLong, 0, 1, 1) == quad_key)
        self.assertEquals("3", quad_key.toInternalString())
        quad_key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
            Type_LatLong, GeoCoordinate2d(Longitude(+180.0),
                                          Latitude(-90.0)), 1)
        self.assertTrue(QuadKey(Type_LatLong, 0, 1, 1) == quad_key)
        self.assertEquals("3", quad_key.toInternalString())
        quad_key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
            Type_LatLong, GeoCoordinate2d(Longitude(+180.0),
                                          Latitude(-0.1)), 1)
        self.assertTrue(QuadKey(Type_LatLong, 0, 1, 1) == quad_key)
        self.assertEquals("3", quad_key.toInternalString())
        quad_key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
            Type_LatLong, GeoCoordinate2d(Longitude(+0.0),
                                          Latitude(-0.1)), 1)
        self.assertTrue(QuadKey(Type_LatLong, 0, 1, 1) == quad_key)
        self.assertEquals("3", quad_key.toInternalString())

        quad_key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
            Type_LatLong, GeoCoordinate2d(Longitude(-180.0),
                                          Latitude(+0.0)), 1)
        self.assertTrue(QuadKey(Type_LatLong, 1, 0, 1) == quad_key)
        self.assertEquals("0", quad_key.toInternalString())
        quad_key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
            Type_LatLong, GeoCoordinate2d(Longitude(-0.1),
                                          Latitude(+0.0)), 1)
        self.assertTrue(QuadKey(Type_LatLong, 1, 0, 1) == quad_key)
        self.assertEquals("0", quad_key.toInternalString())
        quad_key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
            Type_LatLong, GeoCoordinate2d(Longitude(-180.0),
                                          Latitude(+90.0)), 1)
        self.assertTrue(QuadKey(Type_LatLong, 1, 0, 1) == quad_key)
        self.assertEquals("0", quad_key.toInternalString())
        quad_key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
            Type_LatLong, GeoCoordinate2d(Longitude(-0.1),
                                          Latitude(+90.0)), 1)
        self.assertTrue(QuadKey(Type_LatLong, 1, 0, 1) == quad_key)
        self.assertEquals("0", quad_key.toInternalString())

        quad_key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
            Type_LatLong, GeoCoordinate2d(Longitude(+0.0),
                                          Latitude(+0.0)), 1)
        self.assertTrue(QuadKey(Type_LatLong, 1, 1, 1) == quad_key)
        self.assertEquals("1", quad_key.toInternalString())
        quad_key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
            Type_LatLong, GeoCoordinate2d(Longitude(+180.0),
                                          Latitude(+0.0)), 1)
        self.assertTrue(QuadKey(Type_LatLong, 1, 1, 1) == quad_key)
        self.assertEquals("1", quad_key.toInternalString())
        quad_key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
            Type_LatLong, GeoCoordinate2d(Longitude(+0.0),
                                          Latitude(+90.0)), 1)
        self.assertTrue(QuadKey(Type_LatLong, 1, 1, 1) == quad_key)
        self.assertEquals("1", quad_key.toInternalString())
        quad_key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
            Type_LatLong, GeoCoordinate2d(Longitude(+180.0),
                                          Latitude(+90.0)), 1)
        self.assertTrue(QuadKey(Type_LatLong, 1, 1, 1) == quad_key)
        self.assertEquals("1", quad_key.toInternalString())

    def test_get_keys_from_longitude_latitude_bounding_box(self):
        """
        Test to get the bounding box of a quadquad_key.
        """
        outkeys = QuadKey.getKeysFromLongitudeLatitudeBoundingBox(
            Type_LatLong,
            GeoCoordinateBoundingBox2d(
                GeoCoordinate2d(Longitude(-180.0), Latitude(+90.0)),
                GeoCoordinate2d(Longitude(+180.0), Latitude(-90.0))),
            0)
        self.assertEquals(1, outkeys.size())
        self.assertTrue(QuadKey(Type_LatLong, 0, 0, 0) in outkeys)

        outkeys = QuadKey.getKeysFromLongitudeLatitudeBoundingBox(
            Type_LatLong,
            GeoCoordinateBoundingBox2d(
                GeoCoordinate2d(Longitude(-180.0), Latitude(+90.0)),
                GeoCoordinate2d(Longitude(+180.0), Latitude(-90.0))),
            1)
        self.assertEquals(4, outkeys.size())
        self.assertTrue(QuadKey(Type_LatLong, 0, 0, 1) in outkeys)
        self.assertTrue(QuadKey(Type_LatLong, 0, 1, 1) in outkeys)
        self.assertTrue(QuadKey(Type_LatLong, 1, 0, 1) in outkeys)
        self.assertTrue(QuadKey(Type_LatLong, 1, 1, 1) in outkeys)

        outkeys = QuadKey.getKeysFromLongitudeLatitudeBoundingBox(
            Type_LatLong,
            GeoCoordinateBoundingBox2d(
                GeoCoordinate2d(Longitude(-180.0), Latitude(-0.1)),
                GeoCoordinate2d(Longitude(-0.1), Latitude(+90.0))),
            1)
        self.assertEquals(2, outkeys.size())
        self.assertTrue(QuadKey(Type_LatLong, 0, 0, 1) in outkeys)
        self.assertTrue(QuadKey(Type_LatLong, 1, 0, 1) in outkeys)

        outkeys = QuadKey.getKeysFromLongitudeLatitudeBoundingBox(
            Type_LatLong,
            GeoCoordinateBoundingBox2d(
                GeoCoordinate2d(Longitude(+0.0), Latitude(-0.1)),
                GeoCoordinate2d(Longitude(+180.0), Latitude(+90.0))),
            1)
        self.assertEquals(2, outkeys.size())
        self.assertTrue(QuadKey(Type_LatLong, 0, 1, 1) in outkeys)
        self.assertTrue(QuadKey(Type_LatLong, 1, 1, 1) in outkeys)

        outkeys = QuadKey.getKeysFromLongitudeLatitudeBoundingBox(
            Type_LatLong,
            GeoCoordinateBoundingBox2d(
                GeoCoordinate2d(Longitude(-0.1), Latitude(-0.1)),
                GeoCoordinate2d(Longitude(+0.1), Latitude(+0.1))),
            1)
        self.assertEquals(4, outkeys.size())
        self.assertTrue(QuadKey(Type_LatLong, 0, 0, 1) in outkeys)
        self.assertTrue(QuadKey(Type_LatLong, 0, 1, 1) in outkeys)
        self.assertTrue(QuadKey(Type_LatLong, 1, 0, 1) in outkeys)
        self.assertTrue(QuadKey(Type_LatLong, 1, 1, 1) in outkeys)

    def test_selected_cities(self):
        """
        Test a given set of known places make sure they work.
        """
        quad_key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
            Type_LatLong, GeoCoordinate2d(Longitude(-122.4183),
                                          Latitude(37.7750)), 1)
        self.assertEquals("0", quad_key.toInternalString())
        quad_key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
            Type_LatLong, GeoCoordinate2d(Longitude(-122.4183),
                                          Latitude(37.7750)), 2)
        self.assertEquals("02", quad_key.toInternalString())
        quad_key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
            Type_LatLong, GeoCoordinate2d(Longitude(-122.4183),
                                          Latitude(37.7750)), 3)
        self.assertEquals("021", quad_key.toInternalString())
        quad_key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
            Type_LatLong, GeoCoordinate2d(Longitude(-122.4183),
                                          Latitude(37.7750)), 4)
        self.assertEquals("0210", quad_key.toInternalString())

        quad_key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
            Type_LatLong, GeoCoordinate2d(Longitude(+134.9),
                                          Latitude(-67.6)), 3)
        self.assertTrue(QuadKey(Type_LatLong, 0, 6, 3) == quad_key)
        self.assertEquals("332", quad_key.toInternalString())

        quad_key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
            Type_LatLong, GeoCoordinate2d(Longitude(+135.0),
                                          Latitude(-67.5)), 3)
        self.assertTrue(QuadKey(Type_LatLong, 1, 7, 3) == quad_key)
        self.assertEquals("331", quad_key.toInternalString())


def main():
    """
    Bootstrap function for this module
    """
    suite = unittest.TestLoader().loadTestsFromTestCase(TestLatLongSystem)
    unittest.TextTestRunner(verbosity=2).run(suite)

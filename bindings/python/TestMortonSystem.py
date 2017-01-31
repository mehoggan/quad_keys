"""
Unit Tests for Morton System
"""

from __future__ import print_function
import unittest
from quadkey import QuadKey
from quadkey import Type__None
from quadkey import Type_Morton
from quadkey import GeoCoordinate2d
from quadkey import GeoCoordinateBoundingBox2d
from quadkey import Longitude
from quadkey import Latitude


class TestMortonSystem(unittest.TestCase):
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
        Test to get parent of a generically formatted quad_quad_key.
        """
        # Same as BingSystem

    def test_is_my_ancestor(self):
        """
        Checks to see if specified quadkey up in the hierarchy is an "ancestor"
        of the given quad_quad_key.
        """
        # Same as BingSystem

    def test_get_ancestor(self):
        """
        Gets the ancestor up the tree according to a delta provided.
        """
        quad_key = QuadKey(Type_Morton, 0, 1, 1)
        ancestor = QuadKey(Type_Morton, 0, 0, 0)
        self.assertEqual(ancestor, quad_key.getAncestor(1))
        self.assertEqual(quad_key.getParent(), quad_key.getAncestor(1))

        quad_key = QuadKey(Type_Morton, 0, 0, 1)
        ancestor = QuadKey(Type_Morton, 0, 0, 0)
        self.assertEqual(ancestor, quad_key.getAncestor(1))
        self.assertEqual(quad_key.getParent(), quad_key.getAncestor(1))

        quad_key = QuadKey(Type_Morton, 1, 1, 1)
        ancestor = QuadKey(Type_Morton, 0, 0, 0)
        self.assertEqual(ancestor, quad_key.getAncestor(1))

        quad_key = QuadKey(Type_Morton, 1, 2, 1)
        ancestor = QuadKey(Type_Morton, 0, 1, 0)
        self.assertEqual(ancestor, quad_key.getAncestor(1))

        quad_key = QuadKey(Type_Morton, 0, 3, 1)
        ancestor = QuadKey(Type_Morton, 0, 1, 0)
        self.assertEqual(ancestor, quad_key.getAncestor(1))

    def test_get_child(self):
        """
        Get a single child NE, SE, NW, SW
        """
        # Same as BingSystem

    def test_get_children(self):
        """
        Get all the childern of a quad_quad_key.
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
        quad_keys = QuadKey(Type_Morton, 0, 0, 1).getSiblings()
        self.assertEqual(3, quad_keys.size())
        self.assertTrue(QuadKey(Type_Morton, 1, 0, 1) in quad_keys)
        self.assertTrue(QuadKey(Type_Morton, 1, 1, 1) in quad_keys)
        self.assertTrue(QuadKey(Type_Morton, 0, 1, 1) in quad_keys)
        quad_keys = QuadKey(Type_Morton, 1, 3, 1).getSiblings()
        self.assertEqual(3, quad_keys.size())
        self.assertTrue(QuadKey(Type_Morton, 1, 2, 1) in quad_keys)
        self.assertTrue(QuadKey(Type_Morton, 0, 2, 1) in quad_keys)
        self.assertTrue(QuadKey(Type_Morton, 0, 3, 1) in quad_keys)

    def test_get_neighbors(self):
        """
        Test to get the neighbors of a given quadquad_quad_key.
        """
        # Same as BingSystem but just to be safe
        quad_keys = QuadKey().getNeighbors()
        self.assertTrue(quad_keys.empty())

        quad_keys = QuadKey(Type_Morton, 0, 0, 2).getNeighbors()
        self.assertEqual(5, quad_keys.size())
        self.assertTrue(QuadKey(Type_Morton, 0, 1, 2) in quad_keys)
        self.assertTrue(QuadKey(Type_Morton, 1, 1, 2) in quad_keys)
        self.assertTrue(QuadKey(Type_Morton, 1, 0, 2) in quad_keys)
        self.assertTrue(QuadKey(Type_Morton, 0, 7, 2) in quad_keys)
        self.assertTrue(QuadKey(Type_Morton, 1, 7, 2) in quad_keys)

        quad_keys = QuadKey(Type_Morton, 0, 1, 2).getNeighbors()
        self.assertEqual(5, quad_keys.size())
        self.assertTrue(QuadKey(Type_Morton, 0, 0, 2) in quad_keys)
        self.assertTrue(QuadKey(Type_Morton, 1, 0, 2) in quad_keys)
        self.assertTrue(QuadKey(Type_Morton, 1, 1, 2) in quad_keys)
        self.assertTrue(QuadKey(Type_Morton, 1, 2, 2) in quad_keys)
        self.assertTrue(QuadKey(Type_Morton, 0, 2, 2) in quad_keys)

        quad_keys = QuadKey(Type_Morton, 0, 2, 2).getNeighbors()
        self.assertEqual(5, quad_keys.size())
        self.assertTrue(QuadKey(Type_Morton, 0, 1, 2) in quad_keys)
        self.assertTrue(QuadKey(Type_Morton, 1, 1, 2) in quad_keys)
        self.assertTrue(QuadKey(Type_Morton, 1, 2, 2) in quad_keys)
        self.assertTrue(QuadKey(Type_Morton, 1, 3, 2) in quad_keys)
        self.assertTrue(QuadKey(Type_Morton, 0, 3, 2) in quad_keys)

        quad_keys = QuadKey(Type_Morton, 0, 3, 2).getNeighbors()
        self.assertEqual(5, quad_keys.size())
        self.assertTrue(QuadKey(Type_Morton, 0, 2, 2) in quad_keys)
        self.assertTrue(QuadKey(Type_Morton, 1, 2, 2) in quad_keys)
        self.assertTrue(QuadKey(Type_Morton, 1, 3, 2) in quad_keys)
        self.assertTrue(QuadKey(Type_Morton, 1, 4, 2) in quad_keys)
        self.assertTrue(QuadKey(Type_Morton, 0, 4, 2) in quad_keys)

        quad_keys = QuadKey(Type_Morton, 0, 0, 2).getNeighbors()
        self.assertEqual(5, quad_keys.size())
        self.assertTrue(QuadKey(Type_Morton, 0, 1, 2) in quad_keys)
        self.assertTrue(QuadKey(Type_Morton, 1, 1, 2) in quad_keys)
        self.assertTrue(QuadKey(Type_Morton, 1, 0, 2) in quad_keys)
        self.assertTrue(QuadKey(Type_Morton, 1, 7, 2) in quad_keys)
        self.assertTrue(QuadKey(Type_Morton, 0, 7, 2) in quad_keys)

        quad_keys = QuadKey(Type_Morton, 3, 1, 2).getNeighbors()
        self.assertEqual(5, quad_keys.size())
        self.assertTrue(QuadKey(Type_Morton, 3, 0, 2) in quad_keys)
        self.assertTrue(QuadKey(Type_Morton, 2, 0, 2) in quad_keys)
        self.assertTrue(QuadKey(Type_Morton, 2, 1, 2) in quad_keys)
        self.assertTrue(QuadKey(Type_Morton, 2, 2, 2) in quad_keys)
        self.assertTrue(QuadKey(Type_Morton, 3, 2, 2) in quad_keys)

        quad_keys = QuadKey(Type_Morton, 3, 2, 2).getNeighbors()
        self.assertEqual(5, quad_keys.size())
        self.assertTrue(QuadKey(Type_Morton, 3, 1, 2) in quad_keys)
        self.assertTrue(QuadKey(Type_Morton, 2, 1, 2) in quad_keys)
        self.assertTrue(QuadKey(Type_Morton, 2, 2, 2) in quad_keys)
        self.assertTrue(QuadKey(Type_Morton, 2, 3, 2) in quad_keys)
        self.assertTrue(QuadKey(Type_Morton, 3, 3, 2) in quad_keys)

        quad_keys = QuadKey(Type_Morton, 3, 3, 2).getNeighbors()
        self.assertEqual(5, quad_keys.size())
        self.assertTrue(QuadKey(Type_Morton, 3, 2, 2) in quad_keys)
        self.assertTrue(QuadKey(Type_Morton, 2, 2, 2) in quad_keys)
        self.assertTrue(QuadKey(Type_Morton, 2, 3, 2) in quad_keys)
        self.assertTrue(QuadKey(Type_Morton, 2, 4, 2) in quad_keys)
        self.assertTrue(QuadKey(Type_Morton, 3, 4, 2) in quad_keys)

        quad_keys = QuadKey(Type_Morton, 4, 7, 3).getNeighbors()
        self.assertEqual(8, quad_keys.size())
        self.assertTrue(QuadKey(Type_Morton, 3, 7, 3) in quad_keys)
        self.assertTrue(QuadKey(Type_Morton, 3, 6, 3) in quad_keys)
        self.assertTrue(QuadKey(Type_Morton, 4, 6, 3) in quad_keys)
        self.assertTrue(QuadKey(Type_Morton, 5, 6, 3) in quad_keys)
        self.assertTrue(QuadKey(Type_Morton, 5, 7, 3) in quad_keys)
        self.assertTrue(QuadKey(Type_Morton, 5, 8, 3) in quad_keys)
        self.assertTrue(QuadKey(Type_Morton, 4, 8, 3) in quad_keys)
        self.assertTrue(QuadKey(Type_Morton, 3, 8, 3) in quad_keys)

        quad_keys = QuadKey(Type_Morton, 4, 0, 3).getNeighbors()
        self.assertEqual(8, quad_keys.size())
        self.assertTrue(QuadKey(Type_Morton, 3, 0, 3) in quad_keys)
        self.assertTrue(QuadKey(Type_Morton, 3, 1, 3) in quad_keys)
        self.assertTrue(QuadKey(Type_Morton, 4, 1, 3) in quad_keys)
        self.assertTrue(QuadKey(Type_Morton, 5, 1, 3) in quad_keys)
        self.assertTrue(QuadKey(Type_Morton, 5, 0, 3) in quad_keys)
        self.assertTrue(QuadKey(Type_Morton, 5, 15, 3) in quad_keys)
        self.assertTrue(QuadKey(Type_Morton, 4, 15, 3) in quad_keys)
        self.assertTrue(QuadKey(Type_Morton, 3, 15, 3) in quad_keys)

        quad_keys = QuadKey(Type_Morton, 0, 0, 0).getNeighbors()
        self.assertEqual(0, quad_keys.size())

    def test_to_string_from_string(self):
        """
        Test to convert an internally formatted string and back.
        """
        # X ==> Unused
        # O ==> Used but never set
        # (0,1) ==> Binary digits
        quad_key = QuadKey(Type_Morton, 0, 0, 0)
        fmt = quad_key.toInternalString()
        self.assertEqual("65537",
                         fmt)  # ... XXXX XXXX XXX1 XXXX XXXX XXXX XXO1
        quad_key_back = QuadKey.fromInternalString(Type_Morton, fmt)
        self.assertEqual(quad_key, quad_key_back)

        quad_key = QuadKey(Type_Morton, 0, 1, 0)
        fmt = quad_key.toInternalString()
        self.assertEqual("65536",
                         fmt)  # ... XXXX XXXX XXX1 XXXX XXXX XXXX XXO0
        quad_key_back = QuadKey.fromInternalString(Type_Morton, fmt)
        self.assertEqual(quad_key, quad_key_back)

        quad_key = QuadKey(Type_Morton, 0, 0, 1)
        fmt = quad_key.toInternalString()
        self.assertEqual("131078",
                         fmt)  # ... XXXX XXXX XX1X XXXX XXXX XXXX O110
        quad_key_back = QuadKey.fromInternalString(Type_Morton, fmt)
        self.assertEqual(quad_key, quad_key_back)

        quad_key = QuadKey(Type_Morton, 0, 1, 1)
        fmt = quad_key.toInternalString()
        self.assertEqual("131079",
                         fmt)  # ... XXXX XXXX XX1O OOOO OOOO OOOO O111
        quad_key_back = QuadKey.fromInternalString(Type_Morton, fmt)
        self.assertEqual(quad_key, quad_key_back)

        quad_key = QuadKey(Type_Morton, 0, 2, 1)
        fmt = quad_key.toInternalString()
        self.assertEqual("131074",
                         fmt)  # ... XXXX XXXX XX1X XXXX XXXX XXXX O010
        quad_key_back = QuadKey.fromInternalString(Type_Morton, fmt)
        self.assertEqual(quad_key, quad_key_back)

        quad_key = QuadKey(Type_Morton, 0, 3, 1)
        fmt = quad_key.toInternalString()
        self.assertEqual("131075",
                         fmt)  # ... XXXX XXXX XX1X XXXX XXXX XXXX O011
        quad_key_back = QuadKey.fromInternalString(Type_Morton, fmt)
        self.assertEqual(quad_key, quad_key_back)

        quad_key = QuadKey(Type_Morton, 1, 0, 1)
        fmt = quad_key.toInternalString()
        self.assertEqual("131076",
                         fmt)  # ... XXXX XXXX XX1X XXXX XXXX XXXX O100
        quad_key_back = QuadKey.fromInternalString(Type_Morton, fmt)
        self.assertEqual(quad_key, quad_key_back)

        quad_key = QuadKey(Type_Morton, 1, 1, 1)
        fmt = quad_key.toInternalString()
        self.assertEqual("131077",
                         fmt)  # ... XXXX XXXX XX1X XXXX XXXX XXXX O101
        quad_key_back = QuadKey.fromInternalString(Type_Morton, fmt)
        self.assertEqual(quad_key, quad_key_back)

        quad_key = QuadKey(Type_Morton, 1, 2, 1)
        fmt = quad_key.toInternalString()
        self.assertEqual("131072",
                         fmt)  # ... XXXX XXXX XX1X XXXX XXXX XXXX O000
        quad_key_back = QuadKey.fromInternalString(Type_Morton, fmt)
        self.assertEqual(quad_key, quad_key_back)

        quad_key = QuadKey(Type_Morton, 1, 3, 1)
        fmt = quad_key.toInternalString()
        self.assertEqual("131073",
                         fmt)  # ... XXXX XXXX XX1X XXXX XXXX XXXX O001
        quad_key_back = QuadKey.fromInternalString(Type_Morton, fmt)
        self.assertEqual(quad_key, quad_key_back)

        quad_key = QuadKey(Type_Morton, 0, 0, 2)
        fmt = quad_key.toInternalString()
        self.assertEqual("262168",
                         fmt)  # ... XXXX XXXX X1XX XXXX XXXX XXO1 1000
        quad_key_back = QuadKey.fromInternalString(Type_Morton, fmt)
        self.assertEqual(quad_key, quad_key_back)

        quad_key = QuadKey(Type_Morton, 0, 1, 2)
        fmt = quad_key.toInternalString()
        self.assertEqual("262169",
                         fmt)  # ... XXXX XXXX X1XX XXXX XXXX XXO1 1001
        quad_key_back = QuadKey.fromInternalString(Type_Morton, fmt)
        self.assertEqual(quad_key, quad_key_back)

        quad_key = QuadKey(Type_Morton, 0, 2, 2)
        fmt = quad_key.toInternalString()
        self.assertEqual("262172",
                         fmt)  # ... XXXX XXXX X1XX XXXX XXXX XXO1 1100
        quad_key_back = QuadKey.fromInternalString(Type_Morton, fmt)
        self.assertEqual(quad_key, quad_key_back)

        quad_key = QuadKey(Type_Morton, 0, 3, 2)
        fmt = quad_key.toInternalString()
        self.assertEqual("262173",
                         fmt)  # ... XXXX XXXX X1XX XXXX XXXX XXO1 1101
        quad_key_back = QuadKey.fromInternalString(Type_Morton, fmt)
        self.assertEqual(quad_key, quad_key_back)

        quad_key = QuadKey(Type_Morton, 0, 4, 2)
        fmt = quad_key.toInternalString()
        self.assertEqual("262152",
                         fmt)  # ... XXXX XXXX X1XX XXXX XXXX XXO0 1000
        quad_key_back = QuadKey.fromInternalString(Type_Morton, fmt)
        self.assertEqual(quad_key, quad_key_back)

        quad_key = QuadKey(Type_Morton, 0, 5, 2)
        fmt = quad_key.toInternalString()
        self.assertEqual("262153",
                         fmt)  # ... XXXX XXXX X1XX XXXX XXXX XXO0 1001
        quad_key_back = QuadKey.fromInternalString(Type_Morton, fmt)
        self.assertEqual(quad_key, quad_key_back)

        quad_key = QuadKey(Type_Morton, 0, 6, 2)
        fmt = quad_key.toInternalString()
        self.assertEqual("262156",
                         fmt)  # ... XXXX XXXX X1XX XXXX XXXX XXO0 1100
        quad_key_back = QuadKey.fromInternalString(Type_Morton, fmt)
        self.assertEqual(quad_key, quad_key_back)

        quad_key = QuadKey(Type_Morton, 0, 7, 2)
        fmt = quad_key.toInternalString()
        self.assertEqual("262157",
                         fmt)  # ... XXXX XXXX X1XX XXXX XXXX XXO0 1101
        quad_key_back = QuadKey.fromInternalString(Type_Morton, fmt)
        self.assertEqual(quad_key, quad_key_back)

        quad_key = QuadKey(Type_Morton, 1, 0, 2)
        fmt = quad_key.toInternalString()
        self.assertEqual("262170",
                         fmt)  # ... XXXX XXXX X1XX XXXX XXXX XXO1 1010
        quad_key_back = QuadKey.fromInternalString(Type_Morton, fmt)
        self.assertEqual(quad_key, quad_key_back)

        quad_key = QuadKey(Type_Morton, 1, 1, 2)
        fmt = quad_key.toInternalString()
        self.assertEqual("262171",
                         fmt)  # ... XXXX XXXX X1XX XXXX XXXX XXO1 1011
        quad_key_back = QuadKey.fromInternalString(Type_Morton, fmt)
        self.assertEqual(quad_key, quad_key_back)

        quad_key = QuadKey(Type_Morton, 1, 2, 2)
        fmt = quad_key.toInternalString()
        self.assertEqual("262174",
                         fmt)  # ... XXXX XXXX X1XX XXXX XXXX XXO1 1110
        quad_key_back = QuadKey.fromInternalString(Type_Morton, fmt)
        self.assertEqual(quad_key, quad_key_back)

        quad_key = QuadKey(Type_Morton, 1, 3, 2)
        fmt = quad_key.toInternalString()
        self.assertEqual("262175",
                         fmt)  # ... XXXX XXXX X1XX XXXX XXXX XXO1 1111
        quad_key_back = QuadKey.fromInternalString(Type_Morton, fmt)
        self.assertEqual(quad_key, quad_key_back)

        quad_key = QuadKey(Type_Morton, 1, 4, 2)
        fmt = quad_key.toInternalString()
        self.assertEqual("262154",
                         fmt)  # ... XXXX XXXX X1XX XXXX XXXX XXO0 1010
        quad_key_back = QuadKey.fromInternalString(Type_Morton, fmt)
        self.assertEqual(quad_key, quad_key_back)

        quad_key = QuadKey(Type_Morton, 1, 5, 2)
        fmt = quad_key.toInternalString()
        self.assertEqual("262155",
                         fmt)  # ... XXXX XXXX X1XX XXXX XXXX XXO0 1011
        quad_key_back = QuadKey.fromInternalString(Type_Morton, fmt)
        self.assertEqual(quad_key, quad_key_back)

        quad_key = QuadKey(Type_Morton, 1, 6, 2)
        fmt = quad_key.toInternalString()
        self.assertEqual("262158",
                         fmt)  # ... XXXX XXXX X1XX XXXX XXXX XXO0 1110
        quad_key_back = QuadKey.fromInternalString(Type_Morton, fmt)
        self.assertEqual(quad_key, quad_key_back)

        quad_key = QuadKey(Type_Morton, 1, 7, 2)
        fmt = quad_key.toInternalString()
        self.assertEqual("262159",
                         fmt)  # ... XXXX XXXX X1XX XXXX XXXX XXO0 1111
        quad_key_back = QuadKey.fromInternalString(Type_Morton, fmt)
        self.assertEqual(quad_key, quad_key_back)

        quad_key = QuadKey(Type_Morton, 2, 0, 2)
        fmt = quad_key.toInternalString()
        self.assertEqual("262160",
                         fmt)  # ... XXXX XXXX X1XX XXXX XXXX XXO1 0000
        quad_key_back = QuadKey.fromInternalString(Type_Morton, fmt)
        self.assertEqual(quad_key, quad_key_back)

        quad_key = QuadKey(Type_Morton, 2, 1, 2)
        fmt = quad_key.toInternalString()
        self.assertEqual("262161",
                         fmt)  # ... XXXX XXXX X1XX XXXX XXXX XXO1 0001
        quad_key_back = QuadKey.fromInternalString(Type_Morton, fmt)
        self.assertEqual(quad_key, quad_key_back)

        quad_key = QuadKey(Type_Morton, 2, 2, 2)
        fmt = quad_key.toInternalString()
        self.assertEqual("262164",
                         fmt)  # ... XXXX XXXX X1XX XXXX XXXX XXO1 0100
        quad_key_back = QuadKey.fromInternalString(Type_Morton, fmt)
        self.assertEqual(quad_key, quad_key_back)

        quad_key = QuadKey(Type_Morton, 2, 3, 2)
        fmt = quad_key.toInternalString()
        self.assertEqual("262165",
                         fmt)  # ... XXXX XXXX X1XX XXXX XXXX XXO1 0101
        quad_key_back = QuadKey.fromInternalString(Type_Morton, fmt)
        self.assertEqual(quad_key, quad_key_back)

        quad_key = QuadKey(Type_Morton, 2, 4, 2)
        fmt = quad_key.toInternalString()
        self.assertEqual("262144",
                         fmt)  # ... XXXX XXXX X1XX XXXX XXXX XXO0 0000
        quad_key_back = QuadKey.fromInternalString(Type_Morton, fmt)
        self.assertEqual(quad_key, quad_key_back)

        quad_key = QuadKey(Type_Morton, 2, 5, 2)
        fmt = quad_key.toInternalString()
        self.assertEqual("262145",
                         fmt)  # ... XXXX XXXX X1XX XXXX XXXX XXO0 0001
        quad_key_back = QuadKey.fromInternalString(Type_Morton, fmt)
        self.assertEqual(quad_key, quad_key_back)

        quad_key = QuadKey(Type_Morton, 2, 6, 2)
        fmt = quad_key.toInternalString()
        self.assertEqual("262148",
                         fmt)  # ... XXXX XXXX X1XX XXXX XXXX XXO0 0100
        quad_key_back = QuadKey.fromInternalString(Type_Morton, fmt)
        self.assertEqual(quad_key, quad_key_back)

        quad_key = QuadKey(Type_Morton, 2, 7, 2)
        fmt = quad_key.toInternalString()
        self.assertEqual("262149",
                         fmt)  # ... XXXX XXXX X1XX XXXX XXXX XXO0 0101
        quad_key_back = QuadKey.fromInternalString(Type_Morton, fmt)
        self.assertEqual(quad_key, quad_key_back)

        quad_key = QuadKey(Type_Morton, 3, 0, 2)
        fmt = quad_key.toInternalString()
        self.assertEqual("262162",
                         fmt)  # ... XXXX XXXX X1XX XXXX XXXX XXO1 0010
        quad_key_back = QuadKey.fromInternalString(Type_Morton, fmt)
        self.assertEqual(quad_key, quad_key_back)

        quad_key = QuadKey(Type_Morton, 3, 1, 2)
        fmt = quad_key.toInternalString()
        self.assertEqual("262163",
                         fmt)  # ... XXXX XXXX X1XX XXXX XXXX XXO1 0011
        quad_key_back = QuadKey.fromInternalString(Type_Morton, fmt)
        self.assertEqual(quad_key, quad_key_back)

        quad_key = QuadKey(Type_Morton, 3, 2, 2)
        fmt = quad_key.toInternalString()
        self.assertEqual("262166",
                         fmt)  # ... XXXX XXXX X1XX XXXX XXXX XXO1 0110
        quad_key_back = QuadKey.fromInternalString(Type_Morton, fmt)
        self.assertEqual(quad_key, quad_key_back)

        quad_key = QuadKey(Type_Morton, 3, 3, 2)
        fmt = quad_key.toInternalString()
        self.assertEqual("262167",
                         fmt)  # ... XXXX XXXX X1XX XXXX XXXX XXO1 0111
        quad_key_back = QuadKey.fromInternalString(Type_Morton, fmt)
        self.assertEqual(quad_key, quad_key_back)

        quad_key = QuadKey(Type_Morton, 3, 4, 2)
        fmt = quad_key.toInternalString()
        self.assertEqual("262146",
                         fmt)  # ... XXXX XXXX X1XX XXXX XXXX XXO0 0010
        quad_key_back = QuadKey.fromInternalString(Type_Morton, fmt)
        self.assertEqual(quad_key, quad_key_back)

        quad_key = QuadKey(Type_Morton, 3, 5, 2)
        fmt = quad_key.toInternalString()
        self.assertEqual("262147",
                         fmt)  # ... XXXX XXXX X1XX XXXX XXXX XXO0 0011
        quad_key_back = QuadKey.fromInternalString(Type_Morton, fmt)
        self.assertEqual(quad_key, quad_key_back)

        quad_key = QuadKey(Type_Morton, 3, 6, 2)
        fmt = quad_key.toInternalString()
        self.assertEqual("262150",
                         fmt)  # ... XXXX XXXX X1XX XXXX XXXX XXO0 0110
        quad_key_back = QuadKey.fromInternalString(Type_Morton, fmt)
        self.assertEqual(quad_key, quad_key_back)

        quad_key = QuadKey(Type_Morton, 3, 7, 2)
        fmt = quad_key.toInternalString()
        self.assertEqual("262151",
                         fmt)  # ... XXXX XXXX X1XX XXXX XXXX XXO0 0111
        quad_key_back = QuadKey.fromInternalString(Type_Morton, fmt)
        self.assertEqual(quad_key, quad_key_back)

    def test_get_geo_coordinate_bounds_2d(self):
        """
        Test to get geographic bounds of quadquad_quad_key.
        """
        bbox = GeoCoordinateBoundingBox2d()

        quad_key = QuadKey(Type_Morton, 0, 0, 0)
        quad_key.getGeoCoordinateBounds2d(bbox)
        self.assertTrue(bbox.lowerLeft().near(GeoCoordinate2d(
            Longitude(-180.0), Latitude(-90.0)), 1e-4))
        self.assertTrue(bbox.upperRight().near(GeoCoordinate2d(
            Longitude(-0.1), Latitude(+90.0)), 1e-4))

        quad_key = QuadKey(Type_Morton, 0, 1, 0)
        quad_key.getGeoCoordinateBounds2d(bbox)
        self.assertTrue(bbox.lowerLeft().near(GeoCoordinate2d(
            Longitude(+0.0), Latitude(-90.0)), 1e-4))
        self.assertTrue(bbox.upperRight().near(GeoCoordinate2d(
            Longitude(+180.0), Latitude(+90.0)), 1e-4))

        quad_key = QuadKey(Type_Morton, 0, 0, 1)
        quad_key.getGeoCoordinateBounds2d(bbox)
        self.assertTrue(bbox.lowerLeft().near(GeoCoordinate2d(
            Longitude(-180.0), Latitude(-90.0)), 1e-4))
        self.assertTrue(bbox.upperRight().near(GeoCoordinate2d(
            Longitude(-90.0), Latitude(+0.0)), 1e-4))

        quad_key = QuadKey(Type_Morton, 0, 1, 1)
        quad_key.getGeoCoordinateBounds2d(bbox)
        self.assertTrue(bbox.lowerLeft().near(GeoCoordinate2d(
            Longitude(-90.0), Latitude(-90.0)), 1e-4))
        self.assertTrue(bbox.upperRight().near(GeoCoordinate2d(
            Longitude(+0.0), Latitude(+0.0)), 1e-4))

        quad_key = QuadKey(Type_Morton, 0, 2, 1)
        quad_key.getGeoCoordinateBounds2d(bbox)
        self.assertTrue(bbox.lowerLeft().near(GeoCoordinate2d(
            Longitude(+0.0), Latitude(-90.0)), 1e-4))
        self.assertTrue(bbox.upperRight().near(GeoCoordinate2d(
            Longitude(+90.0), Latitude(+0.0)), 1e-4))

        quad_key = QuadKey(Type_Morton, 0, 3, 1)
        quad_key.getGeoCoordinateBounds2d(bbox)
        self.assertTrue(bbox.lowerLeft().near(GeoCoordinate2d(
            Longitude(+90.0), Latitude(-90.0)), 1e-4))
        self.assertTrue(bbox.upperRight().near(GeoCoordinate2d(
            Longitude(+180.0), Latitude(+0.0)), 1e-4))

        quad_key = QuadKey(Type_Morton, 1, 0, 1)
        quad_key.getGeoCoordinateBounds2d(bbox)
        self.assertTrue(bbox.lowerLeft().near(GeoCoordinate2d(
            Longitude(-180.0), Latitude(+0.0)), 1e-4))
        self.assertTrue(bbox.upperRight().near(GeoCoordinate2d(
            Longitude(-90.0), Latitude(+90.0)), 1e-4))

        quad_key = QuadKey(Type_Morton, 1, 1, 1)
        quad_key.getGeoCoordinateBounds2d(bbox)
        self.assertTrue(bbox.lowerLeft().near(GeoCoordinate2d(
            Longitude(-90.0), Latitude(+0.0)), 1e-4))
        self.assertTrue(bbox.upperRight().near(GeoCoordinate2d(
            Longitude(+0.0), Latitude(+90.0)), 1e-4))

        quad_key = QuadKey(Type_Morton, 1, 2, 1)
        quad_key.getGeoCoordinateBounds2d(bbox)
        self.assertTrue(bbox.lowerLeft().near(GeoCoordinate2d(
            Longitude(+0.0), Latitude(+0.0)), 1e-4))
        self.assertTrue(bbox.upperRight().near(GeoCoordinate2d(
            Longitude(+90.0), Latitude(+90.0)), 1e-4))

        quad_key = QuadKey(Type_Morton, 1, 3, 1)
        quad_key.getGeoCoordinateBounds2d(bbox)
        self.assertTrue(bbox.lowerLeft().near(GeoCoordinate2d(
            Longitude(+90.0), Latitude(+0.0)), 1e-4))
        self.assertTrue(bbox.upperRight().near(GeoCoordinate2d(
            Longitude(+180.0), Latitude(+90.0)), 1e-4))

    def test_get_key_from_longitude_latitude_at_depth_to_bounds(self):
        """
        Test to get a quadkey from longitude and latitude and then get bounds.
        """
        depth = 0

        coords = GeoCoordinate2d(Longitude(-0.1), Latitude(0.0))
        quad_key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
            Type_Morton, coords, depth)
        self.assertEqual("65537", quad_key.toInternalString())
        coords = GeoCoordinate2d(Longitude(-180.0), Latitude(90.0))
        quad_key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
            Type_Morton, coords, depth)
        self.assertEqual("65537", quad_key.toInternalString())
        coords = GeoCoordinate2d(Longitude(-180.0), Latitude(-90.0))
        quad_key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
            Type_Morton, coords, depth)
        self.assertEqual("65537", quad_key.toInternalString())
        actual = GeoCoordinateBoundingBox2d()
        quad_key.getGeoCoordinateBounds2d(actual)
        self.assertTrue(GeoCoordinate2d(Longitude(-180.0),
                                        Latitude(-90.0)).near(
            actual.lowerLeft(), 1))
        self.assertTrue(GeoCoordinate2d(Longitude(-0.1),
                                        Latitude(+90.0)).near(
            actual.upperRight(), 1))

        coords = GeoCoordinate2d(Longitude(0.0), Latitude(0.0))
        quad_key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
            Type_Morton, coords, depth)
        self.assertEqual("65536", quad_key.toInternalString())
        coords = GeoCoordinate2d(Longitude(180.0), Latitude(-90.0))
        quad_key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
            Type_Morton, coords, depth)
        self.assertEqual("65536", quad_key.toInternalString())
        coords = GeoCoordinate2d(Longitude(180.0), Latitude(90.0))
        quad_key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
            Type_Morton, coords, depth)
        self.assertEqual("65536", quad_key.toInternalString())
        actual = GeoCoordinateBoundingBox2d()
        quad_key.getGeoCoordinateBounds2d(actual)
        self.assertTrue(GeoCoordinate2d(Longitude(+0.0),
                                        Latitude(-90.0)).near(
            actual.lowerLeft(), 1))
        self.assertTrue(GeoCoordinate2d(Longitude(+180.0),
                                        Latitude(+90.0)).near(
            actual.upperRight(), 1))

        depth = 1

        coords = GeoCoordinate2d(Longitude(-180.0), Latitude(-0.1))
        quad_key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
            Type_Morton, coords, depth)
        self.assertEqual("131078", quad_key.toInternalString())
        coords = GeoCoordinate2d(Longitude(-180.0), Latitude(-90.0))
        quad_key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
            Type_Morton, coords, depth)
        self.assertEqual("131078", quad_key.toInternalString())
        coords = GeoCoordinate2d(Longitude(-90.1), Latitude(-90.0))
        quad_key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
            Type_Morton, coords, depth)
        self.assertEqual("131078", quad_key.toInternalString())
        coords = GeoCoordinate2d(Longitude(-90.1), Latitude(-0.1))
        quad_key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
            Type_Morton, coords, depth)
        self.assertEqual("131078", quad_key.toInternalString())

        coords = GeoCoordinate2d(Longitude(-90.0), Latitude(-0.1))
        quad_key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
            Type_Morton, coords, depth)
        self.assertEqual("131079", quad_key.toInternalString())
        coords = GeoCoordinate2d(Longitude(-90.0), Latitude(-90.0))
        quad_key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
            Type_Morton, coords, depth)
        self.assertEqual("131079", quad_key.toInternalString())
        coords = GeoCoordinate2d(Longitude(-0.1), Latitude(-90.0))
        quad_key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
            Type_Morton, coords, depth)
        self.assertEqual("131079", quad_key.toInternalString())
        coords = GeoCoordinate2d(Longitude(-0.1), Latitude(-0.1))
        quad_key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
            Type_Morton, coords, depth)
        self.assertEqual("131079", quad_key.toInternalString())

        coords = GeoCoordinate2d(Longitude(0.0), Latitude(-0.1))
        quad_key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
            Type_Morton, coords, depth)
        self.assertEqual("131074", quad_key.toInternalString())
        coords = GeoCoordinate2d(Longitude(0.0), Latitude(-90.0))
        quad_key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
            Type_Morton, coords, depth)
        self.assertEqual("131074", quad_key.toInternalString())
        coords = GeoCoordinate2d(Longitude(90.0), Latitude(-90.0))
        quad_key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
            Type_Morton, coords, depth)
        self.assertEqual("131074", quad_key.toInternalString())
        coords = GeoCoordinate2d(Longitude(90.0), Latitude(-0.1))
        quad_key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
            Type_Morton, coords, depth)
        self.assertEqual("131074", quad_key.toInternalString())

        coords = GeoCoordinate2d(Longitude(90.1), Latitude(-0.1))
        quad_key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
            Type_Morton, coords, depth)
        self.assertEqual("131075", quad_key.toInternalString())
        coords = GeoCoordinate2d(Longitude(90.1), Latitude(-90.0))
        quad_key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
            Type_Morton, coords, depth)
        self.assertEqual("131075", quad_key.toInternalString())
        coords = GeoCoordinate2d(Longitude(180.0), Latitude(-90.0))
        quad_key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
            Type_Morton, coords, depth)
        self.assertEqual("131075", quad_key.toInternalString())
        coords = GeoCoordinate2d(Longitude(180.0), Latitude(-0.1))
        quad_key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
            Type_Morton, coords, depth)
        self.assertEqual("131075", quad_key.toInternalString())

        coords = GeoCoordinate2d(Longitude(-180.0), Latitude(90.0))
        quad_key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
            Type_Morton, coords, depth)
        self.assertEqual("131076", quad_key.toInternalString())
        coords = GeoCoordinate2d(Longitude(-180.0), Latitude(0.0))
        quad_key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
            Type_Morton, coords, depth)
        self.assertEqual("131076", quad_key.toInternalString())
        coords = GeoCoordinate2d(Longitude(-90.1), Latitude(0.0))
        quad_key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
            Type_Morton, coords, depth)
        self.assertEqual("131076", quad_key.toInternalString())
        coords = GeoCoordinate2d(Longitude(-90.1), Latitude(90.0))
        quad_key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
            Type_Morton, coords, depth)
        self.assertEqual("131076", quad_key.toInternalString())

        coords = GeoCoordinate2d(Longitude(-90.0), Latitude(90.0))
        quad_key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
            Type_Morton, coords, depth)
        self.assertEqual("131077", quad_key.toInternalString())
        coords = GeoCoordinate2d(Longitude(-90.0), Latitude(0.0))
        quad_key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
            Type_Morton, coords, depth)
        self.assertEqual("131077", quad_key.toInternalString())
        coords = GeoCoordinate2d(Longitude(-0.1), Latitude(0.0))
        quad_key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
            Type_Morton, coords, depth)
        self.assertEqual("131077", quad_key.toInternalString())
        coords = GeoCoordinate2d(Longitude(-0.1), Latitude(90.0))
        quad_key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
            Type_Morton, coords, depth)
        self.assertEqual("131077", quad_key.toInternalString())

        coords = GeoCoordinate2d(Longitude(0.0), Latitude(90.0))
        quad_key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
            Type_Morton, coords, depth)
        self.assertEqual("131072", quad_key.toInternalString())
        coords = GeoCoordinate2d(Longitude(0.0), Latitude(0.0))
        quad_key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
            Type_Morton, coords, depth)
        self.assertEqual("131072", quad_key.toInternalString())
        coords = GeoCoordinate2d(Longitude(90.0), Latitude(0.0))
        quad_key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
            Type_Morton, coords, depth)
        self.assertEqual("131072", quad_key.toInternalString())
        coords = GeoCoordinate2d(Longitude(90.0), Latitude(90.0))
        quad_key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
            Type_Morton, coords, depth)
        self.assertEqual("131072", quad_key.toInternalString())

        coords = GeoCoordinate2d(Longitude(90.1), Latitude(90.0))
        quad_key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
            Type_Morton, coords, depth)
        self.assertEqual("131073", quad_key.toInternalString())
        coords = GeoCoordinate2d(Longitude(90.1), Latitude(0.0))
        quad_key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
            Type_Morton, coords, depth)
        self.assertEqual("131073", quad_key.toInternalString())
        coords = GeoCoordinate2d(Longitude(180.0), Latitude(0.0))
        quad_key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
            Type_Morton, coords, depth)
        self.assertEqual("131073", quad_key.toInternalString())
        coords = GeoCoordinate2d(Longitude(180.0), Latitude(90.0))
        quad_key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
            Type_Morton, coords, depth)
        self.assertEqual("131073", quad_key.toInternalString())

        tests = [
            [GeoCoordinateBoundingBox2d(
                GeoCoordinate2d(Longitude(-180.0), Latitude(-90.0)),
                GeoCoordinate2d(Longitude(-135.1), Latitude(-45.1))),
                "262168"],
            [GeoCoordinateBoundingBox2d(
                GeoCoordinate2d(Longitude(-135.0), Latitude(-90.0)),
                GeoCoordinate2d(Longitude(-90.1), Latitude(-45.1))),
                "262169"],
            [GeoCoordinateBoundingBox2d(
                GeoCoordinate2d(Longitude(-90.0), Latitude(-90.0)),
                GeoCoordinate2d(Longitude(-45.1), Latitude(-45.1))),
                "262172"],
            [GeoCoordinateBoundingBox2d(
                GeoCoordinate2d(Longitude(-45.0), Latitude(-90.0)),
                GeoCoordinate2d(Longitude(-0.1), Latitude(-45.1))),
                "262173"],
            [GeoCoordinateBoundingBox2d(
                GeoCoordinate2d(Longitude(+0.0), Latitude(-90.0)),
                GeoCoordinate2d(Longitude(+45.0), Latitude(-45.1))),
                "262152"],
            [GeoCoordinateBoundingBox2d(
                GeoCoordinate2d(Longitude(+45.1), Latitude(-90.0)),
                GeoCoordinate2d(Longitude(+90.0), Latitude(-45.1))),
                "262153"],
            [GeoCoordinateBoundingBox2d(
                GeoCoordinate2d(Longitude(+90.1), Latitude(-90.0)),
                GeoCoordinate2d(Longitude(+135.0), Latitude(-45.1))),
                "262156"],
            [GeoCoordinateBoundingBox2d(
                GeoCoordinate2d(Longitude(+135.1), Latitude(-90.0)),
                GeoCoordinate2d(Longitude(+180.0), Latitude(-45.1))),
                "262157"],
            [GeoCoordinateBoundingBox2d(
                GeoCoordinate2d(Longitude(-180.0), Latitude(-45.0)),
                GeoCoordinate2d(Longitude(-135.1), Latitude(-0.1))),
                "262170"],
            [GeoCoordinateBoundingBox2d(
                GeoCoordinate2d(Longitude(-135.0), Latitude(-45.0)),
                GeoCoordinate2d(Longitude(-90.1), Latitude(-0.1))),
                "262171"],
            [GeoCoordinateBoundingBox2d(
                GeoCoordinate2d(Longitude(-90.0), Latitude(-45.0)),
                GeoCoordinate2d(Longitude(-45.1), Latitude(-0.1))),
                "262174"],
            [GeoCoordinateBoundingBox2d(
                GeoCoordinate2d(Longitude(-45.0), Latitude(-45.0)),
                GeoCoordinate2d(Longitude(-0.1), Latitude(-0.1))),
                "262175"],
            [GeoCoordinateBoundingBox2d(
                GeoCoordinate2d(Longitude(+0.0), Latitude(-45.0)),
                GeoCoordinate2d(Longitude(+45.0), Latitude(-0.1))),
                "262154"],
            [GeoCoordinateBoundingBox2d(
                GeoCoordinate2d(Longitude(+45.1), Latitude(-45.0)),
                GeoCoordinate2d(Longitude(+90.0), Latitude(-0.1))),
                "262155"],
            [GeoCoordinateBoundingBox2d(
                GeoCoordinate2d(Longitude(+90.1), Latitude(-45.0)),
                GeoCoordinate2d(Longitude(+135.0), Latitude(-0.1))),
                "262158"],
            [GeoCoordinateBoundingBox2d(
                GeoCoordinate2d(Longitude(+135.1), Latitude(-45.0)),
                GeoCoordinate2d(Longitude(+180.0), Latitude(-0.1))),
                "262159"],
            [GeoCoordinateBoundingBox2d(
                GeoCoordinate2d(Longitude(-180.0), Latitude(+0.0)),
                GeoCoordinate2d(Longitude(-135.1), Latitude(+45.0))),
                "262160"],
            [GeoCoordinateBoundingBox2d(
                GeoCoordinate2d(Longitude(-135.0), Latitude(+0.0)),
                GeoCoordinate2d(Longitude(-90.1), Latitude(+45.0))),
                "262161"],
            [GeoCoordinateBoundingBox2d(
                GeoCoordinate2d(Longitude(-90.0), Latitude(+0.0)),
                GeoCoordinate2d(Longitude(-45.1), Latitude(+45.0))),
                "262164"],
            [GeoCoordinateBoundingBox2d(
                GeoCoordinate2d(Longitude(-45.0), Latitude(+0.0)),
                GeoCoordinate2d(Longitude(-0.1), Latitude(+45.0))),
                "262165"],
            [GeoCoordinateBoundingBox2d(
                GeoCoordinate2d(Longitude(+0.0), Latitude(+0.0)),
                GeoCoordinate2d(Longitude(+45.0), Latitude(+45.0))),
                "262144"],
            [GeoCoordinateBoundingBox2d(
                GeoCoordinate2d(Longitude(+45.1), Latitude(+0.0)),
                GeoCoordinate2d(Longitude(+90.0), Latitude(+45.0))),
                "262145"],
            [GeoCoordinateBoundingBox2d(
                GeoCoordinate2d(Longitude(+90.1), Latitude(+0.0)),
                GeoCoordinate2d(Longitude(+135.0), Latitude(+45.0))),
                "262148"],
            [GeoCoordinateBoundingBox2d(
                GeoCoordinate2d(Longitude(+135.1), Latitude(+0.0)),
                GeoCoordinate2d(Longitude(+180.0), Latitude(+45.0))),
                "262149"],
            [GeoCoordinateBoundingBox2d(
                GeoCoordinate2d(Longitude(-180.0), Latitude(+45.1)),
                GeoCoordinate2d(Longitude(-135.1), Latitude(+90.0))),
                "262162"],
            [GeoCoordinateBoundingBox2d(
                GeoCoordinate2d(Longitude(-135.0), Latitude(+45.1)),
                GeoCoordinate2d(Longitude(-90.1), Latitude(+90.0))),
                "262163"],
            [GeoCoordinateBoundingBox2d(
                GeoCoordinate2d(Longitude(-90.0), Latitude(+45.1)),
                GeoCoordinate2d(Longitude(-45.1), Latitude(+90.0))),
                "262166"],
            [GeoCoordinateBoundingBox2d(
                GeoCoordinate2d(Longitude(-45.0), Latitude(+45.1)),
                GeoCoordinate2d(Longitude(-0.1), Latitude(+90.0))),
                "262167"],
            [GeoCoordinateBoundingBox2d(
                GeoCoordinate2d(Longitude(+0.0), Latitude(+45.1)),
                GeoCoordinate2d(Longitude(+45.0), Latitude(+90.0))),
                "262146"],
            [GeoCoordinateBoundingBox2d(
                GeoCoordinate2d(Longitude(+45.1), Latitude(+45.1)),
                GeoCoordinate2d(Longitude(+90.0), Latitude(+90.0))),
                "262147"],
            [GeoCoordinateBoundingBox2d(
                GeoCoordinate2d(Longitude(+90.1), Latitude(+45.1)),
                GeoCoordinate2d(Longitude(+135.0), Latitude(+90.0))),
                "262150"],
            [GeoCoordinateBoundingBox2d(
                GeoCoordinate2d(Longitude(+135.1), Latitude(+45.1)),
                GeoCoordinate2d(Longitude(+180.0), Latitude(+90.0))),
                "262151"]]

        depth = 2

        for lst in tests:
            bbox = lst[0]
            ll = GeoCoordinate2d(bbox.lowerLeft())
            lr = GeoCoordinate2d(bbox.upperRight().longitude(),
                                 bbox.lowerLeft().latitude())
            ur = GeoCoordinate2d(bbox.upperRight())
            ul = GeoCoordinate2d(bbox.lowerLeft().longitude(),
                                 bbox.upperRight().latitude())
            quad_key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                Type_Morton, ll, depth)
            self.assertEqual(lst[1], quad_key.toInternalString())
            quad_key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                Type_Morton, lr, depth)
            self.assertEqual(lst[1], quad_key.toInternalString())
            quad_key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                Type_Morton, ur, depth)
            self.assertEqual(lst[1], quad_key.toInternalString())
            quad_key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                Type_Morton, ul, depth)
            self.assertEqual(lst[1], quad_key.toInternalString())
            actual = GeoCoordinateBoundingBox2d()
            quad_key.getGeoCoordinateBounds2d(actual)
            self.assertTrue(ll.near(actual.lowerLeft(), 1))
            self.assertTrue(ur.near(actual.upperRight(), 1))

    def test_get_keys_from_longitude_latitude_bounding_box(self):
        """
        Test to get the bounding box of a quadquad_quad_key.
        """
        tests = [
            (
                GeoCoordinateBoundingBox2d(
                    GeoCoordinate2d(Longitude(-180.0), Latitude(-90.0)),
                    GeoCoordinate2d(Longitude(-0.1), Latitude(+90.0))),
                [
                    QuadKey(Type_Morton, 0, 0, 0)
                ]
            ),
            (
                GeoCoordinateBoundingBox2d(
                    GeoCoordinate2d(Longitude(+0.0), Latitude(-90.0)),
                    GeoCoordinate2d(Longitude(+180.0), Latitude(+90.0))),
                [
                    QuadKey(Type_Morton, 0, 1, 0)
                ]
            ),
        ]

        for test in tests:
            actual = QuadKey.getKeysFromLongitudeLatitudeBoundingBox(
                Type_Morton, test[0], 0)
            self.assertEqual(len(test[1]), actual.size())
            for quad_key in test[1]:
                self.assertTrue(quad_key in actual)

        tests = (
            (
                GeoCoordinateBoundingBox2d(  # i = 0
                    GeoCoordinate2d(Longitude(-180.0), Latitude(-90.0)),
                    GeoCoordinate2d(Longitude(-0.1), Latitude(+90.0))),
                [
                    QuadKey(Type_Morton, 0, 0, 1), QuadKey(Type_Morton, 0, 1, 1),
                    QuadKey(Type_Morton, 1, 0, 1), QuadKey(Type_Morton, 1, 1, 1)
                ]
            ),
            (
                GeoCoordinateBoundingBox2d(  # i = 1
                    GeoCoordinate2d(Longitude(+0.0), Latitude(-90.0)),
                    GeoCoordinate2d(Longitude(+180.0), Latitude(+90.0))),
                [
                    QuadKey(Type_Morton, 0, 2, 1), QuadKey(Type_Morton, 0, 3, 1),
                    QuadKey(Type_Morton, 1, 2, 1), QuadKey(Type_Morton, 1, 3, 1),
                ]
            ),
            (
                GeoCoordinateBoundingBox2d(  # i = 2
                    GeoCoordinate2d(Longitude(-180.0), Latitude(-90.0)),
                    GeoCoordinate2d(Longitude(-0.1), Latitude(-0.1))),
                [
                    QuadKey(Type_Morton, 0, 0, 1), QuadKey(Type_Morton, 0, 1, 1),
                ]
            ),
            (
                GeoCoordinateBoundingBox2d(  # i = 3
                    GeoCoordinate2d(Longitude(-180.0), Latitude(+0.0)),
                    GeoCoordinate2d(Longitude(-0.1), Latitude(+90.0))),
                [
                    QuadKey(Type_Morton, 1, 0, 1), QuadKey(Type_Morton, 1, 1, 1),
                ]
            ),
            (
                GeoCoordinateBoundingBox2d(  # i = 4
                    GeoCoordinate2d(Longitude(+0.0), Latitude(-90.0)),
                    GeoCoordinate2d(Longitude(+180.0), Latitude(-0.1))),
                [
                    QuadKey(Type_Morton, 0, 2, 1), QuadKey(Type_Morton, 0, 3, 1),
                ]
            ),
            (
                GeoCoordinateBoundingBox2d(  # i = 5
                    GeoCoordinate2d(Longitude(+0.0), Latitude(+0.0)),
                    GeoCoordinate2d(Longitude(+180.0), Latitude(+90.0))),
                [
                    QuadKey(Type_Morton, 1, 2, 1), QuadKey(Type_Morton, 1, 3, 1),
                ]
            ),
            (
                GeoCoordinateBoundingBox2d(  # i = 6
                    GeoCoordinate2d(Longitude(-180.0), Latitude(-90.0)),
                    GeoCoordinate2d(Longitude(-90.1), Latitude(-0.1))),
                [
                    QuadKey(Type_Morton, 0, 0, 1),
                ]
            ),
            (
                GeoCoordinateBoundingBox2d(  # i = 7
                    GeoCoordinate2d(Longitude(-90.0), Latitude(-90.0)),
                    GeoCoordinate2d(Longitude(-0.1), Latitude(-0.1))),
                [
                    QuadKey(Type_Morton, 0, 1, 1),
                ]
            ),
            (
                GeoCoordinateBoundingBox2d(  # i = 8
                    GeoCoordinate2d(Longitude(+0.0), Latitude(-90.0)),
                    GeoCoordinate2d(Longitude(+90.0), Latitude(-0.1))),
                [
                    QuadKey(Type_Morton, 0, 2, 1),
                ]
            ),
            (
                GeoCoordinateBoundingBox2d(  # i = 9
                    GeoCoordinate2d(Longitude(+90.1), Latitude(-90.0)),
                    GeoCoordinate2d(Longitude(+180.0), Latitude(-0.1))),
                [
                    QuadKey(Type_Morton, 0, 3, 1),
                ]
            ),
            (
                GeoCoordinateBoundingBox2d(  # i = 10
                    GeoCoordinate2d(Longitude(-180.0), Latitude(+0.0)),
                    GeoCoordinate2d(Longitude(-90.1), Latitude(+90.0))),
                [
                    QuadKey(Type_Morton, 1, 0, 1),
                ]
            ),
            (
                GeoCoordinateBoundingBox2d(  # i = 11
                    GeoCoordinate2d(Longitude(-90.0), Latitude(+0.0)),
                    GeoCoordinate2d(Longitude(-0.1), Latitude(+90.0))),
                [
                    QuadKey(Type_Morton, 1, 1, 1),
                ]
            ),
            (
                GeoCoordinateBoundingBox2d(  # i = 12
                    GeoCoordinate2d(Longitude(+0.0), Latitude(+0.0)),
                    GeoCoordinate2d(Longitude(+90.0), Latitude(+90.0))),
                [
                    QuadKey(Type_Morton, 1, 2, 1),
                ]
            ),
            (
                GeoCoordinateBoundingBox2d(  # i = 13
                    GeoCoordinate2d(Longitude(+90.1), Latitude(+0.0)),
                    GeoCoordinate2d(Longitude(+180.0), Latitude(+90.0))),
                [
                    QuadKey(Type_Morton, 1, 3, 1),
                ]
            ),
        )

        for test in tests:
            actual = QuadKey.getKeysFromLongitudeLatitudeBoundingBox(
                Type_Morton, test[0], 1)
            self.assertEqual(len(test[1]), actual.size())
            for quad_key in test[1]:
                self.assertTrue(quad_key in actual)

        test = [
            GeoCoordinateBoundingBox2d(
                GeoCoordinate2d(Longitude(-140.0), Latitude(-48.0)),
                GeoCoordinate2d(Longitude(+10.0), Latitude(+39.0))),
            [
                QuadKey(Type_Morton, 0, 0, 2), QuadKey(Type_Morton, 0, 1, 2),
                QuadKey(Type_Morton, 0, 2, 2), QuadKey(Type_Morton, 0, 3, 2),
                QuadKey(Type_Morton, 0, 4, 2), QuadKey(Type_Morton, 1, 0, 2),
                QuadKey(Type_Morton, 1, 1, 2), QuadKey(Type_Morton, 1, 2, 2),
                QuadKey(Type_Morton, 1, 3, 2), QuadKey(Type_Morton, 1, 4, 2),
                QuadKey(Type_Morton, 2, 0, 2), QuadKey(Type_Morton, 2, 1, 2),
                QuadKey(Type_Morton, 2, 2, 2), QuadKey(Type_Morton, 2, 3, 2),
                QuadKey(Type_Morton, 2, 4, 2),
            ]]
        actual = QuadKey.getKeysFromLongitudeLatitudeBoundingBox(
            Type_Morton, test[0], 2)
        self.assertEqual(len(test[1]), actual.size())
        for quad_key in test[1]:
            self.assertTrue(quad_key in actual)

    def test_selected_cities(self):
        """
        Test a given set of known places make sure they work.
        """
        data = (13, GeoCoordinate2d(
            Longitude(+ 2.29450000000000),
            Latitude(+48.85822200000000)))
        tile = 8428778 | (1 << (data[0] + 16))
        quad_key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
            Type_Morton, data[1], data[0])
        self.assertEqual(str(tile), quad_key.toInternalString())

        data = (13, GeoCoordinate2d(
            Longitude(-74.04444400000000),
            Latitude(+40.68916700000000)))
        tile = 86924190 | (1 << (data[0] + 16))
        quad_key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
            Type_Morton, data[1], data[0])
        self.assertEqual(str(tile), quad_key.toInternalString())

        data = (13, GeoCoordinate2d(
            Longitude(-43.15744400000000),
            Latitude(-22.94865800000000)))
        tile = 130726287 | (1 << (data[0] + 16))
        quad_key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
            Type_Morton, data[1], data[0])
        self.assertEqual(str(tile), quad_key.toInternalString())

        data = (13, GeoCoordinate2d(
            Longitude(+151.21527800000000),
            Latitude(-33.85611100000000)))
        tile = 63372939 | (1 << (data[0] + 16))
        quad_key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
            Type_Morton, data[1], data[0])
        self.assertEqual(str(tile), quad_key.toInternalString())

        data = (13, GeoCoordinate2d(
            Longitude(+ 0.00000000000000),
            Latitude(+51.50300000000000)))
        tile = 8521770 | (1 << (data[0] + 16))
        quad_key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
            Type_Morton, data[1], data[0])
        self.assertEqual(str(tile), quad_key.toInternalString())

        data = (13, GeoCoordinate2d(
            Longitude(-78.45000000000000),
            Latitude(+0.00000000000000)))
        tile = 84148305 | (1 << (data[0] + 16))
        quad_key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
            Type_Morton, data[1], data[0])
        self.assertEqual(str(tile), quad_key.toInternalString())

        data = (10, GeoCoordinate2d(
            Longitude(+2.29450000000000),
            Latitude(+48.85822200000000)))
        tile = 131699 | (1 << (16 + data[0]))
        quad_key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
            Type_Morton, data[1], data[0])
        self.assertEqual(str(tile), quad_key.toInternalString())

        data = (10, GeoCoordinate2d(
            Longitude(-74.04444400000000),
            Latitude(+40.68916700000000)))
        tile = 1358190 | (1 << (16 + data[0]))
        quad_key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
            Type_Morton, data[1], data[0])
        self.assertEqual(str(tile), quad_key.toInternalString())

        data = (10, GeoCoordinate2d(
            Longitude(-43.15744400000000),
            Latitude(-22.94865800000000)))
        tile = 2042598 | (1 << (16 + data[0]))
        quad_key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
            Type_Morton, data[1], data[0])
        self.assertEqual(str(tile), quad_key.toInternalString())

        data = (10, GeoCoordinate2d(
            Longitude(+151.21527800000000),
            Latitude(-33.85611100000000)))
        tile = 990202 | (1 << (16 + data[0]))
        quad_key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
            Type_Morton, data[1], data[0])
        self.assertEqual(str(tile), quad_key.toInternalString())

        data = (10, GeoCoordinate2d(
            Longitude(+ 0.00000000000000),
            Latitude(+51.50300000000000)))
        tile = 133152 | (1 << (16 + data[0]))
        quad_key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
            Type_Morton, data[1], data[0])
        self.assertEqual(str(tile), quad_key.toInternalString())

        data = (10, GeoCoordinate2d(
            Longitude(-78.45000000000000),
            Latitude(+0.00000000000000)))
        tile = 1314817 | (1 << (16 + data[0]))
        quad_key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
            Type_Morton, data[1], data[0])
        self.assertEqual(str(tile), quad_key.toInternalString())


def main():
    """
    Bootstrap function for this module
    """
    suite = unittest.TestLoader().loadTestsFromTestCase(TestMortonSystem)
    unittest.TextTestRunner(verbosity=2).run(suite)

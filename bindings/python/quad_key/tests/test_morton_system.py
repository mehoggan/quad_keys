"""
Unit Tests for morton System
"""

from __future__ import print_function
import unittest
from quad_key.quad_key import quad_key
from quad_key.quad_key import type_morton
from quad_key.quad_key import geo_coordinate2d
from quad_key.quad_key import geo_coordinate_bounding_box2d
from quad_key.quad_key import longitude
from quad_key.quad_key import latitude


class TestMortonSystem(unittest.TestCase):
    """Class for running unit tests."""

    def test_is_valid(self):
        """See Testquad_key.test_is_valid."""
        # Same as bing_system

    def test_is_root_key(self):
        """See Testquad_key.test_is_root_key."""
        # Same as bing_system

    def test_get_parent(self):
        """Test to get parent of a generically formatted quad_quad_key."""
        # Same as bing_system

    def test_is_my_ancestor(self):
        """Checks to see if specified quad_key up in the hierarchy is an
        "ancestor" of the given quad_quad_key."""
        # Same as bing_system

    def test_get_ancestor(self):
        """Gets the ancestor up the tree according to a delta provided."""
        qk = quad_key(type_morton, 0, 1, 1)
        ancestor = quad_key(type_morton, 0, 0, 0)
        self.assertEqual(ancestor, qk.get_ancestor(1))
        self.assertEqual(qk.get_parent(), qk.get_ancestor(1))

        qk = quad_key(type_morton, 0, 0, 1)
        ancestor = quad_key(type_morton, 0, 0, 0)
        self.assertEqual(ancestor, qk.get_ancestor(1))
        self.assertEqual(qk.get_parent(), qk.get_ancestor(1))

        qk = quad_key(type_morton, 1, 1, 1)
        ancestor = quad_key(type_morton, 0, 0, 0)
        self.assertEqual(ancestor, qk.get_ancestor(1))

        qk = quad_key(type_morton, 1, 2, 1)
        ancestor = quad_key(type_morton, 0, 1, 0)
        self.assertEqual(ancestor, qk.get_ancestor(1))

        qk = quad_key(type_morton, 0, 3, 1)
        ancestor = quad_key(type_morton, 0, 1, 0)
        self.assertEqual(ancestor, qk.get_ancestor(1))

    def test_get_child(self):
        """Get a single child NE, SE, NW, SW."""
        # Same as bing_system

    def test_get_children(self):
        """Get all the childern of a quad_key."""
        # Same as bing_system

    def test_get_descendants(self):
        """Get all the defendants at some delta in the tree."""
        # Same as bing_system

    def test_get_siblings(self):
        """Test to get siblings of a given quad_key."""
        quad_keys = quad_key(type_morton, 0, 0, 1).get_siblings()
        self.assertEqual(3, quad_keys.size())
        self.assertTrue(quad_key(type_morton, 1, 0, 1) in quad_keys)
        self.assertTrue(quad_key(type_morton, 1, 1, 1) in quad_keys)
        self.assertTrue(quad_key(type_morton, 0, 1, 1) in quad_keys)
        quad_keys = quad_key(type_morton, 1, 3, 1).get_siblings()
        self.assertEqual(3, quad_keys.size())
        self.assertTrue(quad_key(type_morton, 1, 2, 1) in quad_keys)
        self.assertTrue(quad_key(type_morton, 0, 2, 1) in quad_keys)
        self.assertTrue(quad_key(type_morton, 0, 3, 1) in quad_keys)

    def test_get_neighbors(self):
        """Test to get the neighbors of a given quadquad_quad_key."""
        # Same as bing_system but just to be safe
        quad_keys = quad_key().get_neighbors()
        self.assertTrue(quad_keys.empty())

        quad_keys = quad_key(type_morton, 0, 0, 2).get_neighbors()
        self.assertEqual(5, quad_keys.size())
        self.assertTrue(quad_key(type_morton, 0, 1, 2) in quad_keys)
        self.assertTrue(quad_key(type_morton, 1, 1, 2) in quad_keys)
        self.assertTrue(quad_key(type_morton, 1, 0, 2) in quad_keys)
        self.assertTrue(quad_key(type_morton, 0, 7, 2) in quad_keys)
        self.assertTrue(quad_key(type_morton, 1, 7, 2) in quad_keys)

        quad_keys = quad_key(type_morton, 0, 1, 2).get_neighbors()
        self.assertEqual(5, quad_keys.size())
        self.assertTrue(quad_key(type_morton, 0, 0, 2) in quad_keys)
        self.assertTrue(quad_key(type_morton, 1, 0, 2) in quad_keys)
        self.assertTrue(quad_key(type_morton, 1, 1, 2) in quad_keys)
        self.assertTrue(quad_key(type_morton, 1, 2, 2) in quad_keys)
        self.assertTrue(quad_key(type_morton, 0, 2, 2) in quad_keys)

        quad_keys = quad_key(type_morton, 0, 2, 2).get_neighbors()
        self.assertEqual(5, quad_keys.size())
        self.assertTrue(quad_key(type_morton, 0, 1, 2) in quad_keys)
        self.assertTrue(quad_key(type_morton, 1, 1, 2) in quad_keys)
        self.assertTrue(quad_key(type_morton, 1, 2, 2) in quad_keys)
        self.assertTrue(quad_key(type_morton, 1, 3, 2) in quad_keys)
        self.assertTrue(quad_key(type_morton, 0, 3, 2) in quad_keys)

        quad_keys = quad_key(type_morton, 0, 3, 2).get_neighbors()
        self.assertEqual(5, quad_keys.size())
        self.assertTrue(quad_key(type_morton, 0, 2, 2) in quad_keys)
        self.assertTrue(quad_key(type_morton, 1, 2, 2) in quad_keys)
        self.assertTrue(quad_key(type_morton, 1, 3, 2) in quad_keys)
        self.assertTrue(quad_key(type_morton, 1, 4, 2) in quad_keys)
        self.assertTrue(quad_key(type_morton, 0, 4, 2) in quad_keys)

        quad_keys = quad_key(type_morton, 0, 0, 2).get_neighbors()
        self.assertEqual(5, quad_keys.size())
        self.assertTrue(quad_key(type_morton, 0, 1, 2) in quad_keys)
        self.assertTrue(quad_key(type_morton, 1, 1, 2) in quad_keys)
        self.assertTrue(quad_key(type_morton, 1, 0, 2) in quad_keys)
        self.assertTrue(quad_key(type_morton, 1, 7, 2) in quad_keys)
        self.assertTrue(quad_key(type_morton, 0, 7, 2) in quad_keys)

        quad_keys = quad_key(type_morton, 3, 1, 2).get_neighbors()
        self.assertEqual(5, quad_keys.size())
        self.assertTrue(quad_key(type_morton, 3, 0, 2) in quad_keys)
        self.assertTrue(quad_key(type_morton, 2, 0, 2) in quad_keys)
        self.assertTrue(quad_key(type_morton, 2, 1, 2) in quad_keys)
        self.assertTrue(quad_key(type_morton, 2, 2, 2) in quad_keys)
        self.assertTrue(quad_key(type_morton, 3, 2, 2) in quad_keys)

        quad_keys = quad_key(type_morton, 3, 2, 2).get_neighbors()
        self.assertEqual(5, quad_keys.size())
        self.assertTrue(quad_key(type_morton, 3, 1, 2) in quad_keys)
        self.assertTrue(quad_key(type_morton, 2, 1, 2) in quad_keys)
        self.assertTrue(quad_key(type_morton, 2, 2, 2) in quad_keys)
        self.assertTrue(quad_key(type_morton, 2, 3, 2) in quad_keys)
        self.assertTrue(quad_key(type_morton, 3, 3, 2) in quad_keys)

        quad_keys = quad_key(type_morton, 3, 3, 2).get_neighbors()
        self.assertEqual(5, quad_keys.size())
        self.assertTrue(quad_key(type_morton, 3, 2, 2) in quad_keys)
        self.assertTrue(quad_key(type_morton, 2, 2, 2) in quad_keys)
        self.assertTrue(quad_key(type_morton, 2, 3, 2) in quad_keys)
        self.assertTrue(quad_key(type_morton, 2, 4, 2) in quad_keys)
        self.assertTrue(quad_key(type_morton, 3, 4, 2) in quad_keys)

        quad_keys = quad_key(type_morton, 4, 7, 3).get_neighbors()
        self.assertEqual(8, quad_keys.size())
        self.assertTrue(quad_key(type_morton, 3, 7, 3) in quad_keys)
        self.assertTrue(quad_key(type_morton, 3, 6, 3) in quad_keys)
        self.assertTrue(quad_key(type_morton, 4, 6, 3) in quad_keys)
        self.assertTrue(quad_key(type_morton, 5, 6, 3) in quad_keys)
        self.assertTrue(quad_key(type_morton, 5, 7, 3) in quad_keys)
        self.assertTrue(quad_key(type_morton, 5, 8, 3) in quad_keys)
        self.assertTrue(quad_key(type_morton, 4, 8, 3) in quad_keys)
        self.assertTrue(quad_key(type_morton, 3, 8, 3) in quad_keys)

        quad_keys = quad_key(type_morton, 4, 0, 3).get_neighbors()
        self.assertEqual(8, quad_keys.size())
        self.assertTrue(quad_key(type_morton, 3, 0, 3) in quad_keys)
        self.assertTrue(quad_key(type_morton, 3, 1, 3) in quad_keys)
        self.assertTrue(quad_key(type_morton, 4, 1, 3) in quad_keys)
        self.assertTrue(quad_key(type_morton, 5, 1, 3) in quad_keys)
        self.assertTrue(quad_key(type_morton, 5, 0, 3) in quad_keys)
        self.assertTrue(quad_key(type_morton, 5, 15, 3) in quad_keys)
        self.assertTrue(quad_key(type_morton, 4, 15, 3) in quad_keys)
        self.assertTrue(quad_key(type_morton, 3, 15, 3) in quad_keys)

        quad_keys = quad_key(type_morton, 0, 0, 0).get_neighbors()
        self.assertEqual(0, quad_keys.size())

    def test_to_string_from_string(self):
        """Test to convert an internally formatted string and back."""
        # X ==> Unused
        # O ==> Used but never set
        # (0,1) ==> Binary digits
        qk = quad_key(type_morton, 0, 0, 0)
        fmt = qk.to_internal_string()
        self.assertEqual("65537",
                         fmt)  # ... XXXX XXXX XXX1 XXXX XXXX XXXX XXO1
        quad_key_back = quad_key.from_internal_string(type_morton, fmt)
        self.assertEqual(qk, quad_key_back)

        qk = quad_key(type_morton, 0, 1, 0)
        fmt = qk.to_internal_string()
        self.assertEqual("65536",
                         fmt)  # ... XXXX XXXX XXX1 XXXX XXXX XXXX XXO0
        quad_key_back = quad_key.from_internal_string(type_morton, fmt)
        self.assertEqual(qk, quad_key_back)

        qk = quad_key(type_morton, 0, 0, 1)
        fmt = qk.to_internal_string()
        self.assertEqual("131078",
                         fmt)  # ... XXXX XXXX XX1X XXXX XXXX XXXX O110
        quad_key_back = quad_key.from_internal_string(type_morton, fmt)
        self.assertEqual(qk, quad_key_back)

        qk = quad_key(type_morton, 0, 1, 1)
        fmt = qk.to_internal_string()
        self.assertEqual("131079",
                         fmt)  # ... XXXX XXXX XX1O OOOO OOOO OOOO O111
        quad_key_back = quad_key.from_internal_string(type_morton, fmt)
        self.assertEqual(qk, quad_key_back)

        qk = quad_key(type_morton, 0, 2, 1)
        fmt = qk.to_internal_string()
        self.assertEqual("131074",
                         fmt)  # ... XXXX XXXX XX1X XXXX XXXX XXXX O010
        quad_key_back = quad_key.from_internal_string(type_morton, fmt)
        self.assertEqual(qk, quad_key_back)

        qk = quad_key(type_morton, 0, 3, 1)
        fmt = qk.to_internal_string()
        self.assertEqual("131075",
                         fmt)  # ... XXXX XXXX XX1X XXXX XXXX XXXX O011
        quad_key_back = quad_key.from_internal_string(type_morton, fmt)
        self.assertEqual(qk, quad_key_back)

        qk = quad_key(type_morton, 1, 0, 1)
        fmt = qk.to_internal_string()
        self.assertEqual("131076",
                         fmt)  # ... XXXX XXXX XX1X XXXX XXXX XXXX O100
        quad_key_back = quad_key.from_internal_string(type_morton, fmt)
        self.assertEqual(qk, quad_key_back)

        qk = quad_key(type_morton, 1, 1, 1)
        fmt = qk.to_internal_string()
        self.assertEqual("131077",
                         fmt)  # ... XXXX XXXX XX1X XXXX XXXX XXXX O101
        quad_key_back = quad_key.from_internal_string(type_morton, fmt)
        self.assertEqual(qk, quad_key_back)

        qk = quad_key(type_morton, 1, 2, 1)
        fmt = qk.to_internal_string()
        self.assertEqual("131072",
                         fmt)  # ... XXXX XXXX XX1X XXXX XXXX XXXX O000
        quad_key_back = quad_key.from_internal_string(type_morton, fmt)
        self.assertEqual(qk, quad_key_back)

        qk = quad_key(type_morton, 1, 3, 1)
        fmt = qk.to_internal_string()
        self.assertEqual("131073",
                         fmt)  # ... XXXX XXXX XX1X XXXX XXXX XXXX O001
        quad_key_back = quad_key.from_internal_string(type_morton, fmt)
        self.assertEqual(qk, quad_key_back)

        qk = quad_key(type_morton, 0, 0, 2)
        fmt = qk.to_internal_string()
        self.assertEqual("262168",
                         fmt)  # ... XXXX XXXX X1XX XXXX XXXX XXO1 1000
        quad_key_back = quad_key.from_internal_string(type_morton, fmt)
        self.assertEqual(qk, quad_key_back)

        qk = quad_key(type_morton, 0, 1, 2)
        fmt = qk.to_internal_string()
        self.assertEqual("262169",
                         fmt)  # ... XXXX XXXX X1XX XXXX XXXX XXO1 1001
        quad_key_back = quad_key.from_internal_string(type_morton, fmt)
        self.assertEqual(qk, quad_key_back)

        qk = quad_key(type_morton, 0, 2, 2)
        fmt = qk.to_internal_string()
        self.assertEqual("262172",
                         fmt)  # ... XXXX XXXX X1XX XXXX XXXX XXO1 1100
        quad_key_back = quad_key.from_internal_string(type_morton, fmt)
        self.assertEqual(qk, quad_key_back)

        qk = quad_key(type_morton, 0, 3, 2)
        fmt = qk.to_internal_string()
        self.assertEqual("262173",
                         fmt)  # ... XXXX XXXX X1XX XXXX XXXX XXO1 1101
        quad_key_back = quad_key.from_internal_string(type_morton, fmt)
        self.assertEqual(qk, quad_key_back)

        qk = quad_key(type_morton, 0, 4, 2)
        fmt = qk.to_internal_string()
        self.assertEqual("262152",
                         fmt)  # ... XXXX XXXX X1XX XXXX XXXX XXO0 1000
        quad_key_back = quad_key.from_internal_string(type_morton, fmt)
        self.assertEqual(qk, quad_key_back)

        qk = quad_key(type_morton, 0, 5, 2)
        fmt = qk.to_internal_string()
        self.assertEqual("262153",
                         fmt)  # ... XXXX XXXX X1XX XXXX XXXX XXO0 1001
        quad_key_back = quad_key.from_internal_string(type_morton, fmt)
        self.assertEqual(qk, quad_key_back)

        qk = quad_key(type_morton, 0, 6, 2)
        fmt = qk.to_internal_string()
        self.assertEqual("262156",
                         fmt)  # ... XXXX XXXX X1XX XXXX XXXX XXO0 1100
        quad_key_back = quad_key.from_internal_string(type_morton, fmt)
        self.assertEqual(qk, quad_key_back)

        qk = quad_key(type_morton, 0, 7, 2)
        fmt = qk.to_internal_string()
        self.assertEqual("262157",
                         fmt)  # ... XXXX XXXX X1XX XXXX XXXX XXO0 1101
        quad_key_back = quad_key.from_internal_string(type_morton, fmt)
        self.assertEqual(qk, quad_key_back)

        qk = quad_key(type_morton, 1, 0, 2)
        fmt = qk.to_internal_string()
        self.assertEqual("262170",
                         fmt)  # ... XXXX XXXX X1XX XXXX XXXX XXO1 1010
        quad_key_back = quad_key.from_internal_string(type_morton, fmt)
        self.assertEqual(qk, quad_key_back)

        qk = quad_key(type_morton, 1, 1, 2)
        fmt = qk.to_internal_string()
        self.assertEqual("262171",
                         fmt)  # ... XXXX XXXX X1XX XXXX XXXX XXO1 1011
        quad_key_back = quad_key.from_internal_string(type_morton, fmt)
        self.assertEqual(qk, quad_key_back)

        qk = quad_key(type_morton, 1, 2, 2)
        fmt = qk.to_internal_string()
        self.assertEqual("262174",
                         fmt)  # ... XXXX XXXX X1XX XXXX XXXX XXO1 1110
        quad_key_back = quad_key.from_internal_string(type_morton, fmt)
        self.assertEqual(qk, quad_key_back)

        qk = quad_key(type_morton, 1, 3, 2)
        fmt = qk.to_internal_string()
        self.assertEqual("262175",
                         fmt)  # ... XXXX XXXX X1XX XXXX XXXX XXO1 1111
        quad_key_back = quad_key.from_internal_string(type_morton, fmt)
        self.assertEqual(qk, quad_key_back)

        qk = quad_key(type_morton, 1, 4, 2)
        fmt = qk.to_internal_string()
        self.assertEqual("262154",
                         fmt)  # ... XXXX XXXX X1XX XXXX XXXX XXO0 1010
        quad_key_back = quad_key.from_internal_string(type_morton, fmt)
        self.assertEqual(qk, quad_key_back)

        qk = quad_key(type_morton, 1, 5, 2)
        fmt = qk.to_internal_string()
        self.assertEqual("262155",
                         fmt)  # ... XXXX XXXX X1XX XXXX XXXX XXO0 1011
        quad_key_back = quad_key.from_internal_string(type_morton, fmt)
        self.assertEqual(qk, quad_key_back)

        qk = quad_key(type_morton, 1, 6, 2)
        fmt = qk.to_internal_string()
        self.assertEqual("262158",
                         fmt)  # ... XXXX XXXX X1XX XXXX XXXX XXO0 1110
        quad_key_back = quad_key.from_internal_string(type_morton, fmt)
        self.assertEqual(qk, quad_key_back)

        qk = quad_key(type_morton, 1, 7, 2)
        fmt = qk.to_internal_string()
        self.assertEqual("262159",
                         fmt)  # ... XXXX XXXX X1XX XXXX XXXX XXO0 1111
        quad_key_back = quad_key.from_internal_string(type_morton, fmt)
        self.assertEqual(qk, quad_key_back)

        qk = quad_key(type_morton, 2, 0, 2)
        fmt = qk.to_internal_string()
        self.assertEqual("262160",
                         fmt)  # ... XXXX XXXX X1XX XXXX XXXX XXO1 0000
        quad_key_back = quad_key.from_internal_string(type_morton, fmt)
        self.assertEqual(qk, quad_key_back)

        qk = quad_key(type_morton, 2, 1, 2)
        fmt = qk.to_internal_string()
        self.assertEqual("262161",
                         fmt)  # ... XXXX XXXX X1XX XXXX XXXX XXO1 0001
        quad_key_back = quad_key.from_internal_string(type_morton, fmt)
        self.assertEqual(qk, quad_key_back)

        qk = quad_key(type_morton, 2, 2, 2)
        fmt = qk.to_internal_string()
        self.assertEqual("262164",
                         fmt)  # ... XXXX XXXX X1XX XXXX XXXX XXO1 0100
        quad_key_back = quad_key.from_internal_string(type_morton, fmt)
        self.assertEqual(qk, quad_key_back)

        qk = quad_key(type_morton, 2, 3, 2)
        fmt = qk.to_internal_string()
        self.assertEqual("262165",
                         fmt)  # ... XXXX XXXX X1XX XXXX XXXX XXO1 0101
        quad_key_back = quad_key.from_internal_string(type_morton, fmt)
        self.assertEqual(qk, quad_key_back)

        qk = quad_key(type_morton, 2, 4, 2)
        fmt = qk.to_internal_string()
        self.assertEqual("262144",
                         fmt)  # ... XXXX XXXX X1XX XXXX XXXX XXO0 0000
        quad_key_back = quad_key.from_internal_string(type_morton, fmt)
        self.assertEqual(qk, quad_key_back)

        qk = quad_key(type_morton, 2, 5, 2)
        fmt = qk.to_internal_string()
        self.assertEqual("262145",
                         fmt)  # ... XXXX XXXX X1XX XXXX XXXX XXO0 0001
        quad_key_back = quad_key.from_internal_string(type_morton, fmt)
        self.assertEqual(qk, quad_key_back)

        qk = quad_key(type_morton, 2, 6, 2)
        fmt = qk.to_internal_string()
        self.assertEqual("262148",
                         fmt)  # ... XXXX XXXX X1XX XXXX XXXX XXO0 0100
        quad_key_back = quad_key.from_internal_string(type_morton, fmt)
        self.assertEqual(qk, quad_key_back)

        qk = quad_key(type_morton, 2, 7, 2)
        fmt = qk.to_internal_string()
        self.assertEqual("262149",
                         fmt)  # ... XXXX XXXX X1XX XXXX XXXX XXO0 0101
        quad_key_back = quad_key.from_internal_string(type_morton, fmt)
        self.assertEqual(qk, quad_key_back)

        qk = quad_key(type_morton, 3, 0, 2)
        fmt = qk.to_internal_string()
        self.assertEqual("262162",
                         fmt)  # ... XXXX XXXX X1XX XXXX XXXX XXO1 0010
        quad_key_back = quad_key.from_internal_string(type_morton, fmt)
        self.assertEqual(qk, quad_key_back)

        qk = quad_key(type_morton, 3, 1, 2)
        fmt = qk.to_internal_string()
        self.assertEqual("262163",
                         fmt)  # ... XXXX XXXX X1XX XXXX XXXX XXO1 0011
        quad_key_back = quad_key.from_internal_string(type_morton, fmt)
        self.assertEqual(qk, quad_key_back)

        qk = quad_key(type_morton, 3, 2, 2)
        fmt = qk.to_internal_string()
        self.assertEqual("262166",
                         fmt)  # ... XXXX XXXX X1XX XXXX XXXX XXO1 0110
        quad_key_back = quad_key.from_internal_string(type_morton, fmt)
        self.assertEqual(qk, quad_key_back)

        qk = quad_key(type_morton, 3, 3, 2)
        fmt = qk.to_internal_string()
        self.assertEqual("262167",
                         fmt)  # ... XXXX XXXX X1XX XXXX XXXX XXO1 0111
        quad_key_back = quad_key.from_internal_string(type_morton, fmt)
        self.assertEqual(qk, quad_key_back)

        qk = quad_key(type_morton, 3, 4, 2)
        fmt = qk.to_internal_string()
        self.assertEqual("262146",
                         fmt)  # ... XXXX XXXX X1XX XXXX XXXX XXO0 0010
        quad_key_back = quad_key.from_internal_string(type_morton, fmt)
        self.assertEqual(qk, quad_key_back)

        qk = quad_key(type_morton, 3, 5, 2)
        fmt = qk.to_internal_string()
        self.assertEqual("262147",
                         fmt)  # ... XXXX XXXX X1XX XXXX XXXX XXO0 0011
        quad_key_back = quad_key.from_internal_string(type_morton, fmt)
        self.assertEqual(qk, quad_key_back)

        qk = quad_key(type_morton, 3, 6, 2)
        fmt = qk.to_internal_string()
        self.assertEqual("262150",
                         fmt)  # ... XXXX XXXX X1XX XXXX XXXX XXO0 0110
        quad_key_back = quad_key.from_internal_string(type_morton, fmt)
        self.assertEqual(qk, quad_key_back)

        qk = quad_key(type_morton, 3, 7, 2)
        fmt = qk.to_internal_string()
        self.assertEqual("262151",
                         fmt)  # ... XXXX XXXX X1XX XXXX XXXX XXO0 0111
        quad_key_back = quad_key.from_internal_string(type_morton, fmt)
        self.assertEqual(qk, quad_key_back)

    def test_get_geo_coordinate_bounds_2d(self):
        """Test to get geographic bounds of quadquad_quad_key."""
        bbox = geo_coordinate_bounding_box2d()

        qk = quad_key(type_morton, 0, 0, 0)
        qk.get_geo_coordinate_bounds2d(bbox)
        self.assertTrue(bbox.lower_left().near(geo_coordinate2d(
            longitude(-180.0), latitude(-90.0)), 1e-4))
        self.assertTrue(bbox.upper_right().near(geo_coordinate2d(
            longitude(-0.1), latitude(+90.0)), 1e-4))

        qk = quad_key(type_morton, 0, 1, 0)
        qk.get_geo_coordinate_bounds2d(bbox)
        self.assertTrue(bbox.lower_left().near(geo_coordinate2d(
            longitude(+0.0), latitude(-90.0)), 1e-4))
        self.assertTrue(bbox.upper_right().near(geo_coordinate2d(
            longitude(+180.0), latitude(+90.0)), 1e-4))

        qk = quad_key(type_morton, 0, 0, 1)
        qk.get_geo_coordinate_bounds2d(bbox)
        self.assertTrue(bbox.lower_left().near(geo_coordinate2d(
            longitude(-180.0), latitude(-90.0)), 1e-4))
        self.assertTrue(bbox.upper_right().near(geo_coordinate2d(
            longitude(-90.0), latitude(+0.0)), 1e-4))

        qk = quad_key(type_morton, 0, 1, 1)
        qk.get_geo_coordinate_bounds2d(bbox)
        self.assertTrue(bbox.lower_left().near(geo_coordinate2d(
            longitude(-90.0), latitude(-90.0)), 1e-4))
        self.assertTrue(bbox.upper_right().near(geo_coordinate2d(
            longitude(+0.0), latitude(+0.0)), 1e-4))

        qk = quad_key(type_morton, 0, 2, 1)
        qk.get_geo_coordinate_bounds2d(bbox)
        self.assertTrue(bbox.lower_left().near(geo_coordinate2d(
            longitude(+0.0), latitude(-90.0)), 1e-4))
        self.assertTrue(bbox.upper_right().near(geo_coordinate2d(
            longitude(+90.0), latitude(+0.0)), 1e-4))

        qk = quad_key(type_morton, 0, 3, 1)
        qk.get_geo_coordinate_bounds2d(bbox)
        self.assertTrue(bbox.lower_left().near(geo_coordinate2d(
            longitude(+90.0), latitude(-90.0)), 1e-4))
        self.assertTrue(bbox.upper_right().near(geo_coordinate2d(
            longitude(+180.0), latitude(+0.0)), 1e-4))

        qk = quad_key(type_morton, 1, 0, 1)
        qk.get_geo_coordinate_bounds2d(bbox)
        self.assertTrue(bbox.lower_left().near(geo_coordinate2d(
            longitude(-180.0), latitude(+0.0)), 1e-4))
        self.assertTrue(bbox.upper_right().near(geo_coordinate2d(
            longitude(-90.0), latitude(+90.0)), 1e-4))

        qk = quad_key(type_morton, 1, 1, 1)
        qk.get_geo_coordinate_bounds2d(bbox)
        self.assertTrue(bbox.lower_left().near(geo_coordinate2d(
            longitude(-90.0), latitude(+0.0)), 1e-4))
        self.assertTrue(bbox.upper_right().near(geo_coordinate2d(
            longitude(+0.0), latitude(+90.0)), 1e-4))

        qk = quad_key(type_morton, 1, 2, 1)
        qk.get_geo_coordinate_bounds2d(bbox)
        self.assertTrue(bbox.lower_left().near(geo_coordinate2d(
            longitude(+0.0), latitude(+0.0)), 1e-4))
        self.assertTrue(bbox.upper_right().near(geo_coordinate2d(
            longitude(+90.0), latitude(+90.0)), 1e-4))

        qk = quad_key(type_morton, 1, 3, 1)
        qk.get_geo_coordinate_bounds2d(bbox)
        self.assertTrue(bbox.lower_left().near(geo_coordinate2d(
            longitude(+90.0), latitude(+0.0)), 1e-4))
        self.assertTrue(bbox.upper_right().near(geo_coordinate2d(
            longitude(+180.0), latitude(+90.0)), 1e-4))

    def test_get_key_from_longitude_latitude_at_depth_to_bounds(self):
        """Test to get a quad_key from longitude and latitude and then get
        bounds.
        """
        depth = 0

        coords = geo_coordinate2d(longitude(-0.1), latitude(0.0))
        qk = quad_key.get_key_from_longitude_latitude_at_depth(
            type_morton, coords, depth)
        self.assertEqual("65537", qk.to_internal_string())
        coords = geo_coordinate2d(longitude(-180.0), latitude(90.0))
        qk = quad_key.get_key_from_longitude_latitude_at_depth(
            type_morton, coords, depth)
        self.assertEqual("65537", qk.to_internal_string())
        coords = geo_coordinate2d(longitude(-180.0), latitude(-90.0))
        qk = quad_key.get_key_from_longitude_latitude_at_depth(
            type_morton, coords, depth)
        self.assertEqual("65537", qk.to_internal_string())
        actual = geo_coordinate_bounding_box2d()
        qk.get_geo_coordinate_bounds2d(actual)
        self.assertTrue(geo_coordinate2d(longitude(-180.0),
                                         latitude(-90.0)).near(
            actual.lower_left(), 1))
        self.assertTrue(geo_coordinate2d(longitude(-0.1),
                                         latitude(+90.0)).near(
            actual.upper_right(), 1))

        coords = geo_coordinate2d(longitude(0.0), latitude(0.0))
        qk = quad_key.get_key_from_longitude_latitude_at_depth(
            type_morton, coords, depth)
        self.assertEqual("65536", qk.to_internal_string())
        coords = geo_coordinate2d(longitude(180.0), latitude(-90.0))
        qk = quad_key.get_key_from_longitude_latitude_at_depth(
            type_morton, coords, depth)
        self.assertEqual("65536", qk.to_internal_string())
        coords = geo_coordinate2d(longitude(180.0), latitude(90.0))
        qk = quad_key.get_key_from_longitude_latitude_at_depth(
            type_morton, coords, depth)
        self.assertEqual("65536", qk.to_internal_string())
        actual = geo_coordinate_bounding_box2d()
        qk.get_geo_coordinate_bounds2d(actual)
        self.assertTrue(geo_coordinate2d(longitude(+0.0),
                                         latitude(-90.0)).near(
            actual.lower_left(), 1))
        self.assertTrue(geo_coordinate2d(longitude(+180.0),
                                         latitude(+90.0)).near(
            actual.upper_right(), 1))

        depth = 1

        coords = geo_coordinate2d(longitude(-180.0), latitude(-0.1))
        qk = quad_key.get_key_from_longitude_latitude_at_depth(
            type_morton, coords, depth)
        self.assertEqual("131078", qk.to_internal_string())
        coords = geo_coordinate2d(longitude(-180.0), latitude(-90.0))
        qk = quad_key.get_key_from_longitude_latitude_at_depth(
            type_morton, coords, depth)
        self.assertEqual("131078", qk.to_internal_string())
        coords = geo_coordinate2d(longitude(-90.1), latitude(-90.0))
        qk = quad_key.get_key_from_longitude_latitude_at_depth(
            type_morton, coords, depth)
        self.assertEqual("131078", qk.to_internal_string())
        coords = geo_coordinate2d(longitude(-90.1), latitude(-0.1))
        qk = quad_key.get_key_from_longitude_latitude_at_depth(
            type_morton, coords, depth)
        self.assertEqual("131078", qk.to_internal_string())

        coords = geo_coordinate2d(longitude(-90.0), latitude(-0.1))
        qk = quad_key.get_key_from_longitude_latitude_at_depth(
            type_morton, coords, depth)
        self.assertEqual("131079", qk.to_internal_string())
        coords = geo_coordinate2d(longitude(-90.0), latitude(-90.0))
        qk = quad_key.get_key_from_longitude_latitude_at_depth(
            type_morton, coords, depth)
        self.assertEqual("131079", qk.to_internal_string())
        coords = geo_coordinate2d(longitude(-0.1), latitude(-90.0))
        qk = quad_key.get_key_from_longitude_latitude_at_depth(
            type_morton, coords, depth)
        self.assertEqual("131079", qk.to_internal_string())
        coords = geo_coordinate2d(longitude(-0.1), latitude(-0.1))
        qk = quad_key.get_key_from_longitude_latitude_at_depth(
            type_morton, coords, depth)
        self.assertEqual("131079", qk.to_internal_string())

        coords = geo_coordinate2d(longitude(0.0), latitude(-0.1))
        qk = quad_key.get_key_from_longitude_latitude_at_depth(
            type_morton, coords, depth)
        self.assertEqual("131074", qk.to_internal_string())
        coords = geo_coordinate2d(longitude(0.0), latitude(-90.0))
        qk = quad_key.get_key_from_longitude_latitude_at_depth(
            type_morton, coords, depth)
        self.assertEqual("131074", qk.to_internal_string())
        coords = geo_coordinate2d(longitude(90.0), latitude(-90.0))
        qk = quad_key.get_key_from_longitude_latitude_at_depth(
            type_morton, coords, depth)
        self.assertEqual("131074", qk.to_internal_string())
        coords = geo_coordinate2d(longitude(90.0), latitude(-0.1))
        qk = quad_key.get_key_from_longitude_latitude_at_depth(
            type_morton, coords, depth)
        self.assertEqual("131074", qk.to_internal_string())

        coords = geo_coordinate2d(longitude(90.1), latitude(-0.1))
        qk = quad_key.get_key_from_longitude_latitude_at_depth(
            type_morton, coords, depth)
        self.assertEqual("131075", qk.to_internal_string())
        coords = geo_coordinate2d(longitude(90.1), latitude(-90.0))
        qk = quad_key.get_key_from_longitude_latitude_at_depth(
            type_morton, coords, depth)
        self.assertEqual("131075", qk.to_internal_string())
        coords = geo_coordinate2d(longitude(180.0), latitude(-90.0))
        qk = quad_key.get_key_from_longitude_latitude_at_depth(
            type_morton, coords, depth)
        self.assertEqual("131075", qk.to_internal_string())
        coords = geo_coordinate2d(longitude(180.0), latitude(-0.1))
        qk = quad_key.get_key_from_longitude_latitude_at_depth(
            type_morton, coords, depth)
        self.assertEqual("131075", qk.to_internal_string())

        coords = geo_coordinate2d(longitude(-180.0), latitude(90.0))
        qk = quad_key.get_key_from_longitude_latitude_at_depth(
            type_morton, coords, depth)
        self.assertEqual("131076", qk.to_internal_string())
        coords = geo_coordinate2d(longitude(-180.0), latitude(0.0))
        qk = quad_key.get_key_from_longitude_latitude_at_depth(
            type_morton, coords, depth)
        self.assertEqual("131076", qk.to_internal_string())
        coords = geo_coordinate2d(longitude(-90.1), latitude(0.0))
        qk = quad_key.get_key_from_longitude_latitude_at_depth(
            type_morton, coords, depth)
        self.assertEqual("131076", qk.to_internal_string())
        coords = geo_coordinate2d(longitude(-90.1), latitude(90.0))
        qk = quad_key.get_key_from_longitude_latitude_at_depth(
            type_morton, coords, depth)
        self.assertEqual("131076", qk.to_internal_string())

        coords = geo_coordinate2d(longitude(-90.0), latitude(90.0))
        qk = quad_key.get_key_from_longitude_latitude_at_depth(
            type_morton, coords, depth)
        self.assertEqual("131077", qk.to_internal_string())
        coords = geo_coordinate2d(longitude(-90.0), latitude(0.0))
        qk = quad_key.get_key_from_longitude_latitude_at_depth(
            type_morton, coords, depth)
        self.assertEqual("131077", qk.to_internal_string())
        coords = geo_coordinate2d(longitude(-0.1), latitude(0.0))
        qk = quad_key.get_key_from_longitude_latitude_at_depth(
            type_morton, coords, depth)
        self.assertEqual("131077", qk.to_internal_string())
        coords = geo_coordinate2d(longitude(-0.1), latitude(90.0))
        qk = quad_key.get_key_from_longitude_latitude_at_depth(
            type_morton, coords, depth)
        self.assertEqual("131077", qk.to_internal_string())

        coords = geo_coordinate2d(longitude(0.0), latitude(90.0))
        qk = quad_key.get_key_from_longitude_latitude_at_depth(
            type_morton, coords, depth)
        self.assertEqual("131072", qk.to_internal_string())
        coords = geo_coordinate2d(longitude(0.0), latitude(0.0))
        qk = quad_key.get_key_from_longitude_latitude_at_depth(
            type_morton, coords, depth)
        self.assertEqual("131072", qk.to_internal_string())
        coords = geo_coordinate2d(longitude(90.0), latitude(0.0))
        qk = quad_key.get_key_from_longitude_latitude_at_depth(
            type_morton, coords, depth)
        self.assertEqual("131072", qk.to_internal_string())
        coords = geo_coordinate2d(longitude(90.0), latitude(90.0))
        qk = quad_key.get_key_from_longitude_latitude_at_depth(
            type_morton, coords, depth)
        self.assertEqual("131072", qk.to_internal_string())

        coords = geo_coordinate2d(longitude(90.1), latitude(90.0))
        qk = quad_key.get_key_from_longitude_latitude_at_depth(
            type_morton, coords, depth)
        self.assertEqual("131073", qk.to_internal_string())
        coords = geo_coordinate2d(longitude(90.1), latitude(0.0))
        qk = quad_key.get_key_from_longitude_latitude_at_depth(
            type_morton, coords, depth)
        self.assertEqual("131073", qk.to_internal_string())
        coords = geo_coordinate2d(longitude(180.0), latitude(0.0))
        qk = quad_key.get_key_from_longitude_latitude_at_depth(
            type_morton, coords, depth)
        self.assertEqual("131073", qk.to_internal_string())
        coords = geo_coordinate2d(longitude(180.0), latitude(90.0))
        qk = quad_key.get_key_from_longitude_latitude_at_depth(
            type_morton, coords, depth)
        self.assertEqual("131073", qk.to_internal_string())

        tests = [
            [geo_coordinate_bounding_box2d(
                geo_coordinate2d(longitude(-180.0), latitude(-90.0)),
                geo_coordinate2d(longitude(-135.1), latitude(-45.1))),
                "262168"],
            [geo_coordinate_bounding_box2d(
                geo_coordinate2d(longitude(-135.0), latitude(-90.0)),
                geo_coordinate2d(longitude(-90.1), latitude(-45.1))),
                "262169"],
            [geo_coordinate_bounding_box2d(
                geo_coordinate2d(longitude(-90.0), latitude(-90.0)),
                geo_coordinate2d(longitude(-45.1), latitude(-45.1))),
                "262172"],
            [geo_coordinate_bounding_box2d(
                geo_coordinate2d(longitude(-45.0), latitude(-90.0)),
                geo_coordinate2d(longitude(-0.1), latitude(-45.1))),
                "262173"],
            [geo_coordinate_bounding_box2d(
                geo_coordinate2d(longitude(+0.0), latitude(-90.0)),
                geo_coordinate2d(longitude(+45.0), latitude(-45.1))),
                "262152"],
            [geo_coordinate_bounding_box2d(
                geo_coordinate2d(longitude(+45.1), latitude(-90.0)),
                geo_coordinate2d(longitude(+90.0), latitude(-45.1))),
                "262153"],
            [geo_coordinate_bounding_box2d(
                geo_coordinate2d(longitude(+90.1), latitude(-90.0)),
                geo_coordinate2d(longitude(+135.0), latitude(-45.1))),
                "262156"],
            [geo_coordinate_bounding_box2d(
                geo_coordinate2d(longitude(+135.1), latitude(-90.0)),
                geo_coordinate2d(longitude(+180.0), latitude(-45.1))),
                "262157"],
            [geo_coordinate_bounding_box2d(
                geo_coordinate2d(longitude(-180.0), latitude(-45.0)),
                geo_coordinate2d(longitude(-135.1), latitude(-0.1))),
                "262170"],
            [geo_coordinate_bounding_box2d(
                geo_coordinate2d(longitude(-135.0), latitude(-45.0)),
                geo_coordinate2d(longitude(-90.1), latitude(-0.1))),
                "262171"],
            [geo_coordinate_bounding_box2d(
                geo_coordinate2d(longitude(-90.0), latitude(-45.0)),
                geo_coordinate2d(longitude(-45.1), latitude(-0.1))),
                "262174"],
            [geo_coordinate_bounding_box2d(
                geo_coordinate2d(longitude(-45.0), latitude(-45.0)),
                geo_coordinate2d(longitude(-0.1), latitude(-0.1))),
                "262175"],
            [geo_coordinate_bounding_box2d(
                geo_coordinate2d(longitude(+0.0), latitude(-45.0)),
                geo_coordinate2d(longitude(+45.0), latitude(-0.1))),
                "262154"],
            [geo_coordinate_bounding_box2d(
                geo_coordinate2d(longitude(+45.1), latitude(-45.0)),
                geo_coordinate2d(longitude(+90.0), latitude(-0.1))),
                "262155"],
            [geo_coordinate_bounding_box2d(
                geo_coordinate2d(longitude(+90.1), latitude(-45.0)),
                geo_coordinate2d(longitude(+135.0), latitude(-0.1))),
                "262158"],
            [geo_coordinate_bounding_box2d(
                geo_coordinate2d(longitude(+135.1), latitude(-45.0)),
                geo_coordinate2d(longitude(+180.0), latitude(-0.1))),
                "262159"],
            [geo_coordinate_bounding_box2d(
                geo_coordinate2d(longitude(-180.0), latitude(+0.0)),
                geo_coordinate2d(longitude(-135.1), latitude(+45.0))),
                "262160"],
            [geo_coordinate_bounding_box2d(
                geo_coordinate2d(longitude(-135.0), latitude(+0.0)),
                geo_coordinate2d(longitude(-90.1), latitude(+45.0))),
                "262161"],
            [geo_coordinate_bounding_box2d(
                geo_coordinate2d(longitude(-90.0), latitude(+0.0)),
                geo_coordinate2d(longitude(-45.1), latitude(+45.0))),
                "262164"],
            [geo_coordinate_bounding_box2d(
                geo_coordinate2d(longitude(-45.0), latitude(+0.0)),
                geo_coordinate2d(longitude(-0.1), latitude(+45.0))),
                "262165"],
            [geo_coordinate_bounding_box2d(
                geo_coordinate2d(longitude(+0.0), latitude(+0.0)),
                geo_coordinate2d(longitude(+45.0), latitude(+45.0))),
                "262144"],
            [geo_coordinate_bounding_box2d(
                geo_coordinate2d(longitude(+45.1), latitude(+0.0)),
                geo_coordinate2d(longitude(+90.0), latitude(+45.0))),
                "262145"],
            [geo_coordinate_bounding_box2d(
                geo_coordinate2d(longitude(+90.1), latitude(+0.0)),
                geo_coordinate2d(longitude(+135.0), latitude(+45.0))),
                "262148"],
            [geo_coordinate_bounding_box2d(
                geo_coordinate2d(longitude(+135.1), latitude(+0.0)),
                geo_coordinate2d(longitude(+180.0), latitude(+45.0))),
                "262149"],
            [geo_coordinate_bounding_box2d(
                geo_coordinate2d(longitude(-180.0), latitude(+45.1)),
                geo_coordinate2d(longitude(-135.1), latitude(+90.0))),
                "262162"],
            [geo_coordinate_bounding_box2d(
                geo_coordinate2d(longitude(-135.0), latitude(+45.1)),
                geo_coordinate2d(longitude(-90.1), latitude(+90.0))),
                "262163"],
            [geo_coordinate_bounding_box2d(
                geo_coordinate2d(longitude(-90.0), latitude(+45.1)),
                geo_coordinate2d(longitude(-45.1), latitude(+90.0))),
                "262166"],
            [geo_coordinate_bounding_box2d(
                geo_coordinate2d(longitude(-45.0), latitude(+45.1)),
                geo_coordinate2d(longitude(-0.1), latitude(+90.0))),
                "262167"],
            [geo_coordinate_bounding_box2d(
                geo_coordinate2d(longitude(+0.0), latitude(+45.1)),
                geo_coordinate2d(longitude(+45.0), latitude(+90.0))),
                "262146"],
            [geo_coordinate_bounding_box2d(
                geo_coordinate2d(longitude(+45.1), latitude(+45.1)),
                geo_coordinate2d(longitude(+90.0), latitude(+90.0))),
                "262147"],
            [geo_coordinate_bounding_box2d(
                geo_coordinate2d(longitude(+90.1), latitude(+45.1)),
                geo_coordinate2d(longitude(+135.0), latitude(+90.0))),
                "262150"],
            [geo_coordinate_bounding_box2d(
                geo_coordinate2d(longitude(+135.1), latitude(+45.1)),
                geo_coordinate2d(longitude(+180.0), latitude(+90.0))),
                "262151"]]

        depth = 2

        for lst in tests:
            bbox = lst[0]
            ll = geo_coordinate2d(bbox.lower_left())
            lr = geo_coordinate2d(bbox.upper_right().get_longitude(),
                                  bbox.lower_left().get_latitude())
            ur = geo_coordinate2d(bbox.upper_right())
            ul = geo_coordinate2d(bbox.lower_left().get_longitude(),
                                  bbox.upper_right().get_latitude())
            qk = quad_key.get_key_from_longitude_latitude_at_depth(
                type_morton, ll, depth)
            self.assertEqual(lst[1], qk.to_internal_string())
            qk = quad_key.get_key_from_longitude_latitude_at_depth(
                type_morton, lr, depth)
            self.assertEqual(lst[1], qk.to_internal_string())
            qk = quad_key.get_key_from_longitude_latitude_at_depth(
                type_morton, ur, depth)
            self.assertEqual(lst[1], qk.to_internal_string())
            qk = quad_key.get_key_from_longitude_latitude_at_depth(
                type_morton, ul, depth)
            self.assertEqual(lst[1], qk.to_internal_string())
            actual = geo_coordinate_bounding_box2d()
            qk.get_geo_coordinate_bounds2d(actual)
            self.assertTrue(ll.near(actual.lower_left(), 1))
            self.assertTrue(ur.near(actual.upper_right(), 1))

    def test_get_keys_from_longitude_latitude_bounding_box(self):
        """Test to get the bounding box of a quadquad_quad_key."""
        tests = [
            (
                geo_coordinate_bounding_box2d(
                    geo_coordinate2d(longitude(-180.0), latitude(-90.0)),
                    geo_coordinate2d(longitude(-0.1), latitude(+90.0))),
                [
                    quad_key(type_morton, 0, 0, 0)
                ]
            ),
            (
                geo_coordinate_bounding_box2d(
                    geo_coordinate2d(longitude(+0.0), latitude(-90.0)),
                    geo_coordinate2d(longitude(+180.0), latitude(+90.0))),
                [
                    quad_key(type_morton, 0, 1, 0)
                ]
            ),
        ]

        for test in tests:
            actual = quad_key.get_keys_from_longitude_latitude_bounding_box(
                type_morton, test[0], 0)
            self.assertEqual(len(test[1]), actual.size())
            for qk in test[1]:
                self.assertTrue(qk in actual)

        tests = (
            (
                geo_coordinate_bounding_box2d(  # i = 0
                    geo_coordinate2d(longitude(-180.0), latitude(-90.0)),
                    geo_coordinate2d(longitude(-0.1), latitude(+90.0))),
                [
                    quad_key(type_morton, 0, 0, 1),
                    quad_key(type_morton, 0, 1, 1),
                    quad_key(type_morton, 1, 0, 1),
                    quad_key(type_morton, 1, 1, 1)
                ]
            ),
            (
                geo_coordinate_bounding_box2d(  # i = 1
                    geo_coordinate2d(longitude(+0.0), latitude(-90.0)),
                    geo_coordinate2d(longitude(+180.0), latitude(+90.0))),
                [
                    quad_key(type_morton, 0, 2, 1),
                    quad_key(type_morton, 0, 3, 1),
                    quad_key(type_morton, 1, 2, 1),
                    quad_key(type_morton, 1, 3, 1),
                ]
            ),
            (
                geo_coordinate_bounding_box2d(  # i = 2
                    geo_coordinate2d(longitude(-180.0), latitude(-90.0)),
                    geo_coordinate2d(longitude(-0.1), latitude(-0.1))),
                [
                    quad_key(type_morton, 0, 0, 1),
                    quad_key(type_morton, 0, 1, 1),
                ]
            ),
            (
                geo_coordinate_bounding_box2d(  # i = 3
                    geo_coordinate2d(longitude(-180.0), latitude(+0.0)),
                    geo_coordinate2d(longitude(-0.1), latitude(+90.0))),
                [
                    quad_key(type_morton, 1, 0, 1),
                    quad_key(type_morton, 1, 1, 1),
                ]
            ),
            (
                geo_coordinate_bounding_box2d(  # i = 4
                    geo_coordinate2d(longitude(+0.0), latitude(-90.0)),
                    geo_coordinate2d(longitude(+180.0), latitude(-0.1))),
                [
                    quad_key(type_morton, 0, 2, 1),
                    quad_key(type_morton, 0, 3, 1),
                ]
            ),
            (
                geo_coordinate_bounding_box2d(  # i = 5
                    geo_coordinate2d(longitude(+0.0), latitude(+0.0)),
                    geo_coordinate2d(longitude(+180.0), latitude(+90.0))),
                [
                    quad_key(type_morton, 1, 2, 1),
                    quad_key(type_morton, 1, 3, 1),
                ]
            ),
            (
                geo_coordinate_bounding_box2d(  # i = 6
                    geo_coordinate2d(longitude(-180.0), latitude(-90.0)),
                    geo_coordinate2d(longitude(-90.1), latitude(-0.1))),
                [
                    quad_key(type_morton, 0, 0, 1),
                ]
            ),
            (
                geo_coordinate_bounding_box2d(  # i = 7
                    geo_coordinate2d(longitude(-90.0), latitude(-90.0)),
                    geo_coordinate2d(longitude(-0.1), latitude(-0.1))),
                [
                    quad_key(type_morton, 0, 1, 1),
                ]
            ),
            (
                geo_coordinate_bounding_box2d(  # i = 8
                    geo_coordinate2d(longitude(+0.0), latitude(-90.0)),
                    geo_coordinate2d(longitude(+90.0), latitude(-0.1))),
                [
                    quad_key(type_morton, 0, 2, 1),
                ]
            ),
            (
                geo_coordinate_bounding_box2d(  # i = 9
                    geo_coordinate2d(longitude(+90.1), latitude(-90.0)),
                    geo_coordinate2d(longitude(+180.0), latitude(-0.1))),
                [
                    quad_key(type_morton, 0, 3, 1),
                ]
            ),
            (
                geo_coordinate_bounding_box2d(  # i = 10
                    geo_coordinate2d(longitude(-180.0), latitude(+0.0)),
                    geo_coordinate2d(longitude(-90.1), latitude(+90.0))),
                [
                    quad_key(type_morton, 1, 0, 1),
                ]
            ),
            (
                geo_coordinate_bounding_box2d(  # i = 11
                    geo_coordinate2d(longitude(-90.0), latitude(+0.0)),
                    geo_coordinate2d(longitude(-0.1), latitude(+90.0))),
                [
                    quad_key(type_morton, 1, 1, 1),
                ]
            ),
            (
                geo_coordinate_bounding_box2d(  # i = 12
                    geo_coordinate2d(longitude(+0.0), latitude(+0.0)),
                    geo_coordinate2d(longitude(+90.0), latitude(+90.0))),
                [
                    quad_key(type_morton, 1, 2, 1),
                ]
            ),
            (
                geo_coordinate_bounding_box2d(  # i = 13
                    geo_coordinate2d(longitude(+90.1), latitude(+0.0)),
                    geo_coordinate2d(longitude(+180.0), latitude(+90.0))),
                [
                    quad_key(type_morton, 1, 3, 1),
                ]
            ),
        )

        for test in tests:
            actual = qk.get_keys_from_longitude_latitude_bounding_box(
                type_morton, test[0], 1)
            self.assertEqual(len(test[1]), actual.size())
            for qk in test[1]:
                self.assertTrue(qk in actual)

        test = [
            geo_coordinate_bounding_box2d(
                geo_coordinate2d(longitude(-140.0), latitude(-48.0)),
                geo_coordinate2d(longitude(+10.0), latitude(+39.0))),
            [
                quad_key(type_morton, 0, 0, 2),
                quad_key(type_morton, 0, 1, 2),
                quad_key(type_morton, 0, 2, 2),
                quad_key(type_morton, 0, 3, 2),
                quad_key(type_morton, 0, 4, 2),
                quad_key(type_morton, 1, 0, 2),
                quad_key(type_morton, 1, 1, 2),
                quad_key(type_morton, 1, 2, 2),
                quad_key(type_morton, 1, 3, 2),
                quad_key(type_morton, 1, 4, 2),
                quad_key(type_morton, 2, 0, 2),
                quad_key(type_morton, 2, 1, 2),
                quad_key(type_morton, 2, 2, 2),
                quad_key(type_morton, 2, 3, 2),
                quad_key(type_morton, 2, 4, 2),
            ]]
        actual = qk.get_keys_from_longitude_latitude_bounding_box(
            type_morton, test[0], 2)
        self.assertEqual(len(test[1]), actual.size())
        for qk in test[1]:
            self.assertTrue(qk in actual)

    def test_selected_cities(self):
        """Test a given set of known places make sure they work."""
        data = (13, geo_coordinate2d(
            longitude(+ 2.29450000000000),
            latitude(+48.85822200000000)))
        tile = 8428778 | (1 << (data[0] + 16))
        qk = quad_key.get_key_from_longitude_latitude_at_depth(
            type_morton, data[1], data[0])
        self.assertEqual(str(tile), qk.to_internal_string())

        data = (13, geo_coordinate2d(
            longitude(-74.04444400000000),
            latitude(+40.68916700000000)))
        tile = 86924190 | (1 << (data[0] + 16))
        qk = quad_key.get_key_from_longitude_latitude_at_depth(
            type_morton, data[1], data[0])
        self.assertEqual(str(tile), qk.to_internal_string())

        data = (13, geo_coordinate2d(
            longitude(-43.15744400000000),
            latitude(-22.94865800000000)))
        tile = 130726287 | (1 << (data[0] + 16))
        qk = quad_key.get_key_from_longitude_latitude_at_depth(
            type_morton, data[1], data[0])
        self.assertEqual(str(tile), qk.to_internal_string())

        data = (13, geo_coordinate2d(
            longitude(+151.21527800000000),
            latitude(-33.85611100000000)))
        tile = 63372939 | (1 << (data[0] + 16))
        qk = quad_key.get_key_from_longitude_latitude_at_depth(
            type_morton, data[1], data[0])
        self.assertEqual(str(tile), qk.to_internal_string())

        data = (13, geo_coordinate2d(
            longitude(+ 0.00000000000000),
            latitude(+51.50300000000000)))
        tile = 8521770 | (1 << (data[0] + 16))
        qk = quad_key.get_key_from_longitude_latitude_at_depth(
            type_morton, data[1], data[0])
        self.assertEqual(str(tile), qk.to_internal_string())

        data = (13, geo_coordinate2d(
            longitude(-78.45000000000000),
            latitude(+0.00000000000000)))
        tile = 84148305 | (1 << (data[0] + 16))
        qk = quad_key.get_key_from_longitude_latitude_at_depth(
            type_morton, data[1], data[0])
        self.assertEqual(str(tile), qk.to_internal_string())

        data = (10, geo_coordinate2d(
            longitude(+2.29450000000000),
            latitude(+48.85822200000000)))
        tile = 131699 | (1 << (16 + data[0]))
        qk = quad_key.get_key_from_longitude_latitude_at_depth(
            type_morton, data[1], data[0])
        self.assertEqual(str(tile), qk.to_internal_string())

        data = (10, geo_coordinate2d(
            longitude(-74.04444400000000),
            latitude(+40.68916700000000)))
        tile = 1358190 | (1 << (16 + data[0]))
        qk = quad_key.get_key_from_longitude_latitude_at_depth(
            type_morton, data[1], data[0])
        self.assertEqual(str(tile), qk.to_internal_string())

        data = (10, geo_coordinate2d(
            longitude(-43.15744400000000),
            latitude(-22.94865800000000)))
        tile = 2042598 | (1 << (16 + data[0]))
        qk = quad_key.get_key_from_longitude_latitude_at_depth(
            type_morton, data[1], data[0])
        self.assertEqual(str(tile), qk.to_internal_string())

        data = (10, geo_coordinate2d(
            longitude(+151.21527800000000),
            latitude(-33.85611100000000)))
        tile = 990202 | (1 << (16 + data[0]))
        qk = quad_key.get_key_from_longitude_latitude_at_depth(
            type_morton, data[1], data[0])
        self.assertEqual(str(tile), qk.to_internal_string())

        data = (10, geo_coordinate2d(
            longitude(+ 0.00000000000000),
            latitude(+51.50300000000000)))
        tile = 133152 | (1 << (16 + data[0]))
        qk = quad_key.get_key_from_longitude_latitude_at_depth(
            type_morton, data[1], data[0])
        self.assertEqual(str(tile), qk.to_internal_string())

        data = (10, geo_coordinate2d(
            longitude(-78.45000000000000),
            latitude(+0.00000000000000)))
        tile = 1314817 | (1 << (16 + data[0]))
        qk = quad_key.get_key_from_longitude_latitude_at_depth(
            type_morton, data[1], data[0])
        self.assertEqual(str(tile), qk.to_internal_string())

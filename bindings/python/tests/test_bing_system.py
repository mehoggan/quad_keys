"""
Unit Tests for Bing System
"""

from __future__ import print_function

import math
import unittest

from quad_key.quad_key import quad_key
from quad_key.quad_key import type_bing
from quad_key.quad_key import type_osgeo
from quad_key.quad_key import geo_coordinate2d
from quad_key.quad_key import geo_coordinate_bounding_box2d
from quad_key.quad_key import longitude
from quad_key.quad_key import latitude


class TestBingSystem(unittest.TestCase):
    """Class for running unit tests."""

    def test_default_ctor(self):
        """
        Test default construction of quad_key using type_bing
        """
        qk = quad_key(type_bing)
        self.assertEqual(qk.get_row(), 0)
        self.assertEqual(qk.get_col(), 0)
        self.assertEqual(qk.get_type(), type_bing)
        self.assertEqual(qk.to_internal_string(), '')

    def test_is_valid(self):
        """
        See Testqk.test_is_valid
        """

    def test_is_root_key(self):
        """
        See Testqk.test_is_root_key
        """

    def test_get_parent(self):
        """
        Test to get parent of a generically formatted qk.
        """
        key0 = quad_key(type_bing, 0, 0, 1)
        key1 = quad_key(type_bing, 1, 0, 1)
        key2 = quad_key(type_bing, 1, 1, 1)
        key3 = quad_key(type_bing, 0, 1, 1)

        parent = quad_key(type_bing, 0, 0, 0)

        self.assertEqual(type_bing, key0.get_type())
        self.assertEqual(type_bing, key1.get_type())
        self.assertEqual(type_bing, key2.get_type())
        self.assertEqual(type_bing, key3.get_type())

        self.assertEqual(type_bing, parent.get_type())

        self.assertEqual(key0.get_parent(), parent)
        self.assertEqual(key1.get_parent(), parent)
        self.assertEqual(key2.get_parent(), parent)
        self.assertEqual(key3.get_parent(), parent)

        key0 = quad_key(type_bing, 5, 6, 3)
        key1 = quad_key(type_bing, 4, 6, 3)
        key2 = quad_key(type_bing, 4, 7, 3)
        key3 = quad_key(type_bing, 5, 7, 3)

        parent = quad_key(type_bing, 2, 3, 2)

        self.assertEqual(type_bing, key0.get_type())
        self.assertEqual(type_bing, key1.get_type())
        self.assertEqual(type_bing, key2.get_type())
        self.assertEqual(type_bing, key3.get_type())

        self.assertEqual(key0.get_parent(), parent)
        self.assertEqual(key1.get_parent(), parent)
        self.assertEqual(key2.get_parent(), parent)
        self.assertEqual(key3.get_parent(), parent)

    def test_is_my_ancestor(self):
        """
        Checks to see if specified quadkey up in the hierarchy is an "ancestor"
        of the given qk.
        """
        none = quad_key()
        self.assertFalse(none.is_my_ancestor(quad_key()))

        qk = quad_key(type_bing, 5, 7, 3)
        self.assertFalse(qk.is_my_ancestor(quad_key()))
        self.assertFalse(qk.is_my_ancestor(quad_key(type_osgeo, 2, 3, 2)))
        self.assertFalse(qk.is_my_ancestor(quad_key(type_osgeo, 0, 0, 0)))
        self.assertFalse(qk.is_my_ancestor(quad_key(type_bing, 5, 7, 3)))
        self.assertTrue(qk.is_my_ancestor(quad_key(type_bing, 2, 3, 2)))
        self.assertTrue(qk.is_my_ancestor(quad_key(type_bing, 0, 0, 0)))

    def test_get_ancestor(self):
        """
        Gets the ancestor up the tree according to a delta provided.
        """
        qk = quad_key(type_bing, 0, 7, 3)
        ancestor = quad_key(type_bing, 0, 1, 1)
        self.assertTrue(qk.get_ancestor(2), ancestor)
        qk = quad_key(type_bing, 4, 31, 5)
        ancestor = quad_key(type_bing, 0, 3, 2)
        self.assertTrue(qk.get_ancestor(4), ancestor)
        qk = quad_key(type_bing, 4, 31, 5)
        ancestor = quad_key(type_bing, 0, 3, 2)
        self.assertTrue(qk.get_ancestor(3), ancestor)
        qk = quad_key(type_bing, 4, 31, 5)
        ancestor = quad_key(type_bing, 1, 7, 3)
        self.assertTrue(qk.get_ancestor(2), ancestor)

    def test_get_child(self):
        """
        Get a single child NE, SE, NW, SW
        """
        self.assertEqual(quad_key(),
                         quad_key().get_child(quad_key.quadrant_north_west))
        maxdepthbing = quad_key.max_depth(type_bing)
        self.assertEqual(quad_key(),
                         quad_key(type_bing, 0, 0, maxdepthbing).get_child(
                         quad_key.quadrant_north_east))

        qk = quad_key(type_bing, 0, 0, 3)
        self.assertEqual(quad_key(type_bing, 1, 0, 4),
                         qk.get_child(qk.quadrant_north_west))
        self.assertEqual(quad_key(type_bing, 1, 1, 4),
                         qk.get_child(qk.quadrant_north_east))
        self.assertEqual(quad_key(type_bing, 0, 1, 4),
                         qk.get_child(qk.quadrant_south_east))
        self.assertEqual(quad_key(type_bing, 0, 0, 4),
                         qk.get_child(qk.quadrant_south_west))

        qk = quad_key(type_bing, 2, 3, 3)
        self.assertEqual(quad_key(type_bing, 5, 6, 4),
                         qk.get_child(qk.quadrant_north_west))
        self.assertEqual(quad_key(type_bing, 5, 7, 4),
                         qk.get_child(qk.quadrant_north_east))
        self.assertEqual(quad_key(type_bing, 4, 7, 4),
                         qk.get_child(qk.quadrant_south_east))
        self.assertEqual(quad_key(type_bing, 4, 6, 4),
                         qk.get_child(qk.quadrant_south_west))

    def test_get_children(self):
        """
        Get all the childern of a qk.
        """
        qk = quad_key()
        vec = qk.get_children()
        self.assertEqual(0, len(vec))

        qk = quad_key(type_bing, 0, 0, 1)
        vec = qk.get_children()
        self.assertEqual(4, len(vec))
        self.assertTrue(quad_key(type_bing, 0, 0, 2) in vec)
        self.assertTrue(quad_key(type_bing, 0, 1, 2) in vec)
        self.assertTrue(quad_key(type_bing, 1, 0, 2) in vec)
        self.assertTrue(quad_key(type_bing, 1, 1, 2) in vec)

        qk = quad_key(type_bing, 0, 1, 1)
        vec = qk.get_children()
        self.assertEqual(4, len(vec))
        self.assertTrue(quad_key(type_bing, 0, 2, 2) in vec)
        self.assertTrue(quad_key(type_bing, 0, 3, 2) in vec)
        self.assertTrue(quad_key(type_bing, 1, 2, 2) in vec)
        self.assertTrue(quad_key(type_bing, 1, 3, 2) in vec)

        qk = quad_key(type_bing, 1, 0, 1)
        vec = qk.get_children()
        self.assertEqual(4, len(vec))
        self.assertTrue(quad_key(type_bing, 2, 0, 2) in vec)
        self.assertTrue(quad_key(type_bing, 2, 1, 2) in vec)
        self.assertTrue(quad_key(type_bing, 3, 0, 2) in vec)
        self.assertTrue(quad_key(type_bing, 3, 1, 2) in vec)

        qk = quad_key(type_bing, 1, 1, 1)
        vec = qk.get_children()
        self.assertEqual(4, len(vec))
        self.assertTrue(quad_key(type_bing, 2, 2, 2) in vec)
        self.assertTrue(quad_key(type_bing, 2, 3, 2) in vec)
        self.assertTrue(quad_key(type_bing, 3, 2, 2) in vec)
        self.assertTrue(quad_key(type_bing, 3, 3, 2) in vec)

    def test_get_descendants(self):
        """
        Get all the defendants at some delta in the tree.
        """
        bing_max_depth = quad_key.max_depth(type_bing)
        qk = quad_key(type_bing, 0, 0, bing_max_depth - 3)

        vec = qk.get_descendants(4)
        self.assertEqual(0, len(vec))

        none = quad_key()
        vec = none.get_descendants(1)
        self.assertEqual(0, len(vec))

        qk = quad_key(type_bing, 0, 0, 0)
        vec = qk.get_descendants(0)
        self.assertEqual(0, len(vec))

        qk = quad_key(type_bing, 0, 0, 0)
        vec = qk.get_descendants(1)
        self.assertEqual(4, len(vec))
        self.assertTrue(quad_key(type_bing, 0, 0, 1) in vec)
        self.assertTrue(quad_key(type_bing, 0, 1, 1) in vec)
        self.assertTrue(quad_key(type_bing, 1, 0, 1) in vec)
        self.assertTrue(quad_key(type_bing, 1, 1, 1) in vec)

        vec = qk.get_descendants(2)
        self.assertEqual(16, len(vec))
        self.assertTrue(quad_key(type_bing, 0, 0, 2) in vec)
        self.assertTrue(quad_key(type_bing, 0, 1, 2) in vec)
        self.assertTrue(quad_key(type_bing, 0, 2, 2) in vec)
        self.assertTrue(quad_key(type_bing, 0, 3, 2) in vec)
        self.assertTrue(quad_key(type_bing, 1, 0, 2) in vec)
        self.assertTrue(quad_key(type_bing, 1, 1, 2) in vec)
        self.assertTrue(quad_key(type_bing, 1, 2, 2) in vec)
        self.assertTrue(quad_key(type_bing, 1, 3, 2) in vec)
        self.assertTrue(quad_key(type_bing, 2, 0, 2) in vec)
        self.assertTrue(quad_key(type_bing, 2, 1, 2) in vec)
        self.assertTrue(quad_key(type_bing, 2, 2, 2) in vec)
        self.assertTrue(quad_key(type_bing, 2, 3, 2) in vec)
        self.assertTrue(quad_key(type_bing, 3, 0, 2) in vec)
        self.assertTrue(quad_key(type_bing, 3, 1, 2) in vec)
        self.assertTrue(quad_key(type_bing, 3, 2, 2) in vec)
        self.assertTrue(quad_key(type_bing, 3, 3, 2) in vec)

        vec = qk.get_descendants(3)
        self.assertEqual(64, len(vec))
        self.assertTrue(quad_key(type_bing, 0, 0, 3) in vec)
        self.assertTrue(quad_key(type_bing, 0, 1, 3) in vec)
        self.assertTrue(quad_key(type_bing, 0, 2, 3) in vec)
        self.assertTrue(quad_key(type_bing, 0, 3, 3) in vec)
        self.assertTrue(quad_key(type_bing, 0, 4, 3) in vec)
        self.assertTrue(quad_key(type_bing, 0, 5, 3) in vec)
        self.assertTrue(quad_key(type_bing, 0, 6, 3) in vec)
        self.assertTrue(quad_key(type_bing, 0, 7, 3) in vec)
        self.assertTrue(quad_key(type_bing, 1, 0, 3) in vec)
        self.assertTrue(quad_key(type_bing, 1, 1, 3) in vec)
        self.assertTrue(quad_key(type_bing, 1, 2, 3) in vec)
        self.assertTrue(quad_key(type_bing, 1, 3, 3) in vec)
        self.assertTrue(quad_key(type_bing, 1, 4, 3) in vec)
        self.assertTrue(quad_key(type_bing, 1, 5, 3) in vec)
        self.assertTrue(quad_key(type_bing, 1, 6, 3) in vec)
        self.assertTrue(quad_key(type_bing, 1, 7, 3) in vec)
        self.assertTrue(quad_key(type_bing, 2, 0, 3) in vec)
        self.assertTrue(quad_key(type_bing, 2, 1, 3) in vec)
        self.assertTrue(quad_key(type_bing, 2, 2, 3) in vec)
        self.assertTrue(quad_key(type_bing, 2, 3, 3) in vec)
        self.assertTrue(quad_key(type_bing, 2, 4, 3) in vec)
        self.assertTrue(quad_key(type_bing, 2, 5, 3) in vec)
        self.assertTrue(quad_key(type_bing, 2, 6, 3) in vec)
        self.assertTrue(quad_key(type_bing, 2, 7, 3) in vec)
        self.assertTrue(quad_key(type_bing, 3, 0, 3) in vec)
        self.assertTrue(quad_key(type_bing, 3, 1, 3) in vec)
        self.assertTrue(quad_key(type_bing, 3, 2, 3) in vec)
        self.assertTrue(quad_key(type_bing, 3, 3, 3) in vec)
        self.assertTrue(quad_key(type_bing, 3, 4, 3) in vec)
        self.assertTrue(quad_key(type_bing, 3, 5, 3) in vec)
        self.assertTrue(quad_key(type_bing, 3, 6, 3) in vec)
        self.assertTrue(quad_key(type_bing, 3, 7, 3) in vec)
        self.assertTrue(quad_key(type_bing, 4, 0, 3) in vec)
        self.assertTrue(quad_key(type_bing, 4, 1, 3) in vec)
        self.assertTrue(quad_key(type_bing, 4, 2, 3) in vec)
        self.assertTrue(quad_key(type_bing, 4, 3, 3) in vec)
        self.assertTrue(quad_key(type_bing, 4, 4, 3) in vec)
        self.assertTrue(quad_key(type_bing, 4, 5, 3) in vec)
        self.assertTrue(quad_key(type_bing, 4, 6, 3) in vec)
        self.assertTrue(quad_key(type_bing, 4, 7, 3) in vec)
        self.assertTrue(quad_key(type_bing, 5, 0, 3) in vec)
        self.assertTrue(quad_key(type_bing, 5, 1, 3) in vec)
        self.assertTrue(quad_key(type_bing, 5, 2, 3) in vec)
        self.assertTrue(quad_key(type_bing, 5, 3, 3) in vec)
        self.assertTrue(quad_key(type_bing, 5, 4, 3) in vec)
        self.assertTrue(quad_key(type_bing, 5, 5, 3) in vec)
        self.assertTrue(quad_key(type_bing, 5, 6, 3) in vec)
        self.assertTrue(quad_key(type_bing, 5, 7, 3) in vec)
        self.assertTrue(quad_key(type_bing, 6, 0, 3) in vec)
        self.assertTrue(quad_key(type_bing, 6, 1, 3) in vec)
        self.assertTrue(quad_key(type_bing, 6, 2, 3) in vec)
        self.assertTrue(quad_key(type_bing, 6, 3, 3) in vec)
        self.assertTrue(quad_key(type_bing, 6, 4, 3) in vec)
        self.assertTrue(quad_key(type_bing, 6, 5, 3) in vec)
        self.assertTrue(quad_key(type_bing, 6, 6, 3) in vec)
        self.assertTrue(quad_key(type_bing, 6, 7, 3) in vec)
        self.assertTrue(quad_key(type_bing, 7, 0, 3) in vec)
        self.assertTrue(quad_key(type_bing, 7, 1, 3) in vec)
        self.assertTrue(quad_key(type_bing, 7, 2, 3) in vec)
        self.assertTrue(quad_key(type_bing, 7, 3, 3) in vec)
        self.assertTrue(quad_key(type_bing, 7, 4, 3) in vec)
        self.assertTrue(quad_key(type_bing, 7, 5, 3) in vec)
        self.assertTrue(quad_key(type_bing, 7, 6, 3) in vec)
        self.assertTrue(quad_key(type_bing, 7, 7, 3) in vec)

    def test_get_siblings(self):
        """
        Test to get siblings of a given quadkey
        """
        qk = quad_key()
        vec = qk.get_siblings()
        self.assertEqual(0, len(vec))

        qk = quad_key(type_bing, 0, 0, 1)
        vec = qk.get_siblings()
        self.assertEqual(3, len(vec))
        self.assertTrue(quad_key(type_bing, 0, 1, 1) in vec)
        self.assertTrue(quad_key(type_bing, 1, 1, 1) in vec)
        self.assertTrue(quad_key(type_bing, 1, 0, 1) in vec)

    def test_get_neighbors(self):
        """
        Test to get the neighbors of a given quadqk.
        """
        vec = quad_key().get_neighbors()
        self.assertEqual(0, len(vec))

        vec = quad_key(type_bing, 0, 0, 0).get_neighbors()
        self.assertEqual(0, len(vec))

        vec = quad_key(type_bing, 0, 0, 2).get_neighbors()
        self.assertEqual(5, len(vec))
        self.assertTrue(quad_key(type_bing, 0, 1, 2) in vec)
        self.assertTrue(quad_key(type_bing, 1, 1, 2) in vec)
        self.assertTrue(quad_key(type_bing, 1, 0, 2) in vec)
        self.assertTrue(quad_key(type_bing, 0, 3, 2) in vec)
        self.assertTrue(quad_key(type_bing, 1, 3, 2) in vec)

        vec = quad_key(type_bing, 0, 1, 2).get_neighbors()
        self.assertEqual(5, len(vec))
        self.assertTrue(quad_key(type_bing, 0, 0, 2) in vec)
        self.assertTrue(quad_key(type_bing, 1, 0, 2) in vec)
        self.assertTrue(quad_key(type_bing, 1, 1, 2) in vec)
        self.assertTrue(quad_key(type_bing, 1, 2, 2) in vec)
        self.assertTrue(quad_key(type_bing, 0, 2, 2) in vec)

        vec = quad_key(type_bing, 0, 2, 2).get_neighbors()
        self.assertEqual(5, len(vec))
        self.assertTrue(quad_key(type_bing, 0, 1, 2) in vec)
        self.assertTrue(quad_key(type_bing, 1, 1, 2) in vec)
        self.assertTrue(quad_key(type_bing, 1, 2, 2) in vec)
        self.assertTrue(quad_key(type_bing, 1, 3, 2) in vec)
        self.assertTrue(quad_key(type_bing, 0, 3, 2) in vec)

        vec = quad_key(type_bing, 0, 3, 2).get_neighbors()
        self.assertEqual(5, len(vec))
        self.assertTrue(quad_key(type_bing, 0, 2, 2) in vec)
        self.assertTrue(quad_key(type_bing, 1, 2, 2) in vec)
        self.assertTrue(quad_key(type_bing, 1, 3, 2) in vec)
        self.assertTrue(quad_key(type_bing, 1, 0, 2) in vec)
        self.assertTrue(quad_key(type_bing, 0, 0, 2) in vec)

        vec = quad_key(type_bing, 1, 0, 2).get_neighbors()
        self.assertEqual(8, len(vec))
        self.assertTrue(quad_key(type_bing, 0, 0, 2) in vec)
        self.assertTrue(quad_key(type_bing, 0, 1, 2) in vec)
        self.assertTrue(quad_key(type_bing, 1, 1, 2) in vec)
        self.assertTrue(quad_key(type_bing, 2, 1, 2) in vec)
        self.assertTrue(quad_key(type_bing, 2, 0, 2) in vec)
        self.assertTrue(quad_key(type_bing, 2, 3, 2) in vec)
        self.assertTrue(quad_key(type_bing, 1, 3, 2) in vec)
        self.assertTrue(quad_key(type_bing, 0, 3, 2) in vec)

        vec = quad_key(type_bing, 1, 1, 2).get_neighbors()
        self.assertEqual(8, len(vec))
        self.assertTrue(quad_key(type_bing, 1, 0, 2) in vec)
        self.assertTrue(quad_key(type_bing, 0, 0, 2) in vec)
        self.assertTrue(quad_key(type_bing, 0, 1, 2) in vec)
        self.assertTrue(quad_key(type_bing, 2, 2, 2) in vec)
        self.assertTrue(quad_key(type_bing, 2, 1, 2) in vec)
        self.assertTrue(quad_key(type_bing, 2, 0, 2) in vec)
        self.assertTrue(quad_key(type_bing, 0, 2, 2) in vec)
        self.assertTrue(quad_key(type_bing, 1, 2, 2) in vec)

        vec = quad_key(type_bing, 1, 2, 2).get_neighbors()
        self.assertEqual(8, len(vec))
        self.assertTrue(quad_key(type_bing, 1, 1, 2) in vec)
        self.assertTrue(quad_key(type_bing, 0, 1, 2) in vec)
        self.assertTrue(quad_key(type_bing, 0, 2, 2) in vec)
        self.assertTrue(quad_key(type_bing, 2, 3, 2) in vec)
        self.assertTrue(quad_key(type_bing, 2, 2, 2) in vec)
        self.assertTrue(quad_key(type_bing, 2, 1, 2) in vec)
        self.assertTrue(quad_key(type_bing, 0, 3, 2) in vec)
        self.assertTrue(quad_key(type_bing, 1, 3, 2) in vec)

        vec = quad_key(type_bing, 1, 3, 2).get_neighbors()
        self.assertEqual(8, len(vec))
        self.assertTrue(quad_key(type_bing, 1, 2, 2) in vec)
        self.assertTrue(quad_key(type_bing, 0, 2, 2) in vec)
        self.assertTrue(quad_key(type_bing, 0, 3, 2) in vec)
        self.assertTrue(quad_key(type_bing, 2, 0, 2) in vec)
        self.assertTrue(quad_key(type_bing, 2, 3, 2) in vec)
        self.assertTrue(quad_key(type_bing, 2, 2, 2) in vec)
        self.assertTrue(quad_key(type_bing, 0, 0, 2) in vec)
        self.assertTrue(quad_key(type_bing, 1, 0, 2) in vec)

        vec = quad_key(type_bing, 4, 7, 3).get_neighbors()
        self.assertEqual(8, len(vec))
        self.assertTrue(quad_key(type_bing, 3, 7, 3) in vec)
        self.assertTrue(quad_key(type_bing, 3, 6, 3) in vec)
        self.assertTrue(quad_key(type_bing, 4, 6, 3) in vec)
        self.assertTrue(quad_key(type_bing, 5, 6, 3) in vec)
        self.assertTrue(quad_key(type_bing, 5, 7, 3) in vec)
        self.assertTrue(quad_key(type_bing, 5, 0, 3) in vec)
        self.assertTrue(quad_key(type_bing, 4, 0, 3) in vec)
        self.assertTrue(quad_key(type_bing, 3, 0, 3) in vec)

        vec = quad_key(type_bing, 4, 0, 3).get_neighbors()
        self.assertEqual(8, len(vec))
        self.assertTrue(quad_key(type_bing, 3, 0, 3) in vec)
        self.assertTrue(quad_key(type_bing, 3, 1, 3) in vec)
        self.assertTrue(quad_key(type_bing, 4, 1, 3) in vec)
        self.assertTrue(quad_key(type_bing, 5, 1, 3) in vec)
        self.assertTrue(quad_key(type_bing, 5, 0, 3) in vec)
        self.assertTrue(quad_key(type_bing, 5, 7, 3) in vec)
        self.assertTrue(quad_key(type_bing, 4, 7, 3) in vec)
        self.assertTrue(quad_key(type_bing, 3, 7, 3) in vec)

    def test_to_string_from_string(self):
        """
        Test to convert an internally formatted string and back.
        """
        root = quad_key.from_internal_string(type_bing, "")
        self.assertEqual(0, root.get_row())
        self.assertEqual(0, root.get_col())
        self.assertEqual(0, root.get_depth())

        qk = quad_key.from_internal_string(type_bing, "0")
        self.assertEqual(1, qk.get_row())
        self.assertEqual(0, qk.get_col())
        self.assertEqual(1, qk.get_depth())
        self.assertEqual("0", qk.to_internal_string())
        qk = quad_key.from_internal_string(type_bing, "1")
        self.assertEqual(1, qk.get_row())
        self.assertEqual(1, qk.get_col())
        self.assertEqual(1, qk.get_depth())
        self.assertEqual("1", qk.to_internal_string())
        qk = quad_key.from_internal_string(type_bing, "2")
        self.assertEqual(0, qk.get_row())
        self.assertEqual(0, qk.get_col())
        self.assertEqual(1, qk.get_depth())
        self.assertEqual("2", qk.to_internal_string())
        qk = quad_key.from_internal_string(type_bing, "3")
        self.assertEqual(0, qk.get_row())
        self.assertEqual(1, qk.get_col())
        self.assertEqual(1, qk.get_depth())
        self.assertEqual("3", qk.to_internal_string())

        qk = quad_key.from_internal_string(type_bing, "00")
        self.assertEqual(3, qk.get_row())
        self.assertEqual(0, qk.get_col())
        self.assertEqual(2, qk.get_depth())
        self.assertEqual("00", qk.to_internal_string())
        qk = quad_key.from_internal_string(type_bing, "01")
        self.assertEqual(3, qk.get_row())
        self.assertEqual(1, qk.get_col())
        self.assertEqual(2, qk.get_depth())
        self.assertEqual("01", qk.to_internal_string())
        qk = quad_key.from_internal_string(type_bing, "02")
        self.assertEqual(2, qk.get_row())
        self.assertEqual(0, qk.get_col())
        self.assertEqual(2, qk.get_depth())
        self.assertEqual("02", qk.to_internal_string())
        qk = quad_key.from_internal_string(type_bing, "03")
        self.assertEqual(2, qk.get_row())
        self.assertEqual(1, qk.get_col())
        self.assertEqual(2, qk.get_depth())
        self.assertEqual("03", qk.to_internal_string())
        qk = quad_key.from_internal_string(type_bing, "10")
        self.assertEqual(3, qk.get_row())
        self.assertEqual(2, qk.get_col())
        self.assertEqual(2, qk.get_depth())
        self.assertEqual("10", qk.to_internal_string())
        qk = quad_key.from_internal_string(type_bing, "11")
        self.assertEqual(3, qk.get_row())
        self.assertEqual(3, qk.get_col())
        self.assertEqual(2, qk.get_depth())
        self.assertEqual("11", qk.to_internal_string())
        qk = quad_key.from_internal_string(type_bing, "12")
        self.assertEqual(2, qk.get_row())
        self.assertEqual(2, qk.get_col())
        self.assertEqual(2, qk.get_depth())
        self.assertEqual("12", qk.to_internal_string())
        qk = quad_key.from_internal_string(type_bing, "13")
        self.assertEqual(2, qk.get_row())
        self.assertEqual(3, qk.get_col())
        self.assertEqual(2, qk.get_depth())
        self.assertEqual("13", qk.to_internal_string())
        qk = quad_key.from_internal_string(type_bing, "20")
        self.assertEqual(1, qk.get_row())
        self.assertEqual(0, qk.get_col())
        self.assertEqual(2, qk.get_depth())
        self.assertEqual("20", qk.to_internal_string())
        qk = quad_key.from_internal_string(type_bing, "21")
        self.assertEqual(1, qk.get_row())
        self.assertEqual(1, qk.get_col())
        self.assertEqual(2, qk.get_depth())
        self.assertEqual("21", qk.to_internal_string())
        qk = quad_key.from_internal_string(type_bing, "22")
        self.assertEqual(0, qk.get_row())
        self.assertEqual(0, qk.get_col())
        self.assertEqual(2, qk.get_depth())
        self.assertEqual("22", qk.to_internal_string())
        qk = quad_key.from_internal_string(type_bing, "23")
        self.assertEqual(0, qk.get_row())
        self.assertEqual(1, qk.get_col())
        self.assertEqual(2, qk.get_depth())
        self.assertEqual("23", qk.to_internal_string())
        qk = quad_key.from_internal_string(type_bing, "30")
        self.assertEqual(1, qk.get_row())
        self.assertEqual(2, qk.get_col())
        self.assertEqual(2, qk.get_depth())
        self.assertEqual("30", qk.to_internal_string())
        qk = quad_key.from_internal_string(type_bing, "31")
        self.assertEqual(1, qk.get_row())
        self.assertEqual(3, qk.get_col())
        self.assertEqual(2, qk.get_depth())
        self.assertEqual("31", qk.to_internal_string())
        qk = quad_key.from_internal_string(type_bing, "32")
        self.assertEqual(0, qk.get_row())
        self.assertEqual(2, qk.get_col())
        self.assertEqual(2, qk.get_depth())
        self.assertEqual("32", qk.to_internal_string())
        qk = quad_key.from_internal_string(type_bing, "33")
        self.assertEqual(0, qk.get_row())
        self.assertEqual(3, qk.get_col())
        self.assertEqual(2, qk.get_depth())
        self.assertEqual("33", qk.to_internal_string())

    def test_get_geo_coordinate_bounds_2d(self):
        """Test to get geographic bounds of quadqk.
        """
        bbox = geo_coordinate_bounding_box2d()

        qk = quad_key.from_internal_string(type_bing, "")
        qk.get_geo_coordinate_bounds2d(bbox)
        self.assertAlmostEqual(-180.0,
                               bbox.lower_left().get_longitude().val())
        self.assertAlmostEqual(-84.9283209,
                               bbox.lower_left().get_latitude().val())
        self.assertAlmostEqual(178.593750,
                               bbox.upper_right().get_longitude().val())
        self.assertAlmostEqual(85.05112877,
                               bbox.upper_right().get_latitude().val())

    def test_get_key_from_longitude_latitude_at_depth_to_bounds(self):
        """Test to get a quadkey from longitude and latitude and then get
        bounds.
        """
        bbox = geo_coordinate_bounding_box2d()

        qk = quad_key.get_key_from_longitude_latitude_at_depth(
            type_bing, geo_coordinate2d(longitude(-180.0),
                                        latitude(-84.0)), 0)
        self.assertEqual(quad_key(type_bing, 0, 0, 0), qk)
        qk.get_geo_coordinate_bounds2d(bbox)
        diff = math.fabs(
            bbox.lower_left().get_longitude() - longitude(-180.0))
        self.assertTrue(2.0 > diff)
        diff = math.fabs(
            bbox.lower_left().get_latitude() - latitude(-85.0))
        self.assertTrue(2.0 > diff)
        diff = math.fabs(
            bbox.upper_right().get_longitude() - longitude(+180.0))
        self.assertTrue(2.0 > diff)
        diff = math.fabs(
            bbox.upper_right().get_latitude() - latitude(+85.0))
        self.assertTrue(2.0 > diff)

        # Inclusion here consists of upper left
        # ul X------X------X
        #    |      |      |
        #    |      |      |
        #    X------X------X
        #    |      |      |
        #    |      |      |
        #    X------X------X
        left = longitude(-180.0)
        midleft = longitude(-0.36)
        midright = longitude(0.0)
        right = longitude(+180.0)
        bottom = latitude(-90.0)
        midbottom = latitude(0.0)
        midtop = latitude(0.36)
        top = latitude(+90.0)

        qk = quad_key.get_key_from_longitude_latitude_at_depth(
            type_bing, geo_coordinate2d(left, top), 1)
        self.assertEqual(quad_key(type_bing, 1, 0, 1), qk)
        qk = quad_key.get_key_from_longitude_latitude_at_depth(
            type_bing, geo_coordinate2d(left, midtop), 1)
        self.assertEqual(quad_key(type_bing, 1, 0, 1), qk)
        qk = quad_key.get_key_from_longitude_latitude_at_depth(
            type_bing, geo_coordinate2d(midleft, midtop), 1)
        self.assertEqual(quad_key(type_bing, 1, 0, 1), qk)
        qk = quad_key.get_key_from_longitude_latitude_at_depth(
            type_bing, geo_coordinate2d(midleft, top), 1)
        self.assertEqual(quad_key(type_bing, 1, 0, 1), qk)
        qk.get_geo_coordinate_bounds2d(bbox)
        diff = math.fabs(bbox.lower_left().get_longitude() - left)
        self.assertTrue(2.0 > diff)
        diff = math.fabs(bbox.lower_left().get_latitude() - midtop)
        self.assertTrue(2.0 > diff)
        diff = math.fabs(bbox.upper_right().get_longitude() - midleft)
        self.assertTrue(2.0 > diff)
        diff = math.fabs(bbox.upper_right().get_latitude() - latitude(+85.0))
        self.assertTrue(2.0 > diff)

        qk = quad_key.get_key_from_longitude_latitude_at_depth(
            type_bing, geo_coordinate2d(midright, top), 1)
        self.assertEqual(quad_key(type_bing, 1, 1, 1), qk)
        qk = quad_key.get_key_from_longitude_latitude_at_depth(
            type_bing, geo_coordinate2d(midright, midtop), 1)
        self.assertEqual(quad_key(type_bing, 1, 1, 1), qk)
        qk = quad_key.get_key_from_longitude_latitude_at_depth(
            type_bing, geo_coordinate2d(right, midtop), 1)
        self.assertEqual(quad_key(type_bing, 1, 1, 1), qk)
        qk = quad_key.get_key_from_longitude_latitude_at_depth(
            type_bing, geo_coordinate2d(right, top), 1)
        self.assertEqual(quad_key(type_bing, 1, 1, 1), qk)
        qk.get_geo_coordinate_bounds2d(bbox)
        diff = math.fabs(bbox.lower_left().get_longitude() - midright)
        self.assertTrue(2.0 > diff)
        diff = math.fabs(bbox.lower_left().get_latitude() - midtop)
        self.assertTrue(2.0 > diff)
        diff = math.fabs(bbox.upper_right().get_longitude() - right)
        self.assertTrue(2.0 > diff)
        diff = math.fabs(bbox.upper_right().get_latitude() - latitude(+85.0))
        self.assertTrue(2.0 > diff)

        qk = quad_key.get_key_from_longitude_latitude_at_depth(
            type_bing, geo_coordinate2d(left, midbottom), 1)
        self.assertEqual(quad_key(type_bing, 0, 0, 1), qk)
        qk = quad_key.get_key_from_longitude_latitude_at_depth(
            type_bing, geo_coordinate2d(left, bottom), 1)
        self.assertEqual(quad_key(type_bing, 0, 0, 1), qk)
        qk = quad_key.get_key_from_longitude_latitude_at_depth(
            type_bing, geo_coordinate2d(midleft, bottom), 1)
        self.assertEqual(quad_key(type_bing, 0, 0, 1), qk)
        qk = quad_key.get_key_from_longitude_latitude_at_depth(
            type_bing, geo_coordinate2d(midleft, midbottom), 1)
        self.assertEqual(quad_key(type_bing, 0, 0, 1), qk)
        qk.get_geo_coordinate_bounds2d(bbox)
        diff = math.fabs(bbox.lower_left().get_longitude() - left)
        self.assertTrue(2.0 > diff)
        diff = math.fabs(bbox.lower_left().get_latitude() - latitude(-85.0))
        self.assertTrue(2.0 > diff)
        diff = math.fabs(bbox.upper_right().get_longitude() - midleft)
        self.assertTrue(2.0 > diff)
        diff = math.fabs(bbox.upper_right().get_latitude() - midbottom)
        self.assertTrue(2.0 > diff)

        qk = quad_key.get_key_from_longitude_latitude_at_depth(
            type_bing, geo_coordinate2d(midright, midbottom), 1)
        self.assertEqual(quad_key(type_bing, 0, 1, 1), qk)
        qk = quad_key.get_key_from_longitude_latitude_at_depth(
            type_bing, geo_coordinate2d(midright, bottom), 1)
        self.assertEqual(quad_key(type_bing, 0, 1, 1), qk)
        qk = quad_key.get_key_from_longitude_latitude_at_depth(
            type_bing, geo_coordinate2d(right, bottom), 1)
        self.assertEqual(quad_key(type_bing, 0, 1, 1), qk)
        qk = quad_key.get_key_from_longitude_latitude_at_depth(
            type_bing, geo_coordinate2d(right, midbottom), 1)
        self.assertEqual(quad_key(type_bing, 0, 1, 1), qk)
        qk.get_geo_coordinate_bounds2d(bbox)
        diff = math.fabs(bbox.lower_left().get_longitude() - midright)
        self.assertTrue(2.0 > diff)
        diff = math.fabs(bbox.lower_left().get_latitude() - latitude(-85.0))
        self.assertTrue(2.0 > diff)
        diff = math.fabs(bbox.upper_right().get_longitude() - right)
        self.assertTrue(2.0 > diff)
        diff = math.fabs(bbox.upper_right().get_latitude() - midbottom)
        self.assertTrue(2.0 > diff)

    def test_get_keys_from_longitude_latitude_bounding_box(self):
        """
        Test to get the bounding box of a quadqk.
        """
        out_keys = quad_key.get_keys_from_longitude_latitude_bounding_box(
            type_bing,
            geo_coordinate_bounding_box2d(
                geo_coordinate2d(longitude(-180.0), latitude(+90.0)),
                geo_coordinate2d(longitude(+180.0), latitude(-90.0))), 0)
        self.assertEqual(1, out_keys.size())
        self.assertTrue(quad_key(type_bing, 0, 0, 0) in out_keys)

        out_keys = quad_key.get_keys_from_longitude_latitude_bounding_box(
            type_bing,
            geo_coordinate_bounding_box2d(
                geo_coordinate2d(longitude(-180.0), latitude(+90.0)),
                geo_coordinate2d(longitude(+180.0), latitude(-90.0))), 1)
        self.assertEqual(4, out_keys.size())
        self.assertTrue(quad_key(type_bing, 0, 0, 1) in out_keys)
        self.assertTrue(quad_key(type_bing, 0, 1, 1) in out_keys)
        self.assertTrue(quad_key(type_bing, 1, 0, 1) in out_keys)
        self.assertTrue(quad_key(type_bing, 1, 1, 1) in out_keys)

        out_keys = quad_key.get_keys_from_longitude_latitude_bounding_box(
            type_bing,
            geo_coordinate_bounding_box2d(
                geo_coordinate2d(longitude(-180.0), latitude(+0.35)),
                geo_coordinate2d(longitude(-0.36), latitude(+90.0))), 1)
        self.assertEqual(2, out_keys.size())
        self.assertTrue(quad_key(type_bing, 0, 0, 1) in out_keys)
        self.assertTrue(quad_key(type_bing, 1, 0, 1) in out_keys)

        out_keys = quad_key.get_keys_from_longitude_latitude_bounding_box(
            type_bing,
            geo_coordinate_bounding_box2d(
                geo_coordinate2d(longitude(-0.36), latitude(+0.36)),
                geo_coordinate2d(longitude(+0.36), latitude(+90.0))), 1)
        self.assertEqual(2, out_keys.size())
        self.assertTrue(quad_key(type_bing, 1, 0, 1) in out_keys)
        self.assertTrue(quad_key(type_bing, 1, 1, 1) in out_keys)

        out_keys = quad_key.get_keys_from_longitude_latitude_bounding_box(
            type_bing,
            geo_coordinate_bounding_box2d(
                geo_coordinate2d(longitude(-0.36), latitude(+0.35)),
                geo_coordinate2d(longitude(+0.36), latitude(+90.0))), 1)
        self.assertEqual(4, out_keys.size())
        self.assertTrue(quad_key(type_bing, 0, 0, 1) in out_keys)
        self.assertTrue(quad_key(type_bing, 0, 1, 1) in out_keys)
        self.assertTrue(quad_key(type_bing, 1, 0, 1) in out_keys)
        self.assertTrue(quad_key(type_bing, 1, 1, 1) in out_keys)

    def test_selected_cities(self):
        """
        Test a given set of known places make sure they work.
        """
        qk_type = type_bing

        # Chicago 41.822, -87.635
        depth = 16
        coords = geo_coordinate2d(longitude(-87.635), latitude(41.822))
        qk = quad_key.get_key_from_longitude_latitude_at_depth(qk_type,
                                                               coords,
                                                               depth)
        self.assertEqual("0302222310321132", qk.to_internal_string())
        bbox = geo_coordinate_bounding_box2d()
        qk.get_geo_coordinate_bounds2d(bbox)
        # Note that Bing will return a bounding box of all sides inclusive
        keys = quad_key.get_keys_from_longitude_latitude_bounding_box(
            qk_type, bbox, depth)
        self.assertEqual(4, keys.size())
        self.assertTrue(qk in keys)

        # Rio -43.1964,-22.9083
        depth = 17
        coords = geo_coordinate2d(longitude(-43.1964), latitude(-22.9083))
        qk = quad_key.get_key_from_longitude_latitude_at_depth(qk_type,
                                                               coords,
                                                               depth)
        self.assertEqual("21120001212232200", qk.to_internal_string())
        bbox = geo_coordinate_bounding_box2d()
        qk.get_geo_coordinate_bounds2d(bbox)
        # Note that Bing will return a bounding box of all sides inclusive
        keys = quad_key.get_keys_from_longitude_latitude_bounding_box(
            qk_type, bbox, depth)
        self.assertEqual(4, keys.size())
        self.assertTrue(qk in keys)

        # Helsinki 60.1708 N, 24.9375 E
        depth = 17
        coords = geo_coordinate2d(longitude(24.9375), latitude(60.1708))
        qk = quad_key.get_key_from_longitude_latitude_at_depth(qk_type,
                                                               coords,
                                                               depth)
        self.assertEqual("12012021101330131", qk.to_internal_string())
        bbox = geo_coordinate_bounding_box2d()
        qk.get_geo_coordinate_bounds2d(bbox)
        # Note that Bing will return a bounding box of all sides inclusive
        keys = quad_key.get_keys_from_longitude_latitude_bounding_box(
            qk_type, bbox, depth)
        self.assertEqual(4, keys.size())
        self.assertTrue(qk in keys)

        # Cape Town South Africa 33.9253 S, 18.4239 E
        depth = 17
        coords = geo_coordinate2d(longitude(18.4239), latitude(-33.9253))
        qk = quad_key.get_key_from_longitude_latitude_at_depth(qk_type,
                                                               coords,
                                                               depth)
        self.assertEqual("30023103202132011", qk.to_internal_string())
        bbox = geo_coordinate_bounding_box2d()
        qk.get_geo_coordinate_bounds2d(bbox)
        # Note that Bing will return a bounding box of all sides inclusive
        keys = quad_key.get_keys_from_longitude_latitude_bounding_box(
            qk_type, bbox, depth)
        self.assertEqual(4, keys.size())
        self.assertTrue(qk in keys)

        # Quito 0.2500 S, 78.5833 W
        depth = 17
        coords = geo_coordinate2d(longitude(-78.5836), latitude(-0.25))
        qk = quad_key.get_key_from_longitude_latitude_at_depth(qk_type,
                                                               coords,
                                                               depth)
        self.assertEqual("21001000002133122", qk.to_internal_string())
        bbox = geo_coordinate_bounding_box2d()
        qk.get_geo_coordinate_bounds2d(bbox)
        # Note that Bing will return a bounding box of all sides inclusive
        keys = quad_key.get_keys_from_longitude_latitude_bounding_box(
            qk_type, bbox, depth)
        self.assertEqual(4, keys.size())
        self.assertTrue(qk in keys)

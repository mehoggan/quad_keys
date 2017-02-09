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
    """
    Class for running unit tests.
    """

    def test_default_ctor(self):
        """
        Test default construction of quad_key using type_bing
        """
        quad_key = quad_key(type_bing)
        self.assertEqual(quad_key.getRow(), 0)
        self.assertEqual(quad_key.getCol(), 0)
        self.assertEqual(quad_key.getType(), type_bing)
        self.assertEqual(quad_key.toInternalString(), '')

    def test_is_valid(self):
        """
        See Testquad_key.test_is_valid
        """

    def test_is_root_key(self):
        """
        See Testquad_key.test_is_root_key
        """

    def test_get_parent(self):
        """
        Test to get parent of a generically formatted quad_key.
        """
        key0 = quad_key(type_bing, 0, 0, 1)
        key1 = quad_key(type_bing, 1, 0, 1)
        key2 = quad_key(type_bing, 1, 1, 1)
        key3 = quad_key(type_bing, 0, 1, 1)

        parent = quad_key(type_bing, 0, 0, 0)

        self.assertEqual(type_bing, key0.getType())
        self.assertEqual(type_bing, key1.getType())
        self.assertEqual(type_bing, key2.getType())
        self.assertEqual(type_bing, key3.getType())

        self.assertEqual(type_bing, parent.getType())

        self.assertEqual(key0.getParent(), parent)
        self.assertEqual(key1.getParent(), parent)
        self.assertEqual(key2.getParent(), parent)
        self.assertEqual(key3.getParent(), parent)

        key0 = quad_key(type_bing, 5, 6, 3)
        key1 = quad_key(type_bing, 4, 6, 3)
        key2 = quad_key(type_bing, 4, 7, 3)
        key3 = quad_key(type_bing, 5, 7, 3)

        parent = quad_key(type_bing, 2, 3, 2)

        self.assertEqual(type_bing, key0.getType())
        self.assertEqual(type_bing, key1.getType())
        self.assertEqual(type_bing, key2.getType())
        self.assertEqual(type_bing, key3.getType())

        self.assertEqual(key0.getParent(), parent)
        self.assertEqual(key1.getParent(), parent)
        self.assertEqual(key2.getParent(), parent)
        self.assertEqual(key3.getParent(), parent)

    def test_is_my_ancestor(self):
        """
        Checks to see if specified quadkey up in the hierarchy is an "ancestor"
        of the given quad_key.
        """
        none = quad_key()
        self.assertFalse(none.isMyAncestor(quad_key()))

        quad_key = quad_key(type_bing, 5, 7, 3)
        self.assertFalse(quad_key.isMyAncestor(quad_key()))
        self.assertFalse(quad_key.isMyAncestor(quad_key(type_osgeo, 2, 3, 2)))
        self.assertFalse(quad_key.isMyAncestor(quad_key(type_osgeo, 0, 0, 0)))
        self.assertFalse(quad_key.isMyAncestor(quad_key(type_bing, 5, 7, 3)))
        self.assertTrue(quad_key.isMyAncestor(quad_key(type_bing, 2, 3, 2)))
        self.assertTrue(quad_key.isMyAncestor(quad_key(type_bing, 0, 0, 0)))

    def test_get_ancestor(self):
        """
        Gets the ancestor up the tree according to a delta provided.
        """
        quad_key = quad_key(type_bing, 0, 7, 3)
        ancestor = quad_key(type_bing, 0, 1, 1)
        self.assertTrue(quad_key.getAncestor(2), ancestor)
        quad_key = quad_key(type_bing, 4, 31, 5)
        ancestor = quad_key(type_bing, 0, 3, 2)
        self.assertTrue(quad_key.getAncestor(4), ancestor)
        quad_key = quad_key(type_bing, 4, 31, 5)
        ancestor = quad_key(type_bing, 0, 3, 2)
        self.assertTrue(quad_key.getAncestor(3), ancestor)
        quad_key = quad_key(type_bing, 4, 31, 5)
        ancestor = quad_key(type_bing, 1, 7, 3)
        self.assertTrue(quad_key.getAncestor(2), ancestor)

    def test_get_child(self):
        """
        Get a single child NE, SE, NW, SW
        """
        self.assertEqual(quad_key(),
                         quad_key().getChild(quad_key.Quadrant_NorthWest))
        maxdepthbing = quad_key.maxDepth(type_bing)
        self.assertEqual(quad_key(),
                         quad_key(type_bing, 0, 0, maxdepthbing).getChild(
                             quad_key.Quadrant_NorthEast))

        quad_key = quad_key(type_bing, 0, 0, 3)
        self.assertEqual(quad_key(type_bing, 1, 0, 4),
                         quad_key.getChild(quad_key.Quadrant_NorthWest))
        self.assertEqual(quad_key(type_bing, 1, 1, 4),
                         quad_key.getChild(quad_key.Quadrant_NorthEast))
        self.assertEqual(quad_key(type_bing, 0, 1, 4),
                         quad_key.getChild(quad_key.Quadrant_SouthEast))
        self.assertEqual(quad_key(type_bing, 0, 0, 4),
                         quad_key.getChild(quad_key.Quadrant_SouthWest))

        quad_key = quad_key(type_bing, 2, 3, 3)
        self.assertEqual(quad_key(type_bing, 5, 6, 4),
                         quad_key.getChild(quad_key.Quadrant_NorthWest))
        self.assertEqual(quad_key(type_bing, 5, 7, 4),
                         quad_key.getChild(quad_key.Quadrant_NorthEast))
        self.assertEqual(quad_key(type_bing, 4, 7, 4),
                         quad_key.getChild(quad_key.Quadrant_SouthEast))
        self.assertEqual(quad_key(type_bing, 4, 6, 4),
                         quad_key.getChild(quad_key.Quadrant_SouthWest))

    def test_get_children(self):
        """
        Get all the childern of a quad_key.
        """
        quad_key = quad_key()
        vec = quad_key.getChildren()
        self.assertEqual(0, len(vec))

        quad_key = quad_key(type_bing, 0, 0, 1)
        vec = quad_key.getChildren()
        self.assertEqual(4, len(vec))
        self.assertTrue(quad_key(type_bing, 0, 0, 2) in vec)
        self.assertTrue(quad_key(type_bing, 0, 1, 2) in vec)
        self.assertTrue(quad_key(type_bing, 1, 0, 2) in vec)
        self.assertTrue(quad_key(type_bing, 1, 1, 2) in vec)

        quad_key = quad_key(type_bing, 0, 1, 1)
        vec = quad_key.getChildren()
        self.assertEqual(4, len(vec))
        self.assertTrue(quad_key(type_bing, 0, 2, 2) in vec)
        self.assertTrue(quad_key(type_bing, 0, 3, 2) in vec)
        self.assertTrue(quad_key(type_bing, 1, 2, 2) in vec)
        self.assertTrue(quad_key(type_bing, 1, 3, 2) in vec)

        quad_key = quad_key(type_bing, 1, 0, 1)
        vec = quad_key.getChildren()
        self.assertEqual(4, len(vec))
        self.assertTrue(quad_key(type_bing, 2, 0, 2) in vec)
        self.assertTrue(quad_key(type_bing, 2, 1, 2) in vec)
        self.assertTrue(quad_key(type_bing, 3, 0, 2) in vec)
        self.assertTrue(quad_key(type_bing, 3, 1, 2) in vec)

        quad_key = quad_key(type_bing, 1, 1, 1)
        vec = quad_key.getChildren()
        self.assertEqual(4, len(vec))
        self.assertTrue(quad_key(type_bing, 2, 2, 2) in vec)
        self.assertTrue(quad_key(type_bing, 2, 3, 2) in vec)
        self.assertTrue(quad_key(type_bing, 3, 2, 2) in vec)
        self.assertTrue(quad_key(type_bing, 3, 3, 2) in vec)

    def test_get_descendants(self):
        """
        Get all the defendants at some delta in the tree.
        """
        bing_max_depth = quad_key.maxDepth(type_bing)
        quad_key = quad_key(type_bing, 0, 0, bing_max_depth - 3)

        vec = quad_key.getDescendants(4)
        self.assertEqual(0, len(vec))

        none = quad_key()
        vec = none.getDescendants(1)
        self.assertEqual(0, len(vec))

        quad_key = quad_key(type_bing, 0, 0, 0)
        vec = quad_key.getDescendants(0)
        self.assertEqual(0, len(vec))

        quad_key = quad_key(type_bing, 0, 0, 0)
        vec = quad_key.getDescendants(1)
        self.assertEqual(4, len(vec))
        self.assertTrue(quad_key(type_bing, 0, 0, 1) in vec)
        self.assertTrue(quad_key(type_bing, 0, 1, 1) in vec)
        self.assertTrue(quad_key(type_bing, 1, 0, 1) in vec)
        self.assertTrue(quad_key(type_bing, 1, 1, 1) in vec)

        vec = quad_key.getDescendants(2)
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

        vec = quad_key.getDescendants(3)
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
        quad_key = quad_key()
        vec = quad_key.getSiblings()
        self.assertEqual(0, len(vec))

        quad_key = quad_key(type_bing, 0, 0, 1)
        vec = quad_key.getSiblings()
        self.assertEqual(3, len(vec))
        self.assertTrue(quad_key(type_bing, 0, 1, 1) in vec)
        self.assertTrue(quad_key(type_bing, 1, 1, 1) in vec)
        self.assertTrue(quad_key(type_bing, 1, 0, 1) in vec)

    def test_get_neighbors(self):
        """
        Test to get the neighbors of a given quadquad_key.
        """
        vec = quad_key().getNeighbors()
        self.assertEqual(0, len(vec))

        vec = quad_key(type_bing, 0, 0, 0).getNeighbors()
        self.assertEqual(0, len(vec))

        vec = quad_key(type_bing, 0, 0, 2).getNeighbors()
        self.assertEqual(5, len(vec))
        self.assertTrue(quad_key(type_bing, 0, 1, 2) in vec)
        self.assertTrue(quad_key(type_bing, 1, 1, 2) in vec)
        self.assertTrue(quad_key(type_bing, 1, 0, 2) in vec)
        self.assertTrue(quad_key(type_bing, 0, 3, 2) in vec)
        self.assertTrue(quad_key(type_bing, 1, 3, 2) in vec)

        vec = quad_key(type_bing, 0, 1, 2).getNeighbors()
        self.assertEqual(5, len(vec))
        self.assertTrue(quad_key(type_bing, 0, 0, 2) in vec)
        self.assertTrue(quad_key(type_bing, 1, 0, 2) in vec)
        self.assertTrue(quad_key(type_bing, 1, 1, 2) in vec)
        self.assertTrue(quad_key(type_bing, 1, 2, 2) in vec)
        self.assertTrue(quad_key(type_bing, 0, 2, 2) in vec)

        vec = quad_key(type_bing, 0, 2, 2).getNeighbors()
        self.assertEqual(5, len(vec))
        self.assertTrue(quad_key(type_bing, 0, 1, 2) in vec)
        self.assertTrue(quad_key(type_bing, 1, 1, 2) in vec)
        self.assertTrue(quad_key(type_bing, 1, 2, 2) in vec)
        self.assertTrue(quad_key(type_bing, 1, 3, 2) in vec)
        self.assertTrue(quad_key(type_bing, 0, 3, 2) in vec)

        vec = quad_key(type_bing, 0, 3, 2).getNeighbors()
        self.assertEqual(5, len(vec))
        self.assertTrue(quad_key(type_bing, 0, 2, 2) in vec)
        self.assertTrue(quad_key(type_bing, 1, 2, 2) in vec)
        self.assertTrue(quad_key(type_bing, 1, 3, 2) in vec)
        self.assertTrue(quad_key(type_bing, 1, 0, 2) in vec)
        self.assertTrue(quad_key(type_bing, 0, 0, 2) in vec)

        vec = quad_key(type_bing, 1, 0, 2).getNeighbors()
        self.assertEqual(8, len(vec))
        self.assertTrue(quad_key(type_bing, 0, 0, 2) in vec)
        self.assertTrue(quad_key(type_bing, 0, 1, 2) in vec)
        self.assertTrue(quad_key(type_bing, 1, 1, 2) in vec)
        self.assertTrue(quad_key(type_bing, 2, 1, 2) in vec)
        self.assertTrue(quad_key(type_bing, 2, 0, 2) in vec)
        self.assertTrue(quad_key(type_bing, 2, 3, 2) in vec)
        self.assertTrue(quad_key(type_bing, 1, 3, 2) in vec)
        self.assertTrue(quad_key(type_bing, 0, 3, 2) in vec)

        vec = quad_key(type_bing, 1, 1, 2).getNeighbors()
        self.assertEqual(8, len(vec))
        self.assertTrue(quad_key(type_bing, 1, 0, 2) in vec)
        self.assertTrue(quad_key(type_bing, 0, 0, 2) in vec)
        self.assertTrue(quad_key(type_bing, 0, 1, 2) in vec)
        self.assertTrue(quad_key(type_bing, 2, 2, 2) in vec)
        self.assertTrue(quad_key(type_bing, 2, 1, 2) in vec)
        self.assertTrue(quad_key(type_bing, 2, 0, 2) in vec)
        self.assertTrue(quad_key(type_bing, 0, 2, 2) in vec)
        self.assertTrue(quad_key(type_bing, 1, 2, 2) in vec)

        vec = quad_key(type_bing, 1, 2, 2).getNeighbors()
        self.assertEqual(8, len(vec))
        self.assertTrue(quad_key(type_bing, 1, 1, 2) in vec)
        self.assertTrue(quad_key(type_bing, 0, 1, 2) in vec)
        self.assertTrue(quad_key(type_bing, 0, 2, 2) in vec)
        self.assertTrue(quad_key(type_bing, 2, 3, 2) in vec)
        self.assertTrue(quad_key(type_bing, 2, 2, 2) in vec)
        self.assertTrue(quad_key(type_bing, 2, 1, 2) in vec)
        self.assertTrue(quad_key(type_bing, 0, 3, 2) in vec)
        self.assertTrue(quad_key(type_bing, 1, 3, 2) in vec)

        vec = quad_key(type_bing, 1, 3, 2).getNeighbors()
        self.assertEqual(8, len(vec))
        self.assertTrue(quad_key(type_bing, 1, 2, 2) in vec)
        self.assertTrue(quad_key(type_bing, 0, 2, 2) in vec)
        self.assertTrue(quad_key(type_bing, 0, 3, 2) in vec)
        self.assertTrue(quad_key(type_bing, 2, 0, 2) in vec)
        self.assertTrue(quad_key(type_bing, 2, 3, 2) in vec)
        self.assertTrue(quad_key(type_bing, 2, 2, 2) in vec)
        self.assertTrue(quad_key(type_bing, 0, 0, 2) in vec)
        self.assertTrue(quad_key(type_bing, 1, 0, 2) in vec)

        vec = quad_key(type_bing, 4, 7, 3).getNeighbors()
        self.assertEqual(8, len(vec))
        self.assertTrue(quad_key(type_bing, 3, 7, 3) in vec)
        self.assertTrue(quad_key(type_bing, 3, 6, 3) in vec)
        self.assertTrue(quad_key(type_bing, 4, 6, 3) in vec)
        self.assertTrue(quad_key(type_bing, 5, 6, 3) in vec)
        self.assertTrue(quad_key(type_bing, 5, 7, 3) in vec)
        self.assertTrue(quad_key(type_bing, 5, 0, 3) in vec)
        self.assertTrue(quad_key(type_bing, 4, 0, 3) in vec)
        self.assertTrue(quad_key(type_bing, 3, 0, 3) in vec)

        vec = quad_key(type_bing, 4, 0, 3).getNeighbors()
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
        root = quad_key.fromInternalString(type_bing, "")
        self.assertEqual(0, root.getRow())
        self.assertEqual(0, root.getCol())
        self.assertEqual(0, root.getDepth())

        quad_key = quad_key.fromInternalString(type_bing, "0")
        self.assertEqual(1, quad_key.getRow())
        self.assertEqual(0, quad_key.getCol())
        self.assertEqual(1, quad_key.getDepth())
        self.assertEqual("0", quad_key.toInternalString())
        quad_key = quad_key.fromInternalString(type_bing, "1")
        self.assertEqual(1, quad_key.getRow())
        self.assertEqual(1, quad_key.getCol())
        self.assertEqual(1, quad_key.getDepth())
        self.assertEqual("1", quad_key.toInternalString())
        quad_key = quad_key.fromInternalString(type_bing, "2")
        self.assertEqual(0, quad_key.getRow())
        self.assertEqual(0, quad_key.getCol())
        self.assertEqual(1, quad_key.getDepth())
        self.assertEqual("2", quad_key.toInternalString())
        quad_key = quad_key.fromInternalString(type_bing, "3")
        self.assertEqual(0, quad_key.getRow())
        self.assertEqual(1, quad_key.getCol())
        self.assertEqual(1, quad_key.getDepth())
        self.assertEqual("3", quad_key.toInternalString())

        quad_key = quad_key.fromInternalString(type_bing, "00")
        self.assertEqual(3, quad_key.getRow())
        self.assertEqual(0, quad_key.getCol())
        self.assertEqual(2, quad_key.getDepth())
        self.assertEqual("00", quad_key.toInternalString())
        quad_key = quad_key.fromInternalString(type_bing, "01")
        self.assertEqual(3, quad_key.getRow())
        self.assertEqual(1, quad_key.getCol())
        self.assertEqual(2, quad_key.getDepth())
        self.assertEqual("01", quad_key.toInternalString())
        quad_key = quad_key.fromInternalString(type_bing, "02")
        self.assertEqual(2, quad_key.getRow())
        self.assertEqual(0, quad_key.getCol())
        self.assertEqual(2, quad_key.getDepth())
        self.assertEqual("02", quad_key.toInternalString())
        quad_key = quad_key.fromInternalString(type_bing, "03")
        self.assertEqual(2, quad_key.getRow())
        self.assertEqual(1, quad_key.getCol())
        self.assertEqual(2, quad_key.getDepth())
        self.assertEqual("03", quad_key.toInternalString())
        quad_key = quad_key.fromInternalString(type_bing, "10")
        self.assertEqual(3, quad_key.getRow())
        self.assertEqual(2, quad_key.getCol())
        self.assertEqual(2, quad_key.getDepth())
        self.assertEqual("10", quad_key.toInternalString())
        quad_key = quad_key.fromInternalString(type_bing, "11")
        self.assertEqual(3, quad_key.getRow())
        self.assertEqual(3, quad_key.getCol())
        self.assertEqual(2, quad_key.getDepth())
        self.assertEqual("11", quad_key.toInternalString())
        quad_key = quad_key.fromInternalString(type_bing, "12")
        self.assertEqual(2, quad_key.getRow())
        self.assertEqual(2, quad_key.getCol())
        self.assertEqual(2, quad_key.getDepth())
        self.assertEqual("12", quad_key.toInternalString())
        quad_key = quad_key.fromInternalString(type_bing, "13")
        self.assertEqual(2, quad_key.getRow())
        self.assertEqual(3, quad_key.getCol())
        self.assertEqual(2, quad_key.getDepth())
        self.assertEqual("13", quad_key.toInternalString())
        quad_key = quad_key.fromInternalString(type_bing, "20")
        self.assertEqual(1, quad_key.getRow())
        self.assertEqual(0, quad_key.getCol())
        self.assertEqual(2, quad_key.getDepth())
        self.assertEqual("20", quad_key.toInternalString())
        quad_key = quad_key.fromInternalString(type_bing, "21")
        self.assertEqual(1, quad_key.getRow())
        self.assertEqual(1, quad_key.getCol())
        self.assertEqual(2, quad_key.getDepth())
        self.assertEqual("21", quad_key.toInternalString())
        quad_key = quad_key.fromInternalString(type_bing, "22")
        self.assertEqual(0, quad_key.getRow())
        self.assertEqual(0, quad_key.getCol())
        self.assertEqual(2, quad_key.getDepth())
        self.assertEqual("22", quad_key.toInternalString())
        quad_key = quad_key.fromInternalString(type_bing, "23")
        self.assertEqual(0, quad_key.getRow())
        self.assertEqual(1, quad_key.getCol())
        self.assertEqual(2, quad_key.getDepth())
        self.assertEqual("23", quad_key.toInternalString())
        quad_key = quad_key.fromInternalString(type_bing, "30")
        self.assertEqual(1, quad_key.getRow())
        self.assertEqual(2, quad_key.getCol())
        self.assertEqual(2, quad_key.getDepth())
        self.assertEqual("30", quad_key.toInternalString())
        quad_key = quad_key.fromInternalString(type_bing, "31")
        self.assertEqual(1, quad_key.getRow())
        self.assertEqual(3, quad_key.getCol())
        self.assertEqual(2, quad_key.getDepth())
        self.assertEqual("31", quad_key.toInternalString())
        quad_key = quad_key.fromInternalString(type_bing, "32")
        self.assertEqual(0, quad_key.getRow())
        self.assertEqual(2, quad_key.getCol())
        self.assertEqual(2, quad_key.getDepth())
        self.assertEqual("32", quad_key.toInternalString())
        quad_key = quad_key.fromInternalString(type_bing, "33")
        self.assertEqual(0, quad_key.getRow())
        self.assertEqual(3, quad_key.getCol())
        self.assertEqual(2, quad_key.getDepth())
        self.assertEqual("33", quad_key.toInternalString())

    def test_get_geo_coordinate_bounds_2d(self):
        """
        Test to get geographic bounds of quadquad_key.
        """
        bbox = geo_coordinate_bounding_box2d()

        quad_key = quad_key.fromInternalString(type_bing, "")
        quad_key.getGeoCoordinateBounds2d(bbox)
        self.assertAlmostEqual(-180.0, bbox.lowerLeft().longitude().val())
        self.assertAlmostEqual(-84.9283209, bbox.lowerLeft().latitude().val())
        self.assertAlmostEqual(178.593750, bbox.upperRight().longitude().val())
        self.assertAlmostEqual(85.05112877, bbox.upperRight().latitude().val())

    def test_get_key_from_longitude_latitude_at_depth_to_bounds(self):
        """
        Test to get a quadkey from longitude and latitude and then get bounds.
        """
        bbox = geo_coordinate_bounding_box2d()

        quad_key = quad_key.getKeyFromlongitudelatitudeAtDepth(
            type_bing, geo_coordinate2d(longitude(-180.0),
                                       latitude(-84.0)), 0)
        self.assertEqual(quad_key(type_bing, 0, 0, 0), quad_key)
        quad_key.getGeoCoordinateBounds2d(bbox)
        diff = math.fabs(bbox.lowerLeft().longitude() - longitude(-180.0))
        self.assertTrue(2.0 > diff)
        diff = math.fabs(bbox.lowerLeft().latitude() - latitude(-85.0))
        self.assertTrue(2.0 > diff)
        diff = math.fabs(bbox.upperRight().longitude() - longitude(+180.0))
        self.assertTrue(2.0 > diff)
        diff = math.fabs(bbox.upperRight().latitude() - latitude(+85.0))
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

        quad_key = quad_key.getKeyFromlongitudelatitudeAtDepth(
            type_bing, geo_coordinate2d(left, top), 1)
        self.assertEqual(quad_key(type_bing, 1, 0, 1), quad_key)
        quad_key = quad_key.getKeyFromlongitudelatitudeAtDepth(
            type_bing, geo_coordinate2d(left, midtop), 1)
        self.assertEqual(quad_key(type_bing, 1, 0, 1), quad_key)
        quad_key = quad_key.getKeyFromlongitudelatitudeAtDepth(
            type_bing, geo_coordinate2d(midleft, midtop), 1)
        self.assertEqual(quad_key(type_bing, 1, 0, 1), quad_key)
        quad_key = quad_key.getKeyFromlongitudelatitudeAtDepth(
            type_bing, geo_coordinate2d(midleft, top), 1)
        self.assertEqual(quad_key(type_bing, 1, 0, 1), quad_key)
        quad_key.getGeoCoordinateBounds2d(bbox)
        diff = math.fabs(bbox.lowerLeft().longitude() - left)
        self.assertTrue(2.0 > diff)
        diff = math.fabs(bbox.lowerLeft().latitude() - midtop)
        self.assertTrue(2.0 > diff)
        diff = math.fabs(bbox.upperRight().longitude() - midleft)
        self.assertTrue(2.0 > diff)
        diff = math.fabs(bbox.upperRight().latitude() - latitude(+85.0))
        self.assertTrue(2.0 > diff)

        quad_key = quad_key.getKeyFromlongitudelatitudeAtDepth(
            type_bing, geo_coordinate2d(midright, top), 1)
        self.assertEqual(quad_key(type_bing, 1, 1, 1), quad_key)
        quad_key = quad_key.getKeyFromlongitudelatitudeAtDepth(
            type_bing, geo_coordinate2d(midright, midtop), 1)
        self.assertEqual(quad_key(type_bing, 1, 1, 1), quad_key)
        quad_key = quad_key.getKeyFromlongitudelatitudeAtDepth(
            type_bing, geo_coordinate2d(right, midtop), 1)
        self.assertEqual(quad_key(type_bing, 1, 1, 1), quad_key)
        quad_key = quad_key.getKeyFromlongitudelatitudeAtDepth(
            type_bing, geo_coordinate2d(right, top), 1)
        self.assertEqual(quad_key(type_bing, 1, 1, 1), quad_key)
        quad_key.getGeoCoordinateBounds2d(bbox)
        diff = math.fabs(bbox.lowerLeft().longitude() - midright)
        self.assertTrue(2.0 > diff)
        diff = math.fabs(bbox.lowerLeft().latitude() - midtop)
        self.assertTrue(2.0 > diff)
        diff = math.fabs(bbox.upperRight().longitude() - right)
        self.assertTrue(2.0 > diff)
        diff = math.fabs(bbox.upperRight().latitude() - latitude(+85.0))
        self.assertTrue(2.0 > diff)

        quad_key = quad_key.getKeyFromlongitudelatitudeAtDepth(
            type_bing, geo_coordinate2d(left, midbottom), 1)
        self.assertEqual(quad_key(type_bing, 0, 0, 1), quad_key)
        quad_key = quad_key.getKeyFromlongitudelatitudeAtDepth(
            type_bing, geo_coordinate2d(left, bottom), 1)
        self.assertEqual(quad_key(type_bing, 0, 0, 1), quad_key)
        quad_key = quad_key.getKeyFromlongitudelatitudeAtDepth(
            type_bing, geo_coordinate2d(midleft, bottom), 1)
        self.assertEqual(quad_key(type_bing, 0, 0, 1), quad_key)
        quad_key = quad_key.getKeyFromlongitudelatitudeAtDepth(
            type_bing, geo_coordinate2d(midleft, midbottom), 1)
        self.assertEqual(quad_key(type_bing, 0, 0, 1), quad_key)
        quad_key.getGeoCoordinateBounds2d(bbox)
        diff = math.fabs(bbox.lowerLeft().longitude() - left)
        self.assertTrue(2.0 > diff)
        diff = math.fabs(bbox.lowerLeft().latitude() - latitude(-85.0))
        self.assertTrue(2.0 > diff)
        diff = math.fabs(bbox.upperRight().longitude() - midleft)
        self.assertTrue(2.0 > diff)
        diff = math.fabs(bbox.upperRight().latitude() - midbottom)
        self.assertTrue(2.0 > diff)

        quad_key = quad_key.getKeyFromlongitudelatitudeAtDepth(
            type_bing, geo_coordinate2d(midright, midbottom), 1)
        self.assertEqual(quad_key(type_bing, 0, 1, 1), quad_key)
        quad_key = quad_key.getKeyFromlongitudelatitudeAtDepth(
            type_bing, geo_coordinate2d(midright, bottom), 1)
        self.assertEqual(quad_key(type_bing, 0, 1, 1), quad_key)
        quad_key = quad_key.getKeyFromlongitudelatitudeAtDepth(
            type_bing, geo_coordinate2d(right, bottom), 1)
        self.assertEqual(quad_key(type_bing, 0, 1, 1), quad_key)
        quad_key = quad_key.getKeyFromlongitudelatitudeAtDepth(
            type_bing, geo_coordinate2d(right, midbottom), 1)
        self.assertEqual(quad_key(type_bing, 0, 1, 1), quad_key)
        quad_key.getGeoCoordinateBounds2d(bbox)
        diff = math.fabs(bbox.lowerLeft().longitude() - midright)
        self.assertTrue(2.0 > diff)
        diff = math.fabs(bbox.lowerLeft().latitude() - latitude(-85.0))
        self.assertTrue(2.0 > diff)
        diff = math.fabs(bbox.upperRight().longitude() - right)
        self.assertTrue(2.0 > diff)
        diff = math.fabs(bbox.upperRight().latitude() - midbottom)
        self.assertTrue(2.0 > diff)

    def test_get_keys_from_longitude_latitude_bounding_box(self):
        """
        Test to get the bounding box of a quadquad_key.
        """
        out_keys = quad_key.getKeysFromlongitudelatitudeBoundingBox(
            type_bing,
            geo_coordinate_bounding_box2d(
                geo_coordinate2d(longitude(-180.0), latitude(+90.0)),
                geo_coordinate2d(longitude(+180.0), latitude(-90.0))), 0)
        self.assertEqual(1, out_keys.size())
        self.assertTrue(quad_key(type_bing, 0, 0, 0) in out_keys)

        out_keys = quad_key.getKeysFromlongitudelatitudeBoundingBox(
            type_bing,
            geo_coordinate_bounding_box2d(
                geo_coordinate2d(longitude(-180.0), latitude(+90.0)),
                geo_coordinate2d(longitude(+180.0), latitude(-90.0))), 1)
        self.assertEqual(4, out_keys.size())
        self.assertTrue(quad_key(type_bing, 0, 0, 1) in out_keys)
        self.assertTrue(quad_key(type_bing, 0, 1, 1) in out_keys)
        self.assertTrue(quad_key(type_bing, 1, 0, 1) in out_keys)
        self.assertTrue(quad_key(type_bing, 1, 1, 1) in out_keys)

        out_keys = quad_key.getKeysFromlongitudelatitudeBoundingBox(
            type_bing,
            geo_coordinate_bounding_box2d(
                geo_coordinate2d(longitude(-180.0), latitude(+0.35)),
                geo_coordinate2d(longitude(-0.36), latitude(+90.0))), 1)
        self.assertEqual(2, out_keys.size())
        self.assertTrue(quad_key(type_bing, 0, 0, 1) in out_keys)
        self.assertTrue(quad_key(type_bing, 1, 0, 1) in out_keys)

        out_keys = quad_key.getKeysFromlongitudelatitudeBoundingBox(
            type_bing,
            geo_coordinate_bounding_box2d(
                geo_coordinate2d(longitude(-0.36), latitude(+0.36)),
                geo_coordinate2d(longitude(+0.36), latitude(+90.0))), 1)
        self.assertEqual(2, out_keys.size())
        self.assertTrue(quad_key(type_bing, 1, 0, 1) in out_keys)
        self.assertTrue(quad_key(type_bing, 1, 1, 1) in out_keys)

        out_keys = quad_key.getKeysFromlongitudelatitudeBoundingBox(
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
        quad_key = quad_key.getKeyFromlongitudelatitudeAtDepth(qk_type, coords,
                                                              depth)
        self.assertEqual("0302222310321132", quad_key.toInternalString())
        bbox = geo_coordinate_bounding_box2d()
        quad_key.getGeoCoordinateBounds2d(bbox)
        # Note that Bing will return a bounding box of all sides inclusive
        keys = quad_key.getKeysFromlongitudelatitudeBoundingBox(qk_type, bbox,
                                                               depth)
        self.assertEqual(4, keys.size())
        self.assertTrue(quad_key in keys)

        # Rio -43.1964,-22.9083
        depth = 17
        coords = geo_coordinate2d(longitude(-43.1964), latitude(-22.9083))
        quad_key = quad_key.getKeyFromlongitudelatitudeAtDepth(qk_type, coords,
                                                              depth)
        self.assertEqual("21120001212232200", quad_key.toInternalString())
        bbox = geo_coordinate_bounding_box2d()
        quad_key.getGeoCoordinateBounds2d(bbox)
        # Note that Bing will return a bounding box of all sides inclusive
        keys = quad_key.getKeysFromlongitudelatitudeBoundingBox(qk_type, bbox,
                                                               depth)
        self.assertEqual(4, keys.size())
        self.assertTrue(quad_key in keys)

        # Helsinki 60.1708 N, 24.9375 E
        depth = 17
        coords = geo_coordinate2d(longitude(24.9375), latitude(60.1708))
        quad_key = quad_key.getKeyFromlongitudelatitudeAtDepth(qk_type, coords,
                                                              depth)
        self.assertEqual("12012021101330131", quad_key.toInternalString())
        bbox = geo_coordinate_bounding_box2d()
        quad_key.getGeoCoordinateBounds2d(bbox)
        # Note that Bing will return a bounding box of all sides inclusive
        keys = quad_key.getKeysFromlongitudelatitudeBoundingBox(qk_type, bbox,
                                                               depth)
        self.assertEqual(4, keys.size())
        self.assertTrue(quad_key in keys)

        # Cape Town South Africa 33.9253 S, 18.4239 E
        depth = 17
        coords = geo_coordinate2d(longitude(18.4239), latitude(-33.9253))
        quad_key = quad_key.getKeyFromlongitudelatitudeAtDepth(qk_type, coords,
                                                              depth)
        self.assertEqual("30023103202132011", quad_key.toInternalString())
        bbox = geo_coordinate_bounding_box2d()
        quad_key.getGeoCoordinateBounds2d(bbox)
        # Note that Bing will return a bounding box of all sides inclusive
        keys = quad_key.getKeysFromlongitudelatitudeBoundingBox(qk_type, bbox,
                                                               depth)
        self.assertEqual(4, keys.size())
        self.assertTrue(quad_key in keys)

        # Quito 0.2500 S, 78.5833 W
        depth = 17
        coords = geo_coordinate2d(longitude(-78.5836), latitude(-0.25))
        quad_key = quad_key.getKeyFromlongitudelatitudeAtDepth(qk_type, coords,
                                                              depth)
        self.assertEqual("21001000002133122", quad_key.toInternalString())
        bbox = geo_coordinate_bounding_box2d()
        quad_key.getGeoCoordinateBounds2d(bbox)
        # Note that Bing will return a bounding box of all sides inclusive
        keys = quad_key.getKeysFromlongitudelatitudeBoundingBox(qk_type, bbox,
                                                               depth)
        self.assertEqual(4, keys.size())
        self.assertTrue(quad_key in keys)

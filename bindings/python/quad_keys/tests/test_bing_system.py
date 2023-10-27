"""
Unit Tests for Bing System
"""

from __future__ import print_function

import math
import unittest

from quad_keys.quad_keys import QuadKey
from quad_keys.quad_keys import Type_Bing
from quad_keys.quad_keys import Type_OsGeo
from quad_keys.quad_keys import GeoCoordinate2d
from quad_keys.quad_keys import GeoCoordinateBoundingBox2d
from quad_keys.quad_keys import Longitude
from quad_keys.quad_keys import Latitude


class TestBingSystem(unittest.TestCase):
    """Class for running unit tests."""

    def test_default_ctor(self):
        """Test default construction of quad_key using Type_Bing."""
        qk = QuadKey(Type_Bing)
        self.assertEqual(qk.get_row(), 0)
        self.assertEqual(qk.get_col(), 0)
        self.assertEqual(qk.get_type(), Type_Bing)
        self.assertEqual(qk.to_internal_string(), '')

    def test_is_valid(self):
        """See Testqk.test_is_valid."""

    def test_is_root_key(self):
        """See Testqk.test_is_root_key."""

    def test_get_parent(self):
        """Test to get parent of a generically formatted qk."""
        key0 = QuadKey(Type_Bing, 0, 0, 1)
        key1 = QuadKey(Type_Bing, 1, 0, 1)
        key2 = QuadKey(Type_Bing, 1, 1, 1)
        key3 = QuadKey(Type_Bing, 0, 1, 1)

        parent = QuadKey(Type_Bing, 0, 0, 0)

        self.assertEqual(Type_Bing, key0.get_type())
        self.assertEqual(Type_Bing, key1.get_type())
        self.assertEqual(Type_Bing, key2.get_type())
        self.assertEqual(Type_Bing, key3.get_type())

        self.assertEqual(Type_Bing, parent.get_type())

        self.assertEqual(key0.get_parent(), parent)
        self.assertEqual(key1.get_parent(), parent)
        self.assertEqual(key2.get_parent(), parent)
        self.assertEqual(key3.get_parent(), parent)

        key0 = QuadKey(Type_Bing, 5, 6, 3)
        key1 = QuadKey(Type_Bing, 4, 6, 3)
        key2 = QuadKey(Type_Bing, 4, 7, 3)
        key3 = QuadKey(Type_Bing, 5, 7, 3)

        parent = QuadKey(Type_Bing, 2, 3, 2)

        self.assertEqual(Type_Bing, key0.get_type())
        self.assertEqual(Type_Bing, key1.get_type())
        self.assertEqual(Type_Bing, key2.get_type())
        self.assertEqual(Type_Bing, key3.get_type())

        self.assertEqual(key0.get_parent(), parent)
        self.assertEqual(key1.get_parent(), parent)
        self.assertEqual(key2.get_parent(), parent)
        self.assertEqual(key3.get_parent(), parent)

    def test_is_my_ancestor(self):
        """Checks to see if specified quadkey up in the hierarchy is an
        "ancestor" of the given qk.
        """
        none = QuadKey()
        self.assertFalse(none.is_my_ancestor(QuadKey()))

        qk = QuadKey(Type_Bing, 5, 7, 3)
        self.assertFalse(qk.is_my_ancestor(QuadKey()))
        self.assertFalse(qk.is_my_ancestor(QuadKey(Type_OsGeo, 2, 3, 2)))
        self.assertFalse(qk.is_my_ancestor(QuadKey(Type_OsGeo, 0, 0, 0)))
        self.assertFalse(qk.is_my_ancestor(QuadKey(Type_Bing, 5, 7, 3)))
        self.assertTrue(qk.is_my_ancestor(QuadKey(Type_Bing, 2, 3, 2)))
        self.assertTrue(qk.is_my_ancestor(QuadKey(Type_Bing, 0, 0, 0)))

    def test_get_ancestor(self):
        """Gets the ancestor up the tree according to a delta provided."""
        qk = QuadKey(Type_Bing, 0, 7, 3)
        ancestor = QuadKey(Type_Bing, 0, 1, 1)
        self.assertTrue(qk.get_ancestor(2), ancestor)
        qk = QuadKey(Type_Bing, 4, 31, 5)
        ancestor = QuadKey(Type_Bing, 0, 3, 2)
        self.assertTrue(qk.get_ancestor(4), ancestor)
        qk = QuadKey(Type_Bing, 4, 31, 5)
        ancestor = QuadKey(Type_Bing, 0, 3, 2)
        self.assertTrue(qk.get_ancestor(3), ancestor)
        qk = QuadKey(Type_Bing, 4, 31, 5)
        ancestor = QuadKey(Type_Bing, 1, 7, 3)
        self.assertTrue(qk.get_ancestor(2), ancestor)

    def test_get_child(self):
        """Get a single child NE, SE, NW, SW."""
        self.assertEqual(QuadKey(),
                         QuadKey().get_child(QuadKey.quadrant_north_west))
        maxdepthbing = QuadKey.max_depth(Type_Bing)
        self.assertEqual(QuadKey(),
                         QuadKey(Type_Bing, 0, 0, maxdepthbing).get_child(
                         QuadKey.quadrant_north_east))

        qk = QuadKey(Type_Bing, 0, 0, 3)
        self.assertEqual(QuadKey(Type_Bing, 1, 0, 4),
                         qk.get_child(qk.quadrant_north_west))
        self.assertEqual(QuadKey(Type_Bing, 1, 1, 4),
                         qk.get_child(qk.quadrant_north_east))
        self.assertEqual(QuadKey(Type_Bing, 0, 1, 4),
                         qk.get_child(qk.quadrant_south_east))
        self.assertEqual(QuadKey(Type_Bing, 0, 0, 4),
                         qk.get_child(qk.quadrant_south_west))

        qk = QuadKey(Type_Bing, 2, 3, 3)
        self.assertEqual(QuadKey(Type_Bing, 5, 6, 4),
                         qk.get_child(qk.quadrant_north_west))
        self.assertEqual(QuadKey(Type_Bing, 5, 7, 4),
                         qk.get_child(qk.quadrant_north_east))
        self.assertEqual(QuadKey(Type_Bing, 4, 7, 4),
                         qk.get_child(qk.quadrant_south_east))
        self.assertEqual(QuadKey(Type_Bing, 4, 6, 4),
                         qk.get_child(qk.quadrant_south_west))

    def test_get_children(self):
        """Get all the childern of a qk."""
        qk = QuadKey()
        vec = qk.get_children()
        self.assertEqual(0, len(vec))

        qk = QuadKey(Type_Bing, 0, 0, 1)
        vec = qk.get_children()
        self.assertEqual(4, len(vec))
        self.assertTrue(QuadKey(Type_Bing, 0, 0, 2) in vec)
        self.assertTrue(QuadKey(Type_Bing, 0, 1, 2) in vec)
        self.assertTrue(QuadKey(Type_Bing, 1, 0, 2) in vec)
        self.assertTrue(QuadKey(Type_Bing, 1, 1, 2) in vec)

        qk = QuadKey(Type_Bing, 0, 1, 1)
        vec = qk.get_children()
        self.assertEqual(4, len(vec))
        self.assertTrue(QuadKey(Type_Bing, 0, 2, 2) in vec)
        self.assertTrue(QuadKey(Type_Bing, 0, 3, 2) in vec)
        self.assertTrue(QuadKey(Type_Bing, 1, 2, 2) in vec)
        self.assertTrue(QuadKey(Type_Bing, 1, 3, 2) in vec)

        qk = QuadKey(Type_Bing, 1, 0, 1)
        vec = qk.get_children()
        self.assertEqual(4, len(vec))
        self.assertTrue(QuadKey(Type_Bing, 2, 0, 2) in vec)
        self.assertTrue(QuadKey(Type_Bing, 2, 1, 2) in vec)
        self.assertTrue(QuadKey(Type_Bing, 3, 0, 2) in vec)
        self.assertTrue(QuadKey(Type_Bing, 3, 1, 2) in vec)

        qk = QuadKey(Type_Bing, 1, 1, 1)
        vec = qk.get_children()
        self.assertEqual(4, len(vec))
        self.assertTrue(QuadKey(Type_Bing, 2, 2, 2) in vec)
        self.assertTrue(QuadKey(Type_Bing, 2, 3, 2) in vec)
        self.assertTrue(QuadKey(Type_Bing, 3, 2, 2) in vec)
        self.assertTrue(QuadKey(Type_Bing, 3, 3, 2) in vec)

    def test_get_descendants(self):  # noqa E501  # pylint: disable = too-many-statements
        """Get all the defendants at some delta in the tree."""
        bing_max_depth = QuadKey.max_depth(Type_Bing)
        qk = QuadKey(Type_Bing, 0, 0, bing_max_depth - 3)

        vec = qk.get_descendants(4)
        self.assertEqual(0, len(vec))

        none = QuadKey()
        vec = none.get_descendants(1)
        self.assertEqual(0, len(vec))

        qk = QuadKey(Type_Bing, 0, 0, 0)
        vec = qk.get_descendants(0)
        self.assertEqual(0, len(vec))

        qk = QuadKey(Type_Bing, 0, 0, 0)
        vec = qk.get_descendants(1)
        self.assertEqual(4, len(vec))
        self.assertTrue(QuadKey(Type_Bing, 0, 0, 1) in vec)
        self.assertTrue(QuadKey(Type_Bing, 0, 1, 1) in vec)
        self.assertTrue(QuadKey(Type_Bing, 1, 0, 1) in vec)
        self.assertTrue(QuadKey(Type_Bing, 1, 1, 1) in vec)

        vec = qk.get_descendants(2)
        self.assertEqual(16, len(vec))
        self.assertTrue(QuadKey(Type_Bing, 0, 0, 2) in vec)
        self.assertTrue(QuadKey(Type_Bing, 0, 1, 2) in vec)
        self.assertTrue(QuadKey(Type_Bing, 0, 2, 2) in vec)
        self.assertTrue(QuadKey(Type_Bing, 0, 3, 2) in vec)
        self.assertTrue(QuadKey(Type_Bing, 1, 0, 2) in vec)
        self.assertTrue(QuadKey(Type_Bing, 1, 1, 2) in vec)
        self.assertTrue(QuadKey(Type_Bing, 1, 2, 2) in vec)
        self.assertTrue(QuadKey(Type_Bing, 1, 3, 2) in vec)
        self.assertTrue(QuadKey(Type_Bing, 2, 0, 2) in vec)
        self.assertTrue(QuadKey(Type_Bing, 2, 1, 2) in vec)
        self.assertTrue(QuadKey(Type_Bing, 2, 2, 2) in vec)
        self.assertTrue(QuadKey(Type_Bing, 2, 3, 2) in vec)
        self.assertTrue(QuadKey(Type_Bing, 3, 0, 2) in vec)
        self.assertTrue(QuadKey(Type_Bing, 3, 1, 2) in vec)
        self.assertTrue(QuadKey(Type_Bing, 3, 2, 2) in vec)
        self.assertTrue(QuadKey(Type_Bing, 3, 3, 2) in vec)

        vec = qk.get_descendants(3)
        self.assertEqual(64, len(vec))
        self.assertTrue(QuadKey(Type_Bing, 0, 0, 3) in vec)
        self.assertTrue(QuadKey(Type_Bing, 0, 1, 3) in vec)
        self.assertTrue(QuadKey(Type_Bing, 0, 2, 3) in vec)
        self.assertTrue(QuadKey(Type_Bing, 0, 3, 3) in vec)
        self.assertTrue(QuadKey(Type_Bing, 0, 4, 3) in vec)
        self.assertTrue(QuadKey(Type_Bing, 0, 5, 3) in vec)
        self.assertTrue(QuadKey(Type_Bing, 0, 6, 3) in vec)
        self.assertTrue(QuadKey(Type_Bing, 0, 7, 3) in vec)
        self.assertTrue(QuadKey(Type_Bing, 1, 0, 3) in vec)
        self.assertTrue(QuadKey(Type_Bing, 1, 1, 3) in vec)
        self.assertTrue(QuadKey(Type_Bing, 1, 2, 3) in vec)
        self.assertTrue(QuadKey(Type_Bing, 1, 3, 3) in vec)
        self.assertTrue(QuadKey(Type_Bing, 1, 4, 3) in vec)
        self.assertTrue(QuadKey(Type_Bing, 1, 5, 3) in vec)
        self.assertTrue(QuadKey(Type_Bing, 1, 6, 3) in vec)
        self.assertTrue(QuadKey(Type_Bing, 1, 7, 3) in vec)
        self.assertTrue(QuadKey(Type_Bing, 2, 0, 3) in vec)
        self.assertTrue(QuadKey(Type_Bing, 2, 1, 3) in vec)
        self.assertTrue(QuadKey(Type_Bing, 2, 2, 3) in vec)
        self.assertTrue(QuadKey(Type_Bing, 2, 3, 3) in vec)
        self.assertTrue(QuadKey(Type_Bing, 2, 4, 3) in vec)
        self.assertTrue(QuadKey(Type_Bing, 2, 5, 3) in vec)
        self.assertTrue(QuadKey(Type_Bing, 2, 6, 3) in vec)
        self.assertTrue(QuadKey(Type_Bing, 2, 7, 3) in vec)
        self.assertTrue(QuadKey(Type_Bing, 3, 0, 3) in vec)
        self.assertTrue(QuadKey(Type_Bing, 3, 1, 3) in vec)
        self.assertTrue(QuadKey(Type_Bing, 3, 2, 3) in vec)
        self.assertTrue(QuadKey(Type_Bing, 3, 3, 3) in vec)
        self.assertTrue(QuadKey(Type_Bing, 3, 4, 3) in vec)
        self.assertTrue(QuadKey(Type_Bing, 3, 5, 3) in vec)
        self.assertTrue(QuadKey(Type_Bing, 3, 6, 3) in vec)
        self.assertTrue(QuadKey(Type_Bing, 3, 7, 3) in vec)
        self.assertTrue(QuadKey(Type_Bing, 4, 0, 3) in vec)
        self.assertTrue(QuadKey(Type_Bing, 4, 1, 3) in vec)
        self.assertTrue(QuadKey(Type_Bing, 4, 2, 3) in vec)
        self.assertTrue(QuadKey(Type_Bing, 4, 3, 3) in vec)
        self.assertTrue(QuadKey(Type_Bing, 4, 4, 3) in vec)
        self.assertTrue(QuadKey(Type_Bing, 4, 5, 3) in vec)
        self.assertTrue(QuadKey(Type_Bing, 4, 6, 3) in vec)
        self.assertTrue(QuadKey(Type_Bing, 4, 7, 3) in vec)
        self.assertTrue(QuadKey(Type_Bing, 5, 0, 3) in vec)
        self.assertTrue(QuadKey(Type_Bing, 5, 1, 3) in vec)
        self.assertTrue(QuadKey(Type_Bing, 5, 2, 3) in vec)
        self.assertTrue(QuadKey(Type_Bing, 5, 3, 3) in vec)
        self.assertTrue(QuadKey(Type_Bing, 5, 4, 3) in vec)
        self.assertTrue(QuadKey(Type_Bing, 5, 5, 3) in vec)
        self.assertTrue(QuadKey(Type_Bing, 5, 6, 3) in vec)
        self.assertTrue(QuadKey(Type_Bing, 5, 7, 3) in vec)
        self.assertTrue(QuadKey(Type_Bing, 6, 0, 3) in vec)
        self.assertTrue(QuadKey(Type_Bing, 6, 1, 3) in vec)
        self.assertTrue(QuadKey(Type_Bing, 6, 2, 3) in vec)
        self.assertTrue(QuadKey(Type_Bing, 6, 3, 3) in vec)
        self.assertTrue(QuadKey(Type_Bing, 6, 4, 3) in vec)
        self.assertTrue(QuadKey(Type_Bing, 6, 5, 3) in vec)
        self.assertTrue(QuadKey(Type_Bing, 6, 6, 3) in vec)
        self.assertTrue(QuadKey(Type_Bing, 6, 7, 3) in vec)
        self.assertTrue(QuadKey(Type_Bing, 7, 0, 3) in vec)
        self.assertTrue(QuadKey(Type_Bing, 7, 1, 3) in vec)
        self.assertTrue(QuadKey(Type_Bing, 7, 2, 3) in vec)
        self.assertTrue(QuadKey(Type_Bing, 7, 3, 3) in vec)
        self.assertTrue(QuadKey(Type_Bing, 7, 4, 3) in vec)
        self.assertTrue(QuadKey(Type_Bing, 7, 5, 3) in vec)
        self.assertTrue(QuadKey(Type_Bing, 7, 6, 3) in vec)
        self.assertTrue(QuadKey(Type_Bing, 7, 7, 3) in vec)

    def test_get_siblings(self):
        """Test to get siblings of a given quadkey."""
        qk = QuadKey()
        vec = qk.get_siblings()
        self.assertEqual(0, len(vec))

        qk = QuadKey(Type_Bing, 0, 0, 1)
        vec = qk.get_siblings()
        self.assertEqual(3, len(vec))
        self.assertTrue(QuadKey(Type_Bing, 0, 1, 1) in vec)
        self.assertTrue(QuadKey(Type_Bing, 1, 1, 1) in vec)
        self.assertTrue(QuadKey(Type_Bing, 1, 0, 1) in vec)

    def test_get_neighbors(self):  # noqa E501  # pylint: disable = too-many-statements
        """Test to get the neighbors of a given QuadKey."""
        vec = QuadKey().get_neighbors()
        self.assertEqual(0, len(vec))

        vec = QuadKey(Type_Bing, 0, 0, 0).get_neighbors()
        self.assertEqual(0, len(vec))

        vec = QuadKey(Type_Bing, 0, 0, 2).get_neighbors()
        self.assertEqual(5, len(vec))
        self.assertTrue(QuadKey(Type_Bing, 0, 1, 2) in vec)
        self.assertTrue(QuadKey(Type_Bing, 1, 1, 2) in vec)
        self.assertTrue(QuadKey(Type_Bing, 1, 0, 2) in vec)
        self.assertTrue(QuadKey(Type_Bing, 0, 3, 2) in vec)
        self.assertTrue(QuadKey(Type_Bing, 1, 3, 2) in vec)

        vec = QuadKey(Type_Bing, 0, 1, 2).get_neighbors()
        self.assertEqual(5, len(vec))
        self.assertTrue(QuadKey(Type_Bing, 0, 0, 2) in vec)
        self.assertTrue(QuadKey(Type_Bing, 1, 0, 2) in vec)
        self.assertTrue(QuadKey(Type_Bing, 1, 1, 2) in vec)
        self.assertTrue(QuadKey(Type_Bing, 1, 2, 2) in vec)
        self.assertTrue(QuadKey(Type_Bing, 0, 2, 2) in vec)

        vec = QuadKey(Type_Bing, 0, 2, 2).get_neighbors()
        self.assertEqual(5, len(vec))
        self.assertTrue(QuadKey(Type_Bing, 0, 1, 2) in vec)
        self.assertTrue(QuadKey(Type_Bing, 1, 1, 2) in vec)
        self.assertTrue(QuadKey(Type_Bing, 1, 2, 2) in vec)
        self.assertTrue(QuadKey(Type_Bing, 1, 3, 2) in vec)
        self.assertTrue(QuadKey(Type_Bing, 0, 3, 2) in vec)

        vec = QuadKey(Type_Bing, 0, 3, 2).get_neighbors()
        self.assertEqual(5, len(vec))
        self.assertTrue(QuadKey(Type_Bing, 0, 2, 2) in vec)
        self.assertTrue(QuadKey(Type_Bing, 1, 2, 2) in vec)
        self.assertTrue(QuadKey(Type_Bing, 1, 3, 2) in vec)
        self.assertTrue(QuadKey(Type_Bing, 1, 0, 2) in vec)
        self.assertTrue(QuadKey(Type_Bing, 0, 0, 2) in vec)

        vec = QuadKey(Type_Bing, 1, 0, 2).get_neighbors()
        self.assertEqual(8, len(vec))
        self.assertTrue(QuadKey(Type_Bing, 0, 0, 2) in vec)
        self.assertTrue(QuadKey(Type_Bing, 0, 1, 2) in vec)
        self.assertTrue(QuadKey(Type_Bing, 1, 1, 2) in vec)
        self.assertTrue(QuadKey(Type_Bing, 2, 1, 2) in vec)
        self.assertTrue(QuadKey(Type_Bing, 2, 0, 2) in vec)
        self.assertTrue(QuadKey(Type_Bing, 2, 3, 2) in vec)
        self.assertTrue(QuadKey(Type_Bing, 1, 3, 2) in vec)
        self.assertTrue(QuadKey(Type_Bing, 0, 3, 2) in vec)

        vec = QuadKey(Type_Bing, 1, 1, 2).get_neighbors()
        self.assertEqual(8, len(vec))
        self.assertTrue(QuadKey(Type_Bing, 1, 0, 2) in vec)
        self.assertTrue(QuadKey(Type_Bing, 0, 0, 2) in vec)
        self.assertTrue(QuadKey(Type_Bing, 0, 1, 2) in vec)
        self.assertTrue(QuadKey(Type_Bing, 2, 2, 2) in vec)
        self.assertTrue(QuadKey(Type_Bing, 2, 1, 2) in vec)
        self.assertTrue(QuadKey(Type_Bing, 2, 0, 2) in vec)
        self.assertTrue(QuadKey(Type_Bing, 0, 2, 2) in vec)
        self.assertTrue(QuadKey(Type_Bing, 1, 2, 2) in vec)

        vec = QuadKey(Type_Bing, 1, 2, 2).get_neighbors()
        self.assertEqual(8, len(vec))
        self.assertTrue(QuadKey(Type_Bing, 1, 1, 2) in vec)
        self.assertTrue(QuadKey(Type_Bing, 0, 1, 2) in vec)
        self.assertTrue(QuadKey(Type_Bing, 0, 2, 2) in vec)
        self.assertTrue(QuadKey(Type_Bing, 2, 3, 2) in vec)
        self.assertTrue(QuadKey(Type_Bing, 2, 2, 2) in vec)
        self.assertTrue(QuadKey(Type_Bing, 2, 1, 2) in vec)
        self.assertTrue(QuadKey(Type_Bing, 0, 3, 2) in vec)
        self.assertTrue(QuadKey(Type_Bing, 1, 3, 2) in vec)

        vec = QuadKey(Type_Bing, 1, 3, 2).get_neighbors()
        self.assertEqual(8, len(vec))
        self.assertTrue(QuadKey(Type_Bing, 1, 2, 2) in vec)
        self.assertTrue(QuadKey(Type_Bing, 0, 2, 2) in vec)
        self.assertTrue(QuadKey(Type_Bing, 0, 3, 2) in vec)
        self.assertTrue(QuadKey(Type_Bing, 2, 0, 2) in vec)
        self.assertTrue(QuadKey(Type_Bing, 2, 3, 2) in vec)
        self.assertTrue(QuadKey(Type_Bing, 2, 2, 2) in vec)
        self.assertTrue(QuadKey(Type_Bing, 0, 0, 2) in vec)
        self.assertTrue(QuadKey(Type_Bing, 1, 0, 2) in vec)

        vec = QuadKey(Type_Bing, 4, 7, 3).get_neighbors()
        self.assertEqual(8, len(vec))
        self.assertTrue(QuadKey(Type_Bing, 3, 7, 3) in vec)
        self.assertTrue(QuadKey(Type_Bing, 3, 6, 3) in vec)
        self.assertTrue(QuadKey(Type_Bing, 4, 6, 3) in vec)
        self.assertTrue(QuadKey(Type_Bing, 5, 6, 3) in vec)
        self.assertTrue(QuadKey(Type_Bing, 5, 7, 3) in vec)
        self.assertTrue(QuadKey(Type_Bing, 5, 0, 3) in vec)
        self.assertTrue(QuadKey(Type_Bing, 4, 0, 3) in vec)
        self.assertTrue(QuadKey(Type_Bing, 3, 0, 3) in vec)

        vec = QuadKey(Type_Bing, 4, 0, 3).get_neighbors()
        self.assertEqual(8, len(vec))
        self.assertTrue(QuadKey(Type_Bing, 3, 0, 3) in vec)
        self.assertTrue(QuadKey(Type_Bing, 3, 1, 3) in vec)
        self.assertTrue(QuadKey(Type_Bing, 4, 1, 3) in vec)
        self.assertTrue(QuadKey(Type_Bing, 5, 1, 3) in vec)
        self.assertTrue(QuadKey(Type_Bing, 5, 0, 3) in vec)
        self.assertTrue(QuadKey(Type_Bing, 5, 7, 3) in vec)
        self.assertTrue(QuadKey(Type_Bing, 4, 7, 3) in vec)
        self.assertTrue(QuadKey(Type_Bing, 3, 7, 3) in vec)

    def test_to_string_from_string(self):  # noqa E501  # pylint: disable = too-many-statements
        """Test to convert an internally formatted string and back."""
        root = QuadKey.from_internal_string(Type_Bing, "")
        self.assertEqual(0, root.get_row())
        self.assertEqual(0, root.get_col())
        self.assertEqual(0, root.get_depth())

        qk = QuadKey.from_internal_string(Type_Bing, "0")
        self.assertEqual(1, qk.get_row())
        self.assertEqual(0, qk.get_col())
        self.assertEqual(1, qk.get_depth())
        self.assertEqual("0", qk.to_internal_string())
        qk = QuadKey.from_internal_string(Type_Bing, "1")
        self.assertEqual(1, qk.get_row())
        self.assertEqual(1, qk.get_col())
        self.assertEqual(1, qk.get_depth())
        self.assertEqual("1", qk.to_internal_string())
        qk = QuadKey.from_internal_string(Type_Bing, "2")
        self.assertEqual(0, qk.get_row())
        self.assertEqual(0, qk.get_col())
        self.assertEqual(1, qk.get_depth())
        self.assertEqual("2", qk.to_internal_string())
        qk = QuadKey.from_internal_string(Type_Bing, "3")
        self.assertEqual(0, qk.get_row())
        self.assertEqual(1, qk.get_col())
        self.assertEqual(1, qk.get_depth())
        self.assertEqual("3", qk.to_internal_string())

        qk = QuadKey.from_internal_string(Type_Bing, "00")
        self.assertEqual(3, qk.get_row())
        self.assertEqual(0, qk.get_col())
        self.assertEqual(2, qk.get_depth())
        self.assertEqual("00", qk.to_internal_string())
        qk = QuadKey.from_internal_string(Type_Bing, "01")
        self.assertEqual(3, qk.get_row())
        self.assertEqual(1, qk.get_col())
        self.assertEqual(2, qk.get_depth())
        self.assertEqual("01", qk.to_internal_string())
        qk = QuadKey.from_internal_string(Type_Bing, "02")
        self.assertEqual(2, qk.get_row())
        self.assertEqual(0, qk.get_col())
        self.assertEqual(2, qk.get_depth())
        self.assertEqual("02", qk.to_internal_string())
        qk = QuadKey.from_internal_string(Type_Bing, "03")
        self.assertEqual(2, qk.get_row())
        self.assertEqual(1, qk.get_col())
        self.assertEqual(2, qk.get_depth())
        self.assertEqual("03", qk.to_internal_string())
        qk = QuadKey.from_internal_string(Type_Bing, "10")
        self.assertEqual(3, qk.get_row())
        self.assertEqual(2, qk.get_col())
        self.assertEqual(2, qk.get_depth())
        self.assertEqual("10", qk.to_internal_string())
        qk = QuadKey.from_internal_string(Type_Bing, "11")
        self.assertEqual(3, qk.get_row())
        self.assertEqual(3, qk.get_col())
        self.assertEqual(2, qk.get_depth())
        self.assertEqual("11", qk.to_internal_string())
        qk = QuadKey.from_internal_string(Type_Bing, "12")
        self.assertEqual(2, qk.get_row())
        self.assertEqual(2, qk.get_col())
        self.assertEqual(2, qk.get_depth())
        self.assertEqual("12", qk.to_internal_string())
        qk = QuadKey.from_internal_string(Type_Bing, "13")
        self.assertEqual(2, qk.get_row())
        self.assertEqual(3, qk.get_col())
        self.assertEqual(2, qk.get_depth())
        self.assertEqual("13", qk.to_internal_string())
        qk = QuadKey.from_internal_string(Type_Bing, "20")
        self.assertEqual(1, qk.get_row())
        self.assertEqual(0, qk.get_col())
        self.assertEqual(2, qk.get_depth())
        self.assertEqual("20", qk.to_internal_string())
        qk = QuadKey.from_internal_string(Type_Bing, "21")
        self.assertEqual(1, qk.get_row())
        self.assertEqual(1, qk.get_col())
        self.assertEqual(2, qk.get_depth())
        self.assertEqual("21", qk.to_internal_string())
        qk = QuadKey.from_internal_string(Type_Bing, "22")
        self.assertEqual(0, qk.get_row())
        self.assertEqual(0, qk.get_col())
        self.assertEqual(2, qk.get_depth())
        self.assertEqual("22", qk.to_internal_string())
        qk = QuadKey.from_internal_string(Type_Bing, "23")
        self.assertEqual(0, qk.get_row())
        self.assertEqual(1, qk.get_col())
        self.assertEqual(2, qk.get_depth())
        self.assertEqual("23", qk.to_internal_string())
        qk = QuadKey.from_internal_string(Type_Bing, "30")
        self.assertEqual(1, qk.get_row())
        self.assertEqual(2, qk.get_col())
        self.assertEqual(2, qk.get_depth())
        self.assertEqual("30", qk.to_internal_string())
        qk = QuadKey.from_internal_string(Type_Bing, "31")
        self.assertEqual(1, qk.get_row())
        self.assertEqual(3, qk.get_col())
        self.assertEqual(2, qk.get_depth())
        self.assertEqual("31", qk.to_internal_string())
        qk = QuadKey.from_internal_string(Type_Bing, "32")
        self.assertEqual(0, qk.get_row())
        self.assertEqual(2, qk.get_col())
        self.assertEqual(2, qk.get_depth())
        self.assertEqual("32", qk.to_internal_string())
        qk = QuadKey.from_internal_string(Type_Bing, "33")
        self.assertEqual(0, qk.get_row())
        self.assertEqual(3, qk.get_col())
        self.assertEqual(2, qk.get_depth())
        self.assertEqual("33", qk.to_internal_string())

    def test_get_geo_coordinate_bounds_2d(self):
        """Test to get geographic bounds of QuadKey."""
        bbox = GeoCoordinateBoundingBox2d()

        qk = QuadKey.from_internal_string(Type_Bing, "")
        qk.get_geo_coordinate_bounds2d(bbox)
        self.assertAlmostEqual(-180.0,
                               bbox.lower_left().get_longitude().val())
        self.assertAlmostEqual(-84.9283209,
                               bbox.lower_left().get_latitude().val())
        self.assertAlmostEqual(178.593750,
                               bbox.upper_right().get_longitude().val())
        self.assertAlmostEqual(85.05112877,
                               bbox.upper_right().get_latitude().val())

    def test_get_key_from_longitude_latitude_at_depth_to_bounds(self):  # noqa E501  # pylint: disable = too-many-statements
        """Test to get a quadkey from longitude and latitude and then get
        bounds.
        """
        bbox = GeoCoordinateBoundingBox2d()

        qk = QuadKey.get_key_from_longitude_latitude_at_depth(
            Type_Bing, GeoCoordinate2d(Longitude(-180.0),
                                       Latitude(-84.0)), 0)
        self.assertEqual(QuadKey(Type_Bing, 0, 0, 0), qk)
        qk.get_geo_coordinate_bounds2d(bbox)
        diff = math.fabs(
            bbox.lower_left().get_longitude() - Longitude(-180.0))
        self.assertTrue(2.0 > diff)
        diff = math.fabs(
            bbox.lower_left().get_latitude() - Latitude(-85.0))
        self.assertTrue(2.0 > diff)
        diff = math.fabs(
            bbox.upper_right().get_longitude() - Longitude(+180.0))
        self.assertTrue(2.0 > diff)
        diff = math.fabs(
            bbox.upper_right().get_latitude() - Latitude(+85.0))
        self.assertTrue(2.0 > diff)

        # Inclusion here consists of upper left
        # ul X------X------X
        #    |      |      |
        #    |      |      |
        #    X------X------X
        #    |      |      |
        #    |      |      |
        #    X------X------X
        left = Longitude(-180.0)
        midleft = Longitude(-0.36)
        midright = Longitude(0.0)
        right = Longitude(+180.0)
        bottom = Latitude(-90.0)
        midbottom = Latitude(0.0)
        midtop = Latitude(0.36)
        top = Latitude(+90.0)

        qk = QuadKey.get_key_from_longitude_latitude_at_depth(
            Type_Bing, GeoCoordinate2d(left, top), 1)
        self.assertEqual(QuadKey(Type_Bing, 1, 0, 1), qk)
        qk = QuadKey.get_key_from_longitude_latitude_at_depth(
            Type_Bing, GeoCoordinate2d(left, midtop), 1)
        self.assertEqual(QuadKey(Type_Bing, 1, 0, 1), qk)
        qk = QuadKey.get_key_from_longitude_latitude_at_depth(
            Type_Bing, GeoCoordinate2d(midleft, midtop), 1)
        self.assertEqual(QuadKey(Type_Bing, 1, 0, 1), qk)
        qk = QuadKey.get_key_from_longitude_latitude_at_depth(
            Type_Bing, GeoCoordinate2d(midleft, top), 1)
        self.assertEqual(QuadKey(Type_Bing, 1, 0, 1), qk)
        qk.get_geo_coordinate_bounds2d(bbox)
        diff = math.fabs(bbox.lower_left().get_longitude() - left)
        self.assertTrue(2.0 > diff)
        diff = math.fabs(bbox.lower_left().get_latitude() - midtop)
        self.assertTrue(2.0 > diff)
        diff = math.fabs(bbox.upper_right().get_longitude() - midleft)
        self.assertTrue(2.0 > diff)
        diff = math.fabs(bbox.upper_right().get_latitude() - Latitude(+85.0))
        self.assertTrue(2.0 > diff)

        qk = QuadKey.get_key_from_longitude_latitude_at_depth(
            Type_Bing, GeoCoordinate2d(midright, top), 1)
        self.assertEqual(QuadKey(Type_Bing, 1, 1, 1), qk)
        qk = QuadKey.get_key_from_longitude_latitude_at_depth(
            Type_Bing, GeoCoordinate2d(midright, midtop), 1)
        self.assertEqual(QuadKey(Type_Bing, 1, 1, 1), qk)
        qk = QuadKey.get_key_from_longitude_latitude_at_depth(
            Type_Bing, GeoCoordinate2d(right, midtop), 1)
        self.assertEqual(QuadKey(Type_Bing, 1, 1, 1), qk)
        qk = QuadKey.get_key_from_longitude_latitude_at_depth(
            Type_Bing, GeoCoordinate2d(right, top), 1)
        self.assertEqual(QuadKey(Type_Bing, 1, 1, 1), qk)
        qk.get_geo_coordinate_bounds2d(bbox)
        diff = math.fabs(bbox.lower_left().get_longitude() - midright)
        self.assertTrue(2.0 > diff)
        diff = math.fabs(bbox.lower_left().get_latitude() - midtop)
        self.assertTrue(2.0 > diff)
        diff = math.fabs(bbox.upper_right().get_longitude() - right)
        self.assertTrue(2.0 > diff)
        diff = math.fabs(bbox.upper_right().get_latitude() - Latitude(+85.0))
        self.assertTrue(2.0 > diff)

        qk = QuadKey.get_key_from_longitude_latitude_at_depth(
            Type_Bing, GeoCoordinate2d(left, midbottom), 1)
        self.assertEqual(QuadKey(Type_Bing, 0, 0, 1), qk)
        qk = QuadKey.get_key_from_longitude_latitude_at_depth(
            Type_Bing, GeoCoordinate2d(left, bottom), 1)
        self.assertEqual(QuadKey(Type_Bing, 0, 0, 1), qk)
        qk = QuadKey.get_key_from_longitude_latitude_at_depth(
            Type_Bing, GeoCoordinate2d(midleft, bottom), 1)
        self.assertEqual(QuadKey(Type_Bing, 0, 0, 1), qk)
        qk = QuadKey.get_key_from_longitude_latitude_at_depth(
            Type_Bing, GeoCoordinate2d(midleft, midbottom), 1)
        self.assertEqual(QuadKey(Type_Bing, 0, 0, 1), qk)
        qk.get_geo_coordinate_bounds2d(bbox)
        diff = math.fabs(bbox.lower_left().get_longitude() - left)
        self.assertTrue(2.0 > diff)
        diff = math.fabs(bbox.lower_left().get_latitude() - Latitude(-85.0))
        self.assertTrue(2.0 > diff)
        diff = math.fabs(bbox.upper_right().get_longitude() - midleft)
        self.assertTrue(2.0 > diff)
        diff = math.fabs(bbox.upper_right().get_latitude() - midbottom)
        self.assertTrue(2.0 > diff)

        qk = QuadKey.get_key_from_longitude_latitude_at_depth(
            Type_Bing, GeoCoordinate2d(midright, midbottom), 1)
        self.assertEqual(QuadKey(Type_Bing, 0, 1, 1), qk)
        qk = QuadKey.get_key_from_longitude_latitude_at_depth(
            Type_Bing, GeoCoordinate2d(midright, bottom), 1)
        self.assertEqual(QuadKey(Type_Bing, 0, 1, 1), qk)
        qk = QuadKey.get_key_from_longitude_latitude_at_depth(
            Type_Bing, GeoCoordinate2d(right, bottom), 1)
        self.assertEqual(QuadKey(Type_Bing, 0, 1, 1), qk)
        qk = QuadKey.get_key_from_longitude_latitude_at_depth(
            Type_Bing, GeoCoordinate2d(right, midbottom), 1)
        self.assertEqual(QuadKey(Type_Bing, 0, 1, 1), qk)
        qk.get_geo_coordinate_bounds2d(bbox)
        diff = math.fabs(bbox.lower_left().get_longitude() - midright)
        self.assertTrue(2.0 > diff)
        diff = math.fabs(bbox.lower_left().get_latitude() - Latitude(-85.0))
        self.assertTrue(2.0 > diff)
        diff = math.fabs(bbox.upper_right().get_longitude() - right)
        self.assertTrue(2.0 > diff)
        diff = math.fabs(bbox.upper_right().get_latitude() - midbottom)
        self.assertTrue(2.0 > diff)

    def test_get_keys_from_longitude_latitude_bounding_box(self):
        """Test to get the bounding box of a QuadKey."""
        out_keys = QuadKey.get_keys_from_longitude_latitude_bounding_box(
            Type_Bing,
            GeoCoordinateBoundingBox2d(
                GeoCoordinate2d(Longitude(-180.0), Latitude(+90.0)),
                GeoCoordinate2d(Longitude(+180.0), Latitude(-90.0))), 0)
        self.assertEqual(1, out_keys.size())
        self.assertTrue(QuadKey(Type_Bing, 0, 0, 0) in out_keys)

        out_keys = QuadKey.get_keys_from_longitude_latitude_bounding_box(
            Type_Bing,
            GeoCoordinateBoundingBox2d(
                GeoCoordinate2d(Longitude(-180.0), Latitude(+90.0)),
                GeoCoordinate2d(Longitude(+180.0), Latitude(-90.0))), 1)
        self.assertEqual(4, out_keys.size())
        self.assertTrue(QuadKey(Type_Bing, 0, 0, 1) in out_keys)
        self.assertTrue(QuadKey(Type_Bing, 0, 1, 1) in out_keys)
        self.assertTrue(QuadKey(Type_Bing, 1, 0, 1) in out_keys)
        self.assertTrue(QuadKey(Type_Bing, 1, 1, 1) in out_keys)

        out_keys = QuadKey.get_keys_from_longitude_latitude_bounding_box(
            Type_Bing,
            GeoCoordinateBoundingBox2d(
                GeoCoordinate2d(Longitude(-180.0), Latitude(+0.35)),
                GeoCoordinate2d(Longitude(-0.36), Latitude(+90.0))), 1)
        self.assertEqual(2, out_keys.size())
        self.assertTrue(QuadKey(Type_Bing, 0, 0, 1) in out_keys)
        self.assertTrue(QuadKey(Type_Bing, 1, 0, 1) in out_keys)

        out_keys = QuadKey.get_keys_from_longitude_latitude_bounding_box(
            Type_Bing,
            GeoCoordinateBoundingBox2d(
                GeoCoordinate2d(Longitude(-0.36), Latitude(+0.36)),
                GeoCoordinate2d(Longitude(+0.36), Latitude(+90.0))), 1)
        self.assertEqual(2, out_keys.size())
        self.assertTrue(QuadKey(Type_Bing, 1, 0, 1) in out_keys)
        self.assertTrue(QuadKey(Type_Bing, 1, 1, 1) in out_keys)

        out_keys = QuadKey.get_keys_from_longitude_latitude_bounding_box(
            Type_Bing,
            GeoCoordinateBoundingBox2d(
                GeoCoordinate2d(Longitude(-0.36), Latitude(+0.35)),
                GeoCoordinate2d(Longitude(+0.36), Latitude(+90.0))), 1)
        self.assertEqual(4, out_keys.size())
        self.assertTrue(QuadKey(Type_Bing, 0, 0, 1) in out_keys)
        self.assertTrue(QuadKey(Type_Bing, 0, 1, 1) in out_keys)
        self.assertTrue(QuadKey(Type_Bing, 1, 0, 1) in out_keys)
        self.assertTrue(QuadKey(Type_Bing, 1, 1, 1) in out_keys)

    def test_selected_cities(self):
        """Test a given set of known places make sure they work."""
        qk_type = Type_Bing

        # Chicago 41.822, -87.635
        depth = 16
        coords = GeoCoordinate2d(Longitude(-87.635), Latitude(41.822))
        qk = QuadKey.get_key_from_longitude_latitude_at_depth(qk_type,
                                                              coords,
                                                              depth)
        self.assertEqual("0302222310321132", qk.to_internal_string())
        bbox = GeoCoordinateBoundingBox2d()
        qk.get_geo_coordinate_bounds2d(bbox)
        # Note that Bing will return a bounding box of all sides inclusive
        keys = QuadKey.get_keys_from_longitude_latitude_bounding_box(
            qk_type, bbox, depth)
        self.assertEqual(4, keys.size())
        self.assertTrue(qk in keys)

        # Rio -43.1964,-22.9083
        depth = 17
        coords = GeoCoordinate2d(Longitude(-43.1964), Latitude(-22.9083))
        qk = QuadKey.get_key_from_longitude_latitude_at_depth(qk_type,
                                                              coords,
                                                              depth)
        self.assertEqual("21120001212232200", qk.to_internal_string())
        bbox = GeoCoordinateBoundingBox2d()
        qk.get_geo_coordinate_bounds2d(bbox)
        # Note that Bing will return a bounding box of all sides inclusive
        keys = QuadKey.get_keys_from_longitude_latitude_bounding_box(
            qk_type, bbox, depth)
        self.assertEqual(4, keys.size())
        self.assertTrue(qk in keys)

        # Helsinki 60.1708 N, 24.9375 E
        depth = 17
        coords = GeoCoordinate2d(Longitude(24.9375), Latitude(60.1708))
        qk = QuadKey.get_key_from_longitude_latitude_at_depth(qk_type,
                                                              coords,
                                                              depth)
        self.assertEqual("12012021101330131", qk.to_internal_string())
        bbox = GeoCoordinateBoundingBox2d()
        qk.get_geo_coordinate_bounds2d(bbox)
        # Note that Bing will return a bounding box of all sides inclusive
        keys = QuadKey.get_keys_from_longitude_latitude_bounding_box(
            qk_type, bbox, depth)
        self.assertEqual(4, keys.size())
        self.assertTrue(qk in keys)

        # Cape Town South Africa 33.9253 S, 18.4239 E
        depth = 17
        coords = GeoCoordinate2d(Longitude(18.4239), Latitude(-33.9253))
        qk = QuadKey.get_key_from_longitude_latitude_at_depth(qk_type,
                                                              coords,
                                                              depth)
        self.assertEqual("30023103202132011", qk.to_internal_string())
        bbox = GeoCoordinateBoundingBox2d()
        qk.get_geo_coordinate_bounds2d(bbox)
        # Note that Bing will return a bounding box of all sides inclusive
        keys = QuadKey.get_keys_from_longitude_latitude_bounding_box(
            qk_type, bbox, depth)
        self.assertEqual(4, keys.size())
        self.assertTrue(qk in keys)

        # Quito 0.2500 S, 78.5833 W
        depth = 17
        coords = GeoCoordinate2d(Longitude(-78.5836), Latitude(-0.25))
        qk = QuadKey.get_key_from_longitude_latitude_at_depth(qk_type,
                                                              coords,
                                                              depth)
        self.assertEqual("21001000002133122", qk.to_internal_string())
        bbox = GeoCoordinateBoundingBox2d()
        qk.get_geo_coordinate_bounds2d(bbox)
        # Note that Bing will return a bounding box of all sides inclusive
        keys = QuadKey.get_keys_from_longitude_latitude_bounding_box(
            qk_type, bbox, depth)
        self.assertEqual(4, keys.size())
        self.assertTrue(qk in keys)

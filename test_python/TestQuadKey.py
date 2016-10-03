"""
Unit Tests for QuadKey
"""

from __future__ import print_function
import unittest
from quadkey import QuadKey
from quadkey import Type__None
from quadkey import Type_Bing
from quadkey import Type_LatLong
from quadkey import Type_UlpQnr
from quadkey import Type_OsGeo
from quadkey import Type_Morton


class TestQuadKey(unittest.TestCase):
    """
    Class for running unit tests.
    """

    def test_default_ctor(self):
        """
        Test default construction of QuadKey using Type_Bing
        """
        quad_key = QuadKey()
        self.assertIsNotNone(quad_key)
        self.assertEqual(quad_key.getRow(), 0)
        self.assertEqual(quad_key.getCol(), 0)
        self.assertEqual(quad_key.getType(), Type__None)
        self.assertEqual(quad_key.toInternalString(), '')

    def test_ctor_only_type(self):
        """
        Test constructor which takes type
        """
        types = [Type__None, Type_Bing, Type_LatLong, Type_UlpQnr,
                 Type_OsGeo, Type_Morton]
        for qk_type in types:
            assert isinstance(qk_type, int)
            quad_key = QuadKey(qk_type)
            self.assertIsNotNone(quad_key)
            self.assertEqual(quad_key.getRow(), 0)
            self.assertEqual(quad_key.getCol(), 0)
            self.assertEqual(quad_key.getType(), qk_type)

    def test_copy_ctor(self):
        """
        Test the copying of a quadkey
        """
        quad_key = QuadKey(Type_OsGeo)
        quad_key_copy = QuadKey(quad_key)
        self.assertEqual(quad_key, quad_key_copy)
        self.assertIsNotNone(quad_key_copy)
        self.assertEqual(quad_key.getRow(), 0)
        self.assertEqual(quad_key.getCol(), 0)
        self.assertEqual(quad_key.getType(), Type_OsGeo)

    def test_assignment_operator(self):
        """
        Test the assignment of quadkey
        """
        # This is not allowed in python

    def test_is_root_key(self):
        """
        Test if a quadkey is the root key
        """
        quad_key = QuadKey(Type_OsGeo)
        self.assertTrue(quad_key.isRootKey())

    def test_system_specifc_ctor(self):
        """
        Tests boundary case to see if constructed quadkey is valid.
        """
        types = [Type__None, Type_Bing, Type_LatLong, Type_UlpQnr,
                 Type_OsGeo, Type_Morton]
        quad_key_none = QuadKey()
        for qk_type in types:
            for depth in range(1, 10):
                maxrows = QuadKey.maxRows(qk_type, depth)
                maxcols = QuadKey.maxCols(qk_type, depth)
                assert isinstance(maxrows, int)
                assert isinstance(maxcols, int)
                quad_key_invalid = QuadKey(qk_type, maxrows, maxcols, depth)
                self.assertEqual(quad_key_none, quad_key_invalid)

                validrow = max(0, maxrows - 1)
                validcol = max(0, maxcols - 1)
                assert isinstance(validrow, int)
                assert isinstance(validcol, int)
                quad_key_valid = QuadKey(qk_type, validrow, validcol, depth)
                expected = QuadKey(qk_type, validrow, validcol, depth)
                self.assertEqual(quad_key_valid, expected)


def main():
    """
    Bootstrap function for this module
    """
    suite = unittest.TestLoader().loadTestsFromTestCase(TestQuadKey)
    unittest.TextTestRunner(verbosity=2).run(suite)

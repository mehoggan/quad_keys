"""
Unit Tests for quad_key
"""

from __future__ import print_function

import unittest

from quad_keys.quad_keys import QuadKey
from quad_keys.quad_keys import Type__None
from quad_keys.quad_keys import Type_Bing
from quad_keys.quad_keys import Type_LatLon
from quad_keys.quad_keys import Type_UlpQnr
from quad_keys.quad_keys import Type_OsGeo
from quad_keys.quad_keys import Type_Morton


class TestQuadKey(unittest.TestCase):
    """Class for running unit tests."""

    def test_default_ctor(self):
        """Test default construction of quad_key using Type_Bing."""
        qk = QuadKey()
        self.assertIsNotNone(qk)
        self.assertEqual(qk.get_row(), 0)
        self.assertEqual(qk.get_col(), 0)
        self.assertEqual(qk.get_type(), Type__None)
        self.assertEqual(qk.to_internal_string(), '')

    def test_ctor_only_type(self):
        """Test constructor which takes type."""
        types = [Type__None, Type_Bing, Type_LatLon, Type_UlpQnr,
                 Type_OsGeo, Type_Morton]
        for qk_type in types:
            assert isinstance(qk_type, int)
            qk = QuadKey(qk_type)
            self.assertIsNotNone(qk)
            self.assertEqual(qk.get_row(), 0)
            self.assertEqual(qk.get_col(), 0)
            self.assertEqual(qk.get_type(), qk_type)

    def test_copy_ctor(self):
        """Test the copying of a qk.QuadKey."""
        qk = QuadKey(Type_OsGeo)
        quad_key_copy = QuadKey(qk)
        self.assertEqual(qk, quad_key_copy)
        self.assertIsNotNone(quad_key_copy)
        self.assertEqual(qk.get_row(), 0)
        self.assertEqual(qk.get_col(), 0)
        self.assertEqual(qk.get_type(), Type_OsGeo)

    def test_assignment_operator(self):
        """Test the assignment of qk.QuadKey."""
        # This is not allowed in python

    def test_is_root_key(self):
        """Test if a qk.quad_key is the root key."""
        qk = QuadKey(Type_OsGeo)
        self.assertTrue(qk.is_root_key())

    def test_system_specifc_ctor(self):
        """Tests boundary case to see if constructed qk.quad_key is valid.
        """
        types = [Type__None, Type_Bing, Type_LatLon, Type_UlpQnr,
                 Type_OsGeo, Type_Morton]
        quad_key_none = QuadKey()
        for qk_type in types:
            for depth in range(1, 10):
                maxrows = QuadKey.max_rows(qk_type, depth)
                maxcols = QuadKey.max_cols(qk_type, depth)
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

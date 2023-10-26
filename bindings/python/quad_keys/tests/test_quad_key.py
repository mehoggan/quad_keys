"""
Unit Tests for quad_key
"""

from __future__ import print_function

import unittest

from quad_key.quad_key import quad_key
from quad_key.quad_key import type_none
from quad_key.quad_key import type_bing
from quad_key.quad_key import type_lat_long
from quad_key.quad_key import type_ulp_qnr
from quad_key.quad_key import type_osgeo
from quad_key.quad_key import type_morton


class Testquad_key(unittest.TestCase):
    """Class for running unit tests."""

    def test_default_ctor(self):
        """Test default construction of quad_key using type_bing."""
        qk = quad_key()
        self.assertIsNotNone(quad_key)
        self.assertEqual(qk.get_row(), 0)
        self.assertEqual(qk.get_col(), 0)
        self.assertEqual(qk.get_type(), type_none)
        self.assertEqual(qk.to_internal_string(), '')

    def test_ctor_only_type(self):
        """Test constructor which takes type."""
        types = [type_none, type_bing, type_lat_long, type_ulp_qnr,
                 type_osgeo, type_morton]
        for qk_type in types:
            assert isinstance(qk_type, int)
            qk = quad_key(qk_type)
            self.assertIsNotNone(quad_key)
            self.assertEqual(qk.get_row(), 0)
            self.assertEqual(qk.get_col(), 0)
            self.assertEqual(qk.get_type(), qk_type)

    def test_copy_ctor(self):
        """Test the copying of a qk.quad_key."""
        qk = quad_key(type_osgeo)
        quad_key_copy = quad_key(qk)
        self.assertEqual(qk, quad_key_copy)
        self.assertIsNotNone(quad_key_copy)
        self.assertEqual(qk.get_row(), 0)
        self.assertEqual(qk.get_col(), 0)
        self.assertEqual(qk.get_type(), type_osgeo)

    def test_assignment_operator(self):
        """Test the assignment of qk.quad_key."""
        # This is not allowed in python

    def test_is_root_key(self):
        """Test if a qk.quad_key is the root key."""
        qk = quad_key(type_osgeo)
        self.assertTrue(qk.is_root_key())

    def test_system_specifc_ctor(self):
        """Tests boundary case to see if constructed qk.quad_key is valid.
        """
        types = [type_none, type_bing, type_lat_long, type_ulp_qnr,
                 type_osgeo, type_morton]
        quad_key_none = quad_key()
        for qk_type in types:
            for depth in range(1, 10):
                maxrows = quad_key.max_rows(qk_type, depth)
                maxcols = quad_key.max_cols(qk_type, depth)
                assert isinstance(maxrows, int)
                assert isinstance(maxcols, int)
                quad_key_invalid = quad_key(qk_type, maxrows, maxcols, depth)
                self.assertEqual(quad_key_none, quad_key_invalid)

                validrow = max(0, maxrows - 1)
                validcol = max(0, maxcols - 1)
                assert isinstance(validrow, int)
                assert isinstance(validcol, int)
                quad_key_valid = quad_key(qk_type, validrow, validcol, depth)
                expected = quad_key(qk_type, validrow, validcol, depth)
                self.assertEqual(quad_key_valid, expected)

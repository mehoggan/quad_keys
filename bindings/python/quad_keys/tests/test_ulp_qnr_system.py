"""
Unit Tests for ulp_qnr System
"""

from __future__ import print_function

import unittest

from quad_key.quad_key import quad_key
from quad_key.quad_key import type_ulp_qnr
from quad_key.quad_key import geo_coordinate2d
from quad_key.quad_key import geo_coordinate_bounding_box2d
from quad_key.quad_key import longitude
from quad_key.quad_key import latitude


class Testulp_qnrSystem(unittest.TestCase):
    """Class for running unit tests."""

    def test_is_valid(self):
        """See Testquad_key.test_is_valid"""
        # Same as bing_system

    def test_is_root_key(self):
        """See Testquad_key.test_is_root_key"""
        # Same as bing_system

    def test_get_parent(self):
        """Test to get parent of a generically formatted quad_key."""
        # Same as bing_system

    def test_is_my_ancestor(self):
        """Checks to see if specified quad_key up in the hierarchy is an
        "ancestor" of the given quad_key.
        """
        # Same as bing_system

    def test_get_ancestor(self):
        """Gets the ancestor up the tree according to a delta provided."""
        # Same as bing_system

    def test_get_child(self):
        """Get a single child NE, SE, NW, SW"""
        # Same as bing_system

    def test_get_children(self):
        """Get all the childern of a quad_key."""
        # Same as bing_system

    def test_get_descendants(self):
        """Get all the defendants at some delta in the tree."""
        # Same as bing_system

    def test_get_siblings(self):
        """Test to get siblings of a given quad_key."""
        # Same as bing_system

    def test_get_neighbors(self):
        """Test to get the neighbors of a given quad_key."""
        # Same as bing_system

    def test_to_string_from_string(self):
        """Test to convert an internally formatted string and back."""
        qk_type = type_ulp_qnr

        qk = quad_key(qk_type, 0, 0, 0)
        fmt = qk.to_internal_string()
        self.assertEquals("1", fmt)
        quad_key_back = quad_key.from_internal_string(qk_type, fmt)
        self.assertTrue(qk == quad_key_back)

        qk = quad_key(qk_type, 0, 0, 1)
        fmt = qk.to_internal_string()
        self.assertEquals("4", fmt)
        quad_key_back = quad_key.from_internal_string(qk_type, fmt)
        self.assertTrue(qk == quad_key_back)

        qk = quad_key(qk_type, 0, 1, 1)
        fmt = qk.to_internal_string()
        self.assertEquals("5", fmt)
        quad_key_back = quad_key.from_internal_string(qk_type, fmt)
        self.assertTrue(qk == quad_key_back)

        qk = quad_key(qk_type, 0, 0, 2)
        fmt = qk.to_internal_string()
        self.assertEquals("16", fmt)
        quad_key_back = quad_key.from_internal_string(qk_type, fmt)
        self.assertTrue(qk == quad_key_back)

        qk = quad_key(qk_type, 0, 1, 2)
        fmt = qk.to_internal_string()
        self.assertEquals("17", fmt)
        quad_key_back = quad_key.from_internal_string(qk_type, fmt)
        self.assertTrue(qk == quad_key_back)

        qk = quad_key(qk_type, 1, 0, 2)
        fmt = qk.to_internal_string()
        self.assertEquals("20", fmt)
        quad_key_back = quad_key.from_internal_string(qk_type, fmt)
        self.assertTrue(qk == quad_key_back)

        qk = quad_key(qk_type, 1, 1, 2)
        fmt = qk.to_internal_string()
        self.assertEquals("21", fmt)
        quad_key_back = quad_key.from_internal_string(qk_type, fmt)
        self.assertTrue(qk == quad_key_back)

        qk = quad_key(qk_type, 0, 2, 2)
        fmt = qk.to_internal_string()
        self.assertEquals("18", fmt)
        quad_key_back = quad_key.from_internal_string(qk_type, fmt)
        self.assertTrue(qk == quad_key_back)

        qk = quad_key(qk_type, 0, 3, 2)
        fmt = qk.to_internal_string()
        self.assertEquals("19", fmt)
        quad_key_back = quad_key.from_internal_string(qk_type, fmt)
        self.assertTrue(qk == quad_key_back)

        qk = quad_key(qk_type, 1, 2, 2)
        fmt = qk.to_internal_string()
        self.assertEquals("22", fmt)
        quad_key_back = quad_key.from_internal_string(qk_type, fmt)
        self.assertTrue(qk == quad_key_back)

        qk = quad_key(qk_type, 1, 3, 2)
        fmt = qk.to_internal_string()
        self.assertEquals("23", fmt)
        quad_key_back = quad_key.from_internal_string(qk_type, fmt)
        self.assertTrue(qk == quad_key_back)

        # For Sanity Purposes and to Verify NO Fence Post Erros. Use a bit of
        # brute force.
        for i in range(64, 64 + 32):
            row = (i - 64) / 8
            col = (i - 64) % 8
            qk = quad_key(qk_type, int(row), int(col), 3)
            qk = quad_key(qk_type, row, col, 3)
            fmt = qk.to_internal_string()
            expected_str = str(i)

            self.assertEquals(expected_str, fmt)
            quad_key_back = quad_key.from_internal_string(qk_type, fmt)
            self.assertTrue(qk == quad_key_back)

        qk = quad_key(qk_type, 0, 0, 3)
        fmt = qk.to_internal_string()
        self.assertEquals("64", fmt)
        quad_key_back = quad_key.from_internal_string(qk_type, fmt)
        self.assertTrue(qk == quad_key_back)

    def test_get_geo_coordinate_bounds_2d(self):
        """Test to get geographic bounds of quad_key."""
        bbox = geo_coordinate_bounding_box2d()

        qk = quad_key(type_ulp_qnr, 0, 0, 0)
        qk.get_geo_coordinate_bounds2d(bbox)
        self.assertTrue(bbox.lower_left().near(geo_coordinate2d(
            longitude(-180.0), latitude(-90.0)), 1e-4))
        self.assertTrue(bbox.upper_right().near(geo_coordinate2d(
            longitude(+180.0), latitude(+90.0)), 1e-4))

        qk = quad_key(type_ulp_qnr, 0, 0, 1)
        qk.get_geo_coordinate_bounds2d(bbox)
        self.assertTrue(bbox.lower_left().near(geo_coordinate2d(
            longitude(-180.0), latitude(-90.0)), 1e-4))
        self.assertTrue(bbox.upper_right().near(geo_coordinate2d(
            longitude(+0.0), latitude(+90.0)), 1e-4))

        qk = quad_key(type_ulp_qnr, 0, 1, 1)
        qk.get_geo_coordinate_bounds2d(bbox)
        self.assertTrue(bbox.lower_left().near(geo_coordinate2d(
            longitude(+0.0), latitude(-90.0)), 1e-4))
        self.assertTrue(bbox.upper_right().near(geo_coordinate2d(
            longitude(+180.0), latitude(+90.0)), 1e-4))

        qk = quad_key(type_ulp_qnr, 0, 0, 2)
        qk.get_geo_coordinate_bounds2d(bbox)
        self.assertTrue(bbox.lower_left().near(geo_coordinate2d(
            longitude(-180.0), latitude(-90.0)), 1e-4))
        self.assertTrue(bbox.upper_right().near(geo_coordinate2d(
            longitude(-90.0), latitude(+0.0)), 1e-4))

        qk = quad_key(type_ulp_qnr, 0, 1, 2)
        qk.get_geo_coordinate_bounds2d(bbox)
        self.assertTrue(bbox.lower_left().near(geo_coordinate2d(
            longitude(-90.0), latitude(-90.0)), 1e-4))
        self.assertTrue(bbox.upper_right().near(geo_coordinate2d(
            longitude(+0.0),
            latitude(+0.0)), 1e-4))

        qk = quad_key(type_ulp_qnr, 1, 0, 2)
        qk.get_geo_coordinate_bounds2d(bbox)
        self.assertTrue(bbox.lower_left().near(geo_coordinate2d(
            longitude(-180.0), latitude(+0.0)), 1e-4))
        self.assertTrue(bbox.upper_right().near(geo_coordinate2d(
            longitude(-90.0), latitude(+90.0)), 1e-4))

        qk = quad_key(type_ulp_qnr, 1, 1, 2)
        qk.get_geo_coordinate_bounds2d(bbox)
        self.assertTrue(bbox.lower_left().near(geo_coordinate2d(
            longitude(-90.0), latitude(+0.0)), 1e-4))
        self.assertTrue(bbox.upper_right().near(geo_coordinate2d(
            longitude(+0.0), latitude(+90.0)), 1e-4))

        qk = quad_key(type_ulp_qnr, 0, 2, 2)
        qk.get_geo_coordinate_bounds2d(bbox)
        self.assertTrue(bbox.lower_left().near(geo_coordinate2d(
            longitude(+0.0), latitude(-90.0)), 1e-4))
        self.assertTrue(bbox.upper_right().near(geo_coordinate2d(
            longitude(+90.0), latitude(+0.0)), 1e-4))

        qk = quad_key(type_ulp_qnr, 0, 3, 2)
        qk.get_geo_coordinate_bounds2d(bbox)
        self.assertTrue(bbox.lower_left().near(geo_coordinate2d(
            longitude(+90.0), latitude(-90.0)), 1e-4))
        self.assertTrue(bbox.upper_right().near(geo_coordinate2d(
            longitude(+180.0), latitude(+0.0)), 1e-4))

        qk = quad_key(type_ulp_qnr, 1, 2, 2)
        qk.get_geo_coordinate_bounds2d(bbox)
        self.assertTrue(bbox.lower_left().near(geo_coordinate2d(
            longitude(+0.0), latitude(+0.0)), 1e-4))
        self.assertTrue(bbox.upper_right().near(geo_coordinate2d(
            longitude(+90.0), latitude(+90.0)), 1e-4))

        qk = quad_key(type_ulp_qnr, 1, 3, 2)
        qk.get_geo_coordinate_bounds2d(bbox)
        self.assertTrue(bbox.lower_left().near(geo_coordinate2d(
            longitude(+90.0), latitude(+0.0)), 1e-4))
        self.assertTrue(bbox.upper_right().near(geo_coordinate2d(
            longitude(+180.0), latitude(+90.0)), 1e-4))

    def test_get_key_from_longitude_latitude_at_depth_to_bounds(self):
        """Test to get a quad_key from longitude and latitude and then get
        bounds.
        """
        qk = quad_key.get_key_from_longitude_latitude_at_depth(
            type_ulp_qnr,
            geo_coordinate2d(longitude(-180.0), latitude(-90.0)), 0)
        self.assertEqual("1", qk.to_internal_string())
        qk = quad_key.get_key_from_longitude_latitude_at_depth(
            type_ulp_qnr,
            geo_coordinate2d(longitude(0.0), latitude(0.0)), 0)
        self.assertEqual("1", qk.to_internal_string())

        qk = quad_key.get_key_from_longitude_latitude_at_depth(
            type_ulp_qnr,
            geo_coordinate2d(longitude(-180.0), latitude(-90.0)), 1)
        self.assertEqual("4", qk.to_internal_string())
        qk = quad_key.get_key_from_longitude_latitude_at_depth(
            type_ulp_qnr,
            geo_coordinate2d(longitude(-180.0), latitude(90.0)), 1)
        self.assertEqual("4", qk.to_internal_string())
        qk = quad_key.get_key_from_longitude_latitude_at_depth(
            type_ulp_qnr,
            geo_coordinate2d(longitude(0.1), latitude(-90.0)), 1)
        self.assertEqual("5", qk.to_internal_string())
        qk = quad_key.get_key_from_longitude_latitude_at_depth(
            type_ulp_qnr,
            geo_coordinate2d(longitude(180.0), latitude(90.0)), 1)
        self.assertEqual("5", qk.to_internal_string())

        qk = quad_key.get_key_from_longitude_latitude_at_depth(
            type_ulp_qnr,
            geo_coordinate2d(longitude(-180.0), latitude(-90.0)), 2)
        self.assertEqual("16", qk.to_internal_string())
        qk = quad_key.get_key_from_longitude_latitude_at_depth(
            type_ulp_qnr,
            geo_coordinate2d(longitude(-89.9), latitude(-90.0)), 2)
        self.assertEqual("17", qk.to_internal_string())
        qk = quad_key.get_key_from_longitude_latitude_at_depth(
            type_ulp_qnr,
            geo_coordinate2d(longitude(0.1), latitude(-90.0)), 2)
        self.assertEqual("18", qk.to_internal_string())
        qk = quad_key.get_key_from_longitude_latitude_at_depth(
            type_ulp_qnr,
            geo_coordinate2d(longitude(90.1), latitude(-90.0)), 2)
        self.assertEqual("19", qk.to_internal_string())
        qk = quad_key.get_key_from_longitude_latitude_at_depth(
            type_ulp_qnr,
            geo_coordinate2d(longitude(-180.0), latitude(89.0)), 2)
        self.assertEqual("20", qk.to_internal_string())
        qk = quad_key.get_key_from_longitude_latitude_at_depth(
            type_ulp_qnr,
            geo_coordinate2d(longitude(-89.9), latitude(0.1)), 2)
        self.assertEqual("21", qk.to_internal_string())
        qk = quad_key.get_key_from_longitude_latitude_at_depth(
            type_ulp_qnr,
            geo_coordinate2d(longitude(0.1), latitude(0.1)), 2)
        self.assertEqual("22", qk.to_internal_string())
        qk = quad_key.get_key_from_longitude_latitude_at_depth(
            type_ulp_qnr,
            geo_coordinate2d(longitude(90.1), latitude(0.1)), 2)
        self.assertEqual("23", qk.to_internal_string())

    def test_get_keys_from_longitude_latitude_bounding_box(self):
        """Test to get the bounding box of a quad_key."""
        # Select Entire Earth
        quad_keys = quad_key.get_keys_from_longitude_latitude_bounding_box(
            type_ulp_qnr,
            geo_coordinate_bounding_box2d(
                geo_coordinate2d(longitude(-180.0), latitude(-90.0)),
                geo_coordinate2d(longitude(180.0), latitude(90.0))), 0)
        qk = quad_key.from_internal_string(type_ulp_qnr, "1")
        self.assertEqual(1, quad_keys.size())
        self.assertTrue(qk in quad_keys)

        # Select Very Center of the Earth
        quad_keys = quad_key.get_keys_from_longitude_latitude_bounding_box(
            type_ulp_qnr,
            geo_coordinate_bounding_box2d(
                geo_coordinate2d(longitude(-0.1), latitude(-0.1)),
                geo_coordinate2d(longitude(0.1), latitude(0.1))), 0)
        qk = quad_key.from_internal_string(type_ulp_qnr, "1")
        self.assertEqual(1, quad_keys.size())
        self.assertTrue(qk in quad_keys)

        # Select Western Hemisphere
        quad_keys = quad_key.get_keys_from_longitude_latitude_bounding_box(
            type_ulp_qnr,
            geo_coordinate_bounding_box2d(
                geo_coordinate2d(longitude(-180.0), latitude(-90.0)),
                geo_coordinate2d(longitude(0.0), latitude(90.0))), 1)
        qk = quad_key.from_internal_string(type_ulp_qnr, "4")
        self.assertEqual(1, quad_keys.size())
        self.assertTrue(qk in quad_keys)

        # Select Eastern Hemisphere
        quad_keys = quad_key.get_keys_from_longitude_latitude_bounding_box(
            type_ulp_qnr,
            geo_coordinate_bounding_box2d(
                geo_coordinate2d(longitude(0.1), latitude(-90.0)),
                geo_coordinate2d(longitude(180), latitude(90.0))), 1)
        qk = quad_key.from_internal_string(type_ulp_qnr, "5")
        self.assertEqual(1, quad_keys.size())
        self.assertTrue(qk in quad_keys)

        # Select Entire Planet
        quad_keys = quad_key.get_keys_from_longitude_latitude_bounding_box(
            type_ulp_qnr,
            geo_coordinate_bounding_box2d(
                geo_coordinate2d(longitude(-180.0), latitude(-90.0)),
                geo_coordinate2d(longitude(180), latitude(90.0))), 1)
        quad_keya = quad_key.from_internal_string(type_ulp_qnr, "4")
        quad_keyb = quad_key.from_internal_string(type_ulp_qnr, "5")
        self.assertEqual(2, quad_keys.size())
        self.assertTrue(quad_keya in quad_keys)
        self.assertTrue(quad_keyb in quad_keys)

        # Select South West Corner
        quad_keys = quad_key.get_keys_from_longitude_latitude_bounding_box(
            type_ulp_qnr,
            geo_coordinate_bounding_box2d(
                geo_coordinate2d(longitude(-180.0), latitude(-90.0)),
                geo_coordinate2d(longitude(-90.0), latitude(0.0))), 2)
        qk = quad_key.from_internal_string(type_ulp_qnr, "16")
        self.assertEqual(1, quad_keys.size())
        self.assertTrue(qk in quad_keys)

        # Select South America
        quad_keys = quad_key.get_keys_from_longitude_latitude_bounding_box(
            type_ulp_qnr,
            geo_coordinate_bounding_box2d(
                geo_coordinate2d(longitude(-89.9), latitude(-90.0)),
                geo_coordinate2d(longitude(0.0), latitude(0.0))), 2)
        qk = quad_key.from_internal_string(type_ulp_qnr, "17")
        self.assertEqual(1, quad_keys.size())
        self.assertTrue(qk in quad_keys)

        # Select North West Corner
        quad_keys = quad_key.get_keys_from_longitude_latitude_bounding_box(
            type_ulp_qnr,
            geo_coordinate_bounding_box2d(
                geo_coordinate2d(longitude(-180.0), latitude(0.1)),
                geo_coordinate2d(longitude(-90.0), latitude(90.0))), 2)
        qk = quad_key.from_internal_string(type_ulp_qnr, "20")
        self.assertEqual(1, quad_keys.size())
        self.assertTrue(qk in quad_keys)

        # Select Greenland
        quad_keys = quad_key.get_keys_from_longitude_latitude_bounding_box(
            type_ulp_qnr,
            geo_coordinate_bounding_box2d(
                geo_coordinate2d(longitude(-89.9), latitude(0.1)),
                geo_coordinate2d(longitude(0.0), latitude(90.0))), 2)
        qk = quad_key.from_internal_string(type_ulp_qnr, "21")
        self.assertEqual(1, quad_keys.size())
        self.assertTrue(qk in quad_keys)

        # Select South Pole
        quad_keys = quad_key.get_keys_from_longitude_latitude_bounding_box(
            type_ulp_qnr,
            geo_coordinate_bounding_box2d(
                geo_coordinate2d(longitude(0.1), latitude(-90.0)),
                geo_coordinate2d(longitude(90.0), latitude(0.0))), 2)
        qk = quad_key.from_internal_string(type_ulp_qnr, "18")
        self.assertEqual(1, quad_keys.size())
        self.assertTrue(qk in quad_keys)

        # Select South East Corner
        quad_keys = quad_key.get_keys_from_longitude_latitude_bounding_box(
            type_ulp_qnr,
            geo_coordinate_bounding_box2d(
                geo_coordinate2d(longitude(90.1), latitude(-90.0)),
                geo_coordinate2d(longitude(180.0), latitude(0.0))), 2)
        qk = quad_key.from_internal_string(type_ulp_qnr, "19")
        self.assertEqual(1, quad_keys.size())
        self.assertTrue(qk in quad_keys)

        # Select Over Europe
        quad_keys = quad_key.get_keys_from_longitude_latitude_bounding_box(
            type_ulp_qnr,
            geo_coordinate_bounding_box2d(
                geo_coordinate2d(longitude(0.1), latitude(0.1)),
                geo_coordinate2d(longitude(90.0), latitude(90.0))), 2)
        qk = quad_key.from_internal_string(type_ulp_qnr, "22")
        self.assertEqual(1, quad_keys.size())
        self.assertTrue(qk in quad_keys)

        # Select North East Corner
        quad_keys = quad_key.get_keys_from_longitude_latitude_bounding_box(
            type_ulp_qnr,
            geo_coordinate_bounding_box2d(
                geo_coordinate2d(longitude(90.1), latitude(0.1)),
                geo_coordinate2d(longitude(180.0), latitude(90.0))), 2)

        qk = quad_key.from_internal_string(type_ulp_qnr, "23")
        self.assertEqual(1, quad_keys.size())
        self.assertTrue(qk in quad_keys)

        # Select Entire Map
        quad_keys = quad_key.get_keys_from_longitude_latitude_bounding_box(
            type_ulp_qnr,
            geo_coordinate_bounding_box2d(
                geo_coordinate2d(longitude(-179.9), latitude(-89.9)),
                geo_coordinate2d(longitude(90.1), latitude(0.1))), 2)

        quad_key0 = quad_key.from_internal_string(type_ulp_qnr, "16")
        quad_key1 = quad_key.from_internal_string(type_ulp_qnr, "17")
        quad_key2 = quad_key.from_internal_string(type_ulp_qnr, "18")
        quad_key3 = quad_key.from_internal_string(type_ulp_qnr, "19")
        quad_key4 = quad_key.from_internal_string(type_ulp_qnr, "20")
        quad_key5 = quad_key.from_internal_string(type_ulp_qnr, "21")
        quad_key6 = quad_key.from_internal_string(type_ulp_qnr, "22")
        quad_key7 = quad_key.from_internal_string(type_ulp_qnr, "23")
        self.assertEqual(8, quad_keys.size())
        self.assertTrue(quad_key0 in quad_keys)
        self.assertTrue(quad_key1 in quad_keys)
        self.assertTrue(quad_key2 in quad_keys)
        self.assertTrue(quad_key3 in quad_keys)
        self.assertTrue(quad_key4 in quad_keys)
        self.assertTrue(quad_key5 in quad_keys)
        self.assertTrue(quad_key6 in quad_keys)
        self.assertTrue(quad_key7 in quad_keys)

    def test_selected_cities(self):
        """Test a given set of known places make sure they work."""

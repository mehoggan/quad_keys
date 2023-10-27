"""
Unit Tests for ulp_qnr System
"""

from __future__ import print_function

import unittest

from quad_keys.quad_keys import QuadKey
from quad_keys.quad_keys import Type_UlpQnr
from quad_keys.quad_keys import GeoCoordinate2d
from quad_keys.quad_keys import GeoCoordinateBoundingBox2d
from quad_keys.quad_keys import Longitude
from quad_keys.quad_keys import Latitude


class TestUlpQnrSystem(unittest.TestCase):
    """Class for running unit tests."""

    def test_is_valid(self):
        """See TestQuadKey.test_is_valid"""
        # Same as bing_system

    def test_is_root_key(self):
        """See TestQuadKey.test_is_root_key"""
        # Same as bing_system

    def test_get_parent(self):
        """Test to get parent of a generically formatted QuadKey."""
        # Same as bing_system

    def test_is_my_ancestor(self):
        """Checks to see if specified quad_key up in the hierarchy is an
        "ancestor" of the given QuadKey.
        """
        # Same as bing_system

    def test_get_ancestor(self):
        """Gets the ancestor up the tree according to a delta provided."""
        # Same as bing_system

    def test_get_child(self):
        """Get a single child NE, SE, NW, SW"""
        # Same as bing_system

    def test_get_children(self):
        """Get all the childern of a QuadKey."""
        # Same as bing_system

    def test_get_descendants(self):
        """Get all the defendants at some delta in the tree."""
        # Same as bing_system

    def test_get_siblings(self):
        """Test to get siblings of a given QuadKey."""
        # Same as bing_system

    def test_get_neighbors(self):
        """Test to get the neighbors of a given QuadKey."""
        # Same as bing_system

    def test_to_string_from_string(self):  # noqa E501  # pylint: disable = too-many-statements
        """Test to convert an internally formatted string and back."""
        qk_type = Type_UlpQnr

        qk = QuadKey(qk_type, 0, 0, 0)
        fmt = qk.to_internal_string()
        self.assertEqual("1", fmt)
        quad_key_back = QuadKey.from_internal_string(qk_type, fmt)
        self.assertTrue(qk == quad_key_back)

        qk = QuadKey(qk_type, 0, 0, 1)
        fmt = qk.to_internal_string()
        self.assertEqual("4", fmt)
        quad_key_back = QuadKey.from_internal_string(qk_type, fmt)
        self.assertTrue(qk == quad_key_back)

        qk = QuadKey(qk_type, 0, 1, 1)
        fmt = qk.to_internal_string()
        self.assertEqual("5", fmt)
        quad_key_back = QuadKey.from_internal_string(qk_type, fmt)
        self.assertTrue(qk == quad_key_back)

        qk = QuadKey(qk_type, 0, 0, 2)
        fmt = qk.to_internal_string()
        self.assertEqual("16", fmt)
        quad_key_back = QuadKey.from_internal_string(qk_type, fmt)
        self.assertTrue(qk == quad_key_back)

        qk = QuadKey(qk_type, 0, 1, 2)
        fmt = qk.to_internal_string()
        self.assertEqual("17", fmt)
        quad_key_back = QuadKey.from_internal_string(qk_type, fmt)
        self.assertTrue(qk == quad_key_back)

        qk = QuadKey(qk_type, 1, 0, 2)
        fmt = qk.to_internal_string()
        self.assertEqual("20", fmt)
        quad_key_back = QuadKey.from_internal_string(qk_type, fmt)
        self.assertTrue(qk == quad_key_back)

        qk = QuadKey(qk_type, 1, 1, 2)
        fmt = qk.to_internal_string()
        self.assertEqual("21", fmt)
        quad_key_back = QuadKey.from_internal_string(qk_type, fmt)
        self.assertTrue(qk == quad_key_back)

        qk = QuadKey(qk_type, 0, 2, 2)
        fmt = qk.to_internal_string()
        self.assertEqual("18", fmt)
        quad_key_back = QuadKey.from_internal_string(qk_type, fmt)
        self.assertTrue(qk == quad_key_back)

        qk = QuadKey(qk_type, 0, 3, 2)
        fmt = qk.to_internal_string()
        self.assertEqual("19", fmt)
        quad_key_back = QuadKey.from_internal_string(qk_type, fmt)
        self.assertTrue(qk == quad_key_back)

        qk = QuadKey(qk_type, 1, 2, 2)
        fmt = qk.to_internal_string()
        self.assertEqual("22", fmt)
        quad_key_back = QuadKey.from_internal_string(qk_type, fmt)
        self.assertTrue(qk == quad_key_back)

        qk = QuadKey(qk_type, 1, 3, 2)
        fmt = qk.to_internal_string()
        self.assertEqual("23", fmt)
        quad_key_back = QuadKey.from_internal_string(qk_type, fmt)
        self.assertTrue(qk == quad_key_back)

        # For Sanity Purposes and to Verify NO Fence Post Erros. Use a bit of
        # brute force.
        for i in range(64, 64 + 32):
            row = int((i - 64) / 8)
            col = int((i - 64) % 8)
            qk = QuadKey(qk_type, int(row), int(col), 3)
            qk = QuadKey(qk_type, row, col, 3)
            fmt = qk.to_internal_string()
            expected_str = str(i)

            self.assertEqual(expected_str, fmt)
            quad_key_back = QuadKey.from_internal_string(qk_type, fmt)
            self.assertTrue(qk == quad_key_back)

        qk = QuadKey(qk_type, 0, 0, 3)
        fmt = qk.to_internal_string()
        self.assertEqual("64", fmt)
        quad_key_back = QuadKey.from_internal_string(qk_type, fmt)
        self.assertTrue(qk == quad_key_back)

    def test_get_geo_coordinate_bounds_2d(self):
        """Test to get geographic bounds of QuadKey."""
        bbox = GeoCoordinateBoundingBox2d()

        qk = QuadKey(Type_UlpQnr, 0, 0, 0)
        qk.get_geo_coordinate_bounds2d(bbox)
        self.assertTrue(bbox.lower_left().near(GeoCoordinate2d(
            Longitude(-180.0), Latitude(-90.0)), 1e-4))
        self.assertTrue(bbox.upper_right().near(GeoCoordinate2d(
            Longitude(+180.0), Latitude(+90.0)), 1e-4))

        qk = QuadKey(Type_UlpQnr, 0, 0, 1)
        qk.get_geo_coordinate_bounds2d(bbox)
        self.assertTrue(bbox.lower_left().near(GeoCoordinate2d(
            Longitude(-180.0), Latitude(-90.0)), 1e-4))
        self.assertTrue(bbox.upper_right().near(GeoCoordinate2d(
            Longitude(+0.0), Latitude(+90.0)), 1e-4))

        qk = QuadKey(Type_UlpQnr, 0, 1, 1)
        qk.get_geo_coordinate_bounds2d(bbox)
        self.assertTrue(bbox.lower_left().near(GeoCoordinate2d(
            Longitude(+0.0), Latitude(-90.0)), 1e-4))
        self.assertTrue(bbox.upper_right().near(GeoCoordinate2d(
            Longitude(+180.0), Latitude(+90.0)), 1e-4))

        qk = QuadKey(Type_UlpQnr, 0, 0, 2)
        qk.get_geo_coordinate_bounds2d(bbox)
        self.assertTrue(bbox.lower_left().near(GeoCoordinate2d(
            Longitude(-180.0), Latitude(-90.0)), 1e-4))
        self.assertTrue(bbox.upper_right().near(GeoCoordinate2d(
            Longitude(-90.0), Latitude(+0.0)), 1e-4))

        qk = QuadKey(Type_UlpQnr, 0, 1, 2)
        qk.get_geo_coordinate_bounds2d(bbox)
        self.assertTrue(bbox.lower_left().near(GeoCoordinate2d(
            Longitude(-90.0), Latitude(-90.0)), 1e-4))
        self.assertTrue(bbox.upper_right().near(GeoCoordinate2d(
            Longitude(+0.0),
            Latitude(+0.0)), 1e-4))

        qk = QuadKey(Type_UlpQnr, 1, 0, 2)
        qk.get_geo_coordinate_bounds2d(bbox)
        self.assertTrue(bbox.lower_left().near(GeoCoordinate2d(
            Longitude(-180.0), Latitude(+0.0)), 1e-4))
        self.assertTrue(bbox.upper_right().near(GeoCoordinate2d(
            Longitude(-90.0), Latitude(+90.0)), 1e-4))

        qk = QuadKey(Type_UlpQnr, 1, 1, 2)
        qk.get_geo_coordinate_bounds2d(bbox)
        self.assertTrue(bbox.lower_left().near(GeoCoordinate2d(
            Longitude(-90.0), Latitude(+0.0)), 1e-4))
        self.assertTrue(bbox.upper_right().near(GeoCoordinate2d(
            Longitude(+0.0), Latitude(+90.0)), 1e-4))

        qk = QuadKey(Type_UlpQnr, 0, 2, 2)
        qk.get_geo_coordinate_bounds2d(bbox)
        self.assertTrue(bbox.lower_left().near(GeoCoordinate2d(
            Longitude(+0.0), Latitude(-90.0)), 1e-4))
        self.assertTrue(bbox.upper_right().near(GeoCoordinate2d(
            Longitude(+90.0), Latitude(+0.0)), 1e-4))

        qk = QuadKey(Type_UlpQnr, 0, 3, 2)
        qk.get_geo_coordinate_bounds2d(bbox)
        self.assertTrue(bbox.lower_left().near(GeoCoordinate2d(
            Longitude(+90.0), Latitude(-90.0)), 1e-4))
        self.assertTrue(bbox.upper_right().near(GeoCoordinate2d(
            Longitude(+180.0), Latitude(+0.0)), 1e-4))

        qk = QuadKey(Type_UlpQnr, 1, 2, 2)
        qk.get_geo_coordinate_bounds2d(bbox)
        self.assertTrue(bbox.lower_left().near(GeoCoordinate2d(
            Longitude(+0.0), Latitude(+0.0)), 1e-4))
        self.assertTrue(bbox.upper_right().near(GeoCoordinate2d(
            Longitude(+90.0), Latitude(+90.0)), 1e-4))

        qk = QuadKey(Type_UlpQnr, 1, 3, 2)
        qk.get_geo_coordinate_bounds2d(bbox)
        self.assertTrue(bbox.lower_left().near(GeoCoordinate2d(
            Longitude(+90.0), Latitude(+0.0)), 1e-4))
        self.assertTrue(bbox.upper_right().near(GeoCoordinate2d(
            Longitude(+180.0), Latitude(+90.0)), 1e-4))

    def test_get_key_from_longitude_latitude_at_depth_to_bounds(self):
        """Test to get a quad_key from longitude and latitude and then get
        bounds.
        """
        qk = QuadKey.get_key_from_longitude_latitude_at_depth(
            Type_UlpQnr,
            GeoCoordinate2d(Longitude(-180.0), Latitude(-90.0)), 0)
        self.assertEqual("1", qk.to_internal_string())
        qk = QuadKey.get_key_from_longitude_latitude_at_depth(
            Type_UlpQnr,
            GeoCoordinate2d(Longitude(0.0), Latitude(0.0)), 0)
        self.assertEqual("1", qk.to_internal_string())

        qk = QuadKey.get_key_from_longitude_latitude_at_depth(
            Type_UlpQnr,
            GeoCoordinate2d(Longitude(-180.0), Latitude(-90.0)), 1)
        self.assertEqual("4", qk.to_internal_string())
        qk = QuadKey.get_key_from_longitude_latitude_at_depth(
            Type_UlpQnr,
            GeoCoordinate2d(Longitude(-180.0), Latitude(90.0)), 1)
        self.assertEqual("4", qk.to_internal_string())
        qk = QuadKey.get_key_from_longitude_latitude_at_depth(
            Type_UlpQnr,
            GeoCoordinate2d(Longitude(0.1), Latitude(-90.0)), 1)
        self.assertEqual("5", qk.to_internal_string())
        qk = QuadKey.get_key_from_longitude_latitude_at_depth(
            Type_UlpQnr,
            GeoCoordinate2d(Longitude(180.0), Latitude(90.0)), 1)
        self.assertEqual("5", qk.to_internal_string())

        qk = QuadKey.get_key_from_longitude_latitude_at_depth(
            Type_UlpQnr,
            GeoCoordinate2d(Longitude(-180.0), Latitude(-90.0)), 2)
        self.assertEqual("16", qk.to_internal_string())
        qk = QuadKey.get_key_from_longitude_latitude_at_depth(
            Type_UlpQnr,
            GeoCoordinate2d(Longitude(-89.9), Latitude(-90.0)), 2)
        self.assertEqual("17", qk.to_internal_string())
        qk = QuadKey.get_key_from_longitude_latitude_at_depth(
            Type_UlpQnr,
            GeoCoordinate2d(Longitude(0.1), Latitude(-90.0)), 2)
        self.assertEqual("18", qk.to_internal_string())
        qk = QuadKey.get_key_from_longitude_latitude_at_depth(
            Type_UlpQnr,
            GeoCoordinate2d(Longitude(90.1), Latitude(-90.0)), 2)
        self.assertEqual("19", qk.to_internal_string())
        qk = QuadKey.get_key_from_longitude_latitude_at_depth(
            Type_UlpQnr,
            GeoCoordinate2d(Longitude(-180.0), Latitude(89.0)), 2)
        self.assertEqual("20", qk.to_internal_string())
        qk = QuadKey.get_key_from_longitude_latitude_at_depth(
            Type_UlpQnr,
            GeoCoordinate2d(Longitude(-89.9), Latitude(0.1)), 2)
        self.assertEqual("21", qk.to_internal_string())
        qk = QuadKey.get_key_from_longitude_latitude_at_depth(
            Type_UlpQnr,
            GeoCoordinate2d(Longitude(0.1), Latitude(0.1)), 2)
        self.assertEqual("22", qk.to_internal_string())
        qk = QuadKey.get_key_from_longitude_latitude_at_depth(
            Type_UlpQnr,
            GeoCoordinate2d(Longitude(90.1), Latitude(0.1)), 2)
        self.assertEqual("23", qk.to_internal_string())

    def test_get_keys_from_longitude_latitude_bounding_box(self):  # noqa E501  # pylint: disable = too-many-statements
        """Test to get the bounding box of a QuadKey."""
        # Select Entire Earth
        quad_keys = QuadKey.get_keys_from_longitude_latitude_bounding_box(
            Type_UlpQnr,
            GeoCoordinateBoundingBox2d(
                GeoCoordinate2d(Longitude(-180.0), Latitude(-90.0)),
                GeoCoordinate2d(Longitude(180.0), Latitude(90.0))), 0)
        qk = QuadKey.from_internal_string(Type_UlpQnr, "1")
        self.assertEqual(1, quad_keys.size())
        self.assertTrue(qk in quad_keys)

        # Select Very Center of the Earth
        quad_keys = QuadKey.get_keys_from_longitude_latitude_bounding_box(
            Type_UlpQnr,
            GeoCoordinateBoundingBox2d(
                GeoCoordinate2d(Longitude(-0.1), Latitude(-0.1)),
                GeoCoordinate2d(Longitude(0.1), Latitude(0.1))), 0)
        qk = QuadKey.from_internal_string(Type_UlpQnr, "1")
        self.assertEqual(1, quad_keys.size())
        self.assertTrue(qk in quad_keys)

        # Select Western Hemisphere
        quad_keys = QuadKey.get_keys_from_longitude_latitude_bounding_box(
            Type_UlpQnr,
            GeoCoordinateBoundingBox2d(
                GeoCoordinate2d(Longitude(-180.0), Latitude(-90.0)),
                GeoCoordinate2d(Longitude(0.0), Latitude(90.0))), 1)
        qk = QuadKey.from_internal_string(Type_UlpQnr, "4")
        self.assertEqual(1, quad_keys.size())
        self.assertTrue(qk in quad_keys)

        # Select Eastern Hemisphere
        quad_keys = QuadKey.get_keys_from_longitude_latitude_bounding_box(
            Type_UlpQnr,
            GeoCoordinateBoundingBox2d(
                GeoCoordinate2d(Longitude(0.1), Latitude(-90.0)),
                GeoCoordinate2d(Longitude(180), Latitude(90.0))), 1)
        qk = QuadKey.from_internal_string(Type_UlpQnr, "5")
        self.assertEqual(1, quad_keys.size())
        self.assertTrue(qk in quad_keys)

        # Select Entire Planet
        quad_keys = QuadKey.get_keys_from_longitude_latitude_bounding_box(
            Type_UlpQnr,
            GeoCoordinateBoundingBox2d(
                GeoCoordinate2d(Longitude(-180.0), Latitude(-90.0)),
                GeoCoordinate2d(Longitude(180), Latitude(90.0))), 1)
        quad_keya = QuadKey.from_internal_string(Type_UlpQnr, "4")
        quad_keyb = QuadKey.from_internal_string(Type_UlpQnr, "5")
        self.assertEqual(2, quad_keys.size())
        self.assertTrue(quad_keya in quad_keys)
        self.assertTrue(quad_keyb in quad_keys)

        # Select South West Corner
        quad_keys = QuadKey.get_keys_from_longitude_latitude_bounding_box(
            Type_UlpQnr,
            GeoCoordinateBoundingBox2d(
                GeoCoordinate2d(Longitude(-180.0), Latitude(-90.0)),
                GeoCoordinate2d(Longitude(-90.0), Latitude(0.0))), 2)
        qk = QuadKey.from_internal_string(Type_UlpQnr, "16")
        self.assertEqual(1, quad_keys.size())
        self.assertTrue(qk in quad_keys)

        # Select South America
        quad_keys = QuadKey.get_keys_from_longitude_latitude_bounding_box(
            Type_UlpQnr,
            GeoCoordinateBoundingBox2d(
                GeoCoordinate2d(Longitude(-89.9), Latitude(-90.0)),
                GeoCoordinate2d(Longitude(0.0), Latitude(0.0))), 2)
        qk = QuadKey.from_internal_string(Type_UlpQnr, "17")
        self.assertEqual(1, quad_keys.size())
        self.assertTrue(qk in quad_keys)

        # Select North West Corner
        quad_keys = QuadKey.get_keys_from_longitude_latitude_bounding_box(
            Type_UlpQnr,
            GeoCoordinateBoundingBox2d(
                GeoCoordinate2d(Longitude(-180.0), Latitude(0.1)),
                GeoCoordinate2d(Longitude(-90.0), Latitude(90.0))), 2)
        qk = QuadKey.from_internal_string(Type_UlpQnr, "20")
        self.assertEqual(1, quad_keys.size())
        self.assertTrue(qk in quad_keys)

        # Select Greenland
        quad_keys = QuadKey.get_keys_from_longitude_latitude_bounding_box(
            Type_UlpQnr,
            GeoCoordinateBoundingBox2d(
                GeoCoordinate2d(Longitude(-89.9), Latitude(0.1)),
                GeoCoordinate2d(Longitude(0.0), Latitude(90.0))), 2)
        qk = QuadKey.from_internal_string(Type_UlpQnr, "21")
        self.assertEqual(1, quad_keys.size())
        self.assertTrue(qk in quad_keys)

        # Select South Pole
        quad_keys = QuadKey.get_keys_from_longitude_latitude_bounding_box(
            Type_UlpQnr,
            GeoCoordinateBoundingBox2d(
                GeoCoordinate2d(Longitude(0.1), Latitude(-90.0)),
                GeoCoordinate2d(Longitude(90.0), Latitude(0.0))), 2)
        qk = QuadKey.from_internal_string(Type_UlpQnr, "18")
        self.assertEqual(1, quad_keys.size())
        self.assertTrue(qk in quad_keys)

        # Select South East Corner
        quad_keys = QuadKey.get_keys_from_longitude_latitude_bounding_box(
            Type_UlpQnr,
            GeoCoordinateBoundingBox2d(
                GeoCoordinate2d(Longitude(90.1), Latitude(-90.0)),
                GeoCoordinate2d(Longitude(180.0), Latitude(0.0))), 2)
        qk = QuadKey.from_internal_string(Type_UlpQnr, "19")
        self.assertEqual(1, quad_keys.size())
        self.assertTrue(qk in quad_keys)

        # Select Over Europe
        quad_keys = QuadKey.get_keys_from_longitude_latitude_bounding_box(
            Type_UlpQnr,
            GeoCoordinateBoundingBox2d(
                GeoCoordinate2d(Longitude(0.1), Latitude(0.1)),
                GeoCoordinate2d(Longitude(90.0), Latitude(90.0))), 2)
        qk = QuadKey.from_internal_string(Type_UlpQnr, "22")
        self.assertEqual(1, quad_keys.size())
        self.assertTrue(qk in quad_keys)

        # Select North East Corner
        quad_keys = QuadKey.get_keys_from_longitude_latitude_bounding_box(
            Type_UlpQnr,
            GeoCoordinateBoundingBox2d(
                GeoCoordinate2d(Longitude(90.1), Latitude(0.1)),
                GeoCoordinate2d(Longitude(180.0), Latitude(90.0))), 2)

        qk = QuadKey.from_internal_string(Type_UlpQnr, "23")
        self.assertEqual(1, quad_keys.size())
        self.assertTrue(qk in quad_keys)

        # Select Entire Map
        quad_keys = QuadKey.get_keys_from_longitude_latitude_bounding_box(
            Type_UlpQnr,
            GeoCoordinateBoundingBox2d(
                GeoCoordinate2d(Longitude(-179.9), Latitude(-89.9)),
                GeoCoordinate2d(Longitude(90.1), Latitude(0.1))), 2)

        quad_key0 = QuadKey.from_internal_string(Type_UlpQnr, "16")
        quad_key1 = QuadKey.from_internal_string(Type_UlpQnr, "17")
        quad_key2 = QuadKey.from_internal_string(Type_UlpQnr, "18")
        quad_key3 = QuadKey.from_internal_string(Type_UlpQnr, "19")
        quad_key4 = QuadKey.from_internal_string(Type_UlpQnr, "20")
        quad_key5 = QuadKey.from_internal_string(Type_UlpQnr, "21")
        quad_key6 = QuadKey.from_internal_string(Type_UlpQnr, "22")
        quad_key7 = QuadKey.from_internal_string(Type_UlpQnr, "23")
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

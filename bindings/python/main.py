"""Docstring."""
from quad_keys.quad_keys import QuadKey
from quad_keys.quad_keys import GeoCoordinateBoundingBox2d


def main():
    """Docstring."""
    qk = QuadKey()
    print(qk.type_as_string())
    geo_bounds = GeoCoordinateBoundingBox2d()
    print(qk.get_geo_coordinate_bounds2d(geo_bounds))


if __name__ == "__main__":
    main()

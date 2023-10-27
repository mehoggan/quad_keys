package com.quad_keys;

import org.junit.BeforeClass;
import org.junit.Test;

import java.util.Map;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertTrue;

public class OsGeoSystemTest {

  private boolean vectorContains(QuadKeysVector vect, QuadKey key) {
    boolean found = false;
    for (QuadKey curr : vect) {
      if (curr.equalTo(key)) {
        found = true;
        break;
      }
    }
    return found;
  }

  @BeforeClass
  public static void setUpBeforeClass() throws Exception {
    System.loadLibrary("quad_keys_java");
  }

  @Test
  public void is_valid_test() {
      // See TestQuadKey TestSpecificCtorTest.
  }

  @Test
  public void is_root_key_test() {
      // Same as bing_system
  }

  @Test
  public void get_parent_test() {
      // Same as bing_system
  }

  @Test
  public void is_my_ancestor_test() {
      // Same as bing_system
  }

  @Test
  public void get_ancestor_test() {
      // Same as bing_system
  }

  @Test
  public void get_child_test() {
      // Same as bing_system
  }

  @Test
  public void get_children_test() {
      // Same as bing_system
  }

  @Test
  public void get_descendants_test() {
      // Same as bing_system
  }

  @Test
  public void get_siblings_test() {
      // Same as bing_system
  }

  @Test
  public void get_neighbors_test() {
      // Same as bing_system
  }

  @Test
  public void from_string_to_string_test() {
    // Same thing as osgeo Except for it allows for negative 1 in both the
    // rows and the columns. depth/col/row.
    QuadKey quadKey = new QuadKey(Type.OsGeo, 3, 3, (short)2);
    String fmt = quadKey.to_internal_string();
    assertEquals("2/3/3", fmt);
    QuadKey quadKeyBack = QuadKey.from_internal_string(Type.OsGeo, fmt);
    assertTrue(quadKey.equalTo(quadKeyBack));

    fmt = "0/-1/-1";
    quadKeyBack = QuadKey.from_internal_string(Type.OsGeo, fmt);
    assertTrue(new QuadKey(Type.OsGeo, 0, 0,(short)0).equalTo(
      quadKeyBack));

    fmt = "1/1/-1";
    quadKeyBack = QuadKey.from_internal_string(Type.OsGeo, fmt);
    assertTrue(new QuadKey(Type.OsGeo, 0, 1, (short)1).equalTo(
      quadKeyBack));

    fmt = "1/-1/1";
    quadKeyBack = QuadKey.from_internal_string(Type.OsGeo, fmt);
    assertTrue(new QuadKey(Type.OsGeo, 1, 0, (short)1).equalTo(
      quadKeyBack));
  }

  @Test
  public void get_geo_coordinate_bounds2d_test() {
    QuadKey quadKey;
    GeoCoordinateBoundingBox2d bbox = new GeoCoordinateBoundingBox2d();

    { // Depth 0
      quadKey = QuadKey.from_internal_string(Type.OsGeo, "0/0/0");
      quadKey.get_geo_coordinate_bounds2d(bbox);
      assertTrue(new Longitude(-180.0f).near(
        bbox.lower_left().get_longitude(), 1e-4));
      assertTrue(new Latitude(-85.051132).near(
        bbox.lower_left().get_latitude(), 1e-4));
      assertTrue(new Longitude(+180.0).near(
        bbox.upper_right().get_longitude(), 1e-4));
      assertTrue(new Latitude(+85.051132).near(
        bbox.upper_right().get_latitude(), 1e-4));
    }
  }

  @Test
  public void get_key_from_longitude_latitude_at_depth_to_bounds_test() {
    QuadKey quadKey;
    GeoCoordinateBoundingBox2d bbox = new GeoCoordinateBoundingBox2d();

    // Inclusion here consists of upper right. In the case along bottom or
    // left Inclusion points the opposite direction.
    //    X------X------X ur
    //    |      |      |
    //    |      |      |
    //    X------X------X
    //    |      |      |
    //    |      |      |
    //    X------X------X
    // Note that in this system bounds consist of all 4 sides, so two quads
    // will share the same boundary.
    quadKey = QuadKey.get_key_from_longitude_latitude_at_depth(Type.OsGeo,
      new GeoCoordinate2d(new Longitude(-180.0),
        new Latitude(+85.05113877)), (short)0);
    assertTrue(new QuadKey(Type.OsGeo, 0, 0, (short)0).equalTo(quadKey));
    quadKey = QuadKey.get_key_from_longitude_latitude_at_depth(Type.OsGeo,
      new GeoCoordinate2d(new Longitude(+180.0),
        new Latitude(+85.05113877)), (short)0);
    assertTrue(new QuadKey(Type.OsGeo, 0, 0, (short)0).equalTo(quadKey));
    quadKey = QuadKey.get_key_from_longitude_latitude_at_depth(Type.OsGeo,
      new GeoCoordinate2d(new Longitude(+180.0),
        new Latitude(-85.05113877)), (short)0);
    assertTrue(new QuadKey(Type.OsGeo, 0, 0, (short)0).equalTo(quadKey));
    quadKey = QuadKey.get_key_from_longitude_latitude_at_depth(Type.OsGeo,
      new GeoCoordinate2d(new Longitude(-180.0),
        new Latitude(-85.05113877)), (short)0);
    assertTrue(new QuadKey(Type.OsGeo, 0, 0, (short)0).equalTo(quadKey));
    quadKey.get_geo_coordinate_bounds2d(bbox);
    assertTrue(bbox.lower_left().near(new GeoCoordinate2d(
      new Longitude(-180.0), new Latitude(-85.05113877)), 1e-4));
    assertTrue(bbox.upper_right().near(new GeoCoordinate2d(
      new Longitude(+180.0), new Latitude(+85.05113877)), 1e-4));

    quadKey = QuadKey.get_key_from_longitude_latitude_at_depth(Type.OsGeo,
      new GeoCoordinate2d(new Longitude(+0.0),
        new Latitude(+0.00000000)), (short)0);
    assertTrue(new QuadKey(Type.OsGeo, 0, 0, (short)0).equalTo(quadKey));

    quadKey = QuadKey.get_key_from_longitude_latitude_at_depth(Type.OsGeo,
      new GeoCoordinate2d(new Longitude(-180.0),
        new Latitude(+85.05113877)), (short)1);
    assertTrue(new QuadKey(Type.OsGeo, 1, 0, (short)1).equalTo(quadKey));
    quadKey.get_geo_coordinate_bounds2d(bbox);
    assertTrue(bbox.lower_left().near(new GeoCoordinate2d(
      new Longitude(-180.0), new Latitude(+0.00000000)), 1e-4));
    assertTrue(bbox.upper_right().near(new GeoCoordinate2d(
      new Longitude(+0.0), new Latitude(+85.05113877)), 1e-4));

    quadKey = QuadKey.get_key_from_longitude_latitude_at_depth(Type.OsGeo,
      new GeoCoordinate2d(new Longitude(+180.0),
        new Latitude(+85.05113877)), (short)1);
    assertTrue(new QuadKey(Type.OsGeo, 1, 1,(short)1).equalTo(quadKey));
    quadKey.get_geo_coordinate_bounds2d(bbox);
    assertTrue(bbox.lower_left().near(new GeoCoordinate2d(
      new Longitude(+0.0), new Latitude(+0.00000000)), 1e-4));
    assertTrue(bbox.upper_right().near(new GeoCoordinate2d(
      new Longitude(+180.0), new Latitude(+85.05113877)), 1e-4));

    quadKey = QuadKey.get_key_from_longitude_latitude_at_depth(Type.OsGeo,
      new GeoCoordinate2d(new Longitude(+180.0),
        new Latitude(-85.05113877)), (short)1);
    assertTrue(new QuadKey(Type.OsGeo, 0, 1, (short)1).equalTo(quadKey));
    quadKey.get_geo_coordinate_bounds2d(bbox);
    assertTrue(bbox.lower_left().near(new GeoCoordinate2d(
      new Longitude(+0.0), new Latitude(-85.05113877)), 1e-4));
    assertTrue(bbox.upper_right().near(new GeoCoordinate2d(
      new Longitude(+180.0), new Latitude(+0.00000000)), 1e-4));

    quadKey = QuadKey.get_key_from_longitude_latitude_at_depth(Type.OsGeo,
      new GeoCoordinate2d(new Longitude(-180.0),
        new Latitude(-85.05113877)), (short)1);
    assertTrue(new QuadKey(Type.OsGeo, 0, 0,(short)1).equalTo(quadKey));
    quadKey.get_geo_coordinate_bounds2d(bbox);
    assertTrue(bbox.lower_left().near(new GeoCoordinate2d(
      new Longitude(-180.0), new Latitude(-85.05113877)), 1e-4));
    assertTrue(bbox.upper_right().near(new GeoCoordinate2d(
      new Longitude(+0.0), new Latitude(+0.00000000)), 1e-4));

    quadKey = QuadKey.get_key_from_longitude_latitude_at_depth(Type.OsGeo,
      new GeoCoordinate2d(new Longitude(-180.0),
        new Latitude(+0.00000000)), (short)1);
    assertTrue(new QuadKey(Type.OsGeo, 0, 0, (short)1).equalTo(quadKey));
    quadKey = QuadKey.get_key_from_longitude_latitude_at_depth(Type.OsGeo,
      new GeoCoordinate2d(new Longitude(+0.0),
        new Latitude(+85.05113877)), (short)1);
    assertTrue(new QuadKey(Type.OsGeo, 1, 0, (short)1).equalTo(quadKey));
    quadKey = QuadKey.get_key_from_longitude_latitude_at_depth(Type.OsGeo,
      new GeoCoordinate2d(new Longitude(+180.0),
        new Latitude(+0.00000000)), (short)1);
    assertTrue(new QuadKey(Type.OsGeo, 0, 1, (short)1).equalTo(quadKey));
    quadKey = QuadKey.get_key_from_longitude_latitude_at_depth(Type.OsGeo,
      new GeoCoordinate2d(new Longitude(+0.0),
        new Latitude(-85.05113877)), (short)1);
    assertTrue(new QuadKey(Type.OsGeo, 0, 0, (short)1).equalTo(quadKey));
    quadKey = QuadKey.get_key_from_longitude_latitude_at_depth(Type.OsGeo,
      new GeoCoordinate2d(new Longitude(+0.0),
        new Latitude(+0.00000000)), (short)1);
    assertTrue(new QuadKey(Type.OsGeo, 0, 0, (short)1).equalTo(quadKey));

    // Note at depth 2 because of the Mercator projection the lines
    // of latitude are note perfect divisions by 2.
    quadKey = QuadKey.get_key_from_longitude_latitude_at_depth(Type.OsGeo,
      new GeoCoordinate2d(new Longitude(-180.0),
        new Latitude(-85.05113877)), (short)2);
    assertTrue(new QuadKey(Type.OsGeo, 0, 0, (short)2).equalTo(quadKey));
    quadKey = QuadKey.get_key_from_longitude_latitude_at_depth(Type.OsGeo,
      new GeoCoordinate2d(new Longitude(-180.0),
        new Latitude(-66.5133)), (short)2);
    assertTrue(new QuadKey(Type.OsGeo, 0, 0, (short)2).equalTo(quadKey));
    quadKey = QuadKey.get_key_from_longitude_latitude_at_depth(Type.OsGeo,
      new GeoCoordinate2d(new Longitude(-180.0),
        new Latitude(-66.5132)), (short)2);
    assertTrue(new QuadKey(Type.OsGeo, 1, 0, (short)2).equalTo(quadKey));
    quadKey = QuadKey.get_key_from_longitude_latitude_at_depth(Type.OsGeo,
      new GeoCoordinate2d(new Longitude(-180.0),
        new Latitude(+0.1)), (short)2);
    assertTrue(new QuadKey(Type.OsGeo, 2, 0, (short)2).equalTo(quadKey));
    quadKey = QuadKey.get_key_from_longitude_latitude_at_depth(Type.OsGeo,
      new GeoCoordinate2d(new Longitude(-180.0),
        new Latitude(+66.5132)), (short)2);
    assertTrue(new QuadKey(Type.OsGeo, 2, 0, (short)2).equalTo(quadKey));
    quadKey = QuadKey.get_key_from_longitude_latitude_at_depth(Type.OsGeo,
      new GeoCoordinate2d(new Longitude(-180.0),
        new Latitude(+66.5133)), (short)2);
    assertTrue(new QuadKey(Type.OsGeo, 3, 0, (short)2).equalTo(quadKey));
    quadKey = QuadKey.get_key_from_longitude_latitude_at_depth(Type.OsGeo,
      new GeoCoordinate2d(new Longitude(-180.0),
        new Latitude(+85.05113877)), (short)2);
    assertTrue(new QuadKey(Type.OsGeo, 3, 0, (short)2).equalTo(quadKey));
    quadKey = QuadKey.get_key_from_longitude_latitude_at_depth(Type.OsGeo,
      new GeoCoordinate2d(new Longitude(-90.0),
        new Latitude(-85.05113877)), (short)2);
    assertTrue(new QuadKey(Type.OsGeo, 0, 0, (short)2).equalTo(quadKey));
    quadKey = QuadKey.get_key_from_longitude_latitude_at_depth(Type.OsGeo,
      new GeoCoordinate2d(new Longitude(-90.0),
        new Latitude(-66.5133)), (short)2);
    assertTrue(new QuadKey(Type.OsGeo, 0, 0, (short)2).equalTo(quadKey));
    quadKey = QuadKey.get_key_from_longitude_latitude_at_depth(Type.OsGeo,
      new GeoCoordinate2d(new Longitude(-90.0),
        new Latitude(-66.5132)), (short)2);
    assertTrue(new QuadKey(Type.OsGeo, 1, 0, (short)2).equalTo(quadKey));
    quadKey = QuadKey.get_key_from_longitude_latitude_at_depth(Type.OsGeo,
      new GeoCoordinate2d(new Longitude(-90.0),
        new Latitude(+0.1)), (short)2);
    assertTrue(new QuadKey(Type.OsGeo, 2, 0, (short)2).equalTo(quadKey));
    quadKey = QuadKey.get_key_from_longitude_latitude_at_depth(Type.OsGeo,
      new GeoCoordinate2d(new Longitude(-90.0),
        new Latitude(+66.5132)), (short)2);
    assertTrue(new QuadKey(Type.OsGeo, 2, 0, (short)2).equalTo(quadKey));
    quadKey = QuadKey.get_key_from_longitude_latitude_at_depth(Type.OsGeo,
      new GeoCoordinate2d(new Longitude(-90.0),
        new Latitude(+66.5133)), (short)2);
    assertTrue(new QuadKey(Type.OsGeo, 3, 0, (short)2).equalTo(quadKey));
    quadKey = QuadKey.get_key_from_longitude_latitude_at_depth(Type.OsGeo,
      new GeoCoordinate2d(new Longitude(-90.0),
        new Latitude(+85.05113877)), (short)2);
    assertTrue(new QuadKey(Type.OsGeo, 3, 0, (short)2).equalTo(quadKey));
    quadKey = QuadKey.get_key_from_longitude_latitude_at_depth(Type.OsGeo,
      new GeoCoordinate2d(new Longitude(-89.9),
        new Latitude(-85.05113877)), (short)2);
    assertTrue(new QuadKey(Type.OsGeo, 0, 1, (short)2).equalTo(quadKey));
    quadKey = QuadKey.get_key_from_longitude_latitude_at_depth(Type.OsGeo,
      new GeoCoordinate2d(new Longitude(-89.9),
        new Latitude(-66.5133)), (short)2);
    assertTrue(new QuadKey(Type.OsGeo, 0, 1, (short)2).equalTo(quadKey));
    quadKey = QuadKey.get_key_from_longitude_latitude_at_depth(Type.OsGeo,
      new GeoCoordinate2d(new Longitude(-89.9),
        new Latitude(-66.5132)), (short)2);
    assertTrue(new QuadKey(Type.OsGeo, 1, 1, (short)2).equalTo(quadKey));
    quadKey = QuadKey.get_key_from_longitude_latitude_at_depth(Type.OsGeo,
      new GeoCoordinate2d(new Longitude(-89.9),
        new Latitude(+0.1)), (short)2);
    assertTrue(new QuadKey(Type.OsGeo, 2, 1, (short)2).equalTo(quadKey));
    quadKey = QuadKey.get_key_from_longitude_latitude_at_depth(Type.OsGeo,
      new GeoCoordinate2d(new Longitude(-89.9),
        new Latitude(+66.5132)), (short)2);
    assertTrue(new QuadKey(Type.OsGeo, 2, 1, (short)2).equalTo(quadKey));
    quadKey = QuadKey.get_key_from_longitude_latitude_at_depth(Type.OsGeo,
      new GeoCoordinate2d(new Longitude(-89.9),
        new Latitude(+66.5133)), (short)2);
    assertTrue(new QuadKey(Type.OsGeo, 3, 1, (short)2).equalTo(quadKey));
    quadKey = QuadKey.get_key_from_longitude_latitude_at_depth(Type.OsGeo,
      new GeoCoordinate2d(new Longitude(-89.9),
        new Latitude(+85.05113877)), (short)2);
    assertTrue(new QuadKey(Type.OsGeo, 3, 1, (short)2).equalTo(quadKey));
    quadKey = QuadKey.get_key_from_longitude_latitude_at_depth(Type.OsGeo,
      new GeoCoordinate2d(new Longitude(+0.0),
        new Latitude(-85.05113877)), (short)2);
    assertTrue(new QuadKey(Type.OsGeo, 0, 1, (short)2).equalTo(quadKey));
    quadKey = QuadKey.get_key_from_longitude_latitude_at_depth(Type.OsGeo,
      new GeoCoordinate2d(new Longitude(+0.0),
        new Latitude(-66.5133)), (short)2);
    assertTrue(new QuadKey(Type.OsGeo, 0, 1, (short)2).equalTo(quadKey));
    quadKey = QuadKey.get_key_from_longitude_latitude_at_depth(Type.OsGeo,
      new GeoCoordinate2d(new Longitude(+0.0),
        new Latitude(-66.5132)), (short)2);
    assertTrue(new QuadKey(Type.OsGeo, 1, 1, (short)2).equalTo(quadKey));
    quadKey = QuadKey.get_key_from_longitude_latitude_at_depth(Type.OsGeo,
      new GeoCoordinate2d(new Longitude(+0.0),
        new Latitude(+0.1)), (short)2);
    assertTrue(new QuadKey(Type.OsGeo, 2, 1, (short)2).equalTo(quadKey));
    quadKey = QuadKey.get_key_from_longitude_latitude_at_depth(Type.OsGeo,
      new GeoCoordinate2d(new Longitude(+0.0),
        new Latitude(+66.5132)), (short)2);
    assertTrue(new QuadKey(Type.OsGeo, 2, 1, (short)2).equalTo(quadKey));
    quadKey = QuadKey.get_key_from_longitude_latitude_at_depth(Type.OsGeo,
      new GeoCoordinate2d(new Longitude(+0.0),
        new Latitude(+66.5133)), (short)2);
    assertTrue(new QuadKey(Type.OsGeo, 3, 1, (short)2).equalTo(quadKey));
    quadKey = QuadKey.get_key_from_longitude_latitude_at_depth(Type.OsGeo,
      new GeoCoordinate2d(new Longitude(+0.0),
        new Latitude(+85.05113877)), (short)2);
    assertTrue(new QuadKey(Type.OsGeo, 3, 1, (short)2).equalTo(quadKey));
    quadKey = QuadKey.get_key_from_longitude_latitude_at_depth(Type.OsGeo,
      new GeoCoordinate2d(new Longitude(+0.1),
        new Latitude(-85.05113877)), (short)2);
    assertTrue(new QuadKey(Type.OsGeo, 0, 2, (short)2).equalTo(quadKey));
    quadKey = QuadKey.get_key_from_longitude_latitude_at_depth(Type.OsGeo,
      new GeoCoordinate2d(new Longitude(+0.1),
        new Latitude(-66.5133)), (short)2);
    assertTrue(new QuadKey(Type.OsGeo, 0, 2, (short)2).equalTo(quadKey));
    quadKey = QuadKey.get_key_from_longitude_latitude_at_depth(Type.OsGeo,
      new GeoCoordinate2d(new Longitude(+0.1),
        new Latitude(-66.5132)), (short)2);
    assertTrue(new QuadKey(Type.OsGeo, 1, 2, (short)2).equalTo(quadKey));
    quadKey = QuadKey.get_key_from_longitude_latitude_at_depth(Type.OsGeo,
      new GeoCoordinate2d(new Longitude(+0.1),
        new Latitude(+0.1)), (short)2);
    assertTrue(new QuadKey(Type.OsGeo, 2, 2, (short)2).equalTo(quadKey));
    quadKey = QuadKey.get_key_from_longitude_latitude_at_depth(Type.OsGeo,
      new GeoCoordinate2d(new Longitude(+0.1),
        new Latitude(+66.5132)), (short)2);
    assertTrue(new QuadKey(Type.OsGeo, 2, 2, (short)2).equalTo(quadKey));
    quadKey = QuadKey.get_key_from_longitude_latitude_at_depth(Type.OsGeo,
      new GeoCoordinate2d(new Longitude(+0.1),
        new Latitude(+66.5133)), (short)2);
    assertTrue(new QuadKey(Type.OsGeo, 3, 2, (short)2).equalTo(quadKey));
    quadKey = QuadKey.get_key_from_longitude_latitude_at_depth(Type.OsGeo,
      new GeoCoordinate2d(new Longitude(+0.1),
        new Latitude(+85.05113877)), (short)2);
    assertTrue(new QuadKey(Type.OsGeo, 3, 2, (short)2).equalTo(quadKey));
    quadKey = QuadKey.get_key_from_longitude_latitude_at_depth(Type.OsGeo,
      new GeoCoordinate2d(new Longitude(+90.0),
        new Latitude(-85.05113877)), (short)2);
    assertTrue(new QuadKey(Type.OsGeo, 0, 2, (short)2).equalTo(quadKey));
    quadKey = QuadKey.get_key_from_longitude_latitude_at_depth(Type.OsGeo,
      new GeoCoordinate2d(new Longitude(+90.0),
        new Latitude(-66.5133)), (short)2);
    assertTrue(new QuadKey(Type.OsGeo, 0, 2, (short)2).equalTo(quadKey));
    quadKey = QuadKey.get_key_from_longitude_latitude_at_depth(Type.OsGeo,
      new GeoCoordinate2d(new Longitude(+90.0),
        new Latitude(-66.5132)), (short)2);
    assertTrue(new QuadKey(Type.OsGeo, 1, 2, (short)2).equalTo(quadKey));
    quadKey = QuadKey.get_key_from_longitude_latitude_at_depth(Type.OsGeo,
      new GeoCoordinate2d(new Longitude(+90.0),
        new Latitude(+0.1)), (short)2);
    assertTrue(new QuadKey(Type.OsGeo, 2, 2, (short)2).equalTo(quadKey));
    quadKey = QuadKey.get_key_from_longitude_latitude_at_depth(Type.OsGeo,
      new GeoCoordinate2d(new Longitude(+90.0),
        new Latitude(+66.5132)), (short)2);
    assertTrue(new QuadKey(Type.OsGeo, 2, 2, (short)2).equalTo(quadKey));
    quadKey = QuadKey.get_key_from_longitude_latitude_at_depth(Type.OsGeo,
      new GeoCoordinate2d(new Longitude(+90.0),
        new Latitude(+66.5133)), (short)2);
    assertTrue(new QuadKey(Type.OsGeo, 3, 2, (short)2).equalTo(quadKey));
    quadKey = QuadKey.get_key_from_longitude_latitude_at_depth(Type.OsGeo,
      new GeoCoordinate2d(new Longitude(+90.0),
        new Latitude(+85.05113877)), (short)2);
    assertTrue(new QuadKey(Type.OsGeo, 3, 2, (short)2).equalTo(quadKey));
    quadKey = QuadKey.get_key_from_longitude_latitude_at_depth(Type.OsGeo,
      new GeoCoordinate2d(new Longitude(+90.1),
        new Latitude(-85.05113877)), (short)2);
    assertTrue(new QuadKey(Type.OsGeo, 0, 3, (short)2).equalTo(quadKey));
    quadKey = QuadKey.get_key_from_longitude_latitude_at_depth(Type.OsGeo,
      new GeoCoordinate2d(new Longitude(+90.1),
        new Latitude(-66.5133)), (short)2);
    assertTrue(new QuadKey(Type.OsGeo, 0, 3, (short)2).equalTo(quadKey));
    quadKey = QuadKey.get_key_from_longitude_latitude_at_depth(Type.OsGeo,
      new GeoCoordinate2d(new Longitude(+90.1),
        new Latitude(-66.5132)), (short)2);
    assertTrue(new QuadKey(Type.OsGeo, 1, 3, (short)2).equalTo(quadKey));
    quadKey = QuadKey.get_key_from_longitude_latitude_at_depth(Type.OsGeo,
      new GeoCoordinate2d(new Longitude(+90.1),
        new Latitude(+0.1)), (short)2);
    assertTrue(new QuadKey(Type.OsGeo, 2, 3, (short)2).equalTo(quadKey));
    quadKey = QuadKey.get_key_from_longitude_latitude_at_depth(Type.OsGeo,
      new GeoCoordinate2d(new Longitude(+90.1),
        new Latitude(+66.5132)), (short)2);
    assertTrue(new QuadKey(Type.OsGeo, 2, 3, (short)2).equalTo(quadKey));
    quadKey = QuadKey.get_key_from_longitude_latitude_at_depth(Type.OsGeo,
      new GeoCoordinate2d(new Longitude(+90.1),
        new Latitude(+66.5133)), (short)2);
    assertTrue(new QuadKey(Type.OsGeo, 3, 3, (short)2).equalTo(quadKey));
    quadKey = QuadKey.get_key_from_longitude_latitude_at_depth(Type.OsGeo,
      new GeoCoordinate2d(new Longitude(+90.1),
        new Latitude(+85.05113877)), (short)2);
    assertTrue(new QuadKey(Type.OsGeo, 3, 3, (short)2).equalTo(quadKey));
    quadKey = QuadKey.get_key_from_longitude_latitude_at_depth(Type.OsGeo,
      new GeoCoordinate2d(new Longitude(+180.0),
        new Latitude(-85.05113877)), (short)2);
    assertTrue(new QuadKey(Type.OsGeo, 0, 3, (short)2).equalTo(quadKey));
    quadKey = QuadKey.get_key_from_longitude_latitude_at_depth(Type.OsGeo,
      new GeoCoordinate2d(new Longitude(+180.0),
        new Latitude(-66.5133)), (short)2);
    assertTrue(new QuadKey(Type.OsGeo, 0, 3, (short)2).equalTo(quadKey));
    quadKey = QuadKey.get_key_from_longitude_latitude_at_depth(Type.OsGeo,
      new GeoCoordinate2d(new Longitude(+180.0),
        new Latitude(-66.5132)), (short)2);
    assertTrue(new QuadKey(Type.OsGeo, 1, 3, (short)2).equalTo(quadKey));
    quadKey = QuadKey.get_key_from_longitude_latitude_at_depth(Type.OsGeo,
      new GeoCoordinate2d(new Longitude(+180.0),
        new Latitude(+0.1)), (short)2);
    assertTrue(new QuadKey(Type.OsGeo, 2, 3, (short)2).equalTo(quadKey));
    quadKey = QuadKey.get_key_from_longitude_latitude_at_depth(Type.OsGeo,
      new GeoCoordinate2d(new Longitude(+180.0),
        new Latitude(+66.5132)), (short)2);
    assertTrue(new QuadKey(Type.OsGeo, 2, 3, (short)2).equalTo(quadKey));
    quadKey = QuadKey.get_key_from_longitude_latitude_at_depth(Type.OsGeo,
      new GeoCoordinate2d(new Longitude(+180.0),
        new Latitude(+66.5133)), (short)2);
    assertTrue(new QuadKey(Type.OsGeo, 3, 3, (short)2).equalTo(quadKey));
    quadKey = QuadKey.get_key_from_longitude_latitude_at_depth(Type.OsGeo,
      new GeoCoordinate2d(new Longitude(+180.0),
        new Latitude(+85.05113877)), (short)2);
    assertTrue(new QuadKey(Type.OsGeo, 3, 3, (short)2).equalTo(quadKey));
  }

  @Test
  public void get_keys_from_longitude_latitude_bounding_box_test() {
    QuadKeysVector quadKeys;

    quadKeys = QuadKey.get_keys_from_longitude_latitude_bounding_box(
      Type.OsGeo, new GeoCoordinateBoundingBox2d(
        new GeoCoordinate2d(new Longitude(+0.0),
          new Latitude(-0.10000000)),
        new GeoCoordinate2d(new Longitude(+0.1),
          new Latitude(+0.10000000))), (short)0);
    assertEquals(1, quadKeys.size());
    assertTrue(vectorContains(quadKeys, new QuadKey(Type.OsGeo, 0, 0,
      (short)0)));

    quadKeys = QuadKey.get_keys_from_longitude_latitude_bounding_box(
      Type.OsGeo, new GeoCoordinateBoundingBox2d(
        new GeoCoordinate2d(new Longitude(-180.0),
          new Latitude(-85.05113877)),
        new GeoCoordinate2d(new Longitude(+180.0),
          new Latitude(+85.05113877))), (short)1);
    assertEquals(4, quadKeys.size());
    assertTrue(vectorContains(quadKeys, new QuadKey(Type.OsGeo, 0, 0,
      (short)1)));
    assertTrue(vectorContains(quadKeys, new QuadKey(Type.OsGeo, 0, 1,
      (short)1)));
    assertTrue(vectorContains(quadKeys, new QuadKey(Type.OsGeo, 1, 0,
      (short)1)));
    assertTrue(vectorContains(quadKeys, new QuadKey(Type.OsGeo, 1, 1,
      (short)1)));

    quadKeys = QuadKey.get_keys_from_longitude_latitude_bounding_box(
      Type.OsGeo, new GeoCoordinateBoundingBox2d(
        new GeoCoordinate2d(new Longitude(-180.0),
          new Latitude(-85.05113877)),
        new GeoCoordinate2d(new Longitude(+0.0),
          new Latitude(+85.05113877))), (short)1);
    assertEquals(2, quadKeys.size());
    assertTrue(vectorContains(quadKeys, new QuadKey(Type.OsGeo, 1, 0,
      (short)1)));
    assertTrue(vectorContains(quadKeys, new QuadKey(Type.OsGeo, 0, 0,
      (short)1)));

    quadKeys = QuadKey.get_keys_from_longitude_latitude_bounding_box(
      Type.OsGeo, new GeoCoordinateBoundingBox2d(
        new GeoCoordinate2d(new Longitude(+0.1),
          new Latitude(-85.05113877)),
        new GeoCoordinate2d(new Longitude(+180.0),
          new Latitude(+85.05113877))), (short)1);
    assertEquals(2, quadKeys.size());
    assertTrue(vectorContains(quadKeys, new QuadKey(Type.OsGeo, 1, 1,
      (short)1)));
    assertTrue(vectorContains(quadKeys, new QuadKey(Type.OsGeo, 0, 1,
      (short)1)));

    quadKeys = QuadKey.get_keys_from_longitude_latitude_bounding_box(
      Type.OsGeo, new GeoCoordinateBoundingBox2d(
        new GeoCoordinate2d(new Longitude(-180.0),
          new Latitude(-85.05113877)),
        new GeoCoordinate2d(new Longitude(+0.0),
          new Latitude(+0.00000000))), (short)1);
    assertEquals(1, quadKeys.size());
    assertTrue(vectorContains(quadKeys, new QuadKey(Type.OsGeo, 0, 0,
      (short)1)));

    quadKeys = QuadKey.get_keys_from_longitude_latitude_bounding_box(
      Type.OsGeo, new GeoCoordinateBoundingBox2d(
        new GeoCoordinate2d(new Longitude(-180.0),
          new Latitude(+0.10000000)),
        new GeoCoordinate2d(new Longitude(+0.0),
          new Latitude(+85.05113877))), (short)1);
    assertEquals(1, quadKeys.size());
    assertTrue(vectorContains(quadKeys, new QuadKey(Type.OsGeo, 1, 0,
      (short)1)));

    quadKeys = QuadKey.get_keys_from_longitude_latitude_bounding_box(
      Type.OsGeo, new GeoCoordinateBoundingBox2d(
        new GeoCoordinate2d(new Longitude(+0.1),
          new Latitude(-85.05113877)),
        new GeoCoordinate2d(new Longitude(+180.0),
          new Latitude(+0.00000000))), (short)1);
    assertEquals(1, quadKeys.size());
    assertTrue(vectorContains(quadKeys, new QuadKey(Type.OsGeo, 0, 1,
      (short)1)));

    quadKeys = QuadKey.get_keys_from_longitude_latitude_bounding_box(
      Type.OsGeo, new GeoCoordinateBoundingBox2d(
        new GeoCoordinate2d(new Longitude(+0.1),
          new Latitude(+0.10000000)),
        new GeoCoordinate2d(new Longitude(+180.0),
          new Latitude(+85.05113877))), (short)1);
    assertEquals(1, quadKeys.size());
    assertTrue(vectorContains(quadKeys, new QuadKey(Type.OsGeo, 1, 1,
      (short)1)));
  }

  @Test
  public void selected_citites_test() {
    // TODO: Implement Tests. Taken from Earthscape. No tests there.
  }
}

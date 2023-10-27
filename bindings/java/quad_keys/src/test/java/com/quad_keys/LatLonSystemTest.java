package com.quad_keys;

import static org.junit.Assert.*;

import org.junit.BeforeClass;
import org.junit.Test;

public class LatLonSystemTest {

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
  public void is_valid_test()
  {
    // See TestQuadKey TestSpecificCtorTest.
  }

  @Test
  public void is_root_key_test()
  {
    // Same as bing_system
  }

  @Test
  public void get_parent_test()
  {
    // Same as bing_system
  }

  @Test
  public void is_my_ancestor_test()
  {
    // Same as bing_system
  }

  @Test
  public void get_ancestor_test()
  {
    // Same as bing_system
  }

  @Test
  public void get_child_test()
  {
    // Same as bing_system
  }

  @Test
  public void get_children_test()
  {
    // Same as bing_system
  }

  @Test
  public void get_descendants_test()
  {
    // Same as bing_system
  }

  @Test
  public void get_siblings_test()
  {
    // Same as bing_system
  }

  @Test
  public void get_neighbors_test()
  {
    // Same as bing_system
  }

  @Test
  public void from_string_to_string_test()
  {
    // Same as bing_system
  }

  @Test
  public void get_geo_coordinate_bounds_2d_test()
  {
    QuadKey key;
    GeoCoordinateBoundingBox2d bbox = new GeoCoordinateBoundingBox2d();

    { // Depth 0
      key = new QuadKey(Type.LatLon, 0, 0, (short)0);
      key.get_geo_coordinate_bounds2d(bbox);
      assertTrue(new GeoCoordinate2d(new Longitude(-180.0),
        new Latitude(-90.0)).equalTo(bbox.lower_left()));
      assertTrue(new GeoCoordinate2d(new Longitude(+180.0),
        new Latitude(+90.0)).equalTo(bbox.upper_right()));
    }

    { // Depth 1
      key = new QuadKey(Type.LatLon, 0, 0, (short)1);
      key.get_geo_coordinate_bounds2d(bbox);
      assertTrue(bbox.lower_left().get_longitude().near(
        new Longitude(-180.0), 1e-6));
      assertTrue(bbox.lower_left().get_latitude().near(
        new Latitude(-90.0), 1e-6));
      assertTrue(bbox.upper_right().get_longitude().near(
        new Longitude(+0.0), 1e-6));
      assertTrue(bbox.upper_right().get_latitude().near(
        new Latitude(+0.0), 1e-6));

      key = new QuadKey(Type.LatLon, 0, 1, (short)1);
      key.get_geo_coordinate_bounds2d(bbox);
      assertTrue(bbox.lower_left().get_longitude().near(
        new Longitude(+0.0), 1e-6));
      assertTrue(bbox.lower_left().get_latitude().near(
        new Latitude(-90.0), 1e-6));
      assertTrue(bbox.upper_right().get_longitude().near(
        new Longitude(+180.0), 1e-6));
      assertTrue(bbox.upper_right().get_latitude().near(
        new Latitude(+0.0), 1e-6));

      key = new QuadKey(Type.LatLon, 1, 0, (short)1);
      key.get_geo_coordinate_bounds2d(bbox);
      assertTrue(bbox.lower_left().get_longitude().near(
        new Longitude(-180.0), 1e-6));
      assertTrue(bbox.lower_left().get_latitude().near(
        new Latitude(+0.0), 1e-6));
      assertTrue(bbox.upper_right().get_longitude().near(
        new Longitude(+0.0), 1e-6));
      assertTrue(bbox.upper_right().get_latitude().near(
        new Latitude(+90.0), 1e-6));

      key = new QuadKey(Type.LatLon, 1, 1, (short)1);
      key.get_geo_coordinate_bounds2d(bbox);
      assertTrue(bbox.lower_left().get_longitude().near(
        new Longitude(+0.0), 1e-6));
      assertTrue(bbox.lower_left().get_latitude().near(
        new Latitude(+0.0), 1e-6));
      assertTrue(bbox.upper_right().get_longitude().near(
        new Longitude(+180.0), 1e-6));
      assertTrue(bbox.upper_right().get_latitude().near(
        new Latitude(+90.0), 1e-6));
    }
  }

  @Test
  public void get_keys_from_longitude_latitude_at_depth_to_bounds_test()
  {
    QuadKey key;

    { // Depth 0
      key = QuadKey.get_key_from_longitude_latitude_at_depth(
        Type.LatLon, new GeoCoordinate2d(
          new Longitude(-180.0), new Latitude(-90)), (short)0);
      assertTrue(new QuadKey(Type.LatLon, 0, 0, (short)0).equalTo(key));
      assertEquals("", key.to_internal_string());
    }

    // Inclusion here consists of lower left
    //    X------X------X
    //    |   2  |   3  |
    //    |      |      |
    //    X------X------X
    //    |   0  |   1  |
    //    |      |      |
    // ll X------X------X
    { // Depth 1
      key = QuadKey.get_key_from_longitude_latitude_at_depth(
        Type.LatLon, new GeoCoordinate2d(
          new Longitude(-180.0), new Latitude(-90.0)), (short)1);
      assertTrue(new QuadKey(Type.LatLon, 0, 0, (short)1).equalTo(key));
      assertEquals("2", key.to_internal_string());
      key = QuadKey.get_key_from_longitude_latitude_at_depth(
        Type.LatLon, new GeoCoordinate2d(
          new Longitude(-0.1), new Latitude(-90.0)), (short)1);
      assertTrue(new QuadKey(Type.LatLon, 0, 0, (short)1).equalTo(key));
      assertEquals("2", key.to_internal_string());
      key = QuadKey.get_key_from_longitude_latitude_at_depth(
        Type.LatLon, new GeoCoordinate2d(
          new Longitude(-0.1), new Latitude(-0.1)), (short)1);
      assertTrue(new QuadKey(Type.LatLon, 0, 0, (short)1).equalTo(key));
      assertEquals("2", key.to_internal_string());
      key = QuadKey.get_key_from_longitude_latitude_at_depth(
        Type.LatLon, new GeoCoordinate2d(
          new Longitude(-180.0), new Latitude(-0.1)), (short)1);
      assertTrue(new QuadKey(Type.LatLon, 0, 0, (short)1).equalTo(key));
      assertEquals("2", key.to_internal_string());

      key = QuadKey.get_key_from_longitude_latitude_at_depth(
        Type.LatLon, new GeoCoordinate2d(
          new Longitude(+0.0), new Latitude(-90.0)), (short)1);
      assertTrue(new QuadKey(Type.LatLon, 0, 1, (short)1).equalTo(key));
      assertEquals("3", key.to_internal_string());
      key = QuadKey.get_key_from_longitude_latitude_at_depth(
        Type.LatLon, new GeoCoordinate2d(
          new Longitude(+180.0), new Latitude(-90.0)), (short)1);
      assertTrue(new QuadKey(Type.LatLon, 0, 1, (short)1).equalTo(key));
      assertEquals("3", key.to_internal_string());
      key = QuadKey.get_key_from_longitude_latitude_at_depth(
        Type.LatLon, new GeoCoordinate2d(
          new Longitude(+180.0), new Latitude(-0.1)), (short)1);
      assertTrue(new QuadKey(Type.LatLon, 0, 1, (short)1).equalTo(key));
      assertEquals("3", key.to_internal_string());
      key = QuadKey.get_key_from_longitude_latitude_at_depth(
        Type.LatLon, new GeoCoordinate2d(
          new Longitude(+0.0), new Latitude(-0.1)), (short)1);
      assertTrue(new QuadKey(Type.LatLon, 0, 1, (short)1).equalTo(key));
      assertEquals("3", key.to_internal_string());

      key = QuadKey.get_key_from_longitude_latitude_at_depth(
        Type.LatLon, new GeoCoordinate2d(
          new Longitude(-180.0), new Latitude(+0.0)), (short)1);
      assertTrue(new QuadKey(Type.LatLon, 1, 0, (short)1).equalTo(key));
      assertEquals("0", key.to_internal_string());
      key = QuadKey.get_key_from_longitude_latitude_at_depth(
        Type.LatLon, new GeoCoordinate2d(
          new Longitude(-0.1), new Latitude(+0.0)), (short)1);
      assertTrue(new QuadKey(Type.LatLon, 1, 0, (short)1).equalTo(key));
      assertEquals("0", key.to_internal_string());
      key = QuadKey.get_key_from_longitude_latitude_at_depth(
        Type.LatLon, new GeoCoordinate2d(
          new Longitude(-180.0), new Latitude(+90.0)), (short)1);
      assertTrue(new QuadKey(Type.LatLon, 1, 0, (short)1).equalTo(key));
      assertEquals("0", key.to_internal_string());
      key = QuadKey.get_key_from_longitude_latitude_at_depth(
        Type.LatLon, new GeoCoordinate2d(
          new Longitude(-0.1), new Latitude(+90.0)), (short)1);
      assertTrue(new QuadKey(Type.LatLon, 1, 0, (short)1).equalTo(key));
      assertEquals("0", key.to_internal_string());

      key = QuadKey.get_key_from_longitude_latitude_at_depth(
        Type.LatLon, new GeoCoordinate2d(
          new Longitude(+0.0), new Latitude(+0.0)), (short)1);
      assertTrue(new QuadKey(Type.LatLon, 1, 1, (short)1).equalTo(key));
      assertEquals("1", key.to_internal_string());
      key = QuadKey.get_key_from_longitude_latitude_at_depth(
        Type.LatLon, new GeoCoordinate2d(
          new Longitude(+180.0), new Latitude(+0.0)), (short)1);
      assertTrue(new QuadKey(Type.LatLon, 1, 1, (short)1).equalTo(key));
      assertEquals("1", key.to_internal_string());
      key = QuadKey.get_key_from_longitude_latitude_at_depth(
        Type.LatLon, new GeoCoordinate2d(
          new Longitude(+0.0), new Latitude(+90.0)), (short)1);
      assertTrue(new QuadKey(Type.LatLon, 1, 1, (short)1).equalTo(key));
      assertEquals("1", key.to_internal_string());
      key = QuadKey.get_key_from_longitude_latitude_at_depth(
        Type.LatLon, new GeoCoordinate2d(
          new Longitude(+180.0), new Latitude(+90.0)), (short)1);
      assertTrue(new QuadKey(Type.LatLon, 1, 1, (short)1).equalTo(key));
      assertEquals("1", key.to_internal_string());
    }
  }

  @Test
  public void get_keys_from_longitude_latitude_bounding_box_test() {
    {
      QuadKeysVector outKeys;
      outKeys = QuadKey.get_keys_from_longitude_latitude_bounding_box(
        Type.LatLon,
        new GeoCoordinateBoundingBox2d(
          new GeoCoordinate2d(new Longitude(-180.0), new Latitude(+90.0)),
          new GeoCoordinate2d(new Longitude(+180.0), new Latitude(-90.0))),
        (short)0);
      assertEquals((short)1, outKeys.size());
      assertTrue(vectorContains(outKeys, new QuadKey(Type.LatLon, 0, 0,
        (short)0)));
    }

    {
      QuadKeysVector outKeys;
      outKeys = QuadKey.get_keys_from_longitude_latitude_bounding_box(
        Type.LatLon,
        new GeoCoordinateBoundingBox2d(
          new GeoCoordinate2d(new Longitude(-180.0), new Latitude(+90.0)),
          new GeoCoordinate2d(new Longitude(+180.0), new Latitude(-90.0))),
        (short)1);
      assertEquals((short)4, outKeys.size());
      assertTrue(vectorContains(outKeys, new QuadKey(Type.LatLon, 0, 0,
        (short)1)));
      assertTrue(vectorContains(outKeys, new QuadKey(Type.LatLon, 0, 1,
        (short)1)));
      assertTrue(vectorContains(outKeys, new QuadKey(Type.LatLon, 1, 0,
        (short)1)));
      assertTrue(vectorContains(outKeys, new QuadKey(Type.LatLon, 1, 1,
        (short)1)));
    }

    {
      QuadKeysVector outKeys;
      outKeys = QuadKey.get_keys_from_longitude_latitude_bounding_box(
        Type.LatLon,
        new GeoCoordinateBoundingBox2d(
          new GeoCoordinate2d(new Longitude(-180.0), new Latitude(-0.1)),
          new GeoCoordinate2d(new Longitude(-0.1), new Latitude(+90.0))),
        (short)1);
      assertEquals(2, outKeys.size());
      assertTrue(vectorContains(outKeys, new QuadKey(Type.LatLon, 0, 0,
        (short)1)));
      assertTrue(vectorContains(outKeys, new QuadKey(Type.LatLon, 1, 0,
        (short)1)));
    }

    {
      QuadKeysVector outKeys;
      outKeys = QuadKey.get_keys_from_longitude_latitude_bounding_box(
        Type.LatLon,
        new GeoCoordinateBoundingBox2d(
          new GeoCoordinate2d(new Longitude(+0.0), new Latitude(-0.1)),
          new GeoCoordinate2d(new Longitude(+180.0), new Latitude(+90.0))),
        (short)1);
      assertEquals(2, outKeys.size());
      assertTrue(vectorContains(outKeys, new QuadKey(Type.LatLon, 0, 1,
        (short)1)));
      assertTrue(vectorContains(outKeys, new QuadKey(Type.LatLon, 1, 1,
        (short)1)));
    }

    {
      QuadKeysVector outKeys;
      outKeys = QuadKey.get_keys_from_longitude_latitude_bounding_box(
        Type.LatLon,
        new GeoCoordinateBoundingBox2d(
          new GeoCoordinate2d(new Longitude(-0.1), new Latitude(-0.1)),
          new GeoCoordinate2d(new Longitude(+0.1), new Latitude(+0.1))),
        (short)1);
      assertEquals(4, outKeys.size());
      assertTrue(vectorContains(outKeys, new QuadKey(Type.LatLon, 0, 0,
        (short)1)));
      assertTrue(vectorContains(outKeys, new QuadKey(Type.LatLon, 0, 1,
        (short)1)));
      assertTrue(vectorContains(outKeys, new QuadKey(Type.LatLon, 1, 0,
        (short)1)));
      assertTrue(vectorContains(outKeys, new QuadKey(Type.LatLon, 1, 1,
        (short)1)));
    }
  }

  @Test
  public void known_sample_of_locations_test()
  {
    QuadKey key;

    {
      key = QuadKey.get_key_from_longitude_latitude_at_depth(
        Type.LatLon, new GeoCoordinate2d(new Longitude(-122.4183),
          new Latitude(37.7750)), (short)1);
      assertEquals("0", key.to_internal_string());
      key = QuadKey.get_key_from_longitude_latitude_at_depth(
        Type.LatLon, new GeoCoordinate2d(new Longitude(-122.4183),
          new Latitude(37.7750)), (short)2);
      assertEquals("02", key.to_internal_string());
      key = QuadKey.get_key_from_longitude_latitude_at_depth(
        Type.LatLon, new GeoCoordinate2d(new Longitude(-122.4183),
          new Latitude(37.7750)), (short)3);
      assertEquals("021", key.to_internal_string());
      key = QuadKey.get_key_from_longitude_latitude_at_depth(
        Type.LatLon, new GeoCoordinate2d(new Longitude(-122.4183),
          new Latitude(37.7750)), (short)4);
      assertEquals("0210", key.to_internal_string());
    }

    {
      key = QuadKey.get_key_from_longitude_latitude_at_depth(
        Type.LatLon, new GeoCoordinate2d(new Longitude(+134.9),
          new Latitude(-67.6)), (short)3);
      assertTrue(new QuadKey(Type.LatLon, 0, 6, (short)3).equalTo(key));
      assertEquals("332", key.to_internal_string());

      key = QuadKey.get_key_from_longitude_latitude_at_depth(
        Type.LatLon, new GeoCoordinate2d(new Longitude(+135.0),
          new Latitude(-67.5)), (short)3);
      assertTrue(new QuadKey(Type.LatLon, 1, 7, (short)3).equalTo(key));
      assertEquals("331", key.to_internal_string());
    }
  }
}

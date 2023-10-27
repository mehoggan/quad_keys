package com.quad_keys;

import org.junit.BeforeClass;
import org.junit.Test;

import java.util.ArrayList;
import java.util.List;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertTrue;

public class UlpQnrSystemTest {

  private boolean vectorContains(QuadKeysVector vect, QuadKey key) {
    boolean found = false;
    for (int i = 0; i < vect.size(); ++i) {
      QuadKey curr = vect.get(i);
      if (curr.equalTo(key)) {
        found = true;
        break;
      }
    }
    return found;
  }

  @BeforeClass
  public static void setUpBeforeClass() throws Exception {
    System.loadLibrary("QuadKeys_java");
  }

  @Test
  public void is_valid_test() {
    // See Test_QuadKey TestSpecificCtorTest.
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
    QuadKey quadKey = new QuadKey(Type.UlpQnr, 0, 0, (short)0);
    String fmt = quadKey.to_internal_string();
    assertEquals("1", fmt);
    QuadKey quadKeyBack = QuadKey.from_internal_string(Type.UlpQnr, fmt);
    assertTrue(quadKey.equalTo(quadKeyBack));

    quadKey = new QuadKey(Type.UlpQnr, 0, 0, (short)1);
    fmt = quadKey.to_internal_string();
    assertEquals("4", fmt);
    quadKeyBack = QuadKey.from_internal_string(Type.UlpQnr, fmt);
    assertTrue(quadKey.equalTo(quadKeyBack));

    quadKey = new QuadKey(Type.UlpQnr, 0, 1, (short)1);
    fmt = quadKey.to_internal_string();
    assertEquals("5", fmt);
    quadKeyBack = QuadKey.from_internal_string(Type.UlpQnr, fmt);
    assertTrue(quadKey.equalTo(quadKeyBack));

    quadKey = new QuadKey(Type.UlpQnr, 0, 0, (short)2);
    fmt = quadKey.to_internal_string();
    assertEquals("16", fmt);
    quadKeyBack = QuadKey.from_internal_string(Type.UlpQnr, fmt);
    assertTrue(quadKey.equalTo(quadKeyBack));

    quadKey = new QuadKey(Type.UlpQnr, 0, 1, (short)2);
    fmt = quadKey.to_internal_string();
    assertEquals("17", fmt);
    quadKeyBack = QuadKey.from_internal_string(Type.UlpQnr, fmt);
    assertTrue(quadKey.equalTo(quadKeyBack));

    quadKey = new QuadKey(Type.UlpQnr, 1, 0, (short)2);
    fmt = quadKey.to_internal_string();
    assertEquals("20", fmt);
    quadKeyBack = QuadKey.from_internal_string(Type.UlpQnr, fmt);
    assertTrue(quadKey.equalTo(quadKeyBack));

    quadKey = new QuadKey(Type.UlpQnr, 1, 1, (short)2);
    fmt = quadKey.to_internal_string();
    assertEquals("21", fmt);
    quadKeyBack = QuadKey.from_internal_string(Type.UlpQnr, fmt);
    assertTrue(quadKey.equalTo(quadKeyBack));

    quadKey = new QuadKey(Type.UlpQnr, 0, 2, (short)2);
    fmt = quadKey.to_internal_string();
    assertEquals("18", fmt);
    quadKeyBack = QuadKey.from_internal_string(Type.UlpQnr, fmt);
    assertTrue(quadKey.equalTo(quadKeyBack));

    quadKey = new QuadKey(Type.UlpQnr, 0, 3, (short)2);
    fmt = quadKey.to_internal_string();
    assertEquals("19", fmt);
    quadKeyBack = QuadKey.from_internal_string(Type.UlpQnr, fmt);
    assertTrue(quadKey.equalTo(quadKeyBack));

    quadKey = new QuadKey(Type.UlpQnr, 1, 2, (short)2);
    fmt = quadKey.to_internal_string();
    assertEquals("22", fmt);
    quadKeyBack = QuadKey.from_internal_string(Type.UlpQnr, fmt);
    assertTrue(quadKey.equalTo(quadKeyBack));

    quadKey = new QuadKey(Type.UlpQnr, 1, 3, (short)2);
    fmt = quadKey.to_internal_string();
    assertEquals("23", fmt);
    quadKeyBack = QuadKey.from_internal_string(Type.UlpQnr, fmt);
    assertTrue(quadKey.equalTo(quadKeyBack));

    // For Sanity Purposes and to Verify NO Fence Post Erros. Use a bit of
    // brute force.
    List<Integer> expected = new ArrayList<>();
    for (int i = 64; i < 64 + 32; ++i) {
      expected.add(i);
    }
    for (int i = 0; i < (8 * 4); ++i) {
      int row = i / 8;
      int col = i % 8;
      quadKey = new QuadKey(Type.UlpQnr, row, col, (short)3);
      fmt = quadKey.to_internal_string();

      String expectedStr = "" + expected.get(i);

      assertEquals(expectedStr, fmt);
      quadKeyBack = QuadKey.from_internal_string(Type.UlpQnr, fmt);
      assertTrue(quadKey.equalTo(quadKeyBack));
    }

    quadKey = new QuadKey(Type.UlpQnr, 0, 0, (short)3);
    fmt = quadKey.to_internal_string();
    assertEquals("64", fmt);
    quadKeyBack = QuadKey.from_internal_string(Type.UlpQnr, fmt);
    assertTrue(quadKey.equalTo(quadKeyBack));
  }

  @Test
  public void get_geo_coordinate_bounds2d_test() {
    QuadKey quadKey;
    GeoCoordinateBoundingBox2d bbox = new GeoCoordinateBoundingBox2d();

    quadKey = new QuadKey(Type.UlpQnr, 0, 0, (short)0);
    quadKey.get_geo_coordinate_bounds2d(bbox);
    assertTrue(bbox.lower_left().near(new GeoCoordinate2d(
      new Longitude(-180.0), new Latitude(-90.0)), 1e-4));
    assertTrue(bbox.upper_right().near(new GeoCoordinate2d(
      new Longitude(+180.0), new Latitude(+90.0)), 1e-4));

    quadKey = new QuadKey(Type.UlpQnr, 0, 0, (short)1);
    quadKey.get_geo_coordinate_bounds2d(bbox);
    assertTrue(bbox.lower_left().near(new GeoCoordinate2d(
      new Longitude(-180.0), new Latitude(-90.0)), 1e-4));
    assertTrue(bbox.upper_right().near(new GeoCoordinate2d(
      new Longitude(+0.0), new Latitude(+90.0)), 1e-4));

    quadKey = new QuadKey(Type.UlpQnr, 0, 1, (short)1);
    quadKey.get_geo_coordinate_bounds2d(bbox);
    assertTrue(bbox.lower_left().near(new GeoCoordinate2d(
      new Longitude(+0.0), new Latitude(-90.0)), 1e-4));
    assertTrue(bbox.upper_right().near(new GeoCoordinate2d(
      new Longitude(+180.0), new Latitude(+90.0)), 1e-4));

    quadKey = new QuadKey(Type.UlpQnr, 0, 0, (short)2);
    quadKey.get_geo_coordinate_bounds2d(bbox);
    assertTrue(bbox.lower_left().near(new GeoCoordinate2d(
      new Longitude(-180.0), new Latitude(-90.0)), 1e-4));
    assertTrue(bbox.upper_right().near(new GeoCoordinate2d(
      new Longitude(-90.0), new Latitude(+0.0)), 1e-4));

    quadKey = new QuadKey(Type.UlpQnr, 0, 1, (short)2);
    quadKey.get_geo_coordinate_bounds2d(bbox);
    assertTrue(bbox.lower_left().near(new GeoCoordinate2d(
      new Longitude(-90.0), new Latitude(-90.0)), 1e-4));

    assertTrue(bbox.upper_right().near(new GeoCoordinate2d(
      new Longitude(+0.0), new Latitude(+0.0)), 1e-4));

    quadKey = new QuadKey(Type.UlpQnr, 1, 0, (short)2);
    quadKey.get_geo_coordinate_bounds2d(bbox);
    assertTrue(bbox.lower_left().near(new GeoCoordinate2d(
      new Longitude(-180.0), new Latitude(+0.0)), 1e-4));
    assertTrue(bbox.upper_right().near(new GeoCoordinate2d(
      new Longitude(-90.0), new Latitude(+90.0)), 1e-4));

    quadKey = new QuadKey(Type.UlpQnr, 1, 1, (short)2);
    quadKey.get_geo_coordinate_bounds2d(bbox);
    assertTrue(bbox.lower_left().near(new GeoCoordinate2d(
      new Longitude(-90.0), new Latitude(+0.0)), 1e-4));
    assertTrue(bbox.upper_right().near(new GeoCoordinate2d(
      new Longitude(+0.0), new Latitude(+90.0)), 1e-4));

    quadKey = new QuadKey(Type.UlpQnr, 0, 2, (short)2);
    quadKey.get_geo_coordinate_bounds2d(bbox);
    assertTrue(bbox.lower_left().near(new GeoCoordinate2d(
      new Longitude(+0.0), new Latitude(-90.0)), 1e-4));
    assertTrue(bbox.upper_right().near(new GeoCoordinate2d(
      new Longitude(+90.0), new Latitude(+0.0)), 1e-4));

    quadKey = new QuadKey(Type.UlpQnr, 0, 3, (short)2);
    quadKey.get_geo_coordinate_bounds2d(bbox);
    assertTrue(bbox.lower_left().near(new GeoCoordinate2d(
      new Longitude(+90.0), new Latitude(-90.0)), 1e-4));
    assertTrue(bbox.upper_right().near(new GeoCoordinate2d(
      new Longitude(+180.0), new Latitude(+0.0)), 1e-4));

    quadKey = new QuadKey(Type.UlpQnr, 1, 2, (short)2);
    quadKey.get_geo_coordinate_bounds2d(bbox);
    assertTrue(bbox.lower_left().near(new GeoCoordinate2d(
      new Longitude(+0.0), new Latitude(+0.0)), 1e-4));
    assertTrue(bbox.upper_right().near(new GeoCoordinate2d(
      new Longitude(+90.0), new Latitude(+90.0)), 1e-4));

    quadKey = new QuadKey(Type.UlpQnr, 1, 3, (short)2);
    quadKey.get_geo_coordinate_bounds2d(bbox);
    assertTrue(bbox.lower_left().near(new GeoCoordinate2d(
      new Longitude(+90.0), new Latitude(+0.0)), 1e-4));
    assertTrue(bbox.upper_right().near(new GeoCoordinate2d(
      new Longitude(+180.0), new Latitude(+90.0)), 1e-4));
  }

  @Test
  public void get_key_from_longitude_latitude_at_depth_to_bounds_test() {
    QuadKey computedKey;
    computedKey = QuadKey.get_key_from_longitude_latitude_at_depth(
      Type.UlpQnr, new GeoCoordinate2d(new Longitude(-180.0),
        new Latitude(-90.0)), (short)0);
    assertEquals("1", computedKey.to_internal_string());
    computedKey = QuadKey.get_key_from_longitude_latitude_at_depth(
      Type.UlpQnr, new GeoCoordinate2d(new Longitude(0.0),
        new Latitude(0.0)), (short)0);
    assertEquals("1", computedKey.to_internal_string());

    computedKey = QuadKey.get_key_from_longitude_latitude_at_depth(
      Type.UlpQnr, new GeoCoordinate2d(new Longitude(-180.0),
        new Latitude(-90.0)), (short)1);
    assertEquals("4", computedKey.to_internal_string());
    computedKey = QuadKey.get_key_from_longitude_latitude_at_depth(
      Type.UlpQnr, new GeoCoordinate2d(new Longitude(-180.0),
        new Latitude(90.0)), (short)1);
    assertEquals("4", computedKey.to_internal_string());
    computedKey = QuadKey.get_key_from_longitude_latitude_at_depth(
      Type.UlpQnr, new GeoCoordinate2d(new Longitude(0.1),
        new Latitude(-90.0)), (short)1);
    assertEquals("5", computedKey.to_internal_string());
    computedKey = QuadKey.get_key_from_longitude_latitude_at_depth(
      Type.UlpQnr, new GeoCoordinate2d(new Longitude(180.0),
        new Latitude(90.0)), (short)1);
    assertEquals("5", computedKey.to_internal_string());

    computedKey = QuadKey.get_key_from_longitude_latitude_at_depth(
      Type.UlpQnr, new GeoCoordinate2d(new Longitude(-180.0),
        new Latitude(-90.0)), (short)2);
    assertEquals("16", computedKey.to_internal_string());
    computedKey = QuadKey.get_key_from_longitude_latitude_at_depth(
      Type.UlpQnr, new GeoCoordinate2d(new Longitude(-89.9),
        new Latitude(-90.0)), (short)2);
    assertEquals("17", computedKey.to_internal_string());
    computedKey = QuadKey.get_key_from_longitude_latitude_at_depth(
      Type.UlpQnr, new GeoCoordinate2d(new Longitude(0.1),
        new Latitude(-90.0)), (short)2);
    assertEquals("18", computedKey.to_internal_string());
    computedKey = QuadKey.get_key_from_longitude_latitude_at_depth(
      Type.UlpQnr, new GeoCoordinate2d(new Longitude(90.1),
        new Latitude(-90.0)), (short)2);
    assertEquals("19", computedKey.to_internal_string());
    computedKey = QuadKey.get_key_from_longitude_latitude_at_depth(
      Type.UlpQnr, new GeoCoordinate2d(new Longitude(-180.0),
        new Latitude(0.1)), (short)2);
    assertEquals("20", computedKey.to_internal_string());
    computedKey = QuadKey.get_key_from_longitude_latitude_at_depth(
      Type.UlpQnr, new GeoCoordinate2d(new Longitude(-89.9),
        new Latitude(0.1)), (short)2);
    assertEquals("21", computedKey.to_internal_string());
    computedKey = QuadKey.get_key_from_longitude_latitude_at_depth(
      Type.UlpQnr, new GeoCoordinate2d(new Longitude(0.1),
        new Latitude(0.1)), (short)2);
    assertEquals("22", computedKey.to_internal_string());
    computedKey = QuadKey.get_key_from_longitude_latitude_at_depth(
      Type.UlpQnr, new GeoCoordinate2d(new Longitude(90.1),
        new Latitude(0.1)), (short)2);
    assertEquals("23", computedKey.to_internal_string());
  }

  @Test
  public void get_keys_from_longitude_latitude_bounding_boxTest() {
    QuadKeysVector outKeys;
    QuadKey quadKey;

    // Select Entire Earth
    outKeys = QuadKey.get_keys_from_longitude_latitude_bounding_box
      (Type.UlpQnr,
      new GeoCoordinateBoundingBox2d(new GeoCoordinate2d(
        new Longitude(-180.0), new Latitude(-90.0)), new GeoCoordinate2d(
        new Longitude(180.0), new Latitude(90.0))),
      (short)0);
    quadKey = QuadKey.from_internal_string(Type.UlpQnr, "1");
    assertEquals(1, outKeys.size());
    assertTrue(vectorContains(outKeys, quadKey));

    // Select Very Center of the Earth
    outKeys = QuadKey.get_keys_from_longitude_latitude_bounding_box
      (Type.UlpQnr,
      new GeoCoordinateBoundingBox2d(new GeoCoordinate2d(
        new Longitude(-0.1), new Latitude(-0.1)), new GeoCoordinate2d(
        new Longitude(0.1), new Latitude(0.1))),
      (short)0);
    quadKey = QuadKey.from_internal_string(Type.UlpQnr, "1");
    assertEquals(1, outKeys.size());
    assertTrue(vectorContains(outKeys, quadKey));

    // Select Western Hemisphere
    outKeys = QuadKey.get_keys_from_longitude_latitude_bounding_box
      (Type.UlpQnr,
      new GeoCoordinateBoundingBox2d(new GeoCoordinate2d(
        new Longitude(-180.0), new Latitude(-90.0)), new GeoCoordinate2d(
        new Longitude(0.0), new Latitude(90.0))),
      (short)1);
    quadKey = QuadKey.from_internal_string(Type.UlpQnr, "4");
    assertEquals(1, outKeys.size());
    assertTrue(vectorContains(outKeys, quadKey));

    // Select Eastern Hemisphere
    outKeys = QuadKey.get_keys_from_longitude_latitude_bounding_box
      (Type.UlpQnr,
      new GeoCoordinateBoundingBox2d(new GeoCoordinate2d(
        new Longitude(0.1), new Latitude(-90.0)), new GeoCoordinate2d(
        new Longitude(180), new Latitude(90.0))),
      (short)1);
    quadKey = QuadKey.from_internal_string(Type.UlpQnr, "5");
    assertEquals(1, outKeys.size());
    assertTrue(vectorContains(outKeys, quadKey));

    // Select Entire Planet
    outKeys = QuadKey.get_keys_from_longitude_latitude_bounding_box
      (Type.UlpQnr,
      new GeoCoordinateBoundingBox2d(new GeoCoordinate2d(
        new Longitude(-180.0), new Latitude(-90.0)), new GeoCoordinate2d(
        new Longitude(180), new Latitude(90.0))),
      (short)1);
    QuadKey quadKeya = QuadKey.from_internal_string(Type.UlpQnr, "4");
    QuadKey quadKeyb = QuadKey.from_internal_string(Type.UlpQnr, "5");
    assertEquals(2, outKeys.size());
    assertTrue(vectorContains(outKeys, quadKeya));
    assertTrue(vectorContains(outKeys, quadKeyb));

    // Select South West Corner
    outKeys = QuadKey.get_keys_from_longitude_latitude_bounding_box
      (Type.UlpQnr,
      new GeoCoordinateBoundingBox2d(new GeoCoordinate2d(
        new Longitude(-180.0), new Latitude(-90.0)), new GeoCoordinate2d(
        new Longitude(-90.0), new Latitude(0.0))),
      (short)2);
    quadKey = QuadKey.from_internal_string(Type.UlpQnr, "16");
    assertEquals(1, outKeys.size());
    assertTrue(vectorContains(outKeys, quadKey));

    // Select South America
    outKeys = QuadKey.get_keys_from_longitude_latitude_bounding_box
      (Type.UlpQnr,
      new GeoCoordinateBoundingBox2d(new GeoCoordinate2d(
        new Longitude(-89.9), new Latitude(-90.0)), new GeoCoordinate2d(
        new Longitude(0.0), new Latitude(0.0))),
      (short)2);
    quadKey = QuadKey.from_internal_string(Type.UlpQnr, "17");
    assertEquals(1, outKeys.size());
    assertTrue(vectorContains(outKeys, quadKey));

    // Select North West Corner
    outKeys = QuadKey.get_keys_from_longitude_latitude_bounding_box
      (Type.UlpQnr,
      new GeoCoordinateBoundingBox2d(new GeoCoordinate2d(
        new Longitude(-180.0), new Latitude(0.1)), new GeoCoordinate2d(
        new Longitude(-90.0), new Latitude(90.0))),
      (short)2);
    quadKey = QuadKey.from_internal_string(Type.UlpQnr, "20");
    assertEquals(1, outKeys.size());
    assertTrue(vectorContains(outKeys, quadKey));

    // Select Greenland
    outKeys = QuadKey.get_keys_from_longitude_latitude_bounding_box
      (Type.UlpQnr,
      new GeoCoordinateBoundingBox2d(new GeoCoordinate2d(
        new Longitude(-89.9), new Latitude(0.1)), new GeoCoordinate2d(
        new Longitude(0.0), new Latitude(90.0))),
      (short)2);
    quadKey = QuadKey.from_internal_string(Type.UlpQnr, "21");
    assertEquals(1, outKeys.size());
    assertTrue(vectorContains(outKeys, quadKey));

    // Select South Pole
    outKeys = QuadKey.get_keys_from_longitude_latitude_bounding_box
      (Type.UlpQnr,
      new GeoCoordinateBoundingBox2d(new GeoCoordinate2d(
        new Longitude(0.1), new Latitude(-90.0)), new GeoCoordinate2d(
        new Longitude(90.0), new Latitude(0.0))),
      (short)2);
    quadKey = QuadKey.from_internal_string(Type.UlpQnr, "18");
    assertEquals(1, outKeys.size());
    assertTrue(vectorContains(outKeys, quadKey));

    // Select South East Corner
    outKeys = QuadKey.get_keys_from_longitude_latitude_bounding_box
      (Type.UlpQnr,
      new GeoCoordinateBoundingBox2d(new GeoCoordinate2d(
        new Longitude(90.1), new Latitude(-90.0)), new GeoCoordinate2d(
        new Longitude(180.0), new Latitude(0.0))),
      (short)2);
    quadKey = QuadKey.from_internal_string(Type.UlpQnr, "19");
    assertEquals(1, outKeys.size());
    assertTrue(vectorContains(outKeys, quadKey));

    // Select Over Europe
    outKeys = QuadKey.get_keys_from_longitude_latitude_bounding_box
      (Type.UlpQnr,
      new GeoCoordinateBoundingBox2d(new GeoCoordinate2d(
        new Longitude(0.1), new Latitude(0.1)), new GeoCoordinate2d(
        new Longitude(90.0), new Latitude(90.0))),
      (short)2);
    quadKey = QuadKey.from_internal_string(Type.UlpQnr, "22");
    assertEquals(1, outKeys.size());
    assertTrue(vectorContains(outKeys, quadKey));

    // Select North East Corner
    outKeys = QuadKey.get_keys_from_longitude_latitude_bounding_box
      (Type.UlpQnr,
      new GeoCoordinateBoundingBox2d(new GeoCoordinate2d(
        new Longitude(90.1), new Latitude(0.1)), new GeoCoordinate2d(
        new Longitude(180.0), new Latitude(90.0))),
      (short)2);
    quadKey = QuadKey.from_internal_string
      (Type.UlpQnr, "23");
    assertEquals(1, outKeys.size());
    assertTrue(vectorContains(outKeys, quadKey));

    // Select Entire Map
    outKeys = QuadKey.get_keys_from_longitude_latitude_bounding_box
      (Type.UlpQnr,
      new GeoCoordinateBoundingBox2d(new GeoCoordinate2d(
        new Longitude(-179.9), new Latitude(-89.9)), new GeoCoordinate2d(
        new Longitude(90.1), new Latitude(0.1))),
      (short)2);
    QuadKey quadKey0 = QuadKey.from_internal_string(Type.UlpQnr, "16");
    QuadKey quadKey1 = QuadKey.from_internal_string(Type.UlpQnr, "17");
    QuadKey quadKey2 = QuadKey.from_internal_string(Type.UlpQnr, "18");
    QuadKey quadKey3 = QuadKey.from_internal_string(Type.UlpQnr, "19");
    QuadKey quadKey4 = QuadKey.from_internal_string(Type.UlpQnr, "20");
    QuadKey quadKey5 = QuadKey.from_internal_string(Type.UlpQnr, "21");
    QuadKey quadKey6 = QuadKey.from_internal_string(Type.UlpQnr, "22");
    QuadKey quadKey7 = QuadKey.from_internal_string(Type.UlpQnr, "23");
    assertEquals(8, outKeys.size());
    assertTrue(vectorContains(outKeys, quadKey0));
    assertTrue(vectorContains(outKeys, quadKey1));
    assertTrue(vectorContains(outKeys, quadKey2));
    assertTrue(vectorContains(outKeys, quadKey3));
    assertTrue(vectorContains(outKeys, quadKey4));
    assertTrue(vectorContains(outKeys, quadKey5));
    assertTrue(vectorContains(outKeys, quadKey6));
    assertTrue(vectorContains(outKeys, quadKey7));
  }

  @Test
  public void selecetedCitiesTest() {
    // TODO: Implement Tests.
  }
}

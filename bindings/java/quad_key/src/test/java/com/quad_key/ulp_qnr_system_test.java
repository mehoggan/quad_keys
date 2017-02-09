import com.quad_key.*;
import org.junit.BeforeClass;
import org.junit.Test;

import java.util.ArrayList;
import java.util.List;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertTrue;

public class ulp_qnr_system_test {

  private boolean vectorContains(quad_key_vector vect, quad_key key) {
    boolean found = false;
    for (int i = 0; i < vect.size(); ++i) {
      quad_key curr = vect.get(i);
      if (curr.equal_to(key)) {
        found = true;
        break;
      }
    }
    return found;
  }

  @BeforeClass
  public static void setUpBeforeClass() throws Exception {
    System.loadLibrary("quad_key_jni");
  }

  @Test
  public void is_valid_test() {
    // See Test_quad_key TestSpecificCtorTest.
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
    quad_key quadKey = new quad_key(type.ulp_qnr, 0, 0, (short)0);
    String fmt = quadKey.to_internal_string();
    assertEquals("1", fmt);
    quad_key quadKeyBack = quad_key.from_internal_string(type.ulp_qnr, fmt);
    assertTrue(quadKey.equal_to(quadKeyBack));

    quadKey = new quad_key(type.ulp_qnr, 0, 0, (short)1);
    fmt = quadKey.to_internal_string();
    assertEquals("4", fmt);
    quadKeyBack = quad_key.from_internal_string(type.ulp_qnr, fmt);
    assertTrue(quadKey.equal_to(quadKeyBack));

    quadKey = new quad_key(type.ulp_qnr, 0, 1, (short)1);
    fmt = quadKey.to_internal_string();
    assertEquals("5", fmt);
    quadKeyBack = quad_key.from_internal_string(type.ulp_qnr, fmt);
    assertTrue(quadKey.equal_to(quadKeyBack));

    quadKey = new quad_key(type.ulp_qnr, 0, 0, (short)2);
    fmt = quadKey.to_internal_string();
    assertEquals("16", fmt);
    quadKeyBack = quad_key.from_internal_string(type.ulp_qnr, fmt);
    assertTrue(quadKey.equal_to(quadKeyBack));

    quadKey = new quad_key(type.ulp_qnr, 0, 1, (short)2);
    fmt = quadKey.to_internal_string();
    assertEquals("17", fmt);
    quadKeyBack = quad_key.from_internal_string(type.ulp_qnr, fmt);
    assertTrue(quadKey.equal_to(quadKeyBack));

    quadKey = new quad_key(type.ulp_qnr, 1, 0, (short)2);
    fmt = quadKey.to_internal_string();
    assertEquals("20", fmt);
    quadKeyBack = quad_key.from_internal_string(type.ulp_qnr, fmt);
    assertTrue(quadKey.equal_to(quadKeyBack));

    quadKey = new quad_key(type.ulp_qnr, 1, 1, (short)2);
    fmt = quadKey.to_internal_string();
    assertEquals("21", fmt);
    quadKeyBack = quad_key.from_internal_string(type.ulp_qnr, fmt);
    assertTrue(quadKey.equal_to(quadKeyBack));

    quadKey = new quad_key(type.ulp_qnr, 0, 2, (short)2);
    fmt = quadKey.to_internal_string();
    assertEquals("18", fmt);
    quadKeyBack = quad_key.from_internal_string(type.ulp_qnr, fmt);
    assertTrue(quadKey.equal_to(quadKeyBack));

    quadKey = new quad_key(type.ulp_qnr, 0, 3, (short)2);
    fmt = quadKey.to_internal_string();
    assertEquals("19", fmt);
    quadKeyBack = quad_key.from_internal_string(type.ulp_qnr, fmt);
    assertTrue(quadKey.equal_to(quadKeyBack));

    quadKey = new quad_key(type.ulp_qnr, 1, 2, (short)2);
    fmt = quadKey.to_internal_string();
    assertEquals("22", fmt);
    quadKeyBack = quad_key.from_internal_string(type.ulp_qnr, fmt);
    assertTrue(quadKey.equal_to(quadKeyBack));

    quadKey = new quad_key(type.ulp_qnr, 1, 3, (short)2);
    fmt = quadKey.to_internal_string();
    assertEquals("23", fmt);
    quadKeyBack = quad_key.from_internal_string(type.ulp_qnr, fmt);
    assertTrue(quadKey.equal_to(quadKeyBack));

    // For Sanity Purposes and to Verify NO Fence Post Erros. Use a bit of
    // brute force.
    List<Integer> expected = new ArrayList<>();
    for (Integer i = 64; i < 64 + 32; ++i) {
      expected.add(i);
    }
    for (Integer i = 0; i < (8 * 4); ++i) {
      Integer row = i / 8;
      Integer col = i % 8;
      quadKey = new quad_key(type.ulp_qnr, row, col, (short)3);
      fmt = quadKey.to_internal_string();

      String expectedStr = "" + expected.get(i);

      assertEquals(expectedStr, fmt);
      quadKeyBack = quad_key.from_internal_string(type.ulp_qnr, fmt);
      assertTrue(quadKey.equal_to(quadKeyBack));
    }

    quadKey = new quad_key(type.ulp_qnr, 0, 0, (short)3);
    fmt = quadKey.to_internal_string();
    assertEquals("64", fmt);
    quadKeyBack = quad_key.from_internal_string(type.ulp_qnr, fmt);
    assertTrue(quadKey.equal_to(quadKeyBack));
  }

  @Test
  public void get_geo_coordinate_bounds2d_test() {
    quad_key quadKey;
    geo_coordinate_bounding_box2d bbox = new geo_coordinate_bounding_box2d();

    quadKey = new quad_key(type.ulp_qnr, 0, 0, (short)0);
    quadKey.get_geo_coordinate_bounds2d(bbox);
    assertTrue(bbox.lower_left().near(new geo_coordinate2d(
      new longitude(-180.0), new latitude(-90.0)), 1e-4));
    assertTrue(bbox.upper_right().near(new geo_coordinate2d(
      new longitude(+180.0), new latitude(+90.0)), 1e-4));

    quadKey = new quad_key(type.ulp_qnr, 0, 0, (short)1);
    quadKey.get_geo_coordinate_bounds2d(bbox);
    assertTrue(bbox.lower_left().near(new geo_coordinate2d(
      new longitude(-180.0), new latitude(-90.0)), 1e-4));
    assertTrue(bbox.upper_right().near(new geo_coordinate2d(
      new longitude(+0.0), new latitude(+90.0)), 1e-4));

    quadKey = new quad_key(type.ulp_qnr, 0, 1, (short)1);
    quadKey.get_geo_coordinate_bounds2d(bbox);
    assertTrue(bbox.lower_left().near(new geo_coordinate2d(
      new longitude(+0.0), new latitude(-90.0)), 1e-4));
    assertTrue(bbox.upper_right().near(new geo_coordinate2d(
      new longitude(+180.0), new latitude(+90.0)), 1e-4));

    quadKey = new quad_key(type.ulp_qnr, 0, 0, (short)2);
    quadKey.get_geo_coordinate_bounds2d(bbox);
    assertTrue(bbox.lower_left().near(new geo_coordinate2d(
      new longitude(-180.0), new latitude(-90.0)), 1e-4));
    assertTrue(bbox.upper_right().near(new geo_coordinate2d(
      new longitude(-90.0), new latitude(+0.0)), 1e-4));

    quadKey = new quad_key(type.ulp_qnr, 0, 1, (short)2);
    quadKey.get_geo_coordinate_bounds2d(bbox);
    assertTrue(bbox.lower_left().near(new geo_coordinate2d(
      new longitude(-90.0), new latitude(-90.0)), 1e-4));

    assertTrue(bbox.upper_right().near(new geo_coordinate2d(
      new longitude(+0.0), new latitude(+0.0)), 1e-4));

    quadKey = new quad_key(type.ulp_qnr, 1, 0, (short)2);
    quadKey.get_geo_coordinate_bounds2d(bbox);
    assertTrue(bbox.lower_left().near(new geo_coordinate2d(
      new longitude(-180.0), new latitude(+0.0)), 1e-4));
    assertTrue(bbox.upper_right().near(new geo_coordinate2d(
      new longitude(-90.0), new latitude(+90.0)), 1e-4));

    quadKey = new quad_key(type.ulp_qnr, 1, 1, (short)2);
    quadKey.get_geo_coordinate_bounds2d(bbox);
    assertTrue(bbox.lower_left().near(new geo_coordinate2d(
      new longitude(-90.0), new latitude(+0.0)), 1e-4));
    assertTrue(bbox.upper_right().near(new geo_coordinate2d(
      new longitude(+0.0), new latitude(+90.0)), 1e-4));

    quadKey = new quad_key(type.ulp_qnr, 0, 2, (short)2);
    quadKey.get_geo_coordinate_bounds2d(bbox);
    assertTrue(bbox.lower_left().near(new geo_coordinate2d(
      new longitude(+0.0), new latitude(-90.0)), 1e-4));
    assertTrue(bbox.upper_right().near(new geo_coordinate2d(
      new longitude(+90.0), new latitude(+0.0)), 1e-4));

    quadKey = new quad_key(type.ulp_qnr, 0, 3, (short)2);
    quadKey.get_geo_coordinate_bounds2d(bbox);
    assertTrue(bbox.lower_left().near(new geo_coordinate2d(
      new longitude(+90.0), new latitude(-90.0)), 1e-4));
    assertTrue(bbox.upper_right().near(new geo_coordinate2d(
      new longitude(+180.0), new latitude(+0.0)), 1e-4));

    quadKey = new quad_key(type.ulp_qnr, 1, 2, (short)2);
    quadKey.get_geo_coordinate_bounds2d(bbox);
    assertTrue(bbox.lower_left().near(new geo_coordinate2d(
      new longitude(+0.0), new latitude(+0.0)), 1e-4));
    assertTrue(bbox.upper_right().near(new geo_coordinate2d(
      new longitude(+90.0), new latitude(+90.0)), 1e-4));

    quadKey = new quad_key(type.ulp_qnr, 1, 3, (short)2);
    quadKey.get_geo_coordinate_bounds2d(bbox);
    assertTrue(bbox.lower_left().near(new geo_coordinate2d(
      new longitude(+90.0), new latitude(+0.0)), 1e-4));
    assertTrue(bbox.upper_right().near(new geo_coordinate2d(
      new longitude(+180.0), new latitude(+90.0)), 1e-4));
  }

  @Test
  public void get_key_from_longitude_latitude_at_depth_to_bounds_test() {
    quad_key computedKey;
    computedKey = quad_key.get_key_from_longitude_latitude_at_depth(
      type.ulp_qnr, new geo_coordinate2d(new longitude(-180.0),
        new latitude(-90.0)), (short)0);
    assertEquals("1", computedKey.to_internal_string());
    computedKey = quad_key.get_key_from_longitude_latitude_at_depth(
      type.ulp_qnr, new geo_coordinate2d(new longitude(0.0),
        new latitude(0.0)), (short)0);
    assertEquals("1", computedKey.to_internal_string());

    computedKey = quad_key.get_key_from_longitude_latitude_at_depth(
      type.ulp_qnr, new geo_coordinate2d(new longitude(-180.0),
        new latitude(-90.0)), (short)1);
    assertEquals("4", computedKey.to_internal_string());
    computedKey = quad_key.get_key_from_longitude_latitude_at_depth(
      type.ulp_qnr, new geo_coordinate2d(new longitude(-180.0),
        new latitude(90.0)), (short)1);
    assertEquals("4", computedKey.to_internal_string());
    computedKey = quad_key.get_key_from_longitude_latitude_at_depth(
      type.ulp_qnr, new geo_coordinate2d(new longitude(0.1),
        new latitude(-90.0)), (short)1);
    assertEquals("5", computedKey.to_internal_string());
    computedKey = quad_key.get_key_from_longitude_latitude_at_depth(
      type.ulp_qnr, new geo_coordinate2d(new longitude(180.0), 
        new latitude(90.0)), (short)1);
    assertEquals("5", computedKey.to_internal_string());

    computedKey = quad_key.get_key_from_longitude_latitude_at_depth(
      type.ulp_qnr, new geo_coordinate2d(new longitude(-180.0), 
        new latitude(-90.0)), (short)2);
    assertEquals("16", computedKey.to_internal_string());
    computedKey = quad_key.get_key_from_longitude_latitude_at_depth(
      type.ulp_qnr, new geo_coordinate2d(new longitude(-89.9), 
        new latitude(-90.0)), (short)2);
    assertEquals("17", computedKey.to_internal_string());
    computedKey = quad_key.get_key_from_longitude_latitude_at_depth(
      type.ulp_qnr, new geo_coordinate2d(new longitude(0.1), 
        new latitude(-90.0)), (short)2);
    assertEquals("18", computedKey.to_internal_string());
    computedKey = quad_key.get_key_from_longitude_latitude_at_depth(
      type.ulp_qnr, new geo_coordinate2d(new longitude(90.1), 
        new latitude(-90.0)), (short)2);
    assertEquals("19", computedKey.to_internal_string());
    computedKey = quad_key.get_key_from_longitude_latitude_at_depth(
      type.ulp_qnr, new geo_coordinate2d(new longitude(-180.0), 
        new latitude(0.1)), (short)2);
    assertEquals("20", computedKey.to_internal_string());
    computedKey = quad_key.get_key_from_longitude_latitude_at_depth(
      type.ulp_qnr, new geo_coordinate2d(new longitude(-89.9), 
        new latitude(0.1)), (short)2);
    assertEquals("21", computedKey.to_internal_string());
    computedKey = quad_key.get_key_from_longitude_latitude_at_depth(
      type.ulp_qnr, new geo_coordinate2d(new longitude(0.1), 
        new latitude(0.1)), (short)2);
    assertEquals("22", computedKey.to_internal_string());
    computedKey = quad_key.get_key_from_longitude_latitude_at_depth(
      type.ulp_qnr, new geo_coordinate2d(new longitude(90.1), 
        new latitude(0.1)), (short)2);
    assertEquals("23", computedKey.to_internal_string());
  }

  @Test
  public void get_keys_from_longitude_latitude_bounding_boxTest() {
    quad_key_vector outKeys;
    quad_key quadKey;

    // Select Entire Earth
    outKeys = quad_key.get_keys_from_longitude_latitude_bounding_box
      (type.ulp_qnr,
      new geo_coordinate_bounding_box2d(new geo_coordinate2d(
        new longitude(-180.0), new latitude(-90.0)), new geo_coordinate2d(
        new longitude(180.0), new latitude(90.0))),
      (short)0);
    quadKey = quad_key.from_internal_string(type.ulp_qnr, "1");
    assertEquals(1, outKeys.size());
    assertTrue(vectorContains(outKeys, quadKey));

    // Select Very Center of the Earth
    outKeys = quad_key.get_keys_from_longitude_latitude_bounding_box
      (type.ulp_qnr,
      new geo_coordinate_bounding_box2d(new geo_coordinate2d(
        new longitude(-0.1), new latitude(-0.1)), new geo_coordinate2d(
        new longitude(0.1), new latitude(0.1))),
      (short)0);
    quadKey = quad_key.from_internal_string(type.ulp_qnr, "1");
    assertEquals(1, outKeys.size());
    assertTrue(vectorContains(outKeys, quadKey));

    // Select Western Hemisphere
    outKeys = quad_key.get_keys_from_longitude_latitude_bounding_box
      (type.ulp_qnr,
      new geo_coordinate_bounding_box2d(new geo_coordinate2d(
        new longitude(-180.0), new latitude(-90.0)), new geo_coordinate2d(
        new longitude(0.0), new latitude(90.0))),
      (short)1);
    quadKey = quad_key.from_internal_string(type.ulp_qnr, "4");
    assertEquals(1, outKeys.size());
    assertTrue(vectorContains(outKeys, quadKey));

    // Select Eastern Hemisphere
    outKeys = quad_key.get_keys_from_longitude_latitude_bounding_box
      (type.ulp_qnr,
      new geo_coordinate_bounding_box2d(new geo_coordinate2d(
        new longitude(0.1), new latitude(-90.0)), new geo_coordinate2d(
        new longitude(180), new latitude(90.0))),
      (short)1);
    quadKey = quad_key.from_internal_string(type.ulp_qnr, "5");
    assertEquals(1, outKeys.size());
    assertTrue(vectorContains(outKeys, quadKey));

    // Select Entire Planet
    outKeys = quad_key.get_keys_from_longitude_latitude_bounding_box
      (type.ulp_qnr,
      new geo_coordinate_bounding_box2d(new geo_coordinate2d(
        new longitude(-180.0), new latitude(-90.0)), new geo_coordinate2d(
        new longitude(180), new latitude(90.0))),
      (short)1);
    quad_key quadKeya = quad_key.from_internal_string(type.ulp_qnr, "4");
    quad_key quadKeyb = quad_key.from_internal_string(type.ulp_qnr, "5");
    assertEquals(2, outKeys.size());
    assertTrue(vectorContains(outKeys, quadKeya));
    assertTrue(vectorContains(outKeys, quadKeyb));

    // Select South West Corner
    outKeys = quad_key.get_keys_from_longitude_latitude_bounding_box
      (type.ulp_qnr,
      new geo_coordinate_bounding_box2d(new geo_coordinate2d(
        new longitude(-180.0), new latitude(-90.0)), new geo_coordinate2d(
        new longitude(-90.0), new latitude(0.0))),
      (short)2);
    quadKey = quad_key.from_internal_string(type.ulp_qnr, "16");
    assertEquals(1, outKeys.size());
    assertTrue(vectorContains(outKeys, quadKey));

    // Select South America
    outKeys = quad_key.get_keys_from_longitude_latitude_bounding_box
      (type.ulp_qnr,
      new geo_coordinate_bounding_box2d(new geo_coordinate2d(
        new longitude(-89.9), new latitude(-90.0)), new geo_coordinate2d(
        new longitude(0.0), new latitude(0.0))),
      (short)2);
    quadKey = quad_key.from_internal_string(type.ulp_qnr, "17");
    assertEquals(1, outKeys.size());
    assertTrue(vectorContains(outKeys, quadKey));

    // Select North West Corner
    outKeys = quad_key.get_keys_from_longitude_latitude_bounding_box
      (type.ulp_qnr,
      new geo_coordinate_bounding_box2d(new geo_coordinate2d(
        new longitude(-180.0), new latitude(0.1)), new geo_coordinate2d(
        new longitude(-90.0), new latitude(90.0))),
      (short)2);
    quadKey = quad_key.from_internal_string(type.ulp_qnr, "20");
    assertEquals(1, outKeys.size());
    assertTrue(vectorContains(outKeys, quadKey));

    // Select Greenland
    outKeys = quad_key.get_keys_from_longitude_latitude_bounding_box
      (type.ulp_qnr,
      new geo_coordinate_bounding_box2d(new geo_coordinate2d(
        new longitude(-89.9), new latitude(0.1)), new geo_coordinate2d(
        new longitude(0.0), new latitude(90.0))),
      (short)2);
    quadKey = quad_key.from_internal_string(type.ulp_qnr, "21");
    assertEquals(1, outKeys.size());
    assertTrue(vectorContains(outKeys, quadKey));

    // Select South Pole
    outKeys = quad_key.get_keys_from_longitude_latitude_bounding_box
      (type.ulp_qnr,
      new geo_coordinate_bounding_box2d(new geo_coordinate2d(
        new longitude(0.1), new latitude(-90.0)), new geo_coordinate2d(
        new longitude(90.0), new latitude(0.0))),
      (short)2);
    quadKey = quad_key.from_internal_string(type.ulp_qnr, "18");
    assertEquals(1, outKeys.size());
    assertTrue(vectorContains(outKeys, quadKey));

    // Select South East Corner
    outKeys = quad_key.get_keys_from_longitude_latitude_bounding_box
      (type.ulp_qnr,
      new geo_coordinate_bounding_box2d(new geo_coordinate2d(
        new longitude(90.1), new latitude(-90.0)), new geo_coordinate2d(
        new longitude(180.0), new latitude(0.0))),
      (short)2);
    quadKey = quad_key.from_internal_string(type.ulp_qnr, "19");
    assertEquals(1, outKeys.size());
    assertTrue(vectorContains(outKeys, quadKey));

    // Select Over Europe
    outKeys = quad_key.get_keys_from_longitude_latitude_bounding_box
      (type.ulp_qnr,
      new geo_coordinate_bounding_box2d(new geo_coordinate2d(
        new longitude(0.1), new latitude(0.1)), new geo_coordinate2d(
        new longitude(90.0), new latitude(90.0))),
      (short)2);
    quadKey = quad_key.from_internal_string(type.ulp_qnr, "22");
    assertEquals(1, outKeys.size());
    assertTrue(vectorContains(outKeys, quadKey));

    // Select North East Corner
    outKeys = quad_key.get_keys_from_longitude_latitude_bounding_box
      (type.ulp_qnr,
      new geo_coordinate_bounding_box2d(new geo_coordinate2d(
        new longitude(90.1), new latitude(0.1)), new geo_coordinate2d(
        new longitude(180.0), new latitude(90.0))),
      (short)2);
    quadKey = quad_key.from_internal_string
      (type.ulp_qnr, "23");
    assertEquals(1, outKeys.size());
    assertTrue(vectorContains(outKeys, quadKey));

    // Select Entire Map
    outKeys = quad_key.get_keys_from_longitude_latitude_bounding_box
      (type.ulp_qnr,
      new geo_coordinate_bounding_box2d(new geo_coordinate2d(
        new longitude(-179.9), new latitude(-89.9)), new geo_coordinate2d(
        new longitude(90.1), new latitude(0.1))),
      (short)2);
    quad_key quadKey0 = quad_key.from_internal_string(type.ulp_qnr, "16");
    quad_key quadKey1 = quad_key.from_internal_string(type.ulp_qnr, "17");
    quad_key quadKey2 = quad_key.from_internal_string(type.ulp_qnr, "18");
    quad_key quadKey3 = quad_key.from_internal_string(type.ulp_qnr, "19");
    quad_key quadKey4 = quad_key.from_internal_string(type.ulp_qnr, "20");
    quad_key quadKey5 = quad_key.from_internal_string(type.ulp_qnr, "21");
    quad_key quadKey6 = quad_key.from_internal_string(type.ulp_qnr, "22");
    quad_key quadKey7 = quad_key.from_internal_string(type.ulp_qnr, "23");
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

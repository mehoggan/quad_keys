import com.quad_key.*;
import org.junit.BeforeClass;
import org.junit.Test;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertTrue;

public class osgeo_system_test {

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
      // See Testquad_key TestSpecificCtorTest.
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
    quad_key quadKey = new quad_key(type.osgeo, 3, 3, (short)2);
    String fmt = quadKey.to_internal_string();
    assertEquals("2/3/3", fmt);
    quad_key quadKeyBack = quad_key.from_internal_string(type.osgeo, fmt);
    assertTrue(quadKey.equal_to(quadKeyBack));

    fmt = "0/-1/-1";
    quadKeyBack = quad_key.from_internal_string(type.osgeo, fmt);
    assertTrue(new quad_key(type.osgeo, 0, 0,(short)0).equal_to(
      quadKeyBack));

    fmt = "1/1/-1";
    quadKeyBack = quad_key.from_internal_string(type.osgeo, fmt);
    assertTrue(new quad_key(type.osgeo, 0, 1, (short)1).equal_to(
      quadKeyBack));

    fmt = "1/-1/1";
    quadKeyBack = quad_key.from_internal_string(type.osgeo, fmt);
    assertTrue(new quad_key(type.osgeo, 1, 0, (short)1).equal_to(
      quadKeyBack));
  }

  @Test
  public void get_geo_coordinate_bounds2d_test() {
    quad_key quadKey;
    geo_coordinate_bounding_box2d bbox = new geo_coordinate_bounding_box2d();

    { // Depth 0
      quadKey = quad_key.from_internal_string(type.osgeo, "0/0/0");
      quadKey.get_geo_coordinate_bounds2d(bbox);
      assertTrue(new longitude(-180.0f).near(
        bbox.lower_left().get_longitude(), 1e-4));
      assertTrue(new latitude(-85.051132).near(
        bbox.lower_left().get_latitude(), 1e-4));
      assertTrue(new longitude(+180.0).near(
        bbox.upper_right().get_longitude(), 1e-4));
      assertTrue(new latitude(+85.051132).near(
        bbox.upper_right().get_latitude(), 1e-4));
    }
  }

  @Test
  public void get_key_from_longitude_latitude_at_depth_to_bounds_test() {
    quad_key quadKey;
    geo_coordinate_bounding_box2d bbox = new geo_coordinate_bounding_box2d();

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
    quadKey = quad_key.get_key_from_longitude_latitude_at_depth(type.osgeo,
      new geo_coordinate2d(new longitude(-180.0),
        new latitude(+85.05113877)), (short)0);
    assertTrue(new quad_key(type.osgeo, 0, 0, (short)0).equal_to(quadKey));
    quadKey = quad_key.get_key_from_longitude_latitude_at_depth(type.osgeo,
      new geo_coordinate2d(new longitude(+180.0),
        new latitude(+85.05113877)), (short)0);
    assertTrue(new quad_key(type.osgeo, 0, 0, (short)0).equal_to(quadKey));
    quadKey = quad_key.get_key_from_longitude_latitude_at_depth(type.osgeo,
      new geo_coordinate2d(new longitude(+180.0),
        new latitude(-85.05113877)), (short)0);
    assertTrue(new quad_key(type.osgeo, 0, 0, (short)0).equal_to(quadKey));
    quadKey = quad_key.get_key_from_longitude_latitude_at_depth(type.osgeo,
      new geo_coordinate2d(new longitude(-180.0),
        new latitude(-85.05113877)), (short)0);
    assertTrue(new quad_key(type.osgeo, 0, 0, (short)0).equal_to(quadKey));
    quadKey.get_geo_coordinate_bounds2d(bbox);
    assertTrue(bbox.lower_left().near(new geo_coordinate2d(
      new longitude(-180.0), new latitude(-85.05113877)), 1e-4));
    assertTrue(bbox.upper_right().near(new geo_coordinate2d(
      new longitude(+180.0), new latitude(+85.05113877)), 1e-4));

    quadKey = quad_key.get_key_from_longitude_latitude_at_depth(type.osgeo,
      new geo_coordinate2d(new longitude(+0.0),
        new latitude(+0.00000000)), (short)0);
    assertTrue(new quad_key(type.osgeo, 0, 0, (short)0).equal_to(quadKey));

    quadKey = quad_key.get_key_from_longitude_latitude_at_depth(type.osgeo,
      new geo_coordinate2d(new longitude(-180.0),
        new latitude(+85.05113877)), (short)1);
    assertTrue(new quad_key(type.osgeo, 1, 0, (short)1).equal_to(quadKey));
    quadKey.get_geo_coordinate_bounds2d(bbox);
    assertTrue(bbox.lower_left().near(new geo_coordinate2d(
      new longitude(-180.0), new latitude(+0.00000000)), 1e-4));
    assertTrue(bbox.upper_right().near(new geo_coordinate2d(
      new longitude(+0.0), new latitude(+85.05113877)), 1e-4));

    quadKey = quad_key.get_key_from_longitude_latitude_at_depth(type.osgeo,
      new geo_coordinate2d(new longitude(+180.0),
        new latitude(+85.05113877)), (short)1);
    assertTrue(new quad_key(type.osgeo, 1, 1,(short)1).equal_to(quadKey));
    quadKey.get_geo_coordinate_bounds2d(bbox);
    assertTrue(bbox.lower_left().near(new geo_coordinate2d(
      new longitude(+0.0), new latitude(+0.00000000)), 1e-4));
    assertTrue(bbox.upper_right().near(new geo_coordinate2d(
      new longitude(+180.0), new latitude(+85.05113877)), 1e-4));

    quadKey = quad_key.get_key_from_longitude_latitude_at_depth(type.osgeo,
      new geo_coordinate2d(new longitude(+180.0),
        new latitude(-85.05113877)), (short)1);
    assertTrue(new quad_key(type.osgeo, 0, 1, (short)1).equal_to(quadKey));
    quadKey.get_geo_coordinate_bounds2d(bbox);
    assertTrue(bbox.lower_left().near(new geo_coordinate2d(
      new longitude(+0.0), new latitude(-85.05113877)), 1e-4));
    assertTrue(bbox.upper_right().near(new geo_coordinate2d(
      new longitude(+180.0), new latitude(+0.00000000)), 1e-4));

    quadKey = quad_key.get_key_from_longitude_latitude_at_depth(type.osgeo,
      new geo_coordinate2d(new longitude(-180.0),
        new latitude(-85.05113877)), (short)1);
    assertTrue(new quad_key(type.osgeo, 0, 0,(short)1).equal_to(quadKey));
    quadKey.get_geo_coordinate_bounds2d(bbox);
    assertTrue(bbox.lower_left().near(new geo_coordinate2d(
      new longitude(-180.0), new latitude(-85.05113877)), 1e-4));
    assertTrue(bbox.upper_right().near(new geo_coordinate2d(
      new longitude(+0.0), new latitude(+0.00000000)), 1e-4));

    quadKey = quad_key.get_key_from_longitude_latitude_at_depth(type.osgeo,
      new geo_coordinate2d(new longitude(-180.0),
        new latitude(+0.00000000)), (short)1);
    assertTrue(new quad_key(type.osgeo, 0, 0, (short)1).equal_to(quadKey));
    quadKey = quad_key.get_key_from_longitude_latitude_at_depth(type.osgeo,
      new geo_coordinate2d(new longitude(+0.0),
        new latitude(+85.05113877)), (short)1);
    assertTrue(new quad_key(type.osgeo, 1, 0, (short)1).equal_to(quadKey));
    quadKey = quad_key.get_key_from_longitude_latitude_at_depth(type.osgeo,
      new geo_coordinate2d(new longitude(+180.0),
        new latitude(+0.00000000)), (short)1);
    assertTrue(new quad_key(type.osgeo, 0, 1, (short)1).equal_to(quadKey));
    quadKey = quad_key.get_key_from_longitude_latitude_at_depth(type.osgeo,
      new geo_coordinate2d(new longitude(+0.0),
        new latitude(-85.05113877)), (short)1);
    assertTrue(new quad_key(type.osgeo, 0, 0, (short)1).equal_to(quadKey));
    quadKey = quad_key.get_key_from_longitude_latitude_at_depth(type.osgeo,
      new geo_coordinate2d(new longitude(+0.0),
        new latitude(+0.00000000)), (short)1);
    assertTrue(new quad_key(type.osgeo, 0, 0, (short)1).equal_to(quadKey));

    // Note at depth 2 because of the Mercator projection the lines
    // of latitude are note perfect divisions by 2.
    quadKey = quad_key.get_key_from_longitude_latitude_at_depth(type.osgeo,
      new geo_coordinate2d(new longitude(-180.0),
        new latitude(-85.05113877)), (short)2);
    assertTrue(new quad_key(type.osgeo, 0, 0, (short)2).equal_to(quadKey));
    quadKey = quad_key.get_key_from_longitude_latitude_at_depth(type.osgeo,
      new geo_coordinate2d(new longitude(-180.0),
        new latitude(-66.5133)), (short)2);
    assertTrue(new quad_key(type.osgeo, 0, 0, (short)2).equal_to(quadKey));
    quadKey = quad_key.get_key_from_longitude_latitude_at_depth(type.osgeo,
      new geo_coordinate2d(new longitude(-180.0),
        new latitude(-66.5132)), (short)2);
    assertTrue(new quad_key(type.osgeo, 1, 0, (short)2).equal_to(quadKey));
    quadKey = quad_key.get_key_from_longitude_latitude_at_depth(type.osgeo,
      new geo_coordinate2d(new longitude(-180.0),
        new latitude(+0.1)), (short)2);
    assertTrue(new quad_key(type.osgeo, 2, 0, (short)2).equal_to(quadKey));
    quadKey = quad_key.get_key_from_longitude_latitude_at_depth(type.osgeo,
      new geo_coordinate2d(new longitude(-180.0),
        new latitude(+66.5132)), (short)2);
    assertTrue(new quad_key(type.osgeo, 2, 0, (short)2).equal_to(quadKey));
    quadKey = quad_key.get_key_from_longitude_latitude_at_depth(type.osgeo,
      new geo_coordinate2d(new longitude(-180.0),
        new latitude(+66.5133)), (short)2);
    assertTrue(new quad_key(type.osgeo, 3, 0, (short)2).equal_to(quadKey));
    quadKey = quad_key.get_key_from_longitude_latitude_at_depth(type.osgeo,
      new geo_coordinate2d(new longitude(-180.0),
        new latitude(+85.05113877)), (short)2);
    assertTrue(new quad_key(type.osgeo, 3, 0, (short)2).equal_to(quadKey));
    quadKey = quad_key.get_key_from_longitude_latitude_at_depth(type.osgeo,
      new geo_coordinate2d(new longitude(-90.0),
        new latitude(-85.05113877)), (short)2);
    assertTrue(new quad_key(type.osgeo, 0, 0, (short)2).equal_to(quadKey));
    quadKey = quad_key.get_key_from_longitude_latitude_at_depth(type.osgeo,
      new geo_coordinate2d(new longitude(-90.0),
        new latitude(-66.5133)), (short)2);
    assertTrue(new quad_key(type.osgeo, 0, 0, (short)2).equal_to(quadKey));
    quadKey = quad_key.get_key_from_longitude_latitude_at_depth(type.osgeo,
      new geo_coordinate2d(new longitude(-90.0),
        new latitude(-66.5132)), (short)2);
    assertTrue(new quad_key(type.osgeo, 1, 0, (short)2).equal_to(quadKey));
    quadKey = quad_key.get_key_from_longitude_latitude_at_depth(type.osgeo,
      new geo_coordinate2d(new longitude(-90.0),
        new latitude(+0.1)), (short)2);
    assertTrue(new quad_key(type.osgeo, 2, 0, (short)2).equal_to(quadKey));
    quadKey = quad_key.get_key_from_longitude_latitude_at_depth(type.osgeo,
      new geo_coordinate2d(new longitude(-90.0),
        new latitude(+66.5132)), (short)2);
    assertTrue(new quad_key(type.osgeo, 2, 0, (short)2).equal_to(quadKey));
    quadKey = quad_key.get_key_from_longitude_latitude_at_depth(type.osgeo,
      new geo_coordinate2d(new longitude(-90.0),
        new latitude(+66.5133)), (short)2);
    assertTrue(new quad_key(type.osgeo, 3, 0, (short)2).equal_to(quadKey));
    quadKey = quad_key.get_key_from_longitude_latitude_at_depth(type.osgeo,
      new geo_coordinate2d(new longitude(-90.0),
        new latitude(+85.05113877)), (short)2);
    assertTrue(new quad_key(type.osgeo, 3, 0, (short)2).equal_to(quadKey));
    quadKey = quad_key.get_key_from_longitude_latitude_at_depth(type.osgeo,
      new geo_coordinate2d(new longitude(-89.9),
        new latitude(-85.05113877)), (short)2);
    assertTrue(new quad_key(type.osgeo, 0, 1, (short)2).equal_to(quadKey));
    quadKey = quad_key.get_key_from_longitude_latitude_at_depth(type.osgeo,
      new geo_coordinate2d(new longitude(-89.9),
        new latitude(-66.5133)), (short)2);
    assertTrue(new quad_key(type.osgeo, 0, 1, (short)2).equal_to(quadKey));
    quadKey = quad_key.get_key_from_longitude_latitude_at_depth(type.osgeo,
      new geo_coordinate2d(new longitude(-89.9),
        new latitude(-66.5132)), (short)2);
    assertTrue(new quad_key(type.osgeo, 1, 1, (short)2).equal_to(quadKey));
    quadKey = quad_key.get_key_from_longitude_latitude_at_depth(type.osgeo,
      new geo_coordinate2d(new longitude(-89.9),
        new latitude(+0.1)), (short)2);
    assertTrue(new quad_key(type.osgeo, 2, 1, (short)2).equal_to(quadKey));
    quadKey = quad_key.get_key_from_longitude_latitude_at_depth(type.osgeo,
      new geo_coordinate2d(new longitude(-89.9),
        new latitude(+66.5132)), (short)2);
    assertTrue(new quad_key(type.osgeo, 2, 1, (short)2).equal_to(quadKey));
    quadKey = quad_key.get_key_from_longitude_latitude_at_depth(type.osgeo,
      new geo_coordinate2d(new longitude(-89.9),
        new latitude(+66.5133)), (short)2);
    assertTrue(new quad_key(type.osgeo, 3, 1, (short)2).equal_to(quadKey));
    quadKey = quad_key.get_key_from_longitude_latitude_at_depth(type.osgeo,
      new geo_coordinate2d(new longitude(-89.9),
        new latitude(+85.05113877)), (short)2);
    assertTrue(new quad_key(type.osgeo, 3, 1, (short)2).equal_to(quadKey));
    quadKey = quad_key.get_key_from_longitude_latitude_at_depth(type.osgeo,
      new geo_coordinate2d(new longitude(+0.0),
        new latitude(-85.05113877)), (short)2);
    assertTrue(new quad_key(type.osgeo, 0, 1, (short)2).equal_to(quadKey));
    quadKey = quad_key.get_key_from_longitude_latitude_at_depth(type.osgeo,
      new geo_coordinate2d(new longitude(+0.0),
        new latitude(-66.5133)), (short)2);
    assertTrue(new quad_key(type.osgeo, 0, 1, (short)2).equal_to(quadKey));
    quadKey = quad_key.get_key_from_longitude_latitude_at_depth(type.osgeo,
      new geo_coordinate2d(new longitude(+0.0),
        new latitude(-66.5132)), (short)2);
    assertTrue(new quad_key(type.osgeo, 1, 1, (short)2).equal_to(quadKey));
    quadKey = quad_key.get_key_from_longitude_latitude_at_depth(type.osgeo,
      new geo_coordinate2d(new longitude(+0.0),
        new latitude(+0.1)), (short)2);
    assertTrue(new quad_key(type.osgeo, 2, 1, (short)2).equal_to(quadKey));
    quadKey = quad_key.get_key_from_longitude_latitude_at_depth(type.osgeo,
      new geo_coordinate2d(new longitude(+0.0),
        new latitude(+66.5132)), (short)2);
    assertTrue(new quad_key(type.osgeo, 2, 1, (short)2).equal_to(quadKey));
    quadKey = quad_key.get_key_from_longitude_latitude_at_depth(type.osgeo,
      new geo_coordinate2d(new longitude(+0.0),
        new latitude(+66.5133)), (short)2);
    assertTrue(new quad_key(type.osgeo, 3, 1, (short)2).equal_to(quadKey));
    quadKey = quad_key.get_key_from_longitude_latitude_at_depth(type.osgeo,
      new geo_coordinate2d(new longitude(+0.0),
        new latitude(+85.05113877)), (short)2);
    assertTrue(new quad_key(type.osgeo, 3, 1, (short)2).equal_to(quadKey));
    quadKey = quad_key.get_key_from_longitude_latitude_at_depth(type.osgeo,
      new geo_coordinate2d(new longitude(+0.1),
        new latitude(-85.05113877)), (short)2);
    assertTrue(new quad_key(type.osgeo, 0, 2, (short)2).equal_to(quadKey));
    quadKey = quad_key.get_key_from_longitude_latitude_at_depth(type.osgeo,
      new geo_coordinate2d(new longitude(+0.1),
        new latitude(-66.5133)), (short)2);
    assertTrue(new quad_key(type.osgeo, 0, 2, (short)2).equal_to(quadKey));
    quadKey = quad_key.get_key_from_longitude_latitude_at_depth(type.osgeo,
      new geo_coordinate2d(new longitude(+0.1),
        new latitude(-66.5132)), (short)2);
    assertTrue(new quad_key(type.osgeo, 1, 2, (short)2).equal_to(quadKey));
    quadKey = quad_key.get_key_from_longitude_latitude_at_depth(type.osgeo,
      new geo_coordinate2d(new longitude(+0.1),
        new latitude(+0.1)), (short)2);
    assertTrue(new quad_key(type.osgeo, 2, 2, (short)2).equal_to(quadKey));
    quadKey = quad_key.get_key_from_longitude_latitude_at_depth(type.osgeo,
      new geo_coordinate2d(new longitude(+0.1),
        new latitude(+66.5132)), (short)2);
    assertTrue(new quad_key(type.osgeo, 2, 2, (short)2).equal_to(quadKey));
    quadKey = quad_key.get_key_from_longitude_latitude_at_depth(type.osgeo,
      new geo_coordinate2d(new longitude(+0.1),
        new latitude(+66.5133)), (short)2);
    assertTrue(new quad_key(type.osgeo, 3, 2, (short)2).equal_to(quadKey));
    quadKey = quad_key.get_key_from_longitude_latitude_at_depth(type.osgeo,
      new geo_coordinate2d(new longitude(+0.1),
        new latitude(+85.05113877)), (short)2);
    assertTrue(new quad_key(type.osgeo, 3, 2, (short)2).equal_to(quadKey));
    quadKey = quad_key.get_key_from_longitude_latitude_at_depth(type.osgeo,
      new geo_coordinate2d(new longitude(+90.0),
        new latitude(-85.05113877)), (short)2);
    assertTrue(new quad_key(type.osgeo, 0, 2, (short)2).equal_to(quadKey));
    quadKey = quad_key.get_key_from_longitude_latitude_at_depth(type.osgeo,
      new geo_coordinate2d(new longitude(+90.0),
        new latitude(-66.5133)), (short)2);
    assertTrue(new quad_key(type.osgeo, 0, 2, (short)2).equal_to(quadKey));
    quadKey = quad_key.get_key_from_longitude_latitude_at_depth(type.osgeo,
      new geo_coordinate2d(new longitude(+90.0),
        new latitude(-66.5132)), (short)2);
    assertTrue(new quad_key(type.osgeo, 1, 2, (short)2).equal_to(quadKey));
    quadKey = quad_key.get_key_from_longitude_latitude_at_depth(type.osgeo,
      new geo_coordinate2d(new longitude(+90.0),
        new latitude(+0.1)), (short)2);
    assertTrue(new quad_key(type.osgeo, 2, 2, (short)2).equal_to(quadKey));
    quadKey = quad_key.get_key_from_longitude_latitude_at_depth(type.osgeo,
      new geo_coordinate2d(new longitude(+90.0),
        new latitude(+66.5132)), (short)2);
    assertTrue(new quad_key(type.osgeo, 2, 2, (short)2).equal_to(quadKey));
    quadKey = quad_key.get_key_from_longitude_latitude_at_depth(type.osgeo,
      new geo_coordinate2d(new longitude(+90.0),
        new latitude(+66.5133)), (short)2);
    assertTrue(new quad_key(type.osgeo, 3, 2, (short)2).equal_to(quadKey));
    quadKey = quad_key.get_key_from_longitude_latitude_at_depth(type.osgeo,
      new geo_coordinate2d(new longitude(+90.0),
        new latitude(+85.05113877)), (short)2);
    assertTrue(new quad_key(type.osgeo, 3, 2, (short)2).equal_to(quadKey));
    quadKey = quad_key.get_key_from_longitude_latitude_at_depth(type.osgeo,
      new geo_coordinate2d(new longitude(+90.1),
        new latitude(-85.05113877)), (short)2);
    assertTrue(new quad_key(type.osgeo, 0, 3, (short)2).equal_to(quadKey));
    quadKey = quad_key.get_key_from_longitude_latitude_at_depth(type.osgeo,
      new geo_coordinate2d(new longitude(+90.1),
        new latitude(-66.5133)), (short)2);
    assertTrue(new quad_key(type.osgeo, 0, 3, (short)2).equal_to(quadKey));
    quadKey = quad_key.get_key_from_longitude_latitude_at_depth(type.osgeo,
      new geo_coordinate2d(new longitude(+90.1),
        new latitude(-66.5132)), (short)2);
    assertTrue(new quad_key(type.osgeo, 1, 3, (short)2).equal_to(quadKey));
    quadKey = quad_key.get_key_from_longitude_latitude_at_depth(type.osgeo,
      new geo_coordinate2d(new longitude(+90.1),
        new latitude(+0.1)), (short)2);
    assertTrue(new quad_key(type.osgeo, 2, 3, (short)2).equal_to(quadKey));
    quadKey = quad_key.get_key_from_longitude_latitude_at_depth(type.osgeo,
      new geo_coordinate2d(new longitude(+90.1),
        new latitude(+66.5132)), (short)2);
    assertTrue(new quad_key(type.osgeo, 2, 3, (short)2).equal_to(quadKey));
    quadKey = quad_key.get_key_from_longitude_latitude_at_depth(type.osgeo,
      new geo_coordinate2d(new longitude(+90.1),
        new latitude(+66.5133)), (short)2);
    assertTrue(new quad_key(type.osgeo, 3, 3, (short)2).equal_to(quadKey));
    quadKey = quad_key.get_key_from_longitude_latitude_at_depth(type.osgeo,
      new geo_coordinate2d(new longitude(+90.1),
        new latitude(+85.05113877)), (short)2);
    assertTrue(new quad_key(type.osgeo, 3, 3, (short)2).equal_to(quadKey));
    quadKey = quad_key.get_key_from_longitude_latitude_at_depth(type.osgeo,
      new geo_coordinate2d(new longitude(+180.0),
        new latitude(-85.05113877)), (short)2);
    assertTrue(new quad_key(type.osgeo, 0, 3, (short)2).equal_to(quadKey));
    quadKey = quad_key.get_key_from_longitude_latitude_at_depth(type.osgeo,
      new geo_coordinate2d(new longitude(+180.0),
        new latitude(-66.5133)), (short)2);
    assertTrue(new quad_key(type.osgeo, 0, 3, (short)2).equal_to(quadKey));
    quadKey = quad_key.get_key_from_longitude_latitude_at_depth(type.osgeo,
      new geo_coordinate2d(new longitude(+180.0),
        new latitude(-66.5132)), (short)2);
    assertTrue(new quad_key(type.osgeo, 1, 3, (short)2).equal_to(quadKey));
    quadKey = quad_key.get_key_from_longitude_latitude_at_depth(type.osgeo,
      new geo_coordinate2d(new longitude(+180.0),
        new latitude(+0.1)), (short)2);
    assertTrue(new quad_key(type.osgeo, 2, 3, (short)2).equal_to(quadKey));
    quadKey = quad_key.get_key_from_longitude_latitude_at_depth(type.osgeo,
      new geo_coordinate2d(new longitude(+180.0),
        new latitude(+66.5132)), (short)2);
    assertTrue(new quad_key(type.osgeo, 2, 3, (short)2).equal_to(quadKey));
    quadKey = quad_key.get_key_from_longitude_latitude_at_depth(type.osgeo,
      new geo_coordinate2d(new longitude(+180.0),
        new latitude(+66.5133)), (short)2);
    assertTrue(new quad_key(type.osgeo, 3, 3, (short)2).equal_to(quadKey));
    quadKey = quad_key.get_key_from_longitude_latitude_at_depth(type.osgeo,
      new geo_coordinate2d(new longitude(+180.0),
        new latitude(+85.05113877)), (short)2);
    assertTrue(new quad_key(type.osgeo, 3, 3, (short)2).equal_to(quadKey));
  }

  @Test
  public void get_keys_from_longitude_latitude_bounding_box_test() {
    quad_key_vector quadKeys;

    quadKeys = quad_key.get_keys_from_longitude_latitude_bounding_box(
      type.osgeo, new geo_coordinate_bounding_box2d(
        new geo_coordinate2d(new longitude(+0.0),
          new latitude(-0.10000000)),
        new geo_coordinate2d(new longitude(+0.1),
          new latitude(+0.10000000))), (short)0);
    assertEquals(1, quadKeys.size());
    assertTrue(vectorContains(quadKeys, new quad_key(type.osgeo, 0, 0,
      (short)0)));

    quadKeys = quad_key.get_keys_from_longitude_latitude_bounding_box(
      type.osgeo, new geo_coordinate_bounding_box2d(
        new geo_coordinate2d(new longitude(-180.0),
          new latitude(-85.05113877)),
        new geo_coordinate2d(new longitude(+180.0),
          new latitude(+85.05113877))), (short)1);
    assertEquals(4, quadKeys.size());
    assertTrue(vectorContains(quadKeys, new quad_key(type.osgeo, 0, 0,
      (short)1)));
    assertTrue(vectorContains(quadKeys, new quad_key(type.osgeo, 0, 1,
      (short)1)));
    assertTrue(vectorContains(quadKeys, new quad_key(type.osgeo, 1, 0,
      (short)1)));
    assertTrue(vectorContains(quadKeys, new quad_key(type.osgeo, 1, 1,
      (short)1)));

    quadKeys = quad_key.get_keys_from_longitude_latitude_bounding_box(
      type.osgeo, new geo_coordinate_bounding_box2d(
        new geo_coordinate2d(new longitude(-180.0),
          new latitude(-85.05113877)),
        new geo_coordinate2d(new longitude(+0.0),
          new latitude(+85.05113877))), (short)1);
    assertEquals(2, quadKeys.size());
    assertTrue(vectorContains(quadKeys, new quad_key(type.osgeo, 1, 0,
      (short)1)));
    assertTrue(vectorContains(quadKeys, new quad_key(type.osgeo, 0, 0,
      (short)1)));

    quadKeys = quad_key.get_keys_from_longitude_latitude_bounding_box(
      type.osgeo, new geo_coordinate_bounding_box2d(
        new geo_coordinate2d(new longitude(+0.1),
          new latitude(-85.05113877)),
        new geo_coordinate2d(new longitude(+180.0),
          new latitude(+85.05113877))), (short)1);
    assertEquals(2, quadKeys.size());
    assertTrue(vectorContains(quadKeys, new quad_key(type.osgeo, 1, 1,
      (short)1)));
    assertTrue(vectorContains(quadKeys, new quad_key(type.osgeo, 0, 1,
      (short)1)));

    quadKeys = quad_key.get_keys_from_longitude_latitude_bounding_box(
      type.osgeo, new geo_coordinate_bounding_box2d(
        new geo_coordinate2d(new longitude(-180.0),
          new latitude(-85.05113877)),
        new geo_coordinate2d(new longitude(+0.0),
          new latitude(+0.00000000))), (short)1);
    assertEquals(1, quadKeys.size());
    assertTrue(vectorContains(quadKeys, new quad_key(type.osgeo, 0, 0,
      (short)1)));

    quadKeys = quad_key.get_keys_from_longitude_latitude_bounding_box(
      type.osgeo, new geo_coordinate_bounding_box2d(
        new geo_coordinate2d(new longitude(-180.0),
          new latitude(+0.10000000)),
        new geo_coordinate2d(new longitude(+0.0),
          new latitude(+85.05113877))), (short)1);
    assertEquals(1, quadKeys.size());
    assertTrue(vectorContains(quadKeys, new quad_key(type.osgeo, 1, 0,
      (short)1)));

    quadKeys = quad_key.get_keys_from_longitude_latitude_bounding_box(
      type.osgeo, new geo_coordinate_bounding_box2d(
        new geo_coordinate2d(new longitude(+0.1),
          new latitude(-85.05113877)),
        new geo_coordinate2d(new longitude(+180.0),
          new latitude(+0.00000000))), (short)1);
    assertEquals(1, quadKeys.size());
    assertTrue(vectorContains(quadKeys, new quad_key(type.osgeo, 0, 1,
      (short)1)));

    quadKeys = quad_key.get_keys_from_longitude_latitude_bounding_box(
      type.osgeo, new geo_coordinate_bounding_box2d(
        new geo_coordinate2d(new longitude(+0.1),
          new latitude(+0.10000000)),
        new geo_coordinate2d(new longitude(+180.0),
          new latitude(+85.05113877))), (short)1);
    assertEquals(1, quadKeys.size());
    assertTrue(vectorContains(quadKeys, new quad_key(type.osgeo, 1, 1,
      (short)1)));
  }

  @Test
  public void selected_citites_test() {
    // TODO: Implement Tests. Taken from Earthscape. No tests there.
  }
}

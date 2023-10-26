import static org.junit.Assert.*;

import com.quad_key.quad_key;
import com.quad_key.type;
import com.quad_key.quad_key_vector;
import com.quad_key.geo_coordinate2d;
import com.quad_key.geo_coordinate_bounding_box2d;
import com.quad_key.latitude;
import com.quad_key.longitude;

import org.junit.BeforeClass;
import org.junit.Test;

public class lat_long_system_test {

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
  public void is_valid_test()
  {
    // See Testquad_key TestSpecificCtorTest.
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
    quad_key key;
    geo_coordinate_bounding_box2d bbox = new geo_coordinate_bounding_box2d();

    { // Depth 0
      key = new quad_key(type.lat_long, 0, 0, (short)0);
      key.get_geo_coordinate_bounds2d(bbox);
      assertTrue(new geo_coordinate2d(new longitude(-180.0),
        new latitude(-90.0)).equal_to(bbox.lower_left()));
      assertTrue(new geo_coordinate2d(new longitude(+180.0),
        new latitude(+90.0)).equal_to(bbox.upper_right()));
    }

    { // Depth 1
      key = new quad_key(type.lat_long, 0, 0, (short)1);
      key.get_geo_coordinate_bounds2d(bbox);
      assertTrue(bbox.lower_left().get_longitude().near(
        new longitude(-180.0), 1e-6));
      assertTrue(bbox.lower_left().get_latitude().near(
        new latitude(-90.0), 1e-6));
      assertTrue(bbox.upper_right().get_longitude().near(
        new longitude(+0.0), 1e-6));
      assertTrue(bbox.upper_right().get_latitude().near(
        new latitude(+0.0), 1e-6));

      key = new quad_key(type.lat_long, 0, 1, (short)1);
      key.get_geo_coordinate_bounds2d(bbox);
      assertTrue(bbox.lower_left().get_longitude().near(
        new longitude(+0.0), 1e-6));
      assertTrue(bbox.lower_left().get_latitude().near(
        new latitude(-90.0), 1e-6));
      assertTrue(bbox.upper_right().get_longitude().near(
        new longitude(+180.0), 1e-6));
      assertTrue(bbox.upper_right().get_latitude().near(
        new latitude(+0.0), 1e-6));

      key = new quad_key(type.lat_long, 1, 0, (short)1);
      key.get_geo_coordinate_bounds2d(bbox);
      assertTrue(bbox.lower_left().get_longitude().near(
        new longitude(-180.0), 1e-6));
      assertTrue(bbox.lower_left().get_latitude().near(
        new latitude(+0.0), 1e-6));
      assertTrue(bbox.upper_right().get_longitude().near(
        new longitude(+0.0), 1e-6));
      assertTrue(bbox.upper_right().get_latitude().near(
        new latitude(+90.0), 1e-6));

      key = new quad_key(type.lat_long, 1, 1, (short)1);
      key.get_geo_coordinate_bounds2d(bbox);
      assertTrue(bbox.lower_left().get_longitude().near(
        new longitude(+0.0), 1e-6));
      assertTrue(bbox.lower_left().get_latitude().near(
        new latitude(+0.0), 1e-6));
      assertTrue(bbox.upper_right().get_longitude().near(
        new longitude(+180.0), 1e-6));
      assertTrue(bbox.upper_right().get_latitude().near(
        new latitude(+90.0), 1e-6));
    }
  }

  @Test
  public void get_keys_from_longitude_latitude_at_depth_to_bounds_test()
  {
    quad_key key;

    { // Depth 0
      key = quad_key.get_key_from_longitude_latitude_at_depth(
        type.lat_long, new geo_coordinate2d(
          new longitude(-180.0), new latitude(-90)), (short)0);
      assertTrue(new quad_key(type.lat_long, 0, 0, (short)0).equal_to(key));
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
      key = quad_key.get_key_from_longitude_latitude_at_depth(
        type.lat_long, new geo_coordinate2d(
          new longitude(-180.0), new latitude(-90.0)), (short)1);
      assertTrue(new quad_key(type.lat_long, 0, 0, (short)1).equal_to(key));
      assertEquals("2", key.to_internal_string());
      key = quad_key.get_key_from_longitude_latitude_at_depth(
        type.lat_long, new geo_coordinate2d(
          new longitude(-0.1), new latitude(-90.0)), (short)1);
      assertTrue(new quad_key(type.lat_long, 0, 0, (short)1).equal_to(key));
      assertEquals("2", key.to_internal_string());
      key = quad_key.get_key_from_longitude_latitude_at_depth(
        type.lat_long, new geo_coordinate2d(
          new longitude(-0.1), new latitude(-0.1)), (short)1);
      assertTrue(new quad_key(type.lat_long, 0, 0, (short)1).equal_to(key));
      assertEquals("2", key.to_internal_string());
      key = quad_key.get_key_from_longitude_latitude_at_depth(
        type.lat_long, new geo_coordinate2d(
          new longitude(-180.0), new latitude(-0.1)), (short)1);
      assertTrue(new quad_key(type.lat_long, 0, 0, (short)1).equal_to(key));
      assertEquals("2", key.to_internal_string());

      key = quad_key.get_key_from_longitude_latitude_at_depth(
        type.lat_long, new geo_coordinate2d(
          new longitude(+0.0), new latitude(-90.0)), (short)1);
      assertTrue(new quad_key(type.lat_long, 0, 1, (short)1).equal_to(key));
      assertEquals("3", key.to_internal_string());
      key = quad_key.get_key_from_longitude_latitude_at_depth(
        type.lat_long, new geo_coordinate2d(
          new longitude(+180.0), new latitude(-90.0)), (short)1);
      assertTrue(new quad_key(type.lat_long, 0, 1, (short)1).equal_to(key));
      assertEquals("3", key.to_internal_string());
      key = quad_key.get_key_from_longitude_latitude_at_depth(
        type.lat_long, new geo_coordinate2d(
          new longitude(+180.0), new latitude(-0.1)), (short)1);
      assertTrue(new quad_key(type.lat_long, 0, 1, (short)1).equal_to(key));
      assertEquals("3", key.to_internal_string());
      key = quad_key.get_key_from_longitude_latitude_at_depth(
        type.lat_long, new geo_coordinate2d(
          new longitude(+0.0), new latitude(-0.1)), (short)1);
      assertTrue(new quad_key(type.lat_long, 0, 1, (short)1).equal_to(key));
      assertEquals("3", key.to_internal_string());

      key = quad_key.get_key_from_longitude_latitude_at_depth(
        type.lat_long, new geo_coordinate2d(
          new longitude(-180.0), new latitude(+0.0)), (short)1);
      assertTrue(new quad_key(type.lat_long, 1, 0, (short)1).equal_to(key));
      assertEquals("0", key.to_internal_string());
      key = quad_key.get_key_from_longitude_latitude_at_depth(
        type.lat_long, new geo_coordinate2d(
          new longitude(-0.1), new latitude(+0.0)), (short)1);
      assertTrue(new quad_key(type.lat_long, 1, 0, (short)1).equal_to(key));
      assertEquals("0", key.to_internal_string());
      key = quad_key.get_key_from_longitude_latitude_at_depth(
        type.lat_long, new geo_coordinate2d(
          new longitude(-180.0), new latitude(+90.0)), (short)1);
      assertTrue(new quad_key(type.lat_long, 1, 0, (short)1).equal_to(key));
      assertEquals("0", key.to_internal_string());
      key = quad_key.get_key_from_longitude_latitude_at_depth(
        type.lat_long, new geo_coordinate2d(
          new longitude(-0.1), new latitude(+90.0)), (short)1);
      assertTrue(new quad_key(type.lat_long, 1, 0, (short)1).equal_to(key));
      assertEquals("0", key.to_internal_string());

      key = quad_key.get_key_from_longitude_latitude_at_depth(
        type.lat_long, new geo_coordinate2d(
          new longitude(+0.0), new latitude(+0.0)), (short)1);
      assertTrue(new quad_key(type.lat_long, 1, 1, (short)1).equal_to(key));
      assertEquals("1", key.to_internal_string());
      key = quad_key.get_key_from_longitude_latitude_at_depth(
        type.lat_long, new geo_coordinate2d(
          new longitude(+180.0), new latitude(+0.0)), (short)1);
      assertTrue(new quad_key(type.lat_long, 1, 1, (short)1).equal_to(key));
      assertEquals("1", key.to_internal_string());
      key = quad_key.get_key_from_longitude_latitude_at_depth(
        type.lat_long, new geo_coordinate2d(
          new longitude(+0.0), new latitude(+90.0)), (short)1);
      assertTrue(new quad_key(type.lat_long, 1, 1, (short)1).equal_to(key));
      assertEquals("1", key.to_internal_string());
      key = quad_key.get_key_from_longitude_latitude_at_depth(
        type.lat_long, new geo_coordinate2d(
          new longitude(+180.0), new latitude(+90.0)), (short)1);
      assertTrue(new quad_key(type.lat_long, 1, 1, (short)1).equal_to(key));
      assertEquals("1", key.to_internal_string());
    }
  }

  @Test
  public void get_keys_from_longitude_latitude_bounding_box_test() {
    {
      quad_key_vector outKeys;
      outKeys = quad_key.get_keys_from_longitude_latitude_bounding_box(
        type.lat_long,
        new geo_coordinate_bounding_box2d(
          new geo_coordinate2d(new longitude(-180.0), new latitude(+90.0)),
          new geo_coordinate2d(new longitude(+180.0), new latitude(-90.0))),
        (short)0);
      assertEquals((short)1, outKeys.size());
      assertTrue(vectorContains(outKeys, new quad_key(type.lat_long, 0, 0,
        (short)0)));
    }

    {
      quad_key_vector outKeys;
      outKeys = quad_key.get_keys_from_longitude_latitude_bounding_box(
        type.lat_long,
        new geo_coordinate_bounding_box2d(
          new geo_coordinate2d(new longitude(-180.0), new latitude(+90.0)),
          new geo_coordinate2d(new longitude(+180.0), new latitude(-90.0))),
        (short)1);
      assertEquals((short)4, outKeys.size());
      assertTrue(vectorContains(outKeys, new quad_key(type.lat_long, 0, 0,
        (short)1)));
      assertTrue(vectorContains(outKeys, new quad_key(type.lat_long, 0, 1,
        (short)1)));
      assertTrue(vectorContains(outKeys, new quad_key(type.lat_long, 1, 0,
        (short)1)));
      assertTrue(vectorContains(outKeys, new quad_key(type.lat_long, 1, 1,
        (short)1)));
    }

    {
      quad_key_vector outKeys;
      outKeys = quad_key.get_keys_from_longitude_latitude_bounding_box(
        type.lat_long,
        new geo_coordinate_bounding_box2d(
          new geo_coordinate2d(new longitude(-180.0), new latitude(-0.1)),
          new geo_coordinate2d(new longitude(-0.1), new latitude(+90.0))),
        (short)1);
      assertEquals(2, outKeys.size());
      assertTrue(vectorContains(outKeys, new quad_key(type.lat_long, 0, 0,
        (short)1)));
      assertTrue(vectorContains(outKeys, new quad_key(type.lat_long, 1, 0,
        (short)1)));
    }

    {
      quad_key_vector outKeys;
      outKeys = quad_key.get_keys_from_longitude_latitude_bounding_box(
        type.lat_long,
        new geo_coordinate_bounding_box2d(
          new geo_coordinate2d(new longitude(+0.0), new latitude(-0.1)),
          new geo_coordinate2d(new longitude(+180.0), new latitude(+90.0))),
        (short)1);
      assertEquals(2, outKeys.size());
      assertTrue(vectorContains(outKeys, new quad_key(type.lat_long, 0, 1,
        (short)1)));
      assertTrue(vectorContains(outKeys, new quad_key(type.lat_long, 1, 1,
        (short)1)));
    }

    {
      quad_key_vector outKeys;
      outKeys = quad_key.get_keys_from_longitude_latitude_bounding_box(
        type.lat_long,
        new geo_coordinate_bounding_box2d(
          new geo_coordinate2d(new longitude(-0.1), new latitude(-0.1)),
          new geo_coordinate2d(new longitude(+0.1), new latitude(+0.1))),
        (short)1);
      assertEquals(4, outKeys.size());
      assertTrue(vectorContains(outKeys, new quad_key(type.lat_long, 0, 0,
        (short)1)));
      assertTrue(vectorContains(outKeys, new quad_key(type.lat_long, 0, 1,
        (short)1)));
      assertTrue(vectorContains(outKeys, new quad_key(type.lat_long, 1, 0,
        (short)1)));
      assertTrue(vectorContains(outKeys, new quad_key(type.lat_long, 1, 1,
        (short)1)));
    }
  }

  @Test
  public void known_sample_of_locations_test()
  {
    quad_key key;

    {
      key = quad_key.get_key_from_longitude_latitude_at_depth(
        type.lat_long, new geo_coordinate2d(new longitude(-122.4183),
          new latitude(37.7750)), (short)1);
      assertEquals("0", key.to_internal_string());
      key = quad_key.get_key_from_longitude_latitude_at_depth(
        type.lat_long, new geo_coordinate2d(new longitude(-122.4183),
          new latitude(37.7750)), (short)2);
      assertEquals("02", key.to_internal_string());
      key = quad_key.get_key_from_longitude_latitude_at_depth(
        type.lat_long, new geo_coordinate2d(new longitude(-122.4183),
          new latitude(37.7750)), (short)3);
      assertEquals("021", key.to_internal_string());
      key = quad_key.get_key_from_longitude_latitude_at_depth(
        type.lat_long, new geo_coordinate2d(new longitude(-122.4183),
          new latitude(37.7750)), (short)4);
      assertEquals("0210", key.to_internal_string());
    }

    {
      key = quad_key.get_key_from_longitude_latitude_at_depth(
        type.lat_long, new geo_coordinate2d(new longitude(+134.9),
          new latitude(-67.6)), (short)3);
      assertTrue(new quad_key(type.lat_long, 0, 6, (short)3).equal_to(key));
      assertEquals("332", key.to_internal_string());

      key = quad_key.get_key_from_longitude_latitude_at_depth(
        type.lat_long, new geo_coordinate2d(new longitude(+135.0),
          new latitude(-67.5)), (short)3);
      assertTrue(new quad_key(type.lat_long, 1, 7, (short)3).equal_to(key));
      assertEquals("331", key.to_internal_string());
    }
  }
}

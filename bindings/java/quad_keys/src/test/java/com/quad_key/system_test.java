import com.quad_key.*;
import org.junit.BeforeClass;
import org.junit.Test;

import java.util.ArrayList;
import java.util.List;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertTrue;

public class system_test {

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
  public void getChildTest() {
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
  }

  @Test
  public void get_geo_coordinate_bounds2d_test() {
  }

  @Test
  public void get_key_from_longitude_latitude_at_depth_to_bounds_test() {
  }

  @Test
  public void getKeysFromLongitudeLatitudeBoundingBoxTest() {
  }

  @Test
  public void selecetedCitiesTest() {
  }
}

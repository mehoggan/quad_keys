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

public class bing_system_test {

  private boolean vectorContains(quad_key_vector vector, quad_key key) {
    boolean found = false;
    for (int i = 0; i < vector.size(); ++i) {
      quad_key curr = vector.get(i);
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
  public void isValid_test() {
    // See quad_keyTest.systemSpecificCtorTest
  }

  @Test
  public void isRootKey_test() {
    // See quad_keyTest.isValidTest
  }

  @Test
  public void get_parent_test() {
    {
      quad_key key0 = new quad_key(type.bing, 0, 0, (short)1);
      quad_key key1 = new quad_key(type.bing, 1, 0, (short)1);
      quad_key key2 = new quad_key(type.bing, 1, 1, (short)1);
      quad_key key3 = new quad_key(type.bing, 0, 1, (short)1);

      quad_key parent = new quad_key(type.bing, 0, 0, (short)0);

      assertEquals(type.bing, key0.get_type());
      assertEquals(type.bing, key1.get_type());
      assertEquals(type.bing, key2.get_type());
      assertEquals(type.bing, key3.get_type());
      assertEquals(type.bing, parent.get_type());

      assertTrue(key0.get_parent().equal_to(parent));
      assertTrue(key1.get_parent().equal_to(parent));
      assertTrue(key2.get_parent().equal_to(parent));
      assertTrue(key3.get_parent().equal_to(parent));
    }

    {
      quad_key key0 = new quad_key(type.bing, 5, 6, (short)3);
      quad_key key1 = new quad_key(type.bing, 4, 6, (short)3);
      quad_key key2 = new quad_key(type.bing, 4, 7, (short)3);
      quad_key key3 = new quad_key(type.bing, 5, 7, (short)3);

      quad_key parent = new quad_key(type.bing, 2, 3, (short)2);

      assertEquals(type.bing, key0.get_type());
      assertEquals(type.bing, key1.get_type());
      assertEquals(type.bing, key2.get_type());
      assertEquals(type.bing, key3.get_type());
      assertEquals(type.bing, parent.get_type());

      assertTrue(key0.get_parent().equal_to(parent));
      assertTrue(key1.get_parent().equal_to(parent));
      assertTrue(key2.get_parent().equal_to(parent));
      assertTrue(key3.get_parent().equal_to(parent));
    }
  }

  @Test
  public void is_my_ancestor_test() {
    {
      quad_key key = new quad_key(type.bing, 5, 7, (short)3);
      assertFalse(key.is_my_ancestor(new quad_key()));
      assertFalse(key.is_my_ancestor(new quad_key(type.osgeo, 2, 3,
        (short)2)));
      assertFalse(key.is_my_ancestor(new quad_key(type.osgeo, 0, 0,
        (short)0)));
      assertFalse(key.is_my_ancestor(new quad_key(type.bing, 5, 7,
        (short)3)));
      assertTrue(key.is_my_ancestor(new quad_key(type.bing, 2, 3,
        (short)2)));
      assertTrue(key.is_my_ancestor(new quad_key(type.bing, 0, 0,
        (short)0)));

      quad_key none = new quad_key();
      assertFalse(none.is_my_ancestor(new quad_key()));
    }

    {
      quad_key key = new quad_key(type.bing, 5, 7, (short)3);
      assertFalse(key.is_my_ancestor(new quad_key()));
      assertFalse(key.is_my_ancestor(new quad_key(type.osgeo, 2, 3,
        (short)2)));
      assertFalse(key.is_my_ancestor(new quad_key(type.osgeo, 0, 0,
        (short)0)));
      assertFalse(key.is_my_ancestor(new quad_key(type.bing, 5, 7,
        (short)3)));
      assertTrue(key.is_my_ancestor(new quad_key(type.bing, 2, 3,
        (short)2)));
      assertTrue(key.is_my_ancestor(new quad_key(type.bing, 0, 0,
        (short)0)));

      quad_key none = new quad_key();
      assertFalse(none.is_my_ancestor(new quad_key()));
    }
  }

  @Test
  public void get_ancestor_test() {
    {
      quad_key key = new quad_key(type.bing, 0, 7, (short)3);
      quad_key ancestor = new quad_key(type.bing, 0, 1, (short)1);
      assertTrue(ancestor.equal_to(key.get_ancestor((short)2)));
    }

    {
      quad_key key = new quad_key(type.bing, 4, 31, (short)5);
      quad_key ancestor = new quad_key(type.bing, 0, 1, (short)1);
      assertTrue(ancestor.equal_to(key.get_ancestor((short)4)));
    }

    {
      quad_key key = new quad_key(type.bing, 4, 31, (short)5);
      quad_key ancestor = new quad_key(type.bing, 0, 3, (short)2);
      assertTrue(ancestor.equal_to(key.get_ancestor((short)3)));
    }

    {
      quad_key key = new quad_key(type.bing, 4, 31, (short)5);
      quad_key ancestor = new quad_key(type.bing, 1, 7, (short)3);
      assertTrue(ancestor.equal_to(key.get_ancestor((short)2)));
    }
  }

  @Test
  public void get_child_test() {
    assertTrue(new quad_key().equal_to(
      new quad_key().get_child(quad_key.quadrant.north_west)));
    short max_depthbing = quad_key.max_depth(type.bing);
    assertTrue(new quad_key().equal_to(
      new quad_key(type.bing, 0, 0, max_depthbing).get_child(
        quad_key.quadrant.north_east)));

    {
      quad_key key = new quad_key(type.bing, 0, 0, (short)3);
      assertTrue(new quad_key(type.bing, 1, 0, (short)4).equal_to(
        key.get_child(quad_key.quadrant.north_west)));
      assertTrue(new quad_key(type.bing, 1, 1, (short)4).equal_to(
        key.get_child(quad_key.quadrant.north_east)));
      assertTrue(new quad_key(type.bing, 0, 1, (short)4).equal_to(
        key.get_child(quad_key.quadrant.south_west)));
      assertTrue(new quad_key(type.bing, 0, 0, (short)4).equal_to(
        key.get_child(quad_key.quadrant.south_west)));
    }

    {
      quad_key key = new quad_key(type.bing, 2, 3, (short)3);
      assertTrue(new quad_key(type.bing, 5, 6, (short)4).equal_to(
        key.get_child(quad_key.quadrant.north_west)));
      assertTrue(new quad_key(type.bing, 5, 7, (short)4).equal_to(
        key.get_child(quad_key.quadrant.north_east)));
      assertTrue(new quad_key(type.bing, 4, 7, (short)4).equal_to(
        key.get_child(quad_key.quadrant.south_west)));
      assertTrue(new quad_key(type.bing, 4, 6, (short)4).equal_to(
        key.get_child(quad_key.quadrant.south_west)));
    }
  }

  @Test
  public void test_get_childern() {
    quad_key_vector testKeys;
    short max_depthbing = quad_key.max_depth(type.bing);
    testKeys = new quad_key(type.bing, 0, 0, max_depthbing).get_children();
    assertEquals(0, testKeys.size());

    testKeys.clear();

    quad_key key0 = new quad_key(type.bing, 0, 0, (short)1);
    testKeys = key0.get_children();
    assertEquals(4, testKeys.size());
    assertTrue(vectorContains(testKeys, new quad_key(type.bing, 0, 0,
      (short)2)));
    assertTrue(vectorContains(testKeys, new quad_key(type.bing, 0, 1,
      (short)2)));
    assertTrue(vectorContains(testKeys, new quad_key(type.bing, 1, 0,
      (short)2)));
    assertTrue(vectorContains(testKeys, new quad_key(type.bing, 1, 1,
      (short)2)));

    quad_key key1 = new quad_key(type.bing, 0, 1, (short)1);
    testKeys = key1.get_children();
    assertEquals(4, testKeys.size());
    assertTrue(vectorContains(testKeys, new quad_key(type.bing, 0, 2,
      (short)2)));
    assertTrue(vectorContains(testKeys, new quad_key(type.bing, 0, 3,
      (short)2)));
    assertTrue(vectorContains(testKeys, new quad_key(type.bing, 1, 2,
      (short)2)));
    assertTrue(vectorContains(testKeys, new quad_key(type.bing, 1, 3,
      (short)2)));

    quad_key key2 = new quad_key(type.bing, 1, 0, (short)1);
    testKeys = key2.get_children();
    assertEquals(4, testKeys.size());
    assertTrue(vectorContains(testKeys, new quad_key(type.bing, 2, 0,
      (short)2)));
    assertTrue(vectorContains(testKeys, new quad_key(type.bing, 2, 1,
      (short)2)));
    assertTrue(vectorContains(testKeys, new quad_key(type.bing, 3, 0,
      (short)2)));
    assertTrue(vectorContains(testKeys, new quad_key(type.bing, 3, 1,
      (short)2)));

    quad_key key3 = new quad_key(type.bing, 1, 1, (short)1);
    testKeys = key3.get_children();
    assertEquals(4, testKeys.size());
    assertTrue(vectorContains(testKeys, new quad_key(type.bing, 2, 2,
      (short)2)));
    assertTrue(vectorContains(testKeys, new quad_key(type.bing, 2, 3,
      (short)2)));
    assertTrue(vectorContains(testKeys, new quad_key(type.bing, 3, 2,
      (short)2)));
    assertTrue(vectorContains(testKeys, new quad_key(type.bing, 3, 3,
      (short)2)));
  }

  @Test
  public void get_descendants_test() {
    short bingMaxDepth = quad_key.max_depth(type.bing);
    short requetedDepth = (short)(bingMaxDepth - 3);
    quad_key key = new quad_key(type.bing, 0, 0, requetedDepth);
    quad_key_vector testKeys;

    /* We are going beyond the max depth */
    testKeys = key.get_descendants((short)4);
    assertEquals(0, testKeys.size());

    quad_key none = new quad_key();
    testKeys = none.get_descendants((short)1);
    assertEquals(0, testKeys.size());

    {
      quad_key bingKey = new quad_key(type.bing, 0, 0, (short)0);
      testKeys = bingKey.get_descendants((short)0);
      assertEquals(0, testKeys.size());
    }

    {
      quad_key bingKey = new quad_key(type.bing, 0, 0, (short)0);
      testKeys = bingKey.get_descendants((short)1);
      assertEquals(4, testKeys.size());
      assertTrue(vectorContains(testKeys, new quad_key(type.bing, 0, 0,
        (short)1)));
      assertTrue(vectorContains(testKeys, new quad_key(type.bing, 0, 1,
        (short)1)));
      assertTrue(vectorContains(testKeys, new quad_key(type.bing, 1, 0,
        (short)1)));
      assertTrue(vectorContains(testKeys, new quad_key(type.bing, 1, 1,
        (short)1)));
      testKeys.clear();

      testKeys = bingKey.get_descendants((short)2);
      assertEquals(16, testKeys.size());
      assertTrue(vectorContains(testKeys, new quad_key(type.bing, 0, 0,
        (short)2)));
      assertTrue(vectorContains(testKeys, new quad_key(type.bing, 0, 1,
        (short)2)));
      assertTrue(vectorContains(testKeys, new quad_key(type.bing, 0, 2,
        (short)2)));
      assertTrue(vectorContains(testKeys, new quad_key(type.bing, 0, 3,
        (short)2)));
      assertTrue(vectorContains(testKeys, new quad_key(type.bing, 1, 0,
        (short)2)));
      assertTrue(vectorContains(testKeys, new quad_key(type.bing, 1, 1,
        (short)2)));
      assertTrue(vectorContains(testKeys, new quad_key(type.bing, 1, 2,
        (short)2)));
      assertTrue(vectorContains(testKeys, new quad_key(type.bing, 1, 3,
        (short)2)));
      assertTrue(vectorContains(testKeys, new quad_key(type.bing, 2, 0,
        (short)2)));
      assertTrue(vectorContains(testKeys, new quad_key(type.bing, 2, 1,
        (short)2)));
      assertTrue(vectorContains(testKeys, new quad_key(type.bing, 2, 2,
        (short)2)));
      assertTrue(vectorContains(testKeys, new quad_key(type.bing, 2, 3,
        (short)2)));
      assertTrue(vectorContains(testKeys, new quad_key(type.bing, 3, 0,
        (short)2)));
      assertTrue(vectorContains(testKeys, new quad_key(type.bing, 3, 1,
        (short)2)));
      assertTrue(vectorContains(testKeys, new quad_key(type.bing, 3, 2,
        (short)2)));
      assertTrue(vectorContains(testKeys, new quad_key(type.bing, 3, 3,
        (short)2)));
      testKeys.clear();

      testKeys = bingKey.get_descendants((short)3);
      assertEquals(64, testKeys.size());
      assertTrue(vectorContains(testKeys, new quad_key(type.bing, 0, 0,
        (short)3)));
      assertTrue(vectorContains(testKeys, new quad_key(type.bing, 0, 1,
        (short)3)));
      assertTrue(vectorContains(testKeys, new quad_key(type.bing, 0, 2,
        (short)3)));
      assertTrue(vectorContains(testKeys, new quad_key(type.bing, 0, 3,
        (short)3)));
      assertTrue(vectorContains(testKeys, new quad_key(type.bing, 0, 4,
        (short)3)));
      assertTrue(vectorContains(testKeys, new quad_key(type.bing, 0, 5,
        (short)3)));
      assertTrue(vectorContains(testKeys, new quad_key(type.bing, 0, 6,
        (short)3)));
      assertTrue(vectorContains(testKeys, new quad_key(type.bing, 0, 7,
        (short)3)));
      assertTrue(vectorContains(testKeys, new quad_key(type.bing, 1, 0,
        (short)3)));
      assertTrue(vectorContains(testKeys, new quad_key(type.bing, 1, 1,
        (short)3)));
      assertTrue(vectorContains(testKeys, new quad_key(type.bing, 1, 2,
        (short)3)));
      assertTrue(vectorContains(testKeys, new quad_key(type.bing, 1, 3,
        (short)3)));
      assertTrue(vectorContains(testKeys, new quad_key(type.bing, 1, 4,
        (short)3)));
      assertTrue(vectorContains(testKeys, new quad_key(type.bing, 1, 5,
        (short)3)));
      assertTrue(vectorContains(testKeys, new quad_key(type.bing, 1, 6,
        (short)3)));
      assertTrue(vectorContains(testKeys, new quad_key(type.bing, 1, 7,
        (short)3)));
      assertTrue(vectorContains(testKeys, new quad_key(type.bing, 2, 0,
        (short)3)));
      assertTrue(vectorContains(testKeys, new quad_key(type.bing, 2, 1,
        (short)3)));
      assertTrue(vectorContains(testKeys, new quad_key(type.bing, 2, 2,
        (short)3)));
      assertTrue(vectorContains(testKeys, new quad_key(type.bing, 2, 3,
        (short)3)));
      assertTrue(vectorContains(testKeys, new quad_key(type.bing, 2, 4,
        (short)3)));
      assertTrue(vectorContains(testKeys, new quad_key(type.bing, 2, 5,
        (short)3)));
      assertTrue(vectorContains(testKeys, new quad_key(type.bing, 2, 6,
        (short)3)));
      assertTrue(vectorContains(testKeys, new quad_key(type.bing, 2, 7,
        (short)3)));
      assertTrue(vectorContains(testKeys, new quad_key(type.bing, 3, 0,
        (short)3)));
      assertTrue(vectorContains(testKeys, new quad_key(type.bing, 3, 1,
        (short)3)));
      assertTrue(vectorContains(testKeys, new quad_key(type.bing, 3, 2,
        (short)3)));
      assertTrue(vectorContains(testKeys, new quad_key(type.bing, 3, 3,
        (short)3)));
      assertTrue(vectorContains(testKeys, new quad_key(type.bing, 3, 4,
        (short)3)));
      assertTrue(vectorContains(testKeys, new quad_key(type.bing, 3, 5,
        (short)3)));
      assertTrue(vectorContains(testKeys, new quad_key(type.bing, 3, 6,
        (short)3)));
      assertTrue(vectorContains(testKeys, new quad_key(type.bing, 3, 7,
        (short)3)));
      assertTrue(vectorContains(testKeys, new quad_key(type.bing, 4, 0,
        (short)3)));
      assertTrue(vectorContains(testKeys, new quad_key(type.bing, 4, 1,
        (short)3)));
      assertTrue(vectorContains(testKeys, new quad_key(type.bing, 4, 2,
        (short)3)));
      assertTrue(vectorContains(testKeys, new quad_key(type.bing, 4, 3,
        (short)3)));
      assertTrue(vectorContains(testKeys, new quad_key(type.bing, 4, 4,
        (short)3)));
      assertTrue(vectorContains(testKeys, new quad_key(type.bing, 4, 5,
        (short)3)));
      assertTrue(vectorContains(testKeys, new quad_key(type.bing, 4, 6,
        (short)3)));
      assertTrue(vectorContains(testKeys, new quad_key(type.bing, 4, 7,
        (short)3)));
      assertTrue(vectorContains(testKeys, new quad_key(type.bing, 5, 0,
        (short)3)));
      assertTrue(vectorContains(testKeys, new quad_key(type.bing, 5, 1,
        (short)3)));
      assertTrue(vectorContains(testKeys, new quad_key(type.bing, 5, 2,
        (short)3)));
      assertTrue(vectorContains(testKeys, new quad_key(type.bing, 5, 3,
        (short)3)));
      assertTrue(vectorContains(testKeys, new quad_key(type.bing, 5, 4,
        (short)3)));
      assertTrue(vectorContains(testKeys, new quad_key(type.bing, 5, 5,
        (short)3)));
      assertTrue(vectorContains(testKeys, new quad_key(type.bing, 5, 6,
        (short)3)));
      assertTrue(vectorContains(testKeys, new quad_key(type.bing, 5, 7,
        (short)3)));
      assertTrue(vectorContains(testKeys, new quad_key(type.bing, 6, 0,
        (short)3)));
      assertTrue(vectorContains(testKeys, new quad_key(type.bing, 6, 1,
        (short)3)));
      assertTrue(vectorContains(testKeys, new quad_key(type.bing, 6, 2,
        (short)3)));
      assertTrue(vectorContains(testKeys, new quad_key(type.bing, 6, 3,
        (short)3)));
      assertTrue(vectorContains(testKeys, new quad_key(type.bing, 6, 4,
        (short)3)));
      assertTrue(vectorContains(testKeys, new quad_key(type.bing, 6, 5,
        (short)3)));
      assertTrue(vectorContains(testKeys, new quad_key(type.bing, 6, 6,
        (short)3)));
      assertTrue(vectorContains(testKeys, new quad_key(type.bing, 6, 7,
        (short)3)));
      assertTrue(vectorContains(testKeys, new quad_key(type.bing, 7, 0,
        (short)3)));
      assertTrue(vectorContains(testKeys, new quad_key(type.bing, 7, 1,
        (short)3)));
      assertTrue(vectorContains(testKeys, new quad_key(type.bing, 7, 2,
        (short)3)));
      assertTrue(vectorContains(testKeys, new quad_key(type.bing, 7, 3,
        (short)3)));
      assertTrue(vectorContains(testKeys, new quad_key(type.bing, 7, 4,
        (short)3)));
      assertTrue(vectorContains(testKeys, new quad_key(type.bing, 7, 5,
        (short)3)));
      assertTrue(vectorContains(testKeys, new quad_key(type.bing, 7, 6,
        (short)3)));
      assertTrue(vectorContains(testKeys, new quad_key(type.bing, 7, 7,
        (short)3)));
      testKeys.clear();
    }
  }

  @Test
  public void get_siblings_test() {
    quad_key_vector testKeys;

    quad_key none = new quad_key();
    testKeys = none.get_siblings();
    assertEquals(0, testKeys.size());

    quad_key root = new quad_key(type.bing, 0, 0, (short)0);
    testKeys = root.get_siblings();
    assertEquals(0, testKeys.size());

    quad_key bingKey = new quad_key(type.bing, 0, 0, (short)1);
    testKeys = bingKey.get_siblings();
    assertEquals(3, testKeys.size());
    assertTrue(vectorContains(testKeys, new quad_key(type.bing, 0, 1,
      (short)1)));
    assertTrue(vectorContains(testKeys, new quad_key(type.bing, 1, 1,
      (short)1)));
    assertTrue(vectorContains(testKeys, new quad_key(type.bing, 1, 0,
      (short)1)));
  }

  @Test
  public void get_neighbors_test() {
    quad_key_vector testKeys;

    quad_key none = new quad_key();
    testKeys = none.get_neighbors();
    assertEquals(0, testKeys.size());

    quad_key root = new quad_key(type.bing, 0, 0, (short)0);
    testKeys = root.get_neighbors();
    assertEquals(0, testKeys.size());

    testKeys.clear();

    quad_key key0 = new quad_key(type.bing, 0, 0, (short)2);
    testKeys = key0.get_neighbors();
    assertEquals(5, testKeys.size());
    assertTrue(vectorContains(testKeys, new quad_key(type.bing, 0, 1,
      (short)2)));
    assertTrue(vectorContains(testKeys, new quad_key(type.bing, 1, 1,
      (short)2)));
    assertTrue(vectorContains(testKeys, new quad_key(type.bing, 1, 0,
      (short)2)));
    assertTrue(vectorContains(testKeys, new quad_key(type.bing, 0, 3,
      (short)2)));
    assertTrue(vectorContains(testKeys, new quad_key(type.bing, 1, 3,
      (short)2)));

    testKeys.clear();

    quad_key key;

    key = new quad_key(type.bing, 0, 1, (short)2);
    testKeys = key.get_neighbors();
    assertEquals(5, testKeys.size());
    assertTrue(vectorContains(testKeys, new quad_key(type.bing, 0, 0,
      (short)2)));
    assertTrue(vectorContains(testKeys, new quad_key(type.bing, 1, 0,
      (short)2)));
    assertTrue(vectorContains(testKeys, new quad_key(type.bing, 1, 1,
      (short)2)));
    assertTrue(vectorContains(testKeys, new quad_key(type.bing, 1, 2,
      (short)2)));
    assertTrue(vectorContains(testKeys, new quad_key(type.bing, 0, 2,
      (short)2)));

    testKeys.clear();

    key = new quad_key(type.bing, 0, 2, (short)2);
    testKeys = key.get_neighbors();
    assertEquals(5, testKeys.size());
    assertTrue(vectorContains(testKeys, new quad_key(type.bing, 0, 1,
      (short)2)));
    assertTrue(vectorContains(testKeys, new quad_key(type.bing, 1, 1,
      (short)2)));
    assertTrue(vectorContains(testKeys, new quad_key(type.bing, 1, 2,
      (short)2)));
    assertTrue(vectorContains(testKeys, new quad_key(type.bing, 1, 3,
      (short)2)));
    assertTrue(vectorContains(testKeys, new quad_key(type.bing, 0, 3,
      (short)2)));

    testKeys.clear();

    key = new quad_key(type.bing, 0, 3, (short)2);
    testKeys = key.get_neighbors();
    assertEquals(5, testKeys.size());
    assertTrue(vectorContains(testKeys, new quad_key(type.bing, 0, 2,
      (short)2)));
    assertTrue(vectorContains(testKeys, new quad_key(type.bing, 1, 2,
      (short)2)));
    assertTrue(vectorContains(testKeys, new quad_key(type.bing, 1, 3,
      (short)2)));
    assertTrue(vectorContains(testKeys, new quad_key(type.bing, 1, 0,
      (short)2)));
    assertTrue(vectorContains(testKeys, new quad_key(type.bing, 0, 0,
      (short)2)));

    testKeys.clear();

    key = new quad_key(type.bing, 1, 0, (short)2);
    testKeys = key.get_neighbors();
    assertEquals(8, testKeys.size());
    assertTrue(vectorContains(testKeys, new quad_key(type.bing, 0, 0,
      (short)2)));
    assertTrue(vectorContains(testKeys, new quad_key(type.bing, 0, 1,
      (short)2)));
    assertTrue(vectorContains(testKeys, new quad_key(type.bing, 1, 1,
      (short)2)));
    assertTrue(vectorContains(testKeys, new quad_key(type.bing, 2, 1,
      (short)2)));
    assertTrue(vectorContains(testKeys, new quad_key(type.bing, 2, 0,
      (short)2)));
    assertTrue(vectorContains(testKeys, new quad_key(type.bing, 2, 3,
      (short)2)));
    assertTrue(vectorContains(testKeys, new quad_key(type.bing, 1, 3,
      (short)2)));
    assertTrue(vectorContains(testKeys, new quad_key(type.bing, 0, 3,
      (short)2)));

    testKeys.clear();

    key = new quad_key(type.bing, 1, 1, (short)2);
    testKeys = key.get_neighbors();
    assertEquals(8, testKeys.size());
    assertTrue(vectorContains(testKeys, new quad_key(type.bing, 1, 0,
      (short)2)));
    assertTrue(vectorContains(testKeys, new quad_key(type.bing, 0, 0,
      (short)2)));
    assertTrue(vectorContains(testKeys, new quad_key(type.bing, 0, 1,
      (short)2)));
    assertTrue(vectorContains(testKeys, new quad_key(type.bing, 2, 2,
      (short)2)));
    assertTrue(vectorContains(testKeys, new quad_key(type.bing, 2, 1,
      (short)2)));
    assertTrue(vectorContains(testKeys, new quad_key(type.bing, 2, 0,
      (short)2)));
    assertTrue(vectorContains(testKeys, new quad_key(type.bing, 0, 2,
      (short)2)));
    assertTrue(vectorContains(testKeys, new quad_key(type.bing, 1, 2,
      (short)2)));

    testKeys.clear();

    key = new quad_key(type.bing, 1, 2, (short)2);
    testKeys = key.get_neighbors();
    assertEquals(8, testKeys.size());
    assertTrue(vectorContains(testKeys, new quad_key(type.bing, 1, 1,
      (short)2)));
    assertTrue(vectorContains(testKeys, new quad_key(type.bing, 0, 1,
      (short)2)));
    assertTrue(vectorContains(testKeys, new quad_key(type.bing, 0, 2,
      (short)2)));
    assertTrue(vectorContains(testKeys, new quad_key(type.bing, 2, 3,
      (short)2)));
    assertTrue(vectorContains(testKeys, new quad_key(type.bing, 2, 2,
      (short)2)));
    assertTrue(vectorContains(testKeys, new quad_key(type.bing, 2, 1,
      (short)2)));
    assertTrue(vectorContains(testKeys, new quad_key(type.bing, 0, 3,
      (short)2)));
    assertTrue(vectorContains(testKeys, new quad_key(type.bing, 1, 3,
      (short)2)));

    testKeys.clear();

    key = new quad_key(type.bing, 1, 3, (short)2);
    testKeys = key.get_neighbors();
    assertEquals(8, testKeys.size());
    assertTrue(vectorContains(testKeys, new quad_key(type.bing, 1, 2,
      (short)2)));
    assertTrue(vectorContains(testKeys, new quad_key(type.bing, 0, 2,
      (short)2)));
    assertTrue(vectorContains(testKeys, new quad_key(type.bing, 0, 3,
      (short)2)));
    assertTrue(vectorContains(testKeys, new quad_key(type.bing, 2, 0,
      (short)2)));
    assertTrue(vectorContains(testKeys, new quad_key(type.bing, 2, 3,
      (short)2)));
    assertTrue(vectorContains(testKeys, new quad_key(type.bing, 2, 2,
      (short)2)));
    assertTrue(vectorContains(testKeys, new quad_key(type.bing, 0, 0,
      (short)2)));
    assertTrue(vectorContains(testKeys, new quad_key(type.bing, 1, 0,
      (short)2)));

    testKeys.clear();

    key = new quad_key(type.bing, 4, 7, (short)3);
    testKeys = key.get_neighbors();
    assertEquals(8, testKeys.size());
    assertTrue(vectorContains(testKeys, new quad_key(type.bing, 3, 7,
      (short)3)));
    assertTrue(vectorContains(testKeys, new quad_key(type.bing, 3, 6,
      (short)3)));
    assertTrue(vectorContains(testKeys, new quad_key(type.bing, 4, 6,
      (short)3)));
    assertTrue(vectorContains(testKeys, new quad_key(type.bing, 5, 6,
      (short)3)));
    assertTrue(vectorContains(testKeys, new quad_key(type.bing, 5, 7,
      (short)3)));
    assertTrue(vectorContains(testKeys, new quad_key(type.bing, 5, 0,
      (short)3)));
    assertTrue(vectorContains(testKeys, new quad_key(type.bing, 4, 0,
      (short)3)));
    assertTrue(vectorContains(testKeys, new quad_key(type.bing, 3, 0,
      (short)3)));

    testKeys.clear();

    key = new quad_key(type.bing, 4, 0, (short)3);
    testKeys = key.get_neighbors();
    assertEquals(8, testKeys.size());
    assertTrue(vectorContains(testKeys, new quad_key(type.bing, 3, 0,
      (short)3)));
    assertTrue(vectorContains(testKeys, new quad_key(type.bing, 3, 1,
      (short)3)));
    assertTrue(vectorContains(testKeys, new quad_key(type.bing, 4, 1,
      (short)3)));
    assertTrue(vectorContains(testKeys, new quad_key(type.bing, 5, 1,
      (short)3)));
    assertTrue(vectorContains(testKeys, new quad_key(type.bing, 5, 0,
      (short)3)));
    assertTrue(vectorContains(testKeys, new quad_key(type.bing, 5, 7,
      (short)3)));
    assertTrue(vectorContains(testKeys, new quad_key(type.bing, 4, 7,
      (short)3)));
    assertTrue(vectorContains(testKeys, new quad_key(type.bing, 3, 7,
      (short)3)));

    testKeys.clear();
  }

  @Test
  public void from_internal_string_to_string_test() {
    {
      quad_key root = quad_key.from_internal_string(type.bing, "");
      assertEquals(0, root.get_row());
      assertEquals(0, root.get_col());
      assertEquals(0, root.get_depth());
    }

    {
      quad_key key;
      key = quad_key.from_internal_string(type.bing, "0");
      assertEquals(1, key.get_row());
      assertEquals(0, key.get_col());
      assertEquals(1, key.get_depth());
      assertEquals("0", key.to_internal_string());
      key = quad_key.from_internal_string(type.bing, "1");
      assertEquals(1, key.get_row());
      assertEquals(1, key.get_col());
      assertEquals(1, key.get_depth());
      assertEquals("1", key.to_internal_string());
      key = quad_key.from_internal_string(type.bing, "2");
      assertEquals(0, key.get_row());
      assertEquals(0, key.get_col());
      assertEquals(1, key.get_depth());
      assertEquals("2", key.to_internal_string());
      key = quad_key.from_internal_string(type.bing, "3");
      assertEquals(0, key.get_row());
      assertEquals(1, key.get_col());
      assertEquals(1, key.get_depth());
      assertEquals("3", key.to_internal_string());
    }

    {
      quad_key key;
      key = quad_key.from_internal_string(type.bing, "00");
      assertEquals(3, key.get_row());
      assertEquals(0, key.get_col());
      assertEquals(2, key.get_depth());
      assertEquals("00", key.to_internal_string());
      key = quad_key.from_internal_string(type.bing, "01");
      assertEquals(3, key.get_row());
      assertEquals(1, key.get_col());
      assertEquals(2, key.get_depth());
      assertEquals("01", key.to_internal_string());
      key = quad_key.from_internal_string(type.bing, "02");
      assertEquals(2, key.get_row());
      assertEquals(0, key.get_col());
      assertEquals(2, key.get_depth());
      assertEquals("02", key.to_internal_string());
      key = quad_key.from_internal_string(type.bing, "03");
      assertEquals(2, key.get_row());
      assertEquals(1, key.get_col());
      assertEquals(2, key.get_depth());
      assertEquals("03", key.to_internal_string());
      key = quad_key.from_internal_string(type.bing, "10");
      assertEquals(3, key.get_row());
      assertEquals(2, key.get_col());
      assertEquals(2, key.get_depth());
      assertEquals("10", key.to_internal_string());
      key = quad_key.from_internal_string(type.bing, "11");
      assertEquals(3, key.get_row());
      assertEquals(3, key.get_col());
      assertEquals(2, key.get_depth());
      assertEquals("11", key.to_internal_string());
      key = quad_key.from_internal_string(type.bing, "12");
      assertEquals(2, key.get_row());
      assertEquals(2, key.get_col());
      assertEquals(2, key.get_depth());
      assertEquals("12", key.to_internal_string());
      key = quad_key.from_internal_string(type.bing, "13");
      assertEquals(2, key.get_row());
      assertEquals(3, key.get_col());
      assertEquals(2, key.get_depth());
      assertEquals("13", key.to_internal_string());
      key = quad_key.from_internal_string(type.bing, "20");
      assertEquals(1, key.get_row());
      assertEquals(0, key.get_col());
      assertEquals(2, key.get_depth());
      assertEquals("20", key.to_internal_string());
      key = quad_key.from_internal_string(type.bing, "21");
      assertEquals(1, key.get_row());
      assertEquals(1, key.get_col());
      assertEquals(2, key.get_depth());
      assertEquals("21", key.to_internal_string());
      key = quad_key.from_internal_string(type.bing, "22");
      assertEquals(0, key.get_row());
      assertEquals(0, key.get_col());
      assertEquals(2, key.get_depth());
      assertEquals("22", key.to_internal_string());
      key = quad_key.from_internal_string(type.bing, "23");
      assertEquals(0, key.get_row());
      assertEquals(1, key.get_col());
      assertEquals(2, key.get_depth());
      assertEquals("23", key.to_internal_string());
      key = quad_key.from_internal_string(type.bing, "30");
      assertEquals(1, key.get_row());
      assertEquals(2, key.get_col());
      assertEquals(2, key.get_depth());
      assertEquals("30", key.to_internal_string());
      key = quad_key.from_internal_string(type.bing, "31");
      assertEquals(1, key.get_row());
      assertEquals(3, key.get_col());
      assertEquals(2, key.get_depth());
      assertEquals("31", key.to_internal_string());
      key = quad_key.from_internal_string(type.bing, "32");
      assertEquals(0, key.get_row());
      assertEquals(2, key.get_col());
      assertEquals(2, key.get_depth());
      assertEquals("32", key.to_internal_string());
      key = quad_key.from_internal_string(type.bing, "33");
      assertEquals(0, key.get_row());
      assertEquals(3, key.get_col());
      assertEquals(2, key.get_depth());
      assertEquals("33", key.to_internal_string());
    }
  }

  @Test
  public void get_geo_coordinate_bounds2d_test() {
    quad_key key;
    geo_coordinate_bounding_box2d bbox = new geo_coordinate_bounding_box2d();

    key = quad_key.from_internal_string(type.bing, "");
    key.get_geo_coordinate_bounds2d(bbox);
    assertEquals(-180.0, bbox.lower_left().get_longitude().val(), 1e-7);
    assertEquals(-84.9283209, bbox.lower_left().get_latitude().val(), 1e-7);
    assertEquals(178.593750, bbox.upper_right().get_longitude().val(), 1e-7);
    assertEquals(85.05112877, bbox.upper_right().get_latitude().val(), 1e-7);
  }

  @Test
  public void get_key_from_longitude_latitude_at_depthToBounds_test() {
    quad_key key;
    geo_coordinate_bounding_box2d bbox = new geo_coordinate_bounding_box2d();
    double diff;

    { // Depth 0
      key = quad_key.get_key_from_longitude_latitude_at_depth(
        type.bing, new geo_coordinate2d(new longitude(-180.0),
        new latitude(-84.0)), (short)0);
      assertTrue(new quad_key(type.bing, 0, 0, (short)0).equal_to(key));
      key.get_geo_coordinate_bounds2d(bbox);
      diff = Math.abs(bbox.lower_left().get_longitude().longitude_difference(
        new longitude(-180.0)));
      assertTrue(2.0 > diff);
      diff = Math.abs(bbox.lower_left().get_latitude().latitude_difference(
        new latitude(-85.0)));
      assertTrue(2.0 > diff);
      diff = Math.abs(
        bbox.upper_right().get_longitude().longitude_difference(
          new longitude(+180.0)));
      assertTrue(2.0 > diff);
      diff = Math.abs(bbox.upper_right().get_latitude().latitude_difference(
        new latitude(+85.0)));
      assertTrue(2.0 > diff);
    }

    // Inclusion here consists of upper left
    // ul X------X------X
    //    |      |      |
    //    |      |      |
    //    X------X------X
    //    |      |      |
    //    |      |      |
    //    X------X------X
    longitude left = new longitude(-180.0);
    longitude midLeft = new longitude(-0.36);
    longitude midRight = new longitude(0.0);
    longitude right = new longitude(+180.0);
    latitude bottom = new latitude(-90.0);
    latitude midBottom = new latitude(0.0);
    latitude midTop = new latitude(0.36);
    latitude top = new latitude(+90.0);

    { // Depth 1
      key = quad_key.get_key_from_longitude_latitude_at_depth( // Q0 ul
        type.bing, new geo_coordinate2d(left, top), (short)1);
      assertTrue(new quad_key(type.bing, 1, 0, (short)1).equal_to(key));
      key = quad_key.get_key_from_longitude_latitude_at_depth( // Q0 ll
        type.bing, new geo_coordinate2d(left, midTop), (short)1);
      assertTrue(new quad_key(type.bing, 1, 0, (short)1).equal_to(key));
      key = quad_key.get_key_from_longitude_latitude_at_depth( // Q0 lr
        type.bing, new geo_coordinate2d(midLeft, midTop), (short)1);
      assertTrue(new quad_key(type.bing, 1, 0, (short)1).equal_to(key));
      key = quad_key.get_key_from_longitude_latitude_at_depth( // Q0 ur
        type.bing, new geo_coordinate2d(midLeft, top), (short)1);
      assertTrue(new quad_key(type.bing, 1, 0, (short)1).equal_to(key));
      key.get_geo_coordinate_bounds2d(bbox);
      diff = Math.abs(bbox.lower_left().get_longitude().longitude_difference(
        left));
      assertTrue(2.0 > diff);
      diff = Math.abs(bbox.lower_left().get_latitude().latitude_difference(
        midTop));
      assertTrue(2.0 > diff);
      diff =
        Math.abs(bbox.upper_right().get_longitude().longitude_difference(
          midLeft));
      assertTrue(2.0 > diff);
      diff = Math.abs(bbox.upper_right().get_latitude().latitude_difference(
        new latitude(+85.0)));
      assertTrue(2.0 > diff);

      key = quad_key.get_key_from_longitude_latitude_at_depth( // Q1 ul
        type.bing, new geo_coordinate2d(midRight, top), (short)1);
      assertTrue(new quad_key(type.bing, 1, 1, (short)1).equal_to(key));
      key = quad_key.get_key_from_longitude_latitude_at_depth( // Q1 ll
        type.bing, new geo_coordinate2d(midRight, midTop), (short)1);
      assertTrue(new quad_key(type.bing, 1, 1, (short)1).equal_to(key));
      key = quad_key.get_key_from_longitude_latitude_at_depth( // Q1 lr
        type.bing, new geo_coordinate2d(right, midTop), (short)1);
      assertTrue(new quad_key(type.bing, 1, 1, (short)1).equal_to(key));
      key = quad_key.get_key_from_longitude_latitude_at_depth( // Q1 ur
        type.bing, new geo_coordinate2d(right, top), (short)1);
      assertTrue(new quad_key(type.bing, 1, 1, (short)1).equal_to(key));
      key.get_geo_coordinate_bounds2d(bbox);
      diff = Math.abs(bbox.lower_left().get_longitude().longitude_difference(
        midRight));
      assertTrue(2.0 > diff);
      diff = Math.abs(bbox.lower_left().get_latitude().latitude_difference(
        midTop));
      assertTrue(2.0 > diff);
      diff =
        Math.abs(bbox.upper_right().get_longitude().longitude_difference(
          right));
      assertTrue(2.0 > diff);
      diff = Math.abs(bbox.upper_right().get_latitude().latitude_difference(
        new latitude(+85.0)));
      assertTrue(2.0 > diff);

      key = quad_key.get_key_from_longitude_latitude_at_depth( // Q2 ul
        type.bing, new geo_coordinate2d(left, midBottom), (short)1);
      assertTrue(new quad_key(type.bing, 0, 0, (short)1).equal_to(key));
      key = quad_key.get_key_from_longitude_latitude_at_depth( // Q2 ll
        type.bing, new geo_coordinate2d(left, bottom), (short)1);
      assertTrue(new quad_key(type.bing, 0, 0, (short)1).equal_to(key));
      key = quad_key.get_key_from_longitude_latitude_at_depth( // Q2 lr
        type.bing, new geo_coordinate2d(midLeft, bottom), (short)1);
      assertTrue(new quad_key(type.bing, 0, 0, (short)1).equal_to(key));
      key = quad_key.get_key_from_longitude_latitude_at_depth( // Q2 ur
        type.bing, new geo_coordinate2d(midLeft, midBottom), (short)1);
      assertTrue(new quad_key(type.bing, 0, 0, (short)1).equal_to(key));
      key.get_geo_coordinate_bounds2d(bbox);
      diff = Math.abs(bbox.lower_left().get_longitude().longitude_difference(
        left));
      assertTrue(2.0 > diff);
      diff = Math.abs(bbox.lower_left().get_latitude().latitude_difference(
        new latitude(-85.0)));
      assertTrue(2.0 > diff);
      diff =
        Math.abs(bbox.upper_right().get_longitude().longitude_difference(
          midLeft));
      assertTrue(2.0 > diff);
      diff = Math.abs(bbox.upper_right().get_latitude().latitude_difference(
        midBottom));
      assertTrue(2.0 > diff);

      key = quad_key.get_key_from_longitude_latitude_at_depth( // Q3 ul
        type.bing, new geo_coordinate2d(midRight, midBottom), (short)1);
      assertTrue(new quad_key(type.bing, 0, 1, (short)1).equal_to(key));
      key = quad_key.get_key_from_longitude_latitude_at_depth( // Q3 ll
        type.bing, new geo_coordinate2d(midRight, bottom), (short)1);
      assertTrue(new quad_key(type.bing, 0, 1, (short)1).equal_to(key));
      key = quad_key.get_key_from_longitude_latitude_at_depth( // Q3 lr
        type.bing, new geo_coordinate2d(right, bottom), (short)1);
      assertTrue(new quad_key(type.bing, 0, 1, (short)1).equal_to(key));
      key = quad_key.get_key_from_longitude_latitude_at_depth( // Q3 ur
        type.bing, new geo_coordinate2d(right, midBottom), (short)1);
      assertTrue(new quad_key(type.bing, 0, 1, (short)1).equal_to(key));
      key.get_geo_coordinate_bounds2d(bbox);
      diff = Math.abs(bbox.lower_left().get_longitude().longitude_difference(
        midRight));
      assertTrue(2.0 > diff);
      diff = Math.abs(bbox.lower_left().get_latitude().latitude_difference(
        new latitude(-85.0)));
      assertTrue(2.0 > diff);
      diff =
        Math.abs(bbox.upper_right().get_longitude().longitude_difference(
          right));
      assertTrue(2.0 > diff);
      diff = Math.abs(bbox.upper_right().get_latitude().latitude_difference(
        midBottom));
      assertTrue(2.0 > diff);
    }
  }

  @Test
  public void get_keys_from_longitude_latitude_bounding_box() {
    {
      quad_key_vector outKeys;
      outKeys = quad_key.get_keys_from_longitude_latitude_bounding_box(
        type.bing,
        new geo_coordinate_bounding_box2d(
          new geo_coordinate2d(
            new longitude(-180.0), new latitude(+90.0)),
          new geo_coordinate2d(
            new longitude(+180.0), new latitude(-90.0))), (short)0);
      assertEquals(1, outKeys.size());
      assertTrue(vectorContains(outKeys, new quad_key(type.bing, 0, 0,
        (short)0)));
    }

    {
      quad_key_vector outKeys;
      outKeys = quad_key.get_keys_from_longitude_latitude_bounding_box(
        type.bing,
        new geo_coordinate_bounding_box2d(
          new geo_coordinate2d(
            new longitude(-180.0), new latitude(+90.0)),
          new geo_coordinate2d(
            new longitude(+180.0), new latitude(-90.0))),
        (short)1);
      assertEquals(4, outKeys.size());
      assertTrue(vectorContains(outKeys, new quad_key(type.bing, 0, 0,
        (short)1)));
      assertTrue(vectorContains(outKeys, new quad_key(type.bing, 0, 1,
        (short)1)));
      assertTrue(vectorContains(outKeys, new quad_key(type.bing, 1, 0,
        (short)1)));
      assertTrue(vectorContains(outKeys, new quad_key(type.bing, 1, 1,
        (short)1)));
    }

    {
      quad_key_vector outKeys;
      outKeys = quad_key.get_keys_from_longitude_latitude_bounding_box(
        type.bing,
        new geo_coordinate_bounding_box2d(
          new geo_coordinate2d(
            new longitude(-180.0), new latitude(+0.35)),
          new geo_coordinate2d(
            new longitude(-0.36), new latitude(+90.0))), (short)1);
      assertEquals(2, outKeys.size());
      assertTrue(vectorContains(outKeys, new quad_key(type.bing, 0, 0,
        (short)1)));
      assertTrue(vectorContains(outKeys, new quad_key(type.bing, 1, 0,
        (short)1)));
    }

    {
      quad_key_vector outKeys;
      outKeys = quad_key.get_keys_from_longitude_latitude_bounding_box(
        type.bing,
        new geo_coordinate_bounding_box2d(
          new geo_coordinate2d(
            new longitude(-0.36), new latitude(+0.36)),
          new geo_coordinate2d(
            new longitude(+0.36), new latitude(+90.0))), (short)1);
      assertEquals(2, outKeys.size());
      assertTrue(vectorContains(outKeys, new quad_key(type.bing, 1, 0,
        (short)1)));
      assertTrue(vectorContains(outKeys, new quad_key(type.bing, 1, 1,
        (short)1)));
    }

    {
      quad_key_vector outKeys;
      outKeys = quad_key.get_keys_from_longitude_latitude_bounding_box(
        type.bing,
        new geo_coordinate_bounding_box2d(
          new geo_coordinate2d(
            new longitude(-0.36), new latitude(+0.35)),
          new geo_coordinate2d(
            new longitude(+0.36), new latitude(+90.0))), (short)1);
      assertEquals(4, outKeys.size());
      assertTrue(vectorContains(outKeys, new quad_key(type.bing, 0, 0,
        (short)1)));
      assertTrue(vectorContains(outKeys, new quad_key(type.bing, 0, 1,
        (short)1)));
      assertTrue(vectorContains(outKeys, new quad_key(type.bing, 1, 0,
        (short)1)));
      assertTrue(vectorContains(outKeys, new quad_key(type.bing, 1, 1,
        (short)1)));
    }
  }

  @Test
  public void selected_cities_test() {
    quad_key key;
    type t = type.bing;

    { // Chicago 41.822, -87.635
      short depth = 16;
      geo_coordinate2d coords = new geo_coordinate2d(
        new longitude(-87.635), new latitude(41.822));

      key = quad_key.get_key_from_longitude_latitude_at_depth(t, coords,
        depth);
      String keyStr = key.to_internal_string();
      assertEquals("0302222310321132", keyStr);

      geo_coordinate_bounding_box2d bbox =
        new geo_coordinate_bounding_box2d();
      key.get_geo_coordinate_bounds2d(bbox);

      // Note that bing will return a bounding box of all sides inclusive
      quad_key_vector keys;
      keys =quad_key.get_keys_from_longitude_latitude_bounding_box(t, bbox,
        depth);
      assertEquals(4, keys.size());
      assertTrue(vectorContains(keys, key));
    }

    { // Rio -43.1964,-22.9083
      short depth = 17;
      geo_coordinate2d coords = new geo_coordinate2d(
              new longitude(-43.1964), new latitude(-22.9083));

      key = quad_key.get_key_from_longitude_latitude_at_depth(t, coords,
        depth);
      String keyStr = key.to_internal_string();
      assertEquals("21120001212232200", keyStr);

      geo_coordinate_bounding_box2d bbox =
        new geo_coordinate_bounding_box2d();
      key.get_geo_coordinate_bounds2d(bbox);

      // Note that bing will return a bounding box of all sides inclusive
      quad_key_vector keys;
      keys = quad_key.get_keys_from_longitude_latitude_bounding_box(t,
        bbox, depth);
      assertEquals(4, keys.size());
      assertTrue(vectorContains(keys, key));
    }

    { // Helsinki 60.1708 N, 24.9375 E
      short depth = 17;
      geo_coordinate2d coords = new geo_coordinate2d(
        new longitude(24.9375), new latitude(60.1708));

      key = quad_key.get_key_from_longitude_latitude_at_depth(t, coords,
        depth);
      String keyStr = key.to_internal_string();
      assertEquals("12012021101330131", keyStr);

      geo_coordinate_bounding_box2d bbox =
        new geo_coordinate_bounding_box2d();
      key.get_geo_coordinate_bounds2d(bbox);

      // Note that bing will return a bounding box of all sides inclusive
      quad_key_vector keys;
      keys = quad_key.get_keys_from_longitude_latitude_bounding_box(t,
        bbox, depth);
      assertEquals(4, keys.size());
      assertTrue(vectorContains(keys, key));
    }

    { // Cape Town South Africa 33.9253 S, 18.4239 E
      short depth = 17;
      geo_coordinate2d coords = new geo_coordinate2d(
        new longitude(18.4239), new latitude(-33.9253));

      key = quad_key.get_key_from_longitude_latitude_at_depth(t, coords,
        depth);
      String keyStr = key.to_internal_string();
      assertEquals("30023103202132011", keyStr);

      geo_coordinate_bounding_box2d bbox =
        new geo_coordinate_bounding_box2d();
      key.get_geo_coordinate_bounds2d(bbox);

      // Note that bing will return a bounding box of all sides inclusive
      quad_key_vector keys;
      keys = quad_key.get_keys_from_longitude_latitude_bounding_box(t,
        bbox, depth);
      assertEquals(4, keys.size());
      assertTrue(vectorContains(keys, key));
    }

    { // Quito 0.2500 S, 78.5833 W
      short depth = 17;
      geo_coordinate2d coords = new geo_coordinate2d(
        new longitude(-78.5836), new latitude(-0.25));

      key = quad_key.get_key_from_longitude_latitude_at_depth(t, coords,
        depth);
      String keyStr = key.to_internal_string();
      assertEquals("21001000002133122", keyStr);

      geo_coordinate_bounding_box2d bbox =
        new geo_coordinate_bounding_box2d();
      key.get_geo_coordinate_bounds2d(bbox);

      // Note that bing will return a bounding box of all sides inclusive
      quad_key_vector keys;
      keys = quad_key.get_keys_from_longitude_latitude_bounding_box(t,
        bbox, depth);
      assertEquals(4, keys.size());
      assertTrue(vectorContains(keys, key));
    }
  }
}

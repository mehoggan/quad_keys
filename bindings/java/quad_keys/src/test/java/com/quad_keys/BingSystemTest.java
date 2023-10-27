package com.quad_keys;

import static org.junit.Assert.*;

import org.junit.BeforeClass;
import org.junit.Test;

public class BingSystemTest {

  private boolean vectorContains(QuadKeysVector vector, QuadKey key) {
    boolean found = false;
    for (QuadKey curr : vector) {
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
  public void isValid_test() {
    // See QuadKeyTest.systemSpecificCtorTest
  }

  @Test
  public void isRootKey_test() {
    // See QuadKeyTest.isValidTest
  }

  @Test
  public void get_parent_test() {
    {
      QuadKey key0 = new QuadKey(Type.Bing, 0, 0, (short)1);
      QuadKey key1 = new QuadKey(Type.Bing, 1, 0, (short)1);
      QuadKey key2 = new QuadKey(Type.Bing, 1, 1, (short)1);
      QuadKey key3 = new QuadKey(Type.Bing, 0, 1, (short)1);

      QuadKey parent = new QuadKey(Type.Bing, 0, 0, (short)0);

      assertEquals(Type.Bing, key0.get_type());
      assertEquals(Type.Bing, key1.get_type());
      assertEquals(Type.Bing, key2.get_type());
      assertEquals(Type.Bing, key3.get_type());
      assertEquals(Type.Bing, parent.get_type());

      assertTrue(key0.get_parent().equalTo(parent));
      assertTrue(key1.get_parent().equalTo(parent));
      assertTrue(key2.get_parent().equalTo(parent));
      assertTrue(key3.get_parent().equalTo(parent));
    }

    {
      QuadKey key0 = new QuadKey(Type.Bing, 5, 6, (short)3);
      QuadKey key1 = new QuadKey(Type.Bing, 4, 6, (short)3);
      QuadKey key2 = new QuadKey(Type.Bing, 4, 7, (short)3);
      QuadKey key3 = new QuadKey(Type.Bing, 5, 7, (short)3);

      QuadKey parent = new QuadKey(Type.Bing, 2, 3, (short)2);

      assertEquals(Type.Bing, key0.get_type());
      assertEquals(Type.Bing, key1.get_type());
      assertEquals(Type.Bing, key2.get_type());
      assertEquals(Type.Bing, key3.get_type());
      assertEquals(Type.Bing, parent.get_type());

      assertTrue(key0.get_parent().equalTo(parent));
      assertTrue(key1.get_parent().equalTo(parent));
      assertTrue(key2.get_parent().equalTo(parent));
      assertTrue(key3.get_parent().equalTo(parent));
    }
  }

  @Test
  public void is_my_ancestor_test() {
    {
      QuadKey key = new QuadKey(Type.Bing, 5, 7, (short)3);
      assertFalse(key.is_my_ancestor(new QuadKey()));
      assertFalse(key.is_my_ancestor(new QuadKey(Type.OsGeo, 2, 3,
        (short)2)));
      assertFalse(key.is_my_ancestor(new QuadKey(Type.OsGeo, 0, 0,
        (short)0)));
      assertFalse(key.is_my_ancestor(new QuadKey(Type.Bing, 5, 7,
        (short)3)));
      assertTrue(key.is_my_ancestor(new QuadKey(Type.Bing, 2, 3,
        (short)2)));
      assertTrue(key.is_my_ancestor(new QuadKey(Type.Bing, 0, 0,
        (short)0)));

      QuadKey none = new QuadKey();
      assertFalse(none.is_my_ancestor(new QuadKey()));
    }

    {
      QuadKey key = new QuadKey(Type.Bing, 5, 7, (short)3);
      assertFalse(key.is_my_ancestor(new QuadKey()));
      assertFalse(key.is_my_ancestor(new QuadKey(Type.OsGeo, 2, 3,
        (short)2)));
      assertFalse(key.is_my_ancestor(new QuadKey(Type.OsGeo, 0, 0,
        (short)0)));
      assertFalse(key.is_my_ancestor(new QuadKey(Type.Bing, 5, 7,
        (short)3)));
      assertTrue(key.is_my_ancestor(new QuadKey(Type.Bing, 2, 3,
        (short)2)));
      assertTrue(key.is_my_ancestor(new QuadKey(Type.Bing, 0, 0,
        (short)0)));

      QuadKey none = new QuadKey();
      assertFalse(none.is_my_ancestor(new QuadKey()));
    }
  }

  @Test
  public void get_ancestor_test() {
    {
      QuadKey key = new QuadKey(Type.Bing, 0, 7, (short)3);
      QuadKey ancestor = new QuadKey(Type.Bing, 0, 1, (short)1);
      assertTrue(ancestor.equalTo(key.get_ancestor((short)2)));
    }

    {
      QuadKey key = new QuadKey(Type.Bing, 4, 31, (short)5);
      QuadKey ancestor = new QuadKey(Type.Bing, 0, 1, (short)1);
      assertTrue(ancestor.equalTo(key.get_ancestor((short)4)));
    }

    {
      QuadKey key = new QuadKey(Type.Bing, 4, 31, (short)5);
      QuadKey ancestor = new QuadKey(Type.Bing, 0, 3, (short)2);
      assertTrue(ancestor.equalTo(key.get_ancestor((short)3)));
    }

    {
      QuadKey key = new QuadKey(Type.Bing, 4, 31, (short)5);
      QuadKey ancestor = new QuadKey(Type.Bing, 1, 7, (short)3);
      assertTrue(ancestor.equalTo(key.get_ancestor((short)2)));
    }
  }

  @Test
  public void get_child_test() {
    assertTrue(new QuadKey().equalTo(
      new QuadKey().get_child(QuadKey.quadrant.north_west)));
    short max_depthbing = QuadKey.max_depth(Type.Bing);
    assertTrue(new QuadKey().equalTo(
      new QuadKey(Type.Bing, 0, 0, max_depthbing).get_child(
        QuadKey.quadrant.north_east)));

    {
      QuadKey key = new QuadKey(Type.Bing, 0, 0, (short)3);
      assertTrue(new QuadKey(Type.Bing, 1, 0, (short)4).equalTo(
        key.get_child(QuadKey.quadrant.north_west)));
      assertTrue(new QuadKey(Type.Bing, 1, 1, (short)4).equalTo(
        key.get_child(QuadKey.quadrant.north_east)));
      assertTrue(new QuadKey(Type.Bing, 0, 1, (short)4).equalTo(
        key.get_child(QuadKey.quadrant.south_east)));
      assertTrue(new QuadKey(Type.Bing, 0, 0, (short)4).equalTo(
        key.get_child(QuadKey.quadrant.south_west)));
    }

    {
      QuadKey key = new QuadKey(Type.Bing, 2, 3, (short)3);
      assertTrue(new QuadKey(Type.Bing, 5, 6, (short)4).equalTo(
        key.get_child(QuadKey.quadrant.north_west)));
      assertTrue(new QuadKey(Type.Bing, 5, 7, (short)4).equalTo(
        key.get_child(QuadKey.quadrant.north_east)));
      assertTrue(new QuadKey(Type.Bing, 4, 7, (short)4).equalTo(
        key.get_child(QuadKey.quadrant.south_east)));
      assertTrue(new QuadKey(Type.Bing, 4, 6, (short)4).equalTo(
        key.get_child(QuadKey.quadrant.south_west)));
    }
  }

  @Test
  public void test_get_childern() {
    QuadKeysVector testKeys;
    short max_depthbing = QuadKey.max_depth(Type.Bing);
    testKeys = new QuadKey(Type.Bing, 0, 0, max_depthbing).get_children();
    assertEquals(0, testKeys.size());

    testKeys.clear();

    QuadKey key0 = new QuadKey(Type.Bing, 0, 0, (short)1);
    testKeys = key0.get_children();
    assertEquals(4, testKeys.size());
    assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 0, 0,
      (short)2)));
    assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 0, 1,
      (short)2)));
    assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 1, 0,
      (short)2)));
    assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 1, 1,
      (short)2)));

    QuadKey key1 = new QuadKey(Type.Bing, 0, 1, (short)1);
    testKeys = key1.get_children();
    assertEquals(4, testKeys.size());
    assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 0, 2,
      (short)2)));
    assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 0, 3,
      (short)2)));
    assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 1, 2,
      (short)2)));
    assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 1, 3,
      (short)2)));

    QuadKey key2 = new QuadKey(Type.Bing, 1, 0, (short)1);
    testKeys = key2.get_children();
    assertEquals(4, testKeys.size());
    assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 2, 0,
      (short)2)));
    assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 2, 1,
      (short)2)));
    assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 3, 0,
      (short)2)));
    assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 3, 1,
      (short)2)));

    QuadKey key3 = new QuadKey(Type.Bing, 1, 1, (short)1);
    testKeys = key3.get_children();
    assertEquals(4, testKeys.size());
    assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 2, 2,
      (short)2)));
    assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 2, 3,
      (short)2)));
    assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 3, 2,
      (short)2)));
    assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 3, 3,
      (short)2)));
  }

  @Test
  public void get_descendants_test() {
    short bingMaxDepth = QuadKey.max_depth(Type.Bing);
    short requetedDepth = (short)(bingMaxDepth - 3);
    QuadKey key = new QuadKey(Type.Bing, 0, 0, requetedDepth);
    QuadKeysVector testKeys;

    /* We are going beyond the max depth */
    testKeys = key.get_descendants((short)4);
    assertEquals(0, testKeys.size());

    QuadKey none = new QuadKey();
    testKeys = none.get_descendants((short)1);
    assertEquals(0, testKeys.size());

    {
      QuadKey bingKey = new QuadKey(Type.Bing, 0, 0, (short)0);
      testKeys = bingKey.get_descendants((short)0);
      assertEquals(0, testKeys.size());
    }

    {
      QuadKey bingKey = new QuadKey(Type.Bing, 0, 0, (short)0);
      testKeys = bingKey.get_descendants((short)1);
      assertEquals(4, testKeys.size());
      assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 0, 0,
        (short)1)));
      assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 0, 1,
        (short)1)));
      assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 1, 0,
        (short)1)));
      assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 1, 1,
        (short)1)));
      testKeys.clear();

      testKeys = bingKey.get_descendants((short)2);
      assertEquals(16, testKeys.size());
      assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 0, 0,
        (short)2)));
      assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 0, 1,
        (short)2)));
      assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 0, 2,
        (short)2)));
      assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 0, 3,
        (short)2)));
      assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 1, 0,
        (short)2)));
      assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 1, 1,
        (short)2)));
      assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 1, 2,
        (short)2)));
      assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 1, 3,
        (short)2)));
      assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 2, 0,
        (short)2)));
      assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 2, 1,
        (short)2)));
      assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 2, 2,
        (short)2)));
      assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 2, 3,
        (short)2)));
      assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 3, 0,
        (short)2)));
      assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 3, 1,
        (short)2)));
      assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 3, 2,
        (short)2)));
      assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 3, 3,
        (short)2)));
      testKeys.clear();

      testKeys = bingKey.get_descendants((short)3);
      assertEquals(64, testKeys.size());
      assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 0, 0,
        (short)3)));
      assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 0, 1,
        (short)3)));
      assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 0, 2,
        (short)3)));
      assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 0, 3,
        (short)3)));
      assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 0, 4,
        (short)3)));
      assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 0, 5,
        (short)3)));
      assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 0, 6,
        (short)3)));
      assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 0, 7,
        (short)3)));
      assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 1, 0,
        (short)3)));
      assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 1, 1,
        (short)3)));
      assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 1, 2,
        (short)3)));
      assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 1, 3,
        (short)3)));
      assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 1, 4,
        (short)3)));
      assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 1, 5,
        (short)3)));
      assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 1, 6,
        (short)3)));
      assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 1, 7,
        (short)3)));
      assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 2, 0,
        (short)3)));
      assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 2, 1,
        (short)3)));
      assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 2, 2,
        (short)3)));
      assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 2, 3,
        (short)3)));
      assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 2, 4,
        (short)3)));
      assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 2, 5,
        (short)3)));
      assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 2, 6,
        (short)3)));
      assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 2, 7,
        (short)3)));
      assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 3, 0,
        (short)3)));
      assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 3, 1,
        (short)3)));
      assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 3, 2,
        (short)3)));
      assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 3, 3,
        (short)3)));
      assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 3, 4,
        (short)3)));
      assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 3, 5,
        (short)3)));
      assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 3, 6,
        (short)3)));
      assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 3, 7,
        (short)3)));
      assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 4, 0,
        (short)3)));
      assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 4, 1,
        (short)3)));
      assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 4, 2,
        (short)3)));
      assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 4, 3,
        (short)3)));
      assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 4, 4,
        (short)3)));
      assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 4, 5,
        (short)3)));
      assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 4, 6,
        (short)3)));
      assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 4, 7,
        (short)3)));
      assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 5, 0,
        (short)3)));
      assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 5, 1,
        (short)3)));
      assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 5, 2,
        (short)3)));
      assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 5, 3,
        (short)3)));
      assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 5, 4,
        (short)3)));
      assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 5, 5,
        (short)3)));
      assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 5, 6,
        (short)3)));
      assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 5, 7,
        (short)3)));
      assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 6, 0,
        (short)3)));
      assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 6, 1,
        (short)3)));
      assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 6, 2,
        (short)3)));
      assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 6, 3,
        (short)3)));
      assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 6, 4,
        (short)3)));
      assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 6, 5,
        (short)3)));
      assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 6, 6,
        (short)3)));
      assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 6, 7,
        (short)3)));
      assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 7, 0,
        (short)3)));
      assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 7, 1,
        (short)3)));
      assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 7, 2,
        (short)3)));
      assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 7, 3,
        (short)3)));
      assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 7, 4,
        (short)3)));
      assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 7, 5,
        (short)3)));
      assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 7, 6,
        (short)3)));
      assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 7, 7,
        (short)3)));
      testKeys.clear();
    }
  }

  @Test
  public void get_siblings_test() {
    QuadKeysVector testKeys;

    QuadKey none = new QuadKey();
    testKeys = none.get_siblings();
    assertEquals(0, testKeys.size());

    QuadKey root = new QuadKey(Type.Bing, 0, 0, (short)0);
    testKeys = root.get_siblings();
    assertEquals(0, testKeys.size());

    QuadKey bingKey = new QuadKey(Type.Bing, 0, 0, (short)1);
    testKeys = bingKey.get_siblings();
    assertEquals(3, testKeys.size());
    assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 0, 1,
      (short)1)));
    assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 1, 1,
      (short)1)));
    assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 1, 0,
      (short)1)));
  }

  @Test
  public void get_neighbors_test() {
    QuadKeysVector testKeys;

    QuadKey none = new QuadKey();
    testKeys = none.get_neighbors();
    assertEquals(0, testKeys.size());

    QuadKey root = new QuadKey(Type.Bing, 0, 0, (short)0);
    testKeys = root.get_neighbors();
    assertEquals(0, testKeys.size());

    testKeys.clear();

    QuadKey key0 = new QuadKey(Type.Bing, 0, 0, (short)2);
    testKeys = key0.get_neighbors();
    assertEquals(5, testKeys.size());
    assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 0, 1,
      (short)2)));
    assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 1, 1,
      (short)2)));
    assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 1, 0,
      (short)2)));
    assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 0, 3,
      (short)2)));
    assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 1, 3,
      (short)2)));

    testKeys.clear();

    QuadKey key;

    key = new QuadKey(Type.Bing, 0, 1, (short)2);
    testKeys = key.get_neighbors();
    assertEquals(5, testKeys.size());
    assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 0, 0,
      (short)2)));
    assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 1, 0,
      (short)2)));
    assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 1, 1,
      (short)2)));
    assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 1, 2,
      (short)2)));
    assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 0, 2,
      (short)2)));

    testKeys.clear();

    key = new QuadKey(Type.Bing, 0, 2, (short)2);
    testKeys = key.get_neighbors();
    assertEquals(5, testKeys.size());
    assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 0, 1,
      (short)2)));
    assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 1, 1,
      (short)2)));
    assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 1, 2,
      (short)2)));
    assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 1, 3,
      (short)2)));
    assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 0, 3,
      (short)2)));

    testKeys.clear();

    key = new QuadKey(Type.Bing, 0, 3, (short)2);
    testKeys = key.get_neighbors();
    assertEquals(5, testKeys.size());
    assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 0, 2,
      (short)2)));
    assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 1, 2,
      (short)2)));
    assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 1, 3,
      (short)2)));
    assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 1, 0,
      (short)2)));
    assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 0, 0,
      (short)2)));

    testKeys.clear();

    key = new QuadKey(Type.Bing, 1, 0, (short)2);
    testKeys = key.get_neighbors();
    assertEquals(8, testKeys.size());
    assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 0, 0,
      (short)2)));
    assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 0, 1,
      (short)2)));
    assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 1, 1,
      (short)2)));
    assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 2, 1,
      (short)2)));
    assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 2, 0,
      (short)2)));
    assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 2, 3,
      (short)2)));
    assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 1, 3,
      (short)2)));
    assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 0, 3,
      (short)2)));

    testKeys.clear();

    key = new QuadKey(Type.Bing, 1, 1, (short)2);
    testKeys = key.get_neighbors();
    assertEquals(8, testKeys.size());
    assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 1, 0,
      (short)2)));
    assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 0, 0,
      (short)2)));
    assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 0, 1,
      (short)2)));
    assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 2, 2,
      (short)2)));
    assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 2, 1,
      (short)2)));
    assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 2, 0,
      (short)2)));
    assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 0, 2,
      (short)2)));
    assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 1, 2,
      (short)2)));

    testKeys.clear();

    key = new QuadKey(Type.Bing, 1, 2, (short)2);
    testKeys = key.get_neighbors();
    assertEquals(8, testKeys.size());
    assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 1, 1,
      (short)2)));
    assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 0, 1,
      (short)2)));
    assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 0, 2,
      (short)2)));
    assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 2, 3,
      (short)2)));
    assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 2, 2,
      (short)2)));
    assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 2, 1,
      (short)2)));
    assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 0, 3,
      (short)2)));
    assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 1, 3,
      (short)2)));

    testKeys.clear();

    key = new QuadKey(Type.Bing, 1, 3, (short)2);
    testKeys = key.get_neighbors();
    assertEquals(8, testKeys.size());
    assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 1, 2,
      (short)2)));
    assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 0, 2,
      (short)2)));
    assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 0, 3,
      (short)2)));
    assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 2, 0,
      (short)2)));
    assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 2, 3,
      (short)2)));
    assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 2, 2,
      (short)2)));
    assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 0, 0,
      (short)2)));
    assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 1, 0,
      (short)2)));

    testKeys.clear();

    key = new QuadKey(Type.Bing, 4, 7, (short)3);
    testKeys = key.get_neighbors();
    assertEquals(8, testKeys.size());
    assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 3, 7,
      (short)3)));
    assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 3, 6,
      (short)3)));
    assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 4, 6,
      (short)3)));
    assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 5, 6,
      (short)3)));
    assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 5, 7,
      (short)3)));
    assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 5, 0,
      (short)3)));
    assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 4, 0,
      (short)3)));
    assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 3, 0,
      (short)3)));

    testKeys.clear();

    key = new QuadKey(Type.Bing, 4, 0, (short)3);
    testKeys = key.get_neighbors();
    assertEquals(8, testKeys.size());
    assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 3, 0,
      (short)3)));
    assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 3, 1,
      (short)3)));
    assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 4, 1,
      (short)3)));
    assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 5, 1,
      (short)3)));
    assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 5, 0,
      (short)3)));
    assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 5, 7,
      (short)3)));
    assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 4, 7,
      (short)3)));
    assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 3, 7,
      (short)3)));

    testKeys.clear();
  }

  @Test
  public void from_internal_string_to_string_test() {
    {
      QuadKey root = QuadKey.from_internal_string(Type.Bing, "");
      assertEquals(0, root.get_row());
      assertEquals(0, root.get_col());
      assertEquals(0, root.get_depth());
    }

    {
      QuadKey key;
      key = QuadKey.from_internal_string(Type.Bing, "0");
      assertEquals(1, key.get_row());
      assertEquals(0, key.get_col());
      assertEquals(1, key.get_depth());
      assertEquals("0", key.to_internal_string());
      key = QuadKey.from_internal_string(Type.Bing, "1");
      assertEquals(1, key.get_row());
      assertEquals(1, key.get_col());
      assertEquals(1, key.get_depth());
      assertEquals("1", key.to_internal_string());
      key = QuadKey.from_internal_string(Type.Bing, "2");
      assertEquals(0, key.get_row());
      assertEquals(0, key.get_col());
      assertEquals(1, key.get_depth());
      assertEquals("2", key.to_internal_string());
      key = QuadKey.from_internal_string(Type.Bing, "3");
      assertEquals(0, key.get_row());
      assertEquals(1, key.get_col());
      assertEquals(1, key.get_depth());
      assertEquals("3", key.to_internal_string());
    }

    {
      QuadKey key;
      key = QuadKey.from_internal_string(Type.Bing, "00");
      assertEquals(3, key.get_row());
      assertEquals(0, key.get_col());
      assertEquals(2, key.get_depth());
      assertEquals("00", key.to_internal_string());
      key = QuadKey.from_internal_string(Type.Bing, "01");
      assertEquals(3, key.get_row());
      assertEquals(1, key.get_col());
      assertEquals(2, key.get_depth());
      assertEquals("01", key.to_internal_string());
      key = QuadKey.from_internal_string(Type.Bing, "02");
      assertEquals(2, key.get_row());
      assertEquals(0, key.get_col());
      assertEquals(2, key.get_depth());
      assertEquals("02", key.to_internal_string());
      key = QuadKey.from_internal_string(Type.Bing, "03");
      assertEquals(2, key.get_row());
      assertEquals(1, key.get_col());
      assertEquals(2, key.get_depth());
      assertEquals("03", key.to_internal_string());
      key = QuadKey.from_internal_string(Type.Bing, "10");
      assertEquals(3, key.get_row());
      assertEquals(2, key.get_col());
      assertEquals(2, key.get_depth());
      assertEquals("10", key.to_internal_string());
      key = QuadKey.from_internal_string(Type.Bing, "11");
      assertEquals(3, key.get_row());
      assertEquals(3, key.get_col());
      assertEquals(2, key.get_depth());
      assertEquals("11", key.to_internal_string());
      key = QuadKey.from_internal_string(Type.Bing, "12");
      assertEquals(2, key.get_row());
      assertEquals(2, key.get_col());
      assertEquals(2, key.get_depth());
      assertEquals("12", key.to_internal_string());
      key = QuadKey.from_internal_string(Type.Bing, "13");
      assertEquals(2, key.get_row());
      assertEquals(3, key.get_col());
      assertEquals(2, key.get_depth());
      assertEquals("13", key.to_internal_string());
      key = QuadKey.from_internal_string(Type.Bing, "20");
      assertEquals(1, key.get_row());
      assertEquals(0, key.get_col());
      assertEquals(2, key.get_depth());
      assertEquals("20", key.to_internal_string());
      key = QuadKey.from_internal_string(Type.Bing, "21");
      assertEquals(1, key.get_row());
      assertEquals(1, key.get_col());
      assertEquals(2, key.get_depth());
      assertEquals("21", key.to_internal_string());
      key = QuadKey.from_internal_string(Type.Bing, "22");
      assertEquals(0, key.get_row());
      assertEquals(0, key.get_col());
      assertEquals(2, key.get_depth());
      assertEquals("22", key.to_internal_string());
      key = QuadKey.from_internal_string(Type.Bing, "23");
      assertEquals(0, key.get_row());
      assertEquals(1, key.get_col());
      assertEquals(2, key.get_depth());
      assertEquals("23", key.to_internal_string());
      key = QuadKey.from_internal_string(Type.Bing, "30");
      assertEquals(1, key.get_row());
      assertEquals(2, key.get_col());
      assertEquals(2, key.get_depth());
      assertEquals("30", key.to_internal_string());
      key = QuadKey.from_internal_string(Type.Bing, "31");
      assertEquals(1, key.get_row());
      assertEquals(3, key.get_col());
      assertEquals(2, key.get_depth());
      assertEquals("31", key.to_internal_string());
      key = QuadKey.from_internal_string(Type.Bing, "32");
      assertEquals(0, key.get_row());
      assertEquals(2, key.get_col());
      assertEquals(2, key.get_depth());
      assertEquals("32", key.to_internal_string());
      key = QuadKey.from_internal_string(Type.Bing, "33");
      assertEquals(0, key.get_row());
      assertEquals(3, key.get_col());
      assertEquals(2, key.get_depth());
      assertEquals("33", key.to_internal_string());
    }
  }

  @Test
  public void get_geo_coordinate_bounds2d_test() {
    QuadKey key;
    GeoCoordinateBoundingBox2d bbox = new GeoCoordinateBoundingBox2d();

    key = QuadKey.from_internal_string(Type.Bing, "");
    key.get_geo_coordinate_bounds2d(bbox);
    assertEquals(-180.0, bbox.lower_left().get_longitude().val(), 1e-7);
    assertEquals(-84.9283209, bbox.lower_left().get_latitude().val(), 1e-7);
    assertEquals(178.593750, bbox.upper_right().get_longitude().val(), 1e-7);
    assertEquals(85.05112877, bbox.upper_right().get_latitude().val(), 1e-7);
  }

  @Test
  public void get_key_from_longitude_latitude_at_depthToBounds_test() {
    QuadKey key;
    GeoCoordinateBoundingBox2d bbox = new GeoCoordinateBoundingBox2d();
    double diff;

    { // Depth 0
      key = QuadKey.get_key_from_longitude_latitude_at_depth(
        Type.Bing, new GeoCoordinate2d(new Longitude(-180.0),
        new Latitude(-84.0)), (short)0);
      assertTrue(new QuadKey(Type.Bing, 0, 0, (short)0).equalTo(key));
      key.get_geo_coordinate_bounds2d(bbox);
      diff = Math.abs(bbox.lower_left().get_longitude().longitudeDifference(
        new Longitude(-180.0)));
      assertTrue(2.0 > diff);
      diff = Math.abs(bbox.lower_left().get_latitude().latitudeDifference(
        new Latitude(-85.0)));
      assertTrue(2.0 > diff);
      diff = Math.abs(
        bbox.upper_right().get_longitude().longitudeDifference(
          new Longitude(+180.0)));
      assertTrue(2.0 > diff);
      diff = Math.abs(bbox.upper_right().get_latitude().latitudeDifference(
        new Latitude(+85.0)));
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
    Longitude left = new Longitude(-180.0);
    Longitude midLeft = new Longitude(-0.36);
    Longitude midRight = new Longitude(0.0);
    Longitude right = new Longitude(+180.0);
    Latitude bottom = new Latitude(-90.0);
    Latitude midBottom = new Latitude(0.0);
    Latitude midTop = new Latitude(0.36);
    Latitude top = new Latitude(+90.0);

    { // Depth 1
      key = QuadKey.get_key_from_longitude_latitude_at_depth( // Q0 ul
        Type.Bing, new GeoCoordinate2d(left, top), (short)1);
      assertTrue(new QuadKey(Type.Bing, 1, 0, (short)1).equalTo(key));
      key = QuadKey.get_key_from_longitude_latitude_at_depth( // Q0 ll
        Type.Bing, new GeoCoordinate2d(left, midTop), (short)1);
      assertTrue(new QuadKey(Type.Bing, 1, 0, (short)1).equalTo(key));
      key = QuadKey.get_key_from_longitude_latitude_at_depth( // Q0 lr
        Type.Bing, new GeoCoordinate2d(midLeft, midTop), (short)1);
      assertTrue(new QuadKey(Type.Bing, 1, 0, (short)1).equalTo(key));
      key = QuadKey.get_key_from_longitude_latitude_at_depth( // Q0 ur
        Type.Bing, new GeoCoordinate2d(midLeft, top), (short)1);
      assertTrue(new QuadKey(Type.Bing, 1, 0, (short)1).equalTo(key));
      key.get_geo_coordinate_bounds2d(bbox);
      diff = Math.abs(bbox.lower_left().get_longitude().longitudeDifference(
        left));
      assertTrue(2.0 > diff);
      diff = Math.abs(bbox.lower_left().get_latitude().latitudeDifference(
        midTop));
      assertTrue(2.0 > diff);
      diff =
        Math.abs(bbox.upper_right().get_longitude().longitudeDifference(
          midLeft));
      assertTrue(2.0 > diff);
      diff = Math.abs(bbox.upper_right().get_latitude().latitudeDifference(
        new Latitude(+85.0)));
      assertTrue(2.0 > diff);

      key = QuadKey.get_key_from_longitude_latitude_at_depth( // Q1 ul
        Type.Bing, new GeoCoordinate2d(midRight, top), (short)1);
      assertTrue(new QuadKey(Type.Bing, 1, 1, (short)1).equalTo(key));
      key = QuadKey.get_key_from_longitude_latitude_at_depth( // Q1 ll
        Type.Bing, new GeoCoordinate2d(midRight, midTop), (short)1);
      assertTrue(new QuadKey(Type.Bing, 1, 1, (short)1).equalTo(key));
      key = QuadKey.get_key_from_longitude_latitude_at_depth( // Q1 lr
        Type.Bing, new GeoCoordinate2d(right, midTop), (short)1);
      assertTrue(new QuadKey(Type.Bing, 1, 1, (short)1).equalTo(key));
      key = QuadKey.get_key_from_longitude_latitude_at_depth( // Q1 ur
        Type.Bing, new GeoCoordinate2d(right, top), (short)1);
      assertTrue(new QuadKey(Type.Bing, 1, 1, (short)1).equalTo(key));
      key.get_geo_coordinate_bounds2d(bbox);
      diff = Math.abs(bbox.lower_left().get_longitude().longitudeDifference(
        midRight));
      assertTrue(2.0 > diff);
      diff = Math.abs(bbox.lower_left().get_latitude().latitudeDifference(
        midTop));
      assertTrue(2.0 > diff);
      diff =
        Math.abs(bbox.upper_right().get_longitude().longitudeDifference(
          right));
      assertTrue(2.0 > diff);
      diff = Math.abs(bbox.upper_right().get_latitude().latitudeDifference(
        new Latitude(+85.0)));
      assertTrue(2.0 > diff);

      key = QuadKey.get_key_from_longitude_latitude_at_depth( // Q2 ul
        Type.Bing, new GeoCoordinate2d(left, midBottom), (short)1);
      assertTrue(new QuadKey(Type.Bing, 0, 0, (short)1).equalTo(key));
      key = QuadKey.get_key_from_longitude_latitude_at_depth( // Q2 ll
        Type.Bing, new GeoCoordinate2d(left, bottom), (short)1);
      assertTrue(new QuadKey(Type.Bing, 0, 0, (short)1).equalTo(key));
      key = QuadKey.get_key_from_longitude_latitude_at_depth( // Q2 lr
        Type.Bing, new GeoCoordinate2d(midLeft, bottom), (short)1);
      assertTrue(new QuadKey(Type.Bing, 0, 0, (short)1).equalTo(key));
      key = QuadKey.get_key_from_longitude_latitude_at_depth( // Q2 ur
        Type.Bing, new GeoCoordinate2d(midLeft, midBottom), (short)1);
      assertTrue(new QuadKey(Type.Bing, 0, 0, (short)1).equalTo(key));
      key.get_geo_coordinate_bounds2d(bbox);
      diff = Math.abs(bbox.lower_left().get_longitude().longitudeDifference(
        left));
      assertTrue(2.0 > diff);
      diff = Math.abs(bbox.lower_left().get_latitude().latitudeDifference(
        new Latitude(-85.0)));
      assertTrue(2.0 > diff);
      diff =
        Math.abs(bbox.upper_right().get_longitude().longitudeDifference(
          midLeft));
      assertTrue(2.0 > diff);
      diff = Math.abs(bbox.upper_right().get_latitude().latitudeDifference(
        midBottom));
      assertTrue(2.0 > diff);

      key = QuadKey.get_key_from_longitude_latitude_at_depth( // Q3 ul
        Type.Bing, new GeoCoordinate2d(midRight, midBottom), (short)1);
      assertTrue(new QuadKey(Type.Bing, 0, 1, (short)1).equalTo(key));
      key = QuadKey.get_key_from_longitude_latitude_at_depth( // Q3 ll
        Type.Bing, new GeoCoordinate2d(midRight, bottom), (short)1);
      assertTrue(new QuadKey(Type.Bing, 0, 1, (short)1).equalTo(key));
      key = QuadKey.get_key_from_longitude_latitude_at_depth( // Q3 lr
        Type.Bing, new GeoCoordinate2d(right, bottom), (short)1);
      assertTrue(new QuadKey(Type.Bing, 0, 1, (short)1).equalTo(key));
      key = QuadKey.get_key_from_longitude_latitude_at_depth( // Q3 ur
        Type.Bing, new GeoCoordinate2d(right, midBottom), (short)1);
      assertTrue(new QuadKey(Type.Bing, 0, 1, (short)1).equalTo(key));
      key.get_geo_coordinate_bounds2d(bbox);
      diff = Math.abs(bbox.lower_left().get_longitude().longitudeDifference(
        midRight));
      assertTrue(2.0 > diff);
      diff = Math.abs(bbox.lower_left().get_latitude().latitudeDifference(
        new Latitude(-85.0)));
      assertTrue(2.0 > diff);
      diff =
        Math.abs(bbox.upper_right().get_longitude().longitudeDifference(
          right));
      assertTrue(2.0 > diff);
      diff = Math.abs(bbox.upper_right().get_latitude().latitudeDifference(
        midBottom));
      assertTrue(2.0 > diff);
    }
  }

  @Test
  public void get_keys_from_longitude_latitude_bounding_box() {
    {
      QuadKeysVector outKeys;
      outKeys = QuadKey.get_keys_from_longitude_latitude_bounding_box(
        Type.Bing,
        new GeoCoordinateBoundingBox2d(
          new GeoCoordinate2d(
            new Longitude(-180.0), new Latitude(+90.0)),
          new GeoCoordinate2d(
            new Longitude(+180.0), new Latitude(-90.0))), (short)0);
      assertEquals(1, outKeys.size());
      assertTrue(vectorContains(outKeys, new QuadKey(Type.Bing, 0, 0,
        (short)0)));
    }

    {
      QuadKeysVector outKeys;
      outKeys = QuadKey.get_keys_from_longitude_latitude_bounding_box(
        Type.Bing,
        new GeoCoordinateBoundingBox2d(
          new GeoCoordinate2d(
            new Longitude(-180.0), new Latitude(+90.0)),
          new GeoCoordinate2d(
            new Longitude(+180.0), new Latitude(-90.0))),
        (short)1);
      assertEquals(4, outKeys.size());
      assertTrue(vectorContains(outKeys, new QuadKey(Type.Bing, 0, 0,
        (short)1)));
      assertTrue(vectorContains(outKeys, new QuadKey(Type.Bing, 0, 1,
        (short)1)));
      assertTrue(vectorContains(outKeys, new QuadKey(Type.Bing, 1, 0,
        (short)1)));
      assertTrue(vectorContains(outKeys, new QuadKey(Type.Bing, 1, 1,
        (short)1)));
    }

    {
      QuadKeysVector outKeys;
      outKeys = QuadKey.get_keys_from_longitude_latitude_bounding_box(
        Type.Bing,
        new GeoCoordinateBoundingBox2d(
          new GeoCoordinate2d(
            new Longitude(-180.0), new Latitude(+0.35)),
          new GeoCoordinate2d(
            new Longitude(-0.36), new Latitude(+90.0))), (short)1);
      assertEquals(2, outKeys.size());
      assertTrue(vectorContains(outKeys, new QuadKey(Type.Bing, 0, 0,
        (short)1)));
      assertTrue(vectorContains(outKeys, new QuadKey(Type.Bing, 1, 0,
        (short)1)));
    }

    {
      QuadKeysVector outKeys;
      outKeys = QuadKey.get_keys_from_longitude_latitude_bounding_box(
        Type.Bing,
        new GeoCoordinateBoundingBox2d(
          new GeoCoordinate2d(
            new Longitude(-0.36), new Latitude(+0.36)),
          new GeoCoordinate2d(
            new Longitude(+0.36), new Latitude(+90.0))), (short)1);
      assertEquals(2, outKeys.size());
      assertTrue(vectorContains(outKeys, new QuadKey(Type.Bing, 1, 0,
        (short)1)));
      assertTrue(vectorContains(outKeys, new QuadKey(Type.Bing, 1, 1,
        (short)1)));
    }

    {
      QuadKeysVector outKeys;
      outKeys = QuadKey.get_keys_from_longitude_latitude_bounding_box(
        Type.Bing,
        new GeoCoordinateBoundingBox2d(
          new GeoCoordinate2d(
            new Longitude(-0.36), new Latitude(+0.35)),
          new GeoCoordinate2d(
            new Longitude(+0.36), new Latitude(+90.0))), (short)1);
      assertEquals(4, outKeys.size());
      assertTrue(vectorContains(outKeys, new QuadKey(Type.Bing, 0, 0,
        (short)1)));
      assertTrue(vectorContains(outKeys, new QuadKey(Type.Bing, 0, 1,
        (short)1)));
      assertTrue(vectorContains(outKeys, new QuadKey(Type.Bing, 1, 0,
        (short)1)));
      assertTrue(vectorContains(outKeys, new QuadKey(Type.Bing, 1, 1,
        (short)1)));
    }
  }

  @Test
  public void selected_cities_test() {
    QuadKey key;
    Type t = Type.Bing;

    { // Chicago 41.822, -87.635
      short depth = 16;
      GeoCoordinate2d coords = new GeoCoordinate2d(
        new Longitude(-87.635), new Latitude(41.822));

      key = QuadKey.get_key_from_longitude_latitude_at_depth(t, coords,
        depth);
      String keyStr = key.to_internal_string();
      assertEquals("0302222310321132", keyStr);

      GeoCoordinateBoundingBox2d bbox =
        new GeoCoordinateBoundingBox2d();
      key.get_geo_coordinate_bounds2d(bbox);

      // Note that bing will return a bounding box of all sides inclusive
      QuadKeysVector keys;
      keys =QuadKey.get_keys_from_longitude_latitude_bounding_box(t, bbox,
        depth);
      assertEquals(4, keys.size());
      assertTrue(vectorContains(keys, key));
    }

    { // Rio -43.1964,-22.9083
      short depth = 17;
      GeoCoordinate2d coords = new GeoCoordinate2d(
              new Longitude(-43.1964), new Latitude(-22.9083));

      key = QuadKey.get_key_from_longitude_latitude_at_depth(t, coords,
        depth);
      String keyStr = key.to_internal_string();
      assertEquals("21120001212232200", keyStr);

      GeoCoordinateBoundingBox2d bbox =
        new GeoCoordinateBoundingBox2d();
      key.get_geo_coordinate_bounds2d(bbox);

      // Note that bing will return a bounding box of all sides inclusive
      QuadKeysVector keys;
      keys = QuadKey.get_keys_from_longitude_latitude_bounding_box(t,
        bbox, depth);
      assertEquals(4, keys.size());
      assertTrue(vectorContains(keys, key));
    }

    { // Helsinki 60.1708 N, 24.9375 E
      short depth = 17;
      GeoCoordinate2d coords = new GeoCoordinate2d(
        new Longitude(24.9375), new Latitude(60.1708));

      key = QuadKey.get_key_from_longitude_latitude_at_depth(t, coords,
        depth);
      String keyStr = key.to_internal_string();
      assertEquals("12012021101330131", keyStr);

      GeoCoordinateBoundingBox2d bbox =
        new GeoCoordinateBoundingBox2d();
      key.get_geo_coordinate_bounds2d(bbox);

      // Note that bing will return a bounding box of all sides inclusive
      QuadKeysVector keys;
      keys = QuadKey.get_keys_from_longitude_latitude_bounding_box(t,
        bbox, depth);
      assertEquals(4, keys.size());
      assertTrue(vectorContains(keys, key));
    }

    { // Cape Town South Africa 33.9253 S, 18.4239 E
      short depth = 17;
      GeoCoordinate2d coords = new GeoCoordinate2d(
        new Longitude(18.4239), new Latitude(-33.9253));

      key = QuadKey.get_key_from_longitude_latitude_at_depth(t, coords,
        depth);
      String keyStr = key.to_internal_string();
      assertEquals("30023103202132011", keyStr);

      GeoCoordinateBoundingBox2d bbox =
        new GeoCoordinateBoundingBox2d();
      key.get_geo_coordinate_bounds2d(bbox);

      // Note that bing will return a bounding box of all sides inclusive
      QuadKeysVector keys;
      keys = QuadKey.get_keys_from_longitude_latitude_bounding_box(t,
        bbox, depth);
      assertEquals(4, keys.size());
      assertTrue(vectorContains(keys, key));
    }

    { // Quito 0.2500 S, 78.5833 W
      short depth = 17;
      GeoCoordinate2d coords = new GeoCoordinate2d(
        new Longitude(-78.5836), new Latitude(-0.25));

      key = QuadKey.get_key_from_longitude_latitude_at_depth(t, coords,
        depth);
      String keyStr = key.to_internal_string();
      assertEquals("21001000002133122", keyStr);

      GeoCoordinateBoundingBox2d bbox =
        new GeoCoordinateBoundingBox2d();
      key.get_geo_coordinate_bounds2d(bbox);

      // Note that bing will return a bounding box of all sides inclusive
      QuadKeysVector keys;
      keys = QuadKey.get_keys_from_longitude_latitude_bounding_box(t,
        bbox, depth);
      assertEquals(4, keys.size());
      assertTrue(vectorContains(keys, key));
    }
  }
}

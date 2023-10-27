package com.quad_keys;

import org.junit.BeforeClass;
import org.junit.Test;

import java.util.ArrayList;
import java.util.List;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertTrue;

public class MortonSystemTest {

  private static class Pair<X, Y> {
    private final X m_X;
    private final Y m_Y;

    public Pair(X x, Y y) {
      m_X = x;
      m_Y = y;
    }

    X first() {
      return m_X;
    }

    Y second() {
      return m_Y;
    }
  }

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
    // See test_QuadKey TestSpecificCtorTest.
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
    {
      QuadKey quadKey = new QuadKey(Type.Morton, 0, 1, (short)1);
      QuadKey ancestor = new QuadKey(Type.Morton, 0, 0, (short)0);
      assertTrue(ancestor.equalTo(quadKey.get_ancestor((short)1)));
      assertTrue(quadKey.get_parent().equalTo(quadKey.get_ancestor(
        (short)1)));
    }
    {
      QuadKey quadKey = new QuadKey(Type.Morton, 0, 0, (short)1);
      QuadKey ancestor = new QuadKey(Type.Morton, 0, 0, (short)0);
      assertTrue(ancestor.equalTo(quadKey.get_ancestor((short)1)));
      assertTrue(quadKey.get_parent().equalTo(quadKey.get_ancestor(
        (short)1)));
    }
    {
      QuadKey quadKey = new QuadKey(Type.Morton, 1, 1, (short)1);
      QuadKey ancestor = new QuadKey(Type.Morton, 0, 0, (short)0);
      assertTrue(ancestor.equalTo(quadKey.get_ancestor((short)1)));
    }
    {
      QuadKey quadKey = new QuadKey(Type.Morton, 1, 2, (short)1);
      QuadKey ancestor = new QuadKey(Type.Morton, 0, 1, (short)0);
      assertTrue(ancestor.equalTo(quadKey.get_ancestor((short)1)));
    }
    {
      QuadKey quadKey = new QuadKey(Type.Morton, 0, 2, (short)1);
      QuadKey ancestor = new QuadKey(Type.Morton, 0, 1, (short)0);
      assertTrue(ancestor.equalTo(quadKey.get_ancestor((short)1)));
    }
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
    QuadKeysVector testKeys;
    testKeys = new QuadKey(Type.Morton, 0, 0, (short)1).get_siblings();
    assertEquals(3, testKeys.size());
    assertTrue(vectorContains(testKeys,
      new QuadKey(Type.Morton, 1, 0, (short)1)));
    assertTrue(vectorContains(testKeys,
      new QuadKey(Type.Morton, 1, 1, (short)1)));
    assertTrue(vectorContains(testKeys,
      new QuadKey(Type.Morton, 0, 1, (short)1)));
    testKeys = new QuadKey(Type.Morton, 1, 3, (short)1).get_siblings();
    assertEquals(3, testKeys.size());
    assertTrue(vectorContains(testKeys,
      new QuadKey(Type.Morton, 1, 2, (short)1)));
    assertTrue(vectorContains(testKeys,
      new QuadKey(Type.Morton, 0, 2, (short)1)));
    assertTrue(vectorContains(testKeys,
      new QuadKey(Type.Morton, 0, 3, (short)1)));
  }

  @Test
  public void get_neighbors_test() {
    // Same as bing_system but just to be safe
    QuadKeysVector testKeys;
    testKeys = new QuadKey().get_neighbors();
    assertTrue(testKeys.isEmpty());

    testKeys = new QuadKey(Type.Morton, 0, 0, (short)2).get_neighbors();
    assertEquals(5, testKeys.size());
    assertTrue(vectorContains(testKeys,
      new QuadKey(Type.Morton, 0, 1, (short)2)));
    assertTrue(vectorContains(testKeys,
      new QuadKey(Type.Morton, 1, 1, (short)2)));
    assertTrue(vectorContains(testKeys,
      new QuadKey(Type.Morton, 1, 0, (short)2)));
    assertTrue(vectorContains(testKeys,
      new QuadKey(Type.Morton, 0, 7, (short)2)));
    assertTrue(vectorContains(testKeys,
      new QuadKey(Type.Morton, 1, 7, (short)2)));

    testKeys = new QuadKey(Type.Morton, 0, 1, (short)2).get_neighbors();
    assertEquals(5, testKeys.size());
    assertTrue(vectorContains(testKeys,
      new QuadKey(Type.Morton, 0, 0, (short)2)));
    assertTrue(vectorContains(testKeys,
      new QuadKey(Type.Morton, 1, 0, (short)2)));
    assertTrue(vectorContains(testKeys,
      new QuadKey(Type.Morton, 1, 1, (short)2)));
    assertTrue(vectorContains(testKeys,
      new QuadKey(Type.Morton, 1, 2, (short)2)));
    assertTrue(vectorContains(testKeys,
      new QuadKey(Type.Morton, 0, 2, (short)2)));

    testKeys = new QuadKey(Type.Morton, 0, 2, (short)2).get_neighbors();
    assertEquals(5, testKeys.size());
    assertTrue(vectorContains(testKeys,
      new QuadKey(Type.Morton, 0, 1, (short)2)));
    assertTrue(vectorContains(testKeys,
      new QuadKey(Type.Morton, 1, 1, (short)2)));
    assertTrue(vectorContains(testKeys,
      new QuadKey(Type.Morton, 1, 2, (short)2)));
    assertTrue(vectorContains(testKeys,
      new QuadKey(Type.Morton, 1, 3, (short)2)));
    assertTrue(vectorContains(testKeys,
      new QuadKey(Type.Morton, 0, 3, (short)2)));

    testKeys = new QuadKey(Type.Morton, 0, 3, (short)2).get_neighbors();
    assertEquals(5, testKeys.size());
    assertTrue(vectorContains(testKeys,
      new QuadKey(Type.Morton, 0, 2, (short)2)));
    assertTrue(vectorContains(testKeys,
      new QuadKey(Type.Morton, 1, 2, (short)2)));
    assertTrue(vectorContains(testKeys,
      new QuadKey(Type.Morton, 1, 3, (short)2)));
    assertTrue(vectorContains(testKeys,
      new QuadKey(Type.Morton, 1, 4, (short)2)));
    assertTrue(vectorContains(testKeys,
      new QuadKey(Type.Morton, 0, 4, (short)2)));

    testKeys = new QuadKey(Type.Morton, 0, 0, (short)2).get_neighbors();
    assertEquals(5, testKeys.size());
    assertTrue(vectorContains(testKeys,
      new QuadKey(Type.Morton, 0, 1, (short)2)));
    assertTrue(vectorContains(testKeys,
      new QuadKey(Type.Morton, 1, 1, (short)2)));
    assertTrue(vectorContains(testKeys,
      new QuadKey(Type.Morton, 1, 0, (short)2)));
    assertTrue(vectorContains(testKeys,
      new QuadKey(Type.Morton, 1, 7, (short)2)));
    assertTrue(vectorContains(testKeys,
      new QuadKey(Type.Morton, 0, 7, (short)2)));

    testKeys = new QuadKey(Type.Morton, 3, 1, (short)2).get_neighbors();
    assertEquals(5, testKeys.size());
    assertTrue(vectorContains(testKeys,
      new QuadKey(Type.Morton, 3, 0, (short)2)));
    assertTrue(vectorContains(testKeys,
      new QuadKey(Type.Morton, 2, 0, (short)2)));
    assertTrue(vectorContains(testKeys,
      new QuadKey(Type.Morton, 2, 1, (short)2)));
    assertTrue(vectorContains(testKeys,
      new QuadKey(Type.Morton, 2, 2, (short)2)));
    assertTrue(vectorContains(testKeys,
      new QuadKey(Type.Morton, 3, 2, (short)2)));

    testKeys = new QuadKey(Type.Morton, 3, 2, (short)2).get_neighbors();
    assertEquals(5, testKeys.size());
    assertTrue(vectorContains(testKeys,
      new QuadKey(Type.Morton, 3, 1, (short)2)));
    assertTrue(vectorContains(testKeys,
      new QuadKey(Type.Morton, 2, 1, (short)2)));
    assertTrue(vectorContains(testKeys,
      new QuadKey(Type.Morton, 2, 2, (short)2)));
    assertTrue(vectorContains(testKeys,
      new QuadKey(Type.Morton, 2, 3, (short)2)));
    assertTrue(vectorContains(testKeys,
      new QuadKey(Type.Morton, 3, 3, (short)2)));

    testKeys = new QuadKey(Type.Morton, 3, 3, (short)2).get_neighbors();
    assertEquals(5, testKeys.size());
    assertTrue(vectorContains(testKeys,
      new QuadKey(Type.Morton, 3, 2, (short)2)));
    assertTrue(vectorContains(testKeys,
      new QuadKey(Type.Morton, 2, 2, (short)2)));
    assertTrue(vectorContains(testKeys,
      new QuadKey(Type.Morton, 2, 3, (short)2)));
    assertTrue(vectorContains(testKeys,
      new QuadKey(Type.Morton, 2, 4, (short)2)));
    assertTrue(vectorContains(testKeys,
      new QuadKey(Type.Morton, 3, 4, (short)2)));

    testKeys = new QuadKey(Type.Morton, 4, 7, (short)3).get_neighbors();
    assertEquals(8, testKeys.size());
    assertTrue(vectorContains(testKeys,
      new QuadKey(Type.Morton, 3, 7, (short)3)));
    assertTrue(vectorContains(testKeys,
      new QuadKey(Type.Morton, 3, 6, (short)3)));
    assertTrue(vectorContains(testKeys,
      new QuadKey(Type.Morton, 4, 6, (short)3)));
    assertTrue(vectorContains(testKeys,
      new QuadKey(Type.Morton, 5, 6, (short)3)));
    assertTrue(vectorContains(testKeys,
      new QuadKey(Type.Morton, 5, 7, (short)3)));
    assertTrue(vectorContains(testKeys,
      new QuadKey(Type.Morton, 5, 8, (short)3)));
    assertTrue(vectorContains(testKeys,
      new QuadKey(Type.Morton, 4, 8, (short)3)));
    assertTrue(vectorContains(testKeys,
      new QuadKey(Type.Morton, 3, 8, (short)3)));

    testKeys = new QuadKey(Type.Morton, 4, 0, (short)3).get_neighbors();
    assertEquals(8, testKeys.size());
    assertTrue(vectorContains(testKeys,
      new QuadKey(Type.Morton, 3, 0, (short)3)));
    assertTrue(vectorContains(testKeys,
      new QuadKey(Type.Morton, 3, 1, (short)3)));
    assertTrue(vectorContains(testKeys,
      new QuadKey(Type.Morton, 4, 1, (short)3)));
    assertTrue(vectorContains(testKeys,
      new QuadKey(Type.Morton, 5, 1, (short)3)));
    assertTrue(vectorContains(testKeys,
      new QuadKey(Type.Morton, 5, 0, (short)3)));
    assertTrue(vectorContains(testKeys,
      new QuadKey(Type.Morton, 5, 15, (short)3)));
    assertTrue(vectorContains(testKeys,
      new QuadKey(Type.Morton, 4, 15, (short)3)));
    assertTrue(vectorContains(testKeys,
      new QuadKey(Type.Morton, 3, 15, (short)3)));

    testKeys = new QuadKey(Type.Morton, 0, 0, (short)0).get_neighbors();
    assertEquals(0, testKeys.size());
  }

  @Test
  public void from_string_to_string_test() {
    // X ==> Unused
    // O ==> Used but never set
    // (0,1) ==> Binary digits
    QuadKey quadKey = new QuadKey(Type.Morton, 0, 0, (short)0);
    String fmt = quadKey.to_internal_string();
    assertEquals("65537", fmt); // XXXX XXXX XXXX XXX1 XXXX XXXX XXXX XXO1
    QuadKey quadKeyBack = QuadKey.from_internal_string(Type.Morton, fmt);
    assertTrue(quadKey.equalTo(quadKeyBack));
    quadKey = new QuadKey(Type.Morton, 0, 1, (short)0);
    fmt = quadKey.to_internal_string();
    assertEquals("65536", fmt); // XXXX XXXX XXXX XXX1 XXXX XXXX XXXX XXO0
    quadKeyBack = QuadKey.from_internal_string(Type.Morton, fmt);
    assertTrue(quadKey.equalTo(quadKeyBack));
    quadKey = new QuadKey(Type.Morton, 0, 0, (short)1);
    fmt = quadKey.to_internal_string();
    assertEquals("131078", fmt); // XXXX XXXX XXXX XX1X XXXX XXXX XXXX O110
    quadKeyBack = QuadKey.from_internal_string(Type.Morton, fmt);
    assertTrue(quadKey.equalTo(quadKeyBack));
    quadKey = new QuadKey(Type.Morton, 0, 1, (short)1);
    fmt = quadKey.to_internal_string();
    assertEquals("131079", fmt); // XXXX XXXX XXXX XX1O OOOO OOOO OOOO O111
    quadKeyBack = QuadKey.from_internal_string(Type.Morton, fmt);
    assertTrue(quadKey.equalTo(quadKeyBack));
    quadKey = new QuadKey(Type.Morton, 0, 2, (short)1);
    fmt = quadKey.to_internal_string();
    assertEquals("131074", fmt); // XXXX XXXX XXXX XX1X XXXX XXXX XXXX O010
    quadKeyBack = QuadKey.from_internal_string(Type.Morton, fmt);
    assertTrue(quadKey.equalTo(quadKeyBack));
    quadKey = new QuadKey(Type.Morton, 0, 3, (short)1);
    fmt = quadKey.to_internal_string();
    assertEquals("131075", fmt); // XXXX XXXX XXXX XX1X XXXX XXXX XXXX O011
    quadKeyBack = QuadKey.from_internal_string(Type.Morton, fmt);
    assertTrue(quadKey.equalTo(quadKeyBack));
    quadKey = new QuadKey(Type.Morton, 1, 0, (short)1);
    fmt = quadKey.to_internal_string();
    assertEquals("131076", fmt); // XXXX XXXX XXXX XX1X XXXX XXXX XXXX O100
    quadKeyBack = QuadKey.from_internal_string(Type.Morton, fmt);
    assertTrue(quadKey.equalTo(quadKeyBack));
    quadKey = new QuadKey(Type.Morton, 1, 1, (short)1);
    fmt = quadKey.to_internal_string();
    assertEquals("131077", fmt); // XXXX XXXX XXXX XX1X XXXX XXXX XXXX O101
    quadKeyBack = QuadKey.from_internal_string(Type.Morton, fmt);
    assertTrue(quadKey.equalTo(quadKeyBack));
    quadKey = new QuadKey(Type.Morton, 1, 2, (short)1);
    fmt = quadKey.to_internal_string();
    assertEquals("131072", fmt); // XXXX XXXX XXXX XX1X XXXX XXXX XXXX O000
    quadKeyBack = QuadKey.from_internal_string(Type.Morton, fmt);
    assertTrue(quadKey.equalTo(quadKeyBack));
    quadKey = new QuadKey(Type.Morton, 1, 3, (short)1);
    fmt = quadKey.to_internal_string();
    assertEquals("131073", fmt); // XXXX XXXX XXXX XX1X XXXX XXXX XXXX O001
    quadKeyBack = QuadKey.from_internal_string(Type.Morton, fmt);
    assertTrue(quadKey.equalTo(quadKeyBack));
    quadKey = new QuadKey(Type.Morton, 0, 0, (short)2);
    fmt = quadKey.to_internal_string();
    assertEquals("262168", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO1 1000
    quadKeyBack = QuadKey.from_internal_string(Type.Morton, fmt);
    assertTrue(quadKey.equalTo(quadKeyBack));
    quadKey = new QuadKey(Type.Morton, 0, 1, (short)2);
    fmt = quadKey.to_internal_string();
    assertEquals("262169", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO1 1001
    quadKeyBack = QuadKey.from_internal_string(Type.Morton, fmt);
    assertTrue(quadKey.equalTo(quadKeyBack));
    quadKey = new QuadKey(Type.Morton, 0, 2, (short)2);
    fmt = quadKey.to_internal_string();
    assertEquals("262172", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO1 1100
    quadKeyBack = QuadKey.from_internal_string(Type.Morton, fmt);
    assertTrue(quadKey.equalTo(quadKeyBack));
    quadKey = new QuadKey(Type.Morton, 0, 3, (short)2);
    fmt = quadKey.to_internal_string();
    assertEquals("262173", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO1 1101
    quadKeyBack = QuadKey.from_internal_string(Type.Morton, fmt);
    assertTrue(quadKey.equalTo(quadKeyBack));
    quadKey = new QuadKey(Type.Morton, 0, 4, (short)2);
    fmt = quadKey.to_internal_string();
    assertEquals("262152", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO0 1000
    quadKeyBack = QuadKey.from_internal_string(Type.Morton, fmt);
    assertTrue(quadKey.equalTo(quadKeyBack));
    quadKey = new QuadKey(Type.Morton, 0, 5, (short)2);
    fmt = quadKey.to_internal_string();
    assertEquals("262153", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO0 1001
    quadKeyBack = QuadKey.from_internal_string(Type.Morton, fmt);
    assertTrue(quadKey.equalTo(quadKeyBack));
    quadKey = new QuadKey(Type.Morton, 0, 6, (short)2);
    fmt = quadKey.to_internal_string();
    assertEquals("262156", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO0 1100
    quadKeyBack = QuadKey.from_internal_string(Type.Morton, fmt);
    assertTrue(quadKey.equalTo(quadKeyBack));
    quadKey = new QuadKey(Type.Morton, 0, 7, (short)2);
    fmt = quadKey.to_internal_string();
    assertEquals("262157", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO0 1101
    quadKeyBack = QuadKey.from_internal_string(Type.Morton, fmt);
    assertTrue(quadKey.equalTo(quadKeyBack));
    quadKey = new QuadKey(Type.Morton, 1, 0, (short)2);
    fmt = quadKey.to_internal_string();
    assertEquals("262170", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO1 1010
    quadKeyBack = QuadKey.from_internal_string(Type.Morton, fmt);
    assertTrue(quadKey.equalTo(quadKeyBack));
    quadKey = new QuadKey(Type.Morton, 1, 1, (short)2);
    fmt = quadKey.to_internal_string();
    assertEquals("262171", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO1 1011
    quadKeyBack = QuadKey.from_internal_string(Type.Morton, fmt);
    assertTrue(quadKey.equalTo(quadKeyBack));
    quadKey = new QuadKey(Type.Morton, 1, 2, (short)2);
    fmt = quadKey.to_internal_string();
    assertEquals("262174", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO1 1110
    quadKeyBack = QuadKey.from_internal_string(Type.Morton, fmt);
    assertTrue(quadKey.equalTo(quadKeyBack));
    quadKey = new QuadKey(Type.Morton, 1, 3, (short)2);
    fmt = quadKey.to_internal_string();
    assertEquals("262175", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO1 1111
    quadKeyBack = QuadKey.from_internal_string(Type.Morton, fmt);
    assertTrue(quadKey.equalTo(quadKeyBack));
    quadKey = new QuadKey(Type.Morton, 1, 4, (short)2);
    fmt = quadKey.to_internal_string();
    assertEquals("262154", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO0 1010
    quadKeyBack = QuadKey.from_internal_string(Type.Morton, fmt);
    assertTrue(quadKey.equalTo(quadKeyBack));
    quadKey = new QuadKey(Type.Morton, 1, 5, (short)2);
    fmt = quadKey.to_internal_string();
    assertEquals("262155", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO0 1011
    quadKeyBack = QuadKey.from_internal_string(Type.Morton, fmt);
    assertTrue(quadKey.equalTo(quadKeyBack));
    quadKey = new QuadKey(Type.Morton, 1, 6, (short)2);
    fmt = quadKey.to_internal_string();
    assertEquals("262158", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO0 1110
    quadKeyBack = QuadKey.from_internal_string(Type.Morton, fmt);
    assertTrue(quadKey.equalTo(quadKeyBack));
    quadKey = new QuadKey(Type.Morton, 1, 7, (short)2);
    fmt = quadKey.to_internal_string();
    assertEquals("262159", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO0 1111
    quadKeyBack = QuadKey.from_internal_string(Type.Morton, fmt);
    assertTrue(quadKey.equalTo(quadKeyBack));
    quadKey = new QuadKey(Type.Morton, 2, 0, (short)2);
    fmt = quadKey.to_internal_string();
    assertEquals("262160", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO1 0000
    quadKeyBack = QuadKey.from_internal_string(Type.Morton, fmt);
    assertTrue(quadKey.equalTo(quadKeyBack));
    quadKey = new QuadKey(Type.Morton, 2, 1, (short)2);
    fmt = quadKey.to_internal_string();
    assertEquals("262161", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO1 0001
    quadKeyBack = QuadKey.from_internal_string(Type.Morton, fmt);
    assertTrue(quadKey.equalTo(quadKeyBack));
    quadKey = new QuadKey(Type.Morton, 2, 2, (short)2);
    fmt = quadKey.to_internal_string();
    assertEquals("262164", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO1 0100
    quadKeyBack = QuadKey.from_internal_string(Type.Morton, fmt);
    assertTrue(quadKey.equalTo(quadKeyBack));
    quadKey = new QuadKey(Type.Morton, 2, 3, (short)2);
    fmt = quadKey.to_internal_string();
    assertEquals("262165", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO1 0101
    quadKeyBack = QuadKey.from_internal_string(Type.Morton, fmt);
    assertTrue(quadKey.equalTo(quadKeyBack));
    quadKey = new QuadKey(Type.Morton, 2, 4, (short)2);
    fmt = quadKey.to_internal_string();
    assertEquals("262144", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO0 0000
    quadKeyBack = QuadKey.from_internal_string(Type.Morton, fmt);
    assertTrue(quadKey.equalTo(quadKeyBack));
    quadKey = new QuadKey(Type.Morton, 2, 5, (short)2);
    fmt = quadKey.to_internal_string();
    assertEquals("262145", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO0 0001
    quadKeyBack = QuadKey.from_internal_string(Type.Morton, fmt);
    assertTrue(quadKey.equalTo(quadKeyBack));
    quadKey = new QuadKey(Type.Morton, 2, 6, (short)2);
    fmt = quadKey.to_internal_string();
    assertEquals("262148", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO0 0100
    quadKeyBack = QuadKey.from_internal_string(Type.Morton, fmt);
    assertTrue(quadKey.equalTo(quadKeyBack));
    quadKey = new QuadKey(Type.Morton, 2, 7, (short)2);
    fmt = quadKey.to_internal_string();
    assertEquals("262149", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO0 0101
    quadKeyBack = QuadKey.from_internal_string(Type.Morton, fmt);
    assertTrue(quadKey.equalTo(quadKeyBack));
    quadKey = new QuadKey(Type.Morton, 3, 0, (short)2);
    fmt = quadKey.to_internal_string();
    assertEquals("262162", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO1 0010
    quadKeyBack = QuadKey.from_internal_string(Type.Morton, fmt);
    assertTrue(quadKey.equalTo(quadKeyBack));
    quadKey = new QuadKey(Type.Morton, 3, 1, (short)2);
    fmt = quadKey.to_internal_string();
    assertEquals("262163", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO1 0011
    quadKeyBack = QuadKey.from_internal_string(Type.Morton, fmt);
    assertTrue(quadKey.equalTo(quadKeyBack));
    quadKey = new QuadKey(Type.Morton, 3, 2, (short)2);
    fmt = quadKey.to_internal_string();
    assertEquals("262166", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO1 0110
    quadKeyBack = QuadKey.from_internal_string(Type.Morton, fmt);
    assertTrue(quadKey.equalTo(quadKeyBack));
    quadKey = new QuadKey(Type.Morton, 3, 3, (short)2);
    fmt = quadKey.to_internal_string();
    assertEquals("262167", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO1 0111
    quadKeyBack = QuadKey.from_internal_string(Type.Morton, fmt);
    assertTrue(quadKey.equalTo(quadKeyBack));
    quadKey = new QuadKey(Type.Morton, 3, 4, (short)2);
    fmt = quadKey.to_internal_string();
    assertEquals("262146", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO0 0010
    quadKeyBack = QuadKey.from_internal_string(Type.Morton, fmt);
    assertTrue(quadKey.equalTo(quadKeyBack));
    quadKey = new QuadKey(Type.Morton, 3, 5, (short)2);
    fmt = quadKey.to_internal_string();
    assertEquals("262147", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO0 0011
    quadKeyBack = QuadKey.from_internal_string(Type.Morton, fmt);
    assertTrue(quadKey.equalTo(quadKeyBack));
    quadKey = new QuadKey(Type.Morton, 3, 6, (short)2);
    fmt = quadKey.to_internal_string();
    assertEquals("262150", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO0 0110
    quadKeyBack = QuadKey.from_internal_string(Type.Morton, fmt);
    assertTrue(quadKey.equalTo(quadKeyBack));
    quadKey = new QuadKey(Type.Morton, 3, 7, (short)2);
    fmt = quadKey.to_internal_string();
    assertEquals("262151", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO0 0111
    quadKeyBack = QuadKey.from_internal_string(Type.Morton, fmt);
    assertTrue(quadKey.equalTo(quadKeyBack));
  }

  @Test
  public void get_geo_coordinate_bounds2d_test() {
    QuadKey quadKey;
    GeoCoordinateBoundingBox2d bbox = new GeoCoordinateBoundingBox2d();
    quadKey = new QuadKey(Type.Morton, 0, 0, (short)0);
    quadKey.get_geo_coordinate_bounds2d(bbox);
    assertTrue(bbox.lower_left().near(new GeoCoordinate2d(
      new Longitude(-180.0), new Latitude(-90.0)), 1e-4));
    assertTrue(bbox.upper_right().near(new GeoCoordinate2d(
      new Longitude(-0.1), new Latitude(+90.0)), 1e-4));

    quadKey = new QuadKey(Type.Morton, 0, 1, (short)0);
    quadKey.get_geo_coordinate_bounds2d(bbox);
    assertTrue(bbox.lower_left().near(new GeoCoordinate2d(
      new Longitude(+0.0), new Latitude(-90.0)), 1e-4));
    assertTrue(bbox.upper_right().near(new GeoCoordinate2d(
      new Longitude(+180.0), new Latitude(+90.0)), 1e-4));

    quadKey = new QuadKey(Type.Morton, 0, 0, (short)1);
    quadKey.get_geo_coordinate_bounds2d(bbox);
    assertTrue(bbox.lower_left().near(new GeoCoordinate2d(
      new Longitude(-180.0), new Latitude(-90.0)), 1e-4));
    assertTrue(bbox.upper_right().near(new GeoCoordinate2d(
      new Longitude(-90.0), new Latitude(+0.0)), 1e-4));

    quadKey = new QuadKey(Type.Morton, 0, 1, (short)1);
    quadKey.get_geo_coordinate_bounds2d(bbox);
    assertTrue(bbox.lower_left().near(new GeoCoordinate2d(
      new Longitude(-90.0), new Latitude(-90.0)), 1e-4));
    assertTrue(bbox.upper_right().near(new GeoCoordinate2d(
      new Longitude(+0.0), new Latitude(+0.0)), 1e-4));

    quadKey = new QuadKey(Type.Morton, 0, 2, (short)1);
    quadKey.get_geo_coordinate_bounds2d(bbox);
    assertTrue(bbox.lower_left().near(new GeoCoordinate2d(
      new Longitude(+0.0), new Latitude(-90.0)), 1e-4));
    assertTrue(bbox.upper_right().near(new GeoCoordinate2d(
      new Longitude(+90.0), new Latitude(+0.0)), 1e-4));

    quadKey = new QuadKey(Type.Morton, 0, 3, (short)1);
    quadKey.get_geo_coordinate_bounds2d(bbox);
    assertTrue(bbox.lower_left().near(new GeoCoordinate2d(
      new Longitude(+90.0), new Latitude(-90.0)), 1e-4));
    assertTrue(bbox.upper_right().near(new GeoCoordinate2d(
      new Longitude(+180.0), new Latitude(+0.0)), 1e-4));

    quadKey = new QuadKey(Type.Morton, 1, 0, (short)1);
    quadKey.get_geo_coordinate_bounds2d(bbox);
    assertTrue(bbox.lower_left().near(new GeoCoordinate2d(
      new Longitude(-180.0), new Latitude(+0.0)), 1e-4));
    assertTrue(bbox.upper_right().near(new GeoCoordinate2d(
      new Longitude(-90.0), new Latitude(+90.0)), 1e-4));

    quadKey = new QuadKey(Type.Morton, 1, 1, (short)1);
    quadKey.get_geo_coordinate_bounds2d(bbox);
    assertTrue(bbox.lower_left().near(new GeoCoordinate2d(
      new Longitude(-90.0), new Latitude(+0.0)), 1e-4));
    assertTrue(bbox.upper_right().near(new GeoCoordinate2d(
      new Longitude(+0.0), new Latitude(+90.0)), 1e-4));

    quadKey = new QuadKey(Type.Morton, 1, 2, (short)1);
    quadKey.get_geo_coordinate_bounds2d(bbox);
    assertTrue(bbox.lower_left().near(new GeoCoordinate2d(
      new Longitude(+0.0), new Latitude(+0.0)), 1e-4));
    assertTrue(bbox.upper_right().near(new GeoCoordinate2d(
      new Longitude(+90.0), new Latitude(+90.0)), 1e-4));

    quadKey = new QuadKey(Type.Morton, 1, 3, (short)1);
    quadKey.get_geo_coordinate_bounds2d(bbox);
    assertTrue(bbox.lower_left().near(new GeoCoordinate2d(
      new Longitude(+90.0), new Latitude(+0.0)), 1e-4));
    assertTrue(bbox.upper_right().near(new GeoCoordinate2d(
      new Longitude(+180.0), new Latitude(+90.0)), 1e-4));
  }

  @Test
  public void get_key_from_longitude_latitude_at_depth_to_boumorton_test() {
    GeoCoordinate2d coords;
    short depth = 0;
    { // West
      QuadKey mortonKey;
      coords = new GeoCoordinate2d(new Longitude(-0.1), new Latitude(0.0));
      mortonKey = QuadKey.get_key_from_longitude_latitude_at_depth(Type.Morton,
        coords, depth);
      assertEquals("65537", mortonKey.to_internal_string());
      coords = new GeoCoordinate2d(new Longitude(-180.0), new Latitude(90.0));
      mortonKey = QuadKey.get_key_from_longitude_latitude_at_depth(Type.Morton,
        coords, depth);
      assertEquals("65537", mortonKey.to_internal_string());
      coords = new GeoCoordinate2d(new Longitude(-180.0), new Latitude(-90.0));
      mortonKey = QuadKey.get_key_from_longitude_latitude_at_depth(Type.Morton,
        coords, depth);
      assertEquals("65537", mortonKey.to_internal_string());
      GeoCoordinateBoundingBox2d actual =
        new GeoCoordinateBoundingBox2d();
      mortonKey.get_geo_coordinate_bounds2d(actual);
      assertTrue(new GeoCoordinate2d(new Longitude(-180.0), new Latitude(-90.0)).near(actual.lower_left(), 1));
      assertTrue(new GeoCoordinate2d(new Longitude(-0.1), new Latitude(+90.0)).near(actual.upper_right(), 1));
    }
    { // East
      QuadKey mortonKey;
      coords = new GeoCoordinate2d(new Longitude(0.0), new Latitude(0.0));
      mortonKey = QuadKey.get_key_from_longitude_latitude_at_depth(Type.Morton,
        coords, depth);
      assertEquals("65536", mortonKey.to_internal_string());
      coords = new GeoCoordinate2d(new Longitude(180.0), new Latitude(-90.0));
      mortonKey = QuadKey.get_key_from_longitude_latitude_at_depth(
      Type.Morton, coords, depth);
      assertEquals("65536", mortonKey.to_internal_string());
      coords = new GeoCoordinate2d(new Longitude(180.0), new Latitude(90.0));
      mortonKey = QuadKey.get_key_from_longitude_latitude_at_depth(
      Type.Morton, coords, depth);
      assertEquals("65536", mortonKey.to_internal_string());
      GeoCoordinateBoundingBox2d actual =
        new GeoCoordinateBoundingBox2d();
      mortonKey.get_geo_coordinate_bounds2d(actual);
      assertTrue(new GeoCoordinate2d(new Longitude(+0.0), new Latitude(-90.0)).near(actual.lower_left(), 1));
      assertTrue(new GeoCoordinate2d(new Longitude(+180.0), new Latitude(+90.0)).near(actual.upper_right(), 1));
    }
    depth = 1;
    { // 0x6
      QuadKey mortonKey;
      coords = new GeoCoordinate2d(new Longitude(-180.0), new Latitude(-0.1));
      mortonKey = QuadKey.get_key_from_longitude_latitude_at_depth(
      Type.Morton, coords, depth);
      assertEquals("131078", mortonKey.to_internal_string());
      coords = new GeoCoordinate2d(new Longitude(-180.0), new Latitude(-90.0));
      mortonKey = QuadKey.get_key_from_longitude_latitude_at_depth(
      Type.Morton, coords, depth);
      assertEquals("131078", mortonKey.to_internal_string());
      coords = new GeoCoordinate2d(new Longitude(-90.1), new Latitude(-90.0));
      mortonKey = QuadKey.get_key_from_longitude_latitude_at_depth(
      Type.Morton, coords, depth);
      assertEquals("131078", mortonKey.to_internal_string());
      coords = new GeoCoordinate2d(new Longitude(-90.1), new Latitude(-0.1));
      mortonKey = QuadKey.get_key_from_longitude_latitude_at_depth(
      Type.Morton, coords, depth);
      assertEquals("131078", mortonKey.to_internal_string());
    }
    { // 0x7
      QuadKey mortonKey;
      coords = new GeoCoordinate2d(new Longitude(-90.0), new Latitude(-0.1));
      mortonKey = QuadKey.get_key_from_longitude_latitude_at_depth(
      Type.Morton, coords, depth);
      assertEquals("131079", mortonKey.to_internal_string());
      coords = new GeoCoordinate2d(new Longitude(-90.0), new Latitude(-90.0));
      mortonKey = QuadKey.get_key_from_longitude_latitude_at_depth(
      Type.Morton, coords, depth);
      assertEquals("131079", mortonKey.to_internal_string());
      coords = new GeoCoordinate2d(new Longitude(-0.1), new Latitude(-90.0));
      mortonKey = QuadKey.get_key_from_longitude_latitude_at_depth(
      Type.Morton, coords, depth);
      assertEquals("131079", mortonKey.to_internal_string());
      coords = new GeoCoordinate2d(new Longitude(-0.1), new Latitude(-0.1));
      mortonKey = QuadKey.get_key_from_longitude_latitude_at_depth(
      Type.Morton, coords, depth);
      assertEquals("131079", mortonKey.to_internal_string());
    }
    { // 0x2
      QuadKey mortonKey;
      coords = new GeoCoordinate2d(new Longitude(0.0), new Latitude(-0.1));
      mortonKey = QuadKey.get_key_from_longitude_latitude_at_depth(
      Type.Morton, coords, depth);
      assertEquals("131074", mortonKey.to_internal_string());
      coords = new GeoCoordinate2d(new Longitude(0.0), new Latitude(-90.0));
      mortonKey = QuadKey.get_key_from_longitude_latitude_at_depth(
      Type.Morton, coords, depth);
      assertEquals("131074", mortonKey.to_internal_string());
      coords = new GeoCoordinate2d(new Longitude(90.0), new Latitude(-90.0));
      mortonKey = QuadKey.get_key_from_longitude_latitude_at_depth(
      Type.Morton, coords, depth);
      assertEquals("131074", mortonKey.to_internal_string());
      coords = new GeoCoordinate2d(new Longitude(90.0), new Latitude(-0.1));
      mortonKey = QuadKey.get_key_from_longitude_latitude_at_depth(
      Type.Morton, coords, depth);
      assertEquals("131074", mortonKey.to_internal_string());
    }
    { // 0x3
      QuadKey mortonKey;
      coords = new GeoCoordinate2d(new Longitude(90.1), new Latitude(-0.1));
      mortonKey = QuadKey.get_key_from_longitude_latitude_at_depth(
      Type.Morton, coords, depth);
      assertEquals("131075", mortonKey.to_internal_string());
      coords = new GeoCoordinate2d(new Longitude(90.1), new Latitude(-90.0));
      mortonKey = QuadKey.get_key_from_longitude_latitude_at_depth(
      Type.Morton, coords, depth);
      assertEquals("131075", mortonKey.to_internal_string());
      coords = new GeoCoordinate2d(new Longitude(180.0), new Latitude(-90.0));
      mortonKey = QuadKey.get_key_from_longitude_latitude_at_depth(
      Type.Morton, coords, depth);
      assertEquals("131075", mortonKey.to_internal_string());
      coords = new GeoCoordinate2d(new Longitude(180.0), new Latitude(-0.1));
      mortonKey = QuadKey.get_key_from_longitude_latitude_at_depth(
      Type.Morton, coords, depth);
      assertEquals("131075", mortonKey.to_internal_string());
    }
    { // 0x4
      QuadKey mortonKey;
      coords = new GeoCoordinate2d(new Longitude(-180.0), new Latitude(90.0));
      mortonKey = QuadKey.get_key_from_longitude_latitude_at_depth(
      Type.Morton, coords, depth);
      assertEquals("131076", mortonKey.to_internal_string());
      coords = new GeoCoordinate2d(new Longitude(-180.0), new Latitude(0.0));
      mortonKey = QuadKey.get_key_from_longitude_latitude_at_depth(
      Type.Morton, coords, depth);
      assertEquals("131076", mortonKey.to_internal_string());
      coords = new GeoCoordinate2d(new Longitude(-90.1), new Latitude(0.0));
      mortonKey = QuadKey.get_key_from_longitude_latitude_at_depth(
        Type.Morton, coords, depth);
      assertEquals("131076", mortonKey.to_internal_string());
      coords = new GeoCoordinate2d(new Longitude(-90.1), new Latitude(90.0));
      mortonKey = QuadKey.get_key_from_longitude_latitude_at_depth(
        Type.Morton, coords, depth);
      assertEquals("131076", mortonKey.to_internal_string());
    }
    { // 0x5
      QuadKey mortonKey;
      coords = new GeoCoordinate2d(new Longitude(-90.0), new Latitude(90.0));
      mortonKey = QuadKey.get_key_from_longitude_latitude_at_depth(
        Type.Morton, coords, depth);
      assertEquals("131077", mortonKey.to_internal_string());
      coords = new GeoCoordinate2d(new Longitude(-90.0), new Latitude(0.0));
      mortonKey = QuadKey.get_key_from_longitude_latitude_at_depth(
        Type.Morton, coords, depth);
      assertEquals("131077", mortonKey.to_internal_string());
      coords = new GeoCoordinate2d(new Longitude(-0.1), new Latitude(0.0));
      mortonKey = QuadKey.get_key_from_longitude_latitude_at_depth(
        Type.Morton, coords, depth);
      assertEquals("131077", mortonKey.to_internal_string());
      coords = new GeoCoordinate2d(new Longitude(-0.1), new Latitude(90.0));
      mortonKey = QuadKey.get_key_from_longitude_latitude_at_depth(
        Type.Morton, coords, depth);
      assertEquals("131077", mortonKey.to_internal_string());
    }
    { // 0x0
      QuadKey mortonKey;
      coords = new GeoCoordinate2d(new Longitude(0.0), new Latitude(90.0));
      mortonKey = QuadKey.get_key_from_longitude_latitude_at_depth(
        Type.Morton, coords, depth);
      assertEquals("131072", mortonKey.to_internal_string());
      coords = new GeoCoordinate2d(new Longitude(0.0), new Latitude(0.0));
      mortonKey = QuadKey.get_key_from_longitude_latitude_at_depth(
        Type.Morton, coords, depth);
      assertEquals("131072", mortonKey.to_internal_string());
      coords = new GeoCoordinate2d(new Longitude(90.0), new Latitude(0.0));
      mortonKey = QuadKey.get_key_from_longitude_latitude_at_depth(
        Type.Morton, coords, depth);
      assertEquals("131072", mortonKey.to_internal_string());
      coords = new GeoCoordinate2d(new Longitude(90.0), new Latitude(90.0));
      mortonKey = QuadKey.get_key_from_longitude_latitude_at_depth(
        Type.Morton, coords, depth);
      assertEquals("131072", mortonKey.to_internal_string());
    }
    { // 0x1
      QuadKey mortonKey;
      coords = new GeoCoordinate2d(new Longitude(90.1), new Latitude(90.0));
      mortonKey = QuadKey.get_key_from_longitude_latitude_at_depth(
        Type.Morton, coords, depth);
      assertEquals("131073", mortonKey.to_internal_string());
      coords = new GeoCoordinate2d(new Longitude(90.1), new Latitude(0.0));
      mortonKey = QuadKey.get_key_from_longitude_latitude_at_depth(
        Type.Morton, coords, depth);
      assertEquals("131073", mortonKey.to_internal_string());
      coords = new GeoCoordinate2d(new Longitude(180.0), new Latitude(0.0));
      mortonKey = QuadKey.get_key_from_longitude_latitude_at_depth(
        Type.Morton, coords, depth);
      assertEquals("131073", mortonKey.to_internal_string());
      coords = new GeoCoordinate2d(new Longitude(180.0), new Latitude(90.0));
      mortonKey = QuadKey.get_key_from_longitude_latitude_at_depth(
        Type.Morton, coords, depth);
      assertEquals("131073", mortonKey.to_internal_string());
    }
    depth = 2;
    List<Pair<GeoCoordinateBoundingBox2d, String>> tests =
      new ArrayList<>();

    tests.add(new Pair<>(
            new GeoCoordinateBoundingBox2d(
                    new GeoCoordinate2d(new Longitude(-180.0), new Latitude(-90.0)),
                    new GeoCoordinate2d(new Longitude(-135.1), new Latitude(-45.1))),
            "262168"));
    tests.add(new Pair<>(
            new GeoCoordinateBoundingBox2d(
                    new GeoCoordinate2d(new Longitude(-135.0), new Latitude(-90.0)),
                    new GeoCoordinate2d(new Longitude(-90.1), new Latitude(-45.1))),
            "262169"));
    tests.add(new Pair<>(
            new GeoCoordinateBoundingBox2d(
                    new GeoCoordinate2d(new Longitude(-90.0), new Latitude(-90.0)),
                    new GeoCoordinate2d(new Longitude(-45.1), new Latitude(-45.1))),
            "262172"));
    tests.add(new Pair<>(
            new GeoCoordinateBoundingBox2d(
                    new GeoCoordinate2d(new Longitude(-45.0), new Latitude(-90.0)),
                    new GeoCoordinate2d(new Longitude(-0.1), new Latitude(-45.1))),
            "262173"));
    tests.add(new Pair<>(
            new GeoCoordinateBoundingBox2d(
                    new GeoCoordinate2d(new Longitude(+0.0), new Latitude(-90.0)),
                    new GeoCoordinate2d(new Longitude(+45.0), new Latitude(-45.1))),
            "262152"));
    tests.add(new Pair<>(
            new GeoCoordinateBoundingBox2d(
                    new GeoCoordinate2d(new Longitude(+45.1), new Latitude(-90.0)),
                    new GeoCoordinate2d(new Longitude(+90.0), new Latitude(-45.1))),
            "262153"));
    tests.add(new Pair<>(
            new GeoCoordinateBoundingBox2d(
                    new GeoCoordinate2d(new Longitude(+90.1), new Latitude(-90.0)),
                    new GeoCoordinate2d(new Longitude(+135.0), new Latitude(-45.1))),
            "262156"));
    tests.add(new Pair<>(
            new GeoCoordinateBoundingBox2d(
                    new GeoCoordinate2d(new Longitude(+135.1), new Latitude(-90.0)),
                    new GeoCoordinate2d(new Longitude(+180.0), new Latitude(-45.1))),
            "262157"));
    tests.add(new Pair<>(
            new GeoCoordinateBoundingBox2d(
                    new GeoCoordinate2d(new Longitude(-180.0), new Latitude(-45.0)),
                    new GeoCoordinate2d(new Longitude(-135.1), new Latitude(-0.1))),
            "262170"));
    tests.add(new Pair<>(
            new GeoCoordinateBoundingBox2d(
                    new GeoCoordinate2d(new Longitude(-135.0), new Latitude(-45.0)),
                    new GeoCoordinate2d(new Longitude(-90.1), new Latitude(-0.1))),
            "262171"));
    tests.add(new Pair<>(
            new GeoCoordinateBoundingBox2d(
                    new GeoCoordinate2d(new Longitude(-90.0), new Latitude(-45.0)),
                    new GeoCoordinate2d(new Longitude(-45.1), new Latitude(-0.1))),
            "262174"));
    tests.add(new Pair<>(
            new GeoCoordinateBoundingBox2d(
                    new GeoCoordinate2d(new Longitude(-45.0), new Latitude(-45.0)),
                    new GeoCoordinate2d(new Longitude(-0.1), new Latitude(-0.1))),
            "262175"));
    tests.add(new Pair<>(
            new GeoCoordinateBoundingBox2d(
                    new GeoCoordinate2d(new Longitude(+0.0), new Latitude(-45.0)),
                    new GeoCoordinate2d(new Longitude(+45.0), new Latitude(-0.1))),
            "262154"));
    tests.add(new Pair<>(
            new GeoCoordinateBoundingBox2d(
                    new GeoCoordinate2d(new Longitude(+45.1), new Latitude(-45.0)),
                    new GeoCoordinate2d(new Longitude(+90.0), new Latitude(-0.1))),
            "262155"));
    tests.add(new Pair<>(
            new GeoCoordinateBoundingBox2d(
                    new GeoCoordinate2d(new Longitude(+90.1), new Latitude(-45.0)),
                    new GeoCoordinate2d(new Longitude(+135.0), new Latitude(-0.1))),
            "262158"));
    tests.add(new Pair<>(
            new GeoCoordinateBoundingBox2d(
                    new GeoCoordinate2d(new Longitude(+135.1), new Latitude(-45.0)),
                    new GeoCoordinate2d(new Longitude(+180.0), new Latitude(-0.1))),
            "262159"));
    tests.add(new Pair<>(
            new GeoCoordinateBoundingBox2d(
                    new GeoCoordinate2d(new Longitude(-180.0), new Latitude(+0.0)),
                    new GeoCoordinate2d(new Longitude(-135.1), new Latitude(+45.0))),
            "262160"));
    tests.add(new Pair<>(
            new GeoCoordinateBoundingBox2d(
                    new GeoCoordinate2d(new Longitude(-135.0), new Latitude(+0.0)),
                    new GeoCoordinate2d(new Longitude(-90.1), new Latitude(+45.0))),
            "262161"));
    tests.add(new Pair<>(
            new GeoCoordinateBoundingBox2d(
                    new GeoCoordinate2d(new Longitude(-90.0), new Latitude(+0.0)),
                    new GeoCoordinate2d(new Longitude(-45.1), new Latitude(+45.0))),
            "262164"));
    tests.add(new Pair<>(
            new GeoCoordinateBoundingBox2d(
                    new GeoCoordinate2d(new Longitude(-45.0), new Latitude(+0.0)),
                    new GeoCoordinate2d(new Longitude(-0.1), new Latitude(+45.0))),
            "262165"));
    tests.add(new Pair<>(
            new GeoCoordinateBoundingBox2d(
                    new GeoCoordinate2d(new Longitude(+0.0), new Latitude(+0.0)),
                    new GeoCoordinate2d(new Longitude(+45.0), new Latitude(+45.0))),
            "262144"));
    tests.add(new Pair<>(
            new GeoCoordinateBoundingBox2d(
                    new GeoCoordinate2d(new Longitude(+45.1), new Latitude(+0.0)),
                    new GeoCoordinate2d(new Longitude(+90.0), new Latitude(+45.0))),
            "262145"));
    tests.add(new Pair<>(
            new GeoCoordinateBoundingBox2d(
                    new GeoCoordinate2d(new Longitude(+90.1), new Latitude(+0.0)),
                    new GeoCoordinate2d(new Longitude(+135.0), new Latitude(+45.0))),
            "262148"));
    tests.add(new Pair<>(
            new GeoCoordinateBoundingBox2d(
                    new GeoCoordinate2d(new Longitude(+135.1), new Latitude(+0.0)),
                    new GeoCoordinate2d(new Longitude(+180.0), new Latitude(+45.0))),
            "262149"));
    tests.add(new Pair<>(
            new GeoCoordinateBoundingBox2d(
                    new GeoCoordinate2d(new Longitude(-180.0), new Latitude(+45.1)),
                    new GeoCoordinate2d(new Longitude(-135.1), new Latitude(+90.0))),
            "262162"));
    tests.add(new Pair<>(
            new GeoCoordinateBoundingBox2d(
                    new GeoCoordinate2d(new Longitude(-135.0), new Latitude(+45.1)),
                    new GeoCoordinate2d(new Longitude(-90.1), new Latitude(+90.0))),
            "262163"));
    tests.add(new Pair<>(
            new GeoCoordinateBoundingBox2d(
                    new GeoCoordinate2d(new Longitude(-90.0), new Latitude(+45.1)),
                    new GeoCoordinate2d(new Longitude(-45.1), new Latitude(+90.0))),
            "262166"));
    tests.add(new Pair<>(
            new GeoCoordinateBoundingBox2d(
                    new GeoCoordinate2d(new Longitude(-45.0), new Latitude(+45.1)),
                    new GeoCoordinate2d(new Longitude(-0.1), new Latitude(+90.0))),
            "262167"));
    tests.add(new Pair<>(
            new GeoCoordinateBoundingBox2d(
                    new GeoCoordinate2d(new Longitude(+0.0), new Latitude(+45.1)),
                    new GeoCoordinate2d(new Longitude(+45.0), new Latitude(+90.0))),
            "262146"));
    tests.add(new Pair<>(
            new GeoCoordinateBoundingBox2d(
                    new GeoCoordinate2d(new Longitude(+45.1), new Latitude(+45.1)),
                    new GeoCoordinate2d(new Longitude(+90.0), new Latitude(+90.0))),
            "262147"));
    tests.add(new Pair<>(
            new GeoCoordinateBoundingBox2d(
                    new GeoCoordinate2d(new Longitude(+90.1), new Latitude(+45.1)),
                    new GeoCoordinate2d(new Longitude(+135.0), new Latitude(+90.0))),
            "262150"));
    tests.add(new Pair<>(
            new GeoCoordinateBoundingBox2d(
                    new GeoCoordinate2d(new Longitude(+135.1), new Latitude(+45.1)),
                    new GeoCoordinate2d(new Longitude(+180.0), new Latitude(+90.0))),
            "262151"));

    for (Pair<GeoCoordinateBoundingBox2d, String> pair : tests) {
      GeoCoordinateBoundingBox2d bbox = pair.first();
      GeoCoordinate2d ll = new GeoCoordinate2d(bbox.lower_left());
      GeoCoordinate2d lr = new GeoCoordinate2d(
        bbox.upper_right().get_longitude(),
        bbox.lower_left().get_latitude());
      GeoCoordinate2d ur = new GeoCoordinate2d(bbox.upper_right());
      GeoCoordinate2d ul = new GeoCoordinate2d(
        bbox.lower_left().get_longitude(),
        bbox.upper_right().get_latitude());
      QuadKey mortonKey;
      mortonKey = QuadKey.get_key_from_longitude_latitude_at_depth(
        Type.Morton, ll, depth);
      assertEquals(pair.second(), mortonKey.to_internal_string());
      mortonKey = QuadKey.get_key_from_longitude_latitude_at_depth(
        Type.Morton, lr, depth);
      assertEquals(pair.second(), mortonKey.to_internal_string());
      mortonKey = QuadKey.get_key_from_longitude_latitude_at_depth(
        Type.Morton, ur, depth);
      assertEquals(pair.second(), mortonKey.to_internal_string());
      mortonKey = QuadKey.get_key_from_longitude_latitude_at_depth(
        Type.Morton, ul, depth);
      assertEquals(pair.second(), mortonKey.to_internal_string());
      GeoCoordinateBoundingBox2d actual =
        new GeoCoordinateBoundingBox2d();
      mortonKey.get_geo_coordinate_bounds2d(actual);
      assertTrue(ll.near(actual.lower_left(), 1));
      assertTrue(ur.near(actual.upper_right(), 1));
    }
  }

  @Test
  public void get_keys_from_longitude_latitude_bounding_boxTest() {
    List<Pair<GeoCoordinateBoundingBox2d, QuadKeysVector>> tests =
      new ArrayList<>();

    tests.add(new Pair<>(new GeoCoordinateBoundingBox2d(
            new GeoCoordinate2d(new Longitude(-180.0), new Latitude(-90.0)),
            new GeoCoordinate2d(new Longitude(-0.1), new Latitude(+90.0))),
            new QuadKeysVector()));
   tests.get(0).second().add(new QuadKey(Type.Morton, 0, 0, (short)0));
    tests.add(new Pair<>(new GeoCoordinateBoundingBox2d(
            new GeoCoordinate2d(new Longitude(+0.0), new Latitude(-90.0)),
            new GeoCoordinate2d(new Longitude(+180.0), new Latitude(+90.0))),
            new QuadKeysVector()));
   tests.get(1).second().add(new QuadKey(Type.Morton, 0, 1, (short)0));

    for (Pair<GeoCoordinateBoundingBox2d, QuadKeysVector> pair : tests) {
      QuadKeysVector actual;
      actual = QuadKey.get_keys_from_longitude_latitude_bounding_box(
        Type.Morton, pair.first(), (short)0);
      assertEquals(pair.second().size(), actual.size());
      for (int i = 0; i < actual.size(); ++i) {
        assertTrue(vectorContains(actual, pair.second().get(i)));
      }
    }

    tests = new ArrayList<>();

    tests.add(new Pair<>(new GeoCoordinateBoundingBox2d(
            new GeoCoordinate2d(new Longitude(-180.0), new Latitude(-90.0)),
            new GeoCoordinate2d(new Longitude(-0.1), new Latitude(+90.0))),
            new QuadKeysVector()));
    tests.get(0).second().add(new QuadKey(Type.Morton, 0, 0, (short)1));
    tests.get(0).second().add(new QuadKey(Type.Morton, 0, 1, (short)1));
    tests.get(0).second().add(new QuadKey(Type.Morton, 1, 0, (short)1));
    tests.get(0).second().add(new QuadKey(Type.Morton, 1, 1, (short)1));
    tests.add(new Pair<>(new GeoCoordinateBoundingBox2d(
            new GeoCoordinate2d(new Longitude(+0.0), new Latitude(-90.0)),
            new GeoCoordinate2d(new Longitude(+180.0), new Latitude(+90.0))),
            new QuadKeysVector()));
    tests.get(1).second().add(new QuadKey(Type.Morton, 0, 2, (short)1));
    tests.get(1).second().add(new QuadKey(Type.Morton, 0, 3, (short)1));
    tests.get(1).second().add(new QuadKey(Type.Morton, 1, 2, (short)1));
    tests.get(1).second().add(new QuadKey(Type.Morton, 1, 3, (short)1));
    tests.add(new Pair<>(new GeoCoordinateBoundingBox2d(
            new GeoCoordinate2d(new Longitude(-180.0), new Latitude(-90.0)),
            new GeoCoordinate2d(new Longitude(-0.1), new Latitude(-0.1))),
            new QuadKeysVector()));
    tests.get(2).second().add(new QuadKey(Type.Morton, 0, 0, (short)1));
    tests.get(2).second().add(new QuadKey(Type.Morton, 0, 1, (short)1));
    tests.add(new Pair<>(new GeoCoordinateBoundingBox2d(
            new GeoCoordinate2d(new Longitude(-180.0), new Latitude(+0.0)),
            new GeoCoordinate2d(new Longitude(-0.1), new Latitude(+90.0))),
            new QuadKeysVector()));
    tests.get(3).second().add(new QuadKey(Type.Morton, 1, 0, (short)1));
    tests.get(3).second().add(new QuadKey(Type.Morton, 1, 1, (short)1));
    tests.add(new Pair<>(new GeoCoordinateBoundingBox2d(
            new GeoCoordinate2d(new Longitude(+0.0), new Latitude(-90.0)),
            new GeoCoordinate2d(new Longitude(+180.0), new Latitude(-0.1))),
            new QuadKeysVector()));
    tests.get(4).second().add(new QuadKey(Type.Morton, 0, 2, (short)1));
    tests.get(4).second().add(new QuadKey(Type.Morton, 0, 3, (short)1));
    tests.add(new Pair<>(new GeoCoordinateBoundingBox2d(
            new GeoCoordinate2d(new Longitude(+0.0), new Latitude(+0.0)),
            new GeoCoordinate2d(new Longitude(+180.0), new Latitude(+90.0))),
            new QuadKeysVector()));
    tests.get(5).second().add(new QuadKey(Type.Morton, 1, 2, (short)1));
    tests.get(5).second().add(new QuadKey(Type.Morton, 1, 3, (short)1));
    tests.add(new Pair<>(new GeoCoordinateBoundingBox2d(
            new GeoCoordinate2d(new Longitude(-180.0), new Latitude(-90.0)),
            new GeoCoordinate2d(new Longitude(-90.1), new Latitude(-0.1))),
            new QuadKeysVector()));
    tests.get(6).second().add(new QuadKey(Type.Morton, 0, 0, (short)1));
    tests.add(new Pair<>(new GeoCoordinateBoundingBox2d(
            new GeoCoordinate2d(new Longitude(-90.0), new Latitude(-90.0)),
            new GeoCoordinate2d(new Longitude(-0.1), new Latitude(-0.1))),
            new QuadKeysVector()));
    tests.get(7).second().add(new QuadKey(Type.Morton, 0, 1, (short)1));
    tests.add(new Pair<>(new GeoCoordinateBoundingBox2d(
            new GeoCoordinate2d(new Longitude(+0.0), new Latitude(-90.0)),
            new GeoCoordinate2d(new Longitude(+90.0), new Latitude(-0.1))),
            new QuadKeysVector()));
    tests.get(8).second().add(new QuadKey(Type.Morton, 0, 2, (short)1));
    tests.add(new Pair<>(new GeoCoordinateBoundingBox2d(
            new GeoCoordinate2d(new Longitude(+90.1), new Latitude(-90.0)),
            new GeoCoordinate2d(new Longitude(+180.0), new Latitude(-0.1))),
            new QuadKeysVector()));
    tests.get(9).second().add(new QuadKey(Type.Morton, 0, 3, (short)1));
    tests.add(new Pair<>(new GeoCoordinateBoundingBox2d(
            new GeoCoordinate2d(new Longitude(-180.0), new Latitude(+0.0)),
            new GeoCoordinate2d(new Longitude(-90.1), new Latitude(+90.0))),
            new QuadKeysVector()));
    tests.get(10).second().add(new QuadKey(Type.Morton, 1, 0, (short)1));
    tests.add(new Pair<>(new GeoCoordinateBoundingBox2d(
            new GeoCoordinate2d(new Longitude(-90.0), new Latitude(+0.0)),
            new GeoCoordinate2d(new Longitude(-0.1), new Latitude(+90.0))),
            new QuadKeysVector()));
    tests.get(11).second().add(new QuadKey(Type.Morton, 1, 1, (short)1));
    tests.add(new Pair<>(new GeoCoordinateBoundingBox2d(
            new GeoCoordinate2d(new Longitude(+0.0), new Latitude(+0.0)),
            new GeoCoordinate2d(new Longitude(+90.0), new Latitude(+90.0))),
            new QuadKeysVector()));
    tests.get(12).second().add(new QuadKey(Type.Morton, 1, 2, (short)1));
    tests.add(new Pair<>(new GeoCoordinateBoundingBox2d(
            new GeoCoordinate2d(new Longitude(+90.1), new Latitude(+0.0)),
            new GeoCoordinate2d(new Longitude(+180.0), new Latitude(+90.0))),
            new QuadKeysVector()));
    tests.get(13).second().add(new QuadKey(Type.Morton, 1, 3, (short)1));

    for (Pair<GeoCoordinateBoundingBox2d, QuadKeysVector> pair : tests) {
      QuadKeysVector actual;
      actual = QuadKey.get_keys_from_longitude_latitude_bounding_box(
        Type.Morton, pair.first(), (short)1);
      assertEquals(pair.second().size(), actual.size());
      for (int i = 0; i < actual.size(); ++i) {
        assertTrue(vectorContains(actual, pair.second().get(i)));
      }
    }

    {
      Pair<GeoCoordinateBoundingBox2d, QuadKeysVector> test = new Pair<>(
              new GeoCoordinateBoundingBox2d(
                      new GeoCoordinate2d(new Longitude(-140.0), new Latitude(-48.0)),
                      new GeoCoordinate2d(new Longitude(+10.0), new Latitude(+39.0))),
              new QuadKeysVector());
      test.second().add(new QuadKey(Type.Morton, 0, 0, (short)2));
      test.second().add(new QuadKey(Type.Morton, 0, 1, (short)2));
      test.second().add(new QuadKey(Type.Morton, 0, 2, (short)2));
      test.second().add(new QuadKey(Type.Morton, 0, 3, (short)2));
      test.second().add(new QuadKey(Type.Morton, 0, 4, (short)2));
      test.second().add(new QuadKey(Type.Morton, 1, 0, (short)2));
      test.second().add(new QuadKey(Type.Morton, 1, 1, (short)2));
      test.second().add(new QuadKey(Type.Morton, 1, 2, (short)2));
      test.second().add(new QuadKey(Type.Morton, 1, 3, (short)2));
      test.second().add(new QuadKey(Type.Morton, 1, 4, (short)2));
      test.second().add(new QuadKey(Type.Morton, 2, 0, (short)2));
      test.second().add(new QuadKey(Type.Morton, 2, 1, (short)2));
      test.second().add(new QuadKey(Type.Morton, 2, 2, (short)2));
      test.second().add(new QuadKey(Type.Morton, 2, 3, (short)2));
      test.second().add(new QuadKey(Type.Morton, 2, 4, (short)2));

      QuadKeysVector actual;
      actual = QuadKey.get_keys_from_longitude_latitude_bounding_box(
        Type.Morton, test.first(), (short)2);
      assertEquals(test.second().size(), actual.size());
      for (int i = 0; i < actual.size(); ++i) {
        assertTrue(vectorContains(actual, test.second().get(i)));
      }
    }
  }

  @Test
  public void selecetedCitiesTest() {
    {
      Pair<Short, GeoCoordinate2d> data = new Pair<>((short) 13,
              new GeoCoordinate2d(new Longitude(+2.29450000000000),
                      new Latitude(+48.85822200000000)));
      int tile = 8428778 | (1 << (data.first() + 16));
      String ss = "" + tile;
      QuadKey mortonQuadKey =
        QuadKey.get_key_from_longitude_latitude_at_depth(
          Type.Morton, data.second(), data.first());
      assertEquals(ss, mortonQuadKey.to_internal_string());
    }
    {
      Pair<Short, GeoCoordinate2d> data = new Pair<>((short) 13,
              new GeoCoordinate2d(new Longitude(-74.04444400000000),
                      new Latitude(+40.68916700000000)));
      int tile = 86924190 | (1 << (data.first() + 16));
      String ss = "" + tile;
      QuadKey mortonQuadKey =
        QuadKey.get_key_from_longitude_latitude_at_depth(Type.Morton,
          data.second(), data.first());
      assertEquals(ss, mortonQuadKey.to_internal_string());
    }
    {
      Pair<Short, GeoCoordinate2d> data = new Pair<>((short) 13,
              new GeoCoordinate2d(new Longitude(-43.15744400000000),
                      new Latitude(-22.94865800000000)));
      int tile = 130726287 | (1 << (data.first() + 16));
      String ss = "" + tile;
      QuadKey mortonQuadKey =
        QuadKey.get_key_from_longitude_latitude_at_depth(
          Type.Morton, data.second(), data.first());
      assertEquals(ss, mortonQuadKey.to_internal_string());
    }
    {
      Pair<Short, GeoCoordinate2d> data = new Pair<>((short) 13,
              new GeoCoordinate2d(new Longitude(+151.21527800000000),
                      new Latitude(-33.85611100000000)));
      int tile = 63372939 | (1 << (data.first() + 16));
      String ss = "" + tile;
      QuadKey mortonQuadKey =
        QuadKey.get_key_from_longitude_latitude_at_depth(
          Type.Morton, data.second(), data.first());
      assertEquals(ss, mortonQuadKey.to_internal_string());
    }
    {
      Pair<Short, GeoCoordinate2d> data = new Pair<>((short) 13,
              new GeoCoordinate2d(new Longitude(+0.00000000000000),
                      new Latitude(+51.50300000000000)));
      int tile = 8521770 | (1 << (data.first() + 16));
      String ss = "" + tile;
      QuadKey mortonQuadKey = QuadKey.get_key_from_longitude_latitude_at_depth(
      Type.Morton, data.second(), data.first());
      assertEquals(ss, mortonQuadKey.to_internal_string());
    }
    {
      Pair<Short, GeoCoordinate2d> data = new Pair<>((short) 13,
              new GeoCoordinate2d(new Longitude(-78.45000000000000),
                      new Latitude(+0.00000000000000)));
      int tile = 84148305 | (1 << (data.first() + 16));
      String ss = "" + tile;
      QuadKey mortonQuadKey =
        QuadKey.get_key_from_longitude_latitude_at_depth(
          Type.Morton, data.second(), data.first());
      assertEquals(ss, mortonQuadKey.to_internal_string());
    }
    {
      Pair<Short, GeoCoordinate2d> data = new Pair<>((short) 10,
              new GeoCoordinate2d(new Longitude(+2.29450000000000),
                      new Latitude(+48.85822200000000)));
      int tile = 131699 | (1 << (16 + data.first()));
      String ss = "" + tile;
      QuadKey mortonQuadKey =
        QuadKey.get_key_from_longitude_latitude_at_depth(
          Type.Morton, data.second(), data.first());
      assertEquals(ss, mortonQuadKey.to_internal_string());
    }
    {
      Pair<Short, GeoCoordinate2d> data = new Pair<>((short) 10,
              new GeoCoordinate2d(new Longitude(-74.04444400000000),
                      new Latitude(+40.68916700000000)));
      int tile = 1358190 | (1 << (16 + data.first()));
      String ss = "" + tile;
      QuadKey mortonQuadKey =
        QuadKey.get_key_from_longitude_latitude_at_depth(
          Type.Morton, data.second(), data.first());
      assertEquals(ss, mortonQuadKey.to_internal_string());
    }
    {
      Pair<Short, GeoCoordinate2d> data = new Pair<>((short) 10,
              new GeoCoordinate2d(new Longitude(-43.15744400000000),
                      new Latitude(-22.94865800000000)));
      int tile = 2042598 | (1 << (16 + data.first()));
      String ss = "" + tile;
      QuadKey mortonQuadKey =
        QuadKey.get_key_from_longitude_latitude_at_depth(
          Type.Morton, data.second(), data.first());
      assertEquals(ss, mortonQuadKey.to_internal_string());
    }
    {
      Pair<Short, GeoCoordinate2d> data = new Pair<>((short) 10,
              new GeoCoordinate2d(new Longitude(+151.21527800000000),
                      new Latitude(-33.85611100000000)));
      int tile = 990202 | (1 << (16 + data.first()));
      String ss = "" + tile;
      QuadKey mortonQuadKey =
        QuadKey.get_key_from_longitude_latitude_at_depth(
          Type.Morton, data.second(), data.first());
      assertEquals(ss, mortonQuadKey.to_internal_string());
    }
    {
      Pair<Short, GeoCoordinate2d> data = new Pair<>((short) 10,
              new GeoCoordinate2d(new Longitude(+0.00000000000000),
                      new Latitude(+51.50300000000000)));
      int tile = 133152 | (1 << (16 + data.first()));
      String ss = "" + tile;
      QuadKey mortonQuadKey =
        QuadKey.get_key_from_longitude_latitude_at_depth(
          Type.Morton, data.second(), data.first());
      assertEquals(ss, mortonQuadKey.to_internal_string());
    }
    {
      Pair<Short, GeoCoordinate2d> data = new Pair<>((short) 10,
              new GeoCoordinate2d(new Longitude(-78.45000000000000),
                      new Latitude(+0.00000000000000)));
      int tile = 1314817 | (1 << (16 + data.first()));
      String ss = "" + tile;
      QuadKey mortonQuadKey =
        QuadKey.get_key_from_longitude_latitude_at_depth(
          Type.Morton, data.second(), data.first());
      assertEquals(ss, mortonQuadKey.to_internal_string());
    }
  }
}

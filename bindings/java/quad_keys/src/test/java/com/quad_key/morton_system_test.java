import com.quad_key.*;
import org.junit.BeforeClass;
import org.junit.Test;

import java.util.ArrayList;
import java.util.List;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertTrue;

public class morton_system_test {

  private class Pair<X, Y> {
    private X m_X;
    private Y m_Y;

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
    // See test_quad_key TestSpecificCtorTest.
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
      quad_key quadKey = new quad_key(type.morton, 0, 1, (short)1);
      quad_key ancestor = new quad_key(type.morton, 0, 0, (short)0);
      assertTrue(ancestor.equal_to(quadKey.get_ancestor((short)1)));
      assertTrue(quadKey.get_parent().equal_to(quadKey.get_ancestor(
        (short)1)));
    }
    {
      quad_key quadKey = new quad_key(type.morton, 0, 0, (short)1);
      quad_key ancestor = new quad_key(type.morton, 0, 0, (short)0);
      assertTrue(ancestor.equal_to(quadKey.get_ancestor((short)1)));
      assertTrue(quadKey.get_parent().equal_to(quadKey.get_ancestor(
        (short)1)));
    }
    {
      quad_key quadKey = new quad_key(type.morton, 1, 1, (short)1);
      quad_key ancestor = new quad_key(type.morton, 0, 0, (short)0);
      assertTrue(ancestor.equal_to(quadKey.get_ancestor((short)1)));
    }
    {
      quad_key quadKey = new quad_key(type.morton, 1, 2, (short)1);
      quad_key ancestor = new quad_key(type.morton, 0, 1, (short)0);
      assertTrue(ancestor.equal_to(quadKey.get_ancestor((short)1)));
    }
    {
      quad_key quadKey = new quad_key(type.morton, 0, 2, (short)1);
      quad_key ancestor = new quad_key(type.morton, 0, 1, (short)0);
      assertTrue(ancestor.equal_to(quadKey.get_ancestor((short)1)));
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
    quad_key_vector testKeys;
    testKeys = new quad_key(type.morton, 0, 0, (short)1).get_siblings();
    assertEquals(3, testKeys.size());
    assertTrue(vectorContains(testKeys,
      new quad_key(type.morton, 1, 0, (short)1)));
    assertTrue(vectorContains(testKeys,
      new quad_key(type.morton, 1, 1, (short)1)));
    assertTrue(vectorContains(testKeys,
      new quad_key(type.morton, 0, 1, (short)1)));
    testKeys = new quad_key(type.morton, 1, 3, (short)1).get_siblings();
    assertEquals(3, testKeys.size());
    assertTrue(vectorContains(testKeys,
      new quad_key(type.morton, 1, 2, (short)1)));
    assertTrue(vectorContains(testKeys,
      new quad_key(type.morton, 0, 2, (short)1)));
    assertTrue(vectorContains(testKeys,
      new quad_key(type.morton, 0, 3, (short)1)));
  }

  @Test
  public void get_neighbors_test() {
    // Same as bing_system but just to be safe
    quad_key_vector testKeys;
    testKeys = new quad_key().get_neighbors();
    assertTrue(testKeys.isEmpty());

    testKeys = new quad_key(type.morton, 0, 0, (short)2).get_neighbors();
    assertEquals(5, testKeys.size());
    assertTrue(vectorContains(testKeys,
      new quad_key(type.morton, 0, 1, (short)2)));
    assertTrue(vectorContains(testKeys,
      new quad_key(type.morton, 1, 1, (short)2)));
    assertTrue(vectorContains(testKeys,
      new quad_key(type.morton, 1, 0, (short)2)));
    assertTrue(vectorContains(testKeys,
      new quad_key(type.morton, 0, 7, (short)2)));
    assertTrue(vectorContains(testKeys,
      new quad_key(type.morton, 1, 7, (short)2)));

    testKeys = new quad_key(type.morton, 0, 1, (short)2).get_neighbors();
    assertEquals(5, testKeys.size());
    assertTrue(vectorContains(testKeys,
      new quad_key(type.morton, 0, 0, (short)2)));
    assertTrue(vectorContains(testKeys,
      new quad_key(type.morton, 1, 0, (short)2)));
    assertTrue(vectorContains(testKeys,
      new quad_key(type.morton, 1, 1, (short)2)));
    assertTrue(vectorContains(testKeys,
      new quad_key(type.morton, 1, 2, (short)2)));
    assertTrue(vectorContains(testKeys,
      new quad_key(type.morton, 0, 2, (short)2)));

    testKeys = new quad_key(type.morton, 0, 2, (short)2).get_neighbors();
    assertEquals(5, testKeys.size());
    assertTrue(vectorContains(testKeys,
      new quad_key(type.morton, 0, 1, (short)2)));
    assertTrue(vectorContains(testKeys,
      new quad_key(type.morton, 1, 1, (short)2)));
    assertTrue(vectorContains(testKeys,
      new quad_key(type.morton, 1, 2, (short)2)));
    assertTrue(vectorContains(testKeys,
      new quad_key(type.morton, 1, 3, (short)2)));
    assertTrue(vectorContains(testKeys,
      new quad_key(type.morton, 0, 3, (short)2)));

    testKeys = new quad_key(type.morton, 0, 3, (short)2).get_neighbors();
    assertEquals(5, testKeys.size());
    assertTrue(vectorContains(testKeys,
      new quad_key(type.morton, 0, 2, (short)2)));
    assertTrue(vectorContains(testKeys,
      new quad_key(type.morton, 1, 2, (short)2)));
    assertTrue(vectorContains(testKeys,
      new quad_key(type.morton, 1, 3, (short)2)));
    assertTrue(vectorContains(testKeys,
      new quad_key(type.morton, 1, 4, (short)2)));
    assertTrue(vectorContains(testKeys,
      new quad_key(type.morton, 0, 4, (short)2)));

    testKeys = new quad_key(type.morton, 0, 0, (short)2).get_neighbors();
    assertEquals(5, testKeys.size());
    assertTrue(vectorContains(testKeys,
      new quad_key(type.morton, 0, 1, (short)2)));
    assertTrue(vectorContains(testKeys,
      new quad_key(type.morton, 1, 1, (short)2)));
    assertTrue(vectorContains(testKeys,
      new quad_key(type.morton, 1, 0, (short)2)));
    assertTrue(vectorContains(testKeys,
      new quad_key(type.morton, 1, 7, (short)2)));
    assertTrue(vectorContains(testKeys,
      new quad_key(type.morton, 0, 7, (short)2)));

    testKeys = new quad_key(type.morton, 3, 1, (short)2).get_neighbors();
    assertEquals(5, testKeys.size());
    assertTrue(vectorContains(testKeys,
      new quad_key(type.morton, 3, 0, (short)2)));
    assertTrue(vectorContains(testKeys,
      new quad_key(type.morton, 2, 0, (short)2)));
    assertTrue(vectorContains(testKeys,
      new quad_key(type.morton, 2, 1, (short)2)));
    assertTrue(vectorContains(testKeys,
      new quad_key(type.morton, 2, 2, (short)2)));
    assertTrue(vectorContains(testKeys,
      new quad_key(type.morton, 3, 2, (short)2)));

    testKeys = new quad_key(type.morton, 3, 2, (short)2).get_neighbors();
    assertEquals(5, testKeys.size());
    assertTrue(vectorContains(testKeys,
      new quad_key(type.morton, 3, 1, (short)2)));
    assertTrue(vectorContains(testKeys,
      new quad_key(type.morton, 2, 1, (short)2)));
    assertTrue(vectorContains(testKeys,
      new quad_key(type.morton, 2, 2, (short)2)));
    assertTrue(vectorContains(testKeys,
      new quad_key(type.morton, 2, 3, (short)2)));
    assertTrue(vectorContains(testKeys,
      new quad_key(type.morton, 3, 3, (short)2)));

    testKeys = new quad_key(type.morton, 3, 3, (short)2).get_neighbors();
    assertEquals(5, testKeys.size());
    assertTrue(vectorContains(testKeys,
      new quad_key(type.morton, 3, 2, (short)2)));
    assertTrue(vectorContains(testKeys,
      new quad_key(type.morton, 2, 2, (short)2)));
    assertTrue(vectorContains(testKeys,
      new quad_key(type.morton, 2, 3, (short)2)));
    assertTrue(vectorContains(testKeys,
      new quad_key(type.morton, 2, 4, (short)2)));
    assertTrue(vectorContains(testKeys,
      new quad_key(type.morton, 3, 4, (short)2)));

    testKeys = new quad_key(type.morton, 4, 7, (short)3).get_neighbors();
    assertEquals(8, testKeys.size());
    assertTrue(vectorContains(testKeys,
      new quad_key(type.morton, 3, 7, (short)3)));
    assertTrue(vectorContains(testKeys,
      new quad_key(type.morton, 3, 6, (short)3)));
    assertTrue(vectorContains(testKeys,
      new quad_key(type.morton, 4, 6, (short)3)));
    assertTrue(vectorContains(testKeys,
      new quad_key(type.morton, 5, 6, (short)3)));
    assertTrue(vectorContains(testKeys,
      new quad_key(type.morton, 5, 7, (short)3)));
    assertTrue(vectorContains(testKeys,
      new quad_key(type.morton, 5, 8, (short)3)));
    assertTrue(vectorContains(testKeys,
      new quad_key(type.morton, 4, 8, (short)3)));
    assertTrue(vectorContains(testKeys,
      new quad_key(type.morton, 3, 8, (short)3)));

    testKeys = new quad_key(type.morton, 4, 0, (short)3).get_neighbors();
    assertEquals(8, testKeys.size());
    assertTrue(vectorContains(testKeys,
      new quad_key(type.morton, 3, 0, (short)3)));
    assertTrue(vectorContains(testKeys,
      new quad_key(type.morton, 3, 1, (short)3)));
    assertTrue(vectorContains(testKeys,
      new quad_key(type.morton, 4, 1, (short)3)));
    assertTrue(vectorContains(testKeys,
      new quad_key(type.morton, 5, 1, (short)3)));
    assertTrue(vectorContains(testKeys,
      new quad_key(type.morton, 5, 0, (short)3)));
    assertTrue(vectorContains(testKeys,
      new quad_key(type.morton, 5, 15, (short)3)));
    assertTrue(vectorContains(testKeys,
      new quad_key(type.morton, 4, 15, (short)3)));
    assertTrue(vectorContains(testKeys,
      new quad_key(type.morton, 3, 15, (short)3)));

    testKeys = new quad_key(type.morton, 0, 0, (short)0).get_neighbors();
    assertEquals(0, testKeys.size());
  }

  @Test
  public void from_string_to_string_test() {
    // X ==> Unused
    // O ==> Used but never set
    // (0,1) ==> Binary digits
    quad_key quadKey = new quad_key(type.morton, 0, 0, (short)0);
    String fmt = quadKey.to_internal_string();
    assertEquals("65537", fmt); // XXXX XXXX XXXX XXX1 XXXX XXXX XXXX XXO1
    quad_key quadKeyBack = quad_key.from_internal_string(type.morton, fmt);
    assertTrue(quadKey.equal_to(quadKeyBack));
    quadKey = new quad_key(type.morton, 0, 1, (short)0);
    fmt = quadKey.to_internal_string();
    assertEquals("65536", fmt); // XXXX XXXX XXXX XXX1 XXXX XXXX XXXX XXO0
    quadKeyBack = quad_key.from_internal_string(type.morton, fmt);
    assertTrue(quadKey.equal_to(quadKeyBack));
    quadKey = new quad_key(type.morton, 0, 0, (short)1);
    fmt = quadKey.to_internal_string();
    assertEquals("131078", fmt); // XXXX XXXX XXXX XX1X XXXX XXXX XXXX O110
    quadKeyBack = quad_key.from_internal_string(type.morton, fmt);
    assertTrue(quadKey.equal_to(quadKeyBack));
    quadKey = new quad_key(type.morton, 0, 1, (short)1);
    fmt = quadKey.to_internal_string();
    assertEquals("131079", fmt); // XXXX XXXX XXXX XX1O OOOO OOOO OOOO O111
    quadKeyBack = quad_key.from_internal_string(type.morton, fmt);
    assertTrue(quadKey.equal_to(quadKeyBack));
    quadKey = new quad_key(type.morton, 0, 2, (short)1);
    fmt = quadKey.to_internal_string();
    assertEquals("131074", fmt); // XXXX XXXX XXXX XX1X XXXX XXXX XXXX O010
    quadKeyBack = quad_key.from_internal_string(type.morton, fmt);
    assertTrue(quadKey.equal_to(quadKeyBack));
    quadKey = new quad_key(type.morton, 0, 3, (short)1);
    fmt = quadKey.to_internal_string();
    assertEquals("131075", fmt); // XXXX XXXX XXXX XX1X XXXX XXXX XXXX O011
    quadKeyBack = quad_key.from_internal_string(type.morton, fmt);
    assertTrue(quadKey.equal_to(quadKeyBack));
    quadKey = new quad_key(type.morton, 1, 0, (short)1);
    fmt = quadKey.to_internal_string();
    assertEquals("131076", fmt); // XXXX XXXX XXXX XX1X XXXX XXXX XXXX O100
    quadKeyBack = quad_key.from_internal_string(type.morton, fmt);
    assertTrue(quadKey.equal_to(quadKeyBack));
    quadKey = new quad_key(type.morton, 1, 1, (short)1);
    fmt = quadKey.to_internal_string();
    assertEquals("131077", fmt); // XXXX XXXX XXXX XX1X XXXX XXXX XXXX O101
    quadKeyBack = quad_key.from_internal_string(type.morton, fmt);
    assertTrue(quadKey.equal_to(quadKeyBack));
    quadKey = new quad_key(type.morton, 1, 2, (short)1);
    fmt = quadKey.to_internal_string();
    assertEquals("131072", fmt); // XXXX XXXX XXXX XX1X XXXX XXXX XXXX O000
    quadKeyBack = quad_key.from_internal_string(type.morton, fmt);
    assertTrue(quadKey.equal_to(quadKeyBack));
    quadKey = new quad_key(type.morton, 1, 3, (short)1);
    fmt = quadKey.to_internal_string();
    assertEquals("131073", fmt); // XXXX XXXX XXXX XX1X XXXX XXXX XXXX O001
    quadKeyBack = quad_key.from_internal_string(type.morton, fmt);
    assertTrue(quadKey.equal_to(quadKeyBack));
    quadKey = new quad_key(type.morton, 0, 0, (short)2);
    fmt = quadKey.to_internal_string();
    assertEquals("262168", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO1 1000
    quadKeyBack = quad_key.from_internal_string(type.morton, fmt);
    assertTrue(quadKey.equal_to(quadKeyBack));
    quadKey = new quad_key(type.morton, 0, 1, (short)2);
    fmt = quadKey.to_internal_string();
    assertEquals("262169", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO1 1001
    quadKeyBack = quad_key.from_internal_string(type.morton, fmt);
    assertTrue(quadKey.equal_to(quadKeyBack));
    quadKey = new quad_key(type.morton, 0, 2, (short)2);
    fmt = quadKey.to_internal_string();
    assertEquals("262172", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO1 1100
    quadKeyBack = quad_key.from_internal_string(type.morton, fmt);
    assertTrue(quadKey.equal_to(quadKeyBack));
    quadKey = new quad_key(type.morton, 0, 3, (short)2);
    fmt = quadKey.to_internal_string();
    assertEquals("262173", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO1 1101
    quadKeyBack = quad_key.from_internal_string(type.morton, fmt);
    assertTrue(quadKey.equal_to(quadKeyBack));
    quadKey = new quad_key(type.morton, 0, 4, (short)2);
    fmt = quadKey.to_internal_string();
    assertEquals("262152", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO0 1000
    quadKeyBack = quad_key.from_internal_string(type.morton, fmt);
    assertTrue(quadKey.equal_to(quadKeyBack));
    quadKey = new quad_key(type.morton, 0, 5, (short)2);
    fmt = quadKey.to_internal_string();
    assertEquals("262153", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO0 1001
    quadKeyBack = quad_key.from_internal_string(type.morton, fmt);
    assertTrue(quadKey.equal_to(quadKeyBack));
    quadKey = new quad_key(type.morton, 0, 6, (short)2);
    fmt = quadKey.to_internal_string();
    assertEquals("262156", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO0 1100
    quadKeyBack = quad_key.from_internal_string(type.morton, fmt);
    assertTrue(quadKey.equal_to(quadKeyBack));
    quadKey = new quad_key(type.morton, 0, 7, (short)2);
    fmt = quadKey.to_internal_string();
    assertEquals("262157", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO0 1101
    quadKeyBack = quad_key.from_internal_string(type.morton, fmt);
    assertTrue(quadKey.equal_to(quadKeyBack));
    quadKey = new quad_key(type.morton, 1, 0, (short)2);
    fmt = quadKey.to_internal_string();
    assertEquals("262170", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO1 1010
    quadKeyBack = quad_key.from_internal_string(type.morton, fmt);
    assertTrue(quadKey.equal_to(quadKeyBack));
    quadKey = new quad_key(type.morton, 1, 1, (short)2);
    fmt = quadKey.to_internal_string();
    assertEquals("262171", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO1 1011
    quadKeyBack = quad_key.from_internal_string(type.morton, fmt);
    assertTrue(quadKey.equal_to(quadKeyBack));
    quadKey = new quad_key(type.morton, 1, 2, (short)2);
    fmt = quadKey.to_internal_string();
    assertEquals("262174", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO1 1110
    quadKeyBack = quad_key.from_internal_string(type.morton, fmt);
    assertTrue(quadKey.equal_to(quadKeyBack));
    quadKey = new quad_key(type.morton, 1, 3, (short)2);
    fmt = quadKey.to_internal_string();
    assertEquals("262175", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO1 1111
    quadKeyBack = quad_key.from_internal_string(type.morton, fmt);
    assertTrue(quadKey.equal_to(quadKeyBack));
    quadKey = new quad_key(type.morton, 1, 4, (short)2);
    fmt = quadKey.to_internal_string();
    assertEquals("262154", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO0 1010
    quadKeyBack = quad_key.from_internal_string(type.morton, fmt);
    assertTrue(quadKey.equal_to(quadKeyBack));
    quadKey = new quad_key(type.morton, 1, 5, (short)2);
    fmt = quadKey.to_internal_string();
    assertEquals("262155", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO0 1011
    quadKeyBack = quad_key.from_internal_string(type.morton, fmt);
    assertTrue(quadKey.equal_to(quadKeyBack));
    quadKey = new quad_key(type.morton, 1, 6, (short)2);
    fmt = quadKey.to_internal_string();
    assertEquals("262158", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO0 1110
    quadKeyBack = quad_key.from_internal_string(type.morton, fmt);
    assertTrue(quadKey.equal_to(quadKeyBack));
    quadKey = new quad_key(type.morton, 1, 7, (short)2);
    fmt = quadKey.to_internal_string();
    assertEquals("262159", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO0 1111
    quadKeyBack = quad_key.from_internal_string(type.morton, fmt);
    assertTrue(quadKey.equal_to(quadKeyBack));
    quadKey = new quad_key(type.morton, 2, 0, (short)2);
    fmt = quadKey.to_internal_string();
    assertEquals("262160", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO1 0000
    quadKeyBack = quad_key.from_internal_string(type.morton, fmt);
    assertTrue(quadKey.equal_to(quadKeyBack));
    quadKey = new quad_key(type.morton, 2, 1, (short)2);
    fmt = quadKey.to_internal_string();
    assertEquals("262161", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO1 0001
    quadKeyBack = quad_key.from_internal_string(type.morton, fmt);
    assertTrue(quadKey.equal_to(quadKeyBack));
    quadKey = new quad_key(type.morton, 2, 2, (short)2);
    fmt = quadKey.to_internal_string();
    assertEquals("262164", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO1 0100
    quadKeyBack = quad_key.from_internal_string(type.morton, fmt);
    assertTrue(quadKey.equal_to(quadKeyBack));
    quadKey = new quad_key(type.morton, 2, 3, (short)2);
    fmt = quadKey.to_internal_string();
    assertEquals("262165", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO1 0101
    quadKeyBack = quad_key.from_internal_string(type.morton, fmt);
    assertTrue(quadKey.equal_to(quadKeyBack));
    quadKey = new quad_key(type.morton, 2, 4, (short)2);
    fmt = quadKey.to_internal_string();
    assertEquals("262144", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO0 0000
    quadKeyBack = quad_key.from_internal_string(type.morton, fmt);
    assertTrue(quadKey.equal_to(quadKeyBack));
    quadKey = new quad_key(type.morton, 2, 5, (short)2);
    fmt = quadKey.to_internal_string();
    assertEquals("262145", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO0 0001
    quadKeyBack = quad_key.from_internal_string(type.morton, fmt);
    assertTrue(quadKey.equal_to(quadKeyBack));
    quadKey = new quad_key(type.morton, 2, 6, (short)2);
    fmt = quadKey.to_internal_string();
    assertEquals("262148", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO0 0100
    quadKeyBack = quad_key.from_internal_string(type.morton, fmt);
    assertTrue(quadKey.equal_to(quadKeyBack));
    quadKey = new quad_key(type.morton, 2, 7, (short)2);
    fmt = quadKey.to_internal_string();
    assertEquals("262149", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO0 0101
    quadKeyBack = quad_key.from_internal_string(type.morton, fmt);
    assertTrue(quadKey.equal_to(quadKeyBack));
    quadKey = new quad_key(type.morton, 3, 0, (short)2);
    fmt = quadKey.to_internal_string();
    assertEquals("262162", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO1 0010
    quadKeyBack = quad_key.from_internal_string(type.morton, fmt);
    assertTrue(quadKey.equal_to(quadKeyBack));
    quadKey = new quad_key(type.morton, 3, 1, (short)2);
    fmt = quadKey.to_internal_string();
    assertEquals("262163", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO1 0011
    quadKeyBack = quad_key.from_internal_string(type.morton, fmt);
    assertTrue(quadKey.equal_to(quadKeyBack));
    quadKey = new quad_key(type.morton, 3, 2, (short)2);
    fmt = quadKey.to_internal_string();
    assertEquals("262166", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO1 0110
    quadKeyBack = quad_key.from_internal_string(type.morton, fmt);
    assertTrue(quadKey.equal_to(quadKeyBack));
    quadKey = new quad_key(type.morton, 3, 3, (short)2);
    fmt = quadKey.to_internal_string();
    assertEquals("262167", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO1 0111
    quadKeyBack = quad_key.from_internal_string(type.morton, fmt);
    assertTrue(quadKey.equal_to(quadKeyBack));
    quadKey = new quad_key(type.morton, 3, 4, (short)2);
    fmt = quadKey.to_internal_string();
    assertEquals("262146", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO0 0010
    quadKeyBack = quad_key.from_internal_string(type.morton, fmt);
    assertTrue(quadKey.equal_to(quadKeyBack));
    quadKey = new quad_key(type.morton, 3, 5, (short)2);
    fmt = quadKey.to_internal_string();
    assertEquals("262147", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO0 0011
    quadKeyBack = quad_key.from_internal_string(type.morton, fmt);
    assertTrue(quadKey.equal_to(quadKeyBack));
    quadKey = new quad_key(type.morton, 3, 6, (short)2);
    fmt = quadKey.to_internal_string();
    assertEquals("262150", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO0 0110
    quadKeyBack = quad_key.from_internal_string(type.morton, fmt);
    assertTrue(quadKey.equal_to(quadKeyBack));
    quadKey = new quad_key(type.morton, 3, 7, (short)2);
    fmt = quadKey.to_internal_string();
    assertEquals("262151", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO0 0111
    quadKeyBack = quad_key.from_internal_string(type.morton, fmt);
    assertTrue(quadKey.equal_to(quadKeyBack));
  }

  @Test
  public void get_geo_coordinate_bounds2d_test() {
    quad_key quadKey;
    geo_coordinate_bounding_box2d bbox = new geo_coordinate_bounding_box2d();
    quadKey = new quad_key(type.morton, 0, 0, (short)0);
    quadKey.get_geo_coordinate_bounds2d(bbox);
    assertTrue(bbox.lower_left().near(new geo_coordinate2d(
      new longitude(-180.0), new latitude(-90.0)), 1e-4));
    assertTrue(bbox.upper_right().near(new geo_coordinate2d(
      new longitude(-0.1), new latitude(+90.0)), 1e-4));

    quadKey = new quad_key(type.morton, 0, 1, (short)0);
    quadKey.get_geo_coordinate_bounds2d(bbox);
    assertTrue(bbox.lower_left().near(new geo_coordinate2d(
      new longitude(+0.0), new latitude(-90.0)), 1e-4));
    assertTrue(bbox.upper_right().near(new geo_coordinate2d(
      new longitude(+180.0), new latitude(+90.0)), 1e-4));

    quadKey = new quad_key(type.morton, 0, 0, (short)1);
    quadKey.get_geo_coordinate_bounds2d(bbox);
    assertTrue(bbox.lower_left().near(new geo_coordinate2d(
      new longitude(-180.0), new latitude(-90.0)), 1e-4));
    assertTrue(bbox.upper_right().near(new geo_coordinate2d(
      new longitude(-90.0), new latitude(+0.0)), 1e-4));

    quadKey = new quad_key(type.morton, 0, 1, (short)1);
    quadKey.get_geo_coordinate_bounds2d(bbox);
    assertTrue(bbox.lower_left().near(new geo_coordinate2d(
      new longitude(-90.0), new latitude(-90.0)), 1e-4));
    assertTrue(bbox.upper_right().near(new geo_coordinate2d(
      new longitude(+0.0), new latitude(+0.0)), 1e-4));

    quadKey = new quad_key(type.morton, 0, 2, (short)1);
    quadKey.get_geo_coordinate_bounds2d(bbox);
    assertTrue(bbox.lower_left().near(new geo_coordinate2d(
      new longitude(+0.0), new latitude(-90.0)), 1e-4));
    assertTrue(bbox.upper_right().near(new geo_coordinate2d(
      new longitude(+90.0), new latitude(+0.0)), 1e-4));

    quadKey = new quad_key(type.morton, 0, 3, (short)1);
    quadKey.get_geo_coordinate_bounds2d(bbox);
    assertTrue(bbox.lower_left().near(new geo_coordinate2d(
      new longitude(+90.0), new latitude(-90.0)), 1e-4));
    assertTrue(bbox.upper_right().near(new geo_coordinate2d(
      new longitude(+180.0), new latitude(+0.0)), 1e-4));

    quadKey = new quad_key(type.morton, 1, 0, (short)1);
    quadKey.get_geo_coordinate_bounds2d(bbox);
    assertTrue(bbox.lower_left().near(new geo_coordinate2d(
      new longitude(-180.0), new latitude(+0.0)), 1e-4));
    assertTrue(bbox.upper_right().near(new geo_coordinate2d(
      new longitude(-90.0), new latitude(+90.0)), 1e-4));

    quadKey = new quad_key(type.morton, 1, 1, (short)1);
    quadKey.get_geo_coordinate_bounds2d(bbox);
    assertTrue(bbox.lower_left().near(new geo_coordinate2d(
      new longitude(-90.0), new latitude(+0.0)), 1e-4));
    assertTrue(bbox.upper_right().near(new geo_coordinate2d(
      new longitude(+0.0), new latitude(+90.0)), 1e-4));

    quadKey = new quad_key(type.morton, 1, 2, (short)1);
    quadKey.get_geo_coordinate_bounds2d(bbox);
    assertTrue(bbox.lower_left().near(new geo_coordinate2d(
      new longitude(+0.0), new latitude(+0.0)), 1e-4));
    assertTrue(bbox.upper_right().near(new geo_coordinate2d(
      new longitude(+90.0), new latitude(+90.0)), 1e-4));

    quadKey = new quad_key(type.morton, 1, 3, (short)1);
    quadKey.get_geo_coordinate_bounds2d(bbox);
    assertTrue(bbox.lower_left().near(new geo_coordinate2d(
      new longitude(+90.0), new latitude(+0.0)), 1e-4));
    assertTrue(bbox.upper_right().near(new geo_coordinate2d(
      new longitude(+180.0), new latitude(+90.0)), 1e-4));
  }

  @Test
  public void get_key_from_longitude_latitude_at_depth_to_boumorton_test() {
    geo_coordinate2d coords;
    short depth = 0;
    { // West
      quad_key mortonKey;
      coords = new geo_coordinate2d(new longitude(-0.1), new latitude(0.0));
      mortonKey = quad_key.get_key_from_longitude_latitude_at_depth(type.morton,
        coords, depth);
      assertEquals("65537", mortonKey.to_internal_string());
      coords = new geo_coordinate2d(new longitude(-180.0), new latitude(90.0));
      mortonKey = quad_key.get_key_from_longitude_latitude_at_depth(type.morton,
        coords, depth);
      assertEquals("65537", mortonKey.to_internal_string());
      coords = new geo_coordinate2d(new longitude(-180.0), new latitude(-90.0));
      mortonKey = quad_key.get_key_from_longitude_latitude_at_depth(type.morton,
        coords, depth);
      assertEquals("65537", mortonKey.to_internal_string());
      geo_coordinate_bounding_box2d actual =
        new geo_coordinate_bounding_box2d();
      mortonKey.get_geo_coordinate_bounds2d(actual);
      assertTrue(new geo_coordinate2d(new longitude(-180.0), new latitude(-90.0)).near(actual.lower_left(), 1));
      assertTrue(new geo_coordinate2d(new longitude(-0.1), new latitude(+90.0)).near(actual.upper_right(), 1));
    }
    { // East
      quad_key mortonKey;
      coords = new geo_coordinate2d(new longitude(0.0), new latitude(0.0));
      mortonKey = quad_key.get_key_from_longitude_latitude_at_depth(type.morton,
        coords, depth);
      assertEquals("65536", mortonKey.to_internal_string());
      coords = new geo_coordinate2d(new longitude(180.0), new latitude(-90.0));
      mortonKey = quad_key.get_key_from_longitude_latitude_at_depth(
      type.morton, coords, depth);
      assertEquals("65536", mortonKey.to_internal_string());
      coords = new geo_coordinate2d(new longitude(180.0), new latitude(90.0));
      mortonKey = quad_key.get_key_from_longitude_latitude_at_depth(
      type.morton, coords, depth);
      assertEquals("65536", mortonKey.to_internal_string());
      geo_coordinate_bounding_box2d actual =
        new geo_coordinate_bounding_box2d();
      mortonKey.get_geo_coordinate_bounds2d(actual);
      assertTrue(new geo_coordinate2d(new longitude(+0.0), new latitude(-90.0)).near(actual.lower_left(), 1));
      assertTrue(new geo_coordinate2d(new longitude(+180.0), new latitude(+90.0)).near(actual.upper_right(), 1));
    }
    depth = 1;
    { // 0x6
      quad_key mortonKey;
      coords = new geo_coordinate2d(new longitude(-180.0), new latitude(-0.1));
      mortonKey = quad_key.get_key_from_longitude_latitude_at_depth(
      type.morton, coords, depth);
      assertEquals("131078", mortonKey.to_internal_string());
      coords = new geo_coordinate2d(new longitude(-180.0), new latitude(-90.0));
      mortonKey = quad_key.get_key_from_longitude_latitude_at_depth(
      type.morton, coords, depth);
      assertEquals("131078", mortonKey.to_internal_string());
      coords = new geo_coordinate2d(new longitude(-90.1), new latitude(-90.0));
      mortonKey = quad_key.get_key_from_longitude_latitude_at_depth(
      type.morton, coords, depth);
      assertEquals("131078", mortonKey.to_internal_string());
      coords = new geo_coordinate2d(new longitude(-90.1), new latitude(-0.1));
      mortonKey = quad_key.get_key_from_longitude_latitude_at_depth(
      type.morton, coords, depth);
      assertEquals("131078", mortonKey.to_internal_string());
    }
    { // 0x7
      quad_key mortonKey;
      coords = new geo_coordinate2d(new longitude(-90.0), new latitude(-0.1));
      mortonKey = quad_key.get_key_from_longitude_latitude_at_depth(
      type.morton, coords, depth);
      assertEquals("131079", mortonKey.to_internal_string());
      coords = new geo_coordinate2d(new longitude(-90.0), new latitude(-90.0));
      mortonKey = quad_key.get_key_from_longitude_latitude_at_depth(
      type.morton, coords, depth);
      assertEquals("131079", mortonKey.to_internal_string());
      coords = new geo_coordinate2d(new longitude(-0.1), new latitude(-90.0));
      mortonKey = quad_key.get_key_from_longitude_latitude_at_depth(
      type.morton, coords, depth);
      assertEquals("131079", mortonKey.to_internal_string());
      coords = new geo_coordinate2d(new longitude(-0.1), new latitude(-0.1));
      mortonKey = quad_key.get_key_from_longitude_latitude_at_depth(
      type.morton, coords, depth);
      assertEquals("131079", mortonKey.to_internal_string());
    }
    { // 0x2
      quad_key mortonKey;
      coords = new geo_coordinate2d(new longitude(0.0), new latitude(-0.1));
      mortonKey = quad_key.get_key_from_longitude_latitude_at_depth(
      type.morton, coords, depth);
      assertEquals("131074", mortonKey.to_internal_string());
      coords = new geo_coordinate2d(new longitude(0.0), new latitude(-90.0));
      mortonKey = quad_key.get_key_from_longitude_latitude_at_depth(
      type.morton, coords, depth);
      assertEquals("131074", mortonKey.to_internal_string());
      coords = new geo_coordinate2d(new longitude(90.0), new latitude(-90.0));
      mortonKey = quad_key.get_key_from_longitude_latitude_at_depth(
      type.morton, coords, depth);
      assertEquals("131074", mortonKey.to_internal_string());
      coords = new geo_coordinate2d(new longitude(90.0), new latitude(-0.1));
      mortonKey = quad_key.get_key_from_longitude_latitude_at_depth(
      type.morton, coords, depth);
      assertEquals("131074", mortonKey.to_internal_string());
    }
    { // 0x3
      quad_key mortonKey;
      coords = new geo_coordinate2d(new longitude(90.1), new latitude(-0.1));
      mortonKey = quad_key.get_key_from_longitude_latitude_at_depth(
      type.morton, coords, depth);
      assertEquals("131075", mortonKey.to_internal_string());
      coords = new geo_coordinate2d(new longitude(90.1), new latitude(-90.0));
      mortonKey = quad_key.get_key_from_longitude_latitude_at_depth(
      type.morton, coords, depth);
      assertEquals("131075", mortonKey.to_internal_string());
      coords = new geo_coordinate2d(new longitude(180.0), new latitude(-90.0));
      mortonKey = quad_key.get_key_from_longitude_latitude_at_depth(
      type.morton, coords, depth);
      assertEquals("131075", mortonKey.to_internal_string());
      coords = new geo_coordinate2d(new longitude(180.0), new latitude(-0.1));
      mortonKey = quad_key.get_key_from_longitude_latitude_at_depth(
      type.morton, coords, depth);
      assertEquals("131075", mortonKey.to_internal_string());
    }
    { // 0x4
      quad_key mortonKey;
      coords = new geo_coordinate2d(new longitude(-180.0), new latitude(90.0));
      mortonKey = quad_key.get_key_from_longitude_latitude_at_depth(
      type.morton, coords, depth);
      assertEquals("131076", mortonKey.to_internal_string());
      coords = new geo_coordinate2d(new longitude(-180.0), new latitude(0.0));
      mortonKey = quad_key.get_key_from_longitude_latitude_at_depth(
      type.morton, coords, depth);
      assertEquals("131076", mortonKey.to_internal_string());
      coords = new geo_coordinate2d(new longitude(-90.1), new latitude(0.0));
      mortonKey = quad_key.get_key_from_longitude_latitude_at_depth(
        type.morton, coords, depth);
      assertEquals("131076", mortonKey.to_internal_string());
      coords = new geo_coordinate2d(new longitude(-90.1), new latitude(90.0));
      mortonKey = quad_key.get_key_from_longitude_latitude_at_depth(
        type.morton, coords, depth);
      assertEquals("131076", mortonKey.to_internal_string());
    }
    { // 0x5
      quad_key mortonKey;
      coords = new geo_coordinate2d(new longitude(-90.0), new latitude(90.0));
      mortonKey = quad_key.get_key_from_longitude_latitude_at_depth(
        type.morton, coords, depth);
      assertEquals("131077", mortonKey.to_internal_string());
      coords = new geo_coordinate2d(new longitude(-90.0), new latitude(0.0));
      mortonKey = quad_key.get_key_from_longitude_latitude_at_depth(
        type.morton, coords, depth);
      assertEquals("131077", mortonKey.to_internal_string());
      coords = new geo_coordinate2d(new longitude(-0.1), new latitude(0.0));
      mortonKey = quad_key.get_key_from_longitude_latitude_at_depth(
        type.morton, coords, depth);
      assertEquals("131077", mortonKey.to_internal_string());
      coords = new geo_coordinate2d(new longitude(-0.1), new latitude(90.0));
      mortonKey = quad_key.get_key_from_longitude_latitude_at_depth(
        type.morton, coords, depth);
      assertEquals("131077", mortonKey.to_internal_string());
    }
    { // 0x0
      quad_key mortonKey;
      coords = new geo_coordinate2d(new longitude(0.0), new latitude(90.0));
      mortonKey = quad_key.get_key_from_longitude_latitude_at_depth(
        type.morton, coords, depth);
      assertEquals("131072", mortonKey.to_internal_string());
      coords = new geo_coordinate2d(new longitude(0.0), new latitude(0.0));
      mortonKey = quad_key.get_key_from_longitude_latitude_at_depth(
        type.morton, coords, depth);
      assertEquals("131072", mortonKey.to_internal_string());
      coords = new geo_coordinate2d(new longitude(90.0), new latitude(0.0));
      mortonKey = quad_key.get_key_from_longitude_latitude_at_depth(
        type.morton, coords, depth);
      assertEquals("131072", mortonKey.to_internal_string());
      coords = new geo_coordinate2d(new longitude(90.0), new latitude(90.0));
      mortonKey = quad_key.get_key_from_longitude_latitude_at_depth(
        type.morton, coords, depth);
      assertEquals("131072", mortonKey.to_internal_string());
    }
    { // 0x1
      quad_key mortonKey;
      coords = new geo_coordinate2d(new longitude(90.1), new latitude(90.0));
      mortonKey = quad_key.get_key_from_longitude_latitude_at_depth(
        type.morton, coords, depth);
      assertEquals("131073", mortonKey.to_internal_string());
      coords = new geo_coordinate2d(new longitude(90.1), new latitude(0.0));
      mortonKey = quad_key.get_key_from_longitude_latitude_at_depth(
        type.morton, coords, depth);
      assertEquals("131073", mortonKey.to_internal_string());
      coords = new geo_coordinate2d(new longitude(180.0), new latitude(0.0));
      mortonKey = quad_key.get_key_from_longitude_latitude_at_depth(
        type.morton, coords, depth);
      assertEquals("131073", mortonKey.to_internal_string());
      coords = new geo_coordinate2d(new longitude(180.0), new latitude(90.0));
      mortonKey = quad_key.get_key_from_longitude_latitude_at_depth(
        type.morton, coords, depth);
      assertEquals("131073", mortonKey.to_internal_string());
    }
    depth = 2;
    List<Pair<geo_coordinate_bounding_box2d, String>> tests =
      new ArrayList<>();

    tests.add(new Pair<>(
      new geo_coordinate_bounding_box2d(
        new geo_coordinate2d(new longitude(-180.0), new latitude(-90.0)),
        new geo_coordinate2d(new longitude(-135.1), new latitude(-45.1))),
        "262168"));
    tests.add(new Pair<>(
      new geo_coordinate_bounding_box2d(
          new geo_coordinate2d(new longitude(-135.0), new latitude(-90.0)),
          new geo_coordinate2d(new longitude(-90.1), new latitude(-45.1))),
        "262169"));
    tests.add(new Pair<>(
      new geo_coordinate_bounding_box2d(
          new geo_coordinate2d(new longitude(-90.0), new latitude(-90.0)),
          new geo_coordinate2d(new longitude(-45.1), new latitude(-45.1))),
        "262172"));
    tests.add(new Pair<>(
      new geo_coordinate_bounding_box2d(
          new geo_coordinate2d(new longitude(-45.0), new latitude(-90.0)),
          new geo_coordinate2d(new longitude(-0.1), new latitude(-45.1))),
        "262173"));
    tests.add(new Pair<>(
      new geo_coordinate_bounding_box2d(
          new geo_coordinate2d(new longitude(+0.0), new latitude(-90.0)),
          new geo_coordinate2d(new longitude(+45.0), new latitude(-45.1))),
        "262152"));
    tests.add(new Pair<>(
      new geo_coordinate_bounding_box2d(
          new geo_coordinate2d(new longitude(+45.1), new latitude(-90.0)),
          new geo_coordinate2d(new longitude(+90.0), new latitude(-45.1))),
        "262153"));
    tests.add(new Pair<>(
      new geo_coordinate_bounding_box2d(
          new geo_coordinate2d(new longitude(+90.1), new latitude(-90.0)),
          new geo_coordinate2d(new longitude(+135.0), new latitude(-45.1))),
        "262156"));
    tests.add(new Pair<>(
      new geo_coordinate_bounding_box2d(
          new geo_coordinate2d(new longitude(+135.1), new latitude(-90.0)),
          new geo_coordinate2d(new longitude(+180.0), new latitude(-45.1))),
        "262157"));
    tests.add(new Pair<>(
      new geo_coordinate_bounding_box2d(
          new geo_coordinate2d(new longitude(-180.0), new latitude(-45.0)),
          new geo_coordinate2d(new longitude(-135.1), new latitude(-0.1))),
        "262170"));
    tests.add(new Pair<>(
      new geo_coordinate_bounding_box2d(
          new geo_coordinate2d(new longitude(-135.0), new latitude(-45.0)),
          new geo_coordinate2d(new longitude(-90.1), new latitude(-0.1))),
        "262171"));
    tests.add(new Pair<>(
      new geo_coordinate_bounding_box2d(
          new geo_coordinate2d(new longitude(-90.0), new latitude(-45.0)),
          new geo_coordinate2d(new longitude(-45.1), new latitude(-0.1))),
        "262174"));
    tests.add(new Pair<>(
      new geo_coordinate_bounding_box2d(
          new geo_coordinate2d(new longitude(-45.0), new latitude(-45.0)),
          new geo_coordinate2d(new longitude(-0.1), new latitude(-0.1))),
        "262175"));
    tests.add(new Pair<>(
      new geo_coordinate_bounding_box2d(
          new geo_coordinate2d(new longitude(+0.0), new latitude(-45.0)),
          new geo_coordinate2d(new longitude(+45.0), new latitude(-0.1))),
        "262154"));
    tests.add(new Pair<>(
      new geo_coordinate_bounding_box2d(
          new geo_coordinate2d(new longitude(+45.1), new latitude(-45.0)),
          new geo_coordinate2d(new longitude(+90.0), new latitude(-0.1))),
        "262155"));
    tests.add(new Pair<>(
      new geo_coordinate_bounding_box2d(
          new geo_coordinate2d(new longitude(+90.1), new latitude(-45.0)),
          new geo_coordinate2d(new longitude(+135.0), new latitude(-0.1))),
        "262158"));
    tests.add(new Pair<>(
      new geo_coordinate_bounding_box2d(
          new geo_coordinate2d(new longitude(+135.1), new latitude(-45.0)),
          new geo_coordinate2d(new longitude(+180.0), new latitude(-0.1))),
        "262159"));
    tests.add(new Pair<>(
      new geo_coordinate_bounding_box2d(
          new geo_coordinate2d(new longitude(-180.0), new latitude(+0.0)),
          new geo_coordinate2d(new longitude(-135.1), new latitude(+45.0))),
        "262160"));
    tests.add(new Pair<>(
      new geo_coordinate_bounding_box2d(
          new geo_coordinate2d(new longitude(-135.0), new latitude(+0.0)),
          new geo_coordinate2d(new longitude(-90.1), new latitude(+45.0))),
        "262161"));
    tests.add(new Pair<>(
      new geo_coordinate_bounding_box2d(
          new geo_coordinate2d(new longitude(-90.0), new latitude(+0.0)),
          new geo_coordinate2d(new longitude(-45.1), new latitude(+45.0))),
        "262164"));
    tests.add(new Pair<>(
      new geo_coordinate_bounding_box2d(
          new geo_coordinate2d(new longitude(-45.0), new latitude(+0.0)),
          new geo_coordinate2d(new longitude(-0.1), new latitude(+45.0))),
        "262165"));
    tests.add(new Pair<>(
      new geo_coordinate_bounding_box2d(
          new geo_coordinate2d(new longitude(+0.0), new latitude(+0.0)),
          new geo_coordinate2d(new longitude(+45.0), new latitude(+45.0))),
        "262144"));
    tests.add(new Pair<>(
      new geo_coordinate_bounding_box2d(
          new geo_coordinate2d(new longitude(+45.1), new latitude(+0.0)),
          new geo_coordinate2d(new longitude(+90.0), new latitude(+45.0))),
        "262145"));
    tests.add(new Pair<>(
      new geo_coordinate_bounding_box2d(
          new geo_coordinate2d(new longitude(+90.1), new latitude(+0.0)),
          new geo_coordinate2d(new longitude(+135.0), new latitude(+45.0))),
        "262148"));
    tests.add(new Pair<>(
      new geo_coordinate_bounding_box2d(
          new geo_coordinate2d(new longitude(+135.1), new latitude(+0.0)),
          new geo_coordinate2d(new longitude(+180.0), new latitude(+45.0))),
        "262149"));
    tests.add(new Pair<>(
      new geo_coordinate_bounding_box2d(
          new geo_coordinate2d(new longitude(-180.0), new latitude(+45.1)),
          new geo_coordinate2d(new longitude(-135.1), new latitude(+90.0))),
        "262162"));
    tests.add(new Pair<>(
      new geo_coordinate_bounding_box2d(
          new geo_coordinate2d(new longitude(-135.0), new latitude(+45.1)),
          new geo_coordinate2d(new longitude(-90.1), new latitude(+90.0))),
        "262163"));
    tests.add(new Pair<>(
      new geo_coordinate_bounding_box2d(
          new geo_coordinate2d(new longitude(-90.0), new latitude(+45.1)),
          new geo_coordinate2d(new longitude(-45.1), new latitude(+90.0))),
        "262166"));
    tests.add(new Pair<>(
      new geo_coordinate_bounding_box2d(
          new geo_coordinate2d(new longitude(-45.0), new latitude(+45.1)),
          new geo_coordinate2d(new longitude(-0.1), new latitude(+90.0))),
        "262167"));
    tests.add(new Pair<>(
      new geo_coordinate_bounding_box2d(
          new geo_coordinate2d(new longitude(+0.0), new latitude(+45.1)),
          new geo_coordinate2d(new longitude(+45.0), new latitude(+90.0))),
        "262146"));
    tests.add(new Pair<>(
      new geo_coordinate_bounding_box2d(
          new geo_coordinate2d(new longitude(+45.1), new latitude(+45.1)),
          new geo_coordinate2d(new longitude(+90.0), new latitude(+90.0))),
        "262147"));
    tests.add(new Pair<>(
      new geo_coordinate_bounding_box2d(
          new geo_coordinate2d(new longitude(+90.1), new latitude(+45.1)),
          new geo_coordinate2d(new longitude(+135.0), new latitude(+90.0))),
        "262150"));
    tests.add(new Pair<>(
      new geo_coordinate_bounding_box2d(
          new geo_coordinate2d(new longitude(+135.1), new latitude(+45.1)),
          new geo_coordinate2d(new longitude(+180.0), new latitude(+90.0))),
        "262151"));

    for (Pair<geo_coordinate_bounding_box2d, String> pair : tests) {
      geo_coordinate_bounding_box2d bbox = pair.first();
      geo_coordinate2d ll = new geo_coordinate2d(bbox.lower_left());
      geo_coordinate2d lr = new geo_coordinate2d(
        bbox.upper_right().get_longitude(),
        bbox.lower_left().get_latitude());
      geo_coordinate2d ur = new geo_coordinate2d(bbox.upper_right());
      geo_coordinate2d ul = new geo_coordinate2d(
        bbox.lower_left().get_longitude(),
        bbox.upper_right().get_latitude());
      quad_key mortonKey;
      mortonKey = quad_key.get_key_from_longitude_latitude_at_depth(
        type.morton, ll, depth);
      assertEquals(pair.second(), mortonKey.to_internal_string());
      mortonKey = quad_key.get_key_from_longitude_latitude_at_depth(
        type.morton, lr, depth);
      assertEquals(pair.second(), mortonKey.to_internal_string());
      mortonKey = quad_key.get_key_from_longitude_latitude_at_depth(
        type.morton, ur, depth);
      assertEquals(pair.second(), mortonKey.to_internal_string());
      mortonKey = quad_key.get_key_from_longitude_latitude_at_depth(
        type.morton, ul, depth);
      assertEquals(pair.second(), mortonKey.to_internal_string());
      geo_coordinate_bounding_box2d actual =
        new geo_coordinate_bounding_box2d();
      mortonKey.get_geo_coordinate_bounds2d(actual);
      assertTrue(ll.near(actual.lower_left(), 1));
      assertTrue(ur.near(actual.upper_right(), 1));
    }
  }

  @Test
  public void get_keys_from_longitude_latitude_bounding_boxTest() {
    List<Pair<geo_coordinate_bounding_box2d, quad_key_vector>> tests =
      new ArrayList<>();

    tests.add(new Pair<>(new geo_coordinate_bounding_box2d(
      new geo_coordinate2d(new longitude(-180.0), new latitude(-90.0)),
      new geo_coordinate2d(new longitude(-0.1), new latitude(+90.0))),
      new quad_key_vector()));
   tests.get(0).second().add(new quad_key(type.morton, 0, 0, (short)0));
    tests.add(new Pair<>(new geo_coordinate_bounding_box2d(
      new geo_coordinate2d(new longitude(+0.0), new latitude(-90.0)),
      new geo_coordinate2d(new longitude(+180.0), new latitude(+90.0))),
      new quad_key_vector()));
   tests.get(1).second().add(new quad_key(type.morton, 0, 1, (short)0));

    for (Pair<geo_coordinate_bounding_box2d, quad_key_vector> pair : tests) {
      quad_key_vector actual;
      actual = quad_key.get_keys_from_longitude_latitude_bounding_box(
        type.morton, pair.first(), (short)0);
      assertEquals(pair.second().size(), actual.size());
      for (int i = 0; i < actual.size(); ++i) {
        assertTrue(vectorContains(actual, pair.second().get(i)));
      }
    }

    tests = new ArrayList<>();

    tests.add(new Pair<>(new geo_coordinate_bounding_box2d(
      new geo_coordinate2d(new longitude(-180.0), new latitude(-90.0)),
      new geo_coordinate2d(new longitude(-0.1), new latitude(+90.0))),
      new quad_key_vector()));
    tests.get(0).second().add(new quad_key(type.morton, 0, 0, (short)1));
    tests.get(0).second().add(new quad_key(type.morton, 0, 1, (short)1));
    tests.get(0).second().add(new quad_key(type.morton, 1, 0, (short)1));
    tests.get(0).second().add(new quad_key(type.morton, 1, 1, (short)1));
    tests.add(new Pair<>(new geo_coordinate_bounding_box2d(
      new geo_coordinate2d(new longitude(+0.0), new latitude(-90.0)),
      new geo_coordinate2d(new longitude(+180.0), new latitude(+90.0))),
      new quad_key_vector()));
    tests.get(1).second().add(new quad_key(type.morton, 0, 2, (short)1));
    tests.get(1).second().add(new quad_key(type.morton, 0, 3, (short)1));
    tests.get(1).second().add(new quad_key(type.morton, 1, 2, (short)1));
    tests.get(1).second().add(new quad_key(type.morton, 1, 3, (short)1));
    tests.add(new Pair<>(new geo_coordinate_bounding_box2d(
      new geo_coordinate2d(new longitude(-180.0), new latitude(-90.0)),
      new geo_coordinate2d(new longitude(-0.1), new latitude(-0.1))),
      new quad_key_vector()));
    tests.get(2).second().add(new quad_key(type.morton, 0, 0, (short)1));
    tests.get(2).second().add(new quad_key(type.morton, 0, 1, (short)1));
    tests.add(new Pair<>(new geo_coordinate_bounding_box2d(
      new geo_coordinate2d(new longitude(-180.0), new latitude(+0.0)),
      new geo_coordinate2d(new longitude(-0.1), new latitude(+90.0))),
      new quad_key_vector()));
    tests.get(3).second().add(new quad_key(type.morton, 1, 0, (short)1));
    tests.get(3).second().add(new quad_key(type.morton, 1, 1, (short)1));
    tests.add(new Pair<>(new geo_coordinate_bounding_box2d(
      new geo_coordinate2d(new longitude(+0.0), new latitude(-90.0)),
      new geo_coordinate2d(new longitude(+180.0), new latitude(-0.1))),
      new quad_key_vector()));
    tests.get(4).second().add(new quad_key(type.morton, 0, 2, (short)1));
    tests.get(4).second().add(new quad_key(type.morton, 0, 3, (short)1));
    tests.add(new Pair<>(new geo_coordinate_bounding_box2d(
      new geo_coordinate2d(new longitude(+0.0), new latitude(+0.0)),
      new geo_coordinate2d(new longitude(+180.0), new latitude(+90.0))),
      new quad_key_vector()));
    tests.get(5).second().add(new quad_key(type.morton, 1, 2, (short)1));
    tests.get(5).second().add(new quad_key(type.morton, 1, 3, (short)1));
    tests.add(new Pair<>(new geo_coordinate_bounding_box2d(
      new geo_coordinate2d(new longitude(-180.0), new latitude(-90.0)),
      new geo_coordinate2d(new longitude(-90.1), new latitude(-0.1))),
      new quad_key_vector()));
    tests.get(6).second().add(new quad_key(type.morton, 0, 0, (short)1));
    tests.add(new Pair<>(new geo_coordinate_bounding_box2d(
      new geo_coordinate2d(new longitude(-90.0), new latitude(-90.0)),
      new geo_coordinate2d(new longitude(-0.1), new latitude(-0.1))),
      new quad_key_vector()));
    tests.get(7).second().add(new quad_key(type.morton, 0, 1, (short)1));
    tests.add(new Pair<>(new geo_coordinate_bounding_box2d(
      new geo_coordinate2d(new longitude(+0.0), new latitude(-90.0)),
      new geo_coordinate2d(new longitude(+90.0), new latitude(-0.1))),
      new quad_key_vector()));
    tests.get(8).second().add(new quad_key(type.morton, 0, 2, (short)1));
    tests.add(new Pair<>(new geo_coordinate_bounding_box2d(
      new geo_coordinate2d(new longitude(+90.1), new latitude(-90.0)),
      new geo_coordinate2d(new longitude(+180.0), new latitude(-0.1))),
      new quad_key_vector()));
    tests.get(9).second().add(new quad_key(type.morton, 0, 3, (short)1));
    tests.add(new Pair<>(new geo_coordinate_bounding_box2d(
      new geo_coordinate2d(new longitude(-180.0), new latitude(+0.0)),
      new geo_coordinate2d(new longitude(-90.1), new latitude(+90.0))),
      new quad_key_vector()));
    tests.get(10).second().add(new quad_key(type.morton, 1, 0, (short)1));
    tests.add(new Pair<>(new geo_coordinate_bounding_box2d(
      new geo_coordinate2d(new longitude(-90.0), new latitude(+0.0)),
      new geo_coordinate2d(new longitude(-0.1), new latitude(+90.0))),
      new quad_key_vector()));
    tests.get(11).second().add(new quad_key(type.morton, 1, 1, (short)1));
    tests.add(new Pair<>(new geo_coordinate_bounding_box2d(
      new geo_coordinate2d(new longitude(+0.0), new latitude(+0.0)),
      new geo_coordinate2d(new longitude(+90.0), new latitude(+90.0))),
      new quad_key_vector()));
    tests.get(12).second().add(new quad_key(type.morton, 1, 2, (short)1));
    tests.add(new Pair<>(new geo_coordinate_bounding_box2d(
      new geo_coordinate2d(new longitude(+90.1), new latitude(+0.0)),
      new geo_coordinate2d(new longitude(+180.0), new latitude(+90.0))),
      new quad_key_vector()));
    tests.get(13).second().add(new quad_key(type.morton, 1, 3, (short)1));

    for (Pair<geo_coordinate_bounding_box2d, quad_key_vector> pair : tests) {
      quad_key_vector actual;
      actual = quad_key.get_keys_from_longitude_latitude_bounding_box(
        type.morton, pair.first(), (short)1);
      assertEquals(pair.second().size(), actual.size());
      for (int i = 0; i < actual.size(); ++i) {
        assertTrue(vectorContains(actual, pair.second().get(i)));
      }
    }

    {
      Pair<geo_coordinate_bounding_box2d, quad_key_vector> test = new Pair<>(
        new geo_coordinate_bounding_box2d(
          new geo_coordinate2d(new longitude(-140.0), new latitude(-48.0)),
          new geo_coordinate2d(new longitude(+10.0), new latitude(+39.0))),
        new quad_key_vector());
      test.second().add(new quad_key(type.morton, 0, 0, (short)2));
      test.second().add(new quad_key(type.morton, 0, 1, (short)2));
      test.second().add(new quad_key(type.morton, 0, 2, (short)2));
      test.second().add(new quad_key(type.morton, 0, 3, (short)2));
      test.second().add(new quad_key(type.morton, 0, 4, (short)2));
      test.second().add(new quad_key(type.morton, 1, 0, (short)2));
      test.second().add(new quad_key(type.morton, 1, 1, (short)2));
      test.second().add(new quad_key(type.morton, 1, 2, (short)2));
      test.second().add(new quad_key(type.morton, 1, 3, (short)2));
      test.second().add(new quad_key(type.morton, 1, 4, (short)2));
      test.second().add(new quad_key(type.morton, 2, 0, (short)2));
      test.second().add(new quad_key(type.morton, 2, 1, (short)2));
      test.second().add(new quad_key(type.morton, 2, 2, (short)2));
      test.second().add(new quad_key(type.morton, 2, 3, (short)2));
      test.second().add(new quad_key(type.morton, 2, 4, (short)2));

      quad_key_vector actual;
      actual = quad_key.get_keys_from_longitude_latitude_bounding_box(
        type.morton, test.first(), (short)2);
      assertEquals(test.second().size(), actual.size());
      for (int i = 0; i < actual.size(); ++i) {
        assertTrue(vectorContains(actual, test.second().get(i)));
      }
    }
  }

  @Test
  public void selecetedCitiesTest() {
    {
      Pair<Short, geo_coordinate2d> data = new Pair<>((short)13,
        new geo_coordinate2d(new longitude(+2.29450000000000),
          new latitude(+48.85822200000000)));
      int tile = 8428778 | (1 << (data.first() + 16));
      String ss = "" + tile;
      quad_key mortonquad_key =
        quad_key.get_key_from_longitude_latitude_at_depth(
          type.morton, data.second(), data.first());
      assertEquals(ss, mortonquad_key.to_internal_string());
    }
    {
      Pair<Short, geo_coordinate2d> data = new Pair<>((short)13,
        new geo_coordinate2d(new longitude(-74.04444400000000),
          new latitude(+40.68916700000000)));
      int tile = 86924190 | (1 << (data.first() + 16));
      String ss = "" + tile;
      quad_key mortonquad_key =
        quad_key.get_key_from_longitude_latitude_at_depth(type.morton,
          data.second(), data.first());
      assertEquals(ss, mortonquad_key.to_internal_string());
    }
    {
      Pair<Short, geo_coordinate2d> data = new Pair<>((short)13,
        new geo_coordinate2d(new longitude(-43.15744400000000),
          new latitude(-22.94865800000000)));
      int tile = 130726287 | (1 << (data.first() + 16));
      String ss = "" + tile;
      quad_key mortonquad_key =
        quad_key.get_key_from_longitude_latitude_at_depth(
          type.morton, data.second(), data.first());
      assertEquals(ss, mortonquad_key.to_internal_string());
    }
    {
      Pair<Short, geo_coordinate2d> data = new Pair<>((short)13,
        new geo_coordinate2d(new longitude(+151.21527800000000),
          new latitude(-33.85611100000000)));
      int tile = 63372939 | (1 << (data.first() + 16));
      String ss = "" + tile;
      quad_key mortonquad_key =
        quad_key.get_key_from_longitude_latitude_at_depth(
          type.morton, data.second(), data.first());
      assertEquals(ss, mortonquad_key.to_internal_string());
    }
    {
      Pair<Short, geo_coordinate2d> data = new Pair<>((short)13,
        new geo_coordinate2d(new longitude(+0.00000000000000),
          new latitude(+51.50300000000000)));
      int tile = 8521770 | (1 << (data.first() + 16));
      String ss = "" + tile;
      quad_key mortonquad_key = quad_key.get_key_from_longitude_latitude_at_depth(
      type.morton, data.second(), data.first());
      assertEquals(ss, mortonquad_key.to_internal_string());
    }
    {
      Pair<Short, geo_coordinate2d> data = new Pair<>((short)13,
        new geo_coordinate2d(new longitude(-78.45000000000000),
          new latitude(+0.00000000000000)));
      int tile = 84148305 | (1 << (data.first() + 16));
      String ss = "" + tile;
      quad_key mortonquad_key =
        quad_key.get_key_from_longitude_latitude_at_depth(
          type.morton, data.second(), data.first());
      assertEquals(ss, mortonquad_key.to_internal_string());
    }
    {
      Pair<Short, geo_coordinate2d> data = new Pair<>((short)10,
        new geo_coordinate2d(new longitude(+2.29450000000000),
          new latitude(+48.85822200000000)));
      int tile = 131699 | (1 << (16 + data.first()));
      String ss = "" + tile;
      quad_key mortonquad_key =
        quad_key.get_key_from_longitude_latitude_at_depth(
          type.morton, data.second(), data.first());
      assertEquals(ss, mortonquad_key.to_internal_string());
    }
    {
      Pair<Short, geo_coordinate2d> data = new Pair<>((short)10,
        new geo_coordinate2d(new longitude(-74.04444400000000),
          new latitude(+40.68916700000000)));
      int tile = 1358190 | (1 << (16 + data.first()));
      String ss = "" + tile;
      quad_key mortonquad_key =
        quad_key.get_key_from_longitude_latitude_at_depth(
          type.morton, data.second(), data.first());
      assertEquals(ss, mortonquad_key.to_internal_string());
    }
    {
      Pair<Short, geo_coordinate2d> data = new Pair<>((short)10,
        new geo_coordinate2d(new longitude(-43.15744400000000),
          new latitude(-22.94865800000000)));
      int tile = 2042598 | (1 << (16 + data.first()));
      String ss = "" + tile;
      quad_key mortonquad_key =
        quad_key.get_key_from_longitude_latitude_at_depth(
          type.morton, data.second(), data.first());
      assertEquals(ss, mortonquad_key.to_internal_string());
    }
    {
      Pair<Short, geo_coordinate2d> data = new Pair<>((short)10,
        new geo_coordinate2d(new longitude(+151.21527800000000),
          new latitude(-33.85611100000000)));
      int tile = 990202 | (1 << (16 + data.first()));
      String ss = "" + tile;
      quad_key mortonquad_key =
        quad_key.get_key_from_longitude_latitude_at_depth(
          type.morton, data.second(), data.first());
      assertEquals(ss, mortonquad_key.to_internal_string());
    }
    {
      Pair<Short, geo_coordinate2d> data = new Pair<>((short)10,
        new geo_coordinate2d(new longitude(+0.00000000000000),
          new latitude(+51.50300000000000)));
      int tile = 133152 | (1 << (16 + data.first()));
      String ss = "" + tile;
      quad_key mortonquad_key =
        quad_key.get_key_from_longitude_latitude_at_depth(
          type.morton, data.second(), data.first());
      assertEquals(ss, mortonquad_key.to_internal_string());
    }
    {
      Pair<Short, geo_coordinate2d> data = new Pair<>((short)10,
        new geo_coordinate2d(new longitude(-78.45000000000000),
          new latitude(+0.00000000000000)));
      int tile = 1314817 | (1 << (16 + data.first()));
      String ss = "" + tile;
      quad_key mortonquad_key =
        quad_key.get_key_from_longitude_latitude_at_depth(
          type.morton, data.second(), data.first());
      assertEquals(ss, mortonquad_key.to_internal_string());
    }
  }
}

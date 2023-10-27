package com.quad_keys;

import org.junit.Test;
import static org.junit.Assert.*;
import org.junit.BeforeClass;


public class QuadKeyTest {

  @BeforeClass
  public static void setUpBeforeClass() throws Exception {
    System.loadLibrary("quad_keys_java");
  }

  @Test
  public void default_ctor_test() {
    QuadKey key = new QuadKey();
    assertNotNull(key);
    assertEquals(0, key.get_row());
    assertEquals(0, key.get_col());
    assertEquals(0, key.get_depth());
    assertEquals(Type.None, key.get_type());
  }

  @Test
  public void ctor_only_type_test() {
    Type [] types = {Type.None, Type.Bing, Type.LatLon,
      Type.UlpQnr, Type.OsGeo, Type.Morton};

    for(Type type : types) {
      QuadKey key = new QuadKey(type);
      assertNotNull(key);
      assertEquals(0, key.get_row());
      assertEquals(0, key.get_col());
      assertEquals(0, key.get_depth());
      assertEquals(type, key.get_type());
    }
  }

  @Test
  public void copy_ctor_test() {
    QuadKey key = new QuadKey(Type.OsGeo);
    QuadKey key_copy = new QuadKey(key);
    assertNotSame(key, key_copy);
    assertTrue(key.equalTo(key_copy));
    assertNotNull(key);
    assertEquals(0, key_copy.get_row());
    assertEquals(0, key_copy.get_col());
    assertEquals(0, key_copy.get_depth());
    assertEquals(Type.OsGeo, key_copy.get_type());
  }

  @Test
  public void is_root_test() {
    QuadKey key = new QuadKey(Type.OsGeo);
    assertTrue(key.is_root_key());
  }

  @Test
  public void system_specific_ctor_test() {
    Type [] types = {Type.None, Type.Bing, Type.LatLon, Type.UlpQnr,
      Type.OsGeo, Type.Morton};

    for (Type type : types) {
      for (short depth = 0; depth < 10; ++depth) {
        long max_rows = QuadKey.max_rows(type, depth);
        long max_cols = QuadKey.max_cols(type, depth);

        QuadKey invalid = new QuadKey(type, max_rows, max_cols, depth);
        assertTrue(invalid.equalTo(new QuadKey()));

        long validRow = max_rows - 1;
        long validCol = max_cols - 1;
        QuadKey valid = new QuadKey(type, validRow, validCol, depth);
        assertTrue(valid.equalTo(new QuadKey(type, validRow, validCol,
          depth)));
      }
    }
  }
}

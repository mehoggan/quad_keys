import com.quad_key.quad_key;
import com.quad_key.type;
import org.junit.BeforeClass;
import org.junit.Test;

import static org.junit.Assert.*;
import org.junit.BeforeClass;
import org.junit.Test;

import java.util.*;
import java.net.*;


public class quad_key_test {

  @BeforeClass
  public static void setUpBeforeClass() throws Exception {
    System.loadLibrary("quad_key_jni");
  }

  @Test
  public void default_ctor_test() {
    quad_key key = new quad_key();
    assertNotNull(key);
    assertEquals(0, key.get_row());
    assertEquals(0, key.get_col());
    assertEquals(0, key.get_depth());
    assertEquals(type.none, key.get_type());
  }

  @Test
  public void ctor_only_type_test() {
    type [] types = {type.none, type.bing, type.lat_long,
      type.ulp_qnr, type.osgeo, type.morton};

    for(type type : types) {
      quad_key key = new quad_key(type);
      assertNotNull(key);
      assertEquals(0, key.get_row());
      assertEquals(0, key.get_col());
      assertEquals(0, key.get_depth());
      assertEquals(type, key.get_type());
    }
  }

  @Test
  public void copy_ctor_test() {
    quad_key key = new quad_key(type.osgeo);
    quad_key key_copy = new quad_key(key);
    assertNotSame(key, key_copy);
    assertTrue(key.equal_to(key_copy));
    assertNotNull(key);
    assertEquals(0, key_copy.get_row());
    assertEquals(0, key_copy.get_col());
    assertEquals(0, key_copy.get_depth());
    assertEquals(type.osgeo, key_copy.get_type());
  }

  @Test
  public void is_root_test() {
    quad_key key = new quad_key(type.osgeo);
    assertTrue(key.is_root_key());
  }

  @Test
  public void system_specific_ctor_test() {
    type [] types = {type.none, type.bing, type.lat_long, type.ulp_qnr,
      type.osgeo, type.morton};

    for (type type : types) {
      for (short depth = 0; depth < 10; ++depth) {
        long max_rows = quad_key.max_rows(type, depth);
        long max_cols = quad_key.max_cols(type, depth);

        quad_key invalid = new quad_key(type, max_rows, max_cols, depth);
        assertTrue(invalid.equal_to(new quad_key()));

        long validRow = max_rows - 1;
        long validCol = max_cols - 1;
        quad_key valid = new quad_key(type, validRow, validCol, depth);
        assertTrue(valid.equal_to(new quad_key(type, validRow, validCol,
          depth)));
      }
    }
  }
}

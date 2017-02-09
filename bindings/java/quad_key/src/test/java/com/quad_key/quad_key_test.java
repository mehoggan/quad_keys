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

/*
    @Test
    public void defaultCtorTest() {
        quad_key key = new quad_key();
        assertNotNull(key);
        assertEquals(0, key.getRow());
        assertEquals(0, key.getCol());
        assertEquals(0, key.getDepth());
        assertEquals(type.None, key.gettype());
    }

    @Test
    public void ctorOnlytypeTest() {
        type [] types = {type.None, type.Bing, type.LatLong,
                type.UlpQnr, type.OsGeo, type.Morton};

        for(type type : types) {
            quad_key key = new quad_key(type);
            assertNotNull(key);
            assertEquals(0, key.getRow());
            assertEquals(0, key.getCol());
            assertEquals(0, key.getDepth());
            assertEquals(type, key.gettype());
        }
    }

    @Test
    public void copyCtorTest() {
        quad_key key = new quad_key(type.OsGeo);
        quad_key key_copy = new quad_key(key);
        assertNotSame(key, key_copy);
        assertTrue(key.equal_to(key_copy));
        assertNotNull(key);
        assertEquals(0, key_copy.getRow());
        assertEquals(0, key_copy.getCol());
        assertEquals(0, key_copy.getDepth());
        assertEquals(type.OsGeo, key_copy.gettype());
    }

    @Test
    public void isRootTest() {
        quad_key key = new quad_key(type.OsGeo);
        assertTrue(key.isRootKey());
    }

    @Test
    public void systemSpecificCtorTest() {
        type [] types = {type.None, type.Bing, type.LatLong, type.UlpQnr,
                type.OsGeo, type.Morton};

        for (type type : types) {
            for (short depth = 0; depth < 10; ++depth) {
                long maxRows = quad_key.maxRows(type, depth);
                long maxCols = quad_key.maxCols(type, depth);

                quad_key invalid = new quad_key(type, maxRows, maxCols, depth);
                assertTrue(invalid.equal_to(new quad_key()));

                long validRow = maxRows - 1;
                long validCol = maxCols - 1;
                quad_key valid = new quad_key(type, validRow, validCol, depth);
                assertTrue(valid.equal_to(new quad_key(type, validRow, validCol,
                        depth)));
            }
        }
    }
*/
}

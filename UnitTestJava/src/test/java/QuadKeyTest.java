import com.quadkey.QuadKey;
import com.quadkey.Type;
import org.junit.BeforeClass;
import org.junit.Test;

import static org.junit.Assert.*;
import org.junit.BeforeClass;
import org.junit.Test;

import java.util.*;
import java.net.*;


public class QuadKeyTest {

    @BeforeClass
    public static void setUpBeforeClass() throws Exception {
        System.loadLibrary("QuadKey");
    }

    @Test
    public void defaultCtorTest() {
        QuadKey key = new QuadKey();
        assertNotNull(key);
        assertEquals(0, key.getRow());
        assertEquals(0, key.getCol());
        assertEquals(0, key.getDepth());
        assertEquals(Type.None, key.getType());
    }

    @Test
    public void ctorOnlyTypeTest() {
        Type [] types = {Type.None, Type.Bing, Type.LatLong,
                Type.UlpQnr, Type.OsGeo, Type.Morton};

        for(Type type : types) {
            QuadKey key = new QuadKey(type);
            assertNotNull(key);
            assertEquals(0, key.getRow());
            assertEquals(0, key.getCol());
            assertEquals(0, key.getDepth());
            assertEquals(type, key.getType());
        }
    }

    @Test
    public void copyCtorTest() {
        QuadKey key = new QuadKey(Type.OsGeo);
        QuadKey key_copy = new QuadKey(key);
        assertNotSame(key, key_copy);
        assertTrue(key.equalTo(key_copy));
        assertNotNull(key);
        assertEquals(0, key_copy.getRow());
        assertEquals(0, key_copy.getCol());
        assertEquals(0, key_copy.getDepth());
        assertEquals(Type.OsGeo, key_copy.getType());
    }

    @Test
    public void isRootTest() {
        QuadKey key = new QuadKey(Type.OsGeo);
        assertTrue(key.isRootKey());
    }

    @Test
    public void systemSpecificCtorTest() {
        Type [] types = {Type.None, Type.Bing, Type.LatLong, Type.UlpQnr,
                Type.OsGeo, Type.Morton};

        for (Type type : types) {
            for (short depth = 0; depth < 10; ++depth) {
                long maxRows = QuadKey.maxRows(type, depth);
                long maxCols = QuadKey.maxCols(type, depth);

                QuadKey invalid = new QuadKey(type, maxRows, maxCols, depth);
                assertTrue(invalid.equalTo(new QuadKey()));

                long validRow = maxRows - 1;
                long validCol = maxCols - 1;
                QuadKey valid = new QuadKey(type, validRow, validCol, depth);
                assertTrue(valid.equalTo(new QuadKey(type, validRow, validCol,
                        depth)));
            }
        }
    }
}

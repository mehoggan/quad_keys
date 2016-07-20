import static org.junit.Assert.*;

import com.quadkey.QuadKey;
import com.quadkey.Type;
import com.quadkey.QuadKeyVector;
import com.quadkey.GeoCoordinate2d;
import com.quadkey.GeoCoordinateBoundingBox2d;
import com.quadkey.Latitude;
import com.quadkey.Longitude;

import org.junit.BeforeClass;
import org.junit.Test;

public class BingSystemTest {

    private boolean vectorContains(QuadKeyVector vector, QuadKey key) {
        boolean found = false;
        for (int i = 0; i < vector.size(); ++i) {
            QuadKey curr = vector.get(i);
            if (curr.equalTo(key)) {
                found = true;
                break;
            }
        }
        return found;
    }

    @BeforeClass
    public static void setUpBeforeClass() throws Exception {
        System.loadLibrary("QuadKey");
    }

    @Test
    public void isValidTest() {
        // See QuadKeyTest.systemSpecificCtorTest
    }

    @Test
    public void isRootKeyTest() {
        // See QuadKeyTest.isValidTest
    }

    @Test
    public void getParentTest() {
        {
            QuadKey key0 = new QuadKey(Type.Bing, 0, 0, (short) 1);
            QuadKey key1 = new QuadKey(Type.Bing, 1, 0, (short) 1);
            QuadKey key2 = new QuadKey(Type.Bing, 1, 1, (short) 1);
            QuadKey key3 = new QuadKey(Type.Bing, 0, 1, (short) 1);

            QuadKey parent = new QuadKey(Type.Bing, 0, 0, (short) 0);

            assertEquals(Type.Bing, key0.getType());
            assertEquals(Type.Bing, key1.getType());
            assertEquals(Type.Bing, key2.getType());
            assertEquals(Type.Bing, key3.getType());
            assertEquals(Type.Bing, parent.getType());

            assertTrue(key0.getParent().equalTo(parent));
            assertTrue(key1.getParent().equalTo(parent));
            assertTrue(key2.getParent().equalTo(parent));
            assertTrue(key3.getParent().equalTo(parent));
        }

        {
            QuadKey key0 = new QuadKey(Type.Bing, 5, 6, (short) 3);
            QuadKey key1 = new QuadKey(Type.Bing, 4, 6, (short) 3);
            QuadKey key2 = new QuadKey(Type.Bing, 4, 7, (short) 3);
            QuadKey key3 = new QuadKey(Type.Bing, 5, 7, (short) 3);

            QuadKey parent = new QuadKey(Type.Bing, 2, 3, (short) 2);

            assertEquals(Type.Bing, key0.getType());
            assertEquals(Type.Bing, key1.getType());
            assertEquals(Type.Bing, key2.getType());
            assertEquals(Type.Bing, key3.getType());
            assertEquals(Type.Bing, parent.getType());

            assertTrue(key0.getParent().equalTo(parent));
            assertTrue(key1.getParent().equalTo(parent));
            assertTrue(key2.getParent().equalTo(parent));
            assertTrue(key3.getParent().equalTo(parent));
        }
    }

    @Test
    public void isMyAncestorTest() {
        {
            QuadKey key = new QuadKey(Type.Bing, 5, 7, (short) 3);
            assertFalse(key.isMyAncestor(new QuadKey()));
            assertFalse(key.isMyAncestor(new QuadKey(Type.OsGeo, 2, 3,
                    (short) 2)));
            assertFalse(key.isMyAncestor(new QuadKey(Type.OsGeo, 0, 0,
                    (short) 0)));
            assertFalse(key.isMyAncestor(new QuadKey(Type.Bing, 5, 7,
                    (short) 3)));
            assertTrue(key.isMyAncestor(new QuadKey(Type.Bing, 2, 3,
                    (short) 2)));
            assertTrue(key.isMyAncestor(new QuadKey(Type.Bing, 0, 0,
                    (short) 0)));

            QuadKey none = new QuadKey();
            assertFalse(none.isMyAncestor(new QuadKey()));
        }

        {
            QuadKey key = new QuadKey(Type.Bing, 5, 7, (short) 3);
            assertFalse(key.isMyAncestor(new QuadKey()));
            assertFalse(key.isMyAncestor(new QuadKey(Type.OsGeo, 2, 3,
                    (short) 2)));
            assertFalse(key.isMyAncestor(new QuadKey(Type.OsGeo, 0, 0,
                    (short) 0)));
            assertFalse(key.isMyAncestor(new QuadKey(Type.Bing, 5, 7,
                    (short) 3)));
            assertTrue(key.isMyAncestor(new QuadKey(Type.Bing, 2, 3,
                    (short) 2)));
            assertTrue(key.isMyAncestor(new QuadKey(Type.Bing, 0, 0,
                    (short) 0)));

            QuadKey none = new QuadKey();
            assertFalse(none.isMyAncestor(new QuadKey()));

        }
    }

    @Test
    public void getAncestorTest() {
        {
            QuadKey key = new QuadKey(Type.Bing, 0, 7, (short)3);
            QuadKey ancestor = new QuadKey(Type.Bing, 0, 1, (short)1);
            assertTrue(ancestor.equalTo(key.getAncestor((short)2)));
        }

        {
            QuadKey key = new QuadKey(Type.Bing, 4, 31, (short)5);
            QuadKey ancestor = new QuadKey(Type.Bing, 0, 1, (short)1);
            assertTrue(ancestor.equalTo(key.getAncestor((short)4)));
        }

        {
            QuadKey key = new QuadKey(Type.Bing, 4, 31, (short)5);
            QuadKey ancestor = new QuadKey(Type.Bing, 0, 3, (short)2);
            assertTrue(ancestor.equalTo(key.getAncestor((short)3)));
        }

        {
            QuadKey key = new QuadKey(Type.Bing, 4, 31, (short)5);
            QuadKey ancestor = new QuadKey(Type.Bing, 1, 7, (short)3);
            assertTrue(ancestor.equalTo(key.getAncestor((short)2)));
        }
    }

    @Test
    public void getChildTest() {
        assertTrue(new QuadKey().equalTo(
                new QuadKey().getChild(QuadKey.Quadrant.NorthWest)));
        short maxDepthBing = QuadKey.maxDepth(Type.Bing);
        assertTrue(new QuadKey().equalTo(
                new QuadKey(Type.Bing, 0, 0, maxDepthBing).getChild(
                        QuadKey.Quadrant.NorthEast)));

        {
            QuadKey key = new QuadKey(Type.Bing, 0, 0, (short)3);
            assertTrue(new QuadKey(Type.Bing, 1, 0, (short)4).equalTo(
                    key.getChild(QuadKey.Quadrant.NorthWest)));
            assertTrue(new QuadKey(Type.Bing, 1, 1, (short)4).equalTo(
                    key.getChild(QuadKey.Quadrant.NorthEast)));
            assertTrue(new QuadKey(Type.Bing, 0, 1, (short)4).equalTo(
                    key.getChild(QuadKey.Quadrant.SouthEast)));
            assertTrue(new QuadKey(Type.Bing, 0, 0, (short)4).equalTo(
                    key.getChild(QuadKey.Quadrant.SouthWest)));
        }

        {
            QuadKey key = new QuadKey(Type.Bing, 2, 3, (short)3);
            assertTrue(new QuadKey(Type.Bing, 5, 6, (short)4).equalTo(
                    key.getChild(QuadKey.Quadrant.NorthWest)));
            assertTrue(new QuadKey(Type.Bing, 5, 7, (short)4).equalTo(
                    key.getChild(QuadKey.Quadrant.NorthEast)));
            assertTrue(new QuadKey(Type.Bing, 4, 7, (short)4).equalTo(
                    key.getChild(QuadKey.Quadrant.SouthEast)));
            assertTrue(new QuadKey(Type.Bing, 4, 6, (short)4).equalTo(
                    key.getChild(QuadKey.Quadrant.SouthWest)));
        }
    }

    @Test
    public void testGetChildern() {
        QuadKeyVector testKeys;
        short maxDepthBing = QuadKey.maxDepth(Type.Bing);
        testKeys = new QuadKey(Type.Bing, 0, 0, maxDepthBing).getChildren();
        assertEquals(0, testKeys.size());

        testKeys.clear();

        QuadKey key0 = new QuadKey(Type.Bing, 0, 0, (short) 1);
        testKeys = key0.getChildren();
        assertEquals(4, testKeys.size());
        assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 0, 0,
                (short) 2)));
        assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 0, 1,
                (short) 2)));
        assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 1, 0,
                (short) 2)));
        assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 1, 1,
                (short) 2)));

        QuadKey key1 = new QuadKey(Type.Bing, 0, 1, (short) 1);
        testKeys = key1.getChildren();
        assertEquals(4, testKeys.size());
        assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 0, 2,
                (short) 2)));
        assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 0, 3,
                (short) 2)));
        assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 1, 2,
                (short) 2)));
        assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 1, 3,
                (short) 2)));

        QuadKey key2 = new QuadKey(Type.Bing, 1, 0, (short) 1);
        testKeys = key2.getChildren();
        assertEquals(4, testKeys.size());
        assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 2, 0,
                (short) 2)));
        assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 2, 1,
                (short) 2)));
        assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 3, 0,
                (short) 2)));
        assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 3, 1,
                (short) 2)));

        QuadKey key3 = new QuadKey(Type.Bing, 1, 1, (short) 1);
        testKeys = key3.getChildren();
        assertEquals(4, testKeys.size());
        assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 2, 2,
                (short) 2)));
        assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 2, 3,
                (short) 2)));
        assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 3, 2,
                (short) 2)));
        assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 3, 3,
                (short) 2)));
    }

    @Test
    public void getDescendantsTest() {
        short bingMaxDepth = QuadKey.maxDepth(Type.Bing);
        short requetedDepth = (short) (bingMaxDepth - 3);
        QuadKey key = new QuadKey(Type.Bing, 0, 0, requetedDepth);
        QuadKeyVector testKeys;

        /* We are going beyond the max depth */
        testKeys = key.getDescendants((short) 4);
        assertEquals(0, testKeys.size());

        QuadKey none = new QuadKey();
        testKeys = none.getDescendants((short) 1);
        assertEquals(0, testKeys.size());

        {
            QuadKey bingKey = new QuadKey(Type.Bing, 0, 0, (short)0);
            testKeys = bingKey.getDescendants((short) 0);
            assertEquals(0, testKeys.size());
        }

        {
            QuadKey bingKey = new QuadKey(Type.Bing, 0, 0, (short) 0);
            testKeys = bingKey.getDescendants((short) 1);
            assertEquals(4, testKeys.size());
            assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 0, 0,
                    (short) 1)));
            assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 0, 1,
                    (short) 1)));
            assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 1, 0,
                    (short) 1)));
            assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 1, 1,
                    (short) 1)));
            testKeys.clear();

            testKeys = bingKey.getDescendants((short) 2);
            assertEquals(16, testKeys.size());
            assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 0, 0,
                    (short) 2)));
            assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 0, 1,
                    (short) 2)));
            assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 0, 2,
                    (short) 2)));
            assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 0, 3,
                    (short) 2)));
            assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 1, 0,
                    (short) 2)));
            assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 1, 1,
                    (short) 2)));
            assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 1, 2,
                    (short) 2)));
            assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 1, 3,
                    (short) 2)));
            assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 2, 0,
                    (short) 2)));
            assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 2, 1,
                    (short) 2)));
            assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 2, 2,
                    (short) 2)));
            assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 2, 3,
                    (short) 2)));
            assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 3, 0,
                    (short) 2)));
            assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 3, 1,
                    (short) 2)));
            assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 3, 2,
                    (short) 2)));
            assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 3, 3,
                    (short) 2)));
            testKeys.clear();

            testKeys = bingKey.getDescendants((short) 3);
            assertEquals(64, testKeys.size());
            assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 0, 0,
                    (short) 3)));
            assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 0, 1,
                    (short) 3)));
            assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 0, 2,
                    (short) 3)));
            assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 0, 3,
                    (short) 3)));
            assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 0, 4,
                    (short) 3)));
            assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 0, 5,
                    (short) 3)));
            assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 0, 6,
                    (short) 3)));
            assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 0, 7,
                    (short) 3)));
            assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 1, 0,
                    (short) 3)));
            assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 1, 1,
                    (short) 3)));
            assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 1, 2,
                    (short) 3)));
            assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 1, 3,
                    (short) 3)));
            assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 1, 4,
                    (short) 3)));
            assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 1, 5,
                    (short) 3)));
            assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 1, 6,
                    (short) 3)));
            assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 1, 7,
                    (short) 3)));
            assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 2, 0,
                    (short) 3)));
            assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 2, 1,
                    (short) 3)));
            assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 2, 2,
                    (short) 3)));
            assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 2, 3,
                    (short) 3)));
            assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 2, 4,
                    (short) 3)));
            assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 2, 5,
                    (short) 3)));
            assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 2, 6,
                    (short) 3)));
            assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 2, 7,
                    (short) 3)));
            assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 3, 0,
                    (short) 3)));
            assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 3, 1,
                    (short) 3)));
            assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 3, 2,
                    (short) 3)));
            assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 3, 3,
                    (short) 3)));
            assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 3, 4,
                    (short) 3)));
            assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 3, 5,
                    (short) 3)));
            assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 3, 6,
                    (short) 3)));
            assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 3, 7,
                    (short) 3)));
            assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 4, 0,
                    (short) 3)));
            assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 4, 1,
                    (short) 3)));
            assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 4, 2,
                    (short) 3)));
            assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 4, 3,
                    (short) 3)));
            assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 4, 4,
                    (short) 3)));
            assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 4, 5,
                    (short) 3)));
            assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 4, 6,
                    (short) 3)));
            assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 4, 7,
                    (short) 3)));
            assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 5, 0,
                    (short) 3)));
            assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 5, 1,
                    (short) 3)));
            assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 5, 2,
                    (short) 3)));
            assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 5, 3,
                    (short) 3)));
            assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 5, 4,
                    (short) 3)));
            assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 5, 5,
                    (short) 3)));
            assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 5, 6,
                    (short) 3)));
            assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 5, 7,
                    (short) 3)));
            assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 6, 0,
                    (short) 3)));
            assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 6, 1,
                    (short) 3)));
            assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 6, 2,
                    (short) 3)));
            assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 6, 3,
                    (short) 3)));
            assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 6, 4,
                    (short) 3)));
            assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 6, 5,
                    (short) 3)));
            assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 6, 6,
                    (short) 3)));
            assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 6, 7,
                    (short) 3)));
            assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 7, 0,
                    (short) 3)));
            assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 7, 1,
                    (short) 3)));
            assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 7, 2,
                    (short) 3)));
            assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 7, 3,
                    (short) 3)));
            assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 7, 4,
                    (short) 3)));
            assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 7, 5,
                    (short) 3)));
            assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 7, 6,
                    (short) 3)));
            assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 7, 7,
                    (short) 3)));
            testKeys.clear();
        }
    }

    @Test
    public void getSiblingsTest() {
        QuadKeyVector testKeys;

        QuadKey none = new QuadKey();
        testKeys = none.getSiblings();
        assertEquals(0, testKeys.size());

        QuadKey root = new QuadKey(Type.Bing, 0, 0, (short) 0);
        testKeys = root.getSiblings();
        assertEquals(0, testKeys.size());

        QuadKey bingKey = new QuadKey(Type.Bing, 0, 0, (short) 1);
        testKeys = bingKey.getSiblings();
        assertEquals(3, testKeys.size());
        assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 0, 1,
                (short) 1)));
        assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 1, 1,
                (short) 1)));
        assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 1, 0,
                (short) 1)));
    }

    @Test
    public void getNeighborsTest() {
        QuadKeyVector testKeys;

        QuadKey none = new QuadKey();
        testKeys = none.getNeighbors();
        assertEquals(0, testKeys.size());

        QuadKey root = new QuadKey(Type.Bing, 0, 0, (short) 0);
        testKeys = root.getNeighbors();
        assertEquals(0, testKeys.size());

        testKeys.clear();

        QuadKey key0 = new QuadKey(Type.Bing, 0, 0, (short) 2);
        testKeys = key0.getNeighbors();
        assertEquals(5, testKeys.size());
        assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 0, 1,
                (short) 2)));
        assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 1, 1,
                (short) 2)));
        assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 1, 0,
                (short) 2)));
        assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 0, 3,
                (short) 2)));
        assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 1, 3,
                (short) 2)));

        testKeys.clear();

        QuadKey key;

        key = new QuadKey(Type.Bing, 0, 1, (short) 2);
        testKeys = key.getNeighbors();
        assertEquals(5, testKeys.size());
        assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 0, 0,
                (short) 2)));
        assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 1, 0,
                (short) 2)));
        assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 1, 1,
                (short) 2)));
        assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 1, 2,
                (short) 2)));
        assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 0, 2,
                (short) 2)));

        testKeys.clear();

        key = new QuadKey(Type.Bing, 0, 2, (short) 2);
        testKeys = key.getNeighbors();
        assertEquals(5, testKeys.size());
        assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 0, 1,
                (short) 2)));
        assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 1, 1,
                (short) 2)));
        assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 1, 2,
                (short) 2)));
        assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 1, 3,
                (short) 2)));
        assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 0, 3,
                (short) 2)));

        testKeys.clear();

        key = new QuadKey(Type.Bing, 0, 3, (short) 2);
        testKeys = key.getNeighbors();
        assertEquals(5, testKeys.size());
        assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 0, 2,
                (short) 2)));
        assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 1, 2,
                (short) 2)));
        assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 1, 3,
                (short) 2)));
        assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 1, 0,
                (short) 2)));
        assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 0, 0,
                (short) 2)));

        testKeys.clear();

        key = new QuadKey(Type.Bing, 1, 0, (short) 2);
        testKeys = key.getNeighbors();
        assertEquals(8, testKeys.size());
        assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 0, 0,
                (short) 2)));
        assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 0, 1,
                (short) 2)));
        assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 1, 1,
                (short) 2)));
        assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 2, 1,
                (short) 2)));
        assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 2, 0,
                (short) 2)));
        assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 2, 3,
                (short) 2)));
        assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 1, 3,
                (short) 2)));
        assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 0, 3,
                (short) 2)));

        testKeys.clear();

        key = new QuadKey(Type.Bing, 1, 1, (short) 2);
        testKeys = key.getNeighbors();
        assertEquals(8, testKeys.size());
        assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 1, 0,
                (short) 2)));
        assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 0, 0,
                (short) 2)));
        assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 0, 1,
                (short) 2)));
        assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 2, 2,
                (short) 2)));
        assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 2, 1,
                (short) 2)));
        assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 2, 0,
                (short) 2)));
        assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 0, 2,
                (short) 2)));
        assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 1, 2,
                (short) 2)));

        testKeys.clear();

        key = new QuadKey(Type.Bing, 1, 2, (short) 2);
        testKeys = key.getNeighbors();
        assertEquals(8, testKeys.size());
        assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 1, 1,
                (short) 2)));
        assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 0, 1,
                (short) 2)));
        assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 0, 2,
                (short) 2)));
        assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 2, 3,
                (short) 2)));
        assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 2, 2,
                (short) 2)));
        assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 2, 1,
                (short) 2)));
        assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 0, 3,
                (short) 2)));
        assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 1, 3,
                (short) 2)));

        testKeys.clear();

        key = new QuadKey(Type.Bing, 1, 3, (short) 2);
        testKeys = key.getNeighbors();
        assertEquals(8, testKeys.size());
        assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 1, 2,
                (short) 2)));
        assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 0, 2,
                (short) 2)));
        assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 0, 3,
                (short) 2)));
        assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 2, 0,
                (short) 2)));
        assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 2, 3,
                (short) 2)));
        assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 2, 2,
                (short) 2)));
        assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 0, 0,
                (short) 2)));
        assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 1, 0,
                (short) 2)));

        testKeys.clear();

        key = new QuadKey(Type.Bing, 4, 7, (short) 3);
        testKeys = key.getNeighbors();
        assertEquals(8, testKeys.size());
        assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 3, 7,
                (short) 3)));
        assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 3, 6,
                (short) 3)));
        assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 4, 6,
                (short) 3)));
        assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 5, 6,
                (short) 3)));
        assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 5, 7,
                (short) 3)));
        assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 5, 0,
                (short) 3)));
        assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 4, 0,
                (short) 3)));
        assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 3, 0,
                (short) 3)));

        testKeys.clear();

        key = new QuadKey(Type.Bing, 4, 0, (short) 3);
        testKeys = key.getNeighbors();
        assertEquals(8, testKeys.size());
        assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 3, 0,
                (short) 3)));
        assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 3, 1,
                (short) 3)));
        assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 4, 1,
                (short) 3)));
        assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 5, 1,
                (short) 3)));
        assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 5, 0,
                (short) 3)));
        assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 5, 7,
                (short) 3)));
        assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 4, 7,
                (short) 3)));
        assertTrue(vectorContains(testKeys, new QuadKey(Type.Bing, 3, 7,
                (short) 3)));

        testKeys.clear();
    }

    @Test
    public void fromInternalStringToStringTest() {
        {
            QuadKey root = QuadKey.fromInternalString(Type.Bing, "");
            assertEquals(0, root.getRow());
            assertEquals(0, root.getCol());
            assertEquals(0, root.getDepth());
        }

        {
            QuadKey key;
            key = QuadKey.fromInternalString(Type.Bing, "0");
            assertEquals(1, key.getRow());
            assertEquals(0, key.getCol());
            assertEquals(1, key.getDepth());
            assertEquals("0", key.toInternalString());
            key = QuadKey.fromInternalString(Type.Bing, "1");
            assertEquals(1, key.getRow());
            assertEquals(1, key.getCol());
            assertEquals(1, key.getDepth());
            assertEquals("1", key.toInternalString());
            key = QuadKey.fromInternalString(Type.Bing, "2");
            assertEquals(0, key.getRow());
            assertEquals(0, key.getCol());
            assertEquals(1, key.getDepth());
            assertEquals("2", key.toInternalString());
            key = QuadKey.fromInternalString(Type.Bing, "3");
            assertEquals(0, key.getRow());
            assertEquals(1, key.getCol());
            assertEquals(1, key.getDepth());
            assertEquals("3", key.toInternalString());
        }

        {
            QuadKey key;
            key = QuadKey.fromInternalString(Type.Bing, "00");
            assertEquals(3, key.getRow());
            assertEquals(0, key.getCol());
            assertEquals(2, key.getDepth());
            assertEquals("00", key.toInternalString());
            key = QuadKey.fromInternalString(Type.Bing, "01");
            assertEquals(3, key.getRow());
            assertEquals(1, key.getCol());
            assertEquals(2, key.getDepth());
            assertEquals("01", key.toInternalString());
            key = QuadKey.fromInternalString(Type.Bing, "02");
            assertEquals(2, key.getRow());
            assertEquals(0, key.getCol());
            assertEquals(2, key.getDepth());
            assertEquals("02", key.toInternalString());
            key = QuadKey.fromInternalString(Type.Bing, "03");
            assertEquals(2, key.getRow());
            assertEquals(1, key.getCol());
            assertEquals(2, key.getDepth());
            assertEquals("03", key.toInternalString());
            key = QuadKey.fromInternalString(Type.Bing, "10");
            assertEquals(3, key.getRow());
            assertEquals(2, key.getCol());
            assertEquals(2, key.getDepth());
            assertEquals("10", key.toInternalString());
            key = QuadKey.fromInternalString(Type.Bing, "11");
            assertEquals(3, key.getRow());
            assertEquals(3, key.getCol());
            assertEquals(2, key.getDepth());
            assertEquals("11", key.toInternalString());
            key = QuadKey.fromInternalString(Type.Bing, "12");
            assertEquals(2, key.getRow());
            assertEquals(2, key.getCol());
            assertEquals(2, key.getDepth());
            assertEquals("12", key.toInternalString());
            key = QuadKey.fromInternalString(Type.Bing, "13");
            assertEquals(2, key.getRow());
            assertEquals(3, key.getCol());
            assertEquals(2, key.getDepth());
            assertEquals("13", key.toInternalString());
            key = QuadKey.fromInternalString(Type.Bing, "20");
            assertEquals(1, key.getRow());
            assertEquals(0, key.getCol());
            assertEquals(2, key.getDepth());
            assertEquals("20", key.toInternalString());
            key = QuadKey.fromInternalString(Type.Bing, "21");
            assertEquals(1, key.getRow());
            assertEquals(1, key.getCol());
            assertEquals(2, key.getDepth());
            assertEquals("21", key.toInternalString());
            key = QuadKey.fromInternalString(Type.Bing, "22");
            assertEquals(0, key.getRow());
            assertEquals(0, key.getCol());
            assertEquals(2, key.getDepth());
            assertEquals("22", key.toInternalString());
            key = QuadKey.fromInternalString(Type.Bing, "23");
            assertEquals(0, key.getRow());
            assertEquals(1, key.getCol());
            assertEquals(2, key.getDepth());
            assertEquals("23", key.toInternalString());
            key = QuadKey.fromInternalString(Type.Bing, "30");
            assertEquals(1, key.getRow());
            assertEquals(2, key.getCol());
            assertEquals(2, key.getDepth());
            assertEquals("30", key.toInternalString());
            key = QuadKey.fromInternalString(Type.Bing, "31");
            assertEquals(1, key.getRow());
            assertEquals(3, key.getCol());
            assertEquals(2, key.getDepth());
            assertEquals("31", key.toInternalString());
            key = QuadKey.fromInternalString(Type.Bing, "32");
            assertEquals(0, key.getRow());
            assertEquals(2, key.getCol());
            assertEquals(2, key.getDepth());
            assertEquals("32", key.toInternalString());
            key = QuadKey.fromInternalString(Type.Bing, "33");
            assertEquals(0, key.getRow());
            assertEquals(3, key.getCol());
            assertEquals(2, key.getDepth());
            assertEquals("33", key.toInternalString());
        }
    }

    @Test
    public void getGeoCoordinateBounds2dTest() {
        QuadKey key;
        GeoCoordinateBoundingBox2d bbox = new GeoCoordinateBoundingBox2d();

        key = QuadKey.fromInternalString(Type.Bing, "");
        key.getGeoCoordinateBounds2d(bbox);
        assertEquals(-180.0, bbox.lowerLeft().longitude().val(), 1e-7);
        assertEquals(-84.9283209, bbox.lowerLeft().latitude().val(), 1e-7);
        assertEquals(178.593750, bbox.upperRight().longitude().val(), 1e-7);
        assertEquals(85.05112877, bbox.upperRight().latitude().val(), 1e-7);
    }

    @Test
    public void getKeyFromLongitudeLatitudeAtDepthToBoundsTest() {
        QuadKey key;
        GeoCoordinateBoundingBox2d bbox = new GeoCoordinateBoundingBox2d();
        double diff;

        { // Depth 0
            key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    Type.Bing, new GeoCoordinate2d(new Longitude(-180.0),
                    new Latitude(-84.0)), (short) 0);
            assertTrue(new QuadKey(Type.Bing, 0, 0, (short) 0).equalTo(key));
            key.getGeoCoordinateBounds2d(bbox);
            diff = Math.abs(bbox.lowerLeft().longitude().longitudeDifference(
                    new Longitude(-180.0)));
            assertTrue(2.0 > diff);
            diff = Math.abs(bbox.lowerLeft().latitude().latitudeDifference(
                    new Latitude(-85.0)));
            assertTrue(2.0 > diff);
            diff = Math.abs(bbox.upperRight().longitude().longitudeDifference(
                    new Longitude(+180.0)));
            assertTrue(2.0 > diff);
            diff = Math.abs(bbox.upperRight().latitude().latitudeDifference(
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
            key = QuadKey.getKeyFromLongitudeLatitudeAtDepth( // Q0 ul
                Type.Bing, new GeoCoordinate2d(left, top), (short) 1);
            assertTrue(new QuadKey(Type.Bing, 1, 0, (short) 1).equalTo(key));
            key = QuadKey.getKeyFromLongitudeLatitudeAtDepth( // Q0 ll
                Type.Bing, new GeoCoordinate2d(left, midTop), (short) 1);
            assertTrue(new QuadKey(Type.Bing, 1, 0, (short) 1).equalTo(key));
            key = QuadKey.getKeyFromLongitudeLatitudeAtDepth( // Q0 lr
                Type.Bing, new GeoCoordinate2d(midLeft, midTop), (short) 1);
            assertTrue(new QuadKey(Type.Bing, 1, 0, (short) 1).equalTo(key));
            key = QuadKey.getKeyFromLongitudeLatitudeAtDepth( // Q0 ur
                Type.Bing, new GeoCoordinate2d(midLeft, top), (short) 1);
            assertTrue(new QuadKey(Type.Bing, 1, 0, (short) 1).equalTo(key));
            key.getGeoCoordinateBounds2d(bbox);
            diff = Math.abs(bbox.lowerLeft().longitude().longitudeDifference(
                    left));
            assertTrue(2.0 > diff);
            diff = Math.abs(bbox.lowerLeft().latitude().latitudeDifference(
                    midTop));
            assertTrue(2.0 > diff);
            diff = Math.abs(bbox.upperRight().longitude().longitudeDifference(
                    midLeft));
            assertTrue(2.0 > diff);
            diff = Math.abs(bbox.upperRight().latitude().latitudeDifference(
                    new Latitude(+85.0)));
            assertTrue(2.0 > diff);

            key = QuadKey.getKeyFromLongitudeLatitudeAtDepth( // Q1 ul
                Type.Bing, new GeoCoordinate2d(midRight, top), (short) 1);
            assertTrue(new QuadKey(Type.Bing, 1, 1, (short) 1).equalTo(key));
            key = QuadKey.getKeyFromLongitudeLatitudeAtDepth( // Q1 ll
                Type.Bing, new GeoCoordinate2d(midRight, midTop), (short) 1);
            assertTrue(new QuadKey(Type.Bing, 1, 1, (short) 1).equalTo(key));
            key = QuadKey.getKeyFromLongitudeLatitudeAtDepth( // Q1 lr
                Type.Bing, new GeoCoordinate2d(right, midTop), (short) 1);
            assertTrue(new QuadKey(Type.Bing, 1, 1, (short) 1).equalTo(key));
            key = QuadKey.getKeyFromLongitudeLatitudeAtDepth( // Q1 ur
                Type.Bing, new GeoCoordinate2d(right, top), (short) 1);
            assertTrue(new QuadKey(Type.Bing, 1, 1, (short) 1).equalTo(key));
            key.getGeoCoordinateBounds2d(bbox);
            diff = Math.abs(bbox.lowerLeft().longitude().longitudeDifference(
                    midRight));
            assertTrue(2.0 > diff);
            diff = Math.abs(bbox.lowerLeft().latitude().latitudeDifference(
                    midTop));
            assertTrue(2.0 > diff);
            diff = Math.abs(bbox.upperRight().longitude().longitudeDifference(
                    right));
            assertTrue(2.0 > diff);
            diff = Math.abs(bbox.upperRight().latitude().latitudeDifference(
                    new Latitude(+85.0)));
            assertTrue(2.0 > diff);

            key = QuadKey.getKeyFromLongitudeLatitudeAtDepth( // Q2 ul
                Type.Bing, new GeoCoordinate2d(left, midBottom), (short) 1);
            assertTrue(new QuadKey(Type.Bing, 0, 0, (short) 1).equalTo(key));
            key = QuadKey.getKeyFromLongitudeLatitudeAtDepth( // Q2 ll
                Type.Bing, new GeoCoordinate2d(left, bottom), (short) 1);
            assertTrue(new QuadKey(Type.Bing, 0, 0, (short) 1).equalTo(key));
            key = QuadKey.getKeyFromLongitudeLatitudeAtDepth( // Q2 lr
                Type.Bing, new GeoCoordinate2d(midLeft, bottom), (short) 1);
            assertTrue(new QuadKey(Type.Bing, 0, 0, (short) 1).equalTo(key));
            key = QuadKey.getKeyFromLongitudeLatitudeAtDepth( // Q2 ur
                Type.Bing, new GeoCoordinate2d(midLeft, midBottom), (short) 1);
            assertTrue(new QuadKey(Type.Bing, 0, 0, (short) 1).equalTo(key));
            key.getGeoCoordinateBounds2d(bbox);
            diff = Math.abs(bbox.lowerLeft().longitude().longitudeDifference(
                    left));
            assertTrue(2.0 > diff);
            diff = Math.abs(bbox.lowerLeft().latitude().latitudeDifference(
                    new Latitude(-85.0)));
            assertTrue(2.0 > diff);
            diff = Math.abs(bbox.upperRight().longitude().longitudeDifference(
                    midLeft));
            assertTrue(2.0 > diff);
            diff = Math.abs(bbox.upperRight().latitude().latitudeDifference(
                    midBottom));
            assertTrue(2.0 > diff);

            key = QuadKey.getKeyFromLongitudeLatitudeAtDepth( // Q3 ul
                Type.Bing, new GeoCoordinate2d(midRight, midBottom), (short) 1);
            assertTrue(new QuadKey(Type.Bing, 0, 1, (short) 1).equalTo(key));
            key = QuadKey.getKeyFromLongitudeLatitudeAtDepth( // Q3 ll
                Type.Bing, new GeoCoordinate2d(midRight, bottom), (short) 1);
            assertTrue(new QuadKey(Type.Bing, 0, 1, (short) 1).equalTo(key));
            key = QuadKey.getKeyFromLongitudeLatitudeAtDepth( // Q3 lr
                Type.Bing, new GeoCoordinate2d(right, bottom), (short) 1);
            assertTrue(new QuadKey(Type.Bing, 0, 1, (short) 1).equalTo(key));
            key = QuadKey.getKeyFromLongitudeLatitudeAtDepth( // Q3 ur
                Type.Bing, new GeoCoordinate2d(right, midBottom), (short) 1);
            assertTrue(new QuadKey(Type.Bing, 0, 1, (short) 1).equalTo(key));
            key.getGeoCoordinateBounds2d(bbox);
            diff = Math.abs(bbox.lowerLeft().longitude().longitudeDifference(
                    midRight));
            assertTrue(2.0 > diff);
            diff = Math.abs(bbox.lowerLeft().latitude().latitudeDifference(
                    new Latitude(-85.0)));
            assertTrue(2.0 > diff);
            diff = Math.abs(bbox.upperRight().longitude().longitudeDifference(
                    right));
            assertTrue(2.0 > diff);
            diff = Math.abs(bbox.upperRight().latitude().latitudeDifference(
                    midBottom));
            assertTrue(2.0 > diff);
        }
    }

    @Test
    public void getKeysFromLongitudeLatitudeBoundingBox() {
        {
            QuadKeyVector outKeys;
            outKeys =QuadKey.getKeysFromLongitudeLatitudeBoundingBox(Type.Bing,
                    new GeoCoordinateBoundingBox2d(
                            new GeoCoordinate2d(
                                    new Longitude(-180.0),
                                    new Latitude(+90.0)),
                            new GeoCoordinate2d(
                                    new Longitude(+180.0),
                                    new Latitude(-90.0))),
                    (short) 0);
            assertEquals(1, outKeys.size());
            assertTrue(vectorContains(outKeys, new QuadKey(Type.Bing, 0, 0,
                    (short) 0)));
        }

        {
            QuadKeyVector outKeys;
            outKeys = QuadKey.getKeysFromLongitudeLatitudeBoundingBox(Type.Bing,
                    new GeoCoordinateBoundingBox2d(
                            new GeoCoordinate2d(
                                    new Longitude(-180.0),
                                    new Latitude(+90.0)),
                            new GeoCoordinate2d(
                                    new Longitude(+180.0),
                                    new Latitude(-90.0))),
                    (short) 1);
            assertEquals(4, outKeys.size());
            assertTrue(vectorContains(outKeys, new QuadKey(Type.Bing, 0, 0,
                    (short) 1)));
            assertTrue(vectorContains(outKeys, new QuadKey(Type.Bing, 0, 1,
                    (short) 1)));
            assertTrue(vectorContains(outKeys, new QuadKey(Type.Bing, 1, 0,
                    (short) 1)));
            assertTrue(vectorContains(outKeys, new QuadKey(Type.Bing, 1, 1,
                    (short) 1)));
        }

        {
            QuadKeyVector outKeys;
            outKeys = QuadKey.getKeysFromLongitudeLatitudeBoundingBox(Type.Bing,
                    new GeoCoordinateBoundingBox2d(
                            new GeoCoordinate2d(
                                    new Longitude(-180.0),
                                    new Latitude(+0.35)),
                            new GeoCoordinate2d(
                                    new Longitude(-0.36),
                                    new Latitude(+90.0))),
                    (short) 1);
            assertEquals(2, outKeys.size());
            assertTrue(vectorContains(outKeys, new QuadKey(Type.Bing, 0, 0,
                    (short) 1)));
            assertTrue(vectorContains(outKeys, new QuadKey(Type.Bing, 1, 0,
                    (short) 1)));
        }

        {
            QuadKeyVector outKeys;
            outKeys = QuadKey.getKeysFromLongitudeLatitudeBoundingBox(Type.Bing,
                    new GeoCoordinateBoundingBox2d(
                            new GeoCoordinate2d(
                                    new Longitude(-0.36),
                                    new Latitude(+0.36)),
                            new GeoCoordinate2d(
                                    new Longitude(+0.36),
                                    new Latitude(+90.0))),
                    (short)1);
            assertEquals(2, outKeys.size());
            assertTrue(vectorContains(outKeys, new QuadKey(Type.Bing, 1, 0,
                    (short) 1)));
            assertTrue(vectorContains(outKeys, new QuadKey(Type.Bing, 1, 1,
                    (short) 1)));
        }

        {
            QuadKeyVector outKeys;
            outKeys = QuadKey.getKeysFromLongitudeLatitudeBoundingBox(Type.Bing,
                    new GeoCoordinateBoundingBox2d(
                            new GeoCoordinate2d(
                                    new Longitude(-0.36),
                                    new Latitude(+0.35)),
                            new GeoCoordinate2d(
                                    new Longitude(+0.36),
                                    new Latitude(+90.0))),
                    (short) 1);
            assertEquals(4, outKeys.size());
            assertTrue(vectorContains(outKeys, new QuadKey(Type.Bing, 0, 0,
                    (short) 1)));
            assertTrue(vectorContains(outKeys, new QuadKey(Type.Bing, 0, 1,
                    (short) 1)));
            assertTrue(vectorContains(outKeys, new QuadKey(Type.Bing, 1, 0,
                    (short) 1)));
            assertTrue(vectorContains(outKeys, new QuadKey(Type.Bing, 1, 1,
                    (short) 1)));
        }
    }

    @Test
    public void selectedCitiesTest() {
        QuadKey key;
        Type type = Type.Bing;

        { // Chicago 41.822, -87.635
            short depth = 16;
            GeoCoordinate2d coords = new GeoCoordinate2d(
                    new Longitude(-87.635), new Latitude(41.822));

            key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(type, coords,
                depth);
            String keyStr = key.toInternalString();
            assertEquals("0302222310321132", keyStr);

            GeoCoordinateBoundingBox2d bbox = new GeoCoordinateBoundingBox2d();
            key.getGeoCoordinateBounds2d(bbox);

            // Note that Bing will return a bounding box of all sides inclusive
            QuadKeyVector keys;
            keys =QuadKey.getKeysFromLongitudeLatitudeBoundingBox(type, bbox,
                depth);
            assertEquals(4, keys.size());
            assertTrue(vectorContains(keys, key));
        }

        { // Rio -43.1964,-22.9083
            short depth = 17;
            GeoCoordinate2d coords = new GeoCoordinate2d(
                    new Longitude(-43.1964), new Latitude(-22.9083));

            key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(type, coords,
                depth);
            String keyStr = key.toInternalString();
            assertEquals("21120001212232200", keyStr);

            GeoCoordinateBoundingBox2d bbox = new GeoCoordinateBoundingBox2d();
            key.getGeoCoordinateBounds2d(bbox);

            // Note that Bing will return a bounding box of all sides inclusive
            QuadKeyVector keys;
            keys = QuadKey.getKeysFromLongitudeLatitudeBoundingBox(type, bbox,
                depth);
            assertEquals(4, keys.size());
            assertTrue(vectorContains(keys, key));
        }

        { // Helsinki 60.1708 N, 24.9375 E
            short depth = 17;
            GeoCoordinate2d coords = new GeoCoordinate2d(
                    new Longitude(24.9375), new Latitude(60.1708));

            key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(type, coords,
                depth);
            String keyStr = key.toInternalString();
            assertEquals("12012021101330131", keyStr);

            GeoCoordinateBoundingBox2d bbox = new GeoCoordinateBoundingBox2d();
            key.getGeoCoordinateBounds2d(bbox);

            // Note that Bing will return a bounding box of all sides inclusive
            QuadKeyVector keys;
            keys = QuadKey.getKeysFromLongitudeLatitudeBoundingBox(type, bbox,
                depth);
            assertEquals(4, keys.size());
            assertTrue(vectorContains(keys, key));
        }

        { // Cape Town South Africa 33.9253 S, 18.4239 E
            short depth = 17;
            GeoCoordinate2d coords = new GeoCoordinate2d(
                    new Longitude(18.4239),
                    new Latitude(-33.9253));

            key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(type, coords,
                depth);
            String keyStr = key.toInternalString();
            assertEquals("30023103202132011", keyStr);

            GeoCoordinateBoundingBox2d bbox = new GeoCoordinateBoundingBox2d();
            key.getGeoCoordinateBounds2d(bbox);

            // Note that Bing will return a bounding box of all sides inclusive
            QuadKeyVector keys;
            keys = QuadKey.getKeysFromLongitudeLatitudeBoundingBox(type, bbox,
                depth);
            assertEquals(4, keys.size());
            assertTrue(vectorContains(keys, key));
        }

        { // Quito 0.2500 S, 78.5833 W
            short depth = 17;
            GeoCoordinate2d coords = new GeoCoordinate2d(
                    new Longitude(-78.5836),
                    new Latitude(-0.25));

            key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(type, coords,
                depth);
            String keyStr = key.toInternalString();
            assertEquals("21001000002133122", keyStr);

            GeoCoordinateBoundingBox2d bbox = new GeoCoordinateBoundingBox2d();
            key.getGeoCoordinateBounds2d(bbox);

            // Note that Bing will return a bounding box of all sides inclusive
            QuadKeyVector keys;
            keys = QuadKey.getKeysFromLongitudeLatitudeBoundingBox(type, bbox,
                depth);
            assertEquals(4, keys.size());
            assertTrue(vectorContains(keys, key));
        }
    }
}

import com.quadkey.*;
import org.junit.BeforeClass;
import org.junit.Test;

import java.util.ArrayList;
import java.util.List;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertTrue;

public class MortonSystemTest {

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

    private boolean vectorContains(QuadKeyVector vect, QuadKey key) {
        boolean found = false;
        for (int i = 0; i < vect.size(); ++i) {
            QuadKey curr = vect.get(i);
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
        // See TestQuadKey TestSpecificCtorTest.
    }

    @Test
    public void isRootKeyTest() {
        // Same as BingSystem
    }

    @Test
    public void getParentTest() {
        // Same as BingSystem
    }

    @Test
    public void isMyAncestorTest() {
        // Same as BingSystem
    }

    @Test
    public void getAncestorTest() {
        {
            QuadKey quadKey = new QuadKey(Type.Morton, 0, 1, (short) 1);
            QuadKey ancestor = new QuadKey(Type.Morton, 0, 0, (short) 0);
            assertTrue(ancestor.equalTo(quadKey.getAncestor((short) 1)));
            assertTrue(quadKey.getParent().equalTo(quadKey.getAncestor(
                    (short) 1)));
        }
        {
            QuadKey quadKey = new QuadKey(Type.Morton, 0, 0, (short) 1);
            QuadKey ancestor = new QuadKey(Type.Morton, 0, 0, (short) 0);
            assertTrue(ancestor.equalTo(quadKey.getAncestor((short) 1)));
            assertTrue(quadKey.getParent().equalTo(quadKey.getAncestor(
                    (short) 1)));
        }
        {
            QuadKey quadKey = new QuadKey(Type.Morton, 1, 1, (short) 1);
            QuadKey ancestor = new QuadKey(Type.Morton, 0, 0, (short) 0);
            assertTrue(ancestor.equalTo(quadKey.getAncestor((short) 1)));
        }
        {
            QuadKey quadKey = new QuadKey(Type.Morton, 1, 2, (short) 1);
            QuadKey ancestor = new QuadKey(Type.Morton, 0, 1, (short) 0);
            assertTrue(ancestor.equalTo(quadKey.getAncestor((short) 1)));
        }
        {
            QuadKey quadKey = new QuadKey(Type.Morton, 0, 2, (short) 1);
            QuadKey ancestor = new QuadKey(Type.Morton, 0, 1, (short) 0);
            assertTrue(ancestor.equalTo(quadKey.getAncestor((short) 1)));
        }
    }

    @Test
    public void getChildTest() {
        // Same as BingSystem
    }

    @Test
    public void getChildrenTest() {
        // Same as BingSystem
    }

    @Test
    public void getDescendantsTest() {
        // Same as BingSystem
    }

    @Test
    public void getSiblingsTest() {
        QuadKeyVector testKeys;
        testKeys = new QuadKey(Type.Morton, 0, 0, (short) 1).getSiblings();
        assertEquals(3, testKeys.size());
        assertTrue(vectorContains(testKeys,
                new QuadKey(Type.Morton, 1, 0, (short) 1)));
        assertTrue(vectorContains(testKeys,
                new QuadKey(Type.Morton, 1, 1, (short) 1)));
        assertTrue(vectorContains(testKeys,
                new QuadKey(Type.Morton, 0, 1, (short) 1)));
        testKeys = new QuadKey(Type.Morton, 1, 3, (short) 1).getSiblings();
        assertEquals(3, testKeys.size());
        assertTrue(vectorContains(testKeys,
                new QuadKey(Type.Morton, 1, 2, (short) 1)));
        assertTrue(vectorContains(testKeys,
                new QuadKey(Type.Morton, 0, 2, (short) 1)));
        assertTrue(vectorContains(testKeys,
                new QuadKey(Type.Morton, 0, 3, (short) 1)));
    }

    @Test
    public void getNeighborsTest() {
        // Same as BingSystem but just to be safe
        QuadKeyVector testKeys;
        testKeys = new QuadKey().getNeighbors();
        assertTrue(testKeys.isEmpty());

        testKeys = new QuadKey(Type.Morton, 0, 0, (short) 2).getNeighbors();
        assertEquals(5, testKeys.size());
        assertTrue(vectorContains(testKeys,
                new QuadKey(Type.Morton, 0, 1, (short) 2)));
        assertTrue(vectorContains(testKeys,
                new QuadKey(Type.Morton, 1, 1, (short) 2)));
        assertTrue(vectorContains(testKeys,
                new QuadKey(Type.Morton, 1, 0, (short) 2)));
        assertTrue(vectorContains(testKeys,
                new QuadKey(Type.Morton, 0, 7, (short) 2)));
        assertTrue(vectorContains(testKeys,
                new QuadKey(Type.Morton, 1, 7, (short) 2)));

        testKeys = new QuadKey(Type.Morton, 0, 1, (short) 2).getNeighbors();
        assertEquals(5, testKeys.size());
        assertTrue(vectorContains(testKeys,
                new QuadKey(Type.Morton, 0, 0, (short) 2)));
        assertTrue(vectorContains(testKeys,
                new QuadKey(Type.Morton, 1, 0, (short) 2)));
        assertTrue(vectorContains(testKeys,
                new QuadKey(Type.Morton, 1, 1, (short) 2)));
        assertTrue(vectorContains(testKeys,
                new QuadKey(Type.Morton, 1, 2, (short) 2)));
        assertTrue(vectorContains(testKeys,
                new QuadKey(Type.Morton, 0, 2, (short) 2)));

        testKeys = new QuadKey(Type.Morton, 0, 2, (short) 2).getNeighbors();
        assertEquals(5, testKeys.size());
        assertTrue(vectorContains(testKeys,
                new QuadKey(Type.Morton, 0, 1, (short) 2)));
        assertTrue(vectorContains(testKeys,
                new QuadKey(Type.Morton, 1, 1, (short) 2)));
        assertTrue(vectorContains(testKeys,
                new QuadKey(Type.Morton, 1, 2, (short) 2)));
        assertTrue(vectorContains(testKeys,
                new QuadKey(Type.Morton, 1, 3, (short) 2)));
        assertTrue(vectorContains(testKeys,
                new QuadKey(Type.Morton, 0, 3, (short) 2)));

        testKeys = new QuadKey(Type.Morton, 0, 3, (short) 2).getNeighbors();
        assertEquals(5, testKeys.size());
        assertTrue(vectorContains(testKeys,
                new QuadKey(Type.Morton, 0, 2, (short) 2)));
        assertTrue(vectorContains(testKeys,
                new QuadKey(Type.Morton, 1, 2, (short) 2)));
        assertTrue(vectorContains(testKeys,
                new QuadKey(Type.Morton, 1, 3, (short) 2)));
        assertTrue(vectorContains(testKeys,
                new QuadKey(Type.Morton, 1, 4, (short) 2)));
        assertTrue(vectorContains(testKeys,
                new QuadKey(Type.Morton, 0, 4, (short) 2)));

        testKeys = new QuadKey(Type.Morton, 0, 0, (short) 2).getNeighbors();
        assertEquals(5, testKeys.size());
        assertTrue(vectorContains(testKeys,
                new QuadKey(Type.Morton, 0, 1, (short) 2)));
        assertTrue(vectorContains(testKeys,
                new QuadKey(Type.Morton, 1, 1, (short) 2)));
        assertTrue(vectorContains(testKeys,
                new QuadKey(Type.Morton, 1, 0, (short) 2)));
        assertTrue(vectorContains(testKeys,
                new QuadKey(Type.Morton, 1, 7, (short) 2)));
        assertTrue(vectorContains(testKeys,
                new QuadKey(Type.Morton, 0, 7, (short) 2)));

        testKeys = new QuadKey(Type.Morton, 3, 1, (short) 2).getNeighbors();
        assertEquals(5, testKeys.size());
        assertTrue(vectorContains(testKeys,
                new QuadKey(Type.Morton, 3, 0, (short) 2)));
        assertTrue(vectorContains(testKeys,
                new QuadKey(Type.Morton, 2, 0, (short) 2)));
        assertTrue(vectorContains(testKeys,
                new QuadKey(Type.Morton, 2, 1, (short) 2)));
        assertTrue(vectorContains(testKeys,
                new QuadKey(Type.Morton, 2, 2, (short) 2)));
        assertTrue(vectorContains(testKeys,
                new QuadKey(Type.Morton, 3, 2, (short) 2)));

        testKeys = new QuadKey(Type.Morton, 3, 2, (short) 2).getNeighbors();
        assertEquals(5, testKeys.size());
        assertTrue(vectorContains(testKeys,
                new QuadKey(Type.Morton, 3, 1, (short) 2)));
        assertTrue(vectorContains(testKeys,
                new QuadKey(Type.Morton, 2, 1, (short) 2)));
        assertTrue(vectorContains(testKeys,
                new QuadKey(Type.Morton, 2, 2, (short) 2)));
        assertTrue(vectorContains(testKeys,
                new QuadKey(Type.Morton, 2, 3, (short) 2)));
        assertTrue(vectorContains(testKeys,
                new QuadKey(Type.Morton, 3, 3, (short) 2)));

        testKeys = new QuadKey(Type.Morton, 3, 3, (short) 2).getNeighbors();
        assertEquals(5, testKeys.size());
        assertTrue(vectorContains(testKeys,
                new QuadKey(Type.Morton, 3, 2, (short) 2)));
        assertTrue(vectorContains(testKeys,
                new QuadKey(Type.Morton, 2, 2, (short) 2)));
        assertTrue(vectorContains(testKeys,
                new QuadKey(Type.Morton, 2, 3, (short) 2)));
        assertTrue(vectorContains(testKeys,
                new QuadKey(Type.Morton, 2, 4, (short) 2)));
        assertTrue(vectorContains(testKeys,
                new QuadKey(Type.Morton, 3, 4, (short) 2)));

        testKeys = new QuadKey(Type.Morton, 4, 7, (short) 3).getNeighbors();
        assertEquals(8, testKeys.size());
        assertTrue(vectorContains(testKeys,
                new QuadKey(Type.Morton, 3, 7, (short) 3)));
        assertTrue(vectorContains(testKeys,
                new QuadKey(Type.Morton, 3, 6, (short) 3)));
        assertTrue(vectorContains(testKeys,
                new QuadKey(Type.Morton, 4, 6, (short) 3)));
        assertTrue(vectorContains(testKeys,
                new QuadKey(Type.Morton, 5, 6, (short) 3)));
        assertTrue(vectorContains(testKeys,
                new QuadKey(Type.Morton, 5, 7, (short) 3)));
        assertTrue(vectorContains(testKeys,
                new QuadKey(Type.Morton, 5, 8, (short) 3)));
        assertTrue(vectorContains(testKeys,
                new QuadKey(Type.Morton, 4, 8, (short) 3)));
        assertTrue(vectorContains(testKeys,
                new QuadKey(Type.Morton, 3, 8, (short) 3)));

        testKeys = new QuadKey(Type.Morton, 4, 0, (short) 3).getNeighbors();
        assertEquals(8, testKeys.size());
        assertTrue(vectorContains(testKeys,
                new QuadKey(Type.Morton, 3, 0, (short) 3)));
        assertTrue(vectorContains(testKeys,
                new QuadKey(Type.Morton, 3, 1, (short) 3)));
        assertTrue(vectorContains(testKeys,
                new QuadKey(Type.Morton, 4, 1, (short) 3)));
        assertTrue(vectorContains(testKeys,
                new QuadKey(Type.Morton, 5, 1, (short) 3)));
        assertTrue(vectorContains(testKeys,
                new QuadKey(Type.Morton, 5, 0, (short) 3)));
        assertTrue(vectorContains(testKeys,
                new QuadKey(Type.Morton, 5, 15, (short) 3)));
        assertTrue(vectorContains(testKeys,
                new QuadKey(Type.Morton, 4, 15, (short) 3)));
        assertTrue(vectorContains(testKeys,
                new QuadKey(Type.Morton, 3, 15, (short) 3)));

        testKeys = new QuadKey(Type.Morton, 0, 0, (short) 0).getNeighbors();
        assertEquals(0, testKeys.size());
    }

    @Test
    public void fromStringToStringTest() {
        // X ==> Unused
        // O ==> Used but never set
        // (0,1) ==> Binary digits
        QuadKey quadKey = new QuadKey(Type.Morton, 0, 0, (short) 0);
        String fmt = quadKey.toInternalString();
        assertEquals("65537", fmt); // XXXX XXXX XXXX XXX1 XXXX XXXX XXXX XXO1
        QuadKey quadKeyBack = QuadKey.fromInternalString(Type.Morton, fmt);
        assertTrue(quadKey.equalTo(quadKeyBack));
        quadKey = new QuadKey(Type.Morton, 0, 1, (short) 0);
        fmt = quadKey.toInternalString();
        assertEquals("65536", fmt); // XXXX XXXX XXXX XXX1 XXXX XXXX XXXX XXO0
        quadKeyBack = QuadKey.fromInternalString(Type.Morton, fmt);
        assertTrue(quadKey.equalTo(quadKeyBack));
        quadKey = new QuadKey(Type.Morton, 0, 0, (short) 1);
        fmt = quadKey.toInternalString();
        assertEquals("131078", fmt); // XXXX XXXX XXXX XX1X XXXX XXXX XXXX O110
        quadKeyBack = QuadKey.fromInternalString(Type.Morton, fmt);
        assertTrue(quadKey.equalTo(quadKeyBack));
        quadKey = new QuadKey(Type.Morton, 0, 1, (short) 1);
        fmt = quadKey.toInternalString();
        assertEquals("131079", fmt); // XXXX XXXX XXXX XX1O OOOO OOOO OOOO O111
        quadKeyBack = QuadKey.fromInternalString(Type.Morton, fmt);
        assertTrue(quadKey.equalTo(quadKeyBack));
        quadKey = new QuadKey(Type.Morton, 0, 2, (short) 1);
        fmt = quadKey.toInternalString();
        assertEquals("131074", fmt); // XXXX XXXX XXXX XX1X XXXX XXXX XXXX O010
        quadKeyBack = QuadKey.fromInternalString(Type.Morton, fmt);
        assertTrue(quadKey.equalTo(quadKeyBack));
        quadKey = new QuadKey(Type.Morton, 0, 3, (short) 1);
        fmt = quadKey.toInternalString();
        assertEquals("131075", fmt); // XXXX XXXX XXXX XX1X XXXX XXXX XXXX O011
        quadKeyBack = QuadKey.fromInternalString(Type.Morton, fmt);
        assertTrue(quadKey.equalTo(quadKeyBack));
        quadKey = new QuadKey(Type.Morton, 1, 0, (short) 1);
        fmt = quadKey.toInternalString();
        assertEquals("131076", fmt); // XXXX XXXX XXXX XX1X XXXX XXXX XXXX O100
        quadKeyBack = QuadKey.fromInternalString(Type.Morton, fmt);
        assertTrue(quadKey.equalTo(quadKeyBack));
        quadKey = new QuadKey(Type.Morton, 1, 1, (short) 1);
        fmt = quadKey.toInternalString();
        assertEquals("131077", fmt); // XXXX XXXX XXXX XX1X XXXX XXXX XXXX O101
        quadKeyBack = QuadKey.fromInternalString(Type.Morton, fmt);
        assertTrue(quadKey.equalTo(quadKeyBack));
        quadKey = new QuadKey(Type.Morton, 1, 2, (short) 1);
        fmt = quadKey.toInternalString();
        assertEquals("131072", fmt); // XXXX XXXX XXXX XX1X XXXX XXXX XXXX O000
        quadKeyBack = QuadKey.fromInternalString(Type.Morton, fmt);
        assertTrue(quadKey.equalTo(quadKeyBack));
        quadKey = new QuadKey(Type.Morton, 1, 3, (short) 1);
        fmt = quadKey.toInternalString();
        assertEquals("131073", fmt); // XXXX XXXX XXXX XX1X XXXX XXXX XXXX O001
        quadKeyBack = QuadKey.fromInternalString(Type.Morton, fmt);
        assertTrue(quadKey.equalTo(quadKeyBack));
        quadKey = new QuadKey(Type.Morton, 0, 0, (short) 2);
        fmt = quadKey.toInternalString();
        assertEquals("262168", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO1 1000
        quadKeyBack = QuadKey.fromInternalString(Type.Morton, fmt);
        assertTrue(quadKey.equalTo(quadKeyBack));
        quadKey = new QuadKey(Type.Morton, 0, 1, (short) 2);
        fmt = quadKey.toInternalString();
        assertEquals("262169", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO1 1001
        quadKeyBack = QuadKey.fromInternalString(Type.Morton, fmt);
        assertTrue(quadKey.equalTo(quadKeyBack));
        quadKey = new QuadKey(Type.Morton, 0, 2, (short) 2);
        fmt = quadKey.toInternalString();
        assertEquals("262172", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO1 1100
        quadKeyBack = QuadKey.fromInternalString(Type.Morton, fmt);
        assertTrue(quadKey.equalTo(quadKeyBack));
        quadKey = new QuadKey(Type.Morton, 0, 3, (short) 2);
        fmt = quadKey.toInternalString();
        assertEquals("262173", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO1 1101
        quadKeyBack = QuadKey.fromInternalString(Type.Morton, fmt);
        assertTrue(quadKey.equalTo(quadKeyBack));
        quadKey = new QuadKey(Type.Morton, 0, 4, (short) 2);
        fmt = quadKey.toInternalString();
        assertEquals("262152", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO0 1000
        quadKeyBack = QuadKey.fromInternalString(Type.Morton, fmt);
        assertTrue(quadKey.equalTo(quadKeyBack));
        quadKey = new QuadKey(Type.Morton, 0, 5, (short) 2);
        fmt = quadKey.toInternalString();
        assertEquals("262153", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO0 1001
        quadKeyBack = QuadKey.fromInternalString(Type.Morton, fmt);
        assertTrue(quadKey.equalTo(quadKeyBack));
        quadKey = new QuadKey(Type.Morton, 0, 6, (short) 2);
        fmt = quadKey.toInternalString();
        assertEquals("262156", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO0 1100
        quadKeyBack = QuadKey.fromInternalString(Type.Morton, fmt);
        assertTrue(quadKey.equalTo(quadKeyBack));
        quadKey = new QuadKey(Type.Morton, 0, 7, (short) 2);
        fmt = quadKey.toInternalString();
        assertEquals("262157", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO0 1101
        quadKeyBack = QuadKey.fromInternalString(Type.Morton, fmt);
        assertTrue(quadKey.equalTo(quadKeyBack));
        quadKey = new QuadKey(Type.Morton, 1, 0, (short) 2);
        fmt = quadKey.toInternalString();
        assertEquals("262170", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO1 1010
        quadKeyBack = QuadKey.fromInternalString(Type.Morton, fmt);
        assertTrue(quadKey.equalTo(quadKeyBack));
        quadKey = new QuadKey(Type.Morton, 1, 1, (short) 2);
        fmt = quadKey.toInternalString();
        assertEquals("262171", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO1 1011
        quadKeyBack = QuadKey.fromInternalString(Type.Morton, fmt);
        assertTrue(quadKey.equalTo(quadKeyBack));
        quadKey = new QuadKey(Type.Morton, 1, 2, (short) 2);
        fmt = quadKey.toInternalString();
        assertEquals("262174", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO1 1110
        quadKeyBack = QuadKey.fromInternalString(Type.Morton, fmt);
        assertTrue(quadKey.equalTo(quadKeyBack));
        quadKey = new QuadKey(Type.Morton, 1, 3, (short) 2);
        fmt = quadKey.toInternalString();
        assertEquals("262175", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO1 1111
        quadKeyBack = QuadKey.fromInternalString(Type.Morton, fmt);
        assertTrue(quadKey.equalTo(quadKeyBack));
        quadKey = new QuadKey(Type.Morton, 1, 4, (short) 2);
        fmt = quadKey.toInternalString();
        assertEquals("262154", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO0 1010
        quadKeyBack = QuadKey.fromInternalString(Type.Morton, fmt);
        assertTrue(quadKey.equalTo(quadKeyBack));
        quadKey = new QuadKey(Type.Morton, 1, 5, (short) 2);
        fmt = quadKey.toInternalString();
        assertEquals("262155", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO0 1011
        quadKeyBack = QuadKey.fromInternalString(Type.Morton, fmt);
        assertTrue(quadKey.equalTo(quadKeyBack));
        quadKey = new QuadKey(Type.Morton, 1, 6, (short) 2);
        fmt = quadKey.toInternalString();
        assertEquals("262158", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO0 1110
        quadKeyBack = QuadKey.fromInternalString(Type.Morton, fmt);
        assertTrue(quadKey.equalTo(quadKeyBack));
        quadKey = new QuadKey(Type.Morton, 1, 7, (short) 2);
        fmt = quadKey.toInternalString();
        assertEquals("262159", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO0 1111
        quadKeyBack = QuadKey.fromInternalString(Type.Morton, fmt);
        assertTrue(quadKey.equalTo(quadKeyBack));
        quadKey = new QuadKey(Type.Morton, 2, 0, (short) 2);
        fmt = quadKey.toInternalString();
        assertEquals("262160", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO1 0000
        quadKeyBack = QuadKey.fromInternalString(Type.Morton, fmt);
        assertTrue(quadKey.equalTo(quadKeyBack));
        quadKey = new QuadKey(Type.Morton, 2, 1, (short) 2);
        fmt = quadKey.toInternalString();
        assertEquals("262161", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO1 0001
        quadKeyBack = QuadKey.fromInternalString(Type.Morton, fmt);
        assertTrue(quadKey.equalTo(quadKeyBack));
        quadKey = new QuadKey(Type.Morton, 2, 2, (short) 2);
        fmt = quadKey.toInternalString();
        assertEquals("262164", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO1 0100
        quadKeyBack = QuadKey.fromInternalString(Type.Morton, fmt);
        assertTrue(quadKey.equalTo(quadKeyBack));
        quadKey = new QuadKey(Type.Morton, 2, 3, (short) 2);
        fmt = quadKey.toInternalString();
        assertEquals("262165", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO1 0101
        quadKeyBack = QuadKey.fromInternalString(Type.Morton, fmt);
        assertTrue(quadKey.equalTo(quadKeyBack));
        quadKey = new QuadKey(Type.Morton, 2, 4, (short) 2);
        fmt = quadKey.toInternalString();
        assertEquals("262144", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO0 0000
        quadKeyBack = QuadKey.fromInternalString(Type.Morton, fmt);
        assertTrue(quadKey.equalTo(quadKeyBack));
        quadKey = new QuadKey(Type.Morton, 2, 5, (short) 2);
        fmt = quadKey.toInternalString();
        assertEquals("262145", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO0 0001
        quadKeyBack = QuadKey.fromInternalString(Type.Morton, fmt);
        assertTrue(quadKey.equalTo(quadKeyBack));
        quadKey = new QuadKey(Type.Morton, 2, 6, (short) 2);
        fmt = quadKey.toInternalString();
        assertEquals("262148", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO0 0100
        quadKeyBack = QuadKey.fromInternalString(Type.Morton, fmt);
        assertTrue(quadKey.equalTo(quadKeyBack));
        quadKey = new QuadKey(Type.Morton, 2, 7, (short) 2);
        fmt = quadKey.toInternalString();
        assertEquals("262149", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO0 0101
        quadKeyBack = QuadKey.fromInternalString(Type.Morton, fmt);
        assertTrue(quadKey.equalTo(quadKeyBack));
        quadKey = new QuadKey(Type.Morton, 3, 0, (short) 2);
        fmt = quadKey.toInternalString();
        assertEquals("262162", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO1 0010
        quadKeyBack = QuadKey.fromInternalString(Type.Morton, fmt);
        assertTrue(quadKey.equalTo(quadKeyBack));
        quadKey = new QuadKey(Type.Morton, 3, 1, (short) 2);
        fmt = quadKey.toInternalString();
        assertEquals("262163", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO1 0011
        quadKeyBack = QuadKey.fromInternalString(Type.Morton, fmt);
        assertTrue(quadKey.equalTo(quadKeyBack));
        quadKey = new QuadKey(Type.Morton, 3, 2, (short) 2);
        fmt = quadKey.toInternalString();
        assertEquals("262166", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO1 0110
        quadKeyBack = QuadKey.fromInternalString(Type.Morton, fmt);
        assertTrue(quadKey.equalTo(quadKeyBack));
        quadKey = new QuadKey(Type.Morton, 3, 3, (short) 2);
        fmt = quadKey.toInternalString();
        assertEquals("262167", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO1 0111
        quadKeyBack = QuadKey.fromInternalString(Type.Morton, fmt);
        assertTrue(quadKey.equalTo(quadKeyBack));
        quadKey = new QuadKey(Type.Morton, 3, 4, (short) 2);
        fmt = quadKey.toInternalString();
        assertEquals("262146", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO0 0010
        quadKeyBack = QuadKey.fromInternalString(Type.Morton, fmt);
        assertTrue(quadKey.equalTo(quadKeyBack));
        quadKey = new QuadKey(Type.Morton, 3, 5, (short) 2);
        fmt = quadKey.toInternalString();
        assertEquals("262147", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO0 0011
        quadKeyBack = QuadKey.fromInternalString(Type.Morton, fmt);
        assertTrue(quadKey.equalTo(quadKeyBack));
        quadKey = new QuadKey(Type.Morton, 3, 6, (short) 2);
        fmt = quadKey.toInternalString();
        assertEquals("262150", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO0 0110
        quadKeyBack = QuadKey.fromInternalString(Type.Morton, fmt);
        assertTrue(quadKey.equalTo(quadKeyBack));
        quadKey = new QuadKey(Type.Morton, 3, 7, (short) 2);
        fmt = quadKey.toInternalString();
        assertEquals("262151", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO0 0111
        quadKeyBack = QuadKey.fromInternalString(Type.Morton, fmt);
        assertTrue(quadKey.equalTo(quadKeyBack));
    }

    @Test
    public void getGeoCoordinateBounds2dTest() {
        QuadKey quadKey;
        GeoCoordinateBoundingBox2d bbox = new GeoCoordinateBoundingBox2d();
        quadKey = new QuadKey(Type.Morton, 0, 0, (short) 0);
        quadKey.getGeoCoordinateBounds2d(bbox);
        assertTrue(bbox.lowerLeft().near(new GeoCoordinate2d(
                new Longitude(-180.0), new Latitude(-90.0)), 1e-4));
        assertTrue(bbox.upperRight().near(new GeoCoordinate2d(
                new Longitude(-0.1), new Latitude(+90.0)), 1e-4));

        quadKey = new QuadKey(Type.Morton, 0, 1, (short) 0);
        quadKey.getGeoCoordinateBounds2d(bbox);
        assertTrue(bbox.lowerLeft().near(new GeoCoordinate2d(
                new Longitude(+0.0), new Latitude(-90.0)), 1e-4));
        assertTrue(bbox.upperRight().near(new GeoCoordinate2d(
                new Longitude(+180.0), new Latitude(+90.0)), 1e-4));

        quadKey = new QuadKey(Type.Morton, 0, 0, (short) 1);
        quadKey.getGeoCoordinateBounds2d(bbox);
        assertTrue(bbox.lowerLeft().near(new GeoCoordinate2d(
                new Longitude(-180.0), new Latitude(-90.0)), 1e-4));
        assertTrue(bbox.upperRight().near(new GeoCoordinate2d(
                new Longitude(-90.0), new Latitude(+0.0)), 1e-4));

        quadKey = new QuadKey(Type.Morton, 0, 1, (short) 1);
        quadKey.getGeoCoordinateBounds2d(bbox);
        assertTrue(bbox.lowerLeft().near(new GeoCoordinate2d(
                new Longitude(-90.0), new Latitude(-90.0)), 1e-4));
        assertTrue(bbox.upperRight().near(new GeoCoordinate2d(
                new Longitude(+0.0), new Latitude(+0.0)), 1e-4));

        quadKey = new QuadKey(Type.Morton, 0, 2, (short) 1);
        quadKey.getGeoCoordinateBounds2d(bbox);
        assertTrue(bbox.lowerLeft().near(new GeoCoordinate2d(
                new Longitude(+0.0), new Latitude(-90.0)), 1e-4));
        assertTrue(bbox.upperRight().near(new GeoCoordinate2d(
                new Longitude(+90.0), new Latitude(+0.0)), 1e-4));

        quadKey = new QuadKey(Type.Morton, 0, 3, (short) 1);
        quadKey.getGeoCoordinateBounds2d(bbox);
        assertTrue(bbox.lowerLeft().near(new GeoCoordinate2d(
                new Longitude(+90.0), new Latitude(-90.0)), 1e-4));
        assertTrue(bbox.upperRight().near(new GeoCoordinate2d(
                new Longitude(+180.0), new Latitude(+0.0)), 1e-4));

        quadKey = new QuadKey(Type.Morton, 1, 0, (short) 1);
        quadKey.getGeoCoordinateBounds2d(bbox);
        assertTrue(bbox.lowerLeft().near(new GeoCoordinate2d(
                new Longitude(-180.0), new Latitude(+0.0)), 1e-4));
        assertTrue(bbox.upperRight().near(new GeoCoordinate2d(
                new Longitude(-90.0), new Latitude(+90.0)), 1e-4));

        quadKey = new QuadKey(Type.Morton, 1, 1, (short) 1);
        quadKey.getGeoCoordinateBounds2d(bbox);
        assertTrue(bbox.lowerLeft().near(new GeoCoordinate2d(
                new Longitude(-90.0), new Latitude(+0.0)), 1e-4));
        assertTrue(bbox.upperRight().near(new GeoCoordinate2d(
                new Longitude(+0.0), new Latitude(+90.0)), 1e-4));

        quadKey = new QuadKey(Type.Morton, 1, 2, (short) 1);
        quadKey.getGeoCoordinateBounds2d(bbox);
        assertTrue(bbox.lowerLeft().near(new GeoCoordinate2d(
                new Longitude(+0.0), new Latitude(+0.0)), 1e-4));
        assertTrue(bbox.upperRight().near(new GeoCoordinate2d(
                new Longitude(+90.0), new Latitude(+90.0)), 1e-4));

        quadKey = new QuadKey(Type.Morton, 1, 3, (short) 1);
        quadKey.getGeoCoordinateBounds2d(bbox);
        assertTrue(bbox.lowerLeft().near(new GeoCoordinate2d(
                new Longitude(+90.0), new Latitude(+0.0)), 1e-4));
        assertTrue(bbox.upperRight().near(new GeoCoordinate2d(
                new Longitude(+180.0), new Latitude(+90.0)), 1e-4));
    }

    @Test
    public void getKeyFromLongitudeLatitudeAtDepthToBoundsTest() {
        GeoCoordinate2d coords;
        short depth = 0;
        { // West
            QuadKey ndsKey;
            coords = new GeoCoordinate2d(new Longitude(-0.1),
                    new Latitude(0.0));
            ndsKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    Type.Morton, coords, depth);
            assertEquals("65537", ndsKey.toInternalString());
            coords = new GeoCoordinate2d(new Longitude(-180.0),
                    new Latitude(90.0));
            ndsKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    Type.Morton, coords, depth);
            assertEquals("65537", ndsKey.toInternalString());
            coords = new GeoCoordinate2d(new Longitude(-180.0),
                    new Latitude(-90.0));
            ndsKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    Type.Morton, coords, depth);
            assertEquals("65537", ndsKey.toInternalString());
            GeoCoordinateBoundingBox2d actual =
                    new GeoCoordinateBoundingBox2d();
            ndsKey.getGeoCoordinateBounds2d(actual);
            assertTrue(new GeoCoordinate2d(new Longitude(-180.0),
                    new Latitude(-90.0)).near(actual.lowerLeft(), 1));
            assertTrue(new GeoCoordinate2d(new Longitude(-0.1),
                    new Latitude(+90.0)).near(actual.upperRight(), 1));
        }
        { // East
            QuadKey ndsKey;
            coords = new GeoCoordinate2d(new Longitude(0.0),
                    new Latitude(0.0));
            ndsKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    Type.Morton, coords, depth);
            assertEquals("65536", ndsKey.toInternalString());
            coords = new GeoCoordinate2d(new Longitude(180.0),
                    new Latitude(-90.0));
            ndsKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    Type.Morton, coords, depth);
            assertEquals("65536", ndsKey.toInternalString());
            coords = new GeoCoordinate2d(new Longitude(180.0),
                    new Latitude(90.0));
            ndsKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    Type.Morton, coords, depth);
            assertEquals("65536", ndsKey.toInternalString());
            GeoCoordinateBoundingBox2d actual =
                    new GeoCoordinateBoundingBox2d();
            ndsKey.getGeoCoordinateBounds2d(actual);
            assertTrue(new GeoCoordinate2d(new Longitude(+0.0),
                    new Latitude(-90.0)).near(actual.lowerLeft(), 1));
            assertTrue(new GeoCoordinate2d(new Longitude(+180.0),
                    new Latitude(+90.0)).near(actual.upperRight(), 1));
        }
        depth = 1;
        { // 0x6
            QuadKey ndsKey;
            coords = new GeoCoordinate2d(new Longitude(-180.0),
                    new Latitude(-0.1));
            ndsKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    Type.Morton, coords, depth);
            assertEquals("131078", ndsKey.toInternalString());
            coords = new GeoCoordinate2d(new Longitude(-180.0),
                    new Latitude(-90.0));
            ndsKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    Type.Morton, coords, depth);
            assertEquals("131078", ndsKey.toInternalString());
            coords = new GeoCoordinate2d(new Longitude(-90.1),
                    new Latitude(-90.0));
            ndsKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    Type.Morton, coords, depth);
            assertEquals("131078", ndsKey.toInternalString());
            coords = new GeoCoordinate2d(new Longitude(-90.1),
                    new Latitude(-0.1));
            ndsKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    Type.Morton, coords, depth);
            assertEquals("131078", ndsKey.toInternalString());
        }
        { // 0x7
            QuadKey ndsKey;
            coords = new GeoCoordinate2d(new Longitude(-90.0),
                    new Latitude(-0.1));
            ndsKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    Type.Morton, coords, depth);
            assertEquals("131079", ndsKey.toInternalString());
            coords = new GeoCoordinate2d(new Longitude(-90.0),
                    new Latitude(-90.0));
            ndsKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    Type.Morton, coords, depth);
            assertEquals("131079", ndsKey.toInternalString());
            coords = new GeoCoordinate2d(new Longitude(-0.1),
                    new Latitude(-90.0));
            ndsKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    Type.Morton, coords, depth);
            assertEquals("131079", ndsKey.toInternalString());
            coords = new GeoCoordinate2d(new Longitude(-0.1),
                    new Latitude(-0.1));
            ndsKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    Type.Morton, coords, depth);
            assertEquals("131079", ndsKey.toInternalString());
        }
        { // 0x2
            QuadKey ndsKey;
            coords = new GeoCoordinate2d(new Longitude(0.0),
                    new Latitude(-0.1));
            ndsKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    Type.Morton, coords, depth);
            assertEquals("131074", ndsKey.toInternalString());
            coords = new GeoCoordinate2d(new Longitude(0.0),
                    new Latitude(-90.0));
            ndsKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    Type.Morton, coords, depth);
            assertEquals("131074", ndsKey.toInternalString());
            coords = new GeoCoordinate2d(new Longitude(90.0),
                    new Latitude(-90.0));
            ndsKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    Type.Morton, coords, depth);
            assertEquals("131074", ndsKey.toInternalString());
            coords = new GeoCoordinate2d(new Longitude(90.0),
                    new Latitude(-0.1));
            ndsKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    Type.Morton, coords, depth);
            assertEquals("131074", ndsKey.toInternalString());
        }
        { // 0x3
            QuadKey ndsKey;
            coords = new GeoCoordinate2d(new Longitude(90.1),
                    new Latitude(-0.1));
            ndsKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    Type.Morton, coords, depth);
            assertEquals("131075", ndsKey.toInternalString());
            coords = new GeoCoordinate2d(new Longitude(90.1),
                    new Latitude(-90.0));
            ndsKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    Type.Morton, coords, depth);
            assertEquals("131075", ndsKey.toInternalString());
            coords = new GeoCoordinate2d(new Longitude(180.0),
                    new Latitude(-90.0));
            ndsKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    Type.Morton, coords, depth);
            assertEquals("131075", ndsKey.toInternalString());
            coords = new GeoCoordinate2d(new Longitude(180.0),
                    new Latitude(-0.1));
            ndsKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    Type.Morton, coords, depth);
            assertEquals("131075", ndsKey.toInternalString());
        }
        { // 0x4
            QuadKey ndsKey;
            coords = new GeoCoordinate2d(new Longitude(-180.0),
                    new Latitude(90.0));
            ndsKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    Type.Morton, coords, depth);
            assertEquals("131076", ndsKey.toInternalString());
            coords = new GeoCoordinate2d(new Longitude(-180.0),
                    new Latitude(0.0));
            ndsKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    Type.Morton, coords, depth);
            assertEquals("131076", ndsKey.toInternalString());
            coords = new GeoCoordinate2d(new Longitude(-90.1),
                    new Latitude(0.0));
            ndsKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    Type.Morton, coords, depth);
            assertEquals("131076", ndsKey.toInternalString());
            coords = new GeoCoordinate2d(new Longitude(-90.1),
                    new Latitude(90.0));
            ndsKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    Type.Morton, coords, depth);
            assertEquals("131076", ndsKey.toInternalString());
        }
        { // 0x5
            QuadKey ndsKey;
            coords = new GeoCoordinate2d(new Longitude(-90.0),
                    new Latitude(90.0));
            ndsKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    Type.Morton, coords, depth);
            assertEquals("131077", ndsKey.toInternalString());
            coords = new GeoCoordinate2d(new Longitude(-90.0),
                    new Latitude(0.0));
            ndsKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    Type.Morton, coords, depth);
            assertEquals("131077", ndsKey.toInternalString());
            coords = new GeoCoordinate2d(new Longitude(-0.1),
                    new Latitude(0.0));
            ndsKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    Type.Morton, coords, depth);
            assertEquals("131077", ndsKey.toInternalString());
            coords = new GeoCoordinate2d(new Longitude(-0.1),
                    new Latitude(90.0));
            ndsKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    Type.Morton, coords, depth);
            assertEquals("131077", ndsKey.toInternalString());
        }
        { // 0x0
            QuadKey ndsKey;
            coords = new GeoCoordinate2d(new Longitude(0.0),
                    new Latitude(90.0));
            ndsKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    Type.Morton, coords, depth);
            assertEquals("131072", ndsKey.toInternalString());
            coords = new GeoCoordinate2d(new Longitude(0.0),
                    new Latitude(0.0));
            ndsKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    Type.Morton, coords, depth);
            assertEquals("131072", ndsKey.toInternalString());
            coords = new GeoCoordinate2d(new Longitude(90.0),
                    new Latitude(0.0));
            ndsKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    Type.Morton, coords, depth);
            assertEquals("131072", ndsKey.toInternalString());
            coords = new GeoCoordinate2d(new Longitude(90.0),
                    new Latitude(90.0));
            ndsKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    Type.Morton, coords, depth);
            assertEquals("131072", ndsKey.toInternalString());
        }
        { // 0x1
            QuadKey ndsKey;
            coords = new GeoCoordinate2d(new Longitude(90.1),
                    new Latitude(90.0));
            ndsKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    Type.Morton, coords, depth);
            assertEquals("131073", ndsKey.toInternalString());
            coords = new GeoCoordinate2d(new Longitude(90.1),
                    new Latitude(0.0));
            ndsKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    Type.Morton, coords, depth);
            assertEquals("131073", ndsKey.toInternalString());
            coords = new GeoCoordinate2d(new Longitude(180.0),
                    new Latitude(0.0));
            ndsKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    Type.Morton, coords, depth);
            assertEquals("131073", ndsKey.toInternalString());
            coords = new GeoCoordinate2d(new Longitude(180.0),
                    new Latitude(90.0));
            ndsKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    Type.Morton, coords, depth);
            assertEquals("131073", ndsKey.toInternalString());
        }
        depth = 2;
        List<Pair<GeoCoordinateBoundingBox2d, String>> tests =
                new ArrayList<>();

        tests.add(new Pair<>(
                new GeoCoordinateBoundingBox2d(
                        new GeoCoordinate2d(new Longitude(-180.0),
                                new Latitude(-90.0)),
                        new GeoCoordinate2d(new Longitude(-135.1),
                                new Latitude(-45.1))),
                "262168"));
        tests.add(new Pair<>(
                new GeoCoordinateBoundingBox2d(
                        new GeoCoordinate2d(new Longitude(-135.0),
                                new Latitude(-90.0)),
                        new GeoCoordinate2d(new Longitude(-90.1),
                                new Latitude(-45.1))),
                "262169"));
        tests.add(new Pair<>(
                new GeoCoordinateBoundingBox2d(
                        new GeoCoordinate2d(new Longitude(-90.0),
                                new Latitude(-90.0)),
                        new GeoCoordinate2d(new Longitude(-45.1),
                                new Latitude(-45.1))),
                "262172"));
        tests.add(new Pair<>(
                new GeoCoordinateBoundingBox2d(
                        new GeoCoordinate2d(new Longitude(-45.0),
                                new Latitude(-90.0)),
                        new GeoCoordinate2d(new Longitude(-0.1),
                                new Latitude(-45.1))),
                "262173"));
        tests.add(new Pair<>(
                new GeoCoordinateBoundingBox2d(
                        new GeoCoordinate2d(new Longitude(+0.0),
                                new Latitude(-90.0)),
                        new GeoCoordinate2d(new Longitude(+45.0),
                                new Latitude(-45.1))),
                "262152"));
        tests.add(new Pair<>(
                new GeoCoordinateBoundingBox2d(
                        new GeoCoordinate2d(new Longitude(+45.1),
                                new Latitude(-90.0)),
                        new GeoCoordinate2d(new Longitude(+90.0),
                                new Latitude(-45.1))),
                "262153"));
        tests.add(new Pair<>(
                new GeoCoordinateBoundingBox2d(
                        new GeoCoordinate2d(new Longitude(+90.1),
                                new Latitude(-90.0)),
                        new GeoCoordinate2d(new Longitude(+135.0),
                                new Latitude(-45.1))),
                "262156"));
        tests.add(new Pair<>(
                new GeoCoordinateBoundingBox2d(
                        new GeoCoordinate2d(new Longitude(+135.1),
                                new Latitude(-90.0)),
                        new GeoCoordinate2d(new Longitude(+180.0),
                                new Latitude(-45.1))),
                "262157"));
        tests.add(new Pair<>(
                new GeoCoordinateBoundingBox2d(
                        new GeoCoordinate2d(new Longitude(-180.0),
                                new Latitude(-45.0)),
                        new GeoCoordinate2d(new Longitude(-135.1),
                                new Latitude(-0.1))),
                "262170"));
        tests.add(new Pair<>(
                new GeoCoordinateBoundingBox2d(
                        new GeoCoordinate2d(new Longitude(-135.0),
                                new Latitude(-45.0)),
                        new GeoCoordinate2d(new Longitude(-90.1),
                                new Latitude(-0.1))),
                "262171"));
        tests.add(new Pair<>(
                new GeoCoordinateBoundingBox2d(
                        new GeoCoordinate2d(new Longitude(-90.0),
                                new Latitude(-45.0)),
                        new GeoCoordinate2d(new Longitude(-45.1),
                                new Latitude(-0.1))),
                "262174"));
        tests.add(new Pair<>(
                new GeoCoordinateBoundingBox2d(
                        new GeoCoordinate2d(new Longitude(-45.0),
                                new Latitude(-45.0)),
                        new GeoCoordinate2d(new Longitude(-0.1),
                                new Latitude(-0.1))),
                "262175"));
        tests.add(new Pair<>(
                new GeoCoordinateBoundingBox2d(
                        new GeoCoordinate2d(new Longitude(+0.0),
                                new Latitude(-45.0)),
                        new GeoCoordinate2d(new Longitude(+45.0),
                                new Latitude(-0.1))),
                "262154"));
        tests.add(new Pair<>(
                new GeoCoordinateBoundingBox2d(
                        new GeoCoordinate2d(new Longitude(+45.1),
                                new Latitude(-45.0)),
                        new GeoCoordinate2d(new Longitude(+90.0),
                                new Latitude(-0.1))),
                "262155"));
        tests.add(new Pair<>(
                new GeoCoordinateBoundingBox2d(
                        new GeoCoordinate2d(new Longitude(+90.1),
                                new Latitude(-45.0)),
                        new GeoCoordinate2d(new Longitude(+135.0),
                                new Latitude(-0.1))),
                "262158"));
        tests.add(new Pair<>(
                new GeoCoordinateBoundingBox2d(
                        new GeoCoordinate2d(new Longitude(+135.1),
                                new Latitude(-45.0)),
                        new GeoCoordinate2d(new Longitude(+180.0),
                                new Latitude(-0.1))),
                "262159"));
        tests.add(new Pair<>(
                new GeoCoordinateBoundingBox2d(
                        new GeoCoordinate2d(new Longitude(-180.0),
                                new Latitude(+0.0)),
                        new GeoCoordinate2d(new Longitude(-135.1),
                                new Latitude(+45.0))),
                "262160"));
        tests.add(new Pair<>(
                new GeoCoordinateBoundingBox2d(
                        new GeoCoordinate2d(new Longitude(-135.0),
                                new Latitude(+0.0)),
                        new GeoCoordinate2d(new Longitude(-90.1),
                                new Latitude(+45.0))),
                "262161"));
        tests.add(new Pair<>(
                new GeoCoordinateBoundingBox2d(
                        new GeoCoordinate2d(new Longitude(-90.0),
                                new Latitude(+0.0)),
                        new GeoCoordinate2d(new Longitude(-45.1),
                                new Latitude(+45.0))),
                "262164"));
        tests.add(new Pair<>(
                new GeoCoordinateBoundingBox2d(
                        new GeoCoordinate2d(new Longitude(-45.0),
                                new Latitude(+0.0)),
                        new GeoCoordinate2d(new Longitude(-0.1),
                                new Latitude(+45.0))),
                "262165"));
        tests.add(new Pair<>(
                new GeoCoordinateBoundingBox2d(
                        new GeoCoordinate2d(new Longitude(+0.0),
                                new Latitude(+0.0)),
                        new GeoCoordinate2d(new Longitude(+45.0),
                                new Latitude(+45.0))),
                "262144"));
        tests.add(new Pair<>(
                new GeoCoordinateBoundingBox2d(
                        new GeoCoordinate2d(new Longitude(+45.1),
                                new Latitude(+0.0)),
                        new GeoCoordinate2d(new Longitude(+90.0),
                                new Latitude(+45.0))),
                "262145"));
        tests.add(new Pair<>(
                new GeoCoordinateBoundingBox2d(
                        new GeoCoordinate2d(new Longitude(+90.1),
                                new Latitude(+0.0)),
                        new GeoCoordinate2d(new Longitude(+135.0),
                                new Latitude(+45.0))),
                "262148"));
        tests.add(new Pair<>(
                new GeoCoordinateBoundingBox2d(
                        new GeoCoordinate2d(new Longitude(+135.1),
                                new Latitude(+0.0)),
                        new GeoCoordinate2d(new Longitude(+180.0),
                                new Latitude(+45.0))),
                "262149"));
        tests.add(new Pair<>(
                new GeoCoordinateBoundingBox2d(
                        new GeoCoordinate2d(new Longitude(-180.0),
                                new Latitude(+45.1)),
                        new GeoCoordinate2d(new Longitude(-135.1),
                                new Latitude(+90.0))),
                "262162"));
        tests.add(new Pair<>(
                new GeoCoordinateBoundingBox2d(
                        new GeoCoordinate2d(new Longitude(-135.0),
                                new Latitude(+45.1)),
                        new GeoCoordinate2d(new Longitude(-90.1),
                                new Latitude(+90.0))),
                "262163"));
        tests.add(new Pair<>(
                new GeoCoordinateBoundingBox2d(
                        new GeoCoordinate2d(new Longitude(-90.0),
                                new Latitude(+45.1)),
                        new GeoCoordinate2d(new Longitude(-45.1),
                                new Latitude(+90.0))),
                "262166"));
        tests.add(new Pair<>(
                new GeoCoordinateBoundingBox2d(
                        new GeoCoordinate2d(new Longitude(-45.0),
                                new Latitude(+45.1)),
                        new GeoCoordinate2d(new Longitude(-0.1),
                                new Latitude(+90.0))),
                "262167"));
        tests.add(new Pair<>(
                new GeoCoordinateBoundingBox2d(
                        new GeoCoordinate2d(new Longitude(+0.0),
                                new Latitude(+45.1)),
                        new GeoCoordinate2d(new Longitude(+45.0),
                                new Latitude(+90.0))),
                "262146"));
        tests.add(new Pair<>(
                new GeoCoordinateBoundingBox2d(
                        new GeoCoordinate2d(new Longitude(+45.1),
                                new Latitude(+45.1)),
                        new GeoCoordinate2d(new Longitude(+90.0),
                                new Latitude(+90.0))),
                "262147"));
        tests.add(new Pair<>(
                new GeoCoordinateBoundingBox2d(
                        new GeoCoordinate2d(new Longitude(+90.1),
                                new Latitude(+45.1)),
                        new GeoCoordinate2d(new Longitude(+135.0),
                                new Latitude(+90.0))),
                "262150"));
        tests.add(new Pair<>(
                new GeoCoordinateBoundingBox2d(
                        new GeoCoordinate2d(new Longitude(+135.1),
                                new Latitude(+45.1)),
                        new GeoCoordinate2d(new Longitude(+180.0),
                                new Latitude(+90.0))),
                "262151"));

        for (Pair<GeoCoordinateBoundingBox2d, String> pair : tests) {
            GeoCoordinateBoundingBox2d bbox = pair.first();
            GeoCoordinate2d ll = new GeoCoordinate2d(bbox.lowerLeft());
            GeoCoordinate2d lr = new GeoCoordinate2d(
                    bbox.upperRight().longitude(), bbox.lowerLeft().latitude());
            GeoCoordinate2d ur = new GeoCoordinate2d(bbox.upperRight());
            GeoCoordinate2d ul = new GeoCoordinate2d(
                    bbox.lowerLeft().longitude(), bbox.upperRight().latitude());
            QuadKey ndsKey;
            ndsKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    Type.Morton, ll, depth);
            assertEquals(pair.second(), ndsKey.toInternalString());
            ndsKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    Type.Morton, lr, depth);
            assertEquals(pair.second(), ndsKey.toInternalString());
            ndsKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    Type.Morton, ur, depth);
            assertEquals(pair.second(), ndsKey.toInternalString());
            ndsKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    Type.Morton, ul, depth);
            assertEquals(pair.second(), ndsKey.toInternalString());
            GeoCoordinateBoundingBox2d actual =
                    new GeoCoordinateBoundingBox2d();
            ndsKey.getGeoCoordinateBounds2d(actual);
            assertTrue(ll.near(actual.lowerLeft(), 1));
            assertTrue(ur.near(actual.upperRight(), 1));
        }
    }

    @Test
    public void getKeysFromLongitudeLatitudeBoundingBoxTest() {
        List<Pair<GeoCoordinateBoundingBox2d, QuadKeyVector>> tests =
                new ArrayList<>();

        tests.add(new Pair<>(new GeoCoordinateBoundingBox2d(
                new GeoCoordinate2d(
                        new Longitude(-180.0), new Latitude(-90.0)),
                new GeoCoordinate2d(
                        new Longitude(-0.1), new Latitude(+90.0))),
                new QuadKeyVector()));
       tests.get(0).second().add(new QuadKey(Type.Morton, 0, 0, (short) 0));
        tests.add(new Pair<>(new GeoCoordinateBoundingBox2d(
                new GeoCoordinate2d(
                        new Longitude(+0.0), new Latitude(-90.0)),
                new GeoCoordinate2d(
                        new Longitude(+180.0), new Latitude(+90.0))),
                new QuadKeyVector()));
       tests.get(1).second().add(new QuadKey(Type.Morton, 0, 1, (short) 0));

        for (Pair<GeoCoordinateBoundingBox2d, QuadKeyVector> pair : tests) {
            QuadKeyVector actual;
            actual = QuadKey.getKeysFromLongitudeLatitudeBoundingBox(
                    Type.Morton, pair.first(), (short) 0);
            assertEquals(pair.second().size(), actual.size());
            for (int i = 0; i < actual.size(); ++i) {
                assertTrue(vectorContains(actual, pair.second().get(i)));
            }
        }

        tests = new ArrayList<>();

        tests.add(new Pair<>(new GeoCoordinateBoundingBox2d(
                new GeoCoordinate2d(
                        new Longitude(-180.0), new Latitude(-90.0)),
                new GeoCoordinate2d(
                        new Longitude(-0.1), new Latitude(+90.0))),
                new QuadKeyVector()));
        tests.get(0).second().add(new QuadKey(Type.Morton, 0, 0, (short) 1));
        tests.get(0).second().add(new QuadKey(Type.Morton, 0, 1, (short) 1));
        tests.get(0).second().add(new QuadKey(Type.Morton, 1, 0, (short) 1));
        tests.get(0).second().add(new QuadKey(Type.Morton, 1, 1, (short) 1));
        tests.add(new Pair<>(new GeoCoordinateBoundingBox2d(
                new GeoCoordinate2d(
                        new Longitude(+0.0), new Latitude(-90.0)),
                new GeoCoordinate2d(
                        new Longitude(+180.0), new Latitude(+90.0))),
                new QuadKeyVector()));
        tests.get(1).second().add(new QuadKey(Type.Morton, 0, 2, (short) 1));
        tests.get(1).second().add(new QuadKey(Type.Morton, 0, 3, (short) 1));
        tests.get(1).second().add(new QuadKey(Type.Morton, 1, 2, (short) 1));
        tests.get(1).second().add(new QuadKey(Type.Morton, 1, 3, (short) 1));
        tests.add(new Pair<>(new GeoCoordinateBoundingBox2d(
                new GeoCoordinate2d(
                        new Longitude(-180.0), new Latitude(-90.0)),
                new GeoCoordinate2d(
                        new Longitude(-0.1), new Latitude(-0.1))),
                new QuadKeyVector()));
        tests.get(2).second().add(new QuadKey(Type.Morton, 0, 0, (short) 1));
        tests.get(2).second().add(new QuadKey(Type.Morton, 0, 1, (short) 1));
        tests.add(new Pair<>(new GeoCoordinateBoundingBox2d(
                new GeoCoordinate2d(
                        new Longitude(-180.0), new Latitude(+0.0)),
                new GeoCoordinate2d(
                        new Longitude(-0.1), new Latitude(+90.0))),
                new QuadKeyVector()));
        tests.get(3).second().add(new QuadKey(Type.Morton, 1, 0, (short) 1));
        tests.get(3).second().add(new QuadKey(Type.Morton, 1, 1, (short) 1));
        tests.add(new Pair<>(new GeoCoordinateBoundingBox2d(
                new GeoCoordinate2d(
                        new Longitude(+0.0), new Latitude(-90.0)),
                new GeoCoordinate2d(
                        new Longitude(+180.0), new Latitude(-0.1))),
                new QuadKeyVector()));
        tests.get(4).second().add(new QuadKey(Type.Morton, 0, 2, (short) 1));
        tests.get(4).second().add(new QuadKey(Type.Morton, 0, 3, (short) 1));
        tests.add(new Pair<>(new GeoCoordinateBoundingBox2d(
                new GeoCoordinate2d(
                        new Longitude(+0.0), new Latitude(+0.0)),
                new GeoCoordinate2d(
                        new Longitude(+180.0), new Latitude(+90.0))),
                new QuadKeyVector()));
        tests.get(5).second().add(new QuadKey(Type.Morton, 1, 2, (short) 1));
        tests.get(5).second().add(new QuadKey(Type.Morton, 1, 3, (short) 1));
        tests.add(new Pair<>(new GeoCoordinateBoundingBox2d(
                new GeoCoordinate2d(
                        new Longitude(-180.0), new Latitude(-90.0)),
                new GeoCoordinate2d(
                        new Longitude(-90.1), new Latitude(-0.1))),
                new QuadKeyVector()));
        tests.get(6).second().add(new QuadKey(Type.Morton, 0, 0, (short) 1));
        tests.add(new Pair<>(new GeoCoordinateBoundingBox2d(
                new GeoCoordinate2d(
                        new Longitude(-90.0), new Latitude(-90.0)),
                new GeoCoordinate2d(
                        new Longitude(-0.1), new Latitude(-0.1))),
                new QuadKeyVector()));
        tests.get(7).second().add(new QuadKey(Type.Morton, 0, 1, (short) 1));
        tests.add(new Pair<>(new GeoCoordinateBoundingBox2d(
                new GeoCoordinate2d(
                        new Longitude(+0.0), new Latitude(-90.0)),
                new GeoCoordinate2d(
                        new Longitude(+90.0), new Latitude(-0.1))),
                new QuadKeyVector()));
        tests.get(8).second().add(new QuadKey(Type.Morton, 0, 2, (short) 1));
        tests.add(new Pair<>(new GeoCoordinateBoundingBox2d(
                new GeoCoordinate2d(
                        new Longitude(+90.1), new Latitude(-90.0)),
                new GeoCoordinate2d(
                        new Longitude(+180.0), new Latitude(-0.1))),
                new QuadKeyVector()));
        tests.get(9).second().add(new QuadKey(Type.Morton, 0, 3, (short) 1));
        tests.add(new Pair<>(new GeoCoordinateBoundingBox2d(
                new GeoCoordinate2d(
                        new Longitude(-180.0), new Latitude(+0.0)),
                new GeoCoordinate2d(
                        new Longitude(-90.1), new Latitude(+90.0))),
                new QuadKeyVector()));
        tests.get(10).second().add(new QuadKey(Type.Morton, 1, 0, (short) 1));
        tests.add(new Pair<>(new GeoCoordinateBoundingBox2d(
                new GeoCoordinate2d(
                        new Longitude(-90.0), new Latitude(+0.0)),
                new GeoCoordinate2d(
                        new Longitude(-0.1), new Latitude(+90.0))),
                new QuadKeyVector()));
        tests.get(11).second().add(new QuadKey(Type.Morton, 1, 1, (short) 1));
        tests.add(new Pair<>(new GeoCoordinateBoundingBox2d(
                new GeoCoordinate2d(
                        new Longitude(+0.0), new Latitude(+0.0)),
                new GeoCoordinate2d(
                        new Longitude(+90.0), new Latitude(+90.0))),
                new QuadKeyVector()));
        tests.get(12).second().add(new QuadKey(Type.Morton, 1, 2, (short) 1));
        tests.add(new Pair<>(new GeoCoordinateBoundingBox2d(
                new GeoCoordinate2d(
                        new Longitude(+90.1), new Latitude(+0.0)),
                new GeoCoordinate2d(
                        new Longitude(+180.0), new Latitude(+90.0))),
                new QuadKeyVector()));
        tests.get(13).second().add(new QuadKey(Type.Morton, 1, 3, (short) 1));

        for (Pair<GeoCoordinateBoundingBox2d, QuadKeyVector> pair : tests) {
            QuadKeyVector actual;
            actual = QuadKey.getKeysFromLongitudeLatitudeBoundingBox(
                    Type.Morton, pair.first(), (short) 1);
            assertEquals(pair.second().size(), actual.size());
            for (int i = 0; i < actual.size(); ++i) {
                assertTrue(vectorContains(actual, pair.second().get(i)));
            }
        }

        {
            Pair<GeoCoordinateBoundingBox2d, QuadKeyVector> test = new Pair<>(
                    new GeoCoordinateBoundingBox2d(
                            new GeoCoordinate2d(
                                    new Longitude(-140.0), new Latitude(-48.0)),
                            new GeoCoordinate2d(
                                    new Longitude(+10.0), new Latitude(+39.0))),
                    new QuadKeyVector());
            test.second().add(new QuadKey(Type.Morton, 0, 0, (short) 2));
            test.second().add(new QuadKey(Type.Morton, 0, 1, (short) 2));
            test.second().add(new QuadKey(Type.Morton, 0, 2, (short) 2));
            test.second().add(new QuadKey(Type.Morton, 0, 3, (short) 2));
            test.second().add(new QuadKey(Type.Morton, 0, 4, (short) 2));
            test.second().add(new QuadKey(Type.Morton, 1, 0, (short) 2));
            test.second().add(new QuadKey(Type.Morton, 1, 1, (short) 2));
            test.second().add(new QuadKey(Type.Morton, 1, 2, (short) 2));
            test.second().add(new QuadKey(Type.Morton, 1, 3, (short) 2));
            test.second().add(new QuadKey(Type.Morton, 1, 4, (short) 2));
            test.second().add(new QuadKey(Type.Morton, 2, 0, (short) 2));
            test.second().add(new QuadKey(Type.Morton, 2, 1, (short) 2));
            test.second().add(new QuadKey(Type.Morton, 2, 2, (short) 2));
            test.second().add(new QuadKey(Type.Morton, 2, 3, (short) 2));
            test.second().add(new QuadKey(Type.Morton, 2, 4, (short) 2));

            QuadKeyVector actual;
            actual = QuadKey.getKeysFromLongitudeLatitudeBoundingBox(
                    Type.Morton, test.first(), (short) 2);
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
                    new GeoCoordinate2d(
                            new Longitude(+2.29450000000000),
                            new Latitude(+48.85822200000000)));
            int tile = 8428778 | (1 << (data.first() + 16));
            String ss = "" + tile;
            QuadKey ndsQuadKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                Type.Morton, data.second(), data.first());
            assertEquals(ss, ndsQuadKey.toInternalString());
        }
        {
            Pair<Short, GeoCoordinate2d> data = new Pair<>((short) 13,
                    new GeoCoordinate2d(
                            new Longitude(-74.04444400000000),
                            new Latitude(+40.68916700000000)));
            int tile = 86924190 | (1 << (data.first() + 16));
            String ss = "" + tile;
            QuadKey ndsQuadKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                Type.Morton, data.second(), data.first());
            assertEquals(ss, ndsQuadKey.toInternalString());
        }
        {
            Pair<Short, GeoCoordinate2d> data = new Pair<>((short) 13,
                    new GeoCoordinate2d(
                            new Longitude(-43.15744400000000),
                            new Latitude(-22.94865800000000)));
            int tile = 130726287 | (1 << (
                data.first() + 16));
            String ss = "" + tile;
            QuadKey ndsQuadKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                Type.Morton, data.second(), data.first());
            assertEquals(ss, ndsQuadKey.toInternalString());
        }
        {
            Pair<Short, GeoCoordinate2d> data = new Pair<>((short) 13,
                    new GeoCoordinate2d(
                            new Longitude(+151.21527800000000),
                            new Latitude(-33.85611100000000)));
            int tile = 63372939 | (1 << (
                data.first() + 16));
            String ss = "" + tile;
            QuadKey ndsQuadKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                Type.Morton, data.second(), data.first());
            assertEquals(ss, ndsQuadKey.toInternalString());
        }
        {
            Pair<Short, GeoCoordinate2d> data = new Pair<>((short) 13,
                    new GeoCoordinate2d(
                            new Longitude(+0.00000000000000),
                            new Latitude(+51.50300000000000)));
            int tile = 8521770 | (1 << (
                data.first() + 16));
            String ss = "" + tile;
            QuadKey ndsQuadKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                Type.Morton, data.second(), data.first());
            assertEquals(ss, ndsQuadKey.toInternalString());
        }
        {
            Pair<Short, GeoCoordinate2d> data = new Pair<>((short) 13,
                    new GeoCoordinate2d(
                            new Longitude(-78.45000000000000),
                            new Latitude(+0.00000000000000)));
            int tile = 84148305 | (1 << (
                data.first() + 16));
            String ss = "" + tile;
            QuadKey ndsQuadKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                Type.Morton, data.second(), data.first());
            assertEquals(ss, ndsQuadKey.toInternalString());
        }
        {
            Pair<Short, GeoCoordinate2d> data = new Pair<>((short) 10,
                    new GeoCoordinate2d(
                            new Longitude(+2.29450000000000),
                            new Latitude(+48.85822200000000)));
            int tile = 131699 | (1 << (16 + data.first()));
            String ss = "" + tile;
            QuadKey ndsQuadKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                Type.Morton, data.second(), data.first());
            assertEquals(ss, ndsQuadKey.toInternalString());
        }
        {
            Pair<Short, GeoCoordinate2d> data = new Pair<>((short) 10,
                    new GeoCoordinate2d(
                            new Longitude(-74.04444400000000),
                            new Latitude(+40.68916700000000)));
            int tile = 1358190 | (1 << (16 + data.first()));
            String ss = "" + tile;
            QuadKey ndsQuadKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                Type.Morton, data.second(), data.first());
            assertEquals(ss, ndsQuadKey.toInternalString());
        }
        {
            Pair<Short, GeoCoordinate2d> data = new Pair<>((short) 10,
                    new GeoCoordinate2d(
                            new Longitude(-43.15744400000000),
                            new Latitude(-22.94865800000000)));
            int tile = 2042598 | (1 << (16 + data.first()));
            String ss = "" + tile;
            QuadKey ndsQuadKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                Type.Morton, data.second(), data.first());
            assertEquals(ss, ndsQuadKey.toInternalString());
        }
        {
            Pair<Short, GeoCoordinate2d> data = new Pair<>((short) 10,
                    new GeoCoordinate2d(
                            new Longitude(+151.21527800000000),
                            new Latitude(-33.85611100000000)));
            int tile = 990202 | (1 << (16 + data.first()));
            String ss = "" + tile;
            QuadKey ndsQuadKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                Type.Morton, data.second(), data.first());
            assertEquals(ss, ndsQuadKey.toInternalString());
        }
        {
            Pair<Short, GeoCoordinate2d> data = new Pair<>((short) 10,
                    new GeoCoordinate2d(
                            new Longitude(+0.00000000000000),
                            new Latitude(+51.50300000000000)));
            int tile = 133152 | (1 << (16 + data.first()));
            String ss = "" + tile;
            QuadKey ndsQuadKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                Type.Morton, data.second(), data.first());
            assertEquals(ss, ndsQuadKey.toInternalString());
        }
        {
            Pair<Short, GeoCoordinate2d> data = new Pair<>((short) 10,
                    new GeoCoordinate2d(
                            new Longitude(-78.45000000000000),
                            new Latitude(+0.00000000000000)));
            int tile = 1314817 | (1 << (16 + data.first()));
            String ss = "" + tile;
            QuadKey ndsQuadKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                Type.Morton, data.second(), data.first());
            assertEquals(ss, ndsQuadKey.toInternalString());
        }
    }
}

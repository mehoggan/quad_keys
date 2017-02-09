import com.quad_key.*;
import org.junit.BeforeClass;
import org.junit.Test;

import java.util.ArrayList;
import java.util.List;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertTrue;

public class ulp_qnr_system_test {

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

/*
    @Test
    public void isValidTest() {
        // See Testquad_key TestSpecificCtorTest.
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
        // Same as BingSystem
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
        // Same as BingSystem
    }

    @Test
    public void getNeighborsTest() {
        // Same as BingSystem
    }

    @Test
    public void fromStringToStringTest() {
        quad_key quadKey = new quad_key(Type.UlpQnr, 0, 0, (short) 0);
        String fmt = quadKey.toInternalString();
        assertEquals("1", fmt);
        quad_key quadKeyBack = quad_key.fromInternalString(Type.UlpQnr, fmt);
        assertTrue(quadKey.equal_to(quadKeyBack));

        quadKey = new quad_key(Type.UlpQnr, 0, 0, (short) 1);
        fmt = quadKey.toInternalString();
        assertEquals("4", fmt);
        quadKeyBack = quad_key.fromInternalString(Type.UlpQnr, fmt);
        assertTrue(quadKey.equal_to(quadKeyBack));

        quadKey = new quad_key(Type.UlpQnr, 0, 1, (short) 1);
        fmt = quadKey.toInternalString();
        assertEquals("5", fmt);
        quadKeyBack = quad_key.fromInternalString(Type.UlpQnr, fmt);
        assertTrue(quadKey.equal_to(quadKeyBack));

        quadKey = new quad_key(Type.UlpQnr, 0, 0, (short) 2);
        fmt = quadKey.toInternalString();
        assertEquals("16", fmt);
        quadKeyBack = quad_key.fromInternalString(Type.UlpQnr, fmt);
        assertTrue(quadKey.equal_to(quadKeyBack));

        quadKey = new quad_key(Type.UlpQnr, 0, 1, (short) 2);
        fmt = quadKey.toInternalString();
        assertEquals("17", fmt);
        quadKeyBack = quad_key.fromInternalString(Type.UlpQnr, fmt);
        assertTrue(quadKey.equal_to(quadKeyBack));

        quadKey = new quad_key(Type.UlpQnr, 1, 0, (short) 2);
        fmt = quadKey.toInternalString();
        assertEquals("20", fmt);
        quadKeyBack = quad_key.fromInternalString(Type.UlpQnr, fmt);
        assertTrue(quadKey.equal_to(quadKeyBack));

        quadKey = new quad_key(Type.UlpQnr, 1, 1, (short) 2);
        fmt = quadKey.toInternalString();
        assertEquals("21", fmt);
        quadKeyBack = quad_key.fromInternalString(Type.UlpQnr, fmt);
        assertTrue(quadKey.equal_to(quadKeyBack));

        quadKey = new quad_key(Type.UlpQnr, 0, 2, (short) 2);
        fmt = quadKey.toInternalString();
        assertEquals("18", fmt);
        quadKeyBack = quad_key.fromInternalString(Type.UlpQnr, fmt);
        assertTrue(quadKey.equal_to(quadKeyBack));

        quadKey = new quad_key(Type.UlpQnr, 0, 3, (short) 2);
        fmt = quadKey.toInternalString();
        assertEquals("19", fmt);
        quadKeyBack = quad_key.fromInternalString(Type.UlpQnr, fmt);
        assertTrue(quadKey.equal_to(quadKeyBack));

        quadKey = new quad_key(Type.UlpQnr, 1, 2, (short) 2);
        fmt = quadKey.toInternalString();
        assertEquals("22", fmt);
        quadKeyBack = quad_key.fromInternalString(Type.UlpQnr, fmt);
        assertTrue(quadKey.equal_to(quadKeyBack));

        quadKey = new quad_key(Type.UlpQnr, 1, 3, (short) 2);
        fmt = quadKey.toInternalString();
        assertEquals("23", fmt);
        quadKeyBack = quad_key.fromInternalString(Type.UlpQnr, fmt);
        assertTrue(quadKey.equal_to(quadKeyBack));

        // For Sanity Purposes and to Verify NO Fence Post Erros. Use a bit of
        // brute force.
        List<Integer> expected = new ArrayList<>();
        for (Integer i = 64; i < 64 + 32; ++i) {
            expected.add(i);
        }
        for (Integer i = 0; i < (8 * 4); ++i) {
            Integer row = i / 8;
            Integer col = i % 8;
            quadKey = new quad_key(Type.UlpQnr, row, col, (short) 3);
            fmt = quadKey.toInternalString();

            String expectedStr = "" + expected.get(i);

            assertEquals(expectedStr, fmt);
            quadKeyBack = quad_key.fromInternalString(Type.UlpQnr, fmt);
            assertTrue(quadKey.equal_to(quadKeyBack));
        }

        quadKey = new quad_key(Type.UlpQnr, 0, 0, (short) 3);
        fmt = quadKey.toInternalString();
        assertEquals("64", fmt);
        quadKeyBack = quad_key.fromInternalString(Type.UlpQnr, fmt);
        assertTrue(quadKey.equal_to(quadKeyBack));
    }

    @Test
    public void getGeoCoordinateBounds2dTest() {
        quad_key quadKey;
        GeoCoordinateBoundingBox2d bbox = new GeoCoordinateBoundingBox2d();

        quadKey = new quad_key(Type.UlpQnr, 0, 0, (short) 0);
        quadKey.getGeoCoordinateBounds2d(bbox);
        assertTrue(bbox.lowerLeft().near(new GeoCoordinate2d(
                new Longitude(-180.0), new Latitude(-90.0)), 1e-4));
        assertTrue(bbox.upperRight().near(new GeoCoordinate2d(
                new Longitude(+180.0), new Latitude(+90.0)), 1e-4));

        quadKey = new quad_key(Type.UlpQnr, 0, 0, (short) 1);
        quadKey.getGeoCoordinateBounds2d(bbox);
        assertTrue(bbox.lowerLeft().near(new GeoCoordinate2d(
                new Longitude(-180.0), new Latitude(-90.0)), 1e-4));
        assertTrue(bbox.upperRight().near(new GeoCoordinate2d(
                new Longitude(+0.0), new Latitude(+90.0)), 1e-4));

        quadKey = new quad_key(Type.UlpQnr, 0, 1, (short) 1);
        quadKey.getGeoCoordinateBounds2d(bbox);
        assertTrue(bbox.lowerLeft().near(new GeoCoordinate2d(
                new Longitude(+0.0), new Latitude(-90.0)), 1e-4));
        assertTrue(bbox.upperRight().near(new GeoCoordinate2d(
                new Longitude(+180.0), new Latitude(+90.0)), 1e-4));

        quadKey = new quad_key(Type.UlpQnr, 0, 0, (short) 2);
        quadKey.getGeoCoordinateBounds2d(bbox);
        assertTrue(bbox.lowerLeft().near(new GeoCoordinate2d(
                new Longitude(-180.0), new Latitude(-90.0)), 1e-4));
        assertTrue(bbox.upperRight().near(new GeoCoordinate2d(
                new Longitude(-90.0), new Latitude(+0.0)), 1e-4));

        quadKey = new quad_key(Type.UlpQnr, 0, 1, (short) 2);
        quadKey.getGeoCoordinateBounds2d(bbox);
        assertTrue(bbox.lowerLeft().near(new GeoCoordinate2d(
                new Longitude(-90.0), new Latitude(-90.0)), 1e-4));

        assertTrue(bbox.upperRight().near(new GeoCoordinate2d(
                new Longitude(+0.0), new Latitude(+0.0)), 1e-4));

        quadKey = new quad_key(Type.UlpQnr, 1, 0, (short) 2);
        quadKey.getGeoCoordinateBounds2d(bbox);
        assertTrue(bbox.lowerLeft().near(new GeoCoordinate2d(
                new Longitude(-180.0), new Latitude(+0.0)), 1e-4));
        assertTrue(bbox.upperRight().near(new GeoCoordinate2d(
                new Longitude(-90.0), new Latitude(+90.0)), 1e-4));

        quadKey = new quad_key(Type.UlpQnr, 1, 1, (short) 2);
        quadKey.getGeoCoordinateBounds2d(bbox);
        assertTrue(bbox.lowerLeft().near(new GeoCoordinate2d(
                new Longitude(-90.0), new Latitude(+0.0)), 1e-4));
        assertTrue(bbox.upperRight().near(new GeoCoordinate2d(
                new Longitude(+0.0), new Latitude(+90.0)), 1e-4));

        quadKey = new quad_key(Type.UlpQnr, 0, 2, (short) 2);
        quadKey.getGeoCoordinateBounds2d(bbox);
        assertTrue(bbox.lowerLeft().near(new GeoCoordinate2d(
                new Longitude(+0.0), new Latitude(-90.0)), 1e-4));
        assertTrue(bbox.upperRight().near(new GeoCoordinate2d(
                new Longitude(+90.0), new Latitude(+0.0)), 1e-4));

        quadKey = new quad_key(Type.UlpQnr, 0, 3, (short) 2);
        quadKey.getGeoCoordinateBounds2d(bbox);
        assertTrue(bbox.lowerLeft().near(new GeoCoordinate2d(
                new Longitude(+90.0), new Latitude(-90.0)), 1e-4));
        assertTrue(bbox.upperRight().near(new GeoCoordinate2d(
                new Longitude(+180.0), new Latitude(+0.0)), 1e-4));

        quadKey = new quad_key(Type.UlpQnr, 1, 2, (short) 2);
        quadKey.getGeoCoordinateBounds2d(bbox);
        assertTrue(bbox.lowerLeft().near(new GeoCoordinate2d(
                new Longitude(+0.0), new Latitude(+0.0)), 1e-4));
        assertTrue(bbox.upperRight().near(new GeoCoordinate2d(
                new Longitude(+90.0), new Latitude(+90.0)), 1e-4));

        quadKey = new quad_key(Type.UlpQnr, 1, 3, (short) 2);
        quadKey.getGeoCoordinateBounds2d(bbox);
        assertTrue(bbox.lowerLeft().near(new GeoCoordinate2d(
                new Longitude(+90.0), new Latitude(+0.0)), 1e-4));
        assertTrue(bbox.upperRight().near(new GeoCoordinate2d(
                new Longitude(+180.0), new Latitude(+90.0)), 1e-4));
    }

    @Test
    public void getKeyFromLongitudeLatitudeAtDepthToBoundsTest() {
        quad_key computedKey;
        computedKey = quad_key.getKeyFromLongitudeLatitudeAtDepth(Type.UlpQnr,
                new GeoCoordinate2d(
                        new Longitude(-180.0), new Latitude(-90.0)),
                (short) 0);
        assertEquals("1", computedKey.toInternalString());
        computedKey = quad_key.getKeyFromLongitudeLatitudeAtDepth(Type.UlpQnr,
                new GeoCoordinate2d(
                        new Longitude(0.0), new Latitude(0.0)),
                (short) 0);
        assertEquals("1", computedKey.toInternalString());

        computedKey = quad_key.getKeyFromLongitudeLatitudeAtDepth(Type.UlpQnr,
                new GeoCoordinate2d(
                        new Longitude(-180.0), new Latitude(-90.0)),
                (short) 1);
        assertEquals("4", computedKey.toInternalString());
        computedKey = quad_key.getKeyFromLongitudeLatitudeAtDepth(Type.UlpQnr,
                new GeoCoordinate2d(
                        new Longitude(-180.0), new Latitude(90.0)),
                (short) 1);
        assertEquals("4", computedKey.toInternalString());
        computedKey = quad_key.getKeyFromLongitudeLatitudeAtDepth(Type.UlpQnr,
                new GeoCoordinate2d(
                        new Longitude(0.1), new Latitude(-90.0)),
                (short) 1);
        assertEquals("5", computedKey.toInternalString());
        computedKey = quad_key.getKeyFromLongitudeLatitudeAtDepth(Type.UlpQnr,
                new GeoCoordinate2d(
                        new Longitude(180.0), new Latitude(90.0)),
                (short) 1);
        assertEquals("5", computedKey.toInternalString());

        computedKey = quad_key.getKeyFromLongitudeLatitudeAtDepth(Type.UlpQnr,
                new GeoCoordinate2d(
                        new Longitude(-180.0), new Latitude(-90.0)),
                (short) 2);
        assertEquals("16", computedKey.toInternalString());
        computedKey = quad_key.getKeyFromLongitudeLatitudeAtDepth(Type.UlpQnr,
                new GeoCoordinate2d(
                        new Longitude(-89.9), new Latitude(-90.0)),
                (short) 2);
        assertEquals("17", computedKey.toInternalString());
        computedKey = quad_key.getKeyFromLongitudeLatitudeAtDepth(Type.UlpQnr,
                new GeoCoordinate2d(
                        new Longitude(0.1), new Latitude(-90.0)),
                (short) 2);
        assertEquals("18", computedKey.toInternalString());
        computedKey = quad_key.getKeyFromLongitudeLatitudeAtDepth(Type.UlpQnr,
                new GeoCoordinate2d(
                        new Longitude(90.1), new Latitude(-90.0)),
                (short) 2);
        assertEquals("19", computedKey.toInternalString());
        computedKey = quad_key.getKeyFromLongitudeLatitudeAtDepth(Type.UlpQnr,
                new GeoCoordinate2d(
                        new Longitude(-180.0), new Latitude(0.1)),
                (short) 2);
        assertEquals("20", computedKey.toInternalString());
        computedKey = quad_key.getKeyFromLongitudeLatitudeAtDepth(Type.UlpQnr,
                new GeoCoordinate2d(
                        new Longitude(-89.9), new Latitude(0.1)),
                (short) 2);
        assertEquals("21", computedKey.toInternalString());
        computedKey = quad_key.getKeyFromLongitudeLatitudeAtDepth(Type.UlpQnr,
                new GeoCoordinate2d(
                        new Longitude(0.1), new Latitude(0.1)),
                (short) 2);
        assertEquals("22", computedKey.toInternalString());
        computedKey = quad_key.getKeyFromLongitudeLatitudeAtDepth(Type.UlpQnr,
                new GeoCoordinate2d(
                        new Longitude(90.1), new Latitude(0.1)),
                (short) 2);
        assertEquals("23", computedKey.toInternalString());
    }

    @Test
    public void getKeysFromLongitudeLatitudeBoundingBoxTest() {
        quad_key_vector outKeys;
        quad_key quadKey;

        // Select Entire Earth
        outKeys = quad_key.getKeysFromLongitudeLatitudeBoundingBox(Type.UlpQnr,
                new GeoCoordinateBoundingBox2d(
                        new GeoCoordinate2d(
                                new Longitude(-180.0), new Latitude(-90.0)),
                        new GeoCoordinate2d(
                                new Longitude(180.0), new Latitude(90.0))),
                (short) 0);
        quadKey = quad_key.fromInternalString(Type.UlpQnr, "1");
        assertEquals(1, outKeys.size());
        assertTrue(vectorContains(outKeys, quadKey));

        // Select Very Center of the Earth
        outKeys = quad_key.getKeysFromLongitudeLatitudeBoundingBox(Type.UlpQnr,
                new GeoCoordinateBoundingBox2d(
                        new GeoCoordinate2d(
                                new Longitude(-0.1), new Latitude(-0.1)),
                        new GeoCoordinate2d(
                                new Longitude(0.1), new Latitude(0.1))),
                (short) 0);
        quadKey = quad_key.fromInternalString(Type.UlpQnr, "1");
        assertEquals(1, outKeys.size());
        assertTrue(vectorContains(outKeys, quadKey));

        // Select Western Hemisphere
        outKeys = quad_key.getKeysFromLongitudeLatitudeBoundingBox(Type.UlpQnr,
                new GeoCoordinateBoundingBox2d(
                        new GeoCoordinate2d(
                                new Longitude(-180.0), new Latitude(-90.0)),
                        new GeoCoordinate2d(
                                new Longitude(0.0), new Latitude(90.0))),
                (short) 1);
        quadKey = quad_key.fromInternalString(Type.UlpQnr, "4");
        assertEquals(1, outKeys.size());
        assertTrue(vectorContains(outKeys, quadKey));

        // Select Eastern Hemisphere
        outKeys = quad_key.getKeysFromLongitudeLatitudeBoundingBox(Type.UlpQnr,
                new GeoCoordinateBoundingBox2d(
                        new GeoCoordinate2d(
                                new Longitude(0.1), new Latitude(-90.0)),
                        new GeoCoordinate2d(
                                new Longitude(180), new Latitude(90.0))),
                (short) 1);
        quadKey = quad_key.fromInternalString(Type.UlpQnr, "5");
        assertEquals(1, outKeys.size());
        assertTrue(vectorContains(outKeys, quadKey));

        // Select Entire Planet
        outKeys = quad_key.getKeysFromLongitudeLatitudeBoundingBox(Type.UlpQnr,
                new GeoCoordinateBoundingBox2d(
                        new GeoCoordinate2d(
                                new Longitude(-180.0), new Latitude(-90.0)),
                        new GeoCoordinate2d(
                                new Longitude(180), new Latitude(90.0))),
                (short) 1);
        quad_key quadKeya = quad_key.fromInternalString(Type.UlpQnr, "4");
        quad_key quadKeyb = quad_key.fromInternalString(Type.UlpQnr, "5");
        assertEquals(2, outKeys.size());
        assertTrue(vectorContains(outKeys, quadKeya));
        assertTrue(vectorContains(outKeys, quadKeyb));

        // Select South West Corner
        outKeys = quad_key.getKeysFromLongitudeLatitudeBoundingBox(Type.UlpQnr,
                new GeoCoordinateBoundingBox2d(
                        new GeoCoordinate2d(
                                new Longitude(-180.0), new Latitude(-90.0)),
                        new GeoCoordinate2d(
                                new Longitude(-90.0), new Latitude(0.0))),
                (short) 2);
        quadKey = quad_key.fromInternalString(Type.UlpQnr, "16");
        assertEquals(1, outKeys.size());
        assertTrue(vectorContains(outKeys, quadKey));

        // Select South America
        outKeys = quad_key.getKeysFromLongitudeLatitudeBoundingBox(Type.UlpQnr,
                new GeoCoordinateBoundingBox2d(
                        new GeoCoordinate2d(
                                new Longitude(-89.9), new Latitude(-90.0)),
                        new GeoCoordinate2d(
                                new Longitude(0.0), new Latitude(0.0))),
                (short) 2);
        quadKey = quad_key.fromInternalString(Type.UlpQnr, "17");
        assertEquals(1, outKeys.size());
        assertTrue(vectorContains(outKeys, quadKey));

        // Select North West Corner
        outKeys = quad_key.getKeysFromLongitudeLatitudeBoundingBox(Type.UlpQnr,
                new GeoCoordinateBoundingBox2d(
                        new GeoCoordinate2d(
                                new Longitude(-180.0), new Latitude(0.1)),
                        new GeoCoordinate2d(
                                new Longitude(-90.0), new Latitude(90.0))),
                (short) 2);
        quadKey = quad_key.fromInternalString(Type.UlpQnr, "20");
        assertEquals(1, outKeys.size());
        assertTrue(vectorContains(outKeys, quadKey));

        // Select Greenland
        outKeys = quad_key.getKeysFromLongitudeLatitudeBoundingBox(Type.UlpQnr,
                new GeoCoordinateBoundingBox2d(
                        new GeoCoordinate2d(
                                new Longitude(-89.9), new Latitude(0.1)),
                        new GeoCoordinate2d(
                                new Longitude(0.0), new Latitude(90.0))),
                (short) 2);
        quadKey = quad_key.fromInternalString(Type.UlpQnr, "21");
        assertEquals(1, outKeys.size());
        assertTrue(vectorContains(outKeys, quadKey));

        // Select South Pole
        outKeys = quad_key.getKeysFromLongitudeLatitudeBoundingBox(Type.UlpQnr,
                new GeoCoordinateBoundingBox2d(
                        new GeoCoordinate2d(
                                new Longitude(0.1), new Latitude(-90.0)),
                        new GeoCoordinate2d(
                                new Longitude(90.0), new Latitude(0.0))),
                (short) 2);
        quadKey = quad_key.fromInternalString(Type.UlpQnr, "18");
        assertEquals(1, outKeys.size());
        assertTrue(vectorContains(outKeys, quadKey));

        // Select South East Corner
        outKeys = quad_key.getKeysFromLongitudeLatitudeBoundingBox(Type.UlpQnr,
                new GeoCoordinateBoundingBox2d(
                        new GeoCoordinate2d(
                                new Longitude(90.1), new Latitude(-90.0)),
                        new GeoCoordinate2d(
                                new Longitude(180.0), new Latitude(0.0))),
                (short) 2);
        quadKey = quad_key.fromInternalString(Type.UlpQnr, "19");
        assertEquals(1, outKeys.size());
        assertTrue(vectorContains(outKeys, quadKey));

        // Select Over Europe
        outKeys = quad_key.getKeysFromLongitudeLatitudeBoundingBox(Type.UlpQnr,
                new GeoCoordinateBoundingBox2d(
                        new GeoCoordinate2d(
                                new Longitude(0.1), new Latitude(0.1)),
                        new GeoCoordinate2d(
                                new Longitude(90.0), new Latitude(90.0))),
                (short) 2);
        quadKey = quad_key.fromInternalString(Type.UlpQnr, "22");
        assertEquals(1, outKeys.size());
        assertTrue(vectorContains(outKeys, quadKey));

        // Select North East Corner
        outKeys = quad_key.getKeysFromLongitudeLatitudeBoundingBox(Type.UlpQnr,
                new GeoCoordinateBoundingBox2d(
                        new GeoCoordinate2d(
                                new Longitude(90.1), new Latitude(0.1)),
                        new GeoCoordinate2d(
                                new Longitude(180.0), new Latitude(90.0))),
                (short) 2);
        quadKey = quad_key.fromInternalString(Type.UlpQnr, "23");
        assertEquals(1, outKeys.size());
        assertTrue(vectorContains(outKeys, quadKey));

        // Select Entire Map
        outKeys = quad_key.getKeysFromLongitudeLatitudeBoundingBox(Type.UlpQnr,
                new GeoCoordinateBoundingBox2d(
                        new GeoCoordinate2d(
                                new Longitude(-179.9), new Latitude(-89.9)),
                        new GeoCoordinate2d(
                                new Longitude(90.1), new Latitude(0.1))),
                (short) 2);
        quad_key quadKey0 = quad_key.fromInternalString(Type.UlpQnr, "16");
        quad_key quadKey1 = quad_key.fromInternalString(Type.UlpQnr, "17");
        quad_key quadKey2 = quad_key.fromInternalString(Type.UlpQnr, "18");
        quad_key quadKey3 = quad_key.fromInternalString(Type.UlpQnr, "19");
        quad_key quadKey4 = quad_key.fromInternalString(Type.UlpQnr, "20");
        quad_key quadKey5 = quad_key.fromInternalString(Type.UlpQnr, "21");
        quad_key quadKey6 = quad_key.fromInternalString(Type.UlpQnr, "22");
        quad_key quadKey7 = quad_key.fromInternalString(Type.UlpQnr, "23");
        assertEquals(8, outKeys.size());
        assertTrue(vectorContains(outKeys, quadKey0));
        assertTrue(vectorContains(outKeys, quadKey1));
        assertTrue(vectorContains(outKeys, quadKey2));
        assertTrue(vectorContains(outKeys, quadKey3));
        assertTrue(vectorContains(outKeys, quadKey4));
        assertTrue(vectorContains(outKeys, quadKey5));
        assertTrue(vectorContains(outKeys, quadKey6));
        assertTrue(vectorContains(outKeys, quadKey7));
    }

    @Test
    public void selecetedCitiesTest() {
        // TODO: Implement Tests. Taken from Earthscape. No tests there.
    }
*/
}

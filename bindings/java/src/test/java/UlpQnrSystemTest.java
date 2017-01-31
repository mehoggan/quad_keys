import com.quadkey.*;
import org.junit.BeforeClass;
import org.junit.Test;

import java.util.ArrayList;
import java.util.List;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertTrue;

public class UlpQnrSystemTest {

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
        QuadKey quadKey = new QuadKey(Type.UlpQnr, 0, 0, (short) 0);
        String fmt = quadKey.toInternalString();
        assertEquals("1", fmt);
        QuadKey quadKeyBack = QuadKey.fromInternalString(Type.UlpQnr, fmt);
        assertTrue(quadKey.equalTo(quadKeyBack));

        quadKey = new QuadKey(Type.UlpQnr, 0, 0, (short) 1);
        fmt = quadKey.toInternalString();
        assertEquals("4", fmt);
        quadKeyBack = QuadKey.fromInternalString(Type.UlpQnr, fmt);
        assertTrue(quadKey.equalTo(quadKeyBack));

        quadKey = new QuadKey(Type.UlpQnr, 0, 1, (short) 1);
        fmt = quadKey.toInternalString();
        assertEquals("5", fmt);
        quadKeyBack = QuadKey.fromInternalString(Type.UlpQnr, fmt);
        assertTrue(quadKey.equalTo(quadKeyBack));

        quadKey = new QuadKey(Type.UlpQnr, 0, 0, (short) 2);
        fmt = quadKey.toInternalString();
        assertEquals("16", fmt);
        quadKeyBack = QuadKey.fromInternalString(Type.UlpQnr, fmt);
        assertTrue(quadKey.equalTo(quadKeyBack));

        quadKey = new QuadKey(Type.UlpQnr, 0, 1, (short) 2);
        fmt = quadKey.toInternalString();
        assertEquals("17", fmt);
        quadKeyBack = QuadKey.fromInternalString(Type.UlpQnr, fmt);
        assertTrue(quadKey.equalTo(quadKeyBack));

        quadKey = new QuadKey(Type.UlpQnr, 1, 0, (short) 2);
        fmt = quadKey.toInternalString();
        assertEquals("20", fmt);
        quadKeyBack = QuadKey.fromInternalString(Type.UlpQnr, fmt);
        assertTrue(quadKey.equalTo(quadKeyBack));

        quadKey = new QuadKey(Type.UlpQnr, 1, 1, (short) 2);
        fmt = quadKey.toInternalString();
        assertEquals("21", fmt);
        quadKeyBack = QuadKey.fromInternalString(Type.UlpQnr, fmt);
        assertTrue(quadKey.equalTo(quadKeyBack));

        quadKey = new QuadKey(Type.UlpQnr, 0, 2, (short) 2);
        fmt = quadKey.toInternalString();
        assertEquals("18", fmt);
        quadKeyBack = QuadKey.fromInternalString(Type.UlpQnr, fmt);
        assertTrue(quadKey.equalTo(quadKeyBack));

        quadKey = new QuadKey(Type.UlpQnr, 0, 3, (short) 2);
        fmt = quadKey.toInternalString();
        assertEquals("19", fmt);
        quadKeyBack = QuadKey.fromInternalString(Type.UlpQnr, fmt);
        assertTrue(quadKey.equalTo(quadKeyBack));

        quadKey = new QuadKey(Type.UlpQnr, 1, 2, (short) 2);
        fmt = quadKey.toInternalString();
        assertEquals("22", fmt);
        quadKeyBack = QuadKey.fromInternalString(Type.UlpQnr, fmt);
        assertTrue(quadKey.equalTo(quadKeyBack));

        quadKey = new QuadKey(Type.UlpQnr, 1, 3, (short) 2);
        fmt = quadKey.toInternalString();
        assertEquals("23", fmt);
        quadKeyBack = QuadKey.fromInternalString(Type.UlpQnr, fmt);
        assertTrue(quadKey.equalTo(quadKeyBack));

        // For Sanity Purposes and to Verify NO Fence Post Erros. Use a bit of
        // brute force.
        List<Integer> expected = new ArrayList<>();
        for (Integer i = 64; i < 64 + 32; ++i) {
            expected.add(i);
        }
        for (Integer i = 0; i < (8 * 4); ++i) {
            Integer row = i / 8;
            Integer col = i % 8;
            quadKey = new QuadKey(Type.UlpQnr, row, col, (short) 3);
            fmt = quadKey.toInternalString();

            String expectedStr = "" + expected.get(i);

            assertEquals(expectedStr, fmt);
            quadKeyBack = QuadKey.fromInternalString(Type.UlpQnr, fmt);
            assertTrue(quadKey.equalTo(quadKeyBack));
        }

        quadKey = new QuadKey(Type.UlpQnr, 0, 0, (short) 3);
        fmt = quadKey.toInternalString();
        assertEquals("64", fmt);
        quadKeyBack = QuadKey.fromInternalString(Type.UlpQnr, fmt);
        assertTrue(quadKey.equalTo(quadKeyBack));
    }

    @Test
    public void getGeoCoordinateBounds2dTest() {
        QuadKey quadKey;
        GeoCoordinateBoundingBox2d bbox = new GeoCoordinateBoundingBox2d();

        quadKey = new QuadKey(Type.UlpQnr, 0, 0, (short) 0);
        quadKey.getGeoCoordinateBounds2d(bbox);
        assertTrue(bbox.lowerLeft().near(new GeoCoordinate2d(
                new Longitude(-180.0), new Latitude(-90.0)), 1e-4));
        assertTrue(bbox.upperRight().near(new GeoCoordinate2d(
                new Longitude(+180.0), new Latitude(+90.0)), 1e-4));

        quadKey = new QuadKey(Type.UlpQnr, 0, 0, (short) 1);
        quadKey.getGeoCoordinateBounds2d(bbox);
        assertTrue(bbox.lowerLeft().near(new GeoCoordinate2d(
                new Longitude(-180.0), new Latitude(-90.0)), 1e-4));
        assertTrue(bbox.upperRight().near(new GeoCoordinate2d(
                new Longitude(+0.0), new Latitude(+90.0)), 1e-4));

        quadKey = new QuadKey(Type.UlpQnr, 0, 1, (short) 1);
        quadKey.getGeoCoordinateBounds2d(bbox);
        assertTrue(bbox.lowerLeft().near(new GeoCoordinate2d(
                new Longitude(+0.0), new Latitude(-90.0)), 1e-4));
        assertTrue(bbox.upperRight().near(new GeoCoordinate2d(
                new Longitude(+180.0), new Latitude(+90.0)), 1e-4));

        quadKey = new QuadKey(Type.UlpQnr, 0, 0, (short) 2);
        quadKey.getGeoCoordinateBounds2d(bbox);
        assertTrue(bbox.lowerLeft().near(new GeoCoordinate2d(
                new Longitude(-180.0), new Latitude(-90.0)), 1e-4));
        assertTrue(bbox.upperRight().near(new GeoCoordinate2d(
                new Longitude(-90.0), new Latitude(+0.0)), 1e-4));

        quadKey = new QuadKey(Type.UlpQnr, 0, 1, (short) 2);
        quadKey.getGeoCoordinateBounds2d(bbox);
        assertTrue(bbox.lowerLeft().near(new GeoCoordinate2d(
                new Longitude(-90.0), new Latitude(-90.0)), 1e-4));

        assertTrue(bbox.upperRight().near(new GeoCoordinate2d(
                new Longitude(+0.0), new Latitude(+0.0)), 1e-4));

        quadKey = new QuadKey(Type.UlpQnr, 1, 0, (short) 2);
        quadKey.getGeoCoordinateBounds2d(bbox);
        assertTrue(bbox.lowerLeft().near(new GeoCoordinate2d(
                new Longitude(-180.0), new Latitude(+0.0)), 1e-4));
        assertTrue(bbox.upperRight().near(new GeoCoordinate2d(
                new Longitude(-90.0), new Latitude(+90.0)), 1e-4));

        quadKey = new QuadKey(Type.UlpQnr, 1, 1, (short) 2);
        quadKey.getGeoCoordinateBounds2d(bbox);
        assertTrue(bbox.lowerLeft().near(new GeoCoordinate2d(
                new Longitude(-90.0), new Latitude(+0.0)), 1e-4));
        assertTrue(bbox.upperRight().near(new GeoCoordinate2d(
                new Longitude(+0.0), new Latitude(+90.0)), 1e-4));

        quadKey = new QuadKey(Type.UlpQnr, 0, 2, (short) 2);
        quadKey.getGeoCoordinateBounds2d(bbox);
        assertTrue(bbox.lowerLeft().near(new GeoCoordinate2d(
                new Longitude(+0.0), new Latitude(-90.0)), 1e-4));
        assertTrue(bbox.upperRight().near(new GeoCoordinate2d(
                new Longitude(+90.0), new Latitude(+0.0)), 1e-4));

        quadKey = new QuadKey(Type.UlpQnr, 0, 3, (short) 2);
        quadKey.getGeoCoordinateBounds2d(bbox);
        assertTrue(bbox.lowerLeft().near(new GeoCoordinate2d(
                new Longitude(+90.0), new Latitude(-90.0)), 1e-4));
        assertTrue(bbox.upperRight().near(new GeoCoordinate2d(
                new Longitude(+180.0), new Latitude(+0.0)), 1e-4));

        quadKey = new QuadKey(Type.UlpQnr, 1, 2, (short) 2);
        quadKey.getGeoCoordinateBounds2d(bbox);
        assertTrue(bbox.lowerLeft().near(new GeoCoordinate2d(
                new Longitude(+0.0), new Latitude(+0.0)), 1e-4));
        assertTrue(bbox.upperRight().near(new GeoCoordinate2d(
                new Longitude(+90.0), new Latitude(+90.0)), 1e-4));

        quadKey = new QuadKey(Type.UlpQnr, 1, 3, (short) 2);
        quadKey.getGeoCoordinateBounds2d(bbox);
        assertTrue(bbox.lowerLeft().near(new GeoCoordinate2d(
                new Longitude(+90.0), new Latitude(+0.0)), 1e-4));
        assertTrue(bbox.upperRight().near(new GeoCoordinate2d(
                new Longitude(+180.0), new Latitude(+90.0)), 1e-4));
    }

    @Test
    public void getKeyFromLongitudeLatitudeAtDepthToBoundsTest() {
        QuadKey computedKey;
        computedKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(Type.UlpQnr,
                new GeoCoordinate2d(
                        new Longitude(-180.0), new Latitude(-90.0)),
                (short) 0);
        assertEquals("1", computedKey.toInternalString());
        computedKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(Type.UlpQnr,
                new GeoCoordinate2d(
                        new Longitude(0.0), new Latitude(0.0)),
                (short) 0);
        assertEquals("1", computedKey.toInternalString());

        computedKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(Type.UlpQnr,
                new GeoCoordinate2d(
                        new Longitude(-180.0), new Latitude(-90.0)),
                (short) 1);
        assertEquals("4", computedKey.toInternalString());
        computedKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(Type.UlpQnr,
                new GeoCoordinate2d(
                        new Longitude(-180.0), new Latitude(90.0)),
                (short) 1);
        assertEquals("4", computedKey.toInternalString());
        computedKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(Type.UlpQnr,
                new GeoCoordinate2d(
                        new Longitude(0.1), new Latitude(-90.0)),
                (short) 1);
        assertEquals("5", computedKey.toInternalString());
        computedKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(Type.UlpQnr,
                new GeoCoordinate2d(
                        new Longitude(180.0), new Latitude(90.0)),
                (short) 1);
        assertEquals("5", computedKey.toInternalString());

        computedKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(Type.UlpQnr,
                new GeoCoordinate2d(
                        new Longitude(-180.0), new Latitude(-90.0)),
                (short) 2);
        assertEquals("16", computedKey.toInternalString());
        computedKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(Type.UlpQnr,
                new GeoCoordinate2d(
                        new Longitude(-89.9), new Latitude(-90.0)),
                (short) 2);
        assertEquals("17", computedKey.toInternalString());
        computedKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(Type.UlpQnr,
                new GeoCoordinate2d(
                        new Longitude(0.1), new Latitude(-90.0)),
                (short) 2);
        assertEquals("18", computedKey.toInternalString());
        computedKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(Type.UlpQnr,
                new GeoCoordinate2d(
                        new Longitude(90.1), new Latitude(-90.0)),
                (short) 2);
        assertEquals("19", computedKey.toInternalString());
        computedKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(Type.UlpQnr,
                new GeoCoordinate2d(
                        new Longitude(-180.0), new Latitude(0.1)),
                (short) 2);
        assertEquals("20", computedKey.toInternalString());
        computedKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(Type.UlpQnr,
                new GeoCoordinate2d(
                        new Longitude(-89.9), new Latitude(0.1)),
                (short) 2);
        assertEquals("21", computedKey.toInternalString());
        computedKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(Type.UlpQnr,
                new GeoCoordinate2d(
                        new Longitude(0.1), new Latitude(0.1)),
                (short) 2);
        assertEquals("22", computedKey.toInternalString());
        computedKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(Type.UlpQnr,
                new GeoCoordinate2d(
                        new Longitude(90.1), new Latitude(0.1)),
                (short) 2);
        assertEquals("23", computedKey.toInternalString());
    }

    @Test
    public void getKeysFromLongitudeLatitudeBoundingBoxTest() {
        QuadKeyVector outKeys;
        QuadKey quadKey;

        // Select Entire Earth
        outKeys = QuadKey.getKeysFromLongitudeLatitudeBoundingBox(Type.UlpQnr,
                new GeoCoordinateBoundingBox2d(
                        new GeoCoordinate2d(
                                new Longitude(-180.0), new Latitude(-90.0)),
                        new GeoCoordinate2d(
                                new Longitude(180.0), new Latitude(90.0))),
                (short) 0);
        quadKey = QuadKey.fromInternalString(Type.UlpQnr, "1");
        assertEquals(1, outKeys.size());
        assertTrue(vectorContains(outKeys, quadKey));

        // Select Very Center of the Earth
        outKeys = QuadKey.getKeysFromLongitudeLatitudeBoundingBox(Type.UlpQnr,
                new GeoCoordinateBoundingBox2d(
                        new GeoCoordinate2d(
                                new Longitude(-0.1), new Latitude(-0.1)),
                        new GeoCoordinate2d(
                                new Longitude(0.1), new Latitude(0.1))),
                (short) 0);
        quadKey = QuadKey.fromInternalString(Type.UlpQnr, "1");
        assertEquals(1, outKeys.size());
        assertTrue(vectorContains(outKeys, quadKey));

        // Select Western Hemisphere
        outKeys = QuadKey.getKeysFromLongitudeLatitudeBoundingBox(Type.UlpQnr,
                new GeoCoordinateBoundingBox2d(
                        new GeoCoordinate2d(
                                new Longitude(-180.0), new Latitude(-90.0)),
                        new GeoCoordinate2d(
                                new Longitude(0.0), new Latitude(90.0))),
                (short) 1);
        quadKey = QuadKey.fromInternalString(Type.UlpQnr, "4");
        assertEquals(1, outKeys.size());
        assertTrue(vectorContains(outKeys, quadKey));

        // Select Eastern Hemisphere
        outKeys = QuadKey.getKeysFromLongitudeLatitudeBoundingBox(Type.UlpQnr,
                new GeoCoordinateBoundingBox2d(
                        new GeoCoordinate2d(
                                new Longitude(0.1), new Latitude(-90.0)),
                        new GeoCoordinate2d(
                                new Longitude(180), new Latitude(90.0))),
                (short) 1);
        quadKey = QuadKey.fromInternalString(Type.UlpQnr, "5");
        assertEquals(1, outKeys.size());
        assertTrue(vectorContains(outKeys, quadKey));

        // Select Entire Planet
        outKeys = QuadKey.getKeysFromLongitudeLatitudeBoundingBox(Type.UlpQnr,
                new GeoCoordinateBoundingBox2d(
                        new GeoCoordinate2d(
                                new Longitude(-180.0), new Latitude(-90.0)),
                        new GeoCoordinate2d(
                                new Longitude(180), new Latitude(90.0))),
                (short) 1);
        QuadKey quadKeya = QuadKey.fromInternalString(Type.UlpQnr, "4");
        QuadKey quadKeyb = QuadKey.fromInternalString(Type.UlpQnr, "5");
        assertEquals(2, outKeys.size());
        assertTrue(vectorContains(outKeys, quadKeya));
        assertTrue(vectorContains(outKeys, quadKeyb));

        // Select South West Corner
        outKeys = QuadKey.getKeysFromLongitudeLatitudeBoundingBox(Type.UlpQnr,
                new GeoCoordinateBoundingBox2d(
                        new GeoCoordinate2d(
                                new Longitude(-180.0), new Latitude(-90.0)),
                        new GeoCoordinate2d(
                                new Longitude(-90.0), new Latitude(0.0))),
                (short) 2);
        quadKey = QuadKey.fromInternalString(Type.UlpQnr, "16");
        assertEquals(1, outKeys.size());
        assertTrue(vectorContains(outKeys, quadKey));

        // Select South America
        outKeys = QuadKey.getKeysFromLongitudeLatitudeBoundingBox(Type.UlpQnr,
                new GeoCoordinateBoundingBox2d(
                        new GeoCoordinate2d(
                                new Longitude(-89.9), new Latitude(-90.0)),
                        new GeoCoordinate2d(
                                new Longitude(0.0), new Latitude(0.0))),
                (short) 2);
        quadKey = QuadKey.fromInternalString(Type.UlpQnr, "17");
        assertEquals(1, outKeys.size());
        assertTrue(vectorContains(outKeys, quadKey));

        // Select North West Corner
        outKeys = QuadKey.getKeysFromLongitudeLatitudeBoundingBox(Type.UlpQnr,
                new GeoCoordinateBoundingBox2d(
                        new GeoCoordinate2d(
                                new Longitude(-180.0), new Latitude(0.1)),
                        new GeoCoordinate2d(
                                new Longitude(-90.0), new Latitude(90.0))),
                (short) 2);
        quadKey = QuadKey.fromInternalString(Type.UlpQnr, "20");
        assertEquals(1, outKeys.size());
        assertTrue(vectorContains(outKeys, quadKey));

        // Select Greenland
        outKeys = QuadKey.getKeysFromLongitudeLatitudeBoundingBox(Type.UlpQnr,
                new GeoCoordinateBoundingBox2d(
                        new GeoCoordinate2d(
                                new Longitude(-89.9), new Latitude(0.1)),
                        new GeoCoordinate2d(
                                new Longitude(0.0), new Latitude(90.0))),
                (short) 2);
        quadKey = QuadKey.fromInternalString(Type.UlpQnr, "21");
        assertEquals(1, outKeys.size());
        assertTrue(vectorContains(outKeys, quadKey));

        // Select South Pole
        outKeys = QuadKey.getKeysFromLongitudeLatitudeBoundingBox(Type.UlpQnr,
                new GeoCoordinateBoundingBox2d(
                        new GeoCoordinate2d(
                                new Longitude(0.1), new Latitude(-90.0)),
                        new GeoCoordinate2d(
                                new Longitude(90.0), new Latitude(0.0))),
                (short) 2);
        quadKey = QuadKey.fromInternalString(Type.UlpQnr, "18");
        assertEquals(1, outKeys.size());
        assertTrue(vectorContains(outKeys, quadKey));

        // Select South East Corner
        outKeys = QuadKey.getKeysFromLongitudeLatitudeBoundingBox(Type.UlpQnr,
                new GeoCoordinateBoundingBox2d(
                        new GeoCoordinate2d(
                                new Longitude(90.1), new Latitude(-90.0)),
                        new GeoCoordinate2d(
                                new Longitude(180.0), new Latitude(0.0))),
                (short) 2);
        quadKey = QuadKey.fromInternalString(Type.UlpQnr, "19");
        assertEquals(1, outKeys.size());
        assertTrue(vectorContains(outKeys, quadKey));

        // Select Over Europe
        outKeys = QuadKey.getKeysFromLongitudeLatitudeBoundingBox(Type.UlpQnr,
                new GeoCoordinateBoundingBox2d(
                        new GeoCoordinate2d(
                                new Longitude(0.1), new Latitude(0.1)),
                        new GeoCoordinate2d(
                                new Longitude(90.0), new Latitude(90.0))),
                (short) 2);
        quadKey = QuadKey.fromInternalString(Type.UlpQnr, "22");
        assertEquals(1, outKeys.size());
        assertTrue(vectorContains(outKeys, quadKey));

        // Select North East Corner
        outKeys = QuadKey.getKeysFromLongitudeLatitudeBoundingBox(Type.UlpQnr,
                new GeoCoordinateBoundingBox2d(
                        new GeoCoordinate2d(
                                new Longitude(90.1), new Latitude(0.1)),
                        new GeoCoordinate2d(
                                new Longitude(180.0), new Latitude(90.0))),
                (short) 2);
        quadKey = QuadKey.fromInternalString(Type.UlpQnr, "23");
        assertEquals(1, outKeys.size());
        assertTrue(vectorContains(outKeys, quadKey));

        // Select Entire Map
        outKeys = QuadKey.getKeysFromLongitudeLatitudeBoundingBox(Type.UlpQnr,
                new GeoCoordinateBoundingBox2d(
                        new GeoCoordinate2d(
                                new Longitude(-179.9), new Latitude(-89.9)),
                        new GeoCoordinate2d(
                                new Longitude(90.1), new Latitude(0.1))),
                (short) 2);
        QuadKey quadKey0 = QuadKey.fromInternalString(Type.UlpQnr, "16");
        QuadKey quadKey1 = QuadKey.fromInternalString(Type.UlpQnr, "17");
        QuadKey quadKey2 = QuadKey.fromInternalString(Type.UlpQnr, "18");
        QuadKey quadKey3 = QuadKey.fromInternalString(Type.UlpQnr, "19");
        QuadKey quadKey4 = QuadKey.fromInternalString(Type.UlpQnr, "20");
        QuadKey quadKey5 = QuadKey.fromInternalString(Type.UlpQnr, "21");
        QuadKey quadKey6 = QuadKey.fromInternalString(Type.UlpQnr, "22");
        QuadKey quadKey7 = QuadKey.fromInternalString(Type.UlpQnr, "23");
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
}

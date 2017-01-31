import com.quadkey.*;
import org.junit.BeforeClass;
import org.junit.Test;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertTrue;

public class OsGeoSystemTest {

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
        // Same thing as OsGeo Except for it allows for negative 1 in both the
        // rows and the columns. depth/col/row.
        QuadKey quadKey = new QuadKey(Type.OsGeo, 3, 3,
                (short) 2);
        String fmt = quadKey.toInternalString();
        assertEquals("2/3/3", fmt);
        QuadKey quadKeyBack = QuadKey.fromInternalString(Type.OsGeo, fmt);
        assertTrue(quadKey.equalTo(quadKeyBack));

        fmt = "0/-1/-1";
        quadKeyBack = QuadKey.fromInternalString(Type.OsGeo, fmt);
        assertTrue(new QuadKey(Type.OsGeo, 0, 0,
                (short) 0).equalTo(quadKeyBack));

        fmt = "1/1/-1";
        quadKeyBack = QuadKey.fromInternalString(Type.OsGeo, fmt);
        assertTrue(new QuadKey(Type.OsGeo, 0, 1,
                (short) 1).equalTo(
                quadKeyBack));

        fmt = "1/-1/1";
        quadKeyBack = QuadKey.fromInternalString(Type.OsGeo, fmt);
        assertTrue(new QuadKey(Type.OsGeo, 1, 0,
                (short) 1).equalTo(
                quadKeyBack));
    }

    @Test
    public void getGeoCoordinateBounds2dTest() {
        QuadKey quadKey;
        GeoCoordinateBoundingBox2d bbox = new GeoCoordinateBoundingBox2d();

        { // Depth 0
            quadKey = QuadKey.fromInternalString(Type.OsGeo, "0/0/0");
            quadKey.getGeoCoordinateBounds2d(bbox);
            assertTrue(new Longitude(-180.0f).near(
                    bbox.lowerLeft().longitude(), 1e-4));
            assertTrue(new Latitude(-85.051132).near(
                    bbox.lowerLeft().latitude(), 1e-4));
            assertTrue(new Longitude(+180.0).near(
                    bbox.upperRight().longitude(), 1e-4));
            assertTrue(new Latitude(+85.051132).near(
                    bbox.upperRight().latitude(), 1e-4));
        }
    }

    @Test
    public void getKeyFromLongitudeLatitudeAtDepthToBoundsTest() {
        QuadKey quadKey;
        GeoCoordinateBoundingBox2d bbox = new GeoCoordinateBoundingBox2d();

        // Inclusion here consists of upper right. In the case along bottom or
        // left Inclusion points the opposite direction.
        //    X------X------X ur
        //    |      |      |
        //    |      |      |
        //    X------X------X
        //    |      |      |
        //    |      |      |
        //    X------X------X
        // Note that in this system bounds consist of all 4 sides, so two quads
        // will share the same boundary.
        quadKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(Type.OsGeo,
                new GeoCoordinate2d(
                        new Longitude(-180.0), new Latitude(+85.05113877)),
                (short) 0);
        assertTrue(new QuadKey(Type.OsGeo, 0, 0,
                (short) 0).equalTo(quadKey));
        quadKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(Type.OsGeo,
                new GeoCoordinate2d(
                        new Longitude(+180.0), new Latitude(+85.05113877)),
                (short) 0);
        assertTrue(new QuadKey(Type.OsGeo, 0, 0,
                (short) 0).equalTo(quadKey));
        quadKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(Type.OsGeo,
                new GeoCoordinate2d(
                        new Longitude(+180.0), new Latitude(-85.05113877)),
                (short) 0);
        assertTrue(new QuadKey(Type.OsGeo, 0, 0,
                (short) 0).equalTo(quadKey));
        quadKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(Type.OsGeo,
                new GeoCoordinate2d(
                        new Longitude(-180.0), new Latitude(-85.05113877)),
                (short) 0);
        assertTrue(new QuadKey(Type.OsGeo, 0, 0,
                (short) 0).equalTo(quadKey));
        quadKey.getGeoCoordinateBounds2d(bbox);
        assertTrue(bbox.lowerLeft().near(new GeoCoordinate2d(
                new Longitude(-180.0), new Latitude(-85.05113877)), 1e-4));
        assertTrue(bbox.upperRight().near(new GeoCoordinate2d(
                new Longitude(+180.0), new Latitude(+85.05113877)), 1e-4));

        quadKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(Type.OsGeo,
                new GeoCoordinate2d(
                        new Longitude(+0.0), new Latitude(+0.00000000)),
                (short) 0);
        assertTrue(new QuadKey(Type.OsGeo, 0, 0,
                (short) 0).equalTo(quadKey));

        quadKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(Type.OsGeo,
                new GeoCoordinate2d(
                        new Longitude(-180.0), new Latitude(+85.05113877)),
                (short) 1);
        assertTrue(new QuadKey(Type.OsGeo, 1, 0,
                (short) 1).equalTo(quadKey));
        quadKey.getGeoCoordinateBounds2d(bbox);
        assertTrue(bbox.lowerLeft().near(new GeoCoordinate2d(
                new Longitude(-180.0), new Latitude(+0.00000000)), 1e-4));
        assertTrue(bbox.upperRight().near(new GeoCoordinate2d(
                new Longitude(+0.0), new Latitude(+85.05113877)), 1e-4));

        quadKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(Type.OsGeo,
                new GeoCoordinate2d(
                        new Longitude(+180.0), new Latitude(+85.05113877)),
                (short) 1);
        assertTrue(new QuadKey(Type.OsGeo, 1, 1,
                (short) 1).equalTo(quadKey));
        quadKey.getGeoCoordinateBounds2d(bbox);
        assertTrue(bbox.lowerLeft().near(new GeoCoordinate2d(
                new Longitude(+0.0), new Latitude(+0.00000000)), 1e-4));
        assertTrue(bbox.upperRight().near(new GeoCoordinate2d(
                new Longitude(+180.0), new Latitude(+85.05113877)), 1e-4));

        quadKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(Type.OsGeo,
                new GeoCoordinate2d(
                        new Longitude(+180.0), new Latitude(-85.05113877)),
                (short) 1);
        assertTrue(new QuadKey(Type.OsGeo, 0, 1,
                (short) 1).equalTo(quadKey));
        quadKey.getGeoCoordinateBounds2d(bbox);
        assertTrue(bbox.lowerLeft().near(new GeoCoordinate2d(
                new Longitude(+0.0), new Latitude(-85.05113877)), 1e-4));
        assertTrue(bbox.upperRight().near(new GeoCoordinate2d(
                new Longitude(+180.0), new Latitude(+0.00000000)), 1e-4));

        quadKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(Type.OsGeo,
                new GeoCoordinate2d(
                        new Longitude(-180.0), new Latitude(-85.05113877)),
                (short) 1);
        assertTrue(new QuadKey(Type.OsGeo, 0, 0,
                (short) 1).equalTo(quadKey));
        quadKey.getGeoCoordinateBounds2d(bbox);
        assertTrue(bbox.lowerLeft().near(new GeoCoordinate2d(
                new Longitude(-180.0), new Latitude(-85.05113877)), 1e-4));
        assertTrue(bbox.upperRight().near(new GeoCoordinate2d(
                new Longitude(+0.0), new Latitude(+0.00000000)), 1e-4));

        quadKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(Type.OsGeo,
                new GeoCoordinate2d(
                        new Longitude(-180.0), new Latitude(+0.00000000)),
                (short) 1);
        assertTrue(new QuadKey(Type.OsGeo, 0, 0,
                (short) 1).equalTo(quadKey));
        quadKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(Type.OsGeo,
                new GeoCoordinate2d(
                        new Longitude(+0.0), new Latitude(+85.05113877)),
                (short) 1);
        assertTrue(new QuadKey(Type.OsGeo, 1, 0,
                (short) 1).equalTo(quadKey));
        quadKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(Type.OsGeo,
                new GeoCoordinate2d(
                        new Longitude(+180.0), new Latitude(+0.00000000)),
                (short) 1);
        assertTrue(new QuadKey(Type.OsGeo, 0, 1,
                (short) 1).equalTo(quadKey));
        quadKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(Type.OsGeo,
                new GeoCoordinate2d(
                        new Longitude(+0.0), new Latitude(-85.05113877)),
                (short) 1);
        assertTrue(new QuadKey(Type.OsGeo, 0, 0,
                (short) 1).equalTo(quadKey));
        quadKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(Type.OsGeo,
                new GeoCoordinate2d(
                        new Longitude(+0.0), new Latitude(+0.00000000)),
                (short) 1);
        assertTrue(new QuadKey(Type.OsGeo, 0, 0,
                (short) 1).equalTo(quadKey));

        // Note at depth 2 because of the Mercator projection the lines
        // of latitude are note perfect divisions by 2.
        quadKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(Type.OsGeo,
                new GeoCoordinate2d(
                        new Longitude(-180.0), new Latitude(-85.05113877)),
                (short) 2);
        assertTrue(new QuadKey(Type.OsGeo, 0, 0,
                (short) 2).equalTo(quadKey));
        quadKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(Type.OsGeo,
                new GeoCoordinate2d(
                        new Longitude(-180.0), new Latitude(-66.5133)),
                (short) 2);
        assertTrue(new QuadKey(Type.OsGeo, 0, 0,
                (short) 2).equalTo(quadKey));
        quadKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(Type.OsGeo,
                new GeoCoordinate2d(
                        new Longitude(-180.0), new Latitude(-66.5132)),
                (short) 2);
        assertTrue(new QuadKey(Type.OsGeo, 1, 0,
                (short) 2).equalTo(quadKey));
        quadKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(Type.OsGeo,
                new GeoCoordinate2d(
                        new Longitude(-180.0), new Latitude(+0.1)),
                (short) 2);
        assertTrue(new QuadKey(Type.OsGeo, 2, 0,
                (short) 2).equalTo(quadKey));
        quadKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(Type.OsGeo,
                new GeoCoordinate2d(
                        new Longitude(-180.0), new Latitude(+66.5132)),
                (short) 2);
        assertTrue(new QuadKey(Type.OsGeo, 2, 0,
                (short) 2).equalTo(quadKey));
        quadKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(Type.OsGeo,
                new GeoCoordinate2d(
                        new Longitude(-180.0), new Latitude(+66.5133)),
                (short) 2);
        assertTrue(new QuadKey(Type.OsGeo, 3, 0,
                (short) 2).equalTo(quadKey));
        quadKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(Type.OsGeo,
                new GeoCoordinate2d(
                        new Longitude(-180.0), new Latitude(+85.05113877)),
                (short) 2);
        assertTrue(new QuadKey(Type.OsGeo, 3, 0,
                (short) 2).equalTo(quadKey));
        quadKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(Type.OsGeo,
                new GeoCoordinate2d(
                        new Longitude(-90.0), new Latitude(-85.05113877)),
                (short) 2);
        assertTrue(new QuadKey(Type.OsGeo, 0, 0,
                (short) 2).equalTo(quadKey));
        quadKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(Type.OsGeo,
                new GeoCoordinate2d(
                        new Longitude(-90.0), new Latitude(-66.5133)),
                (short) 2);
        assertTrue(new QuadKey(Type.OsGeo, 0, 0,
                (short) 2).equalTo(quadKey));
        quadKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(Type.OsGeo,
                new GeoCoordinate2d(
                        new Longitude(-90.0), new Latitude(-66.5132)),
                (short) 2);
        assertTrue(new QuadKey(Type.OsGeo, 1, 0,
                (short) 2).equalTo(quadKey));
        quadKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(Type.OsGeo,
                new GeoCoordinate2d(
                        new Longitude(-90.0), new Latitude(+0.1)),
                (short) 2);
        assertTrue(new QuadKey(Type.OsGeo, 2, 0,
                (short) 2).equalTo(quadKey));
        quadKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(Type.OsGeo,
                new GeoCoordinate2d(
                        new Longitude(-90.0), new Latitude(+66.5132)),
                (short) 2);
        assertTrue(new QuadKey(Type.OsGeo, 2, 0,
                (short) 2).equalTo(quadKey));
        quadKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(Type.OsGeo,
                new GeoCoordinate2d(
                        new Longitude(-90.0), new Latitude(+66.5133)),
                (short) 2);
        assertTrue(new QuadKey(Type.OsGeo, 3, 0,
                (short) 2).equalTo(quadKey));
        quadKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(Type.OsGeo,
                new GeoCoordinate2d(
                        new Longitude(-90.0), new Latitude(+85.05113877)),
                (short) 2);
        assertTrue(new QuadKey(Type.OsGeo, 3, 0,
                (short) 2).equalTo(quadKey));
        quadKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(Type.OsGeo,
                new GeoCoordinate2d(
                        new Longitude(-89.9), new Latitude(-85.05113877)),
                (short) 2);
        assertTrue(new QuadKey(Type.OsGeo, 0, 1,
                (short) 2).equalTo(quadKey));
        quadKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(Type.OsGeo,
                new GeoCoordinate2d(
                        new Longitude(-89.9), new Latitude(-66.5133)),
                (short) 2);
        assertTrue(new QuadKey(Type.OsGeo, 0, 1,
                (short) 2).equalTo(quadKey));
        quadKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(Type.OsGeo,
                new GeoCoordinate2d(
                        new Longitude(-89.9), new Latitude(-66.5132)),
                (short) 2);
        assertTrue(new QuadKey(Type.OsGeo, 1, 1,
                (short) 2).equalTo(quadKey));
        quadKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(Type.OsGeo,
                new GeoCoordinate2d(
                        new Longitude(-89.9), new Latitude(+0.1)),
                (short) 2);
        assertTrue(new QuadKey(Type.OsGeo, 2, 1,
                (short) 2).equalTo(quadKey));
        quadKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(Type.OsGeo,
                new GeoCoordinate2d(
                        new Longitude(-89.9), new Latitude(+66.5132)),
                (short) 2);
        assertTrue(new QuadKey(Type.OsGeo, 2, 1,
                (short) 2).equalTo(quadKey));
        quadKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(Type.OsGeo,
                new GeoCoordinate2d(
                        new Longitude(-89.9), new Latitude(+66.5133)),
                (short) 2);
        assertTrue(new QuadKey(Type.OsGeo, 3, 1,
                (short) 2).equalTo(quadKey));
        quadKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(Type.OsGeo,
                new GeoCoordinate2d(
                        new Longitude(-89.9), new Latitude(+85.05113877)),
                (short) 2);
        assertTrue(new QuadKey(Type.OsGeo, 3, 1,
                (short) 2).equalTo(quadKey));
        quadKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(Type.OsGeo,
                new GeoCoordinate2d(
                        new Longitude(+0.0), new Latitude(-85.05113877)),
                (short) 2);
        assertTrue(new QuadKey(Type.OsGeo, 0, 1,
                (short) 2).equalTo(quadKey));
        quadKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(Type.OsGeo,
                new GeoCoordinate2d(
                        new Longitude(+0.0), new Latitude(-66.5133)),
                (short) 2);
        assertTrue(new QuadKey(Type.OsGeo, 0, 1,
                (short) 2).equalTo(quadKey));
        quadKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(Type.OsGeo,
                new GeoCoordinate2d(
                        new Longitude(+0.0), new Latitude(-66.5132)),
                (short) 2);
        assertTrue(new QuadKey(Type.OsGeo, 1, 1,
                (short) 2).equalTo(quadKey));
        quadKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(Type.OsGeo,
                new GeoCoordinate2d(
                        new Longitude(+0.0), new Latitude(+0.1)),
                (short) 2);
        assertTrue(new QuadKey(Type.OsGeo, 2, 1,
                (short) 2).equalTo(quadKey));
        quadKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(Type.OsGeo,
                new GeoCoordinate2d(
                        new Longitude(+0.0), new Latitude(+66.5132)),
                (short) 2);
        assertTrue(new QuadKey(Type.OsGeo, 2, 1,
                (short) 2).equalTo(quadKey));
        quadKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(Type.OsGeo,
                new GeoCoordinate2d(
                        new Longitude(+0.0), new Latitude(+66.5133)),
                (short) 2);
        assertTrue(new QuadKey(Type.OsGeo, 3, 1,
                (short) 2).equalTo(quadKey));
        quadKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(Type.OsGeo,
                new GeoCoordinate2d(
                        new Longitude(+0.0), new Latitude(+85.05113877)),
                (short) 2);
        assertTrue(new QuadKey(Type.OsGeo, 3, 1,
                (short) 2).equalTo(quadKey));
        quadKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(Type.OsGeo,
                new GeoCoordinate2d(
                        new Longitude(+0.1), new Latitude(-85.05113877)),
                (short) 2);
        assertTrue(new QuadKey(Type.OsGeo, 0, 2,
                (short) 2).equalTo(quadKey));
        quadKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(Type.OsGeo,
                new GeoCoordinate2d(
                        new Longitude(+0.1), new Latitude(-66.5133)),
                (short) 2);
        assertTrue(new QuadKey(Type.OsGeo, 0, 2,
                (short) 2).equalTo(quadKey));
        quadKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(Type.OsGeo,
                new GeoCoordinate2d(
                        new Longitude(+0.1), new Latitude(-66.5132)),
                (short) 2);
        assertTrue(new QuadKey(Type.OsGeo, 1, 2,
                (short) 2).equalTo(quadKey));
        quadKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(Type.OsGeo,
                new GeoCoordinate2d(
                        new Longitude(+0.1), new Latitude(+0.1)),
                (short) 2);
        assertTrue(new QuadKey(Type.OsGeo, 2, 2,
                (short) 2).equalTo(quadKey));
        quadKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(Type.OsGeo,
                new GeoCoordinate2d(
                        new Longitude(+0.1), new Latitude(+66.5132)),
                (short) 2);
        assertTrue(new QuadKey(Type.OsGeo, 2, 2,
                (short) 2).equalTo(quadKey));
        quadKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(Type.OsGeo,
                new GeoCoordinate2d(
                        new Longitude(+0.1), new Latitude(+66.5133)),
                (short) 2);
        assertTrue(new QuadKey(Type.OsGeo, 3, 2,
                (short) 2).equalTo(quadKey));
        quadKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(Type.OsGeo,
                new GeoCoordinate2d(
                        new Longitude(+0.1), new Latitude(+85.05113877)),
                (short) 2);
        assertTrue(new QuadKey(Type.OsGeo, 3, 2,
                (short) 2).equalTo(quadKey));
        quadKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(Type.OsGeo,
                new GeoCoordinate2d(
                        new Longitude(+90.0), new Latitude(-85.05113877)),
                (short) 2);
        assertTrue(new QuadKey(Type.OsGeo, 0, 2,
                (short) 2).equalTo(quadKey));
        quadKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(Type.OsGeo,
                new GeoCoordinate2d(
                        new Longitude(+90.0), new Latitude(-66.5133)),
                (short) 2);
        assertTrue(new QuadKey(Type.OsGeo, 0, 2,
                (short) 2).equalTo(quadKey));
        quadKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(Type.OsGeo,
                new GeoCoordinate2d(
                        new Longitude(+90.0), new Latitude(-66.5132)),
                (short) 2);
        assertTrue(new QuadKey(Type.OsGeo, 1, 2,
                (short) 2).equalTo(quadKey));
        quadKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(Type.OsGeo,
                new GeoCoordinate2d(
                        new Longitude(+90.0), new Latitude(+0.1)),
                (short) 2);
        assertTrue(new QuadKey(Type.OsGeo, 2, 2,
                (short) 2).equalTo(quadKey));
        quadKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(Type.OsGeo,
                new GeoCoordinate2d(
                        new Longitude(+90.0), new Latitude(+66.5132)),
                (short) 2);
        assertTrue(new QuadKey(Type.OsGeo, 2, 2,
                (short) 2).equalTo(quadKey));
        quadKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(Type.OsGeo,
                new GeoCoordinate2d(
                        new Longitude(+90.0), new Latitude(+66.5133)),
                (short) 2);
        assertTrue(new QuadKey(Type.OsGeo, 3, 2,
                (short) 2).equalTo(quadKey));
        quadKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(Type.OsGeo,
                new GeoCoordinate2d(
                        new Longitude(+90.0), new Latitude(+85.05113877)),
                (short) 2);
        assertTrue(new QuadKey(Type.OsGeo, 3, 2,
                (short) 2).equalTo(quadKey));
        quadKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(Type.OsGeo,
                new GeoCoordinate2d(
                        new Longitude(+90.1), new Latitude(-85.05113877)),
                (short) 2);
        assertTrue(new QuadKey(Type.OsGeo, 0, 3,
                (short) 2).equalTo(quadKey));
        quadKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(Type.OsGeo,
                new GeoCoordinate2d(
                        new Longitude(+90.1), new Latitude(-66.5133)),
                (short) 2);
        assertTrue(new QuadKey(Type.OsGeo, 0, 3,
                (short) 2).equalTo(quadKey));
        quadKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(Type.OsGeo,
                new GeoCoordinate2d(
                        new Longitude(+90.1), new Latitude(-66.5132)),
                (short) 2);
        assertTrue(new QuadKey(Type.OsGeo, 1, 3,
                (short) 2).equalTo(quadKey));
        quadKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(Type.OsGeo,
                new GeoCoordinate2d(
                        new Longitude(+90.1), new Latitude(+0.1)),
                (short) 2);
        assertTrue(new QuadKey(Type.OsGeo, 2, 3,
                (short) 2).equalTo(quadKey));
        quadKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(Type.OsGeo,
                new GeoCoordinate2d(
                        new Longitude(+90.1), new Latitude(+66.5132)),
                (short) 2);
        assertTrue(new QuadKey(Type.OsGeo, 2, 3,
                (short) 2).equalTo(quadKey));
        quadKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(Type.OsGeo,
                new GeoCoordinate2d(
                        new Longitude(+90.1), new Latitude(+66.5133)),
                (short) 2);
        assertTrue(new QuadKey(Type.OsGeo, 3, 3,
                (short) 2).equalTo(quadKey));
        quadKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(Type.OsGeo,
                new GeoCoordinate2d(
                        new Longitude(+90.1), new Latitude(+85.05113877)),
                (short) 2);
        assertTrue(new QuadKey(Type.OsGeo, 3, 3,
                (short) 2).equalTo(quadKey));
        quadKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(Type.OsGeo,
                new GeoCoordinate2d(
                        new Longitude(+180.0), new Latitude(-85.05113877)),
                (short) 2);
        assertTrue(new QuadKey(Type.OsGeo, 0, 3,
                (short) 2).equalTo(quadKey));
        quadKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(Type.OsGeo,
                new GeoCoordinate2d(
                        new Longitude(+180.0), new Latitude(-66.5133)),
                (short) 2);
        assertTrue(new QuadKey(Type.OsGeo, 0, 3,
                (short) 2).equalTo(quadKey));
        quadKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(Type.OsGeo,
                new GeoCoordinate2d(
                        new Longitude(+180.0), new Latitude(-66.5132)),
                (short) 2);
        assertTrue(new QuadKey(Type.OsGeo, 1, 3,
                (short) 2).equalTo(quadKey));
        quadKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(Type.OsGeo,
                new GeoCoordinate2d(
                        new Longitude(+180.0), new Latitude(+0.1)),
                (short) 2);
        assertTrue(new QuadKey(Type.OsGeo, 2, 3,
                (short) 2).equalTo(quadKey));
        quadKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(Type.OsGeo,
                new GeoCoordinate2d(
                        new Longitude(+180.0), new Latitude(+66.5132)),
                (short) 2);
        assertTrue(new QuadKey(Type.OsGeo, 2, 3, (short) 2).equalTo(quadKey));
        quadKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(Type.OsGeo,
                new GeoCoordinate2d(
                        new Longitude(+180.0), new Latitude(+66.5133)),
                (short) 2);
        assertTrue(new QuadKey(Type.OsGeo, 3, 3,
                (short) 2).equalTo(quadKey));
        quadKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(Type.OsGeo,
                new GeoCoordinate2d(
                        new Longitude(+180.0), new Latitude(+85.05113877)),
                (short) 2);
        assertTrue(new QuadKey(Type.OsGeo, 3, 3,
                (short) 2).equalTo(quadKey));
    }

    @Test
    public void getKeysFromLongitudeLatitudeBoundingBoxTest() {
        QuadKeyVector quadKeys;

        quadKeys = QuadKey.getKeysFromLongitudeLatitudeBoundingBox(
                Type.OsGeo, new GeoCoordinateBoundingBox2d(
                        new GeoCoordinate2d(
                                new Longitude(+0.0),
                                new Latitude(-0.10000000)),
                        new GeoCoordinate2d(
                                new Longitude(+0.1),
                                new Latitude(+0.10000000))),
                (short) 0);
        assertEquals(1, quadKeys.size());
        assertTrue(vectorContains(quadKeys, new QuadKey(
                Type.OsGeo, 0, 0, (short) 0)));

        quadKeys = QuadKey.getKeysFromLongitudeLatitudeBoundingBox(
                Type.OsGeo, new GeoCoordinateBoundingBox2d(
                        new GeoCoordinate2d(
                                new Longitude(-180.0),
                                new Latitude(-85.05113877)),
                        new GeoCoordinate2d(
                                new Longitude(+180.0),
                                new Latitude(+85.05113877))),
                (short) 1);
        assertEquals(4, quadKeys.size());
        assertTrue(vectorContains(quadKeys, new QuadKey(
                Type.OsGeo, 0, 0, (short) 1)));
        assertTrue(vectorContains(quadKeys, new QuadKey(
                Type.OsGeo, 0, 1, (short) 1)));
        assertTrue(vectorContains(quadKeys, new QuadKey(
                Type.OsGeo, 1, 0, (short) 1)));
        assertTrue(vectorContains(quadKeys, new QuadKey(
                Type.OsGeo, 1, 1, (short) 1)));

        quadKeys = QuadKey.getKeysFromLongitudeLatitudeBoundingBox(
                Type.OsGeo, new GeoCoordinateBoundingBox2d(
                        new GeoCoordinate2d(
                                new Longitude(-180.0),
                                new Latitude(-85.05113877)),
                        new GeoCoordinate2d(
                                new Longitude(+0.0),
                                new Latitude(+85.05113877))),
                (short) 1);
        assertEquals(2, quadKeys.size());
        assertTrue(vectorContains(quadKeys, new QuadKey(
                Type.OsGeo, 1, 0, (short) 1)));
        assertTrue(vectorContains(quadKeys, new QuadKey(
                Type.OsGeo, 0, 0, (short) 1)));

        quadKeys = QuadKey.getKeysFromLongitudeLatitudeBoundingBox(
                Type.OsGeo, new GeoCoordinateBoundingBox2d(
                        new GeoCoordinate2d(
                                new Longitude(+0.1),
                                new Latitude(-85.05113877)),
                        new GeoCoordinate2d(
                                new Longitude(+180.0),
                                new Latitude(+85.05113877))),
                (short) 1);
        assertEquals(2, quadKeys.size());
        assertTrue(vectorContains(quadKeys, new QuadKey(
                Type.OsGeo, 1, 1, (short) 1)));
        assertTrue(vectorContains(quadKeys, new QuadKey(
                Type.OsGeo, 0, 1, (short) 1)));

        quadKeys = QuadKey.getKeysFromLongitudeLatitudeBoundingBox(
                Type.OsGeo, new GeoCoordinateBoundingBox2d(
                        new GeoCoordinate2d(
                                new Longitude(-180.0),
                                new Latitude(-85.05113877)),
                        new GeoCoordinate2d(
                                new Longitude(+0.0),
                                new Latitude(+0.00000000))),
                (short) 1);
        assertEquals(1, quadKeys.size());
        assertTrue(vectorContains(quadKeys, new QuadKey(
                Type.OsGeo, 0, 0, (short) 1)));

        quadKeys = QuadKey.getKeysFromLongitudeLatitudeBoundingBox(
                Type.OsGeo, new GeoCoordinateBoundingBox2d(
                        new GeoCoordinate2d(
                                new Longitude(-180.0),
                                new Latitude(+0.10000000)),
                        new GeoCoordinate2d(
                                new Longitude(+0.0),
                                new Latitude(+85.05113877))),
                (short) 1);
        assertEquals(1, quadKeys.size());
        assertTrue(vectorContains(quadKeys, new QuadKey(
                Type.OsGeo, 1, 0, (short) 1)));

        quadKeys = QuadKey.getKeysFromLongitudeLatitudeBoundingBox(
                Type.OsGeo, new GeoCoordinateBoundingBox2d(
                        new GeoCoordinate2d(
                                new Longitude(+0.1),
                                new Latitude(-85.05113877)),
                        new GeoCoordinate2d(
                                new Longitude(+180.0),
                                new Latitude(+0.00000000))),
                (short) 1);
        assertEquals(1, quadKeys.size());
        assertTrue(vectorContains(quadKeys, new QuadKey(
                Type.OsGeo, 0, 1, (short) 1)));

        quadKeys = QuadKey.getKeysFromLongitudeLatitudeBoundingBox(
                Type.OsGeo, new GeoCoordinateBoundingBox2d(
                        new GeoCoordinate2d(
                                new Longitude(+0.1),
                                new Latitude(+0.10000000)),
                        new GeoCoordinate2d(
                                new Longitude(+180.0),
                                new Latitude(+85.05113877))),
                (short) 1);
        assertEquals(1, quadKeys.size());
        assertTrue(vectorContains(quadKeys, new QuadKey(
                Type.OsGeo, 1, 1, (short) 1)));
    }

    @Test
    public void selecetedCitiesTest() {
        // TODO: Implement Tests. Taken from Earthscape. No tests there.
    }
}

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

public class LatLongSystemTest {

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
    public void isValidTest()
    {
        // See TestQuadKey TestSpecificCtorTest.
    }

    @Test
    public void isRootKeyTest()
    {
        // Same as BingSystem
    }

    @Test
    public void getParentTest()
    {
        // Same as BingSystem
    }

    @Test
    public void isMyAncestorTest()
    {
        // Same as BingSystem
    }

    @Test
    public void getAncestorTest()
    {
        // Same as BingSystem
    }

    @Test
    public void getChildTest()
    {
        // Same as BingSystem
    }

    @Test
    public void getChildrenTest()
    {
        // Same as BingSystem
    }

    @Test
    public void getDescendantsTest()
    {
        // Same as BingSystem
    }

    @Test
    public void getSiblingsTest()
    {
        // Same as BingSystem
    }

    @Test
    public void getNeighborsTest()
    {
        // Same as BingSystem
    }

    @Test
    public void fromStringToStringTest()
    {
        // Same as BingSystem
    }

    @Test
    public void getGeoCoordinateBounds2dTest()
    {
        QuadKey key;
        GeoCoordinateBoundingBox2d bbox = new GeoCoordinateBoundingBox2d();

        { // Depth 0
            key = new QuadKey(Type.LatLong, 0, 0, (short) 0);
            key.getGeoCoordinateBounds2d(bbox);
            assertTrue(new GeoCoordinate2d(new Longitude(-180.0),
                    new Latitude(-90.0)).equalTo(bbox.lowerLeft()));
            assertTrue(new GeoCoordinate2d(new Longitude(+180.0),
                    new Latitude(+90.0)).equalTo(bbox.upperRight()));
        }

        { // Depth 1
            key = new QuadKey(Type.LatLong, 0, 0, (short) 1);
            key.getGeoCoordinateBounds2d(bbox);
            assertTrue(bbox.lowerLeft().longitude().near(
                    new Longitude(-180.0), 1e-6));
            assertTrue(bbox.lowerLeft().latitude().near(
                    new Latitude(-90.0), 1e-6));
            assertTrue(bbox.upperRight().longitude().near(
                    new Longitude(+0.0), 1e-6));
            assertTrue(bbox.upperRight().latitude().near(
                    new Latitude(+0.0), 1e-6));

            key = new QuadKey(Type.LatLong, 0, 1, (short) 1);
            key.getGeoCoordinateBounds2d(bbox);
            assertTrue(bbox.lowerLeft().longitude().near(
                    new Longitude(+0.0), 1e-6));
            assertTrue(bbox.lowerLeft().latitude().near(
                    new Latitude(-90.0), 1e-6));
            assertTrue(bbox.upperRight().longitude().near(
                    new Longitude(+180.0), 1e-6));
            assertTrue(bbox.upperRight().latitude().near(
                    new Latitude(+0.0), 1e-6));

            key = new QuadKey(Type.LatLong, 1, 0, (short) 1);
            key.getGeoCoordinateBounds2d(bbox);
            assertTrue(bbox.lowerLeft().longitude().near(
                    new Longitude(-180.0), 1e-6));
            assertTrue(bbox.lowerLeft().latitude().near(
                    new Latitude(+0.0), 1e-6));
            assertTrue(bbox.upperRight().longitude().near(
                    new Longitude(+0.0), 1e-6));
            assertTrue(bbox.upperRight().latitude().near(
                    new Latitude(+90.0), 1e-6));

            key = new QuadKey(Type.LatLong, 1, 1, (short) 1);
            key.getGeoCoordinateBounds2d(bbox);
            assertTrue(bbox.lowerLeft().longitude().near(
                    new Longitude(+0.0), 1e-6));
            assertTrue(bbox.lowerLeft().latitude().near(
                    new Latitude(+0.0), 1e-6));
            assertTrue(bbox.upperRight().longitude().near(
                    new Longitude(+180.0), 1e-6));
            assertTrue(bbox.upperRight().latitude().near(
                    new Latitude(+90.0), 1e-6));
        }
    }

    @Test
    public void getKeysFromLongitudeLatitudeAtDepthToBoundsTest()
    {
        QuadKey key;

        { // Depth 0
            key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    Type.LatLong, new GeoCoordinate2d(
                            new Longitude(-180.0), new Latitude(-90)),
                    (short) 0);
            assertTrue(new QuadKey(
                    Type.LatLong, 0, 0, (short) 0).equalTo(key));
            assertEquals("", key.toInternalString());
        }

        // Inclusion here consists of lower left
        //    X------X------X
        //    |   2  |   3  |
        //    |      |      |
        //    X------X------X
        //    |   0  |   1  |
        //    |      |      |
        // ll X------X------X
        { // Depth 1
            key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    Type.LatLong, new GeoCoordinate2d(
                            new Longitude(-180.0), new Latitude(-90.0)),
                    (short) 1);
            assertTrue(new QuadKey(
                    Type.LatLong, 0, 0, (short) 1).equalTo(key));
            assertEquals("2", key.toInternalString());
            key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    Type.LatLong, new GeoCoordinate2d(
                            new Longitude(-0.1), new Latitude(-90.0)),
                    (short) 1);
            assertTrue(new QuadKey(
                    Type.LatLong, 0, 0, (short) 1).equalTo(key));
            assertEquals("2", key.toInternalString());
            key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    Type.LatLong, new GeoCoordinate2d(
                            new Longitude(-0.1), new Latitude(-0.1)),
                    (short) 1);
            assertTrue(new QuadKey(
                    Type.LatLong, 0, 0, (short) 1).equalTo(key));
            assertEquals("2", key.toInternalString());
            key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    Type.LatLong, new GeoCoordinate2d(
                            new Longitude(-180.0), new Latitude(-0.1)),
                    (short) 1);
            assertTrue(new QuadKey(
                    Type.LatLong, 0, 0, (short) 1).equalTo(key));
            assertEquals("2", key.toInternalString());

            key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    Type.LatLong, new GeoCoordinate2d(
                            new Longitude(+0.0), new Latitude(-90.0)),
                    (short) 1);
            assertTrue(new QuadKey(
                    Type.LatLong, 0, 1, (short) 1).equalTo(key));
            assertEquals("3", key.toInternalString());
            key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    Type.LatLong, new GeoCoordinate2d(
                            new Longitude(+180.0), new Latitude(-90.0)),
                    (short) 1);
            assertTrue(new QuadKey(
                    Type.LatLong, 0, 1, (short) 1).equalTo(key));
            assertEquals("3", key.toInternalString());
            key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    Type.LatLong, new GeoCoordinate2d(
                            new Longitude(+180.0), new Latitude(-0.1)),
                    (short) 1);
            assertTrue(new QuadKey(
                    Type.LatLong, 0, 1, (short) 1).equalTo(key));
            assertEquals("3", key.toInternalString());
            key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    Type.LatLong, new GeoCoordinate2d(
                            new Longitude(+0.0), new Latitude(-0.1)),
                    (short) 1);
            assertTrue(new QuadKey(
                    Type.LatLong, 0, 1, (short) 1).equalTo(key));
            assertEquals("3", key.toInternalString());

            key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    Type.LatLong, new GeoCoordinate2d(
                            new Longitude(-180.0), new Latitude(+0.0)),
                    (short) 1);
            assertTrue(new QuadKey(
                    Type.LatLong, 1, 0, (short) 1).equalTo(key));
            assertEquals("0", key.toInternalString());
            key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    Type.LatLong, new GeoCoordinate2d(
                            new Longitude(-0.1), new Latitude(+0.0)),
                    (short) 1);
            assertTrue(new QuadKey(
                    Type.LatLong, 1, 0, (short) 1).equalTo(key));
            assertEquals("0", key.toInternalString());
            key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    Type.LatLong, new GeoCoordinate2d(
                            new Longitude(-180.0), new Latitude(+90.0)),
                    (short) 1);
            assertTrue(new QuadKey(
                    Type.LatLong, 1, 0, (short) 1).equalTo(key));
            assertEquals("0", key.toInternalString());
            key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    Type.LatLong, new GeoCoordinate2d(
                            new Longitude(-0.1), new Latitude(+90.0)),
                    (short) 1);
            assertTrue(new QuadKey(
                    Type.LatLong, 1, 0, (short) 1).equalTo(key));
            assertEquals("0", key.toInternalString());

            key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    Type.LatLong, new GeoCoordinate2d(
                            new Longitude(+0.0), new Latitude(+0.0)),
                    (short) 1);
            assertTrue(new QuadKey(
                    Type.LatLong, 1, 1, (short) 1).equalTo(key));
            assertEquals("1", key.toInternalString());
            key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    Type.LatLong, new GeoCoordinate2d(
                            new Longitude(+180.0), new Latitude(+0.0)),
                    (short) 1);
            assertTrue(new QuadKey(
                    Type.LatLong, 1, 1, (short) 1).equalTo(key));
            assertEquals("1", key.toInternalString());
            key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    Type.LatLong, new GeoCoordinate2d(
                            new Longitude(+0.0), new Latitude(+90.0)),
                    (short) 1);
            assertTrue(new QuadKey(
                    Type.LatLong, 1, 1, (short) 1).equalTo(key));
            assertEquals("1", key.toInternalString());
            key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    Type.LatLong, new GeoCoordinate2d(
                            new Longitude(+180.0), new Latitude(+90.0)),
                    (short) 1);
            assertTrue(new QuadKey(
                    Type.LatLong, 1, 1, (short) 1).equalTo(key));
            assertEquals("1", key.toInternalString());
        }
    }

    @Test
    public void getKeysFromLongitudeLatitudeBoundingBoxTest()
    {
        {
            QuadKeyVector outKeys;
            outKeys = QuadKey.getKeysFromLongitudeLatitudeBoundingBox(
                    Type.LatLong,
                    new GeoCoordinateBoundingBox2d(
                            new GeoCoordinate2d(
                                    new Longitude(-180.0),
                                    new Latitude(+90.0)),
                            new GeoCoordinate2d(
                                    new Longitude(+180.0),
                                    new Latitude(-90.0))),
                    (short) 0);
            assertEquals((short) 1, outKeys.size());
            assertTrue(vectorContains(outKeys, new QuadKey(
                    Type.LatLong, 0, 0, (short) 0)));
        }

        {
            QuadKeyVector outKeys;
            outKeys = QuadKey.getKeysFromLongitudeLatitudeBoundingBox(
                    Type.LatLong,
                    new GeoCoordinateBoundingBox2d(
                            new GeoCoordinate2d(
                                    new Longitude(-180.0),
                                    new Latitude(+90.0)),
                            new GeoCoordinate2d(
                                    new Longitude(+180.0),
                                    new Latitude(-90.0))),
                    (short) 1);
            assertEquals((short) 4, outKeys.size());
            assertTrue(vectorContains(outKeys, new QuadKey(
                    Type.LatLong, 0, 0, (short) 1)));
            assertTrue(vectorContains(outKeys, new QuadKey(
                    Type.LatLong, 0, 1, (short) 1)));
            assertTrue(vectorContains(outKeys, new QuadKey(
                    Type.LatLong, 1, 0, (short) 1)));
            assertTrue(vectorContains(outKeys, new QuadKey(
                    Type.LatLong, 1, 1, (short) 1)));
        }

        {
            QuadKeyVector outKeys;
            outKeys = QuadKey.getKeysFromLongitudeLatitudeBoundingBox(
                    Type.LatLong,
                    new GeoCoordinateBoundingBox2d(
                            new GeoCoordinate2d(
                                    new Longitude(-180.0),
                                    new Latitude(-0.1)),
                            new GeoCoordinate2d(
                                    new Longitude(-0.1),
                                    new Latitude(+90.0))),
                    (short) 1);
            assertEquals(2, outKeys.size());
            assertTrue(vectorContains(outKeys, new QuadKey(
                    Type.LatLong, 0, 0, (short) 1)));
            assertTrue(vectorContains(outKeys, new QuadKey(
                    Type.LatLong, 1, 0, (short) 1)));
        }

        {
            QuadKeyVector outKeys;
            outKeys = QuadKey.getKeysFromLongitudeLatitudeBoundingBox(
                    Type.LatLong,
                    new GeoCoordinateBoundingBox2d(
                            new GeoCoordinate2d(
                                    new Longitude(+0.0),
                                    new Latitude(-0.1)),
                            new GeoCoordinate2d(
                                    new Longitude(+180.0),
                                    new Latitude(+90.0))),
                    (short) 1);
            assertEquals(2, outKeys.size());
            assertTrue(vectorContains(outKeys, new QuadKey(
                    Type.LatLong, 0, 1, (short) 1)));
            assertTrue(vectorContains(outKeys, new QuadKey(
                    Type.LatLong, 1, 1, (short) 1)));
        }

        {
            QuadKeyVector outKeys;
            outKeys = QuadKey.getKeysFromLongitudeLatitudeBoundingBox(
                    Type.LatLong,
                    new GeoCoordinateBoundingBox2d(
                            new GeoCoordinate2d(
                                    new Longitude(-0.1),
                                    new Latitude(-0.1)),
                            new GeoCoordinate2d(
                                    new Longitude(+0.1),
                                    new Latitude(+0.1))),
                    (short) 1);
            assertEquals(4, outKeys.size());
            assertTrue(vectorContains(outKeys, new QuadKey(
                    Type.LatLong, 0, 0, (short) 1)));
            assertTrue(vectorContains(outKeys, new QuadKey(
                    Type.LatLong, 0, 1, (short) 1)));
            assertTrue(vectorContains(outKeys, new QuadKey(
                    Type.LatLong, 1, 0, (short) 1)));
            assertTrue(vectorContains(outKeys, new QuadKey(
                    Type.LatLong, 1, 1, (short) 1)));
        }
    }

    @Test
    public void knownSampleOfLocationsTest()
    {
        QuadKey key;

        {
            key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    Type.LatLong, new GeoCoordinate2d(
                            new Longitude(-122.4183), new Latitude(37.7750)),
                    (short) 1);
            assertEquals("0", key.toInternalString());
            key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    Type.LatLong, new GeoCoordinate2d(
                            new Longitude(-122.4183), new Latitude(37.7750)),
                    (short) 2);
            assertEquals("02", key.toInternalString());
            key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    Type.LatLong, new GeoCoordinate2d(
                            new Longitude(-122.4183), new Latitude(37.7750)),
                    (short) 3);
            assertEquals("021", key.toInternalString());
            key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    Type.LatLong, new GeoCoordinate2d(
                            new Longitude(-122.4183), new Latitude(37.7750)),
                    (short) 4);
            assertEquals("0210", key.toInternalString());
        }

        {
            key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    Type.LatLong, new GeoCoordinate2d(
                            new Longitude(+134.9), new Latitude(-67.6)),
                    (short) 3);
            assertTrue(new QuadKey(
                    Type.LatLong, 0, 6, (short) 3).equalTo(key));
            assertEquals("332", key.toInternalString());

            key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    Type.LatLong, new GeoCoordinate2d(
                            new Longitude(+135.0), new Latitude(-67.5)),
                    (short) 3);
            assertTrue(new QuadKey(
                    Type.LatLong, 1, 7, (short) 3).equalTo(key));
            assertEquals("331", key.toInternalString());
        }
    }
}

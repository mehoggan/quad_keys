import static org.junit.Assert.*;

import com.quadkey.GeoCoordinate2d;
import com.quadkey.Latitude;
import com.quadkey.Longitude;

import org.junit.BeforeClass;
import org.junit.Test;

public class GeoCoordinate2dTest {

    @BeforeClass
    public static void setUpBeforeClass() throws Exception {
        System.loadLibrary("QuadKey");
    }

    @Test
    public void defaultCtorTest() {
        GeoCoordinate2d empty = new GeoCoordinate2d();
        assertTrue(new Longitude(0.0).equalTo(empty.longitude()));
        assertTrue(new Latitude(0.0).equalTo(empty.latitude()));
    }

    @Test
    public void ctorTest() {
        {
            GeoCoordinate2d coord = new GeoCoordinate2d(new Longitude(0.0),
                    new Latitude(0.0));
            assertTrue(new Longitude(0.0).equalTo(coord.longitude()));
            assertTrue(new Latitude(0.0).equalTo(coord.latitude()));
        }

        {
            GeoCoordinate2d coord = new GeoCoordinate2d(
                    new Longitude(-180.001), new Latitude(-95.0));
            assertTrue(new Longitude(-180.0).equalTo(
                    coord.longitude()));
            assertTrue(new Latitude(-90.0).equalTo(coord.latitude()));
        }

        {
            GeoCoordinate2d coord = new GeoCoordinate2d(
                    new Longitude(-180.001), new Latitude(95.0));
            assertTrue(new Longitude(-180.0).equalTo(
                    coord.longitude()));
            assertTrue(new Latitude(90.0).equalTo(coord.latitude()));
        }

        {
            GeoCoordinate2d coord = new GeoCoordinate2d(
                    new Longitude(180.001), new Latitude(95.0));
            assertTrue(new Longitude(180.0).equalTo(coord.longitude()));
            assertTrue(new Latitude(90.0).equalTo(coord.latitude()));
        }

        {
            GeoCoordinate2d coord = new GeoCoordinate2d(
                    new Longitude(180.001), new Latitude(-95.0));
            assertTrue(new Longitude(180.0).equalTo(coord.longitude()));
            assertTrue(new Latitude(-90.0).equalTo(coord.latitude()));
        }
    }

    @Test
    public void nearTest() {
        {
            Longitude lon = new Longitude(0.001);
            assertTrue(lon.near(new Longitude(0.0009), 1e-3));
        }

        {
            Longitude lon = new Longitude(0.001);
            assertFalse(lon.near(new Longitude(0.0009), 1e-4));
        }

        {
            Latitude lat = new Latitude(0.001);
            assertTrue(lat.near(new Latitude(0.0009), 1e-3));
        }

        {
            Latitude lat = new Latitude(0.001);
            assertFalse(lat.near(new Latitude(0.0009), 1e-4));
        }

        {
            GeoCoordinate2d coord = new GeoCoordinate2d(
                    new Longitude(0.001), new Latitude(0.001));
            assertTrue(coord.near(new GeoCoordinate2d(
                    new Longitude(0.0009), new Latitude(0.0009)), 1e-3));
        }

        {
            GeoCoordinate2d coord = new GeoCoordinate2d(
                    new Longitude(0.001), new Latitude(0.001));
            assertFalse(coord.near(new GeoCoordinate2d(
                    new Longitude(0.001), new Latitude(0.0009)), 1e-4));
        }

        {
            GeoCoordinate2d  coord = new GeoCoordinate2d(
                    new Longitude(0.001), new Latitude(0.001));
            assertFalse(coord.near(new GeoCoordinate2d(
                    new Longitude(0.0009), new Latitude(0.001)), 1e-4));
        }
    }

    @Test
    public void operatorlessThanTest() {
        GeoCoordinate2d sw = new GeoCoordinate2d(
                new Longitude(-0.1), new Latitude(-0.1));
        GeoCoordinate2d ne = new GeoCoordinate2d(
                new Longitude(+0.1), new Latitude(+0.1));

        assertTrue(sw.longitude().lessThan(ne.longitude()));
        assertTrue(sw.latitude().lessThan(ne.latitude()));
    }

    @Test
    public void operatorlessThanOrEqualTest() {
        {
            GeoCoordinate2d sw = new GeoCoordinate2d(
                    new Longitude(-0.1), new Latitude(-0.1));
            GeoCoordinate2d ne = new GeoCoordinate2d(
                    new Longitude(+0.1), new Latitude(+0.1));

            assertTrue(sw.longitude().lessThanOrEqual(ne.longitude()));
            assertTrue(sw.latitude().lessThanOrEqual(ne.latitude()));
        }

        {
            GeoCoordinate2d sw = new GeoCoordinate2d(
                    new Longitude(-0.1), new Latitude(-0.1));
            GeoCoordinate2d ne = new GeoCoordinate2d(
                    new Longitude(-0.1), new Latitude(-0.1));

            assertTrue(sw.longitude().lessThanOrEqual(ne.longitude()));
            assertTrue(sw.latitude().lessThanOrEqual(ne.latitude()));
        }
    }

    @Test
    public void operatorEqualTest() {
        GeoCoordinate2d sw = new GeoCoordinate2d(
                new Longitude(-0.1), new Latitude(-0.1));
        GeoCoordinate2d ne = new GeoCoordinate2d(
                new Longitude(-0.1), new Latitude(-0.1));

        assertTrue(sw.longitude().equalTo(ne.longitude()));
        assertTrue(sw.latitude().equalTo(ne.latitude()));
    }
}

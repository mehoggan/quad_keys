import static org.junit.Assert.*;

import com.quadkey.GeoCoordinateBoundingBox2d;
import com.quadkey.GeoCoordinate2d;
import com.quadkey.Latitude;
import com.quadkey.Longitude;

import org.junit.BeforeClass;
import org.junit.Test;


public class GeoCoordinateBoundingBox2dTest {

    @BeforeClass
    public static void setUpBeforeClass() throws Exception {
        System.loadLibrary("QuadKey");
    }

   @Test
   public void defaultCtorTest() {
       GeoCoordinateBoundingBox2d empty =
               new GeoCoordinateBoundingBox2d();
       assertFalse(empty.isValid());
       assertFalse(empty.contains(
               new GeoCoordinate2d(new Longitude(0.0), new Latitude(0.0))));
   }

   @Test
   public void ctorStandardConstructionTest() {
       { // Lower Left / Upper Right Construction
           GeoCoordinateBoundingBox2d geoBox =
                   new GeoCoordinateBoundingBox2d(
                           new GeoCoordinate2d(
                                   new Longitude(0.0), new Latitude(0.0)),
                           new GeoCoordinate2d(
                                   new Longitude(180.0), new Latitude(90.0)));

           assertTrue(new GeoCoordinate2d(new Longitude(0.0),
                   new Latitude(0.0)).equalTo(geoBox.lowerLeft()));
           assertTrue(new GeoCoordinate2d(new Longitude(180.0),
                   new Latitude(90.0)).equalTo(geoBox.upperRight()));
           assertTrue(geoBox.isValid());
       }

       { // Upper Left / Lower Right Construction
           GeoCoordinateBoundingBox2d geoBox =
                   new GeoCoordinateBoundingBox2d(
                           new GeoCoordinate2d(
                                   new Longitude(0.0), new Latitude(90.0)),
                           new GeoCoordinate2d(
                                   new Longitude(180.0), new Latitude(0.0)));

           assertTrue(new GeoCoordinate2d(
                   new Longitude(0.0), new Latitude(0.0)).equalTo(
                   geoBox.lowerLeft()));
           assertTrue(new GeoCoordinate2d(
                   new Longitude(180.0), new Latitude(90.0)).equalTo(
                   geoBox.upperRight()));
           assertTrue(geoBox.isValid());
       }

       { // Upper Right / Lower Left Construction
           GeoCoordinateBoundingBox2d geoBox =
                   new GeoCoordinateBoundingBox2d(
                           new GeoCoordinate2d(
                                   new Longitude(180.0), new Latitude(0.0)),
                           new GeoCoordinate2d(
                                   new Longitude(0.0), new Latitude(90.0)));

           assertTrue(new GeoCoordinate2d(new Longitude(0.0),
                   new Latitude(0.0)).equalTo(geoBox.lowerLeft()));
           assertTrue(new GeoCoordinate2d(new Longitude(180.0),
                   new Latitude(90.0)).equalTo(geoBox.upperRight()));
           assertTrue(geoBox.isValid());
       }

       { // Lower Right / Upper Left Construction
           GeoCoordinateBoundingBox2d geoBox =
                   new GeoCoordinateBoundingBox2d(
                           new GeoCoordinate2d(
                                   new Longitude(180.0), new Latitude(0.0)),
                           new GeoCoordinate2d(
                                   new Longitude(0.0), new Latitude(90.0)));

           assertTrue(new GeoCoordinate2d(new Longitude(0.0),
                   new Latitude(0.0)).equalTo(geoBox.lowerLeft()));
           assertTrue(new GeoCoordinate2d(new Longitude(180.0),
                   new Latitude(90.0)).equalTo(geoBox.upperRight()));
           assertTrue(geoBox.isValid());
       }
   }

   @Test
   public void ctorLinearBoxAndPointTest() {
       { // Horizontal
           GeoCoordinateBoundingBox2d geoBox =
                   new GeoCoordinateBoundingBox2d(
                           new GeoCoordinate2d(
                                   new Longitude(0.0), new Latitude(0.0)),
                           new GeoCoordinate2d(
                                   new Longitude(0.0), new Latitude(90.0)));

           assertTrue(new GeoCoordinate2d(new Longitude(0.0),
                   new Latitude(0.0)).equalTo(geoBox.lowerLeft()));
           assertTrue(new GeoCoordinate2d(new Longitude(0.0),
                   new Latitude(90.0)).equalTo(geoBox.upperRight()));
           assertTrue(geoBox.isValid());
       }

       { // Vertical
           GeoCoordinateBoundingBox2d geoBox =
                   new GeoCoordinateBoundingBox2d(
                           new GeoCoordinate2d(
                                   new Longitude(0.0), new Latitude(0.0)),
                           new GeoCoordinate2d(
                                   new Longitude(180.0), new Latitude(0.0)));

           assertTrue(new GeoCoordinate2d(new Longitude(0.0),
                   new Latitude(0.0)).equalTo(geoBox.lowerLeft()));
           assertTrue(new GeoCoordinate2d(new Longitude(180.0),
                   new Latitude(0.0)).equalTo(geoBox.upperRight()));
           assertTrue(geoBox.isValid());
       }

       { // Point
           GeoCoordinateBoundingBox2d geoBox =
                   new GeoCoordinateBoundingBox2d(
                           new GeoCoordinate2d(
                                   new Longitude(0.0), new Latitude(0.0)),
                           new GeoCoordinate2d(
                                   new Longitude(0.0), new Latitude(0.0)));
           assertTrue(geoBox.isValid());
       }
   }

   @Test
   public void containsOrNotTest() {
       {
           GeoCoordinateBoundingBox2d geoBox =
                   new GeoCoordinateBoundingBox2d(
                           new GeoCoordinate2d(
                                   new Longitude(90.0), new Latitude(45.0)),
                           new GeoCoordinate2d(
                                   new Longitude(-90.0), new Latitude(-45.0)));

           assertTrue(geoBox.isValid());

           assertTrue(geoBox.contains(new GeoCoordinate2d(
                   new Longitude(0.0), new Latitude(0.0))));

           assertTrue(geoBox.contains(new GeoCoordinate2d(
                   new Longitude(90.0), new Latitude(45.0))));
           assertTrue(geoBox.contains(new GeoCoordinate2d(
                   new Longitude(90.0), new Latitude(-45.0))));
           assertTrue(geoBox.contains(new GeoCoordinate2d(
                   new Longitude(-90.0), new Latitude(-45.0))));
           assertTrue(geoBox.contains(new GeoCoordinate2d(
                   new Longitude(-90.0), new Latitude(45.0))));

           assertFalse(geoBox.contains(new GeoCoordinate2d(
                   new Longitude(90.01), new Latitude(45.01))));
           assertFalse(geoBox.contains(new GeoCoordinate2d(
                   new Longitude(90.01), new Latitude(-45.01))));
           assertFalse(geoBox.contains(new GeoCoordinate2d(
                   new Longitude(-90.01), new Latitude(-45.01))));
           assertFalse(geoBox.contains(new GeoCoordinate2d(
                   new Longitude(-90.01), new Latitude(45.01))));
       }

       {
           GeoCoordinateBoundingBox2d geoBox =
                   new GeoCoordinateBoundingBox2d(
                           new GeoCoordinate2d(
                                   new Longitude(90.0), new Latitude(45.0)),
                           new GeoCoordinate2d(
                                   new Longitude(0.1), new Latitude(0.1)));

           assertTrue(new GeoCoordinate2d(new Longitude(0.1),
                   new Latitude(0.1)).equalTo(geoBox.lowerLeft()));
           assertTrue(new GeoCoordinate2d(new Longitude(90.0),
                   new Latitude(45.0)).equalTo(geoBox.upperRight()));

           assertTrue(geoBox.isValid());

           assertTrue(geoBox.contains(new GeoCoordinate2d(
                   new Longitude(90.0), new Latitude(45.0))));
           assertTrue(geoBox.contains(new GeoCoordinate2d(
                   new Longitude(90.0), new Latitude(0.1))));
           assertTrue(geoBox.contains(new GeoCoordinate2d(
                   new Longitude(0.1), new Latitude(0.1))));
           assertTrue(geoBox.contains(new GeoCoordinate2d(
                   new Longitude(0.1), new Latitude(45.0))));

           assertFalse(geoBox.contains(new GeoCoordinate2d(
                   new Longitude(90.01), new Latitude(45.01))));
           assertFalse(geoBox.contains(new GeoCoordinate2d(
                   new Longitude(90.01), new Latitude(0.0))));
           assertFalse(geoBox.contains(new GeoCoordinate2d(
                   new Longitude(0.0), new Latitude(0.0))));
           assertFalse(geoBox.contains(new GeoCoordinate2d(
                   new Longitude(0.0), new Latitude(45.01))));
       }
   }

   @Test
   public void growToContainTest() {
       {
           GeoCoordinateBoundingBox2d geoBox =
                   new GeoCoordinateBoundingBox2d(
                           new GeoCoordinate2d(
                                   new Longitude(-90.0), new Latitude(-45.0)),
                           new GeoCoordinate2d(
                                   new Longitude(90.0), new Latitude(45.0)));

           assertTrue(new GeoCoordinate2d(new Longitude(-90.0),
                   new Latitude(-45.0)).equalTo(geoBox.lowerLeft()));
           assertTrue(new GeoCoordinate2d(new Longitude(90.0),
                   new Latitude(45.0)).equalTo(geoBox.upperRight()));

           geoBox.growToContain(new GeoCoordinate2d(new Longitude(180.0),
                   new Latitude(90.0)));

           assertTrue(new GeoCoordinate2d(new Longitude(-90.0),
                   new Latitude(-45.0)).equalTo(geoBox.lowerLeft()));
           assertTrue(new GeoCoordinate2d(new Longitude(180.0),
                   new Latitude(90.0)).equalTo(geoBox.upperRight()));
       }

       {
           GeoCoordinateBoundingBox2d geoBox =
                   new GeoCoordinateBoundingBox2d(
                           new GeoCoordinate2d(
                                   new Longitude(-90.0), new Latitude(-45.0)),
                           new GeoCoordinate2d(
                                   new Longitude(90.0), new Latitude(45.0)));

           assertTrue(new GeoCoordinate2d(new Longitude(-90.0),
                   new Latitude(-45.0)).equalTo(geoBox.lowerLeft()));
           assertTrue(new GeoCoordinate2d(new Longitude(90.0),
                   new Latitude(45.0)).equalTo(geoBox.upperRight()));

           geoBox.growToContain(new GeoCoordinate2d(new Longitude(-180.0),
                   new Latitude(-90.0)));

           assertTrue(new GeoCoordinate2d(new Longitude(-180.0),
                   new Latitude(-90.0)).equalTo(geoBox.lowerLeft()));
           assertTrue(new GeoCoordinate2d(new Longitude(90.0),
                   new Latitude(45.0)).equalTo(geoBox.upperRight()));
       }

       {
           GeoCoordinateBoundingBox2d geoBox =
                   new GeoCoordinateBoundingBox2d(
                           new GeoCoordinate2d(
                                   new Longitude(-90.0), new Latitude(-45.0)),
                           new GeoCoordinate2d(
                                   new Longitude(90.0), new Latitude(45.0)));

           assertTrue(new GeoCoordinate2d(new Longitude(-90.0),
                   new Latitude(-45.0)).equalTo(geoBox.lowerLeft()));
           assertTrue(new GeoCoordinate2d(new Longitude(90.0),
                   new Latitude(45.0)).equalTo(geoBox.upperRight()));

           geoBox.growToContain(new GeoCoordinate2d(new Longitude(-180.0),
                   new Latitude(90.0)));

           assertTrue(new GeoCoordinate2d(new Longitude(-180.0),
                   new Latitude(-45.0)).equalTo(geoBox.lowerLeft()));
           assertTrue(new GeoCoordinate2d(new Longitude(90.0),
                   new Latitude(90.0)).equalTo(geoBox.upperRight()));
       }

       {
           GeoCoordinateBoundingBox2d geoBox =
                   new GeoCoordinateBoundingBox2d(
                           new GeoCoordinate2d(
                                   new Longitude(-90.0), new Latitude(-45.0)),
                           new GeoCoordinate2d(
                                   new Longitude(90.0), new Latitude(45.0)));

           assertTrue(new GeoCoordinate2d(new Longitude(-90.0),
                   new Latitude(-45.0)).equalTo(geoBox.lowerLeft()));
           assertTrue(new GeoCoordinate2d(new Longitude(90.0),
                   new Latitude(45.0)).equalTo(geoBox.upperRight()));

           geoBox.growToContain(new GeoCoordinate2d(new Longitude(180.0),
                   new Latitude(-90.0)));

           assertTrue(new GeoCoordinate2d(new Longitude(-90.0),
                   new Latitude(-90.0)).equalTo(geoBox.lowerLeft()));
           assertTrue(new GeoCoordinate2d(new Longitude(180.0),
                   new Latitude(45.0)).equalTo(geoBox.upperRight()));
       }

       {
           GeoCoordinateBoundingBox2d geoBox =
                   new GeoCoordinateBoundingBox2d(
                           new GeoCoordinate2d(
                                   new Longitude(-90.0), new Latitude(-45.0)),
                           new GeoCoordinate2d(
                                   new Longitude(90.0), new Latitude(45.0)));

           assertTrue(new GeoCoordinate2d(new Longitude(-90.0),
                   new Latitude(-45.0)).equalTo(geoBox.lowerLeft()));
           assertTrue(new GeoCoordinate2d(new Longitude(90.0),
                   new Latitude(45.0)).equalTo(geoBox.upperRight()));

           geoBox.growToContain(new GeoCoordinate2d(new Longitude(0.0),
                   new Latitude(0.0)));

           assertTrue(new GeoCoordinate2d(new Longitude(-90.0),
                   new Latitude(-45.0)).equalTo(geoBox.lowerLeft()));
           assertTrue(new GeoCoordinate2d(new Longitude(90.0),
                   new Latitude(45.0)).equalTo(geoBox.upperRight()));
       }
   }

}

import static org.junit.Assert.*;

import com.quad_key.geo_coordinate_bounding_box2d;
import com.quad_key.geo_coordinate2d;
import com.quad_key.latitude;
import com.quad_key.longitude;

import org.junit.BeforeClass;
import org.junit.Test;


public class geo_coordinate_bounding_box2d_test {

  @BeforeClass
  public static void setUpBeforeClass() throws Exception {
    System.loadLibrary("quad_key_jni");
  }

  @Test
  public void default_ctor_test() {
    geo_coordinate_bounding_box2d empty =
      new geo_coordinate_bounding_box2d();
    assertFalse(empty.is_valid());
    assertFalse(empty.contains(new geo_coordinate2d(new longitude(0.0),
      new latitude(0.0))));
  }

  @Test
  public void ctor_standard_construction_test() {
    { // Lower Left / Upper Right Construction
      geo_coordinate_bounding_box2d geoBox =
        new geo_coordinate_bounding_box2d(
          new geo_coordinate2d(new longitude(0.0), new latitude(0.0)),
          new geo_coordinate2d(new longitude(180.0), new latitude(90.0)));

      assertTrue(new geo_coordinate2d(new longitude(0.0),
        new latitude(0.0)).equal_to(geoBox.lower_left()));
      assertTrue(new geo_coordinate2d(new longitude(180.0),
        new latitude(90.0)).equal_to(geoBox.upper_right()));
      assertTrue(geoBox.is_valid());
    }

    { // Upper Left / Lower Right Construction
      geo_coordinate_bounding_box2d geoBox =
        new geo_coordinate_bounding_box2d(
          new geo_coordinate2d(new longitude(0.0), new latitude(90.0)),
          new geo_coordinate2d(new longitude(180.0), new latitude(0.0)));

      assertTrue(new geo_coordinate2d(
        new longitude(0.0), new latitude(0.0)).equal_to(
        geoBox.lower_left()));
      assertTrue(new geo_coordinate2d(
        new longitude(180.0), new latitude(90.0)).equal_to(
        geoBox.upper_right()));
      assertTrue(geoBox.is_valid());
    }

    { // Upper Right / Lower Left Construction
      geo_coordinate_bounding_box2d geoBox =
        new geo_coordinate_bounding_box2d(
          new geo_coordinate2d(new longitude(180.0), new latitude(0.0)),
          new geo_coordinate2d(new longitude(0.0), new latitude(90.0)));

      assertTrue(new geo_coordinate2d(new longitude(0.0),
        new latitude(0.0)).equal_to(geoBox.lower_left()));
      assertTrue(new geo_coordinate2d(new longitude(180.0),
        new latitude(90.0)).equal_to(geoBox.upper_right()));
      assertTrue(geoBox.is_valid());
    }

    { // Lower Right / Upper Left Construction
      geo_coordinate_bounding_box2d geoBox =
        new geo_coordinate_bounding_box2d(
          new geo_coordinate2d(new longitude(180.0), new latitude(0.0)),
          new geo_coordinate2d(new longitude(0.0), new latitude(90.0)));

      assertTrue(new geo_coordinate2d(new longitude(0.0),
        new latitude(0.0)).equal_to(geoBox.lower_left()));
      assertTrue(new geo_coordinate2d(new longitude(180.0),
        new latitude(90.0)).equal_to(geoBox.upper_right()));
      assertTrue(geoBox.is_valid());
    }
  }

  @Test
  public void ctor_linear_box_and_point_test() {
    { // Horizontal
      geo_coordinate_bounding_box2d geoBox =
        new geo_coordinate_bounding_box2d(
          new geo_coordinate2d(new longitude(0.0), new latitude(0.0)),
          new geo_coordinate2d(new longitude(0.0), new latitude(90.0)));

      assertTrue(new geo_coordinate2d(new longitude(0.0),
        new latitude(0.0)).equal_to(geoBox.lower_left()));
      assertTrue(new geo_coordinate2d(new longitude(0.0),
        new latitude(90.0)).equal_to(geoBox.upper_right()));
      assertTrue(geoBox.is_valid());
    }

    { // Vertical
      geo_coordinate_bounding_box2d geoBox =
        new geo_coordinate_bounding_box2d(
          new geo_coordinate2d(new longitude(0.0), new latitude(0.0)),
          new geo_coordinate2d(new longitude(180.0), new latitude(0.0)));

      assertTrue(new geo_coordinate2d(new longitude(0.0),
        new latitude(0.0)).equal_to(geoBox.lower_left()));
      assertTrue(new geo_coordinate2d(new longitude(180.0),
        new latitude(0.0)).equal_to(geoBox.upper_right()));
      assertTrue(geoBox.is_valid());
    }

    { // Point
      geo_coordinate_bounding_box2d geoBox =
        new geo_coordinate_bounding_box2d(
          new geo_coordinate2d(new longitude(0.0), new latitude(0.0)),
          new geo_coordinate2d(new longitude(0.0), new latitude(0.0)));
      assertTrue(geoBox.is_valid());
    }
  }

  @Test
  public void containsOrNotTest() {
    {
      geo_coordinate_bounding_box2d geoBox =
        new geo_coordinate_bounding_box2d(
          new geo_coordinate2d(new longitude(90.0), new latitude(45.0)),
          new geo_coordinate2d(new longitude(-90.0), new latitude(-45.0)));

      assertTrue(geoBox.is_valid());

      assertTrue(geoBox.contains(new geo_coordinate2d(
              new longitude(0.0), new latitude(0.0))));

      assertTrue(geoBox.contains(new geo_coordinate2d(
        new longitude(90.0), new latitude(45.0))));
      assertTrue(geoBox.contains(new geo_coordinate2d(
        new longitude(90.0), new latitude(-45.0))));
      assertTrue(geoBox.contains(new geo_coordinate2d(
        new longitude(-90.0), new latitude(-45.0))));
      assertTrue(geoBox.contains(new geo_coordinate2d(
        new longitude(-90.0), new latitude(45.0))));

      assertFalse(geoBox.contains(new geo_coordinate2d(
        new longitude(90.01), new latitude(45.01))));
      assertFalse(geoBox.contains(new geo_coordinate2d(
        new longitude(90.01), new latitude(-45.01))));
      assertFalse(geoBox.contains(new geo_coordinate2d(
        new longitude(-90.01), new latitude(-45.01))));
      assertFalse(geoBox.contains(new geo_coordinate2d(
        new longitude(-90.01), new latitude(45.01))));
    }

    {
      geo_coordinate_bounding_box2d geoBox =
        new geo_coordinate_bounding_box2d(
          new geo_coordinate2d(new longitude(90.0), new latitude(45.0)),
          new geo_coordinate2d(new longitude(0.1), new latitude(0.1)));

      assertTrue(new geo_coordinate2d(new longitude(0.1),
        new latitude(0.1)).equal_to(geoBox.lower_left()));
      assertTrue(new geo_coordinate2d(new longitude(90.0),
        new latitude(45.0)).equal_to(geoBox.upper_right()));

      assertTrue(geoBox.is_valid());

      assertTrue(geoBox.contains(new geo_coordinate2d(
        new longitude(90.0), new latitude(45.0))));
      assertTrue(geoBox.contains(new geo_coordinate2d(
        new longitude(90.0), new latitude(0.1))));
      assertTrue(geoBox.contains(new geo_coordinate2d(
        new longitude(0.1), new latitude(0.1))));
      assertTrue(geoBox.contains(new geo_coordinate2d(
        new longitude(0.1), new latitude(45.0))));

      assertFalse(geoBox.contains(new geo_coordinate2d(
        new longitude(90.01), new latitude(45.01))));
      assertFalse(geoBox.contains(new geo_coordinate2d(
        new longitude(90.01), new latitude(0.0))));
      assertFalse(geoBox.contains(new geo_coordinate2d(
        new longitude(0.0), new latitude(0.0))));
      assertFalse(geoBox.contains(new geo_coordinate2d(
        new longitude(0.0), new latitude(45.01))));
    }
  }

  @Test
  public void grow_to_contain_test() {
    {
      geo_coordinate_bounding_box2d geoBox =
        new geo_coordinate_bounding_box2d(
          new geo_coordinate2d(new longitude(-90.0), new latitude(-45.0)),
          new geo_coordinate2d(new longitude(90.0), new latitude(45.0)));

      assertTrue(new geo_coordinate2d(new longitude(-90.0),
        new latitude(-45.0)).equal_to(geoBox.lower_left()));
      assertTrue(new geo_coordinate2d(new longitude(90.0),
        new latitude(45.0)).equal_to(geoBox.upper_right()));

      geoBox.grow_to_contain(new geo_coordinate2d(new longitude(180.0),
        new latitude(90.0)));

      assertTrue(new geo_coordinate2d(new longitude(-90.0),
        new latitude(-45.0)).equal_to(geoBox.lower_left()));
      assertTrue(new geo_coordinate2d(new longitude(180.0),
        new latitude(90.0)).equal_to(geoBox.upper_right()));
    }

    {
      geo_coordinate_bounding_box2d geoBox =
        new geo_coordinate_bounding_box2d(
          new geo_coordinate2d(new longitude(-90.0), new latitude(-45.0)),
          new geo_coordinate2d(new longitude(90.0), new latitude(45.0)));

      assertTrue(new geo_coordinate2d(new longitude(-90.0),
        new latitude(-45.0)).equal_to(geoBox.lower_left()));
      assertTrue(new geo_coordinate2d(new longitude(90.0),
        new latitude(45.0)).equal_to(geoBox.upper_right()));

      geoBox.grow_to_contain(new geo_coordinate2d(new longitude(-180.0),
        new latitude(-90.0)));

      assertTrue(new geo_coordinate2d(new longitude(-180.0),
        new latitude(-90.0)).equal_to(geoBox.lower_left()));
      assertTrue(new geo_coordinate2d(new longitude(90.0),
        new latitude(45.0)).equal_to(geoBox.upper_right()));
    }

    {
      geo_coordinate_bounding_box2d geoBox =
        new geo_coordinate_bounding_box2d(
          new geo_coordinate2d(new longitude(-90.0), new latitude(-45.0)),
          new geo_coordinate2d(new longitude(90.0), new latitude(45.0)));

      assertTrue(new geo_coordinate2d(new longitude(-90.0),
        new latitude(-45.0)).equal_to(geoBox.lower_left()));
      assertTrue(new geo_coordinate2d(new longitude(90.0),
        new latitude(45.0)).equal_to(geoBox.upper_right()));

      geoBox.grow_to_contain(new geo_coordinate2d(new longitude(-180.0),
        new latitude(90.0)));

      assertTrue(new geo_coordinate2d(new longitude(-180.0),
        new latitude(-45.0)).equal_to(geoBox.lower_left()));
      assertTrue(new geo_coordinate2d(new longitude(90.0),
        new latitude(90.0)).equal_to(geoBox.upper_right()));
    }

    {
      geo_coordinate_bounding_box2d geoBox =
        new geo_coordinate_bounding_box2d(
          new geo_coordinate2d(new longitude(-90.0), new latitude(-45.0)),
          new geo_coordinate2d(new longitude(90.0), new latitude(45.0)));

      assertTrue(new geo_coordinate2d(new longitude(-90.0),
        new latitude(-45.0)).equal_to(geoBox.lower_left()));
      assertTrue(new geo_coordinate2d(new longitude(90.0),
        new latitude(45.0)).equal_to(geoBox.upper_right()));

      geoBox.grow_to_contain(new geo_coordinate2d(new longitude(180.0),
        new latitude(-90.0)));

      assertTrue(new geo_coordinate2d(new longitude(-90.0),
        new latitude(-90.0)).equal_to(geoBox.lower_left()));
      assertTrue(new geo_coordinate2d(new longitude(180.0),
        new latitude(45.0)).equal_to(geoBox.upper_right()));
    }

    {
      geo_coordinate_bounding_box2d geoBox =
        new geo_coordinate_bounding_box2d(
          new geo_coordinate2d(new longitude(-90.0), new latitude(-45.0)),
          new geo_coordinate2d(new longitude(90.0), new latitude(45.0)));

      assertTrue(new geo_coordinate2d(new longitude(-90.0),
        new latitude(-45.0)).equal_to(geoBox.lower_left()));
      assertTrue(new geo_coordinate2d(new longitude(90.0),
        new latitude(45.0)).equal_to(geoBox.upper_right()));

      geoBox.grow_to_contain(new geo_coordinate2d(new longitude(0.0),
        new latitude(0.0)));

      assertTrue(new geo_coordinate2d(new longitude(-90.0),
        new latitude(-45.0)).equal_to(geoBox.lower_left()));
      assertTrue(new geo_coordinate2d(new longitude(90.0),
        new latitude(45.0)).equal_to(geoBox.upper_right()));
    }
  }
}

package com.quad_keys;

import static org.junit.Assert.*;

import org.junit.BeforeClass;
import org.junit.Test;


public class GeoCoordinateBoundingBox2dTest {

  @BeforeClass
  public static void setUpBeforeClass() throws Exception {
    System.loadLibrary("quad_keys_java");
  }

  @Test
  public void default_ctor_test() {
    GeoCoordinateBoundingBox2d empty =
      new GeoCoordinateBoundingBox2d();
    assertFalse(empty.is_valid());
    assertFalse(empty.contains(new GeoCoordinate2d(new Longitude(0.0),
      new Latitude(0.0))));
  }

  @Test
  public void ctor_standard_construction_test() {
    { // Lower Left / Upper Right Construction
      GeoCoordinateBoundingBox2d geoBox =
        new GeoCoordinateBoundingBox2d(
          new GeoCoordinate2d(new Longitude(0.0), new Latitude(0.0)),
          new GeoCoordinate2d(new Longitude(180.0), new Latitude(90.0)));

      assertTrue(new GeoCoordinate2d(new Longitude(0.0),
        new Latitude(0.0)).equalTo(geoBox.lower_left()));
      assertTrue(new GeoCoordinate2d(new Longitude(180.0),
        new Latitude(90.0)).equalTo(geoBox.upper_right()));
      assertTrue(geoBox.is_valid());
    }

    { // Upper Left / Lower Right Construction
      GeoCoordinateBoundingBox2d geoBox =
        new GeoCoordinateBoundingBox2d(
          new GeoCoordinate2d(new Longitude(0.0), new Latitude(90.0)),
          new GeoCoordinate2d(new Longitude(180.0), new Latitude(0.0)));

      assertTrue(new GeoCoordinate2d(
        new Longitude(0.0), new Latitude(0.0)).equalTo(
        geoBox.lower_left()));
      assertTrue(new GeoCoordinate2d(
        new Longitude(180.0), new Latitude(90.0)).equalTo(
        geoBox.upper_right()));
      assertTrue(geoBox.is_valid());
    }

    { // Upper Right / Lower Left Construction
      GeoCoordinateBoundingBox2d geoBox =
        new GeoCoordinateBoundingBox2d(
          new GeoCoordinate2d(new Longitude(180.0), new Latitude(0.0)),
          new GeoCoordinate2d(new Longitude(0.0), new Latitude(90.0)));

      assertTrue(new GeoCoordinate2d(new Longitude(0.0),
        new Latitude(0.0)).equalTo(geoBox.lower_left()));
      assertTrue(new GeoCoordinate2d(new Longitude(180.0),
        new Latitude(90.0)).equalTo(geoBox.upper_right()));
      assertTrue(geoBox.is_valid());
    }

    { // Lower Right / Upper Left Construction
      GeoCoordinateBoundingBox2d geoBox =
        new GeoCoordinateBoundingBox2d(
          new GeoCoordinate2d(new Longitude(180.0), new Latitude(0.0)),
          new GeoCoordinate2d(new Longitude(0.0), new Latitude(90.0)));

      assertTrue(new GeoCoordinate2d(new Longitude(0.0),
        new Latitude(0.0)).equalTo(geoBox.lower_left()));
      assertTrue(new GeoCoordinate2d(new Longitude(180.0),
        new Latitude(90.0)).equalTo(geoBox.upper_right()));
      assertTrue(geoBox.is_valid());
    }
  }

  @Test
  public void ctor_linear_box_and_point_test() {
    { // Horizontal
      GeoCoordinateBoundingBox2d geoBox =
        new GeoCoordinateBoundingBox2d(
          new GeoCoordinate2d(new Longitude(0.0), new Latitude(0.0)),
          new GeoCoordinate2d(new Longitude(0.0), new Latitude(90.0)));

      assertTrue(new GeoCoordinate2d(new Longitude(0.0),
        new Latitude(0.0)).equalTo(geoBox.lower_left()));
      assertTrue(new GeoCoordinate2d(new Longitude(0.0),
        new Latitude(90.0)).equalTo(geoBox.upper_right()));
      assertTrue(geoBox.is_valid());
    }

    { // Vertical
      GeoCoordinateBoundingBox2d geoBox =
        new GeoCoordinateBoundingBox2d(
          new GeoCoordinate2d(new Longitude(0.0), new Latitude(0.0)),
          new GeoCoordinate2d(new Longitude(180.0), new Latitude(0.0)));

      assertTrue(new GeoCoordinate2d(new Longitude(0.0),
        new Latitude(0.0)).equalTo(geoBox.lower_left()));
      assertTrue(new GeoCoordinate2d(new Longitude(180.0),
        new Latitude(0.0)).equalTo(geoBox.upper_right()));
      assertTrue(geoBox.is_valid());
    }

    { // Point
      GeoCoordinateBoundingBox2d geoBox =
        new GeoCoordinateBoundingBox2d(
          new GeoCoordinate2d(new Longitude(0.0), new Latitude(0.0)),
          new GeoCoordinate2d(new Longitude(0.0), new Latitude(0.0)));
      assertTrue(geoBox.is_valid());
    }
  }

  @Test
  public void containsOrNotTest() {
    {
      GeoCoordinateBoundingBox2d geoBox =
        new GeoCoordinateBoundingBox2d(
          new GeoCoordinate2d(new Longitude(90.0), new Latitude(45.0)),
          new GeoCoordinate2d(new Longitude(-90.0), new Latitude(-45.0)));

      assertTrue(geoBox.is_valid());

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
          new GeoCoordinate2d(new Longitude(90.0), new Latitude(45.0)),
          new GeoCoordinate2d(new Longitude(0.1), new Latitude(0.1)));

      assertTrue(new GeoCoordinate2d(new Longitude(0.1),
        new Latitude(0.1)).equalTo(geoBox.lower_left()));
      assertTrue(new GeoCoordinate2d(new Longitude(90.0),
        new Latitude(45.0)).equalTo(geoBox.upper_right()));

      assertTrue(geoBox.is_valid());

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
  public void grow_to_contain_test() {
    {
      GeoCoordinateBoundingBox2d geoBox =
        new GeoCoordinateBoundingBox2d(
          new GeoCoordinate2d(new Longitude(-90.0), new Latitude(-45.0)),
          new GeoCoordinate2d(new Longitude(90.0), new Latitude(45.0)));

      assertTrue(new GeoCoordinate2d(new Longitude(-90.0),
        new Latitude(-45.0)).equalTo(geoBox.lower_left()));
      assertTrue(new GeoCoordinate2d(new Longitude(90.0),
        new Latitude(45.0)).equalTo(geoBox.upper_right()));

      geoBox.grow_to_contain(new GeoCoordinate2d(new Longitude(180.0),
        new Latitude(90.0)));

      assertTrue(new GeoCoordinate2d(new Longitude(-90.0),
        new Latitude(-45.0)).equalTo(geoBox.lower_left()));
      assertTrue(new GeoCoordinate2d(new Longitude(180.0),
        new Latitude(90.0)).equalTo(geoBox.upper_right()));
    }

    {
      GeoCoordinateBoundingBox2d geoBox =
        new GeoCoordinateBoundingBox2d(
          new GeoCoordinate2d(new Longitude(-90.0), new Latitude(-45.0)),
          new GeoCoordinate2d(new Longitude(90.0), new Latitude(45.0)));

      assertTrue(new GeoCoordinate2d(new Longitude(-90.0),
        new Latitude(-45.0)).equalTo(geoBox.lower_left()));
      assertTrue(new GeoCoordinate2d(new Longitude(90.0),
        new Latitude(45.0)).equalTo(geoBox.upper_right()));

      geoBox.grow_to_contain(new GeoCoordinate2d(new Longitude(-180.0),
        new Latitude(-90.0)));

      assertTrue(new GeoCoordinate2d(new Longitude(-180.0),
        new Latitude(-90.0)).equalTo(geoBox.lower_left()));
      assertTrue(new GeoCoordinate2d(new Longitude(90.0),
        new Latitude(45.0)).equalTo(geoBox.upper_right()));
    }

    {
      GeoCoordinateBoundingBox2d geoBox =
        new GeoCoordinateBoundingBox2d(
          new GeoCoordinate2d(new Longitude(-90.0), new Latitude(-45.0)),
          new GeoCoordinate2d(new Longitude(90.0), new Latitude(45.0)));

      assertTrue(new GeoCoordinate2d(new Longitude(-90.0),
        new Latitude(-45.0)).equalTo(geoBox.lower_left()));
      assertTrue(new GeoCoordinate2d(new Longitude(90.0),
        new Latitude(45.0)).equalTo(geoBox.upper_right()));

      geoBox.grow_to_contain(new GeoCoordinate2d(new Longitude(-180.0),
        new Latitude(90.0)));

      assertTrue(new GeoCoordinate2d(new Longitude(-180.0),
        new Latitude(-45.0)).equalTo(geoBox.lower_left()));
      assertTrue(new GeoCoordinate2d(new Longitude(90.0),
        new Latitude(90.0)).equalTo(geoBox.upper_right()));
    }

    {
      GeoCoordinateBoundingBox2d geoBox =
        new GeoCoordinateBoundingBox2d(
          new GeoCoordinate2d(new Longitude(-90.0), new Latitude(-45.0)),
          new GeoCoordinate2d(new Longitude(90.0), new Latitude(45.0)));

      assertTrue(new GeoCoordinate2d(new Longitude(-90.0),
        new Latitude(-45.0)).equalTo(geoBox.lower_left()));
      assertTrue(new GeoCoordinate2d(new Longitude(90.0),
        new Latitude(45.0)).equalTo(geoBox.upper_right()));

      geoBox.grow_to_contain(new GeoCoordinate2d(new Longitude(180.0),
        new Latitude(-90.0)));

      assertTrue(new GeoCoordinate2d(new Longitude(-90.0),
        new Latitude(-90.0)).equalTo(geoBox.lower_left()));
      assertTrue(new GeoCoordinate2d(new Longitude(180.0),
        new Latitude(45.0)).equalTo(geoBox.upper_right()));
    }

    {
      GeoCoordinateBoundingBox2d geoBox =
        new GeoCoordinateBoundingBox2d(
          new GeoCoordinate2d(new Longitude(-90.0), new Latitude(-45.0)),
          new GeoCoordinate2d(new Longitude(90.0), new Latitude(45.0)));

      assertTrue(new GeoCoordinate2d(new Longitude(-90.0),
        new Latitude(-45.0)).equalTo(geoBox.lower_left()));
      assertTrue(new GeoCoordinate2d(new Longitude(90.0),
        new Latitude(45.0)).equalTo(geoBox.upper_right()));

      geoBox.grow_to_contain(new GeoCoordinate2d(new Longitude(0.0),
        new Latitude(0.0)));

      assertTrue(new GeoCoordinate2d(new Longitude(-90.0),
        new Latitude(-45.0)).equalTo(geoBox.lower_left()));
      assertTrue(new GeoCoordinate2d(new Longitude(90.0),
        new Latitude(45.0)).equalTo(geoBox.upper_right()));
    }
  }
}

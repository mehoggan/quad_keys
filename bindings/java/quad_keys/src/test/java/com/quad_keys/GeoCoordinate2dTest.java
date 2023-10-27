package com.quad_keys;

import static org.junit.Assert.*;

import org.junit.BeforeClass;
import org.junit.Test;

public class GeoCoordinate2dTest {

  @BeforeClass
  public static void setUpBeforeClass() throws Exception {
    System.loadLibrary("quad_keys_java");
  }

  @Test
  public void default_ctor_test() {
    GeoCoordinate2d empty = new GeoCoordinate2d();
    assertTrue(new Longitude(0.0).equalTo(empty.get_longitude()));
    assertTrue(new Latitude(0.0).equalTo(empty.get_latitude()));
  }

  @Test
  public void ctor_test() {
    {
      GeoCoordinate2d coord = new GeoCoordinate2d(new Longitude(0.0),
        new Latitude(0.0));
      assertTrue(new Longitude(0.0).equalTo(coord.get_longitude()));
      assertTrue(new Latitude(0.0).equalTo(coord.get_latitude()));
    }

    {
      GeoCoordinate2d coord = new GeoCoordinate2d(
        new Longitude(-180.001), new Latitude(-95.0));
      assertTrue(new Longitude(-180.0).equalTo(
        coord.get_longitude()));
      assertTrue(new Latitude(-90.0).equalTo(coord.get_latitude()));
    }

    {
      GeoCoordinate2d coord = new GeoCoordinate2d(
        new Longitude(-180.001), new Latitude(95.0));
      assertTrue(new Longitude(-180.0).equalTo(
        coord.get_longitude()));
      assertTrue(new Latitude(90.0).equalTo(coord.get_latitude()));
    }

    {
      GeoCoordinate2d coord = new GeoCoordinate2d(
        new Longitude(180.001), new Latitude(95.0));
      assertTrue(new Longitude(180.0).equalTo(coord.get_longitude()));
      assertTrue(new Latitude(90.0).equalTo(coord.get_latitude()));
    }

    {
      GeoCoordinate2d coord = new GeoCoordinate2d(
        new Longitude(180.001), new Latitude(-95.0));
      assertTrue(new Longitude(180.0).equalTo(coord.get_longitude()));
      assertTrue(new Latitude(-90.0).equalTo(coord.get_latitude()));
    }
  }

  @Test
  public void near_test() {
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
      GeoCoordinate2d coord = new GeoCoordinate2d(new Longitude(0.001),
        new Latitude(0.001));
      assertTrue(coord.near(new GeoCoordinate2d(new Longitude(0.0009),
        new Latitude(0.0009)), 1e-3));
    }

    {
      GeoCoordinate2d coord = new GeoCoordinate2d(new Longitude(0.001),
        new Latitude(0.001));
      assertFalse(coord.near(new GeoCoordinate2d(
        new Longitude(0.001), new Latitude(0.0009)), 1e-4));
    }

    {
      GeoCoordinate2d  coord = new GeoCoordinate2d(new Longitude(0.001),
        new Latitude(0.001));
      assertFalse(coord.near(new GeoCoordinate2d(new Longitude(0.0009),
        new Latitude(0.001)), 1e-4));
    }
  }

  @Test
  public void operator_lessThan_test() {
    GeoCoordinate2d sw = new GeoCoordinate2d(new Longitude(-0.1),
      new Latitude(-0.1));
    GeoCoordinate2d ne = new GeoCoordinate2d(new Longitude(+0.1),
      new Latitude(+0.1));

    assertTrue(sw.get_longitude().lessThan(ne.get_longitude()));
    assertTrue(sw.get_latitude().lessThan(ne.get_latitude()));
  }

  @Test
  public void operatorlessThanOrEqual_test() {
    {
      GeoCoordinate2d sw = new GeoCoordinate2d(new Longitude(-0.1),
        new Latitude(-0.1));
      GeoCoordinate2d ne = new GeoCoordinate2d(new Longitude(+0.1),
        new Latitude(+0.1));

      assertTrue(sw.get_longitude().lessThanOrEqual(ne.get_longitude()));
      assertTrue(sw.get_latitude().lessThanOrEqual(ne.get_latitude()));
    }

    {
      GeoCoordinate2d sw = new GeoCoordinate2d(new Longitude(-0.1),
        new Latitude(-0.1));
      GeoCoordinate2d ne = new GeoCoordinate2d(new Longitude(-0.1),
        new Latitude(-0.1));

      assertTrue(sw.get_longitude().lessThanOrEqual(ne.get_longitude()));
      assertTrue(sw.get_latitude().lessThanOrEqual(ne.get_latitude()));
    }
  }

  @Test
  public void operator_equal_test() {
    GeoCoordinate2d sw = new GeoCoordinate2d(new Longitude(-0.1),
      new Latitude(-0.1));
    GeoCoordinate2d ne = new GeoCoordinate2d(new Longitude(-0.1),
      new Latitude(-0.1));

    assertTrue(sw.get_longitude().equalTo(ne.get_longitude()));
    assertTrue(sw.get_latitude().equalTo(ne.get_latitude()));
  }
}

import static org.junit.Assert.*;

import com.quad_key.geo_coordinate2d;
import com.quad_key.latitude;
import com.quad_key.longitude;

import org.junit.BeforeClass;
import org.junit.Test;

public class geo_coordinate2d_test {

  @BeforeClass
  public static void setUpBeforeClass() throws Exception {
    System.loadLibrary("quad_key_jni");
  }

  @Test
  public void default_ctor_test() {
    geo_coordinate2d empty = new geo_coordinate2d();
    assertTrue(new longitude(0.0).equal_to(empty.get_longitude()));
    assertTrue(new latitude(0.0).equal_to(empty.get_latitude()));
  }

  @Test
  public void ctor_test() {
    {
      geo_coordinate2d coord = new geo_coordinate2d(new longitude(0.0),
        new latitude(0.0));
      assertTrue(new longitude(0.0).equal_to(coord.get_longitude()));
      assertTrue(new latitude(0.0).equal_to(coord.get_latitude()));
    }

    {
      geo_coordinate2d coord = new geo_coordinate2d(
        new longitude(-180.001), new latitude(-95.0));
      assertTrue(new longitude(-180.0).equal_to(
        coord.get_longitude()));
      assertTrue(new latitude(-90.0).equal_to(coord.get_latitude()));
    }

    {
      geo_coordinate2d coord = new geo_coordinate2d(
        new longitude(-180.001), new latitude(95.0));
      assertTrue(new longitude(-180.0).equal_to(
        coord.get_longitude()));
      assertTrue(new latitude(90.0).equal_to(coord.get_latitude()));
    }

    {
      geo_coordinate2d coord = new geo_coordinate2d(
        new longitude(180.001), new latitude(95.0));
      assertTrue(new longitude(180.0).equal_to(coord.get_longitude()));
      assertTrue(new latitude(90.0).equal_to(coord.get_latitude()));
    }

    {
      geo_coordinate2d coord = new geo_coordinate2d(
        new longitude(180.001), new latitude(-95.0));
      assertTrue(new longitude(180.0).equal_to(coord.get_longitude()));
      assertTrue(new latitude(-90.0).equal_to(coord.get_latitude()));
    }
  }

  @Test
  public void near_test() {
    {
      longitude lon = new longitude(0.001);
      assertTrue(lon.near(new longitude(0.0009), 1e-3));
    }

    {
      longitude lon = new longitude(0.001);
      assertFalse(lon.near(new longitude(0.0009), 1e-4));
    }

    {
      latitude lat = new latitude(0.001);
      assertTrue(lat.near(new latitude(0.0009), 1e-3));
    }

    {
      latitude lat = new latitude(0.001);
      assertFalse(lat.near(new latitude(0.0009), 1e-4));
    }

    {
      geo_coordinate2d coord = new geo_coordinate2d(new longitude(0.001),
        new latitude(0.001));
      assertTrue(coord.near(new geo_coordinate2d(new longitude(0.0009),
        new latitude(0.0009)), 1e-3));
    }

    {
      geo_coordinate2d coord = new geo_coordinate2d(new longitude(0.001),
        new latitude(0.001));
      assertFalse(coord.near(new geo_coordinate2d(
        new longitude(0.001), new latitude(0.0009)), 1e-4));
    }

    {
      geo_coordinate2d  coord = new geo_coordinate2d(new longitude(0.001),
        new latitude(0.001));
      assertFalse(coord.near(new geo_coordinate2d(new longitude(0.0009),
        new latitude(0.001)), 1e-4));
    }
  }

  @Test
  public void operator_less_than_test() {
    geo_coordinate2d sw = new geo_coordinate2d(new longitude(-0.1),
      new latitude(-0.1));
    geo_coordinate2d ne = new geo_coordinate2d(new longitude(+0.1),
      new latitude(+0.1));

    assertTrue(sw.get_longitude().less_than(ne.get_longitude()));
    assertTrue(sw.get_latitude().less_than(ne.get_latitude()));
  }

  @Test
  public void operatorless_than_or_equal_test() {
    {
      geo_coordinate2d sw = new geo_coordinate2d(new longitude(-0.1),
        new latitude(-0.1));
      geo_coordinate2d ne = new geo_coordinate2d(new longitude(+0.1),
        new latitude(+0.1));

      assertTrue(sw.get_longitude().less_than_or_equal(ne.get_longitude()));
      assertTrue(sw.get_latitude().less_than_or_equal(ne.get_latitude()));
    }

    {
      geo_coordinate2d sw = new geo_coordinate2d(new longitude(-0.1),
        new latitude(-0.1));
      geo_coordinate2d ne = new geo_coordinate2d(new longitude(-0.1),
        new latitude(-0.1));

      assertTrue(sw.get_longitude().less_than_or_equal(ne.get_longitude()));
      assertTrue(sw.get_latitude().less_than_or_equal(ne.get_latitude()));
    }
  }

  @Test
  public void operator_equal_test() {
    geo_coordinate2d sw = new geo_coordinate2d(new longitude(-0.1),
      new latitude(-0.1));
    geo_coordinate2d ne = new geo_coordinate2d(new longitude(-0.1),
      new latitude(-0.1));

    assertTrue(sw.get_longitude().equal_to(ne.get_longitude()));
    assertTrue(sw.get_latitude().equal_to(ne.get_latitude()));
  }
}

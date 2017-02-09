/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.12
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package com.quad_key;

public class quad_key {
  private transient long swigCPtr;
  protected transient boolean swigCMemOwn;

  protected quad_key(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(quad_key obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        quad_key_javaJNI.delete_quad_key(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public quad_key() {
    this(quad_key_javaJNI.new_quad_key__SWIG_0(), true);
  }

  public quad_key(type t) {
    this(quad_key_javaJNI.new_quad_key__SWIG_1(t.swigValue()), true);
  }

  public quad_key(type t, long row, long col, short depth) {
    this(quad_key_javaJNI.new_quad_key__SWIG_2(t.swigValue(), row, col, depth), true);
  }

  public quad_key(quad_key other) {
    this(quad_key_javaJNI.new_quad_key__SWIG_3(quad_key.getCPtr(other), other), true);
  }

  public quad_key assignquad_key(quad_key other) {
    return new quad_key(quad_key_javaJNI.quad_key_assignquad_key(swigCPtr, this, quad_key.getCPtr(other), other), false);
  }

  public type get_type() {
    return type.swigToEnum(quad_key_javaJNI.quad_key_get_type(swigCPtr, this));
  }

  public String type_as_string() {
    return quad_key_javaJNI.quad_key_type_as_string(swigCPtr, this);
  }

  public long get_row() {
    return quad_key_javaJNI.quad_key_get_row(swigCPtr, this);
  }

  public long get_col() {
    return quad_key_javaJNI.quad_key_get_col(swigCPtr, this);
  }

  public short get_depth() {
    return quad_key_javaJNI.quad_key_get_depth(swigCPtr, this);
  }

  public boolean is_root_key() {
    return quad_key_javaJNI.quad_key_is_root_key(swigCPtr, this);
  }

  public quad_key get_parent() {
    return new quad_key(quad_key_javaJNI.quad_key_get_parent(swigCPtr, this), true);
  }

  public boolean is_my_ancestor(quad_key quad_key) {
    return quad_key_javaJNI.quad_key_is_my_ancestor(swigCPtr, this, quad_key.getCPtr(quad_key), quad_key);
  }

  public quad_key get_ancestor(short depth_delta) {
    return new quad_key(quad_key_javaJNI.quad_key_get_ancestor(swigCPtr, this, depth_delta), true);
  }

  public quad_key get_child(quad_key.quadrant quad_id) {
    return new quad_key(quad_key_javaJNI.quad_key_get_child(swigCPtr, this, quad_id.swigValue()), true);
  }

  public quad_key_vector get_children() {
    return new quad_key_vector(quad_key_javaJNI.quad_key_get_children(swigCPtr, this), true);
  }

  public quad_key_vector get_descendants(short depth_delta) {
    return new quad_key_vector(quad_key_javaJNI.quad_key_get_descendants(swigCPtr, this, depth_delta), true);
  }

  public quad_key_vector get_siblings() {
    return new quad_key_vector(quad_key_javaJNI.quad_key_get_siblings(swigCPtr, this), true);
  }

  public quad_key_vector get_neighbors() {
    return new quad_key_vector(quad_key_javaJNI.quad_key_get_neighbors(swigCPtr, this), true);
  }

  public void get_geo_coordinate_bounds2d(geo_coordinate_bounding_box2d out_bounds) {
    quad_key_javaJNI.quad_key_get_geo_coordinate_bounds2d(swigCPtr, this, geo_coordinate_bounding_box2d.getCPtr(out_bounds), out_bounds);
  }

  public String to_internal_string() {
    return quad_key_javaJNI.quad_key_to_internal_string(swigCPtr, this);
  }

  public static quad_key from_internal_string(type t, String in_string) {
    return new quad_key(quad_key_javaJNI.quad_key_from_internal_string(t.swigValue(), in_string), true);
  }

  public static quad_key get_key_from_longitude_latitude_at_depth(type t, geo_coordinate2d coords, short depth) {
    return new quad_key(quad_key_javaJNI.quad_key_get_key_from_longitude_latitude_at_depth(t.swigValue(), geo_coordinate2d.getCPtr(coords), coords, depth), true);
  }

  public static quad_key_vector get_keys_from_longitude_latitude_bounding_box(type t, geo_coordinate_bounding_box2d bounds, short depth) {
    return new quad_key_vector(quad_key_javaJNI.quad_key_get_keys_from_longitude_latitude_bounding_box(t.swigValue(), geo_coordinate_bounding_box2d.getCPtr(bounds), bounds, depth), true);
  }

  public static short max_depth(type t) {
    return quad_key_javaJNI.quad_key_max_depth(t.swigValue());
  }

  public static long max_rows(type t, short depth) {
    return quad_key_javaJNI.quad_key_max_rows(t.swigValue(), depth);
  }

  public static long max_cols(type t, short depth) {
    return quad_key_javaJNI.quad_key_max_cols(t.swigValue(), depth);
  }

  public static java.math.BigInteger max_tiles(type t, short depth) {
    return quad_key_javaJNI.quad_key_max_tiles(t.swigValue(), depth);
  }

  public boolean less_than(quad_key rhs) {
    return quad_key_javaJNI.quad_key_less_than(swigCPtr, this, quad_key.getCPtr(rhs), rhs);
  }

  public boolean equal_to(quad_key rhs) {
    return quad_key_javaJNI.quad_key_equal_to(swigCPtr, this, quad_key.getCPtr(rhs), rhs);
  }

  public boolean not_equal_to(quad_key rhs) {
    return quad_key_javaJNI.quad_key_not_equal_to(swigCPtr, this, quad_key.getCPtr(rhs), rhs);
  }

  public final static class quadrant {
    public final static quad_key.quadrant south_west = new quad_key.quadrant("south_west", quad_key_javaJNI.quad_key_quadrant_south_west_get());
    public final static quad_key.quadrant south_east = new quad_key.quadrant("south_east", quad_key_javaJNI.quad_key_quadrant_south_east_get());
    public final static quad_key.quadrant north_west = new quad_key.quadrant("north_west", quad_key_javaJNI.quad_key_quadrant_north_west_get());
    public final static quad_key.quadrant north_east = new quad_key.quadrant("north_east", quad_key_javaJNI.quad_key_quadrant_north_east_get());

    public final int swigValue() {
      return swigValue;
    }

    public String toString() {
      return swigName;
    }

    public static quadrant swigToEnum(int swigValue) {
      if (swigValue < swigValues.length && swigValue >= 0 && swigValues[swigValue].swigValue == swigValue)
        return swigValues[swigValue];
      for (int i = 0; i < swigValues.length; i++)
        if (swigValues[i].swigValue == swigValue)
          return swigValues[i];
      throw new IllegalArgumentException("No enum " + quadrant.class + " with value " + swigValue);
    }

    private quadrant(String swigName) {
      this.swigName = swigName;
      this.swigValue = swigNext++;
    }

    private quadrant(String swigName, int swigValue) {
      this.swigName = swigName;
      this.swigValue = swigValue;
      swigNext = swigValue+1;
    }

    private quadrant(String swigName, quadrant swigEnum) {
      this.swigName = swigName;
      this.swigValue = swigEnum.swigValue;
      swigNext = this.swigValue+1;
    }

    private static quadrant[] swigValues = { south_west, south_east, north_west, north_east };
    private static int swigNext = 0;
    private final int swigValue;
    private final String swigName;
  }

}
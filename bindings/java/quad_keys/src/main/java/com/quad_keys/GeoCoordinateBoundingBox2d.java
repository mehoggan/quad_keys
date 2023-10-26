/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (https://www.swig.org).
 * Version 4.1.1
 *
 * Do not make changes to this file unless you know what you are doing - modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package com.quad_keys;

public class GeoCoordinateBoundingBox2d {
  private transient long swigCPtr;
  protected transient boolean swigCMemOwn;

  protected GeoCoordinateBoundingBox2d(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(GeoCoordinateBoundingBox2d obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected static long swigRelease(GeoCoordinateBoundingBox2d obj) {
    long ptr = 0;
    if (obj != null) {
      if (!obj.swigCMemOwn)
        throw new RuntimeException("Cannot release ownership as memory is not owned");
      ptr = obj.swigCPtr;
      obj.swigCMemOwn = false;
      obj.delete();
    }
    return ptr;
  }

  @SuppressWarnings("deprecation")
  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        quad_key_javaJNI.delete_GeoCoordinateBoundingBox2d(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public GeoCoordinateBoundingBox2d() {
    this(quad_key_javaJNI.new_GeoCoordinateBoundingBox2d__SWIG_0(), true);
  }

  public GeoCoordinateBoundingBox2d(GeoCoordinate2d coordinate0, GeoCoordinate2d coordinate1) {
    this(quad_key_javaJNI.new_GeoCoordinateBoundingBox2d__SWIG_1(GeoCoordinate2d.getCPtr(coordinate0), coordinate0, GeoCoordinate2d.getCPtr(coordinate1), coordinate1), true);
  }

  public boolean contains(GeoCoordinate2d coordinate) {
    return quad_key_javaJNI.GeoCoordinateBoundingBox2d_contains(swigCPtr, this, GeoCoordinate2d.getCPtr(coordinate), coordinate);
  }

  public void grow_to_contain(GeoCoordinate2d coordinate) {
    quad_key_javaJNI.GeoCoordinateBoundingBox2d_grow_to_contain(swigCPtr, this, GeoCoordinate2d.getCPtr(coordinate), coordinate);
  }

  public GeoCoordinate2d lower_left() {
    return new GeoCoordinate2d(quad_key_javaJNI.GeoCoordinateBoundingBox2d_lower_left(swigCPtr, this), false);
  }

  public GeoCoordinate2d upper_right() {
    return new GeoCoordinate2d(quad_key_javaJNI.GeoCoordinateBoundingBox2d_upper_right(swigCPtr, this), false);
  }

  public GeoCoordinate2d upper_left() {
    return new GeoCoordinate2d(quad_key_javaJNI.GeoCoordinateBoundingBox2d_upper_left(swigCPtr, this), true);
  }

  public GeoCoordinate2d lower_right() {
    return new GeoCoordinate2d(quad_key_javaJNI.GeoCoordinateBoundingBox2d_lower_right(swigCPtr, this), true);
  }

  public boolean is_valid() {
    return quad_key_javaJNI.GeoCoordinateBoundingBox2d_is_valid(swigCPtr, this);
  }

}

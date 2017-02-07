/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.12
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package com.quad_key;

public class geo_coordinate2d {
  private transient long swigCPtr;
  protected transient boolean swigCMemOwn;

  protected geo_coordinate2d(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(geo_coordinate2d obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        quad_key_javaJNI.delete_geo_coordinate2d(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public geo_coordinate2d() {
    this(quad_key_javaJNI.new_geo_coordinate2d__SWIG_0(), true);
  }

  public geo_coordinate2d(longitude longitude, latitude latitude) {
    this(quad_key_javaJNI.new_geo_coordinate2d__SWIG_1(longitude.getCPtr(longitude), longitude, latitude.getCPtr(latitude), latitude), true);
  }

  public geo_coordinate2d(geo_coordinate2d other) {
    this(quad_key_javaJNI.new_geo_coordinate2d__SWIG_2(geo_coordinate2d.getCPtr(other), other), true);
  }

  public geo_coordinate2d assign_geo_coordinate2d(geo_coordinate2d rhs) {
    return new geo_coordinate2d(quad_key_javaJNI.geo_coordinate2d_assign_geo_coordinate2d(swigCPtr, this, geo_coordinate2d.getCPtr(rhs), rhs), false);
  }

  public void set_longitude(double longit) {
    quad_key_javaJNI.geo_coordinate2d_set_longitude__SWIG_0(swigCPtr, this, longit);
  }

  public void set_latitude(double latit) {
    quad_key_javaJNI.geo_coordinate2d_set_latitude__SWIG_0(swigCPtr, this, latit);
  }

  public void set_longitude(longitude longit) {
    quad_key_javaJNI.geo_coordinate2d_set_longitude__SWIG_1(swigCPtr, this, longitude.getCPtr(longit), longit);
  }

  public void set_latitude(latitude latit) {
    quad_key_javaJNI.geo_coordinate2d_set_latitude__SWIG_1(swigCPtr, this, latitude.getCPtr(latit), latit);
  }

  public longitude get_longitude() {
    return new longitude(quad_key_javaJNI.geo_coordinate2d_get_longitude(swigCPtr, this), false);
  }

  public latitude get_latitude() {
    return new latitude(quad_key_javaJNI.geo_coordinate2d_get_latitude(swigCPtr, this), false);
  }

  public boolean near(geo_coordinate2d other, double eps) {
    return quad_key_javaJNI.geo_coordinate2d_near__SWIG_0(swigCPtr, this, geo_coordinate2d.getCPtr(other), other, eps);
  }

  public boolean near(geo_coordinate2d other) {
    return quad_key_javaJNI.geo_coordinate2d_near__SWIG_1(swigCPtr, this, geo_coordinate2d.getCPtr(other), other);
  }

  public boolean equalTo(geo_coordinate2d rhs) {
    return quad_key_javaJNI.geo_coordinate2d_equalTo(swigCPtr, this, geo_coordinate2d.getCPtr(rhs), rhs);
  }

  public boolean notEqualTo(geo_coordinate2d rhs) {
    return quad_key_javaJNI.geo_coordinate2d_notEqualTo(swigCPtr, this, geo_coordinate2d.getCPtr(rhs), rhs);
  }

}

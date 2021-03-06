/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.12
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package com.quad_key;

public class longitude {
  private transient long swigCPtr;
  protected transient boolean swigCMemOwn;

  protected longitude(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(longitude obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        quad_key_javaJNI.delete_longitude(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public static double getMin_longitude() {
    return quad_key_javaJNI.longitude_min_longitude_get();
  }

  public static double getMax_longitude() {
    return quad_key_javaJNI.longitude_max_longitude_get();
  }

  public longitude(double val) {
    this(quad_key_javaJNI.new_longitude__SWIG_0(val), true);
  }

  public longitude(longitude other) {
    this(quad_key_javaJNI.new_longitude__SWIG_1(longitude.getCPtr(other), other), true);
  }

  public longitude assign_longitude(longitude rhs) {
    return new longitude(quad_key_javaJNI.longitude_assign_longitude(swigCPtr, this, longitude.getCPtr(rhs), rhs), false);
  }

  public double val() {
    return quad_key_javaJNI.longitude_val(swigCPtr, this);
  }

  public boolean near(longitude other, double eps) {
    return quad_key_javaJNI.longitude_near__SWIG_0(swigCPtr, this, longitude.getCPtr(other), other, eps);
  }

  public boolean near(longitude other) {
    return quad_key_javaJNI.longitude_near__SWIG_1(swigCPtr, this, longitude.getCPtr(other), other);
  }

  public boolean less_than(longitude rhs) {
    return quad_key_javaJNI.longitude_less_than(swigCPtr, this, longitude.getCPtr(rhs), rhs);
  }

  public boolean less_than_or_equal(longitude rhs) {
    return quad_key_javaJNI.longitude_less_than_or_equal(swigCPtr, this, longitude.getCPtr(rhs), rhs);
  }

  public boolean greater_than(longitude rhs) {
    return quad_key_javaJNI.longitude_greater_than(swigCPtr, this, longitude.getCPtr(rhs), rhs);
  }

  public boolean greater_than_or_equal(longitude rhs) {
    return quad_key_javaJNI.longitude_greater_than_or_equal(swigCPtr, this, longitude.getCPtr(rhs), rhs);
  }

  public boolean equal_to(longitude rhs) {
    return quad_key_javaJNI.longitude_equal_to(swigCPtr, this, longitude.getCPtr(rhs), rhs);
  }

  public boolean not_equal_to(longitude rhs) {
    return quad_key_javaJNI.longitude_not_equal_to(swigCPtr, this, longitude.getCPtr(rhs), rhs);
  }

  public double longitude_difference(longitude subtrahend) {
    return quad_key_javaJNI.longitude_longitude_difference(swigCPtr, this, longitude.getCPtr(subtrahend), subtrahend);
  }

}

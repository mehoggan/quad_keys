/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.12
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package com.quad_key;

public final class type {
  public final static type bing = new type("bing");
  public final static type lat_long = new type("lat_long");
  public final static type morton = new type("morton");
  public final static type none = new type("none");
  public final static type osgeo = new type("osgeo");
  public final static type ulp_qnr = new type("ulp_qnr");
  public final static type s2_cell = new type("s2_cell");

  public final int swigValue() {
    return swigValue;
  }

  public String toString() {
    return swigName;
  }

  public static type swigToEnum(int swigValue) {
    if (swigValue < swigValues.length && swigValue >= 0 && swigValues[swigValue].swigValue == swigValue)
      return swigValues[swigValue];
    for (int i = 0; i < swigValues.length; i++)
      if (swigValues[i].swigValue == swigValue)
        return swigValues[i];
    throw new IllegalArgumentException("No enum " + type.class + " with value " + swigValue);
  }

  private type(String swigName) {
    this.swigName = swigName;
    this.swigValue = swigNext++;
  }

  private type(String swigName, int swigValue) {
    this.swigName = swigName;
    this.swigValue = swigValue;
    swigNext = swigValue+1;
  }

  private type(String swigName, type swigEnum) {
    this.swigName = swigName;
    this.swigValue = swigEnum.swigValue;
    swigNext = this.swigValue+1;
  }

  private static type[] swigValues = { bing, lat_long, morton, none, osgeo, ulp_qnr, s2_cell };
  private static int swigNext = 0;
  private final int swigValue;
  private final String swigName;
}


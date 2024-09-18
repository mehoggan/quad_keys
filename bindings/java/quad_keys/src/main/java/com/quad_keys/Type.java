/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (https://www.swig.org).
 * Version 4.2.1
 *
 * Do not make changes to this file unless you know what you are doing - modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package com.quad_keys;

public final class Type {
  public final static Type Bing = new Type("Bing");
  public final static Type LatLon = new Type("LatLon");
  public final static Type Morton = new Type("Morton");
  public final static Type None = new Type("None");
  public final static Type OsGeo = new Type("OsGeo");
  public final static Type UlpQnr = new Type("UlpQnr");

  public final int swigValue() {
    return swigValue;
  }

  public String toString() {
    return swigName;
  }

  public static Type swigToEnum(int swigValue) {
    if (swigValue < swigValues.length && swigValue >= 0 && swigValues[swigValue].swigValue == swigValue)
      return swigValues[swigValue];
    for (int i = 0; i < swigValues.length; i++)
      if (swigValues[i].swigValue == swigValue)
        return swigValues[i];
    throw new IllegalArgumentException("No enum " + Type.class + " with value " + swigValue);
  }

  private Type(String swigName) {
    this.swigName = swigName;
    this.swigValue = swigNext++;
  }

  private Type(String swigName, int swigValue) {
    this.swigName = swigName;
    this.swigValue = swigValue;
    swigNext = swigValue+1;
  }

  private Type(String swigName, Type swigEnum) {
    this.swigName = swigName;
    this.swigValue = swigEnum.swigValue;
    swigNext = this.swigValue+1;
  }

  private static Type[] swigValues = { Bing, LatLon, Morton, None, OsGeo, UlpQnr };
  private static int swigNext = 0;
  private final int swigValue;
  private final String swigName;
}


/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (https://www.swig.org).
 * Version 4.2.1
 *
 * Do not make changes to this file unless you know what you are doing - modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package com.quad_keys;

public class QuadKeysVector extends java.util.AbstractList<QuadKey> implements java.util.RandomAccess {
  private transient long swigCPtr;
  protected transient boolean swigCMemOwn;

  protected QuadKeysVector(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(QuadKeysVector obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected static long swigRelease(QuadKeysVector obj) {
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

  @SuppressWarnings({"deprecation", "removal"})
  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        quad_keys_javaJNI.delete_QuadKeysVector(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public QuadKeysVector(QuadKey[] initialElements) {
    this();
    reserve(initialElements.length);

    for (QuadKey element : initialElements) {
      add(element);
    }
  }

  public QuadKeysVector(Iterable<QuadKey> initialElements) {
    this();
    for (QuadKey element : initialElements) {
      add(element);
    }
  }

  public QuadKey get(int index) {
    return doGet(index);
  }

  public QuadKey set(int index, QuadKey e) {
    return doSet(index, e);
  }

  public boolean add(QuadKey e) {
    modCount++;
    doAdd(e);
    return true;
  }

  public void add(int index, QuadKey e) {
    modCount++;
    doAdd(index, e);
  }

  public QuadKey remove(int index) {
    modCount++;
    return doRemove(index);
  }

  protected void removeRange(int fromIndex, int toIndex) {
    modCount++;
    doRemoveRange(fromIndex, toIndex);
  }

  public int size() {
    return doSize();
  }

  public int capacity() {
    return doCapacity();
  }

  public void reserve(int n) {
    doReserve(n);
  }

  public QuadKeysVector() {
    this(quad_keys_javaJNI.new_QuadKeysVector__SWIG_0(), true);
  }

  public QuadKeysVector(QuadKeysVector other) {
    this(quad_keys_javaJNI.new_QuadKeysVector__SWIG_1(QuadKeysVector.getCPtr(other), other), true);
  }

  public boolean isEmpty() {
    return quad_keys_javaJNI.QuadKeysVector_isEmpty(swigCPtr, this);
  }

  public void clear() {
    quad_keys_javaJNI.QuadKeysVector_clear(swigCPtr, this);
  }

  public QuadKeysVector(int count, QuadKey value) {
    this(quad_keys_javaJNI.new_QuadKeysVector__SWIG_2(count, QuadKey.getCPtr(value), value), true);
  }

  private int doCapacity() {
    return quad_keys_javaJNI.QuadKeysVector_doCapacity(swigCPtr, this);
  }

  private void doReserve(int n) {
    quad_keys_javaJNI.QuadKeysVector_doReserve(swigCPtr, this, n);
  }

  private int doSize() {
    return quad_keys_javaJNI.QuadKeysVector_doSize(swigCPtr, this);
  }

  private void doAdd(QuadKey x) {
    quad_keys_javaJNI.QuadKeysVector_doAdd__SWIG_0(swigCPtr, this, QuadKey.getCPtr(x), x);
  }

  private void doAdd(int index, QuadKey x) {
    quad_keys_javaJNI.QuadKeysVector_doAdd__SWIG_1(swigCPtr, this, index, QuadKey.getCPtr(x), x);
  }

  private QuadKey doRemove(int index) {
    return new QuadKey(quad_keys_javaJNI.QuadKeysVector_doRemove(swigCPtr, this, index), true);
  }

  private QuadKey doGet(int index) {
    return new QuadKey(quad_keys_javaJNI.QuadKeysVector_doGet(swigCPtr, this, index), false);
  }

  private QuadKey doSet(int index, QuadKey val) {
    return new QuadKey(quad_keys_javaJNI.QuadKeysVector_doSet(swigCPtr, this, index, QuadKey.getCPtr(val), val), true);
  }

  private void doRemoveRange(int fromIndex, int toIndex) {
    quad_keys_javaJNI.QuadKeysVector_doRemoveRange(swigCPtr, this, fromIndex, toIndex);
  }

}

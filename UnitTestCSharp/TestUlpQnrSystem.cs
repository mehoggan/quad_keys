using System;
using System.Collections.Generic;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using QuadKeys;

namespace QuadKeyTests
{
    [TestClass]
    public class TestUlpQnrSystem
    {
        private bool VectorContains(QuadKeyVector vect, QuadKey key)
        {
            bool found = false;
            for (int i = 0; i < vect.Count; ++i)
            {
                QuadKey curr = vect[i];
                if (curr.EqualTo(key))
                {
                    found = true;
                    break;
                }
            }
            return found;
        }

        [TestMethod]
        public void TestIsValid()
        {
            // See TestQuadKey TestSpecificCtor.
        }

        [TestMethod]
        public void TestIsRootKey()
        {
            // Same as BingSystem
        }

        [TestMethod]
        public void TestGetParent()
        {
            // Same as BingSystem
        }

        [TestMethod]
        public void TestIsMyAncestor()
        {
            // Same as BingSystem
        }

        [TestMethod]
        public void TestGetAncestor()
        {
            // Same as BingSystem
        }

        [TestMethod]
        public void TestGetChild()
        {
            // Same as BingSystem
        }

        [TestMethod]
        public void TestGetChildren()
        {
            // Same as BingSystem
        }

        [TestMethod]
        public void TestGetDescendants()
        {
            // Same as BingSystem
        }

        [TestMethod]
        public void TestGetSiblings()
        {
            // Same as BingSystem
        }

        [TestMethod]
        public void TestGetNeighbors()
        {
            // Same as BingSystem
        }

        [TestMethod]
        public void TestFromStringToString()
        {
            QuadKey quadKey = new QuadKey(QuadKeys.Type.UlpQnr, 0, 0,(byte) 0);
            String fmt = quadKey.toInternalString();
            Assert.AreEqual("1", fmt);
            QuadKey quadKeyBack = QuadKey.fromInternalString(
                QuadKeys.Type.UlpQnr, fmt);
            Assert.IsTrue(quadKey.EqualTo(quadKeyBack));

            quadKey = new QuadKey(QuadKeys.Type.UlpQnr, 0, 0, (byte) 1);
            fmt = quadKey.toInternalString();
            Assert.AreEqual("4", fmt);
            quadKeyBack = QuadKey.fromInternalString(QuadKeys.Type.UlpQnr, fmt);
            Assert.IsTrue(quadKey.EqualTo(quadKeyBack));

            quadKey = new QuadKey(QuadKeys.Type.UlpQnr, 0, 1, (byte) 1);
            fmt = quadKey.toInternalString();
            Assert.AreEqual("5", fmt);
            quadKeyBack = QuadKey.fromInternalString(QuadKeys.Type.UlpQnr, fmt);
            Assert.IsTrue(quadKey.EqualTo(quadKeyBack));

            quadKey = new QuadKey(QuadKeys.Type.UlpQnr, 0, 0, (byte) 2);
            fmt = quadKey.toInternalString();
            Assert.AreEqual("16", fmt);
            quadKeyBack = QuadKey.fromInternalString(QuadKeys.Type.UlpQnr, fmt);
            Assert.IsTrue(quadKey.EqualTo(quadKeyBack));

            quadKey = new QuadKey(QuadKeys.Type.UlpQnr, 0, 1, (byte) 2);
            fmt = quadKey.toInternalString();
            Assert.AreEqual("17", fmt);
            quadKeyBack = QuadKey.fromInternalString(QuadKeys.Type.UlpQnr, fmt);
            Assert.IsTrue(quadKey.EqualTo(quadKeyBack));

            quadKey = new QuadKey(QuadKeys.Type.UlpQnr, 1, 0, (byte) 2);
            fmt = quadKey.toInternalString();
            Assert.AreEqual("20", fmt);
            quadKeyBack = QuadKey.fromInternalString(QuadKeys.Type.UlpQnr, fmt);
            Assert.IsTrue(quadKey.EqualTo(quadKeyBack));

            quadKey = new QuadKey(QuadKeys.Type.UlpQnr, 1, 1, (byte) 2);
            fmt = quadKey.toInternalString();
            Assert.AreEqual("21", fmt);
            quadKeyBack = QuadKey.fromInternalString(QuadKeys.Type.UlpQnr, fmt);
            Assert.IsTrue(quadKey.EqualTo(quadKeyBack));

            quadKey = new QuadKey(QuadKeys.Type.UlpQnr, 0, 2, (byte) 2);
            fmt = quadKey.toInternalString();
            Assert.AreEqual("18", fmt);
            quadKeyBack = QuadKey.fromInternalString(QuadKeys.Type.UlpQnr, fmt);
            Assert.IsTrue(quadKey.EqualTo(quadKeyBack));

            quadKey = new QuadKey(QuadKeys.Type.UlpQnr, 0, 3, (byte) 2);
            fmt = quadKey.toInternalString();
            Assert.AreEqual("19", fmt);
            quadKeyBack = QuadKey.fromInternalString(QuadKeys.Type.UlpQnr, fmt);
            Assert.IsTrue(quadKey.EqualTo(quadKeyBack));

            quadKey = new QuadKey(QuadKeys.Type.UlpQnr, 1, 2, (byte) 2);
            fmt = quadKey.toInternalString();
            Assert.AreEqual("22", fmt);
            quadKeyBack = QuadKey.fromInternalString(QuadKeys.Type.UlpQnr, fmt);
            Assert.IsTrue(quadKey.EqualTo(quadKeyBack));

            quadKey = new QuadKey(QuadKeys.Type.UlpQnr, 1, 3, (byte) 2);
            fmt = quadKey.toInternalString();
            Assert.AreEqual("23", fmt);
            quadKeyBack = QuadKey.fromInternalString(QuadKeys.Type.UlpQnr, fmt);
            Assert.IsTrue(quadKey.EqualTo(quadKeyBack));

            // For Sanity Purposes and to Verify NO Fence Post Erros. Use a bit
            // of brute force.
            List<int> expected = new List<int>();
            for (int i = 64; i < 64 + 32; ++i) {
                expected.Add(i);
            }
            for (uint i = 0; i < (8 * 4); ++i) {
                uint row = i / 8;
                uint col = i % 8;
                quadKey = new QuadKey(QuadKeys.Type.UlpQnr, row, col, (byte) 3);
                fmt = quadKey.toInternalString();

                String expectedStr = "" + expected[(int)i];

                Assert.AreEqual(expectedStr, fmt);
                quadKeyBack = QuadKey.fromInternalString(QuadKeys.Type.UlpQnr,
                    fmt);
                Assert.IsTrue(quadKey.EqualTo(quadKeyBack));
            }

            quadKey = new QuadKey(QuadKeys.Type.UlpQnr, 0, 0, (byte) 3);
            fmt = quadKey.toInternalString();
            Assert.AreEqual("64", fmt);
            quadKeyBack = QuadKey.fromInternalString(QuadKeys.Type.UlpQnr, fmt);
            Assert.IsTrue(quadKey.EqualTo(quadKeyBack));
        }

        [TestMethod]
        public void TestGetGeoCoordinateBounds2d()
        {
            QuadKey quadKey;
            GeoCoordinateBoundingBox2d bbox = new GeoCoordinateBoundingBox2d();

            quadKey = new QuadKey(QuadKeys.Type.UlpQnr, 0, 0, (byte)0);
            quadKey.getGeoCoordinateBounds2d(bbox);
            Assert.IsTrue(bbox.lowerLeft().near(new GeoCoordinate2d(
                new Longitude(-180.0), new Latitude(-90.0)), 1e-4));
            Assert.IsTrue(bbox.upperRight().near(new GeoCoordinate2d(
                new Longitude(+180.0), new Latitude(+90.0)), 1e-4));

            quadKey = new QuadKey(QuadKeys.Type.UlpQnr, 0, 0, (byte)1);
            quadKey.getGeoCoordinateBounds2d(bbox);
            Assert.IsTrue(bbox.lowerLeft().near(new GeoCoordinate2d(
                new Longitude(-180.0), new Latitude(-90.0)), 1e-4));
            Assert.IsTrue(bbox.upperRight().near(new GeoCoordinate2d(
                new Longitude(+0.0), new Latitude(+90.0)), 1e-4));

            quadKey = new QuadKey(QuadKeys.Type.UlpQnr, 0, 1, (byte)1);
            quadKey.getGeoCoordinateBounds2d(bbox);
            Assert.IsTrue(bbox.lowerLeft().near(new GeoCoordinate2d(
                new Longitude(+0.0), new Latitude(-90.0)), 1e-4));
            Assert.IsTrue(bbox.upperRight().near(new GeoCoordinate2d(
                new Longitude(+180.0), new Latitude(+90.0)), 1e-4));

            quadKey = new QuadKey(QuadKeys.Type.UlpQnr, 0, 0, (byte)2);
            quadKey.getGeoCoordinateBounds2d(bbox);
            Assert.IsTrue(bbox.lowerLeft().near(new GeoCoordinate2d(
                new Longitude(-180.0), new Latitude(-90.0)), 1e-4));
            Assert.IsTrue(bbox.upperRight().near(new GeoCoordinate2d(
                new Longitude(-90.0), new Latitude(+0.0)), 1e-4));

            quadKey = new QuadKey(QuadKeys.Type.UlpQnr, 0, 1, (byte)2);
            quadKey.getGeoCoordinateBounds2d(bbox);
            Assert.IsTrue(bbox.lowerLeft().near(new GeoCoordinate2d(
                new Longitude(-90.0), new Latitude(-90.0)), 1e-4));

            Assert.IsTrue(bbox.upperRight().near(new GeoCoordinate2d(
                new Longitude(+0.0), new Latitude(+0.0)), 1e-4));

            quadKey = new QuadKey(QuadKeys.Type.UlpQnr, 1, 0, (byte)2);
            quadKey.getGeoCoordinateBounds2d(bbox);
            Assert.IsTrue(bbox.lowerLeft().near(new GeoCoordinate2d(
                new Longitude(-180.0), new Latitude(+0.0)), 1e-4));
            Assert.IsTrue(bbox.upperRight().near(new GeoCoordinate2d(
                new Longitude(-90.0), new Latitude(+90.0)), 1e-4));

            quadKey = new QuadKey(QuadKeys.Type.UlpQnr, 1, 1, (byte)2);
            quadKey.getGeoCoordinateBounds2d(bbox);
            Assert.IsTrue(bbox.lowerLeft().near(new GeoCoordinate2d(
                new Longitude(-90.0), new Latitude(+0.0)), 1e-4));
            Assert.IsTrue(bbox.upperRight().near(new GeoCoordinate2d(
                new Longitude(+0.0), new Latitude(+90.0)), 1e-4));

            quadKey = new QuadKey(QuadKeys.Type.UlpQnr, 0, 2, (byte)2);
            quadKey.getGeoCoordinateBounds2d(bbox);
            Assert.IsTrue(bbox.lowerLeft().near(new GeoCoordinate2d(
                new Longitude(+0.0), new Latitude(-90.0)), 1e-4));
            Assert.IsTrue(bbox.upperRight().near(new GeoCoordinate2d(
                new Longitude(+90.0), new Latitude(+0.0)), 1e-4));

            quadKey = new QuadKey(QuadKeys.Type.UlpQnr, 0, 3, (byte)2);
            quadKey.getGeoCoordinateBounds2d(bbox);
            Assert.IsTrue(bbox.lowerLeft().near(new GeoCoordinate2d(
                new Longitude(+90.0), new Latitude(-90.0)), 1e-4));
            Assert.IsTrue(bbox.upperRight().near(new GeoCoordinate2d(
                new Longitude(+180.0), new Latitude(+0.0)), 1e-4));

            quadKey = new QuadKey(QuadKeys.Type.UlpQnr, 1, 2, (byte)2);
            quadKey.getGeoCoordinateBounds2d(bbox);
            Assert.IsTrue(bbox.lowerLeft().near(new GeoCoordinate2d(
                new Longitude(+0.0), new Latitude(+0.0)), 1e-4));
            Assert.IsTrue(bbox.upperRight().near(new GeoCoordinate2d(
                new Longitude(+90.0), new Latitude(+90.0)), 1e-4));

            quadKey = new QuadKey(QuadKeys.Type.UlpQnr, 1, 3, (byte)2);
            quadKey.getGeoCoordinateBounds2d(bbox);
            Assert.IsTrue(bbox.lowerLeft().near(new GeoCoordinate2d(
                new Longitude(+90.0), new Latitude(+0.0)), 1e-4));
            Assert.IsTrue(bbox.upperRight().near(new GeoCoordinate2d(
                new Longitude(+180.0), new Latitude(+90.0)), 1e-4));
        }

        [TestMethod]
        public void TestGetKeyFromLongitudeLatitudeAtDepthToBounds()
        {
            QuadKey computedKey;
            computedKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                QuadKeys.Type.UlpQnr,
                new GeoCoordinate2d(
                    new Longitude(-180.0), new Latitude(-90.0)),
                    (byte)0);
            Assert.AreEqual("1", computedKey.toInternalString());
            computedKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                QuadKeys.Type.UlpQnr,
                new GeoCoordinate2d(
                    new Longitude(0.0), new Latitude(0.0)),
                    (byte)0);
            Assert.AreEqual("1", computedKey.toInternalString());

            computedKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                QuadKeys.Type.UlpQnr,
                new GeoCoordinate2d(
                    new Longitude(-180.0), new Latitude(-90.0)),
                    (byte)1);
            Assert.AreEqual("4", computedKey.toInternalString());
            computedKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                QuadKeys.Type.UlpQnr,
                new GeoCoordinate2d(
                    new Longitude(-180.0), new Latitude(90.0)),
                    (byte)1);
            Assert.AreEqual("4", computedKey.toInternalString());
            computedKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                QuadKeys.Type.UlpQnr,
                new GeoCoordinate2d(
                    new Longitude(0.1), new Latitude(-90.0)),
                    (byte)1);
            Assert.AreEqual("5", computedKey.toInternalString());
            computedKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                QuadKeys.Type.UlpQnr,
                new GeoCoordinate2d(
                    new Longitude(180.0), new Latitude(90.0)),
                    (byte)1);
            Assert.AreEqual("5", computedKey.toInternalString());

            computedKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                QuadKeys.Type.UlpQnr,
                new GeoCoordinate2d(
                    new Longitude(-180.0), new Latitude(-90.0)),
                    (byte)2);
            Assert.AreEqual("16", computedKey.toInternalString());
            computedKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                QuadKeys.Type.UlpQnr,
                new GeoCoordinate2d(
                    new Longitude(-89.9), new Latitude(-90.0)),
                    (byte)2);
            Assert.AreEqual("17", computedKey.toInternalString());
            computedKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                QuadKeys.Type.UlpQnr,
                new GeoCoordinate2d(
                    new Longitude(0.1), new Latitude(-90.0)),
                    (byte)2);
            Assert.AreEqual("18", computedKey.toInternalString());
            computedKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                QuadKeys.Type.UlpQnr,
                new GeoCoordinate2d(
                    new Longitude(90.1), new Latitude(-90.0)),
                    (byte)2);
            Assert.AreEqual("19", computedKey.toInternalString());
            computedKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                QuadKeys.Type.UlpQnr,
                new GeoCoordinate2d(
                    new Longitude(-180.0), new Latitude(0.1)),
                    (byte)2);
            Assert.AreEqual("20", computedKey.toInternalString());
            computedKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                QuadKeys.Type.UlpQnr,
                new GeoCoordinate2d(
                    new Longitude(-89.9), new Latitude(0.1)),
                    (byte)2);
            Assert.AreEqual("21", computedKey.toInternalString());
            computedKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                QuadKeys.Type.UlpQnr,
                new GeoCoordinate2d(
                    new Longitude(0.1), new Latitude(0.1)),
                    (byte)2);
            Assert.AreEqual("22", computedKey.toInternalString());
            computedKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                QuadKeys.Type.UlpQnr,
                new GeoCoordinate2d(
                    new Longitude(90.1), new Latitude(0.1)),
                    (byte)2);
            Assert.AreEqual("23", computedKey.toInternalString());
        }

        [TestMethod]
        public void TestGetKeysFromLongitudeLatitudeBoundingBox()
        {
            QuadKeyVector outKeys;
            QuadKey quadKey;

            // Select Entire Earth
            outKeys = QuadKey.getKeysFromLongitudeLatitudeBoundingBox(
                QuadKeys.Type.UlpQnr,
                new GeoCoordinateBoundingBox2d(
                    new GeoCoordinate2d(
                        new Longitude(-180.0), new Latitude(-90.0)),
                    new GeoCoordinate2d(
                        new Longitude(180.0), new Latitude(90.0))),
                (byte)0);
            quadKey = QuadKey.fromInternalString(QuadKeys.Type.UlpQnr, "1");
            Assert.AreEqual(1, outKeys.Count);
            Assert.IsTrue(VectorContains(outKeys, quadKey));

            // Select Very Center of the Earth
            outKeys = QuadKey.getKeysFromLongitudeLatitudeBoundingBox(
                QuadKeys.Type.UlpQnr,
                new GeoCoordinateBoundingBox2d(
                    new GeoCoordinate2d(
                        new Longitude(-0.1), new Latitude(-0.1)),
                    new GeoCoordinate2d(
                        new Longitude(0.1), new Latitude(0.1))),
                (byte)0);
            quadKey = QuadKey.fromInternalString(QuadKeys.Type.UlpQnr, "1");
            Assert.AreEqual(1, outKeys.Count);
            Assert.IsTrue(VectorContains(outKeys, quadKey));

            // Select Western Hemisphere
            outKeys = QuadKey.getKeysFromLongitudeLatitudeBoundingBox(
                QuadKeys.Type.UlpQnr,
                new GeoCoordinateBoundingBox2d(
                    new GeoCoordinate2d(
                        new Longitude(-180.0), new Latitude(-90.0)),
                    new GeoCoordinate2d(
                        new Longitude(0.0), new Latitude(90.0))),
                (byte)1);
            quadKey = QuadKey.fromInternalString(QuadKeys.Type.UlpQnr, "4");
            Assert.AreEqual(1, outKeys.Count);
            Assert.IsTrue(VectorContains(outKeys, quadKey));

            // Select Eastern Hemisphere
            outKeys = QuadKey.getKeysFromLongitudeLatitudeBoundingBox(
                QuadKeys.Type.UlpQnr,
                new GeoCoordinateBoundingBox2d(
                    new GeoCoordinate2d(
                        new Longitude(0.1), new Latitude(-90.0)),
                    new GeoCoordinate2d(
                        new Longitude(180), new Latitude(90.0))),
                (byte)1);
            quadKey = QuadKey.fromInternalString(QuadKeys.Type.UlpQnr, "5");
            Assert.AreEqual(1, outKeys.Count);
            Assert.IsTrue(VectorContains(outKeys, quadKey));

            // Select Entire Planet
            outKeys = QuadKey.getKeysFromLongitudeLatitudeBoundingBox(
                QuadKeys.Type.UlpQnr,
                new GeoCoordinateBoundingBox2d(
                    new GeoCoordinate2d(
                        new Longitude(-180.0), new Latitude(-90.0)),
                    new GeoCoordinate2d(
                        new Longitude(180), new Latitude(90.0))),
                (byte)1);
            QuadKey quadKeya = QuadKey.fromInternalString(
                QuadKeys.Type.UlpQnr, "4");
            QuadKey quadKeyb = QuadKey.fromInternalString(
                QuadKeys.Type.UlpQnr, "5");
            Assert.AreEqual(2, outKeys.Count);
            Assert.IsTrue(VectorContains(outKeys, quadKeya));
            Assert.IsTrue(VectorContains(outKeys, quadKeyb));

            // Select South West Corner
            outKeys = QuadKey.getKeysFromLongitudeLatitudeBoundingBox(
                QuadKeys.Type.UlpQnr,
                new GeoCoordinateBoundingBox2d(
                    new GeoCoordinate2d(
                        new Longitude(-180.0), new Latitude(-90.0)),
                    new GeoCoordinate2d(
                        new Longitude(-90.0), new Latitude(0.0))),
                (byte)2);
            quadKey = QuadKey.fromInternalString(QuadKeys.Type.UlpQnr, "16");
            Assert.AreEqual(1, outKeys.Count);
            Assert.IsTrue(VectorContains(outKeys, quadKey));

            // Select South America
            outKeys = QuadKey.getKeysFromLongitudeLatitudeBoundingBox(
                QuadKeys.Type.UlpQnr,
                new GeoCoordinateBoundingBox2d(
                    new GeoCoordinate2d(
                        new Longitude(-89.9), new Latitude(-90.0)),
                    new GeoCoordinate2d(
                        new Longitude(0.0), new Latitude(0.0))),
                (byte)2);
            quadKey = QuadKey.fromInternalString(QuadKeys.Type.UlpQnr, "17");
            Assert.AreEqual(1, outKeys.Count);
            Assert.IsTrue(VectorContains(outKeys, quadKey));

            // Select North West Corner
            outKeys = QuadKey.getKeysFromLongitudeLatitudeBoundingBox(
                QuadKeys.Type.UlpQnr,
                new GeoCoordinateBoundingBox2d(
                    new GeoCoordinate2d(
                        new Longitude(-180.0), new Latitude(0.1)),
                    new GeoCoordinate2d(
                        new Longitude(-90.0), new Latitude(90.0))),
                (byte)2);
            quadKey = QuadKey.fromInternalString(QuadKeys.Type.UlpQnr, "20");
            Assert.AreEqual(1, outKeys.Count);
            Assert.IsTrue(VectorContains(outKeys, quadKey));

            // Select Greenland
            outKeys = QuadKey.getKeysFromLongitudeLatitudeBoundingBox(
                QuadKeys.Type.UlpQnr,
                new GeoCoordinateBoundingBox2d(
                    new GeoCoordinate2d(
                        new Longitude(-89.9), new Latitude(0.1)),
                    new GeoCoordinate2d(
                        new Longitude(0.0), new Latitude(90.0))),
                (byte)2);
            quadKey = QuadKey.fromInternalString(QuadKeys.Type.UlpQnr, "21");
            Assert.AreEqual(1, outKeys.Count);
            Assert.IsTrue(VectorContains(outKeys, quadKey));

            // Select South Pole
            outKeys = QuadKey.getKeysFromLongitudeLatitudeBoundingBox(
                QuadKeys.Type.UlpQnr,
                new GeoCoordinateBoundingBox2d(
                    new GeoCoordinate2d(
                        new Longitude(0.1), new Latitude(-90.0)),
                    new GeoCoordinate2d(
                        new Longitude(90.0), new Latitude(0.0))),
                (byte)2);
            quadKey = QuadKey.fromInternalString(QuadKeys.Type.UlpQnr, "18");
            Assert.AreEqual(1, outKeys.Count);
            Assert.IsTrue(VectorContains(outKeys, quadKey));

            // Select South East Corner
            outKeys = QuadKey.getKeysFromLongitudeLatitudeBoundingBox(
                QuadKeys.Type.UlpQnr,
                new GeoCoordinateBoundingBox2d(
                    new GeoCoordinate2d(
                        new Longitude(90.1), new Latitude(-90.0)),
                    new GeoCoordinate2d(
                        new Longitude(180.0), new Latitude(0.0))),
                (byte)2);
            quadKey = QuadKey.fromInternalString(QuadKeys.Type.UlpQnr, "19");
            Assert.AreEqual(1, outKeys.Count);
            Assert.IsTrue(VectorContains(outKeys, quadKey));

            // Select Over Europe
            outKeys = QuadKey.getKeysFromLongitudeLatitudeBoundingBox(
                QuadKeys.Type.UlpQnr,
                new GeoCoordinateBoundingBox2d(
                    new GeoCoordinate2d(
                        new Longitude(0.1), new Latitude(0.1)),
                    new GeoCoordinate2d(
                        new Longitude(90.0), new Latitude(90.0))),
                (byte)2);
            quadKey = QuadKey.fromInternalString(QuadKeys.Type.UlpQnr, "22");
            Assert.AreEqual(1, outKeys.Count);
            Assert.IsTrue(VectorContains(outKeys, quadKey));

            // Select North East Corner
            outKeys = QuadKey.getKeysFromLongitudeLatitudeBoundingBox(
                QuadKeys.Type.UlpQnr,
                new GeoCoordinateBoundingBox2d(
                    new GeoCoordinate2d(
                        new Longitude(90.1), new Latitude(0.1)),
                    new GeoCoordinate2d(
                        new Longitude(180.0), new Latitude(90.0))),
                (byte)2);
            quadKey = QuadKey.fromInternalString(QuadKeys.Type.UlpQnr, "23");
            Assert.AreEqual(1, outKeys.Count);
            Assert.IsTrue(VectorContains(outKeys, quadKey));

            // Select Entire Map
            outKeys = QuadKey.getKeysFromLongitudeLatitudeBoundingBox(
                QuadKeys.Type.UlpQnr,
                new GeoCoordinateBoundingBox2d(
                    new GeoCoordinate2d(
                        new Longitude(-179.9), new Latitude(-89.9)),
                    new GeoCoordinate2d(
                        new Longitude(90.1), new Latitude(0.1))),
                (byte)2);
            QuadKey quadKey0 = QuadKey.fromInternalString(
                QuadKeys.Type.UlpQnr, "16");
            QuadKey quadKey1 = QuadKey.fromInternalString(
                QuadKeys.Type.UlpQnr, "17");
            QuadKey quadKey2 = QuadKey.fromInternalString(
                QuadKeys.Type.UlpQnr, "18");
            QuadKey quadKey3 = QuadKey.fromInternalString(
                QuadKeys.Type.UlpQnr, "19");
            QuadKey quadKey4 = QuadKey.fromInternalString(
                QuadKeys.Type.UlpQnr, "20");
            QuadKey quadKey5 = QuadKey.fromInternalString(
                QuadKeys.Type.UlpQnr, "21");
            QuadKey quadKey6 = QuadKey.fromInternalString(
                QuadKeys.Type.UlpQnr, "22");
            QuadKey quadKey7 = QuadKey.fromInternalString(
                QuadKeys.Type.UlpQnr, "23");
            Assert.AreEqual(8, outKeys.Count);
            Assert.IsTrue(VectorContains(outKeys, quadKey0));
            Assert.IsTrue(VectorContains(outKeys, quadKey1));
            Assert.IsTrue(VectorContains(outKeys, quadKey2));
            Assert.IsTrue(VectorContains(outKeys, quadKey3));
            Assert.IsTrue(VectorContains(outKeys, quadKey4));
            Assert.IsTrue(VectorContains(outKeys, quadKey5));
            Assert.IsTrue(VectorContains(outKeys, quadKey6));
            Assert.IsTrue(VectorContains(outKeys, quadKey7));
        }

        [TestMethod]
        public void TestSelecetedCities()
        {
            // TODO: Implement Tests. Taken from Earthscape. No tests there.
        }
    }
}

using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using QuadKeys;

namespace QuadKeyTests
{
    [TestClass]
    public class TestLatLongSystem
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
            // See TestQuadKey TestSpecificCtorTest.
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
            // Same as BingSystem
        }

        [TestMethod]
        public void TestGetGeoCoordinateBounds2d()
        {
            QuadKey key;
            GeoCoordinateBoundingBox2d bbox = new GeoCoordinateBoundingBox2d();

            { // Depth 0
                key = new QuadKey(QuadKeys.Type.LatLong, 0, 0, 0);
                key.getGeoCoordinateBounds2d(bbox);
                Assert.IsTrue(new GeoCoordinate2d(new Longitude(-180.0),
                    new Latitude(-90.0)).EqualTo(bbox.lowerLeft()));
                Assert.IsTrue(new GeoCoordinate2d(new Longitude(+180.0),
                    new Latitude(+90.0)).EqualTo(bbox.upperRight()));
            }

            { // Depth 1
                key = new QuadKey(QuadKeys.Type.LatLong, 0, 0, 1);
                key.getGeoCoordinateBounds2d(bbox);
                Assert.IsTrue(bbox.lowerLeft().longitude().near(
                  new Longitude(-180.0), 1e-6));
                Assert.IsTrue(bbox.lowerLeft().latitude().near(
                  new Latitude(-90.0), 1e-6));
                Assert.IsTrue(bbox.upperRight().longitude().near(
                  new Longitude(+0.0), 1e-6));
                Assert.IsTrue(bbox.upperRight().latitude().near(
                  new Latitude(+0.0), 1e-6));

                key = new QuadKey(QuadKeys.Type.LatLong, 0, 1, 1);
                key.getGeoCoordinateBounds2d(bbox);
                Assert.IsTrue(bbox.lowerLeft().longitude().near(
                  new Longitude(+0.0), 1e-6));
                Assert.IsTrue(bbox.lowerLeft().latitude().near(
                  new Latitude(-90.0), 1e-6));
                Assert.IsTrue(bbox.upperRight().longitude().near(
                  new Longitude(+180.0), 1e-6));
                Assert.IsTrue(bbox.upperRight().latitude().near(
                  new Latitude(+0.0), 1e-6));

                key = new QuadKey(QuadKeys.Type.LatLong, 1, 0, 1);
                key.getGeoCoordinateBounds2d(bbox);
                Assert.IsTrue(bbox.lowerLeft().longitude().near(
                  new Longitude(-180.0), 1e-6));
                Assert.IsTrue(bbox.lowerLeft().latitude().near(
                  new Latitude(+0.0), 1e-6));
                Assert.IsTrue(bbox.upperRight().longitude().near(
                  new Longitude(+0.0), 1e-6));
                Assert.IsTrue(bbox.upperRight().latitude().near(
                  new Latitude(+90.0), 1e-6));

                key = new QuadKey(QuadKeys.Type.LatLong, 1, 1, 1);
                key.getGeoCoordinateBounds2d(bbox);
                Assert.IsTrue(bbox.lowerLeft().longitude().near(
                  new Longitude(+0.0), 1e-6));
                Assert.IsTrue(bbox.lowerLeft().latitude().near(
                  new Latitude(+0.0), 1e-6));
                Assert.IsTrue(bbox.upperRight().longitude().near(
                  new Longitude(+180.0), 1e-6));
                Assert.IsTrue(bbox.upperRight().latitude().near(
                  new Latitude(+90.0), 1e-6));
            }
        }

        [TestMethod]
        public void TestGetKeysFromLongitudeLatitudeAtDepthToBounds()
        {
            QuadKey key = new QuadKey();

            { // Depth 0
                key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    QuadKeys.Type.LatLong, new GeoCoordinate2d(
                    new Longitude(-180.0), new Latitude(-90)), (byte)0);
                Assert.IsTrue(new QuadKey(
                    QuadKeys.Type.LatLong, 0, 0, 0).EqualTo(key));
                Assert.AreEqual("", key.toInternalString());
            }

            // Inclusion here consists of lower left
            //    X------X------X
            //    |   2  |   3  |
            //    |      |      |
            //    X------X------X
            //    |   0  |   1  |
            //    |      |      |
            // ll X------X------X
            { // Depth 1
                key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    QuadKeys.Type.LatLong, new GeoCoordinate2d(
                        new Longitude(-180.0), new Latitude(-90.0)), (byte)1);
                Assert.IsTrue(new QuadKey(
                    QuadKeys.Type.LatLong, 0, 0, 1).EqualTo(key));
                Assert.AreEqual("2", key.toInternalString());
                key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    QuadKeys.Type.LatLong, new GeoCoordinate2d(
                        new Longitude(-0.1), new Latitude(-90.0)), (byte)1);
                Assert.IsTrue(new QuadKey(
                    QuadKeys.Type.LatLong, 0, 0, 1).EqualTo(key));
                Assert.AreEqual("2", key.toInternalString());
                key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    QuadKeys.Type.LatLong, new GeoCoordinate2d(
                    new Longitude(-0.1), new Latitude(-0.1)), (byte)1);
                Assert.IsTrue(new QuadKey(
                    QuadKeys.Type.LatLong, 0, 0, 1).EqualTo(key));
                Assert.AreEqual("2", key.toInternalString());
                key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    QuadKeys.Type.LatLong, new GeoCoordinate2d(
                        new Longitude(-180.0), new Latitude(-0.1)), (byte)1);
                Assert.IsTrue(new QuadKey(
                    QuadKeys.Type.LatLong, 0, 0, 1).EqualTo(key));
                Assert.AreEqual("2", key.toInternalString());

                key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    QuadKeys.Type.LatLong, new GeoCoordinate2d(
                        new Longitude(+0.0), new Latitude(-90.0)), (byte)1);
                Assert.IsTrue(new QuadKey(
                    QuadKeys.Type.LatLong, 0, 1, 1).EqualTo(key));
                Assert.AreEqual("3", key.toInternalString());
                key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    QuadKeys.Type.LatLong, new GeoCoordinate2d(
                        new Longitude(+180.0), new Latitude(-90.0)), (byte)1);
                Assert.IsTrue(new QuadKey(
                    QuadKeys.Type.LatLong, 0, 1, 1).EqualTo(key));
                Assert.AreEqual("3", key.toInternalString());
                key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    QuadKeys.Type.LatLong, new GeoCoordinate2d(
                        new Longitude(+180.0), new Latitude(-0.1)), (byte)1);
                Assert.IsTrue(new QuadKey(
                    QuadKeys.Type.LatLong, 0, 1, 1).EqualTo(key));
                Assert.AreEqual("3", key.toInternalString());
                key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    QuadKeys.Type.LatLong, new GeoCoordinate2d(
                        new Longitude(+0.0), new Latitude(-0.1)), (byte)1);
                Assert.IsTrue(new QuadKey(
                    QuadKeys.Type.LatLong, 0, 1, 1).EqualTo(key));
                Assert.AreEqual("3", key.toInternalString());

                key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    QuadKeys.Type.LatLong, new GeoCoordinate2d(
                        new Longitude(-180.0), new Latitude(+0.0)), (byte)1);
                Assert.IsTrue(new QuadKey(
                    QuadKeys.Type.LatLong, 1, 0, 1).EqualTo(key));
                Assert.AreEqual("0", key.toInternalString());
                key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    QuadKeys.Type.LatLong, new GeoCoordinate2d(
                        new Longitude(-0.1), new Latitude(+0.0)), (byte)1);
                Assert.IsTrue(new QuadKey(
                    QuadKeys.Type.LatLong, 1, 0, 1).EqualTo(key));
                Assert.AreEqual("0", key.toInternalString());
                key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    QuadKeys.Type.LatLong, new GeoCoordinate2d(
                        new Longitude(-180.0), new Latitude(+90.0)), (byte)1);
                Assert.IsTrue(new QuadKey(
                    QuadKeys.Type.LatLong, 1, 0, 1).EqualTo(key));
                Assert.AreEqual("0", key.toInternalString());
                key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    QuadKeys.Type.LatLong, new GeoCoordinate2d(
                        new Longitude(-0.1), new Latitude(+90.0)), (byte)1);
                Assert.IsTrue(new QuadKey(
                    QuadKeys.Type.LatLong, 1, 0, 1).EqualTo(key));
                Assert.AreEqual("0", key.toInternalString());

                key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    QuadKeys.Type.LatLong, new GeoCoordinate2d(
                        new Longitude(+0.0), new Latitude(+0.0)), (byte)1);
                Assert.IsTrue(new QuadKey(
                    QuadKeys.Type.LatLong, 1, 1, 1).EqualTo(key));
                Assert.AreEqual("1", key.toInternalString());
                key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    QuadKeys.Type.LatLong, new GeoCoordinate2d(
                        new Longitude(+180.0), new Latitude(+0.0)), (byte)1);
                Assert.IsTrue(new QuadKey(
                    QuadKeys.Type.LatLong, 1, 1, 1).EqualTo(key));
                Assert.AreEqual("1", key.toInternalString());
                key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    QuadKeys.Type.LatLong, new GeoCoordinate2d(
                        new Longitude(+0.0), new Latitude(+90.0)), (byte)1);
                Assert.IsTrue(new QuadKey(
                    QuadKeys.Type.LatLong, 1, 1, 1).EqualTo(key));
                Assert.AreEqual("1", key.toInternalString());
                key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    QuadKeys.Type.LatLong, new GeoCoordinate2d(
                        new Longitude(+180.0), new Latitude(+90.0)), (byte)1);
                Assert.IsTrue(new QuadKey(
                    QuadKeys.Type.LatLong, 1, 1, 1).EqualTo(key));
                Assert.AreEqual("1", key.toInternalString());
            }
        }

        [TestMethod]
        public void TestGetKeysFromLongitudeLatitudeBoundingBox()
        {
            {
                QuadKeyVector outKeys;
                outKeys = QuadKey.getKeysFromLongitudeLatitudeBoundingBox(
                    QuadKeys.Type.LatLong,
                    new GeoCoordinateBoundingBox2d(
                        new GeoCoordinate2d(
                            new Longitude(-180.0), new Latitude(+90.0)),
                         new GeoCoordinate2d(
                            new Longitude(+180.0), new Latitude(-90.0))),
                    (byte)0);
                Assert.AreEqual((byte)1, outKeys.Count);
                Assert.IsTrue(VectorContains(outKeys, new QuadKey(
                    QuadKeys.Type.LatLong, 0, 0, 0)));
            }

            {
                QuadKeyVector outKeys;
                outKeys = QuadKey.getKeysFromLongitudeLatitudeBoundingBox(
                    QuadKeys.Type.LatLong,
                    new GeoCoordinateBoundingBox2d(
                        new GeoCoordinate2d(
                            new Longitude(-180.0), new Latitude(+90.0)),
                        new GeoCoordinate2d(
                            new Longitude(+180.0), new Latitude(-90.0))),
                    (byte)1);
                Assert.AreEqual((byte)4, outKeys.Count);
                Assert.IsTrue(VectorContains(outKeys, new QuadKey(
                    QuadKeys.Type.LatLong, 0, 0, 1)));
                Assert.IsTrue(VectorContains(outKeys, new QuadKey(
                    QuadKeys.Type.LatLong, 0, 1, 1)));
                Assert.IsTrue(VectorContains(outKeys, new QuadKey(
                    QuadKeys.Type.LatLong, 1, 0, 1)));
                Assert.IsTrue(VectorContains(outKeys, new QuadKey(
                    QuadKeys.Type.LatLong, 1, 1, 1)));
            }

            {
                QuadKeyVector outKeys;
                outKeys = QuadKey.getKeysFromLongitudeLatitudeBoundingBox(
                    QuadKeys.Type.LatLong,
                    new GeoCoordinateBoundingBox2d(
                        new GeoCoordinate2d(
                            new Longitude(-180.0), new Latitude(-0.1)),
                        new GeoCoordinate2d(
                            new Longitude(-0.1), new Latitude(+90.0))),
                    (byte)1);
                Assert.AreEqual(2, outKeys.Count);
                Assert.IsTrue(VectorContains(outKeys, new QuadKey(
                    QuadKeys.Type.LatLong, 0, 0, 1)));
                Assert.IsTrue(VectorContains(outKeys, new QuadKey(
                    QuadKeys.Type.LatLong, 1, 0, 1)));
            }

            {
                QuadKeyVector outKeys;
                outKeys = QuadKey.getKeysFromLongitudeLatitudeBoundingBox(
                    QuadKeys.Type.LatLong,
                    new GeoCoordinateBoundingBox2d(
                        new GeoCoordinate2d(
                            new Longitude(+0.0), new Latitude(-0.1)),
                        new GeoCoordinate2d(
                            new Longitude(+180.0), new Latitude(+90.0))),
                    (byte)1);
                Assert.AreEqual(2, outKeys.Count);
                Assert.IsTrue(VectorContains(outKeys, new QuadKey(
                    QuadKeys.Type.LatLong, 0, 1, 1)));
                Assert.IsTrue(VectorContains(outKeys, new QuadKey(
                    QuadKeys.Type.LatLong, 1, 1, 1)));
            }

            {
                QuadKeyVector outKeys;
                outKeys = QuadKey.getKeysFromLongitudeLatitudeBoundingBox(
                    QuadKeys.Type.LatLong,
                    new GeoCoordinateBoundingBox2d(
                        new GeoCoordinate2d(
                            new Longitude(-0.1), new Latitude(-0.1)),
                        new GeoCoordinate2d(
                            new Longitude(+0.1), new Latitude(+0.1))),
                    (byte)1);
                Assert.AreEqual(4, outKeys.Count);
                Assert.IsTrue(VectorContains(outKeys, new QuadKey(
                    QuadKeys.Type.LatLong, 0, 0, 1)));
                Assert.IsTrue(VectorContains(outKeys, new QuadKey(
                    QuadKeys.Type.LatLong, 0, 1, 1)));
                Assert.IsTrue(VectorContains(outKeys, new QuadKey(
                    QuadKeys.Type.LatLong, 1, 0, 1)));
                Assert.IsTrue(VectorContains(outKeys, new QuadKey(
                    QuadKeys.Type.LatLong, 1, 1, 1)));
            }
        }

        [TestMethod]
        public void TestKnownSampleOfLocations()
        {
            QuadKey key = new QuadKey();

            {
                key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    QuadKeys.Type.LatLong, new GeoCoordinate2d(
                        new Longitude(-122.4183), new Latitude(37.7750)),
                        (byte)1);
                Assert.AreEqual("0", key.toInternalString());
                key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    QuadKeys.Type.LatLong, new GeoCoordinate2d(
                    new Longitude(-122.4183), new Latitude(37.7750)),
                    (byte)2);
                Assert.AreEqual("02", key.toInternalString());
                key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    QuadKeys.Type.LatLong, new GeoCoordinate2d(
                        new Longitude(-122.4183), new Latitude(37.7750)),
                        (byte)3);
                Assert.AreEqual("021", key.toInternalString());
                key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    QuadKeys.Type.LatLong, new GeoCoordinate2d(
                        new Longitude(-122.4183), new Latitude(37.7750)),
                        (byte)4);
                Assert.AreEqual("0210", key.toInternalString());
            }

            {
                key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    QuadKeys.Type.LatLong, new GeoCoordinate2d(
                        new Longitude(+134.9), new Latitude(-67.6)), (byte)3);
                Assert.IsTrue(new QuadKey(
                    QuadKeys.Type.LatLong, 0, 6, 3).EqualTo(key));
                Assert.AreEqual("332", key.toInternalString());

                key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    QuadKeys.Type.LatLong, new GeoCoordinate2d(
                        new Longitude(+135.0), new Latitude(-67.5)), (byte)3);
                Assert.IsTrue(new QuadKey(
                    QuadKeys.Type.LatLong, 1, 7, 3).EqualTo(key));
                Assert.AreEqual("331", key.toInternalString());
            }
        }
    }
}
using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using QuadKeys;

namespace QuadKeyTests
{
    [TestClass]
    public class TestOsGeoSystem
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
            // Same thing as OsGeo Except for it allows for negative 1 in both
            // the rows and the columns. depth/col/row.
            QuadKey quadKey = new QuadKey(QuadKeys.Type.OsGeo, 3, 3, (byte)2);
            String fmt = quadKey.toInternalString();
            Assert.AreEqual("2/3/3", fmt);
            QuadKey quadKeyBack = QuadKey.fromInternalString(
                QuadKeys.Type.OsGeo, fmt);
            Assert.IsTrue(quadKey.EqualTo(quadKeyBack));

            fmt = "0/-1/-1";
            quadKeyBack = QuadKey.fromInternalString(QuadKeys.Type.OsGeo, fmt);
            Assert.IsTrue(new QuadKey(QuadKeys.Type.OsGeo, 0, 0,
                (byte)0).EqualTo(quadKeyBack));

            fmt = "1/1/-1";
            quadKeyBack = QuadKey.fromInternalString(QuadKeys.Type.OsGeo, fmt);
            Assert.IsTrue(new QuadKey(QuadKeys.Type.OsGeo, 0, 1,
                (byte)1).EqualTo(quadKeyBack));

            fmt = "1/-1/1";
            quadKeyBack = QuadKey.fromInternalString(QuadKeys.Type.OsGeo, fmt);
            Assert.IsTrue(new QuadKey(QuadKeys.Type.OsGeo, 1, 0,
                (byte)1).EqualTo(quadKeyBack));
        }

        [TestMethod]
        public void TestGetGeoCoordinateBounds2d()
        {
            QuadKey quadKey;
            GeoCoordinateBoundingBox2d bbox = new GeoCoordinateBoundingBox2d();

            { // Depth 0
                quadKey = QuadKey.fromInternalString(QuadKeys.Type.OsGeo,
                    "0/0/0");
                quadKey.getGeoCoordinateBounds2d(bbox);
                Assert.IsTrue(new Longitude(-180.0f).near(
                    bbox.lowerLeft().longitude(), 1e-4));
                Assert.IsTrue(new Latitude(-85.051132).near(
                    bbox.lowerLeft().latitude(), 1e-4));
                Assert.IsTrue(new Longitude(+180.0).near(
                    bbox.upperRight().longitude(), 1e-4));
                Assert.IsTrue(new Latitude(+85.051132).near(
                    bbox.upperRight().latitude(), 1e-4));
            }
        }

        [TestMethod]
        public void TestGetKeyFromLongitudeLatitudeAtDepthToBounds()
        {
            QuadKey quadKey;
            GeoCoordinateBoundingBox2d bbox = new GeoCoordinateBoundingBox2d();

            // Inclusion here consists of upper right. In the case along bottom
            // or left Inclusion points the opposite direction.
            //    X------X------X ur
            //    |      |      |
            //    |      |      |
            //    X------X------X
            //    |      |      |
            //    |      |      |
            //    X------X------X
            // Note that in this system bounds consist of all 4 sides, so two
            // quads will share the same boundary.
            quadKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                QuadKeys.Type.OsGeo,
                new GeoCoordinate2d(
                    new Longitude(-180.0), new Latitude(+85.05113877)),
                    (byte)0);
            Assert.IsTrue(new QuadKey(QuadKeys.Type.OsGeo, 0, 0,
                    (byte)0).EqualTo(quadKey));
            quadKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                QuadKeys.Type.OsGeo,
                new GeoCoordinate2d(
                    new Longitude(+180.0), new Latitude(+85.05113877)),
                    (byte)0);
            Assert.IsTrue(new QuadKey(QuadKeys.Type.OsGeo, 0, 0,
                    (byte)0).EqualTo(quadKey));
            quadKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                QuadKeys.Type.OsGeo,
                new GeoCoordinate2d(
                    new Longitude(+180.0), new Latitude(-85.05113877)),
                    (byte)0);
            Assert.IsTrue(new QuadKey(QuadKeys.Type.OsGeo, 0, 0,
                    (byte)0).EqualTo(quadKey));
            quadKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                QuadKeys.Type.OsGeo,
                new GeoCoordinate2d(
                    new Longitude(-180.0), new Latitude(-85.05113877)),
                    (byte)0);
            Assert.IsTrue(new QuadKey(QuadKeys.Type.OsGeo, 0, 0,
                    (byte)0).EqualTo(quadKey));
            quadKey.getGeoCoordinateBounds2d(bbox);
            Assert.IsTrue(bbox.lowerLeft().near(new GeoCoordinate2d(
            new Longitude(-180.0), new Latitude(-85.05113877)), 1e-4));
            Assert.IsTrue(bbox.upperRight().near(new GeoCoordinate2d(
            new Longitude(+180.0), new Latitude(+85.05113877)), 1e-4));

            quadKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                QuadKeys.Type.OsGeo,
                new GeoCoordinate2d(
                    new Longitude(+0.0), new Latitude(+0.00000000)),
                (byte)0);
            Assert.IsTrue(new QuadKey(QuadKeys.Type.OsGeo, 0, 0,
                    (byte)0).EqualTo(quadKey));

            quadKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                QuadKeys.Type.OsGeo,
                new GeoCoordinate2d(
                    new Longitude(-180.0), new Latitude(+85.05113877)),
                (byte)1);
            Assert.IsTrue(new QuadKey(QuadKeys.Type.OsGeo, 1, 0,
                (byte)1).EqualTo(quadKey));
            quadKey.getGeoCoordinateBounds2d(bbox);
            Assert.IsTrue(bbox.lowerLeft().near(new GeoCoordinate2d(
            new Longitude(-180.0), new Latitude(+0.00000000)), 1e-4));
            Assert.IsTrue(bbox.upperRight().near(new GeoCoordinate2d(
            new Longitude(+0.0), new Latitude(+85.05113877)), 1e-4));

            quadKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                QuadKeys.Type.OsGeo,
                new GeoCoordinate2d(
                    new Longitude(+180.0), new Latitude(+85.05113877)),
                (byte)1);
            Assert.IsTrue(new QuadKey(QuadKeys.Type.OsGeo, 1, 1,
                (byte)1).EqualTo(quadKey));
            quadKey.getGeoCoordinateBounds2d(bbox);
            Assert.IsTrue(bbox.lowerLeft().near(new GeoCoordinate2d(
            new Longitude(+0.0), new Latitude(+0.00000000)), 1e-4));
            Assert.IsTrue(bbox.upperRight().near(new GeoCoordinate2d(
            new Longitude(+180.0), new Latitude(+85.05113877)), 1e-4));

            quadKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                QuadKeys.Type.OsGeo,
                new GeoCoordinate2d(
                    new Longitude(+180.0), new Latitude(-85.05113877)),
                (byte)1);
            Assert.IsTrue(new QuadKey(QuadKeys.Type.OsGeo, 0, 1,
                (byte)1).EqualTo(quadKey));
            quadKey.getGeoCoordinateBounds2d(bbox);
            Assert.IsTrue(bbox.lowerLeft().near(new GeoCoordinate2d(
            new Longitude(+0.0), new Latitude(-85.05113877)), 1e-4));
            Assert.IsTrue(bbox.upperRight().near(new GeoCoordinate2d(
            new Longitude(+180.0), new Latitude(+0.00000000)), 1e-4));

            quadKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                QuadKeys.Type.OsGeo,
                new GeoCoordinate2d(
                    new Longitude(-180.0), new Latitude(-85.05113877)),
                (byte)1);
            Assert.IsTrue(new QuadKey(QuadKeys.Type.OsGeo, 0, 0,
                (byte)1).EqualTo(quadKey));
            quadKey.getGeoCoordinateBounds2d(bbox);
            Assert.IsTrue(bbox.lowerLeft().near(new GeoCoordinate2d(
            new Longitude(-180.0), new Latitude(-85.05113877)), 1e-4));
            Assert.IsTrue(bbox.upperRight().near(new GeoCoordinate2d(
            new Longitude(+0.0), new Latitude(+0.00000000)), 1e-4));

            quadKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                QuadKeys.Type.OsGeo,
                new GeoCoordinate2d(
                    new Longitude(-180.0), new Latitude(+0.00000000)),
                (byte)1);
            Assert.IsTrue(new QuadKey(QuadKeys.Type.OsGeo, 0, 0,
                (byte)1).EqualTo(quadKey));
            quadKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                QuadKeys.Type.OsGeo,
                new GeoCoordinate2d(
                    new Longitude(+0.0), new Latitude(+85.05113877)),
                (byte)1);
            Assert.IsTrue(new QuadKey(QuadKeys.Type.OsGeo, 1, 0,
                    (byte)1).EqualTo(quadKey));
            quadKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                QuadKeys.Type.OsGeo,
                new GeoCoordinate2d(
                    new Longitude(+180.0), new Latitude(+0.00000000)),
                (byte)1);
            Assert.IsTrue(new QuadKey(QuadKeys.Type.OsGeo, 0, 1,
                (byte)1).EqualTo(quadKey));
            quadKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                QuadKeys.Type.OsGeo,
                new GeoCoordinate2d(
                    new Longitude(+0.0), new Latitude(-85.05113877)),
                (byte)1);
            Assert.IsTrue(new QuadKey(QuadKeys.Type.OsGeo, 0, 0,
                (byte)1).EqualTo(quadKey));
            quadKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                QuadKeys.Type.OsGeo,
                new GeoCoordinate2d(
                    new Longitude(+0.0), new Latitude(+0.00000000)),
                (byte)1);
            Assert.IsTrue(new QuadKey(QuadKeys.Type.OsGeo, 0, 0,
                (byte)1).EqualTo(quadKey));

            // Note at depth 2 because of the Mercator projection the lines
            // of latitude are note perfect divisions by 2.
            quadKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                QuadKeys.Type.OsGeo,
                new GeoCoordinate2d(
                    new Longitude(-180.0), new Latitude(-85.05113877)),
                (byte)2);
            Assert.IsTrue(new QuadKey(QuadKeys.Type.OsGeo, 0, 0,
                (byte)2).EqualTo(quadKey));
            quadKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                QuadKeys.Type.OsGeo,
                new GeoCoordinate2d(
                    new Longitude(-180.0), new Latitude(-66.5133)),
                (byte)2);
            Assert.IsTrue(new QuadKey(QuadKeys.Type.OsGeo, 0, 0,
                (byte)2).EqualTo(quadKey));
            quadKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                QuadKeys.Type.OsGeo,
                new GeoCoordinate2d(
                    new Longitude(-180.0), new Latitude(-66.5132)),
                (byte)2);
            Assert.IsTrue(new QuadKey(QuadKeys.Type.OsGeo, 1, 0,
                (byte)2).EqualTo(quadKey));
            quadKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                QuadKeys.Type.OsGeo,
                new GeoCoordinate2d(
                    new Longitude(-180.0), new Latitude(+0.1)),
                (byte)2);
            Assert.IsTrue(new QuadKey(QuadKeys.Type.OsGeo, 2, 0,
                (byte)2).EqualTo(quadKey));
            quadKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                QuadKeys.Type.OsGeo,
                new GeoCoordinate2d(
                    new Longitude(-180.0), new Latitude(+66.5132)),
                (byte)2);
            Assert.IsTrue(new QuadKey(QuadKeys.Type.OsGeo, 2, 0,
                (byte)2).EqualTo(quadKey));
            quadKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                QuadKeys.Type.OsGeo,
                new GeoCoordinate2d(
                    new Longitude(-180.0), new Latitude(+66.5133)),
                (byte)2);
            Assert.IsTrue(new QuadKey(QuadKeys.Type.OsGeo, 3, 0,
                (byte)2).EqualTo(quadKey));
            quadKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                QuadKeys.Type.OsGeo,
                new GeoCoordinate2d(
                    new Longitude(-180.0), new Latitude(+85.05113877)),
                (byte)2);
            Assert.IsTrue(new QuadKey(QuadKeys.Type.OsGeo, 3, 0,
                (byte)2).EqualTo(quadKey));
            quadKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                QuadKeys.Type.OsGeo,
                new GeoCoordinate2d(
                    new Longitude(-90.0), new Latitude(-85.05113877)),
                (byte)2);
            Assert.IsTrue(new QuadKey(QuadKeys.Type.OsGeo, 0, 0,
                (byte)2).EqualTo(quadKey));
            quadKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                QuadKeys.Type.OsGeo,
                new GeoCoordinate2d(
                    new Longitude(-90.0), new Latitude(-66.5133)),
                (byte)2);
            Assert.IsTrue(new QuadKey(QuadKeys.Type.OsGeo, 0, 0,
                (byte)2).EqualTo(quadKey));
            quadKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                QuadKeys.Type.OsGeo,
                new GeoCoordinate2d(
                    new Longitude(-90.0), new Latitude(-66.5132)),
                (byte)2);
            Assert.IsTrue(new QuadKey(QuadKeys.Type.OsGeo, 1, 0,
                (byte)2).EqualTo(quadKey));
            quadKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                QuadKeys.Type.OsGeo,
                new GeoCoordinate2d(
                    new Longitude(-90.0), new Latitude(+0.1)),
                (byte)2);
            Assert.IsTrue(new QuadKey(QuadKeys.Type.OsGeo, 2, 0,
                (byte)2).EqualTo(quadKey));
            quadKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                QuadKeys.Type.OsGeo,
                new GeoCoordinate2d(
                    new Longitude(-90.0), new Latitude(+66.5132)),
                (byte)2);
            Assert.IsTrue(new QuadKey(QuadKeys.Type.OsGeo, 2, 0,
                (byte)2).EqualTo(quadKey));
            quadKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                QuadKeys.Type.OsGeo,
                new GeoCoordinate2d(
                    new Longitude(-90.0), new Latitude(+66.5133)),
                (byte)2);
            Assert.IsTrue(new QuadKey(QuadKeys.Type.OsGeo, 3, 0,
                (byte)2).EqualTo(quadKey));
            quadKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                QuadKeys.Type.OsGeo,
                new GeoCoordinate2d(
                    new Longitude(-90.0), new Latitude(+85.05113877)),
                (byte)2);
            Assert.IsTrue(new QuadKey(QuadKeys.Type.OsGeo, 3, 0,
                (byte)2).EqualTo(quadKey));
            quadKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                QuadKeys.Type.OsGeo,
                new GeoCoordinate2d(
                    new Longitude(-89.9), new Latitude(-85.05113877)),
                (byte)2);
            Assert.IsTrue(new QuadKey(QuadKeys.Type.OsGeo, 0, 1,
                (byte)2).EqualTo(quadKey));
            quadKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                QuadKeys.Type.OsGeo,
                new GeoCoordinate2d(
                    new Longitude(-89.9), new Latitude(-66.5133)),
                (byte)2);
            Assert.IsTrue(new QuadKey(QuadKeys.Type.OsGeo, 0, 1,
                (byte)2).EqualTo(quadKey));
            quadKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                QuadKeys.Type.OsGeo,
                new GeoCoordinate2d(
                    new Longitude(-89.9), new Latitude(-66.5132)),
                (byte)2);
            Assert.IsTrue(new QuadKey(QuadKeys.Type.OsGeo, 1, 1,
                (byte)2).EqualTo(quadKey));
            quadKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                QuadKeys.Type.OsGeo,
                new GeoCoordinate2d(
                    new Longitude(-89.9), new Latitude(+0.1)),
                (byte)2);
            Assert.IsTrue(new QuadKey(QuadKeys.Type.OsGeo, 2, 1,
                (byte)2).EqualTo(quadKey));
            quadKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                QuadKeys.Type.OsGeo,
                new GeoCoordinate2d(
                    new Longitude(-89.9), new Latitude(+66.5132)),
                (byte)2);
            Assert.IsTrue(new QuadKey(QuadKeys.Type.OsGeo, 2, 1,
                (byte)2).EqualTo(quadKey));
            quadKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                QuadKeys.Type.OsGeo,
                new GeoCoordinate2d(
                    new Longitude(-89.9), new Latitude(+66.5133)),
                (byte)2);
            Assert.IsTrue(new QuadKey(QuadKeys.Type.OsGeo, 3, 1,
                (byte)2).EqualTo(quadKey));
            quadKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                QuadKeys.Type.OsGeo,
                new GeoCoordinate2d(
                    new Longitude(-89.9), new Latitude(+85.05113877)),
                (byte)2);
            Assert.IsTrue(new QuadKey(QuadKeys.Type.OsGeo, 3, 1,
                (byte)2).EqualTo(quadKey));
            quadKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                QuadKeys.Type.OsGeo,
                new GeoCoordinate2d(
                    new Longitude(+0.0), new Latitude(-85.05113877)),
                (byte)2);
            Assert.IsTrue(new QuadKey(QuadKeys.Type.OsGeo, 0, 1,
                (byte)2).EqualTo(quadKey));
            quadKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                QuadKeys.Type.OsGeo,
                new GeoCoordinate2d(
                    new Longitude(+0.0), new Latitude(-66.5133)),
                (byte)2);
            Assert.IsTrue(new QuadKey(QuadKeys.Type.OsGeo, 0, 1,
                (byte)2).EqualTo(quadKey));
            quadKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                QuadKeys.Type.OsGeo,
                new GeoCoordinate2d(
                    new Longitude(+0.0), new Latitude(-66.5132)),
                (byte)2);
            Assert.IsTrue(new QuadKey(QuadKeys.Type.OsGeo, 1, 1,
                (byte)2).EqualTo(quadKey));
            quadKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                QuadKeys.Type.OsGeo,
                new GeoCoordinate2d(
                    new Longitude(+0.0), new Latitude(+0.1)),
                (byte)2);
            Assert.IsTrue(new QuadKey(QuadKeys.Type.OsGeo, 2, 1,
                    (byte)2).EqualTo(quadKey));
            quadKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                QuadKeys.Type.OsGeo,
                new GeoCoordinate2d(
                    new Longitude(+0.0), new Latitude(+66.5132)),
                (byte)2);
            Assert.IsTrue(new QuadKey(QuadKeys.Type.OsGeo, 2, 1,
                (byte)2).EqualTo(quadKey));
            quadKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                QuadKeys.Type.OsGeo,
                new GeoCoordinate2d(
                    new Longitude(+0.0), new Latitude(+66.5133)),
                (byte)2);
            Assert.IsTrue(new QuadKey(QuadKeys.Type.OsGeo, 3, 1,
                (byte)2).EqualTo(quadKey));
            quadKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                QuadKeys.Type.OsGeo,
                new GeoCoordinate2d(
                    new Longitude(+0.0), new Latitude(+85.05113877)),
                (byte)2);
            Assert.IsTrue(new QuadKey(QuadKeys.Type.OsGeo, 3, 1,
                (byte)2).EqualTo(quadKey));
            quadKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                QuadKeys.Type.OsGeo,
                new GeoCoordinate2d(
                    new Longitude(+0.1), new Latitude(-85.05113877)),
                (byte)2);
            Assert.IsTrue(new QuadKey(QuadKeys.Type.OsGeo, 0, 2,
                (byte)2).EqualTo(quadKey));
            quadKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                QuadKeys.Type.OsGeo,
                new GeoCoordinate2d(
                    new Longitude(+0.1), new Latitude(-66.5133)),
                (byte)2);
            Assert.IsTrue(new QuadKey(QuadKeys.Type.OsGeo, 0, 2,
                (byte)2).EqualTo(quadKey));
            quadKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                QuadKeys.Type.OsGeo,
                new GeoCoordinate2d(
                    new Longitude(+0.1), new Latitude(-66.5132)),
                (byte)2);
            Assert.IsTrue(new QuadKey(QuadKeys.Type.OsGeo, 1, 2,
                (byte)2).EqualTo(quadKey));
            quadKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                QuadKeys.Type.OsGeo,
                new GeoCoordinate2d(
                    new Longitude(+0.1), new Latitude(+0.1)),
                (byte)2);
            Assert.IsTrue(new QuadKey(QuadKeys.Type.OsGeo, 2, 2,
                (byte)2).EqualTo(quadKey));
            quadKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                QuadKeys.Type.OsGeo,
                new GeoCoordinate2d(
                    new Longitude(+0.1), new Latitude(+66.5132)),
                (byte)2);
            Assert.IsTrue(new QuadKey(QuadKeys.Type.OsGeo, 2, 2,
                (byte)2).EqualTo(quadKey));
            quadKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                QuadKeys.Type.OsGeo,
                new GeoCoordinate2d(
                    new Longitude(+0.1), new Latitude(+66.5133)),
                (byte)2);
            Assert.IsTrue(new QuadKey(QuadKeys.Type.OsGeo, 3, 2,
                (byte)2).EqualTo(quadKey));
            quadKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                QuadKeys.Type.OsGeo,
                new GeoCoordinate2d(
                    new Longitude(+0.1), new Latitude(+85.05113877)),
                (byte)2);
            Assert.IsTrue(new QuadKey(QuadKeys.Type.OsGeo, 3, 2,
                (byte)2).EqualTo(quadKey));
            quadKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                QuadKeys.Type.OsGeo,
                new GeoCoordinate2d(
                    new Longitude(+90.0), new Latitude(-85.05113877)),
                (byte)2);
            Assert.IsTrue(new QuadKey(QuadKeys.Type.OsGeo, 0, 2,
                (byte)2).EqualTo(quadKey));
            quadKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                QuadKeys.Type.OsGeo,
                new GeoCoordinate2d(
                    new Longitude(+90.0), new Latitude(-66.5133)),
                (byte)2);
            Assert.IsTrue(new QuadKey(QuadKeys.Type.OsGeo, 0, 2,
                (byte)2).EqualTo(quadKey));
            quadKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                QuadKeys.Type.OsGeo,
                new GeoCoordinate2d(
                    new Longitude(+90.0), new Latitude(-66.5132)),
                (byte)2);
            Assert.IsTrue(new QuadKey(QuadKeys.Type.OsGeo, 1, 2,
                (byte)2).EqualTo(quadKey));
            quadKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                QuadKeys.Type.OsGeo,
                new GeoCoordinate2d(
                    new Longitude(+90.0), new Latitude(+0.1)),
                (byte)2);
            Assert.IsTrue(new QuadKey(QuadKeys.Type.OsGeo, 2, 2,
                (byte)2).EqualTo(quadKey));
            quadKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                QuadKeys.Type.OsGeo,
                new GeoCoordinate2d(
                    new Longitude(+90.0), new Latitude(+66.5132)),
                (byte)2);
            Assert.IsTrue(new QuadKey(QuadKeys.Type.OsGeo, 2, 2,
                (byte)2).EqualTo(quadKey));
            quadKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                QuadKeys.Type.OsGeo,
                new GeoCoordinate2d(
                    new Longitude(+90.0), new Latitude(+66.5133)),
                (byte)2);
            Assert.IsTrue(new QuadKey(QuadKeys.Type.OsGeo, 3, 2,
                (byte)2).EqualTo(quadKey));
            quadKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                QuadKeys.Type.OsGeo,
                new GeoCoordinate2d(
                    new Longitude(+90.0), new Latitude(+85.05113877)),
                (byte)2);
            Assert.IsTrue(new QuadKey(QuadKeys.Type.OsGeo, 3, 2,
                (byte)2).EqualTo(quadKey));
            quadKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                QuadKeys.Type.OsGeo,
                new GeoCoordinate2d(
                    new Longitude(+90.1), new Latitude(-85.05113877)),
                (byte)2);
            Assert.IsTrue(new QuadKey(QuadKeys.Type.OsGeo, 0, 3,
                (byte)2).EqualTo(quadKey));
            quadKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                QuadKeys.Type.OsGeo,
                new GeoCoordinate2d(
                    new Longitude(+90.1), new Latitude(-66.5133)),
                (byte)2);
            Assert.IsTrue(new QuadKey(QuadKeys.Type.OsGeo, 0, 3,
                (byte)2).EqualTo(quadKey));
            quadKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                QuadKeys.Type.OsGeo,
                new GeoCoordinate2d(
                    new Longitude(+90.1), new Latitude(-66.5132)),
                (byte)2);
            Assert.IsTrue(new QuadKey(QuadKeys.Type.OsGeo, 1, 3,
                (byte)2).EqualTo(quadKey));
            quadKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                QuadKeys.Type.OsGeo,
                new GeoCoordinate2d(
                    new Longitude(+90.1), new Latitude(+0.1)),
                (byte)2);
            Assert.IsTrue(new QuadKey(QuadKeys.Type.OsGeo, 2, 3,
                (byte)2).EqualTo(quadKey));
            quadKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                QuadKeys.Type.OsGeo,
                new GeoCoordinate2d(
                    new Longitude(+90.1), new Latitude(+66.5132)),
                (byte)2);
            Assert.IsTrue(new QuadKey(QuadKeys.Type.OsGeo, 2, 3,
                (byte)2).EqualTo(quadKey));
            quadKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                QuadKeys.Type.OsGeo,
                new GeoCoordinate2d(
                    new Longitude(+90.1), new Latitude(+66.5133)),
                (byte)2);
            Assert.IsTrue(new QuadKey(QuadKeys.Type.OsGeo, 3, 3,
                (byte)2).EqualTo(quadKey));
            quadKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                QuadKeys.Type.OsGeo,
                new GeoCoordinate2d(
                    new Longitude(+90.1), new Latitude(+85.05113877)),
                (byte)2);
            Assert.IsTrue(new QuadKey(QuadKeys.Type.OsGeo, 3, 3,
                (byte)2).EqualTo(quadKey));
            quadKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                QuadKeys.Type.OsGeo,
                new GeoCoordinate2d(
                    new Longitude(+180.0), new Latitude(-85.05113877)),
                (byte)2);
            Assert.IsTrue(new QuadKey(QuadKeys.Type.OsGeo, 0, 3,
                (byte)2).EqualTo(quadKey));
            quadKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                QuadKeys.Type.OsGeo,
                new GeoCoordinate2d(
                    new Longitude(+180.0), new Latitude(-66.5133)),
                (byte)2);
            Assert.IsTrue(new QuadKey(QuadKeys.Type.OsGeo, 0, 3,
                (byte)2).EqualTo(quadKey));
            quadKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                QuadKeys.Type.OsGeo,
                new GeoCoordinate2d(
                    new Longitude(+180.0), new Latitude(-66.5132)),
                (byte)2);
            Assert.IsTrue(new QuadKey(QuadKeys.Type.OsGeo, 1, 3,
                (byte)2).EqualTo(quadKey));
            quadKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                QuadKeys.Type.OsGeo,
                new GeoCoordinate2d(
                    new Longitude(+180.0), new Latitude(+0.1)),
                (byte)2);
            Assert.IsTrue(new QuadKey(QuadKeys.Type.OsGeo, 2, 3,
                (byte)2).EqualTo(quadKey));
            quadKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                QuadKeys.Type.OsGeo,
                new GeoCoordinate2d(
                    new Longitude(+180.0), new Latitude(+66.5132)),
                (byte)2);
            Assert.IsTrue(new QuadKey(QuadKeys.Type.OsGeo, 2, 3,
                (byte)2).EqualTo(quadKey));
            quadKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                QuadKeys.Type.OsGeo,
                new GeoCoordinate2d(
                    new Longitude(+180.0), new Latitude(+66.5133)),
                (byte)2);
            Assert.IsTrue(new QuadKey(QuadKeys.Type.OsGeo, 3, 3,
                (byte)2).EqualTo(quadKey));
            quadKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                QuadKeys.Type.OsGeo,
                new GeoCoordinate2d(
                    new Longitude(+180.0), new Latitude(+85.05113877)),
                (byte)2);
            Assert.IsTrue(new QuadKey(QuadKeys.Type.OsGeo, 3, 3,
                (byte)2).EqualTo(quadKey));
        }

        [TestMethod]
        public void TestGetKeysFromLongitudeLatitudeBoundingBox()
        {
            QuadKeyVector quadKeys;

            quadKeys = QuadKey.getKeysFromLongitudeLatitudeBoundingBox(
                QuadKeys.Type.OsGeo, new GeoCoordinateBoundingBox2d(
                    new GeoCoordinate2d(
                        new Longitude(+0.0),
                        new Latitude(-0.10000000)),
                    new GeoCoordinate2d(
                        new Longitude(+0.1),
                        new Latitude(+0.10000000))),
                (byte)0);
            Assert.AreEqual(1, quadKeys.Count);
            Assert.IsTrue(VectorContains(quadKeys, new QuadKey(
                QuadKeys.Type.OsGeo, 0, 0, (byte)0)));

            quadKeys = QuadKey.getKeysFromLongitudeLatitudeBoundingBox(
                QuadKeys.Type.OsGeo, new GeoCoordinateBoundingBox2d(
                    new GeoCoordinate2d(
                        new Longitude(-180.0),
                        new Latitude(-85.05113877)),
                    new GeoCoordinate2d(
                        new Longitude(+180.0),
                        new Latitude(+85.05113877))),
                (byte)1);
            Assert.AreEqual(4, quadKeys.Count);
            Assert.IsTrue(VectorContains(quadKeys, new QuadKey(
                    QuadKeys.Type.OsGeo, 0, 0, (byte)1)));
            Assert.IsTrue(VectorContains(quadKeys, new QuadKey(
                    QuadKeys.Type.OsGeo, 0, 1, (byte)1)));
            Assert.IsTrue(VectorContains(quadKeys, new QuadKey(
                QuadKeys.Type.OsGeo, 1, 0, (byte)1)));
            Assert.IsTrue(VectorContains(quadKeys, new QuadKey(
                QuadKeys.Type.OsGeo, 1, 1, (byte)1)));

            quadKeys = QuadKey.getKeysFromLongitudeLatitudeBoundingBox(
                QuadKeys.Type.OsGeo, new GeoCoordinateBoundingBox2d(
                    new GeoCoordinate2d(
                        new Longitude(-180.0),
                        new Latitude(-85.05113877)),
                    new GeoCoordinate2d(
                        new Longitude(+0.0),
                        new Latitude(+85.05113877))),
                (byte)1);
            Assert.AreEqual(2, quadKeys.Count);
            Assert.IsTrue(VectorContains(quadKeys, new QuadKey(
                QuadKeys.Type.OsGeo, 1, 0, (byte)1)));
            Assert.IsTrue(VectorContains(quadKeys, new QuadKey(
                QuadKeys.Type.OsGeo, 0, 0, (byte)1)));

            quadKeys = QuadKey.getKeysFromLongitudeLatitudeBoundingBox(
                QuadKeys.Type.OsGeo, new GeoCoordinateBoundingBox2d(
                    new GeoCoordinate2d(
                        new Longitude(+0.1),
                        new Latitude(-85.05113877)),
                    new GeoCoordinate2d(
                        new Longitude(+180.0),
                        new Latitude(+85.05113877))),
                (byte)1);
            Assert.AreEqual(2, quadKeys.Count);
            Assert.IsTrue(VectorContains(quadKeys, new QuadKey(
                QuadKeys.Type.OsGeo, 1, 1, (byte)1)));
            Assert.IsTrue(VectorContains(quadKeys, new QuadKey(
                QuadKeys.Type.OsGeo, 0, 1, (byte)1)));

            quadKeys = QuadKey.getKeysFromLongitudeLatitudeBoundingBox(
                QuadKeys.Type.OsGeo, new GeoCoordinateBoundingBox2d(
                    new GeoCoordinate2d(
                        new Longitude(-180.0),
                        new Latitude(-85.05113877)),
                    new GeoCoordinate2d(
                        new Longitude(+0.0),
                        new Latitude(+0.00000000))),
                (byte)1);
            Assert.AreEqual(1, quadKeys.Count);
            Assert.IsTrue(VectorContains(quadKeys, new QuadKey(
                QuadKeys.Type.OsGeo, 0, 0, (byte)1)));

            quadKeys = QuadKey.getKeysFromLongitudeLatitudeBoundingBox(
                QuadKeys.Type.OsGeo, new GeoCoordinateBoundingBox2d(
                    new GeoCoordinate2d(
                        new Longitude(-180.0),
                        new Latitude(+0.10000000)),
                    new GeoCoordinate2d(
                        new Longitude(+0.0),
                        new Latitude(+85.05113877))),
                (byte)1);
            Assert.AreEqual(1, quadKeys.Count);
            Assert.IsTrue(VectorContains(quadKeys, new QuadKey(
                QuadKeys.Type.OsGeo, 1, 0, (byte)1)));

            quadKeys = QuadKey.getKeysFromLongitudeLatitudeBoundingBox(
                QuadKeys.Type.OsGeo, new GeoCoordinateBoundingBox2d(
                    new GeoCoordinate2d(
                        new Longitude(+0.1),
                        new Latitude(-85.05113877)),
                    new GeoCoordinate2d(
                        new Longitude(+180.0),
                        new Latitude(+0.00000000))),
                (byte)1);
            Assert.AreEqual(1, quadKeys.Count);
            Assert.IsTrue(VectorContains(quadKeys, new QuadKey(
                QuadKeys.Type.OsGeo, 0, 1, (byte)1)));

            quadKeys = QuadKey.getKeysFromLongitudeLatitudeBoundingBox(
                QuadKeys.Type.OsGeo, new GeoCoordinateBoundingBox2d(
                    new GeoCoordinate2d(
                        new Longitude(+0.1),
                        new Latitude(+0.10000000)),
                    new GeoCoordinate2d(
                        new Longitude(+180.0),
                        new Latitude(+85.05113877))),
                (byte)1);
            Assert.AreEqual(1, quadKeys.Count);
            Assert.IsTrue(VectorContains(quadKeys, new QuadKey(
                    QuadKeys.Type.OsGeo, 1, 1, (byte)1)));
        }

        [TestMethod]
        public void TestSelecetedCities()
        {
            // TODO: Implement Tests. Taken from Earthscape. No tests there.
        }
    }
}

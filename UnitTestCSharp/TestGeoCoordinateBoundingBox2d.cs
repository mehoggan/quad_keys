using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using QuadKeys;

namespace QuadKeyTests
{
    [TestClass]
    public class TestGeoCoordinateBoundingBox2dTest
    {
        [TestMethod]
        public void TestDefaultCtor()
        {
            GeoCoordinateBoundingBox2d empty =
                new GeoCoordinateBoundingBox2d();
            Assert.IsFalse(empty.isValid());
            Assert.IsFalse(empty.contains(
                new GeoCoordinate2d(new Longitude(0.0), new Latitude(0.0))));
        }

        [TestMethod]
        public void TestCtorStandardConstruction()
        {
            { // Lower Left / Upper Right Construction
                GeoCoordinateBoundingBox2d geoBox =
                    new GeoCoordinateBoundingBox2d(
                        new GeoCoordinate2d(
                            new Longitude(0.0), new Latitude(0.0)),
                        new GeoCoordinate2d(
                            new Longitude(180.0), new Latitude(90.0)));

                Assert.IsTrue(new GeoCoordinate2d(new Longitude(0.0),
                    new Latitude(0.0)).EqualTo(geoBox.lowerLeft()));
                Assert.IsTrue(new GeoCoordinate2d(new Longitude(180.0),
                    new Latitude(90.0)).EqualTo(geoBox.upperRight()));
                Assert.IsTrue(geoBox.isValid());
            }

            { // Upper Left / Lower Right Construction
                GeoCoordinateBoundingBox2d geoBox =
                    new GeoCoordinateBoundingBox2d(
                        new GeoCoordinate2d(
                            new Longitude(0.0), new Latitude(90.0)),
                        new GeoCoordinate2d(
                            new Longitude(180.0), new Latitude(0.0)));

                Assert.IsTrue(new GeoCoordinate2d(
                    new Longitude(0.0), new Latitude(0.0)).EqualTo(
                    geoBox.lowerLeft()));
                Assert.IsTrue(new GeoCoordinate2d(
                    new Longitude(180.0), new Latitude(90.0)).EqualTo(
                    geoBox.upperRight()));
                Assert.IsTrue(geoBox.isValid());
            }

            { // Upper Right / Lower Left Construction
                GeoCoordinateBoundingBox2d geoBox =
                    new GeoCoordinateBoundingBox2d(
                        new GeoCoordinate2d(
                            new Longitude(180.0), new Latitude(0.0)),
                        new GeoCoordinate2d(
                            new Longitude(0.0), new Latitude(90.0)));

                Assert.IsTrue(new GeoCoordinate2d(new Longitude(0.0),
                    new Latitude(0.0)).EqualTo(geoBox.lowerLeft()));
                Assert.IsTrue(new GeoCoordinate2d(new Longitude(180.0),
                    new Latitude(90.0)).EqualTo(geoBox.upperRight()));
                Assert.IsTrue(geoBox.isValid());
            }

            { // Lower Right / Upper Left Construction
                GeoCoordinateBoundingBox2d geoBox =
                    new GeoCoordinateBoundingBox2d(
                        new GeoCoordinate2d(
                            new Longitude(180.0), new Latitude(0.0)),
                        new GeoCoordinate2d(
                            new Longitude(0.0), new Latitude(90.0)));

                Assert.IsTrue(new GeoCoordinate2d(new Longitude(0.0),
                    new Latitude(0.0)).EqualTo(geoBox.lowerLeft()));
                Assert.IsTrue(new GeoCoordinate2d(new Longitude(180.0),
                    new Latitude(90.0)).EqualTo(geoBox.upperRight()));
                Assert.IsTrue(geoBox.isValid());
            }
        }

        [TestMethod]
        public void TestCtorLinearBoxAndPoint()
        {
            { // Horizontal
                GeoCoordinateBoundingBox2d geoBox =
                    new GeoCoordinateBoundingBox2d(
                        new GeoCoordinate2d(
                            new Longitude(0.0), new Latitude(0.0)),
                        new GeoCoordinate2d(
                            new Longitude(0.0), new Latitude(90.0)));

                Assert.IsTrue(new GeoCoordinate2d(new Longitude(0.0),
                    new Latitude(0.0)).EqualTo(geoBox.lowerLeft()));
                Assert.IsTrue(new GeoCoordinate2d(new Longitude(0.0),
                    new Latitude(90.0)).EqualTo(geoBox.upperRight()));
                Assert.IsTrue(geoBox.isValid());
            }

            { // Vertical
                GeoCoordinateBoundingBox2d geoBox =
                    new GeoCoordinateBoundingBox2d(
                        new GeoCoordinate2d(
                            new Longitude(0.0), new Latitude(0.0)),
                        new GeoCoordinate2d(
                            new Longitude(180.0), new Latitude(0.0)));

                Assert.IsTrue(new GeoCoordinate2d(new Longitude(0.0),
                    new Latitude(0.0)).EqualTo(geoBox.lowerLeft()));
                Assert.IsTrue(new GeoCoordinate2d(new Longitude(180.0),
                    new Latitude(0.0)).EqualTo(geoBox.upperRight()));
                Assert.IsTrue(geoBox.isValid());
            }

            { // Point
                GeoCoordinateBoundingBox2d geoBox =
                    new GeoCoordinateBoundingBox2d(
                        new GeoCoordinate2d(
                            new Longitude(0.0), new Latitude(0.0)),
                        new GeoCoordinate2d(
                            new Longitude(0.0), new Latitude(0.0)));
                Assert.IsTrue(geoBox.isValid());
            }
        }

        [TestMethod]
        public void TestContainsOrNot()
        {
            {
                GeoCoordinateBoundingBox2d geoBox =
                    new GeoCoordinateBoundingBox2d(
                        new GeoCoordinate2d(
                            new Longitude(90.0), new Latitude(45.0)),
                        new GeoCoordinate2d(
                            new Longitude(-90.0), new Latitude(-45.0)));

                Assert.IsTrue(geoBox.isValid());

                Assert.IsTrue(geoBox.contains(new GeoCoordinate2d(
                    new Longitude(0.0), new Latitude(0.0))));

                Assert.IsTrue(geoBox.contains(new GeoCoordinate2d(
                    new Longitude(90.0), new Latitude(45.0))));
                Assert.IsTrue(geoBox.contains(new GeoCoordinate2d(
                    new Longitude(90.0), new Latitude(-45.0))));
                Assert.IsTrue(geoBox.contains(new GeoCoordinate2d(
                    new Longitude(-90.0), new Latitude(-45.0))));
                Assert.IsTrue(geoBox.contains(new GeoCoordinate2d(
                    new Longitude(-90.0), new Latitude(45.0))));

                Assert.IsFalse(geoBox.contains(new GeoCoordinate2d(
                    new Longitude(90.01), new Latitude(45.01))));
                Assert.IsFalse(geoBox.contains(new GeoCoordinate2d(
                    new Longitude(90.01), new Latitude(-45.01))));
                Assert.IsFalse(geoBox.contains(new GeoCoordinate2d(
                    new Longitude(-90.01), new Latitude(-45.01))));
                Assert.IsFalse(geoBox.contains(new GeoCoordinate2d(
                    new Longitude(-90.01), new Latitude(45.01))));
            }

            {
                GeoCoordinateBoundingBox2d geoBox =
                    new GeoCoordinateBoundingBox2d(
                        new GeoCoordinate2d(
                            new Longitude(90.0), new Latitude(45.0)),
                        new GeoCoordinate2d(
                            new Longitude(0.1), new Latitude(0.1)));

                Assert.IsTrue(new GeoCoordinate2d(new Longitude(0.1),
                    new Latitude(0.1)).EqualTo(geoBox.lowerLeft()));
                Assert.IsTrue(new GeoCoordinate2d(new Longitude(90.0),
                    new Latitude(45.0)).EqualTo(geoBox.upperRight()));

                Assert.IsTrue(geoBox.isValid());

                Assert.IsTrue(geoBox.contains(new GeoCoordinate2d(
                    new Longitude(90.0), new Latitude(45.0))));
                Assert.IsTrue(geoBox.contains(new GeoCoordinate2d(
                    new Longitude(90.0), new Latitude(0.1))));
                Assert.IsTrue(geoBox.contains(new GeoCoordinate2d(
                    new Longitude(0.1), new Latitude(0.1))));
                Assert.IsTrue(geoBox.contains(new GeoCoordinate2d(
                    new Longitude(0.1), new Latitude(45.0))));

                Assert.IsFalse(geoBox.contains(new GeoCoordinate2d(
                    new Longitude(90.01), new Latitude(45.01))));
                Assert.IsFalse(geoBox.contains(new GeoCoordinate2d(
                    new Longitude(90.01), new Latitude(0.0))));
                Assert.IsFalse(geoBox.contains(new GeoCoordinate2d(
                    new Longitude(0.0), new Latitude(0.0))));
                Assert.IsFalse(geoBox.contains(new GeoCoordinate2d(
                    new Longitude(0.0), new Latitude(45.01))));
            }
        }

        [TestMethod]
        public void TestGrowToContain()
        {
            {
                GeoCoordinateBoundingBox2d geoBox =
                    new GeoCoordinateBoundingBox2d(
                        new GeoCoordinate2d(
                            new Longitude(-90.0), new Latitude(-45.0)),
                        new GeoCoordinate2d(
                            new Longitude(90.0), new Latitude(45.0)));

                Assert.IsTrue(new GeoCoordinate2d(new Longitude(-90.0),
                    new Latitude(-45.0)).EqualTo(geoBox.lowerLeft()));
                Assert.IsTrue(new GeoCoordinate2d(new Longitude(90.0),
                    new Latitude(45.0)).EqualTo(geoBox.upperRight()));

                geoBox.growToContain(new GeoCoordinate2d(new Longitude(180.0),
                    new Latitude(90.0)));

                Assert.IsTrue(new GeoCoordinate2d(new Longitude(-90.0),
                    new Latitude(-45.0)).EqualTo(geoBox.lowerLeft()));
                Assert.IsTrue(new GeoCoordinate2d(new Longitude(180.0),
                    new Latitude(90.0)).EqualTo(geoBox.upperRight()));
            }

            {
                GeoCoordinateBoundingBox2d geoBox =
                    new GeoCoordinateBoundingBox2d(
                        new GeoCoordinate2d(
                            new Longitude(-90.0), new Latitude(-45.0)),
                        new GeoCoordinate2d(
                            new Longitude(90.0), new Latitude(45.0)));

                Assert.IsTrue(new GeoCoordinate2d(new Longitude(-90.0),
                    new Latitude(-45.0)).EqualTo(geoBox.lowerLeft()));
                Assert.IsTrue(new GeoCoordinate2d(new Longitude(90.0),
                    new Latitude(45.0)).EqualTo(geoBox.upperRight()));

                geoBox.growToContain(new GeoCoordinate2d(new Longitude(-180.0),
                    new Latitude(-90.0)));

                Assert.IsTrue(new GeoCoordinate2d(new Longitude(-180.0),
                    new Latitude(-90.0)).EqualTo(geoBox.lowerLeft()));
                Assert.IsTrue(new GeoCoordinate2d(new Longitude(90.0),
                    new Latitude(45.0)).EqualTo(geoBox.upperRight()));
            }

            {
                GeoCoordinateBoundingBox2d geoBox =
                    new GeoCoordinateBoundingBox2d(
                        new GeoCoordinate2d(
                            new Longitude(-90.0), new Latitude(-45.0)),
                        new GeoCoordinate2d(
                            new Longitude(90.0), new Latitude(45.0)));

                Assert.IsTrue(new GeoCoordinate2d(new Longitude(-90.0),
                    new Latitude(-45.0)).EqualTo(geoBox.lowerLeft()));
                Assert.IsTrue(new GeoCoordinate2d(new Longitude(90.0),
                    new Latitude(45.0)).EqualTo(geoBox.upperRight()));

                geoBox.growToContain(new GeoCoordinate2d(new Longitude(-180.0),
                    new Latitude(90.0)));

                Assert.IsTrue(new GeoCoordinate2d(new Longitude(-180.0),
                    new Latitude(-45.0)).EqualTo(geoBox.lowerLeft()));
                Assert.IsTrue(new GeoCoordinate2d(new Longitude(90.0),
                    new Latitude(90.0)).EqualTo(geoBox.upperRight()));
            }

            {
                GeoCoordinateBoundingBox2d geoBox =
                    new GeoCoordinateBoundingBox2d(
                        new GeoCoordinate2d(
                            new Longitude(-90.0), new Latitude(-45.0)),
                        new GeoCoordinate2d(
                            new Longitude(90.0), new Latitude(45.0)));

                Assert.IsTrue(new GeoCoordinate2d(new Longitude(-90.0),
                    new Latitude(-45.0)).EqualTo(geoBox.lowerLeft()));
                Assert.IsTrue(new GeoCoordinate2d(new Longitude(90.0),
                    new Latitude(45.0)).EqualTo(geoBox.upperRight()));

                geoBox.growToContain(new GeoCoordinate2d(new Longitude(180.0),
                    new Latitude(-90.0)));

                Assert.IsTrue(new GeoCoordinate2d(new Longitude(-90.0),
                    new Latitude(-90.0)).EqualTo(geoBox.lowerLeft()));
                Assert.IsTrue(new GeoCoordinate2d(new Longitude(180.0),
                    new Latitude(45.0)).EqualTo(geoBox.upperRight()));
            }

            {
                GeoCoordinateBoundingBox2d geoBox =
                    new GeoCoordinateBoundingBox2d(
                        new GeoCoordinate2d(
                            new Longitude(-90.0), new Latitude(-45.0)),
                        new GeoCoordinate2d(
                            new Longitude(90.0), new Latitude(45.0)));

                Assert.IsTrue(new GeoCoordinate2d(new Longitude(-90.0),
                    new Latitude(-45.0)).EqualTo(geoBox.lowerLeft()));
                Assert.IsTrue(new GeoCoordinate2d(new Longitude(90.0),
                    new Latitude(45.0)).EqualTo(geoBox.upperRight()));

                geoBox.growToContain(new GeoCoordinate2d(new Longitude(0.0),
                    new Latitude(0.0)));

                Assert.IsTrue(new GeoCoordinate2d(new Longitude(-90.0),
                    new Latitude(-45.0)).EqualTo(geoBox.lowerLeft()));
                Assert.IsTrue(new GeoCoordinate2d(new Longitude(90.0),
                    new Latitude(45.0)).EqualTo(geoBox.upperRight()));
            }
        }
    }
}
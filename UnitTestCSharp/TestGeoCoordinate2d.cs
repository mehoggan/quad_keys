using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using QuadKeys;

namespace QuadKeyTests
{
    [TestClass]
    public class TestGeoCoordinate2d
    {
        [TestMethod]
        public void TestDefaultCtor()
        {
            GeoCoordinate2d empty = new GeoCoordinate2d();
            Assert.IsTrue(new Longitude(0.0).EqualTo(empty.longitude()));
            Assert.IsTrue(new Latitude(0.0).EqualTo(empty.latitude()));
        }

        [TestMethod]
        public void TestCtor()
        {
            {
                GeoCoordinate2d coord = new GeoCoordinate2d(new Longitude(0.0),
                    new Latitude(0.0));
                Assert.IsTrue(new Longitude(0.0).EqualTo(coord.longitude()));
                Assert.IsTrue(new Latitude(0.0).EqualTo(coord.latitude()));
            }

            {
                GeoCoordinate2d coord = new GeoCoordinate2d(
                    new Longitude(-180.001), new Latitude(-95.0));
                Assert.IsTrue(new Longitude(-180.0).EqualTo(
                    coord.longitude()));
                Assert.IsTrue(new Latitude(-90.0).EqualTo(coord.latitude()));
            }

            {
                GeoCoordinate2d coord = new GeoCoordinate2d(
                    new Longitude(-180.001), new Latitude(95.0));
                Assert.IsTrue(new Longitude(-180.0).EqualTo(
                    coord.longitude()));
                Assert.IsTrue(new Latitude(90.0).EqualTo(coord.latitude()));
            }

            {
                GeoCoordinate2d coord = new GeoCoordinate2d(
                    new Longitude(180.001), new Latitude(95.0));
                Assert.IsTrue(new Longitude(180.0).EqualTo(coord.longitude()));
                Assert.IsTrue(new Latitude(90.0).EqualTo(coord.latitude()));
            }

            {
                GeoCoordinate2d coord = new GeoCoordinate2d(
                    new Longitude(180.001), new Latitude(-95.0));
                Assert.IsTrue(new Longitude(180.0).EqualTo(coord.longitude()));
                Assert.IsTrue(new Latitude(-90.0).EqualTo(coord.latitude()));
            }
        }

        [TestMethod]
        public void TestNear()
        {
            {
                Longitude lon = new Longitude(0.001);
                Assert.IsTrue(lon.near(new Longitude(0.0009), 1e-3));
            }

            {
                Longitude lon = new Longitude(0.001);
                Assert.IsFalse(lon.near(new Longitude(0.0009), 1e-4));
            }

            {
                Latitude lat = new Latitude(0.001);
                Assert.IsTrue(lat.near(new Latitude(0.0009), 1e-3));
            }

            {
                Latitude lat = new Latitude(0.001);
                Assert.IsFalse(lat.near(new Latitude(0.0009), 1e-4));
            }

            {
                GeoCoordinate2d coord = new GeoCoordinate2d(
                    new Longitude(0.001), new Latitude(0.001));
                Assert.IsTrue(coord.near(new GeoCoordinate2d(
                    new Longitude(0.0009), new Latitude(0.0009)), 1e-3));
            }

            {
                GeoCoordinate2d coord = new GeoCoordinate2d(
                    new Longitude(0.001), new Latitude(0.001));
                Assert.IsFalse(coord.near(new GeoCoordinate2d(
                    new Longitude(0.001), new Latitude(0.0009)), 1e-4));
            }

            {
                GeoCoordinate2d  coord = new GeoCoordinate2d(
                    new Longitude(0.001), new Latitude(0.001));
                Assert.IsFalse(coord.near(new GeoCoordinate2d(
                    new Longitude(0.0009), new Latitude(0.001)), 1e-4));
            }
        }

        [TestMethod]
        public void TestOperatorLessThan()
        {
            GeoCoordinate2d sw = new GeoCoordinate2d(
                new Longitude(-0.1), new Latitude(-0.1));
            GeoCoordinate2d ne = new GeoCoordinate2d(
                new Longitude(+0.1), new Latitude(+0.1));

            Assert.IsTrue(sw.longitude().LessThan(ne.longitude()));
            Assert.IsTrue(sw.latitude().LessThan(ne.latitude()));
        }

        [TestMethod]
        public void TestOperatorLessThanOrEqual()
        {
            {
                GeoCoordinate2d sw = new GeoCoordinate2d(
                    new Longitude(-0.1), new Latitude(-0.1));
                GeoCoordinate2d ne = new GeoCoordinate2d(
                    new Longitude(+0.1), new Latitude(+0.1));

                Assert.IsTrue(sw.longitude().LessThanOrEqual(ne.longitude()));
                Assert.IsTrue(sw.latitude().LessThanOrEqual(ne.latitude()));
            }

            {
                GeoCoordinate2d sw = new GeoCoordinate2d(
                    new Longitude(-0.1), new Latitude(-0.1));
                GeoCoordinate2d ne = new GeoCoordinate2d(
                    new Longitude(-0.1), new Latitude(-0.1));

                Assert.IsTrue(sw.longitude().LessThanOrEqual(ne.longitude()));
                Assert.IsTrue(sw.latitude().LessThanOrEqual(ne.latitude()));
            }
        }

        [TestMethod]
        public void TestOperatorEqual()
        {
            GeoCoordinate2d sw = new GeoCoordinate2d(
                new Longitude(-0.1), new Latitude(-0.1));
            GeoCoordinate2d ne = new GeoCoordinate2d(
                new Longitude(-0.1), new Latitude(-0.1));

            Assert.IsTrue(sw.longitude().EqualTo(ne.longitude()));
            Assert.IsTrue(sw.latitude().EqualTo(ne.latitude()));
        }
    }
}
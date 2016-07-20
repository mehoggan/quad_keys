using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using QuadKeys;

namespace QuadKeyTests
{
    [TestClass]
    public class TestSystem
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
        }

        [TestMethod]
        public void TestGetGeoCoordinateBounds2d()
        {
        }

        [TestMethod]
        public void TestGetKeyFromLongitudeLatitudeAtDepthToBounds()
        {
        }

        [TestMethod]
        public void TestGetKeysFromLongitudeLatitudeBoundingBox()
        {
        }

        [TestMethod]
        public void TestSelecetedCities()
        {
        }
    }
}
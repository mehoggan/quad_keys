using System;
using System.Collections.Generic;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using QuadKeys;

namespace QuadKeyTests
{
    [TestClass]
    public class TestMortonSystem
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
            {
                QuadKey quadKey = new QuadKey(QuadKeys.Type.Morton, 0, 1, (byte)1);
                QuadKey ancestor = new QuadKey(QuadKeys.Type.Morton, 0, 0,
                    (byte)0);
                Assert.IsTrue(ancestor.EqualTo(quadKey.getAncestor((byte)1)));
                Assert.IsTrue(quadKey.getParent().EqualTo(quadKey.getAncestor(
                    (byte)1)));
            }
            {
                QuadKey quadKey = new QuadKey(QuadKeys.Type.Morton, 0, 0, (byte)1);
                QuadKey ancestor = new QuadKey(QuadKeys.Type.Morton, 0, 0,
                    (byte)0);
                Assert.IsTrue(ancestor.EqualTo(quadKey.getAncestor((byte)1)));
                Assert.IsTrue(quadKey.getParent().EqualTo(quadKey.getAncestor(
                    (byte)1)));
            }
            {
                QuadKey quadKey = new QuadKey(QuadKeys.Type.Morton, 1, 1, (byte)1);
                QuadKey ancestor = new QuadKey(QuadKeys.Type.Morton, 0, 0,
                    (byte)0);
                Assert.IsTrue(ancestor.EqualTo(quadKey.getAncestor((byte)1)));
            }
            {
                QuadKey quadKey = new QuadKey(QuadKeys.Type.Morton, 1, 2, (byte)1);
                QuadKey ancestor = new QuadKey(QuadKeys.Type.Morton, 0, 1,
                    (byte)0);
                Assert.IsTrue(ancestor.EqualTo(quadKey.getAncestor((byte)1)));
            }
            {
                QuadKey quadKey = new QuadKey(QuadKeys.Type.Morton, 0, 2, (byte)1);
                QuadKey ancestor = new QuadKey(QuadKeys.Type.Morton, 0, 1,
                    (byte)0);
                Assert.IsTrue(ancestor.EqualTo(quadKey.getAncestor((byte)1)));
            }
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
            QuadKeyVector testKeys;
            testKeys = new QuadKey(QuadKeys.Type.Morton, 0, 0,
                (byte)1).getSiblings();
            Assert.AreEqual(3, testKeys.Count);
            Assert.IsTrue(VectorContains(testKeys,
                new QuadKey(QuadKeys.Type.Morton, 1, 0, (byte)1)));
            Assert.IsTrue(VectorContains(testKeys,
                new QuadKey(QuadKeys.Type.Morton, 1, 1, (byte)1)));
            Assert.IsTrue(VectorContains(testKeys,
                new QuadKey(QuadKeys.Type.Morton, 0, 1, (byte)1)));
            testKeys = new QuadKey(QuadKeys.Type.Morton, 1, 3,
                (byte)1).getSiblings();
            Assert.AreEqual(3, testKeys.Count);
            Assert.IsTrue(VectorContains(testKeys,
                new QuadKey(QuadKeys.Type.Morton, 1, 2, (byte)1)));
            Assert.IsTrue(VectorContains(testKeys,
                new QuadKey(QuadKeys.Type.Morton, 0, 2, (byte)1)));
            Assert.IsTrue(VectorContains(testKeys,
                new QuadKey(QuadKeys.Type.Morton, 0, 3, (byte)1)));
        }

        [TestMethod]
        public void TestGetNeighbors()
        {
            QuadKeyVector testKeys;
            testKeys = new QuadKey().getNeighbors();
            Assert.IsTrue(testKeys.Count == 0);

            testKeys = new QuadKey(QuadKeys.Type.Morton, 0, 0,
                (byte)2).getNeighbors();
            Assert.AreEqual(5, testKeys.Count);
            Assert.IsTrue(VectorContains(testKeys,
                new QuadKey(QuadKeys.Type.Morton, 0, 1, (byte)2)));
            Assert.IsTrue(VectorContains(testKeys,
                new QuadKey(QuadKeys.Type.Morton, 1, 1, (byte)2)));
            Assert.IsTrue(VectorContains(testKeys,
                new QuadKey(QuadKeys.Type.Morton, 1, 0, (byte)2)));
            Assert.IsTrue(VectorContains(testKeys,
                new QuadKey(QuadKeys.Type.Morton, 0, 7, (byte)2)));
            Assert.IsTrue(VectorContains(testKeys,
                new QuadKey(QuadKeys.Type.Morton, 1, 7, (byte)2)));

            testKeys = new QuadKey(QuadKeys.Type.Morton, 0, 1,
                (byte)2).getNeighbors();
            Assert.AreEqual(5, testKeys.Count);
            Assert.IsTrue(VectorContains(testKeys,
                new QuadKey(QuadKeys.Type.Morton, 0, 0, (byte)2)));
            Assert.IsTrue(VectorContains(testKeys,
                new QuadKey(QuadKeys.Type.Morton, 1, 0, (byte)2)));
            Assert.IsTrue(VectorContains(testKeys,
                new QuadKey(QuadKeys.Type.Morton, 1, 1, (byte)2)));
            Assert.IsTrue(VectorContains(testKeys,
                new QuadKey(QuadKeys.Type.Morton, 1, 2, (byte)2)));
            Assert.IsTrue(VectorContains(testKeys,
                new QuadKey(QuadKeys.Type.Morton, 0, 2, (byte)2)));

            testKeys = new QuadKey(QuadKeys.Type.Morton, 0, 2,
                (byte)2).getNeighbors();
            Assert.AreEqual(5, testKeys.Count);
            Assert.IsTrue(VectorContains(testKeys,
                new QuadKey(QuadKeys.Type.Morton, 0, 1, (byte)2)));
            Assert.IsTrue(VectorContains(testKeys,
                new QuadKey(QuadKeys.Type.Morton, 1, 1, (byte)2)));
            Assert.IsTrue(VectorContains(testKeys,
                new QuadKey(QuadKeys.Type.Morton, 1, 2, (byte)2)));
            Assert.IsTrue(VectorContains(testKeys,
                new QuadKey(QuadKeys.Type.Morton, 1, 3, (byte)2)));
            Assert.IsTrue(VectorContains(testKeys,
                new QuadKey(QuadKeys.Type.Morton, 0, 3, (byte)2)));

            testKeys = new QuadKey(QuadKeys.Type.Morton, 0, 3,
                (byte)2).getNeighbors();
            Assert.AreEqual(5, testKeys.Count);
            Assert.IsTrue(VectorContains(testKeys,
                new QuadKey(QuadKeys.Type.Morton, 0, 2, (byte)2)));
            Assert.IsTrue(VectorContains(testKeys,
                new QuadKey(QuadKeys.Type.Morton, 1, 2, (byte)2)));
            Assert.IsTrue(VectorContains(testKeys,
                new QuadKey(QuadKeys.Type.Morton, 1, 3, (byte)2)));
            Assert.IsTrue(VectorContains(testKeys,
                new QuadKey(QuadKeys.Type.Morton, 1, 4, (byte)2)));
            Assert.IsTrue(VectorContains(testKeys,
                new QuadKey(QuadKeys.Type.Morton, 0, 4, (byte)2)));

            testKeys = new QuadKey(QuadKeys.Type.Morton, 0, 0,
                (byte)2).getNeighbors();
            Assert.AreEqual(5, testKeys.Count);
            Assert.IsTrue(VectorContains(testKeys,
                new QuadKey(QuadKeys.Type.Morton, 0, 1, (byte)2)));
            Assert.IsTrue(VectorContains(testKeys,
                new QuadKey(QuadKeys.Type.Morton, 1, 1, (byte)2)));
            Assert.IsTrue(VectorContains(testKeys,
                new QuadKey(QuadKeys.Type.Morton, 1, 0, (byte)2)));
            Assert.IsTrue(VectorContains(testKeys,
                new QuadKey(QuadKeys.Type.Morton, 1, 7, (byte)2)));
            Assert.IsTrue(VectorContains(testKeys,
                new QuadKey(QuadKeys.Type.Morton, 0, 7, (byte)2)));

            testKeys = new QuadKey(QuadKeys.Type.Morton, 3, 1,
                (byte)2).getNeighbors();
            Assert.AreEqual(5, testKeys.Count);
            Assert.IsTrue(VectorContains(testKeys,
                new QuadKey(QuadKeys.Type.Morton, 3, 0, (byte)2)));
            Assert.IsTrue(VectorContains(testKeys,
                new QuadKey(QuadKeys.Type.Morton, 2, 0, (byte)2)));
            Assert.IsTrue(VectorContains(testKeys,
                new QuadKey(QuadKeys.Type.Morton, 2, 1, (byte)2)));
            Assert.IsTrue(VectorContains(testKeys,
                new QuadKey(QuadKeys.Type.Morton, 2, 2, (byte)2)));
            Assert.IsTrue(VectorContains(testKeys,
                new QuadKey(QuadKeys.Type.Morton, 3, 2, (byte)2)));

            testKeys = new QuadKey(QuadKeys.Type.Morton, 3, 2,
                (byte)2).getNeighbors();
            Assert.AreEqual(5, testKeys.Count);
            Assert.IsTrue(VectorContains(testKeys,
                new QuadKey(QuadKeys.Type.Morton, 3, 1, (byte)2)));
            Assert.IsTrue(VectorContains(testKeys,
                new QuadKey(QuadKeys.Type.Morton, 2, 1, (byte)2)));
            Assert.IsTrue(VectorContains(testKeys,
                new QuadKey(QuadKeys.Type.Morton, 2, 2, (byte)2)));
            Assert.IsTrue(VectorContains(testKeys,
                new QuadKey(QuadKeys.Type.Morton, 2, 3, (byte)2)));
            Assert.IsTrue(VectorContains(testKeys,
                new QuadKey(QuadKeys.Type.Morton, 3, 3, (byte)2)));

            testKeys = new QuadKey(QuadKeys.Type.Morton, 3, 3,
                (byte)2).getNeighbors();
            Assert.AreEqual(5, testKeys.Count);
            Assert.IsTrue(VectorContains(testKeys,
                new QuadKey(QuadKeys.Type.Morton, 3, 2, (byte)2)));
            Assert.IsTrue(VectorContains(testKeys,
                new QuadKey(QuadKeys.Type.Morton, 2, 2, (byte)2)));
            Assert.IsTrue(VectorContains(testKeys,
                new QuadKey(QuadKeys.Type.Morton, 2, 3, (byte)2)));
            Assert.IsTrue(VectorContains(testKeys,
                new QuadKey(QuadKeys.Type.Morton, 2, 4, (byte)2)));
            Assert.IsTrue(VectorContains(testKeys,
                new QuadKey(QuadKeys.Type.Morton, 3, 4, (byte)2)));

            testKeys = new QuadKey(QuadKeys.Type.Morton, 4, 7,
                (byte)3).getNeighbors();
            Assert.AreEqual(8, testKeys.Count);
            Assert.IsTrue(VectorContains(testKeys,
                new QuadKey(QuadKeys.Type.Morton, 3, 7, (byte)3)));
            Assert.IsTrue(VectorContains(testKeys,
                new QuadKey(QuadKeys.Type.Morton, 3, 6, (byte)3)));
            Assert.IsTrue(VectorContains(testKeys,
                new QuadKey(QuadKeys.Type.Morton, 4, 6, (byte)3)));
            Assert.IsTrue(VectorContains(testKeys,
                new QuadKey(QuadKeys.Type.Morton, 5, 6, (byte)3)));
            Assert.IsTrue(VectorContains(testKeys,
                new QuadKey(QuadKeys.Type.Morton, 5, 7, (byte)3)));
            Assert.IsTrue(VectorContains(testKeys,
                new QuadKey(QuadKeys.Type.Morton, 5, 8, (byte)3)));
            Assert.IsTrue(VectorContains(testKeys,
                new QuadKey(QuadKeys.Type.Morton, 4, 8, (byte)3)));
            Assert.IsTrue(VectorContains(testKeys,
                new QuadKey(QuadKeys.Type.Morton, 3, 8, (byte)3)));

            testKeys = new QuadKey(QuadKeys.Type.Morton, 4, 0,
                (byte)3).getNeighbors();
            Assert.AreEqual(8, testKeys.Count);
            Assert.IsTrue(VectorContains(testKeys,
                new QuadKey(QuadKeys.Type.Morton, 3, 0, (byte)3)));
            Assert.IsTrue(VectorContains(testKeys,
                new QuadKey(QuadKeys.Type.Morton, 3, 1, (byte)3)));
            Assert.IsTrue(VectorContains(testKeys,
                new QuadKey(QuadKeys.Type.Morton, 4, 1, (byte)3)));
            Assert.IsTrue(VectorContains(testKeys,
                new QuadKey(QuadKeys.Type.Morton, 5, 1, (byte)3)));
            Assert.IsTrue(VectorContains(testKeys,
                new QuadKey(QuadKeys.Type.Morton, 5, 0, (byte)3)));
            Assert.IsTrue(VectorContains(testKeys,
                new QuadKey(QuadKeys.Type.Morton, 5, 15, (byte)3)));
            Assert.IsTrue(VectorContains(testKeys,
                new QuadKey(QuadKeys.Type.Morton, 4, 15, (byte)3)));
            Assert.IsTrue(VectorContains(testKeys,
                new QuadKey(QuadKeys.Type.Morton, 3, 15, (byte)3)));

            testKeys = new QuadKey(QuadKeys.Type.Morton, 0, 0,
                (byte)0).getNeighbors();
            Assert.AreEqual(0, testKeys.Count);
        }

        [TestMethod]
        public void TestFromStringToString()
        {
            // X ==> Unused
            // O ==> Used but never set
            // (0,1) ==> Binary digits
            QuadKey quadKeyBack;

            QuadKey quadKey = new QuadKey(QuadKeys.Type.Morton,
                0, 0, (byte)0);
            String fmt = quadKey.toInternalString();
            Assert.AreEqual("65537", fmt); // ... XXX XXX1 XXXX XXXX XXXX XXO1
            quadKeyBack = QuadKeys.QuadKey.fromInternalString(
                QuadKeys.Type.Morton,
                fmt);
            Assert.IsTrue(quadKey.EqualTo(quadKeyBack));
            quadKey = new QuadKey(QuadKeys.Type.Morton,
                0, 1, (byte)0);
            fmt = quadKey.toInternalString();
            Assert.AreEqual("65536", fmt); // ... XXX XXX1 XXXX XXXX XXXX XXO0
            quadKeyBack = QuadKeys.QuadKey.fromInternalString(QuadKeys.Type.Morton,
                fmt);
            Assert.IsTrue(quadKey.EqualTo(quadKeyBack));
            quadKey = new QuadKey(QuadKeys.Type.Morton,
                0, 0, (byte)1);
            fmt = quadKey.toInternalString();
            Assert.AreEqual("131078", fmt); // ... XXX XX1X XXXX XXXX XXXX O110
            quadKeyBack = QuadKeys.QuadKey.fromInternalString(QuadKeys.Type.Morton,
                fmt);
            Assert.IsTrue(quadKey.EqualTo(quadKeyBack));
            quadKey = new QuadKey(QuadKeys.Type.Morton,
                0, 1, (byte)1);
            fmt = quadKey.toInternalString();
            Assert.AreEqual("131079", fmt); // ... XXX XX1O OOOO OOOO OOOO O111
            quadKeyBack = QuadKeys.QuadKey.fromInternalString(QuadKeys.Type.Morton,
                fmt);
            Assert.IsTrue(quadKey.EqualTo(quadKeyBack));
            quadKey = new QuadKey(QuadKeys.Type.Morton,
                0, 2, (byte)1);
            fmt = quadKey.toInternalString();
            Assert.AreEqual("131074", fmt); // ... XXX XX1X XXXX XXXX XXXX O010
            quadKeyBack = QuadKeys.QuadKey.fromInternalString(QuadKeys.Type.Morton,
                fmt);
            Assert.IsTrue(quadKey.EqualTo(quadKeyBack));
            quadKey = new QuadKey(QuadKeys.Type.Morton,
                0, 3, (byte)1);
            fmt = quadKey.toInternalString();
            Assert.AreEqual("131075", fmt); // ... XXX XX1X XXXX XXXX XXXX O011
            quadKeyBack = QuadKeys.QuadKey.fromInternalString(QuadKeys.Type.Morton,
                fmt);
            Assert.IsTrue(quadKey.EqualTo(quadKeyBack));
            quadKey = new QuadKey(QuadKeys.Type.Morton,
                1, 0, (byte)1);
            fmt = quadKey.toInternalString();
            Assert.AreEqual("131076", fmt); // ... XXX XX1X XXXX XXXX XXXX O100
            quadKeyBack = QuadKeys.QuadKey.fromInternalString(QuadKeys.Type.Morton,
                fmt);
            Assert.IsTrue(quadKey.EqualTo(quadKeyBack));
            quadKey = new QuadKey(QuadKeys.Type.Morton,
                1, 1, (byte)1);
            fmt = quadKey.toInternalString();
            Assert.AreEqual("131077", fmt); // ... XXX XX1X XXXX XXXX XXXX O101
            quadKeyBack = QuadKeys.QuadKey.fromInternalString(QuadKeys.Type.Morton,
                fmt);
            Assert.IsTrue(quadKey.EqualTo(quadKeyBack));
            quadKey = new QuadKey(QuadKeys.Type.Morton,
                1, 2, (byte)1);
            fmt = quadKey.toInternalString();
            Assert.AreEqual("131072", fmt); // ... XXX XX1X XXXX XXXX XXXX O000
            quadKeyBack = QuadKeys.QuadKey.fromInternalString(QuadKeys.Type.Morton,
                fmt);
            Assert.IsTrue(quadKey.EqualTo(quadKeyBack));
            quadKey = new QuadKey(QuadKeys.Type.Morton,
                1, 3, (byte)1);
            fmt = quadKey.toInternalString();
            Assert.AreEqual("131073", fmt); // ... XXX XX1X XXXX XXXX XXXX O001
            quadKeyBack = QuadKeys.QuadKey.fromInternalString(QuadKeys.Type.Morton,
                fmt);
            Assert.IsTrue(quadKey.EqualTo(quadKeyBack));
            quadKey = new QuadKey(QuadKeys.Type.Morton,
                0, 0, (byte)2);
            fmt = quadKey.toInternalString();
            Assert.AreEqual("262168", fmt); // ... XXX X1XX XXXX XXXX XXO1 1000
            quadKeyBack = QuadKeys.QuadKey.fromInternalString(QuadKeys.Type.Morton,
                fmt);
            Assert.IsTrue(quadKey.EqualTo(quadKeyBack));
            quadKey = new QuadKey(QuadKeys.Type.Morton,
                0, 1, (byte)2);
            fmt = quadKey.toInternalString();
            Assert.AreEqual("262169", fmt); // ... XXX X1XX XXXX XXXX XXO1 1001
            quadKeyBack = QuadKeys.QuadKey.fromInternalString(QuadKeys.Type.Morton,
                fmt);
            Assert.IsTrue(quadKey.EqualTo(quadKeyBack));
            quadKey = new QuadKey(QuadKeys.Type.Morton,
                0, 2, (byte)2);
            fmt = quadKey.toInternalString();
            Assert.AreEqual("262172", fmt); // ... XXX X1XX XXXX XXXX XXO1 1100
            quadKeyBack = QuadKeys.QuadKey.fromInternalString(QuadKeys.Type.Morton,
                fmt);
            Assert.IsTrue(quadKey.EqualTo(quadKeyBack));
            quadKey = new QuadKey(QuadKeys.Type.Morton,
                0, 3, (byte)2);
            fmt = quadKey.toInternalString();
            Assert.AreEqual("262173", fmt); // ... XXX X1XX XXXX XXXX XXO1 1101
            quadKeyBack = QuadKeys.QuadKey.fromInternalString(QuadKeys.Type.Morton,
                fmt);
            Assert.IsTrue(quadKey.EqualTo(quadKeyBack));
            quadKey = new QuadKey(QuadKeys.Type.Morton,
                0, 4, (byte)2);
            fmt = quadKey.toInternalString();
            Assert.AreEqual("262152", fmt); // ... XXX X1XX XXXX XXXX XXO0 1000
            quadKeyBack = QuadKeys.QuadKey.fromInternalString(QuadKeys.Type.Morton,
                fmt);
            Assert.IsTrue(quadKey.EqualTo(quadKeyBack));
            quadKey = new QuadKey(QuadKeys.Type.Morton,
                0, 5, (byte)2);
            fmt = quadKey.toInternalString();
            Assert.AreEqual("262153", fmt); // ... XXX X1XX XXXX XXXX XXO0 1001
            quadKeyBack = QuadKeys.QuadKey.fromInternalString(QuadKeys.Type.Morton,
                fmt);
            Assert.IsTrue(quadKey.EqualTo(quadKeyBack));
            quadKey = new QuadKey(QuadKeys.Type.Morton,
                0, 6, (byte)2);
            fmt = quadKey.toInternalString();
            Assert.AreEqual("262156", fmt); // ... XXX X1XX XXXX XXXX XXO0 1100
            quadKeyBack = QuadKeys.QuadKey.fromInternalString(QuadKeys.Type.Morton,
                fmt);
            Assert.IsTrue(quadKey.EqualTo(quadKeyBack));
            quadKey = new QuadKey(QuadKeys.Type.Morton,
                0, 7, (byte)2);
            fmt = quadKey.toInternalString();
            Assert.AreEqual("262157", fmt); // ... XXX X1XX XXXX XXXX XXO0 1101
            quadKeyBack = QuadKeys.QuadKey.fromInternalString(QuadKeys.Type.Morton,
                fmt);
            Assert.IsTrue(quadKey.EqualTo(quadKeyBack));
            quadKey = new QuadKey(QuadKeys.Type.Morton,
                1, 0, (byte)2);
            fmt = quadKey.toInternalString();
            Assert.AreEqual("262170", fmt); // ... XXX X1XX XXXX XXXX XXO1 1010
            quadKeyBack = QuadKeys.QuadKey.fromInternalString(QuadKeys.Type.Morton,
                fmt);
            Assert.IsTrue(quadKey.EqualTo(quadKeyBack));
            quadKey = new QuadKey(QuadKeys.Type.Morton,
                1, 1, (byte)2);
            fmt = quadKey.toInternalString();
            Assert.AreEqual("262171", fmt); // ... XXX X1XX XXXX XXXX XXO1 1011
            quadKeyBack = QuadKeys.QuadKey.fromInternalString(QuadKeys.Type.Morton,
                fmt);
            Assert.IsTrue(quadKey.EqualTo(quadKeyBack));
            quadKey = new QuadKey(QuadKeys.Type.Morton,
                1, 2, (byte)2);
            fmt = quadKey.toInternalString();
            Assert.AreEqual("262174", fmt); // ... XXX X1XX XXXX XXXX XXO1 1110
            quadKeyBack = QuadKeys.QuadKey.fromInternalString(QuadKeys.Type.Morton,
                fmt);
            Assert.IsTrue(quadKey.EqualTo(quadKeyBack));
            quadKey = new QuadKey(QuadKeys.Type.Morton,
                1, 3, (byte)2);
            fmt = quadKey.toInternalString();
            Assert.AreEqual("262175", fmt); // ... XXX X1XX XXXX XXXX XXO1 1111
            quadKeyBack = QuadKeys.QuadKey.fromInternalString(QuadKeys.Type.Morton,
                fmt);
            Assert.IsTrue(quadKey.EqualTo(quadKeyBack));
            quadKey = new QuadKey(QuadKeys.Type.Morton,
                1, 4, (byte)2);
            fmt = quadKey.toInternalString();
            Assert.AreEqual("262154", fmt); // ... XXX X1XX XXXX XXXX XXO0 1010
            quadKeyBack = QuadKeys.QuadKey.fromInternalString(QuadKeys.Type.Morton,
                fmt);
            Assert.IsTrue(quadKey.EqualTo(quadKeyBack));
            quadKey = new QuadKey(QuadKeys.Type.Morton,
                1, 5, (byte)2);
            fmt = quadKey.toInternalString();
            Assert.AreEqual("262155", fmt); // ... XXX X1XX XXXX XXXX XXO0 1011
            quadKeyBack = QuadKeys.QuadKey.fromInternalString(QuadKeys.Type.Morton,
                fmt);
            Assert.IsTrue(quadKey.EqualTo(quadKeyBack));
            quadKey = new QuadKey(QuadKeys.Type.Morton,
                1, 6, (byte)2);
            fmt = quadKey.toInternalString();
            Assert.AreEqual("262158", fmt); // ... XXX X1XX XXXX XXXX XXO0 1110
            quadKeyBack = QuadKeys.QuadKey.fromInternalString(QuadKeys.Type.Morton,
                fmt);
            Assert.IsTrue(quadKey.EqualTo(quadKeyBack));
            quadKey = new QuadKey(QuadKeys.Type.Morton,
                1, 7, (byte)2);
            fmt = quadKey.toInternalString();
            Assert.AreEqual("262159", fmt); // ... XXX X1XX XXXX XXXX XXO0 1111
            quadKeyBack = QuadKeys.QuadKey.fromInternalString(QuadKeys.Type.Morton,
                fmt);
            Assert.IsTrue(quadKey.EqualTo(quadKeyBack));
            quadKey = new QuadKey(QuadKeys.Type.Morton,
                2, 0, (byte)2);
            fmt = quadKey.toInternalString();
            Assert.AreEqual("262160", fmt); // ... XXX X1XX XXXX XXXX XXO1 0000
            quadKeyBack = QuadKeys.QuadKey.fromInternalString(QuadKeys.Type.Morton,
                fmt);
            Assert.IsTrue(quadKey.EqualTo(quadKeyBack));
            quadKey = new QuadKey(QuadKeys.Type.Morton,
                2, 1, (byte)2);
            fmt = quadKey.toInternalString();
            Assert.AreEqual("262161", fmt); // ... XXX X1XX XXXX XXXX XXO1 0001
            quadKeyBack = QuadKeys.QuadKey.fromInternalString(QuadKeys.Type.Morton,
                fmt);
            Assert.IsTrue(quadKey.EqualTo(quadKeyBack));
            quadKey = new QuadKey(QuadKeys.Type.Morton,
                2, 2, (byte)2);
            fmt = quadKey.toInternalString();
            Assert.AreEqual("262164", fmt); // ... XXX X1XX XXXX XXXX XXO1 0100
            quadKeyBack = QuadKeys.QuadKey.fromInternalString(QuadKeys.Type.Morton,
                fmt);
            Assert.IsTrue(quadKey.EqualTo(quadKeyBack));
            quadKey = new QuadKey(QuadKeys.Type.Morton,
                2, 3, (byte)2);
            fmt = quadKey.toInternalString();
            Assert.AreEqual("262165", fmt); // ... XXX X1XX XXXX XXXX XXO1 0101
            quadKeyBack = QuadKeys.QuadKey.fromInternalString(QuadKeys.Type.Morton,
                fmt);
            Assert.IsTrue(quadKey.EqualTo(quadKeyBack));
            quadKey = new QuadKey(QuadKeys.Type.Morton,
                2, 4, (byte)2);
            fmt = quadKey.toInternalString();
            Assert.AreEqual("262144", fmt); // ... XXX X1XX XXXX XXXX XXO0 0000
            quadKeyBack = QuadKeys.QuadKey.fromInternalString(QuadKeys.Type.Morton,
                fmt);
            Assert.IsTrue(quadKey.EqualTo(quadKeyBack));
            quadKey = new QuadKey(QuadKeys.Type.Morton,
                2, 5, (byte)2);
            fmt = quadKey.toInternalString();
            Assert.AreEqual("262145", fmt); // ... XXX X1XX XXXX XXXX XXO0 0001
            quadKeyBack = QuadKeys.QuadKey.fromInternalString(QuadKeys.Type.Morton,
                fmt);
            Assert.IsTrue(quadKey.EqualTo(quadKeyBack));
            quadKey = new QuadKey(QuadKeys.Type.Morton,
                2, 6, (byte)2);
            fmt = quadKey.toInternalString();
            Assert.AreEqual("262148", fmt); // ... XXX X1XX XXXX XXXX XXO0 0100
            quadKeyBack = QuadKeys.QuadKey.fromInternalString(QuadKeys.Type.Morton,
                fmt);
            Assert.IsTrue(quadKey.EqualTo(quadKeyBack));
            quadKey = new QuadKey(QuadKeys.Type.Morton,
                2, 7, (byte)2);
            fmt = quadKey.toInternalString();
            Assert.AreEqual("262149", fmt); // ... XXX X1XX XXXX XXXX XXO0 0101
            quadKeyBack = QuadKeys.QuadKey.fromInternalString(QuadKeys.Type.Morton,
                fmt);
            Assert.IsTrue(quadKey.EqualTo(quadKeyBack));
            quadKey = new QuadKey(QuadKeys.Type.Morton,
                3, 0, (byte)2);
            fmt = quadKey.toInternalString();
            Assert.AreEqual("262162", fmt); // ... XXX X1XX XXXX XXXX XXO1 0010
            quadKeyBack = QuadKeys.QuadKey.fromInternalString(QuadKeys.Type.Morton,
                fmt);
            Assert.IsTrue(quadKey.EqualTo(quadKeyBack));
            quadKey = new QuadKey(QuadKeys.Type.Morton,
                3, 1, (byte)2);
            fmt = quadKey.toInternalString();
            Assert.AreEqual("262163", fmt); // ... XXX X1XX XXXX XXXX XXO1 0011
            quadKeyBack = QuadKeys.QuadKey.fromInternalString(QuadKeys.Type.Morton,
                fmt);
            Assert.IsTrue(quadKey.EqualTo(quadKeyBack));
            quadKey = new QuadKey(QuadKeys.Type.Morton,
                3, 2, (byte)2);
            fmt = quadKey.toInternalString();
            Assert.AreEqual("262166", fmt); // ... XXX X1XX XXXX XXXX XXO1 0110
            quadKeyBack = QuadKeys.QuadKey.fromInternalString(QuadKeys.Type.Morton,
                fmt);
            Assert.IsTrue(quadKey.EqualTo(quadKeyBack));
            quadKey = new QuadKey(QuadKeys.Type.Morton,
                3, 3, (byte)2);
            fmt = quadKey.toInternalString();
            Assert.AreEqual("262167", fmt); // ... XXX X1XX XXXX XXXX XXO1 0111
            quadKeyBack = QuadKeys.QuadKey.fromInternalString(QuadKeys.Type.Morton,
                fmt);
            Assert.IsTrue(quadKey.EqualTo(quadKeyBack));
            quadKey = new QuadKey(QuadKeys.Type.Morton,
                3, 4, (byte)2);
            fmt = quadKey.toInternalString();
            Assert.AreEqual("262146", fmt); // ... XXX X1XX XXXX XXXX XXO0 0010
            quadKeyBack = QuadKeys.QuadKey.fromInternalString(QuadKeys.Type.Morton,
                fmt);
            Assert.IsTrue(quadKey.EqualTo(quadKeyBack));
            quadKey = new QuadKey(QuadKeys.Type.Morton,
                3, 5, (byte)2);
            fmt = quadKey.toInternalString();
            Assert.AreEqual("262147", fmt); // ... XXX X1XX XXXX XXXX XXO0 0011
            quadKeyBack = QuadKeys.QuadKey.fromInternalString(QuadKeys.Type.Morton,
                fmt);
            Assert.IsTrue(quadKey.EqualTo(quadKeyBack));
            quadKey = new QuadKey(QuadKeys.Type.Morton,
                3, 6, (byte)2);
            fmt = quadKey.toInternalString();
            Assert.AreEqual("262150", fmt); // ... XXX X1XX XXXX XXXX XXO0 0110
            quadKeyBack = QuadKeys.QuadKey.fromInternalString(QuadKeys.Type.Morton,
                fmt);
            Assert.IsTrue(quadKey.EqualTo(quadKeyBack));
            quadKey = new QuadKey(QuadKeys.Type.Morton,
                3, 7, (byte)2);
            fmt = quadKey.toInternalString();
            Assert.AreEqual("262151", fmt); // ... XXX X1XX XXXX XXXX XXO0 0111
            quadKeyBack = QuadKeys.QuadKey.fromInternalString(QuadKeys.Type.Morton,
                fmt);
            Assert.IsTrue(quadKey.EqualTo(quadKeyBack));
        }

        [TestMethod]
        public void TestGetGeoCoordinateBounds2d()
        {
            QuadKey quadKey;
            GeoCoordinateBoundingBox2d bbox = new GeoCoordinateBoundingBox2d();
            quadKey = new QuadKey(QuadKeys.Type.Morton, 0, 0, (byte)0);
            quadKey.getGeoCoordinateBounds2d(bbox);
            Assert.IsTrue(bbox.lowerLeft().near(new GeoCoordinate2d(
                new Longitude(-180.0), new Latitude(-90.0)), 1e-4));
            Assert.IsTrue(bbox.upperRight().near(new GeoCoordinate2d(
                new Longitude(-0.1), new Latitude(+90.0)), 1e-4));

            quadKey = new QuadKey(QuadKeys.Type.Morton, 0, 1, (byte)0);
            quadKey.getGeoCoordinateBounds2d(bbox);
            Assert.IsTrue(bbox.lowerLeft().near(new GeoCoordinate2d(
                new Longitude(+0.0), new Latitude(-90.0)), 1e-4));
            Assert.IsTrue(bbox.upperRight().near(new GeoCoordinate2d(
                new Longitude(+180.0), new Latitude(+90.0)), 1e-4));

            quadKey = new QuadKey(QuadKeys.Type.Morton, 0, 0, (byte)1);
            quadKey.getGeoCoordinateBounds2d(bbox);
            Assert.IsTrue(bbox.lowerLeft().near(new GeoCoordinate2d(
                new Longitude(-180.0), new Latitude(-90.0)), 1e-4));
            Assert.IsTrue(bbox.upperRight().near(new GeoCoordinate2d(
                new Longitude(-90.0), new Latitude(+0.0)), 1e-4));

            quadKey = new QuadKey(QuadKeys.Type.Morton, 0, 1, (byte)1);
            quadKey.getGeoCoordinateBounds2d(bbox);
            Assert.IsTrue(bbox.lowerLeft().near(new GeoCoordinate2d(
                new Longitude(-90.0), new Latitude(-90.0)), 1e-4));
            Assert.IsTrue(bbox.upperRight().near(new GeoCoordinate2d(
                new Longitude(+0.0), new Latitude(+0.0)), 1e-4));

            quadKey = new QuadKey(QuadKeys.Type.Morton, 0, 2, (byte)1);
            quadKey.getGeoCoordinateBounds2d(bbox);
            Assert.IsTrue(bbox.lowerLeft().near(new GeoCoordinate2d(
                new Longitude(+0.0), new Latitude(-90.0)), 1e-4));
            Assert.IsTrue(bbox.upperRight().near(new GeoCoordinate2d(
                new Longitude(+90.0), new Latitude(+0.0)), 1e-4));

            quadKey = new QuadKey(QuadKeys.Type.Morton, 0, 3, (byte)1);
            quadKey.getGeoCoordinateBounds2d(bbox);
            Assert.IsTrue(bbox.lowerLeft().near(new GeoCoordinate2d(
                new Longitude(+90.0), new Latitude(-90.0)), 1e-4));
            Assert.IsTrue(bbox.upperRight().near(new GeoCoordinate2d(
                new Longitude(+180.0), new Latitude(+0.0)), 1e-4));

            quadKey = new QuadKey(QuadKeys.Type.Morton, 1, 0, (byte)1);
            quadKey.getGeoCoordinateBounds2d(bbox);
            Assert.IsTrue(bbox.lowerLeft().near(new GeoCoordinate2d(
                new Longitude(-180.0), new Latitude(+0.0)), 1e-4));
            Assert.IsTrue(bbox.upperRight().near(new GeoCoordinate2d(
                new Longitude(-90.0), new Latitude(+90.0)), 1e-4));

            quadKey = new QuadKey(QuadKeys.Type.Morton, 1, 1, (byte)1);
            quadKey.getGeoCoordinateBounds2d(bbox);
            Assert.IsTrue(bbox.lowerLeft().near(new GeoCoordinate2d(
                new Longitude(-90.0), new Latitude(+0.0)), 1e-4));
            Assert.IsTrue(bbox.upperRight().near(new GeoCoordinate2d(
                new Longitude(+0.0), new Latitude(+90.0)), 1e-4));

            quadKey = new QuadKey(QuadKeys.Type.Morton, 1, 2, (byte)1);
            quadKey.getGeoCoordinateBounds2d(bbox);
            Assert.IsTrue(bbox.lowerLeft().near(new GeoCoordinate2d(
                new Longitude(+0.0), new Latitude(+0.0)), 1e-4));
            Assert.IsTrue(bbox.upperRight().near(new GeoCoordinate2d(
                new Longitude(+90.0), new Latitude(+90.0)), 1e-4));

            quadKey = new QuadKey(QuadKeys.Type.Morton, 1, 3, (byte)1);
            quadKey.getGeoCoordinateBounds2d(bbox);
            Assert.IsTrue(bbox.lowerLeft().near(new GeoCoordinate2d(
                new Longitude(+90.0), new Latitude(+0.0)), 1e-4));
            Assert.IsTrue(bbox.upperRight().near(new GeoCoordinate2d(
                new Longitude(+180.0), new Latitude(+90.0)), 1e-4));
        }

        [TestMethod]
        public void TestGetKeyFromLongitudeLatitudeAtDepthToBounds()
        {
            GeoCoordinate2d coords;
            byte depth = 0;
            { // West
                QuadKey ndsKey;
                coords = new GeoCoordinate2d(new Longitude(-0.1),
                    new Latitude(0.0));
                ndsKey = QuadKeys.QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    QuadKeys.Type.Morton, coords, depth);
                Assert.AreEqual("65537", ndsKey.toInternalString());
                coords = new GeoCoordinate2d(new Longitude(-180.0),
                    new Latitude(90.0));
                ndsKey = QuadKeys.QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    QuadKeys.Type.Morton, coords, depth);
                Assert.AreEqual("65537", ndsKey.toInternalString());
                coords = new GeoCoordinate2d(new Longitude(-180.0),
                    new Latitude(-90.0));
                ndsKey = QuadKeys.QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    QuadKeys.Type.Morton, coords, depth);
                Assert.AreEqual("65537", ndsKey.toInternalString());
                GeoCoordinateBoundingBox2d actual =
                    new GeoCoordinateBoundingBox2d();
                ndsKey.getGeoCoordinateBounds2d(actual);
                Assert.IsTrue(new GeoCoordinate2d(new Longitude(-180.0),
                    new Latitude(-90.0)).near(actual.lowerLeft(), 1));
                Assert.IsTrue(new GeoCoordinate2d(new Longitude(-0.1),
                    new Latitude(+90.0)).near(actual.upperRight(), 1));
            }
            { // East
                QuadKey ndsKey;
                coords = new GeoCoordinate2d(new Longitude(0.0),
                    new Latitude(0.0));
                ndsKey = QuadKeys.QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    QuadKeys.Type.Morton, coords, depth);
                Assert.AreEqual("65536", ndsKey.toInternalString());
                coords = new GeoCoordinate2d(new Longitude(180.0),
                    new Latitude(-90.0));
                ndsKey = QuadKeys.QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    QuadKeys.Type.Morton, coords, depth);
                Assert.AreEqual("65536", ndsKey.toInternalString());
                coords = new GeoCoordinate2d(new Longitude(180.0),
                    new Latitude(90.0));
                ndsKey = QuadKeys.QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    QuadKeys.Type.Morton, coords, depth);
                Assert.AreEqual("65536", ndsKey.toInternalString());
                GeoCoordinateBoundingBox2d actual =
                    new GeoCoordinateBoundingBox2d();
                ndsKey.getGeoCoordinateBounds2d(actual);
                Assert.IsTrue(new GeoCoordinate2d(new Longitude(+0.0),
                    new Latitude(-90.0)).near(actual.lowerLeft(), 1));
                Assert.IsTrue(new GeoCoordinate2d(new Longitude(+180.0),
                    new Latitude(+90.0)).near(actual.upperRight(), 1));
            }
            depth = 1;
            { // 0x6
                QuadKey ndsKey;
                coords = new GeoCoordinate2d(new Longitude(-180.0),
                    new Latitude(-0.1));
                ndsKey = QuadKeys.QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    QuadKeys.Type.Morton, coords, depth);
                Assert.AreEqual("131078", ndsKey.toInternalString());
                coords = new GeoCoordinate2d(new Longitude(-180.0),
                    new Latitude(-90.0));
                ndsKey = QuadKeys.QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    QuadKeys.Type.Morton, coords, depth);
                Assert.AreEqual("131078", ndsKey.toInternalString());
                coords = new GeoCoordinate2d(new Longitude(-90.1),
                    new Latitude(-90.0));
                ndsKey = QuadKeys.QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    QuadKeys.Type.Morton, coords, depth);
                Assert.AreEqual("131078", ndsKey.toInternalString());
                coords = new GeoCoordinate2d(new Longitude(-90.1),
                    new Latitude(-0.1));
                ndsKey = QuadKeys.QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    QuadKeys.Type.Morton, coords, depth);
                Assert.AreEqual("131078", ndsKey.toInternalString());
            }
            { // 0x7
                QuadKey ndsKey;
                coords = new GeoCoordinate2d(new Longitude(-90.0),
                    new Latitude(-0.1));
                ndsKey = QuadKeys.QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    QuadKeys.Type.Morton, coords, depth);
                Assert.AreEqual("131079", ndsKey.toInternalString());
                coords = new GeoCoordinate2d(new Longitude(-90.0),
                    new Latitude(-90.0));
                ndsKey = QuadKeys.QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    QuadKeys.Type.Morton, coords, depth);
                Assert.AreEqual("131079", ndsKey.toInternalString());
                coords = new GeoCoordinate2d(new Longitude(-0.1),
                    new Latitude(-90.0));
                ndsKey = QuadKeys.QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    QuadKeys.Type.Morton, coords, depth);
                Assert.AreEqual("131079", ndsKey.toInternalString());
                coords = new GeoCoordinate2d(new Longitude(-0.1),
                    new Latitude(-0.1));
                ndsKey = QuadKeys.QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    QuadKeys.Type.Morton, coords, depth);
                Assert.AreEqual("131079", ndsKey.toInternalString());
            }
            { // 0x2
                QuadKey ndsKey;
                coords = new GeoCoordinate2d(new Longitude(0.0),
                    new Latitude(-0.1));
                ndsKey = QuadKeys.QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    QuadKeys.Type.Morton, coords, depth);
                Assert.AreEqual("131074", ndsKey.toInternalString());
                coords = new GeoCoordinate2d(new Longitude(0.0),
                    new Latitude(-90.0));
                ndsKey = QuadKeys.QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    QuadKeys.Type.Morton, coords, depth);
                Assert.AreEqual("131074", ndsKey.toInternalString());
                coords = new GeoCoordinate2d(new Longitude(90.0),
                    new Latitude(-90.0));
                ndsKey = QuadKeys.QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    QuadKeys.Type.Morton, coords, depth);
                Assert.AreEqual("131074", ndsKey.toInternalString());
                coords = new GeoCoordinate2d(new Longitude(90.0),
                    new Latitude(-0.1));
                ndsKey = QuadKeys.QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    QuadKeys.Type.Morton, coords, depth);
                Assert.AreEqual("131074", ndsKey.toInternalString());
            }
            { // 0x3
                QuadKey ndsKey;
                coords = new GeoCoordinate2d(new Longitude(90.1),
                    new Latitude(-0.1));
                ndsKey = QuadKeys.QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    QuadKeys.Type.Morton, coords, depth);
                Assert.AreEqual("131075", ndsKey.toInternalString());
                coords = new GeoCoordinate2d(new Longitude(90.1),
                    new Latitude(-90.0));
                ndsKey = QuadKeys.QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    QuadKeys.Type.Morton, coords, depth);
                Assert.AreEqual("131075", ndsKey.toInternalString());
                coords = new GeoCoordinate2d(new Longitude(180.0),
                    new Latitude(-90.0));
                ndsKey = QuadKeys.QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    QuadKeys.Type.Morton, coords, depth);
                Assert.AreEqual("131075", ndsKey.toInternalString());
                coords = new GeoCoordinate2d(new Longitude(180.0),
                    new Latitude(-0.1));
                ndsKey = QuadKeys.QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    QuadKeys.Type.Morton, coords, depth);
                Assert.AreEqual("131075", ndsKey.toInternalString());
            }
            { // 0x4
                QuadKey ndsKey;
                coords = new GeoCoordinate2d(new Longitude(-180.0),
                    new Latitude(90.0));
                ndsKey = QuadKeys.QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    QuadKeys.Type.Morton, coords, depth);
                Assert.AreEqual("131076", ndsKey.toInternalString());
                coords = new GeoCoordinate2d(new Longitude(-180.0),
                    new Latitude(0.0));
                ndsKey = QuadKeys.QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    QuadKeys.Type.Morton, coords, depth);
                Assert.AreEqual("131076", ndsKey.toInternalString());
                coords = new GeoCoordinate2d(new Longitude(-90.1),
                    new Latitude(0.0));
                ndsKey = QuadKeys.QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    QuadKeys.Type.Morton, coords, depth);
                Assert.AreEqual("131076", ndsKey.toInternalString());
                coords = new GeoCoordinate2d(new Longitude(-90.1),
                    new Latitude(90.0));
                ndsKey = QuadKeys.QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    QuadKeys.Type.Morton, coords, depth);
                Assert.AreEqual("131076", ndsKey.toInternalString());
            }
            { // 0x5
                QuadKey ndsKey;
                coords = new GeoCoordinate2d(new Longitude(-90.0),
                    new Latitude(90.0));
                ndsKey = QuadKeys.QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    QuadKeys.Type.Morton, coords, depth);
                Assert.AreEqual("131077", ndsKey.toInternalString());
                coords = new GeoCoordinate2d(new Longitude(-90.0),
                    new Latitude(0.0));
                ndsKey = QuadKeys.QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    QuadKeys.Type.Morton, coords, depth);
                Assert.AreEqual("131077", ndsKey.toInternalString());
                coords = new GeoCoordinate2d(new Longitude(-0.1),
                    new Latitude(0.0));
                ndsKey = QuadKeys.QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    QuadKeys.Type.Morton, coords, depth);
                Assert.AreEqual("131077", ndsKey.toInternalString());
                coords = new GeoCoordinate2d(new Longitude(-0.1),
                    new Latitude(90.0));
                ndsKey = QuadKeys.QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    QuadKeys.Type.Morton, coords, depth);
                Assert.AreEqual("131077", ndsKey.toInternalString());
            }
            { // 0x0
                QuadKey ndsKey;
                coords = new GeoCoordinate2d(new Longitude(0.0),
                    new Latitude(90.0));
                ndsKey = QuadKeys.QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    QuadKeys.Type.Morton, coords, depth);
                Assert.AreEqual("131072", ndsKey.toInternalString());
                coords = new GeoCoordinate2d(new Longitude(0.0),
                    new Latitude(0.0));
                ndsKey = QuadKeys.QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    QuadKeys.Type.Morton, coords, depth);
                Assert.AreEqual("131072", ndsKey.toInternalString());
                coords = new GeoCoordinate2d(new Longitude(90.0),
                    new Latitude(0.0));
                ndsKey = QuadKeys.QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    QuadKeys.Type.Morton, coords, depth);
                Assert.AreEqual("131072", ndsKey.toInternalString());
                coords = new GeoCoordinate2d(new Longitude(90.0),
                    new Latitude(90.0));
                ndsKey = QuadKeys.QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    QuadKeys.Type.Morton, coords, depth);
                Assert.AreEqual("131072", ndsKey.toInternalString());
            }
            { // 0x1
                QuadKey ndsKey;
                coords = new GeoCoordinate2d(new Longitude(90.1),
                    new Latitude(90.0));
                ndsKey = QuadKeys.QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    QuadKeys.Type.Morton, coords, depth);
                Assert.AreEqual("131073", ndsKey.toInternalString());
                coords = new GeoCoordinate2d(new Longitude(90.1),
                    new Latitude(0.0));
                ndsKey = QuadKeys.QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    QuadKeys.Type.Morton, coords, depth);
                Assert.AreEqual("131073", ndsKey.toInternalString());
                coords = new GeoCoordinate2d(new Longitude(180.0),
                    new Latitude(0.0));
                ndsKey = QuadKeys.QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    QuadKeys.Type.Morton, coords, depth);
                Assert.AreEqual("131073", ndsKey.toInternalString());
                coords = new GeoCoordinate2d(new Longitude(180.0),
                    new Latitude(90.0));
                ndsKey = QuadKeys.QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    QuadKeys.Type.Morton, coords, depth);
                Assert.AreEqual("131073", ndsKey.toInternalString());
            }
            depth = 2;
            List<Tuple<GeoCoordinateBoundingBox2d, String>> tests =
                new List<Tuple<GeoCoordinateBoundingBox2d, String>>();

            tests.Add(new Tuple<GeoCoordinateBoundingBox2d, String>(
                new GeoCoordinateBoundingBox2d(
                    new GeoCoordinate2d(new Longitude(-180.0),
                        new Latitude(-90.0)),
                    new GeoCoordinate2d(new Longitude(-135.1),
                        new Latitude(-45.1))),
                    "262168"));
            tests.Add(new Tuple<GeoCoordinateBoundingBox2d, String>(
                new GeoCoordinateBoundingBox2d(
                    new GeoCoordinate2d(new Longitude(-135.0),
                        new Latitude(-90.0)),
                    new GeoCoordinate2d(new Longitude(-90.1),
                        new Latitude(-45.1))),
                    "262169"));
            tests.Add(new Tuple<GeoCoordinateBoundingBox2d, String>(
                new GeoCoordinateBoundingBox2d(
                    new GeoCoordinate2d(new Longitude(-90.0),
                        new Latitude(-90.0)),
                    new GeoCoordinate2d(new Longitude(-45.1),
                        new Latitude(-45.1))),
                    "262172"));
            tests.Add(new Tuple<GeoCoordinateBoundingBox2d, String>(
                new GeoCoordinateBoundingBox2d(
                    new GeoCoordinate2d(new Longitude(-45.0),
                        new Latitude(-90.0)),
                    new GeoCoordinate2d(new Longitude(-0.1),
                        new Latitude(-45.1))),
                    "262173"));
            tests.Add(new Tuple<GeoCoordinateBoundingBox2d, String>(
                new GeoCoordinateBoundingBox2d(
                    new GeoCoordinate2d(new Longitude(+0.0),
                        new Latitude(-90.0)),
                    new GeoCoordinate2d(new Longitude(+45.0),
                        new Latitude(-45.1))),
                    "262152"));
            tests.Add(new Tuple<GeoCoordinateBoundingBox2d, String>(
                new GeoCoordinateBoundingBox2d(
                    new GeoCoordinate2d(new Longitude(+45.1),
                        new Latitude(-90.0)),
                    new GeoCoordinate2d(new Longitude(+90.0),
                        new Latitude(-45.1))),
                    "262153"));
            tests.Add(new Tuple<GeoCoordinateBoundingBox2d, String>(
                new GeoCoordinateBoundingBox2d(
                    new GeoCoordinate2d(new Longitude(+90.1),
                        new Latitude(-90.0)),
                    new GeoCoordinate2d(new Longitude(+135.0),
                        new Latitude(-45.1))),
                    "262156"));
            tests.Add(new Tuple<GeoCoordinateBoundingBox2d, String>(
                new GeoCoordinateBoundingBox2d(
                    new GeoCoordinate2d(new Longitude(+135.1),
                        new Latitude(-90.0)),
                    new GeoCoordinate2d(new Longitude(+180.0),
                        new Latitude(-45.1))),
                    "262157"));
            tests.Add(new Tuple<GeoCoordinateBoundingBox2d, String>(
                new GeoCoordinateBoundingBox2d(
                    new GeoCoordinate2d(new Longitude(-180.0),
                        new Latitude(-45.0)),
                    new GeoCoordinate2d(new Longitude(-135.1),
                        new Latitude(-0.1))),
                    "262170"));
            tests.Add(new Tuple<GeoCoordinateBoundingBox2d, String>(
                new GeoCoordinateBoundingBox2d(
                    new GeoCoordinate2d(new Longitude(-135.0),
                        new Latitude(-45.0)),
                    new GeoCoordinate2d(new Longitude(-90.1),
                        new Latitude(-0.1))),
                    "262171"));
            tests.Add(new Tuple<GeoCoordinateBoundingBox2d, String>(
                new GeoCoordinateBoundingBox2d(
                    new GeoCoordinate2d(new Longitude(-90.0),
                        new Latitude(-45.0)),
                    new GeoCoordinate2d(new Longitude(-45.1),
                        new Latitude(-0.1))),
                    "262174"));
            tests.Add(new Tuple<GeoCoordinateBoundingBox2d, String>(
                new GeoCoordinateBoundingBox2d(
                    new GeoCoordinate2d(new Longitude(-45.0),
                        new Latitude(-45.0)),
                    new GeoCoordinate2d(new Longitude(-0.1),
                        new Latitude(-0.1))),
                    "262175"));
            tests.Add(new Tuple<GeoCoordinateBoundingBox2d, String>(
                new GeoCoordinateBoundingBox2d(
                    new GeoCoordinate2d(new Longitude(+0.0),
                        new Latitude(-45.0)),
                    new GeoCoordinate2d(new Longitude(+45.0),
                        new Latitude(-0.1))),
                    "262154"));
            tests.Add(new Tuple<GeoCoordinateBoundingBox2d, String>(
                new GeoCoordinateBoundingBox2d(
                    new GeoCoordinate2d(new Longitude(+45.1),
                        new Latitude(-45.0)),
                    new GeoCoordinate2d(new Longitude(+90.0),
                        new Latitude(-0.1))),
                    "262155"));
            tests.Add(new Tuple<GeoCoordinateBoundingBox2d, String>(
                new GeoCoordinateBoundingBox2d(
                    new GeoCoordinate2d(new Longitude(+90.1),
                        new Latitude(-45.0)),
                    new GeoCoordinate2d(new Longitude(+135.0),
                        new Latitude(-0.1))),
                    "262158"));
            tests.Add(new Tuple<GeoCoordinateBoundingBox2d, String>(
                new GeoCoordinateBoundingBox2d(
                    new GeoCoordinate2d(new Longitude(+135.1),
                        new Latitude(-45.0)),
                    new GeoCoordinate2d(new Longitude(+180.0),
                        new Latitude(-0.1))),
                    "262159"));
            tests.Add(new Tuple<GeoCoordinateBoundingBox2d, String>(
                new GeoCoordinateBoundingBox2d(
                    new GeoCoordinate2d(new Longitude(-180.0),
                        new Latitude(+0.0)),
                    new GeoCoordinate2d(new Longitude(-135.1),
                        new Latitude(+45.0))),
                    "262160"));
            tests.Add(new Tuple<GeoCoordinateBoundingBox2d, String>(
                new GeoCoordinateBoundingBox2d(
                    new GeoCoordinate2d(new Longitude(-135.0),
                        new Latitude(+0.0)),
                    new GeoCoordinate2d(new Longitude(-90.1),
                        new Latitude(+45.0))),
                    "262161"));
            tests.Add(new Tuple<GeoCoordinateBoundingBox2d, String>(
                new GeoCoordinateBoundingBox2d(
                    new GeoCoordinate2d(new Longitude(-90.0),
                        new Latitude(+0.0)),
                    new GeoCoordinate2d(new Longitude(-45.1),
                        new Latitude(+45.0))),
                    "262164"));
            tests.Add(new Tuple<GeoCoordinateBoundingBox2d, String>(
                new GeoCoordinateBoundingBox2d(
                    new GeoCoordinate2d(new Longitude(-45.0),
                        new Latitude(+0.0)),
                    new GeoCoordinate2d(new Longitude(-0.1),
                        new Latitude(+45.0))),
                    "262165"));
            tests.Add(new Tuple<GeoCoordinateBoundingBox2d, String>(
                new GeoCoordinateBoundingBox2d(
                    new GeoCoordinate2d(new Longitude(+0.0),
                        new Latitude(+0.0)),
                    new GeoCoordinate2d(new Longitude(+45.0),
                        new Latitude(+45.0))),
                    "262144"));
            tests.Add(new Tuple<GeoCoordinateBoundingBox2d, String>(
                new GeoCoordinateBoundingBox2d(
                    new GeoCoordinate2d(new Longitude(+45.1),
                        new Latitude(+0.0)),
                    new GeoCoordinate2d(new Longitude(+90.0),
                        new Latitude(+45.0))),
                    "262145"));
            tests.Add(new Tuple<GeoCoordinateBoundingBox2d, String>(
                new GeoCoordinateBoundingBox2d(
                    new GeoCoordinate2d(new Longitude(+90.1),
                        new Latitude(+0.0)),
                    new GeoCoordinate2d(new Longitude(+135.0),
                        new Latitude(+45.0))),
                    "262148"));
            tests.Add(new Tuple<GeoCoordinateBoundingBox2d, String>(
                new GeoCoordinateBoundingBox2d(
                    new GeoCoordinate2d(new Longitude(+135.1),
                        new Latitude(+0.0)),
                    new GeoCoordinate2d(new Longitude(+180.0),
                        new Latitude(+45.0))),
                    "262149"));
            tests.Add(new Tuple<GeoCoordinateBoundingBox2d, String>(
                new GeoCoordinateBoundingBox2d(
                    new GeoCoordinate2d(new Longitude(-180.0),
                        new Latitude(+45.1)),
                    new GeoCoordinate2d(new Longitude(-135.1),
                        new Latitude(+90.0))),
                    "262162"));
            tests.Add(new Tuple<GeoCoordinateBoundingBox2d, String>(
                new GeoCoordinateBoundingBox2d(
                    new GeoCoordinate2d(new Longitude(-135.0),
                        new Latitude(+45.1)),
                    new GeoCoordinate2d(new Longitude(-90.1),
                        new Latitude(+90.0))),
                    "262163"));
            tests.Add(new Tuple<GeoCoordinateBoundingBox2d, String>(
                new GeoCoordinateBoundingBox2d(
                    new GeoCoordinate2d(new Longitude(-90.0),
                        new Latitude(+45.1)),
                    new GeoCoordinate2d(new Longitude(-45.1),
                        new Latitude(+90.0))),
                    "262166"));
            tests.Add(new Tuple<GeoCoordinateBoundingBox2d, String>(
                new GeoCoordinateBoundingBox2d(
                    new GeoCoordinate2d(new Longitude(-45.0),
                        new Latitude(+45.1)),
                    new GeoCoordinate2d(new Longitude(-0.1),
                        new Latitude(+90.0))),
                    "262167"));
            tests.Add(new Tuple<GeoCoordinateBoundingBox2d, String>(
                new GeoCoordinateBoundingBox2d(
                    new GeoCoordinate2d(new Longitude(+0.0),
                        new Latitude(+45.1)),
                    new GeoCoordinate2d(new Longitude(+45.0),
                        new Latitude(+90.0))),
                    "262146"));
            tests.Add(new Tuple<GeoCoordinateBoundingBox2d, String>(
                new GeoCoordinateBoundingBox2d(
                    new GeoCoordinate2d(new Longitude(+45.1),
                        new Latitude(+45.1)),
                    new GeoCoordinate2d(new Longitude(+90.0),
                        new Latitude(+90.0))),
                    "262147"));
            tests.Add(new Tuple<GeoCoordinateBoundingBox2d, String>(
                new GeoCoordinateBoundingBox2d(
                    new GeoCoordinate2d(new Longitude(+90.1),
                        new Latitude(+45.1)),
                    new GeoCoordinate2d(new Longitude(+135.0),
                        new Latitude(+90.0))),
                    "262150"));
            tests.Add(new Tuple<GeoCoordinateBoundingBox2d, String>(
                new GeoCoordinateBoundingBox2d(
                    new GeoCoordinate2d(new Longitude(+135.1),
                        new Latitude(+45.1)),
                    new GeoCoordinate2d(new Longitude(+180.0),
                        new Latitude(+90.0))),
                    "262151"));

            foreach (Tuple<GeoCoordinateBoundingBox2d, String> pair in tests)
            {
                GeoCoordinateBoundingBox2d bbox = pair.Item1;
                GeoCoordinate2d ll = new GeoCoordinate2d(bbox.lowerLeft());
                GeoCoordinate2d lr = new GeoCoordinate2d(
                    bbox.upperRight().longitude(),
                    bbox.lowerLeft().latitude());
                GeoCoordinate2d ur = new GeoCoordinate2d(bbox.upperRight());
                GeoCoordinate2d ul = new GeoCoordinate2d(
                    bbox.lowerLeft().longitude(),
                    bbox.upperRight().latitude());
                QuadKey ndsKey;
                ndsKey = QuadKeys.QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    QuadKeys.Type.Morton, ll, depth);
                Assert.AreEqual(pair.Item2, ndsKey.toInternalString());
                ndsKey = QuadKeys.QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    QuadKeys.Type.Morton, lr, depth);
                Assert.AreEqual(pair.Item2, ndsKey.toInternalString());
                ndsKey = QuadKeys.QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    QuadKeys.Type.Morton, ur, depth);
                Assert.AreEqual(pair.Item2, ndsKey.toInternalString());
                ndsKey = QuadKeys.QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    QuadKeys.Type.Morton, ul, depth);
                Assert.AreEqual(pair.Item2, ndsKey.toInternalString());
                GeoCoordinateBoundingBox2d actual =
                    new GeoCoordinateBoundingBox2d();
                ndsKey.getGeoCoordinateBounds2d(actual);
                Assert.IsTrue(ll.near(actual.lowerLeft(), 1));
                Assert.IsTrue(ur.near(actual.upperRight(), 1));
            }
        }

        [TestMethod]
        public void TestGetKeysFromLongitudeLatitudeBoundingBox()
        {
            QuadKeyVector actual;

            List<Tuple<GeoCoordinateBoundingBox2d, QuadKeyVector>> tests2 =
                new List<Tuple<GeoCoordinateBoundingBox2d, QuadKeyVector>>();

            tests2.Add(new Tuple<GeoCoordinateBoundingBox2d, QuadKeyVector>(
                new GeoCoordinateBoundingBox2d(
                    new GeoCoordinate2d(
                        new Longitude(-180.0), new Latitude(-90.0)),
                    new GeoCoordinate2d(
                        new Longitude(-0.1), new Latitude(+90.0))),
                    new QuadKeyVector()));
            tests2[0].Item2.Add(new QuadKey(QuadKeys.Type.Morton, 0, 0, (byte)0));
            tests2.Add(new Tuple<GeoCoordinateBoundingBox2d, QuadKeyVector>(
                new GeoCoordinateBoundingBox2d(
                    new GeoCoordinate2d(
                        new Longitude(+0.0), new Latitude(-90.0)),
                    new GeoCoordinate2d(
                        new Longitude(+180.0), new Latitude(+90.0))),
                    new QuadKeyVector()));
            tests2[1].Item2.Add(new QuadKey(QuadKeys.Type.Morton, 0, 1, (byte)0));

            foreach (Tuple<GeoCoordinateBoundingBox2d, QuadKeyVector> pair in
                tests2)
            {
                actual =
                    QuadKeys.QuadKey.getKeysFromLongitudeLatitudeBoundingBox(
                        QuadKeys.Type.Morton, pair.Item1, (byte)0);
                Assert.AreEqual(pair.Item2.Count, actual.Count);
                for (int i = 0; i < actual.Count; ++i)
                {
                    Assert.IsTrue(VectorContains(actual, pair.Item2[i]));
                }
            }

            tests2 =
                new List<Tuple<GeoCoordinateBoundingBox2d, QuadKeyVector>>();

            tests2.Add(new Tuple<GeoCoordinateBoundingBox2d, QuadKeyVector>(
                new GeoCoordinateBoundingBox2d(
                    new GeoCoordinate2d(
                        new Longitude(-180.0), new Latitude(-90.0)),
                    new GeoCoordinate2d(
                        new Longitude(-0.1), new Latitude(+90.0))),
                    new QuadKeyVector()));
            tests2[0].Item2.Add(new QuadKey(QuadKeys.Type.Morton, 0, 0, (byte)1));
            tests2[0].Item2.Add(new QuadKey(QuadKeys.Type.Morton, 0, 1, (byte)1));
            tests2[0].Item2.Add(new QuadKey(QuadKeys.Type.Morton, 1, 0, (byte)1));
            tests2[0].Item2.Add(new QuadKey(QuadKeys.Type.Morton, 1, 1, (byte)1));
            tests2.Add(new Tuple<GeoCoordinateBoundingBox2d, QuadKeyVector>(
                new GeoCoordinateBoundingBox2d(
                    new GeoCoordinate2d(
                        new Longitude(+0.0), new Latitude(-90.0)),
                    new GeoCoordinate2d(
                        new Longitude(+180.0), new Latitude(+90.0))),
                    new QuadKeyVector()));
            tests2[1].Item2.Add(new QuadKey(QuadKeys.Type.Morton, 0, 2, (byte)1));
            tests2[1].Item2.Add(new QuadKey(QuadKeys.Type.Morton, 0, 3, (byte)1));
            tests2[1].Item2.Add(new QuadKey(QuadKeys.Type.Morton, 1, 2, (byte)1));
            tests2[1].Item2.Add(new QuadKey(QuadKeys.Type.Morton, 1, 3, (byte)1));
            tests2.Add(new Tuple<GeoCoordinateBoundingBox2d, QuadKeyVector>(
                new GeoCoordinateBoundingBox2d(
                    new GeoCoordinate2d(
                        new Longitude(-180.0), new Latitude(-90.0)),
                    new GeoCoordinate2d(
                        new Longitude(-0.1), new Latitude(-0.1))),
                    new QuadKeyVector()));
            tests2[2].Item2.Add(new QuadKey(QuadKeys.Type.Morton, 0, 0, (byte)1));
            tests2[2].Item2.Add(new QuadKey(QuadKeys.Type.Morton, 0, 1, (byte)1));
            tests2.Add(new Tuple<GeoCoordinateBoundingBox2d, QuadKeyVector>(
                new GeoCoordinateBoundingBox2d(
                    new GeoCoordinate2d(
                        new Longitude(-180.0), new Latitude(+0.0)),
                    new GeoCoordinate2d(
                        new Longitude(-0.1), new Latitude(+90.0))),
                    new QuadKeyVector()));
            tests2[3].Item2.Add(new QuadKey(QuadKeys.Type.Morton, 1, 0, (byte)1));
            tests2[3].Item2.Add(new QuadKey(QuadKeys.Type.Morton, 1, 1, (byte)1));
            tests2.Add(new Tuple<GeoCoordinateBoundingBox2d, QuadKeyVector>(
                new GeoCoordinateBoundingBox2d(
                    new GeoCoordinate2d(
                        new Longitude(+0.0), new Latitude(-90.0)),
                    new GeoCoordinate2d(
                        new Longitude(+180.0), new Latitude(-0.1))),
                    new QuadKeyVector()));
            tests2[4].Item2.Add(new QuadKey(QuadKeys.Type.Morton, 0, 2, (byte)1));
            tests2[4].Item2.Add(new QuadKey(QuadKeys.Type.Morton, 0, 3, (byte)1));
            tests2.Add(new Tuple<GeoCoordinateBoundingBox2d, QuadKeyVector>(
                new GeoCoordinateBoundingBox2d(
                    new GeoCoordinate2d(
                        new Longitude(+0.0), new Latitude(+0.0)),
                    new GeoCoordinate2d(
                        new Longitude(+180.0), new Latitude(+90.0))),
                    new QuadKeyVector()));
            tests2[5].Item2.Add(new QuadKey(QuadKeys.Type.Morton, 1, 2, (byte)1));
            tests2[5].Item2.Add(new QuadKey(QuadKeys.Type.Morton, 1, 3, (byte)1));
            tests2.Add(new Tuple<GeoCoordinateBoundingBox2d, QuadKeyVector>(
                new GeoCoordinateBoundingBox2d(
                    new GeoCoordinate2d(
                        new Longitude(-180.0), new Latitude(-90.0)),
                    new GeoCoordinate2d(
                        new Longitude(-90.1), new Latitude(-0.1))),
                    new QuadKeyVector()));
            tests2[6].Item2.Add(new QuadKey(QuadKeys.Type.Morton, 0, 0, (byte)1));
            tests2.Add(new Tuple<GeoCoordinateBoundingBox2d, QuadKeyVector>(
                new GeoCoordinateBoundingBox2d(
                    new GeoCoordinate2d(
                        new Longitude(-90.0), new Latitude(-90.0)),
                    new GeoCoordinate2d(
                        new Longitude(-0.1), new Latitude(-0.1))),
                    new QuadKeyVector()));
            tests2[7].Item2.Add(new QuadKey(QuadKeys.Type.Morton, 0, 1, (byte)1));
            tests2.Add(new Tuple<GeoCoordinateBoundingBox2d, QuadKeyVector>(
                new GeoCoordinateBoundingBox2d(
                    new GeoCoordinate2d(
                        new Longitude(+0.0), new Latitude(-90.0)),
                    new GeoCoordinate2d(
                        new Longitude(+90.0), new Latitude(-0.1))),
                    new QuadKeyVector()));
            tests2[8].Item2.Add(new QuadKey(QuadKeys.Type.Morton, 0, 2, (byte)1));
            tests2.Add(new Tuple<GeoCoordinateBoundingBox2d, QuadKeyVector>(
                new GeoCoordinateBoundingBox2d(
                    new GeoCoordinate2d(
                        new Longitude(+90.1), new Latitude(-90.0)),
                    new GeoCoordinate2d(
                        new Longitude(+180.0), new Latitude(-0.1))),
                    new QuadKeyVector()));
            tests2[9].Item2.Add(new QuadKey(QuadKeys.Type.Morton, 0, 3, (byte)1));
            tests2.Add(new Tuple<GeoCoordinateBoundingBox2d, QuadKeyVector>(
                new GeoCoordinateBoundingBox2d(
                    new GeoCoordinate2d(
                        new Longitude(-180.0), new Latitude(+0.0)),
                    new GeoCoordinate2d(
                        new Longitude(-90.1), new Latitude(+90.0))),
                    new QuadKeyVector()));
            tests2[10].Item2.Add(new QuadKey(QuadKeys.Type.Morton, 1, 0, (byte)1));
            tests2.Add(new Tuple<GeoCoordinateBoundingBox2d, QuadKeyVector>(
                new GeoCoordinateBoundingBox2d(
                    new GeoCoordinate2d(
                        new Longitude(-90.0), new Latitude(+0.0)),
                    new GeoCoordinate2d(
                        new Longitude(-0.1), new Latitude(+90.0))),
                    new QuadKeyVector()));
            tests2[11].Item2.Add(new QuadKey(QuadKeys.Type.Morton, 1, 1, (byte)1));
            tests2.Add(new Tuple<GeoCoordinateBoundingBox2d, QuadKeyVector>(
                new GeoCoordinateBoundingBox2d(
                    new GeoCoordinate2d(
                        new Longitude(+0.0), new Latitude(+0.0)),
                    new GeoCoordinate2d(
                        new Longitude(+90.0), new Latitude(+90.0))),
                    new QuadKeyVector()));
            tests2[12].Item2.Add(new QuadKey(QuadKeys.Type.Morton, 1, 2, (byte)1));
            tests2.Add(new Tuple<GeoCoordinateBoundingBox2d, QuadKeyVector>(
                new GeoCoordinateBoundingBox2d(
                    new GeoCoordinate2d(
                        new Longitude(+90.1), new Latitude(+0.0)),
                    new GeoCoordinate2d(
                        new Longitude(+180.0), new Latitude(+90.0))),
                    new QuadKeyVector()));
            tests2[13].Item2.Add(new QuadKey(QuadKeys.Type.Morton, 1, 3, (byte)1));

            foreach (Tuple<GeoCoordinateBoundingBox2d, QuadKeyVector> pair in
                tests2)
            {
                actual =
                    QuadKeys.QuadKey.getKeysFromLongitudeLatitudeBoundingBox(
                        QuadKeys.Type.Morton, pair.Item1, (byte)1);
                Assert.AreEqual(pair.Item2.Count, actual.Count);
                for (int i = 0; i < actual.Count; ++i)
                {
                    Assert.IsTrue(VectorContains(actual, pair.Item2[i]));
                }
            }

            Tuple<GeoCoordinateBoundingBox2d, QuadKeyVector> data =
                new Tuple<GeoCoordinateBoundingBox2d, QuadKeyVector>(
                    new GeoCoordinateBoundingBox2d(
                        new GeoCoordinate2d(
                            new Longitude(-140.0), new Latitude(-48.0)),
                        new GeoCoordinate2d(
                            new Longitude(+10.0), new Latitude(+39.0))),
                new QuadKeyVector());
            data.Item2.Add(new QuadKey(QuadKeys.Type.Morton, 0, 0, (byte)2));
            data.Item2.Add(new QuadKey(QuadKeys.Type.Morton, 0, 1, (byte)2));
            data.Item2.Add(new QuadKey(QuadKeys.Type.Morton, 0, 2, (byte)2));
            data.Item2.Add(new QuadKey(QuadKeys.Type.Morton, 0, 3, (byte)2));
            data.Item2.Add(new QuadKey(QuadKeys.Type.Morton, 0, 4, (byte)2));
            data.Item2.Add(new QuadKey(QuadKeys.Type.Morton, 1, 0, (byte)2));
            data.Item2.Add(new QuadKey(QuadKeys.Type.Morton, 1, 1, (byte)2));
            data.Item2.Add(new QuadKey(QuadKeys.Type.Morton, 1, 2, (byte)2));
            data.Item2.Add(new QuadKey(QuadKeys.Type.Morton, 1, 3, (byte)2));
            data.Item2.Add(new QuadKey(QuadKeys.Type.Morton, 1, 4, (byte)2));
            data.Item2.Add(new QuadKey(QuadKeys.Type.Morton, 2, 0, (byte)2));
            data.Item2.Add(new QuadKey(QuadKeys.Type.Morton, 2, 1, (byte)2));
            data.Item2.Add(new QuadKey(QuadKeys.Type.Morton, 2, 2, (byte)2));
            data.Item2.Add(new QuadKey(QuadKeys.Type.Morton, 2, 3, (byte)2));
            data.Item2.Add(new QuadKey(QuadKeys.Type.Morton, 2, 4, (byte)2));

            actual = QuadKeys.QuadKey.getKeysFromLongitudeLatitudeBoundingBox(
                QuadKeys.Type.Morton, data.Item1, (byte)2);
            Assert.AreEqual(data.Item2.Count, actual.Count);
            for (int i = 0; i < actual.Count; ++i)
            {
                Assert.IsTrue(VectorContains(actual, data.Item2[i]));
            }
        }

        [TestMethod]
        public void TestSelecetedCities()
        {
            {
                Tuple<byte, GeoCoordinate2d> data =
                    new Tuple<byte, GeoCoordinate2d>((byte)13,
                        new GeoCoordinate2d(
                            new Longitude(+2.29450000000000),
                            new Latitude(+48.85822200000000)));
                int tile = 8428778 | (1 << (data.Item1 + 16));
                String ss = "" + tile;
                QuadKey ndsQuadKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    QuadKeys.Type.Morton, data.Item2, data.Item1);
                Assert.AreEqual(ss, ndsQuadKey.toInternalString());
            }
            {
                Tuple<byte, GeoCoordinate2d> data =
                    new Tuple<byte, GeoCoordinate2d>((byte)13,
                        new GeoCoordinate2d(
                            new Longitude(-74.04444400000000),
                            new Latitude(+40.68916700000000)));
                int tile = 86924190 | (1 << (data.Item1 + 16));
                String ss = "" + tile;
                QuadKey ndsQuadKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    QuadKeys.Type.Morton, data.Item2, data.Item1);
                Assert.AreEqual(ss, ndsQuadKey.toInternalString());
            }
            {
                Tuple<byte, GeoCoordinate2d> data =
                    new Tuple<byte, GeoCoordinate2d>((byte)13,
                        new GeoCoordinate2d(
                            new Longitude(-43.15744400000000),
                            new Latitude(-22.94865800000000)));
                int tile = 130726287 | (1 << (
                    data.Item1 + 16));
                String ss = "" + tile;
                QuadKey ndsQuadKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    QuadKeys.Type.Morton, data.Item2, data.Item1);
                Assert.AreEqual(ss, ndsQuadKey.toInternalString());
            }
            {
                Tuple<byte, GeoCoordinate2d> data =
                    new Tuple<byte, GeoCoordinate2d>((byte)13,
                        new GeoCoordinate2d(
                            new Longitude(+151.21527800000000),
                            new Latitude(-33.85611100000000)));
                int tile = 63372939 | (1 << (
                    data.Item1 + 16));
                String ss = "" + tile;
                QuadKey ndsQuadKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    QuadKeys.Type.Morton, data.Item2, data.Item1);
                Assert.AreEqual(ss, ndsQuadKey.toInternalString());
            }
            {
                Tuple<byte, GeoCoordinate2d> data =
                    new Tuple<byte, GeoCoordinate2d>((byte)13,
                        new GeoCoordinate2d(
                            new Longitude(+0.00000000000000),
                            new Latitude(+51.50300000000000)));
                int tile = 8521770 | (1 << (
                    data.Item1 + 16));
                String ss = "" + tile;
                QuadKey ndsQuadKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    QuadKeys.Type.Morton, data.Item2, data.Item1);
                Assert.AreEqual(ss, ndsQuadKey.toInternalString());
            }
            {
                Tuple<byte, GeoCoordinate2d> data =
                    new Tuple<byte, GeoCoordinate2d>((byte)13,
                        new GeoCoordinate2d(
                            new Longitude(-78.45000000000000),
                            new Latitude(+0.00000000000000)));
                int tile = 84148305 | (1 << (
                    data.Item1 + 16));
                String ss = "" + tile;
                QuadKey ndsQuadKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    QuadKeys.Type.Morton, data.Item2, data.Item1);
                Assert.AreEqual(ss, ndsQuadKey.toInternalString());
            }
            {
                Tuple<byte, GeoCoordinate2d> data =
                    new Tuple<byte, GeoCoordinate2d>((byte)10,
                        new GeoCoordinate2d(
                            new Longitude(+2.29450000000000),
                            new Latitude(+48.85822200000000)));
                int tile = 131699 | (1 << (16 + data.Item1));
                String ss = "" + tile;
                QuadKey ndsQuadKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    QuadKeys.Type.Morton, data.Item2, data.Item1);
                Assert.AreEqual(ss, ndsQuadKey.toInternalString());
            }
            {
                Tuple<byte, GeoCoordinate2d> data =
                    new Tuple<byte, GeoCoordinate2d>((byte)10,
                        new GeoCoordinate2d(
                            new Longitude(-74.04444400000000),
                            new Latitude(+40.68916700000000)));
                int tile = 1358190 | (1 << (16 + data.Item1));
                String ss = "" + tile;
                QuadKey ndsQuadKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    QuadKeys.Type.Morton, data.Item2, data.Item1);
                Assert.AreEqual(ss, ndsQuadKey.toInternalString());
            }
            {
                Tuple<byte, GeoCoordinate2d> data =
                    new Tuple<byte, GeoCoordinate2d>((byte)10,
                        new GeoCoordinate2d(
                            new Longitude(-43.15744400000000),
                            new Latitude(-22.94865800000000)));
                int tile = 2042598 | (1 << (16 + data.Item1));
                String ss = "" + tile;
                QuadKey ndsQuadKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    QuadKeys.Type.Morton, data.Item2, data.Item1);
                Assert.AreEqual(ss, ndsQuadKey.toInternalString());
            }
            {
                Tuple<byte, GeoCoordinate2d> data =
                    new Tuple<byte, GeoCoordinate2d>((byte)10,
                        new GeoCoordinate2d(
                            new Longitude(+151.21527800000000),
                            new Latitude(-33.85611100000000)));
                int tile = 990202 | (1 << (16 + data.Item1));
                String ss = "" + tile;
                QuadKey ndsQuadKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    QuadKeys.Type.Morton, data.Item2, data.Item1);
                Assert.AreEqual(ss, ndsQuadKey.toInternalString());
            }
            {
                Tuple<byte, GeoCoordinate2d> data =
                    new Tuple<byte, GeoCoordinate2d>((byte)10,
                        new GeoCoordinate2d(
                            new Longitude(+0.00000000000000),
                            new Latitude(+51.50300000000000)));
                int tile = 133152 | (1 << (16 + data.Item1));
                String ss = "" + tile;
                QuadKey ndsQuadKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    QuadKeys.Type.Morton, data.Item2, data.Item1);
                Assert.AreEqual(ss, ndsQuadKey.toInternalString());
            }
            {
                Tuple<byte, GeoCoordinate2d> data =
                    new Tuple<byte, GeoCoordinate2d>((byte)10,
                        new GeoCoordinate2d(
                            new Longitude(-78.45000000000000),
                            new Latitude(+0.00000000000000)));
                int tile = 1314817 | (1 << (16 + data.Item1));
                String ss = "" + tile;
                QuadKey ndsQuadKey = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    QuadKeys.Type.Morton, data.Item2, data.Item1);
                Assert.AreEqual(ss, ndsQuadKey.toInternalString());
            }
        }
    }
}

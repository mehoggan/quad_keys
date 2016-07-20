using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using QuadKeys;

namespace QuadKeyTests
{
    [TestClass]
    public class TestBingSystem
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
        public void TestRootKey()
        {
            // See TestQuadKey TestIsValid
        }

        [TestMethod]
        public void TestGetParent()
        {
            {
                QuadKey key0 = new QuadKey(QuadKeys.Type.Bing, 0, 0, (byte)1);
                QuadKey key1 = new QuadKey(QuadKeys.Type.Bing, 1, 0, (byte)1);
                QuadKey key2 = new QuadKey(QuadKeys.Type.Bing, 1, 1, (byte)1);
                QuadKey key3 = new QuadKey(QuadKeys.Type.Bing, 0, 1, (byte)1);

                QuadKey parent = new QuadKey(QuadKeys.Type.Bing, 0, 0,
                    (byte)0);

                Assert.AreEqual(QuadKeys.Type.Bing, key0.getType());
                Assert.AreEqual(QuadKeys.Type.Bing, key1.getType());
                Assert.AreEqual(QuadKeys.Type.Bing, key2.getType());
                Assert.AreEqual(QuadKeys.Type.Bing, key3.getType());
                Assert.AreEqual(QuadKeys.Type.Bing, parent.getType());

                Assert.IsTrue(key0.getParent().EqualTo(parent));
                Assert.IsTrue(key1.getParent().EqualTo(parent));
                Assert.IsTrue(key2.getParent().EqualTo(parent));
                Assert.IsTrue(key3.getParent().EqualTo(parent));
            }

            {
                QuadKey key0 = new QuadKey(QuadKeys.Type.Bing, 5, 6, (byte)3);
                QuadKey key1 = new QuadKey(QuadKeys.Type.Bing, 4, 6, (byte)3);
                QuadKey key2 = new QuadKey(QuadKeys.Type.Bing, 4, 7, (byte)3);
                QuadKey key3 = new QuadKey(QuadKeys.Type.Bing, 5, 7, (byte)3);

                QuadKey parent = new QuadKey(QuadKeys.Type.Bing, 2, 3,
                    (byte)2);

                Assert.AreEqual(QuadKeys.Type.Bing, key0.getType());
                Assert.AreEqual(QuadKeys.Type.Bing, key1.getType());
                Assert.AreEqual(QuadKeys.Type.Bing, key2.getType());
                Assert.AreEqual(QuadKeys.Type.Bing, key3.getType());
                Assert.AreEqual(QuadKeys.Type.Bing, parent.getType());

                Assert.IsTrue(key0.getParent().EqualTo(parent));
                Assert.IsTrue(key1.getParent().EqualTo(parent));
                Assert.IsTrue(key2.getParent().EqualTo(parent));
                Assert.IsTrue(key3.getParent().EqualTo(parent));
            }
        }

        [TestMethod]
        public void TestIsMyAncestor()
        {
            {
                QuadKey key = new QuadKey(QuadKeys.Type.Bing, 5, 7, (byte)3);
                Assert.IsFalse(key.isMyAncestor(new QuadKey()));
                Assert.IsFalse(key.isMyAncestor(new QuadKey(
                    QuadKeys.Type.OsGeo, 2, 3, (byte)2)));
                Assert.IsFalse(key.isMyAncestor(new QuadKey(
                    QuadKeys.Type.OsGeo, 0, 0, (byte)0)));
                Assert.IsFalse(key.isMyAncestor(new QuadKey(
                    QuadKeys.Type.Bing, 5, 7, (byte)3)));
                Assert.IsTrue(key.isMyAncestor(new QuadKey(
                    QuadKeys.Type.Bing, 2, 3, (byte)2)));
                Assert.IsTrue(key.isMyAncestor(new QuadKey(
                    QuadKeys.Type.Bing, 0, 0, (byte)0)));

                QuadKey none = new QuadKey();
                Assert.IsFalse(none.isMyAncestor(new QuadKey()));
            }

            {
                QuadKey key = new QuadKey(QuadKeys.Type.Bing, 5, 7, (byte)3);
                Assert.IsFalse(key.isMyAncestor(new QuadKey()));
                Assert.IsFalse(key.isMyAncestor(new QuadKey(
                    QuadKeys.Type.OsGeo, 2, 3, (byte)2)));
                Assert.IsFalse(key.isMyAncestor(new QuadKey(
                    QuadKeys.Type.OsGeo, 0, 0, (byte)0)));
                Assert.IsFalse(key.isMyAncestor(new QuadKey(
                    QuadKeys.Type.Bing, 5, 7, (byte)3)));
                Assert.IsTrue(key.isMyAncestor(new QuadKey(
                    QuadKeys.Type.Bing, 2, 3, (byte)2)));
                Assert.IsTrue(key.isMyAncestor(new QuadKey(
                    QuadKeys.Type.Bing, 0, 0, (byte)0)));

                QuadKey none = new QuadKey();
                Assert.IsFalse(none.isMyAncestor(new QuadKey()));
            }
        }

        [TestMethod]
        public void TestGetAncestor()
        {
            {
                QuadKey key = new QuadKey(QuadKeys.Type.Bing, 0, 7, (byte)3);
                QuadKey ancestor = new QuadKey(QuadKeys.Type.Bing, 0, 1,
                    (byte)1);
                Assert.IsTrue(ancestor.EqualTo(key.getAncestor((byte)2)));
            }

            {
                QuadKey key = new QuadKey(QuadKeys.Type.Bing, 4, 31, (byte)5);
                QuadKey ancestor = new QuadKey(QuadKeys.Type.Bing, 0, 1,
                    (byte)1);
                Assert.IsTrue(ancestor.EqualTo(key.getAncestor((byte)4)));
            }

            {
                QuadKey key = new QuadKey(QuadKeys.Type.Bing, 4, 31, (byte)5);
                QuadKey ancestor = new QuadKey(QuadKeys.Type.Bing, 0, 3,
                    (byte)2);
                Assert.IsTrue(ancestor.EqualTo(key.getAncestor((byte)3)));
            }

            {
                QuadKey key = new QuadKey(QuadKeys.Type.Bing, 4, 31, (byte)5);
                QuadKey ancestor = new QuadKey(QuadKeys.Type.Bing, 1, 7,
                    (byte)3);
                Assert.IsTrue(ancestor.EqualTo(key.getAncestor((byte)2)));
            }
        }

        [TestMethod]
        public void TestGetChild()
        {
            Assert.IsTrue(new QuadKey().EqualTo(
                new QuadKey().getChild(QuadKeys.QuadKey.Quadrant.NorthWest)));
            byte maxDepthBing = QuadKey.maxDepth(QuadKeys.Type.Bing);
            Assert.IsTrue(new QuadKey().EqualTo(
                new QuadKey(QuadKeys.Type.Bing, 0, 0, maxDepthBing).getChild(
                QuadKeys.QuadKey.Quadrant.NorthEast)));

            {
                QuadKey key = new QuadKey(QuadKeys.Type.Bing, 0, 0, (byte)3);
                Assert.IsTrue(new QuadKey(QuadKeys.Type.Bing, 1, 0,
                    (byte)4).EqualTo(key.getChild(
                    QuadKeys.QuadKey.Quadrant.NorthWest)));
                Assert.IsTrue(new QuadKey(QuadKeys.Type.Bing, 1, 1,
                    (byte)4).EqualTo(key.getChild(
                    QuadKeys.QuadKey.Quadrant.NorthEast)));
                Assert.IsTrue(new QuadKey(QuadKeys.Type.Bing, 0, 1,
                    (byte)4).EqualTo(key.getChild(
                    QuadKeys.QuadKey.Quadrant.SouthEast)));
                Assert.IsTrue(new QuadKey(QuadKeys.Type.Bing, 0, 0,
                    (byte)4).EqualTo(key.getChild(
                    QuadKeys.QuadKey.Quadrant.SouthWest)));
            }

            {
                QuadKey key = new QuadKey(QuadKeys.Type.Bing, 2, 3, (byte)3);
                Assert.IsTrue(new QuadKey(QuadKeys.Type.Bing, 5, 6,
                    (byte)4).EqualTo(key.getChild(
                    QuadKeys.QuadKey.Quadrant.NorthWest)));
                Assert.IsTrue(new QuadKey(QuadKeys.Type.Bing, 5, 7,
                    (byte)4).EqualTo(key.getChild(
                    QuadKeys.QuadKey.Quadrant.NorthEast)));
                Assert.IsTrue(new QuadKey(QuadKeys.Type.Bing, 4, 7,
                    (byte)4).EqualTo(key.getChild(
                    QuadKeys.QuadKey.Quadrant.SouthEast)));
                Assert.IsTrue(new QuadKey(QuadKeys.Type.Bing, 4, 6,
                    (byte)4).EqualTo(key.getChild(
                    QuadKeys.QuadKey.Quadrant.SouthWest)));
            }
        }

        [TestMethod]
        public void TestGetChildren()
        {
            QuadKeyVector testKeys;
            byte maxDepthBing = QuadKey.maxDepth(QuadKeys.Type.Bing);
            testKeys = new QuadKey(QuadKeys.Type.Bing, 0, 0,
                maxDepthBing).getChildren();

            Assert.AreEqual(0, testKeys.Count);

            QuadKey key0 = new QuadKey(QuadKeys.Type.Bing, 0, 0, (byte)1);
            testKeys = key0.getChildren();
            Assert.AreEqual(4, testKeys.Count);
            Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                QuadKeys.Type.Bing, 0, 0, (byte)2)));
            Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                QuadKeys.Type.Bing, 0, 1, (byte)2)));
            Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                QuadKeys.Type.Bing, 1, 0, (byte)2)));
            Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                QuadKeys.Type.Bing, 1, 1, (byte)2)));

            QuadKey key1 = new QuadKey(QuadKeys.Type.Bing, 0, 1, (byte)1);
            testKeys = key1.getChildren();
            Assert.AreEqual(4, testKeys.Count);
            Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                QuadKeys.Type.Bing, 0, 2, (byte)2)));
            Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                QuadKeys.Type.Bing, 0, 3, (byte)2)));
            Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                QuadKeys.Type.Bing, 1, 2, (byte)2)));
            Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                QuadKeys.Type.Bing, 1, 3, (byte)2)));

            QuadKey key2 = new QuadKey(QuadKeys.Type.Bing, 1, 0, (byte)1);
            testKeys = key2.getChildren();
            Assert.AreEqual(4, testKeys.Count);
            Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                QuadKeys.Type.Bing, 2, 0, (byte)2)));
            Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                QuadKeys.Type.Bing, 2, 1, (byte)2)));
            Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                QuadKeys.Type.Bing, 3, 0, (byte)2)));
            Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                    QuadKeys.Type.Bing, 3, 1, (byte)2)));

            QuadKey key3 = new QuadKey(QuadKeys.Type.Bing, 1, 1, (byte)1);
            testKeys = key3.getChildren();
            Assert.AreEqual(4, testKeys.Count);
            Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                QuadKeys.Type.Bing, 2, 2, (byte)2)));
            Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                QuadKeys.Type.Bing, 2, 3, (byte)2)));
            Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                QuadKeys.Type.Bing, 3, 2, (byte)2)));
            Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                QuadKeys.Type.Bing, 3, 3, (byte)2)));
        }

        [TestMethod]
        public void TestGetDescendants()
        {
            byte bingMaxDepth = QuadKey.maxDepth(QuadKeys.Type.Bing);
            byte requetedDepth = (byte)(bingMaxDepth - 3);
            QuadKey key = new QuadKey(QuadKeys.Type.Bing, 0, 0, requetedDepth);
            QuadKeyVector testKeys;

            /* We are going beyond the max depth */
            testKeys = key.getDescendants((byte)4);
            Assert.AreEqual(0, testKeys.Count);

            QuadKey none = new QuadKey();
            testKeys = none.getDescendants((byte)1);
            Assert.AreEqual(0, testKeys.Count);

            {
                QuadKey bingKey = new QuadKey(QuadKeys.Type.Bing, 0, 0,
                    (byte)0);
                testKeys = bingKey.getDescendants((byte)0);
                Assert.AreEqual(0, testKeys.Count);
            }

            {
                QuadKey bingKey = new QuadKey(QuadKeys.Type.Bing, 0, 0,
                    (byte)0);
                testKeys = bingKey.getDescendants((byte)1);
                Assert.AreEqual(4, testKeys.Count);
                Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                    QuadKeys.Type.Bing, 0, 0, (byte)1)));
                Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                    QuadKeys.Type.Bing, 0, 1, (byte)1)));
                Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                    QuadKeys.Type.Bing, 1, 0, (byte)1)));
                Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                    QuadKeys.Type.Bing, 1, 1, (byte)1)));

                testKeys = bingKey.getDescendants((byte)2);
                Assert.AreEqual(16, testKeys.Count);
                Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                    QuadKeys.Type.Bing, 0, 0, (byte)2)));
                Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                    QuadKeys.Type.Bing, 0, 1, (byte)2)));
                Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                    QuadKeys.Type.Bing, 0, 2, (byte)2)));
                Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                    QuadKeys.Type.Bing, 0, 3, (byte)2)));
                Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                    QuadKeys.Type.Bing, 1, 0, (byte)2)));
                Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                    QuadKeys.Type.Bing, 1, 1, (byte)2)));
                Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                    QuadKeys.Type.Bing, 1, 2, (byte)2)));
                Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                    QuadKeys.Type.Bing, 1, 3, (byte)2)));
                Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                    QuadKeys.Type.Bing, 2, 0, (byte)2)));
                Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                    QuadKeys.Type.Bing, 2, 1, (byte)2)));
                Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                    QuadKeys.Type.Bing, 2, 2, (byte)2)));
                Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                    QuadKeys.Type.Bing, 2, 3, (byte)2)));
                Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                    QuadKeys.Type.Bing, 3, 0, (byte)2)));
                Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                    QuadKeys.Type.Bing, 3, 1, (byte)2)));
                Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                    QuadKeys.Type.Bing, 3, 2, (byte)2)));
                Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                    QuadKeys.Type.Bing, 3, 3, (byte)2)));

                testKeys = bingKey.getDescendants((byte)3);
                Assert.AreEqual(64, testKeys.Count);
                Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                    QuadKeys.Type.Bing, 0, 0, (byte)3)));
                Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                    QuadKeys.Type.Bing, 0, 1, (byte)3)));
                Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                    QuadKeys.Type.Bing, 0, 2, (byte)3)));
                Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                    QuadKeys.Type.Bing, 0, 3, (byte)3)));
                Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                    QuadKeys.Type.Bing, 0, 4, (byte)3)));
                Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                    QuadKeys.Type.Bing, 0, 5, (byte)3)));
                Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                    QuadKeys.Type.Bing, 0, 6, (byte)3)));
                Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                    QuadKeys.Type.Bing, 0, 7, (byte)3)));
                Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                    QuadKeys.Type.Bing, 1, 0, (byte)3)));
                Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                    QuadKeys.Type.Bing, 1, 1, (byte)3)));
                Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                    QuadKeys.Type.Bing, 1, 2, (byte)3)));
                Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                    QuadKeys.Type.Bing, 1, 3, (byte)3)));
                Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                    QuadKeys.Type.Bing, 1, 4, (byte)3)));
                Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                    QuadKeys.Type.Bing, 1, 5, (byte)3)));
                Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                    QuadKeys.Type.Bing, 1, 6, (byte)3)));
                Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                    QuadKeys.Type.Bing, 1, 7, (byte)3)));
                Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                    QuadKeys.Type.Bing, 2, 0, (byte)3)));
                Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                    QuadKeys.Type.Bing, 2, 1, (byte)3)));
                Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                    QuadKeys.Type.Bing, 2, 2, (byte)3)));
                Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                    QuadKeys.Type.Bing, 2, 3, (byte)3)));
                Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                    QuadKeys.Type.Bing, 2, 4, (byte)3)));
                Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                    QuadKeys.Type.Bing, 2, 5, (byte)3)));
                Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                    QuadKeys.Type.Bing, 2, 6, (byte)3)));
                Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                    QuadKeys.Type.Bing, 2, 7, (byte)3)));
                Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                    QuadKeys.Type.Bing, 3, 0, (byte)3)));
                Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                    QuadKeys.Type.Bing, 3, 1, (byte)3)));
                Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                    QuadKeys.Type.Bing, 3, 2, (byte)3)));
                Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                    QuadKeys.Type.Bing, 3, 3, (byte)3)));
                Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                    QuadKeys.Type.Bing, 3, 4, (byte)3)));
                Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                    QuadKeys.Type.Bing, 3, 5, (byte)3)));
                Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                    QuadKeys.Type.Bing, 3, 6, (byte)3)));
                Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                    QuadKeys.Type.Bing, 3, 7, (byte)3)));
                Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                    QuadKeys.Type.Bing, 4, 0, (byte)3)));
                Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                    QuadKeys.Type.Bing, 4, 1, (byte)3)));
                Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                    QuadKeys.Type.Bing, 4, 2, (byte)3)));
                Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                    QuadKeys.Type.Bing, 4, 3, (byte)3)));
                Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                    QuadKeys.Type.Bing, 4, 4, (byte)3)));
                Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                    QuadKeys.Type.Bing, 4, 5, (byte)3)));
                Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                    QuadKeys.Type.Bing, 4, 6, (byte)3)));
                Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                    QuadKeys.Type.Bing, 4, 7, (byte)3)));
                Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                    QuadKeys.Type.Bing, 5, 0, (byte)3)));
                Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                    QuadKeys.Type.Bing, 5, 1, (byte)3)));
                Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                    QuadKeys.Type.Bing, 5, 2, (byte)3)));
                Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                    QuadKeys.Type.Bing, 5, 3, (byte)3)));
                Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                    QuadKeys.Type.Bing, 5, 4, (byte)3)));
                Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                    QuadKeys.Type.Bing, 5, 5, (byte)3)));
                Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                    QuadKeys.Type.Bing, 5, 6, (byte)3)));
                Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                    QuadKeys.Type.Bing, 5, 7, (byte)3)));
                Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                    QuadKeys.Type.Bing, 6, 0, (byte)3)));
                Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                    QuadKeys.Type.Bing, 6, 1, (byte)3)));
                Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                    QuadKeys.Type.Bing, 6, 2, (byte)3)));
                Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                    QuadKeys.Type.Bing, 6, 3, (byte)3)));
                Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                    QuadKeys.Type.Bing, 6, 4, (byte)3)));
                Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                    QuadKeys.Type.Bing, 6, 5, (byte)3)));
                Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                    QuadKeys.Type.Bing, 6, 6, (byte)3)));
                Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                    QuadKeys.Type.Bing, 6, 7, (byte)3)));
                Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                    QuadKeys.Type.Bing, 7, 0, (byte)3)));
                Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                    QuadKeys.Type.Bing, 7, 1, (byte)3)));
                Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                    QuadKeys.Type.Bing, 7, 2, (byte)3)));
                Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                    QuadKeys.Type.Bing, 7, 3, (byte)3)));
                Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                    QuadKeys.Type.Bing, 7, 4, (byte)3)));
                Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                    QuadKeys.Type.Bing, 7, 5, (byte)3)));
                Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                    QuadKeys.Type.Bing, 7, 6, (byte)3)));
                Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                    QuadKeys.Type.Bing, 7, 7, (byte)3)));
            }
        }

        [TestMethod]
        public void TestGetSiblings()
        {
            QuadKeyVector testKeys;

            QuadKey none = new QuadKey();
            testKeys = none.getSiblings();
            Assert.AreEqual(0, testKeys.Count);

            QuadKey root = new QuadKey(QuadKeys.Type.Bing, 0, 0, (byte)0);
            testKeys = root.getSiblings();
            Assert.AreEqual(0, testKeys.Count);

            QuadKey bingKey = new QuadKey(QuadKeys.Type.Bing, 0, 0, (byte)1);
            testKeys = bingKey.getSiblings();
            Assert.AreEqual(3, testKeys.Count);
            Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                QuadKeys.Type.Bing, 0, 1, (byte)1)));
            Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                QuadKeys.Type.Bing, 1, 1, (byte)1)));
            Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                QuadKeys.Type.Bing, 1, 0, (byte)1)));
        }

        [TestMethod]
        public void TestGetNeighbors()
        {
            QuadKeyVector testKeys;

            QuadKey none = new QuadKey();
            testKeys = none.getNeighbors();
            Assert.AreEqual(0, testKeys.Count);

            QuadKey root = new QuadKey(QuadKeys.Type.Bing, 0, 0, (byte)0);
            testKeys = root.getNeighbors();
            Assert.AreEqual(0, testKeys.Count);

            QuadKey key0 = new QuadKey(QuadKeys.Type.Bing, 0, 0, (byte)2);
            testKeys = key0.getNeighbors();
            Assert.AreEqual(5, testKeys.Count);
            Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                QuadKeys.Type.Bing, 0, 1, (byte)2)));
            Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                QuadKeys.Type.Bing, 1, 1, (byte)2)));
            Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                QuadKeys.Type.Bing, 1, 0, (byte)2)));
            Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                QuadKeys.Type.Bing, 0, 3, (byte)2)));
            Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                QuadKeys.Type.Bing, 1, 3, (byte)2)));

            QuadKey key;

            key = new QuadKey(QuadKeys.Type.Bing, 0, 1, (byte)2);
            testKeys = key.getNeighbors();
            Assert.AreEqual(5, testKeys.Count);
            Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                QuadKeys.Type.Bing, 0, 0, (byte)2)));
            Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                QuadKeys.Type.Bing, 1, 0, (byte)2)));
            Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                QuadKeys.Type.Bing, 1, 1, (byte)2)));
            Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                QuadKeys.Type.Bing, 1, 2, (byte)2)));
            Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                QuadKeys.Type.Bing, 0, 2, (byte)2)));

            key = new QuadKey(QuadKeys.Type.Bing, 0, 2, (byte)2);
            testKeys = key.getNeighbors();
            Assert.AreEqual(5, testKeys.Count);
            Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                QuadKeys.Type.Bing, 0, 1, (byte)2)));
            Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                QuadKeys.Type.Bing, 1, 1, (byte)2)));
            Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                QuadKeys.Type.Bing, 1, 2, (byte)2)));
            Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                QuadKeys.Type.Bing, 1, 3, (byte)2)));
            Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                QuadKeys.Type.Bing, 0, 3, (byte)2)));

            key = new QuadKey(QuadKeys.Type.Bing, 0, 3, (byte)2);
            testKeys = key.getNeighbors();
            Assert.AreEqual(5, testKeys.Count);
            Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                QuadKeys.Type.Bing, 0, 2, (byte)2)));
            Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                QuadKeys.Type.Bing, 1, 2, (byte)2)));
            Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                QuadKeys.Type.Bing, 1, 3, (byte)2)));
            Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                QuadKeys.Type.Bing, 1, 0, (byte)2)));
            Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                QuadKeys.Type.Bing, 0, 0, (byte)2)));

            key = new QuadKey(QuadKeys.Type.Bing, 1, 0, (byte)2);
            testKeys = key.getNeighbors();
            Assert.AreEqual(8, testKeys.Count);
            Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                QuadKeys.Type.Bing, 0, 0, (byte)2)));
            Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                QuadKeys.Type.Bing, 0, 1, (byte)2)));
            Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                QuadKeys.Type.Bing, 1, 1, (byte)2)));
            Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                QuadKeys.Type.Bing, 2, 1, (byte)2)));
            Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                QuadKeys.Type.Bing, 2, 0, (byte)2)));
            Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                QuadKeys.Type.Bing, 2, 3, (byte)2)));
            Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                QuadKeys.Type.Bing, 1, 3, (byte)2)));
            Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                QuadKeys.Type.Bing, 0, 3, (byte)2)));

            key = new QuadKey(QuadKeys.Type.Bing, 1, 1, (byte)2);
            testKeys = key.getNeighbors();
            Assert.AreEqual(8, testKeys.Count);
            Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                QuadKeys.Type.Bing, 1, 0, (byte)2)));
            Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                QuadKeys.Type.Bing, 0, 0, (byte)2)));
            Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                QuadKeys.Type.Bing, 0, 1, (byte)2)));
            Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                QuadKeys.Type.Bing, 2, 2, (byte)2)));
            Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                QuadKeys.Type.Bing, 2, 1, (byte)2)));
            Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                QuadKeys.Type.Bing, 2, 0, (byte)2)));
            Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                QuadKeys.Type.Bing, 0, 2, (byte)2)));
            Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                QuadKeys.Type.Bing, 1, 2, (byte)2)));

            key = new QuadKey(QuadKeys.Type.Bing, 1, 2, (byte)2);
            testKeys = key.getNeighbors();
            Assert.AreEqual(8, testKeys.Count);
            Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                QuadKeys.Type.Bing, 1, 1, (byte)2)));
            Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                QuadKeys.Type.Bing, 0, 1, (byte)2)));
            Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                QuadKeys.Type.Bing, 0, 2, (byte)2)));
            Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                QuadKeys.Type.Bing, 2, 3, (byte)2)));
            Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                QuadKeys.Type.Bing, 2, 2, (byte)2)));
            Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                QuadKeys.Type.Bing, 2, 1, (byte)2)));
            Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                QuadKeys.Type.Bing, 0, 3, (byte)2)));
            Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                QuadKeys.Type.Bing, 1, 3, (byte)2)));

            key = new QuadKey(QuadKeys.Type.Bing, 1, 3, (byte)2);
            testKeys = key.getNeighbors();
            Assert.AreEqual(8, testKeys.Count);
            Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                QuadKeys.Type.Bing, 1, 2, (byte)2)));
            Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                QuadKeys.Type.Bing, 0, 2, (byte)2)));
            Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                QuadKeys.Type.Bing, 0, 3, (byte)2)));
            Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                QuadKeys.Type.Bing, 2, 0, (byte)2)));
            Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                QuadKeys.Type.Bing, 2, 3, (byte)2)));
            Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                QuadKeys.Type.Bing, 2, 2, (byte)2)));
            Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                QuadKeys.Type.Bing, 0, 0, (byte)2)));
            Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                QuadKeys.Type.Bing, 1, 0, (byte)2)));

            key = new QuadKey(QuadKeys.Type.Bing, 4, 7, (byte)3);
            testKeys = key.getNeighbors();
            Assert.AreEqual(8, testKeys.Count);
            Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                QuadKeys.Type.Bing, 3, 7, (byte)3)));
            Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                QuadKeys.Type.Bing, 3, 6, (byte)3)));
            Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                QuadKeys.Type.Bing, 4, 6, (byte)3)));
            Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                QuadKeys.Type.Bing, 5, 6, (byte)3)));
            Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                QuadKeys.Type.Bing, 5, 7, (byte)3)));
            Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                QuadKeys.Type.Bing, 5, 0, (byte)3)));
            Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                QuadKeys.Type.Bing, 4, 0, (byte)3)));
            Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                QuadKeys.Type.Bing, 3, 0, (byte)3)));

            key = new QuadKey(QuadKeys.Type.Bing, 4, 0, (byte)3);
            testKeys = key.getNeighbors();
            Assert.AreEqual(8, testKeys.Count);
            Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                QuadKeys.Type.Bing, 3, 0, (byte)3)));
            Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                QuadKeys.Type.Bing, 3, 1, (byte)3)));
            Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                QuadKeys.Type.Bing, 4, 1, (byte)3)));
            Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                QuadKeys.Type.Bing, 5, 1, (byte)3)));
            Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                QuadKeys.Type.Bing, 5, 0, (byte)3)));
            Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                QuadKeys.Type.Bing, 5, 7, (byte)3)));
            Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                QuadKeys.Type.Bing, 4, 7, (byte)3)));
            Assert.IsTrue(VectorContains(testKeys, new QuadKey(
                QuadKeys.Type.Bing, 3, 7, (byte)3)));
        }

        [TestMethod]
        public void TestFromInternalStringToString()
        {
            {
                QuadKey root = QuadKey.fromInternalString(QuadKeys.Type.Bing,
                    "");
                Assert.AreEqual(0u, root.getRow());
                Assert.AreEqual(0u, root.getCol());
                Assert.AreEqual((byte)0, root.getDepth());
            }

            {
                QuadKey key;
                key = QuadKey.fromInternalString(QuadKeys.Type.Bing, "0");
                Assert.AreEqual(1u, key.getRow());
                Assert.AreEqual(0u, key.getCol());
                Assert.AreEqual((byte)1, key.getDepth());
                Assert.AreEqual("0", key.toInternalString());
                key = QuadKey.fromInternalString(QuadKeys.Type.Bing, "1");
                Assert.AreEqual(1u, key.getRow());
                Assert.AreEqual(1u, key.getCol());
                Assert.AreEqual((byte)1, key.getDepth());
                Assert.AreEqual("1", key.toInternalString());
                key = QuadKey.fromInternalString(QuadKeys.Type.Bing, "2");
                Assert.AreEqual(0u, key.getRow());
                Assert.AreEqual(0u, key.getCol());
                Assert.AreEqual((byte)1, key.getDepth());
                Assert.AreEqual("2", key.toInternalString());
                key = QuadKey.fromInternalString(QuadKeys.Type.Bing, "3");
                Assert.AreEqual(0u, key.getRow());
                Assert.AreEqual(1u, key.getCol());
                Assert.AreEqual((byte)1, key.getDepth());
                Assert.AreEqual("3", key.toInternalString());
            }

            {
                QuadKey key;
                key = QuadKey.fromInternalString(QuadKeys.Type.Bing, "00");
                Assert.AreEqual(3u, key.getRow());
                Assert.AreEqual(0u, key.getCol());
                Assert.AreEqual((byte)2, key.getDepth());
                Assert.AreEqual("00", key.toInternalString());
                key = QuadKey.fromInternalString(QuadKeys.Type.Bing, "01");
                Assert.AreEqual(3u, key.getRow());
                Assert.AreEqual(1u, key.getCol());
                Assert.AreEqual((byte)2, key.getDepth());
                Assert.AreEqual("01", key.toInternalString());
                key = QuadKey.fromInternalString(QuadKeys.Type.Bing, "02");
                Assert.AreEqual(2u, key.getRow());
                Assert.AreEqual(0u, key.getCol());
                Assert.AreEqual((byte)2, key.getDepth());
                Assert.AreEqual("02", key.toInternalString());
                key = QuadKey.fromInternalString(QuadKeys.Type.Bing, "03");
                Assert.AreEqual(2u, key.getRow());
                Assert.AreEqual(1u, key.getCol());
                Assert.AreEqual((byte)2, key.getDepth());
                Assert.AreEqual("03", key.toInternalString());
                key = QuadKey.fromInternalString(QuadKeys.Type.Bing, "10");
                Assert.AreEqual(3u, key.getRow());
                Assert.AreEqual(2u, key.getCol());
                Assert.AreEqual((byte)2, key.getDepth());
                Assert.AreEqual("10", key.toInternalString());
                key = QuadKey.fromInternalString(QuadKeys.Type.Bing, "11");
                Assert.AreEqual(3u, key.getRow());
                Assert.AreEqual(3u, key.getCol());
                Assert.AreEqual((byte)2, key.getDepth());
                Assert.AreEqual("11", key.toInternalString());
                key = QuadKey.fromInternalString(QuadKeys.Type.Bing, "12");
                Assert.AreEqual(2u, key.getRow());
                Assert.AreEqual(2u, key.getCol());
                Assert.AreEqual((byte)2, key.getDepth());
                Assert.AreEqual("12", key.toInternalString());
                key = QuadKey.fromInternalString(QuadKeys.Type.Bing, "13");
                Assert.AreEqual(2u, key.getRow());
                Assert.AreEqual(3u, key.getCol());
                Assert.AreEqual((byte)2, key.getDepth());
                Assert.AreEqual("13", key.toInternalString());
                key = QuadKey.fromInternalString(QuadKeys.Type.Bing, "20");
                Assert.AreEqual(1u, key.getRow());
                Assert.AreEqual(0u, key.getCol());
                Assert.AreEqual((byte)2, key.getDepth());
                Assert.AreEqual("20", key.toInternalString());
                key = QuadKey.fromInternalString(QuadKeys.Type.Bing, "21");
                Assert.AreEqual(1u, key.getRow());
                Assert.AreEqual(1u, key.getCol());
                Assert.AreEqual((byte)2, key.getDepth());
                Assert.AreEqual("21", key.toInternalString());
                key = QuadKey.fromInternalString(QuadKeys.Type.Bing, "22");
                Assert.AreEqual(0u, key.getRow());
                Assert.AreEqual(0u, key.getCol());
                Assert.AreEqual((byte)2, key.getDepth());
                Assert.AreEqual("22", key.toInternalString());
                key = QuadKey.fromInternalString(QuadKeys.Type.Bing, "23");
                Assert.AreEqual(0u, key.getRow());
                Assert.AreEqual(1u, key.getCol());
                Assert.AreEqual((byte)2, key.getDepth());
                Assert.AreEqual("23", key.toInternalString());
                key = QuadKey.fromInternalString(QuadKeys.Type.Bing, "30");
                Assert.AreEqual(1u, key.getRow());
                Assert.AreEqual(2u, key.getCol());
                Assert.AreEqual((byte)2, key.getDepth());
                Assert.AreEqual("30", key.toInternalString());
                key = QuadKey.fromInternalString(QuadKeys.Type.Bing, "31");
                Assert.AreEqual(1u, key.getRow());
                Assert.AreEqual(3u, key.getCol());
                Assert.AreEqual((byte)2, key.getDepth());
                Assert.AreEqual("31", key.toInternalString());
                key = QuadKey.fromInternalString(QuadKeys.Type.Bing, "32");
                Assert.AreEqual(0u, key.getRow());
                Assert.AreEqual(2u, key.getCol());
                Assert.AreEqual((byte)2, key.getDepth());
                Assert.AreEqual("32", key.toInternalString());
                key = QuadKey.fromInternalString(QuadKeys.Type.Bing, "33");
                Assert.AreEqual(0u, key.getRow());
                Assert.AreEqual(3u, key.getCol());
                Assert.AreEqual((byte)2, key.getDepth());
                Assert.AreEqual("33", key.toInternalString());
            }
        }

        [TestMethod]
        public void TestGetGeoCoordinateBounds2dTest()
        {
            QuadKey key;
            GeoCoordinateBoundingBox2d bbox = new GeoCoordinateBoundingBox2d();

            key = QuadKey.fromInternalString(QuadKeys.Type.Bing, "");
            key.getGeoCoordinateBounds2d(bbox);
            Assert.AreEqual(-180.0, bbox.lowerLeft().longitude().val(),
                1e-7);
            Assert.AreEqual(-84.9283209, bbox.lowerLeft().latitude().val(),
                1e-7);
            Assert.AreEqual(178.593750, bbox.upperRight().longitude().val(),
                1e-7);
            Assert.AreEqual(85.05112877, bbox.upperRight().latitude().val(),
                1e-7);
        }

        [TestMethod]
        public void TestGetKeyFromLongitudeLatitudeAtDepthToBounds()
        {
            QuadKey key;
            GeoCoordinateBoundingBox2d bbox = new GeoCoordinateBoundingBox2d();
            double diff;

            { // Depth 0
                key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    QuadKeys.Type.Bing,
                    new GeoCoordinate2d(new Longitude(-180.0),
                    new Latitude(-84.0)), (byte)0);
                Assert.IsTrue(new QuadKey(QuadKeys.Type.Bing, 0, 0,
                    (byte)0).EqualTo(key));
                key.getGeoCoordinateBounds2d(bbox);
                diff = Math.Abs(
                    bbox.lowerLeft().longitude().LongitudeDifference(
                    new Longitude(-180.0)));
                Assert.IsTrue(2.0 > diff);
                diff = Math.Abs(
                    bbox.lowerLeft().latitude().LatitudeDifference(
                    new Latitude(-85.0)));
                Assert.IsTrue(2.0 > diff);
                diff = Math.Abs(
                    bbox.upperRight().longitude().LongitudeDifference(
                    new Longitude(+180.0)));
                Assert.IsTrue(2.0 > diff);
                diff = Math.Abs(
                    bbox.upperRight().latitude().LatitudeDifference(
                    new Latitude(+85.0)));
                Assert.IsTrue(2.0 > diff);
            }

            // Inclusion here consists of upper left
            // ul X------X------X
            //    |      |      |
            //    |      |      |
            //    X------X------X
            //    |      |      |
            //    |      |      |
            //    X------X------X
            Longitude left = new Longitude(-180.0);
            Longitude midLeft = new Longitude(-0.36);
            Longitude midRight = new Longitude(0.0);
            Longitude right = new Longitude(+180.0);
            Latitude bottom = new Latitude(-90.0);
            Latitude midBottom = new Latitude(0.0);
            Latitude midTop = new Latitude(0.36);
            Latitude top = new Latitude(+90.0);

            { // Depth 1
                key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    QuadKeys.Type.Bing, new GeoCoordinate2d(left, top),
                    (byte)1);
                Assert.IsTrue(new QuadKey(QuadKeys.Type.Bing, 1, 0,
                    (byte)1).EqualTo(key));
                key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    QuadKeys.Type.Bing, new GeoCoordinate2d(left, midTop),
                    (byte)1);
                Assert.IsTrue(new QuadKey(QuadKeys.Type.Bing, 1, 0,
                    (byte)1).EqualTo(key));
                key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    QuadKeys.Type.Bing, new GeoCoordinate2d(midLeft, midTop),
                    (byte)1);
                Assert.IsTrue(new QuadKey(QuadKeys.Type.Bing, 1, 0,
                    (byte)1).EqualTo(key));
                key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    QuadKeys.Type.Bing, new GeoCoordinate2d(midLeft, top),
                    (byte)1);
                Assert.IsTrue(new QuadKey(QuadKeys.Type.Bing, 1, 0,
                    (byte)1).EqualTo(key));
                key.getGeoCoordinateBounds2d(bbox);
                diff = Math.Abs(
                    bbox.lowerLeft().longitude().LongitudeDifference(left));
                Assert.IsTrue(2.0 > diff);
                diff = Math.Abs(
                    bbox.lowerLeft().latitude().LatitudeDifference(midTop));
                Assert.IsTrue(2.0 > diff);
                diff = Math.Abs(
                    bbox.upperRight().longitude().LongitudeDifference(midLeft));
                Assert.IsTrue(2.0 > diff);
                diff = Math.Abs(
                    bbox.upperRight().latitude().LatitudeDifference(
                    new Latitude(+85.0)));
                Assert.IsTrue(2.0 > diff);

                key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    QuadKeys.Type.Bing, new GeoCoordinate2d(midRight, top),
                    (byte)1);
                Assert.IsTrue(new QuadKey(QuadKeys.Type.Bing, 1, 1,
                    (byte)1).EqualTo(key));
                key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    QuadKeys.Type.Bing, new GeoCoordinate2d(midRight, midTop),
                    (byte)1);
                Assert.IsTrue(new QuadKey(QuadKeys.Type.Bing, 1, 1,
                    (byte)1).EqualTo(key));
                key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    QuadKeys.Type.Bing, new GeoCoordinate2d(right, midTop),
                    (byte)1);
                Assert.IsTrue(new QuadKey(QuadKeys.Type.Bing, 1, 1,
                    (byte)1).EqualTo(key));
                key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    QuadKeys.Type.Bing, new GeoCoordinate2d(right, top),
                    (byte)1);
                Assert.IsTrue(new QuadKey(QuadKeys.Type.Bing, 1, 1,
                    (byte)1).EqualTo(key));
                key.getGeoCoordinateBounds2d(bbox);
                diff = Math.Abs(
                    bbox.lowerLeft().longitude().LongitudeDifference(midRight));
                Assert.IsTrue(2.0 > diff);
                diff = Math.Abs(
                    bbox.lowerLeft().latitude().LatitudeDifference(midTop));
                Assert.IsTrue(2.0 > diff);
                diff = Math.Abs(
                    bbox.upperRight().longitude().LongitudeDifference(right));
                Assert.IsTrue(2.0 > diff);
                diff = Math.Abs(bbox.upperRight().latitude().LatitudeDifference(
                    new Latitude(+85.0)));
                Assert.IsTrue(2.0 > diff);

                key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    QuadKeys.Type.Bing, new GeoCoordinate2d(left, midBottom),
                    (byte)1);
                Assert.IsTrue(new QuadKey(QuadKeys.Type.Bing, 0, 0,
                    (byte)1).EqualTo(key));
                key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    QuadKeys.Type.Bing, new GeoCoordinate2d(left, bottom),
                    (byte)1);
                Assert.IsTrue(new QuadKey(QuadKeys.Type.Bing, 0, 0,
                    (byte)1).EqualTo(key));
                key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    QuadKeys.Type.Bing, new GeoCoordinate2d(midLeft, bottom),
                    (byte)1);
                Assert.IsTrue(new QuadKey(QuadKeys.Type.Bing, 0, 0,
                    (byte)1).EqualTo(key));
                key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    QuadKeys.Type.Bing,
                    new GeoCoordinate2d(midLeft, midBottom), (byte)1);
                Assert.IsTrue(new QuadKey(QuadKeys.Type.Bing, 0, 0,
                    (byte)1).EqualTo(key));
                key.getGeoCoordinateBounds2d(bbox);
                diff = Math.Abs(
                    bbox.lowerLeft().longitude().LongitudeDifference(left));
                Assert.IsTrue(2.0 > diff);
                diff = Math.Abs(
                    bbox.lowerLeft().latitude().LatitudeDifference(
                    new Latitude(-85.0)));
                Assert.IsTrue(2.0 > diff);
                diff = Math.Abs(
                    bbox.upperRight().longitude().LongitudeDifference(midLeft));
                Assert.IsTrue(2.0 > diff);
                diff = Math.Abs(
                    bbox.upperRight().latitude().LatitudeDifference(midBottom));
                Assert.IsTrue(2.0 > diff);

                key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    QuadKeys.Type.Bing,
                    new GeoCoordinate2d(midRight, midBottom), (byte)1);
                Assert.IsTrue(new QuadKey(QuadKeys.Type.Bing, 0, 1,
                    (byte)1).EqualTo(key));
                key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    QuadKeys.Type.Bing,
                    new GeoCoordinate2d(midRight, bottom), (byte)1);
                Assert.IsTrue(new QuadKey(QuadKeys.Type.Bing, 0, 1,
                    (byte)1).EqualTo(key));
                key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    QuadKeys.Type.Bing, new GeoCoordinate2d(right, bottom),
                    (byte)1);
                Assert.IsTrue(new QuadKey(QuadKeys.Type.Bing, 0, 1,
                    (byte)1).EqualTo(key));
                key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    QuadKeys.Type.Bing,
                    new GeoCoordinate2d(right, midBottom), (byte)1);
                Assert.IsTrue(new QuadKey(QuadKeys.Type.Bing, 0, 1,
                    (byte)1).EqualTo(key));
                key.getGeoCoordinateBounds2d(bbox);
                diff = Math.Abs(
                    bbox.lowerLeft().longitude().LongitudeDifference(midRight));
                Assert.IsTrue(2.0 > diff);
                diff = Math.Abs(
                    bbox.lowerLeft().latitude().LatitudeDifference(
                    new Latitude(-85.0)));
                Assert.IsTrue(2.0 > diff);
                diff = Math.Abs(
                    bbox.upperRight().longitude().LongitudeDifference(right));
                Assert.IsTrue(2.0 > diff);
                diff = Math.Abs(
                    bbox.upperRight().latitude().LatitudeDifference(midBottom));
                Assert.IsTrue(2.0 > diff);
            }
        }

        [TestMethod]
        public void TestGetKeysFromLongitudeLatitudeBoundingBox()
        {
            {
                QuadKeyVector outKeys;
                outKeys = QuadKey.getKeysFromLongitudeLatitudeBoundingBox(
                    QuadKeys.Type.Bing,
                    new GeoCoordinateBoundingBox2d(
                        new GeoCoordinate2d(
                            new Longitude(-180.0),
                            new Latitude(+90.0)),
                         new GeoCoordinate2d(
                            new Longitude(+180.0),
                            new Latitude(-90.0))), (byte)0);
                Assert.AreEqual(1, outKeys.Count);
                Assert.IsTrue(VectorContains(outKeys, new QuadKey(
                    QuadKeys.Type.Bing, 0, 0, (byte)0)));
            }

            {
                QuadKeyVector outKeys;
                outKeys = QuadKey.getKeysFromLongitudeLatitudeBoundingBox(
                    QuadKeys.Type.Bing,
                    new GeoCoordinateBoundingBox2d(
                        new GeoCoordinate2d(
                            new Longitude(-180.0),
                            new Latitude(+90.0)),
                        new GeoCoordinate2d(
                            new Longitude(+180.0),
                            new Latitude(-90.0))), (byte)1);
                Assert.AreEqual(4, outKeys.Count);
                Assert.IsTrue(VectorContains(outKeys, new QuadKey(
                    QuadKeys.Type.Bing, 0, 0, (byte)1)));
                Assert.IsTrue(VectorContains(outKeys, new QuadKey(
                    QuadKeys.Type.Bing, 0, 1, (byte)1)));
                Assert.IsTrue(VectorContains(outKeys, new QuadKey(
                    QuadKeys.Type.Bing, 1, 0, (byte)1)));
                Assert.IsTrue(VectorContains(outKeys, new QuadKey(
                    QuadKeys.Type.Bing, 1, 1, (byte)1)));
            }

            {
                QuadKeyVector outKeys;
                outKeys = QuadKey.getKeysFromLongitudeLatitudeBoundingBox(
                    QuadKeys.Type.Bing,
                    new GeoCoordinateBoundingBox2d(
                        new GeoCoordinate2d(
                            new Longitude(-180.0),
                            new Latitude(+0.35)),
                        new GeoCoordinate2d(
                            new Longitude(-0.36),
                            new Latitude(+90.0))), (byte) 1);
                Assert.AreEqual(2, outKeys.Count);
                Assert.IsTrue(VectorContains(outKeys, new QuadKey(
                    QuadKeys.Type.Bing, 0, 0, (byte) 1)));
                Assert.IsTrue(VectorContains(outKeys, new QuadKey(
                    QuadKeys.Type.Bing, 1, 0, (byte)1)));
            }

            {
                QuadKeyVector outKeys;
                outKeys = QuadKey.getKeysFromLongitudeLatitudeBoundingBox(
                    QuadKeys.Type.Bing,
                    new GeoCoordinateBoundingBox2d(
                        new GeoCoordinate2d(
                            new Longitude(-0.36),
                            new Latitude(+0.36)),
                        new GeoCoordinate2d(
                            new Longitude(+0.36),
                            new Latitude(+90.0))), (byte)1);
                Assert.AreEqual(2, outKeys.Count);
                Assert.IsTrue(VectorContains(outKeys, new QuadKey(
                    QuadKeys.Type.Bing, 1, 0, (byte) 1)));
                Assert.IsTrue(VectorContains(outKeys, new QuadKey(
                    QuadKeys.Type.Bing, 1, 1, (byte)1)));
            }

            {
                QuadKeyVector outKeys;
                outKeys = QuadKey.getKeysFromLongitudeLatitudeBoundingBox(
                    QuadKeys.Type.Bing,
                    new GeoCoordinateBoundingBox2d(
                        new GeoCoordinate2d(
                            new Longitude(-0.36),
                            new Latitude(+0.35)),
                        new GeoCoordinate2d(
                            new Longitude(+0.36),
                            new Latitude(+90.0))), (byte)1);
                Assert.AreEqual(4, outKeys.Count);
                Assert.IsTrue(VectorContains(outKeys, new QuadKey(
                    QuadKeys.Type.Bing, 0, 0, (byte)1)));
                Assert.IsTrue(VectorContains(outKeys, new QuadKey(
                    QuadKeys.Type.Bing, 0, 1, (byte)1)));
                Assert.IsTrue(VectorContains(outKeys, new QuadKey(
                    QuadKeys.Type.Bing, 1, 0, (byte)1)));
                Assert.IsTrue(VectorContains(outKeys, new QuadKey(
                    QuadKeys.Type.Bing, 1, 1, (byte)1)));
            }
        }

        [TestMethod]
        public void TestSelectedCities()
        {
            QuadKey key;
            QuadKeys.Type type = QuadKeys.Type.Bing;

            { // Chicago 41.822, -87.635
                byte depth = 16;
                GeoCoordinate2d coords = new GeoCoordinate2d(
                    new Longitude(-87.635), new Latitude(41.822));
                key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    type, coords, depth);
                String keyStr = key.toInternalString();
                Assert.AreEqual("0302222310321132", keyStr);
                GeoCoordinateBoundingBox2d bbox = new
                    GeoCoordinateBoundingBox2d();
                key.getGeoCoordinateBounds2d(bbox);
                // Note that Bing will return a bounding box of all sides
                // inclusive
                QuadKeyVector keys;
                keys = QuadKey.getKeysFromLongitudeLatitudeBoundingBox(
                    type, bbox, depth);
                Assert.AreEqual(4, keys.Count);
                Assert.IsTrue(VectorContains(keys, key));
            }

            { // Rio -43.1964,-22.9083
                byte depth = 17;
                GeoCoordinate2d coords = new GeoCoordinate2d(
                        new Longitude(-43.1964), new Latitude(-22.9083));
                key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    type, coords, depth);
                String keyStr = key.toInternalString();
                Assert.AreEqual("21120001212232200", keyStr);
                GeoCoordinateBoundingBox2d bbox =
                    new GeoCoordinateBoundingBox2d();
                key.getGeoCoordinateBounds2d(bbox);
                // Note that Bing will return a bounding box of all sides
                // inclusive
                QuadKeyVector keys;
                keys = QuadKey.getKeysFromLongitudeLatitudeBoundingBox(
                    type, bbox, depth);
                Assert.AreEqual(4, keys.Count);
                Assert.IsTrue(VectorContains(keys, key));
            }

            { // Helsinki 60.1708 N, 24.9375 E
                byte depth = 17;
                GeoCoordinate2d coords = new GeoCoordinate2d(
                    new Longitude(24.9375), new Latitude(60.1708));
                key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    type, coords, depth);
                String keyStr = key.toInternalString();
                Assert.AreEqual("12012021101330131", keyStr);
                GeoCoordinateBoundingBox2d bbox =
                    new GeoCoordinateBoundingBox2d();
                key.getGeoCoordinateBounds2d(bbox);
                // Note that Bing will return a bounding box of all sides
                // inclusive
                QuadKeyVector keys;
                keys = QuadKey.getKeysFromLongitudeLatitudeBoundingBox(
                    type, bbox, depth);
                Assert.AreEqual(4, keys.Count);
                Assert.IsTrue(VectorContains(keys, key));
            }

            { // Cape Town South Africa 33.9253 S, 18.4239 E
                byte depth = 17;
                GeoCoordinate2d coords = new GeoCoordinate2d(
                    new Longitude(18.4239), new Latitude(-33.9253));
                key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    type, coords, depth);
                String keyStr = key.toInternalString();
                Assert.AreEqual("30023103202132011", keyStr);
                GeoCoordinateBoundingBox2d bbox =
                    new GeoCoordinateBoundingBox2d();
                key.getGeoCoordinateBounds2d(bbox);

                // Note that Bing will return a bounding box of all sides
                // inclusive
                QuadKeyVector keys;
                keys = QuadKey.getKeysFromLongitudeLatitudeBoundingBox(
                    type, bbox, depth);
                Assert.AreEqual(4, keys.Count);
                Assert.IsTrue(VectorContains(keys, key));
            }

            { // Quito 0.2500 S, 78.5833 W
                byte depth = 17;
                GeoCoordinate2d coords = new GeoCoordinate2d(
                    new Longitude(-78.5836), new Latitude(-0.25));
                key = QuadKey.getKeyFromLongitudeLatitudeAtDepth(
                    type, coords, depth);
                String keyStr = key.toInternalString();
                Assert.AreEqual("21001000002133122", keyStr);
                GeoCoordinateBoundingBox2d bbox =
                    new GeoCoordinateBoundingBox2d();
                key.getGeoCoordinateBounds2d(bbox);
                // Note that Bing will return a bounding box of all sides
                // inclusive
                QuadKeyVector keys;
                keys = QuadKey.getKeysFromLongitudeLatitudeBoundingBox(
                    type, bbox, depth);
                Assert.AreEqual(4, keys.Count);
                Assert.IsTrue(VectorContains(keys, key));
            }
        }
    }
}

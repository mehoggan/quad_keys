using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using QuadKeys;

namespace QuadKeyTests
{
    [TestClass]
    public class TestQuadKey
    {
        [TestMethod]
        public void TestCtorBing()
        {
            QuadKey key = new QuadKey();
            Assert.IsNotNull(key);
            Assert.AreEqual(0u, key.getRow());
            Assert.AreEqual(0u, key.getCol());
            Assert.AreEqual((byte)0, key.getDepth());
            Assert.AreEqual(QuadKeys.Type.None, key.getType());
            Assert.AreEqual("", key.toInternalString());
        }

        [TestMethod]
        public void TestCtorOnlyType()
        {
             QuadKeys.Type [] types = { QuadKeys.Type.None,
                QuadKeys.Type.Bing, QuadKeys.Type.LatLong,
                QuadKeys.Type.UlpQnr, QuadKeys.Type.MosSli,
                QuadKeys.Type.Nokia, QuadKeys.Type.OsGeo,
                QuadKeys.Type.Morton, QuadKeys.Type.Here};

            foreach (QuadKeys.Type type in types)
            {
                QuadKey key = new QuadKey(type);
                Assert.IsNotNull(key);
                Assert.AreEqual(0u, key.getRow());
                Assert.AreEqual(0u, key.getCol());
                Assert.AreEqual((byte)0, key.getDepth());
                Assert.AreEqual(type, key.getType());
            }
        }

        [TestMethod]
        public void TestCopyCtor()
        {
            QuadKey key = new QuadKey(QuadKeys.Type.OsGeo);
            QuadKey keyCopy = new QuadKey(key);
            Assert.AreNotSame(key, keyCopy);
            Assert.IsNotNull(key);
            Assert.IsTrue(key.EqualTo(keyCopy));
            Assert.AreEqual(0u, keyCopy.getRow());
            Assert.AreEqual(0u, keyCopy.getCol());
            Assert.AreEqual((byte)0, keyCopy.getDepth());
            Assert.AreEqual(QuadKeys.Type.OsGeo, keyCopy.getType());
        }

        [TestMethod]
        public void TestAssignmentOperator()
        {
            byte depth = 1;
            QuadKey key = new QuadKey(QuadKeys.Type.OsGeo);
            QuadKey keyCopy = new QuadKey(QuadKeys.Type.Nokia, 1u, 1u, depth);
            keyCopy.AssignQuadKey(key);
            Assert.AreNotSame(key, keyCopy);
            Assert.IsNotNull(keyCopy);
            Assert.IsTrue(key.EqualTo(keyCopy));
            Assert.AreEqual(0u, keyCopy.getRow());
            Assert.AreEqual(0u, keyCopy.getCol());
            Assert.AreEqual((byte)0, keyCopy.getDepth());
            Assert.AreEqual(QuadKeys.Type.OsGeo, keyCopy.getType());
        }

        [TestMethod]
        public void TestIsRootTest()
        {
            QuadKey key = new QuadKey(QuadKeys.Type.OsGeo);
            Assert.IsTrue(key.isRootKey());
        }

        [TestMethod]
        public void TestSpecificCtorTest()
        {
             QuadKeys.Type [] types = { QuadKeys.Type.None,
                QuadKeys.Type.Bing, QuadKeys.Type.LatLong,
                QuadKeys.Type.UlpQnr, QuadKeys.Type.MosSli,
                QuadKeys.Type.Nokia, QuadKeys.Type.OsGeo,
                QuadKeys.Type.Morton, QuadKeys.Type.Here};

            foreach (QuadKeys.Type type in types)
            {
                for (byte d = 1; d < 10; ++d)
                {
                    uint maxRows = QuadKey.maxRows(type, d);
                    uint maxCols = QuadKey.maxCols(type, d);

                    QuadKey invalid = new QuadKey(type, maxRows, maxCols, d);
                    QuadKey expected = new QuadKey();

                    Assert.IsTrue(expected.EqualTo(invalid));

                    uint validRow = maxRows - 1;
                    uint validCol = maxCols - 1;
                    QuadKey valid = new QuadKey(type, validRow, validCol, d);
                    expected = new QuadKey(type, validRow, validCol, d);
                    Assert.IsTrue(expected.EqualTo(valid));
                }
            }
        }
    }
}

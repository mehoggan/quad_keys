#include <gtest/gtest.h>

#include "QuadKey/GeoCoordinate2d.h"
#include "QuadKey/QuadKey.h"

#include <cmath>

namespace QuadKeys
{
    class BingSystemTest : public ::testing::Test
    {
    protected:
        virtual void SetUp() {}
        virtual void TearDown() {}
    };

    TEST(BINGSYSTEM, IsValid)
    {
    }

    TEST(BINGSYSTEM, IsRootKey)
    {
    }

    TEST(BINGSYSTEM, GetParent)
    {
        {
            QuadKey bingKey0(Type::Bing, 0, 0, 1);
            QuadKey bingKey1(Type::Bing, 1, 0, 1);
            QuadKey bingKey2(Type::Bing, 1, 1, 1);
            QuadKey bingKey3(Type::Bing, 0, 1, 1);

            QuadKey bingKeyP(Type::Bing, 0, 0, 0);

            ASSERT_TRUE(bingKeyP.getType() == Type::Bing);
            ASSERT_TRUE(bingKey0.getType() == Type::Bing);
            ASSERT_TRUE(bingKey1.getType() == Type::Bing);
            ASSERT_TRUE(bingKey2.getType() == Type::Bing);
            ASSERT_TRUE(bingKey3.getType() == Type::Bing);

            EXPECT_EQ(bingKeyP, bingKey0.getParent());
            EXPECT_EQ(bingKeyP, bingKey1.getParent());
            EXPECT_EQ(bingKeyP, bingKey2.getParent());
            EXPECT_EQ(bingKeyP, bingKey3.getParent());
        }

        {
            QuadKey bingKey0(Type::Bing, 5, 6, 3);
            QuadKey bingKey1(Type::Bing, 4, 6, 3);
            QuadKey bingKey2(Type::Bing, 4, 7, 3);
            QuadKey bingKey3(Type::Bing, 5, 7, 3);

            QuadKey bingKeyP(Type::Bing, 2, 3, 2);

            ASSERT_TRUE(bingKeyP.getType() == Type::Bing);
            ASSERT_TRUE(bingKey0.getType() == Type::Bing);
            ASSERT_TRUE(bingKey1.getType() == Type::Bing);
            ASSERT_TRUE(bingKey2.getType() == Type::Bing);
            ASSERT_TRUE(bingKey3.getType() == Type::Bing);

            EXPECT_EQ(bingKeyP, bingKey0.getParent());
            EXPECT_EQ(bingKeyP, bingKey1.getParent());
            EXPECT_EQ(bingKeyP, bingKey2.getParent());
            EXPECT_EQ(bingKeyP, bingKey3.getParent());
        }
    }

    TEST(BINGSYSTEM, IsMyAncestor)
    {
        {
            QuadKey key(Type::Bing, 5, 7, 3);
            EXPECT_FALSE(key.isMyAncestor(QuadKey()));
            EXPECT_FALSE(key.isMyAncestor(QuadKey(Type::OsGeo, 2, 3, 2)));
            EXPECT_FALSE(key.isMyAncestor(QuadKey(Type::OsGeo, 0, 0, 0)));
            EXPECT_TRUE(key.isMyAncestor(QuadKey(Type::Bing, 2, 3, 2)));
            EXPECT_TRUE(key.isMyAncestor(QuadKey(Type::Bing, 0, 0, 0)));
            EXPECT_FALSE(key.isMyAncestor(QuadKey(Type::Bing, 5, 7, 3)));

            QuadKey none;
            EXPECT_FALSE(none.isMyAncestor(QuadKey()));
        }

        {
            QuadKey key(Type::Bing, 5, 7, 3);
            EXPECT_FALSE(key.isMyAncestor(QuadKey()));
            EXPECT_FALSE(key.isMyAncestor(QuadKey(Type::OsGeo, 2, 3, 2)));
            EXPECT_FALSE(key.isMyAncestor(QuadKey(Type::OsGeo, 0, 0, 0)));
            EXPECT_TRUE(key.isMyAncestor(QuadKey(Type::Bing, 2, 3, 2)));
            EXPECT_TRUE(key.isMyAncestor(QuadKey(Type::Bing, 0, 0, 0)));
            EXPECT_FALSE(key.isMyAncestor(QuadKey(Type::Bing, 5, 7, 3)));

            QuadKey none;
            EXPECT_FALSE(none.isMyAncestor(QuadKey()));
        }
    }

    TEST(BINGSYSTEM, GetAncestor)
    {
        {
            QuadKey key(Type::Bing, 0, 7, 3);
            QuadKey ancestor(Type::Bing, 0, 1, 1);
            EXPECT_EQ(ancestor, key.getAncestor(2));
        }

        {
            QuadKey key(Type::Bing, 4, 31, 5);
            QuadKey ancestor(Type::Bing, 0, 1, 1);
            EXPECT_EQ(ancestor, key.getAncestor(4));
        }

        {
            QuadKey key(Type::Bing, 4, 31, 5);
            QuadKey ancestor(Type::Bing, 0, 3, 2);
            EXPECT_EQ(ancestor, key.getAncestor(3));
        }

        {
            QuadKey key(Type::Bing, 4, 31, 5);
            QuadKey ancestor(Type::Bing, 1, 7, 3);
            EXPECT_EQ(ancestor, key.getAncestor(2));
        }
    }

    TEST(BINGSYSTEM, GetChild)
    {
        EXPECT_EQ(QuadKey(),
            QuadKey().getChild(QuadKey::Quadrant::NorthWest));
        uint8_t maxDepthBing = QuadKey::maxDepth(Type::Bing);
        EXPECT_EQ(QuadKey(), QuadKey(Type::Bing, 0, 0, maxDepthBing).getChild(
            QuadKey::Quadrant::NorthEast));


        {
            QuadKey key(Type::Bing, 0, 0, 3);
            EXPECT_EQ(QuadKey(Type::Bing, 1, 0, 4),
                key.getChild(QuadKey::Quadrant::NorthWest));
            EXPECT_EQ(QuadKey(Type::Bing, 1, 1, 4),
                key.getChild(QuadKey::Quadrant::NorthEast));
            EXPECT_EQ(QuadKey(Type::Bing, 0, 1, 4),
                key.getChild(QuadKey::Quadrant::SouthEast));
            EXPECT_EQ(QuadKey(Type::Bing, 0, 0, 4),
                key.getChild(QuadKey::Quadrant::SouthWest));
        }

        {
            QuadKey key(Type::Bing, 2, 3, 3);
            EXPECT_EQ(QuadKey(Type::Bing, 5, 6, 4),
                key.getChild(QuadKey::Quadrant::NorthWest));
            EXPECT_EQ(QuadKey(Type::Bing, 5, 7, 4),
                key.getChild(QuadKey::Quadrant::NorthEast));
            EXPECT_EQ(QuadKey(Type::Bing, 4, 7, 4),
                key.getChild(QuadKey::Quadrant::SouthEast));
            EXPECT_EQ(QuadKey(Type::Bing, 4, 6, 4),
                key.getChild(QuadKey::Quadrant::SouthWest));
        }
    }

    TEST(BINGSYSTEM, GetChildren)
    {
        std::vector<QuadKey> testKeys;
        uint8_t maxDepthBing = QuadKey::maxDepth(Type::Bing);
        testKeys = QuadKey(Type::Bing, 0, 0, maxDepthBing).getChildren();
        EXPECT_TRUE(testKeys.empty());

        testKeys.clear();

        testKeys = QuadKey(Type::Bing, 0, 0, 1).getChildren();
        EXPECT_EQ(4u, testKeys.size());
        EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
            QuadKey(Type::Bing, 0, 0, 2)), testKeys.end());
        EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
            QuadKey(Type::Bing, 0, 1, 2)), testKeys.end());
        EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
            QuadKey(Type::Bing, 1, 0, 2)), testKeys.end());
        EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
            QuadKey(Type::Bing, 1, 1, 2)), testKeys.end());

        testKeys = QuadKey(Type::Bing, 0, 1, 1).getChildren();
        EXPECT_EQ(4u, testKeys.size());
        EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
            QuadKey(Type::Bing, 0, 2, 2)), testKeys.end());
        EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
            QuadKey(Type::Bing, 0, 3, 2)), testKeys.end());
        EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
            QuadKey(Type::Bing, 1, 2, 2)), testKeys.end());
        EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
            QuadKey(Type::Bing, 1, 3, 2)), testKeys.end());

        testKeys = QuadKey(Type::Bing, 1, 0, 1).getChildren();
        EXPECT_EQ(4u, testKeys.size());
        EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
            QuadKey(Type::Bing, 2, 0, 2)), testKeys.end());
        EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
            QuadKey(Type::Bing, 2, 1, 2)), testKeys.end());
        EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
            QuadKey(Type::Bing, 3, 0, 2)), testKeys.end());
        EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
            QuadKey(Type::Bing, 3, 1, 2)), testKeys.end());

        testKeys = QuadKey(Type::Bing, 1, 1, 1).getChildren();
        EXPECT_EQ(4u, testKeys.size());
        EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
            QuadKey(Type::Bing, 2, 2, 2)), testKeys.end());
        EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
            QuadKey(Type::Bing, 2, 3, 2)), testKeys.end());
        EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
            QuadKey(Type::Bing, 3, 2, 2)), testKeys.end());
        EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
            QuadKey(Type::Bing, 3, 3, 2)), testKeys.end());

        testKeys.clear();
    }

    TEST(BINGSYSTEM, GetDescendants)
    {
        uint8_t bingMaxDepth = QuadKey::maxDepth(Type::Bing);
        QuadKey testKey(Type::Bing, 0, 0, bingMaxDepth - 3);
        std::vector<QuadKey> testKeys;
        testKeys = testKey.getDescendants(4);
        EXPECT_EQ(0u, testKeys.size());

        QuadKey none;
        testKeys = none.getDescendants(1);
        EXPECT_EQ(0u, testKeys.size());

        {
            QuadKey key(Type::Bing, 0, 0, 0);
            testKeys = key.getDescendants(0);
            EXPECT_EQ(0u, testKeys.size());
        }

        {
            QuadKey key(Type::Bing, 0, 0, 0);

            testKeys = key.getDescendants(1);
            EXPECT_EQ(4u, testKeys.size());
            EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
                QuadKey(Type::Bing, 0, 0, 1)), testKeys.end());
            EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
                QuadKey(Type::Bing, 0, 1, 1)), testKeys.end());
            EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
                QuadKey(Type::Bing, 1, 0, 1)), testKeys.end());
            EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
                QuadKey(Type::Bing, 1, 1, 1)), testKeys.end());

            testKeys = key.getDescendants(2);
            EXPECT_EQ(16u, testKeys.size());
            EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
                QuadKey(Type::Bing, 0, 0, 2)), testKeys.end());
            EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
                QuadKey(Type::Bing, 0, 1, 2)), testKeys.end());
            EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
                QuadKey(Type::Bing, 0, 2, 2)), testKeys.end());
            EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
                QuadKey(Type::Bing, 0, 3, 2)), testKeys.end());
            EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
                QuadKey(Type::Bing, 1, 0, 2)), testKeys.end());
            EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
                QuadKey(Type::Bing, 1, 1, 2)), testKeys.end());
            EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
                QuadKey(Type::Bing, 1, 2, 2)), testKeys.end());
            EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
                QuadKey(Type::Bing, 1, 3, 2)), testKeys.end());
            EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
                QuadKey(Type::Bing, 2, 0, 2)), testKeys.end());
            EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
                QuadKey(Type::Bing, 2, 1, 2)), testKeys.end());
            EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
                QuadKey(Type::Bing, 2, 2, 2)), testKeys.end());
            EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
                QuadKey(Type::Bing, 2, 3, 2)), testKeys.end());
            EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
                QuadKey(Type::Bing, 3, 0, 2)), testKeys.end());
            EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
                QuadKey(Type::Bing, 3, 1, 2)), testKeys.end());
            EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
                QuadKey(Type::Bing, 3, 2, 2)), testKeys.end());
            EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
                QuadKey(Type::Bing, 3, 3, 2)), testKeys.end());

            testKeys = key.getDescendants(3);
            EXPECT_EQ(64u, testKeys.size());
            EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
                QuadKey(Type::Bing, 0, 0, 3)), testKeys.end());
            EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
                QuadKey(Type::Bing, 0, 1, 3)), testKeys.end());
            EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
                QuadKey(Type::Bing, 0, 2, 3)), testKeys.end());
            EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
                QuadKey(Type::Bing, 0, 3, 3)), testKeys.end());
            EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
                QuadKey(Type::Bing, 0, 4, 3)), testKeys.end());
            EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
                QuadKey(Type::Bing, 0, 5, 3)), testKeys.end());
            EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
                QuadKey(Type::Bing, 0, 6, 3)), testKeys.end());
            EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
                QuadKey(Type::Bing, 0, 7, 3)), testKeys.end());
            EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
                QuadKey(Type::Bing, 1, 0, 3)), testKeys.end());
            EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
                QuadKey(Type::Bing, 1, 1, 3)), testKeys.end());
            EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
                QuadKey(Type::Bing, 1, 2, 3)), testKeys.end());
            EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
                QuadKey(Type::Bing, 1, 3, 3)), testKeys.end());
            EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
                QuadKey(Type::Bing, 1, 4, 3)), testKeys.end());
            EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
                QuadKey(Type::Bing, 1, 5, 3)), testKeys.end());
            EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
                QuadKey(Type::Bing, 1, 6, 3)), testKeys.end());
            EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
                QuadKey(Type::Bing, 1, 7, 3)), testKeys.end());
            EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
                QuadKey(Type::Bing, 2, 0, 3)), testKeys.end());
            EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
                QuadKey(Type::Bing, 2, 1, 3)), testKeys.end());
            EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
                QuadKey(Type::Bing, 2, 2, 3)), testKeys.end());
            EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
                QuadKey(Type::Bing, 2, 3, 3)), testKeys.end());
            EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
                QuadKey(Type::Bing, 2, 4, 3)), testKeys.end());
            EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
                QuadKey(Type::Bing, 2, 5, 3)), testKeys.end());
            EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
                QuadKey(Type::Bing, 2, 6, 3)), testKeys.end());
            EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
                QuadKey(Type::Bing, 2, 7, 3)), testKeys.end());
            EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
                QuadKey(Type::Bing, 3, 0, 3)), testKeys.end());
            EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
                QuadKey(Type::Bing, 3, 1, 3)), testKeys.end());
            EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
                QuadKey(Type::Bing, 3, 2, 3)), testKeys.end());
            EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
                QuadKey(Type::Bing, 3, 3, 3)), testKeys.end());
            EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
                QuadKey(Type::Bing, 3, 4, 3)), testKeys.end());
            EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
                QuadKey(Type::Bing, 3, 5, 3)), testKeys.end());
            EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
                QuadKey(Type::Bing, 3, 6, 3)), testKeys.end());
            EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
                QuadKey(Type::Bing, 3, 7, 3)), testKeys.end());
            EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
                QuadKey(Type::Bing, 4, 0, 3)), testKeys.end());
            EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
                QuadKey(Type::Bing, 4, 1, 3)), testKeys.end());
            EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
                QuadKey(Type::Bing, 4, 2, 3)), testKeys.end());
            EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
                QuadKey(Type::Bing, 4, 3, 3)), testKeys.end());
            EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
                QuadKey(Type::Bing, 4, 4, 3)), testKeys.end());
            EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
                QuadKey(Type::Bing, 4, 5, 3)), testKeys.end());
            EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
                QuadKey(Type::Bing, 4, 6, 3)), testKeys.end());
            EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
                QuadKey(Type::Bing, 4, 7, 3)), testKeys.end());
            EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
                QuadKey(Type::Bing, 5, 0, 3)), testKeys.end());
            EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
                QuadKey(Type::Bing, 5, 1, 3)), testKeys.end());
            EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
                QuadKey(Type::Bing, 5, 2, 3)), testKeys.end());
            EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
                QuadKey(Type::Bing, 5, 3, 3)), testKeys.end());
            EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
                QuadKey(Type::Bing, 5, 4, 3)), testKeys.end());
            EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
                QuadKey(Type::Bing, 5, 5, 3)), testKeys.end());
            EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
                QuadKey(Type::Bing, 5, 6, 3)), testKeys.end());
            EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
                QuadKey(Type::Bing, 5, 7, 3)), testKeys.end());
            EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
                QuadKey(Type::Bing, 6, 0, 3)), testKeys.end());
            EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
                QuadKey(Type::Bing, 6, 1, 3)), testKeys.end());
            EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
                QuadKey(Type::Bing, 6, 2, 3)), testKeys.end());
            EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
                QuadKey(Type::Bing, 6, 3, 3)), testKeys.end());
            EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
                QuadKey(Type::Bing, 6, 4, 3)), testKeys.end());
            EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
                QuadKey(Type::Bing, 6, 5, 3)), testKeys.end());
            EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
                QuadKey(Type::Bing, 6, 6, 3)), testKeys.end());
            EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
                QuadKey(Type::Bing, 6, 7, 3)), testKeys.end());
            EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
                QuadKey(Type::Bing, 7, 0, 3)), testKeys.end());
            EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
                QuadKey(Type::Bing, 7, 1, 3)), testKeys.end());
            EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
                QuadKey(Type::Bing, 7, 2, 3)), testKeys.end());
            EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
                QuadKey(Type::Bing, 7, 3, 3)), testKeys.end());
            EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
                QuadKey(Type::Bing, 7, 4, 3)), testKeys.end());
            EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
                QuadKey(Type::Bing, 7, 5, 3)), testKeys.end());
            EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
                QuadKey(Type::Bing, 7, 6, 3)), testKeys.end());
            EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
                QuadKey(Type::Bing, 7, 7, 3)), testKeys.end());
        }
    }

    TEST(BINGSYSTEM, GetSiblings)
    {
        std::vector<QuadKey> testKeys;

        testKeys = QuadKey().getSiblings();
        EXPECT_TRUE(testKeys.empty());

        testKeys = QuadKey(Type::Bing, 0, 0, 0).getSiblings();
        EXPECT_TRUE(testKeys.empty());

        testKeys = QuadKey(Type::Bing, 0, 0, 1).getSiblings();
        EXPECT_EQ(3u, testKeys.size());
        EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
            QuadKey(Type::Bing, 0, 1, 1)), testKeys.end());
        EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
            QuadKey(Type::Bing, 1, 1, 1)), testKeys.end());
        EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
            QuadKey(Type::Bing, 1, 0, 1)), testKeys.end());
    }

    TEST(BINGSYSTEM, GetNeighbors)
    {
        std::vector<QuadKey> testKeys;

        testKeys = QuadKey().getNeighbors();
        EXPECT_TRUE(testKeys.empty());

        testKeys = QuadKey(Type::Bing, 0, 0, 0).getNeighbors();
        EXPECT_TRUE(testKeys.empty());

        testKeys.clear();

        testKeys = QuadKey(Type::Bing, 0, 0, 2).getNeighbors();
        EXPECT_EQ(5u, testKeys.size());
        EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
            QuadKey(Type::Bing, 0, 1, 2)), testKeys.end());
        EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
            QuadKey(Type::Bing, 1, 1, 2)), testKeys.end());
        EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
            QuadKey(Type::Bing, 1, 0, 2)), testKeys.end());
        EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
            QuadKey(Type::Bing, 0, 3, 2)), testKeys.end());
        EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
            QuadKey(Type::Bing, 1, 3, 2)), testKeys.end());

        testKeys.clear();

        testKeys = QuadKey(Type::Bing, 0, 1, 2).getNeighbors();
        EXPECT_EQ(5u, testKeys.size());
        EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
            QuadKey(Type::Bing, 0, 0, 2)), testKeys.end());
        EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
            QuadKey(Type::Bing, 1, 0, 2)), testKeys.end());
        EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
            QuadKey(Type::Bing, 1, 1, 2)), testKeys.end());
        EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
            QuadKey(Type::Bing, 1, 2, 2)), testKeys.end());
        EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
            QuadKey(Type::Bing, 0, 2, 2)), testKeys.end());

        testKeys.clear();

        testKeys = QuadKey(Type::Bing, 0, 2, 2).getNeighbors();
        EXPECT_EQ(5u, testKeys.size());
        EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
            QuadKey(Type::Bing, 0, 1, 2)), testKeys.end());
        EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
            QuadKey(Type::Bing, 1, 1, 2)), testKeys.end());
        EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
            QuadKey(Type::Bing, 1, 2, 2)), testKeys.end());
        EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
            QuadKey(Type::Bing, 1, 3, 2)), testKeys.end());
        EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
            QuadKey(Type::Bing, 0, 3, 2)), testKeys.end());

        testKeys.clear();

        testKeys = QuadKey(Type::Bing, 0, 3, 2).getNeighbors();
        EXPECT_EQ(5u, testKeys.size());
        EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
            QuadKey(Type::Bing, 0, 2, 2)), testKeys.end());
        EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
            QuadKey(Type::Bing, 1, 2, 2)), testKeys.end());
        EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
            QuadKey(Type::Bing, 1, 3, 2)), testKeys.end());
        EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
            QuadKey(Type::Bing, 1, 0, 2)), testKeys.end());
        EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
            QuadKey(Type::Bing, 0, 0, 2)), testKeys.end());

        testKeys.clear();

        testKeys = QuadKey(Type::Bing, 1, 0, 2).getNeighbors();
        EXPECT_EQ(8u, testKeys.size());
        EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
            QuadKey(Type::Bing, 0, 0, 2)), testKeys.end());
        EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
            QuadKey(Type::Bing, 0, 1, 2)), testKeys.end());
        EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
            QuadKey(Type::Bing, 1, 1, 2)), testKeys.end());
        EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
            QuadKey(Type::Bing, 2, 1, 2)), testKeys.end());
        EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
            QuadKey(Type::Bing, 2, 0, 2)), testKeys.end());
        EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
            QuadKey(Type::Bing, 2, 3, 2)), testKeys.end());
        EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
            QuadKey(Type::Bing, 1, 3, 2)), testKeys.end());
        EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
            QuadKey(Type::Bing, 0, 3, 2)), testKeys.end());

        testKeys.clear();

        testKeys = QuadKey(Type::Bing, 1, 1, 2).getNeighbors();
        EXPECT_EQ(8u, testKeys.size());
        EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
            QuadKey(Type::Bing, 1, 0, 2)), testKeys.end());
        EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
            QuadKey(Type::Bing, 0, 0, 2)), testKeys.end());
        EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
            QuadKey(Type::Bing, 0, 1, 2)), testKeys.end());
        EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
            QuadKey(Type::Bing, 2, 2, 2)), testKeys.end());
        EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
            QuadKey(Type::Bing, 2, 1, 2)), testKeys.end());
        EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
            QuadKey(Type::Bing, 2, 0, 2)), testKeys.end());
        EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
            QuadKey(Type::Bing, 0, 2, 2)), testKeys.end());
        EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
            QuadKey(Type::Bing, 1, 2, 2)), testKeys.end());

        testKeys.clear();

        testKeys = QuadKey(Type::Bing, 1, 2, 2).getNeighbors();
        EXPECT_EQ(8u, testKeys.size());
        EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
            QuadKey(Type::Bing, 1, 1, 2)), testKeys.end());
        EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
            QuadKey(Type::Bing, 0, 1, 2)), testKeys.end());
        EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
            QuadKey(Type::Bing, 0, 2, 2)), testKeys.end());
        EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
            QuadKey(Type::Bing, 2, 3, 2)), testKeys.end());
        EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
            QuadKey(Type::Bing, 2, 2, 2)), testKeys.end());
        EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
            QuadKey(Type::Bing, 2, 1, 2)), testKeys.end());
        EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
            QuadKey(Type::Bing, 0, 3, 2)), testKeys.end());
        EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
            QuadKey(Type::Bing, 1, 3, 2)), testKeys.end());

        testKeys.clear();

        testKeys = QuadKey(Type::Bing, 1, 3, 2).getNeighbors();
        EXPECT_EQ(8u, testKeys.size());
        EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
            QuadKey(Type::Bing, 1, 2, 2)), testKeys.end());
        EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
            QuadKey(Type::Bing, 0, 2, 2)), testKeys.end());
        EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
            QuadKey(Type::Bing, 0, 3, 2)), testKeys.end());
        EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
            QuadKey(Type::Bing, 2, 0, 2)), testKeys.end());
        EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
            QuadKey(Type::Bing, 2, 3, 2)), testKeys.end());
        EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
            QuadKey(Type::Bing, 2, 2, 2)), testKeys.end());
        EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
            QuadKey(Type::Bing, 0, 0, 2)), testKeys.end());
        EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
            QuadKey(Type::Bing, 1, 0, 2)), testKeys.end());

        testKeys.clear();

        testKeys = QuadKey(Type::Bing, 4, 7, 3).getNeighbors();
        EXPECT_EQ(8u, testKeys.size());
        EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
            QuadKey(Type::Bing, 3, 7, 3)), testKeys.end());
        EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
            QuadKey(Type::Bing, 3, 6, 3)), testKeys.end());
        EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
            QuadKey(Type::Bing, 4, 6, 3)), testKeys.end());
        EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
            QuadKey(Type::Bing, 5, 6, 3)), testKeys.end());
        EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
            QuadKey(Type::Bing, 5, 7, 3)), testKeys.end());
        EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
            QuadKey(Type::Bing, 5, 0, 3)), testKeys.end());
        EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
            QuadKey(Type::Bing, 4, 0, 3)), testKeys.end());
        EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
            QuadKey(Type::Bing, 3, 0, 3)), testKeys.end());

        testKeys.clear();

        testKeys = QuadKey(Type::Bing, 4, 0, 3).getNeighbors();
        EXPECT_EQ(8u, testKeys.size());
        EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
            QuadKey(Type::Bing, 3, 0, 3)), testKeys.end());
        EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
            QuadKey(Type::Bing, 3, 1, 3)), testKeys.end());
        EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
            QuadKey(Type::Bing, 4, 1, 3)), testKeys.end());
        EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
            QuadKey(Type::Bing, 5, 1, 3)), testKeys.end());
        EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
            QuadKey(Type::Bing, 5, 0, 3)), testKeys.end());
        EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
            QuadKey(Type::Bing, 5, 7, 3)), testKeys.end());
        EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
            QuadKey(Type::Bing, 4, 7, 3)), testKeys.end());
        EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
            QuadKey(Type::Bing, 3, 7, 3)), testKeys.end());

        testKeys.clear();
    }

    TEST(BINGSYSTEM, FromStringToString)
    {
        {
            QuadKey root = QuadKey::fromInternalString(Type::Bing, "");
            EXPECT_EQ(0u, root.getRow());
            EXPECT_EQ(0u, root.getCol());
            EXPECT_EQ(0u, root.getDepth());
        }

        {
            QuadKey key;
            key = QuadKey::fromInternalString(Type::Bing, "0");
            EXPECT_EQ(1u, key.getRow());
            EXPECT_EQ(0u, key.getCol());
            EXPECT_EQ(1u, key.getDepth());
            EXPECT_EQ("0", key.toInternalString());
            key = QuadKey::fromInternalString(Type::Bing, "1");
            EXPECT_EQ(1u, key.getRow());
            EXPECT_EQ(1u, key.getCol());
            EXPECT_EQ(1u, key.getDepth());
            EXPECT_EQ("1", key.toInternalString());
            key = QuadKey::fromInternalString(Type::Bing, "2");
            EXPECT_EQ(0u, key.getRow());
            EXPECT_EQ(0u, key.getCol());
            EXPECT_EQ(1u, key.getDepth());
            EXPECT_EQ("2", key.toInternalString());
            key = QuadKey::fromInternalString(Type::Bing, "3");
            EXPECT_EQ(0u, key.getRow());
            EXPECT_EQ(1u, key.getCol());
            EXPECT_EQ(1u, key.getDepth());
            EXPECT_EQ("3", key.toInternalString());
        }

        {
            QuadKey key;
            key = QuadKey::fromInternalString(Type::Bing, "00");
            EXPECT_EQ(3u, key.getRow());
            EXPECT_EQ(0u, key.getCol());
            EXPECT_EQ(2u, key.getDepth());
            EXPECT_EQ("00", key.toInternalString());
            key = QuadKey::fromInternalString(Type::Bing, "01");
            EXPECT_EQ(3u, key.getRow());
            EXPECT_EQ(1u, key.getCol());
            EXPECT_EQ(2u, key.getDepth());
            EXPECT_EQ("01", key.toInternalString());
            key = QuadKey::fromInternalString(Type::Bing, "02");
            EXPECT_EQ(2u, key.getRow());
            EXPECT_EQ(0u, key.getCol());
            EXPECT_EQ(2u, key.getDepth());
            EXPECT_EQ("02", key.toInternalString());
            key = QuadKey::fromInternalString(Type::Bing, "03");
            EXPECT_EQ(2u, key.getRow());
            EXPECT_EQ(1u, key.getCol());
            EXPECT_EQ(2u, key.getDepth());
            EXPECT_EQ("03", key.toInternalString());
            key = QuadKey::fromInternalString(Type::Bing, "10");
            EXPECT_EQ(3u, key.getRow());
            EXPECT_EQ(2u, key.getCol());
            EXPECT_EQ(2u, key.getDepth());
            EXPECT_EQ("10", key.toInternalString());
            key = QuadKey::fromInternalString(Type::Bing, "11");
            EXPECT_EQ(3u, key.getRow());
            EXPECT_EQ(3u, key.getCol());
            EXPECT_EQ(2u, key.getDepth());
            EXPECT_EQ("11", key.toInternalString());
            key = QuadKey::fromInternalString(Type::Bing, "12");
            EXPECT_EQ(2u, key.getRow());
            EXPECT_EQ(2u, key.getCol());
            EXPECT_EQ(2u, key.getDepth());
            EXPECT_EQ("12", key.toInternalString());
            key = QuadKey::fromInternalString(Type::Bing, "13");
            EXPECT_EQ(2u, key.getRow());
            EXPECT_EQ(3u, key.getCol());
            EXPECT_EQ(2u, key.getDepth());
            EXPECT_EQ("13", key.toInternalString());
            key = QuadKey::fromInternalString(Type::Bing, "20");
            EXPECT_EQ(1u, key.getRow());
            EXPECT_EQ(0u, key.getCol());
            EXPECT_EQ(2u, key.getDepth());
            EXPECT_EQ("20", key.toInternalString());
            key = QuadKey::fromInternalString(Type::Bing, "21");
            EXPECT_EQ(1u, key.getRow());
            EXPECT_EQ(1u, key.getCol());
            EXPECT_EQ(2u, key.getDepth());
            EXPECT_EQ("21", key.toInternalString());
            key = QuadKey::fromInternalString(Type::Bing, "22");
            EXPECT_EQ(0u, key.getRow());
            EXPECT_EQ(0u, key.getCol());
            EXPECT_EQ(2u, key.getDepth());
            EXPECT_EQ("22", key.toInternalString());
            key = QuadKey::fromInternalString(Type::Bing, "23");
            EXPECT_EQ(0u, key.getRow());
            EXPECT_EQ(1u, key.getCol());
            EXPECT_EQ(2u, key.getDepth());
            EXPECT_EQ("23", key.toInternalString());
            key = QuadKey::fromInternalString(Type::Bing, "30");
            EXPECT_EQ(1u, key.getRow());
            EXPECT_EQ(2u, key.getCol());
            EXPECT_EQ(2u, key.getDepth());
            EXPECT_EQ("30", key.toInternalString());
            key = QuadKey::fromInternalString(Type::Bing, "31");
            EXPECT_EQ(1u, key.getRow());
            EXPECT_EQ(3u, key.getCol());
            EXPECT_EQ(2u, key.getDepth());
            EXPECT_EQ("31", key.toInternalString());
            key = QuadKey::fromInternalString(Type::Bing, "32");
            EXPECT_EQ(0u, key.getRow());
            EXPECT_EQ(2u, key.getCol());
            EXPECT_EQ(2u, key.getDepth());
            EXPECT_EQ("32", key.toInternalString());
            key = QuadKey::fromInternalString(Type::Bing, "33");
            EXPECT_EQ(0u, key.getRow());
            EXPECT_EQ(3u, key.getCol());
            EXPECT_EQ(2u, key.getDepth());
            EXPECT_EQ("33", key.toInternalString());
        }
    }

    TEST(BINGSYSTEM, GetGeoCoordinateBounds2d)
    {
        QuadKey key;
        GeoCoordinateBoundingBox2d bbox;

        { // Depth 0
            key = QuadKey::fromInternalString(Type::Bing, "");
            key.getGeoCoordinateBounds2d(bbox);
            EXPECT_FLOAT_EQ(-180.0f,
                static_cast<float>(bbox.lowerLeft().longitude().val()));
            EXPECT_FLOAT_EQ(-84.928322f,
                static_cast<float>(bbox.lowerLeft().latitude().val()));
            EXPECT_FLOAT_EQ(178.593750f,
                static_cast<float>(bbox.upperRight().longitude().val()));
            EXPECT_FLOAT_EQ(85.051132f,
                static_cast<float>(bbox.upperRight().latitude().val()));
        }
    }

    TEST(BINGSYSTEM, GetKeyFromLongitudeLatitudeAtDepthToBounds)
    {
        QuadKey key;
        GeoCoordinateBoundingBox2d bbox;
        double diff = 0.0;

        { // Depth 0
            key = QuadKey::getKeyFromLongitudeLatitudeAtDepth(
                Type::Bing, GeoCoordinate2d(Longitude(-180.0),
                Latitude(-84.0)), 0u);
            EXPECT_EQ(QuadKey(Type::Bing, 0, 0, 0), key);
            key.getGeoCoordinateBounds2d(bbox);
            diff = std::fabs(bbox.lowerLeft().longitude() - Longitude(-180.0));
            EXPECT_GT(2.0, diff);
            diff = std::fabs(bbox.lowerLeft().latitude() - Latitude(-85.0));
            EXPECT_GT(2.0, diff);
            diff = std::fabs(bbox.upperRight().longitude() - Longitude(+180.0));
            EXPECT_GT(2.0, diff);
            diff = std::fabs(bbox.upperRight().latitude() - Latitude(+85.0));
            EXPECT_GT(2.0, diff);
        }

        // Inclusion here consists of upper left
        // ul X------X------X
        //    |      |      |
        //    |      |      |
        //    X------X------X
        //    |      |      |
        //    |      |      |
        //    X------X------X
        Longitude left(-180.0);
        Longitude midLeft(-0.36); // This is related to math used by Bing
        Longitude midRight(0.0);
        Longitude right(+180.0);
        Latitude bottom(-90.0); // Outside of Mercator space. Puts them in.
        Latitude midBottom(0.0);
        Latitude midTop(0.36); // This is related to math used by Bing
        Latitude top(+90.0); // Outside of Mercator space. Puts them in.

        { // Depth 1
            key = QuadKey::getKeyFromLongitudeLatitudeAtDepth( // Q0 ul
                Type::Bing, GeoCoordinate2d(left, top), 1u);
            EXPECT_EQ(QuadKey(Type::Bing, 1, 0, 1), key);
            key = QuadKey::getKeyFromLongitudeLatitudeAtDepth( // Q0 ll
                Type::Bing, GeoCoordinate2d(left, midTop), 1u);
            EXPECT_EQ(QuadKey(Type::Bing, 1, 0, 1), key);
            key = QuadKey::getKeyFromLongitudeLatitudeAtDepth( // Q0 lr
                Type::Bing, GeoCoordinate2d(midLeft, midTop), 1u);
            EXPECT_EQ(QuadKey(Type::Bing, 1, 0, 1), key);
            key = QuadKey::getKeyFromLongitudeLatitudeAtDepth( // Q0 ur
                Type::Bing, GeoCoordinate2d(midLeft, top), 1u);
            EXPECT_EQ(QuadKey(Type::Bing, 1, 0, 1), key);
            key.getGeoCoordinateBounds2d(bbox);
            diff = std::fabs(bbox.lowerLeft().longitude() - left);
            EXPECT_GT(2.0, diff);
            diff = std::fabs(bbox.lowerLeft().latitude() - midTop);
            EXPECT_GT(2.0, diff);
            diff = std::fabs(bbox.upperRight().longitude() - midLeft);
            EXPECT_GT(2.0, diff);
            diff = std::fabs(bbox.upperRight().latitude() - Latitude(+85.0));
            EXPECT_GT(2.0, diff);

            key = QuadKey::getKeyFromLongitudeLatitudeAtDepth( // Q1 ul
                Type::Bing, GeoCoordinate2d(midRight, top), 1u);
            EXPECT_EQ(QuadKey(Type::Bing, 1, 1, 1), key);
            key = QuadKey::getKeyFromLongitudeLatitudeAtDepth( // Q1 ll
                Type::Bing, GeoCoordinate2d(midRight, midTop), 1u);
            EXPECT_EQ(QuadKey(Type::Bing, 1, 1, 1), key);
            key = QuadKey::getKeyFromLongitudeLatitudeAtDepth( // Q1 lr
                Type::Bing, GeoCoordinate2d(right, midTop), 1u);
            EXPECT_EQ(QuadKey(Type::Bing, 1, 1, 1), key);
            key = QuadKey::getKeyFromLongitudeLatitudeAtDepth( // Q1 ur
                Type::Bing, GeoCoordinate2d(right, top), 1u);
            EXPECT_EQ(QuadKey(Type::Bing, 1, 1, 1), key);
            key.getGeoCoordinateBounds2d(bbox);
            diff = std::fabs(bbox.lowerLeft().longitude() - midRight);
            EXPECT_GT(2.0, diff);
            diff = std::fabs(bbox.lowerLeft().latitude() - midTop);
            EXPECT_GT(2.0, diff);
            diff = std::fabs(bbox.upperRight().longitude() - right);
            EXPECT_GT(2.0, diff);
            diff = std::fabs(bbox.upperRight().latitude() - Latitude(+85.0));
            EXPECT_GT(2.0, diff);

            key = QuadKey::getKeyFromLongitudeLatitudeAtDepth( // Q2 ul
                Type::Bing, GeoCoordinate2d(left, midBottom), 1u);
            EXPECT_EQ(QuadKey(Type::Bing, 0, 0, 1), key);
            key = QuadKey::getKeyFromLongitudeLatitudeAtDepth( // Q2 ll
                Type::Bing, GeoCoordinate2d(left, bottom), 1u);
            EXPECT_EQ(QuadKey(Type::Bing, 0, 0, 1), key);
            key = QuadKey::getKeyFromLongitudeLatitudeAtDepth( // Q2 lr
                Type::Bing, GeoCoordinate2d(midLeft, bottom), 1u);
            EXPECT_EQ(QuadKey(Type::Bing, 0, 0, 1), key);
            key = QuadKey::getKeyFromLongitudeLatitudeAtDepth( // Q2 ur
                Type::Bing, GeoCoordinate2d(midLeft, midBottom), 1u);
            EXPECT_EQ(QuadKey(Type::Bing, 0, 0, 1), key);
            key.getGeoCoordinateBounds2d(bbox);
            diff = std::fabs(bbox.lowerLeft().longitude() - left);
            EXPECT_GT(2.0, diff);
            diff = std::fabs(bbox.lowerLeft().latitude() - Latitude(-85.0));
            EXPECT_GT(2.0, diff);
            diff = std::fabs(bbox.upperRight().longitude() - midLeft);
            EXPECT_GT(2.0, diff);
            diff = std::fabs(bbox.upperRight().latitude() - midBottom);
            EXPECT_GT(2.0, diff);

            key = QuadKey::getKeyFromLongitudeLatitudeAtDepth( // Q3 ul
                Type::Bing, GeoCoordinate2d(midRight, midBottom), 1u);
            EXPECT_EQ(QuadKey(Type::Bing, 0, 1, 1), key);
            key = QuadKey::getKeyFromLongitudeLatitudeAtDepth( // Q3 ll
                Type::Bing, GeoCoordinate2d(midRight, bottom), 1u);
            EXPECT_EQ(QuadKey(Type::Bing, 0, 1, 1), key);
            key = QuadKey::getKeyFromLongitudeLatitudeAtDepth( // Q3 lr
                Type::Bing, GeoCoordinate2d(right, bottom), 1u);
            EXPECT_EQ(QuadKey(Type::Bing, 0, 1, 1), key);
            key = QuadKey::getKeyFromLongitudeLatitudeAtDepth( // Q3 ur
                Type::Bing, GeoCoordinate2d(right, midBottom), 1u);
            EXPECT_EQ(QuadKey(Type::Bing, 0, 1, 1), key);
            key.getGeoCoordinateBounds2d(bbox);
            diff = std::fabs(bbox.lowerLeft().longitude() - midRight);
            EXPECT_GT(2.0, diff);
            diff = std::fabs(bbox.lowerLeft().latitude() - Latitude(-85.0));
            EXPECT_GT(2.0, diff);
            diff = std::fabs(bbox.upperRight().longitude() - right);
            EXPECT_GT(2.0, diff);
            diff = std::fabs(bbox.upperRight().latitude() - midBottom);
            EXPECT_GT(2.0, diff);
        }
    }

    TEST(BINGSYSTEM, GetKeysFromLongitudeLatitudeBoundingBox)
    {
        {
            std::vector<QuadKey> outKeys;
            outKeys = QuadKey::getKeysFromLongitudeLatitudeBoundingBox(
                Type::Bing,
                GeoCoordinateBoundingBox2d(
                GeoCoordinate2d(Longitude(-180.0), Latitude(+90.0)),
                GeoCoordinate2d(Longitude(+180.0), Latitude(-90.0))), 0);
            EXPECT_EQ(1u, outKeys.size());
            EXPECT_NE(outKeys.end(), std::find(outKeys.begin(), outKeys.end(),
                QuadKey(Type::Bing, 0, 0, 0)));
        }

        {
            std::vector<QuadKey> outKeys;
            outKeys = QuadKey::getKeysFromLongitudeLatitudeBoundingBox(
                Type::Bing,
                GeoCoordinateBoundingBox2d(
                GeoCoordinate2d(Longitude(-180.0), Latitude(+90.0)),
                GeoCoordinate2d(Longitude(+180.0), Latitude(-90.0))), 1);
            EXPECT_EQ(4u, outKeys.size());
            EXPECT_NE(outKeys.end(), std::find(outKeys.begin(), outKeys.end(),
                QuadKey(Type::Bing, 0, 0, 1)));
            EXPECT_NE(outKeys.end(), std::find(outKeys.begin(), outKeys.end(),
                QuadKey(Type::Bing, 0, 1, 1)));
            EXPECT_NE(outKeys.end(), std::find(outKeys.begin(), outKeys.end(),
                QuadKey(Type::Bing, 1, 0, 1)));
            EXPECT_NE(outKeys.end(), std::find(outKeys.begin(), outKeys.end(),
                QuadKey(Type::Bing, 1, 1, 1)));
        }

        {
            std::vector<QuadKey> outKeys;
            outKeys = QuadKey::getKeysFromLongitudeLatitudeBoundingBox(
                Type::Bing,
                GeoCoordinateBoundingBox2d(
                GeoCoordinate2d(Longitude(-180.0), Latitude(+0.35)),
                GeoCoordinate2d(Longitude(-0.36), Latitude(+90.0))), 1);
            EXPECT_EQ(2u, outKeys.size());
            EXPECT_NE(outKeys.end(), std::find(outKeys.begin(), outKeys.end(),
                QuadKey(Type::Bing, 0, 0, 1)));
            EXPECT_NE(outKeys.end(), std::find(outKeys.begin(), outKeys.end(),
                QuadKey(Type::Bing, 1, 0, 1)));
        }

        {
            std::vector<QuadKey> outKeys;
            outKeys = QuadKey::getKeysFromLongitudeLatitudeBoundingBox(
                Type::Bing,
                GeoCoordinateBoundingBox2d(
                    GeoCoordinate2d(Longitude(-0.36), Latitude(+0.36)),
                    GeoCoordinate2d(Longitude(+0.36), Latitude(+90.0))), 1);
            EXPECT_EQ(2u, outKeys.size());
            EXPECT_NE(outKeys.end(), std::find(outKeys.begin(), outKeys.end(),
                QuadKey(Type::Bing, 1, 0, 1)));
            EXPECT_NE(outKeys.end(), std::find(outKeys.begin(), outKeys.end(),
                QuadKey(Type::Bing, 1, 1, 1)));
        }

        {
            std::vector<QuadKey> outKeys;
            outKeys = QuadKey::getKeysFromLongitudeLatitudeBoundingBox(
                Type::Bing,
                GeoCoordinateBoundingBox2d(
                    GeoCoordinate2d(Longitude(-0.36), Latitude(+0.35)),
                    GeoCoordinate2d(Longitude(+0.36), Latitude(+90.0))), 1);
            EXPECT_EQ(4u, outKeys.size());
            EXPECT_NE(outKeys.end(), std::find(outKeys.begin(), outKeys.end(),
                QuadKey(Type::Bing, 0, 0, 1)));
            EXPECT_NE(outKeys.end(), std::find(outKeys.begin(), outKeys.end(),
                QuadKey(Type::Bing, 0, 1, 1)));
            EXPECT_NE(outKeys.end(), std::find(outKeys.begin(), outKeys.end(),
                QuadKey(Type::Bing, 1, 0, 1)));
            EXPECT_NE(outKeys.end(), std::find(outKeys.begin(), outKeys.end(),
                QuadKey(Type::Bing, 1, 1, 1)));
        }
    }

    TEST(BINGSYSTEM, SelectedCities)
    {
        QuadKey key;
        const Type type = Type::Bing;

        { // Chicago 41.822, -87.635
            const std::uint8_t depth = 16;
            GeoCoordinate2d coords(Longitude(-87.635), Latitude(41.822));

            key = QuadKey::getKeyFromLongitudeLatitudeAtDepth(type, coords,
                depth);
            std::string keyStr = key.toInternalString();
            EXPECT_EQ("0302222310321132", keyStr);

            GeoCoordinateBoundingBox2d bbox;
            key.getGeoCoordinateBounds2d(bbox);

            // Note that Bing will return a bounding box of all sides inclusive
            std::vector<QuadKey> keys;
            keys = QuadKey::getKeysFromLongitudeLatitudeBoundingBox(type, bbox,
                depth);
            EXPECT_EQ(4u, keys.size());
            EXPECT_NE(keys.end(), std::find(keys.begin(), keys.end(), key));
        }

        { // Rio -43.1964,-22.9083
            const std::uint8_t depth = 17;
            GeoCoordinate2d coords(Longitude(-43.1964), Latitude(-22.9083));

            key = QuadKey::getKeyFromLongitudeLatitudeAtDepth(type, coords,
                depth);
            std::string keyStr = key.toInternalString();
            EXPECT_EQ("21120001212232200", keyStr);

            GeoCoordinateBoundingBox2d bbox;
            key.getGeoCoordinateBounds2d(bbox);

            // Note that Bing will return a bounding box of all sides inclusive
            std::vector<QuadKey> keys;
            keys = QuadKey::getKeysFromLongitudeLatitudeBoundingBox(type, bbox,
                depth);
            EXPECT_EQ(4u, keys.size());
            EXPECT_NE(keys.end(), std::find(keys.begin(), keys.end(), key));
        }

        { // Helsinki 60.1708 N, 24.9375 E
            const std::uint8_t depth = 17;
            GeoCoordinate2d coords(Longitude(24.9375), Latitude(60.1708));

            key = QuadKey::getKeyFromLongitudeLatitudeAtDepth(type, coords,
                depth);
            std::string keyStr = key.toInternalString();
            EXPECT_EQ("12012021101330131", keyStr);

            GeoCoordinateBoundingBox2d bbox;
            key.getGeoCoordinateBounds2d(bbox);

            // Note that Bing will return a bounding box of all sides inclusive
            std::vector<QuadKey> keys;
            keys = QuadKey::getKeysFromLongitudeLatitudeBoundingBox(type, bbox,
                depth);
            EXPECT_EQ(4u, keys.size());
            EXPECT_NE(keys.end(), std::find(keys.begin(), keys.end(), key));
        }

        { // Cape Town South Africa 33.9253 S, 18.4239 E
            const std::uint8_t depth = 17;
            GeoCoordinate2d coords(Longitude(18.4239), Latitude(-33.9253));

            key = QuadKey::getKeyFromLongitudeLatitudeAtDepth(type, coords,
                depth);
            std::string keyStr = key.toInternalString();
            EXPECT_EQ("30023103202132011", keyStr);

            GeoCoordinateBoundingBox2d bbox;
            key.getGeoCoordinateBounds2d(bbox);

            // Note that Bing will return a bounding box of all sides inclusive
            std::vector<QuadKey> keys;
            keys = QuadKey::getKeysFromLongitudeLatitudeBoundingBox(type, bbox,
                depth);
            EXPECT_EQ(4u, keys.size());
            EXPECT_NE(keys.end(), std::find(keys.begin(), keys.end(), key));
        }

        { // Quito 0.2500 S, 78.5833 W
            const std::uint8_t depth = 17;
            GeoCoordinate2d coords(Longitude(-78.5836), Latitude(-0.25));

            key = QuadKey::getKeyFromLongitudeLatitudeAtDepth(type, coords,
                depth);
            std::string keyStr = key.toInternalString();
            EXPECT_EQ("21001000002133122", keyStr);

            GeoCoordinateBoundingBox2d bbox;
            key.getGeoCoordinateBounds2d(bbox);

            // Note that Bing will return a bounding box of all sides inclusive
            std::vector<QuadKey> keys;
            keys = QuadKey::getKeysFromLongitudeLatitudeBoundingBox(type, bbox,
                depth);
            EXPECT_EQ(4u, keys.size());
            EXPECT_NE(keys.end(), std::find(keys.begin(), keys.end(), key));
        }
    }
}

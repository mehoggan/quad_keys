#include <gtest/gtest.h>

#include "QuadKey/GeoCoordinate2d.h"
#include "QuadKey/QuadKey.h"

#include <iostream>
#include <sstream>
#include <utility>

namespace QuadKeys
{
    class MortonSystemTest : public ::testing::Test
    {
    protected:
        virtual void SetUp() {}
        virtual void TearDown() {}
    };

    TEST(NDSSYSTEM, IsValid)
    {
        // Same as BingSystem
    }

    TEST(NDSSYSTEM, IsRootKey)
    {
        // Same as BingSystem
    }

    TEST(NDSSYSTEM, GetParent)
    {
        // Same as BingSystem
    }

    TEST(NDSSYSTEM, IsMyAncestor)
    {
        // Same as BingSystem
    }

    TEST(NDSSYSTEM, GetAncestor)
    {
        {
              QuadKey key(Type::Morton, 0, 1, 1);
              QuadKey ancestor(Type::Morton, 0, 0, 0);
              EXPECT_EQ(ancestor, key.getAncestor(1));
              EXPECT_EQ(key.getParent(), key.getAncestor(1));
        }
        {
              QuadKey key(Type::Morton, 0, 0, 1);
              QuadKey ancestor(Type::Morton, 0, 0, 0);
              EXPECT_EQ(ancestor, key.getAncestor(1));
              EXPECT_EQ(key.getParent(), key.getAncestor(1));
        }
        {
              QuadKey key(Type::Morton, 1, 1, 1);
              QuadKey ancestor(Type::Morton, 0, 0, 0);
              EXPECT_EQ(ancestor, key.getAncestor(1));
        }
        {
              QuadKey key(Type::Morton, 1, 2, 1);
              QuadKey ancestor(Type::Morton, 0, 1, 0);
              EXPECT_EQ(ancestor, key.getAncestor(1));
        }
        {
              QuadKey key(Type::Morton, 0, 3, 1);
              QuadKey ancestor(Type::Morton, 0, 1, 0);
              EXPECT_EQ(ancestor, key.getAncestor(1));
        }
    }

    TEST(NDSSYSTEM, GetChild)
    {
        // Same as BingSystem
    }

    TEST(NDSSYSTEM, GetChildren)
    {
        // Same as BingSystem
    }

    TEST(NDSSYSTEM, GetDescendants)
    {
        // Same as BingSystem
    }

    TEST(NDSSYSTEM, GetSiblings)
    {
        std::vector<QuadKey> testKeys;
        testKeys = QuadKey(Type::Morton, 0, 0, 1).getSiblings();
        EXPECT_EQ(3u, testKeys.size());
        EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
            QuadKey(Type::Morton, 1, 0, 1)), testKeys.end());
        EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
            QuadKey(Type::Morton, 1, 1, 1)), testKeys.end());
        EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
            QuadKey(Type::Morton, 0, 1, 1)), testKeys.end());
        testKeys = QuadKey(Type::Morton, 1, 3, 1).getSiblings();
        EXPECT_EQ(3u, testKeys.size());
        EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
            QuadKey(Type::Morton, 1, 2, 1)), testKeys.end());
        EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
            QuadKey(Type::Morton, 0, 2, 1)), testKeys.end());
        EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
            QuadKey(Type::Morton, 0, 3, 1)), testKeys.end());
    }

    TEST(NDSSYSTEM, GetNeighbors)
    {
        // Same as BingSystem but just to be safe
        std::vector<QuadKey> testKeys;
        testKeys = QuadKey().getNeighbors();
        EXPECT_TRUE(testKeys.empty());
        testKeys.clear();

        testKeys = QuadKey(Type::Morton, 0, 0, 2).getNeighbors();
        EXPECT_EQ(5u, testKeys.size());
        EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
            QuadKey(Type::Morton, 0, 1, 2)), testKeys.end());
        EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
            QuadKey(Type::Morton, 1, 1, 2)), testKeys.end());
        EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
            QuadKey(Type::Morton, 1, 0, 2)), testKeys.end());
        EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
            QuadKey(Type::Morton, 0, 7, 2)), testKeys.end());
        EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
            QuadKey(Type::Morton, 1, 7, 2)), testKeys.end());
        testKeys.clear();

        testKeys = QuadKey(Type::Morton, 0, 1, 2).getNeighbors();
        EXPECT_EQ(5u, testKeys.size());
        EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
            QuadKey(Type::Morton, 0, 0, 2)), testKeys.end());
        EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
            QuadKey(Type::Morton, 1, 0, 2)), testKeys.end());
        EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
            QuadKey(Type::Morton, 1, 1, 2)), testKeys.end());
        EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
            QuadKey(Type::Morton, 1, 2, 2)), testKeys.end());
        EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
            QuadKey(Type::Morton, 0, 2, 2)), testKeys.end());
        testKeys.clear();

        testKeys = QuadKey(Type::Morton, 0, 2, 2).getNeighbors();
        EXPECT_EQ(5u, testKeys.size());
        EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
            QuadKey(Type::Morton, 0, 1, 2)), testKeys.end());
        EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
            QuadKey(Type::Morton, 1, 1, 2)), testKeys.end());
        EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
            QuadKey(Type::Morton, 1, 2, 2)), testKeys.end());
        EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
            QuadKey(Type::Morton, 1, 3, 2)), testKeys.end());
        EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
            QuadKey(Type::Morton, 0, 3, 2)), testKeys.end());
        testKeys.clear();

        testKeys = QuadKey(Type::Morton, 0, 3, 2).getNeighbors();
        EXPECT_EQ(5u, testKeys.size());
        EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
            QuadKey(Type::Morton, 0, 2, 2)), testKeys.end());
        EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
            QuadKey(Type::Morton, 1, 2, 2)), testKeys.end());
        EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
            QuadKey(Type::Morton, 1, 3, 2)), testKeys.end());
        EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
            QuadKey(Type::Morton, 1, 4, 2)), testKeys.end());
        EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
            QuadKey(Type::Morton, 0, 4, 2)), testKeys.end());
        testKeys.clear();

        testKeys = QuadKey(Type::Morton, 0, 0, 2).getNeighbors();
        EXPECT_EQ(5u, testKeys.size());
        EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
            QuadKey(Type::Morton, 0, 1, 2)), testKeys.end());
        EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
            QuadKey(Type::Morton, 1, 1, 2)), testKeys.end());
        EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
            QuadKey(Type::Morton, 1, 0, 2)), testKeys.end());
        EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
            QuadKey(Type::Morton, 1, 7, 2)), testKeys.end());
        EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
            QuadKey(Type::Morton, 0, 7, 2)), testKeys.end());
        testKeys.clear();

        testKeys = QuadKey(Type::Morton, 3, 1, 2).getNeighbors();
        EXPECT_EQ(5u, testKeys.size());
        EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
            QuadKey(Type::Morton, 3, 0, 2)), testKeys.end());
        EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
            QuadKey(Type::Morton, 2, 0, 2)), testKeys.end());
        EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
            QuadKey(Type::Morton, 2, 1, 2)), testKeys.end());
        EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
            QuadKey(Type::Morton, 2, 2, 2)), testKeys.end());
        EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
            QuadKey(Type::Morton, 3, 2, 2)), testKeys.end());
        testKeys.clear();

        testKeys = QuadKey(Type::Morton, 3, 2, 2).getNeighbors();
        EXPECT_EQ(5u, testKeys.size());
        EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
            QuadKey(Type::Morton, 3, 1, 2)), testKeys.end());
        EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
            QuadKey(Type::Morton, 2, 1, 2)), testKeys.end());
        EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
            QuadKey(Type::Morton, 2, 2, 2)), testKeys.end());
        EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
            QuadKey(Type::Morton, 2, 3, 2)), testKeys.end());
        EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
            QuadKey(Type::Morton, 3, 3, 2)), testKeys.end());
        testKeys.clear();

        testKeys = QuadKey(Type::Morton, 3, 3, 2).getNeighbors();
        EXPECT_EQ(5u, testKeys.size());
        EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
            QuadKey(Type::Morton, 3, 2, 2)), testKeys.end());
        EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
            QuadKey(Type::Morton, 2, 2, 2)), testKeys.end());
        EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
            QuadKey(Type::Morton, 2, 3, 2)), testKeys.end());
        EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
            QuadKey(Type::Morton, 2, 4, 2)), testKeys.end());
        EXPECT_NE(std::find(testKeys.begin(), testKeys.end(),
            QuadKey(Type::Morton, 3, 4, 2)), testKeys.end());
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

        testKeys = QuadKey(Type::Morton, 0, 0, 0).getNeighbors();
        EXPECT_EQ(0u, testKeys.size());
    }

    TEST(NDSSYSTEM, FromStringToString)
    {
        // X ==> Unused
        // O ==> Used but never set
        // (0,1) ==> Binary digits
        QuadKey quadKey(Type::Morton, 0, 0, 0);
        std::string fmt = quadKey.toInternalString();
        EXPECT_EQ("65537", fmt); // XXXX XXXX XXXX XXX1 XXXX XXXX XXXX XXO1
        QuadKey quadKeyBack = QuadKey::fromInternalString(Type::Morton, fmt);
        EXPECT_EQ(quadKey, quadKeyBack);

        quadKey = QuadKey(Type::Morton, 0, 1, 0);
        fmt = quadKey.toInternalString();
        EXPECT_EQ("65536", fmt); // XXXX XXXX XXXX XXX1 XXXX XXXX XXXX XXO0
        quadKeyBack = QuadKey::fromInternalString(Type::Morton, fmt);
        EXPECT_EQ(quadKey, quadKeyBack);

        quadKey = QuadKey(Type::Morton, 0, 0, 1);
        fmt = quadKey.toInternalString();
        EXPECT_EQ("131078", fmt); // XXXX XXXX XXXX XX1X XXXX XXXX XXXX O110
        quadKeyBack = QuadKey::fromInternalString(Type::Morton, fmt);
        EXPECT_EQ(quadKey, quadKeyBack);

        quadKey = QuadKey(Type::Morton, 0, 1, 1);
        fmt = quadKey.toInternalString();
        EXPECT_EQ("131079", fmt); // XXXX XXXX XXXX XX1O OOOO OOOO OOOO O111
        quadKeyBack = QuadKey::fromInternalString(Type::Morton, fmt);
        EXPECT_EQ(quadKey, quadKeyBack);

        quadKey = QuadKey(Type::Morton, 0, 2, 1);
        fmt = quadKey.toInternalString();
        EXPECT_EQ("131074", fmt); // XXXX XXXX XXXX XX1X XXXX XXXX XXXX O010
        quadKeyBack = QuadKey::fromInternalString(Type::Morton, fmt);
        EXPECT_EQ(quadKey, quadKeyBack);

        quadKey = QuadKey(Type::Morton, 0, 3, 1);
        fmt = quadKey.toInternalString();
        EXPECT_EQ("131075", fmt); // XXXX XXXX XXXX XX1X XXXX XXXX XXXX O011
        quadKeyBack = QuadKey::fromInternalString(Type::Morton, fmt);
        EXPECT_EQ(quadKey, quadKeyBack);

        quadKey = QuadKey(Type::Morton, 1, 0, 1);
        fmt = quadKey.toInternalString();
        EXPECT_EQ("131076", fmt); // XXXX XXXX XXXX XX1X XXXX XXXX XXXX O100
        quadKeyBack = QuadKey::fromInternalString(Type::Morton, fmt);
        EXPECT_EQ(quadKey, quadKeyBack);

        quadKey = QuadKey(Type::Morton, 1, 1, 1);
        fmt = quadKey.toInternalString();
        EXPECT_EQ("131077", fmt); // XXXX XXXX XXXX XX1X XXXX XXXX XXXX O101
        quadKeyBack = QuadKey::fromInternalString(Type::Morton, fmt);
        EXPECT_EQ(quadKey, quadKeyBack);

        quadKey = QuadKey(Type::Morton, 1, 2, 1);
        fmt = quadKey.toInternalString();
        EXPECT_EQ("131072", fmt); // XXXX XXXX XXXX XX1X XXXX XXXX XXXX O000
        quadKeyBack = QuadKey::fromInternalString(Type::Morton, fmt);
        EXPECT_EQ(quadKey, quadKeyBack);

        quadKey = QuadKey(Type::Morton, 1, 3, 1);
        fmt = quadKey.toInternalString();
        EXPECT_EQ("131073", fmt); // XXXX XXXX XXXX XX1X XXXX XXXX XXXX O001
        quadKeyBack = QuadKey::fromInternalString(Type::Morton, fmt);
        EXPECT_EQ(quadKey, quadKeyBack);

        quadKey = QuadKey(Type::Morton, 0, 0, 2);
        fmt = quadKey.toInternalString();
        EXPECT_EQ("262168", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO1 1000
        quadKeyBack = QuadKey::fromInternalString(Type::Morton, fmt);
        EXPECT_EQ(quadKey, quadKeyBack);

        quadKey = QuadKey(Type::Morton, 0, 1, 2);
        fmt = quadKey.toInternalString();
        EXPECT_EQ("262169", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO1 1001
        quadKeyBack = QuadKey::fromInternalString(Type::Morton, fmt);
        EXPECT_EQ(quadKey, quadKeyBack);

        quadKey = QuadKey(Type::Morton, 0, 2, 2);
        fmt = quadKey.toInternalString();
        EXPECT_EQ("262172", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO1 1100
        quadKeyBack = QuadKey::fromInternalString(Type::Morton, fmt);
        EXPECT_EQ(quadKey, quadKeyBack);

        quadKey = QuadKey(Type::Morton, 0, 3, 2);
        fmt = quadKey.toInternalString();
        EXPECT_EQ("262173", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO1 1101
        quadKeyBack = QuadKey::fromInternalString(Type::Morton, fmt);
        EXPECT_EQ(quadKey, quadKeyBack);

        quadKey = QuadKey(Type::Morton, 0, 4, 2);
        fmt = quadKey.toInternalString();
        EXPECT_EQ("262152", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO0 1000
        quadKeyBack = QuadKey::fromInternalString(Type::Morton, fmt);
        EXPECT_EQ(quadKey, quadKeyBack);

        quadKey = QuadKey(Type::Morton, 0, 5, 2);
        fmt = quadKey.toInternalString();
        EXPECT_EQ("262153", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO0 1001
        quadKeyBack = QuadKey::fromInternalString(Type::Morton, fmt);
        EXPECT_EQ(quadKey, quadKeyBack);

        quadKey = QuadKey(Type::Morton, 0, 6, 2);
        fmt = quadKey.toInternalString();
        EXPECT_EQ("262156", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO0 1100
        quadKeyBack = QuadKey::fromInternalString(Type::Morton, fmt);
        EXPECT_EQ(quadKey, quadKeyBack);

        quadKey = QuadKey(Type::Morton, 0, 7, 2);
        fmt = quadKey.toInternalString();
        EXPECT_EQ("262157", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO0 1101
        quadKeyBack = QuadKey::fromInternalString(Type::Morton, fmt);
        EXPECT_EQ(quadKey, quadKeyBack);

        quadKey = QuadKey(Type::Morton, 1, 0, 2);
        fmt = quadKey.toInternalString();
        EXPECT_EQ("262170", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO1 1010
        quadKeyBack = QuadKey::fromInternalString(Type::Morton, fmt);
        EXPECT_EQ(quadKey, quadKeyBack);

        quadKey = QuadKey(Type::Morton, 1, 1, 2);
        fmt = quadKey.toInternalString();
        EXPECT_EQ("262171", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO1 1011
        quadKeyBack = QuadKey::fromInternalString(Type::Morton, fmt);
        EXPECT_EQ(quadKey, quadKeyBack);

        quadKey = QuadKey(Type::Morton, 1, 2, 2);
        fmt = quadKey.toInternalString();
        EXPECT_EQ("262174", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO1 1110
        quadKeyBack = QuadKey::fromInternalString(Type::Morton, fmt);
        EXPECT_EQ(quadKey, quadKeyBack);

        quadKey = QuadKey(Type::Morton, 1, 3, 2);
        fmt = quadKey.toInternalString();
        EXPECT_EQ("262175", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO1 1111
        quadKeyBack = QuadKey::fromInternalString(Type::Morton, fmt);
        EXPECT_EQ(quadKey, quadKeyBack);

        quadKey = QuadKey(Type::Morton, 1, 4, 2);
        fmt = quadKey.toInternalString();
        EXPECT_EQ("262154", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO0 1010
        quadKeyBack = QuadKey::fromInternalString(Type::Morton, fmt);
        EXPECT_EQ(quadKey, quadKeyBack);

        quadKey = QuadKey(Type::Morton, 1, 5, 2);
        fmt = quadKey.toInternalString();
        EXPECT_EQ("262155", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO0 1011
        quadKeyBack = QuadKey::fromInternalString(Type::Morton, fmt);
        EXPECT_EQ(quadKey, quadKeyBack);

        quadKey = QuadKey(Type::Morton, 1, 6, 2);
        fmt = quadKey.toInternalString();
        EXPECT_EQ("262158", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO0 1110
        quadKeyBack = QuadKey::fromInternalString(Type::Morton, fmt);
        EXPECT_EQ(quadKey, quadKeyBack);

        quadKey = QuadKey(Type::Morton, 1, 7, 2);
        fmt = quadKey.toInternalString();
        EXPECT_EQ("262159", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO0 1111
        quadKeyBack = QuadKey::fromInternalString(Type::Morton, fmt);
        EXPECT_EQ(quadKey, quadKeyBack);

        quadKey = QuadKey(Type::Morton, 2, 0, 2);
        fmt = quadKey.toInternalString();
        EXPECT_EQ("262160", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO1 0000
        quadKeyBack = QuadKey::fromInternalString(Type::Morton, fmt);
        EXPECT_EQ(quadKey, quadKeyBack);

        quadKey = QuadKey(Type::Morton, 2, 1, 2);
        fmt = quadKey.toInternalString();
        EXPECT_EQ("262161", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO1 0001
        quadKeyBack = QuadKey::fromInternalString(Type::Morton, fmt);
        EXPECT_EQ(quadKey, quadKeyBack);

        quadKey = QuadKey(Type::Morton, 2, 2, 2);
        fmt = quadKey.toInternalString();
        EXPECT_EQ("262164", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO1 0100
        quadKeyBack = QuadKey::fromInternalString(Type::Morton, fmt);
        EXPECT_EQ(quadKey, quadKeyBack);

        quadKey = QuadKey(Type::Morton, 2, 3, 2);
        fmt = quadKey.toInternalString();
        EXPECT_EQ("262165", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO1 0101
        quadKeyBack = QuadKey::fromInternalString(Type::Morton, fmt);
        EXPECT_EQ(quadKey, quadKeyBack);

        quadKey = QuadKey(Type::Morton, 2, 4, 2);
        fmt = quadKey.toInternalString();
        EXPECT_EQ("262144", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO0 0000
        quadKeyBack = QuadKey::fromInternalString(Type::Morton, fmt);
        EXPECT_EQ(quadKey, quadKeyBack);

        quadKey = QuadKey(Type::Morton, 2, 5, 2);
        fmt = quadKey.toInternalString();
        EXPECT_EQ("262145", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO0 0001
        quadKeyBack = QuadKey::fromInternalString(Type::Morton, fmt);
        EXPECT_EQ(quadKey, quadKeyBack);

        quadKey = QuadKey(Type::Morton, 2, 6, 2);
        fmt = quadKey.toInternalString();
        EXPECT_EQ("262148", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO0 0100
        quadKeyBack = QuadKey::fromInternalString(Type::Morton, fmt);
        EXPECT_EQ(quadKey, quadKeyBack);

        quadKey = QuadKey(Type::Morton, 2, 7, 2);
        fmt = quadKey.toInternalString();
        EXPECT_EQ("262149", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO0 0101
        quadKeyBack = QuadKey::fromInternalString(Type::Morton, fmt);
        EXPECT_EQ(quadKey, quadKeyBack);

        quadKey = QuadKey(Type::Morton, 3, 0, 2);
        fmt = quadKey.toInternalString();
        EXPECT_EQ("262162", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO1 0010
        quadKeyBack = QuadKey::fromInternalString(Type::Morton, fmt);
        EXPECT_EQ(quadKey, quadKeyBack);

        quadKey = QuadKey(Type::Morton, 3, 1, 2);
        fmt = quadKey.toInternalString();
        EXPECT_EQ("262163", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO1 0011
        quadKeyBack = QuadKey::fromInternalString(Type::Morton, fmt);
        EXPECT_EQ(quadKey, quadKeyBack);

        quadKey = QuadKey(Type::Morton, 3, 2, 2);
        fmt = quadKey.toInternalString();
        EXPECT_EQ("262166", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO1 0110
        quadKeyBack = QuadKey::fromInternalString(Type::Morton, fmt);
        EXPECT_EQ(quadKey, quadKeyBack);

        quadKey = QuadKey(Type::Morton, 3, 3, 2);
        fmt = quadKey.toInternalString();
        EXPECT_EQ("262167", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO1 0111
        quadKeyBack = QuadKey::fromInternalString(Type::Morton, fmt);
        EXPECT_EQ(quadKey, quadKeyBack);

        quadKey = QuadKey(Type::Morton, 3, 4, 2);
        fmt = quadKey.toInternalString();
        EXPECT_EQ("262146", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO0 0010
        quadKeyBack = QuadKey::fromInternalString(Type::Morton, fmt);
        EXPECT_EQ(quadKey, quadKeyBack);

        quadKey = QuadKey(Type::Morton, 3, 5, 2);
        fmt = quadKey.toInternalString();
        EXPECT_EQ("262147", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO0 0011
        quadKeyBack = QuadKey::fromInternalString(Type::Morton, fmt);
        EXPECT_EQ(quadKey, quadKeyBack);

        quadKey = QuadKey(Type::Morton, 3, 6, 2);
        fmt = quadKey.toInternalString();
        EXPECT_EQ("262150", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO0 0110
        quadKeyBack = QuadKey::fromInternalString(Type::Morton, fmt);
        EXPECT_EQ(quadKey, quadKeyBack);

        quadKey = QuadKey(Type::Morton, 3, 7, 2);
        fmt = quadKey.toInternalString();
        EXPECT_EQ("262151", fmt); // XXXX XXXX XXXX X1XX XXXX XXXX XXO0 0111
        quadKeyBack = QuadKey::fromInternalString(Type::Morton, fmt);
        EXPECT_EQ(quadKey, quadKeyBack);
    }

    TEST(NDSSYSTEM, GetKeyFromLongitudeLatitudeAtDepthToBounds)
    {
        GeoCoordinate2d coords;
        std::uint8_t depth = 0;
        { // West
            QuadKey ndsKey;
            coords = GeoCoordinate2d(Longitude(-0.1), Latitude(0.0));
            ndsKey = QuadKey::getKeyFromLongitudeLatitudeAtDepth(
                Type::Morton, coords, depth);
            EXPECT_EQ("65537", ndsKey.toInternalString());
            coords = GeoCoordinate2d(Longitude(-180.0), Latitude(90.0));
            ndsKey = QuadKey::getKeyFromLongitudeLatitudeAtDepth(
                Type::Morton, coords, depth);
            EXPECT_EQ("65537", ndsKey.toInternalString());
            coords = GeoCoordinate2d(Longitude(-180.0), Latitude(-90.0));
            ndsKey = QuadKey::getKeyFromLongitudeLatitudeAtDepth(
                Type::Morton, coords, depth);
            EXPECT_EQ("65537", ndsKey.toInternalString());
            GeoCoordinateBoundingBox2d actual;
            ndsKey.getGeoCoordinateBounds2d(actual);
            EXPECT_TRUE(GeoCoordinate2d(Longitude(-180.0),
                Latitude(- 90.0)).near(actual.lowerLeft(), 1)) <<
                "actual = " << actual.lowerLeft();
            EXPECT_TRUE(GeoCoordinate2d(Longitude(-  0.1),
                Latitude(+ 90.0)).near(actual.upperRight(), 1)) <<
                "actual = " << actual.upperRight();
        }
        { // East
            QuadKey ndsKey;
            coords = GeoCoordinate2d(Longitude(0.0), Latitude(0.0));
            ndsKey = QuadKey::getKeyFromLongitudeLatitudeAtDepth(
                Type::Morton, coords, depth);
            EXPECT_EQ("65536", ndsKey.toInternalString());
            coords = GeoCoordinate2d(Longitude(180.0), Latitude(-90.0));
            ndsKey = QuadKey::getKeyFromLongitudeLatitudeAtDepth(
                Type::Morton, coords, depth);
            EXPECT_EQ("65536", ndsKey.toInternalString());
            coords = GeoCoordinate2d(Longitude(180.0), Latitude(90.0));
            ndsKey = QuadKey::getKeyFromLongitudeLatitudeAtDepth(
                Type::Morton, coords, depth);
            EXPECT_EQ("65536", ndsKey.toInternalString());
            GeoCoordinateBoundingBox2d actual;
            ndsKey.getGeoCoordinateBounds2d(actual);
            EXPECT_TRUE(GeoCoordinate2d(Longitude(+  0.0),
                Latitude(- 90.0)).near(actual.lowerLeft(), 1)) <<
                "actual = " << actual.lowerLeft();
            EXPECT_TRUE(GeoCoordinate2d(Longitude(+180.0),
                Latitude(+ 90.0)).near(actual.upperRight(), 1)) <<
                "actual = " << actual.upperRight();
        }
        depth = 1;
        { // 0x6
            QuadKey ndsKey;
            coords = GeoCoordinate2d(Longitude(-180.0), Latitude(-0.1));
            ndsKey = QuadKey::getKeyFromLongitudeLatitudeAtDepth(
                Type::Morton, coords, depth);
            EXPECT_EQ("131078", ndsKey.toInternalString());
            coords = GeoCoordinate2d(Longitude(-180.0), Latitude(-90.0));
            ndsKey = QuadKey::getKeyFromLongitudeLatitudeAtDepth(
                Type::Morton, coords, depth);
            EXPECT_EQ("131078", ndsKey.toInternalString());
            coords = GeoCoordinate2d(Longitude(-90.1), Latitude(-90.0));
            ndsKey = QuadKey::getKeyFromLongitudeLatitudeAtDepth(
                Type::Morton, coords, depth);
            EXPECT_EQ("131078", ndsKey.toInternalString());
            coords = GeoCoordinate2d(Longitude(-90.1), Latitude(-0.1));
            ndsKey = QuadKey::getKeyFromLongitudeLatitudeAtDepth(
                Type::Morton, coords, depth);
            EXPECT_EQ("131078", ndsKey.toInternalString());
        }
        { // 0x7
            QuadKey ndsKey;
            coords = GeoCoordinate2d(Longitude(-90.0), Latitude(-0.1));
            ndsKey = QuadKey::getKeyFromLongitudeLatitudeAtDepth(
                Type::Morton, coords, depth);
            EXPECT_EQ("131079", ndsKey.toInternalString());
            coords = GeoCoordinate2d(Longitude(-90.0), Latitude(-90.0));
            ndsKey = QuadKey::getKeyFromLongitudeLatitudeAtDepth(
                Type::Morton, coords, depth);
            EXPECT_EQ("131079", ndsKey.toInternalString());
            coords = GeoCoordinate2d(Longitude(-0.1), Latitude(-90.0));
            ndsKey = QuadKey::getKeyFromLongitudeLatitudeAtDepth(
                Type::Morton, coords, depth);
            EXPECT_EQ("131079", ndsKey.toInternalString());
            coords = GeoCoordinate2d(Longitude(-0.1), Latitude(-0.1));
            ndsKey = QuadKey::getKeyFromLongitudeLatitudeAtDepth(
                Type::Morton, coords, depth);
            EXPECT_EQ("131079", ndsKey.toInternalString());
        }
        { // 0x2
            QuadKey ndsKey;
            coords = GeoCoordinate2d(Longitude(0.0), Latitude(-0.1));
            ndsKey = QuadKey::getKeyFromLongitudeLatitudeAtDepth(
                Type::Morton, coords, depth);
            EXPECT_EQ("131074", ndsKey.toInternalString());
            coords = GeoCoordinate2d(Longitude(0.0), Latitude(-90.0));
            ndsKey = QuadKey::getKeyFromLongitudeLatitudeAtDepth(
                Type::Morton, coords, depth);
            EXPECT_EQ("131074", ndsKey.toInternalString());
            coords = GeoCoordinate2d(Longitude(90.0), Latitude(-90.0));
            ndsKey = QuadKey::getKeyFromLongitudeLatitudeAtDepth(
                Type::Morton, coords, depth);
            EXPECT_EQ("131074", ndsKey.toInternalString());
            coords = GeoCoordinate2d(Longitude(90.0), Latitude(-0.1));
            ndsKey = QuadKey::getKeyFromLongitudeLatitudeAtDepth(
                Type::Morton, coords, depth);
            EXPECT_EQ("131074", ndsKey.toInternalString());
        }
        { // 0x3
            QuadKey ndsKey;
            coords = GeoCoordinate2d(Longitude(90.1), Latitude(-0.1));
            ndsKey = QuadKey::getKeyFromLongitudeLatitudeAtDepth(
                Type::Morton, coords, depth);
            EXPECT_EQ("131075", ndsKey.toInternalString());
            coords = GeoCoordinate2d(Longitude(90.1), Latitude(-90.0));
            ndsKey = QuadKey::getKeyFromLongitudeLatitudeAtDepth(
                Type::Morton, coords, depth);
            EXPECT_EQ("131075", ndsKey.toInternalString());
            coords = GeoCoordinate2d(Longitude(180.0), Latitude(-90.0));
            ndsKey = QuadKey::getKeyFromLongitudeLatitudeAtDepth(
                Type::Morton, coords, depth);
            EXPECT_EQ("131075", ndsKey.toInternalString());
            coords = GeoCoordinate2d(Longitude(180.0), Latitude(-0.1));
            ndsKey = QuadKey::getKeyFromLongitudeLatitudeAtDepth(
                Type::Morton, coords, depth);
            EXPECT_EQ("131075", ndsKey.toInternalString());
        }
        { // 0x4
            QuadKey ndsKey;
            coords = GeoCoordinate2d(Longitude(-180.0), Latitude(90.0));
            ndsKey = QuadKey::getKeyFromLongitudeLatitudeAtDepth(
                Type::Morton, coords, depth);
            EXPECT_EQ("131076", ndsKey.toInternalString());
            coords = GeoCoordinate2d(Longitude(-180.0), Latitude(0.0));
            ndsKey = QuadKey::getKeyFromLongitudeLatitudeAtDepth(
                Type::Morton, coords, depth);
            EXPECT_EQ("131076", ndsKey.toInternalString());
            coords = GeoCoordinate2d(Longitude(-90.1), Latitude(0.0));
            ndsKey = QuadKey::getKeyFromLongitudeLatitudeAtDepth(
                Type::Morton, coords, depth);
            EXPECT_EQ("131076", ndsKey.toInternalString());
            coords = GeoCoordinate2d(Longitude(-90.1), Latitude(90.0));
            ndsKey = QuadKey::getKeyFromLongitudeLatitudeAtDepth(
                Type::Morton, coords, depth);
            EXPECT_EQ("131076", ndsKey.toInternalString());
        }
        { // 0x5
            QuadKey ndsKey;
            coords = GeoCoordinate2d(Longitude(-90.0), Latitude(90.0));
            ndsKey = QuadKey::getKeyFromLongitudeLatitudeAtDepth(
                Type::Morton, coords, depth);
            EXPECT_EQ("131077", ndsKey.toInternalString());
            coords = GeoCoordinate2d(Longitude(-90.0), Latitude(0.0));
            ndsKey = QuadKey::getKeyFromLongitudeLatitudeAtDepth(
                Type::Morton, coords, depth);
            EXPECT_EQ("131077", ndsKey.toInternalString());
            coords = GeoCoordinate2d(Longitude(-0.1), Latitude(0.0));
            ndsKey = QuadKey::getKeyFromLongitudeLatitudeAtDepth(
                Type::Morton, coords, depth);
            EXPECT_EQ("131077", ndsKey.toInternalString());
            coords = GeoCoordinate2d(Longitude(-0.1), Latitude(90.0));
            ndsKey = QuadKey::getKeyFromLongitudeLatitudeAtDepth(
                Type::Morton, coords, depth);
            EXPECT_EQ("131077", ndsKey.toInternalString());
        }
        { // 0x0
            QuadKey ndsKey;
            coords = GeoCoordinate2d(Longitude(0.0), Latitude(90.0));
            ndsKey = QuadKey::getKeyFromLongitudeLatitudeAtDepth(
                Type::Morton, coords, depth);
            EXPECT_EQ("131072", ndsKey.toInternalString());
            coords = GeoCoordinate2d(Longitude(0.0), Latitude(0.0));
            ndsKey = QuadKey::getKeyFromLongitudeLatitudeAtDepth(
                Type::Morton, coords, depth);
            EXPECT_EQ("131072", ndsKey.toInternalString());
            coords = GeoCoordinate2d(Longitude(90.0), Latitude(0.0));
            ndsKey = QuadKey::getKeyFromLongitudeLatitudeAtDepth(
                Type::Morton, coords, depth);
            EXPECT_EQ("131072", ndsKey.toInternalString());
            coords = GeoCoordinate2d(Longitude(90.0), Latitude(90.0));
            ndsKey = QuadKey::getKeyFromLongitudeLatitudeAtDepth(
                Type::Morton, coords, depth);
            EXPECT_EQ("131072", ndsKey.toInternalString());
        }
        { // 0x1
            QuadKey ndsKey;
            coords = GeoCoordinate2d(Longitude(90.1), Latitude(90.0));
            ndsKey = QuadKey::getKeyFromLongitudeLatitudeAtDepth(
                Type::Morton, coords, depth);
            EXPECT_EQ("131073", ndsKey.toInternalString());
            coords = GeoCoordinate2d(Longitude(90.1), Latitude(0.0));
            ndsKey = QuadKey::getKeyFromLongitudeLatitudeAtDepth(
                Type::Morton, coords, depth);
            EXPECT_EQ("131073", ndsKey.toInternalString());
            coords = GeoCoordinate2d(Longitude(180.0), Latitude(0.0));
            ndsKey = QuadKey::getKeyFromLongitudeLatitudeAtDepth(
                Type::Morton, coords, depth);
            EXPECT_EQ("131073", ndsKey.toInternalString());
            coords = GeoCoordinate2d(Longitude(180.0), Latitude(90.0));
            ndsKey = QuadKey::getKeyFromLongitudeLatitudeAtDepth(
                Type::Morton, coords, depth);
            EXPECT_EQ("131073", ndsKey.toInternalString());
        }
        depth = 2;
        for (const auto &pair : {
            std::make_pair(GeoCoordinateBoundingBox2d(
                GeoCoordinate2d(Longitude(-180.0), Latitude(- 90.0)),
                GeoCoordinate2d(Longitude(-135.1), Latitude(- 45.1))),
                "262168"),
            std::make_pair(GeoCoordinateBoundingBox2d(
                GeoCoordinate2d(Longitude(-135.0), Latitude(- 90.0)),
                GeoCoordinate2d(Longitude(- 90.1), Latitude(- 45.1))),
                "262169"),
            std::make_pair(GeoCoordinateBoundingBox2d(
                GeoCoordinate2d(Longitude(- 90.0), Latitude(- 90.0)),
                GeoCoordinate2d(Longitude(- 45.1), Latitude(- 45.1))),
                "262172"),
            std::make_pair(GeoCoordinateBoundingBox2d(
                GeoCoordinate2d(Longitude(- 45.0), Latitude(- 90.0)),
                GeoCoordinate2d(Longitude(-  0.1), Latitude(- 45.1))),
                "262173"),
            std::make_pair(GeoCoordinateBoundingBox2d(
                GeoCoordinate2d(Longitude(+  0.0), Latitude(- 90.0)),
                GeoCoordinate2d(Longitude(+ 45.0), Latitude(- 45.1))),
                "262152"),
            std::make_pair(GeoCoordinateBoundingBox2d(
                GeoCoordinate2d(Longitude(+ 45.1), Latitude(- 90.0)),
                GeoCoordinate2d(Longitude(+ 90.0), Latitude(- 45.1))),
                "262153"),
            std::make_pair(GeoCoordinateBoundingBox2d(
                GeoCoordinate2d(Longitude(+ 90.1), Latitude(- 90.0)),
                GeoCoordinate2d(Longitude(+135.0), Latitude(- 45.1))),
                "262156"),
            std::make_pair(GeoCoordinateBoundingBox2d(
                GeoCoordinate2d(Longitude(+135.1), Latitude(- 90.0)),
                GeoCoordinate2d(Longitude(+180.0), Latitude(- 45.1))),
                "262157"),
            std::make_pair(GeoCoordinateBoundingBox2d(
                GeoCoordinate2d(Longitude(-180.0), Latitude(- 45.0)),
                GeoCoordinate2d(Longitude(-135.1), Latitude(-  0.1))),
                "262170"),
            std::make_pair(GeoCoordinateBoundingBox2d(
                GeoCoordinate2d(Longitude(-135.0), Latitude(- 45.0)),
                GeoCoordinate2d(Longitude(- 90.1), Latitude(-  0.1))),
                "262171"),
            std::make_pair(GeoCoordinateBoundingBox2d(
                GeoCoordinate2d(Longitude(- 90.0), Latitude(- 45.0)),
                GeoCoordinate2d(Longitude(- 45.1), Latitude(-  0.1))),
                "262174"),
            std::make_pair(GeoCoordinateBoundingBox2d(
                GeoCoordinate2d(Longitude(- 45.0), Latitude(- 45.0)),
                GeoCoordinate2d(Longitude(-  0.1), Latitude(-  0.1))),
                "262175"),
            std::make_pair(GeoCoordinateBoundingBox2d(
                GeoCoordinate2d(Longitude(+  0.0), Latitude(- 45.0)),
                GeoCoordinate2d(Longitude(+ 45.0), Latitude(-  0.1))),
                "262154"),
            std::make_pair(GeoCoordinateBoundingBox2d(
                GeoCoordinate2d(Longitude(+ 45.1), Latitude(- 45.0)),
                GeoCoordinate2d(Longitude(+ 90.0), Latitude(-  0.1))),
                "262155"),
            std::make_pair(GeoCoordinateBoundingBox2d(
                GeoCoordinate2d(Longitude(+ 90.1), Latitude(- 45.0)),
                GeoCoordinate2d(Longitude(+135.0), Latitude(-  0.1))),
                "262158"),
            std::make_pair(GeoCoordinateBoundingBox2d(
                GeoCoordinate2d(Longitude(+135.1), Latitude(- 45.0)),
                GeoCoordinate2d(Longitude(+180.0), Latitude(-  0.1))),
                "262159"),
            std::make_pair(GeoCoordinateBoundingBox2d(
                GeoCoordinate2d(Longitude(-180.0), Latitude(+  0.0)),
                GeoCoordinate2d(Longitude(-135.1), Latitude(+ 45.0))),
                "262160"),
            std::make_pair(GeoCoordinateBoundingBox2d(
                GeoCoordinate2d(Longitude(-135.0), Latitude(+  0.0)),
                GeoCoordinate2d(Longitude(- 90.1), Latitude(+ 45.0))),
                "262161"),
            std::make_pair(GeoCoordinateBoundingBox2d(
                GeoCoordinate2d(Longitude(- 90.0), Latitude(+  0.0)),
                GeoCoordinate2d(Longitude(- 45.1), Latitude(+ 45.0))),
                "262164"),
            std::make_pair(GeoCoordinateBoundingBox2d(
                GeoCoordinate2d(Longitude(- 45.0), Latitude(+  0.0)),
                GeoCoordinate2d(Longitude(-  0.1), Latitude(+ 45.0))),
                "262165"),
            std::make_pair(GeoCoordinateBoundingBox2d(
                GeoCoordinate2d(Longitude(+  0.0), Latitude(+  0.0)),
                GeoCoordinate2d(Longitude(+ 45.0), Latitude(+ 45.0))),
                "262144"),
            std::make_pair(GeoCoordinateBoundingBox2d(
                GeoCoordinate2d(Longitude(+ 45.1), Latitude(+  0.0)),
                GeoCoordinate2d(Longitude(+ 90.0), Latitude(+ 45.0))),
                "262145"),
            std::make_pair(GeoCoordinateBoundingBox2d(
                GeoCoordinate2d(Longitude(+ 90.1), Latitude(+  0.0)),
                GeoCoordinate2d(Longitude(+135.0), Latitude(+ 45.0))),
                "262148"),
            std::make_pair(GeoCoordinateBoundingBox2d(
                GeoCoordinate2d(Longitude(+135.1), Latitude(+  0.0)),
                GeoCoordinate2d(Longitude(+180.0), Latitude(+ 45.0))),
                "262149"),
            std::make_pair(GeoCoordinateBoundingBox2d(
                GeoCoordinate2d(Longitude(-180.0), Latitude(+ 45.1)),
                GeoCoordinate2d(Longitude(-135.1), Latitude(+ 90.0))),
                "262162"),
            std::make_pair(GeoCoordinateBoundingBox2d(
                GeoCoordinate2d(Longitude(-135.0), Latitude(+ 45.1)),
                GeoCoordinate2d(Longitude(- 90.1), Latitude(+ 90.0))),
                "262163"),
            std::make_pair(GeoCoordinateBoundingBox2d(
                GeoCoordinate2d(Longitude(- 90.0), Latitude(+ 45.1)),
                GeoCoordinate2d(Longitude(- 45.1), Latitude(+ 90.0))),
                "262166"),
            std::make_pair(GeoCoordinateBoundingBox2d(
                GeoCoordinate2d(Longitude(- 45.0), Latitude(+ 45.1)),
                GeoCoordinate2d(Longitude(-  0.1), Latitude(+ 90.0))),
                "262167"),
            std::make_pair(GeoCoordinateBoundingBox2d(
                GeoCoordinate2d(Longitude(+  0.0), Latitude(+ 45.1)),
                GeoCoordinate2d(Longitude(+ 45.0), Latitude(+ 90.0))),
                "262146"),
            std::make_pair(GeoCoordinateBoundingBox2d(
                GeoCoordinate2d(Longitude(+ 45.1), Latitude(+ 45.1)),
                GeoCoordinate2d(Longitude(+ 90.0), Latitude(+ 90.0))),
                "262147"),
            std::make_pair(GeoCoordinateBoundingBox2d(
                GeoCoordinate2d(Longitude(+ 90.1), Latitude(+ 45.1)),
                GeoCoordinate2d(Longitude(+135.0), Latitude(+ 90.0))),
                "262150"),
            std::make_pair(GeoCoordinateBoundingBox2d(
                GeoCoordinate2d(Longitude(+135.1), Latitude(+ 45.1)),
                GeoCoordinate2d(Longitude(+180.0), Latitude(+ 90.0))),
                "262151"),
            }) {
            const auto &bbox = pair.first;
            GeoCoordinate2d ll(bbox.lowerLeft());
            GeoCoordinate2d lr(bbox.upperRight().longitude(),
                bbox.lowerLeft().latitude());
            GeoCoordinate2d ur(bbox.upperRight());
            GeoCoordinate2d ul(bbox.lowerLeft().longitude(),
                bbox.upperRight().latitude());
            QuadKey ndsKey;
            ndsKey = QuadKey::getKeyFromLongitudeLatitudeAtDepth(
                Type::Morton, ll, depth);
            EXPECT_EQ(pair.second, ndsKey.toInternalString()) << "ll: " <<
                pair.second << " " << pair.first;
            ndsKey = QuadKey::getKeyFromLongitudeLatitudeAtDepth(
                Type::Morton, lr, depth);
            EXPECT_EQ(pair.second, ndsKey.toInternalString()) << "lr: " <<
                pair.second << " " << pair.first;
            ndsKey = QuadKey::getKeyFromLongitudeLatitudeAtDepth(
                Type::Morton, ur, depth);
            EXPECT_EQ(pair.second, ndsKey.toInternalString()) << "ur: " <<
                pair.second << " " << pair.first;
            ndsKey = QuadKey::getKeyFromLongitudeLatitudeAtDepth(
                Type::Morton, ul, depth);
            EXPECT_EQ(pair.second, ndsKey.toInternalString()) << "ul: " <<
                pair.second << " " << pair.first;
            GeoCoordinateBoundingBox2d actual;
            ndsKey.getGeoCoordinateBounds2d(actual);
            EXPECT_TRUE(ll.near(actual.lowerLeft(), 1)) <<
                "actual = " << actual.lowerLeft() << std::endl <<
                "ll     = " << ll;
            EXPECT_TRUE(ur.near(actual.upperRight(), 1)) <<
                "actual = " << actual.upperRight() << std::endl <<
                "ur     = " << ur;
        }
    }

    TEST(NDSSYSTEM, GetKeysFromLongitudeLatitudeBoundingBox)
    {
        for (const auto &data : {
            std::make_pair<GeoCoordinateBoundingBox2d, std::vector<QuadKey>>(
                GeoCoordinateBoundingBox2d(
                    GeoCoordinate2d(Longitude(-180.0), Latitude(- 90.0)),
                    GeoCoordinate2d(Longitude(-  0.1), Latitude(+ 90.0))),
                {
                    QuadKey(Type::Morton, 0, 0, 0)
                }),
            std::make_pair<GeoCoordinateBoundingBox2d, std::vector<QuadKey>>(
                GeoCoordinateBoundingBox2d(
                    GeoCoordinate2d(Longitude(+  0.0), Latitude(- 90.0)),
                    GeoCoordinate2d(Longitude(+180.0), Latitude(+ 90.0))),
                {
                    QuadKey(Type::Morton, 0, 1, 0)
                }),
            }) {
            std::vector<QuadKey> expected;
            expected = QuadKey::getKeysFromLongitudeLatitudeBoundingBox(Type::Morton,
                data.first, 0);
            EXPECT_EQ(data.second.size(), expected.size());
            for (const QuadKey &quadKey : data.second) {
                EXPECT_NE(std::find(data.second.begin(), data.second.end(), quadKey),
                    data.second.end());
            }
        }
        for (const auto &data : {
            std::make_pair<GeoCoordinateBoundingBox2d, std::vector<QuadKey>>(
                GeoCoordinateBoundingBox2d(
                    GeoCoordinate2d(Longitude(-180.0), Latitude(- 90.0)),
                    GeoCoordinate2d(Longitude(-  0.1), Latitude(+ 90.0))),
                {
                    QuadKey(Type::Morton, 0, 0, 1), QuadKey(Type::Morton, 0, 1, 1),
                    QuadKey(Type::Morton, 1, 0, 1), QuadKey(Type::Morton, 1, 1, 1)
                }),
            std::make_pair<GeoCoordinateBoundingBox2d, std::vector<QuadKey>>(
                GeoCoordinateBoundingBox2d(
                    GeoCoordinate2d(Longitude(+  0.0), Latitude(- 90.0)),
                    GeoCoordinate2d(Longitude(+180.0), Latitude(+ 90.0))),
                {
                    QuadKey(Type::Morton, 0, 2, 1), QuadKey(Type::Morton, 0, 3, 1),
                    QuadKey(Type::Morton, 1, 2, 1), QuadKey(Type::Morton, 1, 3, 1),
                }),
            std::make_pair<GeoCoordinateBoundingBox2d, std::vector<QuadKey>>(
                GeoCoordinateBoundingBox2d(
                    GeoCoordinate2d(Longitude(-180.0), Latitude(- 90.0)),
                    GeoCoordinate2d(Longitude(-  0.1), Latitude(-  0.1))),
                {
                    QuadKey(Type::Morton, 0, 0, 1), QuadKey(Type::Morton, 0, 1, 1),
                }),
            std::make_pair<GeoCoordinateBoundingBox2d, std::vector<QuadKey>>(
                GeoCoordinateBoundingBox2d(
                    GeoCoordinate2d(Longitude(-180.0), Latitude(+  0.0)),
                    GeoCoordinate2d(Longitude(-  0.1), Latitude(+ 90.0))),
                {
                    QuadKey(Type::Morton, 1, 0, 1), QuadKey(Type::Morton, 1, 1, 1),
                }),
            std::make_pair<GeoCoordinateBoundingBox2d, std::vector<QuadKey>>(
                GeoCoordinateBoundingBox2d(
                    GeoCoordinate2d(Longitude(+  0.0), Latitude(- 90.0)),
                    GeoCoordinate2d(Longitude(+180.0), Latitude(-  0.1))),
                {
                    QuadKey(Type::Morton, 0, 2, 1), QuadKey(Type::Morton, 0, 3, 1),
                }),
            std::make_pair<GeoCoordinateBoundingBox2d, std::vector<QuadKey>>(
                GeoCoordinateBoundingBox2d(
                    GeoCoordinate2d(Longitude(+  0.0), Latitude(+  0.0)),
                    GeoCoordinate2d(Longitude(+180.0), Latitude(+ 90.0))),
                {
                    QuadKey(Type::Morton, 1, 2, 1), QuadKey(Type::Morton, 1, 3, 1),
                }),
            std::make_pair<GeoCoordinateBoundingBox2d, std::vector<QuadKey>>(
                GeoCoordinateBoundingBox2d(
                    GeoCoordinate2d(Longitude(-180.0), Latitude(- 90.0)),
                    GeoCoordinate2d(Longitude(- 90.1), Latitude(-  0.1))),
                {
                    QuadKey(Type::Morton, 0, 0, 1),
                }),
            std::make_pair<GeoCoordinateBoundingBox2d, std::vector<QuadKey>>(
                GeoCoordinateBoundingBox2d(
                    GeoCoordinate2d(Longitude(- 90.0), Latitude(- 90.0)),
                    GeoCoordinate2d(Longitude(-  0.1), Latitude(-  0.1))),
                {
                    QuadKey(Type::Morton, 0, 0, 1),
                }),
            std::make_pair<GeoCoordinateBoundingBox2d, std::vector<QuadKey>>(
                GeoCoordinateBoundingBox2d(
                    GeoCoordinate2d(Longitude(+  0.0), Latitude(- 90.0)),
                    GeoCoordinate2d(Longitude(+ 90.0), Latitude(-  0.1))),
                {
                    QuadKey(Type::Morton, 0, 2, 1),
                }),
            std::make_pair<GeoCoordinateBoundingBox2d, std::vector<QuadKey>>(
                GeoCoordinateBoundingBox2d(
                    GeoCoordinate2d(Longitude(+ 90.1), Latitude(- 90.0)),
                    GeoCoordinate2d(Longitude(+180.0), Latitude(-  0.1))),
                {
                    QuadKey(Type::Morton, 0, 3, 1),
                }),
            std::make_pair<GeoCoordinateBoundingBox2d, std::vector<QuadKey>>(
                GeoCoordinateBoundingBox2d(
                    GeoCoordinate2d(Longitude(-180.0), Latitude(+  0.0)),
                    GeoCoordinate2d(Longitude(- 90.1), Latitude(+ 90.0))),
                {
                    QuadKey(Type::Morton, 1, 0, 1),
                }),
            std::make_pair<GeoCoordinateBoundingBox2d, std::vector<QuadKey>>(
                GeoCoordinateBoundingBox2d(
                    GeoCoordinate2d(Longitude(- 90.0), Latitude(+  0.0)),
                    GeoCoordinate2d(Longitude(-  0.1), Latitude(+ 90.0))),
                {
                    QuadKey(Type::Morton, 1, 1, 1),
                }),
            std::make_pair<GeoCoordinateBoundingBox2d, std::vector<QuadKey>>(
                GeoCoordinateBoundingBox2d(
                    GeoCoordinate2d(Longitude(+  0.0), Latitude(+  0.0)),
                    GeoCoordinate2d(Longitude(+ 90.0), Latitude(+ 90.0))),
                {
                    QuadKey(Type::Morton, 1, 2, 1),
                }),
            std::make_pair<GeoCoordinateBoundingBox2d, std::vector<QuadKey>>(
                GeoCoordinateBoundingBox2d(
                    GeoCoordinate2d(Longitude(+ 90.1), Latitude(+  0.0)),
                    GeoCoordinate2d(Longitude(+180.0), Latitude(+ 90.0))),
                {
                    QuadKey(Type::Morton, 1, 3, 1),
                }),
            }) {
            std::vector<QuadKey> expected;
            expected = QuadKey::getKeysFromLongitudeLatitudeBoundingBox(
                Type::Morton, data.first, 1);
            EXPECT_EQ(data.second.size(), expected.size());
            for (const QuadKey &quadKey : data.second) {
                EXPECT_NE(std::find(data.second.begin(), data.second.end(),
                    quadKey), data.second.end()) << quadKey;
            }
        }

        {
            auto data =
                std::make_pair<GeoCoordinateBoundingBox2d, std::vector<QuadKey>>
                    (GeoCoordinateBoundingBox2d(
                        GeoCoordinate2d(Longitude(-140.0), Latitude(- 48.0)),
                        GeoCoordinate2d(Longitude(+ 10.0), Latitude(+ 39.0))),
                {
                    QuadKey(Type::Morton, 0, 0, 2), QuadKey(Type::Morton, 0, 1, 2),
                    QuadKey(Type::Morton, 0, 2, 2), QuadKey(Type::Morton, 0, 3, 2),
                    QuadKey(Type::Morton, 0, 4, 2), QuadKey(Type::Morton, 1, 0, 2),
                    QuadKey(Type::Morton, 1, 1, 2), QuadKey(Type::Morton, 1, 2, 2),
                    QuadKey(Type::Morton, 1, 3, 2), QuadKey(Type::Morton, 1, 4, 2),
                    QuadKey(Type::Morton, 2, 0, 2), QuadKey(Type::Morton, 2, 1, 2),
                    QuadKey(Type::Morton, 2, 2, 2), QuadKey(Type::Morton, 2, 3, 2),
                    QuadKey(Type::Morton, 2, 4, 2),
                });
            std::vector<QuadKey> expected;
            expected = QuadKey::getKeysFromLongitudeLatitudeBoundingBox(
                Type::Morton, data.first, 2);
            EXPECT_EQ(data.second.size(), expected.size());
            for (const QuadKey &quadKey : data.second) {
                EXPECT_NE(std::find(data.second.begin(), data.second.end(),
                    quadKey), data.second.end()) << quadKey;
            }
        }
    }

    TEST(NDSSYSTEM, SelectedCities)
    {
        {
            auto data = std::make_pair(13, GeoCoordinate2d(
                Longitude(+  2.29450000000000),
                Latitude( + 48.85822200000000)));
            std::uint32_t tile = 8428778 | (1 << (
                static_cast<std::uint8_t>(data.first) + 16));
            std::stringstream ss;
            ss << tile;
            QuadKey ndsQuadKey = QuadKey::getKeyFromLongitudeLatitudeAtDepth(
                Type::Morton, data.second, static_cast<std::uint8_t>(data.first));
            EXPECT_EQ(ss.str(), ndsQuadKey.toInternalString());
        }
        {
            auto data = std::make_pair(13, GeoCoordinate2d(
                Longitude(- 74.04444400000000),
                Latitude( + 40.68916700000000)));
            std::uint32_t tile = 86924190 | (1 << (
                static_cast<std::uint8_t>(data.first) + 16));
            std::stringstream ss;
            ss << tile;
            QuadKey ndsQuadKey = QuadKey::getKeyFromLongitudeLatitudeAtDepth(
                Type::Morton, data.second, static_cast<std::uint8_t>(data.first));
            EXPECT_EQ(ss.str(), ndsQuadKey.toInternalString());
        }
        {
            auto data = std::make_pair(13, GeoCoordinate2d(
                Longitude(- 43.15744400000000),
                Latitude( - 22.94865800000000)));
            std::uint32_t tile = 130726287 | (1 << (
                static_cast<std::uint8_t>(data.first) + 16));
            std::stringstream ss;
            ss << tile;
            QuadKey ndsQuadKey = QuadKey::getKeyFromLongitudeLatitudeAtDepth(
                Type::Morton, data.second, static_cast<std::uint8_t>(data.first));
            EXPECT_EQ(ss.str(), ndsQuadKey.toInternalString());
        }
        {
            auto data = std::make_pair(13, GeoCoordinate2d(
                Longitude(+151.21527800000000),
                Latitude( - 33.85611100000000)));
            std::uint32_t tile = 63372939 | (1 << (
                static_cast<std::uint8_t>(data.first) + 16));
            std::stringstream ss;
            ss << tile;
            QuadKey ndsQuadKey = QuadKey::getKeyFromLongitudeLatitudeAtDepth(
                Type::Morton, data.second, static_cast<std::uint8_t>(data.first));
            EXPECT_EQ(ss.str(), ndsQuadKey.toInternalString());
        }
        {
            auto data = std::make_pair(13, GeoCoordinate2d(
                Longitude(+  0.00000000000000),
                Latitude( + 51.50300000000000)));
            std::uint32_t tile = 8521770 | (1 << (
                static_cast<std::uint8_t>(data.first) + 16));
            std::stringstream ss;
            ss << tile;
            QuadKey ndsQuadKey = QuadKey::getKeyFromLongitudeLatitudeAtDepth(
                Type::Morton, data.second, static_cast<std::uint8_t>(data.first));
            EXPECT_EQ(ss.str(), ndsQuadKey.toInternalString());
        }
        {
            auto data = std::make_pair(13, GeoCoordinate2d(
                Longitude(- 78.45000000000000),
                Latitude( +  0.00000000000000)));
            std::uint32_t tile = 84148305 | (1 << (
                static_cast<std::uint8_t>(data.first) + 16));
            std::stringstream ss;
            ss << tile;
            QuadKey ndsQuadKey = QuadKey::getKeyFromLongitudeLatitudeAtDepth(
                Type::Morton, data.second, static_cast<std::uint8_t>(data.first));
            EXPECT_EQ(ss.str(), ndsQuadKey.toInternalString());
        }
        {
            auto data = std::make_pair(10, GeoCoordinate2d(
                Longitude(+  2.29450000000000),
                Latitude( + 48.85822200000000)));
            std::uint32_t tile = 131699u | (1 << (16 +
                static_cast<std::uint8_t>(data.first)));
            std::stringstream ss;
            ss << tile;
            QuadKey ndsQuadKey = QuadKey::getKeyFromLongitudeLatitudeAtDepth(
                Type::Morton, data.second, static_cast<std::uint8_t>(data.first));
            EXPECT_EQ(ss.str(), ndsQuadKey.toInternalString());
        }
        {
            auto data = std::make_pair(10, GeoCoordinate2d(
                Longitude(- 74.04444400000000),
                Latitude( + 40.68916700000000)));
            std::uint32_t tile = 1358190u | (1 << (16 +
                static_cast<std::uint8_t>(data.first)));
            std::stringstream ss;
            ss << tile;
            QuadKey ndsQuadKey = QuadKey::getKeyFromLongitudeLatitudeAtDepth(
                Type::Morton, data.second, static_cast<std::uint8_t>(data.first));
            EXPECT_EQ(ss.str(), ndsQuadKey.toInternalString());
        }
        {
            auto data = std::make_pair(10, GeoCoordinate2d(
                Longitude(- 43.15744400000000),
                Latitude( - 22.94865800000000)));
            std::uint32_t tile = 2042598u | (1 << (16 +
                static_cast<std::uint8_t>(data.first)));
            std::stringstream ss;
            ss << tile;
            QuadKey ndsQuadKey = QuadKey::getKeyFromLongitudeLatitudeAtDepth(
                Type::Morton, data.second, static_cast<std::uint8_t>(data.first));
            EXPECT_EQ(ss.str(), ndsQuadKey.toInternalString());
        }
        {
            auto data = std::make_pair(10, GeoCoordinate2d(
                Longitude(+151.21527800000000),
                Latitude( - 33.85611100000000)));
            std::uint32_t tile = 990202u | (1 << (16 +
                static_cast<std::uint8_t>(data.first)));
            std::stringstream ss;
            ss << tile;
            QuadKey ndsQuadKey = QuadKey::getKeyFromLongitudeLatitudeAtDepth(
                Type::Morton, data.second, static_cast<std::uint8_t>(data.first));
            EXPECT_EQ(ss.str(), ndsQuadKey.toInternalString());
        }
        {
            auto data = std::make_pair(10, GeoCoordinate2d(
                Longitude(+  0.00000000000000),
                Latitude( + 51.50300000000000)));
            std::uint32_t tile = 133152u | (1 << (16 +
                static_cast<std::uint8_t>(data.first)));
            std::stringstream ss;
            ss << tile;
            QuadKey ndsQuadKey = QuadKey::getKeyFromLongitudeLatitudeAtDepth(
                Type::Morton, data.second, static_cast<std::uint8_t>(data.first));
            EXPECT_EQ(ss.str(), ndsQuadKey.toInternalString());
        }
        {
            auto data = std::make_pair(10, GeoCoordinate2d(
                Longitude(- 78.45000000000000),
                Latitude( +  0.00000000000000)));
            std::uint32_t tile = 1314817u | (1 << (16 +
                static_cast<std::uint8_t>(data.first)));
            std::stringstream ss;
            ss << tile;
            QuadKey ndsQuadKey = QuadKey::getKeyFromLongitudeLatitudeAtDepth(
                Type::Morton, data.second, static_cast<std::uint8_t>(data.first));
            EXPECT_EQ(ss.str(), ndsQuadKey.toInternalString());
        }
    }
}

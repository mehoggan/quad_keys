#include <gtest/gtest.h>

#include "QuadKey/GeoCoordinate2d.h"
#include "QuadKey/QuadKey.h"

#include <iostream>

namespace QuadKeys
{
    class GeoCoordinate2dTest : public ::testing::Test
    {
    protected:
        virtual void SetUp() {}
        virtual void TearDown() {}
    };

    // Tests that are agnostic of a specific system.
    TEST(QUADKEY, DefaultCtor)
    {
        QuadKey key;
        EXPECT_EQ(0u, key.getRow());
        EXPECT_EQ(0u, key.getCol());
        EXPECT_EQ(0u, key.getDepth());
        EXPECT_EQ(Type::None, key.getType());
    }

    TEST(QUADKEY, CtorOnlyType)
    {
        {
            QuadKey key(Type::Bing);
            EXPECT_EQ(0u, key.getRow());
            EXPECT_EQ(0u, key.getCol());
            EXPECT_EQ(0u, key.getDepth());
            EXPECT_EQ(Type::Bing, key.getType());
        }
        {
            QuadKey key(Type::LatLong);
            EXPECT_EQ(0u, key.getRow());
            EXPECT_EQ(0u, key.getCol());
            EXPECT_EQ(0u, key.getDepth());
            EXPECT_EQ(Type::LatLong, key.getType());
        }
        {
            QuadKey key(Type::UlpQnr);
            EXPECT_EQ(0u, key.getRow());
            EXPECT_EQ(0u, key.getCol());
            EXPECT_EQ(0u, key.getDepth());
            EXPECT_EQ(Type::UlpQnr, key.getType());
        }
        {
            QuadKey key(Type::Morton);
            EXPECT_EQ(0u, key.getRow());
            EXPECT_EQ(0u, key.getCol());
            EXPECT_EQ(0u, key.getDepth());
            EXPECT_EQ(Type::Morton, key.getType());
        }
        {
            QuadKey key(Type::None);
            EXPECT_EQ(0u, key.getRow());
            EXPECT_EQ(0u, key.getCol());
            EXPECT_EQ(0u, key.getDepth());
            EXPECT_EQ(Type::None, key.getType());
        }
        {
            QuadKey key(Type::OsGeo);
            EXPECT_EQ(0u, key.getRow());
            EXPECT_EQ(0u, key.getCol());
            EXPECT_EQ(0u, key.getDepth());
            EXPECT_EQ(Type::OsGeo, key.getType());
        }
    }

    TEST(QUADKEY, CopyCtor)
    {
        QuadKey key(Type::OsGeo);
        EXPECT_EQ(0u, key.getRow());
        EXPECT_EQ(0u, key.getCol());
        EXPECT_EQ(0u, key.getDepth());
        EXPECT_EQ(Type::OsGeo, key.getType());

        QuadKey copy(key);
        EXPECT_EQ(0u, copy.getRow());
        EXPECT_EQ(0u, copy.getCol());
        EXPECT_EQ(0u, copy.getDepth());
        EXPECT_EQ(Type::OsGeo, copy.getType());
    }

    TEST(QUADKEY, AssignmentOperator)
    {
        QuadKey key(Type::OsGeo);
        EXPECT_EQ(0u, key.getRow());
        EXPECT_EQ(0u, key.getCol());
        EXPECT_EQ(0u, key.getDepth());
        EXPECT_EQ(Type::OsGeo, key.getType());

        QuadKey copy;
        copy = key;
        EXPECT_EQ(0u, copy.getRow());
        EXPECT_EQ(0u, copy.getCol());
        EXPECT_EQ(0u, copy.getDepth());
        EXPECT_EQ(Type::OsGeo, copy.getType());
    }

    TEST(QUADKEY, isRootKey)
    {
        QuadKey key(Type::OsGeo);
        EXPECT_TRUE(key.isRootKey());
    }

    // Tests that outside of construction are agnostic of a system.
    TEST(QUADKEY, SystemSpecificCtor)
    {
        auto types = { Type::Bing, Type::LatLong, Type::UlpQnr, Type::Morton,
            Type::None, Type::OsGeo };
        for (auto type : types) {
            for (uint8_t depth = 0; depth < 10; ++depth) {
                uint32_t maxRows = QuadKey::maxRows(type, depth);
                uint32_t maxCols = QuadKey::maxCols(type, depth);

                std::string typeStr = QuadKey(type).typeAsString();

                QuadKey invalid(type, maxRows, maxCols, depth);
                EXPECT_EQ(QuadKey(), invalid) <<
                    (std::string("Failed invalid check on type ") + typeStr);
                QuadKey valid(type, maxRows - 1, maxCols - 1, depth);
                EXPECT_EQ(QuadKey(type, maxRows - 1, maxCols - 1, depth),
                    valid) << (std::string("Failed valid check on type ") +
                    typeStr);
            }
        }
    }
}

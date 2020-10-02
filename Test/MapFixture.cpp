#include "gtest/gtest.h"
#include "Map.h"

TEST(MapTest, testSize) {
    Map gameMap;
    ASSERT_EQ(sf::Vector2u(1600, 1000), gameMap.getMapSize());
}

//
// Created by Niccolo on 31/03/2021.
//

#include "gtest/gtest.h"
#include "Game.h"
#include "Entity.h"


class EntityTest: public ::testing::Test {
  Game * game;

public:
  EntityTest() {
      game = Game::instance();
      game->init();
  }
};

TEST_F(EntityTest , positionAssignement) {
    auto entity = new Entity(EntityGroup::Hero, EntityType::Hero, "Hero");
    entity->setPosition(sf::Vector2f(1,1));
    ASSERT_EQ(entity->getPosition(), sf::Vector2f(1,1));
}
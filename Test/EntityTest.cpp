//
// Created by Niccolo on 31/03/2021.
//

#include "gtest/gtest.h"
#include "Game.h"
#include "AnimationManager.h"
#include "Entity.h"
#include "Mock/MockGameConfig.h"


class EntityTest: public ::testing::Test {
private:
    Game * game;

public:
  EntityTest() {
      Game::deleteInstance();
      auto state = new GameStateMachine(State::Init);
      auto cfg   = new MockGameConfig();
      auto resm  = new ResourceManager();
      auto fact  = new Factory();
      auto scn   = new SceneManager();
      auto stats = new GameStats();
      auto score = new ScoreManager();
      game = Game::instance(state, cfg, resm, fact, scn, stats, score);
  }
};

TEST_F(EntityTest , positionAssignement) {
    auto entity = std::unique_ptr<Entity>(new Entity(EntityGroup::Hero, EntityType::Hero, "Hero"));
    entity->setPosition(sf::Vector2f(1,1));
    ASSERT_EQ(entity->getPosition(), sf::Vector2f(1,1));
}

TEST_F(EntityTest , positionUpdate) {
    dynamic_cast<MockGameConfig*>(CONFIG)->setSceneSpeed({0,0});
    auto entity = std::unique_ptr<Entity>(new Entity(EntityGroup::Hero, EntityType::Hero, "Hero"));
    entity->setPosition(sf::Vector2f(1, 1));
    entity->setSpeed({0,0});
    entity->update(1000);
    ASSERT_EQ(entity->getPosition(), sf::Vector2f(1, 1));
}

TEST_F(EntityTest , positionUpdate2) {
    dynamic_cast<MockGameConfig*>(CONFIG)->setSceneSpeed({0,0});
    auto entity = std::unique_ptr<Entity>(new Entity(EntityGroup::Hero, EntityType::Hero, "Hero"));
    entity->setPosition(sf::Vector2f(1, 1));
    entity->setSpeed({1,1});
    entity->update(1000);
    ASSERT_EQ(entity->getPosition(), sf::Vector2f(2, 2));
}

TEST_F(EntityTest , previousPosition) {
    dynamic_cast<MockGameConfig*>(CONFIG)->setSceneSpeed({0,0});
    auto entity = std::unique_ptr<Entity>(new Entity(EntityGroup::Hero, EntityType::Hero, "Hero"));
    entity->setPosition(sf::Vector2f(1, 1));
    entity->setSpeed({100,100});
    entity->update(1000);
    entity->update(1000);
    ASSERT_EQ(entity->getPrevPosition(), sf::Vector2f(101, 101));
    ASSERT_EQ(entity->getPosition(), sf::Vector2f(201,201));
}

TEST_F(EntityTest, DestroyedFlagNoTexture){
    dynamic_cast<MockGameConfig*>(CONFIG)->setSceneSpeed({0,0});
    auto entity = std::unique_ptr<Entity>(new Entity(EntityGroup::Hero, EntityType::Hero, "Hero"));
    entity->setSpeed({-1,0});
    entity->setPosition(sf::Vector2f(1, 0));
    entity->update(1000);
    ASSERT_EQ(entity->isDestroyed(), false);
    entity->update(1000);
    ASSERT_EQ(entity->isDestroyed(), true);
}

TEST_F(EntityTest, DestroyedFlag){
    dynamic_cast<MockGameConfig*>(CONFIG)->setSceneSpeed({0,0});
    auto entity = std::unique_ptr<Entity>(new Entity(EntityGroup::Hero, EntityType::Hero, "Hero"));
    dynamic_cast<MockGameConfig*>(CONFIG)->setTextureResource("Texture", "Texture.png");
    const std::list<FrameParams> frames = {
            {1, "Texture", {0,0,0,0}, {0,0}, {false, false}}
    };
    entity->addAnimation("DEFAULT", frames);
    entity->setPosition(sf::Vector2f(1, 0));
    entity->setSpeed(sf::Vector2f(-1, 0));
    entity->update(1000);
    ASSERT_EQ(entity->isDestroyed(), false);
    entity->update(1000);
    ASSERT_EQ(entity->isDestroyed(), false);
    entity->update(399*1000);
    ASSERT_EQ(entity->isDestroyed(), false);
    entity->update(1000);
    ASSERT_EQ(entity->isDestroyed(), true);
}

TEST_F(EntityTest, Bounds){
    dynamic_cast<MockGameConfig*>(CONFIG)->setSceneSpeed({100,0});
    auto entity = std::unique_ptr<Entity>(new Entity(EntityGroup::Hero, EntityType::Hero, "Hero"));
    dynamic_cast<MockGameConfig*>(CONFIG)->setTextureResource("Texture", "Texture.png");
    const std::list<FrameParams> frames = {
            {1, "Texture", {0,0,1,1}, {0,0}, {false, false}},
            {1, "Texture", {0,0,10,10}, {0,0}, {false, false}}
    };
    entity->addAnimation("DEFAULT", frames);
    entity->setPosition(sf::Vector2f(1,1));
    entity->update(10);
    ASSERT_EQ(entity->getBounds(), sf::FloatRect (0,1,1,1));
    entity->update(10);
    ASSERT_EQ(entity->getBounds(), sf::FloatRect (-1,1,10,10));
}
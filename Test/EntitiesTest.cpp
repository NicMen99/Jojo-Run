//
// Created by Niccolo on 31/03/2021.
//

#include "gtest/gtest.h"
#include "Game.h"
#include "AnimationManager.h"
#include "Entity.h"
#include "Mock/MockGameConfig.h"


class TestEntity : public Entity{
public:
    TestEntity() : Entity(EntityGroup::Hero, EntityType::Hero, "TEST") {
        const std::list<FrameParams> frames0 = {
                {1, "Texture", {0,0,0,0}, {0,0}, {false, false}},
        };
        addAnimation("ANIM0", frames0);
        const std::list<FrameParams> frames1 = {
                {1, "Texture", {0,0,50,50}, {0,0}, {false, false}},
                {1, "Texture", {50,50,20,20}, {0,0}, {false, false}}
        };
        addAnimation("ANIM1", frames1);
        const std::list<FrameParams> frames2 = {
                {1, "Texture", {0,0,33,33}, {0,0}, {false, false}},
                {1, "Texture", {0,0,66,66}, {0,0}, {false, false}},
                {1, "Texture", {0,0,99,99}, {0,0}, {false, false}}
        };
        addAnimation("ANIM2", frames2);
        setPosition(0,0);
        setSpeed({0,0});
    }
    void playAnimation(const std::string & animation) { Entity::playAnimation(animation); }
    void event(GameEvent event, Entity *collider) override {
        if(GameEvent::OutOfBound == event) { setDestroyed(); }
    }
};


class EntitiesTest: public ::testing::Test {
private:
    Game * game;

public:
  EntitiesTest() {
      Game::deleteInstance();
      auto state = new GameStateMachine(State::Init);
      auto cfg   = new MockGameConfig();
      auto resm  = new ResourceManager();
      auto fact  = new Factory();
      auto scn   = new SceneManager();
      auto stats = new GameStats();
      auto score = new ScoreManager();
      game = Game::instance(state, cfg, resm, fact, scn, stats, score);
      dynamic_cast<MockGameConfig*>(CONFIG)->setTextureResource("Texture", "Texture.png");
      dynamic_cast<MockGameConfig*>(CONFIG)->setSceneSpeed({0,0});
  }
};

TEST_F(EntitiesTest , PositionAssignement) {
    auto entity = std::unique_ptr<TestEntity>(new TestEntity());
    entity->setPosition(sf::Vector2f(1,1));
    ASSERT_EQ(entity->getPosition(), sf::Vector2f(1,1));
    entity->setPosition(sf::Vector2f(100,100));
    ASSERT_EQ(entity->getPosition(), sf::Vector2f(100,100));
}

TEST_F(EntitiesTest , PositionUpdateNoSpeed) {
    auto entity = std::unique_ptr<TestEntity>(new TestEntity());
    entity->setPosition(sf::Vector2f(1, 1));
    entity->update(1000);
    ASSERT_EQ(entity->getPosition(), sf::Vector2f(1, 1));
}

TEST_F(EntitiesTest , PositionUpdateSpeed) {
    auto entity = std::unique_ptr<TestEntity>(new TestEntity());
    entity->setPosition(sf::Vector2f(1, 1));
    entity->setSpeed({100,100});
    entity->update(1000);
    ASSERT_EQ(entity->getPosition(), sf::Vector2f(101, 101));
}

TEST_F(EntitiesTest , PreviousPosition) {
    auto entity = std::unique_ptr<TestEntity>(new TestEntity());
    entity->setPosition(sf::Vector2f(1, 1));
    entity->setSpeed({100,100});
    entity->update(1000);
    entity->update(1000);
    ASSERT_EQ(entity->getPrevPosition(), sf::Vector2f(101, 101));
    ASSERT_EQ(entity->getPosition(), sf::Vector2f(201,201));
}

TEST_F(EntitiesTest, DestroyedFlagNoAnimation){
    auto entity = std::unique_ptr<TestEntity>(new TestEntity());
    entity->setPosition(sf::Vector2f(50, 0));
    entity->setSpeed(sf::Vector2f(-50, 0));
    entity->update(1000);
    ASSERT_EQ(entity->isDestroyed(), false);
    entity->update(1000);
    ASSERT_EQ(entity->isDestroyed(), false);
    entity->update(1000);
    ASSERT_EQ(entity->isDestroyed(), false);
    entity->update(1000);
    ASSERT_EQ(entity->isDestroyed(), true);
}

TEST_F(EntitiesTest, DestroyedFlagAnimation){
    auto entity = std::unique_ptr<TestEntity>(new TestEntity());
    entity->playAnimation("ANIM1");
    entity->setPosition(sf::Vector2f(50, 0));
    entity->setSpeed(sf::Vector2f(-50, 0));
    entity->update(1000);
    ASSERT_EQ(entity->isDestroyed(), false);
    entity->setSpeed(sf::Vector2f(-30, 0));
    entity->update(1000);
    ASSERT_EQ(entity->isDestroyed(), true);
}

TEST_F(EntitiesTest, Bounds){
    auto entity = std::unique_ptr<TestEntity>(new TestEntity());
    dynamic_cast<MockGameConfig*>(CONFIG)->setSceneSpeed({100,100});

    entity->playAnimation("ANIM1");
    entity->setSpeed(200,100);
    entity->setPosition(sf::Vector2f(1,1));
    entity->update(10);
    ASSERT_EQ(entity->getBounds(), sf::FloatRect (2,1,50,50));
    entity->update(10);
    ASSERT_EQ(entity->getBounds(), sf::FloatRect (3,1,20,20));
    entity->setSpeed(300,200);
    entity->update(10);
    ASSERT_EQ(entity->getBounds(), sf::FloatRect (5,2,20,20));

    entity->playAnimation("ANIM2");
    entity->setSpeed(300,200);
    entity->setPosition(sf::Vector2f(1,1));
    entity->update(10);
    ASSERT_EQ(entity->getBounds(), sf::FloatRect (3,2,33,33));
    entity->update(10);
    ASSERT_EQ(entity->getBounds(), sf::FloatRect (5,3,66,66));
    entity->setSpeed(500,500);
    entity->update(10);
    ASSERT_EQ(entity->getBounds(), sf::FloatRect (9,7,99,99));
}

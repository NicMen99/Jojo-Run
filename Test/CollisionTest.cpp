//
// Created by Niccolo on 01/04/2021.
//

#include "gtest/gtest.h"
#include "Entity.h"
#include "Game.h"
#include "AnimationManager.h"
#include "CollisionManager.h"
#include "TestGameConfig.h"

class CollisionTest : public ::testing::Test{
private:
    Game * game;
public:
    CollisionTest(){
        Game::deleteInstance();
        auto state = new GameStateMachine(State::Init);
        auto cfg   = new TestGameConfig();
        auto resm  = new ResourceManager();
        auto fact  = new Factory();
        auto scn   = new SceneManager();
        auto stats = new GameStats();
        auto score = new ScoreManager();
        game = Game::instance(state, cfg, resm, fact, scn, stats, score);
        dynamic_cast<TestGameConfig*>(CONFIG)->setSceneSpeed({0,0});
        dynamic_cast<TestGameConfig*>(CONFIG)->setMapResource("TestPlatform", "Platform.png");
    }
};

TEST_F(CollisionTest, NoOverlap) {
    auto collision = std::unique_ptr<CollisionManager>(new CollisionManager);
    auto entity1 = std::unique_ptr<Entity>(new Entity(EntityGroup::Platform, EntityType::StonePlatform, "Test1"));
    auto entity2 = std::unique_ptr<Entity>(new Entity(EntityGroup::Platform, EntityType::StonePlatform, "Test2"));
    const std::list<FrameParams> frames = {
            {1, "TestPlatform", {0,0,10,10}, {0,0}, {false, false}}
    };
    entity1->addAnimation("DEFAULT", frames);
    entity1->setPosition(sf::Vector2f(10,10));
    entity1->setSpeed(sf::Vector2f(0,0));
    entity1->update(1000);
    entity2->addAnimation("DEFAULT", frames);
    entity2->setSpeed(sf::Vector2f(0,0));
    entity2->setPosition(sf::Vector2f(500,500));
    entity2->update(1000);

    CollisionTag tag1, tag2;
    ASSERT_EQ(collision->collisionCheck(entity1.get(),entity2.get(), tag1, tag2), false);
    ASSERT_EQ(tag1, CollisionTag::None);
    ASSERT_EQ(tag2, CollisionTag::None);
}

TEST_F(CollisionTest, AdjacentEntitiesOnX){
    auto collision = std::unique_ptr<CollisionManager>(new CollisionManager);
    auto entity1 = std::unique_ptr<Entity>(new Entity(EntityGroup::Platform, EntityType::StonePlatform, "Test1"));
    auto entity2 = std::unique_ptr<Entity>(new Entity(EntityGroup::Platform, EntityType::StonePlatform, "Test2"));
    const std::list<FrameParams> frames = {
            {1, "TestPlatform", {0,0,10,10}, {0,0}, {false, false}}
    };
    entity1->addAnimation("DEFAULT", frames);
    entity1->setPosition(sf::Vector2f(0,0));
    entity1->setSpeed(sf::Vector2f(0,0));
    entity1->update(1000);
    entity2->addAnimation("DEFAULT", frames);
    entity2->setSpeed(sf::Vector2f(0,0));
    entity2->setPosition(sf::Vector2f(10,0));
    entity2->update(1000);

    CollisionTag tag1, tag2;
    ASSERT_EQ(collision->collisionCheck(entity1.get(),entity2.get(), tag1, tag2), false);
    ASSERT_EQ(tag1, CollisionTag::None);
    ASSERT_EQ(tag2, CollisionTag::None);
}

TEST_F(CollisionTest, AdjacentEntitiesOnY){
    auto collision = std::unique_ptr<CollisionManager>(new CollisionManager);
    auto entity1 = std::unique_ptr<Entity>(new Entity(EntityGroup::Platform, EntityType::StonePlatform, "Test1"));
    auto entity2 = std::unique_ptr<Entity>(new Entity(EntityGroup::Platform, EntityType::StonePlatform, "Test2"));
    const std::list<FrameParams> frames = {
            {1, "TestPlatform", {0,0,10,10}, {0,0}, {false, false}}
    };
    entity1->addAnimation("DEFAULT", frames);
    entity1->setPosition(sf::Vector2f(0,0));
    entity1->setSpeed(sf::Vector2f(0,0));
    entity1->update(1000);
    entity2->addAnimation("DEFAULT", frames);
    entity2->setSpeed(sf::Vector2f(0,0));
    entity2->setPosition(sf::Vector2f(0,10));
    entity2->update(1000);

    CollisionTag tag1, tag2;
    ASSERT_EQ(collision->collisionCheck(entity1.get(),entity2.get(), tag1, tag2), false);
    ASSERT_EQ(tag1, CollisionTag::None);
    ASSERT_EQ(tag2, CollisionTag::None);
}

TEST_F(CollisionTest, OverlapX){
    auto collision = std::unique_ptr<CollisionManager>(new CollisionManager);
    auto entity1 = std::unique_ptr<Entity>(new Entity(EntityGroup::Platform, EntityType::StonePlatform, "Test1"));
    auto entity2 = std::unique_ptr<Entity>(new Entity(EntityGroup::Platform, EntityType::StonePlatform, "Test2"));
    const std::list<FrameParams> frames = {
            {1, "TestPlatform", {0,0,10,10}, {0,0}, {false, false}}
    };
    entity1->addAnimation("DEFAULT", frames);
    entity1->setPosition(sf::Vector2f(0,0));
    entity1->setSpeed(sf::Vector2f(0,0));
    entity1->update(1000);
    entity2->addAnimation("DEFAULT", frames);
    entity2->setSpeed(sf::Vector2f(0,0));
    entity2->setPosition(sf::Vector2f(3,0));
    entity2->update(1000);

    CollisionTag tag1, tag2;
    ASSERT_EQ(collision->collisionCheck(entity1.get(),entity2.get(), tag1, tag2), true);
    ASSERT_EQ(tag1, CollisionTag::Any);
    ASSERT_EQ(tag2, CollisionTag::Any);
}

TEST_F(CollisionTest, OverlapY){
    auto collision = std::unique_ptr<CollisionManager>(new CollisionManager);
    auto entity1 = std::unique_ptr<Entity>(new Entity(EntityGroup::Platform, EntityType::StonePlatform, "Test1"));
    auto entity2 = std::unique_ptr<Entity>(new Entity(EntityGroup::Platform, EntityType::StonePlatform, "Test2"));
    const std::list<FrameParams> frames = {
            {1, "TestPlatform", {0,0,10,10}, {0,0}, {false, false}}
    };
    entity1->addAnimation("DEFAULT", frames);
    entity1->setPosition(sf::Vector2f(0,0));
    entity1->setSpeed(sf::Vector2f(0,0));
    entity1->update(1000);
    entity2->addAnimation("DEFAULT", frames);
    entity2->setSpeed(sf::Vector2f(0,0));
    entity2->setPosition(sf::Vector2f(0,3));
    entity2->update(1000);

    CollisionTag tag1, tag2;
    ASSERT_EQ(collision->collisionCheck(entity1.get(),entity2.get(), tag1, tag2), true);
    ASSERT_EQ(tag1, CollisionTag::Any);
    ASSERT_EQ(tag2, CollisionTag::Any);
}

TEST_F(CollisionTest, OverlapXY){
    auto collision = std::unique_ptr<CollisionManager>(new CollisionManager);
    auto entity1 = std::unique_ptr<Entity>(new Entity(EntityGroup::Platform, EntityType::StonePlatform, "Test1"));
    auto entity2 = std::unique_ptr<Entity>(new Entity(EntityGroup::Platform, EntityType::StonePlatform, "Test2"));
    const std::list<FrameParams> frames = {
            {1, "TestPlatform", {0,0,10,10}, {0,0}, {false, false}}
    };
    entity1->addAnimation("DEFAULT", frames);
    entity1->setPosition(sf::Vector2f(0,0));
    entity1->setSpeed(sf::Vector2f(0,0));
    entity1->update(1000);
    entity2->addAnimation("DEFAULT", frames);
    entity2->setSpeed(sf::Vector2f(0,0));
    entity2->setPosition(sf::Vector2f(5,5));
    entity2->update(1000);

    CollisionTag tag1, tag2;
    ASSERT_EQ(collision->collisionCheck(entity1.get(),entity2.get(), tag1, tag2), true);
    ASSERT_EQ(tag1, CollisionTag::Any);
    ASSERT_EQ(tag2, CollisionTag::Any);
}

TEST_F(CollisionTest, HeroPlatformCase1){
    /*
     * Istante attuale : Top Hero sopra Top Piattaforma
     * Istante precedente : Bottom Hero sopra Top Piattaforma
     * Velocità: positiva
     *
     * Vedere "Condizione 1" nella documentazione di "CollisionManger.cpp" per più dettagli;
     */

    auto collision = std::unique_ptr<CollisionManager>(new CollisionManager);
    auto entity1 = std::unique_ptr<Entity>(new Entity(EntityGroup::Platform, EntityType::StonePlatform, "Test2"));
    auto entity2 = std::unique_ptr<Entity>(new Entity(EntityGroup::Hero, EntityType::Hero, "Test1"));
    const std::list<FrameParams> frames = {
            {1, "TestPlatform", {0,0,10,10}, {0,0}, {false, false}}
    };

    entity1->addAnimation("DEFAULT", frames);
    entity2->addAnimation("DEFAULT", frames);

    entity1->setPosition(sf::Vector2f(50,50));
    entity1->setSpeed(sf::Vector2f(0,0));
    entity1->update(1000);

    entity2->setPosition(sf::Vector2f(45,40));
    entity2->setSpeed(sf::Vector2f(5,1));
    entity2->update(1000);

    CollisionTag tag1, tag2;
    ASSERT_EQ(collision->collisionCheck(entity2.get(),entity1.get(), tag2, tag1), true);
    ASSERT_EQ(tag2, CollisionTag::Bottom);
    ASSERT_EQ(tag1, CollisionTag::Top);
}

TEST_F(CollisionTest, HeroPlatformCase2){
    /*
     * Istante attuale : Top Hero sopra Top Piattaforma
     * Istante precedente : Bottom Hero sotto Top Piattaforma
     * Velocità : positiva
     *
     * Vedere "Condizione 1" nella documentazione di "CollisionManger.cpp" per più dettagli;
     */

    auto collision = std::unique_ptr<CollisionManager>(new CollisionManager);
    auto entity1 = std::unique_ptr<Entity>(new Entity(EntityGroup::Platform, EntityType::StonePlatform, "Test2"));
    auto entity2 = std::unique_ptr<Entity>(new Entity(EntityGroup::Hero, EntityType::Hero, "Test1"));
    const std::list<FrameParams> frames = {
            {1, "TestPlatform", {0,0,10,10}, {0,0}, {false, false}}
    };

    entity1->addAnimation("DEFAULT", frames);
    entity2->addAnimation("DEFAULT", frames);

    entity1->setPosition(sf::Vector2f(50,50));
    entity1->setSpeed(sf::Vector2f(0,0));
    entity1->update(1000);

    entity2->setPosition(sf::Vector2f(35,45));
    entity2->setSpeed(sf::Vector2f(10,1));
    entity2->update(1000);

    CollisionTag tag1, tag2;
    ASSERT_EQ(collision->collisionCheck(entity2.get(),entity1.get(), tag2, tag1), false);
    ASSERT_EQ(tag2, CollisionTag::None);
    ASSERT_EQ(tag1, CollisionTag::None);
}

TEST_F(CollisionTest, HeroPlatformCase3){
    /*
     * Istante attuale : Top Hero sotto Top Piattaforma
     * Istante precedente : Top Hero sotto Bottom Piattaforma
     * Velocità : negativa
     *
     * Vedere "Condizione 2" nella documentazione di "CollisionManger.cpp" per più dettagli;
     */

    auto collision = std::unique_ptr<CollisionManager>(new CollisionManager);
    auto entity1 = std::unique_ptr<Entity>(new Entity(EntityGroup::Platform, EntityType::StonePlatform, "Test2"));
    auto entity2 = std::unique_ptr<Entity>(new Entity(EntityGroup::Hero, EntityType::Hero, "Test1"));
    const std::list<FrameParams> frames = {
            {1, "TestPlatform", {0,0,10,10}, {0,0}, {false, false}}
    };

    entity1->addAnimation("DEFAULT", frames);
    entity2->addAnimation("DEFAULT", frames);

    entity1->setPosition(sf::Vector2f(50,50));
    entity1->setSpeed(sf::Vector2f(0,0));
    entity1->update(1000);

    entity2->setPosition(sf::Vector2f(35,60));
    entity2->setSpeed(sf::Vector2f(10,-1));
    entity2->update(1000);

    CollisionTag tag1, tag2;
    ASSERT_EQ(collision->collisionCheck(entity2.get(),entity1.get(), tag2, tag1), true);
    ASSERT_EQ(tag2, CollisionTag::Top);
    ASSERT_EQ(tag1, CollisionTag::Bottom);
}

TEST_F(CollisionTest, HeroPlatformCase4){
    /*
     * Istante attuale : Top Hero sotto Top Piattaforma
     * Istante precedente : Top Hero sopra Bottom Piattaforma
     * Velocità : negativa
     *
     * Vedere "Condizione 2" nella documentazione di "CollisionManger.cpp" per più dettagli;
     */

    auto collision = std::unique_ptr<CollisionManager>(new CollisionManager);
    auto entity1 = std::unique_ptr<Entity>(new Entity(EntityGroup::Platform, EntityType::StonePlatform, "Test2"));
    auto entity2 = std::unique_ptr<Entity>(new Entity(EntityGroup::Hero, EntityType::Hero, "Test1"));
    const std::list<FrameParams> frames = {
            {1, "TestPlatform", {0,0,10,10}, {0,0}, {false, false}}
    };

    entity1->addAnimation("DEFAULT", frames);
    entity2->addAnimation("DEFAULT", frames);

    entity1->setPosition(sf::Vector2f(50,50));
    entity1->setSpeed(sf::Vector2f(0,0));
    entity1->update(1000);

    entity2->setPosition(sf::Vector2f(35,55));
    entity2->setSpeed(sf::Vector2f(10,-1));
    entity2->update(1000);

    CollisionTag tag1, tag2;
    ASSERT_EQ(collision->collisionCheck(entity2.get(),entity1.get(), tag2, tag1), false);
    ASSERT_EQ(tag2, CollisionTag::None);
    ASSERT_EQ(tag1, CollisionTag::None);
}

TEST_F(CollisionTest, SinglePixelEntities){
    auto collision = std::unique_ptr<CollisionManager>(new CollisionManager);
    auto entity1 = std::unique_ptr<Entity>(new Entity(EntityGroup::Platform, EntityType::StonePlatform, "Test1"));
    auto entity2 = std::unique_ptr<Entity>(new Entity(EntityGroup::Platform, EntityType::StonePlatform, "Test2"));
    const std::list<FrameParams> frames = {
            {1, "TestPlatform", {0,0,1,1}, {0,0}, {false, false}}
    };
    entity1->addAnimation("DEFAULT", frames);
    entity1->setPosition(sf::Vector2f(10,10));
    entity1->setSpeed(sf::Vector2f(0,0));
    entity1->update(1000);
    entity2->addAnimation("DEFAULT", frames);
    entity2->setPosition(sf::Vector2f(9.5,10));
    entity2->setSpeed(sf::Vector2f(0,0));
    entity2->update(1000);

    CollisionTag tag1, tag2;
    ASSERT_EQ(collision->collisionCheck(entity1.get(),entity2.get(), tag1, tag2), true);
    ASSERT_EQ(tag1, CollisionTag::Any);
    ASSERT_EQ(tag2, CollisionTag::Any);
}

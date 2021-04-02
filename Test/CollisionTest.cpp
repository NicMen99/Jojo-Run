//
// Created by Niccolo on 01/04/2021.
//

#include "gtest/gtest.h"
#include "Entity.h"
#include "Game.h"
#include "AnimationManager.h"
#include "GameConfig.h"
#include "CollisionManager.h"

class TestGameConfig : public GameConfig {
public:
    void setSceneSpeed(sf::Vector2f speed) {m_scene_speed = speed; }
    void setTextureResource(const std::string & name, const std::string & asset_path){
        m_asset_map.insert(std::make_pair(name, "TestAsset/" + asset_path));
    }
};

class CollisionTest : public ::testing::Test{
private:
    Game * game;
public:
    CollisionTest(){
        auto state = new GameStateMachine(State::Init);
        auto cfg   = new TestGameConfig();
        auto resm  = new ResourceManager();
        auto fact  = new Factory();
        auto scn   = new SceneManager();
        auto stats = new GameStats();
        auto score = new ScoreManager();
        game = Game::instance(state, cfg, resm, fact, scn, stats, score);
        game->init();
    }

};

TEST_F(CollisionTest, NoOverlap){
    dynamic_cast<TestGameConfig*>(CONFIG)->setSceneSpeed({0,0});

    auto collision = std::unique_ptr<CollisionManager>(new CollisionManager);
    auto entity1 = std::unique_ptr<Entity>(new Entity(EntityGroup::Map, EntityType::Platform, "Test1"));
    auto entity2 = std::unique_ptr<Entity>(new Entity(EntityGroup::Map, EntityType::Platform, "Test2"));
    dynamic_cast<TestGameConfig*>(CONFIG)->setTextureResource("Platform", "Platform.png");
    const std::list<FrameParams> frames = {
            {1, "Platform", {0,0,10,10}, {0,0}, {false, false}}
    };
    entity1->addAnimation("DEFAULT", frames);
    entity1->setPosition(sf::Vector2f(10,10));
    entity1->setSpeed(sf::Vector2f(0,0));
    entity1->update(1000);
    entity2->addAnimation("DEFAULT", frames);
    entity2->setSpeed(sf::Vector2f(0,0));
    entity2->setPosition(sf::Vector2f(500,500));
    entity2->update(1000);

    ASSERT_EQ(collision->collisionCheck(entity1.get(),entity2.get()), false);
}

TEST_F(CollisionTest, AdjacentEntitiesOnX){
    dynamic_cast<TestGameConfig*>(CONFIG)->setSceneSpeed({0,0});

    auto collision = std::unique_ptr<CollisionManager>(new CollisionManager);
    auto entity1 = std::unique_ptr<Entity>(new Entity(EntityGroup::Map, EntityType::Platform, "Test1"));
    auto entity2 = std::unique_ptr<Entity>(new Entity(EntityGroup::Map, EntityType::Platform, "Test2"));
    dynamic_cast<TestGameConfig*>(CONFIG)->setTextureResource("Platform", "Platform.png");
    const std::list<FrameParams> frames = {
            {1, "Platform", {0,0,10,10}, {0,0}, {false, false}}
    };
    entity1->addAnimation("DEFAULT", frames);
    entity1->setPosition(sf::Vector2f(0,0));
    entity1->setSpeed(sf::Vector2f(0,0));
    entity1->update(1000);
    entity2->addAnimation("DEFAULT", frames);
    entity2->setSpeed(sf::Vector2f(0,0));
    entity2->setPosition(sf::Vector2f(10,0));
    entity2->update(1000);

    ASSERT_EQ(collision->collisionCheck(entity1.get(),entity2.get()), false);}

TEST_F(CollisionTest, AdjacentEntitiesOnY){
    dynamic_cast<TestGameConfig*>(CONFIG)->setSceneSpeed({0,0});

    auto collision = std::unique_ptr<CollisionManager>(new CollisionManager);
    auto entity1 = std::unique_ptr<Entity>(new Entity(EntityGroup::Map, EntityType::Platform, "Test1"));
    auto entity2 = std::unique_ptr<Entity>(new Entity(EntityGroup::Map, EntityType::Platform, "Test2"));
    dynamic_cast<TestGameConfig*>(CONFIG)->setTextureResource("Platform", "Platform.png");
    const std::list<FrameParams> frames = {
            {1, "Platform", {0,0,10,10}, {0,0}, {false, false}}
    };
    entity1->addAnimation("DEFAULT", frames);
    entity1->setPosition(sf::Vector2f(0,0));
    entity1->setSpeed(sf::Vector2f(0,0));
    entity1->update(1000);
    entity2->addAnimation("DEFAULT", frames);
    entity2->setSpeed(sf::Vector2f(0,0));
    entity2->setPosition(sf::Vector2f(0,10));
    entity2->update(1000);

    ASSERT_EQ(collision->collisionCheck(entity1.get(),entity2.get()), false);
}

TEST_F(CollisionTest, OverlapX){
    dynamic_cast<TestGameConfig*>(CONFIG)->setSceneSpeed({0,0});

    auto collision = std::unique_ptr<CollisionManager>(new CollisionManager);
    auto entity1 = std::unique_ptr<Entity>(new Entity(EntityGroup::Map, EntityType::Platform, "Test1"));
    auto entity2 = std::unique_ptr<Entity>(new Entity(EntityGroup::Map, EntityType::Platform, "Test2"));
    dynamic_cast<TestGameConfig*>(CONFIG)->setTextureResource("Platform", "Platform.png");
    const std::list<FrameParams> frames = {
            {1, "Platform", {0,0,10,10}, {0,0}, {false, false}}
    };
    entity1->addAnimation("DEFAULT", frames);
    entity1->setPosition(sf::Vector2f(0,0));
    entity1->setSpeed(sf::Vector2f(0,0));
    entity1->update(1000);
    entity2->addAnimation("DEFAULT", frames);
    entity2->setSpeed(sf::Vector2f(0,0));
    entity2->setPosition(sf::Vector2f(3,0));
    entity2->update(1000);

    ASSERT_EQ(collision->collisionCheck(entity1.get(),entity2.get()), true);
}

TEST_F(CollisionTest, OverlapY){
    dynamic_cast<TestGameConfig*>(CONFIG)->setSceneSpeed({0,0});

    auto collision = std::unique_ptr<CollisionManager>(new CollisionManager);
    auto entity1 = std::unique_ptr<Entity>(new Entity(EntityGroup::Map, EntityType::Platform, "Test1"));
    auto entity2 = std::unique_ptr<Entity>(new Entity(EntityGroup::Map, EntityType::Platform, "Test2"));
    dynamic_cast<TestGameConfig*>(CONFIG)->setTextureResource("Platform", "Platform.png");
    const std::list<FrameParams> frames = {
            {1, "Platform", {0,0,10,10}, {0,0}, {false, false}}
    };
    entity1->addAnimation("DEFAULT", frames);
    entity1->setPosition(sf::Vector2f(0,0));
    entity1->setSpeed(sf::Vector2f(0,0));
    entity1->update(1000);
    entity2->addAnimation("DEFAULT", frames);
    entity2->setSpeed(sf::Vector2f(0,0));
    entity2->setPosition(sf::Vector2f(0,3));
    entity2->update(1000);

    ASSERT_EQ(collision->collisionCheck(entity1.get(),entity2.get()), true);
}

TEST_F(CollisionTest, OverlapXY){
    dynamic_cast<TestGameConfig*>(CONFIG)->setSceneSpeed({0,0});

    auto collision = std::unique_ptr<CollisionManager>(new CollisionManager);
    auto entity1 = std::unique_ptr<Entity>(new Entity(EntityGroup::Map, EntityType::Platform, "Test1"));
    auto entity2 = std::unique_ptr<Entity>(new Entity(EntityGroup::Map, EntityType::Platform, "Test2"));
    dynamic_cast<TestGameConfig*>(CONFIG)->setTextureResource("Platform", "Platform.png");
    const std::list<FrameParams> frames = {
            {1, "Platform", {0,0,10,10}, {0,0}, {false, false}}
    };
    entity1->addAnimation("DEFAULT", frames);
    entity1->setPosition(sf::Vector2f(0,0));
    entity1->setSpeed(sf::Vector2f(0,0));
    entity1->update(1000);
    entity2->addAnimation("DEFAULT", frames);
    entity2->setSpeed(sf::Vector2f(0,0));
    entity2->setPosition(sf::Vector2f(5,5));
    entity2->update(1000);

    ASSERT_EQ(collision->collisionCheck(entity1.get(),entity2.get()), true);
}

TEST_F(CollisionTest, HeroPlatformCase1){
    dynamic_cast<TestGameConfig*>(CONFIG)->setSceneSpeed({0,0});

    /*
     * Istante attuale : Top Hero sopra Top Piattaforma
     * Istante precedente : Bottom Hero sopra Top Piattaforma
     * Velocità: positiva
     *
     * Vedere "Condizione 1" nella documentazione di "CollisionManger.cpp" per più dettagli;
     */

    auto collision = std::unique_ptr<CollisionManager>(new CollisionManager);
    auto entity1 = std::unique_ptr<Entity>(new Entity(EntityGroup::Map, EntityType::Platform, "Test2"));
    auto entity2 = std::unique_ptr<Entity>(new Entity(EntityGroup::Hero, EntityType::Hero, "Test1"));
    dynamic_cast<TestGameConfig*>(CONFIG)->setTextureResource("Platform", "Platform.png");
    const std::list<FrameParams> frames = {
            {1, "Platform", {0,0,10,10}, {0,0}, {false, false}}
    };

    entity1->addAnimation("DEFAULT", frames);
    entity2->addAnimation("DEFAULT", frames);

    entity1->setPosition(sf::Vector2f(50,50));
    entity1->setSpeed(sf::Vector2f(0,0));
    entity1->update(1000);

    entity2->setPosition(sf::Vector2f(45,40));
    entity2->setSpeed(sf::Vector2f(5,1));
    entity2->update(1000);

    ASSERT_EQ(collision->collisionCheck(entity2.get(),entity1.get()), true);
}

TEST_F(CollisionTest, HeroPlatformCase2){
    dynamic_cast<TestGameConfig*>(CONFIG)->setSceneSpeed({0,0});

    /*
     * Istante attuale : Top Hero sopra Top Piattaforma
     * Istante precedente : Bottom Hero sotto Top Piattaforma
     * Velocità : positiva
     *
     * Vedere "Condizione 1" nella documentazione di "CollisionManger.cpp" per più dettagli;
     */

    auto collision = std::unique_ptr<CollisionManager>(new CollisionManager);
    auto entity1 = std::unique_ptr<Entity>(new Entity(EntityGroup::Map, EntityType::Platform, "Test2"));
    auto entity2 = std::unique_ptr<Entity>(new Entity(EntityGroup::Hero, EntityType::Hero, "Test1"));
    dynamic_cast<TestGameConfig*>(CONFIG)->setTextureResource("Platform", "Platform.png");
    const std::list<FrameParams> frames = {
            {1, "Platform", {0,0,10,10}, {0,0}, {false, false}}
    };

    entity1->addAnimation("DEFAULT", frames);
    entity2->addAnimation("DEFAULT", frames);

    entity1->setPosition(sf::Vector2f(50,50));
    entity1->setSpeed(sf::Vector2f(0,0));
    entity1->update(1000);

    entity2->setPosition(sf::Vector2f(35,45));
    entity2->setSpeed(sf::Vector2f(10,1));
    entity2->update(1000);

    ASSERT_EQ(collision->collisionCheck(entity2.get(),entity1.get()), false);
}

TEST_F(CollisionTest, HeroPlatformCase3){
    dynamic_cast<TestGameConfig*>(CONFIG)->setSceneSpeed({0,0});

    /*
     * Istante attuale : Top Hero sotto Top Piattaforma
     * Istante precedente : Top Hero sotto Bottom Piattaforma
     * Velocità : negativa
     *
     * Vedere "Condizione 2" nella documentazione di "CollisionManger.cpp" per più dettagli;
     */

    auto collision = std::unique_ptr<CollisionManager>(new CollisionManager);
    auto entity1 = std::unique_ptr<Entity>(new Entity(EntityGroup::Map, EntityType::Platform, "Test2"));
    auto entity2 = std::unique_ptr<Entity>(new Entity(EntityGroup::Hero, EntityType::Hero, "Test1"));
    dynamic_cast<TestGameConfig*>(CONFIG)->setTextureResource("Platform", "Platform.png");
    const std::list<FrameParams> frames = {
            {1, "Platform", {0,0,10,10}, {0,0}, {false, false}}
    };

    entity1->addAnimation("DEFAULT", frames);
    entity2->addAnimation("DEFAULT", frames);

    entity1->setPosition(sf::Vector2f(50,50));
    entity1->setSpeed(sf::Vector2f(0,0));
    entity1->update(1000);

    entity2->setPosition(sf::Vector2f(35,60));
    entity2->setSpeed(sf::Vector2f(10,-1));
    entity2->update(1000);

    ASSERT_EQ(collision->collisionCheck(entity2.get(),entity1.get()), true);
}

TEST_F(CollisionTest, HeroPlatformCase4){
    dynamic_cast<TestGameConfig*>(CONFIG)->setSceneSpeed({0,0});

    /*
     * Istante attuale : Top Hero sotto Top Piattaforma
     * Istante precedente : Top Hero sopra Bottom Piattaforma
     * Velocità : negativa
     *
     * Vedere "Condizione 2" nella documentazione di "CollisionManger.cpp" per più dettagli;
     */

    auto collision = std::unique_ptr<CollisionManager>(new CollisionManager);
    auto entity1 = std::unique_ptr<Entity>(new Entity(EntityGroup::Map, EntityType::Platform, "Test2"));
    auto entity2 = std::unique_ptr<Entity>(new Entity(EntityGroup::Hero, EntityType::Hero, "Test1"));
    dynamic_cast<TestGameConfig*>(CONFIG)->setTextureResource("Platform", "Platform.png");
    const std::list<FrameParams> frames = {
            {1, "Platform", {0,0,10,10}, {0,0}, {false, false}}
    };

    entity1->addAnimation("DEFAULT", frames);
    entity2->addAnimation("DEFAULT", frames);

    entity1->setPosition(sf::Vector2f(50,50));
    entity1->setSpeed(sf::Vector2f(0,0));
    entity1->update(1000);

    entity2->setPosition(sf::Vector2f(35,55));
    entity2->setSpeed(sf::Vector2f(10,-1));
    entity2->update(1000);

    ASSERT_EQ(collision->collisionCheck(entity2.get(),entity1.get()), false);
}

TEST_F(CollisionTest, SinglePixelEntities){
    dynamic_cast<TestGameConfig*>(CONFIG)->setSceneSpeed({0,0});

    auto collision = std::unique_ptr<CollisionManager>(new CollisionManager);
    auto entity1 = std::unique_ptr<Entity>(new Entity(EntityGroup::Map, EntityType::Platform, "Test1"));
    auto entity2 = std::unique_ptr<Entity>(new Entity(EntityGroup::Map, EntityType::Platform, "Test2"));
    dynamic_cast<TestGameConfig*>(CONFIG)->setTextureResource("Platform", "Platform.png");
    const std::list<FrameParams> frames = {
            {1, "Platform", {0,0,1,1}, {0,0}, {false, false}}
    };
    entity1->addAnimation("DEFAULT", frames);
    entity1->setPosition(sf::Vector2f(10,10));
    entity1->setSpeed(sf::Vector2f(0,0));
    entity1->update(1000);
    entity2->addAnimation("DEFAULT", frames);
    entity2->setPosition(sf::Vector2f(9.5,10));
    entity2->setSpeed(sf::Vector2f(0,0));
    entity2->update(1000);

    ASSERT_EQ(collision->collisionCheck(entity1.get(),entity2.get()), true);
}
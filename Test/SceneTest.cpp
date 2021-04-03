//
// Created by Niccolo on 01/04/2021.
//
#include "gtest/gtest.h"
#include "Game.h"
#include "Entity.h"
#include "CollisionManager.h"
#include "ScoreHUD.h"
#include "Entities/Hero.h"

class TestGameConfig : public GameConfig {
public:
    TestGameConfig() {
    }
    void clear() {
        m_asset_map.clear();
    }
    void seResource(const std::string & name, const std::string & asset_path){
        m_asset_map.insert(std::make_pair(name, "TestAsset/" + asset_path));
    }
};


class TestSceneManager : public SceneManager {
public:
    void clearAll() {
        m_collisionManager.reset();
        m_background1.clear();
        m_background2.clear();
        m_background3.clear();
        m_background4.clear();
        m_platforms.clear();
        m_obstacles.clear();
        m_enemies.clear();
        m_powerups.clear();
        m_bullets.clear();
        m_spawned_objects.clear();
        m_hero.reset();
        m_scorehud.reset();
    }
    std::unique_ptr<Entity>& get_hero() { return m_hero; }
    std::unique_ptr<Entity>& get_scorehud() { return m_scorehud; }
    std::vector<std::unique_ptr<Entity>>& get_background1() { return m_background1; }
    std::vector<std::unique_ptr<Entity>>& get_background2() { return m_background2; }
    std::vector<std::unique_ptr<Entity>>& get_background3() { return m_background3; }
    std::vector<std::unique_ptr<Entity>>& get_background4() { return m_background4; }
    std::vector<std::unique_ptr<Entity>>& get_platforms() { return m_platforms; }
    std::vector<std::unique_ptr<Entity>>& get_obstacles() { return m_obstacles; }
    std::vector<std::unique_ptr<Entity>>& get_enemies() { return m_enemies; }
    std::vector<std::unique_ptr<Entity>>& get_powerups() { return m_powerups; }
    std::vector<std::unique_ptr<Entity>>& get_bullets() { return m_bullets; }
    std::vector<std::unique_ptr<Entity>>& get_spawned_objects() { return m_spawned_objects; }
    void generateBackground() { return SceneManager::generateBackground(); }
};


class SceneTest : public ::testing::Test {
private:
    Game * game;
public:
    SceneTest() {
        Game::deleteInstance();
        auto state = new GameStateMachine(State::Init);
        auto cfg   = new TestGameConfig();
        auto resm  = new ResourceManager();
        auto fact  = new Factory();
        auto scn   = new TestSceneManager();
        auto stats = new GameStats();
        auto score = new ScoreManager();
        game = Game::instance(state, cfg, resm, fact, scn, stats, score);
        dynamic_cast<TestGameConfig*>(CONFIG)->clear();
        dynamic_cast<TestGameConfig*>(CONFIG)->seResource("playerTexture", "Platform.png");
        dynamic_cast<TestGameConfig*>(CONFIG)->seResource("blockTexture", "Platform.png");
        dynamic_cast<TestGameConfig*>(CONFIG)->seResource("BG", "Platform.png");
        dynamic_cast<TestGameConfig*>(CONFIG)->seResource("Background1", "Platform.png");
        dynamic_cast<TestGameConfig*>(CONFIG)->seResource("Foreground", "Platform.png");
        dynamic_cast<TestGameConfig*>(CONFIG)->seResource("Middle", "Platform.png");
    }
};

TEST_F(SceneTest, SceneInit) {
    auto scene = dynamic_cast<TestSceneManager*>(SCENE);
    scene->init();
    Entity * hero = scene->get_hero().get();
    Entity * score = scene->get_scorehud().get();
    ASSERT_NE(hero, nullptr);
    ASSERT_NE(score, nullptr);
    ASSERT_EQ(scene->get_background1().size(), 0);
    ASSERT_EQ(scene->get_background2().size(), 0);
    ASSERT_EQ(scene->get_background3().size(), 0);
    ASSERT_EQ(scene->get_background4().size(), 0);
    ASSERT_EQ(scene->get_platforms().size(), 0);
    ASSERT_EQ(scene->get_obstacles().size(), 0);
    ASSERT_EQ(scene->get_enemies().size(), 0);
    ASSERT_EQ(scene->get_powerups().size(), 0);
    ASSERT_EQ(scene->get_bullets().size(), 0);
    ASSERT_EQ(scene->get_spawned_objects().size(), 0);
}

TEST_F(SceneTest, SceneReInit) {
    auto scene = dynamic_cast<TestSceneManager*>(SCENE);
    scene->init();
    Entity * hero = scene->get_hero().get();
    Entity * score = scene->get_scorehud().get();
    ASSERT_NE(hero, nullptr);
    ASSERT_NE(score, nullptr);
    scene->get_background1().emplace_back(std::move(FACTORY->createBackground(EntityType::Sky)));
    scene->get_background2().emplace_back(std::move(FACTORY->createBackground(EntityType::Sky)));
    scene->get_background3().emplace_back(std::move(FACTORY->createBackground(EntityType::Sky)));
    scene->get_background4().emplace_back(std::move(FACTORY->createBackground(EntityType::Sky)));
    scene->get_platforms().emplace_back(std::move(FACTORY->createBackground(EntityType::Sky)));
    scene->get_obstacles().emplace_back(std::move(FACTORY->createBackground(EntityType::Sky)));
    scene->get_enemies().emplace_back(std::move(FACTORY->createBackground(EntityType::Sky)));
    scene->get_powerups().emplace_back(std::move(FACTORY->createBackground(EntityType::Sky)));
    scene->get_bullets().emplace_back(std::move(FACTORY->createBackground(EntityType::Sky)));
    scene->get_spawned_objects().emplace_back(std::move(FACTORY->createBackground(EntityType::Sky)));
    scene->init();
    Entity * hero1 = scene->get_hero().get();
    Entity * score1 = scene->get_scorehud().get();
    ASSERT_NE(hero1, nullptr);
    ASSERT_NE(score1, nullptr);
    ASSERT_NE(hero1, hero);
    ASSERT_NE(score1, score);
    ASSERT_EQ(scene->get_background1().size(), 0);
    ASSERT_EQ(scene->get_background2().size(), 0);
    ASSERT_EQ(scene->get_background3().size(), 0);
    ASSERT_EQ(scene->get_background4().size(), 0);
    ASSERT_EQ(scene->get_platforms().size(), 0);
    ASSERT_EQ(scene->get_obstacles().size(), 0);
    ASSERT_EQ(scene->get_enemies().size(), 0);
    ASSERT_EQ(scene->get_powerups().size(), 0);
    ASSERT_EQ(scene->get_bullets().size(), 0);
    ASSERT_EQ(scene->get_spawned_objects().size(), 0);
}

TEST_F(SceneTest, generateBackgrounds) {
    auto scene = dynamic_cast<TestSceneManager*>(SCENE);
    scene->init();
    scene->generateBackground();
    ASSERT_EQ(scene->get_background1().size(), 2);
    ASSERT_EQ(scene->get_background2().size(), 2);
    ASSERT_EQ(scene->get_background3().size(), 2);
    ASSERT_EQ(scene->get_background4().size(), 2);
    sf::FloatRect bounds = scene->get_background1().back()->getBounds();
    ASSERT_GT(bounds.left + bounds.width, CONFIG->getWindowSize().x);
    bounds = scene->get_background2().back()->getBounds();
    ASSERT_GT(bounds.left + bounds.width, CONFIG->getWindowSize().x);
    bounds = scene->get_background3().back()->getBounds();
    ASSERT_GT(bounds.left + bounds.width, CONFIG->getWindowSize().x);
    bounds = scene->get_background4().back()->getBounds();
    ASSERT_GT(bounds.left + bounds.width, CONFIG->getWindowSize().x);
}

//Generazione singoli oggetti
TEST_F(SceneTest, generateBackgrounds2){
    auto scene = dynamic_cast<TestSceneManager*>(SCENE);
    scene->init();
    scene->generateBackground();
    scene->get_background1().erase(scene->get_background1().begin());
    int count = scene->get_background1().size();
    scene->generateBackground();
    ASSERT_EQ(scene->get_background1().size(), count+1);
}
/*
//Manage Collision
TEST_F(SceneTest,){
    ASSERT_EQ(true,false);
}

//Collect spawned
TEST_F(SceneTest,){
    ASSERT_EQ(true,false);
}

//Remove Destroyed
TEST_F(SceneTest,){
    ASSERT_EQ(true,false);
}

//Creazioni singole
TEST_F(SceneTest,){
    ASSERT_EQ(true,false);
}

//Level End
TEST_F(SceneTest,){
    ASSERT_EQ(true,false);
}

//Add Spawned
TEST_F(SceneTest,){
    ASSERT_EQ(true,false);
}
TEST_F(SceneTest,){
    ASSERT_EQ(true,false);
}
TEST_F(SceneTest,){
    ASSERT_EQ(true,false);
}
*/

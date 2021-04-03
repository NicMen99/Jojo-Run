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
    }
};

TEST_F(SceneTest, SceneInit){
    auto scene = dynamic_cast<TestSceneManager*>(SCENE);
    scene->clearAll();
    ASSERT_EQ(scene->get_hero().get(), nullptr);
    ASSERT_EQ(scene->get_scorehud().get(), nullptr);
    ASSERT_EQ(scene->get_background1().size(), 0);
    scene->init();
    ASSERT_NE(scene->get_hero().get(), nullptr);
    ASSERT_NE(scene->get_scorehud().get(), nullptr);
    ASSERT_EQ(scene->get_background1().size(), 0);
}

//Distruzione
TEST_F(SceneTest,){
    ASSERT_EQ(true,false);
}

//Generazione singoli oggetti
TEST_F(SceneTest,){
    ASSERT_EQ(true,false);
}

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


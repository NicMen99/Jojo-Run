//
// Created by Niccolo on 01/04/2021.
//
#include "gtest/gtest.h"
#include "Game.h"
#include "Entity.h"
#include "CollisionManager.h"
#include "ScoreHUD.h"
#include "Entities/Hero.h"
#include "TestGameConfig.h"
#include "TestSceneManager.h"


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
        cfg->init();
    }
};

TEST_F(SceneTest, TestInit) {
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

TEST_F(SceneTest, TestReInit) {
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

TEST_F(SceneTest, TestGenerateBackgrounds) {
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

TEST_F(SceneTest, TestGenerateBackgrounds2){
    auto scene = dynamic_cast<TestSceneManager*>(SCENE);
    scene->init();
    scene->generateBackground();
    scene->get_background1().erase(scene->get_background1().begin());
    int count = scene->get_background1().size();
    scene->generateBackground();
    ASSERT_EQ(scene->get_background1().size(), count+1);
}

TEST_F(SceneTest, TestGeneratePlatforms) {
    auto scene = dynamic_cast<TestSceneManager*>(SCENE);
    scene->init();
    bool result = scene->generatePlatforms();
    auto & platforms = scene->get_platforms();
    ASSERT_TRUE(result);
    ASSERT_GT(platforms.size(), 0);
    ASSERT_EQ(scene->get_last_platform().left, 0);
    ASSERT_EQ(scene->get_last_platform().top, CONFIG->getBottomLevel());
    ASSERT_GE(scene->get_last_platform().left + scene->get_last_platform().width, CONFIG->getWindowSize().x);
    ASSERT_TRUE(scene->get_platform_space() == 150 ||
                        scene->get_platform_space() == 250 ||
                        scene->get_platform_space() == 375 ||
                        scene->get_platform_space() == 500);
    float posx = scene->get_last_platform().left;
    for(auto & platform : platforms) {
        ASSERT_EQ(platform->getPosition().x, posx);
        posx += platform->getBounds().width;
    }
}

TEST_F(SceneTest, TestGeneratePlatforms1) {
    auto scene = dynamic_cast<TestSceneManager*>(SCENE);
    scene->init();
    scene->generatePlatforms();
    for(int i=0; i<10; i++) {
        auto & platform = scene->get_platforms().back();
        platform->setPosition(CONFIG->getWindowSize().x - platform->getBounds().width - scene->get_platform_space() +1, platform->getPosition().y);
        bool result = scene->generatePlatforms();
        ASSERT_FALSE(result);
        platform->setPosition(platform->getPosition().x - 1, platform->getPosition().y);
        result = scene->generatePlatforms();
        ASSERT_TRUE(result);
        ASSERT_TRUE(scene->get_platform_space() == 150 ||
                    scene->get_platform_space() == 250 ||
                    scene->get_platform_space() == 375 ||
                    scene->get_platform_space() == 500);
        ASSERT_TRUE(scene->get_last_platform().top == CONFIG->getBottomLevel() ||
                    scene->get_last_platform().top == CONFIG->getMiddleLevel() ||
                    scene->get_last_platform().top == CONFIG->getTopLevel());
//    platform->setPosition(platform->getPosition().x - 1, platform->getPosition().y);
        result = scene->generatePlatforms();
        ASSERT_FALSE(result);
    }
}

TEST_F(SceneTest, TestGenerateEnemies) {
    auto scene = dynamic_cast<TestSceneManager*>(SCENE);
    auto & enemies = scene->get_enemies();
    scene->init();
    scene->set_platforms_count(2);
    scene->set_last_platform({100,CONFIG->getBottomLevel(),0.5f * CONFIG->getWindowSize().x,50});
    scene->generateEnemies(false);
    ASSERT_EQ(enemies.size(), 1);
    auto & enemy = enemies.back();
    sf::FloatRect enemybounds = enemy->getBounds();
    ASSERT_EQ(enemybounds.top + enemybounds.height, scene->get_last_platform().top);
    ASSERT_GT(enemybounds.left, scene->get_last_platform().left);
    ASSERT_LT(enemybounds.left + enemybounds.width, scene->get_last_platform().left + scene->get_last_platform().width);
    scene->generateEnemies(false);
    ASSERT_EQ(enemies.size(), 1);
}

TEST_F(SceneTest, TestGenerateObstacles) {
    auto scene = dynamic_cast<TestSceneManager*>(SCENE);
    auto & obstacles = scene->get_obstacles();
    scene->init();
    scene->set_platforms_count(2);
    scene->set_last_platform({100,CONFIG->getBottomLevel(),0.5f * CONFIG->getWindowSize().x,50});
    scene->generateObstacles(false);
    ASSERT_EQ(obstacles.size(), 1);
    auto & obstacle = obstacles.back();
    sf::FloatRect obstaclebounds = obstacle->getBounds();
    ASSERT_LE(obstaclebounds.top + obstaclebounds.height, scene->get_last_platform().top);
    ASSERT_GT(obstaclebounds.left, scene->get_last_platform().left);
    ASSERT_LT(obstaclebounds.left + obstaclebounds.width, scene->get_last_platform().left + scene->get_last_platform().width);
    scene->generateObstacles(false);
    ASSERT_EQ(obstacles.size(), 1);
}

TEST_F(SceneTest, TestGeneratePowerups) {
    auto scene = dynamic_cast<TestSceneManager*>(SCENE);
    auto & powerups = scene->get_powerups();
    scene->init();
    scene->set_platforms_count(2);
    scene->set_last_platform({100, CONFIG->getBottomLevel(),0.5f * CONFIG->getWindowSize().x,50});
    scene->generatePowerups(false);
    ASSERT_EQ(powerups.size(), 1);
    auto & powerup = powerups.back();
    sf::FloatRect powerupbounds = powerup->getBounds();
    ASSERT_LT(powerupbounds.top + powerupbounds.height, scene->get_last_platform().top - scene->get_hero()->getBounds().height);
    ASSERT_GT(powerupbounds.left, scene->get_last_platform().left);
    ASSERT_LT(powerupbounds.left + powerupbounds.width, scene->get_last_platform().left + scene->get_last_platform().width);
    scene->generatePowerups(false);
    ASSERT_EQ(powerups.size(), 1);
}

TEST_F(SceneTest, TestSpawned) {
    auto scene = dynamic_cast<TestSceneManager*>(SCENE);
    auto & spawned = scene->get_spawned_objects();
    scene->init();
    auto bullet = FACTORY->createBullet(EntityType::Knife);
    scene->addSpawned(bullet);
    bullet = FACTORY->createBullet(EntityType::FireBullet);
    scene->addSpawned(bullet);
    bullet = FACTORY->createBullet(EntityType::EmeraldBullet);
    scene->addSpawned(bullet);
    bullet = FACTORY->createEnemy(EntityType::FireEnemy);
    scene->addSpawned(bullet);
    ASSERT_EQ(spawned.size(), 4);
    scene->collectSpawned();
    auto & bullets = scene->get_bullets();
    ASSERT_EQ(bullets.size(), 3);
    ASSERT_EQ(spawned.size(), 0);
}

TEST_F(SceneTest, TestDestroy) {
    auto scene = dynamic_cast<TestSceneManager *>(SCENE);
    scene->init();
    scene->createEnemy(EntityType::FireEnemy, {0,0});
    scene->createEnemy(EntityType::FireEnemy, {0,0});
    scene->createObstacle(EntityType::Wall, {0,0});
    scene->createObstacle(EntityType::Wall, {0,0});
    scene->createObstacle(EntityType::Wall, {0,0});
    scene->createPowerup(EntityType::Weapon, {0,0});
    scene->createHero();
    ASSERT_EQ(scene->get_enemies().size(), 2);
    ASSERT_EQ(scene->get_obstacles().size(), 3);
    ASSERT_EQ(scene->get_powerups().size(), 1);
    ASSERT_NE(scene->get_hero().get(), nullptr);
    for(auto & enemy: scene->get_enemies()) {
        enemy->setDestroyed();
    }
    for(auto & obstacle: scene->get_obstacles()) {
        obstacle->setDestroyed();
    }
    for(auto & powerup: scene->get_powerups()) {
        powerup->setDestroyed();
    }
    scene->get_hero()->setDestroyed();
    scene->removeDestroyedObjects();
    ASSERT_EQ(scene->get_enemies().size(), 0);
    ASSERT_EQ(scene->get_obstacles().size(), 0);
    ASSERT_EQ(scene->get_powerups().size(), 0);
    ASSERT_EQ(scene->get_hero().get(), nullptr);
}

TEST_F(SceneTest, TestLevelEnd) {
    auto scene = dynamic_cast<TestSceneManager *>(SCENE);
    scene->init();
    scene->createHero();
    ASSERT_EQ(scene->levelend(), false);
    scene->get_hero()->setDestroyed();
    scene->removeDestroyedObjects();
    ASSERT_EQ(scene->levelend(), true);
}

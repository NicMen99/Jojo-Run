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
    bool generatePlatforms() { return SceneManager::generatePlatforms(); }
    bool generateEnemies(bool gen) { return SceneManager::generateEnemies(gen); }
    bool generateObstacles(bool gen) { return SceneManager::generateObstacles(gen); }
    bool generatePowerups(bool gen) { return SceneManager::generatePowerups(gen); }
    void addSpawned(std::unique_ptr<Entity> & newObject) { SceneManager::addSpawned(newObject); }
    void collectSpawned() { SceneManager::collectSpawned(); }
    void createEnemy(EntityType typ, sf::Vector2f pos) { SceneManager::createEnemy(typ, pos); }
    void createObstacle(EntityType typ, sf::Vector2f pos) { SceneManager::createObstacle(typ, pos); }
    void createPowerup(EntityType typ, sf::Vector2f pos) { SceneManager::createPowerup(typ, pos); }
    void createHero() { SceneManager::createHero(); }
    void removeDestroyedObjects() { SceneManager::removeDestroyedObjects(); }
    sf::FloatRect get_last_platform() { return m_last_platform; }
    void set_last_platform(sf::FloatRect last_platform) { m_last_platform = last_platform; }
    float get_platform_space() { return m_platform_space; }
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
        dynamic_cast<TestGameConfig*>(CONFIG)->seResource("PLATFORM", "Platform.png");
        dynamic_cast<TestGameConfig*>(CONFIG)->seResource("playerTexture", "Platform.png");

        dynamic_cast<TestGameConfig*>(CONFIG)->seResource("BG", "Background.png");
        dynamic_cast<TestGameConfig*>(CONFIG)->seResource("Background1", "Background.png");
        dynamic_cast<TestGameConfig*>(CONFIG)->seResource("Foreground", "Background.png");
        dynamic_cast<TestGameConfig*>(CONFIG)->seResource("Middle", "Background.png");

        dynamic_cast<TestGameConfig*>(CONFIG)->seResource("fireEnemyTexture", "Texture.png");
        dynamic_cast<TestGameConfig*>(CONFIG)->seResource("hamonEnemyTexture", "Texture.png");
        dynamic_cast<TestGameConfig*>(CONFIG)->seResource("emeraldEnemyTexture", "Texture.png");

        dynamic_cast<TestGameConfig*>(CONFIG)->seResource("blockTexture", "Texture.png");
        dynamic_cast<TestGameConfig*>(CONFIG)->seResource("hamonBlockTexture", "Texture.png");
        dynamic_cast<TestGameConfig*>(CONFIG)->seResource("fireBlockTexture", "Texture.png");
        dynamic_cast<TestGameConfig*>(CONFIG)->seResource("emeraldBlockTexture", "Texture.png");

        dynamic_cast<TestGameConfig*>(CONFIG)->seResource("fireWallTexture", "Texture.png");
        dynamic_cast<TestGameConfig*>(CONFIG)->seResource("shieldPowerUpTexture", "Texture.png");
        dynamic_cast<TestGameConfig*>(CONFIG)->seResource("knifeTexture", "Texture.png");
        dynamic_cast<TestGameConfig*>(CONFIG)->seResource("Fire", "Texture.png");
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
    ASSERT_LE(scene->get_last_platform().left + scene->get_last_platform().width, CONFIG->getWindowSize().x);
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

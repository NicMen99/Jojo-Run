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

/* General */

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

/* Hero */

TEST_F(EntitiesTest, HeroCreation) {
    auto hero = FACTORY->createHero();
    ASSERT_EQ(hero->getGroup(), EntityGroup::Hero);
    ASSERT_EQ(hero->getType(), EntityType::Hero);
    ASSERT_EQ(hero->isStarted(), false);
    ASSERT_EQ(hero->isDestroyed(), false);
    ASSERT_EQ(hero->isEnabled(), true);
    ASSERT_EQ(hero->isVisible(), true);
}

TEST_F(EntitiesTest, HeroFirstUpdate) {
    dynamic_cast<MockGameConfig*>(CONFIG)->setGravity({0,1000});
    auto hero = FACTORY->createHero();
    float base = CONFIG->getBottomLevel();
    hero->setPosition(100, base);
    hero->update(100);
    ASSERT_EQ(hero->getSpeed(), sf::Vector2f(0, 100));
    ASSERT_EQ(hero->getPosition(), sf::Vector2f(100, base+10));
    ASSERT_TRUE(hero->isStarted());
}

TEST_F(EntitiesTest, HeroGravity) {
    dynamic_cast<MockGameConfig*>(CONFIG)->setGravity({0,1000});
    auto hero = FACTORY->createHero();
    float posx = CONFIG->getHeroPosX();
    float posy = CONFIG->getBottomLevel();
    hero->setPosition(posx, posx);
    hero->update(100);
    ASSERT_EQ(hero->getSpeed(), sf::Vector2f(0, 100));
    ASSERT_EQ(hero->getPosition(), sf::Vector2f(posx, posx + 10));
    hero->update(500);
    ASSERT_EQ(hero->getSpeed(), sf::Vector2f(0, 600));
    ASSERT_EQ(hero->getPosition(), sf::Vector2f(posx, posx + 10 + 300));
    hero->update(1000);
    ASSERT_EQ(hero->getSpeed(), sf::Vector2f(0, 1500));
    ASSERT_EQ(hero->getPosition(), sf::Vector2f(posx, posx + 10 + 300 + 1500));
}

TEST_F(EntitiesTest, HeroFallDown) {
    dynamic_cast<MockGameConfig*>(CONFIG)->setGravity({0,1000});
    auto hero = FACTORY->createHero();
    float posx = CONFIG->getHeroPosX();
    float posy = CONFIG->getBottomLevel();
    hero->setPosition(posx, posx);
    while(posy<CONFIG->getHeroMaxPosY()) {
        ASSERT_FALSE(hero->isDestroyed());
        hero->update(100);
        posy = hero->getPosition().y;
    }
    hero->update(100);
    ASSERT_TRUE(hero->isDestroyed());
}

TEST_F(EntitiesTest, HeroEnemyCollision) {
    dynamic_cast<MockGameConfig*>(CONFIG)->setGravity({0, 0});
    auto hero = FACTORY->createHero();
    float posx = CONFIG->getHeroPosX();
    float posy = CONFIG->getBottomLevel();
    hero->setPosition(posx, posx);
    hero->setSpeed(0,0);
    hero->update(100);
    auto enemy = FACTORY->createEnemy(EntityType::EmeraldEnemy);
    enemy->setPosition(posx + hero->getBounds().width - 1, posy);
    enemy->update(100);
    int health = STATS->getInt(Stats::Health);
    ASSERT_EQ(health, CONFIG->getHeroMaxHealth());
    while(health > 0) {
        ASSERT_EQ(hero->isEnabled(), true);
        hero->event(GameEvent::Collision, enemy.get());
        health -= enemy->getDamage();
        if(health<0) health =0;
        ASSERT_EQ(STATS->getInt(Stats::Health), health);
    }
    ASSERT_EQ(hero->isEnabled(), false);
}

TEST_F(EntitiesTest, HeroObstacleCollision) {
    dynamic_cast<MockGameConfig*>(CONFIG)->setGravity({0, 0});
    auto hero = FACTORY->createHero();
    float posx = CONFIG->getHeroPosX();
    float posy = CONFIG->getBottomLevel();
    hero->setPosition(posx, posx);
    hero->setSpeed(0,0);
    hero->update(100);
    auto obstacle = FACTORY->createObstacle(EntityType::Block);
    obstacle->setPosition(posx + hero->getBounds().width - 1, posy);
    obstacle->update(100);
    int health = STATS->getInt(Stats::Health);
    ASSERT_EQ(health, CONFIG->getHeroMaxHealth());
    hero->event(GameEvent::Collision, obstacle.get());
    health -= obstacle->getDamage();
    ASSERT_EQ(STATS->getInt(Stats::Health), health);
}

TEST_F(EntitiesTest, HeroBulletCollision) {
    dynamic_cast<MockGameConfig*>(CONFIG)->setGravity({0, 0});
    auto hero = FACTORY->createHero();
    float posx = CONFIG->getHeroPosX();
    float posy = CONFIG->getBottomLevel();
    hero->setPosition(posx, posx);
    hero->setSpeed(0,0);
    hero->update(100);
    auto bullet = FACTORY->createBullet(EntityType::FireBullet);
    bullet->setPosition(posx + hero->getBounds().width - 1, posy);
    bullet->update(100);
    int health = STATS->getInt(Stats::Health);
    ASSERT_EQ(health, CONFIG->getHeroMaxHealth());
    hero->event(GameEvent::Collision, bullet.get());
    health -= bullet->getDamage();
    ASSERT_EQ(STATS->getInt(Stats::Health), health);
}

TEST_F(EntitiesTest, HeroPowerupCollision) {
    dynamic_cast<MockGameConfig*>(CONFIG)->setGravity({0, 0});
    auto hero = FACTORY->createHero();
    float posx = CONFIG->getHeroPosX();
    float posy = CONFIG->getBottomLevel();
    hero->setPosition(posx, posx);
    hero->setSpeed(0,0);
    hero->update(100);
    auto powerup = FACTORY->createPowerUp(EntityType::Weapon);
    powerup->setPosition(posx + hero->getBounds().width - 1, posy);
    powerup->update(100);
    int knives = STATS->getInt(Stats::Knives);
    ASSERT_EQ(knives, 2);
    hero->event(GameEvent::Collection, powerup.get());
    knives += powerup->getGain();
    ASSERT_EQ(STATS->getInt(Stats::Knives), knives);
}

TEST_F(EntitiesTest, HeroPlatformCollision1) {
    dynamic_cast<MockGameConfig*>(CONFIG)->setGravity({0, 0});
    auto hero = FACTORY->createHero();
    float posx = CONFIG->getHeroPosX();
    float posy = CONFIG->getBottomLevel() - hero->getBounds().height;
    hero->setPosition(posx, posx);
    hero->setSpeed(0,0);
    hero->update(100);
    auto platform = FACTORY->createPlatform(EntityType::StonePlatform);
    platform->setPosition(0, posy + hero->getBounds().height - 5);
    platform->update(100);
    hero->event(GameEvent::CollisionBottom, platform.get());
    sf::Vector2f pos = hero->getPosition();
    ASSERT_EQ(pos, sf::Vector2f(posx, posy-5));
}

TEST_F(EntitiesTest, HeroPlatformCollision2) {
    dynamic_cast<MockGameConfig*>(CONFIG)->setGravity({0, 0});
    auto platform = FACTORY->createPlatform(EntityType::StonePlatform);
    platform->setPosition(0, CONFIG->getMiddleLevel());
    platform->update(100);
    auto hero = FACTORY->createHero();
    float posx = CONFIG->getHeroPosX();
    float posy = CONFIG->getMiddleLevel() + platform->getBounds().height -5;
    hero->setPosition(posx, posx);
    hero->update(100);
    hero->setSpeed(0, -20);
    hero->event(GameEvent::CollisionTop, platform.get());
    sf::Vector2f pos = hero->getPosition();
    ASSERT_EQ(pos, sf::Vector2f(posx, posy+5));
    sf::Vector2f speed = hero->getSpeed();
    ASSERT_EQ(speed, sf::Vector2f(0, 0));
}

/* Enemies */

TEST_F(EntitiesTest, EmeraldEnemyCreation) {
    auto enemy = FACTORY->createEnemy(EntityType::EmeraldEnemy);
    ASSERT_EQ(enemy->getGroup(), EntityGroup::Enemy);
    ASSERT_EQ(enemy->getType(), EntityType::EmeraldEnemy);
    ASSERT_EQ(enemy->isStarted(), false);
    ASSERT_EQ(enemy->isDestroyed(), false);
    ASSERT_EQ(enemy->isEnabled(), true);
    ASSERT_EQ(enemy->isVisible(), true);
}

TEST_F(EntitiesTest, HamonEnemyCreation) {
    auto enemy = FACTORY->createEnemy(EntityType::HamonEnemy);
    ASSERT_EQ(enemy->getGroup(), EntityGroup::Enemy);
    ASSERT_EQ(enemy->getType(), EntityType::HamonEnemy);
    ASSERT_EQ(enemy->isStarted(), false);
    ASSERT_EQ(enemy->isDestroyed(), false);
    ASSERT_EQ(enemy->isEnabled(), true);
    ASSERT_EQ(enemy->isVisible(), true);
}

TEST_F(EntitiesTest, FireEnemyCreation) {
    auto enemy = FACTORY->createEnemy(EntityType::FireEnemy);
    ASSERT_EQ(enemy->getGroup(), EntityGroup::Enemy);
    ASSERT_EQ(enemy->getType(), EntityType::FireEnemy);
    ASSERT_EQ(enemy->isStarted(), false);
    ASSERT_EQ(enemy->isDestroyed(), false);
    ASSERT_EQ(enemy->isEnabled(), true);
    ASSERT_EQ(enemy->isVisible(), true);
}

TEST_F(EntitiesTest, EnemyFallDown) {
    dynamic_cast<MockGameConfig*>(CONFIG)->setGravity({0,1000});
    auto enemy = FACTORY->createEnemy(EntityType::FireEnemy);
    float posx = 500;
    float posy = CONFIG->getBottomLevel();
    enemy->setPosition(posx, posx);
    while(posy<CONFIG->getWindowSize().y) {
        ASSERT_FALSE(enemy->isDestroyed());
        enemy->update(100);
        posy = enemy->getPosition().y;
    }
    enemy->update(100);
    ASSERT_TRUE(enemy->isDestroyed());
}

TEST_F(EntitiesTest, EnemyPlatformCollision1) {
    dynamic_cast<MockGameConfig*>(CONFIG)->setGravity({0, 0});
    auto enemy = FACTORY->createEnemy(EntityType::HamonEnemy);
    float posx = CONFIG->getHeroPosX();
    float posy = CONFIG->getBottomLevel() - enemy->getBounds().height;
    enemy->setPosition(posx, posx);
    enemy->setSpeed(0,0);
    enemy->update(100);
    auto platform = FACTORY->createPlatform(EntityType::StonePlatform);
    platform->setPosition(0, posy + enemy->getBounds().height - 5);
    platform->update(100);
    enemy->event(GameEvent::CollisionBottom, platform.get());
    sf::Vector2f pos = enemy->getPosition();
    ASSERT_EQ(pos, sf::Vector2f(posx, posy-5));
}

TEST_F(EntitiesTest, EnemyBulletCollision) {
    dynamic_cast<MockGameConfig*>(CONFIG)->setGravity({0, 0});
    auto enemy = FACTORY->createEnemy(EntityType::EmeraldEnemy);
    float posx = CONFIG->getHeroPosX();
    float posy = CONFIG->getBottomLevel();
    enemy->setPosition(posx, posx);
    enemy->setSpeed(0,0);
    enemy->update(100);
    auto bullet = FACTORY->createBullet(EntityType::Knife);
    bullet->setPosition(posx + enemy->getBounds().width - 1, posy);
    bullet->update(100);
    enemy->event(GameEvent::Collision, bullet.get());
    ASSERT_FALSE(enemy->isEnabled());
}

TEST_F(EntitiesTest, EnemyHeroCollision) {
    dynamic_cast<MockGameConfig*>(CONFIG)->setGravity({0, 0});
    auto hero = FACTORY->createHero();
    float posx = CONFIG->getHeroPosX();
    float posy = CONFIG->getBottomLevel();
    hero->setPosition(posx, posx);
    hero->setSpeed(0,0);
    hero->update(100);
    auto enemy = FACTORY->createEnemy(EntityType::EmeraldEnemy);
    enemy->setPosition(posx + hero->getBounds().width - 1, posy);
    enemy->update(100);
    ASSERT_EQ(enemy->isEnabled(), true);
    enemy->event(GameEvent::Collision, hero.get());
    ASSERT_EQ(enemy->isEnabled(), false);
}

/* Bullets */

TEST_F(EntitiesTest, FireBulletCreation) {
    auto bullet = FACTORY->createBullet(EntityType::FireBullet);
    ASSERT_EQ(bullet->getGroup(), EntityGroup::Bullet);
    ASSERT_EQ(bullet->getType(), EntityType::FireBullet);
    ASSERT_EQ(bullet->isStarted(), false);
    ASSERT_EQ(bullet->isDestroyed(), false);
    ASSERT_EQ(bullet->isEnabled(), true);
    ASSERT_EQ(bullet->isVisible(), true);
}

TEST_F(EntitiesTest, EmeraldBulletCreation) {
    auto bullet = FACTORY->createBullet(EntityType::EmeraldBullet);
    ASSERT_EQ(bullet->getGroup(), EntityGroup::Bullet);
    ASSERT_EQ(bullet->getType(), EntityType::EmeraldBullet);
    ASSERT_EQ(bullet->isStarted(), false);
    ASSERT_EQ(bullet->isDestroyed(), false);
    ASSERT_EQ(bullet->isEnabled(), true);
    ASSERT_EQ(bullet->isVisible(), true);
}

TEST_F(EntitiesTest, KnifeCreation) {
    auto bullet = FACTORY->createBullet(EntityType::Knife);
    ASSERT_EQ(bullet->getGroup(), EntityGroup::Bullet);
    ASSERT_EQ(bullet->getType(), EntityType::Knife);
    ASSERT_EQ(bullet->isStarted(), false);
    ASSERT_EQ(bullet->isDestroyed(), false);
    ASSERT_EQ(bullet->isEnabled(), true);
    ASSERT_EQ(bullet->isVisible(), true);
}

TEST_F(EntitiesTest, BulletHeroCollision) {
    dynamic_cast<MockGameConfig*>(CONFIG)->setGravity({0, 0});
    auto hero = FACTORY->createHero();
    float posx = CONFIG->getHeroPosX();
    float posy = CONFIG->getBottomLevel();
    hero->setPosition(posx, posx);
    hero->setSpeed(0,0);
    hero->update(100);
    auto bullet = FACTORY->createBullet(EntityType::FireBullet);
    bullet->setPosition(posx + hero->getBounds().width - 1, posy);
    bullet->update(100);
    bullet->event(GameEvent::Collision, hero.get());
    ASSERT_EQ(bullet->isDestroyed(), true);
}

/* Obstacles */

TEST_F(EntitiesTest, BlockCreation) {
    auto obstacle = FACTORY->createObstacle(EntityType::Block);
    ASSERT_EQ(obstacle->getGroup(), EntityGroup::Obstacle);
    ASSERT_EQ(obstacle->getType(), EntityType::Block);
    ASSERT_EQ(obstacle->isStarted(), false);
    ASSERT_EQ(obstacle->isDestroyed(), false);
    ASSERT_EQ(obstacle->isEnabled(), true);
    ASSERT_EQ(obstacle->isVisible(), true);
}

TEST_F(EntitiesTest, WallCreation) {
    auto obstacle = FACTORY->createObstacle(EntityType::Wall);
    ASSERT_EQ(obstacle->getGroup(), EntityGroup::Obstacle);
    ASSERT_EQ(obstacle->getType(), EntityType::Wall);
    ASSERT_EQ(obstacle->isStarted(), false);
    ASSERT_EQ(obstacle->isDestroyed(), false);
    ASSERT_EQ(obstacle->isEnabled(), true);
    ASSERT_EQ(obstacle->isVisible(), true);
}

/* Powerups */

TEST_F(EntitiesTest, WeaponCreation) {
    auto powerup = FACTORY->createPowerUp(EntityType::Weapon);
    ASSERT_EQ(powerup->getGroup(), EntityGroup::Powerup);
    ASSERT_EQ(powerup->getType(), EntityType::Weapon);
    ASSERT_EQ(powerup->isStarted(), false);
    ASSERT_EQ(powerup->isDestroyed(), false);
    ASSERT_EQ(powerup->isEnabled(), true);
    ASSERT_EQ(powerup->isVisible(), true);
}

TEST_F(EntitiesTest, ShieldCreation) {
    auto powerup = FACTORY->createPowerUp(EntityType::Shield);
    ASSERT_EQ(powerup->getGroup(), EntityGroup::Powerup);
    ASSERT_EQ(powerup->getType(), EntityType::Shield);
    ASSERT_EQ(powerup->isStarted(), false);
    ASSERT_EQ(powerup->isDestroyed(), false);
    ASSERT_EQ(powerup->isEnabled(), true);
    ASSERT_EQ(powerup->isVisible(), true);
}

TEST_F(EntitiesTest, PowerupHeroCollision) {
    dynamic_cast<MockGameConfig*>(CONFIG)->setGravity({0, 0});
    auto hero = FACTORY->createHero();
    float posx = CONFIG->getHeroPosX();
    float posy = CONFIG->getBottomLevel();
    hero->setPosition(posx, posx);
    hero->setSpeed(0,0);
    hero->update(100);
    auto powerup = FACTORY->createPowerUp(EntityType::Weapon);
    powerup->setPosition(posx + hero->getBounds().width - 1, posy);
    powerup->update(100);
    powerup->event(GameEvent::Collection, hero.get());
    ASSERT_EQ(powerup->isDestroyed(), true);
}


/* Maps */

TEST_F(EntitiesTest, PlatformCreation) {
    auto platform = FACTORY->createPlatform(EntityType::StonePlatform);
    ASSERT_EQ(platform->getGroup(), EntityGroup::Platform);
    ASSERT_EQ(platform->getType(), EntityType::Platform);
    ASSERT_EQ(platform->isStarted(), false);
    ASSERT_EQ(platform->isDestroyed(), false);
    ASSERT_EQ(platform->isEnabled(), true);
    ASSERT_EQ(platform->isVisible(), true);
}

TEST_F(EntitiesTest, BackgroundCreation1) {
    auto background = FACTORY->createBackground(EntityType::Bridge);
    ASSERT_EQ(background->getGroup(), EntityGroup::Scene);
    ASSERT_EQ(background->getType(), EntityType::Background);
    ASSERT_EQ(background->isStarted(), false);
    ASSERT_EQ(background->isDestroyed(), false);
    ASSERT_EQ(background->isEnabled(), true);
    ASSERT_EQ(background->isVisible(), true);
}

TEST_F(EntitiesTest, BackgroundCreation2) {
    auto background = FACTORY->createBackground(EntityType::City);
    ASSERT_EQ(background->getGroup(), EntityGroup::Scene);
    ASSERT_EQ(background->getType(), EntityType::Background);
    ASSERT_EQ(background->isStarted(), false);
    ASSERT_EQ(background->isDestroyed(), false);
    ASSERT_EQ(background->isEnabled(), true);
    ASSERT_EQ(background->isVisible(), true);
}

TEST_F(EntitiesTest, BackgroundCreation3) {
    auto background = FACTORY->createBackground(EntityType::Sky);
    ASSERT_EQ(background->getGroup(), EntityGroup::Scene);
    ASSERT_EQ(background->getType(), EntityType::Background);
    ASSERT_EQ(background->isStarted(), false);
    ASSERT_EQ(background->isDestroyed(), false);
    ASSERT_EQ(background->isEnabled(), true);
    ASSERT_EQ(background->isVisible(), true);
}

TEST_F(EntitiesTest, BackgroundCreation4) {
    auto background = FACTORY->createBackground(EntityType::SkyScrapers);
    ASSERT_EQ(background->getGroup(), EntityGroup::Scene);
    ASSERT_EQ(background->getType(), EntityType::Background);
    ASSERT_EQ(background->isStarted(), false);
    ASSERT_EQ(background->isDestroyed(), false);
    ASSERT_EQ(background->isEnabled(), true);
    ASSERT_EQ(background->isVisible(), true);
}

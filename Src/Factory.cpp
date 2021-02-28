//
// Created by angiolo99 on 23/01/20.
//

#include "Block.h"
#include "FireWall.h"
#include "EmeraldEnemy.h"
#include "FireEnemy.h"
#include "HamonEnemy.h"
#include "Shield.h"
#include "Weapon.h"
#include "Knife.h"
#include "platform.h"

#include "Factory.h"

std::unique_ptr<Obstacle> Factory::createObstacle(ObstacleType type) {
    if(type == ObstacleType::Block) {
        std::unique_ptr<Obstacle> obstacle = std::unique_ptr<Obstacle>(new Block("Block"));
        obstacle->init("blockTexture", {0.70, 0.70}, /*{0, 0},*/ 70);
        return obstacle;
    }
    else if (type == ObstacleType::Firewall) {
        std::unique_ptr<Obstacle> obstacle = std::unique_ptr<Obstacle>(new FireWall(""));
        obstacle->init("fireWallTexture", {1, 1}, /*{0,0}*/ 15);
        return obstacle;
    }
    return nullptr;
}

std::unique_ptr<Enemy> Factory::createEnemy(EnemyType type) {
    if (type == EnemyType::EmeraldEnemy){
        std::unique_ptr<Enemy> result = std::unique_ptr<Enemy> (new EmeraldEnemy(""));
        result->init("emeraldEnemyTexture", {-1, 1}, {0, 0}, 90);
        //result->SpecialAction();
        return result;
    }
    else if (type == EnemyType::HamonEnemy){
        std::unique_ptr<Enemy> result = std::unique_ptr<Enemy> (new HamonEnemy(""));
        result->init("hamonEnemyTexture", {-1, 1}, {0, 0}, 90);
        //result->SpecialAction();
        return result;
    }
    else if (type == EnemyType::FireEnemy){
        std::unique_ptr<Enemy> result = std::unique_ptr<Enemy> (new FireEnemy(""));
        result->init("fireEnemy", {-1, 1}, {0, 0}, 90);
        //result->SpecialAction();
        return result;
    }
    return nullptr;
}

std::unique_ptr<PowerUp> Factory::createPowerUp(PowerUpType type) {
    if (type == PowerUpType::Shield) {
        std::unique_ptr<PowerUp> result = std::unique_ptr<PowerUp>(new Shield(""));
        result->init("shieldPowerUpTexture",{0.2, 0.2}, {-0.1, 0});
        return result;
    } else if (type == PowerUpType::Weapon) {
        std::unique_ptr<PowerUp> result = std::unique_ptr<PowerUp>(new Weapon(""));
        result->init("knifeTexture",{1, 1}, {-0.1, 0});
        return result;
    }
    return nullptr;
}

std::unique_ptr<Bullet> Factory::createBullet(BulletType type) {
    if (type == BulletType::Knife) {
        std::unique_ptr<Bullet> result = std::unique_ptr<Bullet>(new Knife(""));
        result -> init("knifeTexture", {1,1}, {0.1, 0}, 100);
        return result;
    }
    return nullptr;
}

std::unique_ptr<Platform> Factory::createMap(PlatformType type) {
    if (type == PlatformType::Large) {
        std::unique_ptr<Platform> result = std::unique_ptr<Platform>(new Platform(""));
        result->init("Platform1", sf::Vector2f {-0.1,0});
        return result;
    }
    return nullptr;
}

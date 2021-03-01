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

std::unique_ptr<GameObject> Factory::createObstacle(ObstacleType type) {
    if(type == ObstacleType::Block) {
        auto * obstacle = new Block("Block");
        obstacle->init("blockTexture", {0.70, 0.70}, {0, 0});
        return std::unique_ptr<GameObject>(obstacle);
    }
    else if (type == ObstacleType::Firewall) {
        auto * obstacle = new FireWall("FireWall");
        obstacle->init("fireWallTexture", {1, 1}, {0,0});
        return std::unique_ptr<GameObject>(obstacle);
    }
    return nullptr;
}

std::unique_ptr<GameObject> Factory::createEnemy(EnemyType type) {
    if (type == EnemyType::EmeraldEnemy){
        auto * enemy = new EmeraldEnemy("EmeraldEnemy");
        enemy->init("emeraldEnemyTexture", {-1, 1}, {0, 0}, 90);
        //result->SpecialAction();
        return std::unique_ptr<GameObject>(enemy);
    }
    else if (type == EnemyType::HamonEnemy){
        auto * enemy =new HamonEnemy("HamonEnemy");
        enemy->init("hamonEnemyTexture", {-1, 1}, {0, 0}, 90);
        //result->SpecialAction();
        return std::unique_ptr<GameObject>(enemy);
    }
    else if (type == EnemyType::FireEnemy){
        auto * enemy = new EmeraldEnemy("FireEnemy");
        enemy->init("fireEnemy", {-1, 1}, {0, 0}, 90);
        //result->SpecialAction();
        return std::unique_ptr<GameObject>(enemy);
    }
    return nullptr;
}

std::unique_ptr<GameObject> Factory::createPowerUp(PowerUpType type) {
    if (type == PowerUpType::Shield) {
        auto * powerUp = new Shield("Shield");
        powerUp->init("shieldPowerUpTexture",{0.2, 0.2}, {-0.1, 0});
        return std::unique_ptr<GameObject>(powerUp);
    } else if (type == PowerUpType::Weapon) {
        auto * powerUp = new Weapon("Weapon");
        powerUp->init("knifeTexture",{1, 1}, {-0.1, 0});
        return std::unique_ptr<GameObject>(powerUp);
    }
    return nullptr;
}

std::unique_ptr<GameObject> Factory::createBullet(BulletType type) {
    if (type == BulletType::Knife) {
        auto * knife = new Knife("Knife");
        knife -> init("knifeTexture", {1,1}, {0.1, 0}, 100);
        return std::unique_ptr<GameObject>(knife);
    }
    return nullptr;
}

std::unique_ptr<GameObject> Factory::createMap(PlatformType type) {
    if (type == PlatformType::Large) {
        auto * platform = new Platform("Platform");
        platform->init("Platform1", sf::Vector2f {-0.1,0});
        return std::unique_ptr<GameObject>(platform);
    }
    return nullptr;
}

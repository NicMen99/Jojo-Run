//
// Created by angiolo99 on 23/01/20.
//

#include "Block.h"
#include "FireWall.h"
#include "EmeraldEnemy.h"
#include "Emerald.h"
#include "FireEnemy.h"
#include "Fire.h"
#include "HamonEnemy.h"
#include "Shield.h"
#include "Weapon.h"
#include "Knife.h"
#include "Platform.h"

#include "Factory.h"

std::unique_ptr<GameObject> Factory::createObstacle(GameObjectType type) {
    if(type == GameObjectType::Block) {
        auto * obstacle = new Block("Block");
        obstacle->init("blockTexture", {0.70, 0.70}, {0, 0});
        return std::unique_ptr<GameObject>(obstacle);
    }
    else if (type == GameObjectType::Wall) {
        auto * obstacle = new FireWall("FireWall");
        obstacle->init("fireWallTexture", {1, 1}, {0,0});
        return std::unique_ptr<GameObject>(obstacle);
    }
    return nullptr;
}

std::unique_ptr<GameObject> Factory::createEnemy(GameObjectType type) {
    if (type == GameObjectType::EmeraldEnemy){
        auto * enemy = new EmeraldEnemy("EmeraldEnemy");
        enemy->init("emeraldEnemyTexture", {-1, 1}, {0, 0}, 90);
        enemy->addSound("EMERALDACTION", "emeraldEnemyShout", 25.f);
        return std::unique_ptr<GameObject>(enemy);
    }
    else if (type == GameObjectType::HamonEnemy){
        auto * enemy =new HamonEnemy("HamonEnemy");
        enemy->init("hamonEnemyTexture", {-1, 1}, {0, 0}, 90);
        return std::unique_ptr<GameObject>(enemy);
    }
    else if (type == GameObjectType::FireEnemy){
        auto * enemy = new FireEnemy("FireEnemy");
        enemy->init("fireEnemy", {-1, 1}, {0, 0}, 90);
        enemy->addSound("FIREACTION", "fireEnemyShout", 25.f);
        return std::unique_ptr<GameObject>(enemy);
    }
    return nullptr;
}

std::unique_ptr<GameObject> Factory::createPowerUp(GameObjectType type) {
    if (type == GameObjectType::Shield) {
        auto * powerUp = new Shield("Shield");
        powerUp->init("shieldPowerUpTexture",{0.2, 0.2}, {-0.1, 0});
        return std::unique_ptr<GameObject>(powerUp);
    } else if (type == GameObjectType::Weapon) {
        auto * powerUp = new Weapon("Weapon");
        powerUp->init("knifeTexture",{1, 1}, {-0.1, 0});
        return std::unique_ptr<GameObject>(powerUp);
    }
    return nullptr;
}

std::unique_ptr<GameObject> Factory::createBullet(GameObjectType type) {
    if (type == GameObjectType::Knife) {
        auto * knife = new Knife("Knife");
        knife -> init("knifeTexture", {1,1}, {0.1, 0}, 100);
        return std::unique_ptr<GameObject>(knife);
    } else if (type == GameObjectType::EmeraldBullet) {
        auto * emerald = new Emerald("Emerald");
        emerald -> init("emeraldBlockTexture", {1,1}, {0.1, 0}, 150);
        return std::unique_ptr<GameObject>(emerald);
    } else if (type == GameObjectType::FireBullet) {
        auto * fire = new Fire("Fire");
        fire -> init("fireBlockTexture", {1,1}, {0.1, 0}, 50);
        return std::unique_ptr<GameObject>(fire);
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

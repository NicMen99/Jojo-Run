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
#include "Background.h"
#include "GameConfig.h"

#include "Factory.h"

std::unique_ptr<GameObject> Factory::createObstacle(GameObjectType type) {
    if(type == GameObjectType::Block) {
        auto * obstacle = new Block("Block");
        obstacle->init();
        return std::unique_ptr<GameObject>(obstacle);
    }
    else if (type == GameObjectType::Wall) {
        auto * obstacle = new FireWall("FireWall");
        obstacle->init();
        return std::unique_ptr<GameObject>(obstacle);
    }
    return nullptr;
}

std::unique_ptr<GameObject> Factory::createEnemy(GameObjectType type) {
    if (type == GameObjectType::EmeraldEnemy){
        auto * enemy = new EmeraldEnemy("EmeraldEnemy");
        enemy->init();
        return std::unique_ptr<GameObject>(enemy);
    }
    else if (type == GameObjectType::HamonEnemy){
        auto * enemy =new HamonEnemy("HamonEnemy");
        enemy->init();
        return std::unique_ptr<GameObject>(enemy);
    }
    else if (type == GameObjectType::FireEnemy){
        auto * enemy = new FireEnemy("FireEnemy");
        enemy->init();
        return std::unique_ptr<GameObject>(enemy);
    }
    return nullptr;
}

std::unique_ptr<GameObject> Factory::createPowerUp(GameObjectType type) {
    if (type == GameObjectType::Shield) {
        auto * powerUp = new Shield("Shield");
        powerUp->init();
        return std::unique_ptr<GameObject>(powerUp);
    }
    else if (type == GameObjectType::Weapon) {
        auto * powerUp = new Weapon("Weapon");
        powerUp->init();
        return std::unique_ptr<GameObject>(powerUp);
    }
    return nullptr;
}

std::unique_ptr<GameObject> Factory::createBullet(GameObjectType type) {
    if (type == GameObjectType::Knife) {
        auto * knife = new Knife("Knife");
        knife -> init();
        return std::unique_ptr<GameObject>(knife);
    }
    else if (type == GameObjectType::EmeraldBullet) {
        auto * emerald = new Emerald("Emerald");
        emerald -> init();
        return std::unique_ptr<GameObject>(emerald);
    }
    else if (type == GameObjectType::FireBullet) {
        auto * fire = new Fire("Fire");
        fire -> init();
        return std::unique_ptr<GameObject>(fire);
    }
    return nullptr;
}

std::unique_ptr<GameObject> Factory::createPlatform(GameObjectType type) {
    auto * platform = new Platform("Platform");
    platform->init();
    return std::unique_ptr<GameObject>(platform);
}

std::unique_ptr<GameObject> Factory::createBackground(GameObjectType type) {
    float speedx = GC.getSceneSpeed().x;
    if(type == GameObjectType::Sky) {
        auto * bg = new Background("Sky");
        bg->init(GameObjectType::Sky);
        return std::unique_ptr<GameObject>(bg);
    }
    else if(type == GameObjectType::City) {
        auto * bg = new Background("City");
        bg->init(GameObjectType::City);
        return std::unique_ptr<GameObject>(bg);
    }
    else if(type == GameObjectType::SkyScrapers) {
        auto * bg = new Background("SkyScrapers");
        bg->init(GameObjectType::SkyScrapers);
        return std::unique_ptr<GameObject>(bg);
    }
    else if(type == GameObjectType::Bridge) {
        auto * bg = new Background("Bridge");
        bg->init(GameObjectType::Bridge);
        return std::unique_ptr<GameObject>(bg);
    }
    return nullptr;
}

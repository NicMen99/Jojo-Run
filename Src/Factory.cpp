//
// Created by angiolo99 on 23/01/20.
//

#include <iostream>

#include "Entities/Block.h"
#include "Entities/Fire.h"
#include "Entities/EmeraldEnemy.h"
#include "Entities/Emerald.h"
#include "Entities/FireEnemy.h"
#include "Entities/FireBall.h"
#include "Entities/HamonEnemy.h"
#include "Entities/Shield.h"
#include "Entities/Weapon.h"
#include "Entities/Knife.h"
#include "Entities/Platform.h"
#include "Entities/Background.h"
#include "GameConfig.h"

#include "Factory.h"

std::unique_ptr<Entity> Factory::createObstacle(GameObjectType type) {
    if(type == GameObjectType::Block) {
        auto * obstacle = new Block("Block");
        obstacle->init();
        return std::unique_ptr<Entity>(obstacle);
    }
    else if (type == GameObjectType::Wall) {
        auto * obstacle = new Fire("Fire");
        obstacle->init();
        return std::unique_ptr<Entity>(obstacle);
    }
    return nullptr;
}

std::unique_ptr<Entity> Factory::createEnemy(GameObjectType type) {
    if (type == GameObjectType::EmeraldEnemy){
        auto * enemy = new EmeraldEnemy("EmeraldEnemy");
        enemy->init();
        return std::unique_ptr<Entity>(enemy);
    }
    else if (type == GameObjectType::HamonEnemy){
        auto * enemy =new HamonEnemy("HamonEnemy");
        enemy->init();
        return std::unique_ptr<Entity>(enemy);
    }
    else if (type == GameObjectType::FireEnemy){
        auto * enemy = new FireEnemy("FireEnemy");
        enemy->init();
        return std::unique_ptr<Entity>(enemy);
    }
    return nullptr;
}

std::unique_ptr<Entity> Factory::createPowerUp(GameObjectType type) {
    if (type == GameObjectType::Shield) {
        auto * powerUp = new Shield("Shield");
        powerUp->init();
        return std::unique_ptr<Entity>(powerUp);
    }
    else if (type == GameObjectType::Weapon) {
        auto * powerUp = new Weapon("Weapon");
        powerUp->init();
        return std::unique_ptr<Entity>(powerUp);
    }
    return nullptr;
}

std::unique_ptr<Entity> Factory::createBullet(GameObjectType type) {
    if (type == GameObjectType::Knife) {
        auto * knife = new Knife("Knife");
        knife -> init();
        return std::unique_ptr<Entity>(knife);
    }
    else if (type == GameObjectType::EmeraldBullet) {
        auto * emerald = new Emerald("Emerald");
        emerald -> init();
        return std::unique_ptr<Entity>(emerald);
    }
    else if (type == GameObjectType::FireBullet) {
        auto * fire = new FireBall("FireBall");
        fire -> init();
        return std::unique_ptr<Entity>(fire);
    }
    return nullptr;
}

std::unique_ptr<Entity> Factory::createPlatform(GameObjectType type) {
    auto * platform = new Platform("Platform");
    platform->init();
    return std::unique_ptr<Entity>(platform);
}

std::unique_ptr<Entity> Factory::createBackground(GameObjectType type) {
    if(type == GameObjectType::Sky) {
        auto * bg = new Background("Sky");
        bg->init(GameObjectType::Sky);
        return std::unique_ptr<Entity>(bg);
    }
    else if(type == GameObjectType::City) {
        auto * bg = new Background("City");
        bg->init(GameObjectType::City);
        return std::unique_ptr<Entity>(bg);
    }
    else if(type == GameObjectType::SkyScrapers) {
        auto * bg = new Background("SkyScrapers");
        bg->init(GameObjectType::SkyScrapers);
        return std::unique_ptr<Entity>(bg);
    }
    else if(type == GameObjectType::Bridge) {
        auto * bg = new Background("Bridge");
        bg->init(GameObjectType::Bridge);
        return std::unique_ptr<Entity>(bg);
    }
    return nullptr;
}

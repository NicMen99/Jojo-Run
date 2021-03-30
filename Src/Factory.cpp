//
// Created by angiolo99 on 23/01/20.
//

#include <iostream>

#include "Game.h"
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

#include "Factory.h"

Factory::Factory() {

}

Factory::~Factory() {

}

std::unique_ptr<Entity> Factory::createObstacle(EntityType type) {
    if(type == EntityType::Block) {
        auto * obstacle = new Block("Block");
        obstacle->init();
        return std::unique_ptr<Entity>(obstacle);
    }
    else if (type == EntityType::Wall) {
        auto * obstacle = new Fire("Fire");
        obstacle->init();
        return std::unique_ptr<Entity>(obstacle);
    }
    return nullptr;
}

std::unique_ptr<Entity> Factory::createEnemy(EntityType type) {
    if (type == EntityType::EmeraldEnemy){
        auto * enemy = new EmeraldEnemy("EmeraldEnemy");
        enemy->init();
        return std::unique_ptr<Entity>(enemy);
    }
    else if (type == EntityType::HamonEnemy){
        auto * enemy =new HamonEnemy("HamonEnemy");
        enemy->init();
        return std::unique_ptr<Entity>(enemy);
    }
    else if (type == EntityType::FireEnemy){
        auto * enemy = new FireEnemy("FireEnemy");
        enemy->init();
        return std::unique_ptr<Entity>(enemy);
    }
    return nullptr;
}

std::unique_ptr<Entity> Factory::createPowerUp(EntityType type) {
    if (type == EntityType::Shield) {
        auto * powerUp = new Shield("Shield");
        powerUp->init();
        return std::unique_ptr<Entity>(powerUp);
    }
    else if (type == EntityType::Weapon) {
        auto * powerUp = new Weapon("Weapon");
        powerUp->init();
        return std::unique_ptr<Entity>(powerUp);
    }
    return nullptr;
}

std::unique_ptr<Entity> Factory::createBullet(EntityType type) {
    if (type == EntityType::Knife) {
        auto * knife = new Knife("Knife");
        knife -> init();
        return std::unique_ptr<Entity>(knife);
    }
    else if (type == EntityType::EmeraldBullet) {
        auto * emerald = new Emerald("Emerald");
        emerald -> init();
        return std::unique_ptr<Entity>(emerald);
    }
    else if (type == EntityType::FireBullet) {
        auto * fire = new FireBall("FireBall");
        fire -> init();
        return std::unique_ptr<Entity>(fire);
    }
    return nullptr;
}

std::unique_ptr<Entity> Factory::createPlatform(EntityType type) {
    auto * platform = new Platform("Platform");
    platform->init();
    return std::unique_ptr<Entity>(platform);
}

std::unique_ptr<Entity> Factory::createBackground(EntityType type) {
    if(type == EntityType::Sky) {
        auto * bg = new Background("Sky");
        bg->init(EntityType::Sky);
        return std::unique_ptr<Entity>(bg);
    }
    else if(type == EntityType::City) {
        auto * bg = new Background("City");
        bg->init(EntityType::City);
        return std::unique_ptr<Entity>(bg);
    }
    else if(type == EntityType::SkyScrapers) {
        auto * bg = new Background("SkyScrapers");
        bg->init(EntityType::SkyScrapers);
        return std::unique_ptr<Entity>(bg);
    }
    else if(type == EntityType::Bridge) {
        auto * bg = new Background("Bridge");
        bg->init(EntityType::Bridge);
        return std::unique_ptr<Entity>(bg);
    }
    return nullptr;
}


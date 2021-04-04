//
// Created by angiolo99 on 23/01/20.
//

#include <iostream>

#include "Game.h"
#include "Entities/Hero.h"
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
#include "AnimationManager.h"

#include "Factory.h"

Factory::Factory() {

}

Factory::~Factory() {

}

std::unique_ptr<Entity> Factory::createHero() {
    auto * hero = new Hero();
    hero->init();
    const std::list<FrameParams> frames = {
        {1, "playerTexture", {0,0,0,0}, {0,0}, {false, false}}
    };
    hero->addAnimation("DEFAULT", frames);
    hero->addSound("COLLISION", "collisionSound");
    hero->addSound("SHIELD", "shieldSound");
    hero->addSound("SHIELDON", "shieldOn");
    return std::unique_ptr<Entity>(hero);
}

std::unique_ptr<Entity> Factory::createEnemy(EntityType type) {
    if (type == EntityType::EmeraldEnemy){
        auto * enemy = new EmeraldEnemy("EmeraldEnemy");
        enemy->init();
        const std::list<FrameParams> frames = {
                {1, "emeraldEnemyTexture", {0,0,0,0}, {0,0}, {true, false}}
        };
        enemy->addAnimation("DEFAULT", frames);
        enemy->addSound("EMERALDACTION", "emeraldEnemyShout");
        return std::unique_ptr<Entity>(enemy);
    }
    else if (type == EntityType::HamonEnemy){
        auto * enemy =new HamonEnemy("HamonEnemy");
        enemy->init();
        const std::list<FrameParams> frames = {
                {1, "hamonEnemyTexture", {0,0,0,0}, {0,0}, {true, false}}
        };
        enemy->addAnimation("DEFAULT", frames);
        enemy->addSound("HAMONACTION", "hamonEnemyShout");
        return std::unique_ptr<Entity>(enemy);
    }
    else if (type == EntityType::FireEnemy){
        auto * enemy = new FireEnemy("FireEnemy");
        enemy->init();
        const std::list<FrameParams> frames = {
                {1, "fireEnemyTexture", {0,0,0,0}, {0,0}, {true, false}}
        };
        enemy->addAnimation("DEFAULT", frames);
        enemy->addSound("FIREACTION", "fireEnemyShout");
        return std::unique_ptr<Entity>(enemy);
    }
    return nullptr;
}

std::unique_ptr<Entity> Factory::createObstacle(EntityType type) {
    if(type == EntityType::Block) {
        auto * obstacle = new Block("Block");
        obstacle->init();
        const std::list<FrameParams> frames = {
            {1, "blockTexture", {0,0,0,0}, {0,0}, {false, false}}
        };
        obstacle->addAnimation("DEFAULT", frames);
        return std::unique_ptr<Entity>(obstacle);
    }
    else if (type == EntityType::Wall) {
        auto * obstacle = new Fire("Fire");
        obstacle->init();
        const std::list<FrameParams> frames = {
            {8, "Fire", {0,0,32,32}, {64,64}, {false, false}},
            {8, "Fire", {32,0,32,32}, {64,64}, {false, false}}
        };
        obstacle->addAnimation("DEFAULT", frames);
        return std::unique_ptr<Entity>(obstacle);
    }
    return nullptr;
}

std::unique_ptr<Entity> Factory::createPowerUp(EntityType type) {
    if (type == EntityType::Shield) {
        auto * powerUp = new Shield("Shield");
        powerUp->init();
        const std::list<FrameParams> frames = {
                {1, "shieldPowerUpTexture", {0,0,0,0}, {39,77}, {true, false}}
        };
        powerUp->addAnimation("DEFAULT", frames);
        return std::unique_ptr<Entity>(powerUp);
    }
    else if (type == EntityType::Weapon) {
        auto * powerUp = new Weapon("Weapon");
        powerUp->init();
        const std::list<FrameParams> frames = {
                {1, "knifeTexture", {0,0,0,0}, {0,0}, {false, false}}
        };
        powerUp->addAnimation("DEFAULT", frames);
        return std::unique_ptr<Entity>(powerUp);
    }
    return nullptr;
}

std::unique_ptr<Entity> Factory::createBullet(EntityType type) {
    if (type == EntityType::Knife) {
        auto * knife = new Knife("Knife");
        knife -> init();
        const std::list<FrameParams> frames = {
            {1, "knifeTexture", {0,0,0,0}, {0,0}, {false, false}}
        };
        knife->addAnimation("DEFAULT", frames);
        return std::unique_ptr<Entity>(knife);
    }
    else if (type == EntityType::EmeraldBullet) {
        auto * emerald = new Emerald("Emerald");
        emerald -> init();
        const std::list<FrameParams> frames = {
            {1, "emeraldBlockTexture", {0,0,0,0}, {0,0}, {false, false}}
        };
        emerald->addAnimation("DEFAULT", frames);
        return std::unique_ptr<Entity>(emerald);
    }
    else if (type == EntityType::FireBullet) {
        auto * fire = new FireBall("FireBall");
        fire -> init();
        const std::list<FrameParams> frames = {
            {1, "fireBlockTexture", {0,0,0,0}, {0,0}, {false, false}}
        };
        fire->addAnimation("DEFAULT", frames);
        return std::unique_ptr<Entity>(fire);
    }
    return nullptr;
}

std::unique_ptr<Entity> Factory::createPlatform(EntityType type) {
    if(type == EntityType::StonePlatform) {
        auto * pl = new Platform("PLATFORM");
        pl->init();
        const std::list<FrameParams> frames = {
            {1, "PLATFORM", {0,0,0,0}, {0,0}, {false, false}}
        };
        pl->addAnimation("DEFAULT", frames);
        return std::unique_ptr<Entity>(pl);
    }
    return nullptr;
}

std::unique_ptr<Entity> Factory::createBackground(EntityType type) {
    if(type == EntityType::Sky) {
        auto * bg = new Background("Sky");
        bg->init(EntityType::Sky);
        const std::list<FrameParams> frames = {
            {1, "BG", {0,0,0,0}, {CONFIG->getWindowSize()}, {false, false}}
        };
        bg->addAnimation("DEFAULT", frames);
        return std::unique_ptr<Entity>(bg);
    }
    else if(type == EntityType::City) {
        auto * bg = new Background("City");
        bg->init(EntityType::City);
        const std::list<FrameParams> frames = {
            {1, "Background1", {0,0,0,0}, {CONFIG->getWindowSize()}, {false, false}}
        };
        bg->addAnimation("DEFAULT", frames);
        return std::unique_ptr<Entity>(bg);
    }
    else if(type == EntityType::SkyScrapers) {
        auto * bg = new Background("SkyScrapers");
        bg->init(EntityType::SkyScrapers);
        const std::list<FrameParams> frames = {
            {1, "Foreground", {0,0,0,0}, {CONFIG->getWindowSize()}, {false, false}}
        };
        bg->addAnimation("DEFAULT", frames);
        return std::unique_ptr<Entity>(bg);
    }
    else if(type == EntityType::Bridge) {
        auto * bg = new Background("Bridge");
        bg->init(EntityType::Bridge);
        const std::list<FrameParams> frames = {
            {1, "Middle", {0,0,0,0}, {CONFIG->getWindowSize()}, {false, false}}
        };
        bg->addAnimation("DEFAULT", frames);
        return std::unique_ptr<Entity>(bg);
    }
    return nullptr;
}


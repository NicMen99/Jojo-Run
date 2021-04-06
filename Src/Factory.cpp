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
    static const std::list<FrameParams> run_animation = {
            {4, "PLAYER_RUN", {0,0,113,87}, {0,0}, {false, false}},
            {4, "PLAYER_RUN", {118,0,117,87}, {0,0}, {false, false}},
            {4, "PLAYER_RUN", {241,0,83,87}, {0,0}, {false, false}},
            {4, "PLAYER_RUN", {331,0,79,87}, {0,0}, {false, false}},
    };
    static const std::list<FrameParams> shield_run_animation = {
            {4, "PLAYER_RUN_SHIELD", {0,0,113,87}, {0,0}, {false, false}},
            {4, "PLAYER_RUN_SHIELD", {118,0,117,87}, {0,0}, {false, false}},
            {4, "PLAYER_RUN_SHIELD", {241,0,83,87}, {0,0}, {false, false}},
            {4, "PLAYER_RUN_SHIELD", {331,0,79,87}, {0,0}, {false, false}},
    };
    static const std::list<FrameParams> jump_animation = {
            {4, "PLAYER_JUMP", {0,58,67,118}, {0,0}, {false, false}},
            {4, "PLAYER_JUMP", {74,21,78,130}, {0,0}, {false, false}},
            {4, "PLAYER_JUMP", {160,20,78,131}, {0,0}, {false, false}},
            {4, "PLAYER_JUMP", {246,27,77,78}, {0,0}, {false, false}},
            {4, "PLAYER_JUMP", {330,28,83,71}, {0,0}, {false, false}},
    };
    static const std::list<FrameParams> fall_animation = {
            {4, "PLAYER_JUMP", {420,31,85,64}, {0,0}, {false, false}},
            {1, "PLAYER_JUMP", {513,16,78,88}, {0,0}, {false, false}},
//            {4, "PLAYER_JUMP", {601,0,60,136}, {0,0}, {false, false}},
//            {4, "PLAYER_JUMP", {673,1,54,148}, {0,0}, {false, false}},
//            {4, "PLAYER_JUMP", {736,1,54,148}, {0,0}, {false, false}},
    };
    static const std::list<FrameParams> fall_animation2 = {
            {4, "PLAYER_JUMP", {804,98,79,78}, {0,0}, {false, false}},
            {4, "PLAYER_JUMP", {892,70,81,106}, {0,0}, {false, false}},
    };
    static const std::list<FrameParams> death_animation = {
            {7, "PLAYER_DEATH", {0,0,126,122}, {0,0}, {false, false}},
            {7, "PLAYER_DEATH", {129,0,129,122}, {0,0}, {false, false}},
            {7, "PLAYER_DEATH", {264,0,137,122}, {0,0}, {false, false}},
            {7, "PLAYER_DEATH", {403,0,135,122}, {0,0}, {false, false}},
            {7, "PLAYER_DEATH", {544,0,129,122}, {0,0}, {false, false}},
            {7, "PLAYER_DEATH", {682,0,93,122}, {0,0}, {false, false}},
            {7, "PLAYER_DEATH", {781,0,101,122}, {0,0}, {false, false}},
    };
    hero->addAnimation("RUN", run_animation);
    hero->addAnimation("SRUN", shield_run_animation);
    hero->addAnimation("JUMP", jump_animation);
    hero->addAnimation("FALL", fall_animation);
    hero->addAnimation("FALL2", fall_animation2);
    hero->addAnimation("DEATH", death_animation);
    hero->addSound("COLLISION", "collisionSound");
    hero->addSound("SHIELD", "shieldSound");
    hero->addSound("SHIELDON", "shieldOn");
    return std::unique_ptr<Entity>(hero);
}

std::unique_ptr<Entity> Factory::createEnemy(EntityType type) {
    if (type == EntityType::EmeraldEnemy){
        auto * enemy = new EmeraldEnemy("EmeraldEnemy");
        enemy->init();
        const std::list<FrameParams> idle = {
                {1, "EMERALD_ENEMY_IDLE", {0,0,0,0}, {0,0}, {true, false}}
        };
        const std::list<FrameParams> death = {
                {7, "EMERALD_ENEMY_DEATH", {0,0,97,91}, {0,0}, {false, false}},
                {7, "EMERALD_ENEMY_DEATH", {161,0,113,91}, {0,0}, {false, false}},
                {7, "EMERALD_ENEMY_DEATH", {327,0,141,91}, {0,0}, {false, false}},
                {7, "EMERALD_ENEMY_DEATH", {504,0,143,91}, {0,0}, {false, false}},
                {7, "EMERALD_ENEMY_DEATH", {670,0,151,91}, {0,0}, {false, false}}
        };
        enemy->addAnimation("IDLE", idle);
        enemy->addAnimation("DEATH", death);
        enemy->addSound("EMERALDACTION", "emeraldEnemyShout");
        return std::unique_ptr<Entity>(enemy);
    }
    else if (type == EntityType::HamonEnemy){
        auto * enemy =new HamonEnemy("HamonEnemy");
        enemy->init();
        const std::list<FrameParams> idle = {
                {1, "HAMON_ENEMY_IDLE", {0,0,0,0}, {0,0}, {true, false}}
        };
        const std::list<FrameParams> death = {
                {7, "HAMON_ENEMY_DEATH", {562,0,75,107}, {0,0}, {false, false}},
                {7, "HAMON_ENEMY_DEATH", {442,0,111,107}, {0,0}, {false, false}},
                {7, "HAMON_ENEMY_DEATH", {285,0,149,107}, {0,0}, {false, false}},
                {7, "HAMON_ENEMY_DEATH", {142,0,133,107}, {0,0}, {false, false}},
                {7, "HAMON_ENEMY_DEATH", {0,0,133,107}, {0,0}, {false, false}}
        };
        enemy->addAnimation("IDLE", idle);
        enemy->addAnimation("DEATH", death);
        enemy->addSound("HAMONACTION", "hamonEnemyShout");
        return std::unique_ptr<Entity>(enemy);
    }
    else if (type == EntityType::FireEnemy){
        auto * enemy = new FireEnemy("FireEnemy");
        enemy->init();
        const std::list<FrameParams> idle = {
                {1, "FIRE_ENEMY_IDLE", {0,0,133,116}, {0,0}, {false, false}}
        };
        const std::list<FrameParams> death = {
                {7, "FIRE_ENEMY_DEATH", {0,0,83,120}, {0,0}, {false, false}},
                {7, "FIRE_ENEMY_DEATH", {213,0,92,120}, {0,0}, {false, false}},
                {7, "FIRE_ENEMY_DEATH", {420,0,105,120}, {0,0}, {false, false}},
                {7, "FIRE_ENEMY_DEATH", {589,0,142,120}, {0,0}, {false, false}},
                {7, "FIRE_ENEMY_DEATH", {855,0,142,120}, {0,0}, {false, false}},
                {7, "FIRE_ENEMY_DEATH", {1094,0,98,120}, {0,0}, {false, false}}
        };
        enemy->addAnimation("DEFAULT", idle);
        enemy->addAnimation("DEATH", death);
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


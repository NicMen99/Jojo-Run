//
// Created by angiolo99 on 23/01/20.
//

#include "GameConfig.h"
#include "Factory.h"

std::unique_ptr<Block> Factory::createBlock(BlockType type) {
    std::unique_ptr<Block> block = std::unique_ptr<Block>(new Block(""));
    block->init("blockTexture", {0.70, 0.70}, {0, 0} );
    return block;
}

std::unique_ptr<FireWall> Factory::createFireWall(FireWallType type) {
    std::unique_ptr<FireWall> result = std::unique_ptr<FireWall>(new FireWall(""));
    result->init("fireWallTexture", {1, 1}, {0,0});
    return result;
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
    } else if (type == PowerUpType::Knife) {
        std::unique_ptr<PowerUp> result = std::unique_ptr<PowerUp>(new Weapon(""));
        result->init("knifeTexture",{1, 1}, {-0.1, 0});
        return result;
    } else if (type == PowerUpType::ThrownKnife) {
        std::unique_ptr<PowerUp> result = std::unique_ptr<PowerUp>(new Weapon(""));
        result->init("knifeTexture",{1, 1}, {-0.1, 0});
        return result;
    }
    return nullptr;
}

std::unique_ptr<Platform> Factory::createPlatform(GroundType type) {
    std::unique_ptr<Platform> result = std::unique_ptr<Platform>(new Platform(""));
    if(type == GroundType::Large) {
        result->init("Platform1", sf::Vector2f {0,0});
        result->setPosition({1650,600});
    }
    return result;
}

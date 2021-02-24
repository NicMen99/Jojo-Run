//
// Created by angiolo99 on 23/01/20.
//

#include "GameConfig.h"
#include "Factory.h"

std::unique_ptr<Block> Factory::createBlock(BlockType type) {
    std::unique_ptr<Block> block = std::unique_ptr<Block>(new Block);
    block->init("blockTexture", {1, 0}, {0.70, 0.70} );
    return block;
}

std::unique_ptr<FireWall> Factory::createFireWall(FireWallType type) {
    std::unique_ptr<FireWall> result = std::unique_ptr<FireWall>(new FireWall);
    result->init("fireWallTexture", sf::Vector2f {0.8, 0}, sf::Vector2f {1,1});
    return result;
}

std::unique_ptr<Enemy> Factory::createEnemy(EnemyType type) {
    if (type == EnemyType::EmeraldEnemy){
        std::unique_ptr<Enemy> result = std::unique_ptr<Enemy> (new EmeraldEnemy);
        result->init("emeraldEnemyTexture", sf::Vector2f {0.5, 0}, sf::Vector2f{-1,1});
        //result->SpecialAction();
        return result;
    }
    else if (type == EnemyType::HamonEnemy){
        std::unique_ptr<Enemy> result = std::unique_ptr<Enemy> (new HamonEnemy);
        result->init("hamonEnemyTexture", sf::Vector2f {0.5, 0}, sf::Vector2f{-1,1});
        //result->SpecialAction();
        return result;
    }
    else if (type == EnemyType::FireEnemy){
        std::unique_ptr<Enemy> result = std::unique_ptr<Enemy> (new FireEnemy);
        result->init("fireEnemy", sf::Vector2f {0.5, 0}, sf::Vector2f{-1,1});
        //result->SpecialAction();
        return result;
    }
    return nullptr;
}

std::unique_ptr<PowerUp> Factory::createPowerUp(PowerUpType type) {
    std::unique_ptr<PowerUp> result = std::unique_ptr<PowerUp>(new PowerUp);
    if (type == PowerUpType::Shield) {
        result->init("shieldPowerUpTexture",{-0.9, 0}, {0.2, 0.2}, true);
    } else if (type == PowerUpType::Knife) {
        result->init("knifeTexture",{-0.9, 0}, {1, 1}, false, true);
    } else if (type == PowerUpType::ThrownKnife) {
        result->init("knifeTexture",{0.9, 0}, {1, 1}, false, false, true);
    }
    return result;
}

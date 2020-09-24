//
// Created by angiolo99 on 23/01/20.
//

#include "Factory.h"

std::unique_ptr<Block> Factory::createBlock(BlockType type) {
    std::unique_ptr<Block> result = std::unique_ptr<Block>(new Block);
    if (type == BlockType::MovingBlock)
        result->setIsMovingBlock();
    result->setScale(0.25, 0.25);
    result->setDamageB(50);
    result->setBlockSpeedX(0.8);
    result->setTexture(blockTexture);
    return result;
}

Factory::Factory() {
    blockTexture.loadFromFile("Texture/blockTexture.png");
    fireWallTexture.loadFromFile("Texture/fireWallTexture.png");
    shieldTexture.loadFromFile("Texture/shieldTexture.png");
    knifeTexture.loadFromFile("Texture/fnifeTexture.png");
    hamonEnemyTexture.loadFromFile("Texture/hamonEnemyTexture.png");
    fireEnemyTexture.loadFromFile("Texture/fireEnemyTexture.png");
    emeraldEnemyTexture.loadFromFile("Texture/emeraldEnemyTexture.png");
    hamonBlockTexture.loadFromFile("Texture/hamonBlockTexture.png");
    fireBlockTexture.loadFromFile("Texture/fireBlockTexture.png");
    emeraldBlockTexture.loadFromFile("Texture/emeraldBlockTexture.png");
}

std::unique_ptr<FireWall> Factory::createFireWall(FireWallType type) {
    std::unique_ptr<FireWall> result = std::unique_ptr<FireWall>(new FireWall);
    if (type == FireWallType::MovingWall)
        result->setIsMovingFW();
    result->setDamageFW(15);
    result->setScale(0.25, 0.25);
    result->setTexture(fireWallTexture);
    return result;
}

std::unique_ptr<Enemy> Factory::createEnemy(EnemyType type) {
    if (type == EnemyType::EmeraldEnemy){
        std::unique_ptr<Enemy> result = std::unique_ptr<Enemy> (new EmeraldEnemy);
        result->setSpeed(0.2);
        result->setDamage(90);
        result->setTexture(emeraldEnemyTexture);
        result->SpecialAction();
        return result;
    }
    else if (type == EnemyType::HamonEnemy){
        std::unique_ptr<Enemy> result = std::unique_ptr<Enemy> (new HamonEnemy);
        result->setSpeed(0.2);
        result->setDamage(90);
        result->setTexture(hamonEnemyTexture);
        result->SpecialAction();
        return result;
    }
    else if (type == EnemyType::FireEnemy){
        std::unique_ptr<Enemy> result = std::unique_ptr<Enemy> (new FireEnemy);
        result->setSpeed(0.2);
        result->setDamage(90);
        result->setTexture(fireEnemyTexture);
        result->SpecialAction();
        return result;
    }
}

std::unique_ptr<PowerUp> Factory::createPowerUp(PowerUpType type) {
    if (type == PowerUpType::Shield) {
        std::unique_ptr<PowerUp> result = std::unique_ptr<PowerUp>(new Shield);
        result->setIsMovingPu(true);
        result->setSpeedPux(0.9);
        result->setTexture(shieldPowerUpTexture);
        return result;
    } else if (type == PowerUpType::Knife) {
        std::unique_ptr<PowerUp> result = std::unique_ptr<PowerUp>(new Knife);
        result->setIsMovingPu(true);
        result->setSpeedPux(0.9);
        result->setTexture(knifeTexture);
        result->setRotation(45.f);
        return result;
    } else if (type == PowerUpType::ThrownKnife) {
        std::unique_ptr<PowerUp> result = std::unique_ptr<PowerUp>(new Knife);
        result->setIsMovingPu(true);
        result->setSpeedPux(0.9);
        result->setTexture(knifeTexture);
        return result;
    }
}
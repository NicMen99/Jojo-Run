//
// Created by angiolo99 on 23/01/20.
//

#include "GameConfig.h"
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
    blockTexture.loadFromFile(GC->getAssetPath("blockTexture"));
    fireWallTexture.loadFromFile(GC->getAssetPath("fireWallTexture"));
    shieldPowerUpTexture.loadFromFile(GC->getAssetPath("shieldPowerUpTexture"));
    knifeTexture.loadFromFile(GC->getAssetPath("knifeTexture"));
    hamonEnemyTexture.loadFromFile(GC->getAssetPath("hamonEnemyTexture"));
    fireEnemyTexture.loadFromFile(GC->getAssetPath("fireEnemy"));
    emeraldEnemyTexture.loadFromFile(GC->getAssetPath("emeraldEnemyTexture"));
    hamonBlockTexture.loadFromFile(GC->getAssetPath("hamonBlockTexture"));
    fireBlockTexture.loadFromFile(GC->getAssetPath("fireBlockTexture"));
    emeraldBlockTexture.loadFromFile(GC->getAssetPath("emeraldBlockTexture"));
}

std::unique_ptr<FireWall> Factory::createFireWall(FireWallType type) {
    std::unique_ptr<FireWall> result = std::unique_ptr<FireWall>(new FireWall);
    if (type == FireWallType::MovingWall)
        result->setIsMovingFW(true);
    result->setDamageFW(15);
    result->setScale(0.25, 0.25);
    result->setTexture(fireWallTexture);
    return result;
}

std::unique_ptr<Enemy> Factory::createEnemy(EnemyType type) {
    if (type == EnemyType::EmeraldEnemy){
        std::unique_ptr<Enemy> result = std::unique_ptr<Enemy> (new EmeraldEnemy);
        result->setSpeed(0.5);
        result->setDamage(90);
        result->setIsMovingEnemy(true);
        result->setScale(-1,1);
        result->setTexture(emeraldEnemyTexture);
        result->SpecialAction();
        return result;
    }
    else if (type == EnemyType::HamonEnemy){
        std::unique_ptr<Enemy> result = std::unique_ptr<Enemy> (new HamonEnemy);
        result->setSpeed(0.5);
        result->setDamage(90);
        result->setIsMovingEnemy(true);
        result->setScale(-1,1);
        result->setTexture(hamonEnemyTexture);
        result->SpecialAction();
        return result;
    }
    else if (type == EnemyType::FireEnemy){
        std::unique_ptr<Enemy> result = std::unique_ptr<Enemy> (new FireEnemy);
        result->setSpeed(0.5);
        result->setDamage(90);
        result->setIsMovingEnemy(true);
        result->setTexture(fireEnemyTexture);
        result->setScale(-1,1);
        result->SpecialAction();
        return result;
    }
    return nullptr;
}

std::unique_ptr<PowerUp> Factory::createPowerUp(PowerUpType type) {
    std::unique_ptr<PowerUp> result = std::unique_ptr<PowerUp>(new PowerUp);
    result->setIsMovingPu(true);
    result->setSpeedPux(0.9);
    if (type == PowerUpType::Shield) {
        result->setTexture(shieldPowerUpTexture);
        result->setScale(0.2,0.2);
        result->setIsShield(true);
    } else if (type == PowerUpType::Knife) {
        result->setTexture(knifeTexture);
        result->setScale(0.8,0.8);
        result->setRotation(45.f);
        result->setIsKnife(true);
    } else if (type == PowerUpType::ThrownKnife) {
        result->setTexture(knifeTexture);
        result->setScale(0.8,0.8);
        result->setIsThrowable(true);
    }
    return result;
}
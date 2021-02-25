//
// Created by angiolo99 on 23/01/20.
//

#ifndef JOJO_RUN_FACTORY_H
#define JOJO_RUN_FACTORY_H

#include <SFML/Graphics.hpp>
#include "Block.h"
#include "FireWall.h"
#include "Shield.h"
#include "Knife.h"
#include "Enemy.h"
#include "PowerUp.h"
#include "EmeraldEnemy.h"
#include "FireEnemy.h"
#include "HamonEnemy.h"
#include "Platform.h"
#include <iostream>

enum class BlockType {MovingBlock/*,StillBlock*/};
enum class FireWallType {MovingWall/*,StillWall*/};
enum class EnemyType {FireEnemy, HamonEnemy, EmeraldEnemy /*, StillEnemy*/};
enum class PowerUpType {Knife, Shield, ThrownKnife};
enum class GroundType {Short, Medium, Large};

class Factory {
public:
    Factory() = default;
    virtual ~Factory() = default;

    virtual std::unique_ptr<Block> createBlock(BlockType type);
    virtual std::unique_ptr<FireWall> createFireWall(FireWallType type);
    virtual std::unique_ptr<Enemy> createEnemy(EnemyType type);
    virtual std::unique_ptr<PowerUp> createPowerUp(PowerUpType type);
    virtual std::unique_ptr<Platform> createPlatform(GroundType type);
};

#endif //JOJO_RUN_FACTORY_H

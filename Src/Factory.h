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
#include <iostream>

enum class BlockType {MovingBlock/*,StillBlock*/};
enum class FireWallType {MovingWall/*,StillWall*/};
enum class EnemyType {FireEnemy, HamonEnemy, EmeraldEnemy /*, StillEnemy*/};
enum class PowerUpType {Knife, Shield, ThrownKnife};

class Factory {
public:
    Factory() = default;
    virtual ~Factory() = default;

    virtual std::unique_ptr<Block> createBlock(BlockType type);
    virtual std::unique_ptr<FireWall> createFireWall(FireWallType type);
    virtual std::unique_ptr<Enemy> createEnemy(EnemyType type);
    virtual std::unique_ptr<PowerUp> createPowerUp(PowerUpType type);

private:

    sf::Texture m_blockTexture;
    sf::Texture m_fireWallTexture;
    sf::Texture m_shieldPowerUpTexture;
    sf::Texture m_knifeTexture;
    sf::Texture m_hamonEnemyTexture;
    sf::Texture m_fireEnemyTexture;
    sf::Texture m_emeraldEnemyTexture;
    sf::Texture m_hamonBlockTexture;
    sf::Texture m_fireBlockTexture;
    sf::Texture m_emeraldBlockTexture;
};

#endif //JOJO_RUN_FACTORY_H

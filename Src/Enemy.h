//
// Created by angiolo99 on 29/01/20.
//

#ifndef JOJO_RUN_ENEMY_H
#define JOJO_RUN_ENEMY_H

#include "Block.h"
#include <SFML/Graphics.hpp>

class Enemy : public sf::Sprite{

public:
    Enemy ();
    virtual ~Enemy() = default;
    virtual std::unique_ptr<Block> SpecialAction() = 0;
    float getSpeed() const;
    void setSpeed(float speed);
    int getDamage() const;
    void setDamage(int damage);
    void setIsMovingEnemy(bool isMovingEnemy);
    bool getIsMovingEnemy() const;
    sf::FloatRect getEnemyBounds() const { return enemy.getGlobalBounds(); }

private:
    float speed = 0.2;
    int damage = 90;
    bool isMovingEnemy;

    sf::Sprite enemy;
};

#endif //JOJO_RUN_ENEMY_H

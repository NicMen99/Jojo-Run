//
// Created by angiolo99 on 29/01/20.
//

#include "Enemy.h"

Enemy::Enemy() {
    speed = 0;
}

float Enemy::getSpeed() const {
    return speed;
}

void Enemy::setSpeed(float speed) {
    Enemy::speed = speed;
}

int Enemy::getDamage() const {
    return damage;
}

void Enemy::setDamage(int damage) {
    Enemy::damage = damage;
}

void Enemy::setIsMovingEnemy(bool isMovingEnemy) {
    isMovingEnemy = true;
}

bool Enemy::getIsMovingEnemy() const {
    return isMovingEnemy;
}







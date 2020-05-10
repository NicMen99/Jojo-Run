//
// Created by angiolo99 on 29/01/20.
//

#include "Enemy.h"

Enemy::Enemy() {
    Hit = false;
    speed = 0;
}

bool Enemy::getHit() const {
    return Hit;
}

float Enemy::getSpeed() const {
    return speed;
}

void Enemy::setSpeed(float speed) {
    speed = 0.2;
}

int Enemy::getDamage() const {
    return damage;
}

void Enemy::setDamage(int damage) {
    damage = 90;
}







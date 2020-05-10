//
// Created by angiolo99 on 29/01/20.
//
#include "Shield.h"

int Shield::getHp() const {
    return hp;
}

void Shield::setHp(int hp) {
    hp = 100;
}

bool Shield::getisShield() const {
    return isShield;
}

void Shield::setIsShield(bool isShield) {
    isShield = true;
}

Shield::Shield() {
    isShield = false;
    hp = 0;
}


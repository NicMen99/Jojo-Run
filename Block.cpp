//
// Created by angiolo99 on 23/01/20.
//
#include "Block.h"

Block::Block() {
    isMovingBlock = false;
}

bool Block::getIsMovingBlock() const {
    return isMovingBlock;
}

float Block::getBlockSpeedX() const {
    return blockSpeedX;
}

void Block::setIsMovingBlock() {
    isMovingBlock = true;
}

int Block::getDamageB() const {
    return damageB;
}

void Block::setDamageB(int damageB) {
    Block::damageB = damageB;
}

void Block::setBlockSpeedX(float blockSpeedX) {
    Block::blockSpeedX = blockSpeedX;
}



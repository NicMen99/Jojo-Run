//
// Created by angiolo99 on 29/01/20.
//

#include "EmeraldEnemy.h"

std::unique_ptr<Block> EmeraldEnemy::SpecialAction() {
    std::unique_ptr<Block> result = std::unique_ptr<Block>(new Block);
    result->setIsMovingBlock();
    result->setScale(0.25, 0.25);
    result->setDamageB(100);
    result->setTexture(emeraldBlockTexture);
    return result;
}


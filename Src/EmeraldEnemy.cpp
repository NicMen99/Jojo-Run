//
// Created by angiolo99 on 29/01/20.
//

#include "EmeraldEnemy.h"

std::unique_ptr<Block> EmeraldEnemy::SpecialAction() {
    std::unique_ptr<Block> block = std::unique_ptr<Block>(new Block);
    block->init("emeraldBlockTexture", {1, 0}, {0.25, 0.25} );
    block->setDamageB(100);
    return block;
}


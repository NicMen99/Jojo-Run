//
// Created by angiolo99 on 29/01/20.
//

#include "HamonEnemy.h"

std::unique_ptr<Block> HamonEnemy::SpecialAction() {
    std::unique_ptr<Block> block = std::unique_ptr<Block>(new Block);
    block->init("hamonBlockTexture", {1, 0}, {0.25, 0.25} );
    block->setDamageB(100);
    return block;
}

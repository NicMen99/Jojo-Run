//
// Created by angiolo99 on 29/01/20.
//

#include "FireEnemy.h"

std::unique_ptr<Block> FireEnemy::SpecialAction() {
    std::unique_ptr<Block> block = std::unique_ptr<Block>(new Block);
    block->init("fireBlockTexture", {1, 0}, {0.25, 0.25} );
    block->setDamageB(100);
    return block;
}

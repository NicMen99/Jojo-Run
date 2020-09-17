//
// Created by angiolo99 on 29/01/20.
//

#ifndef JOJO_RUN_FIREENEMY_H
#define JOJO_RUN_FIREENEMY_H

#include "Enemy.h"
#include <SFML/Graphics.hpp>

class FireEnemy : public Enemy{
public:
    std::unique_ptr<Block> SpecialAction() override;

private:
    sf::Texture fireBlockTexture;
};

#endif //JOJO_RUN_FIREENEMY_H

//
// Created by angiolo99 on 29/01/20.
//

#ifndef JOJO_RUN_HAMONENEMY_H
#define JOJO_RUN_HAMONENEMY_H

#include "Enemy.h"
#include <SFML/Graphics.hpp>

class HamonEnemy : public Enemy{
public:
    std::unique_ptr<Block> SpecialAction() override;

private:
    sf::Texture hamonBlockTexture;
};

#endif //JOJO_RUN_HAMONENEMY_H

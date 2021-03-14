//
// Created by angiolo99 on 23/01/20.
//

#ifndef JOJO_RUN_BLOCK_H
#define JOJO_RUN_BLOCK_H

#include "Obstacle.h"
#include <SFML/Graphics.hpp>

class Block final: public Obstacle {

public:
    explicit Block(std::string id);
    ~Block() override = default;
    void init(const std::string &texture_name, sf::Vector2f scale, sf::Vector2f speed);

    void collision(GameObject *collider) override;
};

#endif //JOJO_RUN_BLOCK_H

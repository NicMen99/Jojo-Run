//
// Created by angiolo99 on 23/01/20.
//

#ifndef JOJO_RUN_BLOCK_H
#define JOJO_RUN_BLOCK_H

#include <SFML/Graphics.hpp>
#include "Obstacle.h"

class Block final: public Obstacle {

public:
    explicit Block(const std::string& id);
    ~Block() override;
    void init();

    void event(GameEvent event, Entity *collider) override;
};

#endif //JOJO_RUN_BLOCK_H

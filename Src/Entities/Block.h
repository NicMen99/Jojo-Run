//
// Created by angiolo99 on 23/01/20.
//

#ifndef JOJO_RUN_BLOCK_H
#define JOJO_RUN_BLOCK_H

#include "Obstacle.h"

class Block final: public Obstacle {

public:
    explicit Block(const std::string& id);
    ~Block() override;
    void init();

    void event(GameEvent event, Entity *collider) override;

private:
    void update(int32_t delta_time) override;
};

#endif //JOJO_RUN_BLOCK_H

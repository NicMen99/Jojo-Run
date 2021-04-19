//
// Created by angiolo99 on 23/01/20.
//

#ifndef JOJO_RUN_FIRE_H
#define JOJO_RUN_FIRE_H

#include "Obstacle.h"

class Fire final : public Obstacle {

public:
    explicit Fire (const std::string& id);
    ~Fire() override;
    void init();

    void update(int32_t delta_time) override;
    void event(GameEvent event, Entity *collider) override;
};

#endif //JOJO_RUN_FIRE_H

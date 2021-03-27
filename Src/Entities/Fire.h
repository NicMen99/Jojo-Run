//
// Created by angiolo99 on 23/01/20.
//

#ifndef JOJO_RUN_FIRE_H
#define JOJO_RUN_FIRE_H

#include "Obstacle.h"
#include <SFML/Graphics.hpp>

class Fire final : public Obstacle {

public:
    explicit Fire (const std::string& id);
    ~Fire() override = default;
    void init();

    void collision (Entity * collider) override;
};

#endif //JOJO_RUN_FIRE_H

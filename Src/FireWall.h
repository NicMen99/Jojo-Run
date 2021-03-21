//
// Created by angiolo99 on 23/01/20.
//

#ifndef JOJO_RUN_FIREWALL_H
#define JOJO_RUN_FIREWALL_H

#include "Obstacle.h"
#include <SFML/Graphics.hpp>

class FireWall final : public Obstacle {

public:
    explicit FireWall (const std::string& id);
    ~FireWall() override = default;
    void init();

    void collision (GameObject * collider) override;
};

#endif //JOJO_RUN_FIREWALL_H

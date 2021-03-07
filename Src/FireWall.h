//
// Created by angiolo99 on 23/01/20.
//

#ifndef JOJO_RUN_FIREWALL_H
#define JOJO_RUN_FIREWALL_H

#include "Obstacle.h"
#include <SFML/Graphics.hpp>

class FireWall final : public Obstacle {

public:
    explicit FireWall (std::string id);
    ~FireWall() = default;
    void init(const std::string &texture_name, sf::Vector2f scale, sf::Vector2f speed);

private:
    int m_damage = 15;
};

#endif //JOJO_RUN_FIREWALL_H

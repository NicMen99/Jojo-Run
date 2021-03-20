//
// Created by angiolo99 on 10/02/20.
//

#ifndef JOJO_RUN_POWERUP_H
#define JOJO_RUN_POWERUP_H

#include "GameObject.h"
#include <SFML/Graphics/Sprite.hpp>

class PowerUp : public GameObject {
public:
    explicit PowerUp(GameObjectType mtype, const std::string & name);
    ~PowerUp() = default;
    void init(const std::string &texture_name, sf::Vector2f scale, sf::Vector2f speed);

};

#endif //JOJO_RUN_POWERUP_H

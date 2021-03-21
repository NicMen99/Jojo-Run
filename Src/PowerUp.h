//
// Created by angiolo99 on 10/02/20.
//

#ifndef JOJO_RUN_POWERUP_H
#define JOJO_RUN_POWERUP_H

#include "GameObject.h"
#include <SFML/Graphics/Sprite.hpp>

class PowerUp : public GameObject {
public:
    explicit PowerUp(GameObjectType mtype, const std::string & name) :
     GameObject(GameObjectGroup::Powerup, mtype, name) {}
    ~PowerUp() override = default;

public:
    void setQuantity(int quantity) { m_quantity = quantity; }
    int getQuantity() const { return m_quantity; };

private:
    int m_quantity = 0;
};

#endif //JOJO_RUN_POWERUP_H

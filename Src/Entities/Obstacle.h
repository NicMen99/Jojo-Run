//
// Created by Niccolo on 28/02/2021.
//

#ifndef JOJO_RUN_OBSTACLE_H
#define JOJO_RUN_OBSTACLE_H

#include "Game.h"
#include "Entity.h"

class Obstacle : public Entity
{
public:
    Obstacle(GameObjectType mtype, const std::string & name) :
            Entity(GameObjectGroup::Map, mtype, name) { }
    ~Obstacle() override = default;

public:
    void setDamage(int damage) { m_damage = damage; }
    int getDamage() const { return m_damage; };

private:
    int m_damage = 0;
};


#endif //JOJO_RUN_OBSTACLE_H

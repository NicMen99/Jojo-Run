//
// Created by Niccolo on 28/02/2021.
//

#ifndef JOJO_RUN_OBSTACLE_H
#define JOJO_RUN_OBSTACLE_H

#include "Entity.h"

class Obstacle : public Entity
{
public:
    Obstacle(EntityType mtype, const std::string & name) :
            Entity(EntityGroup::Obstacle, mtype, name) { }
    ~Obstacle() override {};

    void setDamage(int damage) { m_damage = damage; }
    int getDamage() const { return m_damage; };

private:
    int m_damage = 0;
};


#endif //JOJO_RUN_OBSTACLE_H

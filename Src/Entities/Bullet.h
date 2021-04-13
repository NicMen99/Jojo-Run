//
// Created by Niccolo on 27/02/2021.
//

#ifndef JOJO_RUN_BULLET_H
#define JOJO_RUN_BULLET_H

#include "Entity.h"

class Bullet: public Entity {
public:
    Bullet(EntityType mtype, const std::string & name) :
            Entity(EntityGroup::Bullet, mtype, name) {}
    ~Bullet() override {};

    void setDamage(int damage) { m_damage = damage; }
    int getDamage() const override { return m_damage; };

private:
    int m_damage = 0;
};


#endif //JOJO_RUN_BULLET_H

//
// Created by Niccolo on 27/02/2021.
//

#ifndef JOJO_RUN_BULLET_H
#define JOJO_RUN_BULLET_H

#include "GameObject.h"

class Bullet: public GameObject {
public:
    Bullet(GameObjectType mtype, const std::string & name) :
     GameObject(GameObjectGroup::Bullet, mtype, name) {}
    ~Bullet() override = default;

public:
    void setDamage(int damage) { m_damage = damage; }
    int getDamage() const { return m_damage; };

private:
    int m_damage = 0;
};


#endif //JOJO_RUN_BULLET_H

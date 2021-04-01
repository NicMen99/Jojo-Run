//
// Created by angiolo99 on 10/02/20.
//

#ifndef JOJO_RUN_POWERUP_H
#define JOJO_RUN_POWERUP_H

#include "Entity.h"

class PowerUp : public Entity {
public:
    explicit PowerUp(EntityType mtype, const std::string & name) :
            Entity(EntityGroup::Powerup, mtype, name) {}
    ~PowerUp() override {};

    void setQuantity(int quantity) { m_quantity = quantity; }
    int getQuantity() const { return m_quantity; };

private:
    int m_quantity = 0;
};

#endif //JOJO_RUN_POWERUP_H

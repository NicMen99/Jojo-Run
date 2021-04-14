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

    void setGain(int quantity) { m_gain = quantity; }
    int getGain() const override { return m_gain; };

private:
    int m_gain = 0;
};

#endif //JOJO_RUN_POWERUP_H

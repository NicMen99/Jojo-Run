//
// Created by Niccolo on 14/03/2021.
//

#ifndef JOJO_RUN_FIREBALL_H
#define JOJO_RUN_FIREBALL_H

#include "Entities/Bullet.h"

class FireBall final: public Bullet{
public:
    explicit FireBall(std::string id);
    ~FireBall() override;
    void init();

private:
    void update(int32_t delta_time) override;
    void event(GameEvent event, Entity *collider) override;
};


#endif //JOJO_RUN_FIREBALL_H

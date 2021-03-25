//
// Created by Niccolo on 14/03/2021.
//

#ifndef JOJO_RUN_FIREBALL_H
#define JOJO_RUN_FIREBALL_H

#include "Bullet.h"

class FireBall final: public Bullet{
public:
    explicit FireBall(std::string id);
    ~FireBall() override = default;
    void init();

private:
    void update(int32_t delta_time) override;
    void collision(GameObject* collider) override;
};


#endif //JOJO_RUN_FIREBALL_H

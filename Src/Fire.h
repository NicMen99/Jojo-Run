//
// Created by Niccolo on 14/03/2021.
//

#ifndef JOJO_RUN_FIRE_H
#define JOJO_RUN_FIRE_H

#include "Bullet.h"

class Fire final: public Bullet{
public:
    explicit Fire(std::string id);
    ~Fire() override = default;

private:
    void update(int32_t delta_time) override;
    void collision(GameObject* collider) override;
};


#endif //JOJO_RUN_FIRE_H

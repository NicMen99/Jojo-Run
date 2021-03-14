//
// Created by Niccolo on 14/03/2021.
//

#ifndef JOJO_RUN_EMERALD_H
#define JOJO_RUN_EMERALD_H

#include "Bullet.h"

class Emerald final: public Bullet{
public:
    explicit Emerald(std::string id);
    ~Emerald() override = default;

private:
    void update(int32_t delta_time) override;
    void collision(GameObject* collider) override;
};


#endif //JOJO_RUN_EMERALD_H

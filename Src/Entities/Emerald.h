//
// Created by Niccolo on 14/03/2021.
//

#ifndef JOJO_RUN_EMERALD_H
#define JOJO_RUN_EMERALD_H

#include "Entities/Bullet.h"

class Emerald final: public Bullet{
public:
    explicit Emerald(const std::string& id);
    ~Emerald() override;
    void init();

    void update(int32_t delta_time) override;
    void event(GameEvent event, Entity *collider) override;
};


#endif //JOJO_RUN_EMERALD_H

//
// Created by angiolo99 on 29/01/20.
//

#ifndef JOJO_RUN_KNIFE_H
#define JOJO_RUN_KNIFE_H

#include <SFML/Graphics.hpp>
#include "Entities/Bullet.h"

class Knife final:  public Bullet
{
public:
    explicit Knife (std::string id);
    ~Knife() override;
    void init();

private:
    void update(int32_t delta_time) override;
    void event(GameEvent event, Entity *collider) override;
};

#endif //JOJO_RUN_KNIFE_H

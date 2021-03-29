//
// Created by Niccolo on 28/02/2021.
//

#ifndef JOJO_RUN_WEAPON_H
#define JOJO_RUN_WEAPON_H

#include "Entities/PowerUp.h"

class Weapon final : public PowerUp {
public:

    explicit Weapon (std::string id);
    ~Weapon() override = default;
    void init();

public:
    void event(GameEvent event, Entity *collider) override;

private:
    int m_knives = 2;
};


#endif //JOJO_RUN_WEAPON_H

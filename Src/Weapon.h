//
// Created by Niccolo on 28/02/2021.
//

#ifndef JOJO_RUN_WEAPON_H
#define JOJO_RUN_WEAPON_H

#include "PowerUp.h"

class Weapon final : public PowerUp {
public:

    explicit Weapon (std::string id);
    ~Weapon() = default;

    void collision(GameObject * collider) override;

public:
    int collect() const { return m_knives; }

private:
    int m_knives = 2;
};


#endif //JOJO_RUN_WEAPON_H

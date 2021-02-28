//
// Created by Niccolo on 28/02/2021.
//

#ifndef JOJO_RUN_WEAPON_H
#define JOJO_RUN_WEAPON_H

#include "PowerUp.h"

class Weapon final : public PowerUp {
public:
    explicit Weapon (std::string id);
    ~Weapon()  override = default;
};


#endif //JOJO_RUN_WEAPON_H

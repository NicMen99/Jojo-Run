//
// Created by angiolo99 on 29/01/20.
//

#include "Knife.h"

int Knife::getAmmo() const {
    return ammo;
}

void Knife::setAmmo(int ammo) {
    Knife::ammo = ammo;
}

Knife::Knife() {
    ammo = 0;
}




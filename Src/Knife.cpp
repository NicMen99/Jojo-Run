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
    isKnife = false;
}

bool Knife::getHisKnife() const {
    return isKnife;
}

void Knife::setHisKnife(bool isKnife) {
    isKnife = true;
}



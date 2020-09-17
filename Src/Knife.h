//
// Created by angiolo99 on 29/01/20.
//

#ifndef JOJO_RUN_KNIFE_H
#define JOJO_RUN_KNIFE_H

#include <SFML/Graphics.hpp>
#include "PowerUp.h"

class Knife :  public PowerUp {
public:
    Knife ();
    ~Knife() final = default;

    int getAmmo() const;
    void setAmmo(int ammo);
    bool getHisKnife() const;
    void setHisKnife(bool isKnife);

private:
    int ammo = 4;
    bool isKnife;
};

#endif //JOJO_RUN_KNIFE_H

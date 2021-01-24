//
// Created by angiolo99 on 29/01/20.
//
#ifndef JOJO_RUN_SHIELD_H
#define JOJO_RUN_SHIELD_H

#include <SFML/Graphics.hpp>
#include "PowerUp.h"

class Shield : public PowerUp {
public:
    Shield ();
    ~Shield() = default;

    int getHp() const;
    void setHp(int hp);

private:
    int hp = 100;

};

#endif //JOJO_RUN_SHIELD_H

//
// Created by angiolo99 on 29/01/20.
//
#ifndef JOJO_RUN_SHIELD_H
#define JOJO_RUN_SHIELD_H

#include <SFML/Graphics.hpp>
#include "PowerUp.h"

class Shield : public PowerUp, public sf::Sprite {
public:
    Shield ();
    ~Shield() = default;

    int getHp() const;
    void setHp(int hp);
    bool getisShield() const;
    void setIsShield(bool isShield);

private:
    int hp = 100;
    bool isShield;

};

#endif //JOJO_RUN_SHIELD_H

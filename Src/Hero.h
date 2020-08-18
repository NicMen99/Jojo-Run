//
// Created by angiolo99 on 23/01/20.
//

#ifndef JOJO_RUN_HERO_H
#define JOJO_RUN_HERO_H

#include "Subject.h"
#include <SFML/Graphics.hpp>

class Hero : public sf::Sprite, public Subject{
public:
    //domani continuo ad aggiungere roba
private:
    void death() { isDead = true};
    int hp = 300;
    bool isDead = false;
};

#endif //JOJO_RUN_HERO_H

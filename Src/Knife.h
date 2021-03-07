//
// Created by angiolo99 on 29/01/20.
//

#ifndef JOJO_RUN_KNIFE_H
#define JOJO_RUN_KNIFE_H

#include <SFML/Graphics.hpp>
#include "Bullet.h"

class Knife final:  public Bullet
{
public:
    explicit Knife (std::string id);
    ~Knife() = default;
};

#endif //JOJO_RUN_KNIFE_H

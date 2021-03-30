//
// Created by Niccolo on 20/02/2021.
//

#ifndef JOJO_RUN_BACKGROUND_H
#define JOJO_RUN_BACKGROUND_H


#include "Entity.h"
#include <SFML/Graphics.hpp>


class Background final: public Entity
{
public:
    explicit Background(std::string id);
    ~Background() override;
    void init(EntityType type);
};


#endif //JOJO_RUN_BACKGROUND_H

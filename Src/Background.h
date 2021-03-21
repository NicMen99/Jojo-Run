//
// Created by Niccolo on 20/02/2021.
//

#ifndef JOJO_RUN_BACKGROUND_H
#define JOJO_RUN_BACKGROUND_H


#include "GameObject.h"
#include <SFML/Graphics.hpp>


class Background final: public GameObject
{
public:
    explicit Background(std::string id);
    ~Background() override = default;
    void init(GameObjectType type);
};


#endif //JOJO_RUN_BACKGROUND_H

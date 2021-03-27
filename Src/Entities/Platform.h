//
// Created by Niccolo on 25/02/2021.
//

#ifndef JOJO_RUN_PLATFORM_H
#define JOJO_RUN_PLATFORM_H

#include <SFML/Graphics.hpp>
#include "Entity.h"


class Platform : public Entity {
public:
    Platform(std::string id);
    ~Platform() override = default;
    void init();

};


#endif //JOJO_RUN_PLATFORM_H
//
// Created by Niccolo on 25/02/2021.
//

#ifndef JOJO_RUN_PLATFORM_H
#define JOJO_RUN_PLATFORM_H

#include <SFML/Graphics.hpp>
#include "GameObject.h"

class Platform : public GameObject {
public:
    explicit Platform(std::string id);
    ~Platform() = default;
    void init(const std::string& texture_name, sf::Vector2f speed);

};


#endif //JOJO_RUN_PLATFORM_H

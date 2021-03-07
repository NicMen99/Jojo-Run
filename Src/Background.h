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
    ~Background() = default;
    void init(const std::string & texture_name, bool repeated, sf::Vector2f scale, sf::Vector2f speed);

private:
    sf::Sprite m_sprite;
};


#endif //JOJO_RUN_BACKGROUND_H

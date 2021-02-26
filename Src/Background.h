//
// Created by Niccolo on 20/02/2021.
//

#ifndef JOJO_RUN_BACKGROUND_H
#define JOJO_RUN_BACKGROUND_H

#include "GameObject.h"
#include <SFML/Graphics.hpp>

class Background: public GameObject{
public:
    Background()=default;
    virtual ~Background()=default;

    void init(const std::string &texture_name, sf::Vector2f speed, bool repeated=false, const sf::Vector2f &scale={1,1});
    void update(int32_t delta_time) override;
    void render(sf::RenderWindow& window) override;

private:
    sf::Sprite m_sprite;
};


#endif //JOJO_RUN_BACKGROUND_H

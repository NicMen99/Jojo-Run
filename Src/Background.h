//
// Created by Niccolo on 20/02/2021.
//

#ifndef JOJO_RUN_BACKGROUND_H
#define JOJO_RUN_BACKGROUND_H

#include <SFML/Graphics.hpp>

class Background{
public:
    Background()=default;
    virtual ~Background()=default;

    void init(const std::string &texture_name, bool repeated=false, const sf::Vector2f &scale={1,1});
    void update(sf::Vector2f offset);
    void render(sf::RenderWindow& window);

private:
    sf::Sprite m_sprite;
};


#endif //JOJO_RUN_BACKGROUND_H

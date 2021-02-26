//
// Created by angiolo99 on 23/01/20.
//

#ifndef JOJO_RUN_BLOCK_H
#define JOJO_RUN_BLOCK_H

#include "GameObject.h"
#include <SFML/Graphics.hpp>

class Block final: public GameObject {

public:
    Block () = default;
    virtual ~Block() = default;
    void init(const std::string &texture_name, sf::Vector2f speed={0, 0}, sf::Vector2f scale={1,1});
    void update(int32_t delta_time) override;
    void render(sf::RenderWindow & window) override;

    void setDamageB(int damageB);
    int getDamageB() const;
    void setPosition(sf::Vector2f position);
    sf::Vector2f getPosition() const;
    sf::FloatRect getGlobalBounds() const;

private:
    sf::Sprite m_sprite;
    int m_damageB = 70;
};

#endif //JOJO_RUN_BLOCK_H

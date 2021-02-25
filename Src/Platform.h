//
// Created by Niccolo on 25/02/2021.
//

#ifndef JOJO_RUN_PLATFORM_H
#define JOJO_RUN_PLATFORM_H

#include <SFML/Graphics.hpp>
#include "GameObject.h"

class Platform : public GameObject {
public:
    Platform() = default;
    ~Platform() = default;

    void init(const std::string& texture_name, sf::Vector2f position, sf::Vector2f speed);
    void update() override;
    void render(sf::RenderWindow& window) override;

    int getMSpawnPoint() const;
    void setMSpawnPoint(int mSpawnPoint);
    sf::FloatRect getMBounds() const override{return m_sprite.getGlobalBounds();}

private:
    sf::Sprite m_sprite;
    int m_spawn_point;
    int m_id;
};


#endif //JOJO_RUN_PLATFORM_H

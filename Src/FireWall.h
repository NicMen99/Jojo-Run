//
// Created by angiolo99 on 23/01/20.
//

#ifndef JOJO_RUN_FIREWALL_H
#define JOJO_RUN_FIREWALL_H

#include <SFML/Graphics.hpp>

class FireWall{

public:
    FireWall () = default;
    ~FireWall() = default;
    void init(const std::string &texture_name, sf::Vector2f speed, sf::Vector2f scale);
    void update(){m_sprite.move(-m_fireWallSpeedX);}
    void render(sf::RenderWindow &window);

    bool getIsMovingFW() const;
    sf::Vector2f getFWSpeed() const;
    int getDamageFW() const;
    sf::Vector2f getPosition() const;
    sf::FloatRect getGlobalBounds() const;

    void setFireWallSpeedX(sf::Vector2f fireWallSpeedX);
    void setDamageFW(int damageFW);
    void setPosition(sf::Vector2f position);


private:
    int m_damageFW = 15;
    sf::Vector2f m_fireWallSpeedX = {0.8,0};
    sf::Sprite m_sprite;
};

#endif //JOJO_RUN_FIREWALL_H

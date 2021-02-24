//
// Created by angiolo99 on 23/01/20.
//

#ifndef JOJO_RUN_BLOCK_H
#define JOJO_RUN_BLOCK_H

#include <SFML/Graphics.hpp>

class Block final {

public:
    Block () = default;
    virtual ~Block() = default;
    void init(const std::string &texture_name, sf::Vector2f speed={0, 0}, sf::Vector2f scale={1,1});
    void update(){m_sprite.move(-m_speed);}
    void render(sf::RenderWindow & window);

    void move(sf::Vector2f offset) { m_sprite.move(offset);}

    bool getIsMovingBlock() const;
    float getBlockSpeedX() const;
    void setBlockSpeedX(float blockSpeedX);
    void setDamageB(int damageB);
    int getDamageB() const; //necessario?
    void setPosition(sf::Vector2f position);
    sf::Vector2f getPosition() const;
    sf::FloatRect getGlobalBounds() const;

private:
    sf::Sprite m_sprite;
    sf::Vector2f m_speed={0.8, 0};
    int damageB = 50;
};

#endif //JOJO_RUN_BLOCK_H

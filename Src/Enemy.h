//
// Created by angiolo99 on 29/01/20.
//

#ifndef JOJO_RUN_ENEMY_H
#define JOJO_RUN_ENEMY_H

#include "Block.h"
#include <SFML/Graphics.hpp>

class Enemy {

public:
    Enemy () = default;
    virtual ~Enemy() = default;
    void init(const std::string &texture_name, sf::Vector2f speed, sf::Vector2f scale);
    void update(){m_sprite.move(-m_speed);}
    void render(sf::RenderWindow & window);

    virtual std::unique_ptr<Block> SpecialAction() = 0;
    sf::Vector2f getSpeed() const;
    void setSpeed(sf::Vector2f speed);
    int getDamage() const;
    void setDamage(int damage);
    void setIsMovingEnemy(bool isMovingEnemy);
    bool getIsMovingEnemy() const;
    sf::Vector2f getEnemyPosition() const{return m_sprite.getPosition(); }
    void setEnemyPosition(sf::Vector2f position);
    sf::FloatRect getEnemyBounds() const { return m_sprite.getGlobalBounds(); }

private:
    sf::Vector2f m_speed = {0, 0};
    int m_damage = 90;
    bool m_isMovingEnemy = true; //necessario?

    sf::Sprite m_sprite;
};

#endif //JOJO_RUN_ENEMY_H

//
// Created by angiolo99 on 29/01/20.
//

#ifndef JOJO_RUN_ENEMY_H
#define JOJO_RUN_ENEMY_H


#include <SFML/Graphics.hpp>
#include "GameObject.h"

class Bullet;

class Enemy: public GameObject {

public:
    Enemy(GameObjectType mtype, const std::string & name);
    ~Enemy() override = default;
    void init(const std::string & texture_name, sf::Vector2f scale, sf::Vector2f speed, int damage);

public:
    virtual std::unique_ptr<Bullet> SpecialAction() = 0;
    int getDamage() const { return m_damage; };

private:
    sf::Sprite m_sprite;
    int m_damage = 90;
};


#endif //JOJO_RUN_ENEMY_H

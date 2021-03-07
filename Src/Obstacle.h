//
// Created by Niccolo on 28/02/2021.
//

#ifndef JOJO_RUN_OBSTACLE_H
#define JOJO_RUN_OBSTACLE_H

#include "Game.h"
#include "GameObject.h"

class Obstacle : public GameObject
{
public:
    Obstacle(GameObjectType mtype, const std::string & name);
    ~Obstacle() = default;
    void init(const std::string &texture_name, sf::Vector2f scale, int damage);

public:
    int getDamage() const { return m_damage; };

private:
    sf::Sprite m_sprite;
    int m_damage = 70;

};


#endif //JOJO_RUN_OBSTACLE_H

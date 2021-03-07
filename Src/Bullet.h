//
// Created by Niccolo on 27/02/2021.
//

#ifndef JOJO_RUN_BULLET_H
#define JOJO_RUN_BULLET_H

#include "GameObject.h"

class Bullet: public GameObject {
public:
    Bullet(GameObjectType mtype, const std::string & name);
    ~Bullet() = default;
    void init(const std::string &texture_name, sf::Vector2f scale, sf::Vector2f speed, int damage);

private:
    sf::Sprite m_sprite;
    int m_damage = 100;
};


#endif //JOJO_RUN_BULLET_H

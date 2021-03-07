//
// Created by angiolo99 on 29/01/20.
//

#ifndef JOJO_RUN_ENEMY_H
#define JOJO_RUN_ENEMY_H


#include <SFML/Graphics.hpp>
#include "GameObject.h"

class Bullet;

class Enemy: public GameObject {
    enum State {Alive, Dying, Dead};

public:
    Enemy(GameObjectType mtype, const std::string & name);
    ~Enemy() = default;
    void init(const std::string & texture_name, sf::Vector2f scale, sf::Vector2f speed, int damage);

    void update(int32_t delta_time) override;
    void collision(GameObject *collider) override;

public:
    virtual std::unique_ptr<Bullet> SpecialAction() = 0;
    int getDamage() const { return m_damage; };

private:
    sf::Sprite m_sprite;
    State m_state = State::Alive;
    int m_damage = 90;
};


#endif //JOJO_RUN_ENEMY_H

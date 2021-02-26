//
// Created by angiolo99 on 29/01/20.
//

#ifndef JOJO_RUN_ENEMY_H
#define JOJO_RUN_ENEMY_H

#include "Block.h"
#include <SFML/Graphics.hpp>

class Enemy: public GameObject {

public:
    Enemy () = default;
    virtual ~Enemy() = default;
    void init(const std::string &texture_name, sf::Vector2f speed, sf::Vector2f scale);
    void update(int32_t delta_time) override;
    void render(sf::RenderWindow & window) override;

    virtual std::unique_ptr<Block> SpecialAction() = 0;
    int getDamage() const;
    void setDamage(int damage);
    sf::Vector2f getEnemyPosition() const{return m_sprite.getPosition(); }
    void setEnemyPosition(sf::Vector2f position);
    sf::FloatRect getEnemyBounds() const { return m_sprite.getGlobalBounds(); }

private:
    int m_damage = 90;
    sf::Sprite m_sprite;
};

#endif //JOJO_RUN_ENEMY_H

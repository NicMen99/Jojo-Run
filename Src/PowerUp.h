//
// Created by angiolo99 on 10/02/20.
//

#ifndef JOJO_RUN_POWERUP_H
#define JOJO_RUN_POWERUP_H

#include "GameObject.h"
#include <SFML/Graphics/Sprite.hpp>

class PowerUp : public GameObject{
public:
    PowerUp() = default;
    virtual ~PowerUp() = default;
    void init(const std::string &texture_name, sf::Vector2f speed, sf::Vector2f scale, bool isShield = false, bool isKnife = false, bool isThrown = false);
    void update(int32_t delta_time) override;
    void render(sf::RenderWindow &window) override;

    void setIsShield(bool isShield);
    void setIsKnife(bool isKnife);
    void setIsThrowable(bool isThrowable);
    void setPosition(sf::Vector2f position);

    bool getisShield() const;
    bool getisKnife() const;
    bool getisThrowable() const;
    sf::Vector2f getPosition() const{return  m_sprite.getPosition();}
    sf::FloatRect getGlobalBounds() const{return m_sprite.getGlobalBounds();}

private:
    bool m_isShield = false;
    bool m_isKnife = false;
    bool m_isThrowable = false;

protected:
    sf::Sprite m_sprite;
};

#endif //JOJO_RUN_POWERUP_H

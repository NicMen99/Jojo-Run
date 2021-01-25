//
// Created by angiolo99 on 10/02/20.
//

#ifndef JOJO_RUN_POWERUP_H
#define JOJO_RUN_POWERUP_H

#include <SFML/Graphics/Sprite.hpp>

class PowerUp : public sf::Sprite{
public:
    PowerUp();
    ~PowerUp() = default;

    bool getIsMovingPu() const;
    void setIsMovingPu(bool isMovingPu);
    float getSpeedPux() const;
    void setSpeedPux(float speedPUX);

    void setIsShield(bool isShield);
    void setIsKnife(bool isKnife);
    void setIsThrowable(bool isThrowable);

    bool getisShield() const;
    bool getisKnife() const;
    bool getisThrowable() const;

private:
    bool isMovingPU;
    float speedPUX = 0.9;
    bool isShield = false;
    bool isKnife = false;
    bool isThrowable = false;
};

#endif //JOJO_RUN_POWERUP_H

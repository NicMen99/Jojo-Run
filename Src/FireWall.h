//
// Created by angiolo99 on 23/01/20.
//

#ifndef JOJO_RUN_FIREWALL_H
#define JOJO_RUN_FIREWALL_H

#include <SFML/Graphics.hpp>

class FireWall : public sf::Sprite {

public:
    FireWall ();
    ~FireWall() final = default;

    bool getIsMovingFW() const;
    float getFWSpeedX() const;
    void setIsMovingFW(bool isMovingFW);
    void setFireWallSpeedX(float fireWallSpeedX);
    void setDamageFW(int damageFW);
    int getDamageFW() const;

private:
    int damageFW = 15;
    bool isMovingFW;
    float fireWallSpeedX = 0.8;
};

#endif //JOJO_RUN_FIREWALL_H

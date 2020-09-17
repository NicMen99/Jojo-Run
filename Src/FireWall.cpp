//
// Created by angiolo99 on 23/01/20.
//

#include "FireWall.h"

FireWall::FireWall() {
    isMovingFW = false;
}

bool FireWall::getIsMovingFW() const {
    return isMovingFW;
}

float FireWall::getFWSpeedX() const {
    return fireWallSpeedX;
}

void FireWall::setIsMovingFW() {
    isMovingFW = true;
}

int FireWall::getDamageFW() const {
    return damageFW;
}

void FireWall::setDamageFW(int damageFW) {
    FireWall::damageFW = damageFW;
}

void FireWall::setFireWallSpeedX(float fireWallSpeedX) {
    FireWall::fireWallSpeedX = fireWallSpeedX;
}


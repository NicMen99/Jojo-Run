//
// Created by angiolo99 on 10/02/20.
//

#include "PowerUp.h"

bool PowerUp::getIsMovingPu() const {
    return isMovingPU;
}

void PowerUp::setIsMovingPu(bool isMovingPu) {
    isMovingPU = isMovingPu;
}

float PowerUp::getSpeedPux() const {
    return speedPUX;
}

void PowerUp::setSpeedPux(float speedPUX) {
    speedPUX = speedPUX;
}

PowerUp::PowerUp() {
    isMovingPU = false;
}

void PowerUp::setIsShield(bool isShield) {
    PowerUp::isShield = isShield;
}

void PowerUp::setIsKnife(bool isKnife) {
    PowerUp::isKnife = isKnife;
}

void PowerUp::setIsThrowable(bool isThrowable) {
    PowerUp::isThrowable = isThrowable;
}

bool PowerUp::getisShield() const {
    return isShield;
}

bool PowerUp::getisKnife() const {
    return isKnife;
}

bool PowerUp::getisThrowable() const {
    return isThrowable;
}

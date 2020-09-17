//
// Created by angiolo99 on 10/02/20.
//

#include "PowerUp.h"

bool PowerUp::getIsMovingPu() const {
    return isMovingPU;
}

void PowerUp::setIsMovingPu(bool isMovingPu) {
    isMovingPU = true;
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

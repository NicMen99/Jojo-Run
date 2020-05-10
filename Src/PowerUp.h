//
// Created by angiolo99 on 10/02/20.
//

#ifndef JOJO_RUN_POWERUP_H
#define JOJO_RUN_POWERUP_H

class PowerUp {
public:
    PowerUp();
    ~PowerUp() = default;

    bool isMovingPu() const;
    void setIsMovingPu(bool isMovingPu);
    float getSpeedPux() const;
    void setSpeedPux(float speedPUX);

private:
    bool isMovingPU;
    float speedPUX = 0.9;
};

#endif //JOJO_RUN_POWERUP_H

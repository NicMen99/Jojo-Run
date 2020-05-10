//
// Created by angiolo99 on 23/01/20.
//

#ifndef JOJO_RUN_BLOCK_H
#define JOJO_RUN_BLOCK_H

#include <SFML/Graphics.hpp>

class Block : public sf::Sprite {

public:
    Block ();
    ~Block() final = default;

    bool getIsMovingBlock() const;
    float getBlockSpeedX() const;
    void setIsMovingBlock();
    void setBlockSpeedX(float blockSpeedX);
    void setDamageB(int damageB);
    int getDamageB() const;

private:
    int damageB = 70;
    bool isMovingBlock;
    float blockSpeedX = 0.8;
};

#endif //JOJO_RUN_BLOCK_H

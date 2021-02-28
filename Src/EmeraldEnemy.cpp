//
// Created by angiolo99 on 29/01/20.
//

#include "Knife.h"
#include "EmeraldEnemy.h"

EmeraldEnemy::EmeraldEnemy(std::string id) :
    Enemy(GameObjectType::EmeraldEnemy, id)
{

}

std::unique_ptr<Bullet> EmeraldEnemy::SpecialAction() {
    std::unique_ptr<Bullet> bullet = std::unique_ptr<Bullet>(new Knife(""));
    bullet->init("emeraldBlockTexture", {1, 0}, {0.25, 0.25}, 100);
    return bullet;
}

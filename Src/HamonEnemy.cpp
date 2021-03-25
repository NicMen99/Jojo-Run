//
// Created by angiolo99 on 29/01/20.
//

#include "Knife.h"
#include "HamonEnemy.h"

HamonEnemy::HamonEnemy(const std::string& id) :
    Enemy(GameObjectType::HamonEnemy, id) {

}

void HamonEnemy::init() {
    auto animation = m_animator.createAnimation();
    animation->addFrame("hamonEnemyTexture", {0,0,0,0}, 1, {0,0}, true, false);
    m_animator.play();
    // setScale({-1,1});
    // m_sprite.setOrigin(+m_sprite.getTextureRect().width, 0);
    setDamage(90);
    addSound("HAMONACTION", "hamonEnemyShout");
}

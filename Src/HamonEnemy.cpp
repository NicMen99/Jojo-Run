//
// Created by angiolo99 on 29/01/20.
//

#include "Knife.h"
#include "HamonEnemy.h"

HamonEnemy::HamonEnemy(const std::string& id) :
    Enemy(GameObjectType::HamonEnemy, id) {

}

void HamonEnemy::init() {
    const std::list<Animation::FrameParams> frames = {
            {1, "hamonEnemyTexture", {0,0,0,0}, {0,0}, {true, false}}
    };
    m_animator.addAnimation("DEFAULT", frames);
    setDamage(90);
    addSound("HAMONACTION", "hamonEnemyShout");
}

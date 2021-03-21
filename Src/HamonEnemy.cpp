//
// Created by angiolo99 on 29/01/20.
//

#include "Knife.h"
#include "HamonEnemy.h"

HamonEnemy::HamonEnemy(const std::string& id) :
    Enemy(GameObjectType::HamonEnemy, id) {

}

void HamonEnemy::init() {
    addTexture("DEFAULT", {"hamonEnemyTexture", {0, 0}, true, false });
    updateSprite("DEFAULT");
    m_sprite.setOrigin(+m_sprite.getTextureRect().width, 0);
    setDamage(90);
    addSound("HAMONACTION", "hamonEnemyShout");
}

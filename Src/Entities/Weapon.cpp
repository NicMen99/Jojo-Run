//
// Created by Niccolo on 28/02/2021.
//

#include <list>
#include "AnimationManager.h"

#include "Weapon.h"

Weapon::Weapon(std::string id) :
    PowerUp(EntityType::Weapon, "Weapons")
{

}

Weapon::~Weapon() {

}

void Weapon::init() {
    const std::list<FrameParams> frames = {
            {1, "knifeTexture", {0,0,0,0}, {0,0}, {false, false}}
    };
    addAnimation("DEFAULT", frames);
    setSpeed({0.f, 0.f});
    setQuantity(2);
}

void Weapon::event(GameEvent event, Entity *collider) {
    setDestroyed();
}

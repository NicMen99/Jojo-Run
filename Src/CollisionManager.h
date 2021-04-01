//
// Created by Niccolo on 28/03/2021.
//

#ifndef JOJO_RUN_COLLISIONMANAGER_H
#define JOJO_RUN_COLLISIONMANAGER_H

#include <memory>
#include <SFML/Graphics.hpp>
class Entity;

class CollisionManager {

public:
    bool collisionCheck(Entity * item1, Entity * item2);

private:
    bool checkHeroPlatform(Entity * hero, Entity * platform);
    std::shared_ptr<sf::FloatRect> intersectionRect(Entity * hero, Entity * platform);
};


#endif //JOJO_RUN_COLLISIONMANAGER_H

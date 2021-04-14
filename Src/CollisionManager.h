//
// Created by Niccolo on 28/03/2021.
//

#ifndef JOJO_RUN_COLLISIONMANAGER_H
#define JOJO_RUN_COLLISIONMANAGER_H

#include <memory>
#include <SFML/Graphics.hpp>
class Entity;

enum class CollisionTag { None, Any, Top, Bottom, Left, Right };

class CollisionManager {

public:
    bool collisionCheck(Entity * item1, Entity * item2, CollisionTag & tag1, CollisionTag & tag2);

private:
    bool checkHeroPlatform(Entity * hero, Entity * platform, CollisionTag & hero_tag, CollisionTag & platform_tag);
    bool checkEnemyPlatform(Entity * enemy, Entity * platform, CollisionTag & enemy_tag, CollisionTag & platform_tag);
    std::shared_ptr<sf::FloatRect> intersectionRect(Entity * hero, Entity * platform);
};


#endif //JOJO_RUN_COLLISIONMANAGER_H

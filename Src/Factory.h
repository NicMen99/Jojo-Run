//
// Created by angiolo99 on 23/01/20.
//

#ifndef JOJO_RUN_FACTORY_H
#define JOJO_RUN_FACTORY_H

#include <memory>

class Entity;
enum class EntityType;

class Factory {
public:
    Factory();
    virtual ~Factory();

    virtual std::unique_ptr<Entity> createObstacle(EntityType type);
    virtual std::unique_ptr<Entity> createEnemy(EntityType type);
    virtual std::unique_ptr<Entity> createPowerUp(EntityType type);
    virtual std::unique_ptr<Entity> createBullet(EntityType type);
    virtual std::unique_ptr<Entity> createPlatform(EntityType type);
    virtual std::unique_ptr<Entity> createBackground(EntityType type);
};

#endif //JOJO_RUN_FACTORY_H

//
// Created by angiolo99 on 23/01/20.
//

#ifndef JOJO_RUN_FACTORY_H
#define JOJO_RUN_FACTORY_H

class Entity;
enum class GameObjectType;

class Factory {
public:
    Factory() = default;
    virtual ~Factory() = default;

    virtual std::unique_ptr<Entity> createObstacle(GameObjectType type);
    virtual std::unique_ptr<Entity> createEnemy(GameObjectType type);
    virtual std::unique_ptr<Entity> createPowerUp(GameObjectType type);
    virtual std::unique_ptr<Entity> createBullet(GameObjectType type);
    virtual std::unique_ptr<Entity> createPlatform(GameObjectType type);
    virtual std::unique_ptr<Entity> createBackground(GameObjectType type);
};

#endif //JOJO_RUN_FACTORY_H

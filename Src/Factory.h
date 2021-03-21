//
// Created by angiolo99 on 23/01/20.
//

#ifndef JOJO_RUN_FACTORY_H
#define JOJO_RUN_FACTORY_H

class Obstacle;
class Enemy;
class PowerUp;
class Bullet;
class Platform;
class Background;

enum class BackgroundTpe {Sky, City, SkyScrapers, Bridge};
enum class PlatformType {Short, Medium, Large};

class Factory {
public:
    Factory() = default;
    virtual ~Factory() = default;

    virtual std::unique_ptr<GameObject> createObstacle(GameObjectType type);
    virtual std::unique_ptr<GameObject> createEnemy(GameObjectType type);
    virtual std::unique_ptr<GameObject> createPowerUp(GameObjectType type);
    virtual std::unique_ptr<GameObject> createBullet(GameObjectType type);
    virtual std::unique_ptr<GameObject> createMap(PlatformType type);
    virtual std::unique_ptr<GameObject> createBackground(BackgroundTpe type);
};

#endif //JOJO_RUN_FACTORY_H

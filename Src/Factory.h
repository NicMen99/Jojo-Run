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

enum class ObstacleType {Block, Firewall};
enum class FireWallType {MovingWall};
enum class EnemyType {FireEnemy, HamonEnemy, EmeraldEnemy};
enum class PowerUpType {Shield, Weapon};
enum class PlatformType {Short, Medium, Large};
enum class BulletType {Knife};

class Factory {
public:
    Factory() = default;
    virtual ~Factory() = default;

    virtual std::unique_ptr<GameObject> createObstacle(ObstacleType type);
    virtual std::unique_ptr<GameObject> createEnemy(EnemyType type);
    virtual std::unique_ptr<GameObject> createPowerUp(PowerUpType type);
    virtual std::unique_ptr<GameObject> createBullet(BulletType type);
    virtual std::unique_ptr<GameObject> createMap(PlatformType type);
};

#endif //JOJO_RUN_FACTORY_H

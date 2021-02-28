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

    virtual std::unique_ptr<Obstacle> createObstacle(ObstacleType type);
    virtual std::unique_ptr<Enemy> createEnemy(EnemyType type);
    virtual std::unique_ptr<PowerUp> createPowerUp(PowerUpType type);
    virtual std::unique_ptr<Bullet> createBullet(BulletType type);
    virtual std::unique_ptr<Platform> createMap(PlatformType type);
};

#endif //JOJO_RUN_FACTORY_H

//
// Created by angiolo99 on 02/10/20.
//

#include "gtest/gtest.h"
#include "Game.h"

class GameTest: public ::testing::Test {
protected:
    Game game;
    Map map;
    Hero hero;
    Factory factory;
    Block block;
    FireWall wall;
    HamonEnemy en;
    FireEnemy en2;
    EmeraldEnemy en3;
    PowerUp power;
    PowerUp knifeThrown;

    std::vector<std::unique_ptr<Block>> blocks;
    std::vector<std::unique_ptr<FireWall>> firewalls;
    std::vector<std::unique_ptr<Enemy>> enemies;
    std::vector<std::unique_ptr<PowerUp>> powerups;
    std::vector<std::unique_ptr<PowerUp>> knives;

};

TEST_F(GameTest , testAssignment) {
    ASSERT_EQ(sf::Vector2f(0.9,0.8), game.getSpeed());
    ASSERT_TRUE(game.getCreationRate() <= 1.8f);
    ASSERT_TRUE(game.randomCreation() >= 0 && game.randomCreation()<=2);
    ASSERT_TRUE(game.randomPosY() >= 0 && game.randomPosY() <= game.getMaxY());
    ASSERT_TRUE(game.getHealth() == 300);
}

TEST_F(GameTest, testDeletingBlocks) {
    int blockSize = game.getBlocksSize();
    block.setPosition(-block.getGlobalBounds().width, block.getPosition().y);
    if (block.getPosition().x + block.getGlobalBounds().width < 0) {
        blocks.erase(blocks.begin());
        ASSERT_TRUE(blockSize > game.getBlocksSize());
    }
}

TEST_F(GameTest, testDeletingFireWalls) {
    int FWSize = game.getBlocksSize();
    wall.setPosition(-wall.getGlobalBounds().width, wall.getPosition().y);
    if (wall.getPosition().x + wall.getGlobalBounds().width < 0) {
        firewalls.erase(firewalls.begin());
        ASSERT_TRUE(FWSize > game.getFireWallsSize());
    }
}

TEST_F(GameTest, testDeletingEmeraldEnemy) {
    int enemySize = game.getEnemySize();
    en3.setPosition(-en3.getGlobalBounds().width, en3.getPosition().y);
    if (en3.getPosition().x + en3.getGlobalBounds().width < 0) {
        enemies.erase(enemies.begin());
        ASSERT_TRUE(enemySize > game.getEnemySize());
    }
}

TEST_F(GameTest, testDeletingHamonEnemy) {
    int enemySize = game.getEnemySize();
    en.setPosition(-en.getGlobalBounds().width, en.getPosition().y);
    if (en.getPosition().x + en.getGlobalBounds().width < 0) {
        enemies.erase(enemies.begin());
        ASSERT_TRUE(enemySize > game.getEnemySize());
    }
}

TEST_F(GameTest, testDeletingFireEnemy) {
    int enemySize = game.getEnemySize();
    en2.setPosition(-en2.getGlobalBounds().width, en2.getPosition().y);
    if (en2.getPosition().x + en2.getGlobalBounds().width < 0) {
        enemies.erase(enemies.begin());
        ASSERT_TRUE(enemySize > game.getEnemySize());
    }
}

TEST_F(GameTest, testDeletingPowerUp) {
    int PUSize = game.getPowerUpSize();
    int knifeThrownSize = game.getKnivesSize();
    power.setPosition(-power.getGlobalBounds().width, power.getPosition().y);
    knifeThrown.setPosition(-knifeThrown.getGlobalBounds().width, knifeThrown.getPosition().y);
    if (power.getPosition().x + power.getGlobalBounds().width < 0) {
        powerups.erase(powerups.begin());
        ASSERT_TRUE(PUSize > game.getPowerUpSize());
    }
    if (knifeThrown.getPosition().x + knifeThrown.getGlobalBounds().width < 0) {
        knives.erase(knives.begin());
        ASSERT_TRUE(knifeThrownSize > game.getKnivesSize());
    }
}

/*TEST_F(GameTest, testCollisionStillBlock) {
    int numHP = game.getHealth();
    std::unique_ptr<Block> block = factory.createBlock(BlockType::StillBlock);
    block->setPosition(sf::Vector2f(2*game.getMap()->getMapSize().x,game.randomPosY()));
    block->move(-game.getSpeed().x, 0);
    hero.setHeroPos(game.getMap()->getMapSize().x, -game.randomPosY());
    if (block->getGlobalBounds().intersects(hero.getHeroBounds())) {
        if (game.getIsShieldOn()) {
            ASSERT_FALSE(game.getIsCollided());
            ASSERT_FALSE(game.getIsBlockCollision());
            ASSERT_TRUE(game.getIsShieldOn());
            ASSERT_FALSE(hero.getIsDead());
        }
        else if (game.getHealth() > 0) {
            ASSERT_TRUE(game.getIsCollided());
            ASSERT_TRUE(game.getIsBlockCollision());
            ASSERT_FALSE(hero.getIsDead());
            ASSERT_EQ(numHP -70, game.getHealth());
        }
        else {
            ASSERT_TRUE(game.getIsCollided());
            ASSERT_TRUE(game.getIsBlockCollision());
            ASSERT_TRUE(hero.getIsDead());
        }
    }
}*/

TEST_F(GameTest, testCollisionMovingBlock) {
    int numHP = game.getHealth();
    std::unique_ptr<Block> block = factory.createBlock(BlockType::MovingBlock);
    block->setPosition(sf::Vector2f(2*game.getMap()->getMapSize().x,game.randomPosY()));
    block->move(-game.getSpeed().x, 0);
    hero.setHeroPos(game.getMap()->getMapSize().x, -game.randomPosY());
    if (block->getGlobalBounds().intersects(hero.getHeroBounds())) {
        if (game.getIsShieldOn()) {
            ASSERT_FALSE(game.getIsCollided());
            ASSERT_FALSE(game.getIsBlockCollision());
            ASSERT_TRUE(game.getIsShieldOn());
            ASSERT_FALSE(hero.getIsDead());
        }
        else if (game.getHealth() > 0) {
            ASSERT_TRUE(game.getIsCollided());
            ASSERT_TRUE(game.getIsBlockCollision());
            ASSERT_FALSE(hero.getIsDead());
            ASSERT_EQ(numHP -70, game.getHealth());
        }
        else {
            ASSERT_TRUE(game.getIsCollided());
            ASSERT_TRUE(game.getIsBlockCollision());
            ASSERT_TRUE(hero.getIsDead());
        }
    }
}

/*TEST_F(GameTest, testCollisionStillFirewall) {
    int numHP = game.getHealth();
    std::unique_ptr<FireWall> wall = factory.createFireWall(FireWallType::StillWall);
    wall->setPosition(sf::Vector2f(2*game.getMap()->getMapSize().x,game.randomPosY()));
    wall->move(-game.getSpeed().x, 0);
    hero.setHeroPos(game.getMap()->getMapSize().x, -game.randomPosY());
    if (wall->getGlobalBounds().intersects(hero.getHeroBounds())) {
        if (game.getIsShieldOn()) {
            ASSERT_FALSE(game.getIsCollided());
            ASSERT_FALSE(game.getIsFirewallCollision());
            ASSERT_TRUE(game.getIsShieldOn());
            ASSERT_FALSE(hero.getIsDead());
        }
        else if (game.getHealth() > 0) {
            ASSERT_TRUE(game.getIsCollided());
            ASSERT_TRUE(game.getIsFirewallCollision());
            ASSERT_FALSE(hero.getIsDead());
            ASSERT_EQ(numHP -15, game.getHealth());
        }
        else {
            ASSERT_TRUE(game.getIsCollided());
            ASSERT_TRUE(game.getIsFirewallCollision());
            ASSERT_TRUE(hero.getIsDead());
        }
    }
}*/

TEST_F(GameTest, testCollisionMovingFirewall) {
    int numHP = game.getHealth();
    std::unique_ptr<FireWall> wall = factory.createFireWall(FireWallType::MovingWall);
    wall->setPosition(sf::Vector2f(2*game.getMap()->getMapSize().x,game.randomPosY()));
    wall->move(-game.getSpeed().x, 0);
    hero.setHeroPos(game.getMap()->getMapSize().x, -game.randomPosY());
    if (wall->getGlobalBounds().intersects(hero.getHeroBounds())) {
        if (game.getIsShieldOn()) {
            ASSERT_FALSE(game.getIsCollided());
            ASSERT_FALSE(game.getIsFirewallCollision());
            ASSERT_TRUE(game.getIsShieldOn());
            ASSERT_FALSE(hero.getIsDead());
        }
        else if (game.getHealth() > 0) {
            ASSERT_TRUE(game.getIsCollided());
            ASSERT_TRUE(game.getIsFirewallCollision());
            ASSERT_FALSE(hero.getIsDead());
            ASSERT_EQ(numHP -15, game.getHealth());
        }
        else {
            ASSERT_TRUE(game.getIsCollided());
            ASSERT_TRUE(game.getIsFirewallCollision());
            ASSERT_TRUE(hero.getIsDead());
        }
    }
}

TEST_F(GameTest, testCollisionMovingEnemy) {
    int numHP = game.getHealth();
    std::unique_ptr<Enemy> enem1 = factory.createEnemy(EnemyType::EmeraldEnemy);
    enem1->setPosition(sf::Vector2f(2*game.getMap()->getMapSize().x,game.randomPosY()));
    enem1->move(-game.getSpeed().x, 0);
    std::unique_ptr<Enemy> enem2 = factory.createEnemy(EnemyType::HamonEnemy);
    enem2->setPosition(sf::Vector2f(2*game.getMap()->getMapSize().x,game.randomPosY()));
    enem2->move(-game.getSpeed().x, 0);
    std::unique_ptr<Enemy> enem3 = factory.createEnemy(EnemyType::FireEnemy);
    enem3->setPosition(sf::Vector2f(2*game.getMap()->getMapSize().x,game.randomPosY()));
    enem3->move(-game.getSpeed().x, 0);
    hero.setHeroPos(game.getMap()->getMapSize().x, -game.randomPosY());
    if (enem1->getGlobalBounds().intersects(hero.getHeroBounds())||enem2->getGlobalBounds().intersects(hero.getHeroBounds())||enem3->getGlobalBounds().intersects(hero.getHeroBounds())) {
        if (game.getIsShieldOn()) {
            ASSERT_FALSE(game.getIsCollided());
            ASSERT_FALSE(game.getIsEnemyCollision());
            ASSERT_TRUE(game.getIsShieldOn());
            ASSERT_FALSE(hero.getIsDead());
        }
        else if (game.getHealth() > 0) {
            ASSERT_TRUE(game.getIsCollided());
            ASSERT_TRUE(game.getIsEnemyCollision());
            ASSERT_FALSE(hero.getIsDead());
            ASSERT_EQ(numHP -90, game.getHealth());
        }
        else {
            ASSERT_TRUE(game.getIsCollided());
            ASSERT_TRUE(game.getIsEnemyCollision());
            ASSERT_TRUE(hero.getIsDead());
        }
    }
}

TEST_F(GameTest, testCollisionStillEnemy) {
    int numHP = game.getHealth();
    std::unique_ptr<Enemy> enem = factory.createEnemy(EnemyType::EmeraldEnemy);
    enem->setPosition(sf::Vector2f(2*game.getMap()->getMapSize().x,game.randomPosY()));
    enem->move(-game.getSpeed().x, 0);
    hero.setHeroPos(game.getMap()->getMapSize().x, -game.randomPosY());
    if (enem->getGlobalBounds().intersects(hero.getHeroBounds())) {
        if (game.getIsShieldOn()) {
            ASSERT_FALSE(game.getIsCollided());
            ASSERT_FALSE(game.getIsEnemyCollision());
            ASSERT_TRUE(game.getIsShieldOn());
            ASSERT_FALSE(hero.getIsDead());
        }
        else if (game.getHealth() > 0) {
            ASSERT_TRUE(game.getIsCollided());
            ASSERT_TRUE(game.getIsEnemyCollision());
            ASSERT_FALSE(hero.getIsDead());
            ASSERT_EQ(numHP -90, game.getHealth());
        }
        else {
            ASSERT_TRUE(game.getIsCollided());
            ASSERT_TRUE(game.getIsEnemyCollision());
            ASSERT_TRUE(hero.getIsDead());
        }
    }
}

TEST_F(GameTest, testCollisionPowerUp) {
    int knives = hero.getKnives();
    std::unique_ptr<PowerUp> shield = factory.createPowerUp(PowerUpType::Shield);
    shield->setPosition(sf::Vector2f(2*game.getMap()->getMapSize().x,game.randomPosY()));
    shield->move(-game.getSpeed().x, 0);
    std::unique_ptr<PowerUp> knife = factory.createPowerUp(PowerUpType::Knife);
    knife->setPosition(sf::Vector2f(2*game.getMap()->getMapSize().x,game.randomPosY()));
    knife->move(-game.getSpeed().x, 0);
    hero.setHeroPos(game.getMap()->getMapSize().x, -game.randomPosY());
    if (shield->getGlobalBounds().intersects(hero.getHeroBounds())) {
        ASSERT_TRUE(game.getIsCollided());
        ASSERT_TRUE(game.getIsShieldCollision());
        ASSERT_TRUE(game.getIsShieldOn());
    }
    if (knife->getGlobalBounds().intersects(hero.getHeroBounds())) {
        ASSERT_TRUE(game.getIsCollided());
        ASSERT_TRUE(game.getIsKnifeCollision());
        ASSERT_EQ(knives +2, hero.getKnives());
    }
}

TEST_F(GameTest, testCollisionThrownKnife){
    int numHP = game.getHealth();
    std::unique_ptr<Enemy> enem1 = factory.createEnemy(EnemyType::EmeraldEnemy);
    enem1->setPosition(sf::Vector2f(2*game.getMap()->getMapSize().x,game.randomPosY()));
    enem1->move(-game.getSpeed().x, 0);
    std::unique_ptr<Enemy> enem2 = factory.createEnemy(EnemyType::HamonEnemy);
    enem2->setPosition(sf::Vector2f(2*game.getMap()->getMapSize().x,game.randomPosY()));
    enem2->move(-game.getSpeed().x, 0);
    std::unique_ptr<Enemy> enem3 = factory.createEnemy(EnemyType::FireEnemy);
    enem3->setPosition(sf::Vector2f(2*game.getMap()->getMapSize().x,game.randomPosY()));
    enem3->move(-game.getSpeed().x, 0);
    /*std::unique_ptr<Enemy> enem4 = factory.createEnemy(EnemyType::StillEnemy);
    enem4->setPosition(sf::Vector2f(2*game.getMap()->getMapSize().x,game.randomPosY()));
    enem4->move(-game.getSpeed().x, 0);*/
    std::unique_ptr<PowerUp> knife = factory.createPowerUp(PowerUpType::ThrownKnife);
    knife->setPosition(sf::Vector2f(2*game.getMap()->getMapSize().x,game.randomPosY()));
    knife->move(+game.getSpeed().x, 0);
    if (knife->getGlobalBounds().intersects(enem1->getEnemyBounds())||knife->getGlobalBounds().intersects(enem2->getEnemyBounds())||knife->getGlobalBounds().intersects(enem3->getEnemyBounds())/*||knife->getGlobalBounds().intersects(enem4->getEnemyBounds())*/){
        ASSERT_TRUE(game.getIsCollided());
        ASSERT_TRUE(game.getIsKnifeThrownCollision());
        ASSERT_EQ(numHP +20, game.getHealth());
    }
}
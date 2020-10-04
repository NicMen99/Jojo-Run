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

    std::vector<std::unique_ptr<Block>> blocks;
    std::vector<std::unique_ptr<FireWall>> firewalls;
    std::vector<std::unique_ptr<Enemy>> enemies;
    std::vector<std::unique_ptr<PowerUp>> powerups;

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
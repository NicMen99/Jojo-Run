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
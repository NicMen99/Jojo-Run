//
// Created by Niccolo on 01/04/2021.
//

#include "gtest/gtest.h"
#include "Game.h"
#include "GameConfig.h"
#include "ResourceManager.h"


class TestGameConfig : public GameConfig {
public:
    void setResource(const std::string & name, const std::string & asset_path){
        m_asset_map.insert(std::make_pair(name, "TestAsset/" + asset_path));
    }
};

class ResourcesTest : public ::testing::Test{
private:
    Game * game;
public:
    ResourcesTest(){
        auto state = new GameStateMachine(State::Init);
        auto cfg   = new TestGameConfig();
        auto resm  = new ResourceManager();
        auto fact  = new Factory();
        auto scn   = new SceneManager();
        auto stats = new GameStats();
        auto score = new ScoreManager();
        game = Game::instance(state, cfg, resm, fact, scn, stats, score);
        game->init();
    }

};

TEST_F(ResourcesTest, TestExistingFont){
    dynamic_cast<TestGameConfig*>(CONFIG)->setResource("Font", "GAME_OVER.TTF");

    auto res_manager = std::unique_ptr<ResourceManager>(new ResourceManager);
    auto font = res_manager->getFont("Font");
    ASSERT_NE(font.get(), nullptr);
}

TEST_F(ResourcesTest, TestExistingTexture){
    dynamic_cast<TestGameConfig*>(CONFIG)->setResource("Texture", "Platform.png");

    auto res_manager = std::unique_ptr<ResourceManager>(new ResourceManager);
    auto texture = res_manager->getTexture("Texture");
    ASSERT_NE(texture.get(), nullptr);
}

TEST_F(ResourcesTest, TestExistingSound){
    dynamic_cast<TestGameConfig*>(CONFIG)->setResource("Sound", "gameOverSound.wav");

    auto res_manager = std::unique_ptr<ResourceManager>(new ResourceManager);
    auto sound = res_manager->getSound("Sound");
    ASSERT_NE(sound.get(), nullptr);
}

TEST_F(ResourcesTest, TestCachedFont){
    dynamic_cast<TestGameConfig*>(CONFIG)->setResource("Font", "GAME_OVER.TTF");

    auto res_manager = std::unique_ptr<ResourceManager>(new ResourceManager);
    auto font = res_manager->getFont("Font");
    auto font2 = res_manager->getFont("Font");
    ASSERT_EQ(font.get(), font2.get());
}

TEST_F(ResourcesTest, TestCachedTexture){
    dynamic_cast<TestGameConfig*>(CONFIG)->setResource("Texture", "Platform.png");

    auto res_manager = std::unique_ptr<ResourceManager>(new ResourceManager);
    auto texture = res_manager->getTexture("Texture");
    auto texture2 = res_manager->getTexture("Texture");
    ASSERT_EQ(texture.get(), texture2.get());
}

TEST_F(ResourcesTest, TestCachedSound){
    dynamic_cast<TestGameConfig*>(CONFIG)->setResource("Sound", "gameOverSound.wav");

    auto res_manager = std::unique_ptr<ResourceManager>(new ResourceManager);
    auto sound = res_manager->getSound("Sound");
    auto sound2 = res_manager->getSound("Sound");
    ASSERT_EQ(sound.get(), sound2.get());
}

TEST_F(ResourcesTest, TestNonExistingFont){
    dynamic_cast<TestGameConfig*>(CONFIG)->setResource("Font", "GAME_OVER.TTF");

    auto res_manager = std::unique_ptr<ResourceManager>(new ResourceManager);
    auto font = res_manager->getFont("Font1");
    ASSERT_EQ(font.get(), nullptr);
}

TEST_F(ResourcesTest, TestNonExistingTexture){
    dynamic_cast<TestGameConfig*>(CONFIG)->setResource("Texture", "Platform.png");

    auto res_manager = std::unique_ptr<ResourceManager>(new ResourceManager);
    auto texture = res_manager->getTexture("Texture1");
    ASSERT_EQ(texture.get(), nullptr);
}

TEST_F(ResourcesTest, TestNonExistingSound){
    dynamic_cast<TestGameConfig*>(CONFIG)->setResource("Sound", "gameOverSound.wav");

    auto res_manager = std::unique_ptr<ResourceManager>(new ResourceManager);
    auto sound = res_manager->getSound("Sound1");
    ASSERT_EQ(sound.get(), nullptr);
}

TEST_F(ResourcesTest, WrongResourceType){
    dynamic_cast<TestGameConfig*>(CONFIG)->setResource("Texture", "Platform.png");

    auto res_manager = std::unique_ptr<ResourceManager>(new ResourceManager);
    auto texture = res_manager->getSound("Texture");

    ASSERT_EQ(texture.get(), nullptr);
}
//
// Created by Niccolo on 01/04/2021.
//

#include "gtest/gtest.h"
#include "Game.h"
#include "ResourceManager.h"
#include "Mock/MockGameConfig.h"


class ResourceManagerTest : public ::testing::Test{
private:
    Game * game;
public:
    ResourceManagerTest(){
        Game::deleteInstance();
        auto state = new GameStateMachine(State::Init);
        auto cfg   = new MockGameConfig();
        auto resm  = new ResourceManager();
        auto fact  = new Factory();
        auto scn   = new SceneManager();
        auto stats = new GameStats();
        auto score = new ScoreManager();
        game = Game::instance(state, cfg, resm, fact, scn, stats, score);
        dynamic_cast<MockGameConfig*>(CONFIG)->setFontResource("Font", "Font.ttf");
        dynamic_cast<MockGameConfig*>(CONFIG)->setMapResource("Texture", "StonePlatform.png");
        dynamic_cast<MockGameConfig*>(CONFIG)->setSoundResource("Sound", "Sound.wav");
    }
};

TEST_F(ResourceManagerTest, TestExistingFont){
    auto res_manager = std::unique_ptr<ResourceManager>(new ResourceManager);
    auto font = res_manager->getFont("Font");
    ASSERT_NE(font.get(), nullptr);
}

TEST_F(ResourceManagerTest, TestExistingTexture){
    auto res_manager = std::unique_ptr<ResourceManager>(new ResourceManager);
    auto texture = res_manager->getTexture("Texture");
    ASSERT_NE(texture.get(), nullptr);
}

TEST_F(ResourceManagerTest, TestExistingSound){
    auto res_manager = std::unique_ptr<ResourceManager>(new ResourceManager);
    auto sound = res_manager->getSound("Sound");
    ASSERT_NE(sound.get(), nullptr);
}

TEST_F(ResourceManagerTest, TestCachedFont){
    auto res_manager = std::unique_ptr<ResourceManager>(new ResourceManager);
    res_manager->clearFontCache();
    auto font = res_manager->getFont("Font");
    auto font2 = res_manager->getFont("Font");
    ASSERT_EQ(font.get(), font2.get());
}

TEST_F(ResourceManagerTest, TestCachedTexture){
    auto res_manager = std::unique_ptr<ResourceManager>(new ResourceManager);
    res_manager->clearTextureCache();
    auto texture = res_manager->getTexture("Texture");
    auto texture2 = res_manager->getTexture("Texture");
    ASSERT_EQ(texture.get(), texture2.get());
}

TEST_F(ResourceManagerTest, TestCachedSound){
    auto res_manager = std::unique_ptr<ResourceManager>(new ResourceManager);
    res_manager->clearSoundCache();
    auto sound = res_manager->getSound("Sound");
    auto sound2 = res_manager->getSound("Sound");
    ASSERT_EQ(sound.get(), sound2.get());
}

TEST_F(ResourceManagerTest, TestNonExistingFont){
    dynamic_cast<MockGameConfig*>(CONFIG)->setFontResource("Font", "Font.ttf");

    auto res_manager = std::unique_ptr<ResourceManager>(new ResourceManager);
    auto font = res_manager->getFont("Font1");
    ASSERT_EQ(font.get(), nullptr);
}

TEST_F(ResourceManagerTest, TestNonExistingTexture){
    dynamic_cast<MockGameConfig*>(CONFIG)->setMapResource("Texture", "StonePlatform.png");

    auto res_manager = std::unique_ptr<ResourceManager>(new ResourceManager);
    auto texture = res_manager->getTexture("Texture1");
    ASSERT_EQ(texture.get(), nullptr);
}

TEST_F(ResourceManagerTest, TestNonExistingSound){
    dynamic_cast<MockGameConfig*>(CONFIG)->setSoundResource("Sound", "Sound.wav");

    auto res_manager = std::unique_ptr<ResourceManager>(new ResourceManager);
    auto sound = res_manager->getSound("Sound1");
    ASSERT_EQ(sound.get(), nullptr);
}

TEST_F(ResourceManagerTest, WrongResourceTypeSound){
    auto res_manager = std::unique_ptr<ResourceManager>(new ResourceManager);
    auto texture = res_manager->getSound("Font");

    ASSERT_EQ(texture.get(), nullptr);
}

TEST_F(ResourceManagerTest, WrongResourceTypeTexture){
    auto res_manager = std::unique_ptr<ResourceManager>(new ResourceManager);
    auto texture = res_manager->getTexture("Sound");

    ASSERT_EQ(texture.get(), nullptr);
}

TEST_F(ResourceManagerTest, WrongResourceTypeFont){
    auto res_manager = std::unique_ptr<ResourceManager>(new ResourceManager);
    auto texture = res_manager->getFont("Texture");
    ASSERT_EQ(texture.get(), nullptr);
}

TEST_F(ResourceManagerTest, LoadAllResources) {
    auto res_manager = std::unique_ptr<ResourceManager>(new ResourceManager);
    ASSERT_NE(RESOURCE->getTexture("PLATFORM"), nullptr);
    ASSERT_NE(RESOURCE->getTexture("PLAYER_RUN"), nullptr);
    ASSERT_NE(RESOURCE->getTexture("PLAYER_RUN_SHIELD"), nullptr);
    ASSERT_NE(RESOURCE->getTexture("PLAYER_JUMP"), nullptr);
    ASSERT_NE(RESOURCE->getTexture("PLAYER_ATTACK"), nullptr);
    ASSERT_NE(RESOURCE->getTexture("PLAYER_DEATH"), nullptr);
    ASSERT_NE(RESOURCE->getTexture("EMERALD_ENEMY_IDLE"), nullptr);
    ASSERT_NE(RESOURCE->getTexture("EMERALD_ENEMY_ATTACK"), nullptr);
    ASSERT_NE(RESOURCE->getTexture("EMERALD_ENEMY_DEATH"), nullptr);
    ASSERT_NE(RESOURCE->getTexture("HAMON_ENEMY_IDLE"), nullptr);
    ASSERT_NE(RESOURCE->getTexture("HAMON_ENEMY_ATTACK"), nullptr);
    ASSERT_NE(RESOURCE->getTexture("HAMON_ENEMY_DEATH"), nullptr);
    ASSERT_NE(RESOURCE->getTexture("FIRE_ENEMY_IDLE"), nullptr);
    ASSERT_NE(RESOURCE->getTexture("FIRE_ENEMY_ATTACK"), nullptr);
    ASSERT_NE(RESOURCE->getTexture("FIRE_ENEMY_DEATH"), nullptr);
    ASSERT_NE(RESOURCE->getTexture("LIGHTING"), nullptr);
    ASSERT_NE(RESOURCE->getTexture("FIRE"), nullptr);
    ASSERT_NE(RESOURCE->getTexture("EMERALD_BULLET"), nullptr);
    ASSERT_NE(RESOURCE->getTexture("FIRE_BULLET"), nullptr);
    ASSERT_NE(RESOURCE->getTexture("KNIFE_BULLET"), nullptr);
    ASSERT_NE(RESOURCE->getTexture("SHIELD_PWUP"), nullptr);
    ASSERT_NE(RESOURCE->getTexture("WEAPON_PWUP"), nullptr);
    ASSERT_NE(RESOURCE->getTexture("PLAYER_ICON"), nullptr);
    ASSERT_NE(RESOURCE->getTexture("SPLASH_SCREEN"), nullptr);
    ASSERT_NE(RESOURCE->getTexture("GAME_OVER_SCREEN"), nullptr);
    ASSERT_NE(RESOURCE->getFont("GAME_OVER_FONT"), nullptr);
    ASSERT_NE(RESOURCE->getFont("RETRO_GAMING_FONT"), nullptr);
    ASSERT_NE(RESOURCE->getSound("SOUND_TRACK"), nullptr);
    ASSERT_NE(RESOURCE->getSound("SOUND_TRACK2"), nullptr);
    ASSERT_NE(RESOURCE->getSound("PLAYER_ATTACK_SOUND"), nullptr);
    ASSERT_NE(RESOURCE->getSound("PLAYER_DEATH_SOUND"), nullptr);
    ASSERT_NE(RESOURCE->getSound("PLAYER_HIT_SOUND"), nullptr);
    ASSERT_NE(RESOURCE->getSound("PLAYER_SHIELD_HIT_SOUND"), nullptr);
    ASSERT_NE(RESOURCE->getSound("PLAYER_SHIELD_PICK_SOUND"), nullptr);
    ASSERT_NE(RESOURCE->getSound("EMERALD_ATTACK_SOUND"), nullptr);
    ASSERT_NE(RESOURCE->getSound("EMERALD_DEATH_SOUND"), nullptr);
    ASSERT_NE(RESOURCE->getSound("HAMON_ATTACK_SOUND"), nullptr);
    ASSERT_NE(RESOURCE->getSound("HAMON_DEATH_SOUND"), nullptr);
    ASSERT_NE(RESOURCE->getSound("FIRE_ATTACK_SOUND"), nullptr);
    ASSERT_NE(RESOURCE->getSound("FIRE_DEATH_SOUND"), nullptr);
    ASSERT_NE(RESOURCE->getSound("KEYBOARD_TICK_SOUND"), nullptr);
}


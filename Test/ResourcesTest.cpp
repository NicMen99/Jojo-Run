//
// Created by Niccolo on 01/04/2021.
//

#include "gtest/gtest.h"
#include "GameConfig.h"


class TestGameConfig : public GameConfig {
public:
    void setSceneSpeed(sf::Vector2f speed) {m_scene_speed = speed; }
    void setTextureResource(const std::string & name, const std::string & asset_path){
        m_asset_map.insert(std::make_pair(name, "TestAsset/" + asset_path));
    }
};

class ResourcesTest : public ::testing::Test{

};

TEST_F(ResourcesTest, TestExistingFont){
    ASSERT_EQ(true, false);
}

TEST_F(ResourcesTest, TestExistingTexture){
    ASSERT_EQ(true, false);
}

TEST_F(ResourcesTest, TestExistingSound){
    ASSERT_EQ(true, false);
}

TEST_F(ResourcesTest, TestCachedFont){
    ASSERT_EQ(true, false);
}

TEST_F(ResourcesTest, TestCachedTexture){
    ASSERT_EQ(true, false);
}

TEST_F(ResourcesTest, TestCachedSound){
    ASSERT_EQ(true, false);
}

TEST_F(ResourcesTest, TestNonExistingFont){
    ASSERT_EQ(true, false);
}

TEST_F(ResourcesTest, TestNonExistingTexture){
    ASSERT_EQ(true, false);
}

TEST_F(ResourcesTest, TestNonExistingSound){
    ASSERT_EQ(true, false);
}

TEST_F(ResourcesTest, WrongResourceType){
    ASSERT_EQ(true, false);
}
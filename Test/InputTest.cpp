//
// Created by Niccolo on 01/04/2021.
//
#include "gtest/gtest.h"
#include "InputManager.h"

class TestInputManager : public InputManager {
private:
    sf::Keyboard::Key m_key;
    bool keyPressed(sf::Keyboard::Key key) override {
        return m_key == key;
    }

public:
    void setKeyPressed(sf::Keyboard::Key key){
        m_key = key;
    }
};


class InputTest : public ::testing::Test {

};

TEST_F(InputTest, KeyPressed){
    ASSERT_EQ(true, false);
}

TEST_F(InputTest, KeyJustPressed){
    ASSERT_EQ(true, false);
}

TEST_F(InputTest, KeyReleased){
    ASSERT_EQ(true, false);
}

TEST_F(InputTest, KeyJustReleased){
    ASSERT_EQ(true, false);
}
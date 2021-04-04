//
// Created by Niccolo on 01/04/2021.
//
#include "gtest/gtest.h"
#include "InputManager.h"

class TestInputManager : public InputManager {
private:
    sf::Keyboard::Key m_key = sf::Keyboard::Unknown;
public:
    void setKeyPressed(sf::Keyboard::Key key){
        m_key = key;
    }

    void unSetKeyPressed(){
        m_key = sf::Keyboard::Unknown;
    }

    bool keyPressed(sf::Keyboard::Key key) override {
        return m_key == key;
    }
};


class InputTest : public ::testing::Test {

};

TEST_F(InputTest, KeyPressed){
    auto input = std::unique_ptr<TestInputManager>(new TestInputManager);
    input->setKeyPressed(sf::Keyboard::K);
    input->update();
    ASSERT_EQ(input->keyPressed(sf::Keyboard::K), true);
}

TEST_F(InputTest, KeyJustPressed){
    auto input = std::unique_ptr<TestInputManager>(new TestInputManager);
    input->registerKey(sf::Keyboard::K);
    input->setKeyPressed(sf::Keyboard::K);
    input->update();

    ASSERT_EQ(input->isKeyJustPressed(sf::Keyboard::K), true);

    input->update();
    ASSERT_EQ(input->isKeyJustPressed(sf::Keyboard::K), false);
}

TEST_F(InputTest, KeyReleased){
    auto input = std::unique_ptr<TestInputManager>(new TestInputManager);
    input->setKeyPressed(sf::Keyboard::K);
    input->update();
    input->update();
    input->unSetKeyPressed();
    input->update();

    ASSERT_EQ(input->keyPressed(sf::Keyboard::K), false);
}

TEST_F(InputTest, KeyJustReleased){
    auto input = std::unique_ptr<TestInputManager>(new TestInputManager);
    input->registerKey(sf::Keyboard::K);
    input->setKeyPressed(sf::Keyboard::K);
    input->update();
    input->update();
    input->unSetKeyPressed();
    input->update();

    ASSERT_EQ(input->isKeyJustReleased(sf::Keyboard::K), true);

    input->update();
    ASSERT_EQ(input->isKeyJustReleased(sf::Keyboard::K), false);
}
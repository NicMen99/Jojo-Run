//
// Created by Niccolo on 15/02/2021.
//

#ifndef JOJO_RUN_GAMEOVERSTATE_H
#define JOJO_RUN_GAMEOVERSTATE_H

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "ImageWidget.h"
#include "TextWidget.h"
#include "InputManager.h"
#include "AbsGameState.h"

class GameOverScene {
public:
    GameOverScene() = default;
    virtual ~GameOverScene() = default;
    void init();

public:
    void update(int32_t delta_time);
    void render(sf::RenderWindow & window);

private:
    Widget * m_root = nullptr;
};

class GameOverState: public AbsGameState{

    enum class action {UserInput, ShowRecords};

    static GameOverState* m_instance;
public:
    static GameOverState* instance();

public:
    void init() override;
    void onEnter() override;
    void onExit() override;
    void update(int32_t delta_time) override;
    void render(sf::RenderWindow &window) override;

private:
    GameOverScene m_scene;
    InputManager  m_inputManager;
};


#endif //JOJO_RUN_GAMEOVERSTATE_H

//
// Created by Niccolo on 15/02/2021.
//

#ifndef JOJO_RUN_PLAYSTATE_H
#define JOJO_RUN_PLAYSTATE_H

#include <SFML/Audio/Music.hpp>

#include "Widgets/ImageWidget.h"
#include "Widgets/TextWidget.h"
#include "Widgets/ShapeWidget.h"
#include "InputManager.h"

#include "StateMachine/AbsGameState.h"

class PlayState: public AbsGameState{

public:
    static PlayState* instance();

    void init() override;
    void onEnter() override;
    void onExit() override;
    void update(int32_t delta_time) override;
    void render(sf::RenderWindow &window) override;

private:
    void createOverlay();

    enum Action {Play, Pause};

    static PlayState* m_instance;

    Action       m_action = Action::Play;
    InputManager m_inputManager;
    sf::Music    m_music{};
    Widget *     m_root = nullptr;
};


#endif //JOJO_RUN_PLAYSTATE_H

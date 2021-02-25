//
// Created by Niccolo on 15/02/2021.
//

#ifndef JOJO_RUN_GAMEOVERSTATE_H
#define JOJO_RUN_GAMEOVERSTATE_H

#include "AbsGameState.h"

class GameOverState: public AbsGameState{
public:
    void init() override;
    void onEnter() override;
    void onExit() override;
    void update(int32_t delta_time) override;
    void render(sf::RenderWindow &window) override;

public:
    static GameOverState* instance();
private:
    static GameOverState* m_instance;
};


#endif //JOJO_RUN_GAMEOVERSTATE_H

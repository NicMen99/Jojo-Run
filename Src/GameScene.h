//
// Created by Niccolo on 27/02/2021.
//

#ifndef JOJO_RUN_GAMESCENE_H
#define JOJO_RUN_GAMESCENE_H

#include <SFML/Graphics.hpp>
#include "GameObject.h"


class GameScene
{
public:
    GameScene()=default;
    virtual ~GameScene();
    void init();
public:
    void update(int32_t delta_time);
    void render(sf::RenderWindow & window);


private:
    static void destroyObjects(std::vector<std::unique_ptr<GameObject>> & items);
    void createBackgorund();
    void createPlatform();
    void createBlocks();
    void createEnemies();
    void createPowerup();

public:
    // fino a quando non è migrato il collision manager
    std::vector<std::unique_ptr<GameObject>> m_backgrounds;
    std::vector<std::unique_ptr<GameObject>> m_platforms;
    std::vector<std::unique_ptr<GameObject>> m_blocks;
    std::vector<std::unique_ptr<GameObject>> m_enemies;
    std::vector<std::unique_ptr<GameObject>> m_powerups;
    std::vector<std::unique_ptr<GameObject>> m_bullets;
};


#endif //JOJO_RUN_GAMESCENE_H

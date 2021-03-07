//
// Created by angiolo99 on 23/08/20.
//
#include "GameStateMachine.h"
#include "GameConfig.h"
#include "GameResourceManager.h"
#include "GameScene.h"
#include "InputManager.h"
#include "Factory.h"
#include "Hero.h"
#include "Game.h"

#define DEBUG

Game* Game::m_instance = nullptr;

Game* Game::instance() {
    if(nullptr == m_instance){
        m_instance = new Game;
        m_instance->init();
    }
    return m_instance;
}

Game::Game():
    m_gameMachine(new GameStateMachine(this, State::Init)),
    m_gameConfig(*new GameConfig()),
    m_resourceManager(*new GameResourceManager()),
    m_factory(*new Factory()),
    m_scene(*new GameScene())
{
}

Game::~Game() {
}

void Game::init()
{
    m_gameConfig.init("Assets");
}

void Game::loop()
{
    m_window.create(sf::VideoMode(GC.getWindowSize().x, GC.getWindowSize().y), "JoJo Run");
    m_window.setVerticalSyncEnabled(true);
    while(m_window.isOpen()){
        while (m_window.pollEvent(m_event)) {
            if(m_event.type == sf::Event::Closed)
                m_window.close();
        }

        sf::Time elapsedTime = m_clock.restart();
#ifdef DEBUG
        if(elapsedTime > sf::milliseconds(100))
            elapsedTime = sf::milliseconds(100);
#endif
        m_accumulator += elapsedTime;

        while (m_accumulator > m_framerate) {
            m_accumulator -= m_framerate;
            m_gameMachine->exec();
            m_gameMachine->update(m_framerate.asMilliseconds());
            sf::sleep(sf::milliseconds(10));
        }

        m_window.clear();
        m_gameMachine->render(m_window);
        m_window.display();
    }
}

void Game::handleTxt() {
    scoreTxt.setFont(font);
    scoreTxt.setString("Score");
    scoreTxt.setPosition(10, 3);
    scoreTxt.setCharacterSize(40);
    scoreTxt.setFillColor(sf::Color::White);

    numScore.setFont(font);
    numScore.setString(std::to_string(score));
    numScore.setPosition(135, 3);
    numScore.setCharacterSize(40);
    numScore.setFillColor(sf::Color::White);

    lifeTxt.setFont(font);
    lifeTxt.setString("HP");
    lifeTxt.setPosition(1440, 3);
    lifeTxt.setCharacterSize(40);
    lifeTxt.setFillColor(sf::Color::White);

    numLife.setFont(font);
    numLife.setString(std::to_string(dynamic_cast<Hero*>(m_scene.m_hero.get())->getHealth()));
    numLife.setPosition(1500, 3);
    numLife.setCharacterSize(40);
    numLife.setFillColor(sf::Color::White);

    knivesTxt.setFont(font);
    knivesTxt.setString("Knives");
    knivesTxt.setPosition(1400, 38);
    knivesTxt.setCharacterSize(35);
    knivesTxt.setFillColor(sf::Color::White);

    numKnives.setFont(font);
    numKnives.setString(std::to_string(dynamic_cast<Hero*>(m_scene.m_hero.get())->getKnives()));
    numKnives.setPosition(1535, 38);
    numKnives.setCharacterSize(35);
    numKnives.setFillColor(sf::Color::White);

    bestScoreTxt.setFont(font);
    bestScoreTxt.setString("High Score: ");
    bestScoreTxt.setPosition(450, 800);
    bestScoreTxt.setCharacterSize(75);
    bestScoreTxt.setFillColor(sf::Color::White);

    scoreB.setFont(font);
    scoreB.setString("0");
    scoreB.setCharacterSize(100);
    scoreB.setFillColor(sf::Color::White);

    bestScoreNum.setFont(font);
    bestScoreNum.setString(std::to_string(bestScore));
    bestScoreNum.setPosition(1000, 850);
    bestScoreNum.setCharacterSize(100);
    bestScoreNum.setFillColor(sf::Color::White);

    bestScoreB.setFont(font);
    bestScoreB.setString("h");
    bestScoreB.setPosition(300, 600);
    bestScoreB.setCharacterSize(110);
    bestScoreB.setFillColor(sf::Color::Black);
}

/*
void Game::collision() {
    if (!isCollided) {
        for (int i = 0; i < m_scene.m_obstacles.size(); i++) {
            if (m_scene.m_obstacles[i]->getBounds().intersects(m_hero.getHeroBounds())) {
                m_hero.collisionevent();
                if (isShieldOn) {
                    controlPU.restart();
                } else if (controlPU.getElapsedTime().asSeconds() >= toll) {
                    collisionClk.restart();
                }
                if(m_scene.m_obstacles[i]->getType() == GameObjectType::Block)
                    BlockCollision = true;
                else
                    FirewallCollision = true;
                isCollided = true;
                collidedblocks = i;
            }
        }
        for (int e = 0; e < m_scene.m_enemies.size(); e++) {
            sf::FloatRect heroBounds = m_hero.getHeroBounds();
            sf::FloatRect enemyBounds = m_scene.m_enemies[e]->getBounds();
            if (m_scene.m_enemies[e]->getBounds().intersects(m_hero.getHeroBounds())) {
                m_hero.collisionevent();
                if (isShieldOn) {
                    controlPU.restart();
                } else if (controlPU.getElapsedTime().asSeconds() >= toll) {
                    collisionClk.restart();
                }
                isCollided = true;
                EnemyCollision = true;
                collidedenemies = e;
            }
        }
        for (int m = 0; m < m_scene.m_powerups.size(); m++) {
            if (m_scene.m_powerups[m]->getBounds().intersects(m_hero.getHeroBounds()) &&
                    m_scene.m_powerups[m]->getType() == GameObjectType::Shield) {
                if (controlPU.getElapsedTime().asSeconds() >= toll) {
                    ShieldPowerupCollision = true;
                    isCollided = true;
                    collidedpowerups = m;
                    collisionClk.restart();
                    shieldClk.restart();
                }
            }
            else if (m_scene.m_powerups[m]->getBounds().intersects(m_hero.getHeroBounds()) &&
                    m_scene.m_powerups[m]->getType() == GameObjectType::Knife){
                if (controlPU.getElapsedTime().asSeconds() >= toll){
                    KnivesPowerupCollision = true;
                    isCollided = true;
                    collidedknives = m;
                    collisionClk.restart();
                }
            }
        }
        for (int h = 0; h < knives.size(); h++) {
            for (int e = 0; e < m_scene.m_enemies.size(); e++){
                if (knives[h]->getBounds().intersects(m_scene.m_enemies[e]->getBounds())) {
                    if (controlPU.getElapsedTime().asSeconds() >= toll) {
                        KnifeCollision = true;
                        isCollided = true;
                        collidedknives = h;
                        collidedenemies = e;
                        collisionClk.restart();
                    }
                }
            }
        }
    }
}
*/

int Game::getMaxY() const {
    return maxY;
}

void Game::notify() {
    for (auto i = std::begin(observers); i != std::end(observers); i++)
        (*i)->event();
}

void Game::unsubscribe(Observer *o) {
    observers.remove(o);
}

void Game::subscribe(Observer *o) {
    observers.push_back(o);
}

unsigned int Game::getScore() const {
    return score;
}

int Game::getHealth() const {
    return dynamic_cast<Hero*>(m_scene.m_hero.get())->getHealth();
}

void Game::setScore(unsigned int s) {
    Game::score = s;
    notify();
}

void Game::setHealth(int hp) {
    dynamic_cast<Hero*>(m_scene.m_hero.get())->setHealth(hp);
    notify();
}

bool Game::getIsShieldOn() const {
    return isShieldOn;
}

bool Game::getIsCollided() const{
    return isCollided;
}

bool Game::getIsBlockCollision() const{
    return BlockCollision;
}

bool Game::getIsEnemyCollision() const{
    return EnemyCollision;
}

bool Game::getIsFirewallCollision() const{
    return FirewallCollision;
}

bool Game::getIsShieldCollision() const{
    return ShieldPowerupCollision;
}

bool Game::getIsKnifeCollision() const{
    return KnivesPowerupCollision;
}

bool Game::getIsKnifeThrownCollision() const{
    return KnifeCollision;
}



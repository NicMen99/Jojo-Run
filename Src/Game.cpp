//
// Created by angiolo99 on 23/08/20.
//
#include "GameStateMachine.h"
#include "GameConfig.h"
#include "GameResourceManager.h"
#include "GameScene.h"
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
    m_scene(*new GameScene()),
    m_hero(*new Hero())

{
    srand((unsigned) time(nullptr));
    maxY = static_cast<int>(m_window.getSize().y - (top + blockX));
}

Game::~Game() {
    knives.clear();
}

void Game::init()
{
    m_gameConfig.init("Assets");
}

void Game::loop()
{
    m_window.create(sf::VideoMode(1600, 1000), "JoJo Run");
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

float Game::getCreationRate() const {
    return creationRate;
}

void Game::throwKnife() {
    /*
    if (m_hero.getKnives() > 0 && (sf::Keyboard::isKeyPressed(sf::Keyboard::K))) {
        m_hero.setKnives(m_hero.getKnives() - 1);
        std::unique_ptr<PowerUp> knife = GF.createPowerUp(PowerUpType::ThrownKnife);
        knife->setPosition(sf::Vector2f(m_hero.getHeroPos().x, m_hero.getHeroPos().y));
        knives.emplace_back(std::move(knife));
    }
     */
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
    numLife.setString(std::to_string(m_hero.getHealth()));
    numLife.setPosition(1500, 3);
    numLife.setCharacterSize(40);
    numLife.setFillColor(sf::Color::White);

    knivesTxt.setFont(font);
    knivesTxt.setString("Knives");
    knivesTxt.setPosition(1400, 38);
    knivesTxt.setCharacterSize(35);
    knivesTxt.setFillColor(sf::Color::White);

    numKnives.setFont(font);
    numKnives.setString(std::to_string(m_hero.getKnives()));
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

void Game::moveHero() {
    m_hero.setHeroPos(m_hero.getHeroPos().x, m_hero.getHeroPos().y + g);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        m_hero.setHeroPos(m_hero.getHeroPos().x, m_hero.getHeroPos().y - jump);
        if (isShieldOn)
            m_hero.setShieldOn();
        else
            m_hero.setJumpOn();
    }
    else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
        if (isShieldOn)
            m_hero.setShieldOn();
        else
            m_hero.setStanding();
    }
    if (m_hero.getHeroPos().y + m_hero.getHeroSize().y >= m_window.getSize().y - ground)
        m_hero.setHeroPos(m_hero.getHeroPos().x, m_window.getSize().y - (m_hero.getHeroSize().y + ground));
    if (m_hero.getHeroPos().y <= top )
        m_hero.setHeroPos(m_hero.getHeroPos().x, top);
}

int Game::randomPosY() {
    int res = ((std::rand() % int(getWindowSize().y - this->top - this->ground - 85)) + this->top );
    return res;
}

int Game::randomCreation() {
    return (rand() % 3);
}

const sf::Vector2f &Game::getSpeed() const {
    return speed;
}

int Game::getMaxY() const {
    return maxY;
}

void Game::notify() {
    for (auto i = std::begin(observers); i != std::end(observers); i++)
        (*i)->update();
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
    return m_hero.getHealth();
}

void Game::setScore(unsigned int s) {
    Game::score = s;
    notify();
}

void Game::setHealth(int hp) {
    Game::m_hero.setHealth(hp);
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

void Game::setBlockCollision(bool blockCollision) {
    BlockCollision = blockCollision;
}

void Game::setEnemyCollision(bool enemyCollision) {
    EnemyCollision = enemyCollision;
}

void Game::setFirewallCollision(bool firewallCollision) {
    FirewallCollision = firewallCollision;
}

void Game::setKnifeCollision(bool knifeCollision) {
    KnifeCollision = knifeCollision;
}

void Game::setShieldPowerupCollision(bool shieldPowerupCollision) {
    ShieldPowerupCollision = shieldPowerupCollision;
}

void Game::setKnivesPowerupCollision(bool knivesPowerupCollision) {
    KnivesPowerupCollision = knivesPowerupCollision;
}

void Game::setIsShieldOn(bool isShieldOn) {
    Game::isShieldOn = isShieldOn;
}

void Game::setIsCollided(bool isCollided) {
    Game::isCollided = isCollided;
}

int Game::getEnemySize() {
    return static_cast<int>(m_scene.m_enemies.size());
}

int Game::getPowerUpSize() {
    return static_cast<int>(m_scene.m_powerups.size());
}

int Game::getKnivesSize() {
    return static_cast<int>(knives.size());
}

